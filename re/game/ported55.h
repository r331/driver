#pragma once
#include "menugfx.h"
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported54.h"
#include "ported6.h"
#include "ported7.h"
#include "ported12.h"
#include "ported19.h"
#include "ported23.h"
#include "ported24.h"
#include "ported29.h"
#include "ported31.h"
#include "ported36.h"
#include "ported44.h"
#include "ported52.h"
#include "menuselect.h"
#include "widgets.h"
#include "globalsets.h"
#include "uihandlers3.h"
#include "director.h"
#include <stdint.h>
/* Шаг D: 20 мелких функций без указателей в структурах — циклы по таблицам объектов, списки имён (8 слотов),
   очередь отложенных вызовов, загрузка FRUSTRUM.DAT и файлов целиком, описание устройства Glide/D3D, переключение
   раскладки, остановка звука, инициализация режима Glide, фон «бумага». Все cdecl. */
typedef struct { uint32_t id; uint16_t w; uint16_t pad; uint32_t x, y; } P55_Pop;
_Static_assert(sizeof(P55_Pop) == 0x10, "P55_Pop");
typedef P55_Pop p55_pop_t[146];
typedef void *p55_tabA_t[1106];
typedef void *p55_tabB_t[2081];
typedef uint8_t  p55_frustum_t[0x8000];
typedef int32_t  p55_flags8_t[8];
typedef uint32_t p55_glide_t[16];

#define P55_CntA     GAME_VAR(int32_t, P55_CntA, 0x00cf2f88)
#define P55_TabA     GAME_VAR(p55_tabA_t, P55_TabA, 0x00ce0f40)
#define P55_CntB     GAME_VAR(int32_t, P55_CntB, 0x00d022e4)
#define P55_TabB     GAME_VAR(p55_tabB_t, P55_TabB, 0x00d00260)
#define P55_Flag38C  GAME_VAR(int32_t, P55_Flag38C, 0x00b1c38c)
#define P55_VarC0    GAME_VAR(int32_t, P55_VarC0, 0x00cff9c0)
#define P55_Var20    GAME_VAR(int32_t, P55_Var20, 0x00c97a20)
#define P55_VarD2C   GAME_VAR(int32_t, P55_VarD2C, 0x00d0022c)
#define P55_VarD28   GAME_VAR(int32_t, P55_VarD28, 0x00d00228)
#define P55_VarD24   GAME_VAR(int32_t, P55_VarD24, 0x00d00224)
#define P55_VarD20   GAME_VAR(int32_t, P55_VarD20, 0x00d00220)
#define P55_VarC6    GAME_VAR(uint8_t, P55_VarC6, 0x00cff9c6)
#define P55_DefName  GAME_VAR(const char *, P55_DefName, 0x00c55854)
#define P55_FlagsC   GAME_VAR(p55_flags8_t, P55_FlagsC, 0x00b5a428)
#define P55_PopCnt   GAME_VAR(int32_t, P55_PopCnt, 0x00b2c3b0)
#define P55_PopTab   GAME_VAR(p55_pop_t, P55_PopTab, 0x00d10e80)
#define P55_PopSkip  GAME_VAR(int32_t, P55_PopSkip, 0x00b87ecc)
#define P55_PopB2AC  GAME_VAR(int32_t, P55_PopB2AC, 0x00b2c3ac)
#define P55_Frustum  GAME_VAR(p55_frustum_t, P55_Frustum, 0x00cb8f20)
#define P55_A4219C   GAME_VAR(int32_t, P55_A4219C, 0x00a4219c)
#define P55_A421A0   GAME_VAR(int32_t, P55_A421A0, 0x00a421a0)
#define P55_RecBase  GAME_VAR(uint8_t *, P55_RecBase, 0x00b5a8bc)
#define P55_RecCnt   GAME_VAR(int32_t, P55_RecCnt, 0x00b5a8c0)
#define P55_V57B6FC  GAME_VAR(int32_t, P55_V57B6FC, 0x0057b6fc)
#define P55_V1285428 GAME_VAR(int32_t, P55_V1285428, 0x01285428)
#define P55_V1285424 GAME_VAR(int32_t, P55_V1285424, 0x01285424)
#define P55_BDFA18   GAME_VAR(int32_t, P55_BDFA18, 0x00bdfa18)
#define P55_GlideInfo GAME_VAR(p55_glide_t, P55_GlideInfo, 0x00bdfa80)
#define P55_B87EB8   GAME_VAR(int32_t, P55_B87EB8, 0x00b87eb8)
#define P55_A680 MENUGFX_VAR(int32_t, P55_A680, 0x0054a680)
#define P55_A684 MENUGFX_VAR(int32_t, P55_A684, 0x0054a684)
#define P55_A688 MENUGFX_VAR(int32_t, P55_A688, 0x0054a688)
#define P55_A68C MENUGFX_VAR(int32_t, P55_A68C, 0x0054a68c)
#define P55_A690 MENUGFX_VAR(int32_t, P55_A690, 0x0054a690)
#define P55_Paper0   GAME_VAR(int32_t, P55_Paper0, 0x00d03900)
#define P55_Paper1   GAME_VAR(int32_t, P55_Paper1, 0x00d0448c)
#define P55_Paper2   GAME_VAR(int32_t, P55_Paper2, 0x00d038fc)
#define P55_Lang     GAME_VAR(int32_t, P55_Lang, 0x00c557fc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P55_CntA") /*gvi*/
#undef P55_CntA /*gvi*/
#pragma push_macro("P55_CntB") /*gvi*/
#undef P55_CntB /*gvi*/
#pragma push_macro("P55_Flag38C") /*gvi*/
#undef P55_Flag38C /*gvi*/
#pragma push_macro("P55_VarC0") /*gvi*/
#undef P55_VarC0 /*gvi*/
#pragma push_macro("P55_Var20") /*gvi*/
#undef P55_Var20 /*gvi*/
#pragma push_macro("P55_VarD2C") /*gvi*/
#undef P55_VarD2C /*gvi*/
#pragma push_macro("P55_VarD28") /*gvi*/
#undef P55_VarD28 /*gvi*/
#pragma push_macro("P55_VarD24") /*gvi*/
#undef P55_VarD24 /*gvi*/
#pragma push_macro("P55_VarD20") /*gvi*/
#undef P55_VarD20 /*gvi*/
extern int32_t P55_CntA, P55_CntB, P55_Flag38C, P55_VarC0, P55_Var20, P55_VarD2C, P55_VarD28, P55_VarD24, P55_VarD20;
#pragma pop_macro("P55_VarD20") /*gvi*/
#pragma pop_macro("P55_VarD24") /*gvi*/
#pragma pop_macro("P55_VarD28") /*gvi*/
#pragma pop_macro("P55_VarD2C") /*gvi*/
#pragma pop_macro("P55_Var20") /*gvi*/
#pragma pop_macro("P55_VarC0") /*gvi*/
#pragma pop_macro("P55_Flag38C") /*gvi*/
#pragma pop_macro("P55_CntB") /*gvi*/
#pragma pop_macro("P55_CntA") /*gvi*/
#pragma push_macro("P55_PopCnt") /*gvi*/
#undef P55_PopCnt /*gvi*/
#pragma push_macro("P55_PopSkip") /*gvi*/
#undef P55_PopSkip /*gvi*/
#pragma push_macro("P55_PopB2AC") /*gvi*/
#undef P55_PopB2AC /*gvi*/
#pragma push_macro("P55_A4219C") /*gvi*/
#undef P55_A4219C /*gvi*/
#pragma push_macro("P55_A421A0") /*gvi*/
#undef P55_A421A0 /*gvi*/
#pragma push_macro("P55_RecCnt") /*gvi*/
#undef P55_RecCnt /*gvi*/
#pragma push_macro("P55_V57B6FC") /*gvi*/
#undef P55_V57B6FC /*gvi*/
#pragma push_macro("P55_V1285428") /*gvi*/
#undef P55_V1285428 /*gvi*/
extern int32_t P55_PopCnt, P55_PopSkip, P55_PopB2AC, P55_A4219C, P55_A421A0, P55_RecCnt, P55_V57B6FC, P55_V1285428;
#pragma pop_macro("P55_V1285428") /*gvi*/
#pragma pop_macro("P55_V57B6FC") /*gvi*/
#pragma pop_macro("P55_RecCnt") /*gvi*/
#pragma pop_macro("P55_A421A0") /*gvi*/
#pragma pop_macro("P55_A4219C") /*gvi*/
#pragma pop_macro("P55_PopB2AC") /*gvi*/
#pragma pop_macro("P55_PopSkip") /*gvi*/
#pragma pop_macro("P55_PopCnt") /*gvi*/
#pragma push_macro("P55_V1285424") /*gvi*/
#undef P55_V1285424 /*gvi*/
#pragma push_macro("P55_BDFA18") /*gvi*/
#undef P55_BDFA18 /*gvi*/
#pragma push_macro("P55_B87EB8") /*gvi*/
#undef P55_B87EB8 /*gvi*/
extern int32_t P55_V1285424, P55_BDFA18, P55_B87EB8;
#pragma pop_macro("P55_B87EB8") /*gvi*/
#pragma pop_macro("P55_BDFA18") /*gvi*/
#pragma pop_macro("P55_V1285424") /*gvi*/
#pragma push_macro("P55_Paper0") /*gvi*/
#undef P55_Paper0 /*gvi*/
#pragma push_macro("P55_Paper1") /*gvi*/
#undef P55_Paper1 /*gvi*/
#pragma push_macro("P55_Paper2") /*gvi*/
#undef P55_Paper2 /*gvi*/
#pragma push_macro("P55_Lang") /*gvi*/
#undef P55_Lang /*gvi*/
extern int32_t P55_Paper0, P55_Paper1, P55_Paper2, P55_Lang;
#pragma pop_macro("P55_Lang") /*gvi*/
#pragma pop_macro("P55_Paper2") /*gvi*/
#pragma pop_macro("P55_Paper1") /*gvi*/
#pragma pop_macro("P55_Paper0") /*gvi*/
#pragma push_macro("P55_VarC6") /*gvi*/
#undef P55_VarC6 /*gvi*/
extern uint8_t P55_VarC6; extern const char *P55_DefName; extern uint8_t *P55_RecBase;
#pragma pop_macro("P55_VarC6") /*gvi*/
#pragma push_macro("P55_FlagsC") /*gvi*/
#undef P55_FlagsC /*gvi*/
extern p55_tabA_t P55_TabA; extern p55_tabB_t P55_TabB; extern p55_flags8_t P55_FlagsC; extern p55_pop_t P55_PopTab;
#pragma pop_macro("P55_FlagsC") /*gvi*/
#pragma push_macro("P55_Frustum") /*gvi*/
#undef P55_Frustum /*gvi*/
#pragma push_macro("P55_GlideInfo") /*gvi*/
#undef P55_GlideInfo /*gvi*/
extern p55_frustum_t P55_Frustum; extern p55_glide_t P55_GlideInfo;
#pragma pop_macro("P55_GlideInfo") /*gvi*/
#pragma pop_macro("P55_Frustum") /*gvi*/
#endif

void    P55_RunTableA(void);            /* 004ef309: для каждой из P55_CntA записей вызвать 004ee18b, матрица = транспонат 011effa0 */
void    P55_RunTableB(void);            /* 004ef364: то же для таблицы B, на время цикла флаг 00b1c38c = 2 */
void    P55_ResetSel(void);             /* 004ee129: сбросить 6 индексов в -1, вызвать 004ed5f8/004edaa2 */
void    P55_NamesA(void);               /* 0041219e: имена 8 слотов (по 16 байт) через 00405e79 */
void    P55_NamesB(void);               /* 004125b9: то же через 00405fdb, буфер 32 */
void    P55_NamesC(void);               /* 0041afca: имена по 0x11 через 00405e79 */
void    P55_NamesD(void);               /* 00510784: имена по 0x11 в P52_NameTab через 00405fdb */
void    P55_PopDeferred(void);          /* 004d9237: разобрать очередь отложенных вызовов 004d92d2 */
int32_t P55_LoadFrustum(void);          /* 004eb3c0: FRUSTRUM.DAT, 256 записей по 0x80; 0 — успех, -1 — нет файла */
void    P55_FillDevInfo(uint32_t *out); /* 0041d819: описание устройства D3D (11 слов) */
void    P55_GlideDevInfo(uint32_t *out);/* 00424974: то же для Glide, либо 0041d819 */
void   *P55_LoadFile(const char *name); /* 004d30f8: весь файл в DebugMalloc-буфер (file.c:0x86) или NULL */
void   *P55_LoadFileSize(const char *name, int32_t *size); /* 004d318e: то же + размер (file.c:0xb1) */
void    P55_SaveRec(int32_t idx);       /* 00519873: запись 0x1a4 байт: время, индекс, копия 0x54 и 0x148 байт */
int32_t P55_NextPad(void);              /* 004073ab: следующий джойстик или раскладка по умолчанию; всегда 0 */
void    P55_StopAudio(void);            /* 0050f289: остановить звук/CD после миссии */
void    P55_GlideInit(int32_t a, int32_t b, int32_t mode); /* 005226b5: параметры окна Glide */
int32_t P55_SetScreen(int32_t w, int32_t h);               /* 0040c533: сменить разрешение, при сбое вернуть прежнее; всегда 1 */
void    P55_MenuLangCall(void);         /* 00409d66: номер языка по 005d578c (0x1c..0x20) → 00417651 */
void    P55_LoadPaper(void);            /* 004e6175: текстуры ELPAPEL/LINE/CROSS, PAPER_xx по языку */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P55_CntA
#define P55_CntA (*(int32_t *)re_gvar(0x00cf2f88u, sizeof(int32_t), (void *)&P55_CntA))
#undef P55_CntB
#define P55_CntB (*(int32_t *)re_gvar(0x00d022e4u, sizeof(int32_t), (void *)&P55_CntB))
#undef P55_Flag38C
#define P55_Flag38C (*(int32_t *)re_gvar(0x00b1c38cu, sizeof(int32_t), (void *)&P55_Flag38C))
#undef P55_VarC0
#define P55_VarC0 (*(int32_t *)re_gvar(0x00cff9c0u, sizeof(int32_t), (void *)&P55_VarC0))
#undef P55_Var20
#define P55_Var20 (*(int32_t *)re_gvar(0x00c97a20u, sizeof(int32_t), (void *)&P55_Var20))
#undef P55_VarD2C
#define P55_VarD2C (*(int32_t *)re_gvar(0x00d0022cu, sizeof(int32_t), (void *)&P55_VarD2C))
#undef P55_VarD28
#define P55_VarD28 (*(int32_t *)re_gvar(0x00d00228u, sizeof(int32_t), (void *)&P55_VarD28))
#undef P55_VarD24
#define P55_VarD24 (*(int32_t *)re_gvar(0x00d00224u, sizeof(int32_t), (void *)&P55_VarD24))
#undef P55_VarD20
#define P55_VarD20 (*(int32_t *)re_gvar(0x00d00220u, sizeof(int32_t), (void *)&P55_VarD20))
#undef P55_VarC6
#define P55_VarC6 (*(uint8_t *)re_gvar(0x00cff9c6u, sizeof(uint8_t), (void *)&P55_VarC6))
#undef P55_FlagsC
#define P55_FlagsC (*(p55_flags8_t *)re_gvar(0x00b5a428u, sizeof(p55_flags8_t), (void *)&P55_FlagsC))
#undef P55_PopCnt
#define P55_PopCnt (*(int32_t *)re_gvar(0x00b2c3b0u, sizeof(int32_t), (void *)&P55_PopCnt))
#undef P55_PopSkip
#define P55_PopSkip (*(int32_t *)re_gvar(0x00b87eccu, sizeof(int32_t), (void *)&P55_PopSkip))
#undef P55_PopB2AC
#define P55_PopB2AC (*(int32_t *)re_gvar(0x00b2c3acu, sizeof(int32_t), (void *)&P55_PopB2AC))
#undef P55_Frustum
#define P55_Frustum (*(p55_frustum_t *)re_gvar(0x00cb8f20u, sizeof(p55_frustum_t), (void *)&P55_Frustum))
#undef P55_A4219C
#define P55_A4219C (*(int32_t *)re_gvar(0x00a4219cu, sizeof(int32_t), (void *)&P55_A4219C))
#undef P55_A421A0
#define P55_A421A0 (*(int32_t *)re_gvar(0x00a421a0u, sizeof(int32_t), (void *)&P55_A421A0))
#undef P55_RecCnt
#define P55_RecCnt (*(int32_t *)re_gvar(0x00b5a8c0u, sizeof(int32_t), (void *)&P55_RecCnt))
#undef P55_V57B6FC
#define P55_V57B6FC (*(int32_t *)re_gvar(0x0057b6fcu, sizeof(int32_t), (void *)&P55_V57B6FC))
#undef P55_V1285428
#define P55_V1285428 (*(int32_t *)re_gvar(0x01285428u, sizeof(int32_t), (void *)&P55_V1285428))
#undef P55_V1285424
#define P55_V1285424 (*(int32_t *)re_gvar(0x01285424u, sizeof(int32_t), (void *)&P55_V1285424))
#undef P55_BDFA18
#define P55_BDFA18 (*(int32_t *)re_gvar(0x00bdfa18u, sizeof(int32_t), (void *)&P55_BDFA18))
#undef P55_GlideInfo
#define P55_GlideInfo (*(p55_glide_t *)re_gvar(0x00bdfa80u, sizeof(p55_glide_t), (void *)&P55_GlideInfo))
#undef P55_B87EB8
#define P55_B87EB8 (*(int32_t *)re_gvar(0x00b87eb8u, sizeof(int32_t), (void *)&P55_B87EB8))
#undef P55_Paper0
#define P55_Paper0 (*(int32_t *)re_gvar(0x00d03900u, sizeof(int32_t), (void *)&P55_Paper0))
#undef P55_Paper1
#define P55_Paper1 (*(int32_t *)re_gvar(0x00d0448cu, sizeof(int32_t), (void *)&P55_Paper1))
#undef P55_Paper2
#define P55_Paper2 (*(int32_t *)re_gvar(0x00d038fcu, sizeof(int32_t), (void *)&P55_Paper2))
#undef P55_Lang
#define P55_Lang (*(int32_t *)re_gvar(0x00c557fcu, sizeof(int32_t), (void *)&P55_Lang))
#endif
/* gvar-img v2.03 end */
