/* Проверка перенесённых модулей в нативной сборке: ./driver --selftest */
#include "../game/uihandlers3.h"
#include "../game/uihandlers4.h"
#include "../game/menuselect.h"
#include "../game/director.h"
#include "../game/directorstorage.h"
#include "../game/dirnodes.h"
#include "../game/menustate.h"
#include "../game/uihandlers.h"
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
    {
        static CAR_OBJ car = {{0}, 0, {0}, 5.0f}; DIRECTOR_CAMERA c; memset(&c, 0, sizeof c); c.index = 3;
        CarObjTable[3] = &car; CarMinDist = 2.0f;
        CHECK(IsCameraCarFarEnough(&c) == 1);
        car.flags = 0x400; CHECK(IsCameraCarFarEnough(&c) == 0);
        car.flags = 0; CarMinDist = 9.0f; CHECK(IsCameraCarFarEnough(&c) == 0);
    }
    CHECK(!strcmp(GetCameraTypeName(0x11), "Watch car camera") && !strcmp(GetCameraTypeName(7), "WARNING! Unknown camera type."));
    { int32_t cd[0x23] = {0x11}; CameraDump(cd); }
    memset(TrafficRecs, 0, sizeof TrafficRecs); memset(ObjPosTable, 0, sizeof ObjPosTable);
    CHECK(CountNearbyCars() == 0);
    TrafficRecs[5] = 1; TrafficRecs[0xc] = 1; TrafficRecs[1] = 4;      /* машина 0 рядом (ObjPos[1] = 0,0) */
    CHECK(CountNearbyCars() == 1);
    ObjPosTable[0x52] = 40000; CHECK(CountNearbyCars() == 0);          /* 40000^2 > 9e8 */
    return 0;
}
static int test_nodes(void) {
    DIR_NODE n[3]; memset(n, 0, sizeof n);
    n[0].id = 5; n[0].link1 = 7; n[0].gx = 1; n[0].gy = 2;
    n[1].id = 7; n[1].link2 = 9;
    n[2].id = 0xffff;
    DirNodeTable = n;
    CHECK(FindNodeById(7) == &n[1] && !FindNodeById(0) && !FindNodeById(8));
    CHECK(FindNodeByLink(7) == &n[0] && FindNodeByLink(9) == &n[1] && !FindNodeByLink(3));
    CHECK(FindNodeAtPixel(0x35 + 0x10, 2 * 0x35 + 0x3c) == 5 && FindNodeAtPixel(0x35 + 0x3d, 2 * 0x35 + 0x10) == 0);
    CHECK(SetNodeEnabled(5, 0) == 1 && (n[0].flags & 4) && SetNodeEnabled(5, 1) == 0 && !(n[0].flags & 4));
    n[0].unk18 = 7;
    CHECK(GetNodeParent(5) == &n[1] && !GetNodeParent(7) && !GetNodeParent(0));
    WAYPOINT_REC w[2]; DirectorBuffer = w; DirectorBufferCount = 2;
    CHECK(GetWaypointForFrame(2) == &w[0] && GetWaypointForFrame(152) == &w[1]);
    CHECK(!GetWaypointForFrame(302) && !GetWaypointForFrame(3));
    n[0].unk00 = 1; DrawNodeMarker(&n[0]); DrawNode(&n[0]); n[0].flags |= 1; DrawNodeMarker(&n[0]);
    DirUseDI = 0; KeyState[0xd04bcb-0xd04b00] = 1; KeyState[0xd04b2a-0xd04b00] = 1; CHECK(ReadDirectorKeys() == 0x81); KeyState[0xd04bcb-0xd04b00]=0; KeyState[0xd04b2a-0xd04b00]=0;
    DumpWaypoints(); DirIndicatorOn = 1; DirIndicatorCnt = 0; DirectorUnk84 = 4; DrawCornerIndicator(); DirIndicatorOn = 0;
    return 0;
}
static int test_menu(void) {
    MenuFlagSet(); if (MenuFlag5F7E4C != 1) return 1;
    MenuFlagUpdate(1); if (MenuFlag5F7E4C != 1) return 1;
    MenuFlagUpdate(2); if (MenuFlag5F7E4C != 0) return 1;
    MenuOptBDFA44 = 0; MenuToggleOptBDFA44(); if (MenuOptBDFA44 != 1) return 1;
    MenuToggleOptBDFA44(); if (MenuOptBDFA44 != 0 || MenuReturnOne() != 1) return 1;
    MenuFlag54A0BCSet(); if (MenuFlag54A0BC != 1) return 1; MenuFlag54A0BCClear(); MenuVar54A0CC = 5; MenuVar54A0CCClear(); MenuCounter5D577C = 7; MenuCounter5D577CInc();
    { static const uint8_t b[3]={1,2,250}; if (SumBytes(b,3)!=253) return 1; MenuSrcC559A4=11; MenuSrcC559A8=22; MenuCopyPos(); if (MenuDst54A0C0!=11||MenuDst54A0D0!=22) return 1; }
    if (MenuFlag54A0BC != 0 || MenuVar54A0CC != 0 || MenuCounter5D577C != 8) return 1;
    return MenuStateSetFour() != 0 || MenuState575EF0 != 4;
}

static int test_menu2(void) {
    MenuVar55384C = 0; MenuVar575EF8 = 0;
    MenuToggle55384CRedraw(); if (MenuVar55384C != 1 || MenuVar575EF8 != 4) return 1;
    MenuToggle55384CRedraw(); if (MenuVar55384C != 0) return 1;
    MenuVar5759A4 = 0x3f; MenuIncVar5759A4(); MenuIncVar5759A4(); if (MenuVar5759A4 != 0x40) return 1;
    MenuVar5759A4 = 1; MenuDecVar5759A4(); MenuDecVar5759A4(); if (MenuVar5759A4 != 0) return 1;
    MenuVarB87E4C = 2; MenuIncVarB87E4C(); MenuIncVarB87E4C(); if (MenuVarB87E4C != 3) return 1;
    MenuVarB87E4C = 1; MenuDecVarB87E4C(); MenuDecVarB87E4C(); if (MenuVarB87E4C != 0) return 1;
    MenuEnterMode5(); if (MenuFlag54A8FC != 1 || MenuMode1271060 != 5) return 1;
    MenuLeaveMode5(1); if (!MenuFlag54A8FC) return 1; MenuLeaveMode5(0); if (MenuFlag54A8FC) return 1;
    MenuSet54A844On(); if (MenuVar54A844 != 1) return 1; MenuSet54A844Off(); if (MenuVar54A844 != 0) return 1;
    MenuSet54A854On(); if (MenuVar54A854 != 1) return 1; MenuSet54A854Off(); if (MenuVar54A854 != 0) return 1;
    return 0;
}
static int test_menu3(void) {
    MenuSet54BE5CTo3(); MenuSet54BE7CTo2();
    if (MenuByte54BE5C != 3 || MenuByte54BE7C != 2) return 1;
    MenuSet54BE5CTo2(); MenuSet54BE7CTo3();
    return (MenuByte54BE5C != 2 || MenuByte54BE7C != 3);
}

static int test_menu4(void) {
    MenuSet54ACD4To3(); MenuSet54ACF4To3(); MenuSet54AD14To3(); MenuSet54AD34To3();
    if (MenuByte54ACE4 != 3 || MenuByte54AD04 != 3 || MenuByte54AD24 != 3 || MenuByte54AD44 != 3) return 1;
    MenuTable54B010[7] = 0xabcd; return MenuTableGet54B010(0x107) != 0xabcd;
}

static int test_menu5(void) {
    MenuSelect00407334(1);
    if (MenuB00549F8C != 3 || MenuB00549F9C != 3) return 1;
    MenuSelect00407334(2);
    if (MenuI0057B730 != 1 || MenuI0054A060 != 2) return 1;
    MenuSelect004091A0(2);
    if (MenuI0054A694 != -1 || MenuFlag5F7E4C != 1) return 1;
    MenuLeave0040E8FF(0); MenuLeave0040E8FF(1);
    return (MenuByte54ACD4 != 2 || MenuByte54ACE4 != 2);
}

static int test_ui3(void) {
    CHECK(Round1024(0) == 0 && Round1024(0x200) == 1 && Round1024(0x5ff) == 1 && Round1024(0x600) == 2);
    CHECK(Ret1FFFF8IfZero(0) == 0x1ffff8 && Ret1FFFF8IfZero(3) == 0);
    G00B1FFBC = 4; Inc0B1FFBC(); CHECK(G00B1FFBC == 5);
    G01145934 = 1; Dec145934(); Dec145934(); CHECK(G01145934 == 0);
    FlagSet0127104C(3); CHECK(G0127104C == 8);
    SetScale54EF38(2.0f); CHECK(G0054EF38 == 2.0f);
    UiSetMode005FEEEC_5(); CHECK(G005FEEEC == 5);
    G00B1C0D4 = 0; CHECK(GameCall00424661(7) == 0);
    G0112B284 = 7; CHECK(IsVar112B284Lt8() == 1);
    return 0;
}
static int test_ui4(void) {
    G005759A4 = 0x3f;
    Inc5759A4Max40(); CHECK(G005759A4 == 0x40); Inc5759A4Max40(); CHECK(G005759A4 == 0x40);
    G005759A4 = 1; Dec5759A4Min0(); Dec5759A4Min0(); CHECK(G005759A4 == 0);
    G0054A90C = 5; Clear54A90C_IfZero(1); CHECK(G0054A90C == 5); Clear54A90C_IfZero(0); CHECK(G0054A90C == 0);
    Select54A94C_Mode7(); CHECK(G0054A94C == 1 && G01271060 == 7);
    return 0;
}
static int test_ui(void) {
    UiVar005FE84C = 0; UiVar005FE84C = 0;
    Ui00412F62(); CHECK(Ui00412F9C() == 1);
    CHECK(Ui00412F62() == -1);
    CHECK(Ui004157A9() == 0);
    return 0;
}
int re_selftest(void) {
    int f = test_director() | test_director2() | test_storage() | test_read() | test_nodes() | test_menu() | test_menu2() | test_menu3() | test_menu4() | test_menu5() | test_ui() | test_ui3() | test_ui4();
    printf("selftest: director %s\n", f ? "FAIL" : "OK");
    return f;
}
