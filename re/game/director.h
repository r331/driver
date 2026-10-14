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

#define NumCameras  GAME_VAR(int32_t,           NumCameras, 0x00d17b60)
#define CurCamera   GAME_VAR(DIRECTOR_CAMERA*,  CurCamera,  0x00d17c50)
#define CameraList  GAME_VAR(DIRECTOR_CAMERA**, CameraList, 0x00d17c54)
#define DirectorLastFrame   GAME_VAR(int32_t,          DirectorLastFrame,   0x00d17b68) /* последний кадр повтора */
#define CamBackupValid      GAME_VAR(int32_t,          CamBackupValid,      0x00d17bb4)
#define DirectorCam         GAME_VAR(DIRECTOR_CAMERA,  DirectorCam,         0x00d17bc4) /* рабочая копия камеры */
#define DirectorBuffer      GAME_VAR(void*,            DirectorBuffer,      0x00d17c5c)
#define DirectorBufferCount GAME_VAR(int32_t,          DirectorBufferCount, 0x00d17b70)
#define CamBackup           GAME_VAR(DIRECTOR_CAMERA,  CamBackup,           0x00d17c64) /* предположительно та же структура */
#ifndef RE_HOOK_BUILD
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
