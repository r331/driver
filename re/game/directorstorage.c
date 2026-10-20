/* directorstorage.c — Game\DirectorStorage.c: replay director data in replay files, and the waypoint log
   (English overview; original notes follow).
   A replay file carries a "DRLP" chunk holding "RPDR" (last frame), "WYPT" (player waypoints) and "RCAM"
   (director cameras).  Each chunk starts with CHUNK_HEADER {magic, size including the header, version}.
   While driving, LogWaypoint appends the player's position every 150 frames to Scripts\Waypoint.tmp;
   LoadWaypoints turns that file into the director buffer for the replay editor. */
#include "directorstorage.h"
#include "crt.h"
#include "engine.h"
#include "unported.h"
#include <string.h>

#define DS_FILE "D:\\Driver\\Game\\DirectorStorage.c"

/* Chunk ids: four ASCII characters stored little-endian (the file shows them in this order). */
enum {
    CHUNK_DRLP = 0x504c5244,   /* "DRLP": director data, contains the three chunks below */
    CHUNK_RPDR = 0x52445052,   /* "RPDR": replay header (last frame) */
    CHUNK_WYPT = 0x54505957,   /* "WYPT": waypoints (player route, 12-byte records) */
    CHUNK_RCAM = 0x4d414352    /* "RCAM": director cameras (v2: 0x8c-byte records, v1: 0x3c) */
};
#define CHUNK_HEADER_SIZE   12      /* {magic, size incl. header, version} */
#define WAYPOINT_REC_SIZE   12      /* {x, z, frame} */
#define CAMERA_REC_SIZE     0x8c    /* sizeof(DIRECTOR_CAMERA) as stored in v2 chunks */
#define CAMERA_V1_REC_SIZE  0x3c
#define WAYPOINT_INTERVAL   150     /* frames between logged waypoints (3 s at 50 Hz) */
#define WAYPOINT_GRID       1500    /* waypoint positions are snapped (toward zero) to this grid */
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WaypointDirty")
#undef WaypointDirty
#pragma push_macro("WaypointDirty") /*gvi*/
#undef WaypointDirty /*gvi*/
int32_t WaypointDirty;
#pragma pop_macro("WaypointDirty") /*gvi*/
#pragma pop_macro("WaypointDirty")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WaypointCount")
#undef WaypointCount
#pragma push_macro("WaypointCount") /*gvi*/
#undef WaypointCount /*gvi*/
int32_t WaypointCount;
#pragma pop_macro("WaypointCount") /*gvi*/
#pragma pop_macro("WaypointCount")
#endif

/* после записи содержимого чанка в заголовок пишется реальный размер */
/* finish_chunk — local helper: after a chunk's body is written, rewrites its header at `start` with the real
   size and seeks back to the end. */
static void finish_chunk(void *f, long start, CHUNK_HEADER *h) {
    long end = g_ftell(f);
    h->size = (uint32_t)(end - start);
    g_fseek(f, start, 0);
    g_fwrite(h, CHUNK_HEADER_SIZE, 1, f);
    g_fseek(f, end, 0);
}

/* WriteReplayHeaderChunk — Game.exe 004c988e.  Writes the RPDR chunk (size 0x10): DirectorLastFrame. */
void WriteReplayHeaderChunk(void *f) {
    CHUNK_HEADER h = { CHUNK_RPDR, 0x10, 1 };
    g_fwrite(&h, CHUNK_HEADER_SIZE, 1, f);
    int32_t last = DirectorLastFrame;
    g_fwrite(&last, 4, 1, f);
}

/* WriteWaypointChunk — Game.exe 004c96d6.  Writes the WYPT chunk: count, then DirectorBuffer records. */
void WriteWaypointChunk(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { CHUNK_WYPT, 0, 1 };
    g_fwrite(&h, CHUNK_HEADER_SIZE, 1, f);
    int32_t n = DirectorBufferCount;
    g_fwrite(&n, 4, 1, f);
    if (n != 0) g_fwrite(DirectorBuffer, WAYPOINT_REC_SIZE, (size_t)n, f);
    finish_chunk(f, start, &h);
}

/* WriteCameraChunk — Game.exe 004c97a2.  Writes the RCAM chunk, version 2: count, then each camera (0x8c bytes). */
void WriteCameraChunk(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { CHUNK_RCAM, 0, 2 };
    g_fwrite(&h, CHUNK_HEADER_SIZE, 1, f);
    int32_t n = NumCameras;
    g_fwrite(&n, 4, 1, f);
    for (int i = 0; i < NumCameras; i++) g_fwrite(CameraList[i], CAMERA_REC_SIZE, 1, f);
    finish_chunk(f, start, &h);
}

/* WriteDirectorData — Game.exe 004c9621.  Writes the DRLP chunk wrapping the three chunks above. */
void WriteDirectorData(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER h = { CHUNK_DRLP, 0, 1 };
    g_fwrite(&h, CHUNK_HEADER_SIZE, 1, f);
    WriteReplayHeaderChunk(f);
    WriteWaypointChunk(f);
    WriteCameraChunk(f);
    finish_chunk(f, start, &h);
}

/* LogWaypoint — Game.exe 004c9bf4.  Marks waypoints dirty; on every 150th frame appends {x, z, frame} of the
   player (snapped to 1500 units) to Scripts\Waypoint.tmp and counts it in WaypointCount. */
void LogWaypoint(int frame) {
    WaypointDirty = 1;
    if ((frame / WAYPOINT_INTERVAL) * WAYPOINT_INTERVAL != frame) return;
    void *f = g_fopen("Scripts\\Waypoint.tmp", "a+b");
    if (!f) return;
    int32_t rec[3] = { (PlayerPosX / WAYPOINT_GRID) * WAYPOINT_GRID, (PlayerPosZ / WAYPOINT_GRID) * WAYPOINT_GRID, frame };
    g_fwrite(rec, WAYPOINT_REC_SIZE, 1, f);
    WaypointCount++;
    g_fclose(f);
}

/* старая запись камеры (чанк RCAM версии 1), 0x3c байта; поля 0x1c..0x2b не используются */
typedef struct CAMERA_V1 {
    int32_t w0, w1;
    int32_t f08, f0c, f10, f14, f18;
    uint8_t unused1c[0x2c - 0x1c];
    int32_t v2c, v30, v34, v38;
} CAMERA_V1;
_Static_assert(sizeof(CAMERA_V1) == 0x3c, "CAMERA_V1 size");

/* put32 — local helper: stores an int32 at byte offset `off` of a camera record. */
static void put32(DIRECTOR_CAMERA *c, int off, int32_t v) { memcpy((uint8_t *)c + off, &v, 4); }

/* освободить частично заполненный массив из n указателей */
/* free_camera_array — local helper: frees a partly filled array of n camera pointers and the array itself. */
static void free_camera_array(DIRECTOR_CAMERA **a, int n) {
    for (int i = 0; i < n; i++) if (a[i]) DebugFree(a[i]);
    DebugFree(a);
}

/* 004c98de */
/* ReadCameraChunkV2 — Game.exe 004c98de.  Reads an RCAM v2 body (count + 0x8c-byte cameras) into a new
   CameraList, replacing the old one.  On an allocation failure the old list is kept. */
void ReadCameraChunkV2(void *f) {
    int32_t n;
    g_fread(&n, 4, 1, f);
    if (n == 0) return;
    DIRECTOR_CAMERA **a = DebugMalloc(n * (int)sizeof(*a), DS_FILE, 0x18c);
    if (!a) return;
    memset(a, 0, (size_t)n * sizeof(*a));
    for (int i = 0; i < n; i++) {
        a[i] = DebugMalloc(sizeof(DIRECTOR_CAMERA), DS_FILE, 0x195);
        if (!a[i]) { free_camera_array(a, n); return; }
        g_fread(a[i], CAMERA_REC_SIZE, 1, f);
    }
    FreeCameraList();
    NumCameras = n;
    CameraList = a;
}

/* 004c9a16 — преобразование камер старого формата в текущий */
/* ReadCameraChunkV1 — Game.exe 004c9a16.  Reads an RCAM v1 body (0x3c-byte cameras) and converts each to the
   current DIRECTOR_CAMERA layout, replacing CameraList. */
void ReadCameraChunkV1(void *f) {
    int32_t n;
    g_fread(&n, 4, 1, f);
    if (n == 0) return;
    DIRECTOR_CAMERA **a = DebugMalloc(n * (int)sizeof(*a), DS_FILE, 0x1c5);
    if (!a) return;
    memset(a, 0, (size_t)n * sizeof(*a));
    for (int i = 0; i < n; i++) {
        a[i] = DebugMalloc(sizeof(DIRECTOR_CAMERA), DS_FILE, 0x1ce);
        if (!a[i]) { free_camera_array(a, n); return; }
        CAMERA_V1 o;
        g_fread(&o, CAMERA_V1_REC_SIZE, 1, f);
        DIRECTOR_CAMERA *c = a[i];
        memset(c, 0, sizeof *c);
        /* v1 words +0x2c..+0x38 go to both v2 blocks +0x5c..+0x68 and +0x4c..+0x58.  TODO(RE): unsure what the two blocks are. */
        put32(c, 0x5c, o.v2c); put32(c, 0x60, o.v30); put32(c, 0x64, o.v34); put32(c, 0x68, o.v38);
        put32(c, 0x4c, o.v2c); put32(c, 0x50, o.v30); put32(c, 0x54, o.v34); put32(c, 0x58, o.v38);
        c->unk08 = o.f08;
        c->unk0c = o.f0c;
        c->unk18 = o.f18;
        c->unk10 = o.f10;
        c->id    = o.f14;
        c->unk00 = o.w0;
    }
    FreeCameraList();
    NumCameras = n;
    CameraList = a;
}

/* 004c93e6 — читает блок данных режиссёра (DRLP) из файла повтора и возвращает позицию за ним */
/* ReadDirectorData — Game.exe 004c93e6.  Reads a DRLP chunk at the current file position: frees the old cameras
   and waypoints, then dispatches the sub-chunks by id/version (unknown ones are logged and skipped).
   Always leaves the file positioned just after the DRLP chunk.
   Native deviation: a sub-chunk with size <= 0 ends the loop (the original loops forever). */
void ReadDirectorData(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER top;
    g_fread(&top, CHUNK_HEADER_SIZE, 1, f);
    if (top.magic == CHUNK_DRLP && top.version == 1) {
        int32_t pos = CHUNK_HEADER_SIZE;   /* bytes of the DRLP chunk consumed so far */
        FreeCameraList();
        FreeDirectorBuffer();
        while (pos < (int32_t)top.size) {
            long chunk_start = g_ftell(f);
            CHUNK_HEADER h;
            g_fread(&h, CHUNK_HEADER_SIZE, 1, f);
            if (h.magic == CHUNK_RCAM) {                       /* RCAM */
                if (h.version == 2) ReadCameraChunkV2(f);
                else if (h.version == 1) ReadCameraChunkV1(f);
                else DebugLog("ReadDirectorData: Incompatible replay camera data chunk found.");
            } else if (h.magic == CHUNK_RPDR) {                /* RPDR: заголовок повтора */
                if (h.version == 1) {
                    int32_t last;
                    g_fread(&last, 4, 1, f);
                    DirectorLastFrame = last;
                } else DebugLog("ReadDirectorData: Incompatible director data chunk found.");
            } else if (h.magic == CHUNK_WYPT) {                /* WYPT: путевые точки */
                if (h.version == 1) {
                    int32_t cnt;
                    g_fread(&cnt, 4, 1, f);
                    if (cnt > 0) {
                        FreeDirectorBuffer();
                        DirectorBufferCount = cnt;
                        DirectorBuffer = DebugMalloc(cnt * WAYPOINT_REC_SIZE, DS_FILE, 0xd8);
                        if (!DirectorBuffer) DirectorBufferCount = 0;
                        else g_fread(DirectorBuffer, WAYPOINT_REC_SIZE, (size_t)DirectorBufferCount, f);
                    }
                } else DebugLog("ReadDirectorData: Incompatible waypoint data chunk found.");
            } else DebugLog("ReadDirectorData: Error! unknown chunk found.");
            g_fseek(f, chunk_start, 0);
            g_fseek(f, (long)h.size, 1);
            /* оригинал при размере чанка <= 0 зацикливается; здесь выходим */
            if ((int32_t)h.size <= 0) break;
            pos += (int32_t)h.size;
        }
    }
    g_fseek(f, start, 0);
    g_fseek(f, (long)top.size, 1);
}

/* 004c9dcc — удалить временный файл путевых точек и сбросить счётчики */
/* DeleteWaypointFile — Game.exe 004c9dcc.  Deletes Scripts\Waypoint.tmp and resets WaypointDirty / WaypointCount. */
void DeleteWaypointFile(void) {
    g_remove("Scripts\\Waypoint.tmp");
    WaypointDirty = 0;
    WaypointCount = 0;
}

/* 004c9ca0 — загрузить Scripts\Waypoint.tmp в DirectorBuffer; 1 — успех */
/* LoadWaypoints — Game.exe 004c9ca0.  Loads Scripts\Waypoint.tmp into DirectorBuffer (frees cameras and the old
   buffer first), adds a default camera if there is none, then deletes the file.  Returns 1 on success, 0 if
   the file can't be opened or memory can't be allocated. */
int LoadWaypoints(void) {
    void *f = g_fopen("Scripts\\Waypoint.tmp", "rb");
    if (!f) { DebugLog("LoadWaypoints: Unable to open waypoint file."); return 0; }
    FreeCameraList();
    FreeDirectorBuffer();
    long pos = g_ftell(f);
    g_fseek(f, 0, 2);
    long end = g_ftell(f);
    g_fseek(f, pos, 0);
    uint32_t cnt = (uint32_t)(end - pos) / WAYPOINT_REC_SIZE;
    if (cnt != 0) {
        void *buf = DebugMalloc((int)(cnt * WAYPOINT_REC_SIZE), DS_FILE, 0x238);
        if (!buf) {
            DebugLog("LoadWaypoints: Unable to allocate space for waypoint data.");
            g_fclose(f);
            return 0;
        }
        DirectorBufferCount = (int32_t)cnt;
        DirectorBuffer = buf;
        g_fread(buf, (size_t)(end - pos), 1, f);
    }
    g_fclose(f);
    if (NumCameras == 0) AddDefaultCamera();
    DeleteWaypointFile();
    return 1;
}
