/* Director.c — восстановлено из Game.exe (PC, 1999-09-10). Переносимый код: без WinAPI. */
#include "director.h"
#include "engine.h"
#include "unported.h"
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
