/* director.c — the replay director's camera list (Director.c in Game.exe): a list of camera records sorted by start
   frame (cam->id), insertion / deletion, lookup by frame, camera state backup, waypoints and a few helpers.
   Each function is preceded by its Game.exe address.  Original note: */
/* Director.c — восстановлено из Game.exe (PC, 1999-09-10). Переносимый код: без WinAPI. */
#include <stdio.h>
#include "director.h"
#include "engine.h"
#include "unported.h"
#include "dirnodes.h"
#include "crt.h"
#include "directorstorage.h"
#include "names_g5.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("NumCameras")
#undef NumCameras
#pragma push_macro("NumCameras") /*gvi*/
#undef NumCameras /*gvi*/
int32_t NumCameras;
#pragma pop_macro("NumCameras") /*gvi*/
#pragma pop_macro("NumCameras")
#endif
GAME_VAR_DEF(DIRECTOR_CAMERA*, CurCamera, 0x00d17c50)
GAME_VAR_DEF(DIRECTOR_CAMERA**, CameraList, 0x00d17c54)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorLastFrame")
#undef DirectorLastFrame
#pragma push_macro("DirectorLastFrame") /*gvi*/
#undef DirectorLastFrame /*gvi*/
int32_t DirectorLastFrame;
#pragma pop_macro("DirectorLastFrame") /*gvi*/
#pragma pop_macro("DirectorLastFrame")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("CamBackupValid")
#undef CamBackupValid
#pragma push_macro("CamBackupValid") /*gvi*/
#undef CamBackupValid /*gvi*/
int32_t CamBackupValid;
#pragma pop_macro("CamBackupValid") /*gvi*/
#pragma pop_macro("CamBackupValid")
#endif
GAME_VAR_DEF(DIRECTOR_CAMERA, DirectorCam, 0x00d17bc4)
GAME_VAR_DEF(void*, DirectorBuffer, 0x00d17c5c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorBufferCount")
#undef DirectorBufferCount
#pragma push_macro("DirectorBufferCount") /*gvi*/
#undef DirectorBufferCount /*gvi*/
int32_t DirectorBufferCount;
#pragma pop_macro("DirectorBufferCount") /*gvi*/
#pragma pop_macro("DirectorBufferCount")
#endif
GAME_VAR_DEF(DIRECTOR_CAMERA, CamBackup, 0x00d17c64)

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk64")
#undef DirectorUnk64
#pragma push_macro("DirectorUnk64") /*gvi*/
#undef DirectorUnk64 /*gvi*/
int32_t DirectorUnk64;
#pragma pop_macro("DirectorUnk64") /*gvi*/
#pragma pop_macro("DirectorUnk64")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk6C")
#undef DirectorUnk6C
#pragma push_macro("DirectorUnk6C") /*gvi*/
#undef DirectorUnk6C /*gvi*/
int32_t DirectorUnk6C;
#pragma pop_macro("DirectorUnk6C") /*gvi*/
#pragma pop_macro("DirectorUnk6C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk7C")
#undef DirectorUnk7C
#pragma push_macro("DirectorUnk7C") /*gvi*/
#undef DirectorUnk7C /*gvi*/
int32_t DirectorUnk7C;
#pragma pop_macro("DirectorUnk7C") /*gvi*/
#pragma pop_macro("DirectorUnk7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk84")
#undef DirectorUnk84
#pragma push_macro("DirectorUnk84") /*gvi*/
#undef DirectorUnk84 /*gvi*/
int32_t DirectorUnk84;
#pragma pop_macro("DirectorUnk84") /*gvi*/
#pragma pop_macro("DirectorUnk84")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk88")
#undef DirectorUnk88
#pragma push_macro("DirectorUnk88") /*gvi*/
#undef DirectorUnk88 /*gvi*/
int32_t DirectorUnk88;
#pragma pop_macro("DirectorUnk88") /*gvi*/
#pragma pop_macro("DirectorUnk88")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirectorUnk8C")
#undef DirectorUnk8C
#pragma push_macro("DirectorUnk8C") /*gvi*/
#undef DirectorUnk8C /*gvi*/
int32_t DirectorUnk8C;
#pragma pop_macro("DirectorUnk8C") /*gvi*/
#pragma pop_macro("DirectorUnk8C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("GameMode")
#undef GameMode
#pragma push_macro("GameMode") /*gvi*/
#undef GameMode /*gvi*/
int32_t GameMode;
#pragma pop_macro("GameMode") /*gvi*/
#pragma pop_macro("GameMode")
#endif

/* 004c6168 */
/* Camera whose start frame (id) is id, or NULL. */
DIRECTOR_CAMERA *FindCameraById(int id) {
    for (int i = 0; i < NumCameras; i++)
        if (CameraList[i]->id == id) return CameraList[i];
    return NULL;
}
/* 004c622c */
/* Rewrites each camera's index field to its list position. */
void RenumberCameras(void) {
    for (int i = 0; i < NumCameras; i++) CameraList[i]->index = i;
}
/* 004c6312 — возвращает новую камеру (копию cam) или NULL */
/* Inserts a copy of cam at list position pos (>= count or -1: append); reallocates the pointer list.  Returns the new
   camera or NULL on allocation failure (logged). */
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
/* Deletes camera idx (clears CurCamera if it was current); invalid index is logged. */
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
/* Adds a copy of cam starting at frame id, replacing an existing camera at that frame and keeping the list sorted. */
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
/* Overwrites camera idx with *src (invalid index logged). */
void SetCamera(const DIRECTOR_CAMERA *src, int idx) {
    if (idx < 0 || idx >= NumCameras) { DebugLog("SetCamera: Cannot set camera contents, camera does not exist."); return; }
    *CameraList[idx] = *src;
}
/* 004c6142 */
/* Camera at list index idx, or NULL. */
DIRECTOR_CAMERA *GetCamera(int idx) {
    return (idx < NumCameras && idx >= 0) ? CameraList[idx] : NULL;
}
/* 004c61b2 — камера, действующая на кадре frame (список отсортирован по id) */
/* Camera active at frame (the last one starting at or before it). */
DIRECTOR_CAMERA *FindCameraForFrame(int frame) {
    for (int i = 0; i < NumCameras; i++)
        if (CameraList[i]->id <= frame &&
            (i == NumCameras - 1 || frame < CameraList[i + 1]->id)) return CameraList[i];
    return NULL;
}
/* 004c64bd */
/* Frees all cameras and the list. */
void FreeCameraList(void) {
    for (int i = 0; i < NumCameras; i++) DebugFree(CameraList[i]);
    if (CameraList) DebugFree(CameraList);
    NumCameras = 0;
    CameraList = NULL;
}
/* 004c6691 */
/* Camera whose start frame is nearest to frame.  The best distance is stored signed (original quirk), see below. */
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
/* |start frame of cam - frame|. */
int CameraFrameDistance(const DIRECTOR_CAMERA *cam, int frame) {
    int d = cam->id - frame;
    return d < 0 ? -d : d;
}
/* 004c9360 — камера по умолчанию на кадре 2 */
/* Adds the default camera at frame 2 (distance / max distance 0x500, field +0x18 = 0x800, +0x70 = 0xffffff00;
   TODO(RE): unsure what those two fields are). */
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
/* Frees the recorded waypoint buffer. */
void FreeDirectorBuffer(void) {
    if (DirectorBuffer) DebugFree(DirectorBuffer);
    DirectorBuffer = NULL;
    DirectorBufferCount = 0;
}
/* 004c812e */
/* Frees cameras and waypoints. */
void FreeDirectorData(void) {
    FreeCameraList();
    FreeDirectorBuffer();
}
/* 004c8e9e — запомнить состояние игровой камеры (один раз до сброса) */
/* Saves the game camera state once (until restored / dropped), also into DirectorCam. */
void BackupCameraState(void) {
    if (CamBackupValid == 0) {
        CamBackupValid = 1;
        StoreCameraState(&CamBackup);
        StoreCameraState(&DirectorCam);
    }
}
/* 004c8ed2 */
/* Forgets the saved camera state. */
void DropCameraBackup(void) {
    if (CamBackupValid != 0) CamBackupValid = 0;
}
/* 004c8eec */
/* Restores and forgets the saved camera state. */
void RestoreCameraBackup(void) {
    if (CamBackupValid != 0) {
        RestoreCameraState(&CamBackup);
        CamBackupValid = 0;
    }
}

/* 004c375a — запись путевой точки, следующая за кадром (по одной на 150 кадров), либо NULL */
/* Waypoint record after frame (one waypoint per 150 frames), or NULL. */
WAYPOINT_REC *GetWaypointAfterFrame(int frame) {
    if (!DirectorBuffer) return NULL;
    int i = frame / 150 + 1;
    if (i < DirectorBufferCount) return (WAYPOINT_REC *)DirectorBuffer + i;
    return NULL;
}
/* 004c8070 — сброс состояния режиссёра (вызывает также удаление Waypoint.tmp и временного файла камер) */
/* Resets the director state; outside replay modes (GameMode 4/5) also deletes Waypoint.tmp and $TEMP$.CAMS. */
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
/* Makes the camera of the current frame current; on a camera change moves the view to its position. */
void SyncCameraFromList(void) {
    int32_t old = DirectorUnk64;
    DIRECTOR_CAMERA *c = (DIRECTOR_CAMERA *)FindCameraRecordForFrame(DirectorUnk6C);
    if (!c) return;
    CurCamera = c;
    DirectorCam = *c;
    DirectorUnk64 = CurCamera->index;
    if (DirectorUnk64 != old) {
        const int32_t *w = (const int32_t *)c;
        SetCameraPosition((float)w[DIRCAM_W_POS], (float)w[DIRCAM_W_POS + 1], (float)w[DIRCAM_W_POS + 2]);
    }
}
/* 004c60b2 — 1, если у машины камеры нет флага 0x400 и её дальность >= порога */
/* 1 when the car watched by cam has no flag 0x400 and is at least CarMinDist away. */
int IsCameraCarFarEnough(const DIRECTOR_CAMERA *cam) {
    const CAR_OBJ *car = CarObjTable[cam->index];
    if (car->flags & 0x400) return 0;
    return CarMinDist <= car->dist ? 1 : 0;
}

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("TrafficRecs")
#undef TrafficRecs
#pragma push_macro("TrafficRecs") /*gvi*/
#undef TrafficRecs /*gvi*/
TRAFFIC_RECS_T TrafficRecs;
#pragma pop_macro("TrafficRecs") /*gvi*/
#pragma pop_macro("TrafficRecs")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirTableA")
#undef DirTableA
#pragma push_macro("DirTableA") /*gvi*/
#undef DirTableA /*gvi*/
DIRTABLE_T DirTableA;
#pragma pop_macro("DirTableA") /*gvi*/
#pragma pop_macro("DirTableA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirTableB")
#undef DirTableB
#pragma push_macro("DirTableB") /*gvi*/
#undef DirTableB /*gvi*/
DIRTABLE_T DirTableB;
#pragma pop_macro("DirTableB") /*gvi*/
#pragma pop_macro("DirTableB")
#endif
/* 004c57b7 — название типа камеры */
/* Display name of a camera type (the source of the DIRCAM_* names in names_g5.h). */
const char *GetCameraTypeName(int type) {
    switch (type) {
    case DIRCAM_CHASE:    return "Chase camera";
    case DIRCAM_FLYING:   return "Flying camera";
    case DIRCAM_INCAR:    return "In car camera";
    case DIRCAM_STATIC:   return "Static camera";
    case DIRCAM_WATCHCAR: return "Watch car camera";
    default:   return "WARNING! Unknown camera type.";
    }
}
/* 004c5222 — выбрать новую автокамеру и сделать её текущей */
/* Picks a new automatic camera, starts it at the current frame (at least 2) and makes it current. */
void SelectNewCamera(void) {
    if (!FindAutoCamera((void **)&CurCamera)) return;
    InitNewCamera(CurCamera);
    int32_t *w = (int32_t *)CurCamera;
    w[5] = DirectorUnk6C < 4 ? 2 : DirectorUnk6C;
    DirectorUnk64 = w[1];
    DirectorCam = *CurCamera;
    SetCameraPosition((float)w[DIRCAM_W_POS], (float)w[DIRCAM_W_POS + 1], (float)w[DIRCAM_W_POS + 2]);
}
/* 004c5d40 — сколько из 64 машин (тип 4, активные) ближе 30000 по плоскости к игроку (квадрат < 900000000) */
/* Number of active traffic records of kind 1 in state 4 whose car is within 30000 units (x/z) of the player.
   TODO(RE): unsure what kind 1 / state 4 are (cops in pursuit?). */
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
/* Clears both director node tables. */
void ClearDirectorTables(void) {
    ClearDirectorTable((DIR_NODE *)&DirTableA);
    ClearDirectorTable((DIR_NODE *)&DirTableB);
}

/* 004c567a — лог дампа камеры (cam: 0x8c байт как int32[0x23]) */
/* Logs a camera record (0x8c bytes as int32[0x23]) to debug.log. */
void CameraDump(const int32_t *c) {
    char buf[128];
    DebugLog("CameraDump....");
    snprintf(buf, sizeof buf, "Camera type is %d(%s)", c[0], GetCameraTypeName(c[0])); DebugLog(buf);
    snprintf(buf, sizeof buf, "Camera position is x = %d, y = %d, z = %d", c[0x13], c[0x14], c[0x15]); DebugLog(buf);
    snprintf(buf, sizeof buf, "Holding camera position is x = %d, y = %d, z = %d", c[0x17], c[0x18], c[0x19]); DebugLog(buf);
    snprintf(buf, sizeof buf, "Camera angle is %d, %d, %d", (int)*(const int16_t *)(c + 0x1f),
             (int)*((const int16_t *)(c + 0x1f) + 1), (int)*(const int16_t *)(c + 0x20)); DebugLog(buf);
    snprintf(buf, sizeof buf, "Camera distance is %d", c[2]); DebugLog(buf);
    snprintf(buf, sizeof buf, "Cameras maximum distance is %d", c[3]); DebugLog(buf);
    DebugLog("End of Camera dump\n");
}
