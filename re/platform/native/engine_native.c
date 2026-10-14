/* Нативные реализации сервисов движка (замена DebugMalloc/DebugFree/DebugLog из Game.exe) */
#include "../../game/engine.h"
#include <stdio.h>
#include <stdlib.h>
void *DebugMalloc(int size, const char *file, int line) { (void)file; (void)line; return malloc(size > 0 ? (size_t)size : 1); }
void  DebugFree(void *ptr) { free(ptr); }
void  DebugLog(const char *msg) {
    fprintf(stderr, "[debug] %s\n", msg);
    FILE *f = fopen("debug.log", "a"); if (f) { fprintf(f, "%s\n", msg); fclose(f); }
}
