#pragma once
#include <stdarg.h>
#include "../plat.h"

/* Opt-in native rendering diagnostics. No game state is changed. */
enum re_diag_counter {
    RE_DIAG_PROJECT_NEAR, RE_DIAG_PROJECT_FAR, RE_DIAG_CLIP_STALE,
    RE_DIAG_CLIP_FAR, RE_DIAG_CLIP_BEHIND, RE_DIAG_CLIP_EMITTED,
    RE_DIAG_POLY_EMPTY, RE_DIAG_BATCH_ROLLOVER, RE_DIAG_COUNTERS
};
void re_diag_start(void);
void re_diag_log(const char *fmt, ...);
void re_diag_logv(const char *fmt, va_list args);
void re_diag_count(enum re_diag_counter counter);
void re_diag_model(uint32_t model);
void re_diag_record(uint32_t record, unsigned type, int skipped);
void re_diag_draw(const plat_vertex *vertices, int count, unsigned mode,
                  int texture, int depth_test, int depth_write, int depth_func,
                  int blend, int src_blend, int dst_blend, int alpha_test,
                  int alpha_func, int alpha_ref);
void re_diag_request(void);
void re_diag_frame(int frame);
