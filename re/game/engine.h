/* Базовые сервисы движка (в Game.exe: DebugMalloc 004d8db4, DebugFree 004d8f30, DebugLog 004bf2a0). */
#pragma once
#include "gvar.h"
#ifdef RE_HOOK_BUILD
#  define DebugMalloc ((void*(__cdecl*)(int, const char*, int))0x004d8db4)
#  define DebugFree   ((void (__cdecl*)(void*))0x004d8f30)
#  define DebugLog    ((void (__cdecl*)(const char*))0x004bf2a0)
#else
void *DebugMalloc(int size, const char *file, int line);
void  DebugFree(void *ptr);
void  DebugLog(const char *msg);
#endif
