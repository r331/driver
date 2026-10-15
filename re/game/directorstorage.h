/* DirectorStorage — сохранение данных режиссёра в файл повтора. */
#pragma once
#include "director.h"
typedef struct CHUNK_HEADER {
    uint32_t magic;     /* 'RDPR', 'WYPT', 'RCAM' (little-endian) */
    uint32_t size;      /* размер чанка вместе с заголовком */
    uint32_t version;
} CHUNK_HEADER;
_Static_assert(sizeof(CHUNK_HEADER) == 12, "CHUNK_HEADER size");
#define WaypointDirty   GAME_VAR(int32_t, WaypointDirty,   0x00d17b30)
#define WaypointCount   GAME_VAR(int32_t, WaypointCount,   0x00d17b40)
#define PlayerPosX      CARTAB_VAR(int32_t, PlayerPosX,      0x00d07888)
#define PlayerPosZ      CARTAB_VAR(int32_t, PlayerPosZ,      0x00d07890)
#ifndef RE_HOOK_BUILD
extern int32_t WaypointDirty, WaypointCount;
#endif
void WriteReplayHeaderChunk(void *file);   /* 004c988e */
void WriteWaypointChunk(void *file);       /* 004c96d6 */
void WriteCameraChunk(void *file);         /* 004c97a2 */
void WriteDirectorData(void *file);        /* 004c9621 */
void LogWaypoint(int frame);               /* 004c9bf4 */
void ReadDirectorData(void *file);         /* 004c93e6 */
void ReadCameraChunkV2(void *file);        /* 004c98de — камеры текущего формата (0x8c байт) */
void ReadCameraChunkV1(void *file);        /* 004c9a16 — камеры старого формата (0x3c байт) */
int  LoadWaypoints(void);                  /* 004c9ca0 */
void DeleteWaypointFile(void);             /* 004c9dcc */
