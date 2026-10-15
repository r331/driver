/* Director.c — режиссёр повторов. */
#pragma once
#include "gvar.h"
typedef struct DIRECTOR_CAMERA {
    int32_t unk00;
    int32_t index;      /* +0x04 */
    int32_t unk08;      /* +0x08 (0x500 у камеры по умолчанию) */
    int32_t unk0c;      /* +0x0c (0x500) */
    int32_t unk10;
    int32_t id;         /* +0x14 — кадр повтора, с которого действует камера */
    int32_t unk18;      /* +0x18 (0x800) */
    uint8_t pad1c[0x70 - 0x1c];
    int32_t unk70;      /* +0x70 (0xffffff00) */
    uint8_t rest[0x8c - 0x74];
} DIRECTOR_CAMERA;      /* 0x8c байт, см. InsertCamera */
_Static_assert(sizeof(DIRECTOR_CAMERA) == 0x8c, "DIRECTOR_CAMERA size");

typedef struct WAYPOINT_REC {   /* запись Scripts\Waypoint.tmp и DirectorBuffer */
    int32_t x, z;       /* координаты игрока, округлённые до 1500 */
    int32_t frame;
} WAYPOINT_REC;
_Static_assert(sizeof(WAYPOINT_REC) == 12, "WAYPOINT_REC size");

#define NumCameras  GAME_VAR(int32_t,           NumCameras, 0x00d17b60)
#define CurCamera   GAME_VAR(DIRECTOR_CAMERA*,  CurCamera,  0x00d17c50)
#define CameraList  GAME_VAR(DIRECTOR_CAMERA**, CameraList, 0x00d17c54)
#define DirectorLastFrame   GAME_VAR(int32_t,          DirectorLastFrame,   0x00d17b68) /* последний кадр повтора */
#define CamBackupValid      GAME_VAR(int32_t,          CamBackupValid,      0x00d17bb4)
#define DirectorCam         GAME_VAR(DIRECTOR_CAMERA,  DirectorCam,         0x00d17bc4) /* рабочая копия камеры */
#define DirectorBuffer      GAME_VAR(void*,            DirectorBuffer,      0x00d17c5c)
#define DirectorBufferCount GAME_VAR(int32_t,          DirectorBufferCount, 0x00d17b70)
#define CamBackup           GAME_VAR(DIRECTOR_CAMERA,  CamBackup,           0x00d17c64) /* предположительно та же структура */
#define DirectorUnk64   GAME_VAR(int32_t, DirectorUnk64, 0x00d17b64)
#define DirectorUnk6C   GAME_VAR(int32_t, DirectorUnk6C, 0x00d17b6c)
#define DirectorUnk7C   GAME_VAR(int32_t, DirectorUnk7C, 0x00d17b7c)
#define DirectorUnk84   GAME_VAR(int32_t, DirectorUnk84, 0x00d17b84)
#define DirectorUnk88   GAME_VAR(int32_t, DirectorUnk88, 0x00d17b88)
#define DirectorUnk8C   GAME_VAR(int32_t, DirectorUnk8C, 0x00d17b8c)
#define GameMode        GAME_VAR(int32_t, GameMode,      0x005f7e50)   /* 4 и 5 — режимы, где временные файлы режиссёра не трогаем */
typedef uint8_t TRAFFIC_RECS_T[0x40 * 0x54];
typedef int32_t OBJPOS_T[0x52 * 65];
typedef uint8_t DIRTABLE_T[64];
#define TrafficRecs GAME_VAR(TRAFFIC_RECS_T, TrafficRecs, 0x011443e0)
#define ObjPosTable CARTAB_VAR(OBJPOS_T, ObjPosTable, 0x00d07888)
#define DirTableA   GAME_VAR(DIRTABLE_T, DirTableA, 0x0055f088)
#define DirTableB   GAME_VAR(DIRTABLE_T, DirTableB, 0x0055f030)
#ifndef RE_HOOK_BUILD
extern TRAFFIC_RECS_T TrafficRecs; extern DIRTABLE_T DirTableA, DirTableB;
extern int32_t DirectorUnk64, DirectorUnk6C, DirectorUnk7C, DirectorUnk84, DirectorUnk88, DirectorUnk8C, GameMode;
extern int32_t NumCameras; extern DIRECTOR_CAMERA *CurCamera; extern DIRECTOR_CAMERA **CameraList;
extern int32_t DirectorLastFrame, CamBackupValid, DirectorBufferCount;
extern DIRECTOR_CAMERA DirectorCam, CamBackup; extern void *DirectorBuffer;
#endif

DIRECTOR_CAMERA *FindCameraById(int id);
void RenumberCameras(void);
void DeleteCamera(int idx);
DIRECTOR_CAMERA *InsertCamera(DIRECTOR_CAMERA *cam, int pos);
DIRECTOR_CAMERA *AddDirectorCamera(DIRECTOR_CAMERA *cam, int id);
void SetCamera(const DIRECTOR_CAMERA *src, int idx);
DIRECTOR_CAMERA *GetCamera(int idx);
DIRECTOR_CAMERA *FindCameraForFrame(int frame);
void FreeCameraList(void);
DIRECTOR_CAMERA *FindNearestCamera(int frame);
int  CameraFrameDistance(const DIRECTOR_CAMERA *cam, int frame);
void AddDefaultCamera(void);
void FreeDirectorBuffer(void);
void FreeDirectorData(void);
void BackupCameraState(void);
void DropCameraBackup(void);
void RestoreCameraBackup(void);
WAYPOINT_REC *GetWaypointAfterFrame(int frame);   /* 004c375a */
void ResetDirectorState(void);                    /* 004c8070 */

typedef struct CAR_OBJ { uint8_t pad0[8]; uint32_t flags; uint8_t pad0c[4]; float dist; } CAR_OBJ; /* +8 флаги, +0x10 дальность */
_Static_assert(sizeof(CAR_OBJ) == 0x14, "CAR_OBJ size");
#ifdef RE_HOOK_BUILD
#  define CarObjTable (*(CAR_OBJ*(*)[])(uintptr_t)0x00cfe7a0)   /* массив указателей CAR_OBJ* */
#  define CarMinDist  (*(float*)(uintptr_t)0x00546200)
#else
extern CAR_OBJ *CarObjTable[]; extern float CarMinDist;
#endif
void SyncCameraFromList(void);
int  IsCameraCarFarEnough(const DIRECTOR_CAMERA *cam);

const char *GetCameraTypeName(int type);          /* 004c57b7 */
void SelectNewCamera(void);                       /* 004c5222 */
int  CountNearbyCars(void);                       /* 004c5d40 */
void ClearDirectorTables(void);                   /* 004c810f */
void CameraDump(const int32_t *cam);              /* 004c567a */
