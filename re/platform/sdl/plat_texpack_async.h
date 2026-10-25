/* v2.39: asynchronous HD texture pack loading (native only, docs/PERFORMANCE.md).  A cache miss of an 8-bit (page, palette)
   pair is queued; worker threads (SDL threads) read the PNG, decode it, compare it with the original page in that palette and
   build the CPU mip chain (plat_tex_prepare).  The GL upload happens on the main (GL) thread only, in re_tpa_pump() called once
   per displayed frame from plat_flip, within a time budget (texpack_upload_ms / RE_TEXPACK_UPLOAD_MS, at least one texture
   per frame).  Until a pair is uploaded the caller keeps drawing the original texture.  Workers never touch GL or game state:
   a request carries its own copy of the reference page and of the directory / level names.
   Асинхронная загрузка HD-пака: чтение, декодирование, сверка и мипмапы — в фоновых потоках, загрузка в GL — в главном. */
#ifndef RE_PLAT_TEXPACK_ASYNC_H
#define RE_PLAT_TEXPACK_ASYNC_H
#include <stdint.h>
#include "../plat.h"

enum { RE_TPA_MISSING = 0, RE_TPA_OK = 1, RE_TPA_REJECTED = 2, RE_TPA_FAILED = 3 };
typedef struct {
    int page, pal;          /* the pair as requested */
    unsigned tag;           /* caller's generation tag as requested (stale results are recognised by the caller) */
    int status;             /* RE_TPA_* */
    double err, amis, tol;  /* page check (RE_TPA_OK / RE_TPA_REJECTED) */
    int w;                  /* HD width */
    plat_tex_prep *prep;    /* RE_TPA_OK: prepared image; the callback owns it (plat_tex_create_prepared or plat_tex_prep_free) */
} re_tpa_result;
/* called on the main thread from re_tpa_pump (or re_tpa_drain) for every finished, not cancelled request */
typedef void (*re_tpa_done_fn)(re_tpa_result *r);

/* 1 — asynchronous loading is on: texpack_async in driver.cfg / RE_TEXPACK_ASYNC (default 1); read once */
int  re_tpa_on(void);
/* queue (page, pal) of `level` in pack `dir`; ref = the original page in that palette, 256x256 RGBA (copied).  Returns 1 if
   queued, 0 if the queue is full (the caller retries on a later draw), -1 if the worker threads are unavailable (the caller
   loads synchronously).  Main thread only;
   the caller dedupes (one request per pair in flight). */
int  re_tpa_request(const char *dir, const char *level, int page, int pal, unsigned tag, const uint32_t *ref, re_tpa_done_fn done);
/* main / GL thread, once per frame: hand finished requests to their callbacks within the upload budget */
void re_tpa_pump(void);
/* main thread: drop every queued and finished request; running ones are discarded when they finish (level change) */
void re_tpa_cancel(void);
/* stop and join the worker threads (atexit; safe to call twice) */
void re_tpa_shutdown(void);
/* requests queued, running or finished but not yet handed over */
int  re_tpa_inflight(void);
#endif
