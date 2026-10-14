/* Director.c — восстановлено из Game.exe (PC, 1999-09-10). Переносимый код: без WinAPI. */
#include "director.h"
#include "engine.h"
#include "unported.h"
#include "dirnodes.h"
#include "crt.h"
#include "directorstorage.h"
#include <string.h>

GAME_VAR_DEF(int32_t, NumCameras, 0x00d17b60)
GAME_VAR_DEF(DIRECTOR_CAMERA*, CurCamera, 0x00d17c50)
GAME_VAR_DEF(DIRECTOR_CAMERA**, CameraList, 0x00d17c54)
GAME_VAR_DEF(int32_t, DirectorLastFrame, 0x00d17b68)
GAME_VAR_DEF(int32_t, CamBackupValid, 0x00d17bb4)
GAME_VAR_DEF(DIRECTOR_CAMERA, DirectorCam, 0x00d17bc4)
GAME_VAR_DEF(void*, DirectorBuffer, 0x00d17c5c)
GAME_VAR_DEF(int32_t, DirectorBufferCount, 0x00d17b70)
GAME_VAR_DEF(DIRECTOR_CAMERA, CamBackup, 0x00d17c64)

GAME_VAR_DEF(int32_t, DirectorUnk64, 0x00d17b64)
GAME_VAR_DEF(int32_t, DirectorUnk6C, 0x00d17b6c)
GAME_VAR_DEF(int32_t, DirectorUnk7C, 0x00d17b7c)
GAME_VAR_DEF(int32_t, DirectorUnk84, 0x00d17b84)
GAME_VAR_DEF(int32_t, DirectorUnk88, 0x00d17b88)
GAME_VAR_DEF(int32_t, DirectorUnk8C, 0x00d17b8c)
GAME_VAR_DEF(int32_t, GameMode, 0x005f7e50)

/* 004c6168 */
DIRECTOR_CAMERA *FindCameraById(int id) {
    for (int i = 0; i < NumCameras; i++)
        if (CameraList[i]->id == id) return CameraList[i];
    return NULL;
}
/* 004c622c */
void RenumberCameras(void) {
    for (int i = 0; i < NumCameras; i++) CameraList[i]->index = i;
}
/* 004c6312 — возвращает новую камеру (копию cam) или NULL */
DIRECTOR_CAMERA *InsertCamera(DIRECTOR_CAMERA *cam, int pos) {
    if (pos >= NumCameras) pos = -1;
    DIRECTOR_CAMERA **nl = DebugMalloc((NumCameras + 1) * (int)sizeof(*nl), "D:\\Driver\\Game\\Director.c", 0xa8a);
    if (!nl) { DebugLog("InsertCamera: Error! unable to allocate memory for new camera list."); return NULL; }
    DIRECTOR_CAMERA *c = DebugMalloc(sizeof(DIRECTOR_CAMERA), "D:\\Driver\\Game\\Director.c", 0xa91);
    if (!c) { DebugLog("InsertCamera: Error! unable to allocate memory for new camera."); DebugFree(nl); return NULL; }
    int at = 0;
    if (pos == -1) {
        for (int i = 0; i < NumCameras; i++) nl[i] = CameraList[i];
        at = NumCameras++;
        nl[at] = c;
    } else {
        NumCameras++;
        for (int i = 0, j = 0; i < NumCameras; i++) {
            if (i == pos) { nl[i] = c; at = i; }
            else nl[i] = CameraList[j++];
        }
    }
    *c = *cam;
    if (CameraList) DebugFree(CameraList);
    CameraList = nl;
    RenumberCameras();
    return CameraList[at];
}
/* 004c6524 */
void DeleteCamera(int idx) {
    if (idx >= NumCameras || idx < 0) { DebugLog("DeleteCamera: Error! Specified camera does not exist."); return; }
    if (NumCameras < 2) {
        DebugFree(CameraList[idx]); DebugFree(CameraList);
        CurCamera = NULL; CameraList = NULL;
    } else {
        DIRECTOR_CAMERA **nl = DebugMalloc((NumCameras - 1) * (int)sizeof(*nl), "D:\\Driver\\Game\\Director.c", 0xae9);
        if (!nl) { DebugLog("DeleteCamera: Error! Unable to allocate memory for new camera list."); return; }
        int n = 0;
        for (int i = 0; i < NumCameras; i++)
            if (i != idx) { nl[n] = CameraList[i]; nl[n]->index = n; n++; }
        if (CurCamera && CurCamera->index == idx) CurCamera = NULL;
        DebugFree(CameraList[idx]); DebugFree(CameraList);
        CameraList = nl;
    }
    NumCameras--;
    RenumberCameras();
}
/* 004c6264 */
DIRECTOR_CAMERA *AddDirectorCamera(DIRECTOR_CAMERA *cam, int id) {
    DIRECTOR_CAMERA *old = FindCameraById(id);
    if (old) DeleteCamera(old->index);
    cam->id = id;
    for (int i = 0; i < NumCameras; i++) {
        if (CameraList[i]->id == id) { DebugLog("Director.c::AddDirectorCamera: Camera already exists."); return NULL; }
        if (id < CameraList[i]->id) return InsertCamera(cam, i);
    }
    return InsertCamera(cam, -1);
}

/* 004c60fa */
void SetCamera(const DIRECTOR_CAMERA *src, int idx) {
    if (idx < 0 || idx >= NumCameras) { DebugLog("SetCamera: Cannot set camera contents, camera does not exist."); return; }
    *CameraList[idx] = *src;
}
/* 004c6142 */
DIRECTOR_CAMERA *GetCamera(int idx) {
    return (idx < NumCameras && idx >= 0) ? CameraList[idx] : NULL;
}
/* 004c61b2 — камера, действующая на кадре frame (список отсортирован по id) */
DIRECTOR_CAMERA *FindCameraForFrame(int frame) {
    for (int i = 0; i < NumCameras; i++)
        if (CameraList[i]->id <= frame &&
            (i == NumCameras - 1 || frame < CameraList[i + 1]->id)) return CameraList[i];
    return NULL;
}
/* 004c64bd */
void FreeCameraList(void) {
    for (int i = 0; i < NumCameras; i++) DebugFree(CameraList[i]);
    if (CameraList) DebugFree(CameraList);
    NumCameras = 0;
    CameraList = NULL;
}
/* 004c6691 — ближайшая по кадру камера. Как в оригинале: лучшая дистанция запоминается со знаком,
   поэтому после камеры правее кадра (отрицательная разница) дальше выигрывает только ещё более правая. */
DIRECTOR_CAMERA *FindNearestCamera(int frame) {
    DIRECTOR_CAMERA *best = NULL;
    int bestd = DirectorLastFrame + 500;
    for (int i = 0; i < NumCameras; i++) {
        int d = CameraList[i]->id - frame;
        if ((d < 0 ? -d : d) < bestd) { best = CameraList[i]; bestd = d; }
    }
    return best;
}
/* 004c6715 */
int CameraFrameDistance(const DIRECTOR_CAMERA *cam, int frame) {
    int d = cam->id - frame;
    return d < 0 ? -d : d;
}
/* 004c9360 — камера по умолчанию на кадре 2 */
void AddDefaultCamera(void) {
    DIRECTOR_CAMERA c;
    memset(&c, 0, sizeof c);
    c.unk70 = (int32_t)0xffffff00;
    c.unk18 = 0x800;
    c.unk08 = 0x500;
    c.unk0c = 0x500;
    AddDirectorCamera(&c, 2);
}
/* 004c372a */
void FreeDirectorBuffer(void) {
    if (DirectorBuffer) DebugFree(DirectorBuffer);
    DirectorBuffer = NULL;
    DirectorBufferCount = 0;
}
/* 004c812e */
void FreeDirectorData(void) {
    FreeCameraList();
    FreeDirectorBuffer();
}
/* 004c8e9e — запомнить состояние игровой камеры (один раз до сброса) */
void BackupCameraState(void) {
    if (CamBackupValid == 0) {
        CamBackupValid = 1;
        StoreCameraState(&CamBackup);
        StoreCameraState(&DirectorCam);
    }
}
/* 004c8ed2 */
void DropCameraBackup(void) {
    if (CamBackupValid != 0) CamBackupValid = 0;
}
/* 004c8eec */
void RestoreCameraBackup(void) {
    if (CamBackupValid != 0) {
        RestoreCameraState(&CamBackup);
        CamBackupValid = 0;
    }
}

/* 004c375a — запись путевой точки, следующая за кадром (по одной на 150 кадров), либо NULL */
WAYPOINT_REC *GetWaypointAfterFrame(int frame) {
    if (!DirectorBuffer) return NULL;
    int i = frame / 150 + 1;
    if (i < DirectorBufferCount) return (WAYPOINT_REC *)DirectorBuffer + i;
    return NULL;
}
/* 004c8070 — сброс состояния режиссёра (вызывает также удаление Waypoint.tmp и временного файла камер) */
void ResetDirectorState(void) {
    WaypointCount = 0;
    WaypointDirty = 0;
    DirectorUnk6C = 0;
    DirectorUnk64 = 0;
    memset(&DirectorCam, 0, sizeof DirectorCam);
    DirectorCam.index = -1;
    CurCamera = NULL;
    DirectorUnk8C = 0xffff00;
    DirectorUnk7C = 1;
    DirectorUnk84 = 4;
    DirectorUnk88 = 0x20;
    if (GameMode != 4 && GameMode != 5) {
        DeleteWaypointFile();
        g_remove("REPLAYDATA\\USER\\$TEMP$.CAMS");
    }
}

#ifndef RE_HOOK_BUILD
CAR_OBJ *CarObjTable[64]; float CarMinDist;
#endif
/* 004c52d9 — текущая камера <- запись списка для текущего кадра; при смене камеры двигает позицию */
void SyncCameraFromList(void) {
    int32_t old = DirectorUnk64;
    DIRECTOR_CAMERA *c = (DIRECTOR_CAMERA *)FindCameraRecordForFrame(DirectorUnk6C);
    if (!c) return;
    CurCamera = c;
    DirectorCam = *c;
    DirectorUnk64 = CurCamera->index;
    if (DirectorUnk64 != old) {
        const int32_t *w = (const int32_t *)c;
        SetCameraPosition((float)w[0x13], (float)w[0x14], (float)w[0x15]);
    }
}
/* 004c60b2 — 1, если у машины камеры нет флага 0x400 и её дальность >= порога */
int IsCameraCarFarEnough(const DIRECTOR_CAMERA *cam) {
    const CAR_OBJ *car = CarObjTable[cam->index];
    if (car->flags & 0x400) return 0;
    return CarMinDist <= car->dist ? 1 : 0;
}

GAME_VAR_DEF(TRAFFIC_RECS_T, TrafficRecs, 0x011443e0)
GAME_VAR_DEF(OBJPOS_T, ObjPosTable, 0x00d07888)
GAME_VAR_DEF(DIRTABLE_T, DirTableA, 0x0055f088)
GAME_VAR_DEF(DIRTABLE_T, DirTableB, 0x0055f030)
/* 004c57b7 — название типа камеры */
const char *GetCameraTypeName(int type) {
    switch (type) {
    case 0:    return "Chase camera";
    case 1:    return "Flying camera";
    case 2:    return "In car camera";
    case 0x10: return "Static camera";
    case 0x11: return "Watch car camera";
    default:   return "WARNING! Unknown camera type.";
    }
}
/* 004c5222 — выбрать новую автокамеру и сделать её текущей */
void SelectNewCamera(void) {
    if (!FindAutoCamera((void **)&CurCamera)) return;
    InitNewCamera(CurCamera);
    int32_t *w = (int32_t *)CurCamera;
    w[5] = DirectorUnk6C < 4 ? 2 : DirectorUnk6C;
    DirectorUnk64 = w[1];
    DirectorCam = *CurCamera;
    SetCameraPosition((float)w[0x13], (float)w[0x14], (float)w[0x15]);
}
/* 004c5d40 — сколько из 64 машин (тип 4, активные) ближе 30000 по плоскости к игроку (квадрат < 900000000) */
int CountNearbyCars(void) {
    int n = 0;
    for (int i = 0; i < 0x40; i++) {
        const uint8_t *rec = TrafficRecs + i * 0x54;
        if (rec[5] && rec[0xc] == 1 && rec[1] == 4) {
            const int32_t *pl = ObjPosTable;
            const int32_t *ot = pl + (i + 1) * 0x52;
            int32_t dx = pl[0] - ot[0], dz = pl[2] - ot[2];
            if (dx * dx + dz * dz < 900000000) n++;
        }
    }
    return n;
}
/* 004c810f */
void ClearDirectorTables(void) {
    ClearDirectorTable((DIR_NODE *)&DirTableA);
    ClearDirectorTable((DIR_NODE *)&DirTableB);
}
