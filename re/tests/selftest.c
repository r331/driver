/* Проверка перенесённых модулей в нативной сборке: ./driver --selftest */
#include "../game/director.h"
#include "../game/directorstorage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #c); return 1; } } while (0)
static int test_director(void) {
    DIRECTOR_CAMERA c; memset(&c, 0, sizeof c);
    CHECK(AddDirectorCamera(&c, 30)); CHECK(AddDirectorCamera(&c, 10)); CHECK(AddDirectorCamera(&c, 20));
    CHECK(NumCameras == 3);
    CHECK(CameraList[0]->id == 10 && CameraList[1]->id == 20 && CameraList[2]->id == 30);
    for (int i = 0; i < 3; i++) CHECK(CameraList[i]->index == i);
    CHECK(AddDirectorCamera(&c, 20) && NumCameras == 3);          /* замена существующей */
    CHECK(FindCameraById(20) && !FindCameraById(99));
    DeleteCamera(0); CHECK(NumCameras == 2 && CameraList[0]->id == 20);
    DeleteCamera(5); CHECK(NumCameras == 2);                       /* неверный индекс */
    DeleteCamera(1); DeleteCamera(0); CHECK(NumCameras == 0 && CameraList == NULL);
    return 0;
}
static int test_director2(void) {
    DIRECTOR_CAMERA c; memset(&c, 0, sizeof c);
    AddDirectorCamera(&c, 100); AddDirectorCamera(&c, 200); AddDirectorCamera(&c, 300);
    CHECK(GetCamera(1) && GetCamera(1)->id == 200 && !GetCamera(3) && !GetCamera(-1));
    CHECK(!FindCameraForFrame(50));
    CHECK(FindCameraForFrame(100)->id == 100 && FindCameraForFrame(250)->id == 200 && FindCameraForFrame(9999)->id == 300);
    CHECK(CameraFrameDistance(GetCamera(0), 130) == 30 && CameraFrameDistance(GetCamera(0), 70) == 30);
    DirectorLastFrame = 1000;
    CHECK(FindNearestCamera(50)->id == 100);
    CHECK(FindNearestCamera(190)->id == 100);   /* знаковое сравнение, как в оригинале (004c66f4) */
    c.unk18 = 77; SetCamera(&c, 2); CHECK(GetCamera(2)->unk18 == 77);
    SetCamera(&c, 5);                           /* неверный индекс — только лог */
    FreeDirectorData(); CHECK(NumCameras == 0 && CameraList == NULL && DirectorBuffer == NULL);
    AddDefaultCamera();
    CHECK(NumCameras == 1 && CameraList[0]->id == 2 && CameraList[0]->unk08 == 0x500 && CameraList[0]->unk70 == (int32_t)0xffffff00);
    FreeCameraList();
    CamBackupValid = 0; BackupCameraState(); CHECK(CamBackupValid == 1);
    RestoreCameraBackup(); CHECK(CamBackupValid == 0);
    CamBackupValid = 1; DropCameraBackup(); CHECK(CamBackupValid == 0);
    return 0;
}
static int test_storage(void) {
    DIRECTOR_CAMERA c; memset(&c, 0, sizeof c);
    AddDirectorCamera(&c, 10); AddDirectorCamera(&c, 20);
    DirectorLastFrame = 777; DirectorBufferCount = 0;
    FILE *f = tmpfile(); CHECK(f);
    WriteDirectorData(f);
    long len = ftell(f); CHECK(len == 12 + 16 + (12 + 4) + (12 + 4 + 2 * 0x8c));
    uint8_t *b = malloc(len); rewind(f); CHECK(fread(b, 1, len, f) == (size_t)len);
    CHUNK_HEADER *h = (CHUNK_HEADER*)b;
    CHECK(h->magic == 0x504c5244 && h->size == (uint32_t)len);
    CHECK(((CHUNK_HEADER*)(b + 12))->magic == 0x52445052 && *(int32_t*)(b + 24) == 777);
    CHUNK_HEADER *w = (CHUNK_HEADER*)(b + 28); CHECK(w->magic == 0x54505957 && w->size == 16);
    CHUNK_HEADER *cm = (CHUNK_HEADER*)(b + 44); CHECK(cm->magic == 0x4d414352 && cm->size == 16 + 2 * 0x8c);
    free(b); fclose(f); FreeCameraList();
    LogWaypoint(7); CHECK(WaypointDirty == 1 && WaypointCount == 0);
    return 0;
}
static int test_read(void) {
    DIRECTOR_CAMERA c; memset(&c, 0, sizeof c); c.unk18 = 0x800;
    AddDirectorCamera(&c, 10); AddDirectorCamera(&c, 20); AddDirectorCamera(&c, 30);
    DirectorLastFrame = 4321; DirectorBufferCount = 0;
    FILE *f = tmpfile(); CHECK(f);
    fputs("junk", f);                       /* блок начинается не с начала файла */
    WriteDirectorData(f);
    fputs("tail", f);
    long end = ftell(f);
    FreeDirectorData(); DirectorLastFrame = 0;
    fseek(f, 4, SEEK_SET);
    ReadDirectorData(f);
    CHECK(ftell(f) == end - 4);             /* позиция за блоком */
    CHECK(NumCameras == 3 && CameraList[1]->id == 20 && CameraList[2]->unk18 == 0x800 && DirectorLastFrame == 4321);
    fclose(f); FreeCameraList();
    /* камеры старого формата */
    f = tmpfile(); CHECK(f);
    int32_t n = 1; fwrite(&n, 4, 1, f);
    int32_t old[15]; for (int i = 0; i < 15; i++) old[i] = 100 + i;
    fwrite(old, 0x3c, 1, f); rewind(f);
    ReadCameraChunkV1(f);
    CHECK(NumCameras == 1 && CameraList[0]->unk00 == 100 && CameraList[0]->unk08 == 102 && CameraList[0]->unk0c == 103);
    CHECK(CameraList[0]->unk10 == 104 && CameraList[0]->id == 105 && CameraList[0]->unk18 == 106);
    int32_t *w = (int32_t*)CameraList[0];
    CHECK(w[0x4c / 4] == 111 && w[0x5c / 4] == 111 && w[0x68 / 4] == 114 && w[0x54 / 4] == 113 && w[0x1c / 4] == 0);
    fclose(f); FreeCameraList();
    /* путевые точки: Scripts/Waypoint.tmp */
    DirectorBufferCount = 0; WaypointCount = 0; WaypointDirty = 0;
    CHECK(!LoadWaypoints());                /* файла нет */
    f = fopen("Scripts\\Waypoint.tmp", "wb");
    if (f) {
        int32_t recs[9] = { 1500, 3000, 150, 1500, 4500, 300, 3000, 4500, 450 };
        fwrite(recs, 4, 9, f); fclose(f);
        CHECK(LoadWaypoints() == 1);
        CHECK(DirectorBufferCount == 3 && NumCameras == 1);
        CHECK(GetWaypointAfterFrame(0)->frame == 300 && GetWaypointAfterFrame(150)->frame == 450 && !GetWaypointAfterFrame(300));
        CHECK(!fopen("Scripts\\Waypoint.tmp", "rb"));   /* временный файл удалён */
        FreeDirectorData();
    }
    CHECK(!GetWaypointAfterFrame(0));
    WaypointCount = 5; WaypointDirty = 1; GameMode = 0; CurCamera = (void*)1; DirectorUnk6C = 9;
    ResetDirectorState();
    CHECK(WaypointCount == 0 && WaypointDirty == 0 && CurCamera == NULL && DirectorCam.index == -1 && DirectorUnk6C == 0);
    CHECK(DirectorUnk8C == 0xffff00 && DirectorUnk7C == 1 && DirectorUnk84 == 4 && DirectorUnk88 == 0x20);
    return 0;
}
int re_selftest(void) {
    int f = test_director() | test_director2() | test_storage() | test_read();
    printf("selftest: director %s\n", f ? "FAIL" : "OK");
    return f;
}
