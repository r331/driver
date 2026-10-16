/* Автогенерация: tools/gen_native_links.py. Ещё не перенесённые вызовы в native уходят в слабые заглушки stubs.c; здесь — перенесённые. */
#include "../../game/unported.h"
#include "../../game/ported11.h"
#include "../../game/ported12.h"
#include "../../game/ported14.h"
#include "../../game/ported15.h"
#include "../../game/ported16.h"
#include "../../game/ported17.h"
#include "../../game/ported18.h"
#include "../../game/ported19.h"
#include "../../game/ported20.h"
#include "../../game/ported21.h"
#include "../../game/ported22.h"
#include "../../game/ported23.h"
#include "../../game/ported24.h"
#include "../../game/ported25.h"
#include "../../game/ported26.h"
#include "../../game/ported27.h"
#include "../../game/ported28.h"
#include "../../game/ported29.h"
#include "../../game/ported30.h"
#include "../../game/ported31.h"
#include "../../game/ported33.h"
#include "../../game/ported32.h"
#include "../../game/ported34.h"
#include "../../game/ported35.h"
#include "../../game/ported36.h"
#include "../../game/ported37.h"
#include "../../game/ported38.h"
#include "../../game/ported39.h"
#include "../../game/ported40.h"
#include "../../game/ported41.h"
#include "../../game/ported42.h"
#include "../../game/ported43.h"
#include "../../game/ported44.h"
#include "../../game/ported45.h"
#include "../../game/ported46.h"
#include "../../game/ported47.h"
#include "../../game/ported48.h"
#include "../../game/ported49.h"
#include "../../game/ported50.h"
#include "../../game/ported51.h"
#include "../../game/ported52.h"
#include "../../game/ported53.h"
#include "../../game/ported54.h"
#include "../../game/ported55.h"
#include "../../game/ported56.h"
#include "../../game/ported57.h"
#include "../../game/ported58.h"
#include "../../game/ported59.h"
#include "../../game/ported60.h"
#include "../../game/ported61.h"
#include "../../game/ported62.h"
#include "../../game/ported63.h"
#include "../../game/ported64.h"
#include "../../game/ported65.h"
#include "../../game/ported66.h"
#include "../../game/ported67.h"
#include "../../game/ported68.h"
#include "../../game/ported69.h"
#include "../../game/ported70.h"
#include "../../game/ported71.h"
#include "../../game/ported72.h"
#include "../../game/ported73.h"
#include "../../game/ported74.h"
#include "../../game/ported75.h"
#include "../../game/ported76.h"
#include "../../game/ported77.h"
#include "../../game/ported78.h"
#include "../../game/ported79.h"
#include "../../game/ported80.h"
#include "../../game/ported81.h"
#include "../../game/ported82.h"
#include "../../game/ported83.h"
#include "../../game/ported84.h"
#include "../../game/ported85.h"
#include "../../game/ported86.h"
#include "../../game/ported87.h"
#include "../../game/ported88.h"
#include "../../game/ported89.h"
#include "../../game/ported90.h"
#include "../../game/ported91.h"
#include "../../game/ported92.h"
#include "../../game/ported93.h"
#include "../../game/ported94.h"
#include "../../game/ported95.h"
#include "../../game/ported96.h"
#include "../../game/ported97.h"
#include "../../game/ported98.h"
#include "../../game/ported99.h"
#include "../../game/ported100.h"
#include "../../game/ported101.h"
#include "../../game/ported102.h"
#include "../../game/ported13.h"
#include "../../game/director.h"
#include "../../game/directorstorage.h"
#include "../../game/dirnodes.h"
#include "../../game/menustate.h"
#include "../../game/noop.h"
#include "../../game/uihandlers.h"
#include "../../game/uihandlers2.h"
#include "../../game/uihandlers3.h"
#include "../../game/uihandlers4.h"
#include "../../game/globalsets.h"
#include "../../game/smallfuncs.h"
#include "../../game/smallfuncs2.h"
#include "../../game/menuselect.h"
#include "../../game/widgets.h"
#include "../../game/ported4.h"
#include "../../game/ported5.h"
#include "../../game/ported6.h"
#include "../../game/ported7.h"
#include "../../game/ported8.h"
#include "../../game/ported9.h"
#include "../../game/ported10.h"
void P66_DrawText (int32_t x, int32_t y, uint32_t txt, int32_t a, int32_t b, int32_t r, int32_t g, int32_t bl) { P70_ShadowText(x, y, txt, a, b, r, g, bl); }
int32_t P62_Fn51CC55 (void *a, int32_t t, int32_t i) { return (int32_t)P64_RankPlace(a, t, i); }
uint32_t P62_Fn515CCA (void *p, void *car) { return (uint32_t)P71_FaceCar(p, car); }
void P61_Fn5144D4 (void *p, void *q) { P71_EdgeA(p, q); }
void P61_Fn514779 (void *p, void *q) { P71_EdgeB(p, q); }
void P61_Fn514F47 (void *p) { P68_AimSetup(p); }
void P61_Fn514BC7 (void *p, int32_t a, int32_t b) { InitObjState_00514BC7(p, a, b); }
void P60_SetupCamN (int32_t n) { P61_SetupCamN(n); }
void P60_CamPrepare (void *cam) { P61_CamPrepare(cam); }
void P60_Fn514261 (void *p) { P61_SpawnPart(p); }
int32_t P59_Fn417970 (void) { return (int32_t)P67_Menu417970(); }
void P57_MenuInit (uint32_t tbl, int32_t n) { P97_MenuCall0(tbl, n); }
void P57_Setup40A41C (void) { Copy54A838(); }
void P57_Setup40831C (void) { MenuCopyPos(); }
void P57_Setup41351C (void) { GlobalSet0041351C(); }
void P57_Setup41390C (void) { GlobalSet0041390C(); }
void P57_Setup40A5C6 (void) { GlobalSet0040A5C6(); }
void P57_Setup413691 (void) { GlobalSet00413691(); }
void P57_Setup413B7C (void) { GlobalSet00413B7C(); }
void P57_Setup41640C (void) { GlobalSet0041640C(); }
void P57_Setup40479B (void) { SetPcarName0040479B(); }
void P57_Setup412087 (void) { SetupMenuTable00412087(); }
void P57_Setup412280 (void) { MenuAllRowsTo2_00412280(); }
void P57_Setup4122E7 (void) { Ui004122E7(); }
void P57_Setup412487 (void) { SetupMenuTable00412487(); }
void P57_Setup41269B (void) { MenuAllRowsTo2_0041269B(); }
void P57_Setup412702 (void) { Ui00412702(); }
void P57_Fn51C900 (void) { P97_HsInit(); }
void P57_Fn51CAA7 (void *f) { P76_LoadHsTables(f); }
void P57_Fn51CB98 (void *f) { P62_SaveScores(f); }
void P57_Fn507672 (float *x, float *y) { P94_MapToScreen(x, y); }
void P56_CallSetVoice (uint32_t a0, int32_t a1, float a2, float a3, float a4) { P97_SndStart(a0, a1, a2, a3, a4); }
void P56_Fn406479 (void) { P57_SaveScores(); }
int32_t P56_Fn40682D (void *a0, int32_t a1) { return (int32_t)SumBytes(a0, a1); }
void P87_Fn42982E (uint32_t m, int32_t idx, float *pos, int32_t mode) { P92_DrawAxis(m, idx, pos, mode); }
void P87_Fn42A423 (uint32_t m, int32_t idx, float *pos, int32_t mode) { P90_DrawSingle(m, idx, pos, mode); }
void P87_Fn42A5DE (uint32_t m, int32_t idx, float *pos, int32_t mode) { P92_DrawSpin(m, idx, pos, mode); }
void P55_Fn4ED5F8 (int32_t a0, int32_t a1) { P87_LoadTile(a0, a1); }
void P55_Fn4EDAA2 (void) { P88_StreamTiles(); }
int32_t P55_Fn405E79 (int32_t a0, void *a1) { return (int32_t)P58_SaveSlot(a0, a1); }
int32_t P55_Fn405FDB (int32_t a0, void *a1) { return (int32_t)P59_ReplayCheck(a0, a1); }
void P55_Fn5248CD (void) { P25_CDResume(); }
void P55_Fn424530 (int32_t a0, int32_t a1, int32_t a2) { P74_DevSelect(a0, a1, a2); }
int32_t P55_Fn4245E2 (void) { return (int32_t)GetVarB1C0D8(); }
void P55_Fn4264A7 (void) { Ui004264A7(); }
void N54_Fn4913CC (int32_t a0, int32_t a1, int32_t a2, int32_t a3, uint32_t a4) { P75_TrafficPos(a0, a1, a2, a3, a4); }
int32_t P53_Fn40EFD5 (void) { return (int32_t)P74_KeyScan(); }
int32_t P53_Fn4045E0 (void) { return (int32_t)P57_Menu4045E0(); }
void P52_Fn4E5A1A (void) { P97_FadeIconDraw(); }
void P52_Fn4AB500 (void) { P100_DebrisInit(); }
void P52_Fn4AB808 (void) { P95_PoolIconInit(); }
void P52_Fn4AB95C (void) { P94_IconQuad(); }
void P52_Fn4ABA7C (void) { P102_SixInit(); }
void P52_Fn5173D7 (float a0, float a1, int32_t a2, int32_t a3, int32_t a4) { P73_Text(a0, a1, a2, a3, a4); }
int32_t P52_Fn405F6F (int32_t a0, void *a1) { return (int32_t)P64_ReplayStart(a0, a1); }
void P48_Fn516DA0 (void) { P58_LangStrings(); }
int32_t P47_Fn51B111 (int32_t a0, int32_t a1) { return (int32_t)P72_RoadWord(a0, a1); }
uint32_t P47_Fn51B566 (int32_t a0, int32_t a1) { return (uint32_t)P72_RoadDword(a0, a1); }
void P47_Fn4D90F4 (const char *a0) { P96_LogLine(a0); }
int32_t P47_Fn40A3A0 (void) { return (int32_t)P57_Menu40A3A0(); }
void P47_Fn405BFA (void) { P58_SaveConfig(); }
int32_t P47_Fn406199 (int32_t a0) { return (int32_t)P70_LoadReplay(a0); }
void N14_Fn4CB4FF (int32_t a0, int32_t a1, int32_t a2) { P98_LampColor(a0, a1, a2); }
void N14_Fn4FBA23 (const uint8_t* a0) { P96_ClockText(a0); }
void N14_Fn4D6C5A (void) { P75_BgSound(); }
void N14_Fn4D6DAC (void) { P75_CarSound(); }
void N14_Fn4D6EF2 (void) { P95_AmbientTick(); }
void N14_Fn5259C8 (int32_t a0) { P102_CopTalk(a0); }
void N14_Fn4D2ADE (int32_t a0) { AddClamp4095_004D2ADE(a0); }
void N14_Fn4A7EE9 (int32_t a0) { SetVarD1193C(a0); }
void N14_Fn48A627 (void) { P12_Fn0048A627(); }
uint32_t N14_Fn503ECC (const uint8_t* a0) { return (uint32_t)PackRGB00503ECC(a0); }
void Call0040CCB4 (uint32_t a0, uint32_t a1) { P45_Wait(a0, a1); }
int32_t R12_4082A0 (void) { return (int32_t)P57_Menu4082A0(); }
int32_t R12_413D70 (void) { return (int32_t)P58_Menu413D70(); }
int32_t R12_413B00 (void) { return (int32_t)P57_Menu413B00(); }
int32_t R12_4134A0 (void) { return (int32_t)P57_Menu4134A0(); }
int32_t R12_413890 (void) { return (int32_t)P57_Menu413890(); }
int32_t R12_416390 (void) { return (int32_t)P57_Menu416390(); }
int32_t R12_40A540 (void) { return (int32_t)P57_Menu40A540(); }
int32_t R12_404850 (void) { return (int32_t)P57_Menu404850(); }
int32_t R12_415EC0 (void) { return (int32_t)P67_Menu415EC0(); }
int32_t R12_413610 (void) { return (int32_t)P57_Menu413610(); }
int32_t R12_411FD0 (void) { return (int32_t)P57_Menu411FD0(); }
int32_t R12_40E870 (void) { return (int32_t)P57_Menu40E870(); }
int32_t R12_4123D0 (void) { return (int32_t)P57_Menu4123D0(); }
int32_t R12_40F2D0 (void) { return (int32_t)P57_Menu40F2D0(); }
int32_t R12_408770 (void) { return (int32_t)P77_Menu408770(); }
int32_t R12_414C30 (void) { return (int32_t)P77_Menu414C30(); }
int32_t R12_407160 (void) { return (int32_t)P77_Menu407160(); }
int32_t R12_405CB4 (int32_t a0) { return (int32_t)P56_SaveCheck(a0); }
int32_t R12_405F2E (int32_t a0) { return (int32_t)P47_PrepareTemp(a0); }
void Call004122C4 (void) { GlobalSet004122C4(); }
void Call004126DF (void) { GlobalSet004126DF(); }
void Call00523595 (void) { P48_SndShutdown(); }
void Call0052360D (int32_t a0) { SoundSetVolB0052360D(a0); }
void Call004184DE (uint32_t a0) { Ui004184DE(a0); }
void Call0041846C (uint32_t a0, uint32_t a1) { P66_ScreenFrame(a0, a1); }
void Call004086B4 (void) { StartTimer004086B4(); }
void Call004086EA (void) { StopTimer4086EA(); }
int32_t R12_4D97E9 (void) { return (int32_t)P48_AnyKey(); }
void Call00424921 (int32_t a0, int32_t a1, uint32_t a2, int32_t a3) { P47_TexTable(a0, a1, a2, a3); }
void Call0048A525 (int32_t a0) { P76_MarkSlots(a0); }
void Call0048A68E (int32_t a0) { Dispatch0048A68E(a0); }
void Call004B9AEC (void) { P101_DebrisFly(); }
void Call004B9D79 (void) { P16_StepParticles(); }
void Call004911D9 (void) { P98_TrafficSpin(); }
void Call0050F289 (void) { P55_StopAudio(); }
void Call004D6190 (int32_t a0) { SetFirstFree_004D6190(a0); }
void Call00493ECE (int32_t a0) { P74_FreeTraffic(a0); }
void Call005186CE (void) { P74_ResetHud(); }
void Call004E3391 (void) { P36_PollInput(); }
void Call0041219E (void) { P55_NamesA(); }
void Call004125B9 (void) { P55_NamesB(); }
void Call0052369B (int32_t a0) { P48_SndPause(a0); }
void Call00524873 (void) { P25_CDStop(); }
void Call00524763 (void) { P25_CDClose(); }
void Call00408770 (void) { P77_Menu408770(); }
void Call004072BE (void) { P65_SetNameFields(); }
void Call0040C165 (void) { P56_ResetFrontend(); }
void Call0048B65D (void) { P38_FmvStop(); }
void Call0048B568 (void) { P50_FmvReleaseObjs(); }
void Call005237B1 (void) { P48_StopAll(); }
void Call0052436A (void) { InitChannels_0052436A(); }
void Call0052479E (int32_t a0) { P25_PlayCDTrack(a0); }
void Call0040EA70 (void) { P97_OptMenuAInit(); }
void Call00419B35 (void) { P97_OptMenuBInit(); }
int32_t Call0042655A (int32_t a0) { return (int32_t)DrvSetMode0042655A(a0); }
void Call004D611B (int32_t a0) { TryStartTrack_004D611B(a0); }
void Call004A2C98 (void) { P96_DropFarChairs(); }
void Call004D9478 (void) { CursorWrap004D9478(); }
void Call004C1B46 (void) { FreeBufferD17EC8(); }
void UiCall0041A8AB (void) { StepIfActive0041A8AB(); }
void UiCall004EE065 (void) { P75_ResetObjs(); }
void UiCall004184F5 (void) { P19_FadeStep(); }
void UiCall005170AB (void) { P70_FadeColor(); }
void UiCall00419DB3 (void) { MenuWhite00419DB3(); }
void UiCall0041A085 (void) { SetColorWhite0041A085(); }
void UiCall00417620 (void) { LoadSliderIcons00417620(); }
void UiCall00414C30 (void) { P77_Menu414C30(); }
void UiCall00407160 (void) { P77_Menu407160(); }
void UiCall00419AB0 (void) { P58_Menu419AB0(); }
void UiCall0041B059 (void) { Ui0041B059(); }
void UiCall0041AF29 (int32_t a0) { MenuWhite0041AF29(a0); }
void UiCall0041F2A0 (void) { P31_ReleaseDirectDraw(); }
void UiCall00424647 (void) { Dev00424647(); }
void UiCall00528455 (void) { NoopFn00528455(); }
void UiCall0040C455 (int32_t a0, int32_t a1) { Call3_0040C455(a0, a1); }
void UiCall00523E50 (int32_t a0, int32_t a1, int32_t a2) { SoundPlay00523E50(a0, a1, a2); }
void UiCall00412254 (void) { MenuRowsTo2_00412254(); }
void UiCall00412228 (void) { MenuMark00412228(); }
void UiCall00412087 (void) { SetupMenuTable00412087(); }
void UiCall0041266F (void) { MenuRowsTo2_0041266F(); }
void UiCall00412643 (void) { MenuRowsTo3_00412643(); }
void UiCall00412487 (void) { SetupMenuTable00412487(); }
void UiCall0040C480 (int32_t a0) { P68_ScreenReset(a0); }
void UiCall00408600 (int32_t a0) { P58_PlayDemo(a0); }
void UiCall00417AA2 (void) { SetColorWhite00417AA2(); }
void MenuAction40CD17 (void) { P57_MenuDone(); }
void MenuRefresh (void) { P54_MenuTexSel(); }
void Call004076E2 (void) { MenuWhite004076E2(); }
void * FindCameraRecordForFrame (int frame) { return (void *)FindCameraForFrame(frame); }
void InitNewCamera (void *cam) { P98_CamClamp(cam); }
void DrawSprite (int x, int y, uint32_t tex, int a, int b, int c, int d, int e) { P70_ShadowText(x, y, tex, a, b, c, d, e); }
int IsKeyDown (int sc) { return (int)IsFlagSetNotMasked_004E383A(sc); }
int GetGroundHeight (int *pos) { return (int)P100_RoadHeight(pos); }
void Call00411A9D (void) { MenuHiliteWhite00411A9D(); }
void Call0041AFCA (void) { P55_NamesC(); }
void Call0050F7B2 (void) { P97_SndMenuInit(); }
void P4Call004A3354 (void) { P58_FreeGrid(); }
void P4Call0041A8CD (void) { P12_Fn0041A8CD(); }
void P4Call0051AA5B (void) { P54_AllocRoadbits(); }
void P4Call004ECADE (void) { P77_LoadLevel(); }
void P4Call004D2D85 (int32_t a0) { Call004D2D85(a0); }
void P4Call0041D89C (int32_t a0, int32_t a1) { P46_TexCall(a0, a1); }
void P4Call00528293 (int32_t a0) { P25_TimerStop(a0); }
void P4Call004076E2 (void) { MenuWhite004076E2(); }
void P4Call00409CFA (void) { MenuWhite00409CFA(); }
void P4Call0041074D (void) { MenuHiliteWhite0041074D(); }
void P4Call00411A9D (void) { MenuHiliteWhite00411A9D(); }
void P4Call00415979 (void) { MenuWhite00415979(); }
void G6Call004064B4 (int32_t a0, int32_t a1) { P13_Fn004064B4(a0, a1); }
void G6Call004094E3 (void) { P94_ClampView(); }
void G6Call0050FAB0 (void) { P96_ClampOptions(); }
void G6Call004D5FFC (void) { Chain004D5FFC(); }
void G6Call00524398 (void) { P43_CdFadeInit(); }
void G6Call00523628 (void) { P48_ResetAll(); }
void G6Call0041A16C (void) { FreeBuffer5FED98(); }
void G6Call0040C5BE (int32_t a0) { P54_ClearSwap(a0); }
void G6Call0050E940 (int32_t a0) { SetLatchValue0050E940(a0); }
void G6Call00418119 (int32_t a0) { Ui00418119(a0); }
void G6Call00417CBB (void) { P45_PickColor(); }
void G6Call004A2B70 (void) { ResetSlots_004A2B70(); }
void G6Call004BA457 (void) { P95_SortObjA(); }
void G6Call004BA57A (void) { P95_SortObjC(); }
void G6Call004BA64D (void) { P95_SortObjB(); }
void G6Call004D614A (int32_t a0, int32_t a1, int32_t a2, int32_t a3) { P46_SetBounds(a0, a1, a2, a3); }
void G6Call00426580 (int32_t a0) { P12_Fn00426580(a0); }
void G6Call00516EB4 (int32_t a0, int32_t a1, int32_t a2) { SetRGB00516EB4(a0, a1, a2); }
void G6Call00491360 (void) { P12_Fn00491360(); }
void Call0042486B (int32_t a0, uint32_t a1, int32_t a2, uint32_t a3, int32_t a4) { P52_TexDownloadMipMap(a0, a1, a2, a3, a4); }
int32_t G6Call0041D63B (int32_t a0, int32_t a1, int32_t a2, int32_t a3) { return (int32_t)P53_TexLookup(a0, a1, a2, a3); }
int32_t G6Call00523CDA (int32_t a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4) { return (int32_t)P97_SndStart(a0, a1, a2, a3, a4); }
void Call004D94B7 (uint32_t a0, uint32_t a1) { CursorSet004D94B7(a0, a1); }
int32_t Call00524473 (int32_t a0) { return (int32_t)IsSlotActive00524473(a0); }
uint32_t Call0048F3B4 (int32_t a0, int32_t a1, int32_t a2, int32_t a3) { return (uint32_t)P63_CountByNode(a0, a1, a2, a3); }
void Call00510784 (void) { P55_NamesD(); }
void Call0050FAB0 (void) { P96_ClampOptions(); }
void Call004C64BD (void) { FreeCameraList(); }
void Call004D3402 (void) { P48_ShutdownSystems(); }
void Call004246F0 (void) { P69_FreeDevices(); }
void Call004C372A (void) { FreeDirectorBuffer(); }
void Call00421A39 (void) { P57_ResetTexNodes(); }
void Call0052434A (int32_t a0) { SlotSetOff0052434A(a0); }
void Call004D9663 (void) { P96_LoadBar(); }
void Call004C1B6C (int32_t a0) { P99_CarOpsReset(a0); }
void Call005243EB (void) { P48_FadeEnd(); }
void Call004C2042 (void) { P98_ClearCarData(); }
void Call004C0218 (int32_t a0) { P99_CarModelClean(a0); }
int32_t Call00475A3D (void *src, void *dst) { return (int32_t)P79_Convert(src, dst); }
void Call00427757 (void *m) { P79_Relocate(m); }
void Call0042793F (void *m, int32_t a1) { P79_Radius(m, a1); }
void Call004757D2 (void *m) { P79_MarkRecords(m); }
void Call00475906 (void *m) { P79_FindSameVerts(m); }
void SetCameraPosition (float x, float y, float z) { PushVec3_00523C99(x, y, z); }
void P46_Fn4D6354 (void) { P53_StepBounds(); }
void P46_Fn51BE3C (void) { P58_BuildBlockIndex(); }
void P58_Fn4185D2 (uint32_t tbl, int32_t a1, uint32_t tbl2) { P97_MenuCall2(tbl, a1, tbl2); }
void P58_Fn416605 (void) { P100_ReplayMenuInit(); }
void P58_Fn51763A (const char *a0, int32_t a1) { P98_LoadLang(a0, a1); }
void P58_Fn406875 (void *a0) { P102_ConfigSnap(a0); }
void P58_Fn413E37 (void) { P100_PadMenuInit(); }
