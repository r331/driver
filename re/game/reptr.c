/* Реестр «адрес Game.exe ↔ native-объект» (v1.42). См. reptr.h. */
#define RE_GVAR_PLAIN   /* v2.03: k_regions — константные адреса native-объектов */
#include <stdlib.h>
#include <string.h>
#include "ported117.h"
#include "ported116.h"
#include "ported112.h"
#include "reptr.h"
#include "ported125.h"
#include "ported127.h"
#ifdef RE_HOOK_BUILD
void    *re_ptr(uint32_t addr) { return (void *)(uintptr_t)addr; }
uint32_t re_addr(const void *p) { return (uint32_t)(uintptr_t)p; }
void     re_ptr_register(uint32_t addr, void *native, uint32_t size) { (void)addr; (void)native; (void)size; }
uint32_t re_ptr_register_dyn(void *native, uint32_t size) { (void)size; return (uint32_t)(uintptr_t)native; }
void     re_ptr_unregister(const void *native) { (void)native; }
re_fn_t  re_fn(uint32_t addr) { return (re_fn_t)(uintptr_t)addr; }
uint32_t re_fn_addr(re_fn_t fn) { return (uint32_t)(uintptr_t)fn; }
void     re_fn_register(uint32_t addr, re_fn_t fn) { (void)addr; (void)fn; }
void     re_ptr_set_image(uint32_t base, void *p, uint32_t size) { (void)base; (void)p; (void)size; }
#else
#include "ported26.h"
#include "ported38.h"
#include "ported49.h"
#include "ported50.h"
#include "ported62.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported148.h"
#include "ported98.h"
#include "ported100.h"
#include "p100_data.h"
#include "ported103.h"
#include "p103_data.h"
#include "ported104.h"
#include "ported106.h"
#include "ported7.h"
#include "noop.h"
#include "ported10.h"
#include "ported11.h"
#include "ported48.h"
#include "ported65.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menu57.h"
#include "uihandlers4.h"
#include "menustate.h"
#include "ported12.h"
#include "ported141.h"
#include "ported143.h"
#include <string.h>
#include "ported151.h"
#include "ported22.h"
#include "ported23.h"
#include "ported31.h"
#include "ported32.h"
#include "ported39.h"
#include "ported42.h"
#include "ported53.h"
#include "ported54.h"
#include "ported76.h"
#include "ported8.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "widgets.h"

typedef struct { uint32_t addr; uint8_t *p; uint32_t size; } re_region_t;
typedef struct { uint32_t addr; re_fn_t fn; } re_fnent_t;

/* статические области: GAME_VAR-массивы, на которые в таблицах игры лежат адреса */
static const re_region_t k_regions[] = {
  { 0x00bdcb60u, (uint8_t *)P148_Drv, sizeof(p148_drvtab_t) },   /* v1.93: драйверы DirectSound (имя +0x14 читает P103 через 0054dbd8) */
  { 0x0112da40u, (uint8_t *)P12_0112da00 + 0x40, 0xc74 },   /* v1.73: пути копов (+0x40..+0xcb4 записей 0112da00, до P74_Cars) */
  { 0x0112e718u, (uint8_t *)P12_0112da00 + 0xd18, 0xc74 },
  { 0x0112f3f0u, (uint8_t *)P12_0112da00 + 0x19f0, 0xc74 },
  { 0x011300c8u, (uint8_t *)P12_0112da00 + 0x26c8, 0xc74 },
  { 0x01130da0u, (uint8_t *)P12_0112da00 + 0x33a0, 0xc74 },
  { 0x01131a78u, (uint8_t *)P12_0112da00 + 0x4078, 0xc74 },
  { 0x01132750u, (uint8_t *)P12_0112da00 + 0x4d50, 0xc74 },
  { 0x01133428u, (uint8_t *)P12_0112da00 + 0x5a28, 0xc74 },
  { 0x00574f08u, P117_MenuA, sizeof P117_MenuA },               /* v1.62: .data меню паузы (game/p117_data.h) */
  { 0x00575088u, P117_MenuB, sizeof P117_MenuB },
  { 0x00575370u, P117_MenuC, sizeof P117_MenuC },
  { 0x00574710u, P127_PauseMenu, sizeof P127_PauseMenu },       /* v1.72: .data меню паузы 00574710..00574f08 (game/p127_data.h) */
  { 0x0054cf80u, P127_NameMenu, sizeof P127_NameMenu },         /* v1.72: .data экрана ввода имени */
  { 0x005fe97cu, P127_Cursor, sizeof P127_Cursor },             /* v1.72: строка курсора (адрес в P127_NameMenu) */
  { 0x00b5a48cu, P125_FpsStr, sizeof P125_FpsStr },             /* v1.70: строка fps/языка меню управления (адрес в P117_MenuB) */
  { 0x00b5c950u, P116_SkidRecA, sizeof P116_SkidRecA },         /* v1.62: таблицы следов шин (адреса записей в P117_SkidLastA/B) */
  { 0x00b6e950u, P116_SkidRecB, sizeof P116_SkidRecB },
  { 0x010f5160u, P95_ObjA, sizeof P95_ObjA },
  { 0x0110e500u, P95_ObjB, sizeof P95_ObjB },
  { 0x011237c0u, P95_ObjC, sizeof P95_ObjC },
  { 0x00b5b378u, P62_Hs1, sizeof P62_Hs1 },
  { 0x00b5ba58u, P62_Hs2, sizeof P62_Hs2 },
  { 0x00b5b008u, P62_Hs3, sizeof P62_Hs3 },
  { 0x00b5ac98u, P62_Hs4, sizeof P62_Hs4 },
  { 0x00b5a928u, P62_Hs5, sizeof P62_Hs5 },
  { 0x00b5c138u, P62_Hs6, sizeof P62_Hs6 },
  { 0x00d0fe40u, (uint8_t *)P96_LogBuf, sizeof P96_LogBuf },
  { 0x005fe4e4u, (uint8_t *)P97_FpsTxtA, sizeof P97_FpsTxtA },
  { 0x005fea74u, (uint8_t *)P97_FpsTxtB, sizeof P97_FpsTxtB },
  { 0x00c80c60u, (uint8_t *)P97_MsgBuf, sizeof P97_MsgBuf },
  { 0x005755ecu, (uint8_t *)P97_Str8bit, sizeof P97_Str8bit },
  { 0x005755f4u, (uint8_t *)P97_Str16bit, sizeof P97_Str16bit },
  { 0x005755fcu, (uint8_t *)P97_Str22k, sizeof P97_Str22k },
  { 0x00575608u, (uint8_t *)P97_Str44k, sizeof P97_Str44k },
  { 0x005532ccu, P98_FaceBlk, sizeof P98_FaceBlk },              /* имена лиц титров (00552e1c → сюда) */
  { P99_CARS_ADDR, (uint8_t *)P99_Cars, sizeof P99_Cars },       /* v1.44: таблица игроков/машин 00d077c0 (0x148 × 66) */
  { P100_C810_ADDR, P100_MenuC810, sizeof P100_MenuC810 },     /* v1.45: .data меню (game/p100_data.h) */
  { P100_D4A8_ADDR, P100_MenuD4A8, sizeof P100_MenuD4A8 },
  { P100_E0B0_ADDR, P100_MenuE0B0, sizeof P100_MenuE0B0 },
  { P100_E33C_ADDR, (uint8_t *)P100_SpeedTab, sizeof P100_SpeedTab },
  { P103_MENUDB58_ADDR, P103_MenuTab.b, P103_MENUDB58_SIZE },  /* v1.48: .data экрана настроек 0054db58..0054de94 (game/menutab.h) */
  { P103_MOBJ_ADDR, P103_MObj, P103_MOBJ_SIZE },                /* v1.48: объекты миссий 00572f00 (game/p103_data.h) */
  { 0x00c56780u, A_00C56780, 0x2d00 },                          /* v1.48: пул частиц 0x40 × 0xb4 */
  { P104_MENUGFX_ADDR0, P104_MenuGfx.b, P104_MENUGFX_SIZE0 },     /* v1.49: .data экрана графики 0054a170..0054a6f8 (game/menugfx.h) */
  { 0x00cfe760u, (uint8_t *)P104_Buf760, sizeof P104_Buf760 },  /* v1.49: буфер 00562d7c */
  { P57_MENU_ADDR, P57_MenuTab.b, P57_MENU_SIZE },              /* v1.58: .data меню опций 0057b578..0057b658 (game/menu57.h) */
  { 0x0054bd10u, P141_HsMenu, sizeof P141_HsMenu },             /* v1.86: .data экрана рекордов 0054bd10..0054bee0 (game/p141_data.h) */
  { 0x0054bf1cu, P141_HsStr, sizeof P141_HsStr },               /* v1.86: строки 0054bf1c..0054bf90 (адреса в P141_HsMenu) */
  { P143_FX_ADDR, (uint8_t *)P143_Fx, sizeof P143_Fx },          /* v1.88: .data спрайтов-вспышек 005536a8..005537c8 (game/p143_data.h) */
};
/* таблица функций: адрес Game.exe → перенесённая native-функция */
static const re_fnent_t k_fns[] = {
  /* v1.96: функции D3D-эмуляции Glide (таблица 0041cede); сигнатуры совпадают с прототипами Glide по ABI */
  { 0x0041d8e9u, (re_fn_t)InitIdentityPalette_0041D8E9 }, { 0x0041d94au, (re_fn_t)Ui0041D94A }, { 0x0041d954u, (re_fn_t)FillTable8_0041D954 },
  { 0x0041d9afu, (re_fn_t)NoopFn0041d9af }, { 0x0041d9b6u, (re_fn_t)NoopFn0041d9b6 }, { 0x0041d9bdu, (re_fn_t)NoopFn0041d9bd },
  { 0x0041d9c4u, (re_fn_t)NoopFn0041d9c4 }, { 0x0041d9cbu, (re_fn_t)NoopFn0041d9cb }, { 0x0041d9d2u, (re_fn_t)P23_SetBlendMode },
  { 0x0041dd37u, (re_fn_t)P22_SetAlphaTest }, { 0x0041ddbeu, (re_fn_t)NoopFn0041ddbe }, { 0x0041ddc5u, (re_fn_t)P22_SetAlphaFunc },
  { 0x0041de1du, (re_fn_t)P22_SetAlphaRef }, { 0x0041de46u, (re_fn_t)P54_ClearBuffers }, { 0x0041dec1u, (re_fn_t)Ui0041DEC1 },
  { 0x0041dec8u, (re_fn_t)P39_Present }, { 0x0041e075u, (re_fn_t)NoopFn0041e075 }, { 0x0041e07cu, (re_fn_t)NoopFn0041e07c },
  { 0x0041e083u, (re_fn_t)NoopFn0041e083 }, { 0x0041e08au, (re_fn_t)P22_SetViewport }, { 0x0041e14fu, (re_fn_t)P22_SetTexOp },
  { 0x0041e1e4u, (re_fn_t)SetFlagFromArg0041E1E4 }, { 0x0041e207u, (re_fn_t)NoopFn0041e207 }, { 0x0041e20eu, (re_fn_t)NoopFn0041e20e },
  { 0x0041e215u, (re_fn_t)P22_SetCull }, { 0x0041e28au, (re_fn_t)P22_SetZFunc }, { 0x0041e404u, (re_fn_t)P22_SetZWrite },
  { 0x0041e456u, (re_fn_t)NoopFn0041e456 }, { 0x0041e45bu, (re_fn_t)NoopFn0041e45b }, { 0x0041e462u, (re_fn_t)P23_DrawLineA },
  { 0x0041e4b9u, (re_fn_t)P23_DrawLineB }, { 0x0041e510u, (re_fn_t)NoopFn0041e510 }, { 0x0041e517u, (re_fn_t)NoopFn0041e517 },
  { 0x0041e51eu, (re_fn_t)NoopFn0041e51e }, { 0x0041e525u, (re_fn_t)NoopFn0041e525 }, { 0x0041e52cu, (re_fn_t)P98_QuadA },
  { 0x0041e729u, (re_fn_t)P98_QuadB }, { 0x0041e926u, (re_fn_t)P76_TriA1 }, { 0x0041ea2au, (re_fn_t)P76_TriB1 },
  { 0x0041eb2eu, (re_fn_t)NoopFn0041eb2e }, { 0x0041eb35u, (re_fn_t)NoopFn0041eb35 }, { 0x0041eb3cu, (re_fn_t)NoopFn0041eb3c },
  { 0x0041eb43u, (re_fn_t)NoopFn0041eb43 }, { 0x0041eb4au, (re_fn_t)NoopFn0041eb4a }, { 0x0041eb51u, (re_fn_t)P42_VersionString },
  { 0x0041eb69u, (re_fn_t)NoopFn0041eb69 }, { 0x0041eb70u, (re_fn_t)NoopFn0041eb70 }, { 0x0041eb77u, (re_fn_t)NoopFn0041eb77 },
  { 0x0041eb7eu, (re_fn_t)NoopFn0041eb7e }, { 0x0041eb85u, (re_fn_t)NoopFn0041eb85 }, { 0x0041eb8cu, (re_fn_t)P39_LockSurface },
  { 0x0041ec79u, (re_fn_t)Ui0041EC79 }, { 0x0041ec82u, (re_fn_t)P39_UnlockSurface }, { 0x0041ed00u, (re_fn_t)NoopFn0041ed00 },
  { 0x0041ed07u, (re_fn_t)NoopFn0041ed07 }, { 0x0041ed0eu, (re_fn_t)Ui0041ED0E }, { 0x0041ed1au, (re_fn_t)NoopFn0041ed1a },
  { 0x0041ed21u, (re_fn_t)NoopFn0041ed21 }, { 0x0041ed26u, (re_fn_t)NoopFn0041ed26 }, { 0x0041ed2du, (re_fn_t)Ui0041ED2D },
  { 0x0041ed39u, (re_fn_t)NoopFn0041ed39 }, { 0x0041ed3eu, (re_fn_t)Ui0041ED3E }, { 0x0041ed45u, (re_fn_t)NoopFn0041ed45 },
  { 0x0041ed4cu, (re_fn_t)NoopFn0041ed4c }, { 0x0041ed53u, (re_fn_t)Ui0041ED53 }, { 0x0041ed63u, (re_fn_t)NoopFn0041ed63 },
  { 0x0041ed68u, (re_fn_t)GetVarA421A8 }, { 0x0041ed72u, (re_fn_t)GetVarA421A4 }, { 0x0041ed7cu, (re_fn_t)NoopFn0041ed7c },
  { 0x0041ed83u, (re_fn_t)Ui0041ED83 }, { 0x0041ed8au, (re_fn_t)Ui0041ED8A }, { 0x0041ed91u, (re_fn_t)Ui0041ED91 },
  { 0x0041f2a0u, (re_fn_t)P31_ReleaseDirectDraw }, { 0x0041f47cu, (re_fn_t)Ui0041F47C }, { 0x0041f485u, (re_fn_t)NoopFn0041f485 },
  { 0x0041f48cu, (re_fn_t)NoopFn0041f48c }, { 0x0041f493u, (re_fn_t)NoopFn0041f493 }, { 0x0041f49au, (re_fn_t)NoopFn0041f49a },
  { 0x0041f4a1u, (re_fn_t)P112_TexDownload }, { 0x0041f56fu, (re_fn_t)NoopFn0041f56f }, { 0x0041f576u, (re_fn_t)NoopFn0041f576 },
  { 0x0041f57du, (re_fn_t)P32_SetPalette }, { 0x0041f6a2u, (re_fn_t)NoopFn0041f6a2 }, { 0x0041f6a9u, (re_fn_t)P22_SetTexFilter },
  { 0x0041f72du, (re_fn_t)NoopFn0041f72d }, { 0x0041f734u, (re_fn_t)Ret1FFFF8IfZero }, { 0x0041f74au, (re_fn_t)Ui0041F74A },
  { 0x0041f753u, (re_fn_t)NoopFn0041f753 }, { 0x0041f75au, (re_fn_t)NoopFn0041f75a }, { 0x0041f761u, (re_fn_t)NoopFn0041f761 },
  { 0x0041f768u, (re_fn_t)NoopFn0041f768 }, { 0x0041f76fu, (re_fn_t)P53_SetTexSource }, { 0x0041f7e7u, (re_fn_t)Ui0041F7E7 },
  { 0x0041f7f0u, (re_fn_t)NoopFn0041f7f0 }, { 0x0041f7f7u, (re_fn_t)Ui0041F7F7 }, { 0x0041f800u, (re_fn_t)Ui0041F800 },
  { 0x0041f809u, (re_fn_t)NoopFn0041f809 }, { 0x0041f810u, (re_fn_t)NoopFn0041f810 }, { 0x0041f817u, (re_fn_t)NoopFn0041f817 },
  { 0x0041f81eu, (re_fn_t)NoopFn0041F81E }, { 0x0041f825u, (re_fn_t)P76_TriA2 }, { 0x0041f929u, (re_fn_t)P76_TriB2 },
  { 0x0041fa2du, (re_fn_t)Ui0041FA2D }, { 0x0041fa36u, (re_fn_t)RetZero0041FA36 }, { 0x0041fa40u, (re_fn_t)Ui0041FA40 },
  { 0x0041fa49u, (re_fn_t)NoopFn0041FA49 }, { 0x0041fa50u, (re_fn_t)NoopFn0041FA50 }, { 0x0041fa57u, (re_fn_t)NoopFn0041FA57 },
  { 0x0041fa5eu, (re_fn_t)GetConst0041FA5E }, { 0x0041fa6bu, (re_fn_t)Ui0041FA6B }, { 0x0041fa74u, (re_fn_t)Ui0041FA74 },
  { 0x0041fa7du, (re_fn_t)NoopFn0041FA7D }, { 0x0041fa84u, (re_fn_t)Ui0041FA84 }, { 0x0041fa8bu, (re_fn_t)NoopFn0041FA8B },
  { 0x0041fa92u, (re_fn_t)NoopFn0041FA92 }, { 0x0041fa99u, (re_fn_t)Ui0041FA99 }, { 0x0041faa2u, (re_fn_t)Ui0041FAA2 },
  { 0x0041faabu, (re_fn_t)Ui0041FAAB }, { 0x0041fab4u, (re_fn_t)NoopFn0041fab4 }, { 0x0041fab9u, (re_fn_t)NoopFn0041FAB9 },
  { 0x00421cabu, (re_fn_t)SetZoom_00421CAB },
  { 0x0041ed98u, (re_fn_t)P151_WinOpen },
  /* v1.58: обработчики таблицы меню опций 0057b5a8 (004048dd) */
  { 0x00404e52u, (re_fn_t)MenuRowsTo3_00404E52 },  { 0x00404e7eu, (re_fn_t)MenuRowsIf0To2_00404E7E },
  { 0x00404eb0u, (re_fn_t)ToggleBDFA44_Call40500D }, { 0x00404ec9u, (re_fn_t)ToggleBDFA48_Call40500D },
  { 0x00404ee2u, (re_fn_t)ToggleBDFA4C_Call40500D }, { 0x00404efbu, (re_fn_t)ToggleBDFA50_Call40500D },
  { 0x00404f14u, (re_fn_t)ToggleBDFA54_Call40500D }, { 0x00404f2du, (re_fn_t)ToggleB87E9C_Call40500D },
  { 0x00404f46u, (re_fn_t)ToggleBDFA58_Call40500D }, { 0x00404f5fu, (re_fn_t)Set575EF0_4Ret0 },
  { 0x00404f70u, (re_fn_t)P12_Fn00404F70 },        { 0x00404faeu, (re_fn_t)P12_Fn00404FAE },
  { 0x00404ffeu, (re_fn_t)MenuCallAction40CD17 },
  { 0x0048bcc0u, (re_fn_t)P50_SoundShutdown }, { 0x0048bd3bu, (re_fn_t)NoopFn0048bd3b },
  { 0x0048bd40u, (re_fn_t)P49_Commit },        { 0x0048bd65u, (re_fn_t)P26_WaveSetVolume },
  { 0x0048bf52u, (re_fn_t)P106_EaxPreset },
  { 0x0048bdccu, (re_fn_t)P38_SetPrimaryFormat }, { 0x0048be68u, (re_fn_t)P38_SetSpeakerConfig },
  { 0x0048c520u, (re_fn_t)P50_ReleaseVoice },  { 0x0048c74bu, (re_fn_t)P49_ListenerPos },
  { 0x0048c77eu, (re_fn_t)P49_ListenerOrient }, { 0x0048c7bdu, (re_fn_t)P49_ListenerVel },
  { 0x0048c7f0u, (re_fn_t)P49_Play },          { 0x0048c83du, (re_fn_t)P50_ReleaseBuf },
  { 0x0048c8d6u, (re_fn_t)P50_ResetBuf },      { 0x0048c97cu, (re_fn_t)P49_SetVolume },
  { 0x0048c9b2u, (re_fn_t)P49_SetFreq },       { 0x0048c9e8u, (re_fn_t)P49_SetPos3D },
  { 0x0048ca28u, (re_fn_t)P49_SetVel3D },      { 0x0048ca68u, (re_fn_t)P49_SetMode3D },
  { 0x0048caa0u, (re_fn_t)P49_GetStatus },
  { 0x0048c2a3u, (re_fn_t)P148_DupVoice },     /* v1.93: P97_DrvC */
  /* v1.56: опкоды скрипта .data 0055fcac (P111_ScriptTick 004cf2cf); все 33 перенесены с v1.57 */
  { 0x004d03fdu, (re_fn_t)ReturnZero004D03FD },    { 0x004d020bu, (re_fn_t)P48_OpSet3 },
  { 0x004d02c6u, (re_fn_t)ScriptReadShort3_004D02C6 }, { 0x004d033fu, (re_fn_t)ScriptReadVec3_004D033F },
  { 0x004d0404u, (re_fn_t)ScriptOpSetBit2_004D0404 }, { 0x004d107eu, (re_fn_t)P48_OpSet4 },
  { 0x004d1111u, (re_fn_t)ScriptOpSkipClear004D1111 }, { 0x004d1135u, (re_fn_t)ScriptReadU32_004D1135 },
  { 0x004d116cu, (re_fn_t)P48_OpRampDown },        { 0x004d121bu, (re_fn_t)P48_OpRampUp },
  { 0x004d133cu, (re_fn_t)ScriptLoopStep_004D133C }, { 0x004d13d8u, (re_fn_t)ScriptOpSetBit4_004D13D8 },
  { 0x004d1402u, (re_fn_t)ScriptOpClearBit2_004D1402 }, { 0x004d142cu, (re_fn_t)P48_OpFlags },
  { 0x004d14d8u, (re_fn_t)ScriptSkip16_004D14D8 }, { 0x004d1635u, (re_fn_t)ScriptSkipBack_004D1635 },
  { 0x004d1672u, (re_fn_t)P48_OpRepeat },          { 0x004d1529u, (re_fn_t)P65_ScriptCall },
  { 0x004d1601u, (re_fn_t)ScriptOpSkip4_004D1601 }, { 0x004d12cau, (re_fn_t)ScriptReadPair_004D12CA },
  { 0x004d1737u, (re_fn_t)ScriptOpToggle10_004D1737 }, { 0x004d156au, (re_fn_t)P97_ScriptOpNext },
  { 0x004d0d7cu, (re_fn_t)P48_OpTurn },            { 0x004d0f28u, (re_fn_t)P95_ScriptTurn },
  { 0x004d03d0u, (re_fn_t)ScriptOpSetBit200_004D03D0 },
  /* v1.57: оставшиеся опкоды 0055fcac */
  { 0x004d09fdu, (re_fn_t)P112_OpMoveTo }, { 0x004d1765u, (re_fn_t)P112_OpMoveCur }, { 0x004d0734u, (re_fn_t)P112_OpMoveCurve },
};
#define RE_DYN_MAX 4096
#define RE_FN_MAX 512
static re_region_t g_dyn[RE_DYN_MAX];
static uint32_t g_ndyn, g_next_syn = 0x80000000u;
static re_fnent_t g_fns[RE_FN_MAX];
static uint32_t g_nfns;

/* v2.02: запасная область — образ .rdata+.data Game.exe (game/data_image.c), только в режиме игры */
static uint8_t *g_img; static uint32_t g_img_base, g_img_size;
int re_ptr_has_image(void) { return g_img != NULL; }   /* v2.05: 1 — режим игры (образ .data подключён) */
uint8_t *re_gvar_img; uint32_t re_gvar_img_size;   /* v2.03: gvar.h */
void re_ptr_set_image(uint32_t base, void *p, uint32_t size) {
  g_img = (uint8_t *)p; g_img_base = base; g_img_size = size;
  /* v2.03: переменные GAME_VAR этого диапазона (скалярные типы) в образе (RE_NO_GVAR_IMG=1 — выкл.) */
  /* v2.03: память данных Game.exe целиком — .rdata+.data с .bss, 00546000..01287000 (13 МБ): образ + нули */
  if (base == 0x00546000u && size <= 0x00d41000u) {
    uint8_t *img = (uint8_t *)calloc(1, 0x00d41000u);
    if (img != NULL) { memcpy(img, p, size); g_img = img; g_img_size = 0x00d41000u;
      if (getenv("RE_NO_GVAR_IMG") == NULL) { re_gvar_img = img; re_gvar_img_size = 0x00d41000u; } }
  }
}
/* v2.03: game/gvar_img_tab.c — переменные GAME_VAR, которые в игре живут в образе (их native-объекты не используются):
   адрес внутри такой переменной — в образ раньше реестра g_dyn/k_regions; прочие адреса — как прежде, образ последним */
typedef struct { uint32_t addr, size; } re_gvar_range_t;
extern const re_gvar_range_t re_gvar_ranges[] __attribute__((weak));
extern const uint32_t re_gvar_ranges_n __attribute__((weak));
static int in_gvar_range(uint32_t a) {
  if (&re_gvar_ranges_n == NULL) return 0;
  for (uint32_t i = 0; i < re_gvar_ranges_n; i++) if (a >= re_gvar_ranges[i].addr && a - re_gvar_ranges[i].addr < re_gvar_ranges[i].size) return 1;
  return 0;
}
void *re_ptr(uint32_t addr) {
  if (addr == 0) return NULL;
  if (re_gvar_img != NULL && addr >= g_img_base && addr - g_img_base < g_img_size && in_gvar_range(addr)) return g_img + (addr - g_img_base);   /* v2.03 */
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (addr >= g_dyn[i].addr && addr - g_dyn[i].addr < g_dyn[i].size) return g_dyn[i].p + (addr - g_dyn[i].addr);
  for (size_t i = 0; i < sizeof k_regions / sizeof k_regions[0]; i++)
    if (addr >= k_regions[i].addr && addr - k_regions[i].addr < k_regions[i].size) return k_regions[i].p + (addr - k_regions[i].addr);
  if (g_img != NULL && addr >= g_img_base && addr - g_img_base < g_img_size) return g_img + (addr - g_img_base);   /* v2.02 */
  return NULL;
}
uint32_t re_addr(const void *pv) {
  const uint8_t *p = (const uint8_t *)pv;
  if (p == NULL) return 0;
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (p >= g_dyn[i].p && p < g_dyn[i].p + g_dyn[i].size) return g_dyn[i].addr + (uint32_t)(p - g_dyn[i].p);
  for (size_t i = 0; i < sizeof k_regions / sizeof k_regions[0]; i++)
    if (p >= k_regions[i].p && p < k_regions[i].p + k_regions[i].size) return k_regions[i].addr + (uint32_t)(p - k_regions[i].p);
  if (g_img != NULL && p >= g_img && p < g_img + g_img_size) return g_img_base + (uint32_t)(p - g_img);   /* v2.02 */
  return re_ptr_register_dyn((void *)(uintptr_t)p, 1);
}
void re_ptr_register(uint32_t addr, void *native, uint32_t size) {
  if (native == NULL || size == 0) return;
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (g_dyn[i].p == native) { g_dyn[i].addr = addr; g_dyn[i].size = size; return; }
  if (g_ndyn < RE_DYN_MAX) { g_dyn[g_ndyn].addr = addr; g_dyn[g_ndyn].p = (uint8_t *)native; g_dyn[g_ndyn].size = size; g_ndyn++; }
}
uint32_t re_ptr_register_dyn(void *native, uint32_t size) {
  if (native == NULL || g_ndyn >= RE_DYN_MAX) return 0;
  uint32_t a = g_next_syn;
  g_next_syn += (size + 0xfu) & ~0xfu;
  re_ptr_register(a, native, size);
  return a;
}
void re_ptr_unregister(const void *native) {
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (g_dyn[i].p == native) { g_dyn[i] = g_dyn[--g_ndyn]; return; }
}
/* v2.03: platform/native/fn_table.c (tools/gen_fn_table.py, из re_hook install.c) — только в игре (образ .data задан) */
extern const re_fnent_t re_fn_table[] __attribute__((weak));
extern const size_t re_fn_table_n __attribute__((weak));
static re_fn_t fn_table_find(uint32_t addr) {
  if (g_img == NULL || &re_fn_table_n == NULL || re_fn_table == NULL) return NULL;
  size_t lo = 0, hi = re_fn_table_n;
  while (lo < hi) { size_t m = (lo + hi) / 2; if (re_fn_table[m].addr < addr) lo = m + 1; else hi = m; }
  return (lo < re_fn_table_n && re_fn_table[lo].addr == addr) ? re_fn_table[lo].fn : NULL;
}
static uint32_t fn_table_addr(re_fn_t fn) {
  if (g_img == NULL || &re_fn_table_n == NULL || re_fn_table == NULL) return 0;
  for (size_t i = 0; i < re_fn_table_n; i++) if (re_fn_table[i].fn == fn) return re_fn_table[i].addr;
  return 0;
}
re_fn_t re_fn(uint32_t addr) {
  if (addr == 0) return NULL;
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].addr == addr) return g_fns[i].fn;
  for (size_t i = 0; i < sizeof k_fns / sizeof k_fns[0]; i++) if (k_fns[i].addr == addr) return k_fns[i].fn;
  return fn_table_find(addr);
}
uint32_t re_fn_addr(re_fn_t fn) {
  if (fn == NULL) return 0;
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].fn == fn) return g_fns[i].addr;
  for (size_t i = 0; i < sizeof k_fns / sizeof k_fns[0]; i++) if (k_fns[i].fn == fn) return k_fns[i].addr;
  return fn_table_addr(fn);
}
void re_fn_register(uint32_t addr, re_fn_t fn) {
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].addr == addr) { g_fns[i].fn = fn; return; }
  if (g_nfns < RE_FN_MAX) { g_fns[g_nfns].addr = addr; g_fns[g_nfns].fn = fn; g_nfns++; }
}
#endif
