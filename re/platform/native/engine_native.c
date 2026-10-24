/* Нативные реализации сервисов движка (замена DebugMalloc/DebugFree/DebugLog из Game.exe) */
#include "../../game/engine.h"
#include "diagnostics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* v2.13: calloc — как оригинал 004d8db4 (обнуляет блок через 0048db65); без этого поведение зависело от libc (macOS malloc / MALLOC_PERTURB_) */
/* v2.37: RE_LOG mem — NULL от calloc (error), крупные блоки ≥ 1 МиБ (debug), каждый вызов (trace); file/line — из кода игры */
void *DebugMalloc(int size, const char *file, int line) {
    void *p = calloc(1, size > 0 ? (size_t)size : 1);
    if (!p) RE_LOGE(mem, "DebugMalloc(%d) из %s:%d — нет памяти (NULL)", size, file ? file : "?", line);
    else if (size >= (1 << 20)) RE_LOGD(mem, "DebugMalloc %d байт (%.1f МиБ) из %s:%d -> %p", size, size / 1048576.0, file ? file : "?", line, p);
    else RE_LOGT(mem, "DebugMalloc %d байт из %s:%d -> %p", size, file ? file : "?", line, p);
    if (size < 0) RE_LOGW(mem, "DebugMalloc: отрицательный размер %d из %s:%d", size, file ? file : "?", line);
    return p;
}
void  DebugFree(void *ptr) { RE_LOGT(mem, "DebugFree %p", ptr); free(ptr); }
void  DebugLog(const char *msg) {
    /* «not ported: …» (stubs.c — вызвана не перенесённая функция) и ERROR — предупреждения, остальное — info */
    if (msg && (!strncmp(msg, "not ported", 10) || strstr(msg, "ERROR") || strstr(msg, "Error"))) RE_LOGW(game, "DebugLog: %s", msg);
    else RE_LOGI(game, "DebugLog: %s", msg ? msg : "(null)");
    re_diag_log("[debug] %s\n", msg);
    fprintf(stderr, "[debug] %s\n", msg);
    FILE *f = fopen("debug.log", "a"); if (f) { fprintf(f, "%s\n", msg); fclose(f); }
}
