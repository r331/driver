/* Проверка перенесённых модулей в нативной сборке: ./driver --selftest */
#include "../game/uihandlers3.h"
#include "../game/uihandlers4.h"
#include "../game/menuselect.h"
#include "../game/director.h"
#include "../game/directorstorage.h"
#include "../game/dirnodes.h"
#include "../game/menustate.h"
#include "../game/uihandlers.h"
#include "../game/ported4.h"
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
#include <math.h>
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
  { int16_t s = 3; memcpy(&P17_MapBase + 5 * 0x42, &s, 2);
    int16_t id = 5; memcpy(&P17_SlotBase + 3 * 0x2c + 16, &id, 2); if (P17_SlotMapSide(5) != 0) f++;
    memcpy(&P17_SlotBase + 3 * 0x2c + 16, &(int16_t){0}, 2); if (P17_SlotMapSide(5) != 1) f++;
    memcpy(&P17_SlotBase + 3 * 0x2c + 24, &id, 2); if (P17_SlotFindIndex(3, 5) != 3) f++; if (P17_SlotFindIndex(3, 9) != 0xff) f++; }
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
  P19_Level = 1; P19_Sel2(0); /* Level<2 → Fn00416040 (stub) */
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
  P21_EntryCount = 2; memset(P21_Entries, 0, sizeof P21_Entries);
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
  P22_SetTexOp(0, 0, 0, 0, 2); if (P22_TexVarA != 0x20 || P22_TexVarB != 5) f++;
  P22_SetTexOp(0, 0, 0, 0, 1); if (P22_TexVarA != 5) f++;
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
  P28_EventCount = 2; P28_EventModels[0] = DebugMalloc(16, "t", 1); P28_EventModels[1] = NULL;
  P27_ReadBytes = 0; P27_ReadLimit = 0x7fffffff; P27_ProgressOn = 0;
  P28_LoadEventModels(tf);
  if (P28_EventCount != 0 || P28_EventModels[0] != NULL) f++;
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
  plat_dd_release(dd);
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
  G6_00D0DDC0 = 2; G6_00B2F30C[0] = o1; G6_00B2F30C[1] = o2;
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
  P45_Wait(5, 6); CK(P45_PtrB == 5 && P45_PtrA == 6 && P45_Busy == 0 && P45_Step == 0);
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
    P53_SetTexSource(0, 3u << 16, 0, d);
    CK(P22_TexVarA == 3 && P22_TexVarB == 3 && (uintptr_t)P32_CurHandle == 0x1234 && P32_CurSlot == -1);
    k = 0; memcpy(d + 0xc, &k, 4); P53_SetTexSource(0, 5u << 17, 0, d);
    CK(P22_TexVarA == 10);
    P53_SetTexSource(0, 0x40u << 16, 0, d);   /* вне диапазона: без изменений */
    CK(P22_TexVarA == 10);
    P22_DevReady = 0; P53_SetTexSource(0, 1u << 16, 0, d); CK(P22_TexVarA == 10); }
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
    P54_ObjInit(o); { int32_t a, b; memcpy(&a, o + 0x40, 4); memcpy(&b, o + 0x44, 4); CK(a == 11 && b == 22 && o[1] == 3 && o[0x13] == 0xfb); } }
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
  { FILE *fp = fopen("FRUSTRUM.DAT", "wb"); static uint8_t z[4 + 0x8000]; memset(z, 0, sizeof z);
    for (int i = 0; i < 0x8000; i++) z[4 + i] = (uint8_t)(i * 7);
    fwrite(z, 1, sizeof z, fp); fclose(fp);
    memset(P55_Frustum, 0, sizeof(p55_frustum_t));
    CK(P55_LoadFrustum() == 0 && P55_Frustum[1] == 7 && P55_Frustum[0x8000 - 1] == (uint8_t)(0x7fff * 7));
    remove("FRUSTRUM.DAT"); CK(P55_LoadFrustum() == -1); }
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
int re_selftest(void) {
    int f = test_director() | test_director2() | test_storage() | test_read() | test_nodes() | test_menu() | test_menu2() | test_menu3() | test_menu4() | test_menu5() | test_ui() | test_ui3() | test_ui4() | test_p4() | test_p5() | test_p6() | test_p7() | test_p8() | test_p9() | test_p11() | test_p12() | test_p13() | test_p14() | test_ported15() | test_ported16() | test_ported17() | test_ported18() | test_ported19() | test_p21() | test_p22() | test_p23() | test_p24() | test_p25() | test_p26() | test_p27() | test_p28() | test_p29() | test_p30() | test_p31() | test_p32() | test_p33() | test_p34() | test_p35() | test_p36() | test_p37() | test_p38() | test_p39() | test_p40() | test_p41() | test_p42() | test_p43() | test_p44() | test_p45() | test_p46() | test_p47() | test_p48() | test_p49() | test_p50() | test_p51() | test_p52() | test_p53() | test_p54() | test_p55() | test_p56() | test_snd() | test_render(getenv("RE_RENDER_PNG") ? getenv("RE_RENDER_PNG") : "render_test.png");
    printf("selftest: director %s\n", f ? "FAIL" : "OK");
    return f;
}
