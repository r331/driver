/* reprof.c — RE_PROFILE=N: native frame profiler (see game/reprof.h, docs/PERFORMANCE.md).  Every N displayed
   frames prints the average milliseconds per zone, the per-frame counter averages and the slowest frame. */
#include "../../game/reprof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int re_prof_on;
static int g_every, g_n, g_total, g_depth[RP_ZONES];
static double g_t0[RP_ZONES], g_acc[RP_ZONES], g_win[RP_ZONES], g_frame_t0, g_worst, g_worst_acc[RP_ZONES];
static long g_cnt[RC_COUNTERS], g_cwin[RC_COUNTERS], g_worst_cnt[RC_COUNTERS];
static const char *k_zone[RP_ZONES] = { "frame", "logic", "l.cars", "l.traffic", "l.map", "draw", "d.map", "d.player", "d.traffic", "d.fx", "d.hud", "gl_draw", "tex_up", "swap", "hd_load", "detail_load" };
static const char *k_cnt[RC_COUNTERS] = { "draws", "verts", "tex_up", "tex_px", "tex_var", "surf_up", "pal8", "detail", "ticks", "cars", "hd_loads", "pal_inval" };
void plat_gfx_logf(const char *fmt, ...);

static double now_ms(void) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return ts.tv_sec * 1e3 + ts.tv_nsec / 1e6; }
__attribute__((constructor)) static void prof_init(void) {
    const char *e = getenv("RE_PROFILE");
    g_every = e ? atoi(e) : 0; if (e && *e && g_every <= 0) g_every = 120;
    re_prof_on = g_every > 0;
}
/* a zone re-entered while open (an upload inside an upload) is timed once, by its outermost pair */
void re_prof_begin(int z) { if (z >= 0 && z < RP_ZONES && g_depth[z]++ == 0) g_t0[z] = now_ms(); }
void re_prof_end(int z) { if (z >= 0 && z < RP_ZONES && g_depth[z] > 0 && --g_depth[z] == 0) g_acc[z] += now_ms() - g_t0[z]; }
void re_prof_count(int c, long n) { if (c >= 0 && c < RC_COUNTERS) g_cnt[c] += n; }
void re_prof_frame(void) {
    double t = now_ms();
    if (g_frame_t0 > 0) {
        g_acc[RP_FRAME] = t - g_frame_t0;
        if (g_acc[RP_FRAME] > g_worst) { g_worst = g_acc[RP_FRAME]; memcpy(g_worst_acc, g_acc, sizeof g_acc); memcpy(g_worst_cnt, g_cnt, sizeof g_cnt); }
        for (int i = 0; i < RP_ZONES; i++) g_win[i] += g_acc[i];
        for (int i = 0; i < RC_COUNTERS; i++) g_cwin[i] += g_cnt[i];
        g_n++; g_total++;
    }
    g_frame_t0 = t;
    memset(g_acc, 0, sizeof g_acc); memset(g_cnt, 0, sizeof g_cnt);
    if (g_n < g_every) return;
    char b[2048]; int o = snprintf(b, sizeof b, "[prof] frames %d..%d avg ms:", g_total - g_n + 1, g_total);
    for (int i = 0; i < RP_ZONES && o < (int)sizeof b; i++) o += snprintf(b + o, sizeof b - o, " %s=%.2f", k_zone[i], g_win[i] / g_n);
    if (o < (int)sizeof b) o += snprintf(b + o, sizeof b - o, " | per frame:");
    for (int i = 0; i < RC_COUNTERS && o < (int)sizeof b; i++) o += snprintf(b + o, sizeof b - o, " %s=%.1f", k_cnt[i], (double)g_cwin[i] / g_n);
    if (o < (int)sizeof b) o += snprintf(b + o, sizeof b - o, " | worst frame %.2f ms:", g_worst);
    for (int i = 1; i < RP_ZONES && o < (int)sizeof b; i++) if (g_worst_acc[i] >= 0.05) o += snprintf(b + o, sizeof b - o, " %s=%.2f", k_zone[i], g_worst_acc[i]);
    for (int i = 0; i < RC_COUNTERS && o < (int)sizeof b; i++) if (g_worst_cnt[i]) o += snprintf(b + o, sizeof b - o, " %s=%ld", k_cnt[i], g_worst_cnt[i]);
    if (o < (int)sizeof b) snprintf(b + o, sizeof b - o, "\n");
    plat_gfx_logf("%s", b);   /* stderr + driver_gfx.log */
    memset(g_win, 0, sizeof g_win); memset(g_cwin, 0, sizeof g_cwin); g_n = 0; g_worst = 0;
}
