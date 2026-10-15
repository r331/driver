#include "directorstorage.h"
#include "crt.h"
#include "engine.h"
#include "unported.h"
#include <string.h>

#define DS_FILE "D:\\Driver\\Game\\DirectorStorage.c"
GAME_VAR_DEF(int32_t, WaypointDirty, 0x00d17b30)
GAME_VAR_DEF(int32_t, WaypointCount, 0x00d17b40)

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

/* старая запись камеры (чанк RCAM версии 1), 0x3c байта; поля 0x1c..0x2b не используются */
typedef struct CAMERA_V1 {
    int32_t w0, w1;
    int32_t f08, f0c, f10, f14, f18;
    uint8_t unused1c[0x2c - 0x1c];
    int32_t v2c, v30, v34, v38;
} CAMERA_V1;
_Static_assert(sizeof(CAMERA_V1) == 0x3c, "CAMERA_V1 size");

static void put32(DIRECTOR_CAMERA *c, int off, int32_t v) { memcpy((uint8_t *)c + off, &v, 4); }

/* освободить частично заполненный массив из n указателей */
static void free_camera_array(DIRECTOR_CAMERA **a, int n) {
    for (int i = 0; i < n; i++) if (a[i]) DebugFree(a[i]);
    DebugFree(a);
}

/* 004c98de */
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
        g_fread(a[i], 0x8c, 1, f);
    }
    FreeCameraList();
    NumCameras = n;
    CameraList = a;
}

/* 004c9a16 — преобразование камер старого формата в текущий */
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
        g_fread(&o, 0x3c, 1, f);
        DIRECTOR_CAMERA *c = a[i];
        memset(c, 0, sizeof *c);
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
void ReadDirectorData(void *f) {
    long start = g_ftell(f);
    CHUNK_HEADER top;
    g_fread(&top, 12, 1, f);
    if (top.magic == 0x504c5244 && top.version == 1) {
        int32_t pos = 12;
        FreeCameraList();
        FreeDirectorBuffer();
        while (pos < (int32_t)top.size) {
            long chunk_start = g_ftell(f);
            CHUNK_HEADER h;
            g_fread(&h, 12, 1, f);
            if (h.magic == 0x4d414352) {                       /* RCAM */
                if (h.version == 2) ReadCameraChunkV2(f);
                else if (h.version == 1) ReadCameraChunkV1(f);
                else DebugLog("ReadDirectorData: Incompatible replay camera data chunk found.");
            } else if (h.magic == 0x52445052) {                /* RPDR: заголовок повтора */
                if (h.version == 1) {
                    int32_t last;
                    g_fread(&last, 4, 1, f);
                    DirectorLastFrame = last;
                } else DebugLog("ReadDirectorData: Incompatible director data chunk found.");
            } else if (h.magic == 0x54505957) {                /* WYPT: путевые точки */
                if (h.version == 1) {
                    int32_t cnt;
                    g_fread(&cnt, 4, 1, f);
                    if (cnt > 0) {
                        FreeDirectorBuffer();
                        DirectorBufferCount = cnt;
                        DirectorBuffer = DebugMalloc(cnt * 12, DS_FILE, 0xd8);
                        if (!DirectorBuffer) DirectorBufferCount = 0;
                        else g_fread(DirectorBuffer, 12, (size_t)DirectorBufferCount, f);
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
void DeleteWaypointFile(void) {
    g_remove("Scripts\\Waypoint.tmp");
    WaypointDirty = 0;
    WaypointCount = 0;
}

/* 004c9ca0 — загрузить Scripts\Waypoint.tmp в DirectorBuffer; 1 — успех */
int LoadWaypoints(void) {
    void *f = g_fopen("Scripts\\Waypoint.tmp", "rb");
    if (!f) { DebugLog("LoadWaypoints: Unable to open waypoint file."); return 0; }
    FreeCameraList();
    FreeDirectorBuffer();
    long pos = g_ftell(f);
    g_fseek(f, 0, 2);
    long end = g_ftell(f);
    g_fseek(f, pos, 0);
    uint32_t cnt = (uint32_t)(end - pos) / 12;
    if (cnt != 0) {
        void *buf = DebugMalloc((int)(cnt * 12), DS_FILE, 0x238);
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
