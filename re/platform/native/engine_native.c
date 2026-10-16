/* Нативные реализации сервисов движка (замена DebugMalloc/DebugFree/DebugLog из Game.exe) */
#include "../../game/engine.h"
#include <stdio.h>
#include <stdlib.h>
/* v2.13: calloc — как оригинал 004d8db4 (обнуляет блок через 0048db65); без этого поведение зависело от libc (macOS malloc / MALLOC_PERTURB_) */
void *DebugMalloc(int size, const char *file, int line) { (void)file; (void)line; return calloc(1, size > 0 ? (size_t)size : 1); }
void  DebugFree(void *ptr) { free(ptr); }
void  DebugLog(const char *msg) {
    fprintf(stderr, "[debug] %s\n", msg);
    FILE *f = fopen("debug.log", "a"); if (f) { fprintf(f, "%s\n", msg); fclose(f); }
}
