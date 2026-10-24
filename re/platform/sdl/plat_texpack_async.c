/* plat_texpack_async.c — v2.39: asynchronous HD texture pack loading, see plat_texpack_async.h and docs/PERFORMANCE.md.
   A fixed pool of RE_TPA_JOBS request slots (bounded queue) shared by the main thread and RE_TEXPACK_THREADS worker threads
   (default 2) under one mutex.  Slot life: FREE -> QUEUED (main) -> RUNNING (worker) -> DONE (worker) -> FREE (main, pump).
   re_tpa_cancel bumps the epoch: queued and finished slots are freed at once, a running slot is freed by the pump when it
   finishes.  Workers call only thread-safe code: re_texpack_load8_tol (file read + stb_image), re_texpack_compare_rgba,
   plat_tex_prepare (no GL), RE_LOG (mutex).  Фоновая загрузка HD-пака: пул заявок, рабочие потоки SDL, GL — только главный поток. */
#include "plat_texpack_async.h"
#include "plat_texpack.h"
#include "plat_gfx.h"
#include "../plat_log.h"
#include "../../game/reprof.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RE_TPA_JOBS 64
#define RE_TPA_MAX_THREADS 8
enum { J_FREE, J_QUEUED, J_RUNNING, J_DONE };
typedef struct {
    int state; unsigned seq, epoch;
    char dir[1024], level[128];
    uint32_t *ref;              /* 256x256 RGBA copy of the original page in the pair's palette */
    re_tpa_done_fn done;
    re_tpa_result r;
} tpa_job;

static tpa_job g_job[RE_TPA_JOBS];
static SDL_mutex *g_mx; static SDL_cond *g_cv;
static SDL_Thread *g_th[RE_TPA_MAX_THREADS]; static int g_nth, g_quit, g_started, g_failed;
static unsigned g_seq, g_epoch;

int re_tpa_on(void) {
    static int on = -1;
    if (on < 0) on = re_gfx()->texpack_async ? 1 : 0;   /* RE_TEXPACK_ASYNC is applied to the config by re_gfx_env */
    return on;
}
/* job_work — worker side of one request: load + decode, page check, CPU mip chain.  No shared state. */
static void job_work(tpa_job *j) {
    re_tpa_result *r = &j->r;
    int w = 0, h = 0; double tol = RE_TEXPACK_MAX_ERR;
    uint32_t *hd = re_texpack_load8_tol(j->dir, j->level, r->page, r->pal, &w, &h, &tol);
    r->tol = tol; r->prep = NULL; r->w = w;
    if (!hd) { r->status = RE_TPA_MISSING; return; }
    double err = 0, am = 0;
    re_texpack_compare_rgba(hd, w, h, j->ref, &err, &am);
    r->err = err; r->amis = am;
    if (err > tol || am > RE_TEXPACK_MAX_AMIS) { free(hd); r->status = RE_TPA_REJECTED; return; }
    r->prep = plat_tex_prepare(w, h, hd);   /* takes hd */
    r->status = r->prep ? RE_TPA_OK : RE_TPA_FAILED;
}
static int worker(void *arg) {
    (void)arg;
    SDL_LockMutex(g_mx);
    for (;;) {
        tpa_job *j = NULL;
        while (!g_quit) {
            for (int i = 0; i < RE_TPA_JOBS; i++)   /* oldest queued request first */
                if (g_job[i].state == J_QUEUED && (!j || (int)(g_job[i].seq - j->seq) < 0)) j = &g_job[i];
            if (j) break;
            SDL_CondWait(g_cv, g_mx);
        }
        if (g_quit) break;
        j->state = J_RUNNING;
        SDL_UnlockMutex(g_mx);
        job_work(j);
        SDL_LockMutex(g_mx);
        free(j->ref); j->ref = NULL;
        j->state = J_DONE;
    }
    SDL_UnlockMutex(g_mx);
    return 0;
}
static void job_clear(tpa_job *j) {   /* under g_mx or after the threads stopped */
    free(j->ref); j->ref = NULL;
    if (j->r.prep) { plat_tex_prep_free(j->r.prep); j->r.prep = NULL; }
    j->state = J_FREE;
}
static int start(void) {
    if (g_started) return !g_failed;
    g_started = 1;
    const char *e = getenv("RE_TEXPACK_THREADS");
    int n = e && *e ? atoi(e) : 2;
    if (n < 1) n = 1;
    if (n > RE_TPA_MAX_THREADS) n = RE_TPA_MAX_THREADS;
    g_mx = SDL_CreateMutex(); g_cv = SDL_CreateCond();
    if (!g_mx || !g_cv) { g_failed = 1; RE_LOGW(load, "HD-пак: асинхронная загрузка недоступна (SDL_CreateMutex/Cond: %s) — синхронно", SDL_GetError()); return 0; }
    for (int i = 0; i < n; i++) {
        char name[32]; snprintf(name, sizeof name, "texpack%d", i);
        if ((g_th[g_nth] = SDL_CreateThread(worker, name, NULL))) g_nth++;
    }
    if (!g_nth) { g_failed = 1; RE_LOGW(load, "HD-пак: асинхронная загрузка недоступна (SDL_CreateThread: %s) — синхронно", SDL_GetError()); return 0; }
    atexit(re_tpa_shutdown);
    RE_LOGI(load, "HD-пак: асинхронная загрузка, потоков %d, бюджет загрузки в GL %.1f мс/кадр", g_nth, re_gfx()->texpack_upload_ms);
    return 1;
}
int re_tpa_request(const char *dir, const char *level, int page, int pal, unsigned tag, const uint32_t *ref, re_tpa_done_fn done) {
    if (!dir || !level || !ref || !done) return 0;
    if (!start()) return -1;
    uint32_t *copy = (uint32_t *)malloc(256 * 256 * 4);
    if (!copy) return 0;
    memcpy(copy, ref, 256 * 256 * 4);
    SDL_LockMutex(g_mx);
    tpa_job *j = NULL;
    for (int i = 0; i < RE_TPA_JOBS && !j; i++) if (g_job[i].state == J_FREE) j = &g_job[i];
    if (!j) { SDL_UnlockMutex(g_mx); free(copy); return 0; }   /* bounded: full — the caller asks again on a later draw */
    memset(j, 0, sizeof *j);
    snprintf(j->dir, sizeof j->dir, "%s", dir); snprintf(j->level, sizeof j->level, "%s", level);
    j->ref = copy; j->done = done; j->seq = ++g_seq; j->epoch = g_epoch;
    j->r.page = page; j->r.pal = pal; j->r.tag = tag;
    j->state = J_QUEUED;
    SDL_CondSignal(g_cv);
    SDL_UnlockMutex(g_mx);
    return 1;
}
static double budget_ms(void) { double b = re_gfx()->texpack_upload_ms; return b > 0 ? b : 0; }
/* re_tpa_pump — oldest finished request first.  An image to upload (RE_TPA_OK) is taken only while the frame's budget lasts,
   and always at least one per frame; missing / rejected results cost nothing and are always handed over. */
void re_tpa_pump(void) {
    if (!g_started || g_failed) return;
    RP_BEGIN(RP_HD_UPLOAD);
    Uint64 f = SDL_GetPerformanceFrequency(), t0 = SDL_GetPerformanceCounter();
    double budget = budget_ms();
    int uploaded = 0;
    for (;;) {
        int over = uploaded > 0 && (budget <= 0 || (double)(SDL_GetPerformanceCounter() - t0) * 1000.0 / (double)f >= budget);
        tpa_job tmp; int found = 0;
        SDL_LockMutex(g_mx);
        tpa_job *j = NULL;
        for (int i = 0; i < RE_TPA_JOBS; i++) {
            tpa_job *c = &g_job[i];
            if (c->state != J_DONE) continue;
            if (c->epoch != g_epoch) { job_clear(c); continue; }   /* cancelled while it was running */
            if (over && c->r.status == RE_TPA_OK) continue;          /* budget spent: uploads wait for the next frame */
            if (!j || (int)(c->seq - j->seq) < 0) j = c;
        }
        if (j) { tmp = *j; j->r.prep = NULL; j->ref = NULL; j->state = J_FREE; found = 1; }
        SDL_UnlockMutex(g_mx);
        if (!found) break;
        int costly = tmp.r.status == RE_TPA_OK;
        tmp.done(&tmp.r);   /* the callback owns tmp.r.prep */
        if (costly) { uploaded++; RP_COUNT(RC_HD_UPLOADS, 1); }
    }
    RP_END(RP_HD_UPLOAD);
}
void re_tpa_cancel(void) {
    if (!g_started || g_failed) return;
    SDL_LockMutex(g_mx);
    g_epoch++;
    for (int i = 0; i < RE_TPA_JOBS; i++) if (g_job[i].state == J_QUEUED || g_job[i].state == J_DONE) job_clear(&g_job[i]);
    SDL_UnlockMutex(g_mx);
}
int re_tpa_inflight(void) {
    if (!g_started || g_failed) return 0;
    int n = 0;
    SDL_LockMutex(g_mx);
    for (int i = 0; i < RE_TPA_JOBS; i++) if (g_job[i].state != J_FREE && g_job[i].epoch == g_epoch) n++;
    SDL_UnlockMutex(g_mx);
    return n;
}
void re_tpa_shutdown(void) {
    if (!g_started || g_failed || !g_mx) return;
    SDL_LockMutex(g_mx); g_quit = 1; SDL_CondBroadcast(g_cv); SDL_UnlockMutex(g_mx);
    for (int i = 0; i < g_nth; i++) SDL_WaitThread(g_th[i], NULL);
    g_nth = 0;
    for (int i = 0; i < RE_TPA_JOBS; i++) job_clear(&g_job[i]);
    g_failed = 1;   /* stopped: further requests fall back to the synchronous path */
}
