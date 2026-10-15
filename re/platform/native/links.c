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
void P55_Fn5248CD (void) { P25_CDResume(); }
int32_t P55_Fn4245E2 (void) { return (int32_t)GetVarB1C0D8(); }
void P55_Fn4264A7 (void) { Ui004264A7(); }
void N14_Fn4D2ADE (int32_t a0) { AddClamp4095_004D2ADE(a0); }
void N14_Fn4A7EE9 (int32_t a0) { SetVarD1193C(a0); }
void N14_Fn48A627 (void) { P12_Fn0048A627(); }
uint32_t N14_Fn503ECC (const uint8_t* a0) { return (uint32_t)PackRGB00503ECC(a0); }
void Call0040CCB4 (uint32_t a0, uint32_t a1) { P45_Wait(a0, a1); }
int32_t R12_405F2E (int32_t a0) { return (int32_t)P47_PrepareTemp(a0); }
void Call004122C4 (void) { GlobalSet004122C4(); }
void Call004126DF (void) { GlobalSet004126DF(); }
void Call00523595 (void) { P48_SndShutdown(); }
void Call0052360D (int32_t a0) { SoundSetVolB0052360D(a0); }
void Call004184DE (uint32_t a0) { Ui004184DE(a0); }
void Call004086B4 (void) { StartTimer004086B4(); }
void Call004086EA (void) { StopTimer4086EA(); }
int32_t R12_4D97E9 (void) { return (int32_t)P48_AnyKey(); }
void Call00424921 (int32_t a0, int32_t a1, uint32_t a2, int32_t a3) { P47_TexTable(a0, a1, a2, a3); }
void Call0048A68E (int32_t a0) { Dispatch0048A68E(a0); }
void Call004B9D79 (void) { P16_StepParticles(); }
void Call0050F289 (void) { P55_StopAudio(); }
void Call004D6190 (int32_t a0) { SetFirstFree_004D6190(a0); }
void Call004E3391 (void) { P36_PollInput(); }
void Call0041219E (void) { P55_NamesA(); }
void Call004125B9 (void) { P55_NamesB(); }
void Call0052369B (int32_t a0) { P48_SndPause(a0); }
void Call00524873 (void) { P25_CDStop(); }
void Call00524763 (void) { P25_CDClose(); }
void Call0048B65D (void) { P38_FmvStop(); }
void Call0048B568 (void) { P50_FmvReleaseObjs(); }
void Call005237B1 (void) { P48_StopAll(); }
void Call0052436A (void) { InitChannels_0052436A(); }
void Call0052479E (int32_t a0) { P25_PlayCDTrack(a0); }
int32_t Call0042655A (int32_t a0) { return (int32_t)DrvSetMode0042655A(a0); }
void Call004D611B (int32_t a0) { TryStartTrack_004D611B(a0); }
void Call004D9478 (void) { CursorWrap004D9478(); }
void Call004C1B46 (void) { FreeBufferD17EC8(); }
void UiCall0041A8AB (void) { StepIfActive0041A8AB(); }
void UiCall004184F5 (void) { P19_FadeStep(); }
void UiCall00419DB3 (void) { MenuWhite00419DB3(); }
void UiCall0041A085 (void) { SetColorWhite0041A085(); }
void UiCall00417620 (void) { LoadSliderIcons00417620(); }
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
void UiCall00417AA2 (void) { SetColorWhite00417AA2(); }
void MenuRefresh (void) { P54_MenuTexSel(); }
void Call004076E2 (void) { MenuWhite004076E2(); }
void * FindCameraRecordForFrame (int frame) { return (void *)FindCameraForFrame(frame); }
int IsKeyDown (int sc) { return (int)IsFlagSetNotMasked_004E383A(sc); }
void Call00411A9D (void) { MenuHiliteWhite00411A9D(); }
void Call0041AFCA (void) { P55_NamesC(); }
void P4Call0041A8CD (void) { P12_Fn0041A8CD(); }
void P4Call0051AA5B (void) { P54_AllocRoadbits(); }
void P4Call004D2D85 (int32_t a0) { Call004D2D85(a0); }
void P4Call0041D89C (int32_t a0, int32_t a1) { P46_TexCall(a0, a1); }
void P4Call00528293 (int32_t a0) { P25_TimerStop(a0); }
void P4Call004076E2 (void) { MenuWhite004076E2(); }
void P4Call00409CFA (void) { MenuWhite00409CFA(); }
void P4Call0041074D (void) { MenuHiliteWhite0041074D(); }
void P4Call00411A9D (void) { MenuHiliteWhite00411A9D(); }
void P4Call00415979 (void) { MenuWhite00415979(); }
void G6Call004064B4 (int32_t a0, int32_t a1) { P13_Fn004064B4(a0, a1); }
void G6Call004D5FFC (void) { Chain004D5FFC(); }
void G6Call00524398 (void) { P43_CdFadeInit(); }
void G6Call00523628 (void) { P48_ResetAll(); }
void G6Call0041A16C (void) { FreeBuffer5FED98(); }
void G6Call0040C5BE (int32_t a0) { P54_ClearSwap(a0); }
void G6Call0050E940 (int32_t a0) { SetLatchValue0050E940(a0); }
void G6Call00418119 (int32_t a0) { Ui00418119(a0); }
void G6Call00417CBB (void) { P45_PickColor(); }
void G6Call004A2B70 (void) { ResetSlots_004A2B70(); }
void G6Call004D614A (int32_t a0, int32_t a1, int32_t a2, int32_t a3) { P46_SetBounds(a0, a1, a2, a3); }
void G6Call00426580 (int32_t a0) { P12_Fn00426580(a0); }
void G6Call00516EB4 (int32_t a0, int32_t a1, int32_t a2) { SetRGB00516EB4(a0, a1, a2); }
void G6Call00491360 (void) { P12_Fn00491360(); }
void Call0042486B (int32_t a0, uint32_t a1, int32_t a2, uint32_t a3, int32_t a4) { P52_TexDownloadMipMap(a0, a1, a2, a3, a4); }
int32_t G6Call0041D63B (int32_t a0, int32_t a1, int32_t a2, int32_t a3) { return (int32_t)P53_TexLookup(a0, a1, a2, a3); }
void Call004D94B7 (uint32_t a0, uint32_t a1) { CursorSet004D94B7(a0, a1); }
int32_t Call00524473 (int32_t a0) { return (int32_t)IsSlotActive00524473(a0); }
void Call00510784 (void) { P55_NamesD(); }
void Call004C64BD (void) { FreeCameraList(); }
void Call004D3402 (void) { P48_ShutdownSystems(); }
void Call004C372A (void) { FreeDirectorBuffer(); }
void Call0052434A (int32_t a0) { SlotSetOff0052434A(a0); }
void Call005243EB (void) { P48_FadeEnd(); }
void SetCameraPosition (float x, float y, float z) { PushVec3_00523C99(x, y, z); }
void P46_Fn4D6354 (void) { P53_StepBounds(); }
