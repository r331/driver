#include "diagnostics.h"
#include "../sdl/plat_gfx.h"
#include "../../game/ported11.h"
#include "../../game/ported19.h"
#include "../../game/ported44.h"
#include "../../game/ported59.h"
#include "../../game/ported62.h"
#include "../../game/ported77.h"
#include "../../game/ported85.h"
#include "../../game/ported87.h"
#include "../../game/ported88.h"
#include "../../game/ported110.h"
#include "../../game/cartab.h"
#include <SDL.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#if defined(_WIN32)
#include <direct.h>
#include <process.h>
#define diag_mkdir(p) _mkdir(p)
#define diag_pid() _getpid()
#else
#include <unistd.h>
#define diag_mkdir(p) mkdir(p, 0755)
#define diag_pid() getpid()
#endif

#ifndef RE_BUILD_REV
#define RE_BUILD_REV "unknown"
#endif
#define HISTORY 600
#define LOG_LIMIT (16u * 1024u * 1024u)
#define VERTEX_LIMIT 150000u
#define CAPTURE_LIMIT 10
static int enabled, requested, capturing, captures, last_frame;
static FILE *session, *timeline, *draws, *records, *clipping;
static SDL_mutex *log_lock;
static unsigned long log_bytes, rows, vertices, draw_id, clip_rows;
static unsigned long counters[RE_DIAG_COUNTERS], types[256], skips[256];
static uint32_t model_id = UINT32_MAX, record_id = UINT32_MAX;
static unsigned record_type;
static char directory[2048], capture[2304], history[HISTORY][1536];
static unsigned history_count, history_next;
int png_write_rgba(const char *path, const uint32_t *px, int w, int h);
extern int g_re_dbg[16];
static const char *csv_header =
    "frame,wall_ms,level_frame,car_x,car_y,car_z,heading,speed,cam_x,cam_y,cam_z,cam_angle,cam_mode,"
    "far,mirror_far,scale,draw_multiplier,cell_x,cell_y,slot0,slot1,slot2,slot3,drawable_w,drawable_h,"
    "logical_w,logical_h,content_x,content_y,content_w,content_h,target_w,target_h,fbo,"
    "project_near,project_far,clip_stale,clip_far,clip_behind,clip_emitted,poly_empty,batch_rollovers\n";

static void copy_file(const char *from, const char *to) {
    FILE *in = fopen(from, "rb"); if (!in) return;
    FILE *out = fopen(to, "wb");
    if (out) { char b[4096]; size_t n, total = 0;
        while (total < 65536 && (n = fread(b, 1, sizeof b, in)) != 0) {
            if (fwrite(b, 1, n, out) != n) break;
            total += n;
        }
        fclose(out);
    }
    fclose(in);
}
static void shutdown_diag(void) {
    if (log_lock) SDL_LockMutex(log_lock);
    enabled = 0;
    if (session) { fprintf(session, "Diagnostics ended at frame %d%s\n", last_frame,
                          capturing ? " (capture incomplete)" : ""); fclose(session); session = NULL; }
    if (timeline) { fclose(timeline); timeline = NULL; }
    if (draws) { fclose(draws); draws = NULL; }
    if (records) { fclose(records); records = NULL; }
    if (clipping) { fclose(clipping); clipping = NULL; }
    if (log_lock) SDL_UnlockMutex(log_lock);
}
void re_diag_start(void) {
    const char *e = getenv("RE_DIAG");
    if (!e || !*e || !strcmp(e, "0") || enabled) return;
    const char *root = getenv("RE_DIAG_DIR"); if (!root || !*root) root = "Diagnostics";
    if (diag_mkdir(root) != 0 && errno != EEXIST) { fprintf(stderr, "[diag] cannot create %s: %s\n", root, strerror(errno)); return; }
    time_t now = time(NULL); char stamp[64];
    strftime(stamp, sizeof stamp, "%Y%m%d-%H%M%S", localtime(&now));
    int n = snprintf(directory, sizeof directory, "%s/session-%s-%ld", root, stamp, (long)diag_pid());
    if (n < 0 || (size_t)n >= sizeof directory || diag_mkdir(directory) != 0) {
        fprintf(stderr, "[diag] cannot create session directory\n"); return;
    }
    char path[2304]; snprintf(path, sizeof path, "%s/session.log", directory);
    session = fopen(path, "w"); if (!session) return;
    log_lock = SDL_CreateMutex();
    if (!log_lock) { fclose(session); session = NULL; return; }
    snprintf(path, sizeof path, "%s/timeline.csv", directory); timeline = fopen(path, "w");
    if (timeline) { fputs(csv_header, timeline); fflush(timeline); }
    enabled = 1; atexit(shutdown_diag);
    /* Keep the existing GL diagnostics (vendor, errors, FBO/window events) with this session. */
    if (!getenv("RE_GFXLOG")) {
        snprintf(path, sizeof path, "%s/graphics.log", directory);
#if defined(_WIN32)
        _putenv_s("RE_GFXLOG", path);
#else
        setenv("RE_GFXLOG", path, 0);
#endif
    }
    fprintf(stderr, "[diag] saving diagnostics in %s\n[diag] capture: Cmd+Shift+D (Mac), Ctrl+Shift+D (Linux/Windows)\n", directory);
    re_diag_log("Driver diagnostics v1; build %s; compiled %s %s; platform %s; pointer bits %u\n",
                RE_BUILD_REV, __DATE__, __TIME__, SDL_GetPlatform(), (unsigned)(sizeof(void *) * 8));
    re_diag_log("Session: %s; last 600 frames per capture; max 10 captures, 150000 vertices/capture, 16 MiB session log\n", directory);
    /* Explicit whitelist: do not collect unrelated environment variables or credentials. */
    static const char *const names[] = { "RE_PRESET", "RE_DRAW_DIST", "RE_TEXPACK", "RE_TEXPACK_SKY", "RE_SKYFIX",
        "RE_NO_FBO", "RE_FBO", "RE_ASPECT", "RE_WINDOWED", "RE_FULLSCREEN", "RE_RES", "RE_GAME_RES", "RE_CFG",
        "RE_MSAA", "RE_A2C", "RE_FXAA", "RE_MIPMAPS", "RE_FILTER", "RE_ANISO", "RE_RENDER_SCALE", "RE_VSYNC",
        "RE_FIXED_DT", "RE_KEYS", "RE_TELEPORT", "RE_DIAG_CAPTURE_FRAME", "RE_GAMEPAD", "RE_RUMBLE", "RE_INPUTDBG",
        "SDL_JOYSTICK_HIDAPI_STEAM", "SDL_GAMECONTROLLERCONFIG" };
    for (unsigned i = 0; i < sizeof names / sizeof names[0]; i++) {
        const char *v = getenv(names[i]); if (v) re_diag_log("%s=%s\n", names[i], v);
    }
    snprintf(path, sizeof path, "%s/config-at-start.dat", directory); copy_file("config.dat", path);
}
void re_diag_logv(const char *fmt, va_list args) {
    if (!enabled || !log_lock) return;
    SDL_LockMutex(log_lock);
    if (session && log_bytes < LOG_LIMIT) {
        int a = fprintf(session, "[%u ms frame %d] ", SDL_GetTicks(), last_frame);
        int b = vfprintf(session, fmt, args);
        if (a > 0) log_bytes += (unsigned)a;
        if (b > 0) log_bytes += (unsigned)b;
        if (log_bytes >= LOG_LIMIT) fputs("\nSession log limit reached; telemetry/captures remain available.\n", session);
        fflush(session);
    }
    SDL_UnlockMutex(log_lock);
}
void re_diag_log(const char *fmt, ...) { va_list a; va_start(a, fmt); re_diag_logv(fmt, a); va_end(a); }
void re_diag_count(enum re_diag_counter c) {
    if (!enabled || (unsigned)c >= RE_DIAG_COUNTERS) return;
    counters[c]++;
    if (clipping && c >= RE_DIAG_CLIP_STALE && c <= RE_DIAG_CLIP_BEHIND && clip_rows++ < VERTEX_LIMIT) {
        fprintf(clipping, "%08x,%08x,%u,%u", model_id, record_id, record_type, (unsigned)c);
        for (int i = 0; i < 3; i++) fprintf(clipping, ",%.9g,%.9g,%.9g", P85_RV[i].x, P85_RV[i].y, P85_RV[i].oow);
        fputc('\n', clipping);
    }
}
void re_diag_model(uint32_t model) { if (enabled) { model_id = model; record_id = UINT32_MAX; record_type = 256; } }
void re_diag_record(uint32_t rec, unsigned type, int skipped) {
    if (!enabled) return;
    record_id = rec; record_type = type;
    if (type < 256) { types[type]++; if (skipped) skips[type]++; }
    if (records) {
        if (rows < VERTEX_LIMIT) fprintf(records, "%08x,%08x,%u,%d\n", model_id, rec, type, skipped);
        rows++;
    }
}
void re_diag_draw(const plat_vertex *v, int count, unsigned mode, int tex, int zt, int zw, int zf,
                  int blend, int src, int dst, int at, int af, int ar) {
    if (!draws || !v || count <= 0) return;
    draw_id++;
    for (int i = 0; i < count && vertices < VERTEX_LIMIT; i++, vertices++) {
        fprintf(draws, "%lu,%u,%08x,%08x,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%08x\n",
                draw_id, mode, model_id, record_id, record_type, tex, zt, zw, zf, blend, src, dst, at, af, ar, i,
                v[i].x, v[i].y, v[i].z, v[i].rhw, v[i].u, v[i].v, v[i].color);
    }
}
void re_diag_request(void) {
    if (!enabled) { fprintf(stderr, "[diag] enable diagnostics with RE_DIAG=1\n"); return; }
    if (captures >= CAPTURE_LIMIT) { re_diag_log("Capture limit reached\n"); return; }
    if (!capturing) requested = 1;
}
static void state_file(int frame) {
    char path[2304]; snprintf(path, sizeof path, "%s/state.txt", capture);
    FILE *f = fopen(path, "w"); if (!f) return;
    char settings[2048]; re_gfx_describe(re_gfx(), settings, sizeof settings);
    fprintf(f, "build=%s\nframe=%d\nlevel=%s\n%s\n", RE_BUILD_REV, frame, P77_CurLevelPath, settings);
    fprintf(f, "car angles=%d,%d,%d heading=%d\ncamera matrix=", P99_Cars[0].ang[0], P99_Cars[0].ang[1], P99_Cars[0].ang[2], P99_Cars[0].heading);
    for (int i = 0; i < 9; i++) fprintf(f, " %.9g", P44_ViewMat[i]);
    fprintf(f, "\nclip=%.9g,%.9g,%.9g,%.9g\nviewport extra=%d\ndebug counters (cumulative unless RE_GSTAT resets them)=", P110_ClipX0, P110_ClipY0, P110_ClipX1, P110_ClipY1, plat_view_extra());
    for (int i = 0; i < 16; i++) fprintf(f, " %d", g_re_dbg[i]);
    fprintf(f, "\nvertex rows=%lu (limit %u)\nrecord rows=%lu (limit %u)\n", vertices, VERTEX_LIMIT, rows, VERTEX_LIMIT);
    fprintf(f, "clipping rows=%lu (limit %u)\n", clip_rows, VERTEX_LIMIT);
    int a = 0, u = 0, r = 0, p8 = 0; plat_dd_hd_stats(&a, &u, &r, &p8);
    fprintf(f, "HD attached=%d uploaded=%d rejected=%d palette_binds=%d\nrecord types: type,dispatched,skipped\n", a, u, r, p8);
    for (int i = 0; i < 256; i++) if (types[i]) fprintf(f, "%d,%lu,%lu\n", i, types[i], skips[i]);
    fclose(f);
    snprintf(path, sizeof path, "%s/config.dat", capture); copy_file("config.dat", path);
    if (re_gfx()->source[0]) { snprintf(path, sizeof path, "%s/driver.cfg", capture); copy_file(re_gfx()->source, path); }
}
static void finish_capture(int frame) {
    if (draws) { fclose(draws); draws = NULL; }
    if (records) { fclose(records); records = NULL; }
    if (clipping) { fclose(clipping); clipping = NULL; }
    char path[2304]; snprintf(path, sizeof path, "%s/frames.csv", capture);
    FILE *f = fopen(path, "w");
    if (f) { fputs(csv_header, f); unsigned first = (history_next + HISTORY - history_count) % HISTORY;
        for (unsigned i = 0; i < history_count; i++) fputs(history[(first + i) % HISTORY], f);
        fclose(f);
    }
    state_file(frame);
    int w = 0, h = 0; plat_render_size(&w, &h, NULL, NULL);
    int ok = 0;
    if (w > 0 && h > 0 && (size_t)w <= SIZE_MAX / 4 / (size_t)h) {
        uint32_t *px = malloc((size_t)w * h * 4);
        if (px) { snprintf(path, sizeof path, "%s/screenshot.png", capture);
            ok = plat_render_readback(px) == 0 && png_write_rgba(path, px, w, h) == 0; free(px); }
    }
    re_diag_log("CAPTURE %d frame %d screenshot=%s path=%s\n", captures, frame, ok ? "ok" : "failed", capture);
    fprintf(stderr, "[diag] capture saved: %s (screenshot %s)\n", capture, ok ? "ok" : "failed");
    capturing = 0;
}
static void begin_capture(int frame) {
    snprintf(capture, sizeof capture, "%s/capture-%02d-frame-%06d", directory, ++captures, frame + 1);
    if (diag_mkdir(capture) != 0) { re_diag_log("Cannot create capture: %s\n", strerror(errno)); return; }
    char path[2400]; snprintf(path, sizeof path, "%s/draws.csv", capture); draws = fopen(path, "w");
    if (draws) fputs("draw,mode,model_offset,record_offset,record_type,texture,ztest,zwrite,zfunc,blend,src,dst,alpha_test,alpha_func,alpha_ref,vertex,x,y,depth,rhw,u,v,color\n", draws);
    snprintf(path, sizeof path, "%s/records.csv", capture); records = fopen(path, "w");
    if (records) fputs("model_offset,record_offset,type,skipped\n", records);
    snprintf(path, sizeof path, "%s/clipping.csv", capture); clipping = fopen(path, "w");
    if (clipping) fputs("model_offset,record_offset,type,reason,x0,y0,oow0,x1,y1,oow1,x2,y2,oow2\n", clipping);
    vertices = rows = draw_id = clip_rows = 0; capturing = 1;
}
void re_diag_frame(int frame) {
    if (!enabled) return;
    int dw, dh, lw, lh, x, y, w, h, tw, th;
    plat_render_size(&dw, &dh, &lw, &lh); plat_render_content(&x, &y, &w, &h, &tw, &th);
    const p99_car_t *c = &P99_Cars[0]; last_frame = frame;
    snprintf(history[history_next], sizeof history[0],
        "%d,%u,%d,%d,%d,%d,%d,%d,%.9g,%.9g,%.9g,%d,%d,%.9g,%.9g,%.9g,%.9g,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu\n",
        frame, SDL_GetTicks(), P62_Frame, c->pos[0], c->pos[1], c->pos[2], c->heading, c->speed,
        P44_CamX, P44_CamY, P44_CamZ, (int)(int16_t)P59_AngB, P59_Mode1137324,
        P11_01270c24, P11_0125f3f8, P19_Scale, re_gfx()->draw_distance, P88_CellA.x, P88_CellA.y,
        P87_SlotLumpA[0], P87_SlotLumpA[1], P87_SlotLumpA[2], P87_SlotLumpA[3],
        dw, dh, lw, lh, x, y, w, h, tw, th, plat_render_fbo_on(),
        counters[0], counters[1], counters[2], counters[3], counters[4], counters[5], counters[6], counters[7]);
    if (timeline && frame % 30 == 0 && frame <= 600000) { fputs(history[history_next], timeline); fflush(timeline); }
    history_next = (history_next + 1) % HISTORY; if (history_count < HISTORY) history_count++;
    if (capturing) finish_capture(frame);
    const char *auto_frame = getenv("RE_DIAG_CAPTURE_FRAME");
    if (auto_frame && atoi(auto_frame) == frame) re_diag_request();
    if (requested) { requested = 0; begin_capture(frame); }
    memset(counters, 0, sizeof counters); memset(types, 0, sizeof types); memset(skips, 0, sizeof skips);
    model_id = record_id = UINT32_MAX; record_type = 256;
}
