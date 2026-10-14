#include "directorstorage.h"
#include "crt.h"
GAME_VAR_DEF(int32_t, WaypointDirty, 0x00d17b30)
GAME_VAR_DEF(int32_t, WaypointCount, 0x00d17b40)
GAME_VAR_DEF(int32_t, PlayerPosX, 0x00d07888)
GAME_VAR_DEF(int32_t, PlayerPosZ, 0x00d07890)

/* после записи содержимого чанка в заголовок пишется реальный размер */
static void finish_chunk(void *f, long start, CHUNK_HEADER *h) {
    long end = g_ftell(f);
    h->size = (uint32_t)(end - start);
    g_fseek(f, start, 0);
    g_fwrite(h, 12, 1, f);
    g_fseek(f, end, 0);
}

void WriteReplayHeaderChunk(void *f) {
    CHUNK_HEADER h = { 0x52445052, 0x10, 1 };
    g_fwrite(&h, 12, 1, f);
    int32_t last = DirectorLastFrame;
    g_fwrite(&last, 4, 1, f);
}

void WriteWaypointChunk(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { 0x54505957, 0, 1 };
    g_fwrite(&h, 12, 1, f);
    int32_t n = DirectorBufferCount;
    g_fwrite(&n, 4, 1, f);
    if (n != 0) g_fwrite(DirectorBuffer, 12, (size_t)n, f);
    finish_chunk(f, start, &h);
}

void WriteCameraChunk(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { 0x4d414352, 0, 2 };
    g_fwrite(&h, 12, 1, f);
    int32_t n = NumCameras;
    g_fwrite(&n, 4, 1, f);
    for (int i = 0; i < NumCameras; i++) g_fwrite(CameraList[i], 0x8c, 1, f);
    finish_chunk(f, start, &h);
}

void WriteDirectorData(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { 0x504c5244, 0, 1 };
    g_fwrite(&h, 12, 1, f);
    WriteReplayHeaderChunk(f);
    WriteWaypointChunk(f);
    WriteCameraChunk(f);
    finish_chunk(f, start, &h);
}

void LogWaypoint(int frame) {
    WaypointDirty = 1;
    if ((frame / 150) * 150 != frame) return;
    void *f = g_fopen("Scripts\\Waypoint.tmp", "a+b");
    if (!f) return;
    int32_t rec[3] = { (PlayerPosX / 1500) * 1500, (PlayerPosZ / 1500) * 1500, frame };
    g_fwrite(rec, 12, 1, f);
    WaypointCount++;
    g_fclose(f);
}
