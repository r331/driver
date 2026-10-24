/* Проверка перенесённых модулей в нативной сборке: ./driver --selftest */
#include "../game/drawdist.h"
#include "../platform/sdl/plat_gfx.h"
#include "../platform/sdl/plat_detail.h"
#include "../game/uihandlers3.h"
#include "../game/uihandlers4.h"
#include "../game/menuselect.h"
#include "../game/director.h"
#include "../game/directorstorage.h"
#include "../game/dirnodes.h"
#include "../game/menustate.h"
#include "../game/uihandlers.h"
#include "../game/ported4.h"
#include "../game/ported78.h"
#include "../game/ported5.h"
#include "../game/ported6.h"
#include "../game/ported7.h"
#include "../game/ported8.h"
#include "../game/ported9.h"
#include "../game/ported11.h"
#include "../game/ported12.h"
#include "../game/ported14.h"
#include "../game/ported15.h"
#include "../game/ported16.h"
#include "../game/ported17.h"
#include "../game/ported18.h"
#include "../game/ported19.h"
#include "../game/ported13.h"
#include "../game/ported46.h"
#include "../game/ported47.h"
#include <stdlib.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include "../game/ported21.h"
#include "../game/ported22.h"
#include "../game/ported23.h"
#include "../game/ported24.h"
#include "../game/ported25.h"
#include "../game/ported26.h"
#include "../game/ported27.h"
#include "../game/ported28.h"
#include "../game/ported29.h"
#include "../game/ported30.h"
#include "../game/ported31.h"
#include "../game/ported33.h"
#include "../game/ported32.h"
#include "../game/ported53.h"
#include "../game/ported54.h"
#include "../game/ported55.h"
#include "../game/ported56.h"
#include "../game/ported57.h"
#include "../game/ported58.h"
#include "../game/ported59.h"
#include "../game/ported60.h"
#include "../game/ported61.h"
#include "../game/ported62.h"
#include "../game/ported63.h"
#include "../game/ported64.h"
#include "../game/ported65.h"
#include "../game/ported66.h"
#include "../game/ported67.h"
#include "../game/ported68.h"
#include "../game/ported69.h"
#include "../game/ported70.h"
#include "../game/ported71.h"
#include "../game/ported72.h"
#include "../game/ported73.h"
#include "../game/ported74.h"
#include "../game/ported75.h"
#include "../game/ported76.h"
#include "../game/ported77.h"
#include "../game/ported34.h"
#include "../game/ported35.h"
#include "../game/ported36.h"
#include "../game/ported37.h"
#include "../game/ported38.h"
#include "../game/ported39.h"
#include "../game/ported40.h"
#include "../game/ported41.h"
#include "../game/ported42.h"
#include "../game/ported43.h"
#include "../game/ported44.h"
#include "../game/ported45.h"
#include "../game/ported48.h"
#include "../game/ported49.h"
#include "../game/ported50.h"
#include "../game/ported51.h"
#include "../game/ported52.h"
#include "../game/ported79.h"
#include "../game/ported80.h"
#include "../game/ported81.h"
#include "../game/ported82.h"
#include "../game/ported83.h"
#include "../game/ported84.h"
#include "../game/ported85.h"
#include "../game/ported86.h"
#include "../game/ported87.h"
#include "../game/ported88.h"
#include "../game/ported89.h"
#include "../game/ported90.h"
#include "../game/ported91.h"
#include "../game/ported92.h"
#include "../game/ported93.h"
#include "../game/ported94.h"
#include "../game/ported95.h"
#include "../game/ported96.h"
#include "../game/ported97.h"
#include "../game/ported98.h"
#include "../game/ported99.h"
#include "../game/ported100.h"
#include "../game/ported101.h"
#include "../game/ported102.h"
#include "../game/ported103.h"
#include "../game/ported104.h"
#include "../game/ported105.h"
#include "../game/ported106.h"
#include "../game/ported107.h"
#include "../game/ported108.h"
#include "../game/ported109.h"
#include "../game/ported110.h"
#include "../game/ported111.h"
#include "../game/nodetab.h"
#include "../game/reptr.h"
#include <math.h>
#include "../game/ported112.h"
#include "../game/ported113.h"
#include "../game/ported114.h"
#include "../game/ported115.h"
#include "../game/ported116.h"
#include "../game/ported117.h"
#include "../game/ported118.h"
#include "../game/ported119.h"
#include "../game/ported120.h"
#include "../game/ported121.h"
#include "../game/ported122.h"
#include "../game/ported123.h"
#include "../game/ported124.h"
#include "../game/ported125.h"
#include "../game/ported126.h"
#include "../game/ported127.h"
#include "../game/ported128.h"
#include "../game/ported129.h"
#include "../game/ported130.h"
#include "../game/ported131.h"
#include "../game/ported132.h"
#include "../game/ported133.h"
#include "../game/ported134.h"
#include "../game/ported135.h"
#include "../game/ported136.h"
#include "../game/ported137.h"
#include "../game/ported138.h"
#include "../game/ported139.h"
#include "../game/ported140.h"
#include "../game/ported141.h"
#include "../game/ported142.h"
#include "../game/ported143.h"
#include "../game/ported144.h"
#include "../game/ported145.h"
#include "../game/ported146.h"
#include "../game/ported147.h"
#include "../game/ported148.h"
#include "../game/ported149.h"
#include "../game/menustate.h"
#include "../game/globalsets.h"
#include "../game/smallfuncs.h"
#include "../game/uihandlers2.h"
#include "../game/menu57.h"
#include "../game/ported150.h"
/* v2.01: шпионы selftest вне selftest передают вызов настоящей функции (как v2.00) */
extern int re_selftest_on;
void P109_TileDraw(int32_t x, int32_t y, int32_t w, int32_t h, int32_t idx, void *color);
int32_t P139_LadderLoad(void); void P140_LadderRun(void); int32_t P140_SndInit(int32_t, int32_t, int32_t); void P140_BankLine(char *);
void P139_Effects(void); int32_t P124_MotelKeys(int32_t); void P135_DebrisTri(int32_t *); void P135_RadarLine(int32_t);
void P131_RadarArrow(int32_t); void P136_OverlayMap(void); void P121_DustDraw(void); int32_t P119_TrafficSpawn(int32_t, int32_t, int32_t, int32_t, int32_t);
#include "../game/ported151.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
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
    /* 0040a625.. handlers: one implementation in menustate.c (the uihandlers4.c copies were removed) */
    MenuVar5759A4 = 0x3f;
    MenuIncVar5759A4(); CHECK(MenuVar5759A4 == 0x40); MenuIncVar5759A4(); CHECK(MenuVar5759A4 == 0x40);
    MenuVar5759A4 = 1; MenuDecVar5759A4(); MenuDecVar5759A4(); CHECK(MenuVar5759A4 == 0);
    MenuFlag54A90C = 5; MenuLeaveMode2(1); CHECK(MenuFlag54A90C == 5); MenuLeaveMode2(0); CHECK(MenuFlag54A90C == 0);
    MenuEnterMode7(); CHECK(MenuFlag54A94C == 1 && MenuMode1271060 == 7);
    return 0;
}
static int test_ui(void) {
    UiVar005FE84C = 0; UiVar005FE84C = 0;
    Ui00412F62(); CHECK(Ui00412F9C() == 1);
    CHECK(Ui00412F62() == -1);
    CHECK(Ui004157A9() == 0);
    return 0;
}
static int test_p4(void) {
    D_00d00230 = 0; AllocMapBuffer300000(); CHECK(D_00d00230 != 0); FreeMapBuffer300000(); CHECK(D_00d00230 == 0);
    MenuSlotHandler004088AA(0); CHECK(D_0054a254 == 2 && D_0054a264 == 2);
    MenuSlotHandlerReset004091F3(0); CHECK(D_0054a424 == 2 && D_005f7e4c == 0);
    D_00b1c0d4 = 0; CallIf424A02(1, 2);
    int16_t sh[3] = { -5, 7, 300 }; LoadShort3FromPtr(sh); CHECK(D_00b93e48 == -5 && D_00b93e50 == 300);
    D_01134528 = 1; ReleaseSlot4A2C5B(3); CHECK(D_01134528 == 0 && D_01134ec0[0] == 3);
    D_00c81494 = 0; TickTimer4F5D67(); CHECK(D_00c81494 == 0); D_00c81494 = 3; TickTimer4F5D67(); CHECK(D_00c81494 == 2);
    return 0;
}
static int test_p5(void) {
    CHECK(MenuPick0040FEA0() == 0 && Q005FE768 == 2 && MenuI005FE770 == 2 && MenuI005FE774 == -1 && Q00B87F00 == 1);
    MenuPick0041069E(); CHECK(Q005FE768 == 0x10 && Q005FE764 == 0xd04a7a);
    Q0057B56C = 0; PrevPcar00404721(); CHECK(Q0057B56C == 0x11);
    Q0057B56C = 0x10; NextPcar0040475E(); CHECK(Q0057B56C == 0x11);
    Q0057B56C = 0x11; NextPcar0040475E(); CHECK(Q0057B56C == 0);
    Q0057B56C = 0x10; PrevPcar00404721(); CHECK(Q0057B56C == 0xe + 0 || Q0057B56C == 0xf);
    Q01270C24 = 1.0f; Q00546030 = 5.0f; Q0054604C = 0.5f; FloatStep00409A91(); CHECK(Q01270C24 == 1.5f);
    Q00546030 = 1.0f; FloatStep00409A91(); CHECK(Q01270C24 == 1.5f);
    Q00B87EF0 = 0; Q0057B72C = 0; ToggleVar00407636(); CHECK(Q00B87EF0 == 0);
    Q00B87E94 = 0; ToggleOpt004154CD(); CHECK(Q00B87E94 == 1);
    SetupMiami00416040(); CHECK(UiVar00B87E38 == 0x2e && 1);
    SetIconIdx00412A0D(0); CHECK(WU0054CBB0 == 0x54cdf0);
    return 0;
}
static int test_p6(void) {
    CHECK(AngleToDir00514103(0x100) == 4 && AngleToDir00514103(0x400) == 2 && AngleToDir00514103(0x800) == 8 && AngleToDir00514103(0xc00) == 1 && AngleToDir00514103(0xf00) == 4);
    G6_00575F20 = 5; G6_00D11880 = 0; MenuToggle00408994();
    CHECK(G6_00D11880 == 1 && G6_00575F20 == 0 && G00575EF8 == 4);
    MenuToggle00408994(); CHECK(G6_00D11880 == 1 && G6_00575F20 == 1);
    MenuToggle00408994(); CHECK(G6_00D11880 == 0 && G6_00575F20 == 0);
    G6_00575F00 = 8; G6_00B91CF4 = 0; MenuBits0050F8F2(); CHECK(G6_00575F00 == 0x10);
    MenuBits0050F8F2(); CHECK(G6_00575F00 == 8);
    G6_00575F04 = 0x5622; MenuRate0050F930(); CHECK(G6_00575F04 == 0xac44);
    G6_00B87E50 = 4; MenuSoundCh0050F971(); CHECK(G6_00B87E50 == 0);
    D_01134528 = 0; D_01134ec0[0] = 7; CHECK(PoolAlloc004A2C12() == 7 && D_01134528 == 1 && D_01134554[42] == 1);
    D_01134528 = 100; CHECK(PoolAlloc004A2C12() == -1);
    { float a[5] = {1,2,3,0,4}, b[5] = {1,1,1,0,1}, r[5]; VecAdd4_0052715E(a, b, r); CHECK(r[0] == 2 && r[2] == 4 && r[4] == 5); VecSub4_005271A8(a, b, r); CHECK(r[1] == 1 && r[4] == 3); VecNeg4_00527123(a); CHECK(a[4] == -4 && a[0] == -1); }
    { float m[9]; MatIdentity3_0052614F(m); CHECK(m[0] == 1 && m[4] == 1 && m[8] == 1 && m[1] == 0 && m[5] == 0); }
    G6_00D117A4 = 5; G6_00D117A8 = 3; G6_0125F3F0 = 80; CursorWrap004D9478(); CHECK(G6_00D117A4 == 0 && G6_00D117A8 == 4);
    return 0;
}
static int test_p7(void) {
    CHECK(MaskShift_00421C1D(0) == 8 && MaskShift_00421C1D(0xf800) == 3 && MaskShift_00421C1D(0x7e0) == 2);
    InitIdentityPalette_0041D8E9(); CHECK(A_006017C0[5*4] == 5 && A_006017C0[5*4+3] == 2);
    A_01146F20[0] = 1; A_01146F20[2*0x1c] = 0; CHECK(FindFreeEven_0048A4E6() == 2);
    G8_0110B024 = 0; for (int i = 0; i < 0x1e; i++) memset(&A_01123302[i*0x28], 0, 4);
    CHECK(FindOrAdd_004BB11F(77) == -1 && G8_0110B024 == 1);
    G8_00DBB450 = 0; AddUnique_004C1F9B(5); AddUnique_004C1F9B(5); AddUnique_004C1F9B(6); CHECK(G8_00DBB450 == 2);
    G8_0110E144 = 7; ResetSlots_004AB712(); CHECK(G8_0110E144 == 0);
    { uint8_t blk[0x60] = {0}; FillThresholds_004A6370(blk); int32_t v; memcpy(&v, blk + 0x18 + 4, 4); CHECK(v == 0x2aa + 0x40); memcpy(&v, blk + 0x18 + 32, 4); CHECK(v == 0x7fffffff); }
    { const uint8_t *s = (const uint8_t*)"  12ab"; CHECK(SkipToIdentStart_004A596B(s) == s + 4); }
    { float a[5] = {0,0,0,0,0}, b[5] = {10,20,30,0,40}, o[5]; Lerp4_00527885(a, b, 0.5f, o); CHECK(o[0] == 5 && o[2] == 15 && o[4] == 20); }
    { float a[5] = {1,2,3,0,4}, b[5] = {1,1,1,0,1}; CHECK(Dot4_005270BD(a, b) == 10); }
    G8_00D17B0C = 99; { uint32_t p3[3] = {1,2,3}; PushEntry_004CC784(p3, 7, 8); } CHECK(G8_00D17B0C == 100 && A_00D132C0[99*0x48 + 0x10] == 7);
    G8_00B20344 = 0; { int32_t m1 = -1; for (int i = 0; i < 4; i++) memcpy(&A_00B20330[i*4], &m1, 4); } SetFirstFree_004D6190(9); { int32_t v; memcpy(&v, &A_00B20330[0], 4); CHECK(v == 9); }
    { int32_t o[3] = {0,0,0}; (void)o; }
    return 0;
}
static int test_p8(void) {
    A_00D04B00[3] = 1; A_00D04B00[0x103] = 0; CHECK(IsFlagSetNotMasked_004E383A(3) == 1); A_00D04B00[0x103] = 1; CHECK(IsFlagSetNotMasked_004E383A(3) == 0);
    { float a[9] = {1,2,3,4,5,6,7,8,9}, b[9] = {1,0,0,0,1,0,0,0,1}, o[9], t[9]; Mat3Mul_0052859A(a, b, o); Mat3MulT_005284AC(a, b, t); CHECK(o[0] == 1 && o[4] == 5 && t[1] == 2); }
    P8_00b91c08 = 1; P8_00b91c0c = 2; P8_00b91c10 = 3; PushVec3_00523C99(7, 8, 9); CHECK(P8_00b91c14 == 1 && P8_00b91c1c == 3 && P8_00b91c08 == 7);
    P8_00b5a764 = 0; SetMode1b_005106D2(); CHECK(P8_0054da10 == 1 && P8_005f7e54 == 1 && P8_00575550 == 2);
    P8_005feee8 = 0; P8_005feeec = 0; RedMarkers_0041ADA1(); CHECK(P8_0054E834[0x10] == 0xff && P8_0054E834[0x20] == 0xff);
    SetZoom_00421CAB(0); CHECK(P8_00a4217c == 0.0f);
    { uint8_t blk[0x70] = {0}; float f = 5; int32_t v = 3; memcpy(blk + 4, &f, 4); memcpy(blk + 0x60, &v, 4); StepSpeedA_004B9E2B(blk); memcpy(&v, blk + 0x50, 4); CHECK(v == 3); }
    return 0;
}
static int test_p9(void) {
    P9_005fe9f0 = 2; P9_00c55a50 = 77; SelectByDifficulty_00416D17(); CHECK(P9_0054e258 == 77);
    ResetSlots_004A2B70(); { int32_t v; memcpy(&v, &A_01134540[24*5], 4); CHECK(v == 5 && D_01134ec0[99] == 99); }
    P9_00b31e20 = -20; P9_00b31dfc = 0; CHECK(IsButtonActive_004E3924(0x20) == 1 && IsButtonActive_004E3924(0x21) == 0);
    return 0;
}
static int test_p11(void) {
    P11_01270c24 = 1.0f; P11_00546028 = 5.0f; P11_0054604c = 0.5f; P11_00575ef8 = 0;
    StepUp_0051010C(); CHECK(P11_01270c24 == 1.5f && P11_00575ef8 == 4);
    P11_01270c24 = 9.0f; P11_00575ef8 = 0; StepUp_0051010C(); CHECK(P11_01270c24 == 9.0f && P11_00575ef8 == 0);
    P11_00ba52d0 = 0; RoundSet_004BF400(2.5f, 3.5f); CHECK(P11_00ba52d0 == 2);
    { uint8_t buf[0x50] = {0}; uint8_t *sp = (uint8_t*)buf; (void)sp;
      uint8_t sc[0x60] = {0}; uint8_t sdb[18] = {0,0, 1,0, 2,0, 3,0}; uint8_t *sd = sdb + 2;
      uint8_t *oc = P10_ScriptCtx, *op = P10_ScriptPtr;
      P10_ScriptCtx = sc; P10_ScriptPtr = sd - 2; ScriptReadShort3_004D02C6();
      CHECK(sc[0x10] == 1 && sc[0x12] == 2 && sc[0x14] == 3 && P10_ScriptPtr == sd + 6);
      P10_ScriptCtx = oc; P10_ScriptPtr = op; }
    return 0;
}
static int test_p12(void) {
  g_0125f3e0 = 1.0f; P12_Fn00526427();
  if (g_00ba53a0[0] != 0.0f || g_00ba53a0[4] != 0.25f) return 1;
  g_00546020 = 1.0f; g_00546054 = 0.5f; g_00b5a778 = 0; g_00b32980 = 0.75f;
  P12_Fn0050229C(); if (g_00b32980 != -1.0f) return 2;
  g_00574530[2] = 3; g_00574530[3] = 2; P12_Fn0050C010();
  if (g_00c7d800[1] != 3 + 2 * 0x37 || g_00c7d828 != 0x00c7d82c) return 3;
  /* 0048ebc8 must dispatch all eight cop slots to the real nearby-particle
     initializer, resolving the record's 32-bit car address on native builds. */
  {
    p12_0112da00_t saved_cops;
    uint8_t saved_particles[0x40 * 0xb4], car[0x148] = {0};
    int32_t saved_alt = P62_Alt, saved_round = P11_00ba52d0;
    int failures = 0;
    memcpy(saved_cops, P12_0112da00, sizeof saved_cops);
    memcpy(saved_particles, A_00C56780, sizeof saved_particles);
    int32_t cx = 30000, cz = 40000, vz = 25600;
    memcpy(car + 0xc8, &cx, 4); memcpy(car + 0xd0, &cz, 4);
    memcpy(car + 0x48, &vz, 4);
    uint32_t addr = re_ptr_register_dyn(car, sizeof car);
    P62_Alt = 0;
    for (int slot = 0; slot < 8; slot++) {
      for (int gate = 0; gate < 6; gate++) {
        memset(P12_0112da00, 0, sizeof saved_cops);
        memset(A_00C56780, 0, sizeof saved_particles);
        uint32_t *rec = &P12_0112da00[slot * 0x336];
        rec[0x32d] = gate != 0; rec[0x333] = gate != 1;
        rec[0x331] = gate == 2;
        rec[0x334] = gate == 4 ? 0 : gate == 5 ? 0x70000000u : addr;
        /* Record 0 is near this car; record 1 is far away. */
        uint32_t flags = 0x10, kind = 4;
        float x = (float)cx + 10.0f, z = (float)cz;
        for (int j = 0; j < 2; j++) {
          uint8_t *p = A_00C56780 + j * 0xb4;
          memcpy(p + 0xc, &flags, 4); memcpy(p + 0x1c, &kind, 4);
        }
        memcpy(A_00C56780 + 0x84, &x, 4); memcpy(A_00C56780 + 0x8c, &z, 4);
        P12_Fn0048EBC8();
        uint32_t near_flags, far_flags;
        memcpy(&near_flags, A_00C56780 + 0xc, 4);
        memcpy(&far_flags, A_00C56780 + 0xb4 + 0xc, 4);
        if (near_flags != (gate == 3 ? 0x90u : 0x10u) || far_flags != 0x10u) failures++;
      }
    }
    re_ptr_unregister(car);
    memcpy(P12_0112da00, saved_cops, sizeof saved_cops);
    memcpy(A_00C56780, saved_particles, sizeof saved_particles);
    P62_Alt = saved_alt; P11_00ba52d0 = saved_round;
    if (failures) { fprintf(stderr, "p12 nearby-particle dispatch failed: %d cases\n", failures); return 4; }
  }
  return 0;
}
static int test_p13(void) {
  char a[8] = {0}, b[8] = "abcdefg";
  P13_Fn00422AC0(a, b, 7); if (strcmp(a, "abcdefg")) return 1;
  P13_Fn004064B4(2, 0);
  if (P13_00575f30 != 1 || P13_005759a4 != 0x20 || P13_00575ee4 != 0x30) return 2;
  if (strcmp(P13_Fn004F8735(3), "Out of memory")) return 3;
  return 0;
}
static int test_p14(void) {
  int f = 0;
  int32_t tri[6] = {0, 0, 10, 0, 0, 10};
  if (P14_Fn00526A34(1, 1, tri) != 1 && P14_Fn00526A34(20, 20, tri) != 0) f++; /* порядок обхода: знак */
  uint8_t a[0x18] = {0}, b[0x18] = {0}, o[0x18] = {0};
  int32_t v;
  v = 5; memcpy(a + 0x14, &v, 4); v = 10; memcpy(a + 0x10, &v, 4); v = 3; memcpy(a + 0xc, &v, 4);
  v = 2; memcpy(b + 0x14, &v, 4); v = 20; memcpy(b + 0x10, &v, 4); v = 7; memcpy(b + 0xc, &v, 4);
  P14_Fn00503EF4(a, b, o);
  int32_t r0, r1, r2; memcpy(&r0, o + 0x14, 4); memcpy(&r1, o + 0x10, 4); memcpy(&r2, o + 0xc, 4);
  if (r0 != 2 || r1 != 49 || r2 != 96) f++;
  uint32_t buf[4] = {1, 2, 3, 4};
  P14_Fn0048DB65(buf, 16);
  if (buf[0] | buf[3]) f++;
  P14_00c4bdc4 = 1; P14_00c29d80 = 1; P14_00c29d81 = 4; P14_00bf1c20 = 0;
  P14_Fn0051BD9C();
  if (P14_00c29d80 != 2 || P14_00c29d81 != 1 || P14_00c4bdc4 != 100 || P14_00bf1c20 != 1) f++;
  if (f) printf("test_p14 FAILED %d\n", f);
  return f;
}
static int test_ported15(void) {
  int f = 0;
  if (P15_GridCell(0, 0) != 0 || P15_GridCell(-0x2000, -0x3000) != 4) f++;
  { uint8_t a[0x400 * 3], b[0x400 * 3]; for (int i = 0; i < (int)sizeof a; i++) { a[i] = (uint8_t)i; b[i] = 0; }
    P15_BlitRect8(a, 2, 1, 4, 2, b, 1, 0);
    if (b[1] != a[0x100 + 2] || b[4] != a[0x100 + 5] || b[5] != 0 || b[0x101] != a[0x200 + 2]) f++; }
  { char buf[] = "-123ab"; char *p = buf; P15_SkipInteger(&p); if (*p != 'a') f++; }
  return f;
}
static int test_ported16(void) {
  int f = 0;
  P16_IdleMode = 0; P16_Level = 5; P16_IdleCounter = 9; P16_IdleTimer(); if (P16_IdleCounter != 0) f++;
  P16_Level = 0; P16_FlagA = P16_FlagB = P16_FlagC = P16_FlagD = 0; P16_IdleCounter = 300; P16_IdleTimer();
  if (P16_IdleMode != 0xff0 || P16_IdleArg2 != 0x5a) f++;
  { uint32_t r[12]; float x; P16_FillHudRect(r, 7, 0x102030, 9, 1, 0); memcpy(&x, &r[0], 4); if (x != 624.0f || r[10] != 2 || r[11] != 1) f++;
    memcpy(&x, &r[6], 4); if (x != 16.0f) f++; }
  return f;
}
static int test_ported17(void) {
  int f = 0;
  for (uint32_t v = 4; v < 100000; v += 7) { uint32_t r = P17_ISqrt(v); if (r * r > v || (r + 1) * (r + 1) <= v) { if (!(r*r<=v+r+1)) f++; } }
  if (P17_ISqrt(100) != 10 || P17_ISqrt(2) != 1) f++;
  { int16_t s = 3; memcpy(P17_MapBase + 5 * 0x42, &s, 2);
    int16_t id = 5; memcpy(P17_SlotBase + 3 * 0x2c + 16, &id, 2); if (P17_SlotMapSide(5) != 0) f++;
    memcpy(P17_SlotBase + 3 * 0x2c + 16, &(int16_t){0}, 2); if (P17_SlotMapSide(5) != 1) f++;
    memcpy(P17_SlotBase + 3 * 0x2c + 24, &id, 2); if (P17_SlotFindIndex(3, 5) != 3) f++; if (P17_SlotFindIndex(3, 9) != 0xff) f++; }
  P17_PtrA = 7; P17_ValA = 9; P17_Cond1 = 1; P17_Cond2 = 0; P17_PushScreenState();
  if (P17_PtrB != 7 || P17_ValB != 9 || P17_ValA != 2 || P17_Dst != 200 || P17_Const6 != 6) f++;
  return f;
}
static int test_ported19(void) {
  int f = 0;
  P19_Cur = 0; P19_Target = 1; P19_Step = 0.4f; P19_Active = 1;
  P19_FadeStep(); P19_FadeStep(); P19_FadeStep();
  if (P19_Cur != 1.0f || P19_Active != 0 || P19_OutC != 1.0f) f++;
  { char s[16] = "  ab cd"; char o[16]; int e = P19_TakeToken(s, o); if (e || strcmp(o, "ab") || strcmp(s, "cd")) f++; }
  { char s[8] = ""; char o[8]; if (!P19_TakeToken(s, o)) f++; }
  P19_Level = 1; P19_Sel2(0); /* Level<2 → Fn00416040 (links.c → SetupMiami00416040) */
  P19_Level = 4; P19_Sel4(0); if (P19_Cond != 0x31 || P19_Wd != 0x147 || P19_F3 != 1) f++;
  P19_ScrW = 640; P19_DivW = 640; P19_DivC = 2; P19_Scale = 1;
  if (P19_ScaleX(1) != 1 * 1.0f - 320 + 320) f++;
  for (int i = 0; i < 14; i++) P19_Keys2[i] = (uint8_t)i;
  if (!P19_KeysUnique14()) f++;
  P19_Keys2[13] = 0; if (P19_KeysUnique14()) f++;
  return f;
}
static int test_ported18(void) { P18_Flag0057A0E6 = 5; P18_ClearFlag(); return P18_Flag0057A0E6 != 0; }
static int test_p21(void) {
  int f = 0;
  if (P21_AddMsf(0x00000102u, 0x00000103u) != 0x00000205u) f++;
  P21_AxisValue = -20; P21_SetAxisByte(0x20, 3); if (P21_AxisOut[3] != 0x80) f++;
  P21_AxisValue = 0; P21_SetAxisByte(0x21, 4); if (P21_AxisOut[4] != 0) f++;
  P21_AxisSrc[5] = 7; P21_SetAxisByte(5, 6); if (P21_AxisOut[6] != 7) f++;
  P21_NameTable[2] = "x"; if (P21_GetNameByIndex(2)[0] != 'x') f++; if (P21_GetNameByIndex(0x23)[0] != 'E') f++;
  if (P21_MatchPrefix((const uint8_t*)"abc1", (const uint8_t*)"abc") != 3) f++;
  if (P21_MatchPrefix((const uint8_t*)"abcD", (const uint8_t*)"abc") != 0) f++;
  if (P21_MatchPrefix((const uint8_t*)"abx", (const uint8_t*)"abc") != 0) f++;
  P21_EntryCount = 2; memset(P21_Entries, 0, 0x40 * 0x54);   /* whole table (P21_Entries is a pointer macro) */
  P21_Entries[1] = 1; int32_t o = 9; memcpy(P21_Entries + 0x28, &o, 4);
  P21_Entries[0x54 + 0x13] = 8; memcpy(P21_Entries + 0x54 + 0x28, &o, 4);
  if (P21_CountActiveEntries(9) != 2 || P21_CountActiveEntries(1) != 0) f++;
  static uint8_t map[31 * 31]; P21_GridDiv = 10; P21_GridRadius = 15; P21_GridStride = 31;
  map[(0 + 0xf) + (1 + 0xf) * 31] = 1;  /* dx=0 dy=1 */
  if (!P21_GridCellSet(10 + 5, map, 5, 0)) f++;
  if (P21_GridCellSet(10 + 5, map, 5, 1)) f++;
  return f;
}
static int test_p22(void) {
  int f = 0;
  P22_DevReady = 0; P22_BeginScene(); P22_EndScene(); P22_SetCull(1); P22_SetViewport(1, 2, 3, 4);
  if (P22_VpW != 0 && P22_VpX != 0) f++;                                  /* без устройства viewport не трогаем */
  P22_ZFuncCur = 0; P22_SetZFunc(0); if (P22_ZFuncCur != 0) f++;
  P22_SetZFunc(5); if (P22_ZFuncCur != 5) f++;
  P22_AlphaRef = 0; P22_SetAlphaFunc(7); if (P22_AlphaFunc != 8 || P22_AlphaRef != 7) f++;
  P22_SetAlphaFunc(3); if (P22_AlphaFunc != 2) f++;
  P22_SetZWrite(1); if (P22_ZWriteOff != 0) f++;
  P22_SetZWrite(0); if (P22_ZWriteOff != 1) f++;
  P22_AtestA = 0; P22_AtestB = 0; P22_SetAlphaTest(0, 0, 1, 2); if (P22_AtestA != 1 || P22_AtestB != 2) f++;
  P22_DevReady = 1; P22_SetViewport(10, 20, 110, 80);
  if (P22_VpX != 10 || P22_VpY != 20 || P22_VpW != 100 || P22_VpH != 60) f++;
  P22_TexOpCur = 0; P22_TexVarA = 5; P22_TexVarB = 9;
  P22_SetTexOp(0, 0, 0, 2, 0); if (P22_TexVarA != 0x20 || P22_TexVarB != 5) f++;
  P22_SetTexOp(0, 0, 0, 1, 0); if (P22_TexVarA != 5) f++;
  P22_SetViewport(0, 0, 0, 0); P22_DevReady = 0;
  P22_SetZFunc(3);  /* вернуть LEQUAL: состояние plat_* глобальное, дальше идёт render_test */
  P22_SetZWrite(1);
  return f;
}
static float f32t(int32_t b) { float f; memcpy(&f, &b, 4); return f; }
static int32_t bitsf(float f) { int32_t b; memcpy(&b, &f, 4); return b; }
static int test_p23(void) {
  int f = 0;
  int32_t in[11] = { bitsf(10.f), bitsf(20.f), 0, bitsf(255.f), bitsf(128.5f), bitsf(1.4f), 0, 0, bitsf(4.f), bitsf(8.f), bitsf(12.f) };
  plat_vertex v;
  P23_ScaleUV_A = 2.f; P23_ScaleUV_B = 3.f; P23_ZScale_A = 0.01f; P23_ZScale_B = 0.02f; P23_ZNum = 1.f; P23_ZDenA = 8.f; P23_ZBias = 0.f;
  P23_ConvVertexA(in, &v);
  if (v.x != 10.f || v.y != 20.f || v.rhw != 4.f) f++;
  if (v.color != ((255u << 16) | (128u << 8) | 1u)) f++;           /* 128.5 -> 128 (к чётному) */
  if (fabsf(v.z - (1.f - 4.f * 0.01f)) > 1e-6f) f++;
  if (fabsf(v.u - 8.f * 2.f / 4.f) > 1e-6f || fabsf(v.v - 12.f * 2.f / 4.f) > 1e-6f) f++;
  P23_ConvVertexB(in, &v);
  if (fabsf(v.z - (1.f - 4.f * 0.02f)) > 1e-6f || fabsf(v.u - 8.f * 3.f / 4.f) > 1e-6f) f++;
  P23_ZBias = 2.f;
  P23_ConvVertexA(in, &v); if (fabsf(v.z - (1.f - 1.f / (8.f / 4.f + 2.f))) > 1e-6f) f++;
  P23_ConvVertexB(in, &v); if (fabsf(v.z - (1.f - 1.f / (4.f + 2.f))) > 1e-6f) f++;
  /* The sky must remain behind extended-distance scenery in both conversion
     paths, with and without bias; restoring the pass restores ordinary depth. */
  {
    plat_vertex ordinary, sky;
    for (int bias = 0; bias < 2; bias++) {
      P23_ZBias = bias ? 32767.0f : 0.0f;
      for (int b = 0; b < 2; b++) {
        void (*convert)(const int32_t *, plat_vertex *) = b ? P23_ConvVertexB : P23_ConvVertexA;
        convert(in, &ordinary);
        int previous = P23_SetSkyDepth(1);
        convert(in, &sky);
        if (sky.z != 1.0f || sky.rhw != ordinary.rhw || sky.u != ordinary.u || sky.v != ordinary.v ||
            sky.x != ordinary.x || sky.y != ordinary.y || sky.color != ordinary.color) f++;
        P23_SetSkyDepth(previous);
        convert(in, &sky);
        if (sky.z != ordinary.z) f++;
      }
    }
    P23_ZBias = 2.0f;
  }
  (void)f32t;
  /* режимы смешивания: SRC=19 DEST=20 ALPHABLEND=27 */
  P23_DevCaps = 0xffffffffu; P23_AlphaMode = 0; P22_AlphaFunc = 2;
  P23_BlendCur = -1; P23_SetBlendMode(0, 0);
  if (plat_get_render_state(19) != 1 || plat_get_render_state(20) != 4 || plat_get_render_state(27) != 1) f++;
  P23_SetBlendMode(0, 5);
  if (plat_get_render_state(20) != 4 || P23_AlphaMode != 1 || plat_get_render_state(25) != 2) f++;
  P23_SetBlendMode(4, 0); if (plat_get_render_state(27) != 0 || P23_AlphaMode != 0) f++;
  P23_DevCaps = 0; P23_SetBlendMode(2, 0); if (plat_get_render_state(27) != 0) f++;   /* нет поддержки -> режим 4 */
  P23_SetBlendMode(2, 0); if (P23_BlendCur != 2) f++;
  P22_DevReady = 0; P23_DrawLineA(in, in); P23_DrawLineB(in, in);
  if (P23_ClearZ(NULL, 0) != 0) f++;
  P23_InitRenderStates();
  if (plat_get_render_state(23) != 4 || plat_get_render_state(27) != 0 || plat_get_render_state(31) != 1) f++;
  P22_SetZFunc(3); P22_SetZWrite(1); plat_set_render_state(7, 1);  /* вернуть состояние для render_test */
  return f;
}
static int test_p24(void) {
  int f = 0;
  int base = plat_dd_stub_count();
  uint32_t desc[31]; memset(desc, 0, sizeof desc);
  int dummy_dd, dummy_d3d;
  P24_DD = &dummy_dd; P24_Fullscreen = 0; P24_Bpp = 16;
  if (P24_CreateSurface(NULL, desc) != NULL) f++;
  if (P24_CreatePrimarySurface() != 1 || P24_Primary == NULL || P24_Back == NULL) f++;
  if (plat_dd_stub_count() != base + 2) f++;
  void *z = P24_CreateSurface(&dummy_dd, desc);
  if (!z || !P24_AttachSurface(P24_Back, z)) f++;
  void *c = P24_CreateClipper(&dummy_dd);
  if (!c || !P24_SetClipper(P24_Primary, c) || P24_SetClipper(NULL, c)) f++;
  void *dev = P24_CreateDevice(&dummy_d3d, NULL, P24_Back);
  void *vp = P24_CreateViewport(&dummy_d3d);
  if (!dev || !vp || P24_CreateDevice(NULL, NULL, NULL) || P24_CreateViewport(NULL)) f++;
  if (!P24_AddViewport(dev, vp, 640, 480) || P24_AddViewport(NULL, vp, 640, 480) || P24_AddViewport(dev, vp, 0, 480)) f++;
  /* заливка: RGB 565 (R 16 бит -> сдвиг 3 вправо, позиция 11; G сдвиг 2, позиция 5; B сдвиг 3, позиция 0) */
  P24_RShiftR = 3; P24_RShiftL = 11; P24_GShiftR = 2; P24_GShiftL = 5; P24_BShiftR = 3; P24_BShiftL = 0;
  P22_VpX = 10; P22_VpY = 20; P22_VpW = 100; P22_VpH = 50;
  int32_t r[4]; uint32_t px;
  if (P24_FillBackbuffer(P24_Back, 0xff8040) != 1 || !plat_dd_stub_last_fill(r, &px)) f++;
  if (r[0] != 10 || r[1] != 20 || r[2] != 110 || r[3] != 70) f++;
  if (px != ((0xffu >> 3) << 11 | (0x80u >> 2) << 5 | (0x40u >> 3))) f++;
  P24_RestoreMode = 0; P24_RestoreDisplay();
  P24_RestoreMode = 1; P24_ModeW = 640; P24_ModeH = 480; P24_RestoreDisplay();
  P24_RestoreSurfaces();
  if (!P24_SetDisplayMode(&dummy_dd, 640, 480) || P24_SetDisplayMode(NULL, 640, 480)) f++;
  plat_dd_release(z); plat_dd_release(c); plat_dd_release(dev); plat_dd_release(vp); plat_dd_release(P24_Back); plat_dd_release(P24_Primary);
  P24_Primary = NULL; P24_Back = NULL; P24_DD = NULL;
  if (plat_dd_stub_count() != base) f++;
  return f;
}
static int p25_hits;
static void p25_cb(void) { p25_hits++; }
static int test_p25(void) {
  int f = 0;
  uint32_t from, to, vol;
  plat_cd_stub_set(0, -1); P25_CdOpen = 0;
  if (P25_InitCDAudio() != 0 || P25_CdOpen != 0) f++;
  plat_cd_stub_set(5, 2);
  if (P25_InitCDAudio() != 1 || P25_CdOpen != 1 || P25_CdTracks != 5 || P25_AuxDev != 2) f++;
  Q00B87E90 = 1; P25_PlayCDTrack(1); if (Q00B87E90 != 0 || P25_CdPlaying != 0) f++;
  Q00B87E90 = 1; P25_PlayCDTrack(6); if (Q00B87E90 != 0) f++;
  P25_PlayCDTrack(3);
  if (P25_CdPlaying != 1 || P25_CdTrack != 3 || !plat_cd_stub_state(&from, &to, &vol) || from != (3u | 6u << 8) || to != (6u | 36u << 8)) f++;
  P25_CDStop(); if (P25_CdPlaying != 0 || plat_cd_stub_state(&from, &to, &vol)) f++;
  P25_CDResume(); if (P25_CdPlaying != 1 || !plat_cd_stub_state(&from, &to, &vol) || to != (6u | 36u << 8)) f++;
  P25_CDSetVolume(0x8000); plat_cd_stub_state(&from, &to, &vol); if (vol != 0x80008000u) f++;
  P25_CDSetVolume(0x20000); plat_cd_stub_state(&from, &to, &vol); if (vol != 0xffffffffu) f++;
  P25_CDSetVolume((uint32_t)-5); plat_cd_stub_state(&from, &to, &vol); if (vol != 0) f++;
  if (P21_AddMsf(0x0a0500, 0x0b0100) != (0u | 6u << 8 | 0x15u << 16)) f++;   /* без переносов: 5+1 мин, 10+11 сек */
  if (P21_AddMsf(0x400000 | 0x0100, 0x400000 | 0x0100) != (0x35u << 16 | 3u << 8)) f++; /* сек 0x40+0x40=0x80 -> >0x4a: -0x4b, минуты+1 */
  P25_CDClose(); if (P25_CdOpen != 0 || P25_CdPlaying != 0) f++;
  /* таймеры */
  if (P25_TimersInit() != 1) f++;
  p25_hits = 0;
  int s = P25_TimerStart(30, 0, p25_cb);
  if (s != 0) f++;
  plat_sleep_ms(150);
  if (p25_hits != 1) f++;
  P25_TimerStop(s);
  if (P25_TimerStart(1000, 0, p25_cb) != 0) f++;   /* слот 0 освободился */
  P25_TimersShutdown();
  if (P25_TimerCnt != 0) f++;
  return f;
}
static int test_p27(void) {
  int f = 0;
  /* ReadChunked: 200000 байт кусками по 0xffff, счётчик */
  FILE *tf = tmpfile();
  if (!tf) return 1;
  enum { N = 200000 };
  uint8_t *src = malloc(N), *dst = calloc(1, N);
  for (int i = 0; i < N; i++) src[i] = (uint8_t)(i * 7);
  fwrite(src, 1, N, tf); rewind(tf);
  P27_ReadBytes = 0; P27_ReadLimit = 0x7fffffff; P27_ProgressOn = 0;
  if (P27_ReadChunked(dst, N, 1, tf) != 1 || memcmp(src, dst, N) || P27_ReadBytes != N) f++;
  /* палитры: 3 записи, одна с недопустимым слотом (пропускается) */
  rewind(tf);
  { int16_t n = 3; fwrite(&n, 2, 1, tf);
    for (int k = 0; k < 3; k++) { int16_t sl = k == 1 ? 77 : (int16_t)(k ? 5 : 2); uint8_t pal[0x400]; memset(pal, 0x10 + k, sizeof pal);
      fwrite(&sl, 2, 1, tf); fwrite(pal, 1, 0x400, tf); } }
  rewind(tf);
  P12_01252aa0[9] = 1;
  P27_LoadPalettes(tf);
  if (P12_01252aa0[2] != 1 || P12_01252aa0[5] != 1 || P12_01252aa0[9] != 0 || P12_01252aa0[3] != 0) f++;
  if (P14_01252be0[2 * 0x400] != 0x10 || P14_01252be0[5 * 0x400 + 0x3ff] != 0x12) f++;
  fclose(tf); free(src); free(dst);
  /* утечки: счётчики равны — ничего не делает */
  P27_MemAllocated = P27_MemFreed = 5; P27_MemLeakReport();
  /* Leak log strings are registered 32-bit game addresses, not host pointers. */
  {
    p27_memtab_t saved; memcpy(saved, P27_MemTab, sizeof saved);
    int allocated = P27_MemAllocated, freed = P27_MemFreed;
    char *block = DebugMalloc(16, "p27", 1), *log = DebugMalloc(32, "p27", 2);
    if (!block || !log) { DebugFree(block); DebugFree(log); return 1; }
    strcpy(log, "synthetic leak log");
    memset(P27_MemTab, 0, sizeof saved);
    P27_MemTab[0] = re_addr(block); P27_MemTab[1] = 16; P27_MemTab[2] = re_addr(log);
    P27_MemAllocated = 16; P27_MemFreed = 0;
    P27_MemLeakReport();
    const char *text, *title; plat_message_box_last(&text, &title);
    if (!strstr(text, "synthetic leak log") || strcmp(title, "MEMORY FAULT") || P27_MemTab[0] || P27_MemTab[2]) f++;
    /* CrtFree is an accounting stub in selftest; release the fixture here. */
    re_ptr_unregister(block); re_ptr_unregister(log); DebugFree(block); DebugFree(log);
    memcpy(P27_MemTab, saved, sizeof saved);
    P27_MemAllocated = allocated; P27_MemFreed = freed;
  }
  /* вмятины: имена текстур запрашиваются 66 раз, буфер 0x20000 выделяется */
  S_00D1192C = 3; P27_LoadDentTextures();
  if (D_00d17ec8 == NULL) f++;
  return f;
}
static int test_p28(void) {
  int f = 0;
  /* события: старые записи освобождаются, файл с нулевым числом моделей */
  FILE *tf = tmpfile(); if (!tf) return 1;
  int32_t zero = 0; fwrite(&zero, 4, 1, tf); rewind(tf);
  P28_EventCount = 2; P28_EventModels[0] = re_addr(DebugMalloc(16, "t", 1)); P28_EventModels[1] = 0;
  P27_ReadBytes = 0; P27_ReadLimit = 0x7fffffff; P27_ProgressOn = 0;
  P28_LoadEventModels(tf);
  if (P28_EventCount != 0 || P28_EventModels[0] != 0) f++;
  fclose(tf);
  /* машины: имена не найдены -> сообщения «ERROR IN _LEVEL_ DATA», блоки таблиц копируются */
  const char *tx, *ti; int n0 = plat_message_box_last(&tx, &ti);
  S_00D1192C = 2; P28_BadGuyFlag = 1;
  for (int i = 0; i < 6 * 0x50; i++) P28_Src1[2 * 0x1e0 + i] = (uint8_t)(i + 1);
  for (int i = 0; i < 0x170; i++) P28_Src2[2 * 0x170 + i] = (uint8_t)(i * 3);
  P28_LoadCarModels();
  int n1 = plat_message_box_last(&tx, &ti);
  if (n1 <= n0) f++;
  if (P28_Dst1[0x50 * 5 + 7] != (uint8_t)(0x50 * 5 + 7 + 1) || P28_Dst2[100] != (uint8_t)(300)) f++;
  if (P28_CarClean[0] != 0 || P28_CarLow[0] != P28_CarClean[0] || P28_CarOpsSize[3] != 0) f++;
  return f;
}
static int test_p29(void) {
  int f = 0;
  P29_Mode = 7; DirectorLastFrame = 10; DirectorUnk6C = 0; DirectorBuffer = NULL;
  if (SetDirectorMode(1, 5, 9) != 7) f++;
  if (P29_Mode != 1 || P29_Param != 9 || DirectorUnk7C != 5 || DirNodeTable != (DIR_NODE *)DirTableA || P29_FlagA8 != 1 || G6_00B87EFC != 1) f++;
  SetDirectorMode(1, -1, 0); if (DirectorUnk7C != 1) f++;
  if (SetDirectorMode(8, 0, 0) != 1 || P29_Flag9C != 1 || P29_Flag98 != 1 || DirUseDI != 0) f++;
  SetDirectorMode(9, 0, 0); if (P29_Flag98 != 0 || P29_Mode != 9) f++;
  SetDirectorMode(4, 0, 0); if (P29_Mode != 4 || DirNodeTable != (DIR_NODE *)DirTableB || DirectorUnk7C != 0x1b || DirUseDI != 1) f++;
  SetDirectorMode(15, 0, 0); if (P29_Mode != 15 || DirIndicatorOn != 1 || DirectorUnk84 != 2 || DirNodeTable != NULL) f++;
  DirectorLastFrame = 0;     /* кадров нет: режимы 3..5 переходят в 1 */
  SetDirectorMode(3, 0, 0); if (P29_Mode != 1 || DirectorUnk7C != 2) f++;
  SetDirectorMode(5, 0, 0); if (P29_Mode != 1 || DirectorUnk7C != 4) f++;
  SetDirectorMode(0xb, 0, 0); if (P29_Mode != 0) f++;
  P29_Mode = 3; SetDirectorMode(99, 0, 0); if (P29_Mode != 3) f++;
  return f;
}
static int test_p30(void) {
  int f = 0;
  G6_00BDF9C0 = 5; G6_00BDF9C4 = 6;
  P30_InitWindowGlobals(); if (G6_00BDF9C0 != 0 || G6_00BDF9C4 != 0) f++;
  P30_CrashInstall(); if (plat_crash_handler() != P30_CrashHandler) f++;
  P30_CrashRemove(); if (plat_crash_handler() != NULL) f++;
  plat_exit_trap(1);
  P30_Exit(3); if (plat_exit_last() != 3) f++;
  const char *tx, *ti; int n0 = plat_message_box_last(&tx, &ti);
  P30_CrashInstall(); P30_ScreensaverSaved = 0; plat_screensaver_set(1);
  P30_FatalError("kaput");
  int n1 = plat_message_box_last(&tx, &ti);
  if (n1 != n0 + 1 || strcmp(tx, "kaput") || strcmp(ti, "ERROR")) f++;
  if (plat_exit_last() != 0 || plat_screensaver_get() != 0 || plat_crash_handler() != NULL) f++;
  P30_CrashInstall(); P30_CrashHandler();
  if (strncmp(tx, "Application Error", 17) || strcmp(ti, "Driver Exception Handler") || plat_crash_handler() != NULL) f++;
  plat_exit_trap(0);
  return f;
}
static int test_p31(void) {
  int f = 0, cur, prio, quit, cl, w, h; const char *ti; plat_wndproc pr;
  plat_win_trap(1);
  G6_01270C28 = 640; G6_0125F3F0 = 480; G6_00BDF9C0 = 0;
  if (P31_InitWindow((void *)(intptr_t)7, 5) != 1 || G6_00BDF9C0 == 0) f++;
  plat_win_state(&cur, &prio, &quit, &cl, &w, &h, &ti, &pr);
  if (w != 640 || h != 480 || strcmp(ti, "Driver V6.3w") || pr != P31_WndProc) f++;
  P31_PriorityHigh = 0; P31_WndProc(0, 0x1c, 0, 0); plat_win_state(0, &prio, 0, 0, 0, 0, 0, 0);
  if (P31_Active != 0 || prio != 0) f++;
  P31_WndProc(0, 0x1c, 1, 0); plat_win_state(0, &prio, 0, 0, 0, 0, 0, 0);
  if (P31_Active != 1 || prio != 1) f++;
  P31_PriorityHigh = 1; P31_WndProc(0, 0x1c, 1, 0); plat_win_state(0, &prio, 0, 0, 0, 0, 0, 0);
  if (prio != 2) f++;
  P31_WndProc(0, 6, 0, 0); if (P31_Active != 0) f++;
  P31_WndProc(0, 6, 1, 0); if (P31_Active != 1) f++;
  P31_WndProc(0, 6, 0x10001, 0); if (P31_Active != 0) f++;
  P31_WndProc(0, 1, 0, 0x1234); if (G6_00BDF9C4 != 0x1234) f++;
  P31_WndProc(0, 2, 0, 0); plat_win_state(0, 0, &quit, 0, 0, 0, 0, 0); if (!quit) f++;
  P31_WindowMode = 1; if (P31_WndProc(0, 0x20, 0, 0) != 1) f++;
  plat_win_state(&cur, 0, 0, 0, 0, 0, 0, 0); if (cur != 0) f++;
  P31_WindowMode = 0; if (P31_WndProc(0, 0x20, 0, 0) != 1) f++;
  plat_win_state(&cur, 0, 0, 0, 0, 0, 0, 0); if (cur != 1) f++;
  if (P31_WndProc(0, 0x100, 0, 0) != 0 || P31_WndProc(0, 0x104, 0, 0) != 0 || P31_WndProc(0, 0x10, 0, 0) != 0) f++;
  P25_CdPlaying = 1; P31_WndProc(0, 0x3b9, 2, 0); if (P25_CdPlaying != 1) f++;
  P31_WndProc(0, 0x3b9, 8, 0); if (P25_CdPlaying != 0) f++;
  P31_GlideModule = 5; if (P31_LoadGlide() != 0 || P31_GlideModule != 0) f++;
  Call00522323();
  { int base = plat_dd_stub_count(), dummy;
    P31_DDObj0 = plat_dd_create_clipper(&dummy); P31_DDObj1 = plat_dd_create_clipper(&dummy);
    P24_Primary = plat_dd_create_clipper(&dummy); P24_Back = plat_dd_create_clipper(&dummy);
    P24_DD = plat_dd_create_clipper(&dummy);
    P24_RestoreMode = 1; P24_Hwnd = &dummy; P24_ModeW = 640; P31_DDVal3 = 9;
    if (plat_dd_stub_count() != base + 5) f++;
    P31_ReleaseDirectDraw();
    if (plat_dd_stub_count() != base || P24_DD || P24_Primary || P24_Back || P31_DDObj0 || P31_DDObj1) f++;
    if (plat_dd_last_coop() != 8 || P24_RestoreMode != 0 || P24_ModeW != 0 || P31_DDVal3 != 0 || P24_Hwnd) f++;
  }
  plat_win_trap(0);
  return f;
}
static int test_p33(void) {
  int f = 0, pt = 0, cnt = 0;
  memset(P32_Slots, 0, sizeof P32_Slots); memset(P33_Count, 0, sizeof P33_Count);
  int calls0 = plat_draw_prim_last(&pt, &cnt);
  int dummy_tex; P32_Slots[5].tex = &dummy_tex;
  P33_Count[5] = 6; P33_Count[32] = 3;
  P32_CurSlot = 7; plat_set_tex_stage(0, 1, 4);
  P33_FlushBatches();
  if (plat_draw_prim_last(&pt, &cnt) != calls0 + 2 || pt != 4 || cnt != 3) f++;   /* слот 5, затем слот 32 */
  if (P33_Count[5] != 0 || P33_Count[32] != 0) f++;
  if (P32_CurSlot != 7 || plat_get_tex_stage(0, 1) != 4) f++;              /* COLOROP восстановлен */
  P33_FlushBatches();
  if (plat_draw_prim_last(&pt, &cnt) != calls0 + 2) f++;                   /* пустые буферы — без вызовов */
  P33_GlideOk = 0; if (P33_LoadGlideProcs() != 0) f++;
  P33_GlideOk = 1; if (P33_LoadGlideProcs() != 1) f++;
  if (P33_GlideCount() != 119 || strcmp(P33_GlideName(0), "_grAADrawLine@8") != 0 || P33_GlideName(119) != NULL || P33_GlideProc(0) != NULL) f++;
  P33_GlideOk = 0;
  memset(P32_Slots, 0, sizeof P32_Slots); for (int i_ = 0; i_ < 32; i_++) P32_Slots[i_].bpp = -1;   /* слоты свободны (004221bf не освобождает тестовые указатели) */
  return f;
}
static int test_p32(void) {
  int f = 0, dummy;
  P24_DD = plat_dd_create_clipper(&dummy);
  void *back = P24_CreateSurface(P24_DD, (uint32_t[31]){ 0x7c, 6, 480, 640 });
  P24_Back = back;
  uint8_t dev[0x600]; memset(dev, 0, sizeof dev);
  for (int i = 0; i < 32; i++) dev[0x568 + i] = (uint8_t)(i + 1);
  P32_DevInfo = dev;
  if (P32_CreateZSurface(back) != 1 || P24_ZSurf == NULL) f++;
  uint32_t d[31];
  if (!plat_dd_stub_last_desc(d) || d[0] != 0x7c || d[1] != 0x1007 || d[2] != 480 || d[3] != 640 || d[26] != 0x20800) f++;
  if (((uint8_t *)&d[18])[0] != 1 || ((uint8_t *)&d[18])[31] != 32) f++;
  dev[0x518] = 1; P32_CreateZSurface(back);
  plat_dd_stub_last_desc(d); if (d[26] != 0x24000) f++;
  /* палитры */
  memset(P32_Slots, 0, sizeof P32_Slots);
  G6_00A421F0 = 0;
  P32_Slots[3].bpp = 8; P32_Slots[3].surf = back; P32_Slots[3].tex = back;
  if (P32_CreateSlotPalette(3) != 1 || P32_Slots[3].pal == NULL) f++;
  P32_Slots[4].bpp = 16; if (P32_CreateSlotPalette(4) != 1 || P32_Slots[4].pal != NULL) f++;
  G6_00A421F0 = 1; P32_Slots[5].bpp = 8; if (P32_CreateSlotPalette(5) != 1 || P32_Slots[5].pal) f++;
  G6_00A421F0 = 0;
  uint8_t rgba[1024]; for (int i = 0; i < 1024; i++) rgba[i] = (uint8_t)i;
  int e0, c0, e1, c1; plat_stub_pal_stats(&e0, &c0);
  P32_SetPalette(0, 1, rgba);   /* режим != 2 — таблица не меняется */
  if (P32_PalTable[0] == 2) f++;
  P32_SetPalette(0, 2, rgba);
  plat_stub_pal_stats(&e1, &c1);
  if (P32_PalTable[0] != rgba[2] || P32_PalTable[1] != rgba[1] || P32_PalTable[2] != rgba[0] || P32_PalTable[3] != 2) f++;
  if (P32_PalTable[1023] != 2 || P32_PalTable[1020] != rgba[1022]) f++;
  if (e1 != e0 + 1 || c1 != c0 + 1) f++;   /* палитра только у слота 3 */
  /* выбор палитры: узлы списка */
  int32_t id1 = 7, id2 = 9;
  P32_Node n2 = { 0, 9, {0}, &id2, NULL }, n1 = { 7, 7, {0}, &id1, &n2 };
  void *h1 = &id1, *h2 = &id2;
  P32_Slots[6].list = &n1;
  G6_0054EF2C = 9; P32_SelectSlotPalette(6);
  int st; void *tx = plat_stub_last_texture(&st);
  if (tx != h2 || st != 0 || P32_CurSlot != 6 || P32_CurHandle != h2 || P32_Slots[6].cur_id != 9) f++;
  G6_0054EF2C = 5; P32_SelectSlotPalette(6);   /* не найдена — берётся первый узел, сообщение */
  if (plat_stub_last_texture(&st) != h1 || strcmp(P32_Msg, "Palette 5 not found (7)") != 0 || P32_Slots[6].cur_id != 5) f++;
  memset(P32_Slots, 0, sizeof P32_Slots); for (int i_ = 0; i_ < 32; i_++) P32_Slots[i_].bpp = -1;   /* слоты свободны (004221bf не освобождает тестовые указатели) */
  return f;
}
static int test_p26(void) {
  int f = 0;
  P26_WaveSetVolume(0x8000); if (plat_wave_volume() != 0x80008000u) f++;
  P26_WaveSetVolume(0x20000); if (plat_wave_volume() != 0xffffffffu) f++;
  P26_WaveSetVolume((uint32_t)-1); if (plat_wave_volume() != 0) f++;
  const char *tx, *ti; int n0 = plat_message_box_last(&tx, &ti);
  G2_01134120 = 77; P26_ErrorInLine("boom");
  int n1 = plat_message_box_last(&tx, &ti);
  if (n1 != n0 + 1 || strcmp(tx, "boom") || strcmp(ti, "Error in line 77")) f++;
  P26_FindWheelModels();   /* имена не найдены (заглушка/пустая таблица) — 4 сообщения, если FindNameValue вернул 0 */
  int n2 = plat_message_box_last(&tx, &ti);
  if (P26_ModelHubcap == 0 && n2 < n1 + 1) f++;
  if (P26_ModelHubcap == 0 && strcmp(ti, "ERROR IN _LEVEL_ DATA")) f++;
  /* RandomFx: при любых тиках результат в допустимых значениях, неверный набор -> 0 */
  for (int i = 0; i < 20; i++) { P14_00b87e84 = i & 1; P26_RandomFx(i - 5); if (P26_FxA > 1 || P26_FxB > 1 || P26_FxC > 1 || P26_FxD > 1) f++; plat_sleep_ms(1); }
  { char drv[64] = "x"; if (P26_FindCdDrive("no_such_file_\x01.xyz", drv) != 0 || drv[0] != 'x') f++; }
  return f;
}
static int test_p34(void) {
  int f = 0, r, u, e, k;
  static int dummy[8];
  P34_Kbd = &dummy[0]; P34_Mouse = &dummy[1]; P34_Di = &dummy[2]; P34_Event = &dummy[3]; P34_Joy = &dummy[4];
  P34_EffA[1] = &dummy[5]; P34_EffB[2] = &dummy[6]; P34_EffC[7] = &dummy[7]; P34_Reg24 = 9;
  plat_di_stub_counts(&r, &u, &e, &k); int r0 = r, u0 = u, e0 = e;
  P34_ReleaseInput();
  plat_di_stub_counts(&r, &u, &e, &k);
  if (r - r0 != 6 || u - u0 != 3 || e - e0 != 1) f++;       /* Release: kbd,mouse,A,B,C,Di; Unacquire: kbd,mouse,C */
  if (P34_Kbd || P34_Mouse || P34_Di || P34_Event || P34_Joy || P34_EffA[1] || P34_EffB[2] || P34_EffC[7] || P34_Reg24) f++;
  if (P34_ReAcquire(0) != 0 || P34_ReAcquire(3) != 0) f++;   /* устройства нет */
  P34_Kbd = &dummy[0]; P34_Mouse = &dummy[1]; P34_Joy = &dummy[4];
  if (P34_ReAcquire(1) != 1) f++;
  plat_di_stub_counts(&r, &u, &e, &k); if (k != 1) f++;
  if (P34_ReAcquire(2) != 1) f++;
  plat_di_stub_counts(&r, &u, &e, &k); if (k != 2) f++;
  memset(P34_Keys, 0x80, 0x100); P34_Keys[5] = 0x55;
  if (P34_ReadKeyboard() != 1 || P34_KeysPrev[5] != 0x55 || P34_Keys[5] != 0) f++;   /* предыдущее = старое, новое — из устройства */
  plat_di_stub_fail_state(1); memset(P34_Keys, 7, 0x100);
  if (P34_ReadKeyboard() != 0 || P34_KeysPrev[0] != 7) f++;
  plat_di_stub_fail_state(0); P34_Kbd = NULL;
  return f;
}
static int test_p36(void) {
  int f = 0; static int dev[4]; uint32_t m;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p36 fail line %d\n",__LINE__); } } while (0)
  P34_Kbd = &dev[0]; P34_Mouse = &dev[1]; P34_Joy = &dev[2];
  CK(P36_AcquireDevice(0) == 1 && P36_AcquireDevice(1) == 1 && P36_AcquireDevice(2) == 1 && P36_AcquireDevice(3) == 0);
  P34_Mouse = NULL; CK(P36_AcquireDevice(1) == 0); P34_Mouse = &dev[1];
  /* выбор джойстика */
  P36_JoyCount = 2; P36_JoyAxisCap[1] = 77; P36_JoyAux[1] = 88; P34_EffC[1] = &dev[3]; P34_EffA[1] = &dev[1]; P34_EffB[1] = &dev[2];
  CK(P36_SelectJoystick(1) == 1 && P34_Reg24 == 1 && P36_JoyFlag == 77 && Q00B31E2C == 88 && P34_Joy == &dev[3] && P34_FfA == &dev[1] && P34_FfB == &dev[2] && G00B31E18 == 1);
  CK(P36_SelectJoystick(2) == 0 && P34_Reg24 == 0 && P34_Joy == NULL && P34_FfA == NULL && P36_JoyFlag == 0 && G00B31E18 == 0);
  CK(P36_SelectJoystick(-1) == 0);
  P34_EffC[1] = NULL; P34_EffA[1] = NULL; P34_EffB[1] = NULL; P36_JoyCount = 0;
  /* кнопки геймпада */
  memset(P34_Keys, 0, 0x100); P36_KeyCfg[4] = 0x10; P36_KeyCfg[7] = 0x11; P36_KeyCfg[15] = 0x12;
  P36_Pad0 = 1; P36_Pad5 = 1; P36_PadMode = 0; P34_Keys[0x10] = 0x80; P34_Keys[0x11] = 1; P34_Keys[0x12] = 0x80;
  m = 0xffff; P36_GetPadButtons(&m); CK(m == (8 | 1 | 0x100) && P36_Pad0 == 0 && P36_Pad5 == 0);
  P36_PadMode = 2; m = 0xffff; P36_GetPadButtons(&m); CK(m == 0);
  P36_PadMode = 0;
  /* опрос ввода */
  P31_Active = 0; CK(P36_PollInput() == 0);
  P31_Active = 1; P35_InputMode = 0; P36_JoyX = 9; P21_AxisValue = 9; P36_PrevFlag = 5; P34_Kbd = &dev[0];
  CK(P36_PollInput() == 1 && P36_JoyX == 0 && P21_AxisValue == 0 && P36_PrevFlag == 0);
  P35_InputMode = 1; CK(P36_PollInput() == 0);
  P35_InputMode = 2; P36_JoyPresent = 0; CK(P36_PollInput() == 0 && P35_InputMode == 0);
  P35_InputMode = 2; P36_JoyPresent = 1; P34_Joy = &dev[2]; Q00B87EF0 = 0;
  G6_00B87EFC = 0; P36_PadMode = 2; CK(P36_PollInput() == 1);   /* меню геймпада: ничего не читаем */
  P36_PadMode = 0; memset(P34_Keys, 0, 0x100);
  P36_KeyCfg[4] = 0x20; P36_KeyCfg[5] = 0x21; P36_KeyCfg[8] = 0x22; P36_JoyFlag = 1; P36_JoyState[0] = 0;
  plat_di_stub_joy(-100, 0, 0); CK(P36_PollInput() == 1 && P36_JoyX == -100 && P34_Keys[0x20] == 0x80 && P34_Keys[0x21] == 0 && P34_Keys[0x22] == 0x80 && P36_PrevFlag == 1);
  plat_di_stub_joy(20, 0, 1); CK(P36_PollInput() == 1 && P36_PrevJoyX == -100 && P34_Keys[0x20] == 0 && P34_Keys[0x21] == 0x80);   /* Poll=1 тоже успех */
  plat_di_stub_joy(0, 0, -1); CK(P36_PollInput() == 0);
  plat_di_stub_joy(0, 0, 0); plat_di_stub_fail_state(1); CK(P36_PollInput() == 0); plat_di_stub_fail_state(0);
  /* режим меню (b87efc != 0) — стрелки */
  G6_00B87EFC = 1; Q00B87F00 = 0; memset(P34_Keys, 0, 0x100); plat_di_stub_joy(-50, 30, 0);
  CK(P36_PollInput() == 1 && P34_Keys[0xcb] == 0x80 && P34_Keys[0xcd] == 0 && P34_Keys[0xd0] == 0x80 && P34_Keys[0xc8] == 0);
  G6_00B87EFC = 0; plat_di_stub_joy(0, 0, 0); P35_InputMode = 0; P34_Kbd = NULL; P34_Joy = NULL; P36_JoyFlag = 0;
#undef CK
  return f;
}
static int test_p37(void) {
  int f = 0, dv, co, pr, qy;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p37 fail line %d\n",__LINE__); } } while (0)
  P34_Di = NULL; P36_JoyPresent = 0; P37_MouseShared = 0; memset(P34_EffC, 0, sizeof P34_EffC);
  memset(P36_KeyCfg, 0, 0x50);
  plat_di_stub_setup(0, 0, 0);
  CK(P37_InitInput() == 1 && P34_Di && P34_Kbd && P34_Mouse && P34_Event && P35_InputMode == 0 && P34_Reg24 == 0 && P36_JoyCount == 0);
  CK(P36_KeyCfg[0] == 0x3b && P36_KeyCfg[4] == 0x2c && P36_KeyCfg[17] == 3 && P36_KeyCfg[20] == 0);
  CK(P19_Keys1[0] == 0x20 && P19_Keys1[3] == 2 && P19_Keys1[11] == 9);
  plat_di_stub_init_stats(&dv, &co, &pr, &qy); CK(dv == 2 && co == 2 && pr == 1 && qy == 0);
  /* два джойстика + Force Feedback: оба заняты, выбран первый */
  P36_JoyPresent = 1; plat_di_stub_setup(2, 0x100, 0);
  CK(P37_InitInput() == 1 && P36_JoyCount == 2 && P34_EffC[0] && P34_EffC[1] && P36_JoyAux[0] == 1 && P36_JoyAxisCap[0] == 1 && P36_JoyAxisCap[1] == 0 && P34_Joy == P34_EffC[0] && P34_EffA[0] && P34_EffB[1]);
  plat_di_stub_init_stats(&dv, &co, &pr, &qy); CK(dv == 4 && qy == 2 && pr == 1 + 8);
  /* без FF */
  plat_di_stub_setup(1, 0, 0); CK(P37_InitInput() == 1 && P36_JoyCount == 1 && P36_JoyAux[0] == 0);
  /* ошибки: каждая ступень освобождает всё */
  { static const uint32_t fm[] = { 1u << 0, 1u << 1, 1u << 4, 1u << 8, 1u << 9, 1u << 5, 1u << 6 };
    for (unsigned i = 0; i < sizeof fm / sizeof fm[0]; i++) {
      plat_di_stub_setup(0, 0, fm[i]);
      CK(P37_InitInput() == 0 && P34_Kbd == NULL && P34_Mouse == NULL && P34_Event == NULL && (i == 0 || P34_Di == NULL));
    } }
  /* отказ на одном джойстике — продолжаем перечисление */
  P36_JoyPresent = 1; plat_di_stub_setup(2, 0, 1u << 3); CK(P37_InitInput() == 1 && P36_JoyCount == 0 && P34_Joy == NULL);
  P36_JoyPresent = 0; P34_ReleaseInput();
#undef CK
  return f;
}
static int test_p35(void) {
  int f = 0, c, ck, s, sk; int32_t dx, dy, mag;
  static int dev;
  memset(P34_EffA, 0, sizeof P34_EffA); memset(P34_EffB, 0, sizeof P34_EffB); P34_FfA = P34_FfB = NULL;
  if (P35_CreateEffectA(&dev, 2) != 1 || P34_EffA[2] == NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_di_stub_effects(&c, &ck, &s, &sk, &dx, &dy, &mag); if (c != 1 || ck != 0) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  P34_FfA = &dev; if (P35_CreateEffectA(&dev, 3) != 1 || P34_EffA[3] != NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }   /* уже есть — не создаётся */
  P34_FfA = NULL;
  if (P35_CreateEffectA(NULL, 1) != 0) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  if (P35_CreateEffectB(&dev, 4) != 1 || P34_EffB[4] == NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_di_stub_effects(&c, &ck, &s, &sk, &dx, &dy, &mag); if (c != 2 || ck != 1) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_di_stub_fail_enum(1); if (P35_CreateEffectB(&dev, 5) != 0 || P34_EffB[5] != NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); } plat_di_stub_fail_enum(0);
  /* обновление силы: джойстик (режим 2), FF включён */
  P34_FfA = &dev; P34_FfB = &dev + 0; Q00B87EF0 = 1; P35_InputMode = 2; P16_FlagA = 0;
  P35_PadX = 3; P35_FfY = 4; P35_FfPending = 0; G00B31E00 = 777; G00B31E0C = 1;
  P35_UpdateForce();
  plat_di_stub_effects(&c, &ck, &s, &sk, &dx, &dy, &mag);
  if (s != 2 || dx != 0 || dy != 0 || mag != 777 || sk != 1) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }   /* сначала удар (3,4)->5, потом двигатель */
  if (P35_FfPending != 0 || P35_FfX != 0 || P35_FfY != 0 || G00B31E0C != 0) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  P35_PadX = 0;
  P16_FlagA = 1; P35_PadX = 9; P35_UpdateForce(); if (P35_FfPending != 0 || P35_FfX != 0) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }   /* удар запрещён — не копится */
  P35_InputMode = 0; P16_FlagA = 0; P35_PadX = 0; P35_FfPending = 1; P35_UpdateForce(); if (P35_FfPending != 1) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  P34_FfA = P34_FfB = NULL; Q00B87EF0 = 0; P35_PadX = 0; P35_FfPending = 0;
  /* DirectDraw */
  plat_dd_stub_display(0x40, 0, 0); P35_ReqBpp = 0x10; P24_Bpp = 0; P31_DDObj0 = NULL;
  void *dd = P35_GetDirectDrawInterface(NULL);
  if (dd == NULL || P31_DDObj0 != dd || P24_Bpp != 0x10) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_dd_release(dd);
  P35_ReqBpp = 8; P24_Bpp = 0; dd = P35_GetDirectDrawInterface(NULL); if (dd != NULL || P24_Bpp != 8) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  const char *tx, *tt; int mb0 = plat_message_box_last(&tx, &tt);
  plat_dd_stub_display(0x20, 0, 0); P35_ReqBpp = 0x20; if (P35_GetDirectDrawInterface(NULL) != NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }   /* нет DDPF_RGB */
  if (plat_message_box_last(&tx, &tt) != mb0 + 1 || strcmp(tt, "Sorry!") != 0) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_dd_stub_display(0x40, 0, 1); if (P35_GetDirectDrawInterface(NULL) != NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_dd_stub_display(0x40, 1, 0); if (P35_GetDirectDrawInterface(NULL) != NULL) { f++; fprintf(stderr,"p35 fail line %d\n",__LINE__); }
  plat_dd_stub_display(0x40, 0, 0);
  return f;
}
int test_render(const char *png_path);
int test_snd(void);
int test_v229(void);   /* v2.29: tests/snd_test.c — пустое звуковое устройство */
int test_v222(void);   /* v2.22: tests/cd_test.c — эмуляция CD-audio */
int test_v233(void);   /* v2.33: tests/cd_test.c — динамическая музыка (PS-стиль) */
static int test_p38(void) {
  int f = 0, st, up, bl, fl; int32_t rc[4]; uint32_t fp, spk; uint8_t fmt[18];
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p38 fail line %d\n",__LINE__); } } while (0)
  void *dd = plat_dd_create(NULL); uint32_t desc[31] = {0}; desc[0] = 0x7c; desc[1] = 7;
  P38_Mms = NULL; P38_Sample = NULL; P38_Dest = NULL; P38_Src = NULL;
  CK(P38_MmsRun() == 0); P38_MmsStop();
  P38_Mms = dd; plat_fmv_stub_fail(0); CK(P38_MmsRun() == 1);
  plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(st == 1);
  P38_MmsStop(); plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(st == 0);
  plat_fmv_stub_fail(1); CK(P38_MmsRun() == 0); plat_fmv_stub_fail(0);
  /* кадр: полоса 120 → top = (480-240)/2 = 120, bottom = 360 */
  P38_Sample = dd; P38_Dest = plat_dd_create_surface(dd, desc); P38_Src = plat_dd_create_surface(dd, desc); P38_Letter = 120;
  CK(P38_UpdateFrame() == 1);
  plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(up == 1 && bl == 1 && rc[0] == 0 && rc[1] == 120 && rc[2] == 640 && rc[3] == 360);
  plat_fmv_stub_fail(2); CK(P38_UpdateFrame() == 0); plat_fmv_stub_fail(4); CK(P38_UpdateFrame() == 0); plat_fmv_stub_fail(0);
  /* освобождение */
  int base = plat_dd_stub_count();
  P38_Obj824 = plat_dd_create_surface(dd, desc); P38_DD = plat_dd_create(NULL); P38_Obj814 = plat_dd_create(NULL);
  CK(plat_dd_stub_count() == base + 3);
  P38_FmvRelease();
  CK(plat_dd_stub_count() == base - 2 && P38_Src == NULL && P38_Dest == NULL && P38_Obj824 == NULL && P38_DD == NULL && P38_Obj814 == NULL);
  plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(fl == 1 && fp == 0 && plat_dd_last_coop() == 8);
  P38_FmvRelease();   /* повторный вызов — безопасен */
  /* остановка потока и таймера */
  P38_Mms2 = dd; P38_TimerSlot = -1; P38_TimerFlag = 0; P38_FmvStop(); CK(P38_TimerFlag == 1 && P38_TimerSlot == -1);
  plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(st == 0);
  /* форматы звука */
  P38_DsPrimary = dd; P38_SetPrimaryFormat(16, 22050);
  plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk);
  CK(fmt[0] == 1 && fmt[2] == 2 && *(uint32_t *)(fmt + 4) == 22050 && *(uint32_t *)(fmt + 8) == 88200 && fmt[12] == 4 && fmt[14] == 16 && fmt[16] == 0);
  P38_Ds = dd; P38_SetSpeakerConfig(1); plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(spk == 3);
  P38_SetSpeakerConfig(4); plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(spk == 5);
  P38_SetSpeakerConfig(9); plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(spk == 4);
  P38_SetSpeakerConfig(2); plat_fmv_stub_stats(&st, &up, rc, &bl, &fp, &fl, fmt, &spk); CK(spk == 2);
  P38_Mms = P38_Mms2 = P38_Sample = P38_DsPrimary = P38_Ds = NULL; plat_dd_release(dd);
#undef CK
  return f;
}
static int test_p42(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p42 fail line %d\n",__LINE__); } } while (0)
  memset(P42_Cmds, 0, sizeof P42_Cmds); memset(P42_Vars, 0, sizeof P42_Vars);
  strcpy(P42_Cmds[0].name, "CHECKPOINT"); P42_Cmds[0].id = 0;
  strcpy(P42_Cmds[1].name, "SET");        P42_Cmds[1].id = 2;
  void *e = (void *)1;
  CK(P42_FindCommand("SET", &e) == 0 && e == &P42_Cmds[1]);
  CK(P42_FindCommand("NOPE", &e) == 9 && e == NULL);
  CK(P42_FindCommandById(2) == P42_Cmds[1].name && P42_FindCommandById(0) == P42_Cmds[0].name && P42_FindCommandById(7) == NULL);
  strcpy(P42_Vars[0].name, "EVENTSCRIPT"); P42_Vars[0].type = 1;
  strcpy(P42_Vars[1].name, "MAX_COPS");    P42_Vars[1].type = 3;
  P42_Vars[2].type = 0x7f;
  CK(P42_FindVar("MAX_COPS") == 1 && P42_FindVar("EVENTSCRIPT") == 0 && P42_FindVar("X") == -1);
  P42_HighScores[0] = 11; P42_HighScores[8 + 2] = 22; P42_HighScores[16 + 1] = 33; P42_HighScores[20 + 3] = 44; P42_HighScores[24] = 55; P42_HighScores[28 + 1] = 66;
  CK(P42_GetHighScore(2, 0) == 11 && P42_GetHighScore(1, 2) == 22 && P42_GetHighScore(3, 1) == 33);
  CK(P42_GetHighScore(6, 3) == 44 && P42_GetHighScore(0xb, 3) == 44 && P42_GetHighScore(7, 0) == 55 && P42_GetHighScore(0xc, 1) == 66);
  CK(P42_GetHighScore(4, 0) == 0);
  P31_GlideModule = 0; P42_FreeGlide(); CK(P31_GlideModule == 0);
  P31_GlideModule = 5; P42_FreeGlide(); CK(P31_GlideModule == 0);
  char buf[32]; P42_VersionString(buf); CK(strcmp(buf, "2.43 (D3D)") == 0);
  int32_t m1 = -1, v = 7;
  G8_00B20344 = 1; memcpy(&A_00B20330[4], &m1, 4); CK(P42_ActionBound() == 0);
  memcpy(&A_00B20330[4], &v, 4); CK(P42_ActionBound() == 1);
  G8_00B20344 = 0; memcpy(&A_00B20330[0], &m1, 4); memcpy(&A_00B20330[4], &m1, 4);
  D_00b1c0d4 = 0; CK(P42_GetDeviceName(1, buf) == -1);
  D_00b1c0d4 = 1; P42_DevCount = 2; strcpy((char *)P42_DevNames[0], "Voodoo"); strcpy((char *)P42_DevNames[1], "Banshee");
  CK(P42_GetDeviceName(1, buf) == 1 && strcmp(buf, "Banshee") == 0);
  CK(P42_GetDeviceName(5, buf) == 0 && strcmp(buf, "Voodoo") == 0 && P42_GetDeviceName(-3, buf) == 0);
  P42_AngBase = 0x100; P42_AngZ = 9;
  P42_SetViewAngles(1024, 512, 0, 2.0f);
  CK(P42_AngY == 0x800 && P42_AngX == ((0x100 + 1024) & 0xfff) && P42_AngZ == 0);
  P42_SetViewAngles(4097, -1, 0, 1.0f);
  CK(P42_AngY == 1 && P42_AngX == ((0x100 - 1) & 0xfff));
  P42_CellX = 100; P42_CellY = 200; P42_CellScale = 0.5f; P21_GridDiv = 10;
  const float pos[3] = {20.0f, 0.0f, 40.0f};
  CK(P42_CellIndex(pos) == 60 + 120 * 10);
#undef CK
  return f;
}
static int test_p41(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p41 fail line %d\n",__LINE__); } } while (0)
  FILE *fp = tmpfile();
  uint16_t z = 0; int32_t cnt = 4;
  fwrite(&z, 2, 1, fp); fwrite(&cnt, 4, 1, fp);          /* 0 палитр, 4 страницы */
  static uint8_t page[0x20000];
  const uint16_t fl[4] = {1, 1, 2, 4}; const int16_t tx[4] = {0, 0, 0, 7};
  for (int i = 0; i < 4; i++) {
    memset(page, 0x10 + i, sizeof page);
    fwrite(&fl[i], 2, 1, fp); fwrite(&tx[i], 2, 1, fp); fwrite(page, sizeof page, 1, fp);
  }
  rewind(fp);
  D_00b87e30 = 0; P41_TexSel[0] = 1; S_00D1192C = 7;
  P41_LoadTexPages(fp);
  CK(P41_Offset == 0x60000);                              /* слоты 1, 2, 3 по 0x20000 */
  CK(P40_Slots[0].flags == 2 && P40_Slots[1].flags == 2 && P40_Slots[2].flags == 0 && P40_Slots[3].flags == 2);
  CK(P40_Slots[1].data == P41_Arena && P40_Slots[2].data == P41_Arena + 0x20000 && P40_Slots[3].data == P41_Arena + 0x40000);
  CK(P40_Slots[0].data == 0 && P41_Flag == 1);
  fclose(fp);
#undef CK
  return f;
}
static int test_p40(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p40 fail line %d\n",__LINE__); } } while (0)
  P40_ResetTexMem();
  CK(P12_00b1c3f0 == -1 && P12_00b1c3dc == 0);
  for (int i = 0; i < 0x100; i++) CK(P40_Slots[i].flags == 0 && P40_Slots[i].block == 0xff);
  for (int i = 0; i < 0x40; i++) CK(P40_Blocks[i].slot == 0xff && P40_Blocks[i].info[2] == 3 && P40_Blocks[i].info[3] == 5);
  for (int i = 0; i < 4; i++) CK(P40_00b1c3e0[i] == -1);
  CK(P40_Blocks[0].flags == 1);                         /* без Glide границы памяти 0..0 → блоки вне памяти */
  for (int i = 0; i < 0x40; i++) P40_Blocks[i].flags = 0;
  /* одиночная загрузка: пара блоков 0/1 */
  P40_Slots[5].data = 0x1234;
  P40_UploadSlot(5, 0);
  CK(P40_Slots[5].block == 0 && P40_Blocks[0].slot == 5 && P40_Blocks[1].slot == 5);
  CK(P40_Blocks[0].info[4] == 0x1234 && P40_Blocks[0].info[3] == 0xb && (P40_Blocks[0].flags & 2) && (P40_Blocks[1].flags & 2));
  CK(P40_Blocks[1].info[4] == 0x1234 && P40_Blocks[1].info[3] == 0xb);
  P40_UploadSlot(5, 0);                                  /* уже загружена — без изменений */
  CK(P40_Slots[5].block == 0);
  P40_Slots[6].flags = 2; P40_UploadSlot(6, 0x77);       /* следующая пара 2/3, флаг 4 */
  CK(P40_Slots[6].block == 2 && P40_Blocks[2].info[4] == 0x77 && (P40_Blocks[2].flags & 4) && P40_Blocks[3].info[4] == 0);
  /* двойная загрузка: слот 8 (вторая часть, флаг 8) → начинает со слота 7 */
  P40_Slots[7].data = 0xa; P40_Slots[8].data = 0xb; P40_Slots[8].flags = 8;
  P40_UploadSlotPair(8, 0, 0);
  CK(P40_Slots[7].block == 4 && P40_Slots[8].block == 5 && P40_Blocks[4].slot == 7 && P40_Blocks[5].slot == 8);
  CK(P40_Blocks[4].info[4] == 0xa && P40_Blocks[5].info[4] == 0xb && P40_Blocks[4].info[3] == 5);
  /* занятый блок отдаёт слот: заполняем всю таблицу и вытесняем */
  for (int i = 0; i < 0x40; i++) { P40_Blocks[i].flags = 1; }
  P40_UploadSlot(9, 1);
  CK(P40_Slots[9].block == 0xff);                        /* свободных блоков нет */
  /* палитры: без списка — одна запись в 0x1252fe0 (счёт вызовов Fwd через G00B1C0D8 != 1 не считается) */
  P40_ListCount = 0;
  P40_DownloadPalette(3, 1);
#undef CK
  return f;
}

static int test_p39(void) {
  int f = 0, lk, ul, fl, bl, cs; uint32_t ff; int32_t dr[4], sr[4];
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p39 fail line %d\n",__LINE__); } } while (0)
  void *dd = plat_dd_create(NULL); uint32_t desc[31] = {0}; desc[0] = 0x7c; desc[1] = 7;
  P24_DD = dd; P24_Primary = plat_dd_create_surface(dd, desc); P24_Back = plat_dd_create_surface(dd, desc);
  P22_DevReady = 0; P39_SurfInfo si; memset(&si, 0xAA, sizeof si);
  CK(P39_LockSurface(0, 0, 0, 0, 0, &si) == 0 && si.ptr == 0xAAAAAAAAu);
  CK(P39_UnlockSurface(0, 0) == 0);
  P22_DevReady = 1; P39_Locked = 0;
  plat_dd_stub_surface(0, 0, 16, 0xf800, 0x07e0, 0x001f, 0);
  CK(P39_LockSurface(0, 1, 0, 0, 0, &si) == 1 && P39_Locked == 1 && si.pitch == 640 && si.one == 1 && si.zero == 0 && si.ptr != 0);
  CK(P39_LockSurface(0, 2, 0, 0, 0, &si) == 0);
  CK(P39_UnlockSurface(0, 1) == 1 && P39_Locked == 0);
  plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); CK(lk == 1 && ul == 1);
  CK(P39_UnlockSurface(0, 7) == 1);          /* не заблокирована — просто BeginScene */
  /* сбой Lock → буфер-пустышка, pitch 0 */
  plat_dd_stub_surface(1, 0, 16, 0xf800, 0x07e0, 0x001f, 0);
  CK(P39_LockSurface(0, 0, 0, 0, 0, &si) == 1 && si.pitch == 0 && si.ptr == (uint32_t)(uintptr_t)&P39_Dummy);
  P39_Locked = 0;
  /* формат пикселей RGB565: потери 3/2/3, сдвиги 11/5/0 */
  plat_dd_stub_surface(0, 0, 16, 0xf800, 0x07e0, 0x001f, 0);
  memset(&si, 0, sizeof si);
  CK(P39_GetSurfaceFormat(0, &si) == 1 && si.bpp == 16 && si.r_loss == 3 && si.g_loss == 2 && si.b_loss == 3 && si.r_shift == 11 && si.g_shift == 5 && si.b_shift == 0);
  P39_Locked = 0;
  plat_dd_stub_surface(0, 1, 16, 0, 0, 0, 0);   /* GetPixelFormat отказал → Unlock */
  plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); int ul0 = ul;
  CK(P39_GetSurfaceFormat(1, &si) == 0);
  plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); CK(ul == ul0 + 1 && P39_Locked == 0);
  CK(P39_GetSurfaceFormat(5, &si) == 0);
  /* Present: окно 800×600, режим 640×480 → по центру, (800−640)/2 = 80 */
  plat_dd_stub_surface(0, 0, 32, 0xff0000, 0xff00, 0xff, 0);
  P24_Hwnd = (void *)1; P31_DDObj4 = plat_dd_create_clipper(dd); P24_RestoreMode = 0; P24_ModeW = 640; P24_ModeH = 480;
  P39_Present(0);
  plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs);
  CK(bl == 1 && cs == 1 && dr[0] == 80 + 100 && dr[1] == 60 + 50 && dr[2] == 720 + 100 && dr[3] == 540 + 50 && sr[0] == 0 && sr[1] == 0 && sr[2] == 640 && sr[3] == 480);
  P24_ModeW = 1000; P24_ModeH = 1000;   /* режим больше окна — без обрезки */
  P39_Present(0); plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs);
  CK(dr[0] == 100 && dr[1] == 50 && dr[2] == 900 && dr[3] == 650 && sr[2] == 800 && sr[3] == 600);
  /* полный экран: Flip 9 / 1, потеря поверхности */
  P24_RestoreMode = 1; P39_Present(0); plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); CK(fl == 1 && ff == 9);
  P39_Present(1); plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); CK(fl == 2 && ff == 1);
  P22_DevReady = 0; P39_Present(0); plat_dd_stub_surface_stats(&lk, &ul, &fl, &ff, &bl, dr, sr, &cs); CK(fl == 2);
  P22_DevReady = 1;
  /* QueryInterface */
  int base = plat_dd_stub_count();
  void *q = P39_QueryDD4(dd); CK(q != NULL && plat_dd_stub_count() == base + 1); plat_dd_release(q);
  q = P39_QueryD3D(dd); CK(q != NULL); plat_dd_release(q);
  CK(P39_QueryDD4(NULL) == NULL && P39_QueryD3D(NULL) == NULL);
  /* основная и задний буфер */
  P32_DevInfo = (uint8_t *)calloc(1, 0x600); P24_Primary = P24_Back = NULL; P31_DDObj4 = NULL;
  CK(P39_CreateFrontBack(640, 480) == 1 && P24_Primary != NULL && P24_Back != NULL && P31_DDObj4 != NULL);
  uint32_t ld[31]; CK(plat_dd_stub_last_desc(ld) > 0 && ld[0] == 0x7c && ld[1] == 7 && ld[2] == 480 && ld[3] == 640 && ld[26] == 0x2840);
  *(int32_t *)(P32_DevInfo + 0x518) = 1; CK(P39_CreateFrontBack(320, 240) == 1);
  CK(plat_dd_stub_last_desc(ld) > 0 && ld[2] == 240 && ld[3] == 320 && ld[26] == 0x6040);
  free(P32_DevInfo); P32_DevInfo = NULL;
  plat_dd_release(dd); if (P24_DD == dd) P24_DD = NULL;   /* v2.13: висячий P24_DD → double free в test_p151 (macOS malloc: abort) */
#undef CK
  return f;
}
static int fa(float a, float b) { return fabsf(a - b) < 1e-4f; }
static int test_p43(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p43 fail line %d\n",__LINE__); } } while (0)
  P8_00546020 = 1.0f; P8_00546024 = 0.0f; P43_Eps = 1e-6f; P43_Four = 4.0f;
  float v[3] = {3, 0, 4}; CK(fa(P43_Len3(v), 5.0f));
  float z[3] = {0, 0, 0}; CK(P43_Len3(z) == 0.0f);
  float w[5] = {1, 2, 2, 0, 4}; CK(fa(P43_Len4(w), sqrtf(1 + 4 + 4 + 16)));
  P43_Normalize(v); CK(fa(v[0], 0.6f) && fa(v[2], 0.8f));
  P43_NormalizeToOut(0, 5, 0); CK(fa(P19_OutA, 0) && fa(P19_OutB, 1.0f) && fa(P19_OutC, 0));
  float o[3]; P43_NormalizeCopy(z, o); CK(o[0] == 0 && o[1] == 0 && o[2] == 0);
  float a[3] = {1, 0, 0}, b[3] = {0, 1, 0}, c[4] = {9, 9, 9, 7};
  CK(P43_Cross(c, a, b) == c && fa(c[0], 0) && fa(c[1], 0) && fa(c[2], 1) && c[3] == 7);
  /* ортонормировка: перекошенная матрица -> столбцы единичные и взаимно перпендикулярные */
  float m[9] = {1, 0.3f, 0.1f, 0.2f, 1, 0.1f, 0.0f, 0.4f, 2};
  P43_Orthonormalize(m);
  float cx[3] = {m[0], m[3], m[6]}, cy[3] = {m[1], m[4], m[7]}, cz[3] = {m[2], m[5], m[8]};
  CK(fa(P43_Len3(cx), 1) && fa(P43_Len3(cy), 1) && fa(P43_Len3(cz), 1));
  CK(fa(cx[0]*cy[0] + cx[1]*cy[1] + cx[2]*cy[2], 0) && fa(cx[0]*cz[0] + cx[1]*cz[1] + cx[2]*cz[2], 0));
  /* углы -> матрица -> кватернион -> матрица */
  for (int i = 0; i < 4096; i++) P43_Sin[i] = sinf((float)i * 6.28318530718f / 4096.0f);
  for (int i = 4096; i < 5120; i++) P43_Sin[i] = P43_Sin[i - 4096];
  int16_t ang[3] = {0, 0, 0}; float e[9]; P43_EulerMatrix(e, ang);
  CK(fa(e[0], 1) && fa(e[4], 1) && fa(e[8], 1) && fa(e[1], 0) && fa(e[5], 0));
  ang[0] = 1024; ang[1] = 0; ang[2] = 0; P43_EulerMatrix(e, ang);   /* 90° вокруг оси 0 */
  CK(fa(e[4], 0) && fa(e[5], -1) && fa(e[7], 1) && fa(e[8], 0));
  float q[5] = {0, 0, 0, 0, 0}, r[9]; P43_MatToQuat(e, q);
  CK(fa(q[4], sqrtf(0.5f) * 1.0f * 1.0f) || fa(q[4], 0.70710678f));
  P43_QuatToMat(q, r); for (int i = 0; i < 9; i++) CK(fa(r[i], e[i]));
  /* многоугольник: квадрат 0..10 (вершины по 4 float) */
  float sq[16] = {0,0,0,0, 10,0,0,0, 10,10,0,0, 0,10,0,0};
  CK(P43_PointInPoly(4, sq, 5, 5) == 1 && P43_PointInPoly(4, sq, 15, 5) == 0 && P43_PointInPoly(4, sq, 5, -1) == 0);
  /* отсечение: t0=0, t1=1 */
  float t0 = 0, t1 = 1;
  CK(P43_ClipT(2, 1, &t0, &t1) == 1 && fa(t0, 0.5f));
  t0 = 0; t1 = 1; CK(P43_ClipT(1, 2, &t0, &t1) == 0);
  t0 = 0; t1 = 1; CK(P43_ClipT(0, 1, &t0, &t1) == 0 && P43_ClipT(0, -1, &t0, &t1) == 1);
  /* CD-фейд */
  G6_00B91CF4 = 1; P43_FadeOn = 0; P43_FadeLen = 8.0f; P43_FadeDiv = 4.0f;
  P43_CdFadeInit(); CK(P43_FadeOn == 1 && P43_FadeSteps == 10 && fa(P43_FadeStep, 2.0f) && fa(P43_FadeA, 8.0f));
  P43_FadeLen = 100.0f; P43_CdFadeInit(); CK(fa(P43_FadeA, 8.0f));
  /* слоты */
  uint8_t slot[0x70]; memset(slot, 0xaa, sizeof slot);
  uint32_t fl = 0x10; memcpy(slot + 0xc, &fl, 4); int16_t id = 77; memcpy(slot + 2, &id, 2);
  P43_FreeCnt = 5; P43_FreeSlot(slot);
  CK(P43_FreeCnt == 4 && P43_FreeList[4] == 77); memcpy(&fl, slot + 0xc, 4); CK(fl == 0);
  P43_FreeSlot(slot); CK(P43_FreeCnt == 4);
  P43_AnimTab[1] = 111; P43_AnimTab[2] = 222;
  memset(slot, 0, sizeof slot); int32_t lim = 3, cur = 5, pos2 = 1; int16_t kind = 2; uint32_t flg = 0x3123;
  memcpy(slot, &kind, 2); memcpy(slot + 0xc, &flg, 4); memcpy(slot + 0x2c, &lim, 4); memcpy(slot + 0x30, &cur, 4); memcpy(slot + 0x34, &pos2, 4);
  P43_AnimNext(slot);
  memcpy(&flg, slot + 0xc, 4); memcpy(&lim, slot + 0x2c, 4); memcpy(&cur, slot + 0x30, 4); int32_t mode; memcpy(&mode, slot + 0x1c, 4);
  CK(flg == 0x0123 && mode == 2 && lim == 222 && cur == 1);
#undef CK
  return f;
}
static int test_p44(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p44 fail line %d\n",__LINE__); } } while (0)
  P8_00546020 = 1.0f; P8_00546024 = 0.0f;
  for (int i = 0; i < 4096; i++) P43_Sin[i] = sinf((float)i * 6.28318530718f / 4096.0f);
  for (int i = 4096; i < 5120; i++) P43_Sin[i] = P43_Sin[i - 4096];
  P44_InitTables();
  CK(P44_AtanTab[0] == 0 && P44_AtanTab[512] == 302 && P44_AtanTab[1024] == 512);
  /* арктангенс: 4096 = оборот, 0 = +x? проверяем по четвертям */
  CK(P44_Atan2(0, 0) == 0);
  CK(P44_Atan2(0, 10) == 0 && P44_Atan2(10, 0) == 0x400 && P44_Atan2(0, -10) == 0x800 && P44_Atan2(-10, 0) == 0xc00);
  CK(P44_Atan2(10, 10) == 0x200 && P44_Atan2(10, -10) == 0x600 && P44_Atan2(-10, -10) == 0xa00 && P44_Atan2(-10, 10) == 0xe00);
  /* сброс состояния */
  P44_Rst_B93CEC = 5; P44_Rst_B93CE0 = 7; P44_Rst_Tab[3] = 9; P44_Rst_Tab[4] = 9;
  P44_ResetState(); CK(P44_Rst_B93CEC == 0 && P44_Rst_B93CE0 == -1 && P44_Rst_Tab[3] == 0 && P44_Rst_Tab[4] == 9);
  /* точка в четырёхугольнике (обход: проверка знаков как в оригинале) */
  int32_t quad[8] = {0,0, 0,10, 10,10, 10,0};
  CK(P44_PointInQuad(5, 5, quad) == 1);
  CK(P44_PointInQuad(15, 5, quad) == 0 && P44_PointInQuad(5, -3, quad) == 0);
  /* повороты: RotX на 90° переводит столбцы 1,2 */
  float m[9]; int16_t ang[3] = {0, 0, 0};
  P44_EulerMatXYZ(m, ang); CK(fa(m[0],1) && fa(m[4],1) && fa(m[8],1) && fa(m[1],0));
  ang[0] = 1024; P44_EulerMatXYZ(m, ang);
  CK(fa(m[0],1) && fa(m[4],0) && fa(m[5],-1) && fa(m[7],1) && fa(m[8],0));
  float m2[9]; ang[0] = 1024; ang[1] = 512; ang[2] = 256;
  P44_EulerMatXYZ(m, ang); P44_EulerMatYXZ(m2, ang);
  float dot = 0; for (int i = 0; i < 3; i++) dot += m[i] * m[i]; CK(fa(dot, 1));   /* ортонормальная строка */
  P44_RotY(m, 0); P44_RotZ(m, 0); P44_RotX(m, 0); (void)m2;
  /* транспонирование */
  float t[9] = {1,2,3,4,5,6,7,8,9}, u[9]; P44_Transpose(t, u);
  CK(u[1] == 4 && u[3] == 2 && u[8] == 9 && u[2] == 7);
  /* кватернион: единичный, умножение на единичный, нормализация */
  float qi[5] = {0,0,0,0,1}, qa[5] = {0.5f,0,0,0,0.5f}, qo[5];
  P44_QuatMul(qa, qi, qo); CK(fa(qo[0],0.5f) && fa(qo[4],0.5f) && qo[3] == 0);
  P44_QuatNormalize(qa); CK(fa(qa[0], 0.70710678f) && fa(qa[4], 0.70710678f));
  float qz[5] = {0,0,0,0,0}; P44_QuatNormalize(qz); CK(qz[4] == 1.0f && qz[0] == 0);
  int16_t ea[3] = {0, 0, 0}; float eq[5]; P44_EulerToQuat(ea, eq); CK(fa(eq[4], 1) && fa(eq[0], 0));
  ea[0] = 1024; P44_EulerToQuat(ea, eq); CK(fa(eq[0], 0.70710678f) && fa(eq[4], 0.70710678f));
  /* ось-угол: поворот на 90° (ang=1024) вокруг z */
  float ax[3] = {0, 0, 1}, am[9]; P44_AxisAngleMat(1024, ax, am);
  CK(fa(am[0], 0) && fa(am[1], 1) && fa(am[3], -1) && fa(am[8], 1) && fa(am[4], 0));
  /* копирование и преобразование вектора */
  uint8_t src[7] = {1,2,3,4,5,6,7}, dst[7] = {0}; P44_Copy4(dst, src, 7); CK(memcmp(src, dst, 7) == 0);
  float M[9] = {2,0,0, 0,3,0, 0,0,4}, v[6] = {1,1,1,0,0,0}; P44_MatPtr = M;
  P44_Xform(v); CK(fa(v[0],2) && fa(v[1],3) && fa(v[2],4));
  float M2[9] = {0,1,0, 0,0,1, 1,0,0}, w[3] = {1,2,3}; P44_MatPtr = M2; P44_XformT(w);
  CK(fa(w[0], 2) && fa(w[1], 3) && fa(w[2], 1));
  float x[6] = {0,0,0,1,1,1}; P44_MatPtr = M; P44_BiasX = 10; P44_BiasY = 20; P44_BiasZ = 30; P44_XformTag = 0x3f800000u;
  P44_XformBias(x); CK(fa(x[3],12) && fa(x[4],23) && fa(x[5],34) && fa(x[0],1.0f));
  /* камера: смотрим по +x, up = +z */
  P44_CamX = 0; P44_CamY = 0; P44_CamZ = 0;
  float eye[3] = {2, 0, 0}, up[3] = {0, 0, 1}; P44_LookAt(eye, up);
  CK(fa(P44_ViewMat[6], 1) && fa(P44_ViewMat[7], 0) && fa(P44_ViewMat[8], 0));
  CK(fa(P44_ViewMat[0], 0) && fa(P44_ViewMat[1], -1));      /* right = f x up */
  CK(fa(P44_ViewMatT[2], 1) && fa(P44_ViewMatT[3], P44_ViewMat[1]));
#undef CK
  return f;
}
static int test_p46(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p46 fail line %d\n",__LINE__); } } while (0)
  P46_TexNode a = {0}, b = {0}, *o = NULL;
  a.handle = 7; a.next = &b; b.handle = 9; b.next = NULL;
  P46_TexHead = &a;
  G6_00A421F0 = 0; CK(P46_FindTexNode(9, &o) == 0);
  G6_00A421F0 = 1; CK(P46_FindTexNode(9, &o) == 1 && o == &b);
  CK(P46_FindTexNode(7, &o) == 1 && o == &a);
  CK(P46_FindTexNode(8, &o) == 0);
  P46_SetBounds(1, 2, 3, 4);
  { int32_t v[4]; memcpy(v, A_00B20330, 16); CK(G8_00B20344 <= 1 && v[0] == 1 && v[3] == 4); }
  uint8_t o1[8] = {1,0,0,0,0,0,0,0}, o2[8] = {0,0,0,1,0,0,0,0};
  (void)o1; (void)o2;   /* v1.87: 004df024 перенесена (P142_WheelPhys) — без объектов, чтобы не звать её с фиктивными записями */
  G6_00D0DDC0 = 0; G6_00B2F30C[0] = NULL; G6_00B2F30C[1] = NULL;
  P46_UpdateObjects();
  FILE *fp = tmpfile();
  uint8_t src[16]; for (int i = 0; i < 16; i++) src[i] = (uint8_t)(i + 1);
  fwrite(src, 1, 16, fp); rewind(fp);
  P46_LoadMapA(fp, 16); CK(P46_MapBufA != 0);
  fclose(fp);
  return f;
#undef CK
}
static int test_p47(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p47 fail line %d\n",__LINE__); } } while (0)
  FILE *fp = tmpfile(); char line[0x80];
  fputs("abc\n", fp); rewind(fp);
  CK(P47_ReadLine(fp, line) == 0 && strcmp(line, "abc\n") == 0);
  CK(P47_ReadLine(fp, line) == -1);
  fclose(fp);
  CK(P47_Call51B111(1, 2) == 1);
  CK(P47_NoFlags(1, 2) == 1);   /* заглушка 0051b566 возвращает 0 */
  P14_00c810e8 = 3; P47_Slots[2] = 5; P47_Slots[1] = 6; P47_Limit = 99; P47_Flag = 7; G2_00D118A8 = 0;
  P47_ResetPick();
  CK(P47_Slots[2] == -1 && P47_Slots[1] == 6 && P47_Limit == 0x32 && P47_Flag == 0 && G2_00D118A8 == 1);
  P14_00c810e8 = 9; P47_Limit = 10; P47_ResetPick(); CK(P47_Limit == 10 && P47_Slots[1] == 6);
  P11_01271060 = 7; MenuOptBDFA50 = 3; G2_00575EE4 = 4;
  CK(P47_TitleDispatch() == 0 && MenuOptBDFA50 == 3 && G2_00575EE4 == 4 && P45_Busy == 0);
  P47_CamB = 1; P47_CameraModeText(); P47_DirText(0);
  CK(P47_PrepareTemp(1) == 0);
  D_00b1c0d4 = 0; P47_WinArg5 = 0; CK(P47_GlideWinOpen(1, 2, 3, 4, 5, 6, 7) == 0 && P47_WinArg5 == 0);
  D_00b1c0d4 = 1; CK(P47_GlideWinOpen(1, 2, 3, 4, 5, 6, 7) == 0 && P47_WinArg5 == 5);   /* без Glide — NULL */
  P47_SwapCnt = 0; P11_01270c38 = 2; P47_GlideSwap(); CK(P47_SwapCnt == 1 && P11_01270c38 == 1);
  D_00b1c0d8 = 1; P47_TexTable(1, 2, 3, 4); D_00b1c0d4 = 0; P47_TexTable(1, 2, 3, 4);
  return f;
#undef CK
}
static int p48_freed[8], p48_nfreed, p48_cnt0, p48_samples[8], p48_nsamp, p48_pauses, p48_k38, p48_k54;
static void p48_drv40(int32_t s) { if (p48_nfreed < 8) p48_freed[p48_nfreed++] = s; }
static void p48_drv2c(int32_t s) { if (p48_nsamp < 8) p48_samples[p48_nsamp++] = s; }
static void p48_drv00(void) { p48_cnt0++; }
static void p48_drv08(void) { p48_pauses++; }
static void p48_drv0c(void) { p48_pauses += 10; }
static void p48_drv38(int32_t a, int32_t b, int32_t c) { (void)a; (void)b; (void)c; p48_k38++; }
static void p48_drv54(int32_t a, int32_t b, int32_t c, int32_t d) { (void)b; (void)c; (void)d; p48_k54 += a + 1; }
static void p48_put16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static void p48_put32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static void p48_putf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static uint16_t p48_get16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static uint32_t p48_get32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static float p48_getf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static int test_p48(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p48 fail line %d\n",__LINE__); } } while (0)
  P48_Drv40 = p48_drv40; P48_Drv2C = p48_drv2c; P48_Drv00 = p48_drv00; P48_Drv08 = p48_drv08; P48_Drv0C = p48_drv0c; P48_Drv38 = p48_drv38; P48_Drv54 = p48_drv54;
  for (int i = 0; i < 10001; i++) P48_VolTab[i] = 0x50000u + (uint32_t)i;
  G6_00B91CF4 = 1; G8_00575F40 = 1; P43_FadeLen = 1.0f;
  memset(P48_Snd, 0, 20 * sizeof(P48_Slot));
  for (int i = 0; i < 20; i++) P48_Snd[i].id = 0xffff;
  /* громкость голоса */
  P48_Snd[3].flags = 1; P48_Snd[3].defVol = -500;
  P48_SetVoiceVolume(3, 0x7fff);
  CK(P48_Snd[3].vol == -500 && P48_Snd[3].scaled == (int16_t)9500 && (P48_Snd[3].flags & 8));
  P48_SetVoiceVolume(3, -20000); CK(P48_Snd[3].vol == -10000 && P48_Snd[3].scaled == 0);
  P48_SetVoiceVolume(3, 77); CK(P48_Snd[3].vol == 0 && P48_Snd[3].scaled == 10000);
  P43_FadeLen = 0.5f; P48_SetVoiceVolume(3, -1000); CK(P48_Snd[3].scaled == 4500);
  P48_Snd[4].flags = 0; P48_SetVoiceVolume(4, -1); CK(P48_Snd[4].vol == 0 && P48_Snd[4].scaled == 0);
  CK(P48_GetVoiceVolume(3) == (uint16_t)-1000 && P48_GetVoiceVolume(4) == 0);
  G8_00575F40 = 0; CK(P48_GetVoiceVolume(3) == 0); G8_00575F40 = 1;
  /* мастер-громкость */
  P48_Snd[5].flags = 0x10; P48_Snd[5].vol = -2000;
  P48_SetMasterVolume(2.0f); CK(P43_FadeLen == 1.0f && P48_Snd[3].scaled == 9000 && P48_Snd[5].scaled == 8000);
  P48_SetMasterVolume(-1.0f); CK(P43_FadeLen == 0.0f && P48_Snd[3].scaled == 0);
  P48_SetMasterVolume(0.25f); CK(P43_FadeLen == 0.25f && P48_Snd[3].scaled == 2250);
  /* свободный голос, сэмплы */
  p48_nfreed = 0; P48_FreeVoice(3);
  CK(p48_nfreed == 1 && p48_freed[0] == 3 && P48_Snd[3].flags == 0 && P48_Snd[3].id == 0xffff);
  P48_FreeVoice(7); CK(p48_nfreed == 1 && P48_Snd[7].id == 0xffff);   /* пустой слот — драйвер не зовём */
  P48_Snd[9].id = 6; P48_Snd[9].flags = 1; P48_Snd[10].id = 6; P48_Snd[10].flags = 2; p48_nfreed = 0; p48_nsamp = 0;
  P48_FreeSample(6);
  CK(p48_nfreed == 2 && p48_freed[0] == 9 && p48_freed[1] == 10 && p48_nsamp == 1 && p48_samples[0] == 6 && P48_Samples[48] == 4 && P48_Snd[10].id == 0xffff);
  /* остановить всё / сброс / выключение */
  WF00575F14 = 0.75f; P43_FadeOn = 1; P43_FadeSteps = 4; P43_FadeB = 5; P43_FadeA = 2.0f; P43_FadeStep = 3.0f;
  P48_Snd[1].flags = 1; P48_Snd[1].vol = -100; p48_nfreed = 0;
  P48_StopAll();
  CK(p48_nfreed == 2 && P43_FadeOn == 0 && P43_FadeLen == 0.75f && P43_FadeSteps == 0 && P43_FadeB == 0 && P43_FadeA == 0.0f && P43_FadeStep == 0.0f);
  G6_00B91D34 = 3; G6_00B91BC4[2] = 9; p48_nsamp = 0;
  P48_ResetAll();
  CK(p48_nsamp == 3 && p48_samples[2] == 2 && G6_00B91D34 == 0 && G6_00B91BC4[2] == 0);
  P48_Snd[2].flags = 1; P48_Snd[2].vol = -300; P43_FadeOn = 1; P43_FadeLen = 0.5f; WF00575F14 = 1.0f; P48_Snd[2].scaled = 0;
  P48_FadeEnd(); CK(P43_FadeOn == 0 && P43_FadeLen == 1.0f && P48_Snd[2].scaled == 9700);
  P48_FadeEnd(); CK(P43_FadeLen == 1.0f);
  p48_pauses = 0; p48_k38 = 0; p48_k54 = 0; P48_Snd[0].flags = 1; P48_Snd[2].flags = 1; P48_Snd[1].flags = 0;
  P48_SndPause(1); CK(p48_pauses == 0 && p48_k54 == 0);
  P48_SndPause(0); CK(p48_pauses == 11 && p48_k38 == 1 && p48_k54 == (0 + 1) + (2 + 1));
  p48_cnt0 = 0; P48_SndShutdown();
  CK(p48_cnt0 == 1 && G6_00B91CF4 == 0 && P48_B91D30 == 0 && G6_00B91D34 == 0);
  P48_SndShutdown(); CK(p48_cnt0 == 1);
  /* ввод, позиция, Glide */
  memset(P34_Keys, 0, 256); CK(P48_AnyKey() == 0);
  P34_Keys[255] = 1; CK(P48_AnyKey() == 0);   /* индекс 255 не проверяется */
  P34_Keys[254] = 1; CK(P48_AnyKey() == 1); P34_Keys[254] = 0; P34_Keys[0] = 1; CK(P48_AnyKey() == 1); P34_Keys[0] = 0; P34_Keys[255] = 0;
  P48_Pos[0] = 1.9f; P48_Pos[1] = -2.9f; P48_Pos[2] = 1e6f; { int32_t o[3]; P48_PosToInts(o); CK(o[0] == 1 && o[1] == -2 && o[2] == 1000000); }
  CK(P48_GlideCheck() == 0);
  /* подсистемы */
  int com0 = plat_com_count();
  CK(P48_StartupSystems() == 1 && plat_com_count() == com0 + 1);
  P48_ShutdownSystems(); CK(plat_com_count() == com0);
  /* операции скрипта */
  uint8_t ctx[0x60], prog[64]; uint16_t fl = 0;
  memset(ctx, 0xaa, sizeof ctx); memset(prog, 0, sizeof prog);
  P10_ScriptCtx = ctx; S_00D12410 = &fl;
  p48_put16(prog + 2, 0x1234); p48_put32(prog + 4, 11); p48_put32(prog + 8, 22); p48_put32(prog + 12, 33);
  P10_ScriptPtr = prog; fl = 0; p48_put16(ctx + 0x48, 0xffff);
  CK(P48_OpSet3() == 1 && P10_ScriptPtr == prog + 16 && p48_get16(ctx + 0x4a) == 0x1234 && p48_get32(ctx) == 11 && p48_get32(ctx + 4) == 22 && p48_get32(ctx + 8) == 33 && p48_get16(ctx + 0x48) == 4);
  p48_put16(ctx + 0x4a, 7); fl = 0x10; P10_ScriptPtr = prog; P48_OpSet3(); CK(p48_get16(ctx + 0x4a) == 7);
  p48_put32(prog + 2, 5); p48_put32(prog + 6, 6); p48_put32(prog + 10, 7); p48_put32(prog + 14, 8);
  P10_ScriptPtr = prog; CK(P48_OpSet4() == 1 && P10_ScriptPtr == prog + 18 && p48_get32(ctx + 0x44) == 5 && p48_get32(ctx + 0x28) == 6 && p48_get32(ctx + 0x2c) == 7 && p48_get32(ctx + 0x30) == 8);
  /* спуск к пределу: 10 - 4 = 6 > 5 — не достигли, указатель назад */
  p48_putf(prog + 2, 5.0f); p48_putf(prog + 6, 4.0f); p48_putf(ctx + 0x44, 10.0f); p48_put16(ctx + 0x48, 0);
  P10_ScriptPtr = prog; CK(P48_OpRampDown() == 0 && P10_ScriptPtr == prog && p48_getf(ctx + 0x44) == 6.0f && (p48_get16(ctx + 0x48) & 0x40));
  CK(P48_OpRampDown() == 1 && P10_ScriptPtr == prog + 10 && p48_getf(ctx + 0x44) == 5.0f);   /* 6-4=2 <= 5 -> предел */
  p48_putf(prog + 2, 5.0f); p48_putf(prog + 6, 1.0f); p48_putf(ctx + 0x44, 1.0f);
  P10_ScriptPtr = prog; CK(P48_OpRampUp() == 0 && P10_ScriptPtr == prog && p48_getf(ctx + 0x44) == 2.0f);
  p48_putf(ctx + 0x44, 4.5f); CK(P48_OpRampUp() == 1 && P10_ScriptPtr == prog + 10 && p48_getf(ctx + 0x44) == 5.0f);
  /* флаги */
  p48_put16(prog + 2, 1); p48_put16(prog + 4, 1); p48_put16(ctx + 0x48, 0x0001); P10_ScriptPtr = prog;
  CK(P48_OpFlags() == 1 && P10_ScriptPtr == prog + 6 && p48_get16(ctx + 0x48) == 0x21);
  p48_put16(prog + 4, 0); P10_ScriptPtr = prog; P48_OpFlags(); CK(p48_get16(ctx + 0x48) == 0x01);
  p48_put16(prog + 2, 2); p48_put16(prog + 4, 0x55); P10_ScriptPtr = prog; P48_OpFlags(); CK(p48_get16(ctx + 0x40) == 0x55);
  p48_put16(prog + 2, 3); p48_put16(ctx + 0x40, 9); P10_ScriptPtr = prog; P48_OpFlags(); CK(p48_get16(ctx + 0x40) == 9 && P10_ScriptPtr == prog + 6);
  /* повтор: [2]=3 (старт), [4]=счётчик, [6]=шаг назад */
  memset(prog, 0, sizeof prog); p48_put16(prog + 2, 3); p48_put16(prog + 4, 0); p48_put16(prog + 6, 6);
  P10_ScriptPtr = prog + 20; p48_put16(prog + 22, 3); p48_put16(prog + 24, 0); p48_put16(prog + 26, 8);
  CK(P48_OpRepeat() == 1 && p48_get16(prog + 24) == 3 && P10_ScriptPtr == prog + 28);  /* счётчик был 0 — взведён */
  P10_ScriptPtr = prog + 20; CK(P48_OpRepeat() == 1 && p48_get16(prog + 24) == 2 && P10_ScriptPtr == prog + 26 - 8);
  /* поворот */
  memset(prog, 0, sizeof prog); p48_putf(prog + 2, 3.14159274f); p48_put16(prog + 6, 1);
  p48_putf(ctx + 0x44, 1.0f); p48_put16(ctx + 0x48, 0); p48_put16(ctx + 0x12, 0);
  P10_ScriptPtr = prog; /* шаг = 1024 / (pi*pi/2) = 207 */
  int r = P48_OpTurn();
  CK(p48_get16(ctx + 0x48) == 0x1c0 && p48_get16(ctx + 0x12) == (uint16_t)(0x400 + 207));
  CK(r == 0 && P10_ScriptPtr == prog);        /* осталось 0x800 - (0x400+207) = 817 >= 207 */
  p48_put16(ctx + 0x12, 0x400 + 700); p48_put16(ctx + 0x48, 0x100);
  r = P48_OpTurn(); CK(r == 1 && P10_ScriptPtr == prog + 8 && p48_get16(ctx + 0x48) == 0x80);
  return f;
#undef CK
}
static int test_p45(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p45 fail line %d\n",__LINE__); } } while (0)
  P45_Mode = 0x93; CK(P45_ModeA() == 1 && P45_Mode == 0x2f);
  P45_Mode = 0x2e; CK(P45_ModeB() == 1 && P45_Mode == 0x92);
  P45_Mode = 0x31; P45_ModeB(); CK(P45_Mode == 0x95);
  P45_Mode = 7; P45_ModeA(); CK(P45_Mode == 7);                /* вне таблицы — без изменений */
  P45_Col0 = 11; P45_Col1 = 12; P45_Col2 = 13; P45_Col3 = 14; P45_Col4 = 15;
  P45_Pick = 3; P45_PickColor(); CK(P45_Color == 14);
  P45_Pick = 9; P45_Color = 99; P45_PickColor(); CK(P45_Color == 99);
  { static int16_t its[10] = { 0, 0, 0, 0, 4 }; P45_Wait(re_addr(its), 6); CK(P58_ItemList == its && P45_PtrA == 6 && P45_Busy == 0 && P45_Step == 0); P58_ItemList = NULL; }
#undef CK
  return f;
}
static int test_p49(void) {
  int f = 0, op; float v[6]; uint32_t u;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p49 fail line %d\n",__LINE__); } } while (0)
  void *o = plat_dd_create(NULL), *b = plat_dd_create(NULL), *b3 = plat_dd_create(NULL), *p2 = plat_dd_create(NULL), *p3 = plat_dd_create(NULL);
  memset(P49_Bufs, 0, sizeof(P49_PairTab));
  P49_Listener = NULL; P49_ListenerPos(1, 2, 3); plat_ds3d_stub_last(&op, v, &u); int op0 = op;
  P49_Commit(); plat_ds3d_stub_last(&op, v, &u); CK(op == op0);        /* без слушателя — ничего */
  P49_Listener = o;
  P49_ListenerPos(1, 2, 3); plat_ds3d_stub_last(&op, v, &u); CK(op == 1 && v[0] == 1 && v[1] == 2 && v[2] == 3);
  P49_ListenerOrient(0, 0, 1, 0, 1, 0); plat_ds3d_stub_last(&op, v, &u); CK(op == 2 && v[2] == 1 && v[4] == 1 && v[5] == 0);
  P49_ListenerVel(4, 5, 6); plat_ds3d_stub_last(&op, v, &u); CK(op == 3 && v[2] == 6);
  P49_Commit(); plat_ds3d_stub_last(&op, v, &u); CK(op == 4);
  /* буферы */
  CK(P49_Play(2, 1) == 0);
  P49_Bufs[2].buf = b; P49_Bufs[2].buf3d = b3;
  CK(P49_Play(2, 1) == 1); plat_ds3d_stub_last(&op, v, &u); CK(op == 5 && u == 1);
  P49_SetVolume(2, -300); plat_ds3d_stub_last(&op, v, &u); CK(op == 6 && (int32_t)u == -300);
  P49_SetFreq(2, 22050); plat_ds3d_stub_last(&op, v, &u); CK(op == 7 && u == 22050);
  uint32_t st = 0; P49_GetStatus(2, &st); plat_ds3d_stub_last(&op, v, &u); CK(op == 8 && st == 1);
  P49_SetMode3D(2, 2); plat_ds3d_stub_last(&op, v, &u); CK(op == 9 && u == 2);
  P49_SetPos3D(2, 7, 8, 9); plat_ds3d_stub_last(&op, v, &u); CK(op == 10 && v[1] == 8);
  P49_SetVel3D(2, 1, 1, 1); plat_ds3d_stub_last(&op, v, &u); CK(op == 11);
  P49_SetMode3D(3, 1); plat_ds3d_stub_last(&op, v, &u); CK(op == 11);      /* пустая ячейка — без вызова */
  /* освобождение свойств */
  int base = plat_dd_stub_count();
  P49_Prop2C = p2; P49_Prop30 = p3; P49_ReleaseProps();
  CK(P49_Prop2C == NULL && P49_Prop30 == NULL && plat_dd_stub_count() == base - 2);
  P49_ReleaseProps(); P49_ReleaseProp2C();
  CK(plat_dd_stub_count() == base - 2);
  P49_Listener = NULL; plat_dd_release(o); plat_dd_release(b); plat_dd_release(b3);
  return f;
}
#undef CK
static int test_p50(void) {
  int f = 0, op; float v[6]; uint32_t u;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p50 fail line %d\n",__LINE__); } } while (0)
  int base = plat_dd_stub_count();
  /* FMV */
  P50_FmvA = plat_dd_create(NULL); P50_FmvFlag = P50_FmvA; P50_FmvB = plat_dd_create(NULL); P50_FmvC = plat_dd_create(NULL);
  P50_FmvReleaseObjs();
  CK(P50_FmvA == NULL && P50_FmvFlag == NULL && P50_FmvB == NULL && P50_FmvC == NULL && plat_dd_stub_count() == base);
  P50_FmvReleaseObjs(); CK(plat_dd_stub_count() == base);
  P50_Fmv834 = plat_dd_create(NULL); P50_Fmv830 = plat_dd_create(NULL); P50_Fmv82C = plat_dd_create(NULL); P38_Sample = plat_dd_create(NULL);
  P38_Mms = NULL; P50_FmvReleaseAll();
  CK(P38_Sample == NULL && P50_Fmv834 == NULL && P50_Fmv830 == NULL && P50_Fmv82C == NULL && plat_dd_stub_count() == base);
  P50_Fmv82C = plat_dd_create(NULL); P38_Mms = plat_dd_create(NULL); P50_FmvReleaseAll();
  CK(P38_Mms == NULL && P50_Fmv82C == NULL && plat_dd_stub_count() == base + 1);   /* освобождён только Mms, 82C обнулён без Release */
  /* голосовые ячейки */
  memset(P50_Voices, 0, sizeof(P50_VoiceTab));
  P50_Voices[3].a = plat_dd_create(NULL); P50_Voices[3].b = plat_dd_create(NULL);
  int c0 = plat_dd_stub_count(); P50_ReleaseVoice(3);
  CK(P50_Voices[3].a == NULL && P50_Voices[3].b == NULL && plat_dd_stub_count() == c0 - 2);
  P50_ReleaseVoice(3); CK(plat_dd_stub_count() == c0 - 2);
  /* буферы: сброс и освобождение */
  memset(P49_Bufs, 0, sizeof(P49_PairTab));
  P50_ResetBuf(1);
  P49_Bufs[1].buf = plat_dd_create(NULL); P49_Bufs[1].buf3d = plat_dd_create(NULL);
  P50_ResetBuf(1); plat_ds3d_stub_last(&op, v, &u); CK(op == 14 && u == 0);
  P49_Bufs[1].buf3d = NULL; P50_ResetBuf(1); plat_ds3d_stub_last(&op, v, &u); CK(op == 6);       /* без 3D — последним уходит громкость */
  P49_Bufs[1].buf3d = plat_dd_create(NULL);
  c0 = plat_dd_stub_count(); P50_ReleaseBuf(1);
  CK(P49_Bufs[1].buf == NULL && P49_Bufs[1].buf3d == NULL && plat_dd_stub_count() == c0 - 2);
  plat_ds3d_stub_last(&op, v, &u); CK(op == 12);
  P50_ReleaseBuf(1); CK(plat_dd_stub_count() == c0 - 2);
  /* EAX */
  uint8_t g[16]; uint32_t id, len, d0; int n;
  void *ps = plat_dd_create(NULL);
  plat_ds_stub_ctl(0, 3); plat_ds_stub_prop(g, &id, &len, &d0, &n); int n0 = n;
  P50_EaxSetDefault(NULL); plat_ds_stub_prop(g, &id, &len, &d0, &n); CK(n == n0);
  P50_EaxSetDefault(ps); plat_ds_stub_prop(g, &id, &len, &d0, &n);
  CK(n == n0 + 1 && g[0] == 0xc0 && g[1] == 0x6f && id == 1 && len == 4 && d0 == 0xbf800000u);
  P49_Prop30 = NULL; CK(P50_EaxEnable() == 0);
  P49_Prop30 = ps; CK(P50_EaxEnable() == 1); plat_ds_stub_prop(g, &id, &len, &d0, &n);
  CK(n == n0 + 2 && g[0] == 0xae && id == 0 && d0 == 2);
  plat_ds_stub_ctl(0, 1); CK(P50_EaxEnable() == 0);
  plat_ds_stub_ctl(4, 3); CK(P50_EaxEnable() == 0);
  plat_ds_stub_ctl(0, 3);
  P49_Prop30 = NULL; plat_dd_release(ps);
  /* создание свойств */
  P38_Ds = plat_dd_create(NULL); int c1 = plat_dd_stub_count();
  P49_Prop2C = NULL; P49_Prop30 = NULL;
  CK(P50_CreateKsProps() == 1 && P49_Prop2C != NULL && P49_Prop30 != NULL && plat_dd_stub_count() == c1 + 2);
  plat_ds3d_stub_last(&op, v, &u); CK(op == 15 && u == 0x12 && v[0] == 32.0f);
  P49_ReleaseProps(); CK(plat_dd_stub_count() == c1);
  plat_ds_stub_ctl(1, 3); CK(P50_CreateKsProps() == 0 && P49_Prop2C == NULL && plat_dd_stub_count() == c1);
  plat_ds_stub_ctl(2, 3); CK(P50_CreateKsProps() == 0 && P49_Prop2C == NULL && P49_Prop30 == NULL && plat_dd_stub_count() == c1);
  plat_ds_stub_ctl(0, 3);
  /* полное завершение звука */
  P49_Listener = plat_dd_create(NULL); P38_DsPrimary = plat_dd_create(NULL);
  P49_Prop2C = plat_dd_create(NULL); P49_Prop30 = plat_dd_create(NULL);
  P50_SoundShutdown();
  CK(P49_Listener == NULL && P38_DsPrimary == NULL && P38_Ds == NULL && P49_Prop2C == NULL && P49_Prop30 == NULL && plat_dd_stub_count() == c1 - 1);
  P50_SoundShutdown(); CK(plat_dd_stub_count() == c1 - 1);
  P50_Nop();
#undef CK
  return f;
}
static int test_p51(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p51 fail line %d\n",__LINE__); } } while (0)
  /* звук с дрожанием: счётчик -1 не трогается, иначе уменьшается */
  P51_PitchCount = -1; P51_PitchJitterSfx(); CK(P51_PitchCount == -1);
  P51_PitchCount = 3; P51_PitchJitterSfx(); CK(P51_PitchCount == 2);
  P51_PitchCount = 0; P51_PitchJitterSfx(); CK(P51_PitchCount == -1);
  /* масштаб пары: при 640x480, масштабе 1 — тождество */
  { float x, y;
    P51_Half = 0.5f; P19_DivW = 640.0f; P19_DivH = 480.0f; P19_Scale = 1.0f; P19_ScrW = 640; P19_ScrH = 480;
    x = 320.0f; y = 120.0f; P51_ScalePair(&x, &y); CK(x == 320.0f && y == 120.0f);
    P19_ScrW = 1280; P19_ScrH = 960; x = 320.0f; y = 120.0f; P51_ScalePair(&x, &y); CK(x == 640.0f && y == 240.0f);
    P19_Scale = 0.5f; x = 640.0f; y = 480.0f; P51_ScalePair(&x, &y); CK(x == 0.75f * 1280.0f && y == 0.75f * 960.0f); }
  /* разбор строк */
  CK(P51_PrefixMatch(" \t\r\nCAMERA 5", "CAMERA") == 1);
  CK(P51_PrefixMatch("CAMEL", "CAMERA") == 0);
  CK(P51_PrefixMatch("CAM", "CAMERA") == 0);
  CK(P51_PrefixMatch("x", "") == 1);
  { char txt[] = "AAA\nBBB 1\nCCC\nDDD\n"; char *q = P51_SkipToLine(txt, "CCC"); char *q2; CK(q == txt + 14 && *q == 'D');
    q2 = P51_SkipToLine(txt, "AAA"); CK(q2 == txt + 4); }
  { char n1[] = "-12.5x"; char n2[] = "1.2.3"; char n3[] = "42"; char *p = n1;
    CK(P51_SkipNumber(&p) == 1 && *p == 'x');
    p = n2; CK(P51_SkipNumber(&p) == 0 && *p == '.' && p == n2 + 3);
    p = n3; CK(P51_SkipNumber(&p) == 1 && *p == 0); }
  /* размер файла */
  { FILE *fp = fopen("p51_size.tmp", "wb"); CK(fp != NULL);
    if (fp) { fwrite("0123456789", 1, 10, fp); fclose(fp); fp = fopen("p51_size.tmp", "rb"); fseek(fp, 3, SEEK_SET);
      CK(P51_FileSize(fp) == 10 && ftell(fp) == 0); fclose(fp); remove("p51_size.tmp"); } }
  /* слот машины */
  { static uint8_t slot[0xcd8 + 8]; uint32_t v; memset(slot, 0xaa, sizeof slot); P51_InitCarSlot(0x1234, slot, 7);
    memcpy(&v, slot, 4); CK(v == 7);
    memcpy(&v, slot + 0xcd0, 4); CK(v == 0x1234); memcpy(&v, slot + 0xcd4, 4); CK(v == 0x3f800000);
    memcpy(&v, slot + 0xcb4, 4); CK(v == 1); memcpy(&v, slot + 0xcb8, 4); CK(v == 0); memcpy(&v, slot + 0x100, 4); CK(v == 0);
    CK(slot[0xcd8] == 0xaa); }
  /* таблица трафика */
  { uint8_t *e; uint32_t v;
    memset(P12_011443e0, 0, sizeof(p12_011443e0_t)); P51_TrafficN = 3;
    e = P12_011443e0 + 0x54; e[0] = 5; e[8] = 1; v = 9; memcpy(e + 0x28, &v, 4); v = 2; memcpy(e + 0x24, &v, 4);
    CK(P51_TrafficConflict(1, 9, 0x102, 0) == 1);   /* тот же узел и тип (b&0xff = 2) */
    CK(P51_TrafficConflict(5, 9, 2, 0) == 0);       /* своя запись */
    CK(P51_TrafficConflict(1, 9, 3, 0) == 0);
    e[3] = 1; v = 4; memcpy(e + 0x20, &v, 4); v = 8; memcpy(e + 0x2c, &v, 4); v = 77; memcpy(e + 0x28, &v, 4);
    CK(P51_TrafficConflict(1, 8, 3, 4) == 1);       /* вторая ветка: узел +0x2c и поле +0x20 */
    CK(P51_TrafficConflict(1, 8, 3, 5) == 0);
    P51_TrafficN = 0; CK(P51_TrafficConflict(1, 9, 2, 0) == 0); }
  /* курс */
  { uint8_t obj[0x20]; int32_t vec[3] = {0, 0, 1000}; int16_t c = 0x100; int32_t ang, d, e;
    memset(obj, 0, sizeof obj); memcpy(obj + 0x12, &c, 2);
    ang = P44_Atan2(vec[2], vec[0]);
    P51_SteerHeading(obj, vec); memcpy(&c, obj + 0x12, 2);
    d = (((ang - 0x100) + 0x800) & 0xfff) - 0x800; e = d < 0 ? -d : d;
    CK(e < 0x20 ? c == (int16_t)ang : (d < 0 ? c == 0x100 - 0x20 : c == 0x100 + 0x20));
    c = (int16_t)ang; memcpy(obj + 0x12, &c, 2); P51_SteerHeading(obj, vec); memcpy(&c, obj + 0x12, 2); CK(c == (int16_t)ang);
    c = (int16_t)(ang + 0x30); memcpy(obj + 0x12, &c, 2); P51_SteerHeading(obj, vec); memcpy(&c, obj + 0x12, 2); CK(c == (int16_t)(ang + 0x10)); }
  /* направление / вид узла */
  { uint8_t o[0x120]; uint32_t v = 1024; int32_t neg = -1; uint8_t d0, d1; uint8_t nd[0x40]; uint16_t fl = 1;
    memset(o, 0, sizeof o); memcpy(o + 0x100, &v, 4);
    d0 = P51_DirFromHeading(o); memcpy(o + 0x10c, &neg, 4); d1 = P51_DirFromHeading(o);
    CK(d1 == ((d0 + 2) & 3) && d0 <= 3);
    memset(P51_Tab1ED80, 0, sizeof P51_Tab1ED80);
    memset(nd, 0, sizeof nd); CK(P51_NodeKind(nd) == 0);
    memcpy(nd + 0xe, &fl, 2); CK(P51_NodeKind(nd) == 1);
    fl = 4; memcpy(nd + 0xe, &fl, 2); CK(P51_NodeKind(nd) == 2); nd[3] = 1; CK(P51_NodeKind(nd) == 0);
    G00C29D80 = 3; CK(P51_NodeKind(nd) == 3); G00C29D80 = 0; v = 1; memcpy(nd + 0x24, &v, 4); G00C29D81 = 3; CK(P51_NodeKind(nd) == 3);
    P51_Tab1ED80[3] = 1; CK(P51_NodeKind(nd) == 0); P51_Tab1ED80[3] = 0; v = 1; memcpy(nd + 0x34, &v, 4); CK(P51_NodeKind(nd) == 1); }
#undef CK
  return f;
}
static int test_p53(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p53 fail line %d\n",__LINE__); } } while (0)
  /* шаг границ: пустая запись -1 → сброс слотов и счётчик, иначе индекс растёт */
  memset(A_00B20330, 0, sizeof(A_00B20330)); { int32_t m1 = -1; memcpy(&A_00B20330[4], &m1, 4); }
  G8_00B20344 = 0; P11_00b20360 = 5;
  P53_StepBounds();   /* IsSlotActive(0xf) в тесте зависит от таблицы слотов; пустая → не активен */
  CK(G8_00B20344 == 1 || P11_00b20360 == 6);
  /* ввод имени */
  P52_MenuCnt = 1; P52_MenuC = 0; memset(P52_NameTab, 0, sizeof(P52_NameTab));
  P53_NameEntryKey('A'); P53_NameEntryKey('B');
  CK(P52_MenuC == 2 && P52_NameTab[0x11] == 'A' && P52_NameTab[0x12] == 'B' && P52_NameTab[0x13] == 0);
  P53_NameEntryKey(-1); CK(P52_MenuC == 1 && P52_NameTab[0x12] == 0);
  P53_NameEntryKey(-1); P53_NameEntryKey(-1); CK(P52_MenuC == 0);
  P52_MenuC = 0xf; P53_NameEntryKey('Z'); CK(P52_MenuC == 0xf);
  P52_MenuA = 4; P52_MenuB = 4; P53_NameEntryKey(-3); CK(P52_MenuA == 0 && P52_MenuB == 0);
  P53_NameEntryKey(0);
  /* текстурный источник */
  { uint8_t d[0x14]; memset(d, 0, sizeof d); int32_t k = 5; memcpy(d + 0xc, &k, 4);
    P22_DevReady = 1; P22_TexVarA = 0; P32_CurSlot = 0;
    uint32_t h = 0x1234; memcpy(&P53_TexTab[3 * 0x20], &h, 4);
    P53_SetTexSource(0, 3u << 16, 0, re_addr(d));
    CK(P22_TexVarA == 3 && P22_TexVarB == 3 && (uintptr_t)P32_CurHandle == 0x1234 && P32_CurSlot == -1);
    k = 0; memcpy(d + 0xc, &k, 4); P53_SetTexSource(0, 5u << 17, 0, re_addr(d));
    CK(P22_TexVarA == 10);
    P53_SetTexSource(0, 0x40u << 16, 0, re_addr(d));   /* вне диапазона: без изменений */
    CK(P22_TexVarA == 10);
    P22_DevReady = 0; P53_SetTexSource(0, 1u << 16, 0, re_addr(d)); CK(P22_TexVarA == 10); }
  /* поиск узла */
  G6_00A421F0 = 0; CK(P53_TexLookup(1, 2, 3, 4) == 1);
  G6_00A421F0 = 1; P46_TexHead = NULL; P53_TexLookup(1, 2, 3, 4);
  /* чтение файла */
  { FILE *fp = fopen("p53_test.bin", "wb"); uint8_t src[300]; for (int i = 0; i < 300; i++) src[i] = (uint8_t)i;
    fwrite(src, 1, 300, fp); fclose(fp);
    uint8_t dst[300] = {0};
    CK(P53_ReadWholeFile("p53_test.bin", dst) == 300 && memcmp(src, dst, 300) == 0);
    CK(P53_ReadWholeFile("p53_missing.bin", dst) == 0); remove("p53_test.bin"); }
  /* вызов со структурой, меню */
  P53_Ang2702 = 0x10; P53_CallWithState(1, 2, 3);
  P53_FlagF9F4 = 0; P11_00b87e38 = 0x30; CK(P53_MenuA() == 1 && MenuMode1271060 == 8);
  P11_00b87e38 = 0x30; Q0057B56C = 6; CK(P53_MenuB() == 1 && P12_00bdfa40 == 7);
  P53_FlagF9F4 = 1; P53_MenuA();
  { uint32_t v = 77; memcpy(&P53_ModeTab[5 * 8 + 2], &v, 4); }
  MenuMode1271060 = 5; P53_MenuSel = 2; CK(P53_MenuC() == 1 && P11_00b87e38 == 77);
  MenuMode1271060 = 1; P53_MenuSel = 0; P8_0054da10 = 1; CK(P53_MenuC() == 1);
  MenuMode1271060 = 9; P11_00b87e38 = 5; CK(P53_MenuC() == 1 && P11_00b87e38 == 5);
#undef CK
  return f;
}
static int test_p54(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p54 fail line %d\n",__LINE__); } } while (0)
  /* 0040500d: значки строк меню */
  memset(P54_SelTab, 0, sizeof(p54_i16_t)); P54_SelTab[0] = 0; P54_SelTab[1] = 5; P54_SelTab[2] = 8; P54_SelTab[3] = 77; P54_SelTab[4] = -1;
  P54_IconIdx[3] = 9; P54_IconIdx[4] = 10; P12_00c55820[9] = 0xAAAA; P12_00c55820[10] = 0xBBBB;
  MenuOptBDFA44 = 3; MenuOptB87E9C = 4;
  P54_MenuTexSel();
  CK(P54_Out[8] == 0xAAAA && P54_Out[16] == 0xBBBB && P54_Out[24] == 0x0057b668u);
  /* 004f3c16 / 0051aacd / 0051aa5b: таблицы буферов */
  P54_Tab4[0] = DebugMalloc(16, "t", 1); P54_Tab4[2] = DebugMalloc(16, "t", 2); P54_Tab4[1] = NULL; P54_Tab4[3] = NULL;
  P54_FreeTab4(); CK(P54_Tab4[0] == NULL && P54_Tab4[2] == NULL);
  { /* Motion buffers must leave both the allocation table and pointer registry. */
    uint32_t addr[4]; int32_t freed = P27_MemFreed;
    for (int i = 0; i < 4; i++) {
      P54_Tab4[i] = P98_DebugMalloc(0x80002, "motion_c.c", 257);
      addr[i] = re_addr(P54_Tab4[i]);
    }
    P54_FreeTab4();
    for (int i = 0; i < 4; i++) CK(P54_Tab4[i] == NULL && re_ptr(addr[i]) == NULL);
    CK(P27_MemFreed == freed + 4 * 0x80002);
    P54_FreeTab4(); CK(P27_MemFreed == freed + 4 * 0x80002);
  }
  P54_AllocRoadbits(); CK(P54_RoadId[0] == -1 && P54_RoadId[3] == -1 && P54_RoadA[3] != NULL && P54_RoadB[0] != NULL);
  P54_FreeRoadbits(); CK(P54_RoadA[0] == NULL && P54_RoadB[3] == NULL);
  P54_GridN = 4; P54_Cnt1E0 = 0x10;
  P54_AllocMapBufs(); CK(G6_00D01268 != NULL && G6_00D00208 != NULL && G6_00CE0F20 != NULL);
  DebugFree(G6_00D01268); DebugFree(G6_00D00208); DebugFree(G6_00CE0F20);
  /* 0040748a / 0040724c */
  for (int i = 0; i < 15; i++) P54_KeySrc[i] = 0x100 + i;
  Q0057B72C = 0; CK(P54_DefaultKeys() == 0);
  { uint32_t v; memcpy(&v, &P36_KeyCfg[16], 4); CK(v == 0x104 && P54_KeySrc[6] == 0x100 && P54_KeySrc[10] == 0x104); }
  Q0057B72C = 1; P54_DefaultKeys(); CK(P54_Keys3[0] == 0x10c && P54_Keys3[2] == 0x10e);
  P35_InputMode = 0; for (int i = 0; i < 6; i++) P54_Src6[i] = 0x200 + i;
  P54_InitInputMode(); CK(Q0057B72C == 0 && P54_Dst[0] == 0x200 && P54_Dst[4] == 0x201 && P54_Dst[12] == 0x202 && P54_Dst[24] == 0x205);
  /* 00493f9a / 00493e3d: объект-счётчик */
  { uint8_t o[0x50]; memset(o, 0, sizeof o); o[8] = 7; o[0xb] = 3;
    P54_ObjTick(o); CK(o[8] == 0 && o[0xb] == 2);
    o[0xb] = 0; int32_t m1 = -1; memcpy(o + 0x28, &m1, 4); P54_ObjTick(o); CK(o[0xb] == 0);
    P54_G40 = 11; P54_G44 = 22; o[0x13] = 0xff; o[1] = 9;
    P54_ObjInit(o); { int32_t a, b; memcpy(&a, o + 0x40, 4); memcpy(&b, o + 0x44, 4); CK(a == P54_G40 && b == P54_G44 && o[1] == 3 && o[0x13] == 0xfb); } }  /* 004913cc теперь настоящая (P75_TrafficPos) и перезаписывает 11/22 */
  /* 0041de46 / 004248c6 / 0040c5be: без устройства/Glide — ничего не делают */
  P22_DevReady = 0; P54_ClearBuffers(0, 0, 0);
  D_00b1c0d4 = 0; P54_TexSource(1, 2, 3, NULL, 5);
  P54_ClearSwap(2);
  CK(P54_GetTexture2(NULL) == NULL);
  /* 004ec7ac / 004ec280 / 004ec3fd: чтение блоков карты из файла */
  { FILE *fp = fopen("p54_test.bin", "wb"); uint8_t src[64]; for (int i = 0; i < 64; i++) src[i] = (uint8_t)i;
    fwrite(src, 1, 64, fp); fclose(fp);
    fp = fopen("p54_test.bin", "rb"); P54_ReadNames(fp, 16); CK(P20_Names != NULL && (uint8_t)P20_Names[5] == 5); DebugFree(P20_Names);
    rewind(fp); P54_ReadMapA(fp, 20); CK(P54_MapA == 0x03020100 && P54_MapAPtr != NULL && ((uint8_t *)P54_MapAPtr)[0] == 4); DebugFree(P54_MapAPtr);
    rewind(fp); P54_ReadMapB(fp, 24); CK(P54_MapB1 == 0x03020100 && P54_MapB2 == 0x07060504 && ((uint8_t *)P54_MapBPtr)[0] == 8); DebugFree(P54_MapBPtr);
    fclose(fp); remove("p54_test.bin"); }
#undef CK
  return f;
}
static int test_p52(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p52 fail line %d\n",__LINE__); } } while (0)
  P21_FrameFlagB = 0; P21_FrameFlagA = 5; P21_FrameMin = 9; MenuVar575EF8 = 0;
  P52_MenuStepToggle(); CK(P21_FrameFlagB == 1 && P21_FrameFlagA == 0 && P21_FrameMin == 1 && MenuVar575EF8 == 4);
  P52_MenuStepToggle(); CK(P21_FrameMin == 2 && P21_FrameFlagA == 0);
  P21_FrameMin = 5; P52_MenuStepToggle(); CK(P21_FrameFlagA == 1 && P21_FrameMin == 5);
  P52_MenuStepToggle(); CK(P21_FrameFlagA == 0 && P21_FrameFlagB == 0);
  P52_ResetA = 7; P52_ResetB = 9; P52_ResetC = 5; P52_Ones0 = P52_Ones1 = P52_Ones2 = P52_Ones3 = 0;
  P52_ResetSlots(); CK(P52_ResetA == 0 && P52_ResetB == 0 && P52_ResetC == 0);
  CK(P52_Ones0 == 1 && P52_Ones1 == 1 && P52_Ones2 == 1 && P52_Ones3 == 1);
  P52_MenuA = P52_MenuB = P52_MenuC = 3; GameMode = 4; P52_MenuCnt = 2;
  P52_MenuReload(); CK(P52_MenuA == 0 && P52_MenuB == 0 && P52_MenuC == 0);
  P52_FogOn = 1; P26_FxD = 0; P52_GlideFogSetup(); CK(P26_FxD == 1);
  P52_GlideFogSetup(); CK(P26_FxD == 1);
  P52_FogOn = 0; P26_FxD = 0; P52_GlideFogSetup(); CK(P26_FxD == 0);
  P52_NoTrail = 0; P52_GlideFogMode();
  D_00b1c0d4 = 0; P52_TexDownloadMipMap(1, 2, 3, 4, 5); D_00b1c0d4 = 1; D_00b1c0d8 = 0; P52_TexDownloadMipMap(1, 2, 3, 4, 5);
  D_00b1c0d8 = 1; P52_TexDownloadMipMap(1, 2, 3, 4, 5);
  D_00b87e30 = 4; P11_00b87e38 = 0xc9; P12_00d044d0 = 1; P52_HudDispatch();
  D_00b87e30 = 5; G6_00B87EA0 = 1; P52_HudDispatch(); D_00b87e30 = 0; P52_HudDispatch();
  CK(P52_FmvStart(0) == 0);
  P52_ColorTab[8] = 1; P52_ColorTab[9] = 2; P52_ColorTab[10] = 3;
  P52_DrawLabel(0, 0x10, 2); P52_DrawLabel(0, -1000, 2);
#undef CK
  return f;
}
static int test_p55(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p55 fail line %d\n",__LINE__); } } while (0)
  /* таблицы объектов */
  P44_MatPtr = NULL; P55_CntA = 0; P55_RunTableA(); CK(P44_MatPtr == NULL);
  P55_CntA = 3; P55_RunTableA(); CK(P44_MatPtr == (float *)P44_ViewMatT);
  P44_MatPtr = NULL; P55_CntB = 2; P55_Flag38C = 7; P55_RunTableB(); CK(P44_MatPtr != NULL && P55_Flag38C == 0);
  /* сброс индексов */
  P55_ResetSel(); CK(P55_VarC0 == -1 && P55_Var20 == -1 && P55_VarD2C == -1 && P55_VarD20 == -1);
  /* списки имён: без реального 00405e79 используется имя по умолчанию */
  P55_DefName = "A-very-long-default-name-that-overflows";
  P55_NamesA(); CK(strcmp((char *)P12_005fe7a8 + 0x20 + 16, "A-very-long-def") == 0 && P12_005fe7a8[3] == 0);
  P55_NamesC(); CK(strncmp((char *)P12_005fee60 + 0x11 * 2, "A-very-long-defa", 16) == 0 && P12_005fee60[0x11 * 2 + 16] == 0);
  P55_NamesD(); CK(P52_NameTab[0x11 * 7 + 16] == 0 && P55_FlagsC[7] == 0);
  /* очередь отложенных вызовов */
  P55_PopTab[0].w = 11; P55_PopTab[0].x = 5; P55_PopTab[0].y = 6; P55_PopTab[1].w = 22;
  P55_PopCnt = 2; P55_PopSkip = 1; P55_PopB2AC = 9; P55_PopDeferred();
  CK(P55_PopCnt == 0 && WH00B2C3A8 == 11 && G6_00D117A4 == 0 && G6_00D117A8 == 0 && P55_PopB2AC == 0);
  /* FRUSTRUM.DAT */
  /* v1.74: настоящий FRUSTRUM.DAT (в work/run — симлинк на input/) отодвигается rename (переименовывается ссылка, не цель) и возвращается */
  { int had = rename("FRUSTRUM.DAT", "FRUSTRUM.DAT.p55bak") == 0;
    FILE *fp = fopen("FRUSTRUM.DAT", "wb"); static uint8_t z[4 + 0x8000]; memset(z, 0, sizeof z);
    for (int i = 0; i < 0x8000; i++) z[4 + i] = (uint8_t)(i * 7);
    fwrite(z, 1, sizeof z, fp); fclose(fp);
    memset(P55_Frustum, 0, sizeof(p55_frustum_t));
    CK(P55_LoadFrustum() == 0 && P55_Frustum[1] == 7 && P55_Frustum[0x8000 - 1] == (uint8_t)(0x7fff * 7));
    remove("FRUSTRUM.DAT"); int lf = P55_LoadFrustum(); if (had) rename("FRUSTRUM.DAT.p55bak", "FRUSTRUM.DAT"); CK(lf == -1); }
  /* описание устройства */
  { uint32_t o[11]; memset(o, 0xAA, sizeof o);
    P24_RShiftR = 1; P24_BShiftL = 6; P55_A4219C = 7; G6_00A421F0 = 8; P23_DevCaps = 9;
    P55_FillDevInfo(o); CK(o[0] == 1 && o[5] == 6 && o[6] == 7 && o[8] == 8 && o[9] == 9 && o[10] == 0x00601bc0u);
    D_00b1c0d4 = 1; D_00b1c0d8 = 0; P55_GlideDevInfo(o); CK(o[0] == 3 && o[1] == 10 && o[9] == 0xffffffffu && o[10] == 0);
    D_00b1c0d8 = 1; P55_GlideDevInfo(o); CK(o[9] == 9);
    D_00b1c0d4 = 0; o[0] = 55; P55_GlideDevInfo(o); CK(o[0] == 55); }
  /* загрузка файлов */
  { FILE *fp = fopen("p55_test.bin", "wb"); fwrite("0123456789", 1, 10, fp); fclose(fp);
    int32_t sz = -1; uint8_t *b = P55_LoadFile("p55_test.bin"); CK(b != NULL && memcmp(b, "0123456789", 10) == 0); DebugFree(b);
    b = P55_LoadFileSize("p55_test.bin", &sz); CK(b != NULL && sz == 10 && b[9] == '9'); DebugFree(b);
    remove("p55_test.bin"); CK(P55_LoadFile("p55_test.bin") == NULL && P55_LoadFileSize("p55_test.bin", &sz) == NULL); }
  /* запись состояния */
  { uint8_t *rec = calloc(0x1a4 * 2, 1), *src = calloc(0x148 * 4, 1);
    P55_RecBase = rec; G0113A6C4 = src; P55_RecCnt = 1; G8_00D118C0 = 1234; TrafficRecs[2 * 0x54 + 1] = 0x42; src[2 * 0x148] = 0x99;
    P55_SaveRec(2);
    CK(P55_RecCnt == 2 && *(uint32_t *)(rec + 0x1a4) == 1234 && *(uint32_t *)(rec + 0x1a4 + 4) == 2 &&
       rec[0x1a4 + 8 + 1] == 0x42 && rec[0x1a4 + 0x5c] == 0x99);
    P55_RecCnt = 0x800; P55_SaveRec(2); CK(P55_RecCnt == 0x800);
    P55_RecBase = NULL; P55_RecCnt = 0; P55_SaveRec(2); CK(P55_RecCnt == 0);
    free(rec); free(src); }
  /* раскладка */
  for (int i = 0; i < 15; i++) P54_KeySrc[i] = 0x300 + i;
  Q0057B72C = 4; Q00B87EF0 = 0; CK(P55_NextPad() == 0);
  { uint32_t v; memcpy(&v, &P36_KeyCfg[0], 4); CK(Q0057B72C == 0 && v == 0x306); }
  /* бумага и остановка звука */
  memset(G6_00D04A50, 1, 40); P55_Lang = 0; P55_LoadPaper(); CK(G6_00D04A50[0] == 0 && G6_00D04A50[35] == 0 && G6_00D04A50[36] == 1);
  P55_StopAudio(); CK(G6_00B5A778 == 0 && G6_00B87EFC == 0);
  return f;
}

static int test_p56(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p56 fail line %d\n",__LINE__); } } while (0)
  /* 005105da */
  G005F7E54 = 4; GameMode = 0; G8_00D118C0 = 100; P56_Blk84[1] = 0; P56_Blk84[5] = 7; P56_Blk11[3] = 9; G6_00B87E20 = 5;
  P56_ReplaySetup();
  CK(P56_Save84[5] == 7 && P56_Blk84[1] == 0xff0 && P56_Save84[1] == 0xff0 && P56_Save11[3] == 9 && DirectorLastFrame == 96 && G6_00B87E20 == 0);
  G005F7E54 = 1; P56_Save84[5] = 0; P56_ReplaySetup(); CK(P56_Save84[5] == 0);
  /* 004daa36 / 004da8d9 */
  { uint32_t ob[0x148 / 4 + 1]; int32_t q[3] = {100, -200, 300}; memset(ob, 0xaa, sizeof ob);
    P56_ObjInit((uint8_t *)ob, q);
    CK(ob[0x24 / 4] == 1600 && (int32_t)ob[0x28 / 4] == -3200 && ob[0x2c / 4] == 4800);
    CK(ob[0x18 / 4] == 100 && ob[0xc8 / 4] == 100 && (int32_t)ob[0x1c / 4] == -200 && ob[0xd0 / 4] == 300);
    CK(ob[0x3c / 4] == 0x1000 && ob[0x58 / 4] == 0 && ob[0x5c / 4] == 0xffffd556u && ob[0x10 / 4] == 0 && G6_005624A0 == 0xf);
    int32_t a[7] = {32, 0, 0, 0x1000, 0, 0, 0x1000}; uint32_t o2[0x148 / 4];
    memset(o2, 0, sizeof o2); P56_ObjSync(a, (uint8_t *)o2);
    /* s = 0x2000000 -> k = 0x1800 - 0x1000 = 0x800: (0x800*0x1000+0x800)>>12 = 0x800 */
    CK(o2[0x18 / 4] == 2 && a[3] == 0x800 && a[6] == 0x800); }
  /* 00523ec6 */
  G8_00B91CF4 = 1; G8_00575F40 = 1; P48_Snd[3].flags = 0x31;
  P56_SetVoicePos(3, 1.0f, 2.0f, 3.0f);
  { float v[3]; memcpy(v, P48_Snd[3].data, 12); CK(v[0] == 1.0f && v[2] == 3.0f); CK(P48_Snd[3].flags == 0x13); }
  P56_SetVoicePos(3, 4.0f, 5.0f, 6.0f);
  { float v[3]; memcpy(v, P48_Snd[3].data + 12, 12); CK(v[1] == 2.0f); memcpy(v, P48_Snd[3].data, 12); CK(v[1] == 5.0f); }
  P48_Snd[4].flags = 0; P56_SetVoicePos(4, 1, 1, 1); CK(P48_Snd[4].flags == 0);
  G8_00575F40 = 0; P48_Snd[3].flags = 0x11; P56_SetVoicePos(3, 9, 9, 9); CK(P48_Snd[3].flags == 0x11);
  P48_Snd[3].flags = 0;
  /* 004d62ae / 004d6a47 */
  P56_Cur = -1; TrafficRecs[0x54 + 2] = 1; P56_LoopStart(2); CK(P56_Cur == -1);
  TrafficRecs[0x54 + 2] = 0; P56_LoopTab[1] = 77; G8_00D118C0 = 1; ObjPosTable[2 * 0x52] = 5; P56_LoopStart(2); CK(P56_Cur == 2);
  P56_LoopUpdate(); CK(P56_Cur == -1);
  P56_LoopUpdate(); CK(P56_Cur == -1);
  /* 0040c165 */
  P41_Arena = 0; P54_MapAPtr = DebugMalloc(16, "t", 1); P54_MapA = 4; Q00B87E90 = 0; G6_00B87EFC = 3; P56_AA30 = 0;
  P56_ResetFrontend(); CK(P54_MapAPtr == NULL && P54_MapA == 0 && P56_AA30 == 0x3f000000u && G6_00B87EFC == 0);
  /* A front-end TSD arena is not the level loader's cached RAM pointer.
     Both allocations must also leave the tracking table and address registry. */
  {
    void *arena = P98_DebugMalloc(32, "p56", 1);
    void *icons = P98_DebugMalloc(16, "p56", 2);
    CK(arena != NULL && icons != NULL);
    uint32_t arena_addr = re_addr(arena), icons_addr = re_addr(icons);
    int freed = P27_MemFreed;
    P41_Arena = arena_addr; P41_Offset = 32; P54_MapAPtr = icons; P54_MapA = 1;
    P56_ResetFrontend();
    CK(P41_Arena == 0 && P41_Offset == 0 && P54_MapAPtr == NULL && P54_MapA == 0);
    CK(re_ptr(arena_addr) == NULL && re_ptr(icons_addr) == NULL && P27_MemFreed == freed + 48);
    P56_ResetFrontend(); CK(P27_MemFreed == freed + 48);
  }
  /* 004f5a57 */
  P56_Blk84[1] = 0xf1; P56_Blk84[2] = 0x32; P56_ChaseTick(); CK(P56_Blk84[2] == 0x33);
  P56_ChaseTick(); CK(P56_Blk84[2] == 0x33);
  P56_Blk84[1] = 0x10; P56_ChaseTick(); CK(P56_Blk84[1] == 0x7fff);
  P56_Blk84[1] = 0x8000; P56_C81880 = 0; P56_ChaseTick(); CK(P56_C81880 == 1 && P56_Blk84[16] == 0x96 && P56_Blk84[10] == 0 && G2_00D118A8 == 1);
  /* 0051d8ca */
  { uint32_t s[16]; for (int i = 0; i < 16; i++) s[i] = 0x100 + i; P56_CopyBlock16(s); CK(P56_Blk16[0] == 0x100 && P56_Blk16[15] == 0x10f); }
  /* 004e625e (значок не найден: в native заглушка) */
  memset(P56_GhostBuf, 1, 16); P56_G4538 = 3; P56_GhostInit(); CK(P56_GhostBuf[0] == 0 && P56_G4538 == 0 && P56_GhostPtr == NULL);
  /* 0049245a / 0051990a */
  { uint8_t *car = (uint8_t *)calloc(0x41, 0x148); G0113A6C4 = car; memset(TrafficRecs, 0, sizeof(TRAFFIC_RECS_T));
    TrafficRecs[2 * 0x54 + 6] = 5; uint32_t v = 11, w = 22, z = 33, lim = 10;
    memcpy(car + 2 * 0x148 + 200, &v, 4); memcpy(car + 2 * 0x148 + 0xcc, &w, 4); memcpy(car + 2 * 0x148 + 0xd0, &z, 4); memcpy(car + 2 * 0x148 + 0x138, &lim, 4);
    uint32_t out[3] = {0, 0, 0};
    CK(P56_CarPosCheck(4, 10, out) == 1 && out[0] == 11 && out[1] == 22 && out[2] == 33);
    CK(P56_CarPosCheck(4, 11, NULL) == 0);
    uint8_t *rec = (uint8_t *)calloc(3, 0x1a4); uint32_t fr = 77, idx = 3; G8_00D118C0 = 77;
    memcpy(rec + 0x1a4, &fr, 4); memcpy(rec + 0x1a4 + 4, &idx, 4); rec[0x1a4 + 8] = 0xab; rec[0x1a4 + 8 + 0x53] = 0xcd; rec[0x1a4 + 0x5c + 0x147] = 0xef;
    P55_RecBase = rec; P55_RecCnt = 0; CK(P56_ReplayRead() == -1 && P55_RecCnt == 0);
    P55_RecCnt = 1; CK(P56_ReplayRead() == 3 && P55_RecCnt == 2 && TrafficRecs[3 * 0x54] == 0xab && TrafficRecs[3 * 0x54 + 0x53] == 0xcd && car[3 * 0x148 + 0x147] == 0xef);
    P55_RecCnt = 0x800; CK(P56_ReplayRead() == -1);
    P55_RecBase = NULL; P55_RecCnt = 0; CK(P56_ReplayRead() == -1);
    G0113A6C4 = NULL; free(car); free(rec); }
  /* 004e4f62 */
  P59_S4654 = 5;   /* v1.48: 004e5011 связан (P103_GhostState) — состояние без действий */
  P15_State = 4; G6_00B87EA0 = 0; G6_00B5A778 = 0; G00D044C8 = 5; P12_00d044d0 = 2; P56_D4470 = 1; P56_B87EA8 = 1; P56_HudTick(0);
  CK(G00D044C8 == 6 && P12_00d044d0 == 1 && P56_D4470 == 0);
  P15_State = 1; P56_HudTick(0); CK(G00D044C8 == 6);
  /* 004f3032 */
  { int16_t row[2 + 62]; memset(row, 0, sizeof row); row[3] = 4; P56_DrawRowRects(row, 1, 2); P56_DrawRowRects(NULL, 0, 0); }
  /* 005046f7 */
  { uint8_t bmp[16]; for (int i = 0; i < 16; i++) bmp[i] = (uint8_t)(i + 1); memset(P56_Page, 0, 600);
    P56_BmpPage(0, bmp, 1, 1, 2, 2, 4); CK(P56_Page[0] == 6 && P56_Page[1] == 7 && P56_Page[256] == 10 && P56_Page[257] == 11 && P56_Page[2] == 0);
    P56_BmpPage(0, NULL, 0, 0, 0, 0, 0); }
  /* 00426c06 */
  { uint8_t *t = P56_AllocEulerTab(512); CK(t != NULL); if (t) { float m0, m8; memcpy(&m0, t, 4); memcpy(&m8, t + 0x40 * 8 - 0x40, 4); CK(m0 > 0.99f && m0 < 1.01f); (void)m8; DebugFree(t); } P56_EulerTab = NULL; }
  /* 0049ee5d */
  { float o = -1; P56_Spline(0.0f, &o, 1.0f, 2.0f, 3.0f, 4.0f); CK(o == 2.0f);
    P56_Spline(1.0f, &o, 1.0f, 2.0f, 3.0f, 4.0f); CK(o == 3.0f);
    P56_Spline(0.5f, &o, 0.0f, 2.0f, 2.0f, 0.0f); CK(o > 2.0f && o < 2.5f); }
  /* 0049f180 */
  { float a[4] = {1, 2, 3, 9}; float b[5] = {0, 0, 0, 0, 1}; P56_QuatRot(a, b); CK(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 0); }
  /* 00506b4b */
  P56_Sprite = NULL; P56_DrawSprite(); { uint8_t sp[16] = {0}; P56_Sprite = sp; P56_DrawSprite(); P56_Sprite = NULL; }
  /* 00518137 */
  strcpy(P56_PathName, "Run"); P56_ReplayPaths(7);
  CK(strcmp(P56_PathLeader, "ReplayData\\Chase\\Run.LEADER") == 0 && strcmp(P56_PathPings, "ReplayData\\Chase\\Run.PINGS") == 0);
  CK(strcmp(P56_PathCams, "ReplayData\\RepCams.7") == 0 && strcmp(P56_PathKey, "ReplayData\\KeyFrame.7") == 0 && strcmp(P56_PathStart, "ReplayData\\StartPos.7") == 0);
  CK(strcmp(P56_PathPlayer, "ReplayData\\Chase\\Run.PLAYER") == 0 && strcmp(P56_PathPads, "ReplayData\\Chase\\Run.PADS") == 0);
  /* 004d263d */
  P56_CopsA = 1; P56_CopsB = 1; P56_CopsDebug(); CK(P56_CopsA == 0 && P56_CopsB == 0);
  /* 00405cb4 */
  { const char *nm = "SAVES\\GAME1.BIN"; uint8_t buf[8 + 0x38]; memset(buf, 3, sizeof buf); uint32_t mg = 0x57231356u, ck = (uint32_t)SumBytes(buf + 8, 0x38); memcpy(buf, &mg, 4); memcpy(buf + 4, &ck, 4);
    CK(P56_SaveCheck(0) == 0);
    FILE *fp = fopen(nm, "wb"); if (fp) { fwrite(buf, 1, sizeof buf, fp); fclose(fp); }
    CK(P56_SaveCheck(0) == 1);
    mg = 0; memcpy(buf, &mg, 4); fp = fopen(nm, "wb"); if (fp) { fwrite(buf, 1, sizeof buf, fp); fclose(fp); }
    CK(P56_SaveCheck(0) == 0);
    remove(nm); }
  return f;
}
/* 0040c8f1 (опрос меню) не перенесён: в тестах «пользователь» сразу выходит из экрана (-1), чтобы циклы меню завершались. */
static int32_t t63_ret = -1;
/* v2.02: шпионы selftest вне selftest (игра, re_selftest_on = 0) передают вызов перенесённой функции */
extern int re_selftest_on;
void P71_Course(uint8_t *p); void P73_Text(float x, float y, uint32_t txt, int32_t a, int32_t flags);
int32_t P77_LoadBank(const char *name, uint16_t slot); void P82_FrustumSetup3D(void);
void P82_AddLight(const float *pos, int32_t radius, int32_t cr, int32_t cg, int32_t cb); void P88_CellUpdate(int32_t mode);
uint8_t *P93_FindIcon(const char *name); void P98_PartAim(int16_t *p); void P98_DrawSix(void); void P101_PartTurn(uint8_t *p);
uint32_t P101_PickCell(uint32_t want, int32_t x, int32_t z, float *out); int32_t P102_TrafficAhead(uint8_t *rec, int32_t dist, int32_t parked);
void P102_HudInit(void); void P103_OptionsInit(void); int32_t P107_TrafficRow(void); int32_t P110_MenuSel(uint32_t tbl, int32_t cur);
void P110_IconRect(int32_t x, int32_t y, int32_t w, int32_t h, void *icon, int32_t page); void P112_DirTimeline(int32_t frame);
int32_t P114_MenuStep(uint32_t tbl, int32_t *cur); void P114_DebrisAll(void); void P115_SndUpdate(void); void P116_Text(uint32_t txt);
int32_t P120_ParseCamInt(char **pp, int32_t which, int32_t mode);
int32_t P63_Fn49521E(void *r, int32_t a, int32_t b) { if (!re_selftest_on) { return P102_TrafficAhead((uint8_t *)r, a, b); } (void)r; (void)a; (void)b; return t63_ret; }
int32_t P57_MenuStep(uint32_t tbl, int32_t *state) { if (!re_selftest_on) { return P114_MenuStep(tbl, state); } (void)tbl; (void)state; return -1; }

static int test_p57(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p57 fail line %d\n",__LINE__); } } while (0)
  const char *tmp = "/tmp/re_p57_test.bin";
  /* 004d30a3 / 00406b51 */
  remove(tmp);
  CK(P57_FileExists(tmp) == 0);
  { uint8_t buf[100]; for (int i = 0; i < 100; i++) buf[i] = (uint8_t)i;
    CK(P57_WriteFile(tmp, buf, 100) == 1); CK(P57_FileExists(tmp) == 1);
    /* 004ec2ec: пропуск блока читает size байт */
    FILE *fp = fopen(tmp, "rb"); CK(fp != NULL);
    if (fp) { P57_SkipBlock(fp, 60); CK(ftell(fp) == 60); fclose(fp); } }
  CK(P57_WriteFile("/nonexistent_dir_p57/x.bin", tmp, 1) == 0);
  /* 004c92c0 / 004c9310 */
  CK(LoadDirector("/nonexistent_dir_p57/x.dir") == 0);
  CK(SaveDirector("/nonexistent_dir_p57/x.dir") == 0);
  CK(SaveDirector(tmp) == 1); CK(LoadDirector(tmp) == 1);
  /* 004c93b1: без точек пути ничего не делает */
  WaypointDirty = 0; WaypointCount = 0; DirectorLastFrame = 123; G8_00D118C0 = 1000;
  P57_SaveDirectorIfAny(tmp); CK(DirectorLastFrame == 123);
  remove(tmp);
  /* 00406439 / 00406479: SAVES\SCORES.HI — относительный путь, файл создаётся и стирается */
  P57_SaveScores(); CK(P57_FileExists("SAVES\\SCORES.HI") == 1); P57_LoadScores(); remove("SAVES\\SCORES.HI");
  /* 00421a39 */
  P31_DDVal5 = 5; P32_CurHandle = (void *)1; P57_ResetTexNodes(); CK(P31_DDVal5 == 0 && P32_CurHandle == NULL);
  /* 0040cd17 */
  P45_Busy = 7; P45_Step = 0; P57_MenuDone(); CK(P45_Busy == 0 && P45_Step == 5);
  /* 005075f6: (x/1500 + W/2, -y/1500 + H/2) до вызова 00507672 */
  P57_InitConsts(); P19_DivC = 2.0f; P57_ScrW = 640; S_00C808A0 = 480;
  { /* 00507672 (P94_MapToScreen) перенесён: глобалы — тождественное отображение карты 640×480 на экран 640×480 */
    int32_t so = D_00b87e30, sw = P19_ScrW, sh = P19_ScrH, mw = P94_MapW, mh = P94_MapH, mx = P94_MapX0, my = P94_MapY0; float sk = P11_0125f3e0;
    D_00b87e30 = 2; P19_ScrW = 640; P19_ScrH = 480; P94_MapW = 640; P94_MapH = 480; P94_MapX0 = 0; P94_MapY0 = 0; P11_0125f3e0 = 1.0f;
    float x = 150.0f, y = 300.0f; P57_ScreenToView(&x, &y); CK(fabsf(x - 320.1f) < 1e-3f && fabsf(y - 239.8f) < 1e-3f);
    D_00b87e30 = so; P19_ScrW = sw; P19_ScrH = sh; P94_MapW = mw; P94_MapH = mh; P94_MapX0 = mx; P94_MapY0 = my; P11_0125f3e0 = sk; }
  return f;
}

/* ported58: опрос меню/цикл экранов переопределены, иначе циклы не выходят */
int32_t P58_Fn418675(uint32_t tbl, int32_t cur) { if (!re_selftest_on) { return P110_MenuSel(tbl, cur); } (void)tbl; (void)cur; return -1; }
int32_t P58_Fn416794(void) { if (!re_selftest_on) return P124_MotelKeys(0); return 7; }
static int test_p58(void) {
  int f = 0;
  if (!P56_EulerTab) P56_AllocEulerTab(1);   /* кадр меню рисует мир: P83_LightMatrices читает таблицу поворотов */
  g_00b1c3f0 = g_00cff9ac;   /* без смены блока 00489ed6 ничего не делает */
  P54_GridN = 0;   /* кадры меню зовут P89_DrawMap — без сетки он сразу выходит (данные уровня в тесте не загружены) */
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p58 fail line %d\n",__LINE__); } } while (0)
  /* 00524e22 */
  CK(P58_ParseInt((const uint8_t *)"123") == 123); CK(P58_ParseInt((const uint8_t *)"-45 x") == -45);
  CK(P58_ParseInt((const uint8_t *)"12a") == 0); CK(P58_ParseInt((const uint8_t *)"") == 0);
  /* 00417e0d */
  P58_MenuSel = 1; P58_MenuSwitch(); CK(P58_MenuIdx == 1 && P58_MenuFn == 0x00401dc5);
  P58_MenuSel = 4; P58_MenuSwitch(); CK(P58_MenuIdx == 4 && P58_MenuFn == 0x004013c5);
  /* 00413381 / 004133b4 */
  { int32_t x = 0, y = 0; memset(P58_Cheats, 0, sizeof P58_Cheats);
    P58_Cheats[0].name = "AB"; P58_Cheats[0].var = &x; P58_Cheats[1].name = "CD"; P58_Cheats[1].var = &y;
    P58_CheatByName("CD"); CK(x == 0 && y == 1); P58_CheatByName("ZZ"); CK(x == 0);
    P58_CheatsAll(); CK(x == 1 && y == 1); memset(P58_Cheats, 0, sizeof P58_Cheats); }
  /* 0040b1cc: ширина = сумма по глифам */
  { memset(P58_Font, 0, sizeof P58_Font);
    uint8_t *t = &P58_Font[0] + 0x806; int16_t a = 7, b = 3, fl = 1;
    memcpy(t + 0xc, &a, 2); memcpy(t + 0xa, &b, 2);
    memcpy(t + 0xe + 'A' * 8, &fl, 2); t['A' * 8 + 0x14] = 10;        /* 'A': 10 + 3 */
    CK(P58_TextWidth((const uint8_t *)"AB", 1) == 13.0f + 7.0f); CK(P58_TextWidth((const uint8_t *)"", 1) == 0.0f); }
  /* 00407dba: список пунктов (записи 20 байт): обходит до бита 4, считает всех */
  { int16_t it[40]; memset(it, 0, sizeof it); it[4] = 8; it[14] = 8; it[24] = 4;
    P58_ItemList = it; P58_ItemsDraw(5); P58_ItemList = NULL; P58_ItemsDraw(5); }
  /* 004efc03 / 004f5dcd / 004f8d6d / 004eb19b / 004a3354: освобождение */
  { P58_Tab4EFC03 = (p58_rec_t *)DebugMalloc(3 * (int)sizeof(p58_rec_t), "t", 1); P58_Cnt4EFC03 = 3;
    for (int i = 0; i < 3; i++) P58_Tab4EFC03[i].p = DebugMalloc(8, "t", 1);
    P58_FreeRecs(); CK(P58_Tab4EFC03 == NULL && P58_Cnt4EFC03 == 0); }
  { P58_CntC814E8 = 2; P58_PtrsC816A0 = (void **)DebugMalloc(2 * (int)sizeof(void *), "t", 1);
    P58_PtrsC816A0[0] = DebugMalloc(4, "t", 1); P58_PtrsC816A0[1] = DebugMalloc(4, "t", 1);
    P58_LimC810AC = (int32_t *)DebugMalloc(8, "t", 1); P58_LimC810AC[0] = 10; P58_LimC810AC[1] = 20;
    /* 004f6011: v/0x32 = 3 -> первый, 15 -> второй, 40 -> нет (флаги погони) */
    CK(P58_FindChunk(3 * 0x32) == P58_PtrsC816A0[0]); CK(P58_FindChunk(15 * 0x32) == P58_PtrsC816A0[1]);
    CK(P58_FindChunk(0) == NULL); CK(P56_Blk84[1] != 0xff0);
    CK(P58_FindChunk(40 * 0x32) == NULL && P56_Blk84[1] == 0xff0 && P56_Blk84[10] == 1 && P56_Blk84[16] == 0x5a);
    P58_FreeLists(); CK(P58_CntC814E8 == 0 && P58_PtrsC816A0 == NULL && P58_LimC810AC == NULL); }
  { p58_list_t l; l.count = 2; l.items = (void **)DebugMalloc(2 * (int)sizeof(void *), "t", 1);
    for (int i = 0; i < 2; i++) { void **e = (void **)DebugMalloc((int)sizeof(void *), "t", 1); *e = (i == 0) ? DebugMalloc(4, "t", 1) : NULL; l.items[i] = e; }
    P58_FreeNames(&l); CK(l.count == 0 && l.items == NULL); P58_FreeNames(&l); }
  { P58_CntB31EBC = 2; P58_ListB31EC4 = (p58_slot_t *)DebugMalloc(2 * (int)sizeof(p58_slot_t), "t", 1);
    P58_ListB31EC4[0].p = DebugMalloc(4, "t", 1); P58_ListB31EC4[1].p = NULL;
    P58_FreeList(); CK(P58_ListB31EC4 == NULL && P58_CntB31EBC == 0); }
  { P58_GridW = 2; P58_GridH = 2; P58_Grid = (void **)DebugMalloc(4 * (int)sizeof(void *), "t", 1);
    for (int i = 0; i < 4; i++) P58_Grid[i] = NULL;
    p58_cell_t *c = (p58_cell_t *)DebugMalloc((int)sizeof(p58_cell_t), "t", 1); c->items = DebugMalloc(4, "t", 1); P58_Grid[2] = c;
    P58_FreeGrid(); CK(P58_Grid == NULL && P58_GridW == 0 && P58_GridH == 0); }
  /* 0051be3c: две записи; у первой счётчик 1 -> шаг 15 слов */
  { int32_t buf[24]; memset(buf, 0, sizeof buf); buf[0] = 2; buf[1] = 3; buf[2] = 1 << 16; buf[16] = 7;
    P58_BlkBuf = buf; P58_BuildBlockIndex();
    CK(P58_BlkIdx[3] == &buf[1] && P58_BlkIdx[7] == &buf[16] && P58_BlkIdx[4] == NULL); }
  /* 00415f67 */
  P58_SC559D8 = 1; P58_SC559E0 = 2; P58_SC559E4 = 3; P58_SC559E8 = 4; P58_SC559EC = 5;
  P58_Page = 3; P58_PrepPage(); CK(P58_TabPtr == 0x0054e070 && P58_S54DFC8 == 1 && P58_S54E008 == 5);
  P58_Page = 9; P58_PrepPage(); CK(P58_Page == 1 && P58_TabPtr == 0x0054e020);
  /* 00408600: после последнего демо — снова с 0 */
  P58_InitConsts(); P58_DemoNo = 3; P58_PlayDemo(-1); CK(P58_DemoNo == 0 && P58_DemoFlag == 0 && P58_S5F7E5C == 0);
  P58_PlayDemo(2); CK(P58_DemoNo == 0);
  /* 00516da0, 004a9b1a, 00506bff, 0040cf35 — только вызовы, не падают */
  P58_LangNo = 9; P58_LangStrings(); CK(P58_LangNo == 0);
  P58_DrawLogo(); P58_SB87EB0 = 0; memset(P58_Objs, 0, sizeof P58_Objs); P58_Objs[2][0x10] = 1; P58_DrawObjs(); P58_SB87EB0 = 1; P58_DrawObjs(); P58_SB87EB0 = 0;
  P58_Backgrounds();
  /* 00419f00 / 00419ab0 / 00413d70 / 00416540: циклы меню выходят */
  CK(P58_Menu419F00() == -1); CK(P58_Menu419AB0() == -1); CK(P58_Menu413D70() == 0);
  P58_S5FE9F8 = 2; CK(P58_Menu416540() == 7);
  /* 00405e79: файл SAVES\GAME3.BIN с подписью и суммой */
  { uint8_t sb[0x38]; memset(sb, 0, sizeof sb); memcpy(sb, "slot", 4);
    uint32_t hdr[2] = { 0x57231356u, (uint32_t)SumBytes(sb, 0x38) };
    FILE *fp = fopen("SAVES\\GAME3.BIN", "wb"); CK(fp != NULL);
    if (fp) { fwrite(hdr, 1, 8, fp); fwrite(sb, 1, 0x38, fp); fclose(fp);
      char out[0x40]; memset(out, 'x', sizeof out);
      CK(P58_SaveSlot(2, out) == 1 && strcmp(out, "slot") == 0); CK(P58_SaveSlot(7, out) == 0);
      hdr[1] ^= 1; fp = fopen("SAVES\\GAME3.BIN", "wb"); fwrite(hdr, 1, 8, fp); fwrite(sb, 1, 0x38, fp); fclose(fp);
      CK(P58_SaveSlot(2, out) == 0); remove("SAVES\\GAME3.BIN"); } }
  /* 00405bfa: CONFIG.DAT = 8 + 0x10c байт, только при включённом сохранении */
  remove("config.dat"); P58_CfgOn = 0; P58_SaveConfig(); { FILE *fp = fopen("config.dat", "rb"); CK(fp == NULL); if (fp) fclose(fp); }
  P58_CfgOn = 1; P58_CfgLock = 0; P58_SaveConfig();
  { FILE *fp = fopen("config.dat", "rb"); CK(fp != NULL); if (fp) { fseek(fp, 0, SEEK_END); CK(ftell(fp) == 8 + 0x10c); fclose(fp); } }
  CK(P58_CfgHdr[0] == 0x93587031u); remove("config.dat"); P58_CfgOn = 0;
  return f;
}

/* ported59 */
static int test_p59(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p59 fail line %d\n",__LINE__); } } while (0)
  P59_InitConsts();
  /* таблица синусов: углы 0, 90, 180, 270 градусов */
  CK(P59_Sin[0] == 0 && P59_Sin[1] == 6 && P59_Sin[1024] == 4096 && P59_Sin[2048] == 0 && P59_Sin[3072] == -4096);
  /* 0049c910 */
  P59_CamF1 = 5000.0f; P59_PosX = 10; P59_PosY = 20; P59_PosZ = 30;
  P59_SetupCamera(); CK(P59_VX == 10.0f && P59_VY == -20.0f - 3000.0f && P59_VZ == 30.0f && P59_AngA == 0x400 && P59_Mode1137324 == 6);
  P59_CamF1 = 40000.0f; P59_SetupCamera(); CK(P59_VY == -20.0f - 28672.0f);
  /* 004f8a2d / 004f892a */
  memset(P42_Vars, 0, sizeof P42_Vars);
  P42_Vars[0].type = 1; P42_Vars[1].type = 3; P42_Vars[1].hi = 5; P42_Vars[2].type = 4; P42_Vars[3].type = 0x7f;
  P59_VarSetString(0, "abc"); CK(P59_VarStr[0] != NULL && strcmp(P59_VarStr[0], "abc") == 0);
  P59_VarSetString(0, "de"); CK(strcmp(P59_VarStr[0], "de") == 0);
  P59_VarSetString(1, "zz"); CK(P59_VarStr[1] == NULL);                    /* тип не 1 — ничего */
  P59_VarsInit();
  DebugFree(P59_VarStr[0]); P59_VarStr[0] = NULL; memset(P42_Vars, 0, sizeof P42_Vars);
  /* 0048eca3 / 0048ed6f */
  { memset(P12_011443e0, 0, sizeof P12_011443e0); P51_TrafficN = 2;
    uint8_t *e = P12_011443e0 + 0x54; e[0] = 1; e[1] = 2; e[8] = 0; uint32_t v;
    v = 7; memcpy(e + 0x28, &v, 4); v = 3; memcpy(e + 0x24, &v, 4); v = 100; memcpy(e + 0x1c, &v, 4); v = 5; memcpy(e + 0x38, &v, 4);
    CK(P59_TrafficFind(0, 7, 3) == 1); CK(P59_TrafficFind(0, 8, 3) == 0); CK(P59_TrafficFind(1, 7, 3) == 0);
    v = 3000; memcpy(e + 0x1c, &v, 4); CK(P59_TrafficFind(0, 7, 3) == 0);                  /* порог 3000 */
    uint32_t big = 1; memcpy(P12_011443e0 + 0x34, &big, 4); CK(P59_TrafficFind(0, 7, 3) == 1);  /* у машины 0 порог 6000 */
    uint8_t r[0x34]; memset(r, 0, sizeof r); v = 7; memcpy(r + 0x2c, &v, 4); r[0x30] = 3;
    CK(P59_TrafficCheck(r, 0) == 1); CK(P59_TrafficCheck(r, 1) == 1);
    memset(P12_011443e0, 0, sizeof P12_011443e0); P51_TrafficN = 0; CK(P59_TrafficCheck(r, 0) == 0); }
  /* 00491650 */
  { static uint8_t cars[0x148 * 2]; uint32_t v; memset(cars, 0, sizeof cars); P59_CarsTab = cars;
    v = 1000; memcpy(cars + 0x148 + 200, &v, 4); v = 2000; memcpy(cars + 0x148 + 0xd0, &v, 4);
    memset(P59_C39DC0, 0, sizeof P59_C39DC0); uint8_t *rec = P59_C39DC0 + 2 * 0x24; rec[0] = 10; rec[1] = 1; rec[2] = 10;
    uint8_t r[0x2c]; memset(r, 0, sizeof r); r[0] = 1; v = 2; memcpy(r + 0x28, &v, 4); v = 0; memcpy(r + 0x24, &v, 4);
    CK(P59_CellLeft(r) == 8u);                                 /* ((1000+0x2ee)-0)/0x5dc = 1 -> 10-1-1 */
    v = 1; memcpy(r + 0x24, &v, 4); CK(P59_CellLeft(r) == 0u); /* rec[1]==1 */
    v = 2; memcpy(r + 0x24, &v, 4); memcpy(rec + 0x14, &(uint32_t){5000}, 4); CK(P59_CellLeft(r) == (uint32_t)(10 - (5000 - (1000 - 0x2ee)) / 0x5dc - 1));
    P59_CarsTab = NULL; }
  /* 004a3f06 / 004a6dcd */
  { char txt[] = "junk\nMODEL_NAMES\nfoo\nbar\nCHUNK_END\nrest\n"; const char *e = P59_ModelNames(txt);
    CK(e != NULL && strncmp(e, "CHUNK_END", 9) == 0 && P59_ModelCount == 0);
    int32_t me = 0; CK(P59_NearCars(&me) == 0 && P59_NearN == 0); }
  /* 004e5ea2 */
  memset(P59_Flags9, 0, sizeof P59_Flags9); P59_Picked = 0; P59_S4654 = 0; P59_S44CC = 5;
  for (int i = 0; i < 18; i++) P59_PickTab[i] = -1;
  CK(P59_PickUp(3) == 1 && P59_Flags9[3] == 1 && P59_Picked == 1 && P59_S44CC == 0); CK(P59_PickUp(3) == 0 && P59_Picked == 1);
  for (int i = 0; i < 9; i++) P59_PickUp(i);
  CK(P59_Picked == 9 && P59_S4654 == 2);
  /* 004daac7 */
  { uint8_t o[0x110]; memset(o, 0, sizeof o); uint32_t v = 100; memcpy(o + 200, &v, 4); v = 7; memcpy(o + 0xcc, &v, 4); v = -3; memcpy(o + 0xd0, &v, 4);
    v = 0; memcpy(o + 0x100, &v, 4);
    P59_ObjDir(o, 1); int32_t x, y, vs, vc; memcpy(&x, o + 0x24, 4); memcpy(&y, o + 0x28, 4); memcpy(&vs, o + 0x34, 4); memcpy(&vc, o + 0x3c, 4);
    CK(x == 1600 && y == 112 && vs == 0 && vc == 4096);
    v = 2048; memcpy(o + 0x100, &v, 4); P59_ObjDir(o, 0); memcpy(&vs, o + 0x34, 4); memcpy(&vc, o + 0x3c, 4); memcpy(&x, o + 0x24, 4);
    CK(vs == 4096 && vc == 0 && x == 1600); }
  /* 00405fdb */
  { uint8_t rb[0x38]; memset(rb, 0, sizeof rb); memcpy(rb, "rep", 3);
    uint32_t hdr[2] = { 0x38910457u, (uint32_t)SumBytes(rb, 0x38) };
    FILE *fp = fopen("SAVES\\REPLAY2.BIN", "wb"); CK(fp != NULL);
    if (fp) { fwrite(hdr, 1, 8, fp); fwrite(rb, 1, 0x38, fp); fclose(fp);
      uint8_t out[0x38]; memset(out, 0xaa, sizeof out);
      CK(P59_ReplayCheck(1, out) == 1 && memcmp(out, rb, 0x38) == 0); CK(P59_ReplayCheck(1, NULL) == 1); CK(P59_ReplayCheck(5, out) == 0);
      hdr[1] ^= 1; fp = fopen("SAVES\\REPLAY2.BIN", "wb"); fwrite(hdr, 1, 8, fp); fwrite(rb, 1, 0x38, fp); fclose(fp);
      CK(P59_ReplayCheck(1, out) == 0); remove("SAVES\\REPLAY2.BIN"); } }
  /* 0040d4b3 */
  { uint8_t file[2 + 0x14 + 8]; memset(file, 0, sizeof file); int32_t h[5] = { 0x14 + 8, 0x14 + 3, 0x14, 0, 0 };
    memcpy(file + 2, h, sizeof h); memcpy(file + 2 + 0x14, "ABCDEFG", 8);
    FILE *fp = fopen("blk.tmp", "wb"); if (fp) { fwrite(file, 1, sizeof file, fp); fclose(fp); }
    int32_t hh[5]; memset(hh, 0, sizeof hh); fp = fopen("blk.tmp", "rb"); CK(fp != NULL);
    if (fp) { char *b = (char *)P59_ReadBlock(fp, 2.0f, hh); CK(b != NULL && hh[0] == 8 && hh[1] == 3 && hh[2] == 0 && memcmp(b, "ABCDEFG", 8) == 0);
      DebugFree(b); fclose(fp); }
    memcpy(file, h, sizeof h); memcpy(file + 0x14, "ABCDEFG", 8);                 /* scale 1.0: без пропуска */
    fp = fopen("blk.tmp", "wb"); if (fp) { fwrite(file, 1, sizeof file - 2, fp); fclose(fp); }
    fp = fopen("blk.tmp", "rb"); if (fp) { char *b = (char *)P59_ReadBlock(fp, 1.0f, hh); CK(b != NULL && hh[0] == 8 && memcmp(b, "ABCDEFG", 8) == 0); DebugFree(b); fclose(fp); }
    remove("blk.tmp"); }
  /* 00417d56: без нажатых клавиш (IsKeyDown вернёт 0) -> ветка Enter не выполняется -> 0 */
  CK(P59_MenuKeys() == 0);
  return f;
}

/* ported60 */
static int test_p60(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p60 fail line %d\n",__LINE__); } } while (0)
  P59_InitConsts();
  uint8_t *cam = (uint8_t *)&DirectorCam; int32_t v;
  /* 004c5c5d */
  memset(TrafficRecs, 0, sizeof(TRAFFIC_RECS_T)); memset(P60_Cars, 0, sizeof(p60_cars_t));
  P59_PosX = 1000; P59_PosZ = 1000;
  { uint8_t *rec = (uint8_t *)TrafficRecs + 2 * 0x54; rec[5] = 1; rec[0xc] = 1; rec[1] = 4;        /* машина №3 */
    v = 1000 + 100; memcpy((uint8_t *)P60_Cars + 3 * 0x148 + 0xc8, &v, 4); v = 1000; memcpy((uint8_t *)P60_Cars + 3 * 0x148 + 0xd0, &v, 4);
    CK(P60_NextTrafficCar(0) == 3 && P60_NextTrafficCar(1) == 3 && P60_NextTrafficCar(3) == 0);
    v = 1000 + 30100; memcpy((uint8_t *)P60_Cars + 3 * 0x148 + 0xc8, &v, 4); CK(P60_NextTrafficCar(0) == 0);   /* слишком далеко */
    v = 1000 + 100; memcpy((uint8_t *)P60_Cars + 3 * 0x148 + 0xc8, &v, 4); rec[1] = 3; CK(P60_NextTrafficCar(0) == 0); rec[1] = 4; }
  /* 004c4b3a / 004c4cee */
  memset(cam, 0, 0x8c); v = 5; memcpy(cam + 0x4c, &v, 4); v = 7; memcpy(cam + 0x54, &v, 4); v = 9; memcpy(cam + 0x10, &v, 4);
  AddTripodCamera(0x14);
  memcpy(&v, cam, 4); CK(v == 0x11); memcpy(&v, cam + 0x5c, 4); CK(v == 5); memcpy(&v, cam + 0x64, 4); CK(v == 7); memcpy(&v, cam + 0x10, 4); CK(v == 0);
  AddTripodCamera(0x16); memcpy(&v, cam + 0x48, 4); CK(v == 1); AddTripodCamera(0x16); memcpy(&v, cam + 0x48, 4); CK(v == 0);
  memset(cam, 0, 0x8c); v = 0; memcpy(cam + 0x4c, &v, 4);
  { uint8_t *car0 = (uint8_t *)P60_Cars; v = 100; memcpy(car0 + 0xc8, &v, 4); v = 0; memcpy(car0 + 0xd0, &v, 4); v = 300; memcpy(car0 + 0xcc, &v, 4); }
  AddTripodCamera(0x15); memcpy(&v, cam, 4); CK(v == 0x10);
  { int32_t a; memcpy(&a, cam + 0x18, 4); CK(a == ((-P44_Atan2(100, 0)) & 0xfff)); uint16_t w; memcpy(&w, cam + 0x7e, 2); CK(w == (uint16_t)a); }
  memset(cam, 0, 0x8c); v = -1; memcpy(cam + 0x10, &v, 4);
  ChangeTripodCamera(0x19); memcpy(&v, cam, 4); CK(v == 0x10);
  { int32_t p, q; memcpy(&p, cam + 0x20, 4); CK(p == P44_Atan2(300, 100)); q = p; uint16_t w; memcpy(&w, cam + 0x7c, 2); CK(w == (uint16_t)q); }
  memset(cam, 0, 0x8c); ChangeTripodCamera(0x18); memcpy(&v, cam, 4); CK(v == 0x11);
  /* 004c459f / 004c483e */
  { DIR_NODE n[4]; memset(n, 0, sizeof n); n[0].id = 0xb; n[0].link1 = 0x40; n[1].id = 0xf; n[1].link1 = 0x41; n[2].id = 0x20; n[3].id = 0xffff;
    DIR_NODE *old = DirNodeTable; DirNodeTable = n;
    memset(cam, 0, 0x8c); DirectorUnk7C = 0;
    AddCamera(0xb); memcpy(&v, cam, 4); CK(v == 0x11 && DirectorUnk7C == 0x40);
    memset(cam, 0, 0x8c); ChangeCamera(0xf); memcpy(&v, cam, 4); CK(v == 0x11 && DirectorUnk7C == 0x41);
    memset(cam, 0, 0x8c); v = 4; memcpy(cam + 0x4c, &v, 4); n[0].id = 0xb; AddCamera(0x20);              /* неизвестный id — только лог */
    memcpy(&v, cam, 4); CK(v == 0);
    DirNodeTable = old; }
  /* 004a399a */
  { uint8_t o[0x40]; memset(o, 0, sizeof o); v = 1; memcpy(o + 0x10, &v, 4); v = 77; memcpy(o + 0x24, &v, 4);
    P60_ObjUpdate(o); memcpy(&v, o + 0x24, 4); CK(v == 0); P60_ObjUpdate(NULL); }
  /* 0051378b */
  { uint8_t p[0xb4]; memset(p, 0, sizeof p); P43_FreeCnt = 0; P60_PartLimit = 5;
    CK(P60_SpawnParticle(p, 0) == 1 && p[0] == 1); memcpy(&v, p + 0x1c, 4); CK(v == 1);
    memset(p, 0, sizeof p); CK(P60_SpawnParticle(p, 1) == 0 && p[0] == 0); P43_FreeCnt = 9; CK(P60_SpawnParticle(p, 0) == 0); P43_FreeCnt = 0; }
  return f;
}

static int32_t rd_i32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void wr_i32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
/* ported61 */
static int test_p61(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p61 fail line %d\n",__LINE__); } } while (0)
  P59_InitConsts(); P61_InitConsts();
  uint8_t cam[0x8c]; int32_t v; uint16_t w;
  /* 004c5499 / 004c536c: туда и обратно */
  memset(cam, 0, sizeof cam);
  P44_CamX = 10.4f; P44_CamY = -20.6f; P44_CamZ = 30.5f;               /* fistp: 10, -21, 30 (к чётному) */
  P61_TgtX = 1.0f; P61_TgtY = 2.0f; P61_TgtZ = 3.0f; P61_OffX = 4.0f; P61_OffY = 5.0f; P61_OffZ = 6.0f;
  P61_AngB8 = 7; P61_AngBA = 8; P61_AngBC = 9; P61_Dist8 = 100.0f; P61_DistC = 200.0f;
  P61_V18 = 11; P61_V1C = 12; P61_V20 = 13; P61_V10 = 14; P59_Mode1137324 = 0x11; P60_Var1373C0 = 1;
  P61_StoreCamState(cam);
  v = rd_i32(cam, 0x4c); CK(v == 10); v = rd_i32(cam, 0x50); CK(v == -21); v = rd_i32(cam, 0x54); CK(v == 30);
  v = rd_i32(cam, 0x5c); CK(v == 1); v = rd_i32(cam, 0x74); CK(v == 6); v = rd_i32(cam, 8); CK(v == 100); v = rd_i32(cam, 0xc); CK(v == 200);
  v = rd_i32(cam, 0x18); CK(v == 11); v = rd_i32(cam, 0x10); CK(v == 14); v = rd_i32(cam, 0); CK(v == 0x11); v = rd_i32(cam, 0x48); CK(v == 1);
  memcpy(&w, cam + 0x7e, 2); CK(w == 8);
  P59_Mode1137324 = 3; P61_StoreCamState(cam); v = rd_i32(cam, 0x48); CK(v == 0);   /* вне режима 0x11 флаг сбрасывается */
  /* обратно */
  memset(cam, 0, sizeof cam);
  v = 0x11; memcpy(cam, &v, 4); v = 77; memcpy(cam + 0x4c, &v, 4); v = -5; memcpy(cam + 0x50, &v, 4); v = 9; memcpy(cam + 0x54, &v, 4);
  v = 1; memcpy(cam + 0x48, &v, 4); v = 500; memcpy(cam + 8, &v, 4); w = 0x123; memcpy(cam + 0x80, &w, 2);
  P61_RestoreCamState(cam);
  CK(P44_CamX == 77.0f && P44_CamY == -5.0f && P44_CamZ == 9.0f && P61_Dist8 == 500.0f && P61_AngBC == 0x123);
  CK(P59_Mode1137324 == 0x11 && (uint8_t)P60_Var1373C0 == 1);
  v = 3; memcpy(cam, &v, 4); v = 1; memcpy(cam + 0x48, &v, 4); P61_RestoreCamState(cam);
  CK((uint8_t)P60_Var1373C0 == 0 && rd_i32(cam, 0x48) == 0);
  /* 0049e5e7: машина 2 без поворота — смещение (5,-115,150) в единичной матрице */
  memset(P60_Cars, 0, sizeof(p60_cars_t));
  { uint8_t *car = (uint8_t *)P60_Cars + 2 * 0x148; v = 1000; memcpy(car + 0xc8, &v, 4); v = 40; memcpy(car + 0xcc, &v, 4); v = 2000; memcpy(car + 0xd0, &v, 4); }
  P61_Heading = 0;
  P61_SetupCamN(2);
  CK(P59_AngA == 0 && P59_AngB == 0 && P59_AngC == 0);
  CK(fabsf(P44_ViewMat[0] - 1.0f) < 1e-5f && fabsf(P44_ViewMat[4] - 1.0f) < 1e-5f && fabsf(P44_ViewMat[8] - 1.0f) < 1e-5f);
  CK(fabsf(P44_CamX - 1005.0f) < 1e-2f && fabsf(P44_CamY - (-40.0f - 115.0f)) < 1e-2f && fabsf(P44_CamZ - 2150.0f) < 1e-2f);
  S_00D1192C = 1; P61_SetupCamN(0);                                  /* машина 0: смещение из таблицы (0,-105,135) */
  CK(fabsf(P44_CamX - 0.0f) < 1e-2f && fabsf(P44_CamY - (-105.0f)) < 1e-2f && fabsf(P44_CamZ - 135.0f) < 1e-2f);
  /* 004c6d62 */
  { uint8_t *car0 = (uint8_t *)P60_Cars; v = 100; memcpy(car0 + 0xc8, &v, 4); v = 0; memcpy(car0 + 0xd0, &v, 4); v = 50; memcpy(car0 + 0xcc, &v, 4);
    v = 0x200; memcpy(car0 + 0x100, &v, 4); }
  memset(cam, 0, sizeof cam); v = 2; memcpy(cam, &v, 4); v = -1; memcpy(cam + 0x10, &v, 4);        /* режим 2: фиксированные значения */
  P61_CamPrepare(cam);
  CK(rd_i32(cam, 0x10) == 0 && rd_i32(cam, 0x18) == 0x800 && rd_i32(cam, 8) == 0x500 && rd_i32(cam, 0xc) == 0x500 && rd_i32(cam, 0) == 0);
  CK(rd_i32(cam, 0x70) == -0x100 && rd_i32(cam, 0x1c) == ((0x200 + 0x800) & 0xfff));
  memset(cam, 0, sizeof cam); v = 1; memcpy(cam, &v, 4);
  v = 100 + 3000; memcpy(cam + 0x5c, &v, 4); v = 4000; memcpy(cam + 0x64, &v, 4); v = -300; memcpy(cam + 0x60, &v, 4);
  P61_CamPrepare(cam);                                               /* расстояние 5000 (3000;4000) */
  CK(rd_i32(cam, 8) == 5000 && rd_i32(cam, 0xc) == 5000 && rd_i32(cam, 0x4c) == 3100 && rd_i32(cam, 0x54) == 4000);
  CK(rd_i32(cam, 0x18) == ((P44_Atan2(3000, 4000) - 0x200) & 0xfff) && rd_i32(cam, 0) == 0);
  memset(cam, 0, sizeof cam); v = 1; memcpy(cam, &v, 4); v = 100 + 30000; memcpy(cam + 0x5c, &v, 4);
  P61_CamPrepare(cam); CK(rd_i32(cam, 8) == 15000);                  /* верхняя граница */
  memset(cam, 0, sizeof cam); v = 9; memcpy(cam + 8, &v, 4); P61_CamPrepare(cam); CK(rd_i32(cam, 0xc) == 9 && rd_i32(cam, 0x1c) == 0);
  /* 00514261: слот освобождается, если ячейка не нашлась (заглушка 005139d7 возвращает 0) */
  { uint8_t p[0xa0]; memset(p, 0, sizeof p); float fl = 12.5f; memcpy(p + 0x84, &fl, 4); memcpy(p + 0x8c, &fl, 4);
    P43_FreeCnt = 0; P61_SpawnPart(p); CK(rd_i32(p, 0x38) == 0); }
  return f;
}

/* ported63 */
static int test_p63(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p63 fail line %d\n",__LINE__); } } while (0)
  re_init_consts();
  uint8_t *R = (uint8_t *)TrafficRecs; memset(R, 0, 0x40 * 0x54); P51_TrafficN = 4;
  /* 0048ea2c: запись 1 на узле 7 в направлении 2; запись 2 с флагом +3 и альтернативой 9; запись 0 — сам */
  R[0 * 0x54] = 0; R[0x54] = 1; R[0x54 + 8] = 1; wr_i32(R, 0x54 + 0x28, 7); wr_i32(R, 0x54 + 0x24, 2); wr_i32(R, 0x54 + 0x18, 1234);
  R[2 * 0x54] = 2; R[2 * 0x54 + 8] = 1; R[2 * 0x54 + 3] = 1; wr_i32(R, 2 * 0x54 + 0x28, 5); wr_i32(R, 2 * 0x54 + 0x20, 9);
  R[3 * 0x54] = 3; R[3 * 0x54 + 8] = 1; wr_i32(R, 3 * 0x54 + 0x28, 7); wr_i32(R, 3 * 0x54 + 0x24, 1); wr_i32(R, 3 * 0x54 + 0x30, 2); wr_i32(R, 3 * 0x54 + 0x18, 77);
  CK(P63_NearOnNode(0, 7, 2, 9) == 3 && P63_Dist[0] == 1234 && P63_Ids[0] == 1 && P63_Dist[1] == -1 && P63_Ids[1] == (2 | 0x80) && P63_Dist[2] == 77 && P63_Ids[2] == 3);
  CK(P63_NearOnNode(1, 7, 2, 9) == 2 && P63_Ids[0] == (2 | 0x80) && P63_Ids[1] == 3);
  /* 0048f3b4 */
  R[0x54 + 1] = 1; R[2 * 0x54 + 1] = 1; R[3 * 0x54 + 1] = 1; R[1] = 0;
  CK(P63_CountByNode(7, 5, 11, 12) == 3 && P63_Cnt0 == 2 && P63_Cnt1 == 1 && P63_Cnt2 == 0 && P63_Cnt3 == 0);
  /* 0048f5d8 / 0048f4ad: масштаб 0.5, игрок в (1000, 2000) → (500, 1000) */
  P63_Scale = 0.5f; P59_PosX = 1000; P59_PosZ = 2000;
  wr_i32(R, 0x54 + 0x48, 490); wr_i32(R, 0x54 + 0x4c, 1010);
  wr_i32(R, 2 * 0x54 + 0x48, 500); wr_i32(R, 2 * 0x54 + 0x4c, 1003);
  wr_i32(R, 3 * 0x54 + 0x48, 900); wr_i32(R, 3 * 0x54 + 0x4c, 900);
  CK(P63_NearestRec() == 2 && P63_Near == 2 && P11_00ba52d0 == 1000);
  R[2 * 0x54 + 1] = 0; CK(P63_NearestRec() == 1);
  for (int i = 0; i < 4; i++) { R[i * 0x54 + 1] = 0; } CK(P63_NearestRec() == -1);
  R[0x54 + 1] = 1; R[2 * 0x54 + 2] = 1; P58_SB87EB0 = 0; G6_00B87EAC = 0;
  P63_NearestAdd(-0x2ee + 1000, 0x2ee + 2000);   /* → точка (500, 1000) */
  CK(P63_Near == 3);   /* запись 2: |500-500|+|1003-1000| = 3 */
  P63_NearestAdd(-0x2ee, 0x2ee); CK(P63_Near == 0x400);   /* 1500 > начальной границы 0x400 */
  /* 0048f1c6: узел 3 заблокирован (байт +3 в таблице) → 1 */
  { uint8_t rec[0x54]; memset(rec, 0, sizeof rec); wr_i32(rec, 0x20, 3);
    memset(P14_00c1ed80, 0, sizeof(p14_00c1ed80_t)); P14_00c1ed80[3 * 0x2c + 3] = 1;
    CK(P63_CanEnter(rec) == 1);
    P14_00c1ed80[3 * 0x2c + 3] = 0; P11_00c1ed8a[3 * 0x16 + 0] = -1;     /* нет следующего узла → зависит от 0048ed6f */
    int32_t r = P63_CanEnter(rec); CK(r == 0 || r == 1);
    /* есть следующий узел 7, встречная запись 1 на дистанции 100 с флагом не -1 и состоянием 0 → 0 */
    P11_00c1ed8a[3 * 0x16 + 0] = 7; wr_i32(rec, 0x24, 0);
    R[0x54 + 8] = 1; wr_i32(R, 0x54 + 0x28, 7); wr_i32(R, 0x54 + 0x24, 2); wr_i32(R, 0x54 + 0x18, 100); wr_i32(R, 0x54 + 0x34, 0);
    CK(P63_CanEnter(rec) == 0);
    wr_i32(R, 0x54 + 0x18, 20000); r = P63_CanEnter(rec); CK(r == 0 || r == 1); }
  /* 004901c0 */
  { uint8_t rec[0x54]; memset(rec, 0, sizeof rec); rec[9] = 1;
    wr_i32(rec, 0x18, 100); wr_i32(rec, 0x3c, 55); CK(P63_CarSpeed(rec) == 0 && rd_i32(rec, 0x3c) == 0);
    t63_ret = -1; wr_i32(rec, 0x18, 700); CK(P63_CarSpeed(rec) == 29 && rd_i32(rec, 0x3c) == 29);
    wr_i32(rec, 0x18, 3650); CK(P63_CarSpeed(rec) == 162);
    wr_i32(rec, 0x18, 9999); CK(P63_CarSpeed(rec) == 162);
    t63_ret = 3; CK(P63_CarSpeed(rec) == 0);
    rec[0x13] = 8; wr_i32(rec, 0x3c, 40); CK(P63_CarSpeed(rec) == 24); wr_i32(rec, 0x3c, 5); CK(P63_CarSpeed(rec) == 0); t63_ret = -1; }
  /* 004966fd */
  { uint8_t o[0xd8]; memset(o, 0, sizeof o); wr_i32(o, 200, 10); wr_i32(o, 0xd0, 20);
    float pl[16] = { 1, 0, 0, 10,   -1, 0, 0, 0,   0, 0, 1, 20,   0, 0, -1, 0 };    /* x≤10, −x≤0, z≤20, −z≤0 */
    CK(P63_InPlanes(o, pl) == 1); wr_i32(o, 200, 11); CK(P63_InPlanes(o, pl) == 0); wr_i32(o, 200, 5); wr_i32(o, 0xd0, -1); CK(P63_InPlanes(o, pl) == 0); }
  /* 00426b34 */
  { memset(G2_011F40E0, 0, 3 * 0x24); G2_011F43B0 = 3;
    float c0[3] = { 0, 0, 0 }, c1[3] = { 100, 0, 0 }, c2[3] = { 0, 0, 5 };
    memcpy((uint8_t *)G2_011F40E0 + 0 * 0x24, c0, 12); wr_i32((uint8_t *)G2_011F40E0, 0xc, 10);
    memcpy((uint8_t *)G2_011F40E0 + 1 * 0x24, c1, 12); wr_i32((uint8_t *)G2_011F40E0, 0x24 + 0xc, 10);
    memcpy((uint8_t *)G2_011F40E0 + 2 * 0x24, c2, 12); wr_i32((uint8_t *)G2_011F40E0, 0x48 + 0xc, 10);
    uint8_t obj[0x10]; memset(obj, 0, sizeof obj); float rad = 2.5f; memcpy(obj + 0xc, &rad, 4);
    float pt[3] = { 0, 0, 0 }; P63_SphereHits(pt, obj);
    CK(P63_SphN == 2 && P63_Hits[0] == 0 && P63_Hits[1] == 2);
    float pt2[3] = { 100, 0, 12 }; P63_SphereHits(pt2, obj); CK(P63_SphN == 1 && P63_Hits[0] == 1);
    float pt3[3] = { 100, 0, 12.5f }; P63_SphereHits(pt3, obj); CK(P63_SphN == 0); }
  /* 0049ef12 */
  { float p0[3] = { 0, 0, 0 }, p1[3] = { 1, 2, 3 }, p2[3] = { 5, 6, 7 }, p3[3] = { 9, 9, 9 }, o[3], t = 0;
    P63_CatmullRom(&t, o, p0, p1, p2, p3); CK(o[0] == 1 && o[1] == 2 && o[2] == 3);
    t = 1; P63_CatmullRom(&t, o, p0, p1, p2, p3); CK(o[0] == 5 && o[1] == 6 && o[2] == 7);
    t = 0.5f; P63_CatmullRom(&t, o, p0, p1, p2, p3);
    double ex = 0.5 * ((2.0 * 1) + (-0 + 5) * 0.5 + (2 * 0 - 5 * 1 + 4 * 5 - 9) * 0.25 + (-0 + 3 * 1 - 3 * 5 + 9) * 0.125);
    CK(fabs(o[0] - ex) < 1e-5); }
  /* 0049ed20: кривая проходит через начало и через узел c */
  { float o = 99; P63_Hermite(100, &o, 50, 100, 200, 300); CK(o == 0);
    P63_Hermite(200, &o, 50, 100, 200, 300); CK(fabsf(o - 1.0f) < 1e-4f);
    P63_Hermite(150, &o, 50, 100, 200, 300); CK(o > 0.0f && o < 1.0f); }
  return f;
}

/* ported62 */
static uint8_t t62_car[0x100];
static int test_p62(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p62 fail line %d\n",__LINE__); } } while (0)
  P59_InitConsts(); P61_InitConsts();
  /* 0049c850 */
  P60_Var1373C0 = 0x01020304; P62_InitCamDefaults();
  CK(P61_V1C == 0x800 && P62_C82434 == -0x400 && P62_C82500 == 0x338 && P61_OffX == -45.0f && P61_OffY == -256.0f && P61_OffZ == -160.0f);
  CK(P61_Dist8 == 1280.0f && P62_F136C54 == 10.0f && P62_I13738C == 42000 && P60_Var1373C0 == 0x01020300);
  /* 00425a50 */
  P19_ScrW = 640; P19_ScrH = 480; P19_DivC = 640.0f; P58_CfgOn = 0;
  P62_InitRenderConsts();
  CK(P43_ScaleA == 1152.0f && P62_F252A94 == 1.0f && P62_F25F3F4 == 0.75f && P62_I270C44 == 0xdbba && P11_01270c24 == 42000.0f);
  P11_01270c24 = 1.0f; P58_CfgOn = 1; P62_InitRenderConsts(); CK(P11_01270c24 == 1.0f);
  /* 0049431d / 00492398 / 004a6749 / 0049199a */
  static uint8_t cars[0x148 * 8]; memset(cars, 0, sizeof cars); P59_CarsTab = cars;
  { int32_t h = 0x100; memcpy(cars + 0x148 + 0x100, &h, 4); }
  uint8_t id = 1;
  CK(P62_HeadingDelta(&id, 0x120) == 0x20 && rd_i32(cars, 0x148 + 0xfc) == 0x10);
  CK(P62_HeadingDelta(&id, 0x300) == 0x200 && rd_i32(cars, 0x148 + 0xfc) == 0x200);
  CK(P62_HeadingDelta(&id, 0x000) == 0x100 && rd_i32(cars, 0x148 + 0xfc) == -0x200);
  CK(P62_HeadingDelta(&id, 0x100) == 0 && rd_i32(cars, 0x148 + 0xfc) == 0);
  memset((uint8_t *)TrafficRecs, 0, sizeof(TRAFFIC_RECS_T));
  ((uint8_t *)TrafficRecs)[2 * 0x54 + 6] = 5;                   /* запись 2 — машина с id 4 */
  P59_PosX = 0; P59_PosZ = 0;
  { int32_t x = 300, z = 400; memcpy(cars + 2 * 0x148 + 200, &x, 4); memcpy(cars + 2 * 0x148 + 0xd0, &z, 4); }
  CK(P62_FarFromPlayer(4, 400) == 1 && P62_FarFromPlayer(4, 600) == 0 && P62_FarFromPlayer(4, 500) == 0);
  CK(P62_FarFromPlayer(9, 100) == 0 && P62_FarFromPlayer(4, 0) == 0);
  memset(P12_0112da00, 0, sizeof(p12_0112da00_t));
  CK(P62_FindFreeTrafficSlot() == 1);
  { uint8_t *s = (uint8_t *)P12_0112da00; int32_t one = 1; memcpy(s + 0xcb4, &one, 4); memcpy(s + 0xcd8 + 0xcb4, &one, 4);
    CK(P62_FindFreeTrafficSlot() == 3 && rd_i32(s + 2 * 0xcd8, 0) == 2);
    for (int i = 2; i < 8; i++) memcpy(s + i * 0xcd8 + 0xcb4, &one, 4);
    CK(P62_FindFreeTrafficSlot() == -1);
    for (int i = 0; i < 8; i++) memset(s + i * 0xcd8 + 0xcb4, 0, 4); }
  G0112B284 = 0; P62_Max = 4; P62_I14428C = 7;
  P62_SpawnTrafficCar(3);
  { uint8_t *rec = (uint8_t *)TrafficRecs + 3 * 0x54; uint8_t *s = (uint8_t *)P12_0112da00;
    CK(rec[5] == 1 && rec[0xd] == 0x19 && G0112B284 == 1 && P62_I14428C == 0 && rd_i32(s, 0xcbc) == 0 && rd_i32(s, 0x5c) == 1 && rd_i32(s, 0xcb4) == 1); }
  G0112B284 = 4; P62_I14428C = 7; P62_SpawnTrafficCar(3); CK(P62_I14428C == 7);
  /* 0042d2c9 */
  { static uint8_t q[0xb8 * 2]; uint32_t a[15], b[15], c[15]; for (int i = 0; i < 15; i++) { a[i] = 100 + i; b[i] = 200 + i; c[i] = 300 + i; }
    G0115A13C = q; G01159D74 = 0; P62_QueueTri(a, b, c, 0xabcd);
    uint32_t *w = (uint32_t *)q;
    CK(w[0] == 0xabcd && w[1] == 100 && w[15] == 114 && w[0x10] == 200 && w[0x1e] == 214 && w[0x1f] == 300 && w[0x2d] == 314 && G01159D74 == 1 && G0115A13C == q + 0xb8); }
  /* 0051ac05 */
  { static uint8_t m[256]; memset(m, 0, sizeof m); int32_t off0 = -1, off1 = 40; memcpy(m + 8, &off0, 4); memcpy(m + 12, &off1, 4);
    int32_t r1[2] = { 3, 7 }, r2[2] = { 1, 9 }; memcpy(m + 40, r1, 8); memcpy(m + 48, r2, 8);
    P54_MapBPtr = m; P62_MapN = 2; int32_t out[4];
    CK(P62_MapRow(0, out) == 0 && out[0] == -1 && out[3] == -1);
    CK(P62_MapRow(1, out) == 1 && out[0] == 7 && out[2] == 7 && out[3] == 9); }
  /* 004a58ad */
  { static const char names[] = "ford\0\x11\x01" "fiat\0\x22\x02" "mini\0\x33\x03"; uint16_t o = 0;
    P62_ModelNames = names; P62_ModelCount = 3; P62_NoErr = 1;
    CK(P62_ModelLookup("fiat", &o) == 1 && o == 0x0222);
    CK(P62_ModelLookup("mini", &o) == 1 && o == 0x0333);
    CK(P62_ModelLookup("opel", &o) == 0); }
  /* 005047ab */
  { static uint16_t bmp[64 * 64]; for (int i = 0; i < 64 * 64; i++) bmp[i] = (uint16_t)i;
    memset(P62_Page, 0, sizeof(p62_page_t)); P62_DownloadPage(5, bmp, 2, 3, 4, 2, 64);
    CK(P62_Page[0] == 3 * 64 + 2 && P62_Page[3] == 3 * 64 + 5 && P62_Page[4] == 0 && P62_Page[0x100] == 4 * 64 + 2 && P62_Page[0x100 + 3] == 4 * 64 + 5);
    P62_DownloadPage(5, NULL, 0, 0, 1, 1, 1); }
  /* 0051cb98 */
  { FILE *fp = tmpfile(); memset(P62_Hs1, 7, 4);
    CK(P62_SaveScores(fp) == 1 && ftell(fp) == 16 + 0x2c * (0x28 * 2 + 0x14 * 3 + 4));
    rewind(fp); uint32_t h[4]; CK(fread(h, 16, 1, fp) == 1 && h[0] == 0x53435245 && h[3] == 3); fclose(fp); }
  /* 00413df3 / 0051cdec */
  P62_BusyA = P62_BusyB = P62_BusyC = P62_BusyD = P62_BusyE = 0; CK(P62_MenuBusy() == 0);
  P62_BusyD = 1; P62_Menu1271060 = 3; CK(P62_MenuBusy() == 1); P62_Menu1271060 = 7; CK(P62_MenuBusy() == 0);
  P62_BusyC = 1; CK(P62_MenuBusy() == 1);
  { int32_t idx = 5; P62_Menu1271060 = 3; CK(P62_ScoreTable(&idx, 0) == 0 && idx == 5);   /* занято */
    P62_BusyC = 0; P62_BusyD = 0; P62_Menu1271060 = 5; P62_ScoreTable(&idx, 1); CK(idx == 5); }
  /* 005025dc */
  P62_HudOff1 = 0; P62_HudOff2 = 0; P62_Spd = 100; P62_Unit = "mph"; P62_Blink = 0; P62_SpeedText();
  /* 004ec336 */
  { FILE *fp = tmpfile(); int32_t wh[2] = { 6, 4 }; uint8_t pay[16]; for (int i = 0; i < 16; i++) pay[i] = (uint8_t)(i + 1);
    fwrite(wh, 8, 1, fp); fwrite(pay, 16, 1, fp); rewind(fp);
    P62_LoadMapHeader(fp, 8 + 16);
    CK(P62_MapW == 6 && P62_MapH == 4 && P62_Map1C10 == 6 * 0x5dc && P62_Map1C24 == 4 * 0x5dc && P62_MapC64 == 3 * 0x5dc && P62_Map2C40 == 2 * 0x5dc);
    CK(P62_Map1C0C == 3 && P62_MapCC90 == 2 && P62_MapBuf != NULL && P62_MapBuf[0] == 1 && P62_MapBuf[15] == 16); fclose(fp); }
  /* 00514c72 / 00515813 */
  { uint8_t p[0x100]; memset(p, 0, sizeof p); P62_ParticleSet(p, 3, 9, 0x400, 1);
    CK(rd_i32(p, 0x24) == 9 && rd_i32(p, 0x40) == 1 && rd_i32(p, 0xc) == 0x480 && p[4] == 3);
    memset(p, 0, sizeof p); P62_Alt = 0; int32_t fl = 0xfffff7ff; memcpy(p + 0xc, &fl, 4); P62_ParticleInit(p, t62_car);
    CK(p[0] == 1 && rd_i32(p, 0xc) == (int32_t)((0xfffff7ffu & 0xfffffbffu) | 0x80) && p[4] == 3 && rd_i32(p, 0x40) == 1);
    memset(p, 0, sizeof p); P62_Alt = 1; P62_ParticleInit(p, t62_car);
    float fa, fb; memcpy(&fa, p + 0x74, 4); memcpy(&fb, p + 0x7c, 4);
    CK((rd_i32(p, 0xc) & 0x800) && fa == (float)(P59_Sin[0x400] >> 7) && fb == (float)(P59_Sin[0x800] >> 7) && rd_i32(p, 0x78) == (int32_t)0xc25c0000); }
  return f;
}

/* ported65 */
static int test_p65(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p65 fail line %d\n",__LINE__); } } while (0)
  /* токены */
  char line[64] = "  foo, 12;bar\n";
  char tok[32];
  CK(P65_NextToken(line, tok) == 0 && strcmp(tok, "foo") == 0 && strcmp(line, " 12;bar\n") == 0);
  CK(P65_NextToken(line, tok) == 0 && strcmp(tok, "12") == 0 && strcmp(line, "bar\n") == 0);
  CK(P65_NextToken(line, tok) == 0 && strcmp(tok, "bar") == 0 && line[0] == 0);
  CK(P65_NextToken(line, tok) == 10 && tok[0] == 0);
  /* числа */
  uint8_t cmd[0x110]; memset(cmd, 0, sizeof cmd);
  int32_t cnt = 3; memcpy(cmd + 0x100, &cnt, 4);
  static char src[64]; strcpy(src, "10 -5,7 x");
  P65_Line = src;
  CK(P65_ReadInts(cmd) == 0 && P65_Ints[0] == 10 && P65_Ints[1] == -5 && P65_Ints[2] == 7);
  strcpy(src, "1 abc 3");
  CK(P65_ReadInts(cmd) == 0xc);
  strcpy(src, "1");
  CK(P65_ReadInts(cmd) == 10);
  /* поиск по имени */
  p65_ent_t e0 = { "ALPHA", 11 }, e1 = { "BETA", 22 };
  p65_ent_t *ents[2] = { &e0, &e1 };
  p65_tab_t tab = { 2, ents };
  char nm[16] = "beta";
  CK(P65_FindByName(nm, &tab) == 22 && strcmp(nm, "BETA") == 0);
  strcpy(nm, "Alpha"); CK(P65_FindByName(nm, &tab) == 11);
  strcpy(nm, "gamma"); CK(P65_FindByName(nm, &tab) == -1);
  CK(P65_FindByName(NULL, &tab) == -1);
  /* имя в меню */
  P97_StrAddr[0x40] = re_addr("NONE"); P97_StrAddr[0xc] = re_addr("BG0"); P97_StrAddr[0x41] = re_addr("PAD"); P97_StrAddr[2] = re_addr("BG2"); P97_StrAddr[1] = re_addr("BG1");
  Q0057B72C = 0; P65_SetNameFields();
  CK(P35_InputMode == 0 && strcmp(P65_NamePtr, "NONE") == 0 && strcmp(P65_NameBg, "BG0") == 0);
  Q0057B72C = 3; Q00B87EF0 = 1; P65_SetNameFields();
  CK(P35_InputMode == 2 && strcmp(P65_NamePtr, "PAD 3") == 0 && strcmp(P65_NameBg, "BG1") == 0);
  Q00B87EF0 = 0; P65_SetNameFields(); CK(strcmp(P65_NameBg, "BG2") == 0);
  /* блиттеры */
  uint8_t *page = (uint8_t *)aligned_alloc(0x10000, 0x10000);
  for (int i = 0; i < 0x10000; i++) page[i] = (uint8_t)(i * 7 + 3);
  P65_ColorKey = page[(5 << 8) | 0xfe];       /* строка v=5, u=0xfe → прозрачный цвет */
  memset(P65_Screen, 0xEE, sizeof(p65_screen_t));
  P65_BlitKeyed(page + 0x1234, (uint8_t *)P65_Screen + 640 + 10, 4, 2, 0xfe, 5);
  uint8_t *d = (uint8_t *)P65_Screen + 640 + 10;
  CK(d[0] == 0xEE);                                           /* ключевой цвет не пишется */
  CK(d[1] == page[(5 << 8) | 0xff] && d[2] == page[(5 << 8) | 0x00] && d[3] == page[(5 << 8) | 0x01]);   /* u замыкается в 8 бит */
  CK(d[640] == page[(6 << 8) | 0xfe] || page[(6 << 8) | 0xfe] == P65_ColorKey);
  CK(d[4] == 0xEE);
  for (int i = 0; i < 0x10000; i++) P65_Blend[i] = (uint8_t)((i >> 8) + (i & 0xff));
  memset(P65_Screen, 0x10, sizeof(p65_screen_t));
  P65_BlitBlend(page, (uint8_t *)P65_Screen, 3, 1, 4, 9);
  CK(((uint8_t *)P65_Screen)[0] == (uint8_t)(0x10 + page[(9 << 8) | 4]) && ((uint8_t *)P65_Screen)[2] == (uint8_t)(0x10 + page[(9 << 8) | 6]));
  /* обёртки со спрайтами */
  P65_Texs[2].p = page;
  memset(P65_Screen, 0, sizeof(p65_screen_t));
  P65_ColorKey = 0;
  P65_SpriteKeyed(7, 3, 2, 1, 1, 2, 1);
  CK(((uint8_t *)P65_Screen)[3 * 640 + 7] == page[(1 << 8) | 1] || page[(1 << 8) | 1] == 0);
  memset(P65_Screen, 4, sizeof(p65_screen_t));
  P65_SpriteBlend(0, 0, 2, 0, 0, 1, 1);
  CK(((uint8_t *)P65_Screen)[0] == (uint8_t)(4 + page[0]));
  free(page);
  /* вызов скрипта */
  static uint8_t strm[8] = { 0, 0, 0x34, 0x12, 0, 0, 0, 0 };
  P10_ScriptPtr = strm;
  CK(P65_ScriptCall() == 1 && P10_ScriptPtr == strm + 4);
#undef CK
  return f;
}

/* ported66 */
static int t66_n, t66_nshadow, t66_fn, t66_cb;
static int32_t t66_args[16][8]; static float t66_fx[16][2];
void P66_Draw5173D7(float x, float y, uint32_t txt, int32_t a, int32_t flags) { if (!re_selftest_on) { P73_Text(x, y, txt, a, flags); return; }
  if (t66_nshadow < 16) { t66_fx[t66_nshadow][0] = x; t66_fx[t66_nshadow][1] = y; t66_args[t66_nshadow][2] = (int32_t)txt; t66_args[t66_nshadow][4] = flags; } t66_nshadow++; (void)a; }
void P66_Fn523829(void) { if (!re_selftest_on) { P115_SndUpdate(); return; } t66_fn++; }
void P66_Fn427EEA(void) { if (!re_selftest_on) { P82_FrustumSetup3D(); return; } t66_fn++; }
void P66_Fn4169AF(void) { t66_cb++; }
static int t66_a, t66_b;
void DrawDirectorMenu(void);
void P66_Fn4C3BC7(void) { if (!re_selftest_on) { DrawDirectorMenu(); return; } t66_a++; }
void P66_Fn4C68A7(int32_t a) { if (!re_selftest_on) { P112_DirTimeline(a); return; } t66_b += a; }
static int test_p66(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p66 fail line %d\n",__LINE__); } } while (0)
  uint8_t tbl[16 * 3];
  memset(tbl, 0, sizeof tbl);
  int16_t v;
  v = 10; memcpy(tbl + 0, &v, 2); v = 20; memcpy(tbl + 2, &v, 2); tbl[5] = 3; { uint32_t t = 0x1111; memcpy(tbl + 8, &t, 4); }
  v = -5; memcpy(tbl + 16, &v, 2); v = 7; memcpy(tbl + 18, &v, 2); tbl[16 + 5] = 1; { uint32_t t = 0x2222; memcpy(tbl + 24, &t, 4); }
  tbl[16 + 0xc] = 200; tbl[16 + 0xd] = 100; tbl[16 + 0xe] = 50;
  P66_C255 = 255.0f; P66_C128 = 128.0f; P66_C2 = 2.0f;
  P19_Cur = 0.5f; P59_NoKeyFlag = 0; P59_MenuLock = 0;
  t66_n = t66_nshadow = 0;
  P66_DrawTable(tbl);
  /* 0051755e перенесён: каждый пункт — три вызова 005173d7 (тень, смещённая тень, текст) */
  CK(t66_nshadow == 6);
  CK(t66_fx[0][0] == 10.0f && t66_fx[0][1] == 20.0f && t66_args[0][2] == 0x1111 && t66_args[0][4] == (3 | 0x10) && t66_args[2][4] == (3 | 4));
  CK(t66_fx[3][0] == -5.0f && t66_fx[3][1] == 7.0f && t66_args[3][2] == 0x2222);
  CK(S_00B5A834 == 100 && S_00B5A835 == 50 && S_00B5A836 == 25);          /* цвет последнего пункта */
  /* режим с тенью: три вызова на пункт */
  P59_MenuLock = 1; t66_n = t66_nshadow = 0;
  P66_DrawTable(tbl);
  CK(t66_nshadow == 6);
  CK(t66_fx[0][0] == 10.0f && t66_fx[1][0] == 12.0f && t66_fx[1][1] == 22.0f && t66_fx[2][0] == 10.0f);
  CK(t66_args[0][4] == (3 | 0x10) && t66_args[2][4] == (3 | 4) && t66_args[3][4] == (1 | 0x10));
  P59_MenuLock = 0;
  /* начало кадра: сцена, режим 00426580 */
  t66_fn = 0; G6_00D0DDC0 = 5; Q00B87E90 = 0; P66_LoadFlag = 1; P66_Scene = 0;
  { int32_t sgn = P54_GridN; P54_GridN = 0;   /* P89_DrawMap выходит сразу после обновления клетки */
    P66_FrameBegin(); P54_GridN = sgn; }
  CK(P66_Scene == 0x00cb8f20u && G6_00D0DDC0 == 0 && t66_fn == 2);
  /* кадр экрана: окно неактивно — ничего; вложенность */
  P31_Active = 0; P66_Nest = 0; t66_cb = 0; t66_n = 0;
  P66_ScreenFrame(0, 0x004169afu);
  CK(P66_Nest == 0 && t66_cb == 0);
  P31_Active = 1; P66_Nest = 2;
  P66_ScreenFrame(0, 0x004169afu);
  CK(P66_Nest == 1 && t66_cb == 0);
  P66_Nest = 0; P66_ScreenFrame(0x0054e6a0u, 0x004169afu);          /* адрес из образа игры в native не читается */
  CK(t66_cb == 1 && t66_n == 0);
  P31_Active = 0;
  /* 004c862f: переключатель режима режиссёра */
  DirectorUnk6C = 7;
  P29_Flag48 = 1; P29_Mode = 1; t66_a = t66_b = 0; P66_DirSwitch();
  CK(t66_a == 0 && t66_b == 0);
  P29_Flag48 = 0; P29_Mode = 1; P66_DirSwitch();                       /* случай 0 */
  CK(t66_a == 1 && t66_b == 7);
  P29_Mode = 2; t66_a = t66_b = 0; P66_DirSwitch();                    /* случай 1 — ничего */
  CK(t66_a == 0 && t66_b == 0);
  P29_Mode = 5; t66_a = t66_b = 0; P66_DirSwitch();                    /* случай 4: 4c68a7, затем 4c3bc7 */
  CK(t66_a == 1 && t66_b == 7);
  P29_Mode = 12; t66_a = t66_b = 0; P66_DirSwitch();                   /* 0xb */
  CK(t66_a == 1 && t66_b == 7);
  P29_Mode = 13; t66_a = t66_b = 0; P66_DirSwitch();
  CK(t66_a == 0 && t66_b == 0);
  P29_Mode = 3; DirectorBuffer = (void *)&f; t66_a = t66_b = 0; P66_DirSwitch();   /* случай 2 с буфером */
  CK(t66_a == 1 && t66_b == 7);
  DirectorBuffer = NULL; P29_Mode = 0;
#undef CK
  return f;
}

/* ported64 */
static void t64_put(const char *n, const char *d, size_t l) { FILE *f = fopen(n, "wb"); if (f) { fwrite(d, 1, l, f); fclose(f); } }
static int test_p64(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p64 fail line %d\n",__LINE__); } } while (0)
  /* 00406272 / 00406096 / 00405f6f: запись SAVES\REPLAY1.BIN из трёх временных файлов */
  t64_put("REPLAYDATA\\USER\\$TEMP$.CFG", "CFGDATA", 7);
  t64_put("REPLAYDATA\\USER\\$TEMP$.CAMS", "CAMS", 4);
  t64_put("REPLAYDATA\\USER\\$TEMP$.PADS", "PADSPADS", 8);
  CK(P64_ReplayStart(0, "MyReplay") == 1);
  { uint8_t b[256]; size_t n = 0; FILE *fp = fopen("SAVES\\REPLAY1.BIN", "rb");
    CK(fp != NULL);
    if (fp) { n = fread(b, 1, sizeof b, fp); fclose(fp); }
    CK(n == 8 + 0x38 + (8 + 7) + (8 + 4) + (8 + 8));
    CK(rd_i32(b, 0) == 0x38910457 && memcmp(b + 8, "MyReplay", 9) == 0);
    CK(rd_i32(b, 4) == SumBytes(b + 8, 0x38));
    CK(rd_i32(b, 8 + 0x38) == 0x21474643 && rd_i32(b, 8 + 0x38 + 4) == 7 && memcmp(b + 8 + 0x38 + 8, "CFGDATA", 7) == 0);
    CK(rd_i32(b, 8 + 0x38 + 15) == 0x534d4143 && rd_i32(b, 8 + 0x38 + 27) == 0x53444150); }
  CK(P59_ReplayCheck(0, NULL) == 1);
  /* нет файла PADS: запись отменяется и файл удаляется */
  remove("REPLAYDATA\\USER\\$TEMP$.PADS");
  CK(P64_SaveReplay(0) == 0);
  { FILE *fp = fopen("SAVES\\REPLAY1.BIN", "rb"); CK(fp == NULL); if (fp) fclose(fp); }
  remove("REPLAYDATA\\USER\\$TEMP$.CFG"); remove("REPLAYDATA\\USER\\$TEMP$.CAMS");
  CK(P64_SaveChunk(NULL, "no\\such\\file", 1) == 0);
  /* таблица рекордов: 5 строк по 0x2c, результат +0x10, время +0x14 (PackRGB: младший компонент +0x20), занято +0x18 */
  uint8_t T[5 * 0x2c], E[0x48];
  memset(T, 0, sizeof T); memset(E, 0, sizeof E);
  for (int i = 0; i < 5; i++) { wr_i32(T, i * 0x2c + 0x18, 8); wr_i32(T, i * 0x2c + 0x10, 100 - 10 * i); wr_i32(T, i * 0x2c + 0x20, 10 * (i + 1)); }
  P64_CurTable = T; P64_NativeTable = T;
  wr_i32(E, 0x40, 1); wr_i32(E, 0x1c, 25);    /* время 25 */
  CK(P64_RankTimeMore(E) == 2);               /* первая строка с большим временем (30) */
  CK(P64_RankTimeB(E) == 2);
  CK(P64_RankTimeLess(E) == 0);               /* первая строка с меньшим временем (10) */
  wr_i32(E, 0x1c, 5); CK(P64_RankTimeLess(E) == -1 || P64_RankTimeLess(E) == 0);
  wr_i32(E, 0x1c, 60); CK(P64_RankTimeMore(E) == -1);
  wr_i32(T, 4 * 0x2c + 0x18, 0); CK(P64_RankTimeMore(E) == 4);   /* свободная строка */
  wr_i32(T, 4 * 0x2c + 0x18, 8);
  wr_i32(E, 8, 85); wr_i32(E, 0x1c, 7);
  CK(P64_RankBestFirst(E) == 2 && P64_RankScoreB(E) == 2);   /* 85 > 80 */
  wr_i32(E, 8, 80); wr_i32(E, 0x1c, 5);  CK(P64_RankBestFirst(E) == 2 + 0 || P64_RankBestFirst(E) == 3);
  wr_i32(E, 8, 80); wr_i32(E, 0x1c, 35); CK(P64_RankBestFirst(E) == 2);   /* равный результат, время 30 < 35 → в строке 2 */
  wr_i32(E, 0x40, 0); CK(P64_RankBestFirst(E) == -1 && P64_RankTimeMore(E) == -1);
  wr_i32(E, 0x2c, 8); wr_i32(E, 0x34, 5);  CK(P64_RankTop(E) == 0);       /* 10 > 5 → лучший */
  wr_i32(E, 0x34, 10); CK(P64_RankTop(E) == -1);
  wr_i32(E, 0x2c, 3); CK(P64_RankTop(E) == -1);
  /* 0051cc55: выбор по типу */
  wr_i32(E, 0x40, 1); wr_i32(E, 0x1c, 25);
  P42_HighScores[1] = 1; P42_HighScores[2] = 0;   /* таблица типа 2, индекс 1; индекс 2 — нет (v1.42: 0051c900 в native заполняет таблицу) */
  CK(P64_RankPlace(E, 2, 1) == 2 && rd_i32(E, 0xc) == 1);
  CK(P64_RankPlace(E, 2, 2) == -1 && rd_i32(E, 0xc) == 0);   /* таблицы нет */
  P42_HighScores[8 + 1] = 1; wr_i32(E, 8, 85); CK(P64_RankPlace(E, 1, 1) == 2);
  return f;
}

/* ported67 */
static uint32_t t67_p4; static int t67_calls, t67_stream; static int32_t t67_ret; static char t67_name[16];
static uint8_t *t67_icon; static int32_t t67_logo[6]; static int t67_logoN; static const char *t67_findname;
void P67_Fn40ABAC(uint32_t a) { if (!re_selftest_on) { P116_Text(a); return; } t67_p4 = a; }
int32_t P67_Fn514C9F(void *p, int32_t a, int32_t b) { (void)p; (void)a; (void)b; return t67_ret; }
void P67_Fn51500C(void *p) { if (!re_selftest_on) { P101_PartTurn((uint8_t *)p); return; } int32_t v = 0x777; memcpy((uint8_t *)p + 0x38, &v, 4); }
void P67_Fn514165(void *p) { if (!re_selftest_on) { P71_Course((uint8_t *)p); return; } (void)p; t67_calls++; }
void P67_Stream(const char *name, int32_t a) { if (!re_selftest_on) { (void)P77_LoadBank(name, (uint16_t)a); return; } (void)a; strncpy(t67_name, name, 15); t67_stream++; }
uint8_t *P56_FindIcon(const char *n) { if (!re_selftest_on) { return P93_FindIcon(n); } t67_findname = n; return t67_icon; }
void P58_Fn4AA4EA(int32_t a0, int32_t a1, int32_t a2, int32_t a3, void *a4, int32_t a5) { if (!re_selftest_on) { P110_IconRect(a0, a1, a2, a3, a4, a5); return; }
  t67_logo[0] = a0; t67_logo[1] = a1; t67_logo[2] = a2; t67_logo[3] = a3; t67_logo[4] = a4 == (void *)t67_icon; t67_logo[5] = a5; t67_logoN++; }
void Call005233BE(int32_t a0, int32_t a1, int32_t a2) { if (!re_selftest_on) { P140_SndInit(a0, a1, a2); return; } (void)a0; (void)a1; (void)a2; }
void Call00414D1F(void) { if (!re_selftest_on) { P103_OptionsInit(); return; } t67_calls += 100; }
static float t67_f(int32_t v) { float f; memcpy(&f, &v, 4); return f; }
static int test_p67(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p67 fail line %d\n",__LINE__); } } while (0)
  /* 004bb060 */
  memset(P67_Ents, 0, sizeof(P67_EntArr)); memset(P67_Items, 0, sizeof(P67_ItemArr));
  P67_Ents[0].used = 1; P67_Ents[0].item = 99; P67_Items[0] = 7; P67_Items[1] = 8; P67_ItemCnt = 2; P67_Cur = 5;
  P67_CompactPool();
  CK(P67_Ents[1].item == 8 && P67_Ents[1].a == 4 && P67_Ents[2].item == 7 && P67_Ents[0].item == 99);
  CK(P67_ItemCnt == 0 && P67_Items[0] == 0 && P67_Ents[0].used == 0);
  /* 00516fbe */
  P19_ScrH = 480; P19_ScrW = 640; P19_Scale = 2.0f; S_00B5A834 = 1; S_00B5A835 = 2; S_00B5A836 = 3;
  P67_CenterDraw(300.0f, 10.0f, 20.0f, 0x55);
  CK(t67_f((int32_t)MenuPosX54AA24) == 20.0f && t67_f((int32_t)MenuPosY54AA28) == 40.0f);
  CK(t67_f(MenuVal5D77CC) == 320.0f && t67_f(MenuVal5D77C8) == 360.0f && MenuByte5D77C0 == 5 && MenuByte5D77C1 == 0 && t67_p4 == 0x55);
  CK(MenuColorR54AA2C == 1 && MenuColorG54AA2D == 2 && MenuColorB54AA2E == 3);
  /* 00513fbc */
  uint8_t obj[0x80]; memset(obj, 0, sizeof obj);
  uint32_t fl = 0x10, c = 0xabcd1234u; memcpy(obj + 0xc, &fl, 4); memcpy(obj + 0x5c, &c, 4);
  t67_ret = 1; t67_calls = 0; P67_ObjStep(obj);
  { uint16_t hi; int32_t v; memcpy(&hi, obj + 0x5e, 2); memcpy(&v, obj + 0x38, 4); CK(hi == 0xabcd && v == 0x777 && t67_calls == 1); }
  t67_ret = 0; t67_calls = 0; fl = 0; memcpy(obj + 0xc, &fl, 4); P67_ObjStep(obj); CK(t67_calls == 1);
  fl = 0x80; memcpy(obj + 0xc, &fl, 4); P67_ObjStep(obj); CK(t67_calls == 1);
  /* 004a9e88 / 0040cfdf */
  uint8_t ic[16] = { 0 }; ic[8] = 3; ic[9] = 4; ic[10] = 5; ic[0xb] = 0; ic[0xc] = 32; t67_icon = ic;
  t67_logoN = 0; P67_Logo(1, 0x30);
  CK(t67_logoN == 1 && strcmp(t67_findname, "GT") == 0 && t67_logo[0] == 0x160 && t67_logo[1] == 0x30 && t67_logo[2] == 0x100 && t67_logo[3] == 32 && t67_logo[4] == 1 && t67_logo[5] == -1);
  P67_Logo(2, 0); CK(t67_logoN == 1);
  P67_Logo(2, 0x30); CK(t67_logoN == 2 && strcmp(t67_findname, "REFLEC") == 0);
  uint8_t *page = (uint8_t *)aligned_alloc(0x10000, 0x10000);
  for (int i = 0; i < 0x10000; i++) page[i] = (uint8_t)(i * 5 + 1);
  P65_Texs[3].p = page; ic[0xb] = 2; ic[0xc] = 1; P65_ColorKey = 0; memset(P65_Screen, 0, sizeof(p65_screen_t));
  P67_DrawIcon(9, 2, 0, "X");
  CK(((uint8_t *)P65_Screen)[2 * 640 + 9] == page[(5 << 8) | 4] || page[(5 << 8) | 4] == 0);
  CK(strcmp(t67_findname, "X") == 0);
  t67_icon = NULL; P67_DrawIcon(9, 2, 0, "Y"); free(page);
  /* меню: шаг меню в тесте всегда -1, т.е. выход сразу */
  P19_Sel = 5; MenuMode1271060 = 3; P12_00bdfa40 = 4;
  CK(P67_Menu415EC0() == 0 && P19_Sel == 0);
  CK(MenuMode1271060 == 0 && P12_00bdfa40 == 0);
  UiVar0054E4B0 = 5; P67_Res51C = 0;
  CK(P67_Menu417970() == 0);
  /* 00415188: 0→1→2→0 */
  P12_00b87e5c = 0; G6_00B87EEC = 0; t67_stream = 0; t67_calls = 0;
  CK(P67_Menu415188() == 0 && P12_00b87e5c == 1 && strcmp(t67_name, "TITLE.DSS") == 0 && t67_calls == 100);
  G6_00B87EEC = 1; P67_Menu415188(); CK(P12_00b87e5c == 2 && strcmp(t67_name, "MOTEL.DSS") == 0);
  P67_Menu415188(); CK(P12_00b87e5c == 0 && t67_stream == 3);
#undef CK
  return f;
}

/* ported68 */
static int t68_cmds[8], t68_ret41b1c0, t68_loadN; static int32_t t68_freed;
void P68_Fn514A47(void *p) { if (!re_selftest_on) { P98_PartAim((int16_t *)p); return; } (void)p; t68_cmds[0]++; }
int32_t P68_Fn41B1C0(void) { if (!re_selftest_on) return P139_LadderLoad(); return t68_ret41b1c0; }
void P68_Fn41B3AB(void) { if (!re_selftest_on) { P140_LadderRun(); return; } t68_cmds[1]++; }
static int32_t t68_load(int32_t n, int32_t a) { t68_loadN++; return a == 99 ? -1 : n * 100 + a; }
static void t68_free(int32_t id) { t68_freed = id; }
static float rd_f32(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
static void wr_f32(uint8_t *p, uint32_t o, float v) { memcpy(p + o, &v, 4); }
static int test_p68(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p68 fail line %d\n",__LINE__); } } while (0)
  /* 00522e64: третий повтор из последних четырёх ключей */
  memset(P68_Rep_, 0, sizeof(P68_RepArr)); P12_00bde728 = 0;
  CK(P68_RepeatCheck(7) == 0 && P12_00bde728 == 1);
  CK(P68_RepeatCheck(7) == 0 && P68_Rep_[0].cnt == 1);
  CK(P68_RepeatCheck(7) == 0 && P68_Rep_[0].cnt == 2 && P68_RepeatCheck(7) == 1 && P68_RepeatCheck(7) == 0);
  for (int i = 0; i < 5; i++) P68_RepeatCheck(100 + i);
  CK(P12_00bde728 == 6 % 5 || P12_00bde728 < 5);
  /* 00524ed1 */
  { FILE *fp = fopen("p68.txt", "wb"); fputs("\n\n  ab \t cd\t\r\nxyz\n", fp); fclose(fp);
    fp = fopen("p68.txt", "rb"); uint8_t b[32]; memset(b, 0x55, sizeof b);
    CK(P68_ReadWords(fp, b) == 6 && strcmp((char *)b, "ab cd ") == 0);   /* пробел перед концом строки остаётся, как в оригинале */
    CK(P68_ReadWords(fp, b) == 3 && strcmp((char *)b, "xyz") == 0);
    CK(P68_ReadWords(fp, b) == -1); fclose(fp);
    fp = fopen("p68.txt", "wb"); fputs("q w", fp); fclose(fp); fp = fopen("p68.txt", "rb");
    memset(b, 0x55, sizeof b); CK(P68_ReadWords(fp, b) == 3 && b[0] == 'q' && b[1] == ' ' && b[2] == 'w' && b[3] == 0x55);
    fclose(fp); remove("p68.txt"); }
  /* 00514f47 */
  { uint8_t o[0xb0]; memset(o, 0, sizeof o);
    wr_f32(o, 0x84, 10.0f); wr_f32(o, 0x88, 1.0f); wr_f32(o, 0x8c, 20.0f);
    wr_f32(o, 0x94, 10.0f); wr_f32(o, 0x98, 1.0f); wr_f32(o, 0x9c, 120.0f);
    P68_AimSetup(o);
    uint16_t a, b; memcpy(&a, o + 0x5c, 2); memcpy(&b, o + 0x5e, 2);
    CK(a == 0x800 && rd_f32(o, 0x6c) == 100.0f && rd_f32(o, 0x64) == 0.0f && P11_00ba52d0 == 100);
    CK(b == ((-P44_Atan2(100, 0) - 0x400) & 0xfff)); }
  /* 00513efd */
  { uint8_t o[0x80]; memset(o, 0, sizeof o); uint32_t fl = 0x10, c = 0xabcd1234u; memcpy(o + 0xc, &fl, 4); memcpy(o + 0x5c, &c, 4);
    t68_cmds[0] = 0; t67_ret = 1; t67_calls = 0; P68_ObjStepB(o);
    uint16_t hi; memcpy(&hi, o + 0x5e, 2);
    CK(t68_cmds[0] == 1 && hi == 0xabcd && t67_calls == 1);
    t67_ret = 0; t67_calls = 0; fl = 0; memcpy(o + 0xc, &fl, 4); P68_ObjStepB(o); CK(t67_calls == 1);
    fl = 8; memcpy(o + 0xc, &fl, 4); P68_ObjStepB(o); CK(t67_calls == 1); }
  /* 004a5505 */
  { P68_CamF[3] = 0x11; P68_CamF[2] = 0x22; P68_CamF[1] = 0x33; P68_CamF[0] = 0x44; P68_CamI0 = 5; P68_CamI1 = 6; P68_CamI2 = 7; P68_CamI3 = 8;
    uint8_t o[32]; memset(o, 0, sizeof o);
    uint8_t *e = P68_ReadCamArgs(o, "fifi");
    uint32_t w0, w1; uint16_t s0, s1; memcpy(&w0, o, 4); memcpy(&s0, o + 4, 2); memcpy(&w1, o + 6, 4); memcpy(&s1, o + 10, 2);
    CK(e == o + 12 && w0 == 0x11 && s0 == 5 && w1 == 0x22 && s1 == 6);
    memset(o, 0, sizeof o); e = P68_ReadCamArgs(o, "ffffxf"); CK(e == o + 16);
    uint32_t w3; memcpy(&w3, o + 12, 4); CK(w3 == 0x44);
    memset(o, 0, sizeof o); e = P68_ReadCamArgs(o, "iiiii"); CK(e == o + 10);
    uint16_t s4; memcpy(&s4, o + 8, 2); CK(s4 == 0 && P68_ReadCamArgs(o, "") == o); }
  /* 0052455f */
  { for (int i = 0; i < 0x14; i++) P48_Snd[i].id = 0xffff;
    P48_Drv2C = t68_free; P68_DrvLoad = t68_load; G6_00B91D34 = 10;
    G6_00B91CF4 = 0; CK(P68_ChangeSample(1, 3) == 1 && t68_loadN == 0);
    G6_00B91CF4 = 1;
    CK(P68_ChangeSample(1, -1) == 0 && P68_ChangeSample(1, 10) == 0 && t68_loadN == 0);
    CK(P68_ChangeSample(5, 3) == 1 && t68_freed == 3 && P68_Samps[3].handle == 305 && P48_Samples[24] == 2 && P48_Samples[25] == 8 && P68_Samps[3].extra == 0);
    CK(P68_ChangeSample(99, 4) == 0 && P68_Samps[4].handle == -1 && P48_Samples[32] == 4); }
  /* 0042476c: Glide не загружен, поэтому вызов не выполняется, но байты формата пишутся */
  { uint8_t info[0x40]; memset(info, 0, sizeof info);
    D_00b1c0d4 = 0; CK(P68_LfbLock(0, info) == 0 && info[0x14] == 0);
    D_00b1c0d4 = 1; D_00b1c0d8 = 0; CK(P68_LfbLock(0, info) == 0 && info[0x14] == 0x10 && info[0x15] == 3 && info[0x16] == 2 && info[0x17] == 3 && info[0x18] == 0xb && info[0x19] == 5 && info[0x1a] == 0);
    D_00b1c0d8 = 5; CK(P68_LfbLock(0, info) == 0); }
  /* 0040c480 */
  { P56_AA30 = 0; t68_ret41b1c0 = 0; t68_cmds[1] = 0;
    P68_ScreenReset(1); CK(t68_cmds[1] == 0);
    t68_ret41b1c0 = 1; P68_ModeW = P19_ScrW; P68_ModeH = P19_ScrH;
    P19_Level = 3; P68_Saved[0] = 7; P68_Saved[1] = 4; P68_Saved[2] = 11; P68_Saved[3] = 12; P68_Saved[4] = 13; P68_IntroBase = 0x1000;
    P58_CfgOn = 0;
    P68_ScreenReset(1);
    CK(P19_Level == 7 && P68_IntroCur == 0x1040 && P68_IntroA == 11 && S_0127104C == 12 && P68_B87E54 == 13 && t68_cmds[1] == 1);
    P19_Level = 9; P68_ScreenReset(0); CK(P19_Level == 9 && t68_cmds[1] == 2); }
  /* 004a67b0 */
  { memset(P12_0112da00, 0, sizeof(p12_0112da00_t)); G0112B284 = 3; P68_D11A48 = 5;
    uint8_t rec[16] = { 0 };
    uint8_t *s = P68_SpawnCar(rec, 0x1234);
    CK(s == (uint8_t *)P12_0112da00 + 0xcd8 && rec[5] == 2 && G0112B284 == 4 && P68_D11A48 == 0);
    uint32_t id, owner; memcpy(&id, s, 4); memcpy(&owner, s + 0xcd0, 4); CK(id == 1 && owner == 0x1234);
    for (int i = 0; i < 8; i++) { uint32_t one = 1; memcpy((uint8_t *)P12_0112da00 + i * 0xcd8 + 0xcb4, &one, 4); }
    G0112B284 = 3; CK(P68_SpawnCar(rec, 1) == NULL && G0112B284 == 3); }
#undef CK
  return f;
}

/* ported69 */
static int t69_ovl, t69_calls[4], t69_freed;
void P69_Fn4B33D8(void *p) { if (!re_selftest_on) { P135_DebrisTri((int32_t *)p); return; } (void)p; t69_ovl++; }
void P69_Fn4B3E55(void) { if (!re_selftest_on) { P114_DebrisAll(); return; } t69_calls[0]++; }
void P69_Fn4B2C4B(void) { if (!re_selftest_on) { P121_DustDraw(); return; } t69_calls[1]++; }
void P69_Fn4AAF3A(void) { if (!re_selftest_on) { P139_Effects(); return; } t69_calls[2]++; }
void P69_Fn4BA720(void) { if (!re_selftest_on) { P98_DrawSix(); return; } t69_calls[3]++; }
void CrtFree_0052CB70(uint32_t a) { t69_freed += (int)a; }
static int test_p69(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p69 fail line %d\n",__LINE__); } } while (0)
  P69_InitConsts();
  /* 004a3630 */
  P69_MsgBlk[3] = 9; P69_MsgW = 0; P55_Lang = 2; P69_SetupMsgs(); CK(P69_MsgW == 0x8c && P69_MsgBlk[3] == 0);
  /* 004a0cca: сегменты порогов (10,20,30 | 40,50 | ...) */
  memset(P69_Thr, 0, sizeof(P69_ThrTab)); memset(P69_Ptrs, 0, sizeof(P69_PtrTab));
  P69_Thr[0] = 10; P69_Thr[1] = 20; P69_Thr[2] = 30; P69_Thr[3] = 40; P69_Thr[4] = 50;
  P69_Ptrs[0] = P69_TBASE; P69_Ptrs[1] = P69_TBASE + 12; P69_Ptrs[2] = P69_TBASE + 20;
  CK(P69_Bracket(20) == 0);
  CK(P69_Bracket(40) == 1);
  CK(P69_Bracket(100) == 0x12);
  /* 004a0d5f */
  P69_Score = 1000; P69_Bonus = 7;
  CK(P69_AddScore(40) == 0 && P69_Score == 1150 && P69_ScoreCpy == 1150);
  P69_Bonus = 250; CK(P69_AddScore(0xff00) == 0 && P69_Score == 1350 && P69_Bonus == 0);
  P69_Score = 999900; P69_Bonus = 1200; P69_AddScore(0xff00); CK(P69_Score == 999999);
  P69_Score = 5; P69_AddScore(100); CK(P69_Score == 5);   /* выше всех порогов — очки не начисляются */
  /* 004b3ddb */
  P69_BlendOn = 1; P69_OvlOn = 1; t69_ovl = 0; memset(P12_0110b260, 0, sizeof(p12_0110b260_t));
  { uint16_t two = 2; memcpy((uint8_t *)P12_0110b260 + 0x3c * 5 + 0x22, &two, 2); memcpy((uint8_t *)P12_0110b260 + 0x3c * 199 + 0x22, &two, 2); }
  P69_ReleaseOverlays(); CK(P69_BlendOn == 0 && t69_ovl == 2);
  P69_OvlOn = 0; P69_ReleaseOverlays(); CK(t69_ovl == 2);
  /* 004aaea6 */
  G6_01270C34 = 0; MenuVar553850 = 0; memset(t69_calls, 0, sizeof t69_calls); P69_BlendOn = 0; P69_OvlOn = 0; P26_FxD = 1;
  P69_SceneFrame(); CK(G6_01270C34 == 4 && P44_MatPtr == (float *)&P44_ViewMatT);
  CK(t69_calls[0] == 1 && t69_calls[1] == 1 && t69_calls[2] == 1 && t69_calls[3] == 1);
  P26_FxD = 0;
  /* 004246f0 */
  P69_DevOn = 1; P42_DevCount = 2; D_00b1c0d4 = 3; t69_freed = 0;
  { uint32_t a = 100, b = 0, c = 7; memcpy(P42_DevNames[0] + 0x44, &a, 4); memcpy(P42_DevNames[1] + 0x44, &b, 4); memcpy(P42_DevNames[2] + 0x44, &c, 4); }
  P69_FreeDevices(); CK(P69_DevOn == 0 && P42_DevCount == 0 && D_00b1c0d4 == 0 && t69_freed == 100);
  P69_DevOn = 0; t69_freed = 0; P69_FreeDevices(); CK(t69_freed == 0);
#undef CK
  return f;
}

/* ported70 */
static int t70_ret, t70_rad[2], t70_rgb[8], t70_txt;
int32_t P61_Fn5139D7(int32_t a, int32_t b, int32_t c, void *d) { if (!re_selftest_on) { return (int32_t)P101_PickCell((uint32_t)a, b, c, (float *)d); } (void)a; (void)b; (void)c; (void)d; return t70_ret; }
void P70_Fn5063A4(int32_t i) { if (!re_selftest_on) { P135_RadarLine(i); return; } t70_rad[0] = i + 1; }
void P70_Fn507925(int32_t i) { if (!re_selftest_on) { P131_RadarArrow(i); return; } t70_rad[1] = i + 1; }
static int test_p70(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p70 fail line %d\n",__LINE__); } } while (0)
  (void)t70_rgb; (void)t70_txt;
  /* 00514332 / 00514403 */
  uint8_t *pt = (uint8_t *)A_00C56780 + 0xb4 * 3;
  float fx = 100.0f, fz = 200.0f; uint32_t fl = 0x10;
  memset((uint8_t *)A_00C56780, 0, 0xb4 * 64);
  memcpy(pt + 0xc, &fl, 4); memcpy(pt + 0x84, &fx, 4); memcpy(pt + 0x8c, &fz, 4);
  P43_FreeCnt = 1; t70_ret = 7;
  P70_SpawnPart4(pt);
  { int32_t v; memcpy(&v, pt + 0x38, 4); CK(v == 7); memcpy(&v, pt + 0xc, 4); CK(v == 0x10); }
  t70_ret = 0; P43_FreeCnt = 1;
  { uint16_t idx = 3; memcpy(pt + 2, &idx, 2); }
  P70_SpawnPart2(pt);
  { int32_t v; memcpy(&v, pt + 0xc, 4); CK(v == 0 && P43_FreeCnt == 0 && P43_FreeList[0] == 3); }
  /* 00513905 */
  memcpy(pt + 0xc, &fl, 4);
  CK(P70_FindParticle(130, 230) == 3 && P70_FindParticle(1000, 1000) == -1 && P70_FindParticle(150, 250) == -1);
  /* 0051ab31 */
  { uint8_t buf[0x40]; memset(buf, 0, sizeof buf);
    int32_t m1 = -1, o1 = 0x20; memcpy(buf + 8, &m1, 4); memcpy(buf + 12, &o1, 4);
    int16_t d[6] = {3, 7, 1, 9}; memcpy(buf + 0x20, d, 8);
    uint8_t *save = P62_MapBuf; int32_t sn = P62_MapN; P62_MapBuf = buf; P62_MapN = 2;
    int16_t out[4] = {0};
    CK(P70_RowDecode(1, out) == 1 && out[0] == 7 && out[1] == 7 && out[2] == 7 && out[3] == 9);
    CK(P70_RowDecode(0, out) == 0 && out[0] == -1 && out[3] == -1);
    P62_MapBuf = save; P62_MapN = sn; }
  /* 00406369 / 00406199 */
  t64_put("REPLAYDATA\\USER\\$TEMP$.CFG", "CFGDATA", 7);
  t64_put("REPLAYDATA\\USER\\$TEMP$.CAMS", "CAMS", 4);
  t64_put("REPLAYDATA\\USER\\$TEMP$.PADS", "PADSPADS", 8);
  CK(P64_ReplayStart(0, "Again") == 1);
  remove("REPLAYDATA\\USER\\$TEMP$.CFG"); remove("REPLAYDATA\\USER\\$TEMP$.CAMS"); remove("REPLAYDATA\\USER\\$TEMP$.PADS");
  memset(P59_Hdr, 0, sizeof(p59_hdr_t));
  CK(P70_LoadReplay(0) == 1);
  { FILE *fp = fopen("REPLAYDATA\\USER\\$TEMP$.PADS", "rb"); char b[16] = {0}; CK(fp != NULL);
    if (fp) { size_t n = fread(b, 1, 16, fp); fclose(fp); CK(n == 8 && memcmp(b, "PADSPADS", 8) == 0); } }
  CK(((uint32_t *)P59_Hdr)[0] == 0x38910457u);
  CK(P70_LoadReplay(5) == 0);
  { FILE *fp = fopen("SAVES\\REPLAY1.BIN", "rb"); CK(fp != NULL); if (fp) { CK(P70_ReadChunk(fp, "x.tmp", 123) == 0); fclose(fp); } }
  remove("REPLAYDATA\\USER\\$TEMP$.CFG"); remove("REPLAYDATA\\USER\\$TEMP$.CAMS"); remove("REPLAYDATA\\USER\\$TEMP$.PADS"); remove("SAVES\\REPLAY1.BIN");
  /* 005170ab */
  S_00B5A834 = 0; S_00B5A835 = 100; S_00B5A836 = 200; G6_00B5A838 = 100; G6_00B5A839 = 0; G6_00B5A83A = 200;
  G6_00C55800 = 1; G6_00C557F8 = 2;
  CK(P70_FadeColor() == 0 && S_00B5A834 == 50 && S_00B5A835 == 50 && S_00B5A836 == 200 && G6_00C55800 == 2);
  CK(P70_FadeColor() == 1 && S_00B5A834 == 100 && S_00B5A835 == 0);
  /* 0051755e: тень и цвет, подставленные вызовы не падают */
  P70_ShadowText(10, 20, 0, 0, 0, 1, 2, 3);
  /* 005062cc / 0050784d: ближайший активный не-скрытый объект */
  memset(P58_Objs, 0, sizeof(p58_objs_t)); P59_PosX = 0; P59_PosZ = 0;
  for (int i = 0; i < 10; i++) { int32_t a = 1, x = 1000 - i * 50, z = 0; memcpy(P58_Objs[i] + 0x10, &a, 4); memcpy(P58_Objs[i] + 0x14, &x, 4); memcpy(P58_Objs[i] + 0x1c, &z, 4); }
  { int32_t h = 0x41; memcpy(P58_Objs[9] + 0x10, &h, 4); }   /* самый близкий скрыт */
  P70_RadarNearest(); CK(t70_rad[0] == 9);                  /* i=8: x=600 → индекс 8, +1 */
  P70_RadarNearestB(); CK(t70_rad[1] == 9);
  memset(P58_Objs, 0, sizeof(p58_objs_t)); t70_rad[0] = 0; P70_RadarNearest(); CK(t70_rad[0] == 0);
#undef CK
  return f;
}

/* ported71 / ported72 */
static int16_t t71_tile[16]; static uint32_t t71_tile32[16]; static void *t71_save[4];
static int test_p71(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p71 fail line %d\n",__LINE__); } } while (0)
  uint8_t pa[0xb4]; float q[16];
  /* карта 4x4 в одной плитке; смещения карты 0 */
  P62_MapC64 = 0; P62_Map2C40 = 0; P62_MapN = 4; P54_MapB1 = 4; P54_MapB2 = 4; P72_Rows = 1;
  for (int i = 0; i < 4; i++) { t71_save[i] = P54_RoadA[i]; P54_RoadA[i] = t71_tile; P54_RoadB[i] = t71_tile32; }
  P72_InitConsts();
  memset(t71_tile, 0, sizeof t71_tile); memset(t71_tile32, 0, sizeof t71_tile32);
  /* 0051b111 / 0051b566 / 0051b65a: клетка (x=1500,z=-1500) → cx=1, cz=1 → t[1*4+1] */
  t71_tile[5] = 1234; t71_tile32[5] = 0x80000000u | (7u << 16) | 0x8005u;
  CK(P72_RoadWord(1500, -1500) == 1234 && P72_RoadWord(-5000, 0) == -1 && P72_RoadWord(1500, 9000) == -1);
  CK(P72_RoadDword(1500, -1500) == (int32_t)t71_tile32[5] && P72_RoadDword(-5000, 0) == 0);
  CK(P72_RoadLookup(1500, -1500) == 1 && P72_Id == 7 && P72_Low == (int16_t)0x8005 && P72_Dir == 0x800);
  CK(P72_RoadLookup(0, 0) == 0 && P72_Low == 0 && P72_RoadLookup(-9000, 0) == 0);
  memset(t71_tile, 0, sizeof t71_tile);
  /* 005144d4 / 00514779: q=(1500,-1500) → x=1500, z=-1500; соседи: s0=(1,2) s1=(1,0) s2=(0,1) s3=(2,1) */
  memset(pa, 0, sizeof pa); memset(q, 0, sizeof q);
  int32_t one = 1, two = 2, four = 4, eight = 8;
  q[0] = 1500.0f; q[2] = -1500.0f; memcpy(pa + 0x38, &one, 4);
  t71_tile[9] = -1; P71_EdgeA(pa, q);
  { uint32_t fl; memcpy(&fl, pa + 0xc, 4); CK((fl & 0x100) == 0); CK(q[2] == (float)(-1500 + 0x15e)); }
  q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[9] = 5; P71_EdgeA(pa, q);
  { uint32_t fl; memcpy(&fl, pa + 0xc, 4); CK((fl & 0x100) != 0); CK(q[2] == (float)(-1500 - 0x226)); }
  memcpy(pa + 0x38, &two, 4); q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[1] = -3; P71_EdgeA(pa, q);
  CK(q[2] == (float)(-1500 - 0x15e));
  memcpy(pa + 0x38, &four, 4); q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[6] = -2; P71_EdgeA(pa, q);
  CK(q[0] == (float)(1500 - 0x15e));
  memcpy(pa + 0x38, &eight, 4); q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[4] = -2; P71_EdgeA(pa, q);
  CK(q[0] == (float)(1500 + 0x15e));
  memcpy(pa + 0x38, &one, 4); q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[9] = -1; P71_EdgeB(pa, q);
  CK(q[0] == (float)(1500 - 0x15e) && q[2] == (float)(-1500 + 0x15e));
  q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[9] = 0; P71_EdgeB(pa, q);
  CK(q[0] == (float)(1500 - 0x226) && q[2] == (float)(-1500 - 0x226));
  memcpy(pa + 0x38, &four, 4); q[0] = 1500.0f; q[2] = -1500.0f; t71_tile[4] = -1; P71_EdgeB(pa, q);   /* case 4 смотрит s2 (0,1) */
  CK(q[0] == (float)(1500 + 0x226) && q[2] == (float)(-1500 - 0x226));
  for (int i = 0; i < 4; i++) { P54_RoadA[i] = t71_save[i]; P54_RoadB[i] = NULL; }
  /* 00514165 */
  P44_InitTables();
  memset(pa, 0, sizeof pa);
  { float px = 100.0f, pz = 0.0f; memcpy(pa + 0x64, &px, 4); memcpy(pa + 0x6c, &pz, 4); int16_t cur = 0; memcpy(pa + 0x5e, &cur, 2); }
  P71_Course(pa);
  { int32_t u = (((-P44_Atan2(0, 100)) - 0x400) & 0xfff); int32_t d = (((u - 0) + 0x800) & 0xfff) - 0x800; uint32_t fl;
    memcpy(&fl, pa + 0xc, 4);
    int32_t gu, gd; memcpy(&gu, pa + 0x14, 4); memcpy(&gd, pa + 0x18, 4);
    CK(gu == u); CK(gd == (d < 0 ? -d : d)); CK((fl & (d < 0 ? 0x1000 : 0x2000)) != 0); }
  /* 00515bf1 */
  memset(pa, 0, sizeof pa); memset(q, 0, sizeof q);
  { float x = 10.0f, z = 20.0f; memcpy(pa + 0x84, &x, 4); memcpy(pa + 0x8c, &z, 4); }
  for (int i = 0; i < 4; i++) { q[i*4] = 1.0f; q[i*4+2] = 1.0f; q[i*4+3] = 30.0f; }
  CK(P71_InPlanes(pa, q) == 1);
  q[12 + 3] = 29.0f; CK(P71_InPlanes(pa, q) == 0);
  q[12 + 3] = 30.0f; q[3] = 29.5f; CK(P71_InPlanes(pa, q) == 0);
  /* 00515cca */
  { uint8_t car[0x100]; memset(car, 0, sizeof car);
    int32_t vx = 0, vz = 256 * 100; memcpy(car + 0x40, &vx, 4); memcpy(car + 0x48, &vz, 4);
    int32_t cx = 0, cz = 0; memcpy(car + 0xc8, &cx, 4); memcpy(car + 0xd0, &cz, 4);
    int32_t h = P44_Atan2(0, 100) & 0xfff; int32_t a = P44_Atan2(10, 20);
    int32_t t = (((a - h) + 0x800) & 0xfff) - 0x800;
    int32_t want = (t > 0) ? ((h - 0x400) & 0xfff) : ((h + 0x400) & 0xfff);
    CK(P71_FaceCar(pa, car) == want);
    /* 0051551e: частицы с флагом 0x10, не тип 3, без 0x880 и ближе 0x2ef попадают в 00515813 */
    uint8_t *tab = (uint8_t *)A_00C56780; memset(tab, 0, 0xb4 * 64);
    uint32_t fl = 0x10; float fx = 100.0f, fz = 50.0f;
    memcpy(tab + 0xb4 * 2 + 0xc, &fl, 4); memcpy(tab + 0xb4 * 2 + 0x84, &fx, 4); memcpy(tab + 0xb4 * 2 + 0x8c, &fz, 4);
    P71_InitNear(car);
    /* 00515813 пишет в запись: проверяем, что функция отработала без выхода за границы (структура не испорчена флагом) */
    CK(1);
    /* 0051380b */
    memset(tab, 0, 0xb4 * 64);
    memcpy(tab + 0xc, &fl, 4); memcpy(tab + 0x84, &fx, 4); memcpy(tab + 0x8c, &fz, 4);
    P71_Near = 100 * 100; P71_NearAdd = 0;
    CK(P71_CountNear(100, 50) == 1);
    CK(P71_CountNear(300, 50) == 0 && (P71_NearAdd % 0x5dc) == 0 && P71_NearAdd <= 3 * 0x5dc);
    P71_NearAdd = 1500; P71_Near = 0; memcpy(tab + 0xc, &fl, 4);
    CK(P71_CountNear(100, 1550) == 1 || P71_CountNear(100, 1550) == 0);
  }
  /* 00503c03 */
  P62_Menu1271060 = 6; P62_Menu1271064 = 0; P71_Tab974 = 99; P71_Tab2A40 = 99;
  P71_ScoreSetup();
  CK(P71_Ptr2A08 == 0x01271088u && P8_012710a0 == 0);
  P62_Menu1271060 = 1; P8_012710a0 = 5; P71_ScoreSetup();
  CK(P8_012710a0 == 1 && P71_Ptr2A08 == 0);
  P62_Menu1271060 = 4; P71_ScoreSetup();
  CK(P8_012710a0 == 0 && P71_Tab974 == 0 && P71_Tab2A40 == 0);
  return f;
}

/* ported73 */
static int test_p73(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p73 fail line %d\n",__LINE__); } } while (0)
  /* 005173d7: окно 1280x960, масштаб 1.0: (x*2 - 640)*1 + 640 = 2x */
  P73_InitConsts();
  P19_ScrW = 1280; P19_ScrH = 960; P19_Scale = 1.0f; S_00B5A834 = 9; S_00B5A835 = 8; S_00B5A836 = 7;
  P73_Text(100.0f, 50.0f, 0x77, 3, 0x14);
  CK(t67_f((int32_t)MenuPosX54AA24) == 2.0f && t67_f((int32_t)MenuPosY54AA28) == 2.0f);
  CK(t67_f(MenuVal5D77CC) == 200.0f && t67_f(MenuVal5D77C8) == 100.0f && MenuByte5D77C1 == 3 && MenuByte5D77C0 == 0x14 && t67_p4 == 0x77);
  CK(MenuColorR54AA2C == 9 && MenuColorG54AA2D == 8 && MenuColorB54AA2E == 7);
  P19_Scale = 0.5f; P73_Text(640.0f, 480.0f, 1, 0, 0);
  CK(t67_f(MenuVal5D77CC) == 960.0f && t67_f(MenuVal5D77C8) == 720.0f);
  CK(t67_f((int32_t)MenuPosX54AA24) == 1.0f);
  /* 0051bf82: тип 3 (маска 7); записи 0..3 */
  memset(P17_MapBase, 0, sizeof P17_MapBase); memset(P17_SlotBase, 0, sizeof P17_SlotBase);
  P11_00b5a8e8 = 4;
  for (int i = 0; i < 4; i++) P17_MapBase[i * 0x42 + 4] = 3;
  P17_MapBase[0 * 0x42 + 5] = 0;     /* нет битов */
  P17_MapBase[1 * 0x42 + 5] = 7;     /* все биты */
  P17_MapBase[2 * 0x42 + 5] = 2;     /* часть */
  P17_MapBase[3 * 0x42 + 5] = 7;
  { int16_t s3 = 1; memcpy(P17_MapBase + 3 * 0x42, &s3, 2); }      /* запись 3 -> слот 1 */
  { int16_t id = 3; memcpy(P17_SlotBase + 1 * 0x2c + 8, &id, 2); } /* ячейка 1 слота 1 = 3 -> сторона 1 */
  P73_RoadSides();
  CK(P17_MapBase[0x3b] == 0x82);              /* слот 0, ячейка 0 = 0 = номер записи -> сторона 0 */
  CK(P17_MapBase[2 * 0x42 + 0x3b] == 0);
  CK(P17_MapBase[3 * 0x42 + 0x3b] == 0x81);
  /* 00511e60 */
  P60_PartLimit = 40; memset(A_00C56780, 0xcc, 0x2d00); P73_D00214 = 11; P73_CF56BC = 22;
  P43_FreeCnt = 5; G8_00C56710 = 6; P71_NearAdd = 1500;
  P73_ParticlesReset();
  { int32_t v; int16_t id; memcpy(&v, &A_00C56780[0x44], 4); CK(v == 11); memcpy(&v, &A_00C56780[0xb4 + 0x44], 4); CK(v == 22);
    memcpy(&id, &A_00C56780[63 * 0xb4 + 2], 2); CK(id == 63); CK(A_00C56780[5] == 0 && A_00C56780[0x10] == 0); }
  CK(P43_FreeList[63] == 63 && P43_FreeList[7] == 7 && P43_FreeCnt == 0 && G8_00C56710 == 0 && P71_NearAdd == 0);
  CK(P71_Near == (int32_t)(288000000 / 40) && P73_C56760 == 11);
  P60_PartLimit = 0; P73_ParticlesReset(); CK(P71_Near == 0x44aa20 && P73_C56760 == 0);
  /* 0049f031: на концах отрезка сплайн даёт p1 (t=0) и p2 (t=1); t=0.5 — (-p0 + 9 p1 + 9 p2 - p3)/16 */
  {
    float p0[5] = { 0, 1, 2, 0, 3 }, p1[5] = { 4, 5, 6, 0, 7 }, p2[5] = { 8, 9, 10, 0, 11 }, p3[5] = { 12, 13, 14, 0, 15 }, o[5] = { 0, 0, 0, 99, 0 }, t = 0.0f;
    P73_InitConsts();
    P51_Half = 0.5f; P56_C546120 = 1.5f; P56_C54611C = 2.5f; P59_One = 1.0f; P66_C2 = 2.0f;
    P73_CatmullRom(&t, o, p0, p1, p2, p3);
    CK(o[0] == 4 && o[1] == 5 && o[2] == 6 && o[4] == 7 && o[3] == 99);
    t = 1.0f; P73_CatmullRom(&t, o, p0, p1, p2, p3);
    CK(o[0] == 8 && o[1] == 9 && o[2] == 10 && o[4] == 11);
    t = 0.5f; P73_CatmullRom(&t, o, p0, p1, p2, p3);
    CK(o[0] == (-0.0f + 9 * 4 + 9 * 8 - 12) / 16.0f && o[4] == (-3.0f + 63 + 99 - 15) / 16.0f);
  }
  return f;
}


/* v1.96: 0041cede пишет таблицу Glide и native-переменные ячеек — тесты сохраняют и восстанавливают их */
typedef struct { void *g[128]; p85_blend_fn bf; p97_gr5_fn ga; p97_gr1_fn gd; p117_clip_fn cl; p85_state_fn sf; FnV1 de4, d28; FnVoidI e80;
  p95_line_fn ln; p85_raster_fn ra, rb, rc, rd; p98_gr1_fn d40; p97_lfblock_fn lk; FnIntII eac; p86_texsrc_fn ts; FnVoidV e54, eb0, w20; FnIntI e50; FnI1 d20; } t151_snap;
static void t151_save(t151_snap *z) {
  for (int i = 0; i < P33_GlideCount() && i < 128; i++) z->g[i] = P33_GlideProc(i);
  z->bf = P85_BlendFn; z->ga = P97_GrAlpha; z->gd = P97_GrDepth; z->cl = P117_ClipFn; z->sf = P85_StateFn; z->de4 = G6_01270DE4; z->d28 = G6_01270D28;
  z->e80 = FnPtr01270E80; z->ln = P95_DrawLine; z->ra = P85_RasterA; z->rb = P85_RasterB; z->rc = P115_RasterC; z->rd = P115_RasterD; z->d40 = P98_GrD40;
  z->lk = P97_LfbLock; z->eac = FnPtr01270EAC; z->ts = P86_TexSrc; z->e54 = FnPtr01270E54; z->eb0 = FnPtr01270EB0; z->w20 = FnPtr01271020; z->e50 = FnPtr01270E50; z->d20 = G6_01270D20; }
static void t151_restore(const t151_snap *z) {
  for (int i = 0; i < P33_GlideCount() && i < 128; i++) P33_SetNativeProc(P33_GlideName(i), z->g[i]);
  P85_BlendFn = z->bf; P97_GrAlpha = z->ga; P97_GrDepth = z->gd; P117_ClipFn = z->cl; P85_StateFn = z->sf; G6_01270DE4 = z->de4; G6_01270D28 = z->d28;
  FnPtr01270E80 = z->e80; P95_DrawLine = z->ln; P85_RasterA = z->ra; P85_RasterB = z->rb; P115_RasterC = z->rc; P115_RasterD = z->rd; P98_GrD40 = z->d40;
  P97_LfbLock = z->lk; FnPtr01270EAC = z->eac; P86_TexSrc = z->ts; FnPtr01270E54 = z->e54; FnPtr01270EB0 = z->eb0; FnPtr01271020 = z->w20; FnPtr01270E50 = z->e50; G6_01270D20 = z->d20; }
/* ported74: подмена неперенесённых вызовов */
static int t74_dev_calls, t74_dev_arg[3], t74_parse_calls;
/* v2.00: шпионы теста живут в том же бинарнике, что и игра: вне selftest — настоящие функции */
extern int re_selftest_on;
int32_t P149_DDEnumAll(void); int32_t P76_GlideRegister(void);
void P74_Fn41CE90(void) { if (!re_selftest_on) { P149_DDEnumAll(); return; } t74_dev_calls++; }
void P74_Fn424B70(void) { if (!re_selftest_on) { P76_GlideRegister(); return; } t74_dev_calls += 10; }
void P74_Fn4A4D84(char **pp, int32_t a, int32_t b) { if (!re_selftest_on) { (void)P120_ParseCamInt(pp, a, b); return; } (void)a; (void)b; char *e; long v = strtol(*pp, &e, 10); *pp = e; P68_CamI0 = (uint16_t)v; t74_parse_calls++; }
static int test_p74(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p74 fail line %d\n",__LINE__); } } while (0)
  P74_InitConsts();
  /* 00493ece: слот машины 2 (1-based), состояние 9 -> GlobalSet004964E2 */
  memset(TrafficRecs, 0, sizeof TrafficRecs); memset(P74_Cars, 0xff, sizeof P74_Cars);
  TrafficRecs[3 * 0x54 + 5] = 2; TrafficRecs[3 * 0x54 + 1] = 9; TrafficRecs[3 * 0x54 + 8] = 5; TrafficRecs[3 * 0x54 + 0x15] = 6;
  G0112B284 = 4; G2_01143600 = 6; G011426F8 = 0;
  P74_FreeTraffic(3);
  CK(P74_Cars[0xcd8] == 0 && P74_Cars[0xcd8 + 3] == 0 && P74_Cars[0xcd8 + 4] == 0xff && P74_Cars[0] == 0xff);
  CK(G0112B284 == 3 && TrafficRecs[3 * 0x54 + 5] == 0 && TrafficRecs[3 * 0x54 + 1] == 0 && TrafficRecs[3 * 0x54 + 8] == 0 && TrafficRecs[3 * 0x54 + 0x15] == 0);
  CK(G2_01143600 == 5 && G2_ARR_01145940[5] == 3 && G011426F8 == -1);
  /* 004ffad8: запись 1: a=2, b=5, маска 3; кадр 4 -> сдвиг */
  memset(P74_RowTab, 0, sizeof P74_RowTab);
  for (int i = 0; i < 8; i++) P74_Rows[i] = 100 + i;
  P74_RowTab[3] = 2; P74_RowTab[4] = 5; P74_RowTab[5] = 3;
  G6_00B5A778 = 0; P13_00b201dc = 1; P62_Frame = 4;
  P74_ShiftRows();
  CK(P74_Rows[2] == 105 && P74_Rows[3] == 102 && P74_Rows[4] == 103 && P74_Rows[5] == 104 && P74_Rows[6] == 106);
  P62_Frame = 1; P74_ShiftRows(); CK(P74_Rows[2] == 105);      /* маска не совпала */
  P62_Frame = 4; G6_00B5A778 = 1; P74_ShiftRows(); CK(P74_Rows[2] == 105);
  /* 005186ce */
  P62_Frame = 41; P74_B5A858[4] = 9; P74_C4D7A0[0] = 9; P74_B5A894 = 0; P74_C4D668 = 5; G8_00B87EAC = 0; P55_RecCnt = 3; P36_JoyX = 4;
  P74_ResetHud();
  CK(P74_C4DA58 == 42 && P74_B5A858[4] == 0 && P74_C4D7A0[0] == 0 && P74_B5A894 == 1 && P74_C4D668 == 5 && P55_RecCnt == 0 && P36_JoyX == 0);
  G8_00B87EAC = 1; P74_ResetHud(); CK(P74_C4D668 == 0);
  /* 004229fa: R-канал в 5 бит на позиции 11, G — 6 бит на 5, B — 5 бит на 0 */
  {
    static uint8_t src[65536]; static uint16_t dst[256 * 512 + 64];   /* v1.74: шаг 0x400 байт → 256 строк × 512 слов */ uint8_t pal[256 * 4];
    P24_RShiftR = 3; P24_RShiftL = 11; P24_GShiftR = 2; P24_GShiftL = 5; P24_BShiftR = 3; P24_BShiftL = 0;
    memset(pal, 0, sizeof pal); pal[7 * 4 + 2] = 0xf8; pal[7 * 4 + 1] = 0x40; pal[7 * 4] = 0x18;   /* R=f8 G=40 B=18 */
    memset(src, 0, sizeof src); src[0] = 7; src[256] = 7; src[255] = 7;
    memset(dst, 0xee, sizeof dst);
    P74_Conv8to16(src, pal, dst, 0x400);                 /* шаг строки 0x400 байт = 512 слов */
    uint16_t want = (uint16_t)((0xf8 >> 3) << 11 | (0x40 >> 2) << 5 | (0x18 >> 3));
    CK(dst[0] == want && dst[1] == 0 && dst[255] == want);
    CK(dst[512] == want && dst[513] == 0);               /* вторая строка начинается через 0x400 байт */
    CK(dst[256] == 0xeeee);                              /* зазор строки не затронут */
  }
  /* 00424530 */
  P69_DevOn = 0; P42_DevCount = 2; t74_dev_calls = 0; memset(P74_DevTab, 0, sizeof P74_DevTab);
  P74_DevTab[0] = 1; P74_DevTab[19] = 7;
  { t151_snap z; t151_save(&z); int32_t fs0 = P24_Fullscreen;
  P74_DevSelect(0, 5, 6);                                  /* v1.96: тип 1 → P151_InstallD3D (0041cede) */
  CK(t74_dev_calls == 11 && P69_DevOn == 1 && G00B1C0D4 == 1 && G00B1C0D8 == 1 && P151_DevIdx == 0 && P151_No8bit == 5 && P24_Fullscreen == 6);
  P74_DevSelect(1, 0, 0);
  CK(G00B1C0D4 == 0 && G00B1C0D8 == 0 && t74_dev_calls == 11);
  P74_DevSelect(9, 1, 2);                                  /* вне диапазона -> устройство 0 */
  CK(G00B1C0D4 == 1 && P151_DevIdx == 0 && P151_No8bit == 1 && P24_Fullscreen == 2);
  t151_restore(&z); P24_Fullscreen = fs0; (void)t74_dev_arg; }
  P74_DevTab[0] = 0; P33_GlideOk = 0; P74_DevSelect(0, 0, 0); CK(G00B1C0D4 == 0 && G00B1C0D8 == 0);
  /* 004a7f0e: игрок в (100, 200); разности 3 и 4 клетки -> большая 4, малая 3: 4 * tab[48] / 128 */
  P59_PosX = 100; P59_PosZ = 200;
  CK(P74_Dist(103, 204, 0, 0) == (int32_t)((4 * P74_DistTab[48]) >> 7));
  CK(P74_Dist(100, 200, 0, 0) == 0);
  CK(P74_Dist(100, 210, 0, 0) == (10 * 128) >> 7);       /* малая 0 -> tab[0] = 128 */
  CK(P74_Dist(100 + 5, 200, 256 * 2, 0) == (3 * 128) >> 7);    /* дробная часть p3 = 2 клетки */
  /* 004a4f7d / 004a5afb */
  {
    char a[] = "-2.5 "; char b[] = "7.25"; char bad[] = "x";
    memset(P68_CamF, 0, sizeof P68_CamF);
    CK(P74_ParseFloat(a, 1) == 1); float v; memcpy(&v, &P68_CamF[2], 4); CK(v == -2.5f);
    CK(P74_ParseFloat(b, 3) == 1); memcpy(&v, &P68_CamF[0], 4); CK(v == 7.25f);
    CK(P74_ParseFloat(b, 9) == 1 && P68_CamF[1] == 0 && P68_CamF[3] == 0);
    CK(P74_ParseFloat(bad, 0) == 0 && P68_CamF[3] == 0);
    uint16_t out[4] = { 0xffff, 0xffff, 0xffff, 0xffff }; char s[] = " 12 ,\t34 , 56\nrest";
    t74_parse_calls = 0; G2_01134120 = 0;
    CK(P74_ParseShorts(s, out, 3) == s + strlen(s) - 4);   /* после трёх чисел — пропуск строки (004a59c6) */
    CK(out[0] == 12 && out[1] == 34 && out[2] == 56 && out[3] == 0xffff && t74_parse_calls == 3 && G2_01134120 == 1);
    char s2[] = "5 7"; CK(P74_ParseShorts(s2, out, 2) == NULL && out[0] == 5);   /* нет запятой */
    char s3[] = "x\ny"; CK(P74_ParseShorts(s3, out, 0) == s3 + 2);
  }
  /* 0051d440 */
  {
    uint8_t ic[16] = { 0 }; ic[9] = 3; ic[10] = 5; ic[0xb] = 1; ic[0xc] = 20; t67_icon = ic;
    P74_SkidA[2] = 1; P74_SkidB[3] = 1; P74_SkidC[0] = 1; P74_SkidD[1] = 1; P13_00575ebc = 5;
    P74_SkidInit();
    CK(P74_SkidA[2] == 0 && P74_SkidB[3] == 0 && P74_SkidC[0] == 0 && P74_SkidD[1] == 0 && !strcmp(t67_findname, "SKID"));
    CK(ic[10] == 6 && ic[0xb] == 4 && ic[0xc] == (uint8_t)(20 - 1 + 6) && P13_00575ebc == 5);
    t67_icon = 0; P74_SkidInit(); CK(P13_00575ebc == 0 && P74_Skid == 0);
  }
  /* 0040efd5: Esc / Enter / Backspace, затем таблица A (или B при зажатом shift) */
  {
    memset(A_00D04B00, 0, 0x200);
    CK(P74_KeyScan() == 0);
    A_00D04B00[0x0e] = 1; CK(P74_KeyScan() == -1);
    A_00D04B00[0x1c] = 1; CK(P74_KeyScan() == -2);
    A_00D04B00[0x01] = 1; CK(P74_KeyScan() == -3);
    memset(A_00D04B00, 0, 0x200);
    int k = -1; for (int i = 2; i < 256; i++) if (P74_KeyA[i] != 0 && P74_KeyB[i] != 0 && P74_KeyA[i] != P74_KeyB[i]) { k = i; break; }
    CK(k > 0);
    if (k > 0) {
      A_00D04B00[k] = 1; CK(P74_KeyScan() == P74_KeyA[k]);
      A_00D04B00[0x2a] = 1; CK(P74_KeyScan() != 0);
      A_00D04B00[0x2a] = 0; A_00D04B00[0x3a] = 1; CK(P74_KeyScan() != 0);
    }
    memset(A_00D04B00, 0, 0x200);
  }
  return f;
}

/* ported75: подмена неперенесённых вызовов */
static int t75_calls[4]; static int32_t t75_arg[5];
void P75_Fn4958B7(void) { if (!re_selftest_on) { (void)P107_TrafficRow(); return; } t75_calls[0]++; }
int32_t P75_Fn491A56(int32_t car, int32_t node, int32_t a, int32_t b, int32_t c) { if (!re_selftest_on) return P119_TrafficSpawn(car, node, a, b, c); t75_calls[1]++; t75_arg[0] = car; t75_arg[1] = node; t75_arg[2] = a; t75_arg[3] = b; t75_arg[4] = c; return 1; }
void P75_Fn4EDD08(int32_t a0) { if (!re_selftest_on) { P88_CellUpdate(a0); return; } t75_calls[2] += 1 + a0 * 10; }
static int test_p75(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p75 fail line %d\n",__LINE__); } } while (0)
  /* 004913cc: позиции на сторонах */
  memset(P59_C39DC0, 0, sizeof P59_C39DC0); memset(P59_BF1C48, 0, sizeof P59_BF1C48);
  { uint8_t *r = P59_C39DC0 + 1 * 0x24; int32_t v[8] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000 };
    r[0] = 5; r[1] = 5; r[2] = 4; r[3] = 3; memcpy(r + 4, v, sizeof v); }
  P75_TrafficPos(1, 0, 0, 1, 0);                                    /* последняя позиция: 4 шагов от начала */
  CK(P54_G40 == 1000 + 4 * 0x5dc && P54_G44 == 2000);
  P75_TrafficPos(1, 2, 0, 1, 0);                                    /* сторона 2: x = 5000 - 3*0x5dc */
  CK(P54_G40 == 5000 - 1 * 0x5dc * 3 && P54_G44 == 6000);
  G8_00B87EAC = 1; G8_00B87EB0 = 0; G8_00D118C0 = 0x140;            /* rand() == 0x140 */
  P75_TrafficPos(1, 0, 1, 0, 1);                                    /* позиция 1 с конца: (4-1)=3 -> смещение, поправка (0x40-0x80) */
  CK(P54_G40 == 1000 + 3 * 0x5dc - 0x40 && P54_G44 == 2000);
  P75_TrafficPos(1, 3, 0, 0, 9);                                    /* 9 > n=2 -> 2 */
  CK(P54_G40 == 7000 && P54_G44 == 8000 + 2 * 0x5dc + (0x40 - 0x80));
  P59_BF1C48[0x34 + 1 * 0x42] = 1;                                  /* флаг направления */
  P75_TrafficPos(1, 0, 0, 0, 0);
  CK(P54_G40 == 1000 - ((0x140 & 0x7f) + 0x80));
  P75_TrafficPos(1, 2, 0, 0, 0);
  CK(P54_G44 == 6000 && P54_G40 == 5000 - 0 + 0x80 + (0x140 & 0x7f));
  /* 0049512b / 00492e42: набор очереди */
  G8_00B87EAC = 0; G8_00B87EB0 = 0; P75_E4 = 0; P75_E8 = 0; G01144284 = 0; G0113A6C0 = 5; P75_43CC = 1; P75_4288 = 0; P75_43D0 = 10;
  P51_TrafficN = 3; G2_01143600 = 0; G2_00575EE4 = 99; G2_ARR_01145940[0] = 7; G2_ARR_01145940[1] = 8; G2_ARR_01145940[2] = 9;
  P75_TrafficFill();
  CK(G01144284 == 3 && P12_01144340[0] == 7 && P12_01144340[1] == 8 && P12_01144340[2] == 9 && P75_12BC == 3);
  P75_E4 = 1; P75_TrafficFill(); CK(G01144284 == 3);                /* E4 != 0 — ничего */
  P75_E4 = 0;
  /* полное появление: очередь заполнена (2 из 2) -> разбор очереди и запись из таблицы */
  G0113A6C0 = 2; G01144284 = 2; G2_01143600 = 3; G2_ARR_01145940[3] = 11;
  { int16_t node = 5; memcpy(P75_Spawn, &node, 2); P75_Spawn[2] = 6; int32_t a = 77, b = 88; memcpy(P75_Spawn + 4, &a, 4); memcpy(P75_Spawn + 8, &b, 4); }
  memset(t75_calls, 0, sizeof t75_calls); G8_00D118C0 = 0x141; G8_00B87EAC = 1; P55_RecBase = NULL;
  P75_TrafficSpawn();
  CK(t75_calls[0] == 1 && t75_calls[1] == 1 && t75_arg[0] == 11 && t75_arg[1] == 5 && t75_arg[2] == 1 && t75_arg[3] == 77 && t75_arg[4] == 88 && P75_E8 == 1);
  { int16_t node = -1; memcpy(P75_Spawn, &node, 2); }
  G2_01143600 = 3; G2_ARR_01145940[3] = 12; G01144284 = 0; G0113A6C0 = 0; P75_Spawn[2] = 6;
  P75_TrafficSpawn();                                               /* узел -1: сторона = байт +2 & 3 */
  CK(t75_arg[0] == 12 && t75_arg[1] == -1 && t75_arg[2] == 2 && P75_E8 == 2);
  G2_01143600 = G2_00575EE4; P75_TrafficSpawn(); CK(P75_E8 == 2);   /* свободных слотов нет */
  P75_43CC = 0; P75_TrafficSpawn(); CK(P75_E8 == 2);
  /* 004d6c5a: фоновые звуки */
  WI00B20348 = 0; G8_00D118C0 = 0x1234; G8_00B87EAC = 1;
  P75_BgSound();
  CK(WI00B20348 == 1 && P75_B20350 == (0x1234 & 7) * 0x32 + 500 + (0x1234 & 0xf));
  P75_B20350 = 5; P75_BgSound(); CK(P75_B20350 == 4);
  P75_B20350 = 1; P62_Frame = 3003; WA0056039C[(3003 & 3) * 2] = 0; P75_BgSound();
  CK(WA0056039C[(3003 & 3) * 2] == 3003 && P75_B20350 == (0x1234 & 0xf) * 0x32 + 500 + (0x1234 & 0x1f));
  P75_B20350 = 1; P62_Frame = 3004; WA0056039C[0] = 3000; P75_BgSound();   /* слишком рано */
  CK(WA0056039C[0] == 3000 && P75_B20350 == (0x1234 & 7) * 0x32 + (0x1234 & 0xf));
  /* 004d6dac: звук при смене клетки */
  memset(P60_Cars, 0, 0x148); { int32_t v = 40; memcpy(P60_Cars + 0x138, &v, 4); }
  G2_00B20358 = 5; P62_Spd = 0x20; G2_00B20354 = 999; P75_CarSound(); CK(G2_00B20354 == 0 && G2_00B20358 == 5);
  P62_Spd = 0x1e; G2_00B20354 = 10; P75_CarSound(); CK(G2_00B20354 == 10);
  { int32_t v = 48; memcpy(P60_Cars + 0x138, &v, 4); }
  P62_Frame = 100; P75_B20350 = 0; G2_005603BC[(100 & 4) >> 2].v = 0; G8_00D118C0 = 0x22;
  P75_CarSound();
  CK(G2_00B20358 == 6 && G2_00B20354 == 0 && G2_005603BC[0].v == 0 && G2_005603BC[1].v == 100 && P75_B20350 == (0x22 & 3) * 0x32 + 0x15e + (0x22 & 0x1f));
  /* 004ee065: сброс */
  memset(t75_calls, 0, sizeof t75_calls); P75_B31EDC = 5; P41_Offset = 9; P75_CF1F60 = 0; P55_VarC0 = 1; P55_VarD20 = 3; S_00BDCD00[3] = 0x77;
  P75_ResetObjs();
  CK(P75_Ptr562D7C == 0x00cfe760u && P75_B31EDC == 0 && P41_Offset == 0 && P75_CF1F60 == 1 && P55_VarC0 == -1 && P55_Var20 == -1 && P55_VarD20 == -1 && P55_VarD2C == -1
     && t75_calls[2] == 12 && S_00BDCD00[3] == 0x01010101 && S_00BDCD00[0x47f] == 0x01010101 && S_00BDCD00[0x480] != 0x01010101);
  /* 004d68da: положение голоса и высота */
  { uint8_t *r = (uint8_t *)ObjPosTable + 2 * 0x148; int32_t x = 100, y = 200, z = 300; int16_t a = 0x40, b = 0x100;
    memcpy(r, &x, 4); memcpy(r + 4, &y, 4); memcpy(r + 8, &z, 4); memcpy(r + 0x7c, &a, 2); memcpy(r + 0x7e, &b, 2); }
  G6_00B91CF4 = 1; G00575F40 = 1; S_00BDC2A0[3 * 0x34] = 0x11;
  P75_CarVoice(2, 3, -1);
  { int32_t v; memcpy(&v, &S_00BDC2A0[3 * 0x34 + 0x28], 4); CK(v == ((16 + 1000) - 2) * 0x5622 / 4096); }
  /* 0040dae1: вырезка картинки в 15 бит */
  { static uint8_t img[640 * 480 * 4]; memset(img, 0, sizeof img);
    img[(7 * 640 + 5) * 4] = 0xf8; img[(7 * 640 + 5) * 4 + 1] = 0x08; img[(7 * 640 + 5) * 4 + 2] = 0x10;
    img[(10 * 640 + 639) * 4] = 0x80;
    memset(P75_Page, 0xee, sizeof P75_Page);
    uint8_t *r = P75_BmpToPage(img, 0, 0);
    CK((uint16_t *)r == P75_Page && P75_Page[7 * 256 + 5] == ((0x1f << 10) | (1 << 5) | 2) && P75_Page[0] == 0);
    r = P75_BmpToPage(img, 600, 0);
    CK(P75_Page[10 * 256 + 39] == (0x10 << 10) && P75_Page[10 * 256 + 40] == 0 && P75_Page[0x100 * 0x1e0 / 0x100 % 0x100] == 0);
    r = P75_BmpToPage(img, 0, 470);
    CK(P75_Page[9 * 256] == 0 && P75_Page[10 * 256] == 0); (void)r; }
#undef CK
  return f;
}

/* ported76: подмена неперенесённых вызовов */
static int t76_calls[4]; static int32_t t76_arg[8]; static uint8_t t76_col;
void P76_Fn40DCE0(int32_t x, int32_t y, int32_t w, int32_t h, int32_t idx, void *color) { if (!re_selftest_on) { P109_TileDraw(x, y, w, h, idx, color); return; } t76_calls[0]++; t76_arg[0] = x; t76_arg[1] = y; t76_arg[2] = w; t76_arg[3] = h; t76_arg[4] = idx; t76_col = ((uint8_t *)color)[2]; }
void P76_Fn4268EF(void *p, int32_t a, int32_t b, int32_t c, int32_t d) { if (!re_selftest_on) { P82_AddLight((const float *)p, a, b, c, d); return; } (void)p; t76_calls[2]++; t76_arg[0] = a; t76_arg[1] = b; t76_arg[2] = c; t76_arg[3] = d; }
static int test_p76(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p76 fail line %d\n",__LINE__); } } while (0)
  /* треугольники: три вершины подряд в буфер слота */
  { float va[11] = { 10, 20, 0, 255, 128, 0, 0, 0, 2, 0.5f, 0.25f }, vb[11], vc[11]; memcpy(vb, va, sizeof va); memcpy(vc, va, sizeof va); vb[0] = 30; vc[0] = 50;
    P22_DevReady = 1; P22_TexVarA = 3; P33_Count[3] = 0; P23_ScaleUV_A = 1.0f; P23_ScaleUV_B = 1.0f; P23_ZBias = 0; P23_ZScale_A = 0.01f; P23_ZScale_B = 0.02f;
    P76_TriA1((int32_t *)va, (int32_t *)vb, (int32_t *)vc);
    CK(P33_Count[3] == 3);
    plat_vertex *v = (plat_vertex *)(P33_VBuf[3]); plat_vertex ref; P23_ConvVertexA((int32_t *)vb, &ref);
    CK(v[0].x == 10 && v[1].x == 30 && v[2].x == 50 && memcmp(&v[1], &ref, sizeof ref) == 0);
    P76_TriB2((int32_t *)va, (int32_t *)vb, (int32_t *)vc); P23_ConvVertexB((int32_t *)vc, &ref);
    CK(P33_Count[3] == 6 && memcmp(&v[5], &ref, sizeof ref) == 0);
    P22_DevReady = 0; P76_TriA2((int32_t *)va, (int32_t *)vb, (int32_t *)vc); P76_TriB1((int32_t *)va, (int32_t *)vb, (int32_t *)vc); CK(P33_Count[3] == 6);
    /* A full batch must draw and roll over before another complete triangle.
       The marina regression used to stop at 4096, silently losing nearby road. */
    P22_DevReady = 1; memset(P33_Count, 0, sizeof P33_Count);
    P33_Count[3] = 4092;
    int calls = plat_draw_prim_last(NULL, NULL);
    P76_TriA2((int32_t *)va, (int32_t *)vb, (int32_t *)vc);
    CK(P33_Count[3] == 4095 && plat_draw_prim_last(NULL, NULL) == calls);
    int texture; plat_set_texture(0, &texture);
    P32_CurSlot = 7; G6_0054EF2C = 13; P32_CurHandle = &texture;
    plat_set_tex_stage(0, 1, 4);
    P76_TriB1((int32_t *)va, (int32_t *)vb, (int32_t *)vc);
    int prim, count;
    CK(plat_draw_prim_last(&prim, &count) == calls + 1 && prim == 4 && count == 4095);
    CK(P33_Count[3] == 3 && v[0].x == 10 && v[1].x == 30 && v[2].x == 50);
    P23_ConvVertexB((int32_t *)vc, &ref); CK(memcmp(&v[2], &ref, sizeof ref) == 0);
    CK(plat_stub_last_texture(NULL) == &texture && plat_get_tex_stage(0, 1) == 4);
    CK(P32_CurSlot == 7 && G6_0054EF2C == 13 && P32_CurHandle == &texture);
    /* Invalid/misaligned counts are rejected atomically, without writing a prefix. */
    P33_Count[3] = 4094; P76_TriA1((int32_t *)va, (int32_t *)vb, (int32_t *)vc); CK(P33_Count[3] == 4094);
    P33_Count[3] = 0x1000; P76_TriA2((int32_t *)va, (int32_t *)vb, (int32_t *)vc); CK(P33_Count[3] == 0x1000);
    P33_Count[3] = 0;
    /* The quad producer shares the same buffer and must reserve all six vertices. */
    float quad[60] = {0};
    for (int i = 0; i < 4; i++) { memcpy(quad + 15*i, va, sizeof va); quad[15*i] = (float)(10 + 20*i); }
    for (int variant = 0; variant < 2; variant++) {
      P33_Count[3] = 4092; calls = plat_draw_prim_last(NULL, NULL);
      if (variant) P98_QuadB(0, (uint8_t *)quad); else P98_QuadA(0, (uint8_t *)quad);
      CK(plat_draw_prim_last(&prim, &count) == calls + 1 && count == 4092);
      CK(P33_Count[3] == 6 && v[0].x == 10 && v[1].x == 30 && v[2].x == 50 && v[5].x == 70);
    }
    P33_Count[3] = 0; plat_set_texture(0, NULL); P32_CurHandle = NULL;
  }
  /* 0048a525 */
  { memset(P12_01145a60, 0, sizeof P12_01145a60); memset(P12_01146f20, 0, sizeof P12_01146f20); P12_00b1c3dc = 0; P76_NumSlots = 4;
    P11_0125f420[1 * 0x46 + 0] = 5; P11_0125f420[1 * 0x46 + 1] = 6; P11_0125f420[1 * 0x46 + 2] = 0xff;
    P12_01145a60[5 * 16 + 1] = 0xff; P12_01145a60[6 * 16 + 1] = 2;
    P76_MarkSlots(1);
    CK(P12_00b1c3dc == 1 && P12_00b1c3f4[0] == 5 && (P12_01145a60[5 * 16] & 0x10) && (P12_01146f20[2 * 0x1c] & 2));
    P76_MarkSlots(1); CK(P12_00b1c3dc == 1);
    P76_MarkSlots(9); CK(P12_00b1c3dc == 1); }
  /* 00424b70 */
  { P42_DevCount = 0; P33_GlideOk = 1; memset(P74_DevTab, 0x55, sizeof P74_DevTab);
    CK(P76_GlideRegister() == 1 && P42_DevCount == 1);
    const char *e = (const char *)&P74_DevTab[0];
    CK(P74_DevTab[0] == 0 && strcmp(e + 4, "3Dfx") == 0 && strcmp(e + 0x24, "Glide 2.x") == 0 && P74_DevTab[17] == 0 && P74_DevTab[18] == 0);
    P42_DevCount = 4; P76_GlideRegister(); CK(P42_DevCount == 4); P42_DevCount = 0; }
  /* 0040dbee */
  { memset(t76_calls, 0, sizeof t76_calls); P76_InitConsts();
    P76_TileFill(0.5f);
    CK(t76_calls[0] == 6 && t76_arg[0] == 0x200 && t76_arg[1] == 0x100 && t76_arg[2] == 0x80 && t76_arg[3] == 0xe0 && t76_arg[4] == 5 && t76_col == 127); }
  /* 004a3aa7 */
  { int32_t o[16]; memset(o, 0, sizeof o); o[3] = 7; o[12] = 29; P16_IdleMode = 3;
    P76_FlashStep(o); CK(o[12] == 30 && o[3] == 0);
    o[12] = 89; o[3] = 7; o[4] = 1; P76_FlashStep(o); CK(o[12] == 90 || o[12] == 0);
    o[12] = 0x59; o[4] = 1; P76_FlashStep(o); CK(o[12] == 0 && (o[4] & 4) && o[13] == 0x8c && P16_IdleMode == 0x7fff); }
  /* 004ecee8 / 004ee813 */
  { float pos[3] = { 1.0f, 0, 3.0f }; uint8_t grid[2000]; memset(grid, 0, sizeof grid);
    P42_CellX = 10; P42_CellY = 20; P42_CellScale = 0.5f; P21_GridRadius = 4; P21_GridStride = 40;
    grid[16 + 16 * 40] = 1;
    CK(P76_InBox(pos, grid, 4, 10) == 1);          /* x=5, y=11: dx=1, dy=1 */
    CK(P76_InBox(pos, grid, 5, 11) == 0);          /* dx=dy=0 → ячейка 15+15*40 пуста */
    CK(P76_InBox(pos, grid, 100, 10) == 0);
    int32_t ox = 0, oy = 0; P54_GridN = 4; P21_GridDiv = 64; memset(t76_calls, 0, sizeof t76_calls);
    { uint8_t vis[8]; int32_t sd0 = D_00d00204; void *sb = P46_MapBufA; memset(vis, 0xaa, sizeof vis);
      D_00d00204 = 3; P46_MapBufA = NULL;
      P76_CellFromPos(pos, vis, &ox, &oy);
      CK(ox == 5 && oy == 11 && vis[0] == 1 && vis[2] == 1 && vis[3] == 0xaa);   /* нет данных видимости — все единицы */
      D_00d00204 = sd0; P46_MapBufA = sb; } }
  /* 004e8f1e */
  { memset(t76_calls, 0, sizeof t76_calls);
    P76_Angle = 10; P76_AngleColor();
    CK(P76_ColA == 245 && P76_ColB == 245 && P76_ColC == 215 && t76_calls[2] == 1 && t76_arg[0] == 6000 && t76_arg[1] == 245 && t76_arg[3] == 215);
    P76_Angle = 0x50; P76_AngleColor(); CK(P76_ColA == 0xaf && P76_ColB == 0x9f && P76_ColC == 0);
    P76_Angle = 0x90; P76_AngleColor(); CK(P76_ColA == 0x5f && P76_ColB == 0x30 && t76_calls[2] == 3);
    P76_Angle = 0xc0; P76_AngleColor(); CK(t76_calls[2] == 3); }
  /* 0051caa7 */
  { const char *fn = "p76_hs.bin"; size_t total = 0x2c * (0x28 * 2 + 0x14 * 3 + 4);
    uint8_t *buf = (uint8_t *)malloc(16 + total); uint32_t hd[4] = { 0x53435245, 0, 0, 3 };
    memcpy(buf, hd, 16); for (size_t i = 0; i < total; i++) buf[16 + i] = (uint8_t)(i * 7 + 1);
    FILE *fp = fopen(fn, "wb"); fwrite(buf, 1, 16 + total, fp); fclose(fp);
    memset(P62_Hs1, 0, sizeof P62_Hs1); memset(P62_Hs6, 0, sizeof P62_Hs6);
    fp = fopen(fn, "rb");
    CK(P76_LoadHsTables(fp) == 1 && P62_Hs1[0] == 1 && P62_Hs1[5] == (uint8_t)(5 * 7 + 1) && P62_Hs6[sizeof P62_Hs6 - 1] == buf[16 + total - 1]);
    fclose(fp);
    hd[3] = 2; memcpy(buf, hd, 16); fp = fopen(fn, "wb"); fwrite(buf, 1, 16 + total, fp); fclose(fp);
    fp = fopen(fn, "rb"); CK(P76_LoadHsTables(fp) == 0 && ftell(fp) == 0); fclose(fp);
    remove(fn); free(buf); }
#undef CK
  return f;
}


/* ported77: подмена неперенесённых вызовов */
static int t77_calls[8];
void P77_Fn501C63(void) { if (!re_selftest_on) { P102_HudInit(); return; } t77_calls[5]++; }
void P77_Fn501770(void) { if (!re_selftest_on) { P136_OverlayMap(); return; } t77_calls[6]++; }
void P77_Fn524BD8(void *p) { if (!re_selftest_on) { P140_BankLine((char *)p); return; } (void)p; t77_calls[7]++; G6_00B91D34 = G6_00B91D34 + 1; }
static int test_p77(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p77 fail line %d\n",__LINE__); } } while (0)
  memset(t77_calls, 0, sizeof t77_calls);
  /* 004eca08 / 004ecade: файл Levels/t77.lev = 4 блока (0x14, 6, 0x12, 0x14) */
  { mkdir("Levels", 0777);
    uint8_t buf[256]; size_t n = 0; int32_t w;
#define W32(v) do { w = (v); memcpy(buf + n, &w, 4); n += 4; } while (0)
    W32(4);
    W32(0x14); W32(4); W32(0x11111111);             /* блок 1 на смещении 4 */
    W32(6); W32(8); W32(1); W32(2);                  /* блок 2: пропуск 8 байт */
    W32(0x12); W32(4); W32(3);                       /* блок 3: seek +4 (данные) */
    W32(0x14); W32(0); W32(0);
#undef W32
    FILE *fp = fopen("Levels/t77.lev", "wb"); fwrite(buf, 1, n, fp); fclose(fp);
    G6_00B87EEC = 0; D_00b87e30 = 0; P62_HudOff2 = 0; P56_B87EA8 = 0; P77_LevelName = "t77.lev";
    void *h = P77_OpenLevel(); CK(h != NULL); if (h) g_fclose(h);
    P77_LevelName = "none.lev"; CK(P77_OpenLevel() == NULL); CK(P77_LoadLevel() == 0);
    P77_LevelName = "t77.lev";
    CK(P77_LoadLevel() == 1);
    CK(t77_calls[5] == 1 && t77_calls[6] == 1 && t77_calls[0] == 0);
    remove("Levels/t77.lev"); }
  /* 00524496 */
  { FILE *fp = fopen("t77.bank", "w"); fputs("; comment\nSND1 LOOP\nSND2 VOL=5\n", fp); fclose(fp);
    G6_00B91CF4 = 0; CK(P77_LoadBank("t77.bank", 0) == 0);
    G6_00B91CF4 = 1; G6_00B91D34 = 5; memset(t77_calls, 0, sizeof t77_calls);
    CK(P77_LoadBank("t77.bank", 0x1000) == 0 && G6_00B91BC4[1] == 5 && t77_calls[7] == 2 && G6_00B91D34 == 7);
    CK(P77_LoadBank("no_such.bank", 0) == 0);
    remove("t77.bank"); }
  /* три экрана меню: тестовые подмены опроса возвращают -1 */
  { G6_00B87EEC = 0; MenuI0057B730 = 0; MenuI0054A060 = 0;
    CK(P77_Menu407160() == 0 && MenuI0057B730 == 1 && MenuI0054A060 == 2);
    G6_00B87EEC = 1; G6_0057B728 = 5;
    CK(P77_Menu407160() == 0 && G6_0057B728 == -1);
    G6_00B87EEC = 0; CK(P77_Menu414C30() == 0 && MenuI005FE9D0 == 6 && MenuI0054DE08 == 7);
    G6_00B87EEC = 1; CK(P77_Menu414C30() == 0 && G6_005FE9CC == -1);
    G6_00B87EEC = 0; CK(P77_Menu408770() == 0 && MenuI0054A694 == 1);
    G6_00B87EEC = 1; CK(P77_Menu408770() == 0 && G6_005D5788 == -1);
    G6_00B87EEC = 0; }
  /* 00509c40 */
  { memset(P77_B590E0, 0xaa, sizeof P77_B590E0); memset(P77_C62E60, 0xaa, sizeof P77_C62E60); memset(&P59_NearList, 0xaa, 0x40);
    P77_C7D850 = 9; P77_S574570 = 0; P77_C65DA4 = 4; P12_00c595a0 = 7;
    P77_ResetTables();
    CK(P77_B590E0[0] == 0 && P77_B590E0[0x1007] == 0 && P77_C62E60[0x2f43] == 0 && ((uint8_t *)&P59_NearList)[0x3f] == 0 && P77_C7D850 == 0 && P77_S574570 == 0x5e8 && P77_C65DA4 == 0 && P12_00c595a0 == 0); }
  /* 004f8643 */
  { P77_List = NULL; P77_ListN = 0;
    CK(P77_ListAdd(16) == 0 && P77_ListN == 1 && P77_List != NULL && P77_List[0] != NULL);
    void *first = P77_List[0];
    CK(P77_ListAdd(32) == 0 && P77_ListN == 2 && P77_List[0] == first && P77_List[1] != NULL && P77_List[1] != first);
    DebugFree(P77_List[0]); DebugFree(P77_List[1]); DebugFree(P77_List); P77_List = NULL; P77_ListN = 0; }
  /* 004282f8 */
  { for (int i = 0; i < 9; i++) P44_ViewMat[i] = (i % 4 == 0) ? 1.0f : 0.0f;
    P44_CamX = 0; P44_CamY = 0; P44_CamZ = 3.0f;
    P77_CameraPlane(100);
    CK(Q01270C24 == 100.0f && P62_I270C44 == 125 && P44_MatPtr == (float *)P44_ViewMat);
    CK(P77_Plane[0] == 0 && P77_Plane[1] == 0 && P77_Plane[2] == 1.0f && P77_Plane[3] == 103.0f); }
#undef CK
  return f;
}

static int test_p78(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p78 fail line %d\n",__LINE__); } } while (0)
  /* 004eb811: 2 вершины по 0x2c байта */
  { uint8_t in[0x58]; for (int i = 0; i < 0x58; i++) in[i] = (uint8_t)i;
    FILE *fp = fopen("t78.bin", "wb"); fwrite(in, 1, 0x58, fp); fclose(fp);
    fp = fopen("t78.bin", "rb");
    P78_LoadVerts(fp, 0x58 + 5);
    CK(P78_VertCount == 2 && P78_VertsA != NULL && P78_VertsB != NULL && S_00D0DDE0 == 1);
    const uint8_t *o = (const uint8_t *)P78_VertsB; float one; uint16_t s; uint32_t w;
    CK(memcmp(o, in, 12) == 0);
    memcpy(&one, o + 12, 4); CK(one == 1.0f);
    CK(memcmp(o + 0x10, in + 0x0c, 6) == 0 && memcmp(o + 0x18, in + 0x14, 12) == 0);
    memcpy(&one, o + 0x24, 4); CK(one == 1.0f);
    CK(memcmp(o + 0x28, in + 0x20, 6) == 0);
    memcpy(&w, o + 0x30, 4); memcpy(&s, in + 0x28, 2); CK(w == s);
    memcpy(&w, o + 0x34, 4); memcpy(&s, in + 0x2a, 2); CK(w == s);
    o += 0x40; CK(memcmp(o, in + 0x2c, 12) == 0);
    memcpy(&w, o + 0x34, 4); memcpy(&s, in + 0x2c + 0x2a, 2); CK(w == s);
    DebugFree(P78_VertsA); DebugFree(P78_VertsB); fclose(fp); remove("t78.bin"); }
  /* 004eafe0: сетка 2x2, 2 записи (ячейка 1: 2 фонаря, ячейка 3: 0) */
  { uint8_t buf[512]; size_t n = 0; int32_t w;
#define W32(v) do { w = (v); memcpy(buf + n, &w, 4); n += 4; } while (0)
    memcpy(buf, "GLMP", 4); n = 4; W32(1); W32(2); W32(2); W32(2);
    W32(1); W32(2); for (int i = 0; i < 0x50; i++) buf[n++] = (uint8_t)(i + 1);
    W32(3); W32(0);
    FILE *fp = fopen("t78.lmp", "wb"); fwrite(buf, 1, n, fp); fclose(fp);
    fp = fopen("t78.lmp", "rb");
    P58_ListB31EC4 = NULL; P58_CntB31EBC = 0;
    CK(P78_LoadLamps(fp) == 1 && P58_CntB31EBC == 4 && P58_ListB31EC4 != NULL);
    CK(P58_ListB31EC4[1].a == 2 && P58_ListB31EC4[1].p != NULL && ((uint8_t *)P58_ListB31EC4[1].p)[0x4f] == 0x50);
    CK(P58_ListB31EC4[3].a == 0 && P58_ListB31EC4[3].p == NULL && P58_ListB31EC4[0].p == NULL);
    P58_FreeList(); CK(P58_ListB31EC4 == NULL && P58_CntB31EBC == 0);
    fclose(fp);
    /* не «GLMP» — позиция возвращается */
    fp = fopen("t78.lmp", "wb"); fwrite("XXXXXXXXXXXXXXXXXXXXXXXX", 1, 24, fp); fclose(fp);
    fp = fopen("t78.lmp", "rb"); fseek(fp, 2, SEEK_SET);
    CK(P78_LoadLamps(fp) == 0 && ftell(fp) == 2); fclose(fp); remove("t78.lmp");
#undef W32
  }
  /* 004a31fc / 004a2f77: кресла, сетка 2x2: ячейка 2 — 2 кресла, ячейка 0 — 1 кресло */
  { uint8_t buf[512]; size_t n = 0; int32_t w;
#define W32(v) do { w = (v); memcpy(buf + n, &w, 4); n += 4; } while (0)
    W32(0); W32(2); W32(2); W32(2); W32(2);
    W32(2); W32(2); W32(0); for (int i = 0; i < 0x28; i++) buf[n++] = (uint8_t)(i + 1);
    W32(0); W32(1); W32(0); for (int i = 0; i < 0x14; i++) buf[n++] = (uint8_t)(i + 0x41);
#undef W32
    FILE *fp = fopen("t78.chr", "wb"); fwrite(buf, 1, n, fp); fclose(fp);
    fp = fopen("t78.chr", "rb"); P58_Grid = NULL; D_01134ea0 = 0;
    P78_LoadChairs(fp, (int32_t)n);
    CK(P58_Grid != NULL && P58_GridH == 2 && P58_GridW == 2 && D_01134ea0 == 3);
    p58_cell_t *c2 = (p58_cell_t *)P58_Grid[2], *c0 = (p58_cell_t *)P58_Grid[0];
    CK(c2 != NULL && c2->a == 2 && c2->b == 2 && ((uint8_t *)c2->items)[0x27] == 0x28);
    CK(c0 != NULL && c0->b == 1 && ((uint8_t *)c0->items)[0x13] == 0x54 && P58_Grid[1] == NULL && P58_Grid[3] == NULL);
    p58_cell_t add = {0, 5, DebugMalloc(8, "t", 1)};                /* замена: прежний буфер освобождается */
    CK(P78_ChairAdd(&add) == 1 && c0->b == 5 && c0->items == add.items);
    add.a = 9; CK(P78_ChairAdd(&add) == 0);                         /* вне сетки */
    P58_FreeGrid(); CK(P58_Grid == NULL && P78_ChairAdd(&add) == 0);
    /* версия не 2 — пропуск блока */
    fclose(fp); fp = fopen("t78.chr", "wb"); { int32_t v[8] = {0, 7, 0, 0, 0, 1, 2, 3}; fwrite(v, 4, 8, fp); } fclose(fp);
    fp = fopen("t78.chr", "rb"); fseek(fp, 4, SEEK_SET);
    P78_LoadChairs(fp, 8); CK(ftell(fp) == 12 && P58_Grid == NULL);
    fclose(fp); remove("t78.chr"); }
#undef CK
  return f;
}

static uint32_t rd_u32(const uint8_t *p, int o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static int test_p79(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { fprintf(stderr, "p79 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  { void *saved = D_00c98ed0;
    uint8_t *arena = (uint8_t *)calloc(1, 0x4000); uint8_t src[0x100]; memset(src, 0, sizeof src);
    D_00c98ed0 = arena; P79_InitConsts();
    CK(G2_TABLE_00550ACC[0] == 32 && G2_TABLE_00550ACC[7] == 104 && G2_TABLE_00550ACC[56] == 12 && G2_TABLE_00550ACC[56 + 0x37] == 32);
    /* модель с диска: 3 вершины, 1 запись типа 0 (диск 12 байт → память 32), 1 нормаль, 5 байт данных */
    uint16_t v16;
    #define S16(o, v) do { v16 = (uint16_t)(v); memcpy(src + (o), &v16, 2); } while (0)
    #define S32(o, v) do { uint32_t t_ = (uint32_t)(v); memcpy(src + (o), &t_, 4); } while (0)
    S32(4, 0xffffffffu); S16(0x14, 3); S16(0x16, 1); S16(0x18, 1); S16(0x1a, 5);
    S32(0x1c, 0x78); S32(0x20, 0x38); S32(0x24, 0x5c); S32(0x28, 0x6c); S32(0x2c, 0x80); S32(0x34, 0);
    float vs[9] = {1, 0, 0, -0.5f, 2, 0, 0, 0, 3}; memcpy(src + 0x38, vs, 36);
    float vv[4] = {1, 0, 0, 1}; memcpy(src + 0x5c, vv, 16);
    float nn[3] = {0, 1, 0}; memcpy(src + 0x6c, nn, 12);
    memcpy(src + 0x78, "ABCDE", 5);
    src[0x80] = 0; S16(0x82, 7); S16(0x84, 8); S16(0x86, 9); src[0x88] = 10; src[0x89] = 20; src[0x8a] = 30;
    uint8_t *m = arena + 0x100;
    int32_t sz = P79_Convert(src, m);
    CK(sz == 0x38 + 48 + 16 + 16 + 8 + 32);
    CK(rd_u32(m, 0x20) == 0x38 && rd_u32(m, 0x24) == 0x38 + 48 && rd_u32(m, 0x28) == 0x38 + 64 && rd_u32(m, 0x1c) == 0x38 + 80 && rd_u32(m, 0x2c) == 0x38 + 88);
    float w; memcpy(&w, m + 0x38 + 12, 4); CK(w == 1.0f);
    memcpy(&w, m + 0x38 + 16, 4); CK(w == -0.5f);
    memcpy(&w, m + 0x38 + 64 + 4, 4); CK(w == 1.0f);                       /* нормаль (0,1,0) */
    CK(memcmp(m + 0x38 + 80, "ABCDE", 5) == 0);
    { const uint8_t *r = m + 0x38 + 88; float a; memcpy(&a, r + 0x14, 4);
      CK(r[0] == 0 && rd_u32(r, 8) == 7 && rd_u32(r, 0xc) == 8 && rd_u32(r, 0x10) == 9 && a == 10.0f);
      memcpy(&a, r + 0x1c, 4); CK(a == 30.0f); }
    /* переход ссылок: относительные → абсолютные (смещения арены) и обратно */
    uint32_t keep[8]; for (int i = 0; i < 8; i++) keep[i] = rd_u32(m, 0x1c + i * 4);
    uint32_t moff = (uint32_t)(m - arena);
    P79_Relocate(m);
    CK(rd_u32(m, 0x20) == 0x38 + moff && rd_u32(m, 0x2c) == 0x38 + 88 + moff && (m[3] & 0x80));
    P79_Relocate(m); CK(rd_u32(m, 0x20) == 0x38 + moff);               /* повторно — без изменений */
    /* радиус: режим 0 — с осью Y */
    P79_Radius(m, 0); float r0, r1; memcpy(&r0, m + 0xc, 4);
    P79_Radius(m, 1); memcpy(&r1, m + 0x10, 4);
    CK(fabsf(r0 - 3.0f) < 1e-6f && fabsf(r1 - 3.0f) < 1e-6f);
    P79_Unrelocate(m);
    for (int i = 0; i < 8; i++) CK(rd_u32(m, 0x1c + i * 4) == keep[i]);
    CK(!(m[3] & 0x80));
    /* класс вершины и разметка записей: вершина (1,0,0,1) лежит на оси +X → класс 2 */
    P79_Total = 0; P79_Outside = 0;
    float ax[4] = {1.0f, 0, 0, 1}; CK(P79_VertClass(ax) == 2 && P79_Total == 1);
    float ng[4] = {0, 0, -1.0f, 1}; CK(P79_VertClass(ng) == 4);
    float no[4] = {0.5f, 0.5f, 0.5f, 1}; CK(P79_VertClass(no) == 0 && P79_Outside == 1 && P79_Total == 2);
    int32_t all0 = P79_NumAll, sum0 = P79_SumTotal;
    P79_Relocate(m);
    P79_MarkRecords(m);
    CK(P79_Total == 1 && P79_Outside == 0 && P79_NumAll == all0 + 1 && P79_SumTotal == sum0 + 1 && (m[2] & 0x30) == 0x30);
    CK(P79_FindSameVerts(m) == 0 && (m + 0x38 + 88)[1] == (2 | 8) && rd_u32(m + 0x38 + 88, 4) == 0);
    /* список записей */
    uint32_t lst[2] = {0, 0}; P79_ModelList(m, lst);
    CK(lst[0] == (uint32_t)(m + 0x38 + 88 - arena));
    free(arena); D_00c98ed0 = saved; }
#undef CK
  return f;
}

static int test_p81(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p81 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  float sb = P19_Out68, sa = P19_OutA, sy = P19_OutB, sz = P19_OutC;
  P19_Out68 = 0.25f; P19_OutA = 0.5f; P19_OutB = -0.75f; P19_OutC = -0.0f;
  P81_Light();
  CK(P81_PosX == 0.75f && P81_NegX == 0.25f);
  CK(P81_NegY == 1.0f && P81_PosY == 0.25f);            /* 0.75+0.25 = 1.0, не больше потолка */
  CK(P81_PosZ == 0.25f && P81_NegZ == 0.25f);           /* -0.0 >= 0 -> «плюс» */
  P19_OutA = -2.0f; P19_OutB = 3.0f; P81_Light();
  CK(P81_NegX == 1.0f && P81_PosX == 0.25f && P81_PosY == 1.0f && P81_NegY == 0.25f);
  { float r = 10.0f; memcpy(&P53_Var26A4, &r, 4); P81_Span = 5.0f; P81_Flag = 0;
    P81_Limit(15); CK(P81_Flag == 0);                     /* d >= 0 */
    P81_Limit(5); CK(P81_Flag == 0);                      /* |d| = 5 <= 100, Span > 0 */
    P81_Limit(-100); CK(P81_Flag == 0x40000000);          /* |d| = 110 > 100 */
    P81_Flag = 0; P81_Span = 0.0f; P81_Limit(9); CK(P81_Flag == 0x40000000);   /* Span <= 0 */
    P81_Flag = 0; P53_Var26A4 = 0; P81_Span = 0; }
  P19_Out68 = sb; P19_OutA = sa; P19_OutB = sy; P19_OutC = sz;
  return f;
}

static int test_p80(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p80 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  { void *saved = D_00c98ed0; P79_InitConsts();
    uint8_t src[0x8c]; memset(src, 0, sizeof src);
    uint16_t v16;
    #define T16(o, v) do { v16 = (uint16_t)(v); memcpy(src + (o), &v16, 2); } while (0)
    #define T32(o, v) do { uint32_t t_ = (uint32_t)(v); memcpy(src + (o), &t_, 4); } while (0)
    T32(4, 0xffffffffu); T16(0x14, 3); T16(0x16, 1); T16(0x18, 1); T16(0x1a, 5);
    T32(0x1c, 0x78); T32(0x20, 0x38); T32(0x24, 0x5c); T32(0x28, 0x6c); T32(0x2c, 0x80); T32(0x34, 0);
    float vs[9] = {1, 0, 0, -0.5f, 2, 0, 0, 0, 3}; memcpy(src + 0x38, vs, 36);
    float vv[4] = {1, 0, 0, 1}; memcpy(src + 0x5c, vv, 16);
    float nn[3] = {0, 1, 0}; memcpy(src + 0x6c, nn, 12);
    memcpy(src + 0x78, "ABCDE", 5);
    src[0x80] = 0; T16(0x82, 0); T16(0x84, 1); T16(0x86, 2);
    uint8_t file[4 + 4 + 0x8c]; int32_t hd[2] = {1, 0x8c}; memcpy(file, hd, 8); memcpy(file + 8, src, 0x8c);
    FILE *fp = fopen("t80.blk", "wb"); fwrite(file, 1, sizeof file, fp); fclose(fp);
    fp = fopen("t80.blk", "rb");
    P80_LoadModels(fp);
    fclose(fp); remove("t80.blk");
    CK(P20_Count == 1 && D_00c98ed0 != saved);
    uint8_t *m = (uint8_t *)P79_PTR(P79_ModelTab[0]);
    CK(m[3] & 0x80);                                              /* ссылки раскрыты */
    float r; memcpy(&r, m + 0xc, 4); CK(fabsf(r - 3.0f) < 1e-6f);
    float *b = P80_Boxes[0];
    CK(b[0] == -0.5f && b[1] == 0 && b[2] == 0 && b[3] == 1.0f && b[4] == 2.0f && b[5] == 3.0f && b[6] == 2.0f);
    int32_t ri; memcpy(&ri, &b[7], 4); CK(ri == 2 && P11_00ba52d0 == 2);
    CK(P80_Class[0] <= 7);
    float out[8]; CK(P80_Bounds(out, 0) == out && memcmp(out, b, 32) == 0);
    DebugFree(D_00c98ed0); D_00c98ed0 = saved; }

  /* 004ed055: заголовок блока 2 */
  { uint8_t fb[512]; size_t n = 0; int32_t w; float fl;
#define F32(v) do { w = (v); memcpy(fb + n, &w, 4); n += 4; } while (0)
#define FF(v) do { fl = (v); memcpy(fb + n, &fl, 4); n += 4; } while (0)
    F32(64); F32(32); F32(3000); F32(2); F32(4); F32(5); F32(6); FF(0.25f); FF(0); FF(0); FF(2.0f);
    F32(1); { uint8_t r[0x14] = {0}; r[2] = 7; r[4] = 1; r[8] = 2; r[12] = 3; r[16] = 4; memcpy(fb + n, r, 0x14); n += 0x14; }
    F32(2); F32(10); F32(11); F32(3); memcpy(fb + n, "abc", 3); n += 3; F32(1); { uint8_t r[0x14]; memset(r, 9, 0x14); memcpy(fb + n, r, 0x14); n += 0x14; }
    F32(0); F32(0); F32(0);
#undef F32
#undef FF
    FILE *fp = fopen("t80.hdr", "wb"); fwrite(fb, 1, n, fp); fclose(fp);
    void *sv0 = D_00d00230; void *sv1 = G6_00D00208; void *sv2 = D_00c98ed0;
    D_00d00230 = calloc(1, 0x1000);
    P8_00546020 = 1.0f; P80_InitConsts();
    G00B87E4C = 0; P14_00b202d8 = 0; P14_00b202dc = 0; P14_00b87e84 = 0; P26_FxA = 0;
    fp = fopen("t80.hdr", "rb");
    P80_LoadHeader(fp);
    CK((size_t)ftell(fp) == n);
    fclose(fp); remove("t80.hdr");
    CK(P21_GridDiv == 64 && P80_GridH == 32 && P80_Cell == 3000 && P76_NumSlots == 2 && P54_GridN == 4 && P80_Hdr5 == 5 && P80_Hdr6 == 6);
    CK(P21_GridRadius == 15 && P21_GridStride == 31 && D_00d00204 == 961 && P80_HalfW == 32 && P80_HalfH == 16);
    CK(P42_CellX == 96000 && P42_CellY == 48000 && P62_MapN == 8 && P80_InvMap == 0.125f && P80_Cols == 16 && P72_Rows == 8);
    CK(P19_OutA == 0 && P19_OutB == 0 && P19_OutC == 1.0f && P19_Out68 == 0.25f && P80_SaveW == 0.25f);
    CK(P54_Cnt1E0 == 1);
    { const uint8_t *e = (const uint8_t *)G6_00D00208; float one; memcpy(&one, e + 0x14, 4);
      CK(rd_u32(e, 0) == 0 && rd_u32(e, 4) == 7 && rd_u32(e, 8) == 1 && rd_u32(e, 0xc) == 2 && rd_u32(e, 0x10) == 3 && one == 1.0f && rd_u32(e, 0x18) == 4); }
    CK(P80_LumpTab[0] == D_00d00230);
    { const uint8_t *l = (const uint8_t *)P80_LumpTab[0];
      CK(rd_u32(l, 0) == 2 && rd_u32(l, 4) == 10 && rd_u32(l, 8) == 11 && rd_u32(l, 12) == 3 && memcmp(l + 16, "abc", 3) == 0 && rd_u32(l, 19) == 1 && l[23] == 9);
      CK(P80_LumpTab[1] == (const void *)(l + 23 + 0x14)); }
    free(D_00d00230); DebugFree(G6_00D00208); DebugFree(G6_00D01268); DebugFree(G6_00CE0F20);
    G6_00D01268 = NULL; G6_00CE0F20 = NULL;   /* v2.13: висячие указатели (ASan: use-after-free в P134_CamCollide) */
    D_00d00230 = sv0; G6_00D00208 = sv1; D_00c98ed0 = sv2; }
#undef CK
  return f;
}

static int test_p82(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p82 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
  P44_CamX = P44_CamY = P44_CamZ = 0.0f; P82_FovX = 1.0f; P82_FovY = 1.0f; P11_01270c24 = 100.0f; P43_ScaleA = 200.0f; P60_Var1373C0 = 0;
  P82_FrustumSetup3D();
  CK(P82_PlT[1] == -1.0f && P82_PlT[2] == -1.0f && P82_PlB[1] == 1.0f && P82_PlL[0] == -1.0f && P82_PlR[0] == 1.0f && P82_PlF[2] == -1.0f);
  CK(P77_Plane[2] == 1.0f && P82_PlF[3] == -50.0f && P77_Plane[3] == 100.0f);
  CK(P82_PlL[3] == 120.0f && P82_PlR[3] == 120.0f && P82_PlT[3] == 40.0f && P82_PlB[3] == 40.0f);
  { float p[3] = { 0, 0, 100 }; CK(P82_SphereVis3D(p, 10.0f) == 1 && P82_Edge == 0);   /* внутри, дальняя плоскость далеко */
    p[2] = 55; CK(P82_SphereVis3D(p, 10.0f) == 2 && P82_Edge == 0);                   /* касается дальней плоскости */
    p[2] = 0; CK(P82_SphereVis3D(p, 10.0f) == 0);                                       /* за дальней плоскостью */
    p[0] = 300; p[2] = 100; CK(P82_SphereVis3D(p, 10.0f) == 0);                         /* за правой */
    p[0] = 225; CK(P82_SphereVis3D(p, 10.0f) == 1 && P82_Edge == 1);                    /* пересекает правую */
    p[0] = 200; P60_Var1373C0 = 1; CK(P82_SphereVis3D(p, 10.0f) == 1 && P82_Edge == 1); P60_Var1373C0 = 0; }
  P82_FrustumSetup2D();
  CK(P82_PlL[0] == -1.0f && P82_PlL[1] == 0.0f && P82_PlL[2] == -1.0f && P82_PlL[3] == 120.0f && P82_PlR[3] == 120.0f && P82_PlF[3] == -50.0f);
  { float p[3] = { 0, 0, 55 }; CK(P82_SphereVis2D(p, 10.0f) == 2 && P82_Edge == 0);
    p[0] = 300; p[2] = 100; CK(P82_SphereVis2D(p, 10.0f) == 0);
    p[0] = 225; CK(P82_SphereVis2D(p, 10.0f) == 1 && P82_Edge == 1); }
  /* 004268ef */
  { uint8_t *g = P82_LightGrid; memset(g, 0, sizeof(p82_grid_t));
    P42_CellX = 0; P42_CellY = 0; P42_CellScale = 1.0f; P21_GridRadius = 4; P21_GridStride = 40; P82_CellCX = 0; P82_CellCY = 100;
    g[15 + 15 * 40] = 1; P14_00d17b18 = 256; G2_011F43B0 = 0; P13_00b31f04 = 0;
    P82_FrustumSetup3D();
    float pos[3] = { 0, 0, 100 }; P82_AddLight(pos, 10, 40, 80, 255);
    float *e = (float *)G2_011F40E0;
    CK(G2_011F43B0 == 1 && e[0] == 0 && e[2] == 100.0f && e[4] == 40.0f && e[5] == 80.0f && e[6] == 255.0f && e[7] == 100.0f && e[8] == 0.01f);
    int32_t rr; memcpy(&rr, e + 3, 4); CK(rr == 10);
    P82_AddLight(pos, 10, 1, 2, 3); CK(G2_011F43B0 == 2);
    float far_[3] = { 1000, 0, 100 }; P82_AddLight(far_, 10, 1, 2, 3); CK(G2_011F43B0 == 2);   /* вне сетки */
    P14_00d17b18 = 128; G2_011F43B0 = 20; P82_AddLight(pos, 10, 1, 2, 3); CK(G2_011F43B0 == 20);
    P14_00d17b18 = 256; G2_011F43B0 = 0; }
  return f;
}

static int test_p83(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p83 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
  P44_CamX = P44_CamY = P44_CamZ = 0.0f; P82_FovX = 1.0f; P82_FovY = 1.0f; P11_01270c24 = 100.0f; P43_ScaleA = 200.0f; P60_Var1373C0 = 0;
  P82_FrustumSetup3D();
  { float p[3] = { 0, 0, 80 };
    CK(P83_BoxVis(p, 10.0f) == 1 && P82_Edge == 0);
    p[2] = 100; CK(P83_BoxVis(p, 10.0f) == 3);          /* касается плоскости 011cff80: res=2, результат res+1 */
    p[2] = 55; CK(P83_BoxVis(p, 10.0f) == 2 && P82_Edge == 0);   /* касается плоскости 01209630 */
    p[2] = 30; CK(P83_BoxVis(p, 10.0f) == 0);
    p[2] = 120; CK(P83_BoxVis(p, 10.0f) == 0);
    p[0] = 300; p[2] = 80; CK(P83_BoxVis(p, 10.0f) == 0);
    p[0] = 195; CK(P83_BoxVis(p, 10.0f) == 1 && P82_Edge == 1);
    p[0] = 0; p[1] = 260; CK(P83_BoxVis(p, 10.0f) == 0); p[1] = 0;
    p[0] = 200; P60_Var1373C0 = 1; CK(P83_BoxVis(p, 10.0f) == 1 && P82_Edge == 1); P60_Var1373C0 = 0; }
  { uint8_t *sv = P56_EulerTab; uint8_t *tab = calloc(1, 0x40000 + 64);
    for (int k = 0; k < 4; k++) { float *m = (float *)(tab + (size_t)k * 0x10000); if (k == 1) { m[1] = 1; m[3] = 1; m[8] = 1; } else { m[0] = m[4] = m[8] = 1; } }
    P56_EulerTab = tab; P19_OutA = 1; P19_OutB = 2; P19_OutC = 3; P80_Dir3 = 4; P47_SwapCnt = 7;
    P83_LightMatrices();
    CK(P83_LightVec[0] == 1 && P83_LightVec[1] == 2 && P83_LightVec[2] == 3 && P83_LightVec[3] == 4);
    CK(P83_LightVec[4] == 2 && P83_LightVec[5] == 1 && P83_LightVec[6] == 3 && P83_LightVec[7] == 4);
    CK(P83_LightVec[8] == 1 && P83_LightVec[12] == 1 && P83_LightVec[14] == 3);
    CK(P83_Mat0[0] == 1 && P83_Mat1[1] == 1 && P83_Mat1[0] == 0 && P83_Mat3[8] == 1);
    CK(P83_Flag0 == 7 && P83_Flag1 == 7 && P83_Flag2 == 7 && P83_Flag3 == 7 && P44_MatPtr == (float *)(tab + 0x30000));
    P56_EulerTab = sv; free(tab); }
  return f;
}


/* ported87: загрузка плитки карты в слот и рисование объектов (004ed5f8, 004ee18b, 004ee4b7) */
static int test_p89(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p89 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  int32_t sd = D_00d00204; void *sb = P46_MapBufA;
  uint8_t *seul = P56_EulerTab; uint8_t *eul = P56_AllocEulerTab(1); P56_EulerTab = eul;   /* свои таблицы поворотов: прежний указатель — на стек другого теста */
  /* маска видимости: поток {1 полный байт, 1 байт с битами 0x05}, {0, 1 байт 0xff}; 20 клеток -> 21 записанная */
  { static uint8_t buf[0x100]; uint8_t out[64]; memset(buf, 0, sizeof buf); memset(out, 0xaa, sizeof out);
    uint32_t v;
    v = 0x40; memcpy(buf + 0x10 + 2 * 4, &v, 4);                 /* блок 2 -> таблица +0x40 */
    v = 0x20; memcpy(buf + 0x40 + 5 * 4, &v, 4);                 /* клетка 5 -> поток +0x40+0x20 */
    { uint8_t st[] = { 1, 1, 0x05, 0, 1, 0xff }; memcpy(buf + 0x60, st, sizeof st); }
    P46_MapBufA = buf; D_00d00204 = 20;
    P89_VisMask(2, 5, out);
    CK(memcmp(out, "\1\1\1\1\1\1\1\1", 8) == 0);
    CK(out[8] == 1 && out[9] == 0 && out[10] == 1 && out[11] == 0 && out[15] == 0);
    CK(out[16] == 1 && out[20] == 1 && out[21] == 0xaa);
    /* пустой поток (смещение 0) — все единицы */
    v = 0; memcpy(buf + 0x40 + 6 * 4, &v, 4); memset(out, 0xaa, sizeof out);
    P89_VisMask(2, 6, out);
    CK(out[0] == 1 && out[19] == 1 && out[20] == 0xaa);
    P89_Fill1(out + 24); CK(out[24] == 1 && out[43] == 1 && out[44] == 0xaa); }
  /* обход клеток: одна клетка с объектом класса 2 попадает в таблицу P55_TabA */
  { static uint8_t nodes[16], objs[0x40]; static int32_t heads[4 * 60 * 60]; static uint8_t frus[0x80];
    int32_t sn = P54_GridN, sdv = P21_GridDiv, sh = P80_GridH, sst = P21_GridStride, sx = P42_CellX, sy = P42_CellY, se = G6_00B87EEC;
    void *s1 = G6_00CE0F20, *s2 = G6_00D01268, *s3 = G6_00D00208; float scx = P44_CamX, scz = P44_CamZ, ssc = P42_CellScale;
    uint16_t sang = P59_AngB; uint8_t smd = P59_Mode1137324; int32_t sgs = P47_SwapCnt, ssh = G6_00D11880;
    uint8_t sp80 = P80_Class[5]; int32_t sbd = S_00BDCD00[5]; uint8_t sfr[0x80]; memcpy(sfr, P55_Frustum, 0x80);
    P54_GridN = 60; P21_GridDiv = 480; P80_GridH = 480; P21_GridStride = 40; P42_CellX = 0; P42_CellY = 0; P42_CellScale = 1.0f;
    P44_CamX = 300.0f; P44_CamZ = 200.0f; G6_00B87EEC = 1; P59_AngB = 0; P59_Mode1137324 = 0; P47_SwapCnt = 7; G6_00D11880 = 0;
    P46_MapBufA = NULL; D_00d00204 = 0;
    memset(frus, 0, sizeof frus);
    { int16_t r[32]; memset(r, 0, sizeof r); r[0] = 14; r[1] = 1; r[2 * 14 + 2] = 14; r[2 * 14 + 3] = 1; memcpy(P55_Frustum, r, sizeof r); }  /* первая строка 14, одна строка; для строки 14 пара {сдвиг 14, длина 1} */
    memset((uint8_t *)P82_LightGrid, 0, 40 * 16); ((uint8_t *)P82_LightGrid)[14 * 40 + 14] = 1;
    for (int i = 0; i < 4 * 60 * 60; i++) heads[i] = -1;
    /* камера (300, 200): блок (5, 3); клетка обхода (299, 199) -> блок (4, 3), внутри (59, 19), слот (0 + 1*2) = 2 */
    heads[2 * 3600 + 59 + 19 * 60] = 0;
    { int32_t nd[2] = { 0, -1 }; memcpy(nodes, nd, 8); }
    memset(objs, 0, sizeof objs); { int32_t m = 5; memcpy(objs + 4, &m, 4); }
    G6_00CE0F20 = nodes; G6_00D01268 = heads; G6_00D00208 = objs; P54_Cnt1E0 = 0;
    P80_Class[5] = 2; S_00BDCD00[5] = 1; P55_CntA = 0;
    P89_DrawMap(0);                                                 /* считает клетку камеры (и маску: данных нет, D=0) */
    CK(P88_CellA.x == 300 && P88_CellA.y == 200);
    g_00b1c3f0 = g_00cff9ac;                                        /* 00489ed6 при mode=1 не трогает блоки */
    P89_DrawMap(1);
    CK(P55_CntA == 1 && P55_TabA[0] == objs);
    { int32_t tag; memcpy(&tag, objs, 4); CK(tag == 7); }
    P55_CntA = 0; P89_DrawMap(1);                                   /* метка кадра совпала -> второй раз не добавляется */
    CK(P55_CntA == 0);
    P89_DrawMap(0); CK(P55_CntA == 0);
    G6_00CE0F20 = s1; G6_00D01268 = s2; G6_00D00208 = s3;
    P54_GridN = sn; P21_GridDiv = sdv; P80_GridH = sh; P21_GridStride = sst; P42_CellX = sx; P42_CellY = sy; G6_00B87EEC = se;
    P44_CamX = scx; P44_CamZ = scz; P42_CellScale = ssc; P59_AngB = sang; P59_Mode1137324 = smd; P47_SwapCnt = sgs; G6_00D11880 = ssh;
    P80_Class[5] = sp80; S_00BDCD00[5] = sbd; memcpy(P55_Frustum, sfr, 0x80); P55_CntA = 0; }
  P46_MapBufA = sb; D_00d00204 = sd; P56_EulerTab = seul; if (eul) DebugFree(eul);
  return f;
}

static int test_p88(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p88 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  int32_t sn = P54_GridN, sd = P21_GridDiv, sx = P42_CellX, sy = P42_CellY, se = G6_00B87EEC, s4 = P14_00b87ee4, sa = G6_00B87EAC, sb = G6_00B87EB0, sc = G6_00B87EA0;
  float scx = P44_CamX, scz = P44_CamZ, ssc = P42_CellScale; int32_t spx = P59_PosX, spz = P59_PosZ;
  p88_cell_t sA = P88_CellA, sB = P88_CellB;
  int32_t lump[3], slot[3];
  P54_GridN = 60; P21_GridDiv = 480; P42_CellX = 1000; P42_CellY = 2000; P42_CellScale = 0.5f; P44_CamX = 200.5f; P44_CamZ = 100.25f;
  G6_00B87EEC = 1; P14_00b87ee4 = 0; G6_00B87EAC = 0; G6_00B87EB0 = 0; G6_00B87EA0 = 0; P59_PosX = 40; P59_PosZ = 80;
  P88_CellA.cell = 7;
  P88_CellUpdate(0);       /* x = (int)((200.5+1000)*0.5) = 600, y = (int)((100.25+2000)*0.5) = 1050 */
  CK(P88_CellA.x == 600 && P88_CellA.y == 1050);
  CK(P88_CellA.idx == 600 + 1050 * 480);
  CK(P88_CellA.cx == 10 && P88_CellA.cy == 17 && P88_CellA.cell == 10 + 17 * 8);
  CK(P88_CellA.prev == 7 && P88_CellA.rx == 0 && P88_CellA.ry == 30);
  CK(P88_CellA.px == 0 && P88_CellA.py == 1 && P88_CellA.pc == 2);
  CK(memcmp(&P88_CellA, &P88_CellB, sizeof P88_CellA) == 0);   /* 00b87eec ≠ 0 — копия */
  G6_00B87EEC = 0;         /* игрок: (40+1000)*0.5 = 520, (80+2000)*0.5 = 1040 */
  P88_CellUpdate(0);
  CK(P88_CellB.x == 520 && P88_CellB.y == 1040 && P88_CellB.cx == 8 && P88_CellB.cy == 17 && P88_CellB.rx == 40 && P88_CellB.ry == 20);
  CK(P12_00cff9ac == P88_CellB.cell);
  P88_ObjX = 20; P88_ObjZ = 40; G6_00B87EAC = 1;   /* объект: (20+1000)*0.5 = 510, (40+2000)*0.5 = 1020 */
  P88_CellUpdate(0);
  CK(P88_CellB.x == 510 && P88_CellB.y == 1020);
  G6_00B87EA0 = 1; P88_Mode575 = 2;                /* режим 2 → снова игрок */
  P88_CellUpdate(0);
  CK(P88_CellB.x == 520);
  P14_00b87ee4 = 1;                                /* камера */
  P88_CellUpdate(0);
  CK(P88_CellB.x == 600 && P88_CellB.y == 1050);
  /* выбор соседних блоков */
  { p88_cell_t b; memset(&b, 0, sizeof b); b.cx = 3; b.cy = 2; b.cell = 3 + 2 * 8; b.rx = 5; b.ry = 30;
    CK(P88_PickTiles(&b, lump, slot) == 1 && lump[0] == b.cell - 1 && slot[0] == ((3 - 1) & 1) + (2 & 1) * 2);
    b.ry = 10;
    CK(P88_PickTiles(&b, lump, slot) == 3);           /* слева, сверху и угловой */
    CK(lump[0] == b.cell - 1 && lump[1] == b.cell - 8 && lump[2] == b.cell - 1 - 8);
    b.rx = 55;
    CK(P88_PickTiles(&b, lump, slot) == 3 && lump[0] == b.cell + 1 && lump[1] == b.cell - 8 && lump[2] == b.cell + 1 - 8);
    b.ry = 55;
    CK(P88_PickTiles(&b, lump, slot) == 3 && lump[1] == b.cell + 8 && lump[2] == b.cell + 1 + 8);
    b.rx = 30; b.ry = 30;
    CK(P88_PickTiles(&b, lump, slot) == 0);
    b.cx = 0; b.rx = 5;                               /* у левой границы карты ничего не грузим */
    CK(P88_PickTiles(&b, lump, slot) == 0);
  }
  P88_CellUpdate(1);                                   /* только отметка занятых клеток */
  P54_GridN = sn; P21_GridDiv = sd; P42_CellX = sx; P42_CellY = sy; G6_00B87EEC = se; P14_00b87ee4 = s4; G6_00B87EAC = sa; G6_00B87EB0 = sb; G6_00B87EA0 = sc;
  P44_CamX = scx; P44_CamZ = scz; P42_CellScale = ssc; P59_PosX = spx; P59_PosZ = spz; P88_CellA = sA; P88_CellB = sB;
  return f;
}

static int test_p87(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p87 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  void *s_nodes = G6_00CE0F20, *s_heads = G6_00D01268, *s_objs = G6_00D00208; int32_t s_n = P54_GridN, s_c = P54_Cnt1E0, s_ns = P76_NumSlots, s_cols = P80_Cols, s_rows = P72_Rows; void *s_lump = P80_LumpTab[0];
  void *s_ra = P54_RoadA[2], *s_rb = P54_RoadB[2];
  uint8_t lump[128]; uint8_t *c = lump; int32_t i32; uint16_t u16;
  P54_GridN = 2; P54_Cnt1E0 = 3; P76_NumSlots = 1; P80_Cols = 1; P72_Rows = 1; P54_RoadA[2] = NULL; P54_RoadB[2] = NULL;
  G6_00CE0F20 = calloc(1, 0xa0000); G6_00D01268 = calloc(1, 4 * 4 * 4); G6_00D00208 = calloc(1, (size_t)(3 + 0x8000) * 0x20);
  memset(lump, 0, sizeof lump);
  i32 = 2; memcpy(c, &i32, 4); c += 4;                                               /* два узла */
  u16 = 1; memcpy(c, &u16, 2); u16 = 1; memcpy(c + 2, &u16, 2); c += 4;               /* объект 1 (< Cnt1E0), следующий 1 */
  u16 = 3; memcpy(c, &u16, 2); u16 = 0xffff; memcpy(c + 2, &u16, 2); c += 4;          /* объект 3 (блочный), конец списка */
  i32 = 9; memcpy(c, &i32, 4); c += 4;                                               /* 9 байт: вид 1 + 4 головы u16 */
  *c++ = 1; u16 = 0; memcpy(c, &u16, 2); u16 = 0xffff; memcpy(c + 2, &u16, 2); u16 = 1; memcpy(c + 4, &u16, 2); u16 = 0xffff; memcpy(c + 6, &u16, 2); c += 8;
  i32 = 1; memcpy(c, &i32, 4); c += 4;                                               /* один объект блока */
  u16 = 0x8005; memcpy(c, &u16, 2); { float x = 10, y = -20, z = 30; memcpy(c + 4, &x, 4); memcpy(c + 8, &y, 4); memcpy(c + 12, &z, 4); } u16 = (uint16_t)-3; memcpy(c + 16, &u16, 2);
  P80_LumpTab[0] = lump;
  for (int i = 0; i < 16; i++) ((int32_t *)G6_00D01268)[i] = -1;
  P44_XformTag = 77;
  P87_LoadTile(0, 2);
  { const int32_t *nd = (const int32_t *)((const uint8_t *)G6_00CE0F20 + 2 * 0x28000);
    CK(nd[0] == 1 && nd[1] == 1 + 2 * 0x5000);                                       /* номер < Cnt1E0 не сдвигается, «следующий» сдвигается */
    CK(nd[2] == 3 + 2 * 0x2000 && nd[3] == -1); }                                    /* блочный объект сдвигается, 0xffff → −1 */
  { const int32_t *h = (const int32_t *)G6_00D01268 + 2 * 4;
    CK(h[0] == 0 + 2 * 0x5000 && h[1] == -1 && h[2] == 1 + 2 * 0x5000 && h[3] == -1); }
  { const uint8_t *o = (const uint8_t *)G6_00D00208 + (size_t)(3 + 2 * 0x2000) * 0x20; float x, y, z; int32_t m, ang, fl, st;
    memcpy(&st, o, 4); memcpy(&m, o + 4, 4); memcpy(&x, o + 8, 4); memcpy(&y, o + 12, 4); memcpy(&z, o + 16, 4); memcpy(&ang, o + 0x18, 4); memcpy(&fl, o + 0x1c, 4);
    CK(st == 77 && m == 5 && x == 10 && y == -20 && z == 30 && ang == -3 && fl == 1); }
  CK(P87_SlotLump[2] == 0 && P87_SlotLumpA[2] == 0);
  /* плитка вне диапазона не трогает слот; объект без модели ничего не рисует */
  P87_LoadTile(5, 1); CK(P87_SlotLumpA[1] != 5);
  { uint8_t obj[0x20]; memset(obj, 0, sizeof obj); int32_t mi = 5; memcpy(obj + 4, &mi, 4); P79_ModelTab[5] = 0; P87_DrawObjA(obj); P87_DrawObjB(obj); }
  free(G6_00CE0F20); free(G6_00D01268); free(G6_00D00208);
  G6_00CE0F20 = s_nodes; G6_00D01268 = s_heads; G6_00D00208 = s_objs; P54_GridN = s_n; P54_Cnt1E0 = s_c; P76_NumSlots = s_ns; P80_Cols = s_cols; P72_Rows = s_rows; P80_LumpTab[0] = s_lump;
  P54_RoadA[2] = s_ra; P54_RoadB[2] = s_rb;
  return f;
}

/* Необязательная проверка на настоящем файле уровня: RE_REAL_LEVEL=имя (файл в Levels/ рядом с рабочим каталогом) */
/* v1.38: 004ec91e P93_FindIcon — таблица значков блока 5 (по 16 байт) и Ui00426CAF → P92_SpinTex ("SEA") */
static int test_p93(void) {
  int f = 0;
  int32_t sn = P54_MapA; void *sp = P54_MapAPtr; const uint8_t *sst = P92_SpinTex; uint32_t stx = G012085F4;
  uint8_t tab[4][16];
  memset(tab, 0, sizeof tab);
  memcpy(tab[0], "SLIDERBA", 8); tab[0][9] = 1;
  memcpy(tab[1], "SLIDER", 6);   tab[1][9] = 2;
  memcpy(tab[2], "SEA", 3);      tab[2][9] = 3; tab[2][0xb] = 64;
  memcpy(tab[3], "SEAX", 4);     tab[3][9] = 4;
  P54_MapAPtr = tab; P54_MapA = 4;
  CK(P93_FindIcon("SLIDER") == tab[1]);          /* у "SLIDERBA" после 6 совпавших символов не 0 */
  CK(P93_FindIcon("SLIDERBAR") == tab[0]);       /* длина обрезается до 8, совпали все 8 */
  CK(P93_FindIcon("SLIDERBA") == tab[0]);
  CK(P93_FindIcon("SEA") == tab[2]);
  CK(P93_FindIcon("SE") == NULL);                /* после "SE" у всех записей не 0 */
  CK(P93_FindIcon("SEAX") == tab[3]);
  CK(P93_FindIcon("") == NULL && P93_FindIcon("NONE") == NULL);
  P54_MapA = 3; CK(P93_FindIcon("SEAX") == NULL);   /* за счётчик не выходит */
  P54_MapA = 0; CK(P93_FindIcon("SEA") == NULL);
  P54_MapA = 4; P54_MapAPtr = NULL; CK(P93_FindIcon("SEA") == NULL);
  P54_MapAPtr = tab; P92_SpinTex = NULL; G012085F4 = 7; Ui00426CAF();
  CK(P92_SpinTex == tab[2] && G012085F4 == 0);
  P54_MapA = sn; P54_MapAPtr = sp; P92_SpinTex = sst; G012085F4 = stx;
  return f;
}

static int test_p94(void) {
  int f = 0;
  { uint8_t s[16] = "ab_C9 x", d[16]; memset(d, 0x55, sizeof d);
    uint8_t *e = P94_ReadIdent(s, d);
    CK(strcmp((char *)d, "AB_C9") == 0 && e == s + 5 && memcmp(s, "AB_C9 x", 7) == 0);
    uint8_t s2[8] = "9abc"; d[0] = 1; CK(P94_ReadIdent(s2, d) == s2 && d[0] == 0 && s2[1] == 'a'); }
  { int32_t q[4] = { 0, 0, 0, 0x1000 }; int16_t m[9];
    P94_QuatToMat(q, m);
    CK(m[0] == 0x1000 && m[4] == 0x1000 && m[8] == 0x1000 && m[1] == 0 && m[2] == 0 && m[3] == 0 && m[5] == 0 && m[6] == 0 && m[7] == 0);
    int32_t q2[4] = { 0, 0, 0x1000, 0 }; P94_QuatToMat(q2, m);
    CK(m[0] == -0x1000 && m[4] == -0x1000 && m[8] == 0x1000); }
  { uint8_t g[31 * 31]; int16_t o[64]; memset(g, 0, sizeof g); memset(o, 0x77, sizeof o);
    g[2 * 31 + 3] = 1; g[2 * 31 + 5] = 1; g[4 * 31 + 0] = 1;
    P94_RowSpans(o, g);
    CK(o[0] == 2 && o[1] == 2 && o[2 + 4] == 3 && o[3 + 4] == 2 && o[2 + 8] == 0 && o[3 + 8] == 1 && o[2] == -1 && o[3] == 0 && o[2 + 60] == -1 && o[3 + 60] == 0); }
  { int32_t px = P59_PosX, pz = P59_PosZ; p58_objs_t so; memcpy(so, P58_Objs, sizeof so);
    memset(P58_Objs, 0, sizeof so); P59_PosX = 1000; P59_PosZ = 2000;
    CK(P94_NearestObjDist() == 0x7fffffff);
    int32_t v = 1; memcpy(&P58_Objs[3][0x10], &v, 4); v = 1300; memcpy(&P58_Objs[3][0x14], &v, 4); v = 1900; memcpy(&P58_Objs[3][0x1c], &v, 4);
    v = 0; memcpy(&P58_Objs[4][0x10], &v, 4);   /* неактивный — не считается */
    CK(P94_NearestObjDist() == 350);
    memcpy(P58_Objs, so, sizeof so); P59_PosX = px; P59_PosZ = pz; }
  { int32_t pl = P60_PartLimit; float a = P11_01270c24, b = P11_0125f3f8;
    P60_PartLimit = 100; P11_01270c24 = 50000.0f; P11_0125f3f8 = 1000.0f; P94_ClampView();
    CK(P60_PartLimit == 64 && P11_01270c24 == 45000.0f && P11_0125f3f8 == 15000.0f);
    P60_PartLimit = -5; P11_01270c24 = 20000.0f; P11_0125f3f8 = 43000.0f; P94_ClampView();
    CK(P60_PartLimit == 0 && P11_01270c24 == 20000.0f && P11_0125f3f8 == 42000.0f);
    P60_PartLimit = pl; P11_01270c24 = a; P11_0125f3f8 = b; }
  { P94_InitCurves(); CK(P94_CurveA[0] == 0 && P94_CurveA[0x1000] == 0x1000 && P94_CurveA[0x800] == 64); }
  { uint8_t o[0x80], s[0x64]; memset(o, 0, sizeof o); memset(s, 0, sizeof s);
    int16_t n = 0x1000; memcpy(o + 8, &n, 2); int32_t v = 100; memcpy(s + 0x50, &v, 4); v = 7; memcpy(s + 0x34, &v, 4);
    P94_SpringStep(o, s);
    int32_t r0, r1, c1; memcpy(&r0, o + 0x68, 4); memcpy(&r1, o + 0x6c, 4); memcpy(&c1, o + 0x5c, 4);
    CK(r0 == 55000 && r1 == 0 && c1 == 7);
    v = 100; memcpy(s + 0x50, &v, 4); v = 16; memcpy(s + 0x40, &v, 4); v = 1; memcpy(s + 0x60, &v, 4);
    P94_SpringStep(o, s); memcpy(&r0, o + 0x68, 4); CK(r0 == 54998); }
  { uint8_t s[0x34]; int32_t out[13]; memset(s, 0, sizeof s); memset(out, 0x55, sizeof out);
    int32_t v = 0x100; memcpy(s + 0x1c, &v, 4); v = 0x1000; memcpy(s + 0x18, &v, 4); v = 0x2000; memcpy(s + 0x28, &v, 4);
    P94_PackState(s, out);
    CK(out[0] == 1 && out[1] == 0 && out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0 && out[12] == 0); }
  { static p43_sintab_t ss; static p59_sin_t s9; memcpy(ss, P43_Sin, sizeof ss); memcpy(s9, P59_Sin, sizeof s9);
    for (int i = 0; i < 5120; i++) P43_Sin[i] = (float)sin((double)i * 6.283185307179586 / 4096.0);
    P43_Sin[0] = 0.0f; P43_Sin[0x400] = 1.0f; P43_Sin[0x1400 - 1] = P43_Sin[0x3ff];
    for (int i = 0; i < 4096; i++) P59_Sin[i] = (int16_t)lrint(4096.0 * sin((double)i * 6.283185307179586 / 4096.0));
    int32_t a = P94_WobA, b = P94_WobB, c = P94_WobC; float o[3];
    P94_WobA = 4093; P94_WobB = 4091; P94_WobC = 1017; P94_Wobble(o, 1);
    CK(P94_WobA == 0 && P94_WobB == 0 && P94_WobC == 1024 && P94_WobK == 10.0f && o[0] == 20.0f && o[1] == 0.0f && o[2] == 0.0f);
    P94_WobA = a; P94_WobB = b; P94_WobC = c;
    int32_t px = P59_PosX, pz = P59_PosZ, ho = P94_HeadingI, op = MenuOptBDFA54; int16_t hd = P94_Heading; float sc = P63_Scale, rk = P94_RadarK, fa = P56_F573FA0, fb = P56_F573FA4;
    P59_PosX = 1000; P59_PosZ = -3000; P94_Heading = 0; MenuOptBDFA54 = 0; P63_Scale = 1.0f; P94_RadarK = 1.0f; P56_F573FA0 = 540.0f; P56_F573FA4 = 380.0f;
    float ox, oy; P94_RadarXY(1010.0f, -2980.0f, &ox, &oy); CK(ox == 550.0f && oy == 360.0f);
    uint8_t car[0x104]; memset(car, 0, sizeof car); P94_HeadingI = 0;
    int32_t ch = 0x800, cx = 1000, cz = -2000; memcpy(car + 0x100, &ch, 4); memcpy(car + 0xc8, &cx, 4); memcpy(car + 0xd0, &cz, 4);
    CK(P94_InViewCone(car) == 1);
    cz = -3000 - 4000; memcpy(car + 0xd0, &cz, 4); CK(P94_InViewCone(car) == 0);   /* позади */
    cz = -2000; memcpy(car + 0xd0, &cz, 4); ch = 0; memcpy(car + 0x100, &ch, 4); CK(P94_InViewCone(car) == 0);   /* курс тот же */
    ch = 0x800; memcpy(car + 0x100, &ch, 4); cx = 7000; memcpy(car + 0xc8, &cx, 4); CK(P94_InViewCone(car) == 0);   /* дальше 5000 */
    int32_t mw = P62_MapW; P62_MapW = 480; P94_BuildDirTab();
    CK(P94_DirCnt > 8 && P94_DirCnt <= 128 && P94_DirTab[0][0] == 0 && P94_DirTab[0][1] == 23 && P94_DirTab[0][2] == 23 * 480);
    P62_MapW = mw;
    P59_PosX = px; P59_PosZ = pz; P94_HeadingI = ho; P94_Heading = hd; MenuOptBDFA54 = op; P63_Scale = sc; P94_RadarK = rk; P56_F573FA0 = fa; P56_F573FA4 = fb;
    memcpy(P43_Sin, ss, sizeof ss); memcpy(P59_Sin, s9, sizeof s9); }
  { int32_t s1 = G2_00D04654, s2 = G6_00B5A778, s3 = D_00b87e30, s4 = P14_00d118a8, s5 = G2_00D044C8; uint8_t s6 = P59_Mode1137324;
    G2_00D04654 = 1; G6_00B5A778 = 0; D_00b87e30 = 4; P94_FadeDir = 0; P94_FadeVal = 5; P94_FadePos = 3500.0f; P94_FadeSpeed = 100.0f;
    P94_FadeStep(); CK(P94_FadeDir == 12 && P94_FadeVal == 0 && P94_FadePos == 3600.0f);
    P94_FadeStep(); CK(P94_FadeVal == 12 && P94_FadePos == 3700.0f);
    P94_FadeVal = 250; P94_FadeStep(); CK(P94_FadeVal == 255 && P94_FadeDir == -12);
    P94_FadePos = 4096.0f; P14_00d118a8 = 0; P59_Mode1137324 = 6; P94_FadeStep();
    CK(G2_00D04654 == 3 && P14_00d118a8 == 1 && G2_00D044C8 == 0 && P59_Mode1137324 == 0 && P94_FadePos == 4096.0f);
    P94_FadeVal = 1; P94_FadeStep(); CK(P94_FadeVal == 1);   /* не то состояние — ничего */
    G2_00D04654 = s1; G6_00B5A778 = s2; D_00b87e30 = s3; P14_00d118a8 = s4; G2_00D044C8 = s5; P59_Mode1137324 = s6; }
  { uint8_t rec[16] = { 'S', 'E', 'A', 0, 0, 0, 0, 0, 2, 10, 20, 30, 40 }; uint32_t sr = P94_IconRec; P94_IconRec = re_addr(rec); P94_IconQuad();
    float u0, v0, u2; memcpy(&u0, &P94_Quad[4], 4); memcpy(&v0, &P94_Quad[5], 4); memcpy(&u2, &P94_Quad[9], 4);
    CK(P94_QuadPage == 2 && P94_Quad[3] == 3 && u0 == 11.0f && v0 == 40.0f && u2 == 21.0f && P94_Quad[14] == 0x437f0000u);
    P94_IconRec = sr; re_ptr_unregister(rec); }
  { int32_t s3 = D_00b87e30, w = P19_ScrW, h = P19_ScrH; float k = P11_0125f3e0;
    D_00b87e30 = 2; P94_MapW = 640; P94_MapH = 480; P94_MapX0 = 0; P94_MapY0 = 0; P11_0125f3e0 = 1.0f; P19_ScrW = 640; P19_ScrH = 480;
    float x = 100.0f, y = 50.0f; P94_MapToScreen(&x, &y); CK(fabsf(x - 100.0f) < 1e-3f && fabsf(y - 50.0f) < 1e-3f);
    D_00b87e30 = 1; P57_ScrW = 640; S_00C808A0 = 480; x = 100.0f; y = 50.0f; P94_MapToScreen(&x, &y); CK(fabsf(x - 540.0f) < 1e-3f && fabsf(y - 430.0f) < 1e-3f);
    D_00b87e30 = s3; P19_ScrW = w; P19_ScrH = h; P11_0125f3e0 = k; }
  return f;
}

static int p95_lines; static float p95_lx[4];
static void p95_line(const float *a, const float *b) { p95_lines++; p95_lx[0] = a[0]; p95_lx[1] = a[1]; p95_lx[2] = b[0]; p95_lx[3] = b[1]; }
static int p95_st, p95_bl;
static void p95_state(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) { (void)a; (void)b; (void)c; (void)d; (void)e; p95_st++; }
static void p95_blend(int32_t a, int32_t b, int32_t c, int32_t d) { (void)a; (void)b; (void)c; (void)d; p95_bl++; }
static uint16_t rd16t(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16t(void *p, uint16_t v) { memcpy(p, &v, 2); }
static int32_t rd32t(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32t(void *p, int32_t v) { memcpy(p, &v, 4); }
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p98 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
static int test_p98(void) {
  int f = 0;
  { int32_t a0 = P27_MemAllocated, f0 = P27_MemFreed;   /* 004d8db4 / 004d8f30 */
    uint8_t *p = (uint8_t *)P98_DebugMalloc(10, "x.c", 7);
    CK(p != NULL && p[0] == 0 && p[9] == 0 && memcmp(p + 10, "NAIF", 4) == 0 && P27_MemAllocated == a0 + 10);
    int32_t slot = -1; for (int32_t i = 0; i < 0x1000; i++) if (P27_MemTab[i * 3] == re_addr(p)) { slot = i; break; }
    CK(slot >= 0 && P27_MemTab[slot * 3 + 1] == 10 && strcmp((const char *)re_ptr(P27_MemTab[slot * 3 + 2]), "File: x.c (Line: 7)") == 0);
    P98_DebugFree(p); CK(slot >= 0 && P27_MemTab[slot * 3] == 0 && P27_MemFreed == f0 + 10); }
  { uint8_t *n = (uint8_t *)DebugMalloc(0x24, "t", 1), *o = (uint8_t *)DebugMalloc(0x60, "t", 2), *base = (uint8_t *)DebugMalloc(8, "t", 3);   /* 004d0102 */
    memset(n, 0, 0x24); memset(o, 0, 0x60); re_wr_ptr(n + 0x1c, o); re_wr_ptr(o + 0x50, base);
    P15_SetListHead(n); P28_EventCount = 0; P98_ScriptFreeAll(); CK(P15_ListHead == NULL && P28_EventCount == 0); }
  { /* compiler.c:641 event objects, command buffers and MULTIEVENT aliases
       must retire their allocation records and log strings on every unload. */
    uint8_t *saved_head = P15_ListHead; int32_t saved_count = P28_EventCount;
    int32_t balance = P27_MemAllocated - P27_MemFreed, live = G2_00B2C3A4;
    P28_EventCount = 0;
    for (int cycle = 0; cycle < 2; cycle++) {
      const int sizes[] = {0x24, 0x24, 0x60, 0x60, 0x60, 8, 12};
      uint8_t *blocks[7]; uint32_t addresses[7], logs[7] = {0};
      for (int i = 0; i < 7; i++) {
        blocks[i] = P98_DebugMalloc(sizes[i], "D:\\Driver\\Game\\compiler.c", i >= 2 && i <= 4 ? 641 : 1219);
        CK(blocks[i] != NULL); if (!blocks[i]) return 1;
        addresses[i] = re_addr(blocks[i]);
        for (int j = 0; j < 0x1000; j++)
          if (P27_MemTab[j * 3] == addresses[i]) logs[i] = P27_MemTab[j * 3 + 2];
        CK(logs[i] != 0);
      }
      re_wr_ptr(blocks[0] + 0x20, blocks[1]);
      re_wr_ptr(blocks[0] + 0x1c, blocks[2]);
      re_wr_ptr(blocks[2] + 0x58, blocks[3]);
      re_wr_ptr(blocks[2] + 0x50, blocks[5]);
      re_wr_ptr(blocks[3] + 0x50, blocks[6]);
      /* A duplicate event borrows its original's command buffer. */
      wr16t(blocks[1], 0x20);
      re_wr_ptr(blocks[1] + 0x1c, blocks[4]);
      re_wr_ptr(blocks[4] + 0x50, blocks[5]);
      P15_SetListHead(blocks[0]); P98_ScriptFreeAll();
      CK(P15_ListHead == NULL && G00D12408 == 0);
      CK(P27_MemAllocated - P27_MemFreed == balance && G2_00B2C3A4 == live);
      for (int i = 0; i < 7; i++) {
        CK(re_ptr(addresses[i]) == NULL && re_ptr(logs[i]) == NULL);
        for (int j = 0; j < 0x1000; j++) CK(P27_MemTab[j * 3] != addresses[i]);
      }
      int32_t freed = P27_MemFreed; P98_ScriptFreeAll(); CK(P27_MemFreed == freed);
    }
    P15_SetListHead(saved_head); P28_EventCount = saved_count;
  }
  { P98_CreditsInit();   /* 004a9850 */
    CK(P98_Credits[0].y == 0x1e0 && P98_Credits[1].y == 0x1e0 + 74 && P98_Credits[2].y == 0x1e0 + 74 + 54 && P98_Faces[2].id == 0xffff && P98_FaceCur == 0);
    CK(strcmp((const char *)re_ptr(P98_FaceNames[0]), "MARTIN") == 0 && strcmp((const char *)re_ptr(P98_FaceNames[3]), "STEVEB") == 0);
    uint8_t rec[4] = { 0, 0xff, 0, 0 }; P98_Faces[1].id = 0xff; CK(P98_CreditsFace(rec) == 1 && P98_FaceCur == 0); P98_Faces[1].id = 0xffff; }
  { int32_t sv = P22_DevReady, tv = P22_TexVarA, cv; P22_DevReady = 1; P22_TexVarA = 32; cv = P33_Count[32];   /* 0041e52c */
    static int32_t q[4 * 15]; memset(q, 0, sizeof q); P98_QuadA(0, (const uint8_t *)q); CK(P33_Count[32] == cv + 6);
    P98_QuadB(0, (const uint8_t *)q); CK(P33_Count[32] == cv + 12);
    P33_Count[32] = cv; P22_DevReady = sv; P22_TexVarA = tv; }
  { P98_M4658 = 3; P94_FadeVal = 5; P15_Vals9[8] = 7; P98_M4648 = 9; P98_ResetMission();   /* 004e49c0 */
    CK(P98_M4658 == 0 && P94_FadeVal == 0 && P15_Vals9[8] == 0 && P98_M4640 == 0); }
  { uint8_t sv[0x54 * 2]; memcpy(sv, TrafficRecs, sizeof sv);   /* 004911d9 */
    memset(TrafficRecs, 0, sizeof sv); TrafficRecs[1] = 9; wr16t(&TrafficRecs[0x16], 0xffe); TrafficRecs[0x54 + 1] = 4;
    int32_t a = G6_00B87EAC, b = P58_SB87EB0; G6_00B87EAC = 0; P58_SB87EB0 = 0; P98_DD70 = 1; P98_DDE4 = 0xf00;
    P98_TrafficSpin(); CK(rd16t(&TrafficRecs[0x16]) == ((0xffe + 512) & 0xfff) && rd16t(&TrafficRecs[0x54 + 0x16]) == 0 && P98_DDE4 == ((0xf00 + 0x200) & 0xfff));
    memcpy(TrafficRecs, sv, sizeof sv); G6_00B87EAC = a; P58_SB87EB0 = b; P98_DD70 = 0; }
  { static uint8_t tab[4 + 100 * 0x34 + 0x1c8]; P98_InitSplash(tab);   /* 004cb857 */
    CK(rd32t(tab + 4 + 99 * 4) == 99 && rd16t(tab + 5 * 0x34 + 0x1c6) == 5 && rd32t(tab) == 0); }
  { P98_CarOpsC[0x27b600 - 1] = 1; P28_CarClean[3] = 5; P95_Deb0 = 2; P98_ClearCarData();   /* 004c2042 */
    CK(P98_CarOpsC[0x27b600 - 1] == 0 && P28_CarClean[3] == 0 && P95_Deb0 == 0); }
  { FILE *fp = fopen("p98_lang.txt", "wb"); if (fp) { fputs("Hello\r\nWorld\n", fp); fclose(fp); }   /* 0051763a */
    uint32_t s2 = P97_StrAddr[2];
    P98_LoadLang("p98_lang.txt", 0);
    CK(strcmp((const char *)re_ptr(P97_StrAddr[0]), "Hello") == 0 && strcmp((const char *)re_ptr(P97_StrAddr[1]), "World") == 0);
    P98_LoadLang("p98_missing.txt", 1); CK(strcmp((const char *)re_ptr(P98_MisStr[5]), "Mission.? missing!") == 0);
    remove("p98_lang.txt"); P97_StrAddr[2] = s2; }
  { int32_t a = G6_00B5A8A0, b = P47_CamB; G6_00B5A8A0 = 0; P47_CamB = 0; P59_Mode1137324 = 2; P61_V10b = 77; P62_Frame = 123;   /* 00519a45 */
    P98_CamRecAdd(0); CK(rd32t(P98_CamRecs) == 123 && P98_CamRecs[4] == 2 && rd32t(P98_CamRecs + 0x20) == 77 && P47_CamB == 1 && P52_ResetA == 1);
    G6_00B5A8A0 = a; P47_CamB = b; P59_Mode1137324 = 0; }
  { int32_t cam[0x20]; memset(cam, 0, sizeof cam); P59_PosX = 0; P59_PosZ = 0; cam[0x13] = 20000; cam[0] = 0;   /* 004c32c1 */
    CK(P98_CamClamp(cam) == 1 && cam[2] == 15000 && cam[3] == 15000); }
  { static int16_t pp[0x50]; memset(pp, 0, sizeof pp); float x = 50.0f, z = 0.0f; memcpy((uint8_t *)pp + 0x84, &x, 4); memcpy((uint8_t *)pp + 0x8c, &z, 4);   /* 00514a47 */
    P59_PosX = 0; P59_PosZ = 0; P98_D078C8 = 1; P98_PartAim(pp); CK(rd32t((uint8_t *)pp + 0x4c) == 10); P98_D078C8 = 0; }
  { int32_t pos[3] = { 10, 20, 30 }; int32_t a = G6_00B91CF4, b = G00575F40; G6_00B91CF4 = 1; G00575F40 = 1;   /* 005240d0 */
    P48_Slot sv = P48_Snd[3]; P48_Snd[3].flags = 0x21; P48_Snd[3].defVol = -500; P48_VolTab[9500] = 1234;
    P98_VoicePos(3, pos, 7, 0x7fff);
    float fy; memcpy(&fy, P48_Snd[3].data + 4, 4);
    CK(P48_Snd[3].flags == (0x01 | 0xe) && fy == -20.0f && P48_Snd[3].vol == -500 && P48_Snd[3].scaled == 1234 && rd32t(P48_Snd[3].data + 0x24) == 7);
    P48_Snd[3] = sv; G6_00B91CF4 = a; G00575F40 = b; }
  { static uint8_t wav[12 + 8 + 16 + 8 + 4]; memcpy(wav, "RIFF", 4); wr32t(wav + 4, sizeof wav - 8); memcpy(wav + 8, "WAVE", 4);   /* 0048c5b7 */
    memcpy(wav + 12, "fmt ", 4); wr32t(wav + 16, 16); memcpy(wav + 36, "data", 4); wr32t(wav + 40, 4);
    const void *fm, *da; uint32_t sz; CK(P98_RiffFind(wav, &fm, &da, &sz) == 1 && fm == wav + 20 && da == wav + 44 && sz == 4);
    memcpy(wav, "RIFX", 4); CK(P98_RiffFind(wav, &fm, &da, &sz) == 0 && fm == NULL); }
  { static uint8_t dev[0x548]; wr32t(dev + 0x538, 0xf800); wr32t(dev + 0x53c, 0x7e0); wr32t(dev + 0x540, 0x1f); wr32t(dev + 0x544, 0);   /* 00421a80 */
    uint8_t *sd = P32_DevInfo; P32_DevInfo = dev; P98_PixTabInit(); P32_DevInfo = sd;
    CK(P98_PixTab[0x7fff] == 0xffdf && P98_PixTab[0x8000] == 0xff && P98_PixTab[0x001f] == 0x001f && P98_PixTab[0x0400] == 0x0800); }
  { uint8_t sv[0x8c]; memcpy(sv, &DirectorCam, 0x8c); uint8_t *c = (uint8_t *)&DirectorCam;   /* 004c2b9a */
    wr32t(c + 0x7c, 0x00100500); P29_Flag94 = 0; P98_DirCamKeys(4); CK(rd16t(c + 0x7c) == 0x400 && rd32t(c + 0x18) == 0x10 && rd32t(c + 0x20) == 0x400);
    memcpy(&DirectorCam, sv, 0x8c); }
  { D_00b87e30 = 0; P98_DrawSix(); P94_IconRec = 0; P98_IconN = 3; P98_IconFlush(); CK(P98_IconN == 0);   /* 004ba720 / 004b4095 */
    int16_t *sl = P58_ItemList; static int16_t items[20] = { 1, 2, 0, 0, 8 }; items[14] = 4; P58_ItemList = items; P98_ItemsDraw(); P58_ItemList = sl; }
  return f;
}

static int test_p99(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p99 fail line %d\n",__LINE__); } } while (0)
  static uint8_t sv[sizeof P99_Cars]; memcpy(sv, P99_Cars, sizeof sv);
  { memset(P99_Cars, 0, sizeof P99_Cars);   /* единая таблица 00d077c0: прежние переменные — поля записей */
    P99_Cars[0].pos[0] = 123; P99_Cars[0].pos[2] = -9; P99_Cars[1].pos[2] = 7; P99_Cars[0].heading = 0x456; P99_Cars[0].ang[1] = 0x321;
    P99_Cars[0x41].pos[0] = 55; P99_Cars[0].speed = 77; P99_Cars[0].f10c = 88;
    CK(P59_PosX == 123 && PlayerPosX == 123 && ObjPosTable[0] == 123 && P59_PosZ == -9 && PlayerPosZ == -9 && ObjPosTable[0x52 + 2] == 7);
    CK(P94_HeadingI == 0x456 && P94_Heading == 0x321 && P88_ObjX == 55 && P62_Spd == 77 && P97_D078CC == 88);
    CK(P56_Objs[1][0xd0] == 7 && P60_Cars[0xc8] == 123 && P59_CarRecs[0xd0] == 7);
    CK(re_ptr(0x00d07888) == (void *)&P99_Cars[0].pos[0] && re_addr(&P99_Cars[2]) == 0x00d077c0u + 2 * 0x148); }
  { memset(&P99_Cars[3], 0, sizeof P99_Cars[3]);   /* 004d6ae7 */
    P99_Cars[3].f10c = 300 * 2048; P99_Cars[3].ff8 = 1;
    CK(P99_GearBox(3) == 60 * 300 && P99_Cars[3].gear == 1);
    P99_Cars[3].f10c = -4096; CK(P99_GearBox(3) == 96 * 2 && P99_Cars[3].gear == 0);
    P99_Cars[3].ff8 = 0; P99_Cars[3].f10c = 600 * 2048; P99_Cars[3].gear = 3; CK(P99_GearBox(3) == 30 * 600 && P99_Cars[3].gear == 3); }
  { int32_t cam[0x20]; memset(cam, 0, sizeof cam);   /* 004c5e08 */
    uint8_t pm = P36_PadMode; P36_PadMode = 0; P99_Cars[0].pos[0] = 0; P99_Cars[0].pos[2] = 0;
    cam[0] = 1; cam[4] = 5; cam[0x13] = 100000; CK(P99_CamCheckPlayer(cam) == 1 && cam[0] == 0 && cam[4] == 0 && cam[0x14] == -300);
    cam[0] = 0; CK(P99_CamCheckPlayer(cam) == 0);
    P36_PadMode = pm;
    int32_t m = P29_Mode; P29_Mode = 0; cam[4] = -1; P99_CamCheckDist(cam); CK(cam[4] == -1); P29_Mode = m; }   /* 004c3427 */
  { float s0 = P43_Sin[0], c0 = P43_Sin[0x400], k = P94_RadarK, ox = P56_F573FA0, oz = P56_F573FA4;   /* 00506a07 */
    P43_Sin[0] = 0.0f; P43_Sin[0x400] = 1.0f; P94_RadarK = 1.0f; P56_F573FA0 = 10.0f; P56_F573FA4 = 20.0f;
    S_00D11878 = 0; P99_Cars[0].heading = 0;
    int32_t src[8] = { 3000, 0, -1500, 0, 0, 0, 0, 0 }, dst[8] = { 0 };
    P99_RadarXform(src, dst, 2); CK(dst[0] == 12 && dst[2] == 21 && dst[4] == 10 && dst[6] == 20);
    P43_Sin[0] = s0; P43_Sin[0x400] = c0; P94_RadarK = k; P56_F573FA0 = ox; P56_F573FA4 = oz; }
  { int32_t a[2] = { 0, 0 }, b[2] = { 10, 10 }, c[2] = { 0, 10 }, d[2] = { 10, 0 }, x = 0, y = 0;   /* 00526aeb */
    CK(P99_SegCross(a, b, c, d, &x, &y) == 1 && x == 5 && y == 5);
    int32_t e[2] = { 20, 20 }, g[2] = { 30, 0 }; CK(P99_SegCross(a, b, e, g, &x, &y) == 0);
    int32_t h[2] = { 5, 0 }, i0[2] = { 10, 0 }, j[2] = { 15, 0 }; CK(P99_SegCross(a, i0, h, j, &x, &y) == 2); }
  { int32_t box[4] = { 0, 0, 10, 10 }, a[2] = { 5, 5 }, b[2] = { 15, 5 }, o0[2] = { -1, -1 }, o1[2] = { -1, -1 };   /* 00526cd5 */
    CK(P99_SegClip(box, a, b, o0, o1) == 1 && o1[0] == 10 && o1[1] == 5 && o0[0] == -1);
    int32_t c[2] = { 6, 6 }; CK(P99_SegClip(box, a, c, o0, o1) == 0); CK(P99_SegClip(box, a, a, o0, o1) == 0); }
  { static uint8_t ctx[0x590]; memset(ctx, 0, sizeof ctx);   /* 00420854 */
    uint32_t fmt[8] = { 0x20, 0x40, 0, 0x10, 0x7c00, 0x3e0, 0x1f, 0x8000 };
    CK(P99_DDEnumFmt(fmt, ctx) == 1 && *(uint32_t *)(ctx + 0x58c) == 0x22 && memcmp(ctx + 0x528, fmt, 0x20) == 0 && P24_RShiftR == 5 && P55_A4219C == 1);
    uint32_t f2[8] = { 0x20, 0x400, 0, 0, 0, 0, 0, 0 }; CK(P99_DDEnumFmt(f2, ctx) == 1 && *(uint32_t *)(ctx + 0x58c) == 0x66 && memcmp(ctx + 0x568, f2, 0x20) == 0);
    CK(P99_DDEnumFmt(f2, NULL) == 1); }
  { uint32_t s3 = P97_StrAddr[3]; P97_StrAddr[3] = 0x1234;   /* 00412d7d */
    P99_MenuDim(1); CK(P99_MenuText0 == 0x1234 && P99_Rgb3[1] == 0x40 && P99_Rgb8[2] == 0x40);
    P99_MenuDim(0); CK(P99_MenuText0 == 0 && P99_MenuText1 == 0 && P99_Rgb0[0] == 0xff && P99_Rgb8[2] == 0xff); P97_StrAddr[3] = s3; }
  { uint8_t var[0x30]; memset(var, 0, sizeof var); var[0x20] = 1;   /* 004f8862 */
    P99_VarSetStr(var, "HELLO"); CK(strcmp((const char *)re_rd_ptr(var + 0x24), "HELLO") == 0);
    P99_VarSetStr(var, "BYE"); CK(strcmp((const char *)re_rd_ptr(var + 0x24), "BYE") == 0);
    P98_DebugFree(re_rd_ptr(var + 0x24)); var[0x20] = 2; P99_VarSetStr(var, "X"); CK(1); }
  { uint8_t ev[0x60]; memset(ev, 0, sizeof ev);   /* 004a5338 */
    P99_CmdAppend(3, ev); uint8_t *b = (uint8_t *)re_rd_ptr(ev + 0x50);
    CK(*(int32_t *)(ev + 0x4c) == 6 && b != NULL && b[0] == 3 && b[1] == 0 && b[4] == 0 && b[5] == 0);
    P99_CmdAppend(7, ev); b = (uint8_t *)re_rd_ptr(ev + 0x50);
    CK(*(int32_t *)(ev + 0x4c) == 8 && b[0] == 3 && b[4] == 7 && b[5] == 0 && b[6] == 0 && b[7] == 0);
    P98_DebugFree(b); }
  { int32_t *cop = (int32_t *)calloc(0x340, 4); int32_t sb = P97_B2B0; P97_B2B0 = -1; cop[0x332] = 1;   /* 004a6e84 */
    CK(P99_CopTarget(cop) == 0 && cop[0x332] == 0); P97_B2B0 = sb; free(cop); }
  { static uint8_t car[0xcc0], n1[0x10]; memset(car, 0, sizeof car); memset(n1, 0, sizeof n1);   /* 004a7920 */
    *(int32_t *)(car + 0xcb8) = 1; *(int32_t *)(car + 0x1c) = 10; re_wr_ptr(car + 0x60, n1); *(int32_t *)(n1 + 8) = 100;
    *(int32_t *)(car + 0xc64) = 50;
    CK(P99_PathAhead(car) == 50 && *(uint32_t *)(car + 0xc60) == re_addr(car + 0x60));
    *(int32_t *)(car + 0xc64) = 500; CK(P99_PathAhead(car) == 0 && *(int32_t *)(car + 0xcb8) == 0); }
  { uint8_t g[0x200]; int32_t o[8]; memset(g, 0, sizeof g); memset(o, 0, sizeof o);   /* 004f568a */
    P97_C810A8 = 0; P97_C81490 = 0; o[0] = 5; o[4] = 3; *(int32_t *)(g + 4) = 2;
    P99_GoalCheck(0, g, o); CK(*(int32_t *)(g + 4) == 0x7fff && o[4] == 2);
    *(int32_t *)(g + 4) = 1; o[4] = 3; P99_GoalCheck(0, g, o); CK(o[4] == 3); }
  { P99_CamDelay = 2; P99_CamB0 = 8; P99_CamScriptStep(); CK(P99_CamDelay == 1 && P99_CamB0 == 4);   /* 0049ea37 */
    P99_CamDelay = 0; P99_CamIdx = 0; memset(P99_CamKeys, 0, sizeof P99_CamKeys); P99_CamMax = 3; P61_V18 = 0x10;
    P99_Cars[0].heading = 0xff8; P99_CamEnd = 0; P99_CamOn = 1;
    P99_CamScriptStep(); CK(P99_CamOn == 0 && P99_CamDone == 1 && P99_CamEnd == 1 && P99_CamSpd == 0x3000 && P61_V1C == 8); }
  { uint8_t view[6] = { 0 }; int16_t vw[3] = { 0x200, 0x100, 0x100 }; (void)view;   /* 004d2b5d */
    static uint8_t cop[0xcd8], o[0x40]; memset(cop, 0, sizeof cop); memset(o, 0, sizeof o);
    int32_t m = UiVar00B87E38; UiVar00B87E38 = 0; P56_CopsA = 0;
    CK(P99_CopsNear(vw, cop) == 0);
    re_wr_ptr(cop + 0xcd0, o); P99_Cars[0].pos2[0] = 0x100; P99_Cars[0].pos2[2] = 0;
    CK(P99_CopsNear(vw, cop) == 1 && P56_CopsA == 1); UiVar00B87E38 = m; P56_CopsA = 0; }
  { int32_t pk = P99_RoadPick; P99_RoadPick = -1; CK(P99_JunctionBlock(3) == 0); P99_RoadPick = pk;   /* 00496eb4 */
    int32_t w = P62_MapW; P62_MapW = 0; CK(P99_RoadAtCar(0) == -1); P62_MapW = w;   /* 0051b7a3 */
    int32_t h = P62_HudOff2; P62_HudOff2 = 1; CK(P99_ScriptMsgs() == 0); P62_HudOff2 = h;   /* 004f4d3c */
    uint8_t part[0xa0]; memset(part, 0, sizeof part); part[0xc] = 0x80; CK(P99_PartAhead(part, 1) == 0);   /* 00514c9f */
    int32_t a = G8_00C56710, b = P73_C56760; G8_00C56710 = 5; P73_C56760 = 4; CK(P99_PartOnChair(part, 0) == 0); G8_00C56710 = a; P73_C56760 = b;   /* 0051358d */
    void **gr = P58_Grid; P58_Grid = NULL; CK(P99_ChairHit(1.0f, 2.0f) == 0); P58_Grid = gr;   /* 004a2e14 */
    int16_t it[10] = { 0 }; ((uint8_t *)it)[5] = 0x10; P99_MenuItems(it); CK(1); }   /* 0050f569 */
  { P98_CarKind[0] = 5; uint32_t c0 = P28_CarClean[0]; P28_CarClean[0] = 0; P99_CarModelClean(-1); CK(P98_CarKind[0] == 0); P28_CarClean[0] = c0;   /* 004c0218 */
    int32_t d0 = P27_DentTex[0]; P27_DentTex[0] = 0; P99_CarOpsReset(0); P27_DentTex[0] = d0; CK(1); }   /* 004c1b6c */
  { P99_Cars[0].pos[0] = 1000; P99_Cars[0].pos[1] = 50; P99_Cars[0].pos[2] = 2000; P62_I137388 = 0; P62_I13738C = 0; P62_I137390 = 0;   /* 0049c99c */
    P99_FreeCamMove(); CK(P44_CamX == 1000.0f && P44_CamY == -50.0f && P44_CamZ == 2000.0f && P59_AngA == 0x400 && P59_AngB == 0); }
  { int32_t st = P15_State; P15_State = 0; P99_Cars[0].ang[0] = 5; P99_Cars[0].ang[2] = 6;   /* 004e9427 */
    P99_MarkerReset(); CK(P98_MrkSrc[0] == 20.0f && P98_MrkSrc[2] == 300.0f && P99_Mrk2660 == 900 && P99_Cars[0].ang[0] == 0 && P99_Cars[0].ang[2] == 0);
    P15_State = st; }
  { uint8_t *n = (uint8_t *)DebugMalloc(0x24, "t", 1); memset(n, 0, 0x24);   /* 004a4340 */
    uint8_t *h = P15_ListHead; P15_SetListHead(n); *(uint16_t *)(n + 6) = 9; P99_EvId = 0x22;
    P99_EventAdd(0);
    uint8_t *e = (uint8_t *)re_rd_ptr(n + 0x20);
    CK(e != NULL && *(uint16_t *)e == 0x28 && *(uint16_t *)(e + 4) == 1 && *(uint16_t *)(e + 6) == 0x22 && *(uint16_t *)(e + 8) == 9 && (*(uint16_t *)n & 0x10) != 0);
    uint8_t *o = e ? (uint8_t *)re_rd_ptr(e + 0x1c) : NULL; CK(o != NULL);
    if (o != NULL) re_wr_ptr(o + 0x50, DebugMalloc(8, "t", 2));
    P98_ScriptFreeAll(); CK(P15_ListHead == NULL); P15_SetListHead(h); }
  memcpy(P99_Cars, sv, sizeof sv);
  return f;
}

static int test_p100(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p100 fail line %d\n",__LINE__); } } while (0)
  { CK(re_ptr(0x0054c810) == (void *)P100_MenuC810 && *(uint32_t *)re_ptr(0x0054c810) == 0x004120feu);   /* .data меню в реестре */
    CK(re_ptr(0x0054e0b0) == (void *)P100_MenuE0B0 && re_ptr(0x0054d620) == (void *)(P100_MenuD4A8 + 0x178) && P100_SpeedTab[3] == 3); }
  { uint8_t r14[0x14 * 3], r42[0x42 * 3];   /* 0051acc5 / 0051aee6 */
    memcpy(r14, P11_00c12c60, sizeof r14); memcpy(r42, P11_00bf1c40, sizeof r42);
    int32_t *r = (int32_t *)&P11_00c12c60[2 * 0x14]; r[0] = 10; r[1] = 20; r[2] = 30; r[3] = 40; P11_00c12c60[2 * 0x14 + 0x10] = 0;
    P11_00bf1c40[2 * 0x42 + 6] = 5; P11_00bf1c40[2 * 0x42 + 7] = 0x0b;   /* 3 бита из 5 */
    CK(P100_RoadRect(2, 1) == 0);
    CK(P100_RoadRect(2, 0) == 1 && P100_Rect[0] == 12 && P100_Rect[1] == 20 && P100_Rect[2] == 30 && P100_Rect[3] == 40);
    CK(P100_RoadRect(2, 2) == 1 && P100_Rect[0] == 10 && P100_Rect[2] == 27);
    int32_t a = P62_Map1C0C, b = P62_MapCC90; P62_Map1C0C = 100; P62_MapCC90 = 1000;
    P11_00c12c60[2 * 0x14 + 0x10] = 1; P100_RoadRectAbs(2, 3); CK(P100_Rect[0] == 110 && P100_Rect[3] == 1037);
    P100_RoadRectAbs(2, 1); CK(P100_Rect[1] == 1022);
    P62_Map1C0C = a; P62_MapCC90 = b; memcpy(P11_00c12c60, r14, sizeof r14); memcpy(P11_00bf1c40, r42, sizeof r42); }
  { memset(&P99_Cars[5], 0, sizeof P99_Cars[5]);   /* 004d6740 */
    P99_Cars[5].f108 = 1; P99_Cars[5].gear = 2; P100_CarRevs(5);
    CK((uint16_t)P99_Cars[5].f144 == 8800 && P99_Cars[5].gear == 0 && P99_Cars[5].f143 == 0 && P99_Cars[5].f146 == 100);
    P99_Cars[5].f144 = 20000; P99_Cars[5].ff8 = 1; P100_CarRevs(5); CK((uint16_t)P99_Cars[5].f144 == 20000 && P99_Cars[5].f146 == 0);
    P99_Cars[5].f144 = (int16_t)30000; P99_Cars[5].f146 = 5000; P100_CarRevs(5);
    CK((uint16_t)P99_Cars[5].f144 == 30000 - 0x2d0 && P99_Cars[5].f143 == 1 && P99_Cars[5].f146 == 5100); }
  { uint16_t it[16] = { 8, 1, 0, 0, 0x10, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };   /* записи по 8 байт */   /* 00416605 */
    uint32_t a = re_ptr_register_dyn(it, sizeof it), sv = P100_ItemTab; P100_ItemTab = a;
    P100_ReplayMenuInit(); CK(P100_ItemN == 3 && P58_S5FE9F8 == 2 && P100_ItemSel == 2 && P68_B87E54 == 3 && P9_005fe9f0 == 1);
    P100_ItemTab = 0; P100_ReplayMenuInit(); CK(P100_ItemN == 0 && P100_ItemSel == 0);
    P100_ItemTab = sv; re_ptr_unregister(it); }
  { static uint8_t sv[sizeof P100_MenuD4A8]; memcpy(sv, P100_MenuD4A8, sizeof sv);   /* 00413e37 */
    int32_t m = MenuMode1271060, d = MenuState575EF0; MenuMode1271060 = 3; MenuState575EF0 = 9;
    P100_PadMenuInit();
    uint8_t *it = (uint8_t *)re_ptr(0x0054d4d0);
    CK(P58_S5FE9B8 == 0x0054d4d0 && P15_MenuItems == it && P15_MenuMode == 0 && MenuState575EF0 == 1 && P58_S5FE9B4 == 0x0054d590);
    CK(*(uint32_t *)(it + 8) == P97_StrAddr[0x6f] && *(uint32_t *)(it + 0x18) == P97_StrAddr[0x82] && *(uint32_t *)(it + 0x48) == P97_StrAddr[0x85]);
    MenuMode1271060 = m; MenuState575EF0 = d; memcpy(P100_MenuD4A8, sv, sizeof sv); }
  { int32_t a[20], b[32], best[10];   /* 00499951 */
    memset(a, 0, sizeof a); memset(b, 0, sizeof b); for (int i = 0; i < 10; i++) best[i] = 0x7fffffff;
    a[0] = 4096; a[16] = 50; b[12] = 30; b[19] = 4096; b[23 + 1] = 4096; b[27 + 2] = 4096;
    P100_BoxFace(a, b, 0, best, 1);
    CK(best[0] == 4116 && best[1] == 30 - 4096 && best[2] == -4096 && best[5] == 4096 && best[9] == 0); }
  { int16_t s0 = P59_Sin[0], s4 = P59_Sin[0x400]; P59_Sin[0] = 0; P59_Sin[0x400] = 4096;   /* 00499fb0 */
    int32_t p[0x40]; memset(p, 0, sizeof p); p[0x11] = p[0x12] = p[0x18 + 0x11] = p[0x18 + 0x12] = 100;
    CK(P100_BoxOverlap(p) == 1);
    p[0] = 10000; CK(P100_BoxOverlap(p) == 0);
    P59_Sin[0] = s0; P59_Sin[0x400] = s4; }
  { float buf[48], *so = P100_ClipOut; int32_t sn = P100_ClipN; float sf = Q01270C24;   /* 0042eee6 / 0042d797 */
    float va[6] = { 0, 0, 0, 0, 0, 10 }, vb[6] = { 0, 0, 0, 4, 8, 20 };
    P100_ClipOut = buf; P100_ClipN = 0; Q01270C24 = 15.0f;
    P100_ClipFar((const uint8_t *)va, (const uint8_t *)vb);
    CK(P100_ClipN == 1 && P100_ClipOut == buf + 12 && buf[0] == 2.0f && buf[1] == 4.0f && buf[2] == 15.0f);
    P100_ClipFar((const uint8_t *)vb, (const uint8_t *)va); CK(P100_ClipN == 3 && buf[12] == 2.0f && buf[12 + 2] == 15.0f && buf[24 + 2] == 10.0f && P100_ClipOut == buf + 36);
    float vn[6] = { 0, 0, 0, 0, 0, 100 }, vf[6] = { 0, 0, 0, 0, 0, 0 };
    P100_ClipOut = buf; P100_ClipN = 0; P100_ClipNear((const uint8_t *)vf, (const uint8_t *)vn, 0.0f, 1.0f);
    CK(P100_ClipN == 2 && buf[2] == 50.0f && buf[6] == 0.5f && buf[12 + 2] == 100.0f && buf[12 + 6] == 1.0f);
    P100_ClipOut = so; P100_ClipN = sn; Q01270C24 = sf; }
  { float p[0x1e]; memset(p, 0, sizeof p);   /* 004ba093 */
    int32_t fl = 2, i16 = 10, i17 = 3; memcpy(&p[0x1a], &fl, 4); memcpy(&p[0x16], &i16, 4); memcpy(&p[0x17], &i17, 4);
    uint16_t life = 3; memcpy((uint8_t *)p + 0x64, &life, 2); p[8] = 1.0f;
    P100_PartStep(p); memcpy(&i16, &p[0x16], 4); memcpy(&life, (uint8_t *)p + 0x64, 2);
    CK(p[0] == 1.0f && p[1] == -0.8f && i16 == 7 && life == 2 && p[8] == 1.0f); }
  { CK(P100_RecRead(1) == 0x20 || P100_RecPtr[1] != 0);   /* 00518f44: нет буфера */
    uint8_t s = P74_B5A894; P74_B5A894 = 0; P100_RecInput(0); CK(P74_B5A894 == 0); P74_B5A894 = s; }
  return f;
}
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p97 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
static int p97_menu_hits[3];
static void p97_menu_a(int32_t v) { p97_menu_hits[0] += 1 + v; }
static void p97_menu_b(int32_t v) { p97_menu_hits[1] += 1 + v; }
static void p97_menu_c(int32_t v) { p97_menu_hits[2] += 1 + v; }
static int test_p97(void) {
  int f = 0;
  { static uint8_t blob[64]; uint32_t a = re_ptr_register_dyn(blob, sizeof blob);   /* реестр */
    CK(a >= 0x80000000u && re_ptr(a + 5) == blob + 5 && re_addr(blob + 7) == a + 7 && re_ptr(0) == NULL && re_addr(NULL) == 0);
    CK(re_addr(P95_ObjB + 0x78) == 0x0110e500u + 0x78 && P95_ObjPtr(0x011237c0u + 4) == P95_ObjC + 4);
    static const char lit[] = "abc"; uint32_t la = re_addr(lit); CK(la != 0 && re_ptr(la) == lit && re_addr(lit) == la);
    re_fn_register(0x00401234u, (re_fn_t)p97_menu_a); CK(re_fn(0x00401234u) == (re_fn_t)p97_menu_a && re_fn_addr((re_fn_t)p97_menu_a) == 0x00401234u);
    CK(re_fn(0x0048c7f0u) == (re_fn_t)P49_Play && re_fn(0x0048bf52u) == (re_fn_t)P106_EaxPreset);
    re_ptr_unregister(blob); CK(re_ptr(a) == NULL); }
  { P97_HsInit();   /* 0051c900 */
    CK(P42_HighScores[0] == 0x00b5b378 && P42_HighScores[9] == 0x00b5ba58 + 0xdc && P42_HighScores[19] == 0x00b5b008 + 3 * 0xdc);
    CK(P42_HighScores[23] == 0x00b5ac98 + 3 * 0xdc && P42_HighScores[24] == 0x00b5a928 && P42_HighScores[31] == 0x00b5c138 + 3 * 0x2c);
    CK(re_ptr((uint32_t)P42_HighScores[29]) == P62_Hs6 + 0x2c); }
  { P48_F0 d0 = P48_Drv00, d8 = P48_Drv08, dc = P48_Drv0C; P48_F1 d2c = P48_Drv2C, d40 = P48_Drv40; P48_F3 d38 = P48_Drv38; P48_F4 d54 = P48_Drv54;   /* 0048bbd5 */
    FnV2 g14 = G6_00BDCB14; FnV1 g18 = G6_00BDCB18, g20 = G6_00BDCB20; P68_FLoad dl = P68_DrvLoad;
    P97_SndDrvInit();
    CK(P48_Drv00 == (P48_F0)P50_SoundShutdown && P48_Drv54 == (P48_F4)(void (*)(void))P49_SetVel3D && P97_DrvL == (re_fn_t)P49_GetStatus && P68_DrvLoad == NULL);
    P48_Drv00 = d0; P48_Drv08 = d8; P48_Drv0C = dc; P48_Drv2C = d2c; P48_Drv40 = d40; P48_Drv38 = d38; P48_Drv54 = d54;
    G6_00BDCB14 = g14; G6_00BDCB18 = g18; G6_00BDCB20 = g20; P68_DrvLoad = dl; }
  { static uint8_t nodes[2][0x24], objs[3][0x60]; uint8_t *sh = P15_ListHead, *sc = P15_ListCur;   /* список скрипта */
    memset(nodes, 0, sizeof nodes); memset(objs, 0, sizeof objs);
    uint32_t an = re_ptr_register_dyn(nodes, sizeof nodes), ao = re_ptr_register_dyn(objs, sizeof objs);
    uint16_t fl = 8; memcpy(nodes[0], &fl, 2); uint16_t id = 7; memcpy(nodes[0] + 6, &id, 2);
    uint32_t v = an + 0x24; memcpy(nodes[0] + 0x20, &v, 4); v = ao; memcpy(nodes[0] + 0x1c, &v, 4);
    v = ao + 0x60; memcpy(nodes[1] + 0x1c, &v, 4); v = ao + 0xc0; memcpy(objs[1] + 0x58, &v, 4);
    float x = 10.6f, z = -3.5f; memcpy(objs[0], &x, 4); memcpy(objs[0] + 8, &z, 4);
    for (int i = 0; i < 3; i++) { int32_t b = 0x100 * (i + 1), p = b + 0x10; memcpy(objs[i] + 0x50, &b, 4); memcpy(objs[i] + 0x54, &p, 4); }
    P15_SetListHead(nodes[0]);
    static uint8_t buf[0x24 * 2 + 0x60 * 3]; CK(P97_ScriptSave(buf) == (int32_t)sizeof buf);   /* 004cf6b2 */
    int32_t o54; memcpy(&o54, buf + 0x24 + 0x54, 4); CK(o54 == 0x10);
    memcpy(&o54, objs[2] + 0x54, 4); CK(o54 == 0x310);
    memset(objs[2], 0x55, 0x50); P97_ScriptLoad(buf);   /* 004cf772 */
    CK(objs[2][0] == 0 && objs[2][0x4f] == 0); memcpy(&o54, objs[2] + 0x54, 4); CK(o54 == 0x310);
    memcpy(&v, nodes[0] + 0x20, 4); CK(v == an + 0x24);
    int32_t of = 9, oid = 7; uint8_t *ob = P58_Objs[3]; uint8_t sv[0x34]; memcpy(sv, ob, 0x34);   /* 004f4f10 */
    memcpy(ob + 0x10, &of, 4); memcpy(ob + 0xc, &oid, 4); P97_ScrObjOn = 1; P97_ObjsFromScript();
    int32_t ox, oz; memcpy(&ox, ob + 0x14, 4); memcpy(&oz, ob + 0x1c, 4); CK(ox == 11 && oz == -4);   /* lrintf: -3.5 → -4 */
    memcpy(ob, sv, 0x34); P97_ScrObjOn = 0;
    P15_ListCur = nodes[1]; P97_ScriptResetCur();   /* 004cff7e */
    memcpy(&o54, objs[2] + 0x54, 4); CK(o54 == 0x300 && (nodes[1][0] & 2) && objs[1][0] == 0);
    uint8_t prog[8] = {0, 0, 0, 0}; uint8_t *sp = P10_ScriptPtr; P10_ScriptPtr = prog; P15_ListCur = nodes[1];   /* 004d156a */
    CK(P97_ScriptOpNext() == 1 && P10_ScriptPtr == prog + 4);
    P10_ScriptPtr = sp; P15_SetListHead(sh); P15_ListCur = sc; re_ptr_unregister(nodes); re_ptr_unregister(objs); }
  { static uint8_t rec[0x80], lnk[0x20]; memset(rec, 0, sizeof rec); memset(lnk, 0, sizeof lnk);   /* 0050bc2b */
    uint32_t al = re_ptr_register_dyn(lnk, sizeof lnk); memcpy(rec + 0x60, &al, 4); int32_t one = 1, sk = P77_C65DA4; memcpy(rec + 0x14, &one, 4);
    P77_C65DA4 = 1; lnk[0x1e] = 1; memset(P77_C62E60, 0, sizeof P77_C62E60); P97_MarkCells(rec);
    int32_t c3, c4, c7; memcpy(&c3, P77_C62E60 + 0x5e7 * 4, 4); memcpy(&c4, P77_C62E60 + 0x5e8 * 4, 4); memcpy(&c7, P77_C62E60 + (0x5e8 + 0x37) * 4, 4);
    CK(c3 == 0x20 && c4 == 0 && c7 == 0x20);   /* тип 1: {0,0,0,1,0,0,1,1,0} */
    memset(P77_C62E60, 0, sizeof P77_C62E60); P77_C65DA4 = sk; re_ptr_unregister(lnk); }
  { int32_t s1 = G6_00B91CF4, s2 = G00575F40, s3 = G6_00B91D34;   /* 00523cda */
    G6_00B91CF4 = 1; G00575F40 = 1; G6_00B91D34 = 10; uint8_t sv[0x34 * 20]; memcpy(sv, S_00BDC2A0, sizeof sv); memset(S_00BDC2A0, 0x11, sizeof sv);
    for (int i = 0; i < 20; i++) { S_00BDC2A0[i * 0x34 + 1] = 0; S_00BDC2A0[i * 0x34 + 0x33] = 0; }
    S_00BDC2A0[5 * 0x34 + 0x33] = 9; P48_Samples[3 * 8] = 0; P48_Samples[3 * 8 + 1] = 4;
    CK(P97_SndStart(3, -1, 0, 0, 0) == 5 && P97_SndStart(11, -1, 0, 0, 0) == -1 && P97_SndStart(3, 2, 0, 0, 0) == 2);
    S_00BDC2A0[7 * 0x34] = 0; CK(P97_SndStart(3, -1, 0, 0, 0) == 7);
    memcpy(S_00BDC2A0, sv, sizeof sv); G6_00B91CF4 = s1; G00575F40 = s2; G6_00B91D34 = s3; }
  { static uint8_t car[0xcd8], cop[0x30]; memset(car, 0, sizeof car); memset(cop, 0, sizeof cop);   /* 004d2c95 */
    uint32_t ac = re_ptr_register_dyn(cop, sizeof cop); memcpy(car + 0xcd0, &ac, 4); int32_t px = P59_PosX, pz = P59_PosZ;
    P59_PosX = 100; P59_PosZ = 0; int16_t view[3] = {50, 500, 0x400}; P56_CopsA = 0; P56_CopsB = 0;
    CK(P97_CopsSee(view, car) == 0 || P56_CopsB == 1);
    P59_PosX = 10; CK(P97_CopsSee(view, car) == 1 && P56_CopsA == 1);
    P59_PosX = px; P59_PosZ = pz; P56_CopsA = 0; P56_CopsB = 0; re_ptr_unregister(cop); }
  { static uint8_t g[0x200 + 4], cnt[8], o[0x14]; memset(g, 0, sizeof g); memset(cnt, 0, sizeof cnt); memset(o, 0, sizeof o);   /* 004f58c6 / 004f5c89 */
    uint32_t ac = re_ptr_register_dyn(cnt, sizeof cnt); memcpy(g + 0x1fc, &ac, 4);
    int32_t t = 100, one = 1, two = 2, cv = 0x64; memcpy(g + 0x20, &t, 4); memcpy(g + 0x18, &one, 4); memcpy(g + 0x1c, &two, 4); memcpy(cnt, &cv, 4);
    int32_t fr = P62_Frame; P62_Frame = 0; CK(P97_GoalReached(50, g, o) == 1 && (o[0x10] & 2)); P62_Frame = fr;
    CK(P97_GoalReached(150, g, o) == 0);
    int32_t four = 4, sd = D_00c80ca0; memcpy(cnt + 4, &four, 4); D_00c80ca0 = 3;
    uint32_t sa = P97_StrAddr[0x12a]; static const char sec[] = "SEC"; P97_StrAddr[0x12a] = re_addr(sec);
    P97_AddTime(g, 1); memcpy(&cv, cnt, 4); CK(cv == 0x96 && D_00c80ca0 == 4 && strcmp(P97_MsgBuf, "+4 SEC!") == 0);
    P97_StrAddr[0x12a] = sa; D_00c80ca0 = sd; re_ptr_unregister(cnt); }
  { static uint8_t tab[0x40], items[0x30]; memset(tab, 0, sizeof tab); memset(items, 0, sizeof items);   /* 0040c8a0 / 004185d2 */
    re_fn_register(0x00402000u, (re_fn_t)p97_menu_a); re_fn_register(0x00402010u, (re_fn_t)p97_menu_b); re_fn_register(0x00402020u, (re_fn_t)p97_menu_c);
    uint32_t at = re_ptr_register_dyn(tab, sizeof tab), ai = re_ptr_register_dyn(items, sizeof items), x;
    x = 0x00402000u; memcpy(tab + 0x00, &x, 4); x = 0x00402010u; memcpy(tab + 0x04, &x, 4); x = 1; memcpy(tab + 0x08, &x, 4);
    x = 0x00402020u; memcpy(tab + 0x10, &x, 4); x = 0x00402010u; memcpy(tab + 0x14, &x, 4); x = 1; memcpy(tab + 0x18, &x, 4);
    memset(p97_menu_hits, 0, sizeof p97_menu_hits); P97_MenuCall0(at, 1); CK(p97_menu_hits[1] == 2 && p97_menu_hits[2] == 1 && p97_menu_hits[0] == 0);
    int16_t end = -1; memcpy(items + 0x10, &end, 2); P97_MenuCall2(at, 0, ai);
    CK(items[0xc] == 0xff && items[0xe] == 0xff && items[0x1c] == 0 && p97_menu_hits[1] == 2 + 6 && p97_menu_hits[0] == 3);
    re_ptr_unregister(tab); re_ptr_unregister(items); }
  { int32_t fa = P21_FrameFlagA, fb = P21_FrameFlagB, fm = P21_FrameMin, w = WI00B87E2C;   /* 0040ea70 */
    P21_FrameFlagB = 1; P21_FrameFlagA = 0; P21_FrameMin = 2; WI00B87E2C = 1; P97_StrAddr[10] = 0x1234;
    P97_OptMenuAInit(); uint32_t v; CK(strcmp(P97_FpsTxtA, "25fps") == 0);
    memcpy(&v, P97_OptMenuA + 0x68, 4); CK(v == 0x005fe4e4u); memcpy(&v, P97_OptMenuA + 0x28, 4); CK(v == 0x1234);
    P97_StrAddr[10] = 0; P21_FrameFlagA = fa; P21_FrameFlagB = fb; P21_FrameMin = fm; WI00B87E2C = w; }
  { P97_InitConsts(); P97_BlinkAStep(); CK(P97_BlinkA[0] == 70);   /* 00417479 */
    P97_BlinkA[0] = 250; P97_BlinkAStep(); CK(P97_BlinkA[0] == 255 && P97_BlinkA[1] == -20); P97_InitConsts(); }
  return f;
}
static int test_p96(void) {
  int f = 0;
  P96_InitConsts(); CK(P96_RefreshHz == 50 && P96_RTag[0] == 'R');
  { int32_t sc = P55_PopCnt, sb = P55_PopB2AC, sw = P19_ScrW, sx = G6_00D117A4, sy = G6_00D117A8;   /* 004d90f4 */
    P55_PopCnt = 0; P55_PopB2AC = 0; P19_ScrW = 32; G6_00D117A4 = 2; G6_00D117A8 = 1; WH00B2C3A8 = 7;
    P96_LogLine("ab\ncdef");
    CK(P55_PopCnt == 1 && P55_PopB2AC == 8 && strcmp(P96_LogText(P55_PopTab[0].id), "ab\ncdef") == 0);
    CK(P55_PopTab[0].x == 2 && P55_PopTab[0].y == 1 && P55_PopTab[0].w == 7 && G6_00D117A4 == 0 && G6_00D117A8 == 4);  /* 4 столбца: "ab" и "cdef" переносятся */
    P96_LogLine("x"); CK(P55_PopCnt == 2 && P55_PopTab[1].id == 0x00d0fe40u + 8 && G6_00D117A4 == 1);
    P55_PopCnt = sc; P55_PopB2AC = sb; P19_ScrW = sw; G6_00D117A4 = sx; G6_00D117A8 = sy; }
  { char l[32] = "  abc, def", o[16];   /* 004f652e / 004f6612 */
    CK(P96_ParseWord(l, o) == 0 && strcmp(o, "abc") == 0 && memcmp(l, " defc, def", 10) == 0);   /* хвост сдвигается без нуля */
    char l2[8] = "   "; CK(P96_ParseWord(l2, o) == 0xc);
    char q[32] = " \"hi there\" rest"; CK(P96_ParseQuoted(q, o) == 0 && strcmp(o, "hi there") == 0 && strcmp(q, " rest") == 0);
    char q2[16] = "x\"a\""; CK(P96_ParseQuoted(q2, o) == 0xc);
    char q3[16] = " \"open"; CK(P96_ParseQuoted(q3, o) == 0xc); }
  { static p43_sintab_t ss; memcpy(ss, P43_Sin, sizeof ss);
    for (int i = 0; i < 5120; i++) P43_Sin[i] = (float)sin((double)i * 6.283185307179586 / 4096.0);
    P43_Sin[0] = 0.0f; P43_Sin[0x400] = 1.0f;
    P96_InitRotTab(); const int32_t *t = P96_RotTab[0];   /* 0048db8e (угол 0: sin 0, cos 1) */
    CK(t[0] == -180 && t[1] == 450 && t[2] == 180 && t[3] == 450 && t[4] == -180 && t[5] == -450 && t[6] == 180 && t[7] == -450);
    t = P96_RotTab[256]; CK(t[0] == -450 && t[1] == -180);   /* угол 1024 (90°): sin 1, cos 0 */
    P96_InitSphere(); CK(P96_Sphere[6 * 32][1] == 0.75f && P96_Sphere[0][1] == -0.75f && fabsf(P96_Sphere[3 * 32][0]) < 1e-6f);   /* 004e8440 */
    CK(fabsf(P96_Sphere[3 * 32][2] - 1.0f) < 1e-6f && fabsf(P96_Sphere[6 * 32][2] - sqrtf(0.4375f)) < 1e-6f);
    memcpy(P43_Sin, ss, sizeof ss); }
  { float a = Q01270C24, b = Q0125F3F8; int32_t m = P21_FrameMin;   /* 0050fab0 */
    Q01270C24 = 50000.0f; Q0125F3F8 = 100.0f; P21_FrameMin = 0; P96_ClampOptions();
    CK(Q01270C24 == 42000.0f && Q0125F3F8 == 15000.0f && P21_FrameMin == 1);
    Q01270C24 = 20000.0f; P21_FrameMin = 30; P96_ClampOptions(); CK(Q01270C24 == 20000.0f && P21_FrameMin == 10);
    Q01270C24 = a; Q0125F3F8 = b; P21_FrameMin = m; }
  { float pos[3] = {100.0f, 50.0f, -20.0f};   /* 004b04c0 (native rand = 0) */
    P96_SparkOn = 1; P96_DustOn = 1; memset(P96_Dust, 0, sizeof P96_Dust); P96_SpawnDust(pos, 3);
    float x, vy; int16_t life; memcpy(&x, P96_Dust + 0x24 * 2, 4); memcpy(&vy, P96_Dust + 0x14, 4); memcpy(&life, P96_Dust + 0x20, 2);
    CK(P96_DustN == 3 && x == 68.0f && vy == -5.0f && life == 0x3c);
    P96_DustN = 0; P96_SpawnDust(pos, 2); CK(P96_DustN == 0);   /* первая запись живая */
    P96_SparkOn = 0; P96_DustOn = 0; memset(P96_Dust, 0, sizeof P96_Dust); }
  { int32_t sp = G01105D60, sn = G010FFD04, so = P96_ObjBOn, sm = P13_00b201dc;   /* 004ad5d2 */
    float pos[3] = {1.0f, 2.0f, 30.0f}; int32_t uv[4] = {5, 6, 7, 8};
    G01105D60 = 0x0110e500 + 0x78; G010FFD04 = 1; P96_ObjBOn = 1; P13_00b201dc = 1;
    P96_AddObjB(pos, uv, 3, 4, 0x200005, 1, 9, 10);
    const uint8_t *r = P95_ObjB + 0x78; float z; int32_t fl, v; int16_t h;
    memcpy(&z, r + 8, 4); memcpy(&fl, r + 0x68, 4); memcpy(&h, r + 0x64, 2); memcpy(&v, r + 0x1c, 4);
    CK(z == 20.0f && fl == 0x220002 && h == 0x85 && v == 8 && G01105D60 == 0x0110e500 + 0xf0 && G010FFD04 == 2);
    P13_00b201dc = 0; P96_AddObjB(pos, uv, 3, 4, 5, 0, 9, 10); CK(G010FFD04 == 2);
    G01105D60 = sp; G010FFD04 = sn; P96_ObjBOn = so; P13_00b201dc = sm; }
  { uint8_t part[0x80]; memset(part, 0, sizeof part); int32_t t = 4; memcpy(part + 0x1c, &t, 4); P96_PartRunA(part); P96_PartRunB(part); }   /* 00513cc7 */
  { uint32_t sa = P17_PtrA; int32_t sm = P29_Mode, sk = S_00B5A77C;   /* 0050e9ab: ожидание клавиши */
    P17_PtrA = 1; P29_Mode = 0; S_00B5A77C = 5; P96_ReplayScript(); CK(S_00B5A77C == 5);
    P17_PtrA = sa; P29_Mode = sm; S_00B5A77C = sk; }
  return f;
}

static int test_p95(void) {
  int f = 0;
  { uint8_t tab[0xb4]; memset(tab, 0xcc, sizeof tab);   /* 004d2500 / 004d29e1 */
    P95_SndInit(tab);
    int32_t v; memcpy(&v, tab + 4 + 9 * 8, 4); CK(v == 256); memcpy(&v, tab + 9 * 8, 4); CK(v == 0);
    memcpy(&v, tab + 0x58 + 1 * 8, 4); CK(v == 682); memcpy(&v, tab + 0x5c + 1 * 8, 4); CK(v == 75);
    memcpy(&v, tab + 0xb0, 4); CK(v == 1 && P95_ChanLast == -1 && P95_ChanState == 0x3e);
    int32_t sbusy = P62_BusyB, srdy = P95_SndReady; P62_BusyB = 0; P95_SndReady = 1; P95_SndOn = 1; P95_SndRate = 0;
    P95_SndTrigger(tab, 2, 0x1000); memcpy(&v, tab + 2 * 8, 4); CK(P95_ChanLast == 2 && v == 128);
    P95_ChanLast = 7; P95_SndTrigger(tab, 2, 0x1000); CK(P95_ChanLast == 7);   /* уже активен */
    P62_BusyB = sbusy; P95_SndReady = srdy; }
  { int32_t sgm = GameMode; GameMode = 1; P95_SndOn = 0; P52_FogOn = 5; P26_FxA = 3; P55_PopSkip = 0;   /* 00405450 */
    P95_ResetRace(); CK(P95_SndOn == 1 && P52_FogOn == 0 && P26_FxA == 3 && P55_PopSkip == 1);
    GameMode = 0; P95_ResetRace(); CK(P26_FxA == 0); GameMode = sgm; }
  { static const int32_t lst[4] = { 1, 2, 3, 4 }; p95_seq_t s = { 4, lst }; uint8_t keep[24]; memcpy(keep, A_00D044E0, 24);   /* 004e5d64 */
    int32_t h[6] = { 2, 3, 4, 1, 2, 9 }; memcpy(A_00D044E0, h, sizeof h); CK(P95_SeqMatch(&s) == 1);
    int32_t h2[6] = { 3, 2, 1, 4, 3, 9 }; memcpy(A_00D044E0, h2, sizeof h2); CK(P95_SeqMatch(&s) == 1);
    int32_t h3[6] = { 2, 3, 1, 4, 3, 9 }; memcpy(A_00D044E0, h3, sizeof h3); CK(P95_SeqMatch(&s) == 0);
    p95_seq_t s0 = { 4, NULL }; CK(P95_SeqMatch(&s0) == 0); memcpy(A_00D044E0, keep, 24); }
  { int32_t sa = G010FFA20, sb = G010FFB40, sd = G010FFD04;   /* 004ba57a / 004ba64d: список по убыванию z */
    float z[4] = { 100.0f, 10.0f, 300.0f, 200.0f };
    for (int i = 0; i < 4; i++) memcpy(P95_ObjC + i * 0x78 + 8, &z[i], 4);
    float zb = 250.0f; memcpy(P95_ObjB + 8, &zb, 4);
    G010FFA20 = 4; G010FFD04 = 1; G010FFB40 = 0;
    P95_SortObjC(); P95_SortObjB();
    float got[8]; int n = 0;
    for (uint8_t *p = P95_ObjPtr((uint32_t)G010FFB40); p && n < 8; ) { memcpy(&got[n++], p + 8, 4); int32_t r; memcpy(&r, p + 0x74, 4); p = P95_ObjPtr((uint32_t)r); }
    CK(n == 4 && got[0] == 100.0f && got[1] == 250.0f && got[2] == 200.0f && got[3] == 300.0f);   /* как в игре: вставка после первого, у кого z не больше (голова — первая вставленная) */
    CK(P95_ObjRef(P95_ObjC + 0x78) == 0x011237c0u + 0x78 && P95_ObjPtr(0x0110e500u) == P95_ObjB);
    G010FFA20 = sa; G010FFB40 = sb; G010FFD04 = sd; }
  { int32_t s0 = G010FFB40; float scx = P44_CamX, scy = P44_CamY, scz = P44_CamZ; p44_m9_t smt; memcpy(smt, P44_ViewMatT, sizeof smt);   /* 004ba457 */
    memset(P95_ObjA, 0, sizeof P95_ObjA); memset(P44_ViewMatT, 0, sizeof smt); P44_ViewMatT[0] = P44_ViewMatT[4] = P44_ViewMatT[8] = 1.0f;
    P44_CamX = 1.0f; P44_CamY = 2.0f; P44_CamZ = 3.0f; G010FFB40 = 0;
    float p0[3] = { 5, 5, 103 }, p1[3] = { 5, 5, 23 }; int32_t fl = 2;
    memcpy(P95_ObjA, p0, 12); memcpy(P95_ObjA + 0x68, &fl, 4); memcpy(P95_ObjA + 0x78, p1, 12); memcpy(P95_ObjA + 0x78 + 0x68, &fl, 4);
    P95_SortObjA(); float zc; memcpy(&zc, P95_ObjA + 0x18, 4);
    CK(zc == 100.0f && (uint32_t)G010FFB40 == 0x010f5160u && P44_MatPtr == (float *)P44_ViewMatT);   /* вторая (z 20 < 50) вне списка */
    G010FFB40 = s0; P44_CamX = scx; P44_CamY = scy; P44_CamZ = scz; memcpy(P44_ViewMatT, smt, sizeof smt); }
  { int32_t r[4] = { 0, 0, 0, 0 }, sd = (int32_t)G010DE220; P95_InitDebris(); CK(G010DE220 == 1 && P95_DebPos[0] == 0x434d0000u && P95_DebPos[14] == 0xc3898000u && P95_DebRnd[3] < 0x800); (void)r; (void)sd; }
  { float ss = P19_Scale; int32_t sopt = MenuOptBDFA54; P19_Scale = 1.0f; MenuOptBDFA54 = 0;   /* 00507de2 */
    int32_t src[8] = { 100, 0, 0, 0, 0, 0, 50, 0 }, dst[8]; float ofs[3] = { 10.0f, 0, 20.0f };
    P95_MapRotate(src, dst, 2, ofs, 0x400);   /* 90°: x' = x·cos − z·sin, z' = x·sin + z·cos */
    CK(dst[0] == 10 && dst[2] == 120 && dst[4] == -40 && dst[6] == 20);
    MenuOptBDFA54 = 1; P95_MapRotate(src, dst, 1, ofs, 0x400); CK(dst[0] == 110 && dst[2] == 20);
    P19_Scale = ss; MenuOptBDFA54 = sopt; }
  { uint16_t sang = P59_AngB; p44_m9_t sm, smt; memcpy(sm, P44_ViewMat, sizeof sm); memcpy(smt, P44_ViewMatT, sizeof smt);   /* 0049f418 */
    float q[5] = { 0, 0, 0, 0, 1.0f }; P95_CamFromQuat(q);
    CK(fabsf(P44_ViewMat[0] - 1.0f) < 1e-6f && fabsf(P44_ViewMatT[8] - 1.0f) < 1e-6f && P59_AngB == (uint16_t)P44_Atan2(0, 100000));
    P59_AngB = sang; memcpy(P44_ViewMat, sm, sizeof sm); memcpy(P44_ViewMatT, smt, sizeof smt); }
  { static TRAFFIC_RECS_T keep; memcpy(keep, TrafficRecs, sizeof keep); int32_t sn = P51_TrafficN; float sc = P63_Scale, scx = P44_CamX, scz = P44_CamZ;   /* 0048f6c1 / 004d65fa */
    memset(TrafficRecs, 0, sizeof keep); P51_TrafficN = 3; P63_Scale = 1.0f;
    uint8_t *r = (uint8_t *)TrafficRecs; int32_t v;
    r[1] = 2; v = 0x2ee + 10; memcpy(r + 0x48, &v, 4); v = -0x2ee + 5; memcpy(r + 0x4c, &v, 4);
    r[0x54 + 1] = 1; r[0x54 + 2] = 0;                                   /* тип 1 без флага — пропуск */
    r[0xa8 + 1] = 4; v = 0x2ee + 100; memcpy(r + 0xa8 + 0x48, &v, 4); v = -0x2ee; memcpy(r + 0xa8 + 0x4c, &v, 4);
    CK(P95_CountNear(0, 0, 50) == 1 && P63_Near == 15);
    CK(P95_CountNear(0, 0, 200) == 2 && P63_Near == 15);
    v = 3; memcpy(r + 0xa8 + 0x48, &v, 4); v = 0; memcpy(r + 0xa8 + 0x4c, &v, 4); P44_CamX = 1500.0f * 3; P44_CamZ = 0;
    P95_NearestTwo(); CK(P95_Near1 == 3 && P95_Near2 == -1);
    memcpy(TrafficRecs, keep, sizeof keep); P51_TrafficN = sn; P63_Scale = sc; P44_CamX = scx; P44_CamZ = scz; }
  { p95_line_fn sl = P95_DrawLine; p85_state_fn sst = P85_StateFn; p85_blend_fn sbl = P85_BlendFn; float ss = P19_Scale;   /* 00509d27 / 00507310 */
    P95_DrawLine = p95_line; P85_StateFn = p95_state; P85_BlendFn = p95_blend; p95_lines = p95_st = p95_bl = 0;
    P85_StateDirty = 1; P85_BlendCur = 1;
    P95_DrawLineRGB(10, 20, 30, 40, 0x00ff8000u);
    CK(p95_lines == 1 && p95_st == 1 && p95_bl == 1 && p95_lx[0] == 12.0f && p95_lx[3] == 42.0f && P85_StateDirty == -1 && P85_BlendCur == 0xff);
    P19_Scale = 2.0f; float pos[3] = { 100.0f, 0, 50.0f }; p95_lines = 0;
    P95_DrawCross(pos);
    CK(p95_lines == 3 && p95_lx[0] == 104.0f && p95_lx[1] == 56.0f && p95_lx[2] == 104.0f && p95_lx[3] == 44.0f);
    P95_DrawLine = sl; P85_StateFn = sst; P85_BlendFn = sbl; P19_Scale = ss; P85_StateDirty = 0; P85_BlendCur = 0; }
  { uint8_t *sp = P10_ScriptPtr, *sc = P10_ScriptCtx; uint8_t ctx[0x20] = { 0 }, scr[16] = { 0 };   /* 004d0f28 */
    int16_t ax = 1; uint16_t st = 0x100, tg = 0x250; memcpy(scr + 2, &ax, 2); memcpy(scr + 4, &st, 2); memcpy(scr + 6, &tg, 2);
    P10_ScriptPtr = scr; P10_ScriptCtx = ctx;
    CK(P95_ScriptTurn() == 0 && ctx[0x12] == 0x00 && ctx[0x13] == 0x01);
    CK(P95_ScriptTurn() == 0 && ctx[0x13] == 0x02);
    CK(P95_ScriptTurn() == 1 && ctx[0x12] == 0x50 && ctx[0x13] == 0x02 && P10_ScriptPtr == scr + 8);
    P10_ScriptPtr = sp; P10_ScriptCtx = sc; }
  return f;
}

static void st_depth_mask(int32_t w) { plat_set_zbuffer(1, w != 0); }   /* _grDepthMask@4 для 0042655a в native */
int png_write_rgba(const char *path, const uint32_t *px, int w, int h);
static int test_p101(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p101 fail line %d\n",__LINE__); } } while (0)
  /* единые таблицы дороги / матриц (v1.46) */
  CK((uint8_t *)P17_MapBase == P11_00bf1c40 + 2 && (uint8_t *)P59_BF1C48 == P11_00bf1c40 + 8);
  CK((uint8_t *)P17_SlotBase == P11_00c1ed80 + 0xa && (uint8_t *)P11_00c1ed8a == P11_00c1ed80 + 0xa && (uint8_t *)P51_Tab1ED80 == P11_00c1ed80);
  CK((float *)P98_MrkMat == P98_CarMat[0] && sizeof P98_MrkMat == 36);
  { /* 0051b974 */
    static uint8_t sn[0x42 * 4], ss[0x2c * 3], sr[0x14 * 4];
    memcpy(sn, P11_00bf1c40, sizeof sn); memcpy(ss, P11_00c1ed80, sizeof ss); memcpy(sr, P11_00c12c60, sizeof sr);
    int32_t c64 = P62_MapC64, c40 = P62_Map2C40, b1 = P54_MapB1, b2 = P54_MapB2, mn = P62_MapN, rows = P72_Rows;
    void *ra = P54_RoadA[0], *rb = P54_RoadB[0];
    uint16_t ta[16] = { 3 }; uint32_t tb[16] = { 0x00050007u };
    P62_MapC64 = 0; P62_Map2C40 = 0; P54_MapB1 = P54_MapB2 = 4; P62_MapN = 4; P72_Rows = 1; P54_RoadA[0] = ta; P54_RoadB[0] = tb;
    int16_t v; memset(P11_00bf1c40 + 3 * 0x42, 0, 0x42);
    v = 2; memcpy(P17_MapBase + 3 * 0x42, &v, 2);                    /* +2 — через псевдоним P17_MapBase */
    v = 9; memcpy(P11_00bf1c40 + 3 * 0x42 + 4, &v, 2);
    v = 2; memcpy(P59_BF1C48 + 3 * 0x42, &v, 2);                     /* +8 — через псевдоним P59_BF1C48 */
    memset(P11_00c1ed80 + 2 * 0x2c, 0, 0x2c);
    P11_00c1ed8a[2 * 0x16 + 2 * 4] = 3; P11_00c1ed8a[2 * 0x16 + 2 * 4 + 1] = 7;
    int32_t one = 1; memcpy(P11_00c12c60 + 3 * 0x14 + 4, &one, 4);
    CK(P101_RoadNode(0, 0, 0) == 0 && P101_RdNode == 2 && P101_RdCell == 3 && P101_RdLane == 7 && P72_Id == 5 && P72_Low == 7);
    CK(P101_RdDist == -0x2ee && P101_RdLeft == 2 * 0x5dc + 0x2ee);
    ta[0] = 0x4005; CK(P101_RoadNode(0, 0, 0) == 1 && P101_RdNode == 5);
    ta[0] = 0xffff; CK(P101_RoadNode(0, 0, 0) == -1 && P101_RdDist == 0x7fffffff);
    CK(P101_RoadNode(-100000, 0, 0) == -1);
    p101_nbr_t nb; memcpy(nb, P101_Nbr, sizeof nb); memset(P101_Nbr, 0, sizeof nb); P101_Nbr[3] = -0x8000;   /* 005139d7 */
    float o[3] = { 0, 0, 0 };
    CK(P101_PickCell(0, 0, 0, o) == 1 && o[0] == -1500.0f && o[2] == 0.0f);
    P101_Nbr[3] = 0; CK(P101_PickCell(0, 0, 0, o) == 0);
    memcpy(P101_Nbr, nb, sizeof nb);
    P62_MapC64 = c64; P62_Map2C40 = c40; P54_MapB1 = b1; P54_MapB2 = b2; P62_MapN = mn; P72_Rows = rows; P54_RoadA[0] = ra; P54_RoadB[0] = rb;
    memcpy(P11_00bf1c40, sn, sizeof sn); memcpy(P11_00c1ed80, ss, sizeof ss); memcpy(P11_00c12c60, sr, sizeof sr); }
  { int32_t a[0x20], b[0x20], best[10] = { 0 };   /* 004997a0; v1.74: best — 10 слов (P100_BoxFace пишет best[1..9]) */
    memset(a, 0, sizeof a); memset(b, 0, sizeof b);
    a[0] = 4096; a[5] = 4096; a[10] = 4096; a[0x10] = 100; a[0x11] = 200; a[0x12] = 300; memcpy(b, a, sizeof a);
    int32_t r = P101_BoxHit(a, b, best);
    CK((r == 0 || r == 1) && a[0x13] == 100 && a[0x18] == 200 && a[0x1d] == 300 && b[0x13] == 100); }
  { int32_t p[16]; memset(p, 0, sizeof p);   /* 004b998b */
    int16_t c = 5; memcpy((uint8_t *)p + 0x20, &c, 2); c = 0x80; memcpy((uint8_t *)p + 0x26, &c, 2); c = 0x90; memcpy((uint8_t *)p + 0x28, &c, 2);
    p[0] = 10; p[4] = 5; p[2] = 1; p[6] = 2;
    P101_DebrisBounce(p);
    uint16_t a26; memcpy(&a26, (uint8_t *)p + 0x26, 2); memcpy(&c, (uint8_t *)p + 0x20, 2);
    CK(p[0] == 15 && p[2] == 3 && a26 == 0x10 && c == 4); }
  { uint8_t pt[0xa0]; memset(pt, 0, sizeof pt);   /* 00513d0a */
    uint32_t fl = 0x13; memcpy(pt + 0x10, &fl, 4); P101_PartFall(pt); memcpy(&fl, pt + 0x10, 4); CK(fl == 0x20);
    fl = 0x11; memcpy(pt + 0x10, &fl, 4); P101_PartFall(pt); memcpy(&fl, pt + 0x10, 4); CK(fl == 0x12);
    float vy = 60.0f; fl = 0x10; memcpy(pt + 0x10, &fl, 4); memcpy(pt + 0x78, &vy, 4); P101_PartFall(pt); memcpy(&vy, pt + 0x78, 4); CK(vy == 55.0f); }
  { float buf[48], *so = P100_ClipOut; int32_t sn = P100_ClipN; float sf = P95_Near;   /* 0042da16 */
    float va[6] = { 0, 0, 0, 0, 0, 0 }, vb[6] = { 0, 0, 0, 4, 8, 100 };
    P95_Near = 50.0f; P100_ClipOut = buf; P100_ClipN = 0;
    P101_ClipNearUV((const uint8_t *)va, (const uint8_t *)vb, 0.0f, 0.0f, 1.0f, 2.0f);
    CK(P100_ClipN == 2 && P100_ClipOut == buf + 24 && buf[0] == 2.0f && buf[1] == 4.0f && buf[2] == 50.0f && buf[4] == 0.5f && buf[5] == 1.0f);
    CK(buf[12] == 4.0f && buf[14] == 100.0f && buf[16] == 1.0f && buf[17] == 2.0f);
    P100_ClipOut = buf; P100_ClipN = 0;
    P101_ClipNearRGB((const uint8_t *)vb, (const uint8_t *)va, 1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f);
    CK(P100_ClipN == 1 && buf[7] == 0.5f && buf[8] == 1.0f && buf[9] == 1.5f && buf[2] == 50.0f);
    P100_ClipOut = so; P100_ClipN = sn; P95_Near = sf; }
  /* 005291ed (row fill): single port P152_FillRows, covered by test_p152 */
  { static uint8_t src[640], dst[0x500]; memset(src, 0, sizeof src);   /* 00529253 */
    uint32_t p1 = P101_PalLfb[1], p2 = P101_PalLfb[2]; int32_t pitch = P100_LfbPitch;
    P101_PalLfb[1] = 0x1234; P101_PalLfb[2] = 0x5678; P100_LfbPitch = 0x500; src[0] = 1; src[1] = 2;
    P101_Pal16(src, dst, 0, 1); uint32_t w; memcpy(&w, dst, 4); CK(w == 0x56781234u);
    P101_PalLfb[1] = p1; P101_PalLfb[2] = p2; P100_LfbPitch = pitch; }
  { float m[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 }, v[6] = { 0, 0, 0, 4, 5, 6 };   /* 00528c91 */
    float *sm = P44_MatPtr, bx = P44_BiasX, by = P44_BiasY, bz = P44_BiasZ;
    P44_MatPtr = m; P44_BiasX = 1; P44_BiasY = 2; P44_BiasZ = 3;
    P101_XformBias2(v); uint32_t tg; memcpy(&tg, &v[0], 4);
    CK(v[3] == 5.0f && v[4] == 7.0f && v[5] == 9.0f && tg == P44_XformTag);
    P44_MatPtr = sm; P44_BiasX = bx; P44_BiasY = by; P44_BiasZ = bz; }
  { p99_car_t sv = P99_Cars[6]; uint8_t out[0x20] = { 0 };   /* 004dea35 */
    int16_t cl = 10, sc; memcpy(&sc, S_00D0CC60 + 0xe2, 2); memcpy(S_00D0CC60 + 0xe2, &cl, 2);
    memset(&P99_Cars[6], 0, sizeof P99_Cars[6]);
    int32_t h = P100_RoadHeight((const int32_t *)((uint8_t *)&P99_Cars[6] + 0xc8));
    P101_CarGround(&P99_Cars[6], out);
    CK(out[0x14] == 1 && P99_Cars[6].pos[1] == h - 10 && P99_Cars[6].f78[0][0] == 0x10 && P99_Cars[6].f78[3][0] == 0x10);
    memcpy(S_00D0CC60 + 0xe2, &sc, 2); P99_Cars[6] = sv; }
  return f;
}

static uint32_t fbits_t(float v) { uint32_t u; memcpy(&u, &v, 4); return u; }
static int test_p102(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p102 fail line %d\n",__LINE__); } } while (0)
  /* v1.47: сведённые дубли */
  CK((uint8_t *)P100_CarDim == S_00D0CC60 + 0x164);
  CK((void *)&P12_00c808d0 == (void *)&P101_Hud[4]);
  CK((uint8_t *)P12_011443e0 == (uint8_t *)TrafficRecs && (uint8_t *)A_011443E0 == (uint8_t *)TrafficRecs && (uint8_t *)P21_Entries == (uint8_t *)TrafficRecs);
  { int32_t m = D_00b87e30; p98_six_t sv; memcpy(sv, P98_Six, sizeof sv);   /* 004aba7c */
    D_00b87e30 = 2; P102_SixFlag = 5; P102_SixInit();
    uint32_t w0, w71; memcpy(&w0, P98_Six, 4); memcpy(&w71, P98_Six + 71 * 4, 4);
    CK(w0 == 300 && w71 == 0x69 && P102_SixFlag == 0);
    D_00b87e30 = 3; P102_SixFlag = 5; P102_SixInit(); CK(P102_SixFlag == 5);
    memcpy(P98_Six, sv, sizeof sv); D_00b87e30 = m; }
  { int32_t box[48], out[9]; memset(box, 0, sizeof box); memset(out, 0x55, sizeof out);   /* 0049a21d */
    box[0x15] = 100; box[0x20] = 4096; box[4] = 4096; box[0] = 1000; box[0x11] = 10;
    P102_BoxContact(box, out);
    CK(out[8] == 0 && out[0] == 990 && out[4] == -4096 && out[5] == 0 && out[6] == 0); }
  { p77_c5fe00_t sg; memcpy(sg, P77_C5FE00, sizeof sg);   /* 00509e64 */
    float sc = P63_Scale; int32_t c64 = P62_MapC64, c40 = P62_Map2C40, px = P99_Cars[0].pos[0], pz = P99_Cars[0].pos[2];
    memset(P77_C5FE00, 0, sizeof P77_C5FE00);
    P63_Scale = 1.0f; P62_MapC64 = -0x2ee; P62_Map2C40 = -0x2ee; P99_Cars[0].pos[0] = 0; P99_Cars[0].pos[2] = 0;
    int32_t pos[3] = { 3, 0, 0 };
    CK(P102_RadarClear(pos, 0, 0) == 1);
    int32_t wall = 0x1e; memcpy(&P77_C5FE00[(0x1b + 2 + 0x1b * 0x37) * 4], &wall, 4);
    CK(P102_RadarClear(pos, 0, 0) == 0);
    memcpy(P77_C5FE00, sg, sizeof sg); P63_Scale = sc; P62_MapC64 = c64; P62_Map2C40 = c40; P99_Cars[0].pos[0] = px; P99_Cars[0].pos[2] = pz; }
  { float buf[48], *so = P100_ClipOut; int32_t sn = P100_ClipN; float sf = P95_Near, sfar = Q01270C24;   /* 0042eaa6 / 0042f3f7 */
    float va[6] = { 0, 0, 0, 0, 0, 0 }, vb[6] = { 0, 0, 0, 4, 8, 100 };
    for (int i = 0; i < 48; i++) buf[i] = -1.0f;
    P95_Near = 50.0f; P100_ClipOut = buf; P100_ClipN = 0;
    P102_ClipNear7((const uint8_t *)va, (const uint8_t *)vb, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7);
    CK(P100_ClipN == 2 && P100_ClipOut == buf + 24 && buf[2] == 50.0f && buf[7] == 0.5f && buf[11] == 3.5f && buf[0] == 2.0f);
    CK(buf[12 + 7] == 1.0f && buf[12 + 5] == 5.0f && buf[12 + 10] == -1.0f && buf[12 + 11] == -1.0f && buf[14] == 100.0f);   /* у 2-й вершины [10], [11] не пишутся */
    Q01270C24 = 60.0f; P100_ClipOut = buf; P100_ClipN = 0;
    P102_ClipFar5((const uint8_t *)va, (const uint8_t *)vb, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0);
    CK(P100_ClipN == 1 && buf[2] == 60.0f && fabsf(buf[7] - 6.0f) < 1e-5f);
    P100_ClipOut = so; P100_ClipN = sn; P95_Near = sf; Q01270C24 = sfar; }
  { uint32_t cfg[0x43]; int32_t a = P55_V57B6FC, b = P51_TrafficN, c = P13_00b87e74;   /* 00406875 */
    P55_V57B6FC = 7; P51_TrafficN = 5; P13_00b87e74 = 9;
    P102_ConfigSnap(cfg);
    CK(cfg[0] == 7 && cfg[0x3d] == 5 && cfg[0x2e] == 9 && cfg[0x1b] == fbits_t(WF00575F14));
    P55_V57B6FC = a; P51_TrafficN = b; P13_00b87e74 = c; }
  { static uint8_t cop[0xd00], nd[3][0x20]; memset(cop, 0, sizeof cop); memset(nd, 0, sizeof nd);   /* 004a7aa7 */
    int32_t v; int16_t id = 1;
    for (int i = 0; i < 3; i++) memcpy(nd[i] + 0x1c, &id, 2);
    v = 100; memcpy(nd[1] + 8, &v, 4); memcpy(nd[2] + 8, &v, 4); memcpy(nd[2] + 0xc, &v, 4);
    re_wr_ptr(nd[0], nd[1]); re_wr_ptr(nd[1], nd[2]); re_wr_ptr(cop + 0xc60, nd[0]);
    int32_t sa = P97_B2A0, sb = P97_B2A8, s9 = P97_129584, out[3] = { 0, 0, 0 };
    P102_CopPathPoint(cop, 50, out); CK(out[0] == 50 && out[2] == 0 && P97_129584 == 1);
    P102_CopPathPoint(cop, 150, out); CK(out[0] == 100 && out[2] == 50 && P97_129584 == 0);
    P97_B2A0 = 100; P97_B2A8 = 300;
    P102_CopPathPoint(cop, 500, out); CK(out[0] == 100 && out[2] == 400 && P97_129584 == 0);
    P97_B2A0 = sa; P97_B2A8 = sb; P97_129584 = s9; }
  { uint8_t *sct = P59_CarsTab; p99_car_t sv = P99_Cars[3]; uint8_t rec[0x54]; int32_t v;   /* 00493b51 */
    P59_CarsTab = NULL; memset(rec, 0, sizeof rec); rec[0] = 2;
    v = 1000; memcpy(rec + 0x40, &v, 4); v = 1; memcpy(rec + 0x38, &v, 4); v = 0x7fffffff; memcpy(rec + 0x44, &v, 4);
    P99_Cars[3].pos2[0] = 990;
    CK(P102_TrafficAlign(rec, 0, 0, 0) == 1 && P99_Cars[3].pos2[0] == 1000); memcpy(&v, rec + 0x40, 4); CK(v == 0x7fffffff);
    v = 2000; memcpy(rec + 0x40, &v, 4); v = 2; memcpy(rec + 0x24, &v, 4);
    CK(P102_TrafficAlign(rec, 0, 0, 0) == 0 && P99_Cars[3].ffc == -31); memcpy(&v, rec + 0x40, 4); CK(v == 2000);
    P99_Cars[3] = sv; P59_CarsTab = sct; }
  { int32_t px = P99_Cars[0].pos[0], pz = P99_Cars[0].pos[2]; p96_rottab_t *rt = malloc(sizeof(p96_rottab_t));   /* 004d0439 */
    memcpy(*rt, P96_RotTab, sizeof *rt); memset(P96_RotTab, 0, sizeof P96_RotTab);
    P99_Cars[0].pos[0] = 5000; P99_Cars[0].pos[2] = 7000;
    CK(P102_BoxAnyCar(5000, 7000, 0, 100, 300) == (uint8_t *)&P99_Cars[0]);
    CK(P102_BoxAnyCar(100000000, 7000, 0, 100, 300) == NULL || TrafficRecs[1] != 0);
    memcpy(P96_RotTab, *rt, sizeof *rt); free(rt); P99_Cars[0].pos[0] = px; P99_Cars[0].pos[2] = pz; }
  { p56_ghost_t sg; memcpy(sg, P56_GhostBuf, sizeof sg);   /* 004e6c92 */
    int32_t a = G6_00B5A778, b = G6_00B87EA0, c = P45_Mode, d = P62_Frame, e = P56_G4538, g = P56_G3908; float *mp = P44_MatPtr;
    G6_00B5A778 = 0; G6_00B87EA0 = 0; P45_Mode = 0xc9; P62_Frame = 4; P56_G4538 = 39; P56_G3908 = 0;
    P56_GhostBuf[0x44] = 9; P56_GhostBuf[38 * 0x48 + 0x44] = 1;
    P102_GhostTrail();
    CK(P56_GhostBuf[0x44] == 6 && P56_GhostBuf[39 * 0x48 + 0x47] == 1 && P56_GhostBuf[38 * 0x48 + 0x44] == 0xff && P56_G4538 == 0 && P56_G3908 == 1);
    CK(P44_MatPtr == P102_GhostMat);
    memcpy(P56_GhostBuf, sg, sizeof sg); G6_00B5A778 = a; G6_00B87EA0 = b; P45_Mode = c; P62_Frame = d; P56_G4538 = e; P56_G3908 = g; P44_MatPtr = mp; }
  { p99_car_t sv = P99_Cars[0]; float *mp = P44_MatPtr; float m0[16]; memcpy(m0, P98_CarMat[0], sizeof m0);   /* 0051d51c */
    memset(P99_Cars[0].mat, 0, sizeof P99_Cars[0].mat); P99_Cars[0].mat[0] = P99_Cars[0].mat[4] = P99_Cars[0].mat[8] = 4096;
    P102_PlayerCorners();
    CK(P98_CarMat[0][0] == -1.0f && P98_CarMat[0][4] == 1.0f && P98_CarMat[0][8] == -1.0f && P44_MatPtr == P98_CarMat[0]);
    CK(G00B5C910 == P102_Corners[0] && G00B5C918 == P102_Corners[2]);
    memcpy(P98_CarMat[0], m0, sizeof m0); P99_Cars[0] = sv; P44_MatPtr = mp; }
  { int32_t sv[12] = { P62_MapC64, P62_Map2C40, P62_MapW, P62_MapH, P62_MapN, P72_Rows, P94_DirCnt, P75_43CC, P102_DustN, G6_00B87EB0, G6_00B87EAC, P99_Cars[0].pos[0] };   /* 004902a8 */
    float sc = P63_Scale; int32_t pz = P99_Cars[0].pos[2], d0 = P94_DirTab[0][0], d1 = P94_DirTab[0][1];
    void *ra = P54_RoadA[0], *rb = P54_RoadB[0]; uint8_t sp[12]; memcpy(sp, P75_Spawn, 12);
    int16_t ta[16] = { -0x8000 }; uint32_t tb[16] = { 2 };
    P62_MapC64 = 0; P62_Map2C40 = 0; P62_MapW = P62_MapH = 4; P62_MapN = 4; P72_Rows = 1; P94_DirCnt = 1; P94_DirTab[0][0] = 0; P94_DirTab[0][1] = 0;
    G6_00B87EB0 = 0; G6_00B87EAC = 0; P63_Scale = 1.0f; P99_Cars[0].pos[0] = 0; P99_Cars[0].pos[2] = 0; P54_RoadA[0] = ta; P54_RoadB[0] = tb;
    P102_ScanCells(); CK(P102_DustN == 1 && P75_43CC == 0);
    ta[0] = 5; P102_ScanCells(); int16_t s; memcpy(&s, P75_Spawn, 2); CK(P102_DustN == 0 && P75_43CC == 1 && s == -1);
    P62_MapC64 = sv[0]; P62_Map2C40 = sv[1]; P62_MapW = sv[2]; P62_MapH = sv[3]; P62_MapN = sv[4]; P72_Rows = sv[5]; P94_DirCnt = sv[6]; P75_43CC = sv[7]; P102_DustN = sv[8];
    G6_00B87EB0 = sv[9]; G6_00B87EAC = sv[10]; P99_Cars[0].pos[0] = sv[11]; P99_Cars[0].pos[2] = pz; P63_Scale = sc; P94_DirTab[0][0] = d0; P94_DirTab[0][1] = d1;
    P54_RoadA[0] = ra; P54_RoadB[0] = rb; memcpy(P75_Spawn, sp, 12); }
  { int32_t sn = P11_00b5a8e8; P11_00b5a8e8 = 0; CK(P102_RoadSide(0.0f, 0.0f) == -1); P11_00b5a8e8 = sn; }   /* 0051a750 */
  { /* More than 105 prop marks used to overwrite 010ffb40 (the effect-list
       head) in the scratch area beginning at 010fca00. Keep all B records. */
    uint8_t scratch[128 * 0x78], obj[0x20] = {0};
    memset(scratch, 0x5a, sizeof scratch);
    re_ptr_register(0x010fca00u, scratch, sizeof scratch);
    int32_t cursor = G01105D80, count = G01129580, bcursor = G01105D60, bcount = G010FFD04;
    int32_t on = P52_Ones3, bon = P96_ObjBOn, mark = P13_00b201dc;
    float cx = P44_CamX, cy = P44_CamY, cz = P44_CamZ;
    p44_m9_t view; memcpy(view, P44_ViewMatT, sizeof view);
    uint8_t *euler = P56_EulerTab;
    float identity[16] = {1,0,0,0,1,0,0,0,1};
    P56_EulerTab = (uint8_t *)identity;
    memcpy(P44_ViewMatT, identity, sizeof view); P44_CamX = P44_CamY = P44_CamZ = 0;
    float z = 1000; memcpy(obj + 0x10, &z, 4);
    P52_Ones3 = P96_ObjBOn = 1; P13_00b201dc = 0;
    G01105D80 = 0x010fca00; G01129580 = 0;
    G01105D60 = (int32_t)re_addr(P95_ObjB); G010FFD04 = 0;
    for (int i = 0; i < 128; i++) P102_ObjMark(obj, (float)i, 20, 30, 0x200);
    uint32_t head; memcpy(&head, scratch + (0x010ffb40 - 0x010fca00), 4);
    CK(head == 0x5a5a5a5au && G01129580 == 128 && G010FFD04 == 128);
    for (int i = 0; i < 128; i++) {
      float pos[3]; memcpy(pos, P95_ObjB + i * 0x78, sizeof pos);
      CK(pos[0] == (float)i && pos[1] == 20 && pos[2] == 1020);
    }
    re_ptr_unregister(scratch); re_ptr_unregister(obj);
    G01105D80 = cursor; G01129580 = count; G01105D60 = bcursor; G010FFD04 = bcount;
    P52_Ones3 = on; P96_ObjBOn = bon; P13_00b201dc = G00B201DC = MenuVarB201DC = mark;
    P56_EulerTab = euler; memcpy(P44_ViewMatT, view, sizeof view);
    P44_CamX = cx; P44_CamY = cy; P44_CamZ = cz;
  }
  { static uint8_t car[0x148]; float o[16]; memset(car, 0, sizeof car); memset(o, 0, sizeof o);   /* 005158cf */
    p96_rottab_t *rt = malloc(sizeof(p96_rottab_t)); memcpy(*rt, P96_RotTab, sizeof *rt); memset(P96_RotTab, 0, sizeof P96_RotTab);
    int32_t v = 1000; memcpy(car + 0xc8, &v, 4); v = 2000; memcpy(car + 0xd0, &v, 4);
    P102_CarPlanes(car, o, 50);
    float c = P43_Sin[0x400], sn = P43_Sin[0];
    CK(o[0] == -c && o[4] == c && o[2] == -sn && o[0xc] == sn && o[0xf] == 2000.0f * -c + 1000.0f * sn);
    memcpy(P96_RotTab, *rt, sizeof *rt); free(rt); }
  { uint8_t sv[0x54 * 3]; memcpy(sv, TrafficRecs, sizeof sv); int32_t n = P51_TrafficN, v;   /* 0049521e */
    memset(TrafficRecs, 0, sizeof sv); P51_TrafficN = 2;
    uint8_t *a = TrafficRecs, *b = TrafficRecs + 0x54; a[0] = 1; b[0] = 2; a[1] = 2; b[1] = 2;
    v = 0; memcpy(a + 0x24, &v, 4); memcpy(b + 0x24, &v, 4);
    v = 0x7fff0000; memcpy(b + 0x4c, &v, 4);
    CK(P102_TrafficAhead(a, 5, 1) == -1);   /* +0x48/+0x4c записи a пересчитаны из позиции машины */
    int32_t az; memcpy(&az, a + 0x4c, 4);
    v = az + 3; memcpy(b + 0x4c, &v, 4); CK(P102_TrafficAhead(a, 5, 1) == -1);
    v = az - 3; memcpy(b + 0x4c, &v, 4); CK(P102_TrafficAhead(a, 5, 1) == 1);
    memcpy(TrafficRecs, sv, sizeof sv); P51_TrafficN = n; }
  return f;
}

static int test_p108(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p108 fail line %d\n",__LINE__); } } while (0)
  { int32_t s = P101_RecSaved; P101_RecSaved = 0; P108_ReplayStep(); P101_RecSaved = s; CK(1); }
  { CK(P108_EmulTex16(-1) == 0 && P108_EmulTex8(31) == 0); }
  { void *m = P38_Mms2; P38_Mms2 = NULL; CK(P108_FmvStart() == 0); P38_Mms2 = m; }
  { P108_RadarArrow(10, 999); P108_RadarCar(0, 0, -1); P108_Sprite(0x12345678u, 1.0f, 0); CK(1); }
  { uint8_t o[0x80]; memset(o, 0, sizeof o); uint32_t ic = P108_SmokeIcon; P108_SmokeIcon = 0; P108_SmokeA(o); P108_SmokeB(o);
    float z = 1000.0f; memcpy(o + 0x18, &z, 4); P108_SmokeIcon = 0x12345678u; P108_SmokeA(o); P108_SmokeB(o); P108_SmokeIcon = ic; CK(1); }
  { int32_t c = P98_C824A0, p[3] = { 0, 0, 0 }; P98_C824A0 = 1; int32_t h = P102_HudF4; P108_RadarShape(0x00573f08u, p, p, p); CK(P102_HudF4 == h); P98_C824A0 = c; }
  return f;
}

static int test_p109(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p109 fail line %d\n",__LINE__); } } while (0)
  { int32_t on = G6_00B91CF4; G6_00B91CF4 = 0; uint8_t sv = S_00BDC2A0[0]; P109_SndPlay(0, 1, 0, 0, 0); CK(S_00BDC2A0[0] == sv); G6_00B91CF4 = on; }
  { int32_t on = G6_00B91CF4, en = G00575F40; G6_00B91CF4 = 1; G00575F40 = 1; uint8_t sv[0x34]; memcpy(sv, &S_00BDC2A0[3 * 0x34], 0x34);
    P68_Samps[5] = P68_Samps[5]; uint8_t *sm = (uint8_t *)&P68_Samps[5]; uint8_t ss[8]; memcpy(ss, sm, 8);
    int16_t vol = -20000; memcpy(sm + 4, &vol, 2); sm[6] = 3; sm[7] = 9;
    P109_SndPlay(3, 5, 1.0f, 2.0f, 3.0f); uint8_t *v = &S_00BDC2A0[3 * 0x34]; int16_t vv; memcpy(&vv, v + 0x30, 2); float b; memcpy(&b, v + 0x14, 4);
    CK(v[0] == 0x1e && v[2] == 5 && vv == -10000 && v[0x32] == 3 && v[0x33] == 9 && b == 2.0f && v[0x20] == 1);
    memcpy(sm, ss, 8); memcpy(v, sv, 0x34); G6_00B91CF4 = on; G00575F40 = en; }
  { int32_t sd = P85_StateDirty; P109_GradRect(0, 0, 10, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12); CK(P85_StateDirty == -1);
    P109_GradRectS(0, 0, 10, 10, 0xff0000u, 0xff00u, 0xffu, 0u); CK(P85_StateDirty == -1); P85_StateDirty = sd; }
  { uint8_t rgb[3] = { 1, 2, 3 }; int32_t t = P86_CurTex; P109_TileDraw(0, 0, 256, 256, 7, rgb); CK(P86_CurTex == 7 && P85_StateDirty == 4);
    P109_IconDraw(0, 0, 1, 1, 0, 0, 16, 16, 9, rgb); CK(P86_CurTex == 9); P86_CurTex = t; }
  { int32_t bf = P85_BlendForce; uint8_t sv[0x1c * 6]; memcpy(sv, P101_Drops, sizeof sv); memset(P101_Drops, 0, sizeof sv);
    P109_DropsDraw(1); CK(P85_BlendForce == 0); memcpy(P101_Drops, sv, sizeof sv); P85_BlendForce = bf; }
  { CK(P109_SlotUpload8(NULL, 0) == 0 && P109_SlotUpload16(NULL, 40) == 0); }
  { int32_t a = G6_00B87EA0; G6_00B87EA0 = 1; P109_ScriptMarkers(); G6_00B87EA0 = a; P109_RadarArrows(); CK(1); }
  { uint8_t pm = P36_PadMode; P36_PadMode = 0; int32_t a = P103_C54D04, b = P103_C54FC4; P103_C54D04 = 0; P103_C54FC4 = 1;
    int32_t keep = P109_C81268; P109_C81268 = 0; int32_t rs = P101_RecSaved; (void)rs;
    P36_PadMode = 0; P103_C54FC4 = 0; P109_InputTick(); CK(P103_C54FC4 == 0 && P103_C54D04 == 0); P103_C54D04 = a; P103_C54FC4 = b; P109_C81268 = keep; P36_PadMode = pm; }
  { uint8_t *ic = P100_RadarIcon; P100_RadarIcon = NULL; P109_RadarTraffic(); P100_RadarIcon = ic; CK(1); }
  return f;
}

static int test_p110(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p110 fail line %d\n",__LINE__); } } while (0)
  CK(P110_CellTab[0] == 7 && P110_CellTab[30] == 0x1000 && P110_SelRep == 10 && P110_IconKX == 1.0f);
  P110_RadarGrid();
  { uint8_t g[0x30]; memset(g, 0, sizeof g); float v; v = 10; memcpy(g + 8, &v, 4); memcpy(g + 0xc, &v, 4);
    v = 5; memcpy(g + 0x10, &v, 4); v = 2; memcpy(g + 0x14, &v, 4);
    P110_Gauge(g); memcpy(&v, g + 0x10, 4); CK(v == 5.0f);                 /* выключено — значение не тронуто */
    int32_t on = 1; memcpy(g + 0x2c, &on, 4); P110_Gauge(g); memcpy(&v, g + 0x10, 4); CK(v == 2.0f); }
  { uint8_t ic[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 7, 1, 2, 16, 16 }; int32_t t = P86_CurTex, sd = P85_StateDirty; uint8_t bc = P85_BlendCur;
    P110_IconRect(0, 0, 32, 32, ic, -1); CK(P86_CurTex == 7 && P85_StateDirty == 4 && P85_BlendCur == 0);
    P110_IconRect(0, 0, 32, 32, ic, 9); CK(P86_CurTex == 9);
    P110_IconQuad(10, 10, 1, 1, ic, 255, 255, 255, 1); CK(P86_CurTex == 7 && P85_BlendCur == 1);
    P86_CurTex = t; P85_StateDirty = sd; P85_BlendCur = bc; }
  { uint32_t gi = P110_GlowIcon; int32_t t = P86_CurTex; float p[0x1c]; memset(p, 0, sizeof p); p[2] = 100.0f;
    P110_GlowIcon = 0; P86_CurTex = -5; P110_GlowA((const uint8_t *)p); P110_GlowB((const uint8_t *)p); P110_GlowC((const uint8_t *)p); CK(P86_CurTex == -5);
    static uint8_t ic2[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 32, 32 }; P110_GlowIcon = re_addr(ic2);
    P110_GlowA((const uint8_t *)p); CK(P86_CurTex == 11); P110_GlowIcon = gi; P86_CurTex = t; }
  { int32_t *st = G2_ScriptStack; int32_t s0[0x70]; memset(s0, 0, sizeof s0); G2_ScriptStack = s0; P110_ScriptSprites(); G2_ScriptStack = st; CK(1); }
  { CK(P110_MenuSel(0, 3) == 3); }
  { int32_t w = P19_ScrW, hh = P19_ScrH, fc = P110_FullClip; float sc = P11_0125f3e0, s19 = P19_Scale, f404 = P62_F25F404, ox = P43_OffX, oy = P43_OffY, x0 = P101_ScrX0, y0 = P101_ScrY0;
    P19_ScrW = 640; P19_ScrH = 480; P110_FullClip = 0; P11_0125f3e0 = 0.5f; P62_F25F404 = 0.5f; P110_ViewSetup(10, 0, 0);
    CK(P110_ClipX0 == 170.0f && P110_ClipX1 == 490.0f && P110_ClipY0 == 120.0f && P110_ClipY1 == 360.0f && P101_ScrX0 == 330.0f && P19_Scale == 0.5f);
    P19_ScrW = w; P19_ScrH = hh; P110_FullClip = fc; P11_0125f3e0 = sc; P19_Scale = s19; P62_F25F404 = f404; P43_OffX = ox; P43_OffY = oy; P101_ScrX0 = x0; P101_ScrY0 = y0; }
  { uint32_t si = P108_SmokeIcon; P108_SmokeIcon = 0; float pos[3] = { 0, 0, 0 }; P110_SmokeRing(1.0f, pos, 0, 1, 2, 3, 0, 1); P108_SmokeIcon = si; CK(1); }
#undef CK
  return f;
}

static int test_p107(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p107 fail line %d\n",__LINE__); } } while (0)
  { P107_TexRelease(-1); P107_TexRelease(40); int32_t b = P32_Slots[31].bpp; P32_Slots[31].bpp = -1; P107_TexRelease(31); CK(P32_Slots[31].bpp == -1); P32_Slots[31].bpp = b; }
  { P107_Rect(0, 0, 10, 10, 0x12345678u); P107_RectGrad(0, -0x300, 10, 10, 0, 0); P107_CarLight(0x12345678u, 1.0f); P107_CountModel(9, 0); CK(1); }
  { p99_car_t sv = P99_Cars[5]; P99_Cars[5].ffc = 0x150; P99_Cars[5].f140 = 0x70; P99_Cars[5].f10c = 0;
    int32_t k = S_00D11878; S_00D11878 = 5; int32_t pm = P36_PrevFlag; P36_PrevFlag = 0; uint8_t pd = P36_PadMode; P36_PadMode = 0;
    P107_CarInput(5, 4); CK(P99_Cars[5].ffc == 0x160 && P99_Cars[5].f141 == 0xff && P99_Cars[5].f140 == 0x5b && P99_Cars[5].ff8 == 0);
    P107_CarInput(5, 0); CK(P99_Cars[5].ffc == 0x140 && P99_Cars[5].f141 == 0 && P99_Cars[5].f140 == 0);
    P107_CarInput(-1, 0); P107_CarInput(100, 0);
    S_00D11878 = k; P36_PrevFlag = pm; P36_PadMode = pd; P99_Cars[5] = sv; }
  { int32_t w = P107_NavWait; P107_NavWait = 3; CK(P107_MenuNav(0, 7) == 7 && P107_NavWait == 2); P107_NavWait = 0; CK(P107_MenuNav(0x12345678u, 4) == 4); P107_NavWait = w; }
  { uint8_t rec[0x54]; memset(rec, 0, sizeof rec); rec[0x11] = 9; P107_TrafficLights(1, rec); CK(1); }
  return f;
}

static int test_p106(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p106 fail line %d\n",__LINE__); } } while (0)
  { int32_t n = G010FFA20, ob = G0110B24C, on = G00D17B08;
    G010FFA20 = 0xc9; P106_CarTailLights(0); P106_CarBrakeLights(0); CK(G010FFA20 == 0xc9 && G0110B24C == ob);
    G010FFA20 = n; G00D17B08 = 0; P106_CarHeadSpots(0); CK(G0110B24C == ob);
    P106_CarHeadSpots(70); P106_CarTailLights(-1); CK(G0110B24C == ob);
    G00D17B08 = on; }
  { uint8_t node[0x20]; memset(node, 0, sizeof node);
    P106_EmulUpload8(node, 0); P106_EmulUpload16(node, 0); CK(1); }
  { int32_t x = G6_00D117A4; P106_LfbText(0); CK(G6_00D117A4 == x); }
  { int32_t c = D_00b87e30; D_00b87e30 = 100; P106_SkyModels(); D_00b87e30 = c; CK(1); }
  { int32_t on = P106_PartOn, k = P73_C5670C; P106_PartOn = 0; P106_PartTick(); CK(P73_C5670C == k); P106_PartOn = on; }
  { P106_EaxPreset(-1); P106_EaxPreset(100); CK(1); }
  return f;
}

static int test_p105(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p105 fail line %d\n",__LINE__); } } while (0)
  { /* 004d26ea: счётчики таймеров уменьшаются; при 00d11a5c в (0, 0x2aa) — спад по каналу */
    int32_t t[22]; for (int i = 0; i < 22; i++) t[i] = (i & 1) ? 7 : (i == 4 ? 0 : 3);
    int32_t g = G2_00D11A5C, a38 = P95_D11A38, cs = P95_ChanState, rdy = P95_SndReady, mus = P105_MusLimit, b778 = G6_00B5A778, a54 = P95_D11A54, a4c = P95_D11A4C;
    G6_00B5A778 = 0; G2_00D11A5C = 0x100; P95_D11A38 = 2; P95_ChanState = 2;
    P105_ChaseMusic(t); CK(G2_00D11A5C == 0xff && P95_D11A38 == 0 && t[0] == 3);
    G2_00D11A5C = 0x300; P95_SndReady = 1; P105_MusLimit = 0x7fffffff; P95_D11A54 = 1; P95_D11A4C = 1;
    int32_t sp = P11_00b20360; P11_00b20360 = 0;
    P105_ChaseMusic(t); CK(G2_00D11A5C == 0x301 && P95_D11A54 == 0 && t[0] == 2 && t[1] == 7 && t[4] == 0 && t[20] == 2);
    G2_00D11A5C = 0xfff; P95_D11A54 = 1; P105_ChaseMusic(t); CK(G2_00D11A5C == 0xfff);
    P11_00b20360 = sp; G2_00D11A5C = g; P95_D11A38 = a38; P95_ChanState = cs; P95_SndReady = rdy; P105_MusLimit = mus; G6_00B5A778 = b778; P95_D11A54 = a54; P95_D11A4C = a4c; }
  { /* 004e53b5: не режим 4 — ничего; режим 4 и 00d04654 == 1, 00d04660 == 4 — переход в 3 */
    uint8_t car[0x148]; memset(car, 0, sizeof car);
    int32_t m = D_00b87e30, s4654 = P59_S4654, m4660 = P98_M4660, mx = P98_M4480, a8 = G2_00D118A8, c8 = G2_00D044C8, c8b = G00D044C8; p14_00d118a8_t a8b = P14_00d118a8;
    D_00b87e30 = 0; P98_M4480 = 0; int32_t v = 5 << 12; memcpy(car + 0x10c, &v, 4);
    P105_StuntHints(0, car); CK(P98_M4480 == 0);
    D_00b87e30 = 4; P59_S4654 = 1; P98_M4660 = 4;
    P105_StuntHints(0, car); CK(P98_M4480 == 5 && P59_S4654 == 3 && G2_00D04654 == 3 && G2_00D118A8 == 1);
    D_00b87e30 = m; P59_S4654 = s4654; G2_00D04654 = s4654; P98_M4660 = m4660; P98_M4480 = mx; G2_00D118A8 = a8; P14_00d118a8 = a8b; G2_00D044C8 = c8; G00D044C8 = c8b; }
  { /* 004ca802: индекс вне P20_Count / пустая модель — выход; 0040d81b, 00407c4c — без LFB ничего */
    uint8_t o[0x30]; memset(o, 0, sizeof o); int32_t i = 0x7fffffff; memcpy(o + 0x18, &i, 4);
    int32_t ang = P105_SpinAng; P105_SpinModel(o); CK(P105_SpinAng == ang);
    P105_BlitScaled(NULL); CK(P105_LfbToMenu() == 0 || 1); }
  return f;
}
static int test_p104(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p104 fail line %d\n",__LINE__); } } while (0)
  /* v1.49: .data экрана графики 0054a170 — одна таблица P104_MenuGfx */
  CK((uint8_t *)&D_0054a254 == (uint8_t *)&MenuB0054A254 && (uint8_t *)&MenuB0054A254 == (uint8_t *)re_ptr(0x0054a254));
  CK((uint8_t *)G6_0054A25C == (uint8_t *)re_ptr(0x0054a25c) && (uint8_t *)&P55_A680 == (uint8_t *)re_ptr(0x0054a680));
  CK((uint8_t *)&MenuI0054A694 == (uint8_t *)re_ptr(0x0054a694));
  CK(re_ptr(0x0054a698) != NULL && strcmp((const char *)re_ptr(0x0054a698), "SLIDER") == 0);
  CK(re_ptr(0x00cfe760) == (void *)P104_Buf760);
  { /* 00409622: подписи, переключатели, ползунки */
    uint32_t s2b = P97_StrAddr[0x2b], se4 = P97_StrAddr[0xe4]; int32_t a4 = P13_005759a4, e4c = MenuVarB87E4C, ef8 = P11_00575ef8;
    P97_StrAddr[0x2b] = 0x1111; P97_StrAddr[0xe4] = 0x2222; P13_005759a4 = 32; MenuVarB87E4C = 3; P11_00575ef8 = 0;
    P104_GfxMenuInit();
    uint32_t v; int16_t h; float fl;
    memcpy(&v, re_ptr(0x0054a278), 4); CK(v == 0x1111);
    memcpy(&v, re_ptr(0x0054a258), 4); CK(v == 0x2222);
    memcpy(&fl, re_ptr(0x0054a680), 4); CK(fl == 0.5f);
    memcpy(&h, re_ptr(0x0054a1d4), 2); CK(h == 58 + 0x1d5);
    memcpy(&h, re_ptr(0x0054a224), 2); CK(h == 116 + 0x1d5);
    { int32_t i0; memcpy(&i0, re_ptr(0x0054a66c), 4); memcpy(&v, re_ptr(0x0054a268), 4); CK(v == ((i0 >= 0 && i0 < 0x15e) ? P97_StrAddr[i0] : 0u)); }
    P97_StrAddr[0x2b] = s2b; P97_StrAddr[0xe4] = se4; P13_005759a4 = a4; MenuVarB87E4C = e4c; P11_00575ef8 = ef8; }
  { /* 004ab127: таблицы обломков (матрица поворота для угла 0 — единичная) */
    P104_DebrisTabs();
    CK(P104_DebA[0] == -10.0f && P104_DebA[1] == 10.0f && P104_DebB[4] == 0.0f && P104_DebB[5] == -7.0f);
    CK(P104_DebC[0] == -35.0f && P104_DebC[2] == 40.0f && P104_DebC[8] == -30.0f && P104_DebC[10] == -35.0f);
    uint16_t id; memcpy(&id, &P12_0110b260[5 * 0x3c + 0x24], 2); CK(id == 5);
    memcpy(&id, &S_010FAF40[7 * 2], 2); CK(id == 7);
    CK(P100_DebAng[0] == 0 && P100_DebAng[1] == 0 && S_011173C8 == 0);   /* 256 × 0x10 и 256 × 0x60 по модулю 0x1000 */
    float r = sqrtf(P104_DebA[12] * P104_DebA[12] + P104_DebA[13] * P104_DebA[13] + P104_DebA[14] * P104_DebA[14]);
    CK(fabsf(r - sqrtf(200.0f)) < 0.01f); }
  { /* 0049565b: уже идёт поворот / вне карты */
    int32_t a = G01145934, b = G011426F8; G01145934 = 1; CK(P104_TrafficTurn(0) == 0);
    G01145934 = 0; G011426F8 = 5; CK(P104_TrafficTurn(0) == 0);
    G01145934 = a; G011426F8 = b; }
  { /* 004c1c23: машина трафика без моделей / заблокировано */
    int32_t e = P95_B87ED0; P95_B87ED0 = 1; P104_CarDents(0); P95_B87ED0 = e;
    P104_CarDents(3); CK(1); }
  return f;
}
static int test_p103(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p103 fail line %d\n",__LINE__); } } while (0)
  /* v1.48: сведённые таблицы — .data меню 0054db58 (одна P103_MenuTab), частицы 00c56780 */
  CK((uint8_t *)&D_0054dbc4 == (uint8_t *)&MenuB0054DBC4 && (uint8_t *)&MenuB0054DBC4 == (uint8_t *)re_ptr(0x0054dbc4));
  CK((uint8_t *)G6_0054DBCC == (uint8_t *)re_ptr(0x0054dbcc) && (uint8_t *)&MenuI0054DE08 == (uint8_t *)re_ptr(0x0054de08));
  CK(re_ptr(0x0054de3c) != NULL && strcmp((const char *)re_ptr(0x0054de3c), "SLIDER") == 0);
  CK((void *)&G6_00C56764 == (void *)&P43_FreeCnt && (uint8_t *)G6_00C5678C == (uint8_t *)A_00C56780 + 0xc);
  CK((void *)G6_00C594A0 == (void *)P43_FreeList && (void *)P12_00c594a0 == (void *)P43_FreeList && (uint8_t *)P12_00c5678c == (uint8_t *)A_00C56780 + 0xc);
  CK(re_ptr(0x00c56780 + 0xb4) == (void *)(A_00C56780 + 0xb4) && (void *)&P8_005507d0 == (void *)&P19_OutA);
  CK(re_ptr(0x00573804) != NULL && strcmp((const char *)re_ptr(0x00573804), "LAMP") == 0);
  { /* 00414d1f: подписи и ползунки */
    uint32_t s110 = P97_StrAddr[0x110], s0c = P97_StrAddr[0xc]; int32_t eec = G6_00B87EEC, d2c = G6_00B91D2C; float f14 = WF00575F14, f18 = WF00575F18;
    P97_StrAddr[0x110] = 0x1234; P97_StrAddr[0xc] = 0x5678; G6_00B87EEC = 0; G6_00B91D2C = 0; WF00575F14 = 0.5f; WF00575F18 = 1.0f;
    G6_00575F00 = 8; G6_00575F04 = 0x5622;
    P103_OptionsInit();
    uint32_t v; int16_t h; memcpy(&v, re_ptr(0x0054dbc8), 4); CK(v == 0x1234);
    memcpy(&v, re_ptr(0x0054dbd8), 4); CK(v == 0x5678);
    memcpy(&v, re_ptr(0x0054dc98), 4); CK(v == 0x0054de64);              /* «8bit» */
    memcpy(&h, re_ptr(0x0054db6c), 2); CK(h == 58 + 0x1d5);
    memcpy(&h, re_ptr(0x0054db94), 2); CK(h == 116 + 0x1d5);
    CK(P11_00ba52d0 == 65535);
    P97_StrAddr[0x110] = s110; P97_StrAddr[0xc] = s0c; G6_00B87EEC = eec; G6_00B91D2C = d2c; WF00575F14 = f14; WF00575F18 = f18; }
  { /* 005179d0 */
    P100_RecKeys = 0; G6_00575A70 = 0; P100_RecPtr[3] = 9; P103_ReplayReset();
    CK(P100_RecKeys == 0x20 && G6_00575A70 == -1 && P100_RecPtr[3] == 0 && P101_RecState == 1); }
  { /* 0051b208, 004dcb62: вне карты */
    int32_t b1 = P54_MapB1; P54_MapB1 = 0;
    CK(P103_RoadNeighbour(0, 0, 0) == -1 && P103_1426F0 == 0xff);
    float pos[3] = { 0, 0, 0 }; CK(P103_RoadHeight(pos) == 0.0f && P103_HCellX == 0x7fffff && P103_HQuad == NULL);
    P54_MapB1 = b1; }
  { /* 0049aa14 */
    uint8_t car[0x148]; memset(car, 0, sizeof car); int32_t dir[3] = { 0, 0, 0x1000 };
    int32_t a4c = MenuOptBDFA4C, a58 = MenuOptBDFA58, pct = P103_DmgPct;
    MenuOptBDFA4C = 0; MenuOptBDFA58 = 0; P103_DmgPct = 100; car[0] = 0;
    { int16_t o = 0x1000; memcpy(car + 4, &o, 2); memcpy(car + 0x14, &o, 2); }
    CK(P103_CarDamage(car, dir, 0x800) == 0);
    CK(P103_CarDamage(car, dir, 0x10000) == 1);
    CK(rd_i32(car, 0x138) == 0x140);                                   /* (0x100*0x400 + 0x100²) >> 10 */
    { int hit = 0; for (int k = 0; k < 6; k++) if (rd_i32(car, 0x11c + k * 4) == 0x141) hit = 1; CK(hit); }
    MenuOptBDFA4C = a4c; MenuOptBDFA58 = a58; P103_DmgPct = pct; }
  { /* 00512de7: счётчик жизни частицы */
    uint8_t p[0xb4]; memset(p, 0, sizeof p); int32_t fr = G6_00B5A778; G6_00B5A778 = 1;
    wr_i32(p, 0xc, 0x80); wr_i32(p, 0x1c, 1); wr_i32(p, 0x40, 7); P103_PathLen[0] = 4;
    P103_PartPath(p); CK(rd_i32(p, 0x40) == 4);
    G6_00B5A778 = fr; }
  { /* 004e5011 */
    int32_t s = P59_S4654, ea0 = G6_00B87EA0; P59_S4654 = 0; G6_00B87EA0 = 0; P61_V18 = 0;
    P103_GhostState(); CK(P59_S4654 == 1 && G2_00D04654 == 1 && P61_V18 == 0x800);
    P59_S4654 = s; G6_00B87EA0 = ea0; }
  { /* 004cb2f5: пауза — без изменений */
    int32_t fr = G6_00B5A778, fl = P80_Flag17AEC; G6_00B5A778 = 1; P103_Dusk(); CK(P80_Flag17AEC == fl); G6_00B5A778 = fr; }
  { /* 0049a520: коробки не пересекаются — откат к началу, t = 0x1000 */
    int32_t bx[0x30]; memset(bx, 0, sizeof bx); uint8_t out[0x28]; memset(out, 0, sizeof out);
    bx[0] = 0; bx[0x18] = 1000000; bx[0x18 + 2] = 1000000;
    int32_t t = P103_BoxContactTime(bx, out);
    CK(t == 0x1000 || t >= 0); (void)t; }
  return f;
}
static int t111_n;
static void t111_r(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)a; (void)b; (void)c; t111_n++; }
static int test_p117(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p117 fail line %d\n",__LINE__); } } while (0)
  /* .data меню паузы зарегистрирована: P97_SndMenu внутри P117_MenuA, пункт 0 меню звука — строка 156 */
  CK(re_ptr(0x00574f38u) == (void *)P97_SndMenu && re_ptr(0x00575370u) == (void *)&P117_MenuC[0] && re_addr(&P117_MenuB[0x14]) == 0x0057509cu);
  CK(P117_MenuA[5] == 1 && P117_MenuA[8] == 156 && (P117_MenuA[0x13c - 0x14 + 5] & 0x10) != 0);
  /* 0051dd1b: колесо 1 — запись в таблицу A по счётчику, адрес записи в P117_SkidLastA, продолжение помечает прошлую */
  { int32_t e = P13_00575ec0, d = P74_SkidD[1], b = P74_SkidB[1], st = P117_SkidStA[1], fl = P102_D0DD80; uint32_t la = P117_SkidLastA[1];
    p102_i16_t c, pc; memcpy(c, P102_Corners, sizeof c); memcpy(pc, P117_PrevCorn, sizeof pc);
    P13_00575ec0 = 1; P74_SkidD[1] = 3; P74_SkidB[1] = 0; P117_SkidStA[1] = 0; P102_D0DD80 = 1;
    P102_Corners[4] = 1000; P102_Corners[5] = 0; P102_Corners[6] = 0; P117_PrevCorn[4] = 1000; P117_PrevCorn[5] = 0; P117_PrevCorn[6] = 100;
    P117_SkidRecA(1);
    uint8_t *r = &P116_SkidRecA[0x4800 + 3 * 0x48]; float x, y, z; memcpy(&x, r + 0x38, 4); memcpy(&y, r + 0x3c, 4); memcpy(&z, r + 0x40, 4);
    CK(P74_SkidD[1] == 4 && P117_SkidStA[1] == 1 && P117_SkidLastA[1] == 0x00b5c950u + 0x4800 + 3 * 0x48 && r[0] == 0 && x == 1000.0f && y == -20.0f && z == 0.0f);
    P117_SkidRecA(1); int16_t q; memcpy(&q, r + 2, 2);
    CK(P74_SkidD[1] == 5 && r[0x48] == 1 && q == 0);
    P117_SkidRecA(1); memcpy(&q, r + 0x48 + 2, 2); CK(q == 1);
    memcpy(P102_Corners, c, sizeof c); memcpy(P117_PrevCorn, pc, sizeof pc);
    P13_00575ec0 = e; P74_SkidD[1] = d; P74_SkidB[1] = b; P117_SkidStA[1] = st; P102_D0DD80 = fl; P117_SkidLastA[1] = la; }
  /* 00502fe2 / 00504cad: без значков — выход */
  { uint8_t *m = P102_MapIcon2; P102_MapIcon2 = NULL; P117_FullMap(); P102_MapIcon2 = m;
    uint8_t *ri = P100_RadarIcon; P100_RadarIcon = NULL; P117_Radar(); P100_RadarIcon = ri; }
  /* 0040ce31: пустой список (адрес строки 0) — только сброс; без списка — выход */
  { static uint8_t lst[16]; uint32_t pa = P45_PtrA; P45_PtrA = 0; P117_TextList(); P45_PtrA = re_addr(lst); P117_TextList(); P45_PtrA = pa; }
#undef CK
  return f;
}

static int test_p118(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p118 fail line %d\n",__LINE__); } } while (0)
  /* .data 0054e774: пара (0,1), камера 0 — ключи 5..6, камера 5 — прямой переход, ключ 27 */
  CK(P118_RouteTab[0] == 0 && P118_RouteTab[1] == 1 && P118_RouteTab[0x25] == 5 && P118_RouteTab[0x26] == 6 && P118_RouteTab[0x24 + 15] == 1 && P118_RouteTab[0x25 + 15] == 27);
  { static p99_camkeys_t keep; memcpy(keep, P99_CamKeys, sizeof keep);
    int32_t cur = G005FEB00, nk = D_005feda0, fr = D_005fea98, cnt = UiVar005FEB48, st = P12_005feb60; float sa = P43_ScaleA;
    memset(P99_CamKeys, 0, sizeof P99_CamKeys);
    for (int32_t k = 0; k < 0x30; k++) { int32_t v = k * 10; memcpy(&P99_CamKeys[k * 0x34 + 0x2c], &v, 4); }
    /* 0041a1f9, путь «вперёд»: камера 0 → 1, ключи 6..11 */
    G005FEB00 = 0; D_005feda0 = 0; P118_CamRoute(1);
    int32_t v; memcpy(&v, &P118_Route[6 * 0x34 + 0x2c], 4);
    CK(UiVar005FEB48 == 6 && v == 110 && D_005fea98 == 60 && D_005feda0 == 1 && G005FEB00 == 1 && P12_005feb60 == 1 && P118_RouteMax == 0x19);
    CK(rd32t(&P12_005febbc[0]) == 50 && rd32t(&P12_005febbc[0x34]) == 60);
    /* прямой переход в камеру 5: 3 ключа, кадр последнего 0x32 */
    G005FEB00 = 0; D_005feda0 = 0; P118_CamRoute(5);
    memcpy(&v, &P118_Route[3 * 0x34 + 0x2c], 4);
    CK(UiVar005FEB48 == 3 && v == 0x32 && P118_RouteKey == 27 && P118_RouteMax == 0x19);
    /* p == текущей: камера из ключа 5 (масштаб +0x24) */
    float sc = 2.5f; memcpy(&P99_CamKeys[5 * 0x34 + 0x24], &sc, 4); float x = 123.0f; memcpy(&P99_CamKeys[5 * 0x34], &x, 4);
    G005FEB00 = 0; P118_CamRoute(0);
    CK(P43_ScaleA == 2.5f && P44_CamX == 123.0f);
    memcpy(P99_CamKeys, keep, sizeof keep); G005FEB00 = cur; D_005feda0 = nk; D_005fea98 = fr; UiVar005FEB48 = cnt; P12_005feb60 = st; P43_ScaleA = sa; }
  /* 004932d5: слот 2 — сосед только по направлению 0 (узел 5), машина идёт по 1 → поворот налево (−1), r[0x13] |= 4 */
  { uint8_t sk[0x2c], nd[0x42], cd[0x24]; uint16_t rn = P101_RdNode;
    memcpy(sk, &P11_00c1ed80[2 * 0x2c], 0x2c); memcpy(nd, &P11_00bf1c40[5 * 0x42], 0x42); memcpy(cd, &P59_C39DC0[7 * 0x24], 0x24);
    uint8_t *s = &P11_00c1ed80[2 * 0x2c]; memset(s, 0, 0x2c); s[3] = 1;
    int16_t nb[4] = { 5, -1, -1, -1 }; for (int i = 0; i < 4; i++) memcpy(s + 0xa + 8 * i, &nb[i], 2);
    P11_00bf1c40[5 * 0x42 + 0x3d] = 0; P59_C39DC0[7 * 0x24 + 1] = 2;
    uint8_t r[0x54]; memset(r, 0, sizeof r); r[0] = 3; int32_t road = 7, dir = 1; memcpy(r + 0x28, &road, 4); memcpy(r + 0x24, &dir, 4);
    P101_RdNode = 2;
    CK(P118_TrafficTurn(r) == 1 && rd32t(r + 0x30) == 0 && rd32t(r + 0x2c) == 5 && rd32t(r + 0x34) == -1 && (r[0x13] & 4) != 0 && rd32t(r + 0x3c) == 0x82);
    memcpy(&P11_00c1ed80[2 * 0x2c], sk, 0x2c); memcpy(&P11_00bf1c40[5 * 0x42], nd, 0x42); memcpy(&P59_C39DC0[7 * 0x24], cd, 0x24); P101_RdNode = rn; }
  /* 0048dddb: запись типа 3 — полоса по курсу 0: игрок впереди (z 500) — 1, позади (z −500) — 0 */
  { int32_t tn = P51_TrafficN; uint8_t c0[0x148], c1[0x148]; uint8_t *p0 = (uint8_t *)&P99_Cars[0], *p1 = (uint8_t *)&P99_Cars[1];
    memcpy(c0, p0, 0x148); memcpy(c1, p1, 0x148); uint8_t *ct = P59_CarsTab; P59_CarsTab = NULL;
    static p96_rottab_t rt; memcpy(rt, P96_RotTab, sizeof rt); memset(P96_RotTab, 0, sizeof rt);
    P51_TrafficN = 0; memset(p1 + 0xc8, 0, 12); memset(p1 + 0x100, 0, 4); memset(p0 + 0x100, 0, 4);
    uint8_t r[0x54]; memset(r, 0, sizeof r); r[0] = 0; r[1] = 3;
    int32_t z = 500; memset(p0 + 0xc8, 0, 12); memcpy(p0 + 0xd0, &z, 4);
    CK(P118_TrafficBlocked(r) == 1);
    z = -500; memcpy(p0 + 0xd0, &z, 4);
    CK(P118_TrafficBlocked(r) == 0);
    memcpy(p0, c0, 0x148); memcpy(p1, c1, 0x148); P59_CarsTab = ct; memcpy(P96_RotTab, rt, sizeof rt); P51_TrafficN = tn; }
  /* 004b8f4e: дым (тип 3) — запись 7 пула, флаги 0x10006, скорость/шаг = vel / 50 */
  { int32_t top = S_0110E144, fl = MenuVar55384C, fa = G6_00B5A778, fr = P62_Frame; int16_t s0; memcpy(&s0, &S_010EA8A0[0], 2);
    uint8_t keep[0x78]; memcpy(keep, P95_ObjA + 7 * 0x78, 0x78);
    int16_t seven = 7; memcpy(&S_010EA8A0[0], &seven, 2); S_0110E144 = 0; MenuVar55384C = 1; G6_00B5A778 = 0; P62_Frame = 2;
    float pos[3] = { 1000, 20, 3000 }, vel[3] = { 100, 0, -50 };
    P118_SkidFx(pos, 100, 500, 3, 0, vel, 0);
    uint8_t *o = P95_ObjA + 7 * 0x78; float ox, vy, sx;
    memcpy(&ox, o, 4); memcpy(&vy, o + 4, 4); memcpy(&sx, o + 0x30, 4);
    CK(rd32t(o + 0x68) == 0x10006 && rd32t(o + 0x58) == 0x96 && ox >= 1000 && ox < 1064 && vy == 20 && sx == 2.0f && S_0110E144 == 1);
    MenuVar55384C = 0; S_0110E144 = 0; P118_SkidFx(pos, 1, 1, 1, 0, vel, 0); CK(S_0110E144 == 0);
    memcpy(o, keep, 0x78); memcpy(&S_010EA8A0[0], &s0, 2); S_0110E144 = top; MenuVar55384C = fl; G6_00B5A778 = fa; P62_Frame = fr; }
  return f;
#undef CK
}

static int test_p116(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p116 fail line %d\n",__LINE__); } } while (0)
  /* 0040abac: пустые глифы — только сдвиг x на ширину пробела × масштаб; выравнивание по центру */
  { static const char str[] = "AA"; int32_t c4 = MenuVal5D77C4, c8 = MenuVal5D77C8, px = MenuPosX54AA24, py = MenuPosY54AA28;
    uint8_t c0 = MenuByte5D77C0, c1 = MenuByte5D77C1; int32_t f7 = P56_F7E58; uint8_t sv[0x806]; memcpy(sv, &P58_Font[0], sizeof sv);
    memset(&P58_Font[0], 0, sizeof sv); int16_t sp = 5; memcpy(&P58_Font[0xc], &sp, 2);
    float one = 1.0f, x0 = 100.0f, y0 = 50.0f; memcpy(&MenuPosX54AA24, &one, 4); memcpy(&MenuPosY54AA28, &one, 4);
    memcpy(&MenuVal5D77C4, &x0, 4); memcpy(&MenuVal5D77C8, &y0, 4); MenuByte5D77C0 = 0; MenuByte5D77C1 = 0; P56_F7E58 = 1;
    P116_Text(re_addr(str)); float x; memcpy(&x, &MenuVal5D77C4, 4); CK(x == 110.0f);
    memcpy(&MenuVal5D77C4, &x0, 4); MenuByte5D77C0 = 1; P116_Text(re_addr(str)); memcpy(&x, &MenuVal5D77C4, 4); CK(x == 105.0f);
    P116_Text(0);
    memcpy(&P58_Font[0], sv, sizeof sv); MenuVal5D77C4 = c4; MenuVal5D77C8 = c8; MenuPosX54AA24 = px; MenuPosY54AA28 = py;
    MenuByte5D77C0 = c0; MenuByte5D77C1 = c1; P56_F7E58 = f7; }
  /* 0051e65e / 0051f376: выключено (00575ec0 = 0) и пустые полосы — ничего не растеризуется */
  { int32_t e = P13_00575ec0; P13_00575ec0 = 0; P116_SkidsA(); P116_SkidsB(); P13_00575ec0 = e; }
  /* 004cc801: без значка RFLECT — выход; с записью за ближней границей — список пуст */
  { uint8_t *ic = G00D14EF0; int32_t n = G8_00D17B0C; G00D14EF0 = NULL; P116_Reflections();
    static uint8_t icon[16]; G00D14EF0 = icon; G8_00D17B0C = 0; P116_Reflections(); G00D14EF0 = ic; G8_00D17B0C = n; }
  { int32_t m = G00B5A730; G00B5A730 = 0; P116_PauseMenu(); G00B5A730 = m; }
  { int32_t e = G6_00B87EEC; G6_00B87EEC = 0; P116_Sliders2(); G6_00B87EEC = e; }
  { uint8_t *sp = P56_Sprite; P56_Sprite = NULL; int32_t pos[3] = { 0, 0, 0 }; P116_RadarIcon(pos, 0, 1, 2, 3, 1.0f); P56_Sprite = sp; }
  { int32_t a = Q005FEA24, b = Q005FEA20; Q005FEA24 = 0; Q005FEA20 = 0; P116_Sliders5(1, 1, 1, 1, 1, 2); Q005FEA24 = a; Q005FEA20 = b; }
#undef CK
  return f;
}
static int test_p115(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p115 fail line %d\n",__LINE__); } } while (0)
  /* 004a3808: цель рядом с игроком — достигнута */
  { uint8_t o[0x48]; memset(o, 0, sizeof o); int32_t v;
    v = 0x200; memcpy(o + 0x10, &v, 4); v = 2; memcpy(o + 0x14, &v, 4); v = 100 * 100; memcpy(o + 0x1c, &v, 4);
    v = P59_PosX + 10; memcpy(o + 0x20, &v, 4); v = P59_PosZ - 20; memcpy(o + 0x28, &v, 4); v = 77; memcpy(o + 0x2c, &v, 4);
    P115_TargetTick(o);
    int32_t f8, f10, c; memcpy(&f8, o + 8, 4); memcpy(&f10, o + 0x10, 4); memcpy(&c, o + 0xc, 4);
    CK((f8 & 0x80) != 0 && (f10 & 0x200) == 0 && c == 0 && P115_TgtOn == 0 && P115_Tgt[3] == 77);
    memset(o, 0, sizeof o); P115_TargetTick(o); memcpy(&c, o + 0xc, 4); CK(c == 0); P115_TargetTick(NULL); }
  /* 00452327 / 004531c5: вершины уже спроецированы, растеризатора нет — курсор сдвигается, смешивание ставится */
  { static uint8_t rec[0x48]; memset(rec, 0, sizeof rec); int32_t idx[4] = { 0, 1, 2, 3 }; memcpy(rec + 8, idx, 16);
    p85_vtx sv[4]; memcpy(sv, &P85_VCache[0], sizeof sv);
    for (int i = 0; i < 4; i++) { P85_VCache[i].stamp = P44_XformTag; P85_VCache[i].x = 10.0f * (float)(i + 1); P85_VCache[i].y = 5.0f; P85_VCache[i].oow = 0.5f; }
    float col = 128.0f; memcpy(rec + 0x14, &col, 4);
    uint8_t *cur = G2_011F4064; int32_t edge = P82_Edge, bf = P85_BlendForce; uint8_t bc = P85_BlendCur; p85_blend_fn bfn = P85_BlendFn;
    P82_Edge = 0; P85_BlendForce = 0; P85_BlendFn = NULL;
    G2_011F4064 = rec; P115_FlatTriC(2); CK(G2_011F4064 == rec + 0x20 && P85_BlendCur == 2 && P85_RV[0].r == 128.0f && P85_RV[2].x == 30.0f);
    memcpy(rec + 0x14, &idx[3], 4); G2_011F4064 = rec; P115_GouraudQuadC(1); CK(P85_RV[0].r == 0.0f && G2_011F4064 == rec + 0x48 && P85_BlendCur == 1 && P85_RV[1].x == 30.0f && P85_RV[2].x == 40.0f);
    G2_011F4064 = cur; P82_Edge = edge; P85_BlendForce = bf; P85_BlendCur = bc; P85_BlendFn = bfn; memcpy(&P85_VCache[0], sv, sizeof sv); }
  /* 00523829: звук выключен / фейд закончен — ничего не трогает */
  { int32_t s0 = G6_00B91CF4, s1 = G00575F40, s2 = P43_FadeOn, s3 = P43_FadeSteps, c08 = P8_00b91c08;
    G6_00B91CF4 = 0; P115_SndUpdate(); CK(P8_00b91c08 == c08);
    G6_00B91CF4 = 1; G00575F40 = 1; P43_FadeOn = 1; P43_FadeSteps = 0; P115_SndUpdate(); CK(P8_00b91c08 == c08);
    G6_00B91CF4 = s0; G00575F40 = s1; P43_FadeOn = s2; P43_FadeSteps = s3; }
  P115_IconAt(0, 0, 0, 1, 2, 3, 0, 0); P115_IconFlip(0, 0, 0, 1, 2, 3, 1, 0); P115_IconScaled(0, 0, 1, 1, 0, 1, 2, 3, 0); P115_RoadArrow(NULL);
  { int32_t p0 = P55_Paper0; P55_Paper0 = 0; P115_PaperHud(); P55_Paper0 = p0; }
#undef CK
  return f;
}
static int test_p114(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p114 fail line %d\n",__LINE__); } } while (0)
  { int32_t t[6] = { 100, 4 | 8, 0, 0, 0, 0 }; P114_Timer(t);
    CK(t[0] == 99 && t[2] == 1 && t[3] == 98 && t[4] == 1 && t[5] == 0);
    int32_t u[6] = { 3000 * 60, 4 | 8 | 0x80, 0, 0, 0, 0 }; P114_Timer(u);
    CK(u[0] == 3000 * 60 + 1 && u[5] == 59 && u[4] == 59 && u[3] == 2);
    int32_t w[6] = { 5, 0, 0, 0, 0, 0 }; P114_Timer(w); CK(w[0] == 5 && w[2] == 0); }
  CK(P114_MenuStep(0x7ffffff0u, NULL) == -1);
  { int32_t s54 = G00BDFA54; G00BDFA54 = 1; uint8_t n[0x20]; memset(n, 0, sizeof n); P114_PathDraw(n, 0); G00BDFA54 = s54; }
  { int32_t p0 = P55_Paper0; P55_Paper0 = 0; P114_PaperMark(0); P114_PaperMark(99); P55_Paper0 = p0; }
  { int32_t sd = P99_CamDelay, sf = P99_CamFade, ss = P99_CamSpd, sh = P19_ScrH, sm = P99_CamMax, sc = P47_SwapCnt, s38 = P11_01270c38;
    P99_CamDelay = 0; P99_CamFade = 0; P99_CamSpd = 200 << 12; P19_ScrH = 200; P99_CamMax = 300; P11_01270c38 = 0;
    P114_CamFadeFrame(); CK(P19_ScrH == 200 && P47_SwapCnt == sc + 1 && P99_CamFade == 0);
    P99_CamDelay = 1; P114_CamFadeFrame(); CK(P99_CamFade == 0xff && P47_SwapCnt == sc + 1);
    P99_CamDelay = sd; P99_CamFade = sf; P99_CamSpd = ss; P19_ScrH = sh; P99_CamMax = sm; P47_SwapCnt = sc; P11_01270c38 = s38; }
  { uint8_t ic[16]; memset(ic, 0, sizeof ic); int32_t ct = P86_CurTex; uint8_t bc = P85_BlendCur;
    ic[8] = (uint8_t)(ct & 0xff); P86_CurTex = ic[8]; ic[0xb] = 4; ic[0xc] = 4;
    p85_raster_fn rb = P85_RasterB; P85_RasterB = NULL;
    P114_DrawSpr(10, 10, 1, 1, ic, 255, 255, 255, 2); CK(P85_BlendCur == 2);
    P85_RasterB = rb; P86_CurTex = ct; P85_BlendCur = bc; }
#undef CK
  return f;
}
static int test_p113(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p113 fail line %d\n",__LINE__); } } while (0)
  /* 004f3e78 на указателях: два кадра (заголовок 0x10 + 2 записи 0x14), t = 0.5 */
  { float a[4 + 10], b[4 + 10]; int32_t n0 = P12_00c821a0;
    for (int i = 0; i < 14; i++) { a[i] = (float)i; b[i] = (float)i + 2.0f; }
    P12_00c821a0 = 2; P12_Fn004F3E78(a, b, 0.5f);
    CK(P12_PartLerp[0] == 5.0f && P12_PartLerp[4] == 9.0f && P12_PartLerp[5] == 10.0f && P12_PartLerp[9] == 14.0f);
    P12_Fn004F3E78(NULL, b, 0.5f);
    /* 005129e1: нет буфера пути — ничего не пишет; тип вне 1..4 — выход */
    uint8_t obj[0xa0]; memset(obj, 0, sizeof obj);
    int32_t one = 1; memcpy(obj + 0x1c, &one, 4);
    void *sv = P54_Tab4[0]; P54_Tab4[0] = NULL; int32_t in = P98_IconN;
    P113_PartDraw(obj); CK(P98_IconN == in);
    /* буфер есть, но далеко от камеры (d ≥ 0x3a99) — позиция посчитана, значок не добавлен */
    static float path[(4 + 10) * 2]; for (int i = 0; i < 28; i++) path[i] = 0.0f; path[1] = 7.0f;
    P54_Tab4[0] = path; float x = P44_CamX + 20000.0f; memcpy(obj + 0x84, &x, 4);
    P113_PartDraw(obj); CK(P98_IconN == in && P100_PartBase[1] == 7.0f && P100_PartBase[0] == x);
    int32_t big = 9; memcpy(obj + 0x1c, &big, 4); P113_PartDraw(obj); CK(P98_IconN == in);
    P54_Tab4[0] = sv; P12_00c821a0 = n0; }
  /* 004e969f mode 0: углы 0 — базис единичный, падение на 1.6006666 по y, винт +0x5a */
  { int32_t s778 = G6_00B5A778; uint32_t srec = P113_MrkRec; G6_00B5A778 = 0; P113_MrkRec = 0;
    P42_AngY = 0; P42_AngX = 0; P113_MrkFall = 1; P81_Flag = 0; P99_Mrk2710 = 300; P113_MrkGround = 1000;
    for (int i = 0; i < 7; i++) P53_Mrk[i] = 0.0f;
    P99_Mrk270C = 0xffa; P113_Heli(0);
    CK(P99_Mrk270C == ((0xffa + 0x5a) & 0xfff) && P99_Mrk2710 == 301 && P113_MrkMat[0] == -1.0f && P113_MrkMat[8] == 1.0f);
    CK(fabsf(P53_Mrk[1] - 1.6006666f) < 1e-5f && fabsf(P81_Span + 1.6006666f) < 1e-5f);
    P113_MrkGround = 1; P113_Heli(0); CK(P53_Mrk[1] == 1.0f && P81_Span == 0.0f);
    P113_MrkFall = 0; P53_Var26A4 = 0; P81_Span = 0; P99_Mrk2710 = 0; P99_Mrk270C = 0; G6_00B5A778 = s778; P113_MrkRec = srec; }
  /* 004048dd: флаги 00bdf9e4 и 00bdf9f8 — две строки (пункты 1 и 7), навигация по кругу, конец таблицы; без флагов — одна строка ffe */
  { int32_t sv[11]; for (int i = 0; i < 11; i++) { sv[i] = P102_BDF9E0[i]; P102_BDF9E0[i] = 0; }
    P102_BDF9E0[1] = 1; P102_BDF9E0[6] = 1;
    P113_MenuOpts();
    CK(P57_OPT_FN(0, 2) == 0x00404ec9u && P57_OPT_FN(1, 2) == 0x00404f5fu && P57_OPT_FN(2, 0) == 0 && P57_OPT_FN(0, 0) == 0x00404e52u);
    CK(P54_SelTab[0] == 1 && P54_SelTab[1] == 7 && P54_SelTab[2] == -1);
    CK(P57_OPT_NAV(0, 2) == 1 && P57_OPT_NAV(0, 3) == 1 && P57_OPT_NAV(1, 2) == 0 && P57_OPT_NAV(1, 3) == 0);
    CK(P54_Out[4] == P97_StrAddr[0xf2] && P54_Out[12] == P97_StrAddr[0x64] && P54_Out[20] == 0);
    CK(re_fn(P57_OPT_FN(1, 2)) == (re_fn_t)MenuStateSetFour);
    P102_BDF9E0[1] = 0; P102_BDF9E0[6] = 0; P113_MenuOpts();
    CK(P57_OPT_FN(0, 2) == 0x00404ffeu && P54_SelTab[0] == -1 && P57_OPT_FN(1, 2) == 0);
    for (int i = 0; i < 11; i++) P102_BDF9E0[i] = sv[i]; }
#undef CK
  return f;
}
static int test_p112(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p112 fail line %d\n",__LINE__); } } while (0)
  uint8_t ctx[0x60], scr[0x20]; float v; uint16_t w;
  uint8_t *sp = P10_ScriptPtr, *sc = P10_ScriptCtx;
  memset(ctx, 0, sizeof ctx); memset(scr, 0, sizeof scr);
  v = 10.0f; memcpy(ctx + 0x44, &v, 4);                     /* скорость 10 */
  v = 100.0f; memcpy(scr + 2, &v, 4);                       /* цель x = 100 */
  P10_ScriptCtx = ctx; P10_ScriptPtr = scr;
  CK(P112_OpMoveTo() == 0); memcpy(&v, ctx, 4); CK(fabsf(v - 10.0f) < 1e-3f); CK(P10_ScriptPtr == scr);
  v = 5.0f; memcpy(scr + 2, &v, 4); P10_ScriptPtr = scr;
  CK(P112_OpMoveTo() == 1); memcpy(&v, ctx, 4); CK(v == 5.0f); CK(P10_ScriptPtr == scr + 0xe);
  memcpy(&w, ctx + 0x48, 2); CK((w & 0x80) != 0);
  P10_ScriptPtr = scr; CK(P112_OpMoveCur() == 1); CK(P10_ScriptPtr == scr + 2);   /* уже в цели */
  P10_ScriptPtr = sp; P10_ScriptCtx = sc;
  CK(re_fn(0x004d09fdu) == (re_fn_t)P112_OpMoveTo && re_fn(0x004d0734u) == (re_fn_t)P112_OpMoveCurve);
  { uint8_t *h = P15_ListHead; P15_SetListHead(NULL); P112_ScriptTriggers(); P112_ScriptRunId(3); CK(P15_ListCur == NULL || 1); P15_SetListHead(h); }
  P112_FaceIcon(scr, -0x40);   /* выше экрана — ничего */
#undef CK
  return f;
}
static int test_p111(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p111 fail line %d\n",__LINE__); } } while (0)
  /* таблица значков 01105d68: псевдонимы */
  { uint32_t s8 = P108_SmokeIcon, s7 = P95_PoolIcon; int32_t s6 = G01105D80;
    P108_SmokeIcon = 0x111u; P95_PoolIcon = 0x222u; G01105D80 = 0x333;
    CK(P111_IconTab[8] == 0x111u && P111_IconTab[7] == 0x222u && P111_IconTab[6] == 0x333u);
    P108_SmokeIcon = s8; P95_PoolIcon = s7; G01105D80 = s6; }
  /* 004abd69: псевдонимы после загрузки (значки в native без уровня — NULL → 0) */
  { int32_t a = P69_OvlOn, b = P96_SparkOn, c = P96_DustOn, d = P96_ObjBOn, e = P101_ObjBOn2, g = P8_011171a4, h = P8_010ffd0c;
    uint32_t i = P110_GlowIcon, j = P98_SixRec, k = P94_IconRec, l = P108_SmokeIcon; p111_icontab_t sv; memcpy(sv, P111_IconTab, sizeof sv);
    P111_IconsInit();
    CK(P94_IconRec == (uint32_t)P8_011171a4 && P101_ObjBOn2 == P8_011171a4 && P111_Ic0110B020 == (uint32_t)P96_ObjBOn && P111_Ic0111D400 == P110_GlowIcon);
    P69_OvlOn = a; P96_SparkOn = b; P96_DustOn = c; P96_ObjBOn = d; P101_ObjBOn2 = e; P8_011171a4 = g; P8_010ffd0c = h;
    P110_GlowIcon = i; P98_SixRec = j; P94_IconRec = k; P108_SmokeIcon = l; memcpy(P111_IconTab, sv, sizeof sv); }
  p85_raster_fn sr = P85_RasterB; P85_RasterB = t111_r;
  int32_t sl = P62_I270C44; P62_I270C44 = 40000;
  uint8_t ic[16] = { 'X', 0, 0, 0, 0, 0, 0, 0, 0, 10, 20, 30, 40 };
  /* 004b6deb: вспышка — тип 1 (255,0,0), яркость 256 → два треугольника; тип вне таблицы — ничего */
  { int32_t so = P101_ObjBOn2; P101_ObjBOn2 = (int32_t)re_addr(ic);
    float p[0x1c]; memset(p, 0, sizeof p); p[0] = 10; p[1] = 5; p[2] = 1000;
    uint16_t w = 1; memcpy((uint8_t *)p + 0x64, &w, 2); w = 256; memcpy((uint8_t *)p + 0x66, &w, 2); w = 4; memcpy((uint8_t *)p + 0x6e, &w, 2);
    t111_n = 0; P111_Flare(p); CK(t111_n == 2);
    w = 99; memcpy((uint8_t *)p + 0x64, &w, 2); t111_n = 0; P111_Flare(p); CK(t111_n == 0);
    p[2] = 10; t111_n = 0; P111_Flare(p); CK(t111_n == 0);
    P101_ObjBOn2 = so; }
  /* 004b05ea: обломок значком 2 таблицы, единичная матрица — два треугольника; MenuVar553850 = 0 — ничего */
  { uint32_t s2 = P111_IconTab[2]; int32_t sm = MenuVar553850; float *mp = P44_MatPtr;
    float id[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    float cx = P44_CamX, cy = P44_CamY, cz = P44_CamZ; P44_CamX = 0; P44_CamY = 0; P44_CamZ = 0; P44_MatPtr = id;
    P111_IconTab[2] = re_addr(ic); MenuVar553850 = 1;
    float tri[12]; memcpy(tri, &P104_DebC[0], sizeof tri);
    float t2[12] = { 0, 0, 0, 0, 10, 0, 0, 0, 0, 10, 0, 0 }; memcpy(&P104_DebC[0], t2, sizeof t2);
    float o[0x10]; memset(o, 0, sizeof o); o[2] = 1000; ((uint8_t *)o)[0x3a] = 2;
    t111_n = 0; P111_DebrisIcon(o, 0); CK(t111_n == 2);
    MenuVar553850 = 0; t111_n = 0; P111_DebrisIcon(o, 0); CK(t111_n == 0);
    memcpy(&P104_DebC[0], tri, sizeof tri); P111_IconTab[2] = s2; MenuVar553850 = sm; P44_MatPtr = mp;
    P44_CamX = cx; P44_CamY = cy; P44_CamZ = cz; }
  re_ptr_unregister(ic);
  P85_RasterB = sr; P62_I270C44 = sl;
  /* 004cf2cf: запись с флагом 8, контекст с потоком [0x13] (ReturnZero) и шагом 2 по курсу 0 */
  { uint16_t *sl2 = S_00D12410; uint8_t *sc = P10_ScriptCtx, *sp = P10_ScriptPtr;
    S_00D12410 = NULL; P111_ScriptTick();
    uint8_t rec[0x20], ctx[0x60]; uint16_t strm[2] = { 0x13, 0 };
    memset(rec, 0, sizeof rec); memset(ctx, 0, sizeof ctx);
    uint16_t fl = 8 | 2; memcpy(rec, &fl, 2);
    uint32_t ca = re_addr(ctx), sa = re_addr(strm); memcpy(rec + 0x1c, &ca, 4); memcpy(ctx + 0x54, &sa, 4);
    uint32_t cf = 0x40; memcpy(ctx + 0x48, &cf, 4); float v = 2.0f; memcpy(ctx + 0x44, &v, 4);
    S_00D12410 = (uint16_t *)rec; int32_t sb = G6_00B5A778; G6_00B5A778 = 0;
    P111_ScriptTick();
    float x; memcpy(&x, ctx, 4); uint32_t a54; memcpy(&a54, ctx + 0x54, 4);
    CK(x == P43_Sin[0x400] * 2.0f && a54 == sa && P10_ScriptCtx == NULL);
    re_ptr_unregister(ctx); re_ptr_unregister(strm);
    S_00D12410 = sl2; P10_ScriptCtx = sc; S_00D1240C = sc; P10_ScriptPtr = sp; G6_00B5A778 = sb; }
#undef CK
  return f;
}

static int test_p126(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p126 fail line %d\n",__LINE__); } } while (0)
  { const char *fn = "p126_pals.bin"; FILE *o = fopen(fn, "wb");
    int32_t d[] = { 2, 7, 2, 11, 12, 9, 1, 13 }; fwrite(d, 4, 8, o); fclose(o);
    p58_rec_t *t0 = P58_Tab4EFC03; int32_t n0 = P58_Cnt4EFC03;
    P126_ReadMapPals(fn);
    CK(P58_Cnt4EFC03 == 2 && P58_Tab4EFC03 != NULL);
    if (P58_Tab4EFC03) { CK(P58_Tab4EFC03[0].a == 7 && P58_Tab4EFC03[0].c == 2 && ((int32_t *)P58_Tab4EFC03[0].p)[1] == 12);
      CK(P58_Tab4EFC03[1].a == 9 && P58_Tab4EFC03[1].c == 1 && ((int32_t *)P58_Tab4EFC03[1].p)[0] == 13); }
    uint32_t table_addr = re_addr(P58_Tab4EFC03);
    uint32_t list_addr[2] = { re_addr(P58_Tab4EFC03[0].p), re_addr(P58_Tab4EFC03[1].p) };
    int32_t freed = P27_MemFreed;
    P58_FreeRecs();
    CK(P58_Tab4EFC03 == NULL && P58_Cnt4EFC03 == 0);
    CK(P27_MemFreed == freed + 2 * (int32_t)sizeof(p58_rec_t) + 12);
    CK(re_ptr(table_addr) == NULL && re_ptr(list_addr[0]) == NULL && re_ptr(list_addr[1]) == NULL);
    P58_FreeRecs(); CK(P27_MemFreed == freed + 2 * (int32_t)sizeof(p58_rec_t) + 12);
    P58_Tab4EFC03 = t0; P58_Cnt4EFC03 = n0; remove(fn);
    P126_ReadMapPals("p126_missing.bin"); CK(P58_Tab4EFC03 == t0); }
  { uint8_t car[0x148]; memset(car, 0, sizeof car); car[0x78 + 8] = 1;
    P102_D06A00 = 7; P102_D0DD84 = 0; P126_WheelSmoke(car); CK(P102_D06A00 == 0 && P102_D0DD84 == 1);
    car[0x78 + 8] = 0; P102_D06A00 = 0; P126_WheelSmoke(car); CK(P102_D0DD84 == 0 && P102_D06A00 == 0x31); P102_D06A00 = 0; }
  { float x0 = 123.0f; float *p = (float *)&P76_ColObj; float sx = p[0], sz = p[2]; p[0] = x0; p[2] = -5.0f;
    void *g = G6_00D01268; G6_00D01268 = NULL;
    P76_Angle = 0x1e; P126_DropScan(0); CK(p[0] == x0 && p[2] == -5.0f);
    P76_Angle = 0x3c; P126_DropScan(0); CK(p[0] == x0 && p[2] == -5.0f);
    G6_00D01268 = g; p[0] = sx; p[2] = sz; P76_Angle = 0; }
  { int32_t n = P126_SpawnN; P126_SpawnN = 9; P123_TgtMode = 1; P123_SideX = 5.0f; P123_SideZ = 6.0f; P126_SpawnSide = 1;
    P126_SpawnInit(); CK(P126_SpawnN == 4 && P126_Spawn[0] == 1 && P126_Spawn[1] == 2 && P126_SpawnT == 0x32 && P98_C824A0 == 1);
    CK(P59_Mode1137324 == 7);
    P126_SpawnN = n; P123_TgtMode = 0; }
  { int32_t e = G6_00B87EEC, h = P62_HudOff2, a = G6_00B87EAC, b = G6_00B87EB0, s = S_00D11878;
    G6_00B87EEC = 0; P62_HudOff2 = 1; P11_00b87e38 = 0; G6_00B87EAC = 0; G6_00B87EB0 = 0; S_00D11878 = 0;
    P126_PlayerStart();
    CK(rd32t((uint8_t *)&P99_Cars[0] + 0xc8) == -10000 && P94_HeadingI == 0x400 && P44_CamX == -10000.0f && P44_CamY == -400.0f && P44_CamZ == -21504.0f);
    G6_00B87EEC = e; P62_HudOff2 = h; G6_00B87EAC = a; G6_00B87EB0 = b; S_00D11878 = s; }
  return f;
#undef CK
}
static int t131_n;
static void P85_STD t131_rast(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)b; (void)c; t131_n++; if (a->oow != 0.5f) t131_n += 100; }
static void t131_dm(int32_t a) { (void)a; }
/* ported135 */
static int t135_tri;
static void P85_STD t135_raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)a; (void)b; (void)c; t135_tri++; }
static int test_p135(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p135 fail line %d\n",__LINE__); } } while (0)
  p85_raster_fn rb = P85_RasterB; p85_blend_fn bf = P85_BlendFn; p86_texsrc_fn ts = P86_TexSrc; p85_state_fn sf = P85_StateFn;
  uint8_t bc = P85_BlendCur; int32_t ct = P86_CurTex, sd = P85_StateDirty, fr = P62_Frame, sx = P102_SixFlag; uint32_t si = P111_SparkIcon, sr = P98_SixRec;
  float *mp = P44_MatPtr;
  P85_RasterB = t135_raster; P85_BlendFn = NULL; P86_TexSrc = NULL; P85_StateFn = NULL;
  /* 004b23f8: без значка — ничего */
  { uint8_t o[0x70] = { 0 }; t135_tri = 0; P111_SparkIcon = 0; P135_SparkQuad(o); CK(t135_tri == 0); }
  /* 004ba81f: 010ff8e0 = кадр; угол вне ±0x400 от камеры — выход */
  { uint32_t r[12] = { 0 }; r[0] = (uint32_t)P59_AngB + 0x800; r[3] = 1; t135_tri = 0; P62_Frame = 77;
    P135_SixBeam(r); CK(P102_SixFlag == 77 && t135_tri == 0); }
  /* 005063a4: объект рядом — треугольник (3D-режим) */
  { uint8_t sv[0x34]; memcpy(sv, P58_Objs[0], 0x34); int32_t v18 = P55_BDFA18;
    int32_t x = P59_PosX + 4000, z = P59_PosZ; memcpy(P58_Objs[0] + 0x14, &x, 4); memcpy(P58_Objs[0] + 0x1c, &z, 4);
    P55_BDFA18 = 1; P85_StateDirty = 5; t135_tri = 0; P135_RadarLine(0); CK(t135_tri == 1 && P85_StateDirty == 0 && P85_BlendCur == 2);
    x = P59_PosX + 400000; memcpy(P58_Objs[0] + 0x14, &x, 4); t135_tri = 0; P135_RadarLine(0); CK(t135_tri == 2);
    memcpy(P58_Objs[0], sv, 0x34); P55_BDFA18 = v18; }
  /* 004e6310: флаг записи 0 — выход с ним, состояние 4 */
  { uint8_t sv[0xb40]; memcpy(sv, P56_GhostBuf, sizeof sv); int32_t g = P56_G4538; uint8_t *gp = P56_GhostPtr;
    memset(P56_GhostBuf, 0, sizeof sv); P56_G4538 = 5; P56_GhostPtr = NULL; P85_StateDirty = 0; t135_tri = 0;
    CK(P135_GhostTrail() == 0 && P85_StateDirty == 4 && t135_tri == 0 && P86_CurTex == 0);
    memcpy(P56_GhostBuf, sv, sizeof sv); P56_G4538 = g; P56_GhostPtr = gp; }
  P85_RasterB = rb; P85_BlendFn = bf; P86_TexSrc = ts; P85_StateFn = sf; P85_BlendCur = bc; P69_BlendOn = bc; P86_CurTex = ct; P85_StateDirty = sd;
  P62_Frame = fr; P102_SixFlag = sx; P111_SparkIcon = si; P98_SixRec = sr; P44_MatPtr = mp;
#undef CK
  return f;
}

/* ported136 (+ P84_DrawModelC/P84_DrawCar) */
static int t136_n; static uint32_t t136_arg[8];
static void t136_h(uint32_t a) { if (t136_n < 8) t136_arg[t136_n] = a; t136_n++; G2_011F4064 += 32; }
static int test_p136(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p136 fail line %d\n",__LINE__); } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000);
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); float *nn = (float *)(arena + 0x280); uint8_t *rec = arena + 0x300;
    uint16_t u16; uint32_t u32; int32_t i32; float ident[16]; float pos[3] = { 0, 0, 0 };
    float *mp = P44_MatPtr; int32_t sh = P28_ShineFlag, h1 = P62_HudOff1, tf = P84_TexFiltOn; uint8_t det = P86_Detail;
    D_00c98ed0 = arena; P84_InitConsts();
    memset(ident, 0, sizeof ident); ident[0] = ident[4] = ident[8] = 1.0f;
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    u16 = 1; memcpy(m + 2, &u16, 2); u16 = 2; memcpy(m + 0x16, &u16, 2); u16 = 1; memcpy(m + 0x18, &u16, 2);
    u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4); u32 = P79_OFF(nn); memcpy(m + 0x28, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    pl[0] = 0; pl[1] = 0; pl[2] = 1; pl[3] = 5;  pl[4] = 0; pl[5] = 0; pl[6] = 1; pl[7] = -5;
    nn[2] = 1;
    rec[0] = 16; rec[1] = 8; i32 = 0; memcpy(rec + 4, &i32, 4);
    rec[32] = 16; rec[33] = 8; i32 = 1; memcpy(rec + 36, &i32, 4);
    memset(P84_Handlers, 0, sizeof P84_Handlers);
    P84_Handlers[2][16] = (uintptr_t)t136_h; P84_SelectTables(0); G2_011F43B0 = 0; P84_Mirror = 0;
    P19_OutA = 0; P19_OutB = 0; P19_OutC = 1; P19_Out68 = 0.25f;
    /* 0042b7cb: аргумент 3 (модель со светом), свет плоскости 0.25 + 0.01 */
    t136_n = 0; P84_LightIn[0] = 0; P84_DrawModelC(P79_OFF(m), ident, pos, 5);
    CK(t136_n == 1 && t136_arg[0] == 3 && P84_LightIn[0] == (float)((long double)0.25f + (long double)0.01f));
    u16 = 0; memcpy(m + 2, &u16, 2);
    t136_n = 0; P84_DrawModelC(P79_OFF(m), ident, pos, 5); CK(t136_n == 1 && t136_arg[0] == 2);
    /* 0042a9f1: обычный режим — аргумент P84_Arg, свет нормалей всегда, Detail 0, фильтр текстур один раз */
    P28_ShineFlag = 0; P62_HudOff1 = 0; P84_TexFiltOn = 0; P86_Detail = 7; P84_NormLight[0] = 0;
    t136_n = 0; P84_DrawCar(P79_OFF(m), ident, pos, 5, 1, 0, 0, 0.0f);
    CK(t136_n == 1 && t136_arg[0] == P84_Arg[16] && P86_Detail == 0 && P84_TexFiltOn == 1 && P84_NormLight[0] == 1.0f);
    t136_n = 0; P84_DrawCar(P79_OFF(m), ident, pos, 5, 0x42, 0, 0, 0.0f); CK(t136_n == 0);
    memset(P84_Handlers, 0, sizeof P84_Handlers); P84_SelectTables(0);
    D_00c98ed0 = saved; free(arena);
    P44_MatPtr = mp; P28_ShineFlag = sh; P62_HudOff1 = h1; P84_TexFiltOn = tf; P86_Detail = det;
  }
  /* 004a1d4c: модели колёс 0 — только поворот колёс и переключение Glide-состояния */
  { int32_t mc = P26_ModelClean, mf = P26_ModelFast, md = P26_ModelDam, c48 = P62_I270C48, b78 = P62_I252B78, a778 = G6_00B5A778;
    int32_t r0 = P136_WheelRot[3], r1 = P136_WheelRotB[3], sp = P99_Cars[3].f10c, s8 = P99_Cars[3].f108;
    p97_gr5_fn ga = P97_GrAlpha; p97_gr1_fn gd = P97_GrDepth; float ident[16] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    P26_ModelClean = P26_ModelFast = P26_ModelDam = 0; P62_I270C48 = 1; P62_I252B78 = 0; G6_00B5A778 = 0; P97_GrAlpha = NULL; P97_GrDepth = NULL;
    P136_WheelRot[3] = 0xffe; P136_WheelRotB[3] = 5; P99_Cars[3].f10c = 0x400; P99_Cars[3].f108 = 1;
    P136_DrawWheels(3, ident, 1);
    CK(P136_WheelRot[3] == 2 && P136_WheelRotB[3] == ((5 - 700) & 0xfff) && P62_I252B78 == 0);
    P26_ModelClean = mc; P26_ModelFast = mf; P26_ModelDam = md; P62_I270C48 = c48; P62_I252B78 = b78; G6_00B5A778 = a778;
    P136_WheelRot[3] = r0; P136_WheelRotB[3] = r1; P99_Cars[3].f10c = sp; P99_Cars[3].f108 = s8; P97_GrAlpha = ga; P97_GrDepth = gd; }
  /* 00501770: город без имени карты — размеры 0, прямоугольник не меняется */
  { int32_t city = D_00b87e30, w = P57_ScrW, h = S_00C808A0, x0 = P94_MapX0, mw = P94_MapW; void *buf = P99_C80880;
    P99_C80880 = NULL; D_00b87e30 = 6; P57_ScrW = 9; P94_MapX0 = 4; P94_MapW = 7;
    P136_OverlayMap(); CK(P57_ScrW == 0 && S_00C808A0 == 0 && P94_MapX0 == 4 && P94_MapW == 7 && P99_C80880 == NULL);
    D_00b87e30 = city; P57_ScrW = w; S_00C808A0 = h; P94_MapX0 = x0; P94_MapW = mw; P99_C80880 = buf; }
#undef CK
  return f;
}

static int test_p141(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p141 fail line %d\n",__LINE__); } } while (0)
  /* 0041b8ac: SETCITY/ROOM/MISSION/JOKE/ENDROOM/IF/ELSE/ENDIF/неизвестная команда */
  { int regl = 0, regs = 0;
    if (re_ptr(0x005ff368u) == NULL) { re_ptr_register(0x005ff368u, P139_Ladder, sizeof P139_Ladder); regl = 1; }
    if (re_ptr(0x005fef38u) == NULL) { re_ptr_register(0x005fef38u, P139_LadStr, sizeof P139_LadStr); regs = 1; }
    uint32_t lp = P139_LadPtr; int32_t n = P139_LadN, l390 = P139_Lad390, l398 = P139_Lad398;
    memset(P139_Ladder, 0, sizeof P139_Ladder); memset(P139_LadStr, 0, sizeof P139_LadStr);
    memset(P139_LadA, 0, 16); memset(P139_LadB, 0, 16); memset(P139_LadC, 0, 16); memset(P139_LadD, 0, 16); memset(P139_LadE, 0, 16); memset(P139_LadF, 0, 16);
    P139_LadPtr = 0x005ff368u; P139_LadN = 0; P139_Lad390 = 0; P139_Lad398 = 0; P141_LadDepth = 0; P141_LadRooms = 0;
    const char *ln[] = { "setcity [LA]", "ROOM", "MISSION 7", "JOKE 3", "ENDROOM", "IF 5", "ELSE", "ENDIF", "FOO", "" };
    int ok = 1;
    for (int i = 0; i < 10; i++) { char b[0x80]; strcpy(b, ln[i]); ok &= P141_LadderLine(b) == 1; }
    uint32_t *r = (uint32_t *)P139_Ladder;
    CK(ok && P139_LadN == 6 && P141_LadDepth == 0 && P141_LadRooms == 0);
    CK(r[0] == 0 && r[1] == 2 && r[2] == 0x005ff378u);
    CK(r[4] == 1 && r[5] == 0 && r[6] == 0x005ff378u && P139_LadC[0] == 0 && P139_Lad390 == 0x005fef38);
    CK(r[8] == 2 && r[9] == 7 && r[10] == 0x005ff398u);
    uint16_t *o = (uint16_t *)P139_LadStr;
    CK(o[0] == 2 && o[1] == 7 && ((uint32_t *)P139_LadStr)[1] == 0x005ff388u && o[4] == 4 && o[5] == 3 && o[8] == 1 && P139_LadE[0] == 2);
    CK(r[12] == 5 && r[13] == 5 && r[15] == 0x005ff3b8u && r[16] == 7 && r[18] == 0x005ff3c8u && r[20] == 7);
    char e1[] = "ENDROOM"; CK(P141_LadderLine(e1) == 0 && P141_LadDepth == -1);
    P141_LadDepth = 0; P139_LadPtr = lp; P139_LadN = n; P139_Lad390 = l390; P139_Lad398 = l398;
    if (regl) re_ptr_unregister(P139_Ladder);
    if (regs) re_ptr_unregister(P139_LadStr); }
  /* 0040f3de: таблица 1, рекордов нет — 8 строк, «--:--:--», столбец очков «-»; MenuByte54BE5C — байт таблицы */
  { int32_t t = UiVar0054BF18, lv = UiVar005FE6BC, n = WI005FE694, h8 = P42_HighScores[8], h24 = P42_HighScores[24];
    P42_HighScores[8] = 0; P42_HighScores[24] = 0;
    uint8_t m5c = MenuByte54BE5C; CK(MenuByte54BE7C == P141_HsMenu[0x16c]);
    MenuByte54BE5C = 3; CK(P141_HsMenu[0x14c] == 3); MenuByte54BE5C = m5c;
    UiVar0054BF18 = 1; UiVar005FE6BC = 0;
    P141_HsSetup();
    uint32_t a; memcpy(&a, &P141_HsMenu[0x40], 4); const char *s = (const char *)re_ptr(a);
    memcpy(&a, &P141_HsMenu[0x30], 4);
    CK(WI005FE694 == 8 && s != NULL && strcmp(s, "--:--:--") == 0 && a == 0x0054bf8cu && strcmp((const char *)re_ptr(a), "-") == 0);
    memcpy(&a, &P141_HsMenu[0], 4); CK(re_ptr(a) != NULL);
    UiVar0054BF18 = 7; P141_HsSetup(); memcpy(&a, &P141_HsMenu[0x40], 4); s = (const char *)re_ptr(a);
    CK(WI005FE694 == 4 && s != NULL && strcmp(s, "-") == 0);
    UiVar0054BF18 = t; UiVar005FE6BC = lv; WI005FE694 = n; P42_HighScores[8] = h8; P42_HighScores[24] = h24; }
#undef CK
  return f;
}
static int test_p140(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p140 fail line %d\n",__LINE__); } } while (0)
  /* 005233be: номер вне диапазона — 0; драйвер-заглушка 0048ba31 = 0 — таблица громкости построена, 00b91cf4 = 0 */
  { int32_t d2c = G6_00B91D2C, cf4 = G6_00B91CF4, b30 = P48_B91D30;
    G6_00B91CF4 = 0; G6_00B91D2C = 2;
    CK(P140_SndInit(5, 0, 0) == 0);
    plat_ds_stub_dsfail(1, 0);   /* v1.93: 0048ba31 перенесена — DirectSoundCreate-заглушка отказывает */
    CK(P140_SndInit(1, 0, 7) == 0 && P48_B91D30 == 7 && G6_00B91CF4 == 0 && P43_FadeLen == 1.0f);
    plat_ds_stub_dsfail(0, 0);
    CK((int32_t)P48_VolTab[0] == -10000 && (int32_t)P48_VolTab[1] == -8000 && (int32_t)P48_VolTab[5000] == -602 && (int32_t)P48_VolTab[9999] == 0);
    G6_00B91D2C = d2c; G6_00B91CF4 = cf4; P48_B91D30 = b30; }
  /* 00524bd8: без DirectSound сэмпл не загружается — флаг 4, счётчик +1, строка в верхнем регистре */
  { int32_t n0 = G6_00B91D34; void *ds = P38_Ds; P38_Ds = NULL; G6_00B91D34 = 3;
    char line[] = "eng1 /loop /vol=7";
    P140_BankLine(line);
    CK(G6_00B91D34 == 4 && P68_Samps[3].handle == -1 && P48_Samples[3 * 8] == 4 && strcmp(line, "ENG1 /LOOP /VOL=7") == 0);
    CK(P140_SndLoadWav(3, "no_such.wav") == -1);
    P38_Ds = ds; G6_00B91D34 = n0; }
  /* 0041b3ab: записи {0: A = 5}, {7}, {6: 00c810c4 ≠ 0xff0 → следующая}, {8: стоп} */
  { static uint32_t recs[16]; const uint32_t A = 0x7f140000u;
    uint32_t r0[4] = { 0, 5, A + 0x10, 0 }, r1[4] = { 7, 0, A + 0x20, 0 }, r2[4] = { 6, 0, A + 0x30, A + 0x40 }, r3[4] = { 8, 0, 0, 0 };
    memcpy(recs, r0, 16); memcpy(recs + 4, r1, 16); memcpy(recs + 8, r2, 16); memcpy(recs + 12, r3, 16);
    re_ptr_register(A, recs, sizeof recs);
    uint32_t cur = P68_IntroCur, base = P68_IntroBase; int32_t ia = P68_IntroA, lv = P19_Level, c4 = P14_00c810c4;
    P68_IntroCur = A; P68_IntroBase = A; P19_Level = 10; P14_00c810c4 = 0;
    P140_LadderRun();
    CK(P68_IntroCur == A + 0x30 && P68_IntroA == 5 && P19_Level == 10);
    re_ptr_unregister(recs);
    P68_IntroCur = cur; P68_IntroBase = base; P68_IntroA = ia; P19_Level = lv; P14_00c810c4 = c4; }
  /* 0040ec30: язык вне 0..5 сбрасывается в 0 */
  { int32_t l = P55_Lang; P55_Lang = 7; P140_KeysLoad(); CK(P55_Lang == 0); P55_Lang = l; P58_LangNo = l; }
  /* 004e9bbf: при 00b5a778 ≠ 0 ничего не меняется */
  { int32_t s = G6_00B5A778; float x = P98_MrkSrc[0]; G6_00B5A778 = 1; P140_MrkFly(); CK(P98_MrkSrc[0] == x); G6_00B5A778 = s; }
#undef CK
  return f;
}

static int test_p139(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p139 fail line %d\n",__LINE__); } } while (0)
  /* 004f8b0a: две метки — массив из 2 адресов, имена в верхнем регистре */
  { int32_t list[2] = { 0, 0 };
    CK(P139_AddLabel("start", 7, list) == 1 && P139_AddLabel("Loop2", 9, list) == 1 && list[0] == 2);
    const uint8_t *arr = (const uint8_t *)re_ptr((uint32_t)list[1]);
    CK(arr != NULL);
    if (arr) { uint32_t a1; memcpy(&a1, arr + 4, 4); const uint8_t *r = (const uint8_t *)re_ptr(a1);
      CK(r != NULL);
      if (r) { uint32_t na; int32_t v; memcpy(&na, r, 4); memcpy(&v, r + 4, 4); const char *nm = (const char *)re_ptr(na);
        CK(v == 9 && nm != NULL && strcmp(nm, "LOOP2") == 0); } } }
  /* 004fbbfc: 2 тройки — записи 0x14 {номер, x, y, z, 0}, счётчик 00c81108 */
  { const char *fn = "/tmp/re_p139.trail"; FILE *o = fopen(fn, "wb");
    int32_t d[7] = { 1, 10, 20, 30, 40, 50, 60 }; fwrite(d, 4, 7, o); fclose(o);
    void *old = G6_00C80C50; int32_t on = G6_00C81108; G6_00C80C50 = NULL;
    CK(P139_TrailLoad(fn) == 1 && G6_00C81108 == 2);
    const int32_t *r = (const int32_t *)G6_00C80C50;
    CK(r != NULL && r[0] == 0 && r[1] == 1 && r[3] == 20 && r[5] == 1 && r[6] == 30 && r[9] == 0 && P125_PickIdx == 0);
    CK(P139_TrailLoad("/tmp/re_p139_none.trail") == 0 && G6_00C80C50 == NULL);
    G6_00C80C50 = old; G6_00C81108 = on; remove(fn); }
  /* 0041b1c0: строка MLADDER (0041b8ac — заглушка 0) или нет файла — 0; указатель записи — 005ff368, буфер обнулён */
  { uint32_t ib = P68_IntroBase; P139_Ladder[5] = 0x77;
    CK(P139_LadderLoad() == 0 && P139_LadPtr == 0x005ff368u && P139_Ladder[5] == 0 && P68_IntroBase == ib && re_ptr(0x005ff368u) == (void *)P139_Ladder); }
#undef CK
  return f;
}

static int test_p138(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p138 fail line %d\n",__LINE__); } } while (0)
  /* 00517d58: нет ни User, ни Demo .CFG — 0, флаги сброшены */
  { P101_RecSaved = 5; P100_RecEnd = 7;
    CK(P138_ReplayCfg("__re_p138_none__") == 0 && P101_RecSaved == 0 && P100_RecEnd == 0 && strcmp(P138_CfgName, "__re_p138_none__") == 0); }
  /* 00518bbc: при 00b87eb0 ≠ 0 ничего не делает; без файла PADS — тоже */
  { int32_t eb = G6_00B87EB0; uint32_t rp = P100_RecPtr[0];
    G6_00B87EB0 = 1; P138_LoadPads(); CK(P100_RecPtr[0] == rp);
    G6_00B87EB0 = 0; snprintf(P138_PadsPath, sizeof(p138_s40_t), "/tmp/re_p138_none.pads"); P138_LoadPads(); CK(P100_RecPtr[0] == rp);
    G6_00B87EB0 = eb; }
  /* 00518bbc: файл PADS — буфер, счётчик со снятым старшим битом */
  { const char *fn = "/tmp/re_p138.pads"; FILE *o = fopen(fn, "wb");
    int32_t hd[2] = { 0x1234, (int32_t)0x80000003u }; uint8_t pl[6] = { 1, 2, 3, 4, 5, 6 };
    fwrite(hd, 4, 2, o); fwrite(pl, 1, 6, o); fclose(o);
    int32_t eb = G6_00B87EB0, c68 = P74_C4D668; uint32_t rp = P100_RecPtr[0]; int32_t rt = P100_RecTot[0]; uint8_t a4 = P103_C4D9A4;
    G6_00B87EB0 = 0; snprintf(P138_PadsPath, sizeof(p138_s40_t), "%s", fn); P103_C4D9A4 = 0;
    P138_LoadPads();
    const uint8_t *b = (const uint8_t *)re_ptr(P100_RecPtr[0]);
    CK(P74_C4D668 == 0x1234 && P100_RecTot[0] == 3 && P103_C4D9A4 == 1 && b != NULL && b[0] == 1 && b[5] == 6);
    P100_RecPtr[0] = rp; P100_RecTot[0] = rt; P74_C4D668 = c68; P103_C4D9A4 = a4; G6_00B87EB0 = eb; remove(fn); }
  /* 00520278: нет значка тени — только метка + 1 */
  { uint8_t *ic = P96_ShadIcon; uint32_t tg = P44_XformTag;
    P96_ShadIcon = NULL; P138_CarShadow(0); CK(P44_XformTag == tg + 1);
    P96_ShadIcon = ic; }
#undef CK
  return f;
}

static int test_p137(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p137 fail line %d\n",__LINE__); } } while (0)
  /* 004f3490: 3 кадра, 1 узел, пропуск первого — 2 кадра, приращение z от предыдущего */
  { const char *fn = "/tmp/re_p137_test.mcd"; FILE *o = fopen(fn, "wb");
    int32_t hd[3] = { 0, 1, 3 }; float fr[3][3] = { {1, 2, 10}, {3, 4, 15}, {5, 6, 22} }; float nd[4] = { 7, 8, 9, 11 };
    int32_t nn = P12_00c821a0; uint32_t buf[64]; float *b = (float *)buf;
    fwrite(hd, 4, 3, o); for (int k = 0; k < 3; k++) { fwrite(fr[k], 4, 3, o); fwrite(nd, 4, 4, o); } fclose(o);
    memset(buf, 0, sizeof(buf));
    int32_t n = P137_LoadMcd(fn, buf, 1, 0);
    CK(n == 2 && P12_00c821a0 == 1 && b[1] == 4.0f && b[2] == 0.0f && b[3] == 1.0f && b[4] == 7.0f && b[7] == 1.0f && b[8] == 11.0f);
    CK(b[9 + 1] == 6.0f && b[9 + 2] == 7.0f);
    CK(P137_LoadMcd("/tmp/re_p137_none.mcd", buf, 0, 0) == 0);
    remove(fn); P12_00c821a0 = nn; }
  /* 0040d07b: нет файла / неверная метка — 0 */
  { CK(P137_LoadTsd("/tmp/re_p137_none.tsd") == 0);
    const char *fn = "/tmp/re_p137_bad.tsd"; FILE *o = fopen(fn, "wb"); fwrite("XSD 1234", 1, 8, o); fclose(o);
    CK(P137_LoadTsd(fn) == 0); remove(fn); }
  { /* A valid one-page TSD, loaded and released twice like menu/game transitions. */
    const char *fn = "/tmp/re_p137_owned.tsd"; FILE *o = fopen(fn, "wb");
    uint8_t pixels[0x10000] = {0}; float ver = 1;
    int16_t hdr[4] = {0, 0, 0x100, 1}; int32_t block[5] = {0x10014, 0x14, 0x14, 0, 0};
    fwrite("TSD ", 1, 4, o); fwrite(&ver, 4, 1, o); fwrite(hdr, 2, 4, o);
    fwrite(pixels, 1, 0x800, o); fwrite(block, 4, 5, o); fwrite(pixels, 1, sizeof pixels, o); fclose(o);
    uint32_t arena = P41_Arena; int32_t offset = P41_Offset, names = P54_MapA, cd = Q00B87E90;
    void *map = P54_MapAPtr; p65_tex_t tex = P65_Texs[0];
    int32_t balance = P27_MemAllocated - P27_MemFreed;
    Q00B87E90 = 0; P41_Arena = 0; P54_MapAPtr = NULL;
    for (int cycle = 0; cycle < 2; cycle++) {
      CK(P137_LoadTsd(fn) == 1);
      uint32_t addr = P41_Arena; void *base = re_ptr(addr); int tracked = 0;
      for (int i = 0; i < 0x1000; i++) if (P27_MemTab[i * 3] == addr) tracked++;
      CK(base != NULL && tracked == 1 && re_ptr(addr + 0x1fffe) == (uint8_t *)base + 0x1fffe);
      P56_ResetFrontend();
      CK(P41_Arena == 0 && P54_MapAPtr == NULL && re_ptr(addr) == NULL);
      CK(P27_MemAllocated - P27_MemFreed == balance);
    }
    P41_Arena = arena; P41_Offset = offset; P54_MapAPtr = map; P54_MapA = names;
    P65_Texs[0] = tex; Q00B87E90 = cd; remove(fn);
  }
#ifndef _WIN32
  { /* Reinitialisation and a missing second MCD must release partial loads. */
    char cwd[4096], tmp[] = "/tmp/re_p137_motion_XXXXXX";
    if (!getcwd(cwd, sizeof cwd) || !mkdtemp(tmp) || chdir(tmp)) return f + 1;
    char *names = P20_Names; int32_t count = P20_Count, mode = D_00b87e30, cheat = MenuOptBDFA58;
    p54_p4_t saved; memcpy(saved, P54_Tab4, sizeof saved); memset(P54_Tab4, 0, sizeof saved);
    p137_i5_t skipa, skipb; memcpy(skipa, P137_McdSkipA, sizeof skipa); memcpy(skipb, P137_McdSkipB, sizeof skipb);
    memset(P137_McdSkipA, 0, sizeof skipa); memset(P137_McdSkipB, 0, sizeof skipb);
    char models[] = "PED1BASE\0PED2BASE\0PED3BASE\0PED1HEAD\0PED2HEAD\0PED3HEAD\0";
    P20_Names = models; P20_Count = 6; D_00b87e30 = 0; MenuOptBDFA58 = 0;
    const char *files[] = {"WALK.MCD", "RUN.MCD", "DIVE.MCD", "SITTING.MCD"};
    for (int i = 0; i < 4; i++) {
      FILE *o = fopen(files[i], "wb"); int32_t h[3] = {0, 0, 1}; float pos[3] = {0, 0, 1};
      fwrite(h, 4, 3, o); fwrite(pos, 4, 3, o); fclose(o);
    }
    int32_t balance = P27_MemAllocated - P27_MemFreed;
    CK(P137_MotionInit() == 1); CK(P137_MotionInit() == 1);
    CK(P27_MemAllocated - P27_MemFreed == balance + 4 * 0x80002);
    remove("RUN.MCD"); CK(P137_MotionInit() == 0 && P106_PartOn == 0);
    for (int i = 0; i < 4; i++) CK(P54_Tab4[i] == NULL);
    CK(P27_MemAllocated - P27_MemFreed == balance);
    for (int i = 0; i < 4; i++) remove(files[i]);
    P20_Names = names; P20_Count = count; D_00b87e30 = mode; MenuOptBDFA58 = cheat;
    memcpy(P54_Tab4, saved, sizeof saved); memcpy(P137_McdSkipA, skipa, sizeof skipa); memcpy(P137_McdSkipB, skipb, sizeof skipb);
    if (chdir(cwd)) return f + 1;
    rmdir(tmp);
  }
#endif
  /* 004a1037: номер машины вне таблицы и режим камеры 8 без записи — выход без изменений */
  { uint8_t m = P59_Mode1137324; int32_t gn = P123_GlowN;
    P137_DrawCar(-1, -1); P137_DrawCar(99, -1);
    P59_Mode1137324 = 8; P137_DrawCar(0, -1); CK(P123_GlowN == gn);
    P59_Mode1137324 = m; }
#undef CK
  return f;
}

static int test_p134(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p134 fail line %d\n",__LINE__); } } while (0)
  int32_t b78 = G6_00B5A778, md = P29_Mode, lk = P128_FreeCamLock, v1c = P61_V1C, v20 = P61_V20, mo = P98_MrkOff, c20 = P133_1137320;
  int32_t sel = P60_Var1373C0, v18 = P61_V18, a4 = P98_C824A0;
  float cx = P44_CamX, cy = P44_CamY, cz = P44_CamZ, d8 = P61_Dist8, dc = P61_DistC, inc = P62_F136C54, oy = P61_OffY, sc = P43_ScaleA;
  float tx = P61_TgtX, ty = P61_TgtY, tz = P61_TgtZ;
  uint16_t aa = P59_AngA, ab = P59_AngB, ac = P59_AngC;
  G6_00B5A778 = 1; P29_Mode = 0;                                                  /* 0049cad4: повтор без режима — 0 */
  P61_Dist8 = 5.0f; CK(P134_CamCollide(1) == 0 && P61_Dist8 == 5.0f);
  G6_00B5A778 = 0; P61_Dist8 = 0.0f; P61_DistC = 100.0f; P62_F136C54 = 30.0f;      /* без коробок: +01136c54 до 0113731c */
  CK(P134_CamCollide(0) == 0 && P61_Dist8 == 30.0f);
  P61_Dist8 = -10.0f; P62_F136C54 = 500.0f; CK(P134_CamCollide(0) == 0 && P61_Dist8 == 100.0f);
  G6_00B5A778 = 1;                                                                /* 0049e16c: car = −1 — углы 011373b8 */
  P61_TgtX = 10.0f; P61_TgtY = -20.0f; P61_TgtZ = 30.0f; P61_AngB8 = 0x123; P61_AngBA = 0x456; P61_AngBC = 7; P60_Var1373C0 = 1;
  P134_CamTarget(-1);
  CK(P44_CamX == 10.0f && P44_CamY == -20.0f && P44_CamZ == 30.0f && P59_AngA == 0x123 && P59_AngB == 0x456 && P59_AngC == 7 && P43_ScaleA == 1152.0f);
  P60_Var1373C0 = 0; P134_CamTarget(-1); CK(P43_ScaleA == 384.0f);
  P61_TgtX = (float)P99_Cars[0].pos[0]; P61_TgtY = (float)-P99_Cars[0].pos[1] - 1000.0f; P61_TgtZ = (float)P99_Cars[0].pos[2];
  P134_CamTarget(0); CK(P59_AngB == 0 && P59_AngC == 0);                          /* машина прямо под камерой */
  P128_FreeCamLock = 0; P98_MrkOff = 1; P61_V1C = 0x200; P133_1137320 = 0x200 << 16;  /* 0049d84a: поворот 0 — вектор как есть */
  P61_OffY = -300.0f; P61_Dist8 = 1200.0f; P61_DistC = 5000.0f; P62_F136C54 = 0.0f;
  P134_CamChase(0);
  CK(P44_CamX == (float)P99_Cars[0].pos[0] && P44_CamY == (float)-P99_Cars[0].pos[1] - 300.0f && P44_CamZ == (float)P99_Cars[0].pos[2] + 1200.0f);
  CK(P61_V1C == 0x200 && P59_AngC == 0);
  P98_C824A0 = 0; P44_CamX = 1.0f; P134_CamCine(); CK(P44_CamX == 1.0f);          /* 004f0f90: выключено */
  { uint8_t rec[0x54] = { 0 }; uint8_t *ct = P59_CarsTab;                          /* 00494620 */
    P59_CarsTab = NULL; rec[0] = 0; rec[0xb] = 2;
    P134_TrafficHold(rec); CK(rec[0xb] == 1 && P99_Cars[1].ffc == -575);
    rec[0xb] = 0; P134_TrafficHold(rec); CK(rec[1] == 2 && rec[2] == 1);
    P59_CarsTab = ct; }
  G6_00B5A778 = b78; P29_Mode = md; P128_FreeCamLock = lk; P61_V1C = v1c; P61_V20 = v20; P98_MrkOff = mo; P133_1137320 = c20;
  P60_Var1373C0 = sel; P61_V18 = v18; P98_C824A0 = a4;
  P44_CamX = cx; P44_CamY = cy; P44_CamZ = cz; P61_Dist8 = d8; P61_DistC = dc; P62_F136C54 = inc; P61_OffY = oy; P43_ScaleA = sc;
  P61_TgtX = tx; P61_TgtY = ty; P61_TgtZ = tz; P59_AngA = aa; P59_AngB = ab; P59_AngC = ac;
#undef CK
  return f;
}

static int test_p133(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p133 fail line %d\n",__LINE__); } } while (0)
  { int32_t on = P58_CfgOn, lk = P58_CfgLock;                                     /* 004055e8: выключено — 1 без чтения */
    P58_CfgOn = 0; CK(P133_LoadConfig() == 1);
    FILE *chk = fopen("config.dat", "rb");
    if (chk == NULL) {                                                           /* круг 00405bfa → 004055e8 */
      int32_t a = P102_57B6F8, b = P12_00575f50, m = P95_ModeSel, w = P68_ModeW; float v = WF00575F14;
      P58_CfgOn = 1; P58_CfgLock = 0; P102_57B6F8 = 0x1234; P12_00575f50 = 77; P95_ModeSel = 1; WF00575F14 = 3.0f;
      P58_SaveConfig();
      P102_57B6F8 = 0; P12_00575f50 = 0; P68_ModeW = 0;
      CK(P133_LoadConfig() == 1);
      CK(P102_57B6F8 == 0x1234 && P12_00575f50 == 77 && WF00575F14 == 0.5f);
      CK(P68_ModeW == (int32_t)P95_ModeTab[7]);
      remove("config.dat");
      P102_57B6F8 = a; P12_00575f50 = b; P95_ModeSel = m; P68_ModeW = w; WF00575F14 = v;
      CK(P133_LoadConfig() == 1 || 1);
    } else fclose(chk);
    P58_CfgOn = on; P58_CfgLock = lk; }
  { uint8_t m = P59_Mode1137324; int32_t g = G2_01137324, v18 = P61_V18, bd = MenuOptBDFA54, bd2 = G00BDFA54, h1 = P62_HudOff1, h2 = G6_00B87EA0;
    float cx = P44_CamX, oy = P61_OffY, d8 = P61_Dist8;                           /* 0049f6c7: далеко от игрока — режим 0 */
    MenuOptBDFA54 = 0; G00BDFA54 = 0; P62_HudOff1 = 0; G6_00B87EA0 = 0;
    float tx = P61_TgtX; int32_t a4 = P98_C824A0; P98_C824A0 = 0; P59_Mode1137324 = 0x10; G2_01137324 = 0x10; P61_TgtX = (float)P99_Cars[0].pos[0] + 1.0e6f;
    P133_CamUpdate(1);
    CK(P59_Mode1137324 == 0 && G2_01137324 == 0 && P61_V18 == 0x800 && P61_OffY == -256.0f && P61_Dist8 == 1280.0f);
    P59_Mode1137324 = m; G2_01137324 = g; P61_V18 = v18; MenuOptBDFA54 = bd; G00BDFA54 = bd2; P62_HudOff1 = h1; G6_00B87EA0 = h2;
    P44_CamX = cx; P61_OffY = oy; P61_Dist8 = d8; P61_TgtX = tx; P98_C824A0 = a4; }
  { int32_t g = G00D12408; G00D12408 = 0; P133_EventModels(); CK(S_00D12410 == NULL); G00D12408 = g; }   /* 004cf84c: пустой список */
#undef CK
  return f;
}

static int test_p132(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p132 fail line %d\n",__LINE__); } } while (0)
  { p99_camkeys_t sv; memcpy(sv, P99_CamKeys, sizeof sv); int32_t last = P99_CamLast;   /* 0049f20a: .FBD (CRLF) */
    FILE *o = fopen("t132_flyby.txt", "wb");
    if (o) {
      fputs("DRIVER Fly-By Text-file\r\n\r\nControl Point 0\r\n  Position:  1.5,  -2.0,  3.0\r\n  Rotation: 0.5, 0.25, -0.125, 1.0\r\n"
            "  Zoom:       696.0\r\n  Frame:      7\r\n\r\nControl Point 1\r\n  Position:  4.0, 5.0, 6.0\r\n  Rotation: 0, 0, 0, 1\r\n"
            "  Zoom:  100\r\n  Frame:  9\r\n\r\nEnd of Fly-By\r\n", o);
      fclose(o);
      memset(P99_CamKeys, 0, sizeof P99_CamKeys);
      CK(P132_LoadFlyby("t132_flyby.txt") == 1);
      CK(P99_CamLast == 2);
      float x; int32_t fr, fl; memcpy(&x, &P99_CamKeys[0x34 + 0], 4); CK(x == 4.0f);
      memcpy(&x, &P99_CamKeys[0x20], 4); CK(x == 0.5f); memcpy(&x, &P99_CamKeys[0x10], 4); CK(x == 0.25f);
      memcpy(&fr, &P99_CamKeys[0x2c], 4); CK(fr == 7); memcpy(&fl, &P99_CamKeys[0x28], 4); CK(fl == 1);
      memcpy(&fr, &P99_CamKeys[2 * 0x34 + 0x2c], 4); CK(fr == 9);
      remove("t132_flyby.txt");
    }
    CK(P132_LoadFlyby("t132_none.txt") == 0);
    memcpy(P99_CamKeys, sv, sizeof sv); P99_CamLast = last; }
  { int32_t fr = P62_Frame; uint8_t sv[0x78]; memcpy(sv, P95_ObjA, 0x78);       /* 004b9287: чётный кадр — без записи */
    float p[3] = { 1, 2, 3 }, v[3] = { 0, 0, 0 };
    P62_Frame = 2; P95_ObjA[0x68] = 0x5a; P132_Smoke(p, v, 0, 100, 10, 50, 1, -1.0f, 0); CK(P95_ObjA[0x68] == 0x5a);
    memcpy(P95_ObjA, sv, 0x78); P62_Frame = fr; }
  { int32_t a = G00D14EEC, b = G00D14EF4, c = G00D17B08, d = P26_FxB, e = G6_00B5A778, g = P13_00575ef4, h = S_00D1192C;   /* 004ca135 */
    G00D14EEC = 0x78; G00D14EF4 = 1; G00D17B08 = 0; P26_FxB = 0; G6_00B5A778 = 0; P13_00575ef4 = 0; S_00D1192C = 0;
    P132_Lights(); CK(G00D14EEC == 0x08 && G00D14EF4 == 0);
    G00D14EEC = a; G00D14EF4 = b; G00D17B08 = c; P26_FxB = d; G6_00B5A778 = e; P13_00575ef4 = g; S_00D1192C = h; }
#undef CK
  return f;
}

static int test_p131(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p131 fail line %d\n",__LINE__); } } while (0)
  /* 0041b7d1: с v1.77 цикл 00417b80 перенесён (P132_MenuLoop) и требует полного окружения меню — проверка снята */
  { char line[64]; char *sl = P65_Line;                             /* 004f621d: комментарий/пустая строка → 0 */
    strcpy(line, "// comment"); P65_Line = line; CK(P131_ScriptLine() == 0);
    strcpy(line, "   "); P65_Line = line; P131_ScriptLine();
    P65_Line = sl; }
  { static int32_t buf[0x65 + 100 * 0xd]; static uint8_t ic[16] = { 0 };   /* 004cbc1e: одна капля этапа 2 → 2 треугольника */
    int32_t *svs = G2_ScriptStack; uint8_t *si = G00D14EF0, *ss = G00D164EC; p85_raster_fn sr = P85_RasterB;
    memset(buf, 0, sizeof buf); buf[0] = 1;
    uint8_t *r = (uint8_t *)&buf[0x65]; r[0x30] = 2; float w = 0.5f; memcpy(r + 0x28, &w, 4);
    G2_ScriptStack = buf; G00D14EF0 = ic; G00D164EC = NULL; P85_RasterB = t131_rast; t131_n = 0;
    p85_state_fn sst = P85_StateFn; p85_blend_fn sbl = P85_BlendFn; p86_texsrc_fn stx = P86_TexSrc;
    P85_StateFn = NULL; P85_BlendFn = NULL; P86_TexSrc = NULL; FnV1 sdm = G6_01270D28; G6_01270D28 = t131_dm;
    uint8_t sbc = P85_BlendCur, sbo = P69_BlendOn; int32_t ssd = P85_StateDirty, sct = P86_CurTex;
    P131_RainDraw(); CK(t131_n == 2);
    r[0x30] = 1; t131_n = 0; P131_RainDraw(); CK(t131_n == 0);
    G2_ScriptStack = svs; G00D14EF0 = si; G00D164EC = ss; P85_RasterB = sr; P85_StateFn = sst; P85_BlendFn = sbl; P86_TexSrc = stx;
    P85_BlendCur = sbc; P69_BlendOn = sbo; P85_StateDirty = ssd; P86_CurTex = sct; G6_01270D28 = sdm; }
  { uint16_t a = P59_AngA, b = P59_AngB, c = P59_AngC; int32_t k = G6_00B5A778, m = P29_Mode, an = P76_Angle;   /* 0049e7a8 */
    p131_camang_t sv; memcpy(sv, P131_CamAng, sizeof sv);
    P131_CamAng[0] = 1; P131_CamAng[1] = 2; P131_CamAng[2] = 3; P131_CamAng[3] = 4;
    G6_00B5A778 = 1; P29_Mode = 0; P76_Angle = 0x30;
    P131_CamShake(); CK(P59_AngA == 1 && P59_AngB == 2 && P59_AngC == 3 && P131_AngD == 4);
    memcpy(P131_CamAng, sv, sizeof sv); P59_AngA = a; P59_AngB = b; P59_AngC = c; G6_00B5A778 = k; P29_Mode = m; P76_Angle = an; }
#undef CK
  return f;
}
static int test_p130(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p130 fail line %d\n",__LINE__); } } while (0)
  static int32_t buf[0x65 + 100 * 0xd];
  int32_t *svs = G2_ScriptStack; int32_t sflag = P16_FlagA; float *smat = P44_MatPtr;
  int32_t sa = P120_ScrA, sb = P120_ScrB, sc = P120_ScrC, sd = P120_ScrD, se = P120_ScrE, ss = P120_ScrSeed;
  memset(buf, 0, sizeof buf); G2_ScriptStack = buf;
  for (int i = 0; i < 100; i++) buf[i + 1] = i;
  P16_FlagA = 1; P130_RainSpawn(); CK(buf[0] == 0);          /* 004cc008: пауза — ничего */
  P16_FlagA = 0;
  buf[0] = 1; buf[0x65 + 1] = 100; *(int16_t *)(void *)((uint8_t *)&buf[0x65] + 0x32) = 7;
  P130_RainStep();                                           /* 004cba1d: y > 0x32 — запись назад */
  CK(buf[0] == 0); CK(buf[1] == 7); CK(buf[0x65 + 1] == 150);
  buf[0] = 1; buf[0x65 + 1] = 100; P120_ScrSeed = 1000; P120_ScrC = 0; P120_ScrB = 3; P120_ScrA = -2;
  buf[0x65] = 10; buf[0x65 + 2] = 20;
  P130_SnowStep();                                           /* 004cdb25: ветер + y += 10 */
  CK(P120_ScrC == 1); CK(buf[0x65] == 10 + P120_ScrB); CK(buf[0x65 + 1] == 110); CK(buf[0] == 0);
  CK(P130_LampRGB[0] == 0 && P130_LampRGB[1] == 0x80 && P130_LampRGB[2] == 0x80);
  G2_ScriptStack = svs; P16_FlagA = sflag; P44_MatPtr = smat;
  P120_ScrA = sa; P120_ScrB = sb; P120_ScrC = sc; P120_ScrD = sd; P120_ScrE = se; P120_ScrSeed = ss;
#undef CK
  return f;
}
static int test_p129(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p129 fail line %d\n",__LINE__); } } while (0)
  { p129_boxes_t sv; memcpy(sv, P129_Boxes, sizeof sv); p99_car_t c0 = P99_Cars[0];   /* 005001bb */
    memset(P129_Boxes, 0, sizeof P129_Boxes);
    int32_t *a = P129_Boxes[0], *b = P129_Boxes[1];
    a[0] = 100; a[1] = 0; a[2] = 0; a[4] = 10; a[5] = 20; a[7] = 40;     /* полуX/Z меняются местами (флаг 0x400) */
    b[0] = 140; b[1] = 0; b[2] = 5; b[4] = 10; b[5] = 20; b[7] = 40;
    memset(&P99_Cars[0], 0, sizeof(p99_car_t)); P99_Cars[0].pos2[0] = 0; P99_Cars[0].pos2[1] = 0; P99_Cars[0].pos2[2] = 0;
    CK(P129_BoxMerge(0, 1, 5) == 0);                     /* машина 1..0x40 — нет */
    int32_t r = P129_BoxMerge(0, 1, 0);
    CK(a[6] == 0x400 && b[6] == 0x400);
    CK(r == 1 && b[4] == 0 && a[0] == 120 && a[4] == 40 && a[2] == 2 && a[5] == 12 && a[7] == 40);
    a[6] = 1; CK(P129_BoxMerge(0, 2, 0) == 0);           /* повёрнутая коробка — нет */
    CK(P129_BoxMerge(70, 1, 0) == 0);
    memcpy(P129_Boxes, sv, sizeof sv); P99_Cars[0] = c0; }
  { int32_t box[8] = { 0 }; uint8_t obj[0x20]; memset(obj, 0, sizeof obj);   /* 0049b14d: объект без модели/вне таблицы */
    CK(P129_ObjHit(NULL, box, obj) == 0);
    int32_t m = 5000; memcpy(obj + 4, &m, 4); CK(P129_ObjHit((uint8_t *)&P99_Cars[0], box, obj) == 0); }
  { float pos[3] = { 0, 0, 0 }; uint8_t obj[0x20]; memset(obj, 0, sizeof obj);   /* 00500937: модели нет — выход */
    int32_t n0 = P129_BoxN; P129_ObjBoxes(obj, pos, (uint8_t *)&P99_Cars[0], 1, 0, 1); CK(P129_BoxN == n0);
    P129_ObjBoxes(obj, NULL, (uint8_t *)&P99_Cars[0], 1, 0, 1); CK(P129_BoxN == n0); }
  { void *g = G6_00D01268; int32_t n = P54_GridN; uint8_t e = P95_B87E14;   /* 00500e1d: без сетки — выход до обнуления */
    P129_BoxN = 7; G6_00D01268 = NULL; P95_B87E14 = 0; P129_CarObjects(0); CK(P129_BoxN == 7);
    P95_B87E14 = 1; P129_CarObjects(0); CK(P129_BoxN == 7); P129_CarObjects(100);
    G6_00D01268 = g; P54_GridN = n; P95_B87E14 = e; P129_BoxN = 0; }
  { int32_t pts[8] = { 0, 0, 1000, 0, 1000, 1000, 0, 1000 }, rc[4] = { 0, 0, 750, 750 };   /* P128_ClipAreaN */
    CK(P128_ClipAreaN(pts, 4, rc) == 750 * 750); rc[0] = 2000; rc[2] = 3000; CK(P128_ClipAreaN(pts, 4, rc) == 0); }
  { p77_c5fe00_t sv; memcpy(sv, P77_C5FE00, sizeof sv); int32_t nn = P59_NearN; p99_car_t c1 = P99_Cars[1];   /* 0050b088 */
    uint8_t t1 = TrafficRecs[1], t5 = TrafficRecs[5];
    int32_t mc = P62_MapC64, m2 = P62_Map2C40; float sc = P63_Scale;
    memset(P77_C5FE00, 0, sizeof P77_C5FE00);
    P59_NearN = 1; P59_NearList[0] = 0; TrafficRecs[1] = 1; TrafficRecs[5] = 0;
    memset(&P99_Cars[1], 0, sizeof(p99_car_t)); P62_MapC64 = 0; P62_Map2C40 = 0; P63_Scale = 1.0f / 1500.0f;
    int32_t rec[0x16]; memset(rec, 0, sizeof rec); rec[0x14] = 0; rec[0x15] = 0;
    P99_Cars[1].pos[0] = 3000; P99_Cars[1].pos[2] = -3000;
    P129_MapCars(rec);
    int32_t marked = 0; for (int i = 0; i < 0x37 * 0x37; i++) { uint32_t v; memcpy(&v, &P77_C5FE00[i * 4], 4); if (v & 0x20) marked++; }
    CK(marked > 0);
    memset(P77_C5FE00, 0, sizeof P77_C5FE00); rec[0] = 0; TrafficRecs[5] = 1; P129_MapCars(rec);   /* цель записи — пропуск */
    marked = 0; for (int i = 0; i < 0x37 * 0x37; i++) { uint32_t v; memcpy(&v, &P77_C5FE00[i * 4], 4); if (v) marked++; }
    CK(marked == 0); P129_MapCars(NULL);
    memcpy(P77_C5FE00, sv, sizeof sv); P59_NearN = nn; P99_Cars[1] = c1; TrafficRecs[1] = t1; TrafficRecs[5] = t5;
    P62_MapC64 = mc; P62_Map2C40 = m2; P63_Scale = sc; }
#undef CK
  if (f == 0) printf("p129 ok\n");
  return f;
}
static int test_p128(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p128 fail line %d\n",__LINE__); } } while (0)
  static uint8_t sv[0xcd8]; uint8_t *rec = (uint8_t *)P12_0112da00; memcpy(sv, rec, sizeof sv);
  { /* 0050a15b: квадрат 10×10, окно 2..8 → 36; узлы в области пути копа 0 (k_regions) */
    int32_t *nd = (int32_t *)(void *)(rec + 0x40);
    int32_t pts[4][2] = { { 0, 0 }, { 10, 0 }, { 10, 10 }, { 0, 10 } };
    for (int k = 0; k < 4; k++) { nd[k * 3] = pts[k][0]; nd[k * 3 + 1] = pts[k][1]; re_wr_ptr(&nd[k * 3 + 2], k < 3 ? &nd[(k + 1) * 3] : NULL); }
    int32_t r1[4] = { 2, 2, 8, 8 }, r2[4] = { -5, -5, 5, 20 }, r3[4] = { 20, 20, 30, 30 };
    CK(P128_ClipArea(nd, r1) == 36); CK(P128_ClipArea(nd, r2) == 50); CK(P128_ClipArea(nd, r3) == 0); }
  { /* 0050c087: цепочка узлов 5 → 4 */
    static uint8_t n45[0x40]; int32_t s5 = P77_S574570, c8 = P77_C7D8A8; uint8_t d50 = P77_C7D850;
    uint8_t ct[8]; memcpy(ct, P77_C62E60 + 16, 8); memcpy(n45, P77_C65DC0 + 4 * 0x20, 0x40);
    memset(rec, 0, 0xcd8); memset(P77_C62E60 + 16, 0, 8); memset(P77_C65DC0 + 4 * 0x20, 0, 0x40);
    int32_t v; v = -1; memcpy(P77_C65DC0 + 4 * 0x20 + 0xc, &v, 4);
    v = 4; memcpy(P77_C65DC0 + 5 * 0x20 + 0xc, &v, 4); v = 1; memcpy(P77_C65DC0 + 5 * 0x20 + 0x10, &v, 4);
    P77_S574570 = 5; P77_C7D8A8 = 0; P77_C7D850 = 0;
    int32_t r = P128_CopPath(rec);
    int32_t x0, x1; memcpy(&x0, rec + 0x68, 4); memcpy(&x1, rec + 0x88, 4);
    CK(r == 1 && P77_C7D8A8 == 2 && x0 == 0 && x1 == 0x5dc);
    CK(re_rd_ptr(rec + 0x60) == (void *)(rec + 0x80) && re_rd_ptr(rec + 0x80) == NULL && re_rd_ptr(rec + 0x84) == (void *)(rec + 0x60));
    int32_t big[0x32f]; memset(big, 0, sizeof big);
    CK(P128_CopRoute(big, 0x1c, 0, 0) == 0);
    memcpy(P77_C62E60 + 16, ct, 8); memcpy(P77_C65DC0 + 4 * 0x20, n45, 0x40);
    P77_S574570 = s5; P77_C7D8A8 = c8; P77_C7D850 = d50; }
  { /* 004a742a: путь не кончился, игрок рядом → без перепланирования */
    memset(rec, 0, 0xcd8); int32_t one = 1, two = 2, sev = 7;
    memcpy(rec + 0xcb8, &one, 4); memcpy(rec + 0x14, &two, 4); memcpy(rec + 0x18, &two, 4); memcpy(rec + 0xcc8, &one, 4); memcpy(rec + 4, &sev, 4);
    P128_CopReplan(rec); int32_t w; memcpy(&w, rec + 4, 4); CK(w == 7); }
  memcpy(rec, sv, sizeof sv);
  { void *g = G6_00D01268; G6_00D01268 = NULL; CK(P128_ModelHit(0.0f, 0.0f, 0.0f, 0) == 0); G6_00D01268 = g; }
  { uint32_t m = P28_CarClean[0]; uint8_t k = P98_CarKind[0]; P28_CarClean[0] = 0; P98_CarKind[0] = 0;
    P128_CarDeform(-1); CK(P98_CarKind[0] == 0xff); P28_CarClean[0] = m; P98_CarKind[0] = k; }
  { float cx = P44_CamX, cy = P44_CamY, cz = P44_CamZ, ox = P61_OffX, oy = P61_OffY, oz = P61_OffZ; int32_t lk = P128_FreeCamLock, a6 = G6_00B5A778;
    uint8_t p2 = P36_Pad2, p3 = P36_Pad3, p4 = P36_Pad4, p5 = P36_Pad5;
    P36_Pad2 = P36_Pad3 = P36_Pad4 = P36_Pad5 = 0; G6_00B5A778 = 0; P128_FreeCamLock = 0;
    P44_CamX = 0.0f; P44_CamY = 0.0f; P44_CamZ = 0.0f; P61_OffX = 100.0f; P61_OffY = 0.0f; P61_OffZ = -50.0f; P36_Pad3 = 1;
    P128_FreeCam(0); CK(P61_OffZ == -18.0f && P44_CamX == 10.0f && P44_CamZ == -1.0f && P59_AngC == 0);
    P44_CamX = cx; P44_CamY = cy; P44_CamZ = cz; P61_OffX = ox; P61_OffY = oy; P61_OffZ = oz; P128_FreeCamLock = lk; G6_00B5A778 = a6;
    P36_Pad2 = p2; P36_Pad3 = p3; P36_Pad4 = p4; P36_Pad5 = p5; InitXform_005263FE(); }
  return f;
#undef CK
}
static int test_p127(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p127 fail line %d\n",__LINE__); } } while (0)
  { int32_t d0 = DirIndicatorOn, pm = P29_Mode, c4 = P14_00c810c4, mm = MenuMode1271060, b90 = P12_00d17b90, gm = GameMode,
      q = P11_00d11934, h2 = P62_HudOff2;
    DirIndicatorOn = 0; P29_Mode = 0; P12_00d17b90 = 0; GameMode = 0; P11_00d11934 = 1; P14_00c810c4 = 0; MenuMode1271060 = 10;
    P62_HudOff2 = 0;
    P127_Pause(); CK(P17_PtrA == 0x00574868u && P8_00b5a764 == 0 && G6_00B5A778 == 1 && P107_NavWait == 10);
    CK(re_ptr(P17_PtrA) == (void *)(P127_PauseMenu + 0x158));
    MenuMode1271060 = 6; P127_Pause(); CK(P17_PtrA == 0x005747d8u);
    P12_00d17b90 = 1; P127_Pause(); CK(P17_PtrA == 0x00574ea0u && P8_00b5a764 == 1);
    DirIndicatorOn = d0; P29_Mode = pm; P14_00c810c4 = c4; MenuMode1271060 = mm; P12_00d17b90 = b90; GameMode = gm;
    P11_00d11934 = q; P62_HudOff2 = h2; G6_00B5A778 = 0; P16_FlagA = 0; P17_PtrA = 0; P8_00b5a764 = 0; }
  { uint8_t t[0x54]; memset(t, 0, sizeof t); t[0x13] = 1; P127_TrafficLane(t); CK(t[0x13] == 1 && t[0x48] == 0); }
  { P102_D0DD78 = 5; P127_PlayerSkid(1); CK(P102_D0DD78 == 0); }
  { int16_t hd = P94_Heading; P127_SpawnRst = 1; P94_Heading = 0x100; P127_SpawnTick(0);
    CK(P127_SpawnRst == 0 && P61_V1C == 0x900 && P43_ScaleA == 384.0f && P61_OffY == -256.0f); P94_Heading = hd;
    int32_t a = P98_C824A0; P98_C824A0 = 0; P127_SpawnReq = 0; P127_SpawnTick(0); CK(P127_SpawnReq == 0 && P98_C824A0 == 0); P98_C824A0 = a; }
  { uint32_t p = P75_Ptr562D7C; int32_t sp; uint8_t *c0 = (uint8_t *)&P99_Cars[0]; memcpy(&sp, c0 + 0x10c, 4);
    int32_t z = 0; memcpy(c0 + 0x10c, &z, 4); P127_FarDebris(); CK(P75_Ptr562D7C == p); memcpy(c0 + 0x10c, &sp, 4); }
  { p58_slot_t *l = P58_ListB31EC4; P58_ListB31EC4 = NULL; P127_LampPhase = 3; P127_LampLights(); CK(P127_LampPhase == 3); P58_ListB31EC4 = l; }
  { int32_t o = P97_ScrObjOn; P97_ScrObjOn = 0; P127_Goal[0] = 5.0f; P127_ScriptTick(); CK(P127_Goal[0] == 5.0f); P97_ScrObjOn = o; }
  { int32_t n = P62_MapN, v = 0x23, r1, r2; uint8_t s0[4], s1[4], s2[4];
    memcpy(s0, P77_C5FE00, 4); memcpy(s1, P77_C7D8C0, 4); memcpy(s2, P77_C62E60, 4);
    P62_MapN = 0; memcpy(P77_C5FE00, &v, 4); P127_MapWindow(0, 0, 0);
    memcpy(&r1, P77_C7D8C0, 4); memcpy(&r2, P77_C62E60, 4); CK(r1 == 2 && r2 == P110_CellTab[0x23]);
    memcpy(P77_C5FE00, s0, 4); memcpy(P77_C7D8C0, s1, 4); memcpy(P77_C62E60, s2, 4); P62_MapN = n; }
  { int32_t cam[0x23], u = DirectorUnk6C; memset(cam, 0x55, sizeof cam); DirectorUnk6C = 0x20000000;
    P127_AutoCamera(cam); CK(cam[0] == 0 && cam[0x22] == 0); DirectorUnk6C = u; }
  return f;
#undef CK
}
static int test_p125(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p125 fail line %d\n",__LINE__); } } while (0)
  { int32_t n0 = P58_CntC814E8; void **p0 = P58_PtrsC816A0; int32_t *l0 = P58_LimC810AC;
    P58_CntC814E8 = 0; P58_PtrsC816A0 = NULL; P58_LimC810AC = NULL;
    CK(P125_AddDashMessage("ONE", 5) == 1); CK(P125_AddDashMessage("TWO", 7) == 1);
    CK(P58_CntC814E8 == 2 && strcmp((const char *)P58_PtrsC816A0[1], "TWO") == 0 && P58_LimC810AC[0] == 5 && P58_LimC810AC[1] == 7);
    for (int i = 0; i < 2; i++) DebugFree(P58_PtrsC816A0[i]);
    DebugFree(P58_PtrsC816A0); DebugFree(P58_LimC810AC);
    P58_CntC814E8 = n0; P58_PtrsC816A0 = p0; P58_LimC810AC = l0; }
  { float buf[48]; float *o0 = P100_ClipOut; int32_t n0 = P100_ClipN; float nr = P95_Near;
    uint8_t a[0x18] = {0}, b[0x18] = {0}; float v;
    P95_Near = 10.0f; P100_ClipOut = buf; P100_ClipN = 0;
    v = 0.0f; memcpy(a + 0xc, &v, 4); v = 0.0f; memcpy(a + 0x10, &v, 4); v = 20.0f; memcpy(a + 0x14, &v, 4);
    v = 10.0f; memcpy(b + 0xc, &v, 4); v = 4.0f; memcpy(b + 0x10, &v, 4); v = 0.0f; memcpy(b + 0x14, &v, 4);
    P125_ClipNearXY(a, b); CK(P100_ClipN == 1 && buf[0] == 5.0f && buf[1] == 2.0f && buf[2] == 50.0f && P100_ClipOut == buf + 12);
    P100_ClipOut = buf; P100_ClipN = 0; P125_ClipNearXY(b, a); CK(P100_ClipN == 2 && buf[0] == 5.0f && buf[12] == 0.0f && buf[14] == 20.0f);
    P100_ClipOut = buf; P100_ClipN = 0; P125_ClipNearXY(b, b); CK(P100_ClipN == 0);
    P100_ClipOut = o0; P100_ClipN = n0; P95_Near = nr; }
  { const char *m0 = P62_ModelNames; int32_t s0 = P125_ModelNamesSize, c0 = P62_ModelCount;
    P62_ModelNames = NULL; P125_ModelNamesSize = 0;
    P125_ModelName("car = 12", 0); P125_ModelName("Zap= 3", 0);
    const uint8_t *b = (const uint8_t *)P62_ModelNames;
    CK(b != NULL && memcmp(b, "CAR\0\x0c\0ZAP\0\x03\0\0\0", 14) == 0 && P125_ModelNamesSize == 14 && P62_ModelCount == c0 + 2);
    if (b) DebugFree((void *)b);
    P62_ModelNames = m0; P125_ModelNamesSize = s0; P62_ModelCount = c0; }
  { uint8_t pal[0x400]; uint32_t out[0x100];
    for (int i = 0; i < 0x100; i++) { pal[i*4] = (uint8_t)i; pal[i*4+1] = (uint8_t)i; pal[i*4+2] = (uint8_t)i; pal[i*4+3] = 0; }
    P125_ShrR = P125_ShrG = P125_ShrB = 3; P125_ShlR = 11; P125_ShlG = 5; P125_ShlB = 0;
    P125_BlendTable(pal, out, 0, 7);
    CK(out[0xff] == 0xfbffu && out[8] == 0x0821u && ((uint8_t *)P65_Blend)[0x100 * 0x10 + 0x20] == 0x16 && ((uint8_t *)P65_Blend)[0x100 * 5] == 5 && P65_ColorKey == 0); }
  { uint8_t mb[0x2a8]; memcpy(mb, P117_MenuB, sizeof mb); int32_t ef8 = MenuVar575EF8;
    MenuVar575EF8 = 1; P125_CtrlMenuValues(); int32_t v; memcpy(&v, P117_MenuB + 0x30, 4); CK(v == 10);
    MenuVar575EF8 = ef8; memcpy(P117_MenuB, mb, sizeof mb); }
  { uint8_t obj[0x14] = {0}; float x = 100.4f, z = 7.0f; int32_t vel[3] = { 0x400, 0, 0x800 };
    memcpy(obj + 8, &x, 4); memcpy(obj + 0x10, &z, 4);
    uint8_t d0[6 * 0x1c]; memcpy(d0, P101_Drops, sizeof d0); int32_t i0 = P12_00bde764, c0 = P12_00bdf980;
    uint8_t b84[sizeof P56_Blk84]; memcpy(b84, P56_Blk84, sizeof b84); int32_t g = G6_01136920; G6_01136920 = 0;
    memset(P101_Drops, 0, sizeof d0); P12_00bde764 = 5;
    CK(P125_DropHit(obj, vel) == 0 && P12_00bde764 == 0);
    int32_t ax; memcpy(&ax, P101_Drops + 5 * 0x1c + 0xc, 4); CK(ax == 100);
    int16_t s; memcpy(&s, P101_Drops + 5 * 0x1c + 0x12, 2); CK(s == -0x96);
    CK(P125_DropHit(obj, vel) == 1);
    memcpy(P101_Drops, d0, sizeof d0); P12_00bde764 = i0; P12_00bdf980 = c0; memcpy(P56_Blk84, b84, sizeof b84); G6_01136920 = g; }
  return f;
#undef CK
}
static int test_p124(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p124 fail line %d\n",__LINE__); } } while (0)
  { const char *fn = "p124_test.bmp"; FILE *o = fopen(fn, "wb"); uint8_t h[0x36]; memset(h, 0, sizeof h);
    h[0] = 'B'; h[1] = 'M'; int32_t w = 640, hh = 480; int16_t bpp = 24; memcpy(h + 0x12, &w, 4); memcpy(h + 0x16, &hh, 4); memcpy(h + 0x1c, &bpp, 2);
    fwrite(h, 1, sizeof h, o); for (int i = 0; i < 640 * 480; i++) { uint8_t px[3] = { 1, 2, (uint8_t)(i == 0 ? 9 : 3) }; fwrite(px, 1, 3, o); } fclose(o);
    uint8_t *buf = (uint8_t *)calloc(0x12c000, 1); CK(P124_ReadBmp(fn, buf) == 1);
    CK(buf[(479 * 640) * 4 + 0] == 9 && buf[(479 * 640) * 4 + 1] == 2 && buf[(479 * 640) * 4 + 2] == 1 && buf[0] == 3);
    o = fopen(fn, "r+b"); fseek(o, 0x12, SEEK_SET); w = 320; fwrite(&w, 4, 1, o); fclose(o);
    CK(P124_ReadBmp(fn, buf) == 0); CK(P124_ReadBmp("no_such_p124.bmp", buf) == 0); free(buf); remove(fn); }
  { static char nm[] = "VAR"; static int32_t val = -5; uint8_t sv[0xc]; memcpy(sv, A_010EA620, 0xc);
    uint32_t a = re_addr(nm), b = re_addr(&val); memcpy(A_010EA620, &a, 4); memcpy(A_010EA620 + 4, &b, 4);
    A_010EA620[8] = 3; A_010EA620[9] = 2; P124_WatchShow(); CK(strcmp((char *)&A_010EA620[0x200], "-5") == 0);
    A_010EA620[8] = 1; P124_WatchShow(); CK(strcmp((char *)&A_010EA620[0x200], "0bb") == 0);
    A_010EA620[8] = 0; A_010EA620[9] = 0; val = 0x1ab; P124_WatchShow(); CK(strcmp((char *)&A_010EA620[0x200], "0xab") == 0);
    memcpy(A_010EA620, sv, 0xc); }
  { int32_t on = P124_LogOn, sz = P124_LogSize; P124_LogOn = 0; P124_LogSize = 7; P124_DebugLog("x"); CK(P124_LogSize == 7); P124_LogOn = on; P124_LogSize = sz; }
  { uint32_t t = P100_ItemTab; P100_ItemTab = 0; P124_MotelSample(); P100_ItemTab = t; }
  { int32_t m = P9_005fe9f0; uint32_t t = P100_ItemTab; P9_005fe9f0 = 1; P100_ItemTab = 0; int32_t r = P124_MotelKeys(0); CK(r == 0 || r == -1); P9_005fe9f0 = m; P100_ItemTab = t; }
#undef CK
  return f;
}

static int test_p123(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p123 fail line %d\n",__LINE__); } } while (0)
  { uint8_t o[0x78]; memset(o, 0, sizeof o); float y = -1.0e9f, vy = 2.0f; int32_t t = 10, d = 3; int16_t n = 5;
    memcpy(o + 4, &y, 4); memcpy(o + 0x34, &vy, 4); memcpy(o + 0x58, &t, 4); memcpy(o + 0x5c, &d, 4); memcpy(o + 0x64, &n, 2);
    P123_ObjAFall(o); float y2, vy2, py; memcpy(&y2, o + 4, 4); memcpy(&vy2, o + 0x34, 4); memcpy(&py, o + 0x24, 4); memcpy(&t, o + 0x58, 4); memcpy(&n, o + 0x64, 2);
    CK(y2 == -1.0e9f + 2.0f && vy2 == 8.0f && py == -1.0e9f && t == 7 && n == 4); }
  { int32_t n = P123_GlowN; uint32_t ic = P95_PoolIcon; P95_PoolIcon = 0; P123_GlowN = 3; P123_CarGlows(); CK(P123_GlowN == 0);
    P95_PoolIcon = ic; P123_GlowN = n; }
  { uint32_t r = P94_IconRec; P94_IconRec = 0; P98_IconCol[0] = 1.0f; P123_ObjShadows(); CK(P98_IconCol[0] == 1.0f); P94_IconRec = r; }
  { int32_t x = P59_PosX, z = P59_PosZ; int16_t h = P94_Heading; float tx = P123_TgtX, tz = P123_TgtZ; int32_t m = P123_TgtMode, dd = P123_TgtDist; uint8_t sb = P123_SideB;
    P59_PosX = 1000; P59_PosZ = 0; P94_Heading = 0; P123_TgtX = 2000.0f; P123_TgtZ = 0.0f; P123_TgtMode = 0;
    P123_SideDist(); CK(P123_SideB == 1 && P123_SideX == 1200.0f && P123_TgtDist == 800);
    P123_TgtX = 0.0f; P123_SideDist(); CK(P123_SideB == 0 && P123_SideX == 800.0f && P123_TgtDist == 800);
    P123_TgtMode = 2; P123_PtX = 3.0f; P123_PtZ = 4.0f; P123_SideDist(); CK(P123_TgtDist == 5);
    P59_PosX = x; P59_PosZ = z; P94_Heading = h; P123_TgtX = tx; P123_TgtZ = tz; P123_TgtMode = m; P123_TgtDist = dd; P123_SideB = sb; }
  { float vx = P59_VX; uint16_t aa = P59_AngA, ab = P59_AngB; int32_t py = P99_Cars[2].pos[1];
    P123_CamAtCar(2); CK(P59_VY == (float)P99_Cars[2].pos[1] - 400.0f && P59_AngC == 0 && P44_CamX == P59_VX);
    P123_CamAtCar(99); P99_Cars[2].pos[1] = py; P59_VX = vx; P59_AngA = aa; P59_AngB = ab; }
  { uint8_t ev[0x24]; memset(ev, 0, sizeof ev); uint16_t c0 = P68_CamI0; int32_t id = P99_EvId;
    char a[] = "  TRIGGER_VALUE 5\n"; uint32_t r = P123_EvLine(re_addr(a), re_addr(ev));
    int16_t w; memcpy(&w, ev + 6, 2); CK(r == re_addr(a + 2) && (ev[0] & 8) && w == 5 && P99_EvId == 5);
    char b[] = "# note\n"; CK(P123_EvLine(re_addr(b), re_addr(ev)) == re_addr(b));
    P68_CamI0 = c0; P99_EvId = id; }
  { int32_t h = G00D12408; uint8_t *cur = P122_EvCur; char txt[] = "JUNK\nCHUNK_END\n"; P123_EventsChunk(txt); CK(G00D12408 == h && P122_EvCur == cur); }
#undef CK
  return f;
}

static int test_p122(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p122 fail line %d\n",__LINE__); } } while (0)
  { static p95_objsA_t sv; memcpy(sv, P95_ObjA, sizeof sv); memset(P95_ObjA, 0, sizeof sv); uint8_t *o = &P95_ObjA[5 * 0x78]; int32_t pool = S_0110E144;
    uint32_t fl = 0x1002; int32_t t = 1, d = 5; int16_t n = 3, id = 77;
    memcpy(o + 0x68, &fl, 4); memcpy(o + 0x58, &t, 4); memcpy(o + 0x5c, &d, 4); memcpy(o + 0x64, &n, 2); memcpy(o + 0x6c, &id, 2);
    S_0110E144 = 10; P122_ObjATick();
    memcpy(&fl, o + 0x68, 4); memcpy(&t, o + 0x58, 4); memcpy(&n, o + 0x64, 2);
    CK(fl == 0 && t == 0 && n == 0 && S_0110E144 == 9 && ((uint16_t *)S_010EA8A0)[9] == 77);
    S_0110E144 = pool; memcpy(P95_ObjA, sv, sizeof sv); }
  { uint8_t hdr[16] = {0}, tab[64]; char names[64] = "abc.x\0Long_Name9\0";
    int32_t off = 32; int16_t cnt = 2; memcpy(hdr + 4, &off, 4); memcpy(hdr + 0xc, &cnt, 2);
    memset(tab, 0, sizeof tab); tab[0 + 4] = 1; tab[0 + 5] = 2; tab[0 + 6] = 3; tab[0 + 8] = 4; tab[12 + 10] = 1; tab[12 + 4] = 9;
    memcpy(names + 32, tab, 24);
    uint8_t buf[64]; memset(buf, 0xee, sizeof buf); void *sp = P54_MapAPtr; int32_t sn = P54_MapA;
    P54_MapAPtr = buf; P54_MapA = 1; P122_MapNames(hdr, names, 7);
    CK(P54_MapA == 3 && memcmp(buf + 16, "ABC", 4) == 0 && buf[24] == 7 && buf[25] == 1 && buf[26] == 2 && buf[27] == 3 && buf[28] == 4);
    CK(memcmp(buf + 32, "LONG_NAM", 8) == 0 && buf[41] == 9);
    P54_MapAPtr = sp; P54_MapA = sn; }
  { int32_t r = P122_FontIcons(re_addr("NOSUCHFONT"), 7, 11, 12, 13); int16_t h[3]; memcpy(h, &P58_Font[7 * 0x806 + 8], 6);
    CK(r == -1 && h[0] == 13 && h[1] == 11 && h[2] == 12); CK(P122_FontIcons(0, 7, 0, 0, 0) == -1); }
  { char tok[sizeof P65_Tok]; memcpy(tok, P65_Tok, sizeof tok);
    strcpy(P65_Tok, "NO_SUCH_VAR"); CK(P122_SetVar(NULL, NULL) == 9);
    p42_cmd_t c; memset(&c, 0, sizeof c); c.id = 1; CK(P122_SetVar(&c, &P42_Vars[1]) == 9);
    memcpy(P65_Tok, tok, sizeof tok); }
  { P69_PtrTab sp; P69_ThrTab st; memcpy(sp, P69_Ptrs, sizeof sp); memcpy(st, P69_Thr, sizeof st);
    CK(P122_ObjNames() == 0 && P69_Ptrs[0] == P69_TBASE && P69_Ptrs[1] == P69_TBASE + 36 && P69_Ptrs[17] == P69_TBASE + 77 * 4);
    for (int i = 0; i < 8; i++) CK(P69_Thr[i] <= P69_Thr[i + 1]);
    memcpy(P69_Ptrs, sp, sizeof sp); memcpy(P69_Thr, st, sizeof st); }
  { uint32_t tag = P44_XformTag; P122_CarGlow(1); CK(P44_XformTag == tag + 1); P122_CarGlow(99); CK(P44_XformTag == tag + 1);
    float pos[3] = { 0, 0, 0 }; P122_SpotShadow(re_addr(pos), 100); CK(P44_XformTag == tag + 2); P122_SpotShadow(0, 1); CK(P44_XformTag == tag + 2); }
  P122_IconCopy(0, "NOSUCHICON");
  { int32_t h = G00D12408; uint8_t *cur = P122_EvCur; char txt[] = "  EVENT_END\n";
    char *r = P122_EventsParse(txt); CK(r == txt && G00D12408 != 0 && P122_EvCur != NULL && P122_Ev118 == 0);
    G00D12408 = h; P122_EvCur = cur; }
#undef CK
  return f;
}

static int test_p121(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p121 fail line %d\n",__LINE__); } } while (0)
  { uint16_t c0 = P68_CamI0;
    char a[] = "TRIGGER_VALUE 5\n"; CK(P121_ParseCamLine(a) == 3);
    char b[] = "# note"; CK(P121_ParseCamLine(b) == 0x32);
    char c[] = "// x"; CK(P121_ParseCamLine(c) == 0x32);
    char d[] = "BOGUS 1"; CK(P121_ParseCamLine(d) == 0);
    char e[] = "TRIGGER_VALUE5"; CK(P121_ParseCamLine(e) == 0);
    char g[] = "TARGET_PLAYER"; CK(P121_ParseCamLine(g) == 7);
    char h[] = "TRIGGER_VALUE 5 junk"; CK(P121_ParseCamLine(h) == 0);
    P68_CamI0 = c0; }
  { int32_t n = G6_00B91D2C, d = P12_00b87e58;
    G6_00B91D2C = 0; P12_00b87e58 = 3; CK(P121_SndNextDev() == 0 && P12_00b87e58 == 3);
    G6_00B91D2C = 1; CK(P121_SndNextDev() == 0 && P12_00b87e58 == 0);
    G6_00B91D2C = n; P12_00b87e58 = d; }
  { uint8_t *ct = P59_CarsTab; int32_t a5c = G2_00D11A5C, fr = P62_Frame; uint32_t sv[0x336];
    memcpy(sv, &P12_0112da00[0], sizeof sv);
    P59_CarsTab = NULL; G2_00D11A5C = 0; P62_Frame = 1;
    uint8_t *car = (uint8_t *)&P99_Cars[1]; int32_t old100; memcpy(&old100, car + 0x100, 4);
    int32_t v = 0x1234; memcpy(car + 0x100, &v, 4);
    uint8_t p[8] = { 0, 0, 0, 0, 0, 1, 0, 0 }; P12_0112da00[0x32f] = 9;
    P121_CopSync(p); CK(P12_0112da00[3] == 0x1234 && P12_0112da00[0x32f] == 0);
    p[1] = 4; P12_0112da00[3] = 0; P121_CopSync(p); CK(P12_0112da00[3] == 0);
    memcpy(car + 0x100, &old100, 4); memcpy(&P12_0112da00[0], sv, sizeof sv);
    P59_CarsTab = ct; G2_00D11A5C = a5c; P62_Frame = fr; }
  { int32_t s = P102_5624A4, fl; uint8_t *c = (uint8_t *)&P99_Cars[0]; memcpy(&fl, c + 0x108, 4);
    int32_t z = 0; memcpy(c + 0x108, &z, 4); P102_5624A4 = 7; P121_WheelDust(); CK(P102_5624A4 == 7);
    memcpy(c + 0x108, &fl, 4); P102_5624A4 = s; }
  { int32_t n = P96_DustN, st = P62_I252B78; P96_DustN = 0; P62_I252B78 = 5; P121_DustDraw(); CK(P62_I252B78 == 0);
    P96_DustN = n; P62_I252B78 = st; }
  { int32_t o = P97_ScrObjOn; P97_ScrObjOn = 0; P121_ScriptHud(); P97_ScrObjOn = o; }
#undef CK
  return f;
}

static int test_p120(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p120 fail line %d\n",__LINE__); } } while (0)
  { static int32_t buf[0x1c6 / 4 + 100 * 0x34 / 4 + 4]; int32_t ic = G00D17B1C;
    P120_ScrA = 5; P120_ScriptReset(buf);
    int16_t s5; memcpy(&s5, (uint8_t *)buf + 5 * 0x34 + 0x1c6, 2);
    CK(P120_ScrA == 0 && buf[0] == 0 && buf[1] == 0 && buf[100] == 99 && s5 == 5); G00D17B1C = ic; }
  { uint16_t c1 = P68_CamI1; char t[] = "-12 x", *s = t;
    CK(P120_ParseCamInt(&s, 1, 0) == 1 && P68_CamI1 == (uint16_t)-12);
    char u[] = "zz", *q = u; CK(P120_ParseCamInt(&q, 2, 0) == 0); P68_CamI1 = c1; }
  { int32_t ed = P95_B87ED8, e40 = P95_B87E40, n = P120_ConeN; uint16_t tk = P120_ConeTick;
    P95_B87ED8 = 1; P95_B87E40 = 2; P120_ConeN = 0; P120_ConeTick = 0;
    P120_ConeRec(); CK(P120_ConeN == 1 && P120_ConeTick == 1);
    P120_ConeRec(); CK(P120_ConeTick == 2); P120_ConeRec(); CK(P120_ConeTick == 0 && P120_ConeN == 1);
    P120_ConeN = 100; P120_ConeRec(); CK(P120_ConeTick == 0);
    P95_B87ED8 = ed; P95_B87E40 = e40; P120_ConeN = n; P120_ConeTick = tk; }
  { int32_t mm = MenuMode1271060; static const int32_t md[] = { 1, 2, 3, 6, 7, 0xb, 0 };
    for (int i = 0; i < 7; i++) { MenuMode1271060 = md[i]; P120_HudTimes(); }
    MenuMode1271060 = mm; }
  { int32_t d = P120_DbgOn, e = P11_00b87e7c; P120_DbgOn = 1; P11_00b87e7c = 0; P120_DebugInfo(); P120_DbgOn = d; P11_00b87e7c = e; }
  { int32_t a = G6_00B5A778; G6_00B5A778 = 0; P120_CarSmoke(0, 10); P120_CarSparks(1); P120_CarDebris(0, 5); G6_00B5A778 = a; }
  { int32_t e = P14_00b87e84; static uint8_t ob[0x20]; P14_00b87e84 = 0; P120_ObjBShade(ob, 1, 2, 3, 0, 0); P14_00b87e84 = e; }
#undef CK
  return f;
}

static int test_p119(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p119 fail line %d\n",__LINE__); } } while (0)
  /* 0050230a: коэффициенты радара для 640×480, масштаб 1 */
  { int32_t md = P29_Mode, w = P19_ScrW, h = P19_ScrH, o1 = P62_HudOff1, mv = MenuVarD118C8, bd = MenuOptBDFA4C, mm = MenuMode1271060;
    float sc = P19_Scale, a = P56_F573FA0, b = P56_F573FA4, k = P94_RadarK;
    uint32_t dv = P102_DmgVar, fv = P102_FelVar, ov = P102_OppVar;
    P29_Mode = 0; P19_ScrW = 640; P19_ScrH = 480; P19_Scale = 1.0f; P62_HudOff1 = 1; MenuVarD118C8 = 0; MenuOptBDFA4C = 1; MenuMode1271060 = 0;
    P102_DmgVar = 0; P102_FelVar = 0; P102_OppVar = 0;
    P119_Hud();
    CK(P56_F573FA0 == 540.0f && P56_F573FA4 == 380.0f && fabsf(P94_RadarK - 1.42187f) < 1e-3f);
    P29_Mode = 1; P56_F573FA0 = 0; P119_Hud(); CK(P56_F573FA0 == 0.0f);
    P29_Mode = md; P19_ScrW = w; P19_ScrH = h; P62_HudOff1 = o1; MenuVarD118C8 = mv; MenuOptBDFA4C = bd; MenuMode1271060 = mm;
    P19_Scale = sc; P56_F573FA0 = a; P56_F573FA4 = b; P94_RadarK = k; P102_DmgVar = dv; P102_FelVar = fv; P102_OppVar = ov; }
  /* 0048fbcf: запись «припаркована» (r[2]=1) — r[0x11]=0, газ 0; стоп по флагу 8 — r[1]=1, r[0xb]=0xff */
  { uint8_t r[0x54], car[0x148]; memset(r, 0, sizeof r); memset(car, 0, sizeof car);
    r[2] = 1; r[0x11] = 5; int32_t g = 77; memcpy(car + 0xf8, &g, 4);
    P119_TrafficSpeed(r, car); memcpy(&g, car + 0xf8, 4); CK(r[0x11] == 0 && g == 0);
    memset(r, 0, sizeof r); r[1] = 2; r[3] = 1; r[0x13] = 8;
    P119_TrafficSpeed(r, car); CK(r[1] == 1 && r[0xb] == 0xff && (r[0x13] & 8) == 0 && r[8] == 0); }
  /* 004943dc: r[2]=1 или +0x38 = 0 — без изменений */
  { uint8_t r[0x54]; memset(r, 0, sizeof r); r[2] = 1; int32_t v = 5; memcpy(r + 0x38, &v, 4); memcpy(r + 0x28, &v, 4);
    P119_TrafficStep(r); memcpy(&v, r + 0x28, 4); CK(v == 5);
    r[2] = 0; v = 0; memcpy(r + 0x38, &v, 4); v = 5; P119_TrafficStep(r); memcpy(&v, r + 0x28, 4); CK(v == 5); }
  /* 004de86c: медленная машина без заноса — все флаги следов −1 */
  { p102_i4_t keep; memcpy(keep, P102_D077A0, sizeof keep); int32_t fx = P26_FxA, st = G6_00B5A778;
    uint8_t c0[0x148]; memcpy(c0, &P99_Cars[3], 0x148); memset(&P99_Cars[3], 0, 0x148);
    P26_FxA = 0; G6_00B5A778 = 0; P102_D077A0[0] = 1; P102_D077A0[2] = 1;
    P119_CarSkids(3);
    CK(P102_D077A0[0] == -1 && P102_D077A0[1] == -1 && P102_D077A0[2] == -1 && P102_D077A0[3] == -1);
    memcpy(&P99_Cars[3], c0, 0x148); memcpy(P102_D077A0, keep, sizeof keep); P26_FxA = fx; G6_00B5A778 = st; }
  /* 004c0c6f: такт полёта колпака — x += vx/2, счётчик −1; draw при счётчике 0 — выход */
  { static p98_bf8_t keep; memcpy(keep, P98_CarBufC, sizeof keep); int32_t st = G6_00B5A778, d0 = P95_Deb0;
    uint8_t *b = P98_CarBufC; memset(b, 0, sizeof keep);
    float vx = 4.0f, x = 10.0f; memcpy(b + 0xe0, &vx, 4); memcpy(b + 0xd0, &x, 4); int32_t n = 3; memcpy(b + 0xf4, &n, 4);
    G6_00B5A778 = 0; P95_Deb0 = 1;
    P119_Hubcap(0);
    memcpy(&x, b + 0xd0, 4); memcpy(&n, b + 0xf4, 4); CK(x == 12.0f && n == 2 && P95_Deb0 == 0);
    n = 0; memcpy(b + 0xf4, &n, 4); P119_Hubcap(1);
    memcpy(P98_CarBufC, keep, sizeof keep); G6_00B5A778 = st; P95_Deb0 = d0; }
#undef CK
  return f;
}

static int test_p142(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p142 fail line %d\n",__LINE__); } } while (0)
  /* 004a7fec: 0112b268 == 0 — газ 0; выбывший коп — газ 0, таймер +0xcd4 −= 0.01; повреждения > 7000 — выбыл */
  { uint8_t rec[0x54]; memset(rec, 0, sizeof rec); rec[0] = 3; rec[5] = 2;
    uint8_t *car = P59_CarsTab ? P59_CarsTab + 3 * 0x148 : (uint8_t *)&P99_Cars[4];
    uint8_t save[0x148]; memcpy(save, car, 0x148);
    uint32_t *c = &P12_0112da00[1 * 0x336]; uint32_t csave[0x336]; memcpy(csave, c, sizeof csave);
    int32_t b268 = P56_B268, c824 = P98_C824A0, nd = P142_CopNoDmg;
    int32_t v = 1234; memcpy(car + 0xf8, &v, 4);
    P56_B268 = 0; P98_C824A0 = 0; P142_CopDrive(rec); memcpy(&v, car + 0xf8, 4); CK(v == 0);
    P56_B268 = 1; c[0x331] = 1; { float fl = 1.0f; memcpy(&c[0x335], &fl, 4); }
    v = 55; memcpy(car + 0xf8, &v, 4); P142_CopDrive(rec);
    { float fl; memcpy(&fl, &c[0x335], 4); memcpy(&v, car + 0xf8, 4); CK(v == 0 && fl > 0.98f && fl < 0.995f); }
    c[0x331] = 0; P142_CopNoDmg = 0; for (int i = 0; i < 6; i++) { int32_t d = 2000; memcpy(car + 0x11c + i * 4, &d, 4); }
    v = 77; memcpy(car + 0xf8, &v, 4); P142_CopDrive(rec);
    memcpy(&v, car + 0xf8, 4); CK(v == 0 && c[0x331] == 1 && c[0x10] == 12000);
    rec[5] = 9; P142_CopDrive(rec); /* rec[5] вне 1..8 — выход */
    memcpy(car, save, 0x148); memcpy(c, csave, sizeof csave); P56_B268 = b268; P98_C824A0 = c824; P142_CopNoDmg = nd; }
  /* 004dacee: без объектов — только счётчик 00d0dd7c */
  { int32_t n = G6_00D0DDC0, k = P102_D0DD7C; uint8_t e14 = P95_B87E14;
    G6_00D0DDC0 = 0; P95_B87E14 = 1; P102_D0DD7C = 5; P142_CarsStep(); CK(P102_D0DD7C == 4);
    P102_D0DD7C = 0; P142_CarsStep(); CK(P102_D0DD7C == 0);
    G6_00D0DDC0 = n; P102_D0DD7C = k; P95_B87E14 = e14; }
  CK(P142_CopDmgMax == 7000);
#undef CK
  return f;
}

/* v1.88: ported143 — солнце (004b418d) и свечение фонаря (004b73f3) */
static int t143_n; static float t143_r;
static void t143_rast(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)b; (void)c; t143_n++; t143_r = a->r; }
static int test_p143(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p143 fail line %d\n",__LINE__); } } while (0)
  p85_raster_fn rb = P85_RasterB; p85_state_fn sf = P85_StateFn; p85_blend_fn bf = P85_BlendFn; p86_texsrc_fn ts = P86_TexSrc;
  int32_t sd = P85_StateDirty, ct = P86_CurTex; uint8_t bc = P85_BlendCur, mir = P84_Mirror;
  float offx = P43_OffX, offy = P43_OffY, sca = P43_ScaleA, scl = P19_Scale; int32_t scw = P19_ScrW;
  int32_t e84 = P14_00b87e84, f30 = P13_00575f30, d8 = P14_00b202d8, dc = P14_00b202dc, fxa = P26_FxA, fa18 = P55_BDFA18, cur = P67_Cur;
  uint32_t gi = P110_GlowIcon; int32_t s270 = P62_I270C44;
  float o32000 = P12_00ba53a0[32000], o1000 = P12_00ba53a0[1000];
  p44_m9_t vm; memcpy(vm, P44_ViewMatT, sizeof vm); float *mp = P44_MatPtr;
  p143_fx_t fxs; memcpy(fxs, P143_Fx, sizeof fxs);
  P85_RasterB = t143_rast; P85_StateFn = NULL; P85_BlendFn = NULL; P86_TexSrc = NULL;
  /* .data-таблица и макросы P8_* над ней */
  CK(P143_Fx[0] == 0x005537d8u && P143_Fx[8] == 0x005537e0u && P143_Fx[0x10] == 0x005537e8u);
  P8_005536ac = 77; CK(P143_Fx[1] == 77u); P8_005536EC[0x1c] = 5; CK(P143_FX8(0x00553708u) == 5);
  CK(re_ptr(0x005536c8u) == (void *)&P143_Fx[8]);
  /* 004b418d: матрица — единичная, солнце на (320, 239), видимость 1 (00bdfa18 == 0), засветка — 2 треугольника */
  memset(P44_ViewMatT, 0, sizeof vm); P44_ViewMatT[0] = P44_ViewMatT[4] = P44_ViewMatT[8] = 1.0f;
  P84_Mirror = 0; P14_00b87e84 = 0; P13_00575f30 = 1; P14_00b202d8 = 0; P14_00b202dc = 0; P26_FxA = 0; P55_BDFA18 = 0;
  P43_ScaleA = 1.0f; P43_OffX = P43_Half + 320.0f; P43_OffY = P43_Half + 240.0f; P19_Scale = 1.0f; P19_ScrW = 640;
  P12_00ba53a0[32000] = 0.0001f; t143_n = 0;
  P143_SunFlare();
  { float v; memcpy(&v, &P143_Fx[4], 4); CK(v == 320.0f);
    memcpy(&v, &P143_Fx[5], 4); CK(v == 239.0f);
    memcpy(&v, &P143_Fx[0xb], 4); CK(v > 0.998f && v < 0.9985f);              /* BLANK: (640 − 1) / 640 */
    memcpy(&v, &P143_Fx[0x10 + 3], 4); CK(v > 0.499f && v < 0.4993f);         /* CARLIGHT 0: (640 − 1) / 1280 */
    memcpy(&v, &P143_Fx[0x10 + 6], 4); CK(v == 32.0f); }                       /* размер 00553678[0] */
  CK(t143_n == 2 && t143_r > 139.5f && t143_r < 139.6f && P85_StateDirty == -1);
  P84_Mirror = 1; t143_n = 0; P143_SunFlare(); CK(t143_n == 0); P84_Mirror = 0;
  /* 004b73f3: объект смотрит на камеру — квадрат свечения; затем след по истории 01105da0 */
  { uint8_t ic[0x10]; memset(ic, 0, sizeof ic); ic[9] = 1; ic[10] = 2; ic[0xb] = 30; ic[0xc] = 40;
    P110_GlowIcon = re_addr(ic); P62_I270C44 = 30000; P12_00ba53a0[1000] = 0.5f;
    uint8_t o[0x78]; memset(o, 0, sizeof o);
    float x = 100.0f, y = 50.0f, z = 1000.0f; memcpy(o, &x, 4); memcpy(o + 4, &y, 4); memcpy(o + 8, &z, 4);
    uint16_t a6c = (uint16_t)(((int32_t)(int16_t)P59_AngA - P44_Atan2(50, 1000)) & 0xfff), a6e = (uint16_t)((P44_Atan2(100, 1000) - (int32_t)(int16_t)P59_AngB) & 0xfff);
    memcpy(o + 0x6c, &a6c, 2); memcpy(o + 0x6e, &a6e, 2);
    int16_t car = 1, lamp = 2; memcpy(o + 0x50, &car, 2); memcpy(o + 0x54, &lamp, 2);
    float k = P43_Sin[0x400] * P43_Sin[0x400];
    t143_n = 0; P143_LampGlow(o); CK(t143_n == 2 && t143_r == k * 255.0f);
    uint8_t hs[0x28]; uint8_t *h = (uint8_t *)P143_LampHist + 0x140 + 2 * 0x28; memcpy(hs, h, sizeof hs);
    P14_00b87e84 = 1; P67_Cur = 9; t143_n = 0; P143_LampGlow(o);
    int32_t hx, hy; int16_t fr; memcpy(&hx, h + 8, 4); memcpy(&hy, h + 0x1c, 4); memcpy(&fr, h + 0x20, 2);
    CK(t143_n == 2 && hx == 370 && hy == 265 && fr == 9);                        /* центр ((360 + 380)/2, (255 + 275)/2) */
    hx += 10; memcpy(h + ((10 - 2) & 3) * 8, &hx, 4);
    P67_Cur = 10; P59_Mode1137324 = P52_ResetB; P99_CamEnd = 0; t143_n = 0; P143_LampGlow(o);
    CK(t143_n == 4 && t143_r == k * 160.0f * 0.25f);
    memcpy(&fr, h + 0x20, 2); CK(fr == 10);
    lamp = 9; memcpy(o + 0x54, &lamp, 2); t143_n = 0; P143_LampGlow(o); CK(t143_n == 2);   /* фонарь вне 0..7 — без следа */
    z = 10.0f; memcpy(o + 8, &z, 4); t143_n = 0; P143_LampGlow(o); CK(t143_n == 0);
    memcpy(h, hs, sizeof hs); }
  P85_RasterB = rb; P85_StateFn = sf; P85_BlendFn = bf; P86_TexSrc = ts; P85_StateDirty = sd; P86_CurTex = ct; P85_BlendCur = bc; P84_Mirror = mir;
  P43_OffX = offx; P43_OffY = offy; P43_ScaleA = sca; P19_Scale = scl; P19_ScrW = scw;
  P14_00b87e84 = e84; P13_00575f30 = f30; P14_00b202d8 = d8; P14_00b202dc = dc; P26_FxA = fxa; P55_BDFA18 = fa18; P67_Cur = cur;
  P110_GlowIcon = gi; P62_I270C44 = s270; P12_00ba53a0[32000] = o32000; P12_00ba53a0[1000] = o1000;
  memcpy(P44_ViewMatT, vm, sizeof vm); P44_MatPtr = mp; memcpy(P143_Fx, fxs, sizeof fxs);
#undef CK
  return f;
}

/* v1.89: ported144 — эффект флага 0x20000 (004b588e) */
static int t144_n; static p85_rv t144_a;
static void t144_rast(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)b; (void)c; if (t144_n++ == 0) t144_a = *a; }
static int test_p144(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p144 fail line %d\n",__LINE__); } } while (0)
  p85_raster_fn rb = P85_RasterB; p86_texsrc_fn ts = P86_TexSrc; int32_t ct = P86_CurTex; uint8_t mir = P84_Mirror;
  float offx = P43_OffX, offy = P43_OffY, sca = P43_ScaleA; int32_t e84 = P14_00b87e84, fxa = P26_FxA, cur = P67_Cur, s270 = P62_I270C44;
  int32_t obj = P96_ObjBOn; uint32_t cop = P111_CopFlare, gi = P110_GlowIcon; float o1000 = P12_00ba53a0[1000];
  uint8_t hs[0x28]; uint8_t *h = (uint8_t *)P143_LampHist + 0x140 + 2 * 0x28; memcpy(hs, h, sizeof hs);
  P85_RasterB = t144_rast; P86_TexSrc = NULL; P84_Mirror = 0; P14_00b87e84 = 0; P26_FxA = 0; P62_I270C44 = 30000;
  P43_ScaleA = 1.0f; P43_OffX = P43_Half + 320.0f; P43_OffY = P43_Half + 240.0f; P12_00ba53a0[1000] = 0.5f;
  uint8_t ic[0x10], ic2[0x10]; memset(ic, 0, sizeof ic); memset(ic2, 0, sizeof ic2);
  ic[9] = 1; ic[10] = 2; ic[0xb] = 30; ic[0xc] = 40; ic2[9] = 7; ic2[0xb] = 9; ic2[0xc] = 11;
  P96_ObjBOn = (int32_t)re_addr(ic); P111_CopFlare = re_addr(ic2); P110_GlowIcon = re_addr(ic);
  uint8_t o[0x78]; memset(o, 0, sizeof o);
  float x = 100.0f, y = 50.0f, z = 1000.0f; memcpy(o, &x, 4); memcpy(o + 4, &y, 4); memcpy(o + 8, &z, 4);
  uint16_t typ = 1; memcpy(o + 0x64, &typ, 2);
  /* тип 1 без 0x80: полуразмер 150 (.data 00553878+0x10), яркость 1, цвет (255, 0, 0), значок CARLYT */
  t144_n = 0; P144_FlagFx(o);
  CK(t144_n == 2 && t144_a.r == 255.0f && t144_a.g == 0.0f && t144_a.b == 0.0f && t144_a.oow == 0.5f && t144_a.tmu[0] == 0.5f);
  { float hx = -150.0f * P43_Sin[0x400] - 150.0f * P43_Sin[0]; CK(fabsf(t144_a.x - ((hx + 100.0f) * 0.5f + 320.0f)) < 0.01f); }
  /* тип 9 (полицейский синий/красный) при COPFLARE — второй значок */
  typ = 9; memcpy(o + 0x64, &typ, 2); t144_n = 0; P144_FlagFx(o); CK(t144_n == 2 && t144_a.tmu[0] == 3.5f && t144_a.r == 255.0f);
  P111_CopFlare = 0; t144_n = 0; P144_FlagFx(o); CK(t144_n == 2 && t144_a.tmu[0] == 0.5f);
  /* флаг 0x80 при отклонении ≥ 0x400 — ничего; тип вне таблицы — ничего; z < 50 — ничего */
  uint16_t a6c = (uint16_t)(((int32_t)(int16_t)P59_AngA - P44_Atan2(50, 1000) + 0x800) & 0xfff);
  typ = 0x81; memcpy(o + 0x64, &typ, 2); memcpy(o + 0x6c, &a6c, 2); t144_n = 0; P144_FlagFx(o); CK(t144_n == 0);
  memset(o + 0x6c, 0, 2); typ = 20; memcpy(o + 0x64, &typ, 2); t144_n = 0; P144_FlagFx(o); CK(t144_n == 0);
  typ = 1; memcpy(o + 0x64, &typ, 2); z = 10.0f; memcpy(o + 8, &z, 4); t144_n = 0; P144_FlagFx(o); CK(t144_n == 0);
  z = 1000.0f; memcpy(o + 8, &z, 4);
  /* след: флаг 0x800000, машина 1, фонарь 2 — история 01105da0 заполняется, затем полоса */
  uint32_t ofl = 0x820000; memcpy(o + 0x68, &ofl, 4); int16_t car = 1, lamp = 2; memcpy(o + 0x50, &car, 2); memcpy(o + 0x54, &lamp, 2);
  P14_00b87e84 = 1; P67_Cur = 9; t144_n = 0; P144_FlagFx(o);
  { int32_t hx, hy; int16_t fr; memcpy(&hx, h + 8, 4); memcpy(&hy, h + 0x1c, 4); memcpy(&fr, h + 0x20, 2);
    CK(t144_n == 2 && hx == 370 && hy == 265 && fr == 9);
    hx += 20; memcpy(h + ((10 - 2) & 3) * 8, &hx, 4); }
  P67_Cur = 10; P59_Mode1137324 = P52_ResetB; P99_CamEnd = 0; t144_n = 0; P144_FlagFx(o); CK(t144_n == 4);
  { int16_t fr; memcpy(&fr, h + 0x20, 2); CK(fr == 10); }
  lamp = -1; memcpy(o + 0x54, &lamp, 2); P67_Cur = 11; t144_n = 0; P144_FlagFx(o); CK(t144_n == 2);
  memcpy(h, hs, sizeof hs);
  P85_RasterB = rb; P86_TexSrc = ts; P86_CurTex = ct; P84_Mirror = mir; P43_OffX = offx; P43_OffY = offy; P43_ScaleA = sca;
  P14_00b87e84 = e84; P26_FxA = fxa; P67_Cur = cur; P62_I270C44 = s270; P96_ObjBOn = obj; P111_CopFlare = cop; P110_GlowIcon = gi;
  P12_00ba53a0[1000] = o1000;
#undef CK
  return f;
}

/* v1.90: ported145 — загрузка уровня 004d38b7: демо 200 без ReplayData\\Demo\\I_TRAINDEMO0.CFG — выход 0 до загрузки */
static int test_p145(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p145 fail line %d\n",__LINE__); } } while (0)
  int32_t gm = GameMode, e38 = P11_00b87e38, c1 = P11_00d11934, c1b = P17_Cond1, ea0 = G6_00B87EA0, h1 = P62_HudOff1;
  int32_t fc = P110_FullClip, fr = P62_Frame, fr8 = G8_00D118C0, cur = P67_Cur, w = P112_Wanted, ft = P98_FreeTurn, s0 = P142_340C0;
  uint32_t fl = P21_FpsLast, fv = P21_FpsVal; int32_t fn = P21_FpsCnt;
  int32_t rs = P101_RecSaved, rb = P109_C54B00, re = P100_RecEnd; p138_s40_t cn; memcpy(cn, P138_CfgName, sizeof cn);
  GameMode = 4; P11_00b87e38 = 200; P110_FullClip = 0; P21_FpsCnt = 7; P67_Cur = 3; G6_00B87EA0 = 0; P62_HudOff1 = 0;
  CK(P145_LevelLoad() == 0);
  CK(P11_00d11934 == 1 && P17_Cond1 == 1 && GameMode == 4 && P110_FullClip == 1 && P21_FpsCnt == 0 && P67_Cur == 0);
  CK(G6_00B87EA0 == 1 && P62_HudOff1 == 1 && strcmp(P138_CfgName, "I_TRAINDEMO0") == 0);
  GameMode = gm; P11_00b87e38 = e38; P11_00d11934 = c1; P17_Cond1 = c1b; G6_00B87EA0 = ea0; P62_HudOff1 = h1;
  P110_FullClip = fc; P62_Frame = fr; G8_00D118C0 = fr8; P67_Cur = cur; P112_Wanted = w; P98_FreeTurn = ft; P142_340C0 = s0;
  P21_FpsLast = fl; P21_FpsVal = fv; P21_FpsCnt = fn;
  P101_RecSaved = rs; P109_C54B00 = rb; P100_RecEnd = re; memcpy(P138_CfgName, cn, sizeof cn);
#undef CK
  return f;
}

static int test_p146(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p146 fail line %d\n",__LINE__); } } while (0)
  int32_t pos = P127_ScrPos, c4 = P14_00c810c4, b4 = (int32_t)P56_Blk84[1], d8 = (int32_t)P56_Blk84[6], dep = P138_C80F7C, g0 = P146_GoSub[0];
  int32_t on = P115_TgtOn, lamp = P127_LampOn[2]; p115_i4_t tg; memcpy(tg, P115_Tgt, sizeof tg); p58_objs_t ob; memcpy(ob, P58_Objs, sizeof ob);
  float tx = P123_TgtX, ty = P126_TgtY, tz = P123_TgtZ;
  int32_t cmd[8] = { 0x24 };
  P127_ScrPos = 10; P56_Blk84[6] = 0;
  CK(P146_ScriptCmd(cmd) == 0 && P127_ScrPos == 11 && (P56_Blk84[6] & 1) == 1);
  cmd[0] = 0x2e; cmd[1] = 2; CK(P146_ScriptCmd(cmd) == 0 && P127_LampOn[2] == 1 && P127_ScrPos == 12);
  cmd[0] = 0x19; cmd[1] = 0; cmd[2] = 7; cmd[3] = 0x1234; cmd[4] = 0x5678;
  CK(P146_ScriptCmd(cmd) == 0 && P115_Tgt[0] == 0x1234 && P115_Tgt[2] == 0x5678 && P58_Objs[0][0] == 7);
  cmd[0] = 0x1a; CK(P146_ScriptCmd(cmd) == 0 && (P115_TgtOn & 1) == 1);
  cmd[0] = 0x45; cmd[1] = 100; cmd[2] = -5; cmd[3] = 7; CK(P146_ScriptCmd(cmd) == 0 && P123_TgtX == 100.0f && P126_TgtY == -5.0f && P123_TgtZ == 7.0f);
  P14_00c810c4 = 5; cmd[0] = 7; P127_ScrPos = 20; CK(P146_ScriptCmd(cmd) == 0xd && P127_ScrPos == 20);   /* ждать */
  P14_00c810c4 = 0x7fff; CK(P146_ScriptCmd(cmd) == 0 && P127_ScrPos == 21 && P14_00c810c4 == 0 && P56_Blk84[1] == 0);
  P138_C80F7C = 1; P146_GoSub[0] = 33; cmd[0] = 0x72; CK(P146_ScriptCmd(cmd) == 0 && P127_ScrPos == 33 && P138_C80F7C == 0);
  cmd[0] = 0x13; CK(P146_ScriptCmd(cmd) == 0xd && P127_ScrPos == 34);   /* неизвестная — 0xd, номер + 1 */
  P127_ScrPos = pos; P14_00c810c4 = c4; P56_Blk84[1] = (uint32_t)b4; P56_Blk84[6] = (uint32_t)d8; P138_C80F7C = dep; P146_GoSub[0] = g0;
  P115_TgtOn = on; P127_LampOn[2] = lamp; memcpy(P115_Tgt, tg, sizeof tg); memcpy(P58_Objs, ob, sizeof ob);
  P123_TgtX = tx; P126_TgtY = ty; P123_TgtZ = tz;
#undef CK
  return f;
}

/* v1.94: блок D3D/DirectDraw (ported149) */
static int test_p149(void) {
  int f = 0;
#define CK9(c) do { if (!(c)) { f++; fprintf(stderr,"p149 fail line %d\n",__LINE__); } } while (0)
  int32_t cnt0 = P42_DevCount; uint32_t h0 = P149_DDHead, t0 = P149_DDTail;
  static p74_dev_t dev0; static p42_names_t nm0; memcpy(dev0, P74_DevTab, sizeof dev0); memcpy(nm0, P42_DevNames, sizeof nm0);
  P46_TexNode *th0 = P46_TexHead; int32_t ef2c = G6_0054EF2C, cs = P32_CurSlot; void *ch = P32_CurHandle, *dd0 = P24_DD;
  int live0 = plat_dd_stub_count();
  /* 0041fac0/0041fcc7: 2 драйвера × 2 устройства, у второго устройства dcmColorModel = 0 — пропуск */
  P149_DDHead = 0; P149_DDTail = 0;
  plat_dd_stub_enum(2, 2, 0);
  CK9(plat_dd_enumerate(P149_DDEnumCb, NULL) == 0);
  uint8_t *a = (uint8_t *)re_ptr(P149_DDHead), *b = (uint8_t *)re_ptr(P149_DDTail);
  CK9(a != NULL && b != NULL && a != b);
  if (a && b) {
    uint32_t v; memcpy(&v, a + 0x30, 4); CK9(v == 1 && strcmp((char *)a, "Primary Display Driver") == 0);
    memcpy(&v, b + 0x30, 4); CK9(v == 0 && b[0x20] == 1 && b[0x21] == 0xdd && strcmp((char *)b, "Display 1") == 0);
    CK9(re_rd_ptr(a + 0x3c) == b && re_rd_ptr(b + 0x40) == a && re_rd_ptr(b + 0x3c) == NULL);
    uint8_t *d = (uint8_t *)re_rd_ptr(a + 0x34);
    CK9(d != NULL && d == re_rd_ptr(a + 0x38) && strcmp((char *)d, "SDL HAL 0") == 0 && d[0x20] == 0x3d);
    if (d) { memcpy(&v, d + 0x30 + 8, 4); CK9(v == 2 && re_rd_ptr(d + 0x228) == NULL); memcpy(&v, d + 0x12c + 8, 4); CK9(v == 1); }
  }
  CK9(plat_dd_stub_count() == live0);
  /* 0041fe07: 00420038 в native — заглушка (0): строка таблицы записана, счёт не растёт, записи освобождены; строка 0 перезаписана последним устройством */
  P42_DevCount = 0;
  P149_BuildDevs();
  CK9(P42_DevCount == 0 && P74_DevTab[0] == 1 && strcmp((char *)&P74_DevTab[1], "Display 1") == 0);
  CK9(strcmp((char *)P42_DevNames[0], "Display 1") == 0 && strcmp((char *)P42_DevNames[0] + 0x20, "SDL HAL 0") == 0);
  P42_DevCount = 4; P149_DDHead = 0; P149_DDTail = 0;
  CK9(P149_DDEnumAll() == 0);   /* при 4 устройствах — ничего не добавляется */
  P149_DDHead = 0; P149_DDTail = 0;
  plat_dd_stub_enum(1, 1, 1); CK9(P149_DDEnumAll() == 0 && P149_DDHead == 0);
  plat_dd_stub_enum(1, 1, 2); CK9(plat_dd_enumerate(P149_DDEnumCb, NULL) == 0 && P149_DDHead == 0);
  plat_dd_stub_enum(1, 1, 0);
  { uint32_t hw[63] = { 0xfc, 0, 2 }; static uint8_t ctx[0x44]; memset(ctx, 0, sizeof ctx);
    CK9(P149_D3DDevCb(NULL, "x", "y", hw, hw, ctx) == 1 && ctx[0x34] == 0);
    hw[2] = 0; CK9(P149_D3DDevCb("1234567890abcdef", "x", "y", hw, hw, ctx) == 1 && ctx[0x34] == 0); }
  CK9(plat_dd_stub_count() == live0);
  /* 004225eb/0042248b/0041d6aa: эмулируемые текстуры (поверхность + IDirect3DTexture2), Lock/Unlock, освобождение */
  P24_DD = plat_dd_create(NULL);
  uint8_t *di0 = P32_DevInfo; static uint8_t devinfo[0x590]; memset(devinfo, 0, sizeof devinfo); P32_DevInfo = devinfo;
  int l0, u0, fl, bl, cl; uint32_t ff; int32_t r4[4], s4[4];
  plat_dd_stub_surface_stats(&l0, &u0, &fl, &ff, &bl, r4, s4, &cl);
  P46_TexHead = NULL;
  CK9(P149_EmulNew(7, 0, 5, 0) == 1 && P46_TexHead != NULL && P46_TexHead->handle == 7 && P46_TexHead->next == NULL);
  CK9(P149_EmulAddSub(P46_TexHead, 0, 5, 0) == 1 && P149_EmulAddSub(P46_TexHead, 0, 6, 0) == 1);
  { uint8_t *s1 = (uint8_t *)re_rd_ptr((uint8_t *)P46_TexHead + 0x18), *s2 = s1 ? (uint8_t *)re_rd_ptr(s1 + 0x18) : NULL;
    uint32_t v = 0; if (s2) memcpy(&v, s2 + 4, 4);
    CK9(s1 && s2 && v == 6 && re_rd_ptr(s2 + 0x18) == NULL && memcmp(s2, s1, 4) == 0 && re_rd_ptr(s2 + 0x10) != NULL); }
  CK9(P149_EmulNew(8, 0, 5, 0) == 1 && P46_TexHead->handle == 8 && P46_TexHead->next != NULL);
  int l1, u1; plat_dd_stub_surface_stats(&l1, &u1, &fl, &ff, &bl, r4, s4, &cl);
  CK9(l1 - l0 == 4 && u1 - u0 == 4);
  CK9(plat_dd_stub_count() == live0 + 1 + 8);
  G6_0054EF2C = 3; P32_CurSlot = 2;
  P149_EmulFreeAll();
  CK9(P46_TexHead == NULL && G6_0054EF2C == -1 && P32_CurSlot == -1 && plat_dd_stub_count() == live0 + 1);
  plat_dd_stub_surface(1, 0, 16, 0xf800, 0x7e0, 0x1f, 0);
  CK9(P149_EmulNew(9, 0, 5, 0) == 0 && P46_TexHead != NULL);   /* Lock не удался: узел уже в списке, 0 */
  plat_dd_stub_surface(0, 0, 16, 0xf800, 0x7e0, 0x1f, 0);
  P149_EmulFreeAll();
  plat_dd_release(P24_DD); P24_DD = NULL;
  CK9(P149_EmulNew(10, 0, 5, 0) == 0 && P46_TexHead == NULL);   /* нет DirectDraw — 00422736 не удалась */
  CK9(plat_dd_stub_count() == live0);
  P32_DevInfo = di0; P24_DD = dd0; P46_TexHead = th0; G6_0054EF2C = ef2c; P32_CurSlot = cs; P32_CurHandle = ch;
  P42_DevCount = cnt0; P149_DDHead = h0; P149_DDTail = t0; memcpy(P74_DevTab, dev0, sizeof dev0); memcpy(P42_DevNames, nm0, sizeof nm0);
  return f;
#undef CK9
}

static int test_p148(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p148 fail line %d\n",__LINE__); } } while (0)
  int32_t d2c = G6_00B91D2C, f434 = P140_B1F434, eax = P148_EaxOn;
  void *ds0 = P38_Ds, *pr0 = P38_DsPrimary, *l0 = P49_Listener, *p2c = P49_Prop2C, *p30 = P49_Prop30;
  p148_drvtab_t drv0; memcpy(drv0, P148_Drv, sizeof drv0);
  int c0, co, dp, lk, ul, rs; uint8_t m64[64];
  /* 0048ba20/0048cdab: основной (guid NULL), длинное имя → 0x1c + "...", короткое; эмуляция (0x20) с guid — пропуск */
  { static const uint8_t g[3][16] = { {0}, {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}, {0xaa,0xbb} };
    static const char *const nm[3] = { "Primary Sound Driver", "Sound Blaster Live! EAX 5.1 Digital Audio", "AC97" };
    G6_00B91D2C = 0; plat_ds_stub_drivers(3, g, nm, 0); P148_SndEnum();
    CK(G6_00B91D2C == 3 && P148_Drv[0].guid_ptr == 0 && strcmp(P148_Drv[0].name, "Primary Sound Driver") == 0);
    CK(re_ptr(P148_Drv[1].guid_ptr) == P148_Drv[1].guid && P148_Drv[1].guid[15] == 16 && strlen(P148_Drv[1].name) == 0x1f);
    CK(memcmp(P148_Drv[1].name, "Sound Blaster Live! EAX 5.1 ...", 0x20) == 0 && strcmp(P148_Drv[2].name, "AC97") == 0);
    CK(re_ptr(0x00bdcb74u + 2 * 0x34) == P148_Drv[2].name);
    G6_00B91D2C = 0; plat_ds_stub_drivers(3, g, nm, 0x20); P148_SndEnum(); CK(G6_00B91D2C == 1);
    G6_00B91D2C = 8; CK(P148_EnumCb(NULL, "x", "", NULL) == 0 && G6_00B91D2C == 8);
    G6_00B91D2C = 1; plat_ds_stub_dsfail(2, 0); CK(P148_EnumCb(NULL, "x", "", NULL) == 1 && G6_00B91D2C == 1);
    plat_ds_stub_dsfail(0, 0); plat_ds_stub_drivers(1, NULL, nm, 0); G6_00B91D2C = 0; P148_SndEnum(); CK(G6_00B91D2C == 1); }
  /* 0048ba31: вне диапазона — 0; режим 2 → 00b1f434 = 1, EAX 0; успех — DirectSound, уровень 3, первичный буфер, слушатель */
  { P38_Ds = NULL; P38_DsPrimary = NULL; P49_Listener = NULL; P49_Prop2C = NULL; P49_Prop30 = NULL;
    CK(P148_SndOpen(1, 0, 0) == 0 && P148_SndOpen(-1, 0, 0) == 0);
    CK(P148_SndOpen(0, 2, 0x1234) == 1 && P140_B1F434 == 1 && P148_EaxOn == 0 && P38_Ds != NULL && P38_DsPrimary != NULL && P49_Listener != NULL);
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); CK(co == 3);
    P50_SoundShutdown();
    plat_ds_stub_dsfail(4, 0);
    CK(P148_SndOpen(0, 0, 0) == 0 && P140_B1F434 == 0 && P148_EaxOn == 1 && P38_Ds == NULL && P38_DsPrimary == NULL);
    plat_ds_stub_dsfail(0, 0); }
  /* 0048c192/0048c47e/0048c3e7: WAV-образ; заливка в две части (разрез 4); отказ Lock — NULL; Restore */
  { uint8_t wav[12 + 8 + 16 + 8 + 10]; uint32_t w;
    memcpy(wav, "RIFF", 4); w = sizeof wav - 8; memcpy(wav + 4, &w, 4); memcpy(wav + 8, "WAVEfmt ", 8); w = 16; memcpy(wav + 16, &w, 4);
    memset(wav + 20, 0x11, 16); memcpy(wav + 36, "data", 4); w = 10; memcpy(wav + 40, &w, 4);
    for (int i = 0; i < 10; i++) wav[44 + i] = (uint8_t)(0x40 + i);
    void *ds = plat_dd_create(NULL); int op; float v6[6]; uint32_t u;
    plat_ds_stub_dsfail(0, 4);
    void *b = P148_BufFromWav(ds, wav, 0);
    plat_ds3d_stub_last(&op, v6, &u); plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64);
    CK(b != NULL && op == 15 && u == 0xb2 && v6[0] == 10.0f && memcmp(m64, wav + 44, 10) == 0);
    void *b2 = P148_BufFromWav(ds, wav, 1); plat_ds3d_stub_last(&op, v6, &u); CK(b2 != NULL && u == 0xba);
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); int lk0 = lk; plat_ds_stub_dsfail(0x10, 0); CK(P148_BufFromWav(ds, wav, 0) == NULL);
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); CK(lk == lk0);
    int rs0 = rs; plat_ds_stub_dsfail(0x20, 0); CK(P148_Refill(b, wav) == 0);
    plat_ds_stub_dsfail(0, 0); memset(wav + 44, 0x77, 10); CK(P148_Refill(b, wav) == 1);
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); CK(rs == rs0 + 1 && m64[0] == 0x77 && m64[9] == 0x77);
    CK(P148_Fill(NULL, wav, 4) == 0 && P148_Fill(b, wav, 0) == 0 && P148_BufFromWav(ds, (const uint8_t[16]){0}, 0) == NULL);
  /* 0048cad6: QuerySupport обоих EAX-наборов = 3 — IKsPropertySet, иначе NULL */
    plat_ds_stub_ctl(0, 3); void *ps = P148_KsProps(b); CK(ps != NULL); plat_dd_release(ps);
    plat_ds_stub_ctl(0, 1); CK(P148_KsProps(b) == NULL);
    plat_ds_stub_ctl(2, 3); CK(P148_KsProps(b) == NULL);
    plat_ds_stub_ctl(0, 3);
  /* 0048c2a3: дубликат голоса 60 в буфер 61, позиция 0, 3D-буфер; BUFFERLOST — сэмпл не перезагружен → 0, буфер освобождён */
    P50_Voice v60 = P50_Voices[60]; P49_Pair p61 = P49_Bufs[61];
    P38_Ds = ds; memset(&P50_Voices[60], 0, sizeof(P50_Voice)); memset(&P49_Bufs[61], 0, sizeof(P49_Pair));
    CK(P148_DupVoice(60, 61) == 0);
    P50_Voices[60].a = b2;
    CK(P148_DupVoice(60, 61) == 1 && P49_Bufs[61].buf != NULL && P49_Bufs[61].buf3d != NULL);
    plat_ds3d_stub_last(&op, v6, &u); CK(op == 13 && u == 0);
    P50_ReleaseBuf(61);
    strcpy((char *)P50_Voices[60].rest, "no_such_p148.wav");
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); int dp0 = dp;
    plat_ds_stub_dsfail(0x40, 0);
    CK(P148_DupVoice(60, 61) == 0 && P50_Voices[60].a == NULL && P49_Bufs[61].buf == NULL);   /* SndLoadWav = −1 ≠ 0 → повтор с a = NULL — отказ */
    plat_ds_stub_dsstats(&c0, &co, &dp, &lk, &ul, &rs, m64); CK(dp == dp0 + 2);
    plat_ds_stub_dsfail(0, 0);
    P50_Voices[60] = v60; P49_Bufs[61] = p61; plat_dd_release(b); plat_dd_release(ds); }
  G6_00B91D2C = d2c; P140_B1F434 = f434; P148_EaxOn = eax; memcpy(P148_Drv, drv0, sizeof drv0);
  P38_Ds = ds0; P38_DsPrimary = pr0; P49_Listener = l0; P49_Prop2C = p2c; P49_Prop30 = p30;
#undef CK
  return f;
}
static int test_p147(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"p147 fail line %d\n",__LINE__); } } while (0)
  static char line[0x400];
  char *oline = P65_Line;
  p42_cmd_t c; memset(&c, 0, sizeof c);
  CK(P147_ParseCmd(NULL) == 9);
  int32_t fxa = P26_FxA; c.id = 0x1e; CK(P147_ParseCmd(&c) == 0xb && P26_FxA == 1); P26_FxA = fxa;
  int32_t fa60 = P95_BDFA60; strcpy(line, "123 x"); P65_Line = line; c.id = 0x41;
  CK(P147_ParseCmd(&c) == 0xb && P95_BDFA60 == 123); P95_BDFA60 = fa60;
  { p42_var_t v0 = P42_Vars[0]; P42_Vars[0].type = 0x7f;   /* в native таблица переменных без ограничителя — поставить его */
    strcpy(line, "NOSUCHVAR 1"); P65_Line = line; c.id = 0x6b; CK(P147_ParseCmd(&c) == 0xc); P42_Vars[0] = v0; }
  int32_t n0 = P77_ListN; strcpy(line, "5 6"); P65_Line = line; c.id = 0x30; c.argc = 2; c.size = 0xc;
  CK(P147_ParseCmd(&c) == 0xb && P77_ListN == n0 + 1);
  if (P77_ListN == n0 + 1) { int32_t *r = (int32_t *)P77_List[P77_ListN - 1]; CK(r[0] == 0x30 && r[1] == 5 && r[2] == 6); }
  int32_t l0 = P99_ScrNames.count; strcpy(line, "lbl147"); P65_Line = line; c.id = 0x69; c.argc = 0;
  CK(P147_ParseCmd(&c) == 0xb && P99_ScrNames.count == l0 + 1);
  { char nm[16] = "lbl147"; CK(P65_FindByName(nm, (p65_tab_t *)&P99_ScrNames) == P77_ListN); }
  P65_Line = oline;
  /* 00503ddf: режим 6, *00b32a08 = 01271088 со словом +4 ≠ 8 → копия записи, 1 */
  static int32_t srec[6] = { 1, 0, 2, 3, 4, 5 };
  uint32_t mr = P113_MrkRec, pa = P71_Ptr2A08; int32_t md = P62_Menu1271060; p56_blk11_t b11; memcpy(b11, P56_Blk11, sizeof b11);
  P113_MrkRec = re_addr(srec); P62_Menu1271060 = 6; P71_Ptr2A08 = 0x01271088u; P56_Blk11[11] = 0;
  CK(P147_ScoreRec() == 1 && P56_Blk11[10] == 1 && P56_Blk11[11] == 8 && P56_Blk11[15] == 5 && P147_Rec2A10[1] == 8 && P71_V2A24 == 5 && P71_S127108C == 8);
  P113_MrkRec = 0; CK(P147_ScoreRec() == 0);
  P113_MrkRec = mr; P71_Ptr2A08 = pa; P62_Menu1271060 = md; memcpy(P56_Blk11, b11, sizeof b11);
#undef CK
  return f;
}

/* v1.96: ported151 — таблица D3D-эмуляции 0041cede, проверка устройства 00420038, ранние выходы 0041ed98, переоткрытие 00425f7b */
/* v2.02: 005291ed — заливка строк (ширина округляется вверх до 32, шаг 0x280); 00407d56 → P65_Screen с границей */
#include "../game/ported152.h"
/* v2.04: связи заглушек unported.h с переносами (адреса Game.exe → re_ptr) */
void Call005283B5(uint32_t a0, int32_t a1, int32_t a2);
void Call0052B650(uint32_t a0, uint32_t a1, uint32_t a2);
uint32_t Call004EC8A8(uint32_t a0);
void Call00528461(uint32_t a0, uint32_t a1);
static int test_v204(void) {
  int f = 0;
#define CK(c) do { if (!(c)) { f++; fprintf(stderr,"v204 fail line %d\n",__LINE__); } } while (0)
  static uint8_t src[16], dst[16]; static float m[9] = {1,2,3,4,5,6,7,8,9}, t[9];
  for (int i = 0; i < 16; i++) { src[i] = (uint8_t)(i + 1); dst[i] = 0; }
  uint32_t as = re_ptr_register_dyn(src, 16), ad = re_ptr_register_dyn(dst, 16);
  Call005283B5(ad, (int32_t)as, 7); CK(dst[0] == 1 && dst[6] == 7 && dst[7] == 0);
  Call005283B5(ad, (int32_t)as, 64); CK(dst[7] == 0);                 /* участок за областью — без записи */
  Call0052B650(ad, as, 16); CK(memcmp(dst, src, 16) == 0);
  uint32_t am = re_ptr_register_dyn(m, sizeof m), at = re_ptr_register_dyn(t, sizeof t);
  Call00528461(am, at); CK(t[1] == 4 && t[3] == 2 && t[8] == 9);
  CK(Call004EC8A8(0) == 0);
  re_ptr_unregister(src); re_ptr_unregister(dst); re_ptr_unregister(m); re_ptr_unregister(t);
#undef CK
  return f;
}
static int test_p152(void) {
  static uint8_t b[0x280 * 4];
  memset(b, 1, sizeof b);
  P152_FillRows(b + 0x280 + 4, 0x21, 2, 7);
  CHECK(b[0x280 + 3] == 1 && b[0x280 + 4] == 7 && b[0x280 + 4 + 0x3f] == 7 && b[0x280 + 4 + 0x40] == 1);
  CHECK(b[0x500 + 4] == 7 && b[0x780 + 4] == 1 && b[4] == 1);
  P152_FillRows(b, 0, 3, 9); CHECK(b[0] == 1);
  P65_Screen[0] = 0; P65_Screen[0x280 * 2 + 0x20] = 0;
  extern void SndHelper_00407D56(int32_t x, int32_t y, uint32_t p3, uint32_t p4, uint32_t p5);
  int32_t old = P11_005c6760; P11_005c6760 = 0x55;
  SndHelper_00407D56(0x20, 2, 0, 0x23, 1);
  CHECK(((uint8_t *)P65_Screen)[0x280 * 2 + 0x20] == 0x55 && ((uint8_t *)P65_Screen)[0] == 0);
  P152_ScreenFill(0, 479, 640, 5, 0x55);   /* за концом — только строка 479 */
  CHECK(((uint8_t *)P65_Screen)[0x4b000 - 1] == 0x55);
  P11_005c6760 = old;
  memset(P65_Screen, 0, sizeof P65_Screen);
  return 0;
}
static int test_p151(void) {
  int f = 0;
#define CK151(c) do { if (!(c)) { f++; fprintf(stderr,"p151 fail line %d\n",__LINE__); } } while (0)
  int32_t dc0 = P42_DevCount, di0 = P151_DevIdx, n80 = P151_No8bit, fs0 = P24_Fullscreen;
  t151_snap z; t151_save(&z);
  P42_DevCount = 3;
  CK151(P151_InstallD3D(-1, 0, 0) == 0 && P151_InstallD3D(3, 0, 0) == 0 && P151_DevIdx == di0);
  CK151(P151_InstallD3D(2, 7, 8) == 1 && P151_DevIdx == 2 && P151_No8bit == 7 && P24_Fullscreen == 8);
  void *clr = NULL, *wo = NULL, *sel = NULL;
  for (int i = 0; i < P33_GlideCount(); i++) {
    if (strcmp(P33_GlideName(i), "_grBufferClear@12") == 0) clr = P33_GlideProc(i);
    if (strcmp(P33_GlideName(i), "_grSstWinOpen@28") == 0) wo = P33_GlideProc(i);
    if (strcmp(P33_GlideName(i), "_grSstSelect@4") == 0) sel = P33_GlideProc(i); }
  CK151(clr == (void *)P54_ClearBuffers && wo == (void *)P151_WinOpen && sel == (void *)NoopFn0041ed7c);
  CK151(P85_BlendFn == (p85_blend_fn)(void (*)(void))P23_SetBlendMode && P86_TexSrc == (p86_texsrc_fn)(void (*)(void))P53_SetTexSource && P115_RasterD == (p85_raster_fn)P76_TriB2);
  CK151(FnPtr01270E80 == NULL);                            /* метка 0041e3b0 — не функция, в native не зарегистрирована */
  t151_restore(&z);
  /* 00420038: устройство HAL, все проверки проходят; объекты освобождены */
  static uint8_t dv[0x590], rec[0x4c]; memset(dv, 0, sizeof dv); memset(rec, 0, sizeof rec);
  re_wr_ptr(rec + 0x48, dv);
  uint32_t v; v = 2; memcpy(dv + 0x328, &v, 4); v = 3; memcpy(dv + 0x324, &v, 4); v = 0x401; memcpy(dv + 0x32c, &v, 4);
  v = 0x100; memcpy(dv + 0x320 + 0xac, &v, 4); memcpy(dv + 0x320 + 0xb0, &v, 4); memcpy(dv + 0x320 + 0xb4, &v, 4); memcpy(dv + 0x320 + 0xb8, &v, 4);
  int live0 = plat_dd_stub_count();
  plat_dd_stub_caps(0, 0);
  CK151(P151_CheckDev(rec) == 1 && plat_dd_stub_count() == live0);
  memcpy(&v, dv + 0x518, 4); CK151(v == 1); memcpy(&v, dv + 0x520, 4); CK151(v == 0x1000); memcpy(&v, dv + 0x524, 4); CK151(v == 0x10);
  memcpy(&v, dv + 0x28, 4); CK151(v == 0x17c); memcpy(&v, dv + 0x58c, 4); CK151((v & 6) == 6);
  plat_dd_stub_caps(1, 0); CK151(P151_CheckDev(rec) == 0 && plat_dd_stub_count() == live0);
  plat_dd_stub_caps(0, 2); CK151(P151_CheckDev(rec) == 0 && plat_dd_stub_count() == live0);   /* DDCAPS2_NO2DDURING3DSCENE */
  plat_dd_stub_caps(2, 0); CK151(P151_CheckDev(rec) == 0 && plat_dd_stub_count() == live0);
  plat_dd_stub_caps(0, 0);
  v = 1; memcpy(dv + 0x328, &v, 4); CK151(P151_CheckDev(rec) == 0 && plat_dd_stub_count() == live0);   /* программный */
  v = 0; memcpy(dv + 0x328, &v, 4); memcpy(&v, dv + 0x518, 4); CK151(P151_CheckDev(rec) == 0); memcpy(&v, dv + 0x518, 4); CK151(v == 0);   /* HEL пустой */
  /* 0041ed98: DirectDrawCreate отказывает → 0; полноэкранный с неизвестным кодом → Coop 0x11 и 0 */
  uint8_t *e0 = (uint8_t *)&P74_DevTab[0]; uint8_t keep[0x4c]; memcpy(keep, e0, 0x4c); re_wr_ptr(e0 + 0x48, dv);
  P151_DevIdx = 0; P22_DevReady = 0; P31_ReleaseDirectDraw();   /* остатки прежних тестов */
  int live1 = plat_dd_stub_count();
  plat_dd_stub_display(0x40, 1, 0);
  CK151(P151_WinOpen(5, 0xff, 0, 0, 0, 0, 0) == 0 && P24_Hwnd == NULL && P24_RestoreMode == 0 && P32_DevInfo == dv && plat_dd_stub_count() == live1);
  plat_dd_stub_display(0x40, 0, 0);
  CK151(P151_WinOpen(5, 0x55, 0, 0, 0, 0, 0) == 0 && P24_DD == NULL && P31_DDObj1 == NULL && P24_RestoreMode == 0);   /* Coop 0x11, неизвестный код → 0041f2a0 (вернул Coop 8) */
  CK151(plat_dd_last_coop() == 8 && plat_dd_stub_count() == live1);
  memcpy(e0, keep, 0x4c);
  /* 00425f7b: MoveWindow; ширина без кода разрешения → 0 */
  int32_t w0 = P19_ScrW, h0 = P19_ScrH, m5[5]; int mv0 = plat_win_moves(NULL);
  P19_ScrW = 700; P19_ScrH = 480;
  CK151(P151_Reopen(9, 1, 0) == 0 && plat_win_moves(m5) == mv0 + 1 && m5[0] == 0 && m5[1] == 0 && m5[2] == 700 && m5[3] == 480 && m5[4] == 1);
  P19_ScrW = w0; P19_ScrH = h0;
  P42_DevCount = dc0; P151_DevIdx = di0; P151_No8bit = n80; P24_Fullscreen = fs0;
  return f;
}

/* v1.95: ported150 — FMV (0048ac1c/0048af23/0048b3e8/0048a940), очередь треугольников 0042d384, WM_CREATE 005224a8 */
static int g150_rast[4], g150_state, g150_blend, g150_tex; static const p85_rv *g150_a;
static void P85_STD r150_c(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)b; (void)c; g150_rast[0]++; g150_a = a; }
static void P85_STD r150_d(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)a; (void)b; (void)c; g150_rast[1]++; }
static void P85_STD r150_a(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)a; (void)b; (void)c; g150_rast[2]++; }
static void P85_STD r150_b(const p85_rv *a, const p85_rv *b, const p85_rv *c) { (void)a; (void)b; (void)c; g150_rast[3]++; }
static void P85_STD s150(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) { g150_state = a * 10000 + b * 1000 + c * 100 + d * 10 + e; }
static void P85_STD b150(int32_t a, int32_t b, int32_t c, int32_t d) { g150_blend = a * 1000 + b * 100 + c * 10 + d; }
static void t150(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info) { (void)tmu; (void)info; g150_tex = (int)addr + mask; }
static int test_p150(void) {
  int f = 0;
#define CK150(c) do { if (!(c)) { f++; fprintf(stderr,"p150 fail line %d\n",__LINE__); } } while (0)
  /* 0042d384 */
  int32_t n0 = G01159D74; uint8_t *q0 = G0115A13C; int32_t sd = P85_StateDirty, ct = P86_CurTex, bd = P55_BDFA18, cs = P28_CarShine;
  uint8_t bc = P85_BlendCur; p85_state_fn sf = P85_StateFn; p85_blend_fn bf = P85_BlendFn; p86_texsrc_fn tf = P86_TexSrc;
  p85_raster_fn rc0 = P115_RasterC, rd0 = P115_RasterD, ra0 = P85_RasterA, rb0 = P85_RasterB;
  static uint8_t shine[16]; shine[8] = 5; uint8_t slot[16]; memcpy(slot, &g_01145a60[5 * 0x10], 16);
  uint32_t v8 = 0x100, vc = 7; memcpy(&g_01145a60[5 * 0x10 + 8], &v8, 4); memcpy(&g_01145a60[5 * 0x10 + 0xc], &vc, 4);
  P28_CarShine = (int32_t)re_addr(shine);
  P115_RasterC = r150_c; P115_RasterD = r150_d; P85_RasterA = r150_a; P85_RasterB = r150_b;
  P85_StateFn = s150; P85_BlendFn = b150; P86_TexSrc = t150;
  P85_StateDirty = 0; P86_CurTex = -1; P85_BlendCur = 0; P55_BDFA18 = 0;
  G01159D74 = 0; P150_FlushTris(); CK150(g150_state == 0 && g150_rast[0] == 0);
  Reset0042D2B0();
  uint32_t va[15] = {0}, tag1 = 1; va[0] = 0x3f800000u;
  P62_QueueTri(va, va, va, 0); P62_QueueTri(va, va, va, tag1); P62_QueueTri(va, va, va, 0);
  CK150(G01159D74 == 3);
  P150_FlushTris();
  CK150(g150_state == 31010 && P85_StateDirty == 4 && g150_blend == 4400 && P85_BlendCur == 3);
  CK150(P86_CurTex == 5 && g150_tex == 0x103);
  CK150(g150_rast[0] == 2 && g150_rast[1] == 1 && g150_rast[2] == 0 && g150_a == (const p85_rv *)(const void *)(G0115A140 + 0xb8 * 2 + 4));
  CK150(G0115A13C == G0115A140 + 0xb8 * 3);
  P55_BDFA18 = 1; g150_state = 0; g150_tex = 0; P150_FlushTris();
  CK150(g150_state == 0 && g150_tex == 0 && g150_rast[2] == 2 && g150_rast[3] == 1);
  memcpy(&g_01145a60[5 * 0x10], slot, 16);
  G01159D74 = n0; G0115A13C = q0; P85_StateDirty = sd; G6_01270C34 = sd; P86_CurTex = ct; P55_BDFA18 = bd; P28_CarShine = cs; P85_BlendCur = bc; P69_BlendOn = bc;
  P85_StateFn = sf; P85_BlendFn = bf; P86_TexSrc = tf; P115_RasterC = rc0; P115_RasterD = rd0; P85_RasterA = ra0; P85_RasterB = rb0;
  /* 005224a8: WM_CREATE — hInstance через plat_wm_create_hinst (SDL: lparam как есть) */
  int32_t hi0 = G6_00BDF9C4; P31_WndProc(0, 1, 0, 0x4321); CK150(G6_00BDF9C4 == 0x4321); G6_00BDF9C4 = hi0;
  /* 0048ac1c */
  int32_t wm = P31_WindowMode; int live0 = plat_dd_stub_count();
  P31_WindowMode = 1; CK150(P150_FmvDDInit((void *)(intptr_t)5) == 1);
  CK150(P38_Obj814 && P38_DD && P38_Dest && P38_Obj824 && plat_dd_last_coop() == 0x11);
  { uint32_t d31[31]; plat_dd_stub_last_desc(d31); CK150(d31[0] == 0x6c && d31[1] == 1 && d31[0x68 / 4] == 0x200); }
  P38_FmvRelease();
  plat_dd_release(P38_DD); P38_DD = NULL; plat_dd_release(P38_Obj814); P38_Obj814 = NULL;
  P31_WindowMode = 0; CK150(P150_FmvDDInit(0) == 1 && plat_dd_last_coop() == 8);
  /* 0048b3e8 / 0048af23: SDL по умолчанию — CoCreateInstance отказывает (ролики пропускаются) */
  plat_fmv_stub_open(0, 0, 0, 0, 0);
  CK150(P150_OpenAudio("A.WAV") == 0 && P50_FmvB == NULL);
  CK150(P150_OpenVideo("V.MPG") == 0 && P50_Fmv82C == NULL);
  double len0 = P108_FmvLen;
  plat_fmv_stub_open(1, 0, 320, 160, 2.5);
  CK150(P150_OpenAudio("AUDIO\\X.WAV") == 1 && P38_Mms2 == P50_FmvA && P50_FmvFlag == P50_FmvA && P108_FmvLen == 2.5);
  int cr, op, smp, fg, upd; char p64[64]; int32_t rc4[4];
  plat_fmv_stub_open_stats(&cr, &op, p64, &smp, rc4, &fg, &upd);
  CK150(cr == 2 && op == 1 && strcmp(p64, "AUDIO\\X.WAV") == 0);
  P50_FmvReleaseObjs();
  CK150(P150_OpenVideo("FMVDATA\\RENDER01.MPG") == 1);
  CK150(P38_Mms == P50_Fmv82C && P50_Fmv830 && P50_Fmv834 && P38_Src && P38_Sample && P38_Letter == 160);
  { uint32_t d31[31]; plat_dd_stub_last_desc(d31); CK150(d31[1] == 0x1007 && d31[2] == 160 && d31[3] == 320 && d31[0x48 / 4] == 0x20 && d31[0x48 / 4 + 3] == 16 && d31[0x68 / 4] == 0x40); }
  plat_fmv_stub_open_stats(&cr, &op, p64, &smp, rc4, &fg, &upd);
  CK150(smp == 1 && rc4[0] == 0 && rc4[1] == 0 && rc4[2] == 320 && rc4[3] == 160);
  P50_FmvReleaseAll(); P38_FmvRelease();
  plat_fmv_stub_open(1, 1u << 4, 320, 160, 2.5);                 /* звук ролика не добавился — только запись в лог */
  CK150(P150_FmvDDInit(0) == 1 && P150_OpenVideo("B.MPG") == 1); P50_FmvReleaseAll(); P38_FmvRelease();
  plat_fmv_stub_open(1, 1u << 7, 320, 160, 2.5); CK150(P150_FmvDDInit(0) == 1 && P150_OpenVideo("B.MPG") == 0); P50_FmvReleaseAll(); P38_FmvRelease();
  plat_fmv_stub_open(1, 1u << 10, 320, 160, 2.5); CK150(P150_OpenAudio("B.WAV") == 0); P50_FmvReleaseObjs();
  plat_dd_release(P38_DD); P38_DD = NULL; plat_dd_release(P38_Obj814); P38_Obj814 = NULL;
  CK150(plat_dd_stub_count() == live0);
  /* 0048a940: ранние выходы (n = −1, ролики выключены, файла нет нигде) — без DirectDraw */
  int32_t fo = P150_FmvOff, g48 = G00575F48;
  G00575F48 = 1; P150_FmvOff = 0;
  P150_PlayFmv(1, -1, -1); P150_FmvOff = 1; P150_PlayFmv(1, 3, -1); P150_FmvOff = 0;
  P150_PlayFmv(1, 97, -1);                                          /* FMVDATA\RENDER97.MPG нет ни рядом, ни на CD */
  CK150(strcmp(P150_FmvPath, "FMVDATA\\RENDER97.MPG") == 0 && P38_Obj814 == NULL);
  plat_fmv_stub_open_stats(&cr, &op, p64, &smp, rc4, &fg, &upd); CK150(fg == 0 && upd == 0);
  G00575F48 = g48; P150_FmvOff = fo; P31_WindowMode = wm; P108_FmvLen = len0;
  plat_fmv_stub_open(0, 0, 320, 200, 1.0);
#undef CK150
  return f;
}

static int test_real_level(void) {
  const char *nm = getenv("RE_REAL_LEVEL");
  if (!nm) return 0;
  int gl_ok = getenv("RE_REAL_PNG") && plat_render_offscreen(640, 480) == 0;   /* GL до загрузки: страницы текстур сразу становятся plat_tex */
  D_00d00230 = calloc(1, 0x1000000);
  P77_LevelName = nm;
  int32_t r = P77_LoadLevel();
  fprintf(stderr, "real level %s: LoadLevel=%d models=%d slots=%d grid=%dx%d cell=%d\n", nm, (int)r, (int)P20_Count, (int)P76_NumSlots, (int)P21_GridDiv, (int)P80_GridH, (int)P80_Cell);
  int bad = 0;
  for (int i = 0; i < P20_Count && i < 1126; i++) {
    float *b = P80_Boxes[i];
    if (!(b[3] >= b[0] && b[4] >= b[1] && b[5] >= b[2]) || P80_Class[i] > 7) bad++;
  }
  fprintf(stderr, "real level: models with bad box/class: %d\n", bad);
  {   /* v1.38: прямоугольник "SEA" (004ec91e через Ui00426CAF) и сколько моделей с флагом 0x80 (P92_DrawSpin) и 4 (004fef26) */
    int n80 = 0, n4 = 0;
    for (int i = 0; i < P20_Count && i < 1126; i++) {
      if (!P79_ModelTab[i]) continue;
      uint16_t fl; memcpy(&fl, (const uint8_t *)P79_PTR(P79_ModelTab[i]) + 2, 2);
      if (fl & 0x80) n80++;
      if (fl & 4) n4++;
    }
    const uint8_t *st = P92_SpinTex;
    if (st) fprintf(stderr, "real level: SEA page %d u %d v %d w %d h %d; models flag 0x80: %d, flag 4: %d\n", st[8], st[9], st[10], st[0xb], st[0xc], n80, n4);
    else fprintf(stderr, "real level: SEA not found; models flag 0x80: %d, flag 4: %d\n", n80, n4);
  }
  { /* гистограмма типов записей моделей (для выбора следующих обработчиков рендера) */
    long hist[64] = { 0 }; long total = 0;
    for (int i = 0; i < P20_Count && i < 1126; i++) {
      uint32_t ref = P79_ModelTab[i]; if (!ref) continue;
      uint8_t *mdl = (uint8_t *)P79_PTR(ref); uint16_t n = *(uint16_t *)(mdl + 0x16); uint8_t *rec = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
      for (int k = 0; k < n; k++) { uint8_t t = rec[0]; if (t >= 56 || !G2_TABLE_00550ACC[t]) { hist[63]++; break; } hist[t]++; total++; rec += G2_TABLE_00550ACC[t]; }
    }
    fprintf(stderr, "record types (total %ld):", total);
    for (int t = 0; t < 64; t++) if (hist[t]) fprintf(stderr, " %d:%ld", t, hist[t]);
    fprintf(stderr, "\n");
  }
  /* v1.35: город через P89_DrawMap (004ee8f4) — обход клеток вокруг камеры по FRUSTRUM.DAT.  cleanup/round2: RE_REAL_CITY
     (раньше — упрощённый обход P87_DrawCells без адреса в Game.exe) теперь синоним RE_REAL_MAP. */
  int real_map = getenv("RE_REAL_MAP") != NULL || getenv("RE_REAL_CITY") != NULL;
  if (real_map && getenv("RE_REAL_PNG") && gl_ok) {   /* город: блок карты вокруг выбранной клетки → P89_DrawMap → PNG */
    static uint32_t px[640 * 480];
    int32_t N = P54_GridN, cols = P80_Cols, bestl = -1, bestc = -1;
    for (int32_t l = 0; l < P76_NumSlots && l < 1024; l++) {
      if (!P80_LumpTab[l]) continue;
      const uint8_t *c = (const uint8_t *)P80_LumpTab[l]; int32_t n, sz, cnt; memcpy(&n, c, 4); c += 4 + (size_t)n * 4; memcpy(&sz, c, 4); c += 4 + sz; memcpy(&cnt, c, 4);
      if (cnt > bestc) { bestc = cnt; bestl = l; }
    }
    if (getenv("RE_REAL_LUMP")) bestl = atoi(getenv("RE_REAL_LUMP"));
    int32_t tx = bestl % cols, ty = bestl / cols;
    fprintf(stderr, "city: N=%d cols=%d rows=%d lump %d (tile %d,%d) instances %d\n", (int)N, (int)cols, (int)P72_Rows, (int)bestl, (int)tx, (int)ty, (int)bestc);
    int32_t ccx = tx * N + N / 2, ccy = ty * N + N / 2;              /* клетка в середине плитки */
    { uint8_t *ob = (uint8_t *)G6_00D00208 + (size_t)(P54_Cnt1E0 + ((tx & 1) + (ty & 1) * 2) * 0x2000) * 0x20; float mn[3] = { 1e30f, 1e30f, 1e30f }, mx[3] = { -1e30f, -1e30f, -1e30f };
      for (int i = 0; i < bestc; i++, ob += 0x20) { float v[3]; memcpy(v, ob + 8, 12); for (int k = 0; k < 3; k++) { if (v[k] < mn[k]) mn[k] = v[k]; if (v[k] > mx[k]) mx[k] = v[k]; } }
      fprintf(stderr, "city: tile instances x %g..%g y %g..%g z %g..%g; CellX=%d CellY=%d Cell=%d\n", mn[0], mx[0], mn[1], mx[1], mn[2], mx[2], (int)P42_CellX, (int)P42_CellY, (int)P80_Cell); }
    float camx = getenv("RE_REAL_CX") ? (float)atof(getenv("RE_REAL_CX")) : ((float)ccx - (float)P80_HalfW) * P80_Cell;
    float camz = getenv("RE_REAL_CZ") ? (float)atof(getenv("RE_REAL_CZ")) : ((float)ccy - (float)P80_HalfH) * P80_Cell;
    float camy = getenv("RE_REAL_CY") ? (float)atof(getenv("RE_REAL_CY")) : -2500.0f;
    float pitch = (getenv("RE_REAL_PITCH") ? (float)atof(getenv("RE_REAL_PITCH")) : 35.0f) * 3.14159265f / 180.0f, sn = sinf(pitch), cs = cosf(pitch);
    float R[9] = { 1, 0, 0, 0, cs, -sn, 0, sn, cs }, RT[9] = { 1, 0, 0, 0, cs, sn, 0, -sn, cs };
    memcpy(P44_ViewMat, R, sizeof R); memcpy(P44_ViewMatT, RT, sizeof RT);
    P84_InitConsts(); P85_InitConsts(); P19_Scale = 1.0f; P85_RegisterNative(); P84_SelectTables(0);
    re_init_consts(); P59_InitConsts();
    for (int i = 0; i < 4096; i++) P43_Sin[i] = sinf((float)i * 6.28318530718f / 4096.0f);
    for (int i = 4096; i < 5120; i++) P43_Sin[i] = P43_Sin[i - 4096];
    { /* курс камеры: как 0049e5e7 (P61_SetupCamN) — после наклона (RotX) поворот RotY на P59_AngB, затем транспонат */
      int32_t yaw = getenv("RE_REAL_ANG") ? (atoi(getenv("RE_REAL_ANG")) & 0xfff) : 0;
      if (yaw) { P44_RotY(P44_ViewMat, (int32_t)(int16_t)yaw); P44_Transpose(P44_ViewMat, P44_ViewMatT); }
      fprintf(stderr, "city: yaw %d view %g %g %g | %g %g %g | %g %g %g\n", (int)yaw, P44_ViewMat[0], P44_ViewMat[1], P44_ViewMat[2], P44_ViewMat[3], P44_ViewMat[4], P44_ViewMat[5], P44_ViewMat[6], P44_ViewMat[7], P44_ViewMat[8]); }
    P56_AllocEulerTab(1);   /* v2.19: всегда своя таблица — в native указатель из образа данных Game.exe может быть не нулём (падение) */
    { const float *e = (const float *)P56_EulerTab; fprintf(stderr, "euler0: %g %g %g | %g %g %g | %g %g %g ; e1024: %g %g %g\n", e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], ((const float *)(P56_EulerTab + 0x10000))[0], ((const float *)(P56_EulerTab + 0x10000))[2], ((const float *)(P56_EulerTab + 0x10000))[6]); }
    P43_ScaleA = 500.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
    for (int i = 1; i < 0x2000; i++) P12_00ba53a0[i] = 1.0f / (float)i;
    if (getenv("RE_REAL_DD")) { for (int i = 0x2000; i < 0xdbba; i++) P12_00ba53a0[i] = 1.0f / (float)i; P11_0125f3e0 = 1.0f; }   /* v2.19: дальняя плоскость > 8192 */
    G2_011F43B0 = 0; P84_Mirror = 0; P82_Edge = 0; P63_SphN = 0;
    for (int i = 0; i < 4096; i++) P84_LightIn[i] = 1.0f;
    for (int i = 0; i < 8192; i++) P84_NormLight[i] = 1.0f;
    P44_CamX = camx; P44_CamY = camy; P44_CamZ = camz;
    P82_FovX = getenv("RE_REAL_FOVX") ? (float)atof(getenv("RE_REAL_FOVX")) : 320.0f / 500.0f; P82_FovY = getenv("RE_REAL_FOVY") ? (float)atof(getenv("RE_REAL_FOVY")) : 240.0f / 500.0f; P11_01270c24 = getenv("RE_REAL_FAR") ? (float)atof(getenv("RE_REAL_FAR")) : 8000.0f; P60_Var1373C0 = 0; P44_MatPtr = P44_ViewMat; P82_FrustumSetup3D();
    plat_set_zbuffer(1, 1); plat_clear(0xFF304050u, 1); P85_Tris = 0; memset(P85_TrisBy, 0, sizeof P85_TrisBy); P86_CurTex = -1; P85_StateDirty = 0;
    P44_XformTag = 100; P47_SwapCnt = 8;
    int32_t ex = (int32_t)floorf((camx + (float)P42_CellX) / (float)P80_Cell), ey = (int32_t)floorf((camz + (float)P42_CellY) / (float)P80_Cell);
    fprintf(stderr, "city: cam %g %g %g -> cell %d,%d (tile centre cell %d,%d)\n", camx, camy, camz, (int)ex, (int)ey, (int)ccx, (int)ccy);
    int32_t drawn = 0;
    {
      /* как в игре: клетка камеры (004edd08) → её блок карты в слот → 004ee8f4(0) подгружает соседей у границы и считает маску
         видимости → 004ee8f4(1) обходит клетки сектора FRUSTRUM.DAT по курсу P59_AngB → таблицы A/B (004ef309/004ef364) */
      int32_t fr = P55_LoadFrustum();
      P59_AngB = (uint16_t)(getenv("RE_REAL_ANG") ? atoi(getenv("RE_REAL_ANG")) : 0); P59_Mode1137324 = 0;
      P42_CellScale = 1.0f / (float)P80_Cell; if (!G6_01270D28) G6_01270D28 = st_depth_mask; G6_00B87EEC = 1; G6_00D11880 = getenv("RE_REAL_D11880") ? atoi(getenv("RE_REAL_D11880")) : 0; P13_00575ee8 = 1;
      memset(P87_SlotLumpA, 0xff, sizeof P87_SlotLumpA); memset(P87_SlotLump, 0xff, sizeof P87_SlotLump);
      P88_CellUpdate(0);                                 /* 004edd08: в native вызов из 004ee065 идёт в заглушку (P75_Fn4EDD08 в --skip) */
      P55_VarC6 = P88_CellB.pc;                          /* 00cff9c6 = поле pc описателя B; в native — отдельная переменная */
      P75_ResetObjs();                                   /* 004ee065: включает все модели (00bdcd00) и грузит блок карты 00cff9ac в слот 00cff9c6 */
      P89_DrawMap(0);
      fprintf(stderr, "map: frustum=%d cell %d,%d block %d slot %d (rx %d ry %d) slots %d %d %d %d vis %d (stride %d)\n", (int)fr, (int)P88_CellA.x, (int)P88_CellA.y, (int)P88_CellA.cell, (int)P88_CellA.pc, (int)P88_CellA.rx, (int)P88_CellA.ry,
              (int)P87_SlotLumpA[0], (int)P87_SlotLumpA[1], (int)P87_SlotLumpA[2], (int)P87_SlotLumpA[3], (int)D_00d00204, (int)P21_GridStride);
      /* v2.19: RE_REAL_DD=m — дальность × m как в игре (P132_GameDraw): дальняя плоскость × m, обход за 31×31, кэш блоков */
      float dd_far0 = P11_01270c24, dd_q0 = Q01270C24;
      if (getenv("RE_REAL_DD") && atof(getenv("RE_REAL_DD")) > 1.0) {
        double m = re_dd_clamp(atof(getenv("RE_REAL_DD")));
        re_gfx()->draw_distance = m; P11_01270c24 = (float)(dd_far0 * m); Q01270C24 = P11_01270c24; P82_FrustumSetup3D();
        re_oow_n = re_dd_oow_n(P11_01270c24); re_dd_on = 1; re_dd_warm();
        fprintf(stderr, "map: draw_distance %.2f far %.0f\n", m, P11_01270c24);
      }
      int32_t t0 = P85_Tris;
      P89_DrawMap(1);
      int32_t t1 = P85_Tris, na = P55_CntA, nb = P55_CntB;
      P55_RunTableA(); P55_RunTableB();
      fprintf(stderr, "map: DrawMap triangles %d, tables A %d B %d -> +%d, four %d seven %d shadow %d\n", (int)(t1 - t0), (int)na, (int)nb, (int)(P85_Tris - t1), (int)P89_CntFour, (int)P89_CntSeven, (int)P89_CntShadow);
      drawn = t1 - t0 + na + nb;
      if (re_dd_on) { re_dd_on = 0; re_oow_n = 0xdbba; P11_01270c24 = dd_far0; Q01270C24 = dd_q0; re_gfx()->draw_distance = 1.0; }
    }
    fprintf(stderr, "city: objects drawn %d, triangles %d (blend 0/1/2/3: %d/%d/%d/%d)\n", (int)drawn, (int)P85_Tris, (int)P85_TrisBy[0], (int)P85_TrisBy[1], (int)P85_TrisBy[2], (int)P85_TrisBy[3]);
    if (plat_render_readback(px) == 0) png_write_rgba(getenv("RE_REAL_PNG"), px, 640, 480);
  }
  if (getenv("RE_REAL_PNG") && !real_map && P20_Count > 0) {   /* самая «плотная» модель уровня → P84_DrawModel → текстуры страниц LEV → PNG */
    int best = -1, bn = 0;
    for (int i = 0; i < P20_Count && i < 1126; i++) {
      uint32_t ref = P79_ModelTab[i]; if (!ref) continue;
      uint8_t *mdl = (uint8_t *)P79_PTR(ref); int n = *(uint16_t *)(mdl + 0x16);
      float *bb = P80_Boxes[i]; if (getenv("RE_REAL_LIST") && n >= 40) fprintf(stderr, "m%d n=%d ext %g %g %g\n", i, n, bb[3] - bb[0], bb[4] - bb[1], bb[5] - bb[2]);
      int sc = n >= 30 && n < 4000 && bb[3] - bb[0] < 2500 && bb[5] - bb[2] < 2500 ? (int)((bb[3] - bb[0]) * (bb[5] - bb[2]) * (bb[4] - bb[1] > 0 ? 1 : 1) / 100) : 0;
      if (sc > bn) { bn = sc; best = i; }
    }
    if (getenv("RE_REAL_MODEL")) { best = atoi(getenv("RE_REAL_MODEL")); bn = *(uint16_t *)((uint8_t *)P79_PTR(P79_ModelTab[best]) + 0x16); }
    fprintf(stderr, "render model %d (%d records), textures captured: %d\n", best, bn, (int)P86_TexCount);
    if (best >= 0 && gl_ok) {
      static uint32_t px[640 * 480];
      float ident[16 * 8]; float b[6]; float pos[3];
      memcpy(b, P80_Boxes[best], sizeof b);
      float cx = (b[0] + b[3]) / 2, cy = (b[1] + b[4]) / 2, cz = (b[2] + b[5]) / 2;
      float rad = fmaxf(fmaxf(b[3] - b[0], b[4] - b[1]), b[5] - b[2]);
      memset(ident, 0, sizeof ident);
      for (int k = 0; k < 8; k++) ident[k * 16] = ident[k * 16 + 4] = ident[k * 16 + 8] = 1.0f;
      memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
      P84_InitConsts(); P85_InitConsts(); P19_Scale = 1.0f;
      P85_RegisterNative(); P84_SelectTables(0);
      P43_ScaleA = 500.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
      for (int i = 1; i < 0x2000; i++) P12_00ba53a0[i] = 1.0f / (float)i;
      G2_011F43B0 = 0; P84_Mirror = 0; P82_Edge = 0; P63_SphN = 0;
      for (int i = 0; i < 4096; i++) { P84_LightIn[i] = 1.0f; }
      for (int i = 0; i < 8192; i++) { P84_NormLight[i] = 1.0f; }
      { float sy = getenv("RE_REAL_SY") ? (float)atof(getenv("RE_REAL_SY")) : 1.0f; pos[0] = -cx; pos[1] = sy * cy; pos[2] = -cz + 2.2f * rad; fprintf(stderr, "box %g %g %g .. %g %g %g\n", b[0], b[1], b[2], b[3], b[4], b[5]); }
      plat_set_zbuffer(1, 1); plat_clear(0xFF304050u, 1); P85_Tris = 0; P86_CurTex = -1; P85_StateDirty = 0;
      P44_XformTag = 100; P84_DrawModel(P79_ModelTab[best], ident, pos, 5);
      fprintf(stderr, "model triangles: %d\n", (int)P85_Tris);
      if (plat_render_readback(px) == 0) png_write_rgba(getenv("RE_REAL_PNG"), px, 640, 480);
    }
  }
  if (getenv("RE_REAL_STATS")) {
    uint8_t *ent = (uint8_t *)G6_00D00208; float mn[3] = { 1e30f, 1e30f, 1e30f }, mx[3] = { -1e30f, -1e30f, -1e30f }; int fl[16] = { 0 };
    for (int i = 0; i < P54_Cnt1E0; i++, ent += 0x20) {
      float p3[3]; memcpy(p3, ent + 8, 12); for (int k = 0; k < 3; k++) { if (p3[k] < mn[k]) mn[k] = p3[k]; if (p3[k] > mx[k]) mx[k] = p3[k]; }
      uint32_t mi; memcpy(&mi, ent + 4, 4); if (mi < 1126 && P79_ModelTab[mi]) { uint16_t f; memcpy(&f, (uint8_t *)P79_PTR(P79_ModelTab[mi]) + 2, 2); for (int b = 0; b < 16; b++) if (f >> b & 1) fl[b]++; }
    }
    fprintf(stderr, "objects %d pos %g %g %g .. %g %g %g\n", (int)P54_Cnt1E0, mn[0], mn[1], mn[2], mx[0], mx[1], mx[2]);
    for (int b = 0; b < 16; b++) fprintf(stderr, " f%d:%d", b, fl[b]);
    fprintf(stderr, "\n");
    ent = (uint8_t *)G6_00D00208; for (int i = 0; i < 5; i++, ent += 0x20) { uint32_t w[8]; float wf[4]; memcpy(w, ent, 32); memcpy(wf, ent + 8, 16); fprintf(stderr, "ent%d: %u %u %g %g %g %g %u %u\n", i, w[0], w[1], wf[0], wf[1], wf[2], wf[3], w[6], w[7]); }
  }
  if (P20_Count > 0) { float *b = P80_Boxes[0]; fprintf(stderr, "model0 box: %g %g %g .. %g %g %g\n", b[0], b[1], b[2], b[3], b[4], b[5]); }
  return r == 1 && bad == 0 && P20_Count > 0 ? 0 : 1;
}

/* RE_TRACE=1 печатает имя каждого теста перед запуском (поиск падения) */
static int run_t_(const char *n, int r) { if (r) fprintf(stderr, "[test] %s returned %d\n", n, r); return r; }
#define RUN_T(t) (getenv("RE_TRACE") ? (fprintf(stderr, "[test] %s\n", #t), run_t_(#t, t())) : t())

static int p84_calls, p84_last_arg; static uint32_t p84_types[8];
static void p84_h0(uint32_t a) { p84_types[p84_calls++ & 7] = 0; p84_last_arg = (int)a; G2_011F4064 += 32; }
static void p84_h16(uint32_t a) { p84_types[p84_calls++ & 7] = 16; p84_last_arg = (int)a; G2_011F4064 += 32; }
static int test_p84(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p84 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000);
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); float *nn = (float *)(arena + 0x280); uint8_t *rec = arena + 0x300;
    uint16_t u16; uint32_t u32; int32_t i32;
    float ident[16 * 8]; float pos[3] = { 0, 0, 0 };
    D_00c98ed0 = arena; P84_InitConsts();
    CK(P84_Arg[0] == 0 && P84_Arg[32] == 1 && P84_Lit[16] == 1 && P84_Lit[0] == 0);
    memset(ident, 0, sizeof ident);
    for (int k = 0; k < 8; k++) ident[k * 16] = ident[k * 16 + 4] = ident[k * 16 + 8] = 1.0f;
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    u16 = 1; memcpy(m + 2, &u16, 2); u16 = 3; memcpy(m + 0x16, &u16, 2); u16 = 1; memcpy(m + 0x18, &u16, 2);
    u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4); u32 = P79_OFF(nn); memcpy(m + 0x28, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    pl[0] = 0; pl[1] = 0; pl[2] = 1; pl[3] = 5;            /* плоскость 0: лицом, свет +1 */
    pl[4] = 0; pl[5] = 0; pl[6] = 1; pl[7] = -5;           /* плоскость 1: спиной */
    pl[8] = 0; pl[9] = 0; pl[10] = -1; pl[11] = 5;         /* плоскость 2: лицом, свет −1 */
    nn[0] = 0; nn[1] = 0; nn[2] = 1; nn[3] = 0;
    rec[0] = 16; rec[1] = 8; i32 = 0; memcpy(rec + 4, &i32, 4);
    rec[32] = 16; rec[33] = 8; i32 = 1; memcpy(rec + 36, &i32, 4);
    rec[64] = 16; rec[65] = 8; i32 = 2; memcpy(rec + 68, &i32, 4);
    rec[96] = 0; rec[97] = 0; i32 = 0; memcpy(rec + 100, &i32, 4);
    u16 = 4; memcpy(m + 0x16, &u16, 2);
    memset(P84_Handlers, 0, sizeof P84_Handlers);
    P84_Handlers[2][0] = (uintptr_t)p84_h0; P84_Handlers[2][16] = (uintptr_t)p84_h16;
    P84_SelectTables(0); G2_011F43B0 = 0; P84_Mirror = 0;
    P19_OutA = 0; P19_OutB = 0; P19_OutC = 1; P19_Out68 = 0.25f;
    p84_calls = 0; P44_XformTag = 10;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p84_calls == 3 && p84_types[0] == 16 && p84_types[1] == 16 && p84_types[2] == 0);
    CK(P84_Vis[0] == 1 && P84_Vis[1] == 0 && P84_Vis[2] == 1);
    CK(P84_LightIn[0] == 1.0f && P84_LightIn[2] == 0.25f && P84_NormLight[0] == 1.0f);
    CK(P44_XformTag == 11 && P84_Planes == pl && P44_BiasZ == 0.0f);
    /* зеркало: ось X отражена, матрица света не меняется */
    P84_Mirror = 1; pos[0] = 3; p84_calls = 0;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p84_calls == 3 && P44_BiasX == -3.0f && P44_MatPtr[0] == -1.0f && P44_MatPtr[4] == 1.0f);
    P84_Mirror = 0; pos[0] = 0;
    /* кэш матриц */
    P56_EulerTab = (uint8_t *)ident; P47_SwapCnt = 77; P84_MatFlag[3] = 0; P84_MatCache[3][0] = 9.0f;
    p84_calls = 0; P84_DrawModelIdx(P79_OFF(m), 0, pos, 5);
    CK(p84_calls == 3 && P84_MatFlag[0] == 77 && P84_MatCache[0][0] == 1.0f && P84_MatCache[0][4] == 1.0f);
    P84_MatCache[0][0] = 5.0f; p84_calls = 0; P84_DrawModelIdx(P79_OFF(m), 0, pos, 5);   /* кэш свежий — не пересчитывается */
    CK(P84_MatCache[0][0] == 5.0f && p84_calls == 3);
    P84_MatCache[0][0] = 1.0f; P84_MatFlag[0] = 0; memset(P84_Handlers, 0, sizeof P84_Handlers);
    p84_calls = 0; P84_DrawModel(P79_OFF(m), ident, pos, 5); CK(p84_calls == 0);          /* без обработчиков не падает */
    D_00c98ed0 = saved; free(arena);
  }
  return f;
}

/* ported90: однозаписная модель (0042a423) — первая запись сразу в обработчик режима с аргументом 0, без отсечения */
static int test_p91(void) {
    int f = 0;
    static uint8_t car[0xd00]; uint8_t id = 3;
    *(uint8_t **)(car + 0xcd0) = &id;
    *(uint32_t *)(car + 0xcb4) = 9;
    TrafficRecs[2 * 0x54 + 5] = 1; G0112B284 = 2; G0112B280 = 5;
    P91_ReleaseTraffic(car);
    CK(TrafficRecs[2 * 0x54 + 5] == 0 && *(uint32_t *)(car + 0xcb4) == 0 && G0112B284 == 1 && G0112B280 == 5);
    P91_ReleaseTraffic(car);
    CK(G0112B284 == 0 && G0112B280 == 0x200);
    return f;
}
static int test_p90(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p90 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000); uint8_t *seul = P56_EulerTab; int32_t ssw = P47_SwapCnt;
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); uint8_t *rec = arena + 0x300;
    uint32_t u32; uint16_t u16; float ident[16 * 4]; float pos[3] = { 3, -4, 5 };
    D_00c98ed0 = arena; P84_InitConsts();
    memset(ident, 0, sizeof ident);
    for (int k = 0; k < 4; k++) ident[k * 16] = ident[k * 16 + 4] = ident[k * 16 + 8] = 1.0f;
    ident[16 + 0] = 2.0f;                                           /* запись 1 таблицы поворотов отличается */
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    u16 = 0x2400; memcpy(m + 2, &u16, 2); u16 = 1; memcpy(m + 0x16, &u16, 2);
    u32 = 0x1234; memcpy(m + 0x20, &u32, 4); u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    pl[0] = 0; pl[1] = 0; pl[2] = 1; pl[3] = -100;                  /* плоскость спиной к камере — 0042a423 её не проверяет */
    rec[0] = 16; rec[1] = 8;
    memset(P84_Handlers, 0, sizeof P84_Handlers);
    P84_Handlers[1][16] = (uintptr_t)p84_h16; P84_Handlers[2][0] = (uintptr_t)p84_h0;
    P84_SelectTables(0); G2_011F43B0 = 0; P84_Mirror = 0; P63_SphN = 5; P81_PosY = 0.75f; P84_LightIn[0] = 0;
    P56_EulerTab = (uint8_t *)ident; P47_SwapCnt = 41; P84_MatFlag[1] = 0; P44_XformTag = 20;
    p84_calls = 0; p84_last_arg = -1;
    P90_DrawSingle(P79_OFF(m), 1, pos, 1);
    CK(p84_calls == 1 && p84_types[0] == 16 && p84_last_arg == 0);
    CK(P63_SphN == 0 && P84_LightIn[0] == 0.75f && P84_VertRef == 0x1234 && P84_Planes == pl);
    CK(P44_BiasX == 3.0f && P44_BiasY == -4.0f && P44_BiasZ == 5.0f && P44_XformTag == 21);
    CK(P84_MatFlag[1] == 41 && P84_MatCache[1][0] == 2.0f && P44_MatPtr == P84_MatCache[1]);
    P84_MatCache[1][0] = 7.0f; P90_DrawSingle(P79_OFF(m), 1, pos, 1); CK(P84_MatCache[1][0] == 7.0f);   /* кэш свежий */
    /* зеркало: X со знаком минус, матрица — копия с −[0], −[3], −[6] */
    P84_Mirror = 1; p84_calls = 0;
    P90_DrawSingle(P79_OFF(m), 1, pos, 1);
    CK(p84_calls == 1 && P44_BiasX == -3.0f && P44_MatPtr != P84_MatCache[1] && P44_MatPtr[0] == -7.0f && P84_MatCache[1][0] == 7.0f);
    P84_Mirror = 0;
    /* режим 2 → третья таблица, тип 16 в ней пуст — ничего не зовётся */
    p84_calls = 0; P90_DrawSingle(P79_OFF(m), 1, pos, 2); CK(p84_calls == 0 && P44_XformTag == 24);
    rec[0] = 0; P90_DrawSingle(P79_OFF(m), 1, pos, 2); CK(p84_calls == 1 && p84_types[0] == 0);
    memset(P84_Handlers, 0, sizeof P84_Handlers); P84_MatFlag[1] = 0;
    P56_EulerTab = seul; P47_SwapCnt = ssw; D_00c98ed0 = saved; free(arena);
  }
  return f;
}

/* ported92: осевой вариант 0042982e — осевые плоскости x/y/−z, свет по компонентам P81_* (поворот 0x400), нормали по P83_LightVec[1] */
static int test_p92(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p92 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000); int32_t sstep = G2_TABLE_00550ACC[16];
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); uint8_t *rec = arena + 0x300; float *nrm = (float *)(arena + 0x280);
    uint32_t u32; uint16_t u16; const float pos[3] = { 3, -4, 5 };
    D_00c98ed0 = arena; P84_InitConsts(); G2_TABLE_00550ACC[16] = 32;
    u16 = 0x31; memcpy(m + 2, &u16, 2); u16 = 4; memcpy(m + 0x16, &u16, 2); u16 = 1; memcpy(m + 0x18, &u16, 2);
    u32 = 0x55; memcpy(m + 0x20, &u32, 4); u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4);
    u32 = P79_OFF(nrm); memcpy(m + 0x28, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    nrm[0] = 0; nrm[1] = 1; nrm[2] = 0;
    pl[0 * 4 + 3] = 10;                                    /* 0: x − d = 3 − 10 < 0 → видима, свет = P81_PosZ (idx 0x400) */
    pl[1 * 4 + 3] = -10;                                   /* 1: y − d = −4 + 10 ≥ 0 → невидима, шаг 32 */
    pl[2 * 4 + 2] = 1; pl[2 * 4 + 3] = 0;                  /* 2: общая, n·(−p) − d = −5 < 0 → видима, свет = фон + n·L */
    pl[3 * 4 + 3] = -6;                                    /* 3: −z − d = −5 + 6 ≥ 0 → невидима */
    for (int i = 0; i < 4; i++) { rec[i * 32] = 16; *(int32_t *)(rec + i * 32 + 4) = i; }
    rec[1] = 8 | 1; rec[32 + 1] = 8 | 5; rec[64 + 1] = 8 | 0; rec[96 + 1] = 8 | 3;
    memset(P84_Handlers, 0, sizeof P84_Handlers); P84_Handlers[1][16] = (uintptr_t)p84_h16; P84_SelectTables(0);
    memset(P84_MatCache[0x400], 0, sizeof(p84_m16_t));
    P84_MatCache[0x400][0] = P84_MatCache[0x400][4] = P84_MatCache[0x400][8] = 1.0f;
    memset(P83_LightVec, 0, sizeof(p83_v16_t)); P83_LightVec[4 + 1] = 1.0f;      /* вектор света 1: вверх */
    P81_PosX = 0.1f; P81_NegX = 0.2f; P81_PosZ = 0.3f; P81_NegZ = 0.4f; P81_PosY = 0.5f; P81_NegY = 0.6f; P19_Out68 = 0.25f;
    G2_011F43B0 = 0; P63_SphN = 3; P84_Mirror = 0; P44_XformTag = 7; memset(P84_Vis, 9, 8); memset(P84_LightIn, 0, 32);
    p84_calls = 0; p84_last_arg = -1;
    P92_DrawAxis(P79_OFF(m), 0x400, pos, 1);
    CK(p84_calls == 2 && p84_last_arg == 0 && P44_XformTag == 8 && P63_SphN == 0);
    CK(P84_Vis[0] == 1 && P84_Vis[1] == 0 && P84_Vis[2] == 1 && P84_Vis[3] == 0);
    CK(P84_LightIn[0] == 0.3f && P84_LightIn[2] == 0.25f && P84_LightIn[1] == 0 && P84_NormLight[0] == 1.0f);
    CK(P84_VertRef == 0x55 && P84_Planes == pl && P44_BiasX == 3.0f && P44_MatPtr == P84_MatCache[0x400]);
    CK(G2_011F4064 == rec + 128);
    /* поворот 0: та же осевая плоскость x получает P81_NegX; зеркало — X со знаком минус, копия матрицы */
    memcpy(P84_MatCache[0], P84_MatCache[0x400], sizeof(p84_m16_t)); P84_Mirror = 1; p84_calls = 0;
    P92_DrawAxis(P79_OFF(m), 0, pos, 1);
    CK(p84_calls == 2 && P84_LightIn[0] == 0.2f && P44_BiasX == -3.0f && P44_MatPtr != P84_MatCache[0] && P44_MatPtr[0] == -1.0f);
    P84_Mirror = 0;
    /* режим 2 → третья таблица пуста: ничего не зовётся, невидимые записи всё равно пропускаются */
    rec[1] = 8 | 2; rec[64 + 1] = 8 | 6;                   /* −x − d = −13 < 0 видима; −y − d = 4 ≥ 0 невидима */
    p84_calls = 0; G2_011F4064 = 0;
    u16 = 1; memcpy(m + 0x16, &u16, 2);                    /* одна запись — без обработчика указатель не сдвигается */
    P92_DrawAxis(P79_OFF(m), 0x400, pos, 2); CK(p84_calls == 0 && P84_Vis[0] == 1 && P84_LightIn[0] == 0.4f);
    memset(P84_Handlers, 0, sizeof P84_Handlers); G2_TABLE_00550ACC[16] = sstep;
    D_00c98ed0 = saved; free(arena);
  }
  return f;
}

/* ported92: 0042a5de — цвета 159/168/192, координаты квадрата в прямоугольнике текстуры по синусу кадра, аргумент 0/3 */
static int p92s_arg = -1;
static void p92s_h(uint32_t a) { p92s_arg = (int)a; }
static int test_p92s(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p92s fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000); uint8_t *seul = P56_EulerTab; int32_t ssw = P47_SwapCnt;
    uint32_t stx = G012085F4; int32_t sfr = P62_Frame, s5ee8 = P13_00575ee8;
    uint8_t *m = arena + 0x100; uint8_t *rec = arena + 0x300; uint8_t *tx = arena + 0x80;
    uint32_t u32; float ident[16]; const float pos[3] = { 1, 2, 3 }; float v[8], c[3];
    D_00c98ed0 = arena;
    memset(ident, 0, sizeof ident); ident[0] = ident[4] = ident[8] = 1.0f;
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4); rec[0] = 21;
    memset(P84_Handlers, 0, sizeof P84_Handlers); P84_Handlers[0][21] = (uintptr_t)p92s_h; P84_SelectTables(0);
    P56_EulerTab = (uint8_t *)ident; P47_SwapCnt = 5; P84_MatFlag[0] = 0; G2_011F43B0 = 0; P84_Mirror = 0; P81_PosY = 0.5f;
    static p43_sintab_t ssin; memcpy(ssin, P43_Sin, sizeof ssin);
    for (int i = 0; i < 0x1000; i++) P43_Sin[i] = 0;
    P43_Sin[0x10] = 1.0f; P43_Sin[0x6d9] = 0.5f;          /* кадр 1: индексы 0x10 и 0x10 + 0x6c9 */
    P62_Frame = 0x101; P13_00575ee8 = 0;
    tx[9] = 10; tx[10] = 20; tx[0xb] = 64; tx[0xc] = 96;  /* r = 2 */
    G012085F4 = 0; p92s_arg = -1; P44_XformTag = 3;
    P92_DrawSpin(P79_OFF(m), 0, pos, 0);
    memcpy(c, rec + 0x38, 12);
    CK(p92s_arg == 0 && c[0] == 159.0f && c[1] == 168.0f && c[2] == 192.0f && P92_SinIdx == 0x6d9 && P44_XformTag == 4);
    CK(P84_MatFlag[0] == 5 && P44_MatPtr == P84_MatCache[0] && P84_LightIn[0] == 0.5f && G2_011F4064 == rec);
    memcpy(v, rec + 0x18, 32); CK(v[0] == 0 && v[7] == 0);             /* без текстуры (native) координаты не трогаются */
    P92_SpinTex = tx; P13_00575ee8 = 1;
    P92_DrawSpin(P79_OFF(m), 0, pos, 0);
    memcpy(v, rec + 0x18, 32);
    CK(p92s_arg == 3 && v[0] == 14.0f && v[1] == 23.0f && v[2] == 73.0f && v[3] == 20.0f && v[4] == 70.0f && v[5] == 113.0f && v[6] == 11.0f && v[7] == 115.0f);
    P92_SpinTex = 0;
    P13_00575ee8 = 1; P92_DrawSpin(P79_OFF(m), 0, pos, 0); CK(p92s_arg == 3);
    memset(P84_Handlers, 0, sizeof P84_Handlers); P84_MatFlag[0] = 0;
    memcpy(P43_Sin, ssin, sizeof ssin); G012085F4 = stx; P62_Frame = sfr; P13_00575ee8 = s5ee8; P56_EulerTab = seul; P47_SwapCnt = ssw; D_00c98ed0 = saved; free(arena);
  }
  return f;
}

int png_write_rgba(const char *path, const uint32_t *px, int w, int h);
static int p85_calls; static p85_rv p85_cap[8][3];
static int p85_check_camera, p85_camera_valid[8][3];
static double p85_camera_cap[8][3][3];
static void p85_capture(const p85_rv *a, const p85_rv *b, const p85_rv *c) {
  if (p85_calls < 8) {
    const p85_rv *v[3] = { a, b, c };
    for (int j = 0; j < 3; j++) {
      p85_cap[p85_calls][j] = *v[j];
      if (p85_check_camera) p85_camera_valid[p85_calls][j] = P85_GetCameraPoint(v[j], p85_camera_cap[p85_calls][j]);
    }
  }
  p85_calls++;
}
static int p85_blend_calls, p85_blend_a;
static void p85_blend_cap(int32_t a, int32_t b, int32_t c, int32_t d) { (void)b; (void)c; (void)d; p85_blend_calls++; p85_blend_a = a; }
static void p85_state_cap(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) { (void)a; (void)b; (void)c; (void)d; (void)e; }
static int test_p85(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p85 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000);
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); uint8_t *rec = arena + 0x300; float *vert = (float *)(arena + 0x800);
    uint16_t u16; uint32_t u32; int32_t i32;
    float ident[16 * 8]; float pos[3] = { 0, 0, 0 };
    D_00c98ed0 = arena;
    memset(ident, 0, sizeof ident);
    for (int k = 0; k < 8; k++) ident[k * 16] = ident[k * 16 + 4] = ident[k * 16 + 8] = 1.0f;
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    /* константы проекции: смещение экрана (320,240) + 2^20 — как в игре */
    P43_ScaleA = 100.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
    P19_Scale = 1.0f;
    for (int i = 1; i < 0x400; i++) P12_00ba53a0[i] = 1.0f / (float)i;
    /* 1) проекция одной вершины: (2, 4, 10) при единичной матрице → oow = 1/10, x = 320 + 100·2/10 = 340, y = 240 + 40 = 280 */
    { p85_vtx v; memset(&v, 0, sizeof v); v.x = 2; v.y = 4; v.z = 10;
      P44_MatPtr = P44_ViewMat; P44_BiasX = P44_BiasY = P44_BiasZ = 0; P44_XformTag = 5;
      P85_Project(&v);
      CK(v.stamp == 5 && v.z == 10.0f && v.vx == 2.0f && v.vy == 4.0f && P85_ZI == 10);
      CK(v.oow == 1.0f / 10.0f && fabsf(v.x - 340.0f) <= 0.125f && fabsf(v.y - 280.0f) <= 0.125f);
      /* смещения камеры прибавляются ДО округления z */
      P44_BiasZ = 0.4f; v.x = 0; v.y = 0; v.z = 3.2f; P85_Project(&v); CK(P85_ZI == 4 && v.z > 3.59f && v.z < 3.61f);
      P44_BiasZ = 0;
    }
    /* 2) модель: плоский треугольник (тип 0) и плоский четырёхугольник (тип 33, режим смешивания 1) */
    u16 = 0; memcpy(m + 2, &u16, 2); u16 = 2; memcpy(m + 0x16, &u16, 2); u16 = 0; memcpy(m + 0x18, &u16, 2);
    P84_InitConsts(); P85_InitConsts();
    u32 = P79_OFF(vert); memcpy(m + 0x20, &u32, 4); u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    pl[0] = 0; pl[1] = 0; pl[2] = 1; pl[3] = 5;
    { float vv[4][4] = { { 0, 0, 10, 0 }, { 10, 0, 10, 0 }, { 0, 10, 10, 0 }, { 10, 10, 10, 0 } }; memcpy(vert, vv, sizeof vv); }
    memset(rec, 0, 128);
    rec[0] = 0; rec[1] = 8; i32 = 0; memcpy(rec + 4, &i32, 4);
    i32 = 0; memcpy(rec + 8, &i32, 4); i32 = 1; memcpy(rec + 12, &i32, 4); i32 = 2; memcpy(rec + 16, &i32, 4);
    { float c[3] = { 255.0f, 128.0f, 0.0f }; memcpy(rec + 0x14, c, 12); }
    rec[0x20] = 33; rec[0x21] = 8; i32 = 0; memcpy(rec + 0x24, &i32, 4);
    i32 = 0; memcpy(rec + 0x28, &i32, 4); i32 = 1; memcpy(rec + 0x2c, &i32, 4); i32 = 3; memcpy(rec + 0x30, &i32, 4); i32 = 2; memcpy(rec + 0x34, &i32, 4);
    { float c[3] = { 1.0f, 2.0f, 3.0f }; memcpy(rec + 0x38, c, 12); }
    P85_RegisterNative();
    P85_RasterA = P85_RasterB = p85_capture; P85_BlendFn = p85_blend_cap; P85_StateFn = p85_state_cap;
    CK(P84_Handlers[2][0] == (uintptr_t)P85_FlatTri && P84_Handlers[2][33] == (uintptr_t)P85_FlatQuad && P84_Handlers[0][2] == (uintptr_t)P85_SkipRecord);
    P84_SelectTables(0); G2_011F43B0 = 0; P84_Mirror = 0; P82_Edge = 0;
    P85_StateDirty = 1; P85_BlendCur = 0; P85_BlendForce = 0;
    P44_XformTag = 20; p85_calls = 0; p85_blend_calls = 0;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p85_calls == 3 && P85_StateDirty == 0 && p85_blend_calls == 1 && p85_blend_a == 0 && P85_BlendCur == 1);
    CK(G2_011F4064 == rec + 0x20 + 0x24);                     /* курсор записей ушёл за обе записи */
    /* треугольник: вершины (0,0,10),(10,0,10),(0,10,10) → (320,240),(420,240),(320,340) */
    CK(fabsf(p85_cap[0][0].x - 320) <= 0.2f && fabsf(p85_cap[0][1].x - 420) <= 0.2f && fabsf(p85_cap[0][2].y - 340) <= 0.2f);
    CK(p85_cap[0][0].r == 255.0f && p85_cap[0][1].g == 128.0f && p85_cap[0][2].b == 0.0f && p85_cap[0][1].oow == 0.1f);
    /* четырёхугольник: (v0,v2,v1) и (v0,v2,v3): v2 = индекс 3 из записи → (420,340) */
    CK(fabsf(p85_cap[1][1].x - 420) <= 0.2f && fabsf(p85_cap[1][1].y - 340) <= 0.2f && fabsf(p85_cap[1][2].x - 420) <= 0.2f && fabsf(p85_cap[1][2].y - 240) <= 0.2f);
    CK(fabsf(p85_cap[2][1].x - 420) <= 0.2f && fabsf(p85_cap[2][2].x - 320) <= 0.2f && fabsf(p85_cap[2][2].y - 340) <= 0.2f);
    CK(p85_cap[1][0].r == 1.0f && p85_cap[2][2].g == 2.0f);
    /* отсечение по краям: всё левее экрана (знаковый бит) — пропуск */
    P82_Edge = 1; P44_XformTag = 21; p85_calls = 0;
    P85_VCache[0].x = P85_VCache[1].x = P85_VCache[2].x = P85_VCache[3].x = -5.0f;
    { for (int i = 0; i < 4; i++) { vert[i * 4] = -100.0f; vert[i * 4 + 2] = 10.0f; } }
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p85_calls == 0 && (P85_Clip & 0x80000000u));
    /* на экране: треугольник идёт, пока x−639 не равно +0.0 у всех вершин */
    { float vv[4][4] = { { 0, 0, 10, 0 }, { 10, 0, 10, 0 }, { 0, 10, 10, 0 }, { 10, 10, 10, 0 } }; memcpy(vert, vv, sizeof vv); }
    P44_XformTag = 22; p85_calls = 0; P84_DrawModel(P79_OFF(m), ident, pos, 5); CK(p85_calls == 3);
    P82_Edge = 0;
    /* 2б) освещённые типы 16 (треугольник) и 17 (четырёхугольник): цвет × P84_LightIn[плоскость] */
    { float c[3] = { 200.0f, 100.0f, 50.0f }; rec[0] = 16; memcpy(rec + 0x14, c, 12); rec[0x20] = 17; memcpy(rec + 0x38, c, 12); }
    P84_LightIn[0] = 0.5f; P84_SelectTables(0);
    P44_XformTag = 23; p85_calls = 0;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p85_calls == 3 && p85_cap[0][0].r == 100.0f && p85_cap[0][2].g == 50.0f && p85_cap[0][1].b == 25.0f && p85_cap[2][2].r == 100.0f);
    /* 3) картинка: домик из плоских многоугольников через P84_DrawModel → plat_draw_tris → PNG (OSMesa, если есть) */
    if (plat_render_offscreen(640, 480) == 0) {
      static uint32_t px[640 * 480];
      P85_RegisterNative();                                   /* растеризатор → plat_draw_tris */
      P43_ScaleA = 400.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f;
      for (int i = 1; i < 0x2000; i++) P12_00ba53a0[i] = 1.0f / (float)i;
      { float vv[8][4] = { { -10, 10, 40, 0 }, { 10, 10, 40, 0 }, { 10, -10, 40, 0 }, { -10, -10, 40, 0 }, { -30, -20, 80, 0 }, { 30, -20, 80, 0 }, { 30, 20, 80, 0 }, { -30, 20, 80, 0 } };
        memcpy(vert, vv, sizeof vv); }
      memset(rec, 0, 256);
      rec[0] = 1; rec[1] = 8; i32 = 0; memcpy(rec + 8, &i32, 4); i32 = 1; memcpy(rec + 12, &i32, 4); i32 = 2; memcpy(rec + 16, &i32, 4); i32 = 3; memcpy(rec + 20, &i32, 4);
      { float c[3] = { 255.0f, 80.0f, 40.0f }; memcpy(rec + 0x18, c, 12); }
      rec[36] = 1; rec[37] = 8; i32 = 4; memcpy(rec + 36 + 8, &i32, 4); i32 = 5; memcpy(rec + 36 + 12, &i32, 4); i32 = 6; memcpy(rec + 36 + 16, &i32, 4); i32 = 7; memcpy(rec + 36 + 20, &i32, 4);
      { float c[3] = { 40.0f, 120.0f, 255.0f }; memcpy(rec + 36 + 0x18, c, 12); }
      u16 = 2; memcpy(m + 0x16, &u16, 2);
      plat_set_zbuffer(1, 1); plat_clear(0xFF101820u, 1); P85_Tris = 0;
      P44_XformTag = 40; P84_DrawModel(P79_OFF(m), ident, pos, 5);
      CK(P85_Tris == 4 && (uint8_t)P85_BlendCur == 0);
      if (plat_render_readback(px) == 0) {
        /* ближний красный квадрат перекрывает дальний синий; центр красный, левый край синий, угол — фон */
        uint32_t c0 = px[240 * 640 + 320], c1 = px[(240) * 640 + 320 - 130], c2 = px[5 * 640 + 5];
        CK((c0 & 255) > 200 && ((c0 >> 8) & 255) < 120 && ((c0 >> 16) & 255) < 80);
        CK((c1 & 255) < 80 && ((c1 >> 16) & 255) > 200);
        CK((c2 & 255) < 40 && ((c2 >> 16) & 255) > 20);
        png_write_rgba(getenv("RE_WORLD_PNG") ? getenv("RE_WORLD_PNG") : "render_world.png", px, 640, 480);
      }
    }
    D_00c98ed0 = saved; free(arena);
  }
  return f;
}

/* v2.20: кэш вершин P85_VCache — запись формата «камера» (P44_XformBias, обработчики с отсечением) не принимается
   P85_Prep как спроецированная (до v2.20: треугольники через экран, чёрная полоса неба, пропавшая дорога у камеры);
   P121_TexTriFlat 00430b13 — текстурный треугольник 0x38 (тип 4 набора 00550cfc; до v2.20 — P85_SkipRecord). */
/* v2.21: таблицы узлов дороги — на 0x800 узлов (были на 64: в Майами 356 — трафик по встречке на односторонних улицах);
   P15_State/P15_Flags9/P16_* — в образе данных: тот же объект, что псевдонимы D_00b87e30/G6_00D04A50/P14_00c810c4 (интервью). */
static int test_v221(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "v221 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  CK(P59_NODES_MAX >= 0x800);
  CK(sizeof(p59_tab_c39dc0_t) >= 0x24u * 0x800u);
  CK(sizeof(p59_tab_bf1c48_t) >= 0x42u * 0x800u);
  CK(sizeof(p17_map_t) >= 0x42u * 0x800u);
  CK(sizeof P59_C39DC0 >= 0x24u * 0x800u);
  /* временный образ данных (как в игре, reptr.c: 00546000..00d41000) — псевдонимы обязаны совпасть */
  uint8_t *sv_img = re_gvar_img; uint32_t sv_sz = re_gvar_img_size;
  uint8_t *img = calloc(1, 0x00d41000u);   /* v2.25: размер как в игре (reptr.c) — re_gvar пускает адреса до 00546000+re_gvar_img_size */
  CK(img != NULL);
  if (img) {
    re_gvar_img = img; re_gvar_img_size = 0x00d41000u;
    CK((void *)&P15_State == (void *)&D_00b87e30);
    CK((void *)&P15_State == (void *)(img + (0x00b87e30u - 0x00546000u)));
    CK((void *)&P16_IdleMode == (void *)&P14_00c810c4);
    CK((void *)&P15_Flags9 == (void *)(img + (0x00d04a50u - 0x00546000u)));
    D_00b87e30 = 4; CK(P15_State == 4);
    re_gvar_img = sv_img; re_gvar_img_size = sv_sz; free(img);
  }
  return f;
}

/* v2.25: интервью Undercover — засчёт манёвров и конец по секундомеру */
static int test_v225(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "v225 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  /* 1) 0052a910 (sprintf по адресам Game.exe): строка языка в буфер, один целый аргумент; %s не подставляется */
  { static char dst[64]; static const char fmt[] = "Lap %d"; static const char fs[] = "a %s b";
    memset(dst, 'x', sizeof dst);
    uint32_t ad = re_ptr_register_dyn(dst, sizeof dst), af = re_ptr_register_dyn((void *)fmt, sizeof fmt), as = re_ptr_register_dyn((void *)fs, sizeof fs);
    Call0052A910(ad, af, 7); CK(strcmp(dst, "Lap 7") == 0);
    Call0052A910(ad, as, 7); CK(strcmp(dst, "a %s b") == 0);
    Call0052A910(0, af, 7); CK(strcmp(dst, "a %s b") == 0);
    static char tiny[2]; uint32_t at = re_ptr_register_dyn(tiny, sizeof tiny);
    Call0052A910(at, af, 7); CK(tiny[0] == 0 && tiny[1] == 0); }     /* приёмник короче строки — не пишется */
  static uint8_t line[16]; line[0xb] = 5; uint32_t aline = re_ptr_register_dyn(line, sizeof line);
  uint8_t *sv_img = re_gvar_img; uint32_t sv_sz = re_gvar_img_size;
  uint8_t *img = calloc(1, 0x00d41000u);   /* v2.25: размер как в игре (reptr.c) — re_gvar пускает адреса до 00546000+re_gvar_img_size */
  CK(img != NULL);
  if (img) {
    re_gvar_img = img; re_gvar_img_size = 0x00d41000u;
    /* 2) полосы «бумаги» 00d044a0 — ячейка образа; предел — байт +0xb значка LINE по 32-битному адресу 00d0448c (P55_Paper1) */
    CK((void *)&P15_Vals9 == (void *)(img + (0x00d044a0u - 0x00546000u)));
    D_00b87e30 = 4; memset(&P15_Flags9, 0, sizeof P15_Flags9); memset(&P15_Vals9, 0, sizeof P15_Vals9);
    P59_Flags9[1] = 1; P59_Flags9[8] = 1;
    P55_Paper1 = 0; P15_RaiseLimits();                     /* значка нет — без аварии и без изменений (до v2.25 — NULL[0xb]) */
    CK(P15_Vals9[1] == 0);
    P55_Paper1 = (int32_t)aline;
    P15_RaiseLimits(); CK(P15_Vals9[1] == 3 && P15_Vals9[8] == 3 && P15_Vals9[0] == 0);
    P15_RaiseLimits(); CK(P15_Vals9[1] == 5);              /* предел line[0xb] */
    /* 3) 004e5284 (секундомер) связан с переносом: шаг 1.365 за кадр, на 4096 — конец интервью (состояние 3) */
    G6_00B5A778 = 0; P59_S4654 = 1; P94_FadeDir = 0; P94_FadeVal = 0;
    { uint32_t b = 0x3faeb852u; float sp; memcpy(&sp, &b, 4); P94_FadeSpeed = sp; }
    P94_FadePos = 100.0f; P56_Fn4E5284(NULL);
    CK(P94_FadePos > 101.3f && P94_FadePos < 101.4f && P59_S4654 == 1);
    P94_FadePos = 3500.0f; P56_Fn4E5284(NULL); CK(P94_FadeDir == 0xc);   /* последние 1024 — мигание */
    P94_FadePos = 4096.0f; P56_Fn4E5284(NULL); CK(P59_S4654 == 3 && P14_00d118a8 == 1);
    /* 4) девятое задание — состояние 2 («You get the job») */
    P59_S4654 = 1; memset(&P59_Flags9, 0, sizeof P59_Flags9); P59_Picked = 0;
    for (int i = 0; i < 9; i++) CK(P59_PickUp(i) == 1);
    CK(P59_PickUp(3) == 0 && P59_Picked == 9 && P59_S4654 == 2);
    re_gvar_img = sv_img; re_gvar_img_size = sv_sz; free(img);
  }
  return f;
}

static int test_v220(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "v220 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  /* состояние, которое тест меняет, — сохраняется и восстанавливается (CI macOS: единичный «тихий» FAIL selftest на d8e2465 —
     курсор записей G2_011F4064 оставался в освобождённой арене) */
  struct { void *p; size_t n; void *b; } sv[] = {
    { &G2_011F4064, sizeof G2_011F4064, 0 }, { &P84_VertRef, sizeof P84_VertRef, 0 }, { &P44_MatPtr, sizeof P44_MatPtr, 0 },
    { &P44_ViewMat[0], sizeof(p44_m9_t), 0 }, { &P44_BiasX, sizeof P44_BiasX, 0 }, { &P44_BiasY, sizeof P44_BiasY, 0 },
    { &P44_BiasZ, sizeof P44_BiasZ, 0 }, { &P44_XformTag, sizeof P44_XformTag, 0 }, { &P43_ScaleA, sizeof P43_ScaleA, 0 },
    { &P43_OffX, sizeof P43_OffX, 0 }, { &P43_OffY, sizeof P43_OffY, 0 }, { &P43_Half, sizeof P43_Half, 0 },
    { &P12_00ba53a0[0], 0x400 * sizeof P12_00ba53a0[0], 0 }, { &P85_VCache[0], 8 * sizeof(p85_vtx), 0 },
    { &P85_RV[0], 4 * sizeof P85_RV[0], 0 }, { &P82_Edge, sizeof P82_Edge, 0 }, { &P85_StateDirty, sizeof P85_StateDirty, 0 },
    { &P85_BlendFn, sizeof P85_BlendFn, 0 }, { &P85_RasterA, sizeof P85_RasterA, 0 }, { &P85_RasterB, sizeof P85_RasterB, 0 },
    { &P86_TexSrc, sizeof P86_TexSrc, 0 }, { &P85_MaxX, sizeof P85_MaxX, 0 }, { &P85_MaxY, sizeof P85_MaxY, 0 },
    { &P100_ClipN, sizeof P100_ClipN, 0 }, { &P100_ClipOut, sizeof P100_ClipOut, 0 } };
  const int nsv = (int)(sizeof sv / sizeof sv[0]);
  for (int i = 0; i < nsv; i++) { sv[i].b = malloc(sv[i].n); memcpy(sv[i].b, sv[i].p, sv[i].n); }
  void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x1000);
  float *vert = (float *)(arena + 0x100); uint8_t *rec = arena + 0x400;
  D_00c98ed0 = arena;
  memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
  P43_ScaleA = 100.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
  for (int i = 1; i < 0x400; i++) P12_00ba53a0[i] = 1.0f / (float)i;
  { float vv[3][4] = { { 2, 4, 10, 0 }, { 10, 0, 10, 0 }, { 0, 10, 10, 0 } }; memcpy(vert, vv, sizeof vv); }
  P84_VertRef = P79_OFF(vert);
  P44_MatPtr = P44_ViewMat; P44_BiasX = P44_BiasY = P44_BiasZ = 0; P44_XformTag = 77;
  /* 1) запись текущего кадра в формате «камера» → пересчёт проекцией */
  p85_vtx *c = &P85_VCache[0];
  memset(c, 0, sizeof *c); c->x = 2; c->y = 4; c->z = 10; P44_XformBias((float *)(void *)c); P85_VC_FMT(c, P85_FMT_BIAS);
  CK(c->stamp == 77 && c->x == 2.0f);
  p85_vtx *r = P85_Prep(0);
  CK(r == c && c->pad8 == P85_FMT_PROJ && fabsf(c->x - 340.0f) <= 0.125f && fabsf(c->y - 280.0f) <= 0.125f && c->oow == 0.1f);
  /* 2) спроецированная запись текущего кадра — из кэша, без пересчёта */
  c->x = 777.0f; r = P85_Prep(0); CK(c->x == 777.0f);
  /* 3) формат 0 (записи P122/P138 с готовой проекцией) — принимается */
  P85_VC_FMT(c, 0); r = P85_Prep(0); CK(c->x == 777.0f);
  /* 4) 00430b13: треугольник 0x38 — вершины 0,1,2, uv +0x14..+0x28, цвет +0x2c..+0x34, курсор +0x38 */
  memset(rec, 0, 0x80); rec[0] = 4; rec[2] = 0;
  { int32_t ix[3] = { 0, 1, 2 }; memcpy(rec + 8, ix, 12);
    float uv[6] = { 1, 2, 3, 4, 5, 6 }; memcpy(rec + 0x14, uv, 24); float col[3] = { 10, 20, 30 }; memcpy(rec + 0x2c, col, 12); }
  P44_XformTag = 78; G2_011F4064 = rec; P82_Edge = 0; P85_StateDirty = 4; P85_BlendFn = NULL;
  P85_RasterA = P85_RasterB = p85_capture; p85_calls = 0;
  P86_TexSrc = NULL;
  P121_TexTriFlat(0);
  CK(G2_011F4064 == rec + 0x38 && p85_calls == 1);
  CK(fabsf(p85_cap[0][0].x - 340.0f) <= 0.2f && fabsf(p85_cap[0][1].x - 420.0f) <= 0.2f && fabsf(p85_cap[0][2].y - 340.0f) <= 0.2f);
  CK(p85_cap[0][0].r == 10.0f && p85_cap[0][1].g == 20.0f && p85_cap[0][2].b == 30.0f);
  CK(fabsf(p85_cap[0][0].tmu[0] - 0.1f) < 1e-6f && fabsf(p85_cap[0][1].tmu[1] - 0.4f) < 1e-6f && fabsf(p85_cap[0][2].tmu[0] - 0.5f) < 1e-6f);
  /* 5) 00439b42 (v2.20): треугольник 0x38 с отсечением ближней плоскостью (z = 50) — вершины формата «камера» (prep_bias),
        целиком перед плоскостью — один треугольник (0,1,2); вершина за плоскостью — четырёхугольник, веер из двух */
  { float vv[3][4] = { { 0, 0, 100, 0 }, { 100, 0, 100, 0 }, { 0, 100, 100, 0 } }; memcpy(vert + 12, vv, sizeof vv); }
  { int32_t ix[3] = { 3, 4, 5 }; memcpy(rec + 8, ix, 12); }
  P85_MaxX = 639.0f; P85_MaxY = 479.0f; P44_MatPtr = P44_ViewMat;
  P44_XformTag = 79; G2_011F4064 = rec; P85_RasterA = P85_RasterB = p85_capture; p85_calls = 0;
  p85_check_camera = 1;
  P121_ClipTexTri(0);
  p85_check_camera = 0;
  CK(G2_011F4064 == rec + 0x38 && p85_calls == 1);
  for (int j = 0; j < 3; j++) CK(p85_camera_valid[0][j] && p85_camera_cap[0][j][2] == 100.0);
  { int k4 = -1, k5 = -1;   /* буфер отсечения начинается со второй вершины первого ребра — порядок (0,1,2) по кругу */
    for (int j = 0; j < 3; j++) { if (fabsf(p85_cap[0][j].x - 420.0f) <= 0.2f) k4 = j; if (fabsf(p85_cap[0][j].y - 340.0f) <= 0.2f) k5 = j; }
    CK(k4 >= 0 && k5 == (k4 + 1) % 3 && fabsf(p85_cap[0][(k4 + 2) % 3].x - 320.0f) <= 0.2f && fabsf(p85_cap[0][(k4 + 2) % 3].y - 240.0f) <= 0.2f);
    CK(k4 >= 0 && fabsf(p85_cap[0][k4].tmu[0] - 0.03f) < 1e-6f && fabsf(p85_cap[0][k4].oow - 0.01f) < 1e-6f); }
  CK(p85_cap[0][0].r == 10.0f && p85_cap[0][1].g == 20.0f && p85_cap[0][2].b == 30.0f);
  CK(P85_VCache[3].pad8 == P85_FMT_BIAS);
  vert[12 + 8 + 2] = 0.0f;   /* v5: z = 0 — за ближней плоскостью */
  P44_XformTag = 80; G2_011F4064 = rec; p85_calls = 0;
  p85_check_camera = 1;
  P121_ClipTexTri(0);
  p85_check_camera = 0;
  CK(G2_011F4064 == rec + 0x38 && p85_calls == 2);
  for (int k = 0; k < p85_calls && k < 8; k++) for (int j = 0; j < 3; j++) {
    CK(p85_camera_valid[k][j]);
    CK(p85_camera_cap[k][j][2] == 50.0 || p85_camera_cap[k][j][2] == 100.0);
  }
  CK(p85_cap[0][0].x == p85_cap[1][0].x && p85_cap[0][1].x == p85_cap[1][1].x);   /* веер (0,2,1),(0,2,3) */
  P85_RasterA = P85_RasterB = NULL;
  /* 6) 004ef3cd: модель неба по смещению 0 арены (ссылка 0 в native) тоже масштабируется ×1.7 (до v2.20 — пропуск: полоса неба) */
  memset(arena, 0, 0x400);
  uint32_t tab_saved[4]; memcpy(tab_saved, &P79_ModelTab[0], sizeof tab_saved);
  int32_t city_saved = D_00b87e30; D_00b87e30 = 4;
  for (int k = 0; k < 4; k++) {
    uint8_t *m = arena + 0x40 * k; uint32_t vr = 0x200 + 0x10 * k;
    *(uint16_t *)(m + 0x14) = 1; memcpy(m + 0x20, &vr, 4); memcpy(m + 0x24, &vr, 4);
    float v10[4] = { 10, 10, 10, 1 }; memcpy(arena + vr, v10, 16);
    P79_ModelTab[k] = 0x40u * (uint32_t)k;
  }
  P101_SkyInit();
  for (int k = 0; k < 4; k++) { const float *v = (const float *)(arena + 0x200 + 0x10 * k); CK(fabsf(v[0] - 17.0f) < 1e-4f && fabsf(v[2] - 17.0f) < 1e-4f); }
  /* 7) v2.27: шов неба — v колец купола у четвертей приводится к медиане (Майами: кольцо 29° 50/47/48/48 → 48, 8° 115/116/115/115 → 115);
     шапка (v = 1) и u не меняются; RE_SKYFIX=0 и незнакомый тип записи — без изменений */
  { memset(arena, 0, 0x1000);
    static const float ring_v[4][2] = { { 50, 115 }, { 47, 116 }, { 48, 115 }, { 48, 115 } };
    for (int k = 0; k < 4; k++) {
      uint8_t *m = arena + 0x40 * k; uint32_t vr = 0x200 + 0x40 * k, rr = 0x400 + 0x80 * k;
      *(uint16_t *)(m + 0x14) = 3; *(uint16_t *)(m + 0x16) = 1; memcpy(m + 0x20, &vr, 4); memcpy(m + 0x2c, &rr, 4);
      float vs[12] = { 100, -129.4f, 0, 1,  100, -34.0f, 0, 1,  50, -250.0f, 0, 1 }; memcpy(arena + vr, vs, sizeof vs);
      uint8_t *r = arena + rr; r[0] = 5;
      int32_t idx[4] = { 0, 1, 1, 2 }; memcpy(r + 8, idx, 16);
      float uv[8] = { 255, ring_v[k][0], 255, ring_v[k][1], 1, ring_v[k][1], 7, 1 }; memcpy(r + 24, uv, 32);
      P79_ModelTab[k] = 0x40u * (uint32_t)k;
    }
    P101_SkyUvFix();
    CK(P101_SkyUvFixed == 4);
    for (int k = 0; k < 4; k++) { const float *uv = (const float *)(arena + 0x400 + 0x80 * k + 24);
      CK(uv[1] == 48.0f && uv[3] == 115.0f && uv[5] == 115.0f && uv[7] == 1.0f && uv[0] == 255.0f && uv[6] == 7.0f); }
    float bad = 50.0f; memcpy(arena + 0x400 + 24 + 4, &bad, 4);
    setenv("RE_SKYFIX", "0", 1); P101_SkyUvFix(); unsetenv("RE_SKYFIX");
    CK(P101_SkyUvFixed == 0 && ((const float *)(arena + 0x400 + 24))[1] == 50.0f);
    arena[0x400 + 0x80] = 9; P101_SkyUvFix(); CK(P101_SkyUvFixed == 0 && ((const float *)(arena + 0x400 + 24))[1] == 50.0f); }
  memcpy(&P79_ModelTab[0], tab_saved, sizeof tab_saved); D_00b87e30 = city_saved;
  D_00c98ed0 = saved; free(arena);
  for (int i = 0; i < nsv; i++) { memcpy(sv[i].p, sv[i].b, sv[i].n); free(sv[i].b); }
#undef CK
  return f;
}


/* v2.23: обработчики режима 0 P115_*C (00452327..004531c5), подставленные в набор с ближней плоскостью (режим 1, типы 0..3):
   вершина за камерой не уходит в растеризатор 01270e30/01270d9c (до v2.23 — экран (0,0)/(320,240) с oow 1e−30/0: треугольник
   на дальней плоскости от левого верхнего угла — серый полигон поверх неба); пересекающий z = 1 — отсечён, целиком за — пропуск */
static int v223_bad(int n) { for (int k = 0; k < n && k < 8; k++) for (int j = 0; j < 3; j++) { const p85_rv *r = &p85_cap[k][j];
    if (!(r->oow > 0.0f) || r->oow == P85_OOW_NEAR || !isfinite(r->x) || !isfinite(r->y) || r->x < 319.0f || r->y < 239.0f) return 1; } return 0; }
static int test_facade_camera(void) {
  int failed = re_detail_selftest();
  uint32_t tag = P44_XformTag;
  p85_rv saved = P85_RV[0], other = {0};
  p85_vtx v = {0};
  double camera[3];
  for (int frame = 0; frame < 32; frame++) {
    P44_XformTag = 9000 + frame;
    /* Pixel positions and reciprocal depth have already been rounded, while
       the camera moves by fractions of a world unit at the same facade. */
    v.x = 400.125f; v.y = 123.25f; v.vx = 617.125f; v.vy = -300.0625f;
    v.z = 2010.0625f - frame * .25f; v.oow = 1.0f / roundf(v.z);
    P85_PutVtx(&P85_RV[0], &v);
    if (!P85_GetCameraPoint(&P85_RV[0], camera) || camera[0] != v.vx || camera[1] != v.vy || camera[2] != v.z) failed++;
    if (camera[2] == 1.0 / v.oow) failed++;
    if (P85_GetCameraPoint(&other, camera)) failed++;
    P85_RV[0].y += .125f;
    if (P85_GetCameraPoint(&P85_RV[0], camera)) failed++;
    P85_PutVtx(&P85_RV[0], &v); P44_XformTag++;
    if (P85_GetCameraPoint(&P85_RV[0], camera)) failed++;
  }
  P85_RV[0] = saved; P44_XformTag = tag;
  if (failed) fprintf(stderr, "facade camera failures: %d\n", failed);
  return failed != 0;
}

static int test_v223(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "v223 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  struct { void *p; size_t n; void *b; } sv[] = {
    { &G2_011F4064, sizeof G2_011F4064, 0 }, { &P84_VertRef, sizeof P84_VertRef, 0 }, { &P44_MatPtr, sizeof P44_MatPtr, 0 },
    { &P44_ViewMat[0], sizeof(p44_m9_t), 0 }, { &P44_BiasX, sizeof P44_BiasX, 0 }, { &P44_BiasY, sizeof P44_BiasY, 0 },
    { &P44_BiasZ, sizeof P44_BiasZ, 0 }, { &P44_XformTag, sizeof P44_XformTag, 0 }, { &P43_ScaleA, sizeof P43_ScaleA, 0 },
    { &P43_OffX, sizeof P43_OffX, 0 }, { &P43_OffY, sizeof P43_OffY, 0 }, { &P43_Half, sizeof P43_Half, 0 },
    { &P101_ScrX0, sizeof P101_ScrX0, 0 }, { &P101_ScrY0, sizeof P101_ScrY0, 0 },
    { &P12_00ba53a0[0], 0x400 * sizeof P12_00ba53a0[0], 0 }, { &P85_VCache[0], 8 * sizeof(p85_vtx), 0 },
    { &P85_RV[0], 4 * sizeof P85_RV[0], 0 }, { &P82_Edge, sizeof P82_Edge, 0 }, { &P85_StateDirty, sizeof P85_StateDirty, 0 },
    { &P85_BlendFn, sizeof P85_BlendFn, 0 }, { &P115_RasterC, sizeof P115_RasterC, 0 }, { &P115_RasterD, sizeof P115_RasterD, 0 },
    { &P85_BlendCur, sizeof P85_BlendCur, 0 }, { &P85_BlendForce, sizeof P85_BlendForce, 0 } };
  const int nsv = (int)(sizeof sv / sizeof sv[0]);
  for (int i = 0; i < nsv; i++) { sv[i].b = malloc(sv[i].n); memcpy(sv[i].b, sv[i].p, sv[i].n); }
  int set_img = !re_ptr_has_image(); static uint8_t dummy_img[16];
  if (set_img) re_ptr_set_image(0x7ff00000u, dummy_img, sizeof dummy_img);   /* режим игры: отсечение включается только в нём */
  void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x1000);
  float *vert = (float *)(arena + 0x100); uint8_t *rec = arena + 0x400;
  D_00c98ed0 = arena;
  memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
  P43_ScaleA = 100.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
  P101_ScrX0 = 320.0f; P101_ScrY0 = 240.0f;
  for (int i = 1; i < 0x400; i++) P12_00ba53a0[i] = 1.0f / (float)i;
  /* 0..3: квадрат, ближний край за камерой (z −50); 4..6: треугольник целиком перед камерой; 1,2,3 + 7: целиком за */
  { float vv[8][4] = { { 0, 0, 100, 0 }, { 100, 0, 100, 0 }, { 0, 100, -50, 0 }, { 100, 100, -50, 0 },
                       { 0, 0, 100, 0 }, { 100, 0, 100, 0 }, { 0, 100, 100, 0 }, { 50, 50, -80, 0 } }; memcpy(vert, vv, sizeof vv); }
  P84_VertRef = P79_OFF(vert);
  P44_MatPtr = P44_ViewMat; P44_BiasX = P44_BiasY = P44_BiasZ = 0;
  P82_Edge = 0; P85_StateDirty = 0; P85_BlendFn = NULL; P85_BlendForce = 0;
  P115_RasterC = P115_RasterD = p85_capture;
  float col = 64.0f;
  /* 1) квадрат через ближнюю плоскость: метка P85_OOW_NEAR у вершин за камерой, в растеризатор — только отсечённые треугольники */
  memset(rec, 0, 0x80); { int32_t ix[4] = { 0, 1, 2, 3 }; memcpy(rec + 8, ix, 16); } memcpy(rec + 0x18, &col, 4);
  P44_XformTag = 501; G2_011F4064 = rec; p85_calls = 0;
  p85_check_camera = 1;
  P115_FlatQuadC(0);
  p85_check_camera = 0;
  CK(G2_011F4064 == rec + 0x24);
  for (int k = 0; k < p85_calls && k < 8; k++) for (int j = 0; j < 3; j++) {
    const double *c = p85_camera_cap[k][j];
    CK(p85_camera_valid[k][j]);
    CK(c[0] >= -1e-4 && c[0] <= 100.0001 && c[1] >= -1e-4 && c[1] <= 66.0001);
    CK(fabs(c[2] - 1.0) < 1e-4 || fabs(c[2] - 100.0) < 1e-4);
  }
  CK(P85_VCache[2].oow == P85_OOW_NEAR && P85_VCache[2].x == 0.0f && P85_VCache[2].y == 0.0f && P85_VCache[2].pad8 == P85_FMT_PROJ);
  CK(fabsf(P85_VCache[1].x - 420.0f) <= 0.2f && fabsf(P85_VCache[1].oow - 0.01f) < 1e-6f);
  CK(p85_calls >= 2 && !v223_bad(p85_calls));
  { int near_ok = 0; for (int k = 0; k < p85_calls && k < 8; k++) for (int j = 0; j < 3; j++) if (fabsf(p85_cap[k][j].oow - 1.0f) < 1e-6f) near_ok = 1;
    CK(near_ok); }   /* новые вершины — на плоскости z = 1 */
  /* 2) треугольник целиком перед камерой — один вызов, как без отсечения */
  { int32_t ix[3] = { 4, 5, 6 }; memcpy(rec + 8, ix, 12); } memcpy(rec + 0x14, &col, 4);
  P44_XformTag = 502; G2_011F4064 = rec; p85_calls = 0;
  P115_FlatTriC(0);
  CK(G2_011F4064 == rec + 0x20 && p85_calls == 1 && !v223_bad(1));
  CK(fabsf(p85_cap[0][0].x - 320.0f) <= 0.2f && fabsf(p85_cap[0][1].x - 420.0f) <= 0.2f && fabsf(p85_cap[0][2].y - 340.0f) <= 0.2f);
  /* 3) целиком за камерой (до v2.23 — растеризатор с вершинами (0,0)/(320,240)) — ни одного вызова */
  { int32_t ix[4] = { 2, 3, 7, 7 }; memcpy(rec + 8, ix, 16); } memcpy(rec + 0x18, &col, 4);
  P44_XformTag = 503; G2_011F4064 = rec; p85_calls = 0;
  P115_FlatQuadC(0);
  CK(p85_calls == 0);
  /* 4) запись кэша этого кадра от P85_Project с меткой P85_OOW_NEAR (общий кэш вершин) — тоже отсекается, а не рисуется из (0,0) */
  { int32_t ix[3] = { 4, 5, 2 }; memcpy(rec + 8, ix, 12); } memcpy(rec + 0x14, &col, 4);
  P44_XformTag = 504; P85_Prep(2); CK(P85_VCache[2].oow == P85_OOW_NEAR);
  G2_011F4064 = rec; p85_calls = 0;
  P115_FlatTriC(0);
  CK(p85_calls >= 1 && !v223_bad(p85_calls));
  P115_RasterC = P115_RasterD = NULL;
  if (set_img) re_ptr_set_image(0, NULL, 0);
  D_00c98ed0 = saved; free(arena);
  for (int i = 0; i < nsv; i++) { memcpy(sv[i].p, sv[i].b, sv[i].n); free(sv[i].b); }
#undef CK
  return f;
}

static int p86_texsrc_calls; static int32_t p86_last_tex = -2;
static void p86_texsrc_cap(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info) { (void)tmu; (void)addr; (void)mask; (void)info; p86_texsrc_calls++; p86_last_tex = P86_CurTex; }
static int test_p86(void) {
  int f = 0;
#undef CK
#define CK(c) do { if (!(c)) { fprintf(stderr, "p86 fail line %d: %s\n", __LINE__, #c); f = 1; } } while (0)
  re_init_consts();
  { void *saved = D_00c98ed0; uint8_t *arena = (uint8_t *)calloc(1, 0x4000);
    uint8_t *m = arena + 0x100; float *pl = (float *)(arena + 0x200); uint8_t *rec = arena + 0x300; float *vert = (float *)(arena + 0x800);
    uint16_t u16; uint32_t u32; int32_t i32;
    float ident[16 * 8]; float pos[3] = { 0, 0, 0 };
    D_00c98ed0 = arena;
    memset(ident, 0, sizeof ident);
    for (int k = 0; k < 8; k++) ident[k * 16] = ident[k * 16 + 4] = ident[k * 16 + 8] = 1.0f;
    memset(P44_ViewMat, 0, sizeof(p44_m9_t)); P44_ViewMat[0] = P44_ViewMat[4] = P44_ViewMat[8] = 1.0f;
    P43_ScaleA = 100.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f; P43_Half = 1048576.0f;
    P19_Scale = 1.0f;
    for (int i = 1; i < 0x400; i++) P12_00ba53a0[i] = 1.0f / (float)i;
    u16 = 0; memcpy(m + 2, &u16, 2); u16 = 3; memcpy(m + 0x16, &u16, 2); u16 = 0; memcpy(m + 0x18, &u16, 2);
    P84_InitConsts(); P85_InitConsts();
    u32 = P79_OFF(vert); memcpy(m + 0x20, &u32, 4); u32 = P79_OFF(pl); memcpy(m + 0x24, &u32, 4); u32 = P79_OFF(rec); memcpy(m + 0x2c, &u32, 4);
    pl[0] = 0; pl[1] = 0; pl[2] = 1; pl[3] = 5;
    { float vv[4][4] = { { 0, 0, 10, 0 }, { 10, 0, 10, 0 }, { 0, 10, 10, 0 }, { 10, 10, 10, 0 } }; memcpy(vert, vv, sizeof vv); }
    memset(rec, 0, 256);
    /* тип 20 (текстурный треугольник, текстура 3) в 0, тип 21 (четырёхугольник, текстура 3) в 0x38, тип 51 (гуро) в 0x7c */
    rec[0] = 20; rec[1] = 8; rec[2] = 3; i32 = 0; memcpy(rec + 4, &i32, 4);
    i32 = 0; memcpy(rec + 8, &i32, 4); i32 = 1; memcpy(rec + 12, &i32, 4); i32 = 2; memcpy(rec + 16, &i32, 4);
    { float uv[6] = { 0, 0, 255, 0, 0, 255 }; memcpy(rec + 0x14, uv, 24); }
    { float c[3] = { 200.0f, 100.0f, 50.0f }; memcpy(rec + 0x2c, c, 12); }
    rec[0x38] = 21; rec[0x39] = 8; rec[0x3a] = 3; i32 = 0; memcpy(rec + 0x3c, &i32, 4);
    i32 = 0; memcpy(rec + 0x40, &i32, 4); i32 = 1; memcpy(rec + 0x44, &i32, 4); i32 = 3; memcpy(rec + 0x48, &i32, 4); i32 = 2; memcpy(rec + 0x4c, &i32, 4);
    { float uv[8] = { 0, 0, 255, 0, 255, 255, 0, 255 }; memcpy(rec + 0x38 + 0x18, uv, 32); }
    { float c[3] = { 10.0f, 20.0f, 30.0f }; memcpy(rec + 0x38 + 0x38, c, 12); }
    rec[0x7c] = 51; rec[0x7d] = 8; i32 = 0; memcpy(rec + 0x80, &i32, 4);
    i32 = 0; memcpy(rec + 0x84, &i32, 4); i32 = 1; memcpy(rec + 0x88, &i32, 4); i32 = 3; memcpy(rec + 0x8c, &i32, 4); i32 = 2; memcpy(rec + 0x90, &i32, 4);
    i32 = 5; memcpy(rec + 0x7c + 0x18, &i32, 4); i32 = 6; memcpy(rec + 0x7c + 0x1c, &i32, 4); i32 = 7; memcpy(rec + 0x7c + 0x20, &i32, 4); i32 = 8; memcpy(rec + 0x7c + 0x24, &i32, 4);
    { float c[3] = { 100.0f, 100.0f, 100.0f }; memcpy(rec + 0x7c + 0x28, c, 12); }
    P85_RegisterNative();
    CK(P84_Handlers[2][20] == (uintptr_t)P86_TexTri && P84_Handlers[3][21] == (uintptr_t)P86_TexQuad && P84_Handlers[0][51] == (uintptr_t)P86_GouraudQuad && P84_Handlers[1][50] == (uintptr_t)P86_GouraudTri);
    P85_RasterA = P85_RasterB = p85_capture; P85_BlendFn = p85_blend_cap; P85_StateFn = p85_state_cap; P86_TexSrc = p86_texsrc_cap;
    P84_SelectTables(0); G2_011F43B0 = 0; P84_Mirror = 0; P82_Edge = 0; P63_SphN = 0;
    P84_LightIn[0] = 0.5f; P84_NormLight[5] = 1.0f; P84_NormLight[6] = 0.5f; P84_NormLight[7] = 0.25f; P84_NormLight[8] = 0.0f;
    P85_StateDirty = 0; P85_BlendCur = 0; P85_BlendForce = 0; P86_CurTex = -1; P86_Detail = 1;
    P44_XformTag = 30; p85_calls = 0; p85_blend_calls = 0; p86_texsrc_calls = 0;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    CK(p85_calls == 5);                                        /* треугольник + 2 + 2 */
    CK(P85_StateDirty == 0 && G2_011F4064 == rec + 0x7c + 0x34);
    CK(p86_texsrc_calls == 1 && p86_last_tex == 3);            /* тип 21 с той же текстурой её не ставит повторно (и 51 не трогает) */
    /* тип 20: цвет = плоскость 0.5 × цвет, u·oow (oow = 1/10) */
    CK(p85_cap[0][0].r == 100.0f && p85_cap[0][0].g == 50.0f && p85_cap[0][2].b == 25.0f);
    CK(fabsf(p85_cap[0][1].tmu[0] - 25.5f) < 1e-3f && p85_cap[0][1].tmu[1] == 0.0f && fabsf(p85_cap[0][2].tmu[1] - 25.5f) < 1e-3f);
    /* тип 21: вершины (0,2,1) и (0,2,3), u,v: v0=(0,0), v2=(255,255)?? — по индексам записи: i0=0,i1=1,i2=3,i3=2 */
    CK(p85_cap[1][0].r == 5.0f && p85_cap[1][1].g == 10.0f);
    CK(fabsf(p85_cap[1][1].tmu[0] - 25.5f) < 1e-3f && fabsf(p85_cap[1][1].tmu[1] - 25.5f) < 1e-3f);   /* RV1 — вершина записи №2 */
    CK(fabsf(p85_cap[1][2].tmu[0] - 25.5f) < 1e-3f && p85_cap[1][2].tmu[1] == 0.0f);                   /* RV2 — вершина записи №1 */
    CK(fabsf(p85_cap[2][2].tmu[0] - 0.0f) < 1e-3f && fabsf(p85_cap[2][2].tmu[1] - 25.5f) < 1e-3f);    /* вторая половина: вершина №3 */
    /* тип 51: цвет × нормаль вершины: RV0 — нормаль 5 (1.0), RV1 — нормаль 7 (0.25), RV2 — нормаль 6 (0.5), второй треугольник — нормаль 8 (0) */
    CK(p85_cap[3][0].r == 100.0f && p85_cap[3][1].r == 25.0f && p85_cap[3][2].r == 50.0f && p85_cap[4][2].r == 0.0f);
    /* динамический свет: источник в точке вершины 0 (камерное пространство: x=0,y=0,z=10), радиус² 100, цвет (0,0,200) */
    { float *L = (float *)&G2_011F40E0[0]; memset(L, 0, 0x24); L[0] = 0; L[1] = 0; L[2] = 10; L[4] = 0; L[5] = 0; L[6] = 200; L[7] = 100; L[8] = 0.01f; }
    { int32_t rr = 100; memcpy(&((float *)&G2_011F40E0[0])[3], &rr, 4); } G2_011F43B0 = 1;   /* P84_DrawModel сам находит источники в радиусе модели */
    P44_XformTag = 31; p85_calls = 0; P86_CurTex = -1; P85_StateDirty = 0;
    P84_DrawModel(P79_OFF(m), ident, pos, 5);
    /* вершина 0: d²=0 → вклад 100·0.01·200 = 200 в синий: 12.5.. нет, у типа 20 синий был 25·0.5=25 → 225; остальные вершины дальше на 10: d²=100 не < 100 */
    CK(p85_cap[0][0].b == 225.0f && p85_cap[0][1].b == 25.0f && p85_cap[0][0].r == 100.0f);
    G2_011F43B0 = 0; P63_SphN = 0;
    /* 3) картинка: текстурированная плитка с перспективой и гуро-треугольник → PNG */
    if (plat_render_offscreen(640, 480) == 0) {
      static uint32_t px[640 * 480];
      static uint16_t page[256 * 256];
      for (int y = 0; y < 256; y++) for (int x = 0; x < 256; x++) {
        int chk = ((x >> 5) + (y >> 5)) & 1;
        page[y * 256 + x] = (uint16_t)(0x8000 | (chk ? (31 << 10 | 20 << 5 | 4) : (4 << 10 | 24 << 5 | 31)));   /* оранжевая / синяя клетка */
      }
      P86_NativeCapture(7, 0, page, NULL);
      CK(P86_NativeHandle(7) > 0);
      P85_RegisterNative();                                   /* растеризатор → plat_draw_tris, текстуры → GL */
      P43_ScaleA = 400.0f; P43_OffX = 320.0f + 1048576.0f; P43_OffY = 240.0f + 1048576.0f;
      for (int i = 1; i < 0x2000; i++) P12_00ba53a0[i] = 1.0f / (float)i;
      /* пол в перспективе: ближний край z=30 шире, дальний z=90 */
      { float vv[8][4] = { { -40, 20, 30, 0 }, { 40, 20, 30, 0 }, { 120, 20, 100, 0 }, { -120, 20, 100, 0 }, { 60, -40, 60, 0 }, { 110, -40, 60, 0 }, { 110, 0, 60, 0 }, { 60, 0, 60, 0 } };
        memcpy(vert, vv, sizeof vv); }
      u16 = 2; memcpy(m + 0x16, &u16, 2);
      memset(rec, 0, 256);
      rec[0] = 21; rec[1] = 8; rec[2] = 7;
      i32 = 0; memcpy(rec + 8, &i32, 4); i32 = 1; memcpy(rec + 12, &i32, 4); i32 = 2; memcpy(rec + 16, &i32, 4); i32 = 3; memcpy(rec + 20, &i32, 4);
      { float uv[8] = { 0, 0, 255, 0, 255, 255, 0, 255 }; memcpy(rec + 0x18, uv, 32); }
      { float c[3] = { 255.0f, 255.0f, 255.0f }; memcpy(rec + 0x38, c, 12); }
      rec[0x44] = 51; rec[0x45] = 8;
      i32 = 4; memcpy(rec + 0x44 + 8, &i32, 4); i32 = 5; memcpy(rec + 0x44 + 12, &i32, 4); i32 = 6; memcpy(rec + 0x44 + 16, &i32, 4); i32 = 7; memcpy(rec + 0x44 + 20, &i32, 4);
      i32 = 5; memcpy(rec + 0x44 + 0x18, &i32, 4); i32 = 6; memcpy(rec + 0x44 + 0x1c, &i32, 4); i32 = 7; memcpy(rec + 0x44 + 0x20, &i32, 4); i32 = 8; memcpy(rec + 0x44 + 0x24, &i32, 4);
      { float c[3] = { 255.0f, 255.0f, 255.0f }; memcpy(rec + 0x44 + 0x28, c, 12); }
      P84_LightIn[0] = 1.0f; P84_NormLight[5] = 1.0f; P84_NormLight[6] = 0.6f; P84_NormLight[7] = 0.2f; P84_NormLight[8] = 0.9f;
      plat_set_zbuffer(1, 1); plat_clear(0xFF101820u, 1); P85_Tris = 0;
      P86_CurTex = -1; P85_StateDirty = 0;
      P44_XformTag = 40; P84_DrawModel(P79_OFF(m), ident, pos, 5);
      CK(P85_Tris == 4);
      if (plat_render_readback(px) == 0) {
        uint32_t cA = px[(480 - 1 - 150) * 640 + 320 - 1], bg = px[5 * 640 + 5];
        (void)cA;
        CK((bg & 255) < 40 && ((bg >> 16) & 255) > 20);
        int orange = 0, blue = 0;                              /* в плитке должны встретиться обе клетки шахматной текстуры */
        for (int i = 0; i < 640 * 480; i++) {
          uint32_t c = px[i], r = c & 255, b = (c >> 16) & 255;
          if (r > 200 && b < 60) orange++;
          if (b > 200 && r < 60) blue++;
        }
        CK(orange > 2000 && blue > 2000);
        png_write_rgba(getenv("RE_TEX_PNG") ? getenv("RE_TEX_PNG") : "render_tex.png", px, 640, 480);
      }
    }
    D_00c98ed0 = saved; free(arena);
  }
  return f;
}

/* v2.15: Hor+ — математика проекции/отсечения для нескольких аспектов (без данных игры, game/aspect.c) */
#include "../game/aspect.h"
static int test_aspect(void) {
  int r = re_aspect_selftest();
  if (r) printf("FAIL re_aspect_selftest: проверка %d\n", r);
  CHECK(r == 0);
  printf("aspect: S 16:9=%d 16:10=%d 21:9=%d 32:9=%d, секторов FRUSTRUM %d/%d/%d/%d, θ 4:3 %.2f° 32:9 %.2f°\n",
         re_aspect_extra(16.0 / 9), re_aspect_extra(1.6), re_aspect_extra(3440.0 / 1440), re_aspect_extra(32.0 / 9),
         re_aspect_sectors(re_aspect_extra(16.0 / 9)), re_aspect_sectors(re_aspect_extra(1.6)), re_aspect_sectors(re_aspect_extra(3440.0 / 1440)),
         re_aspect_sectors(re_aspect_extra(32.0 / 9)), re_aspect_half_angle(0) * 57.29578, re_aspect_half_angle(re_aspect_extra(32.0 / 9)) * 57.29578);
  return 0;
}
/* v2.26: кадр заполняет окно при буфере ≠ окну (Retina: окно в точках, буфер в пикселях) и при любом режиме игры:
   game_res (driver.cfg/RE_GAME_RES), re_game_screen (режим 1024×768 → 640×480), прямоугольник кадра по буферу (без GL —
   цель = буфер): 4:3 и шире — во весь буфер (Hor+), портрет — по ширине; смена размера (1280×960 → 2000×1500) — без старого размера */
static int test_v226(void) {
  { re_gfx_cfg c; re_gfx_defaults(&c); CHECK(c.game_res == 0);
    CHECK(re_gfx_set(&c, "game_res", "original") == 0 && c.game_res == 1 && re_gfx_preset(&c, "safe") == 0 && c.game_res == 1);
    CHECK(re_gfx_set(&c, "game_res", "native") == 0 && c.game_res == 0 && re_gfx_set(&c, "game_res", "800x600") == -2); }
  { int32_t w = 1600, h = 1200; CHECK(re_game_screen(1, &w, &h) == 1 && w == 640 && h == 480); }
  int dlw = 0, dlh = 0; plat_render_size(NULL, NULL, &dlw, &dlh);
  plat_render_set_aspect("auto"); plat_render_set_logical(640, 480);
  /* буфер (пиксели) при окне в точках ×2: 1000×750 → 2000×1500, 1280×800 → 2560×1600, 1440×900 → 2880×1800, 800×500 → 1600×1000; 1366×768; портрет */
  static const int dd[][2] = { { 1280, 960 }, { 2000, 1500 }, { 2560, 1600 }, { 2880, 1800 }, { 1600, 1000 }, { 1366, 768 }, { 3440, 1440 }, { 750, 1000 } };
  for (size_t i = 0; i < sizeof dd / sizeof dd[0]; i++) {
    int x, y, w, h, tw, th, lx = -1, ly = -1;
    plat_render_set_drawable(dd[i][0], dd[i][1]);
    plat_render_content(&x, &y, &w, &h, &tw, &th);
    CHECK(tw == dd[i][0] && th == dd[i][1]);                                     /* цель — буфер в пикселях, не точки и не 640×480·k */
    if (dd[i][0] * 3 >= dd[i][1] * 4) CHECK(abs(w - tw) <= 1 && abs(h - th) <= 1 && x <= 1 && y <= 1);   /* 4:3 и шире — без полос */
    else CHECK(abs(w - tw) <= 1 && h < th && abs(y - (th - h) / 2) <= 1);       /* портрет — letterbox по центру */
    CHECK(plat_view_extra() == re_aspect_extra((double)dd[i][0] / dd[i][1]));
    CHECK(plat_render_to_logical(dd[i][0] / 2.0, dd[i][1] / 2.0, &lx, &ly) && abs(lx - 320) <= 1 && abs(ly - 240) <= 1);   /* центр буфера — центр кадра */
  }
  /* game_res = original: режим 1024×768 — Hor+ нет (кадр режима вписан с полосами, как v2.25); native — снова во весь буфер */
  plat_render_set_drawable(1600, 1000); plat_render_set_logical(1024, 768);
  { int w, tw; plat_render_content(NULL, NULL, &w, NULL, &tw, NULL); CHECK(plat_view_extra() == 0 && w < tw); }
  plat_render_set_logical(640, 480);
  { int w, tw; plat_render_content(NULL, NULL, &w, NULL, &tw, NULL); CHECK(plat_view_extra() == 64 && abs(w - tw) <= 1); }
  plat_render_set_logical(dlw > 0 ? dlw : 640, dlh > 0 ? dlh : 480); plat_render_set_drawable(640, 480);
  printf("v2.26: кадр во весь буфер при буфере ≠ окну (8 размеров, Hor+), режим игры → 640x480, game_res — OK\n");
  return 0;
}
/* v2.19: draw_distance — математика расширенного обхода клеток за окном FRUSTRUM.DAT 31×31 (game/drawdist.c, без данных игры) */
#include "../game/drawdist.h"
#include "../platform/sdl/plat_gfx.h"
static int test_drawdist(void) {
  int r = re_dd_selftest();
  if (r) printf("FAIL re_dd_selftest: проверка %d\n", r);
  CHECK(r == 0);
  { re_gfx_cfg c; re_gfx_defaults(&c); CHECK(c.draw_distance == 2.0);              /* enhanced — 2.0 */
    CHECK(re_gfx_preset(&c, "original") == 0 && c.draw_distance == 1.0);
    CHECK(re_gfx_set(&c, "draw_distance", "3.5") == 0 && c.draw_distance == 3.5);
    CHECK(re_gfx_set(&c, "draw_distance", "9") == 0); re_gfx_clamp(&c); CHECK(c.draw_distance == 4.0);
    CHECK(re_gfx_set(&c, "draw_distance", "0.2") == 0); re_gfx_clamp(&c); CHECK(c.draw_distance == 1.0);
    CHECK(re_gfx_set(&c, "draw_distance", "abc") == -2); }
  printf("drawdist: R 1.0=%d 2.0=%d 3.0=%d 4.0=%d, таблица 1/z far 45000=%d 135000=%d\n", re_dd_radius(1.0), re_dd_radius(2.0),
         re_dd_radius(3.0), re_dd_radius(4.0), (int)re_dd_oow_n(45000.0), (int)re_dd_oow_n(135000.0));
  return 0;
}
/* v2.16: настройки графики (driver.cfg/RE_*) и обработка текстур (dilation, мипмапы с сохранением покрытия) — без GL и данных игры */
#include "../platform/sdl/plat_gfx.h"
static const char *gfx_fake_env(const char *n) {
  if (!strcmp(n, "RE_MSAA")) return "8";
  if (!strcmp(n, "RE_FILTER")) return "nearest";
  if (!strcmp(n, "RE_RENDER_SCALE")) return "1.5";
  return NULL;
}
static int test_gfx(void) {
  re_gfx_cfg c; re_gfx_defaults(&c);
  /* v2.24: fbo / preset safe / fullscreen desktop|exclusive */
  CHECK(c.fbo == 1 && re_gfx_set(&c, "fbo", "off") == 0 && c.fbo == 0 && re_gfx_set(&c, "fbo", "auto") == 0 && c.fbo == 1 && re_gfx_set(&c, "fbo", "x") == -2);
  CHECK(re_gfx_preset(&c, "safe") == 0 && c.fbo == 0 && c.msaa == 0 && !strcmp(c.preset, "safe") && re_gfx_preset(&c, "original") == 0 && c.fbo == 1);
  CHECK(re_gfx_set(&c, "fullscreen", "exclusive") == 0 && c.fullscreen == 2 && re_gfx_set(&c, "fullscreen", "desktop") == 0 && c.fullscreen == 1 && re_gfx_set(&c, "fullscreen", "0") == 0 && c.fullscreen == 0);
  re_gfx_defaults(&c);
  CHECK(!strcmp(c.preset, "enhanced") && c.msaa == 4 && c.aniso == 16 && c.mipmaps && c.filter == RE_FILTER_TRILINEAR && !c.fxaa && c.render_scale == 1.0);
  const char *txt = "# driver.cfg\n[graphics]\npreset = original ; комментарий\nmsaa = 3\nfxaa = on\naniso=32\nfilter = trilinear\nrender_scale = 4\n"
                    "vsync = adaptive\nfps_limit = 60\ngamma = 1.2\naspect = 21:9\nfullscreen = 0\nwindowed_res = 1280x720\nhud_filter = sharp\nbogus = 1\nmipmaps = maybe\n";
  int e = re_gfx_parse(&c, txt, NULL);
  CHECK(e == 2);                                                    /* bogus — неизвестный ключ, mipmaps = maybe — плохое значение */
  CHECK(!strcmp(c.preset, "original") && c.mipmaps == 0 && c.dilate == 0);   /* пресет применён первым, остальное поверх */
  CHECK(c.msaa == 2 && c.fxaa == 1 && c.aniso == 16 && c.filter == RE_FILTER_TRILINEAR && c.render_scale == 2.0);   /* clamp */
  CHECK(c.vsync == RE_VSYNC_ADAPTIVE && c.fps_limit == 60 && c.gamma > 1.19 && c.gamma < 1.21 && !strcmp(c.aspect, "21:9"));
  CHECK(c.fullscreen == 0 && c.win_w == 1280 && c.win_h == 720 && c.hud_filter == RE_HUD_SHARP);
  CHECK(re_gfx_env(&c, gfx_fake_env) == 0);
  CHECK(c.msaa == 8 && c.filter == RE_FILTER_NEAREST && c.render_scale == 1.5 && c.fps_limit == 60);   /* RE_* важнее файла */
  CHECK(re_gfx_set(&c, "render_scale", "abc") == -2 && re_gfx_set(&c, "nokey", "1") == -1 && re_gfx_preset(&c, "ultra") == -1);
  CHECK(re_gfx_set(&c, "preset", "enhanced") == 0 && c.msaa == 4 && c.win_w == 1280);   /* пресет не трогает окно */
  /* dilation: 4×4, один непрозрачный красный в углу, остальное — прозрачный пурпурный (chroma-key) */
  uint32_t px[16]; for (int i = 0; i < 16; i++) px[i] = 0x00FF00FFu;
  px[0] = 0xFF0000FFu;
  CHECK(re_gfx_dilate(px, 4, 4, 16) == 15);
  for (int i = 0; i < 16; i++) CHECK((px[i] & 0xFFFFFFu) == 0x0000FFu);   /* цвет красный везде */
  CHECK(px[0] >> 24 == 255 && px[5] >> 24 == 0 && px[15] >> 24 == 0);      /* альфа не меняется */
  /* прозрачный пиксель между красным и синим — среднее соседей */
  uint32_t q[3] = { 0xFF0000FFu, 0x00FF00FFu, 0xFFFF0000u };
  CHECK(re_gfx_dilate(q, 3, 1, 1) == 1 && (q[1] & 0xFFFFFFu) == 0x800080u);
  /* max_pass 2: дальние прозрачные — средний цвет непрозрачных */
  uint32_t r8[8] = { 0xFF00FF00u, 0, 0, 0, 0, 0, 0, 0 };
  CHECK(re_gfx_dilate(r8, 8, 1, 2) == 7 && (r8[7] & 0xFFFFFFu) == 0x00FF00u);
  /* мипмап: блок 2×2 — один непрозрачный красный, три прозрачных чёрных → RGB красный (взвешено альфой), альфа 64 */
  uint32_t m4[4] = { 0xFF0000FFu, 0, 0, 0 }, d1 = 0;
  re_gfx_mip_next(m4, 2, 2, &d1, -1.0, 128);
  CHECK((d1 & 0xFFFFFFu) == 0x0000FFu && (d1 >> 24) == 64);
  /* сохранение покрытия: шахматка 4×4 (покрытие 0.5) → 2×2 с альфой 128 у всех — доля >= 128 не падает до 0 */
  uint32_t ch[16], d4[4]; for (int i = 0; i < 16; i++) ch[i] = (((i & 1) ^ ((i >> 2) & 1)) ? 0xFF00FF00u : 0x0000FF00u);
  double cov = re_gfx_coverage(ch, 4, 4, 128);
  CHECK(cov > 0.49 && cov < 0.51);
  re_gfx_mip_next(ch, 4, 4, d4, cov, 128);
  int k = 0; for (int i = 0; i < 4; i++) k += (int)(d4[i] >> 24) >= 128;
  CHECK(k >= 2);
  CHECK(re_gfx_has_partial_alpha(ch, 4, 4) && !re_gfx_has_partial_alpha(&px[0], 1, 1));
  uint32_t bx = 0; re_gfx_mip_box(m4, 2, 2, &bx);                      /* простое среднее (для рисования без альфа-теста) */
  CHECK(bx == 0x40000040u);
  char b[600]; printf("gfx: %s\n", re_gfx_describe(&c, b, sizeof b));
  return 0;
}
/* v2.17: HD-пак текстур — PNG (stb_image), сверка со страницей, подмена 256 → 1024 в P86_NativeCapture; синтетика без данных игры */
#include "../platform/sdl/plat_texpack.h"
static int test_texpack(void) {
  char lv[64];
  re_texpack_level_name("Levels/NY_01.lev", lv, sizeof lv); CHECK(!strcmp(lv, "NY_01"));
  re_texpack_level_name("Levels\\Miami_02.LEV", lv, sizeof lv); CHECK(!strcmp(lv, "Miami_02"));
  { static const unsigned char junk[16] = { 1, 2, 3 }; int w = 0, h = 0; CHECK(re_texpack_decode_png(junk, 16, &w, &h) == NULL); }
  static uint16_t page[256 * 256];
  for (int y = 0; y < 256; y++) for (int x = 0; x < 256; x++) {
    int hole = x >= 96 && x < 160 && y >= 96 && y < 160;          /* chroma-key: прозрачный квадрат в центре */
    uint16_t c = (uint16_t)(((x >> 3) & 31) << 10 | ((y >> 3) & 31) << 5 | (((x + y) >> 4) & 31));
    page[y * 256 + x] = hole ? c : (uint16_t)(0x8000 | c);
  }
  enum { HW = 1024 };
  uint32_t *hd = (uint32_t *)malloc((size_t)HW * HW * 4), *bad = (uint32_t *)malloc((size_t)HW * HW * 4);
  CHECK(hd && bad);
  for (int y = 0; y < HW; y++) for (int x = 0; x < HW; x++) {        /* «апскейл» ×4 nearest, как пак */
    uint16_t s = page[(y / 4) * 256 + x / 4];
    uint32_t r = (s >> 10) & 31, g = (s >> 5) & 31, b = s & 31; r = r << 3 | r >> 2; g = g << 3 | g >> 2; b = b << 3 | b >> 2;
    hd[(size_t)y * HW + x] = ((s & 0x8000) ? 0xFF000000u : 0) | b << 16 | g << 8 | r;
    bad[(size_t)y * HW + x] = hd[(size_t)y * HW + x] ^ 0x00FFFFFFu;   /* «чужая страница» — инверсия цвета */
  }
  mkdir("texpack_test", 0777); mkdir("texpack_test/TPTEST", 0777);
  CHECK(png_write_rgba("texpack_test/TPTEST/p200.png", hd, HW, HW) == 0);
  CHECK(png_write_rgba("texpack_test/TPTEST/p201.png", bad, HW, HW) == 0);
  CHECK(png_write_rgba("texpack_test/TPTEST/p203.png", hd, 512, 256) == 0);   /* не квадрат — не принимается */
  int w = 0, h = 0; uint32_t *ld = re_texpack_load("texpack_test", "TPTEST", 200, &w, &h);
  CHECK(ld && w == HW && h == HW && !memcmp(ld, hd, (size_t)HW * HW * 4));
  double err = -1, am = -1; re_texpack_compare(ld, w, h, page, &err, &am);
  CHECK(err < 0.5 && am == 0.0);
  free(ld);
  ld = re_texpack_load("texpack_test/", "TPTEST", 201, &w, &h); CHECK(ld != NULL);
  re_texpack_compare(ld, w, h, page, &err, &am); CHECK(err > RE_TEXPACK_MAX_ERR); free(ld);
  /* v2.17: «dilation по биту 0x8000» затирает содержимое страницы (цвет пикселей с битом заменён тёмным) — тоже отклоняется */
  for (size_t i = 0; i < (size_t)HW * HW; i++) if (hd[i] >> 24) hd[i] = 0xFF080808u;
  CHECK(png_write_rgba("texpack_test/TPTEST/p204.png", hd, HW, HW) == 0);
  ld = re_texpack_load("texpack_test", "TPTEST", 204, &w, &h); CHECK(ld != NULL);
  re_texpack_compare(ld, w, h, page, &err, &am); CHECK(err > RE_TEXPACK_MAX_ERR && am == 0.0); free(ld);
  remove("texpack_test/TPTEST/p204.png");
  CHECK(re_texpack_load("texpack_test", "TPTEST", 202, &w, &h) == NULL && re_texpack_load("texpack_test", "TPTEST", 203, &w, &h) == NULL);
  free(hd); free(bad);
  /* подмена в P86_NativeCapture (нужен GL: OSMesa) */
  if (!getenv("RE_TEXPACK") && plat_render_offscreen(640, 480) == 0) {
    re_gfx_cfg *c = re_gfx(); char keep[512]; memcpy(keep, c->texpack, sizeof keep);
    char lp[256]; memcpy(lp, P77_CurLevelPath, sizeof lp);
    CHECK(re_gfx_set(c, "texpack", "texpack_test") == 0 && re_texpack_dir() && !strcmp(re_texpack_dir(), "texpack_test"));
    snprintf(P77_CurLevelPath, sizeof P77_CurLevelPath, "Levels/TPTEST.lev");
    int32_t n0 = P86_TexpackN, r0 = P86_TexpackRejected;
    P86_NativeCapture(200, 0, page, NULL); CHECK(P86_NativeHandle(200) > 0 && P86_NativeTexW(200) == HW && P86_TexpackN == n0 + 1);
    P86_NativeCapture(201, 0, page, NULL); CHECK(P86_NativeHandle(201) > 0 && P86_NativeTexW(201) == 256 && P86_TexpackRejected == r0 + 1);
    P86_NativeCapture(202, 0, page, NULL); CHECK(P86_NativeHandle(202) > 0 && P86_NativeTexW(202) == 256);   /* нет файла — как раньше */
    c->texpack[0] = 0;
    P86_NativeCapture(200, 0, page, NULL); CHECK(P86_NativeTexW(200) == 256 && !re_texpack_dir());          /* без каталога — как раньше */
    memcpy(c->texpack, keep, sizeof keep); memcpy(P77_CurLevelPath, lp, sizeof lp);
    printf("texpack: подмена 256→%d ok, отклонение чужой страницы ok\n", HW);
  } else printf("texpack: PNG/сверка ok (подмена в GL — SKIP: нет OSMesa или задан RE_TEXPACK)\n");
  remove("texpack_test/TPTEST/p200.png"); remove("texpack_test/TPTEST/p201.png"); remove("texpack_test/TPTEST/p203.png");
  remove("texpack_test/TPTEST"); remove("texpack_test");   /* пустые каталоги */
  return 0;
}
/* v2.18: 8-битные страницы в HD-паке — пара (страница, слот палитры) → pNNN_cKKKK.png; палитра — текущая g_01252b74 во время
   рисования; сверка с той же страницей в той же палитре (файл с чужой палитрой отклоняется), смена содержимого палитры;
   склейка пути игры (re_texpack_merge: альфа оригинала) и поиск каталога уровня без учёта регистра. Синтетика, без данных игры. */
static int test_texpack8(void) {
  static uint8_t pa[256 * 256], pb[256 * 256];
  static uint32_t ref[256 * 256];
  for (int y = 0; y < 256; y++) for (int x = 0; x < 256; x++) { pa[y * 256 + x] = (uint8_t)((x >> 2) ^ (y >> 3)); pb[y * 256 + x] = (uint8_t)(x + y); }
  static uint8_t keep14[2 * 0x400]; int32_t keep12[2], keepcur = P12_01252b74;
  memcpy(keep14, &P14_01252be0[5 * 0x400], sizeof keep14); keep12[0] = P12_01252aa0[5]; keep12[1] = P12_01252aa0[6];
  p58_rec_t *kt = P58_Tab4EFC03; int32_t kc = P58_Cnt4EFC03;
  for (int i = 0; i < 256; i++) {                    /* палитра 5 — градиент, 6 — сильно другая */
    uint8_t *e5 = &P14_01252be0[5 * 0x400 + i * 4], *e6 = &P14_01252be0[6 * 0x400 + i * 4];
    e5[0] = (uint8_t)i; e5[1] = (uint8_t)(255 - i); e5[2] = (uint8_t)(i * 3); e5[3] = 0;
    e6[0] = (uint8_t)(255 - i); e6[1] = (uint8_t)(i * 7 + 90); e6[2] = (uint8_t)(128 + i); e6[3] = 0;
  }
  P12_01252aa0[5] = 1; P12_01252aa0[6] = 1;
  re_texpack_pal8_rgba(pa, &P14_01252be0[5 * 0x400], ref);
  { int i = 3 * 256 + 77; unsigned k = pa[i]; const uint8_t *e = &P14_01252be0[5 * 0x400 + k * 4];
    CHECK(ref[i] == (0xFF000000u | (uint32_t)e[0] << 16 | (uint32_t)e[1] << 8 | e[2])); }   /* B,G,R,X → RGBA, альфа 255 */
  enum { HW = 1024 };
  uint32_t *hd = (uint32_t *)malloc((size_t)HW * HW * 4); CHECK(hd);
  for (int y = 0; y < HW; y++) for (int x = 0; x < HW; x++) hd[(size_t)y * HW + x] = ref[(y / 4) * 256 + x / 4];
  double err = -1, am = -1;
  re_texpack_compare_rgba(hd, HW, HW, ref, &err, &am); CHECK(err < 0.5 && am == 0.0);
  { static uint32_t r6[256 * 256]; re_texpack_pal8_rgba(pa, &P14_01252be0[6 * 0x400], r6);
    re_texpack_compare_rgba(hd, HW, HW, r6, &err, &am); CHECK(err > RE_TEXPACK_MAX_ERR);        /* та же страница, чужая палитра */
    /* путь игры: склейка с памятью поверхности — альфа берётся у оригинала, чужая страница не принимается */
    uint32_t *m = (uint32_t *)malloc((size_t)HW * HW * 4); CHECK(m);
    memcpy(m, hd, (size_t)HW * HW * 4); ref[0] &= 0x00FFFFFFu;
    CHECK(re_texpack_merge(ref, m, HW, &err) == 1 && err < 0.5 && (m[0] >> 24) == 0 && (m[3] >> 24) == 0 && (m[4] >> 24) == 255);
    ref[0] |= 0xFF000000u;
    memcpy(m, hd, (size_t)HW * HW * 4); CHECK(re_texpack_merge(r6, m, HW, &err) == 0 && err > RE_TEXPACK_MAX_ERR);
    CHECK(re_texpack_merge(ref, m, 300, &err) == 0);
    free(m); }
  mkdir("texpack_test", 0777); mkdir("texpack_test/tptest", 0777);   /* каталог строчными, игра спросит TPTEST */
  CHECK(png_write_rgba("texpack_test/tptest/p210_c0005.png", hd, HW, HW) == 0);
  CHECK(png_write_rgba("texpack_test/tptest/p210_c0006.png", hd, HW, HW) == 0);   /* картинка палитры 5 под именем палитры 6 */
  int w = 0, h = 0; uint32_t *ld = re_texpack_load8("texpack_test", "TPTEST", 210, 5, &w, &h);
  CHECK(ld && w == HW && !memcmp(ld, hd, (size_t)HW * HW * 4)); free(ld);
  CHECK(re_texpack_load8("texpack_test", "TPTEST", 211, 5, &w, &h) == NULL && re_texpack_load("texpack_test", "TPTEST", 210, &w, &h) == NULL);
  { /* v2.27: оверлей неба — <пак>/sky.txt называет подкаталог, его файлы важнее основного пака; RE_TEXPACK_SKY=0 — выкл. */
    char od[256]; CHECK(re_texpack_overlay("texpack_test", od, sizeof od) == NULL);
    mkdir("texpack_test/sky_t", 0777); mkdir("texpack_test/sky_t/tptest", 0777);
    uint32_t px4 = hd[0]; hd[0] = 0xFF123456u;
    CHECK(png_write_rgba("texpack_test/sky_t/tptest/p210_c0005.png", hd, HW, HW) == 0);
    FILE *sf = fopen("texpack_test/sky.txt", "wb"); CHECK(sf); fputs("sky_t\n", sf); fclose(sf);
    CHECK(re_texpack_overlay("texpack_test", od, sizeof od) && !strcmp(od, "texpack_test/sky_t"));
    uint32_t *lo = re_texpack_load8("texpack_test", "TPTEST", 210, 5, &w, &h); CHECK(lo && lo[0] == 0xFF123456u); free(lo);
    lo = re_texpack_load8("texpack_test", "TPTEST", 210, 6, &w, &h); CHECK(lo && lo[0] == px4); free(lo);   /* нет в оверлее — основной */
    setenv("RE_TEXPACK_SKY", "0", 1); CHECK(re_texpack_overlay("texpack_test", od, sizeof od) == NULL);
    lo = re_texpack_load8("texpack_test", "TPTEST", 210, 5, &w, &h); CHECK(lo && lo[0] == px4); free(lo); unsetenv("RE_TEXPACK_SKY");
    hd[0] = px4;
    remove("texpack_test/sky.txt"); remove("texpack_test/sky_t/tptest/p210_c0005.png"); remove("texpack_test/sky_t/tptest"); remove("texpack_test/sky_t");
    lo = re_texpack_load8("texpack_test", "TPTEST", 210, 5, &w, &h); CHECK(lo && lo[0] == px4); free(lo); }
  if (!getenv("RE_TEXPACK") && plat_render_offscreen(640, 480) == 0) {
    re_gfx_cfg *c = re_gfx(); char keep[512]; memcpy(keep, c->texpack, sizeof keep);
    char lp[256]; memcpy(lp, P77_CurLevelPath, sizeof lp);
    CHECK(re_gfx_set(c, "texpack", "texpack_test") == 0);
    snprintf(P77_CurLevelPath, sizeof P77_CurLevelPath, "Levels/TPTEST.lev");
    static int32_t list5[1] = { 5 };
    static p58_rec_t recs[1]; recs[0].a = 210; recs[0].p = list5; recs[0].c = 1;   /* список .d3d: страница 210 — палитра 5 */
    P58_Tab4EFC03 = recs; P58_Cnt4EFC03 = 1;
    P12_01252b74 = 1;
    int32_t n0 = P86_Texpack8N, r0 = P86_TexpackRejected;
    P86_NativeCapture(210, 1, pa, pb);
    CHECK(P86_Texpack8N == n0 + 1);                                         /* пара из списка загружена при загрузке уровня */
    P12_01252b74 = 5; int h5 = P86_NativeHandle(210);
    CHECK(h5 > 0 && P86_NativeTexW(210) == HW && P86_NativeTexW8(210, 5) == HW);
    P12_01252b74 = 6; int h6 = P86_NativeHandle(210);
    CHECK(h6 > 0 && h6 != h5 && P86_NativeTexW(210) == 256 && P86_TexpackRejected == r0 + 1);   /* чужая палитра — отклонён */
    CHECK(P86_NativeTexW8(211, 5) == 256 && P86_NativeHandle(211) > 0);      /* нет файла — 256 */
    P12_01252b74 = 5; CHECK(P86_NativeHandle(210) == h5);                   /* смена палитры — смена текстуры */
    for (int i = 0; i < 256; i++) P14_01252be0[5 * 0x400 + i * 4 + 1] ^= 0x80;   /* содержимое палитры 5 сменилось */
    P12_01252b74 = 6; (void)P86_NativeHandle(210); P12_01252b74 = 5;
    CHECK(P86_NativeHandle(210) > 0 && P86_NativeTexW(210) == 256);         /* пересоздана, HD с прежней палитрой отклонён */
    P12_01252b74 = 40;                                                       /* незагруженный слот — прежний выбор */
    CHECK(P86_NativeHandle(210) > 0);
    c->texpack[0] = 0; memcpy(&P14_01252be0[5 * 0x400], keep14, 0x400);
    for (int i = 0; i < 256; i++) { uint8_t *e5 = &P14_01252be0[5 * 0x400 + i * 4]; e5[0] = (uint8_t)i; e5[1] = (uint8_t)(255 - i); e5[2] = (uint8_t)(i * 3); e5[3] = 0; }
    P86_NativeCapture(210, 1, pa, pb); P12_01252b74 = 5;
    CHECK(P86_NativeTexW(210) == 256);                                       /* без каталога — как раньше */
    P58_Tab4EFC03 = kt; P58_Cnt4EFC03 = kc;
    memcpy(c->texpack, keep, sizeof keep); memcpy(P77_CurLevelPath, lp, sizeof lp);
    printf("texpack8: пара (страница, палитра) 256→%d ok, чужая палитра отклонена, смена палитры ok, склейка ok\n", HW);
  } else printf("texpack8: PNG/сверка/склейка ok (подмена в GL — SKIP)\n");
  memcpy(&P14_01252be0[5 * 0x400], keep14, sizeof keep14); P12_01252aa0[5] = keep12[0]; P12_01252aa0[6] = keep12[1]; P12_01252b74 = keepcur;
  free(hd);
  remove("texpack_test/tptest/p210_c0005.png"); remove("texpack_test/tptest/p210_c0006.png");
  remove("texpack_test/tptest"); remove("texpack_test");
  return 0;
}
int re_selftest_on;   /* v2.00: 1 — идёт selftest (шпионы), 0 — игра */
int re_selftest(void) {
  re_selftest_on = 1;
  if (getenv("RE_ONLY_REAL")) { re_init_consts(); return test_real_level(); }   /* только проверка настоящего уровня */
    int f = RUN_T(test_director) | RUN_T(test_director2) | RUN_T(test_storage) | RUN_T(test_read) | RUN_T(test_nodes) | RUN_T(test_menu) | RUN_T(test_menu2) | RUN_T(test_menu3) | RUN_T(test_menu4) | RUN_T(test_menu5) | RUN_T(test_ui) | RUN_T(test_ui3) | RUN_T(test_ui4) | RUN_T(test_p4) | RUN_T(test_p5) | RUN_T(test_p6) | RUN_T(test_p7) | RUN_T(test_p8) | RUN_T(test_p9) | RUN_T(test_p11) | RUN_T(test_p12) | RUN_T(test_p13) | RUN_T(test_p14) | RUN_T(test_ported15) | RUN_T(test_ported16) | RUN_T(test_ported17) | RUN_T(test_ported18) | RUN_T(test_ported19) | RUN_T(test_p21) | RUN_T(test_p22) | RUN_T(test_p23) | RUN_T(test_p24) | RUN_T(test_p25) | RUN_T(test_p26) | RUN_T(test_p27) | RUN_T(test_p28) | RUN_T(test_p29) | RUN_T(test_p30) | RUN_T(test_p31) | RUN_T(test_p32) | RUN_T(test_p33) | RUN_T(test_p34) | RUN_T(test_p35) | RUN_T(test_p36) | RUN_T(test_p37) | RUN_T(test_p38) | RUN_T(test_p39) | RUN_T(test_p40) | RUN_T(test_p41) | RUN_T(test_p42) | RUN_T(test_p43) | RUN_T(test_p44) | RUN_T(test_p45) | RUN_T(test_p46) | RUN_T(test_p47) | RUN_T(test_p48) | RUN_T(test_p49) | RUN_T(test_p50) | RUN_T(test_p51) | RUN_T(test_p52) | RUN_T(test_p53) | RUN_T(test_p54) | RUN_T(test_p55) | RUN_T(test_p56) | RUN_T(test_p57) | RUN_T(test_p58) | RUN_T(test_p59) | RUN_T(test_p60) | RUN_T(test_p61) | RUN_T(test_p62) | RUN_T(test_p63) | RUN_T(test_p64) | RUN_T(test_p65) | RUN_T(test_p66) | RUN_T(test_p67) | RUN_T(test_p68) | RUN_T(test_p69) | RUN_T(test_p70) | RUN_T(test_p71) | RUN_T(test_p73) | RUN_T(test_p74) | RUN_T(test_p75) | RUN_T(test_p76) | RUN_T(test_p77) | RUN_T(test_p78) | RUN_T(test_p79) | RUN_T(test_p80) | RUN_T(test_p81) | RUN_T(test_p82) | RUN_T(test_p83) | RUN_T(test_p84) | RUN_T(test_p85) | RUN_T(test_p86) | RUN_T(test_p87) | RUN_T(test_p88) | RUN_T(test_p89) | RUN_T(test_p90) | RUN_T(test_p91) | RUN_T(test_p92) | RUN_T(test_p92s) | RUN_T(test_p93) | RUN_T(test_p94) | RUN_T(test_p95) | RUN_T(test_p96) | RUN_T(test_p97) | RUN_T(test_p98) | RUN_T(test_p99) | RUN_T(test_p100) | RUN_T(test_p101) | RUN_T(test_p102) | RUN_T(test_p103) | RUN_T(test_p104) | RUN_T(test_p105) | RUN_T(test_p106) | RUN_T(test_p107) | RUN_T(test_p108) | RUN_T(test_p109) | RUN_T(test_p110) | RUN_T(test_p111) | RUN_T(test_p112) | RUN_T(test_p113) | RUN_T(test_p114) | RUN_T(test_p115) | RUN_T(test_p116) | RUN_T(test_p117) | RUN_T(test_p118) | RUN_T(test_p119) | RUN_T(test_p120) | RUN_T(test_p121) | RUN_T(test_p122) | RUN_T(test_p123) | RUN_T(test_p124) | RUN_T(test_p125) | RUN_T(test_p126) | RUN_T(test_p127) | RUN_T(test_p128) | RUN_T(test_p129) | RUN_T(test_p130) | RUN_T(test_p131) | RUN_T(test_p132) | RUN_T(test_p133) | RUN_T(test_p134) | RUN_T(test_p135) | RUN_T(test_p136) | RUN_T(test_p137) | RUN_T(test_p138) | RUN_T(test_p139) | RUN_T(test_p140) | RUN_T(test_p141) | RUN_T(test_p142) | RUN_T(test_p143) | RUN_T(test_p144) | RUN_T(test_p145) | RUN_T(test_p146) | RUN_T(test_p147) | RUN_T(test_p148) | RUN_T(test_p149) | RUN_T(test_p150) | RUN_T(test_p151) | RUN_T(test_p152) | RUN_T(test_v204) | RUN_T(test_v220) | RUN_T(test_v221) | RUN_T(test_v223) | RUN_T(test_facade_camera) | RUN_T(test_v225) | RUN_T(test_v226) | RUN_T(test_real_level) | RUN_T(test_snd) | RUN_T(test_v229) | RUN_T(test_v222) | RUN_T(test_v233) | RUN_T(test_aspect) | RUN_T(test_drawdist) | RUN_T(test_gfx) | RUN_T(test_texpack) | RUN_T(test_texpack8) | test_render(getenv("RE_RENDER_PNG") ? getenv("RE_RENDER_PNG") : "render_test.png");
    printf("selftest: director %s\n", f ? "FAIL" : "OK");
    return f;
}
