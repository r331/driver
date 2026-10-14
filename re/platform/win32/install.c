/* Регистрация перенесённых функций для hook-сборки (Game.exe + DINPUT.dll) */
#include "hook.h"
#include "../../game/director.h"
#include "../../game/directorstorage.h"
void re_install_all(void) {
    re_hook(0x004c6168, (void*)FindCameraById,    "FindCameraById");
    re_hook(0x004c622c, (void*)RenumberCameras,   "RenumberCameras");
    re_hook(0x004c6312, (void*)InsertCamera,      "InsertCamera");
    re_hook(0x004c6524, (void*)DeleteCamera,      "DeleteCamera");
    re_hook(0x004c6264, (void*)AddDirectorCamera, "AddDirectorCamera");
    re_hook(0x004c60fa, (void*)SetCamera,           "SetCamera");
    re_hook(0x004c6142, (void*)GetCamera,           "GetCamera");
    re_hook(0x004c61b2, (void*)FindCameraForFrame,  "FindCameraForFrame");
    re_hook(0x004c64bd, (void*)FreeCameraList,      "FreeCameraList");
    re_hook(0x004c6691, (void*)FindNearestCamera,   "FindNearestCamera");
    re_hook(0x004c6715, (void*)CameraFrameDistance, "CameraFrameDistance");
    re_hook(0x004c9360, (void*)AddDefaultCamera,    "AddDefaultCamera");
    re_hook(0x004c988e, (void*)WriteReplayHeaderChunk, "WriteReplayHeaderChunk");
    re_hook(0x004c96d6, (void*)WriteWaypointChunk,     "WriteWaypointChunk");
    re_hook(0x004c97a2, (void*)WriteCameraChunk,       "WriteCameraChunk");
    re_hook(0x004c9621, (void*)WriteDirectorData,      "WriteDirectorData");
    re_hook(0x004c9bf4, (void*)LogWaypoint,            "LogWaypoint");
    re_hook(0x004c372a, (void*)FreeDirectorBuffer,  "FreeDirectorBuffer");
    re_hook(0x004c812e, (void*)FreeDirectorData,    "FreeDirectorData");
    re_hook(0x004c8e9e, (void*)BackupCameraState,   "BackupCameraState");
    re_hook(0x004c8ed2, (void*)DropCameraBackup,    "DropCameraBackup");
    re_hook(0x004c8eec, (void*)RestoreCameraBackup, "RestoreCameraBackup");
    re_hook(0x004c93e6, (void*)ReadDirectorData,    "ReadDirectorData");
    re_hook(0x004c98de, (void*)ReadCameraChunkV2,   "ReadCameraChunkV2");
    re_hook(0x004c9a16, (void*)ReadCameraChunkV1,   "ReadCameraChunkV1");
    re_hook(0x004c9ca0, (void*)LoadWaypoints,       "LoadWaypoints");
    re_hook(0x004c9dcc, (void*)DeleteWaypointFile,  "DeleteWaypointFile");
    re_hook(0x004c375a, (void*)GetWaypointAfterFrame, "GetWaypointAfterFrame");
    re_hook(0x004c8070, (void*)ResetDirectorState,  "ResetDirectorState");
    re_hook(0x004c52d9, (void*)SyncCameraFromList,  "SyncCameraFromList");
    re_hook(0x004c60b2, (void*)IsCameraCarFarEnough, "IsCameraCarFarEnough");
}
