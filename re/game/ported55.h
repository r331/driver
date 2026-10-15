#pragma once
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
typedef uint32_t p55_tabA_t[1106];
typedef uint32_t p55_tabB_t[2081];
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
#define P55_A680     GAME_VAR(int32_t, P55_A680, 0x0054a680)
#define P55_A684     GAME_VAR(int32_t, P55_A684, 0x0054a684)
#define P55_A688     GAME_VAR(int32_t, P55_A688, 0x0054a688)
#define P55_A68C     GAME_VAR(int32_t, P55_A68C, 0x0054a68c)
#define P55_A690     GAME_VAR(int32_t, P55_A690, 0x0054a690)
#define P55_Paper0   GAME_VAR(int32_t, P55_Paper0, 0x00d03900)
#define P55_Paper1   GAME_VAR(int32_t, P55_Paper1, 0x00d0448c)
#define P55_Paper2   GAME_VAR(int32_t, P55_Paper2, 0x00d038fc)
#define P55_Lang     GAME_VAR(int32_t, P55_Lang, 0x00c557fc)
#ifndef RE_HOOK_BUILD
extern int32_t P55_CntA, P55_CntB, P55_Flag38C, P55_VarC0, P55_Var20, P55_VarD2C, P55_VarD28, P55_VarD24, P55_VarD20;
extern int32_t P55_PopCnt, P55_PopSkip, P55_PopB2AC, P55_A4219C, P55_A421A0, P55_RecCnt, P55_V57B6FC, P55_V1285428;
extern int32_t P55_V1285424, P55_BDFA18, P55_B87EB8, P55_A680, P55_A684, P55_A688, P55_A68C, P55_A690;
extern int32_t P55_Paper0, P55_Paper1, P55_Paper2, P55_Lang;
extern uint8_t P55_VarC6; extern const char *P55_DefName; extern uint8_t *P55_RecBase;
extern p55_tabA_t P55_TabA; extern p55_tabB_t P55_TabB; extern p55_flags8_t P55_FlagsC; extern p55_pop_t P55_PopTab;
extern p55_frustum_t P55_Frustum; extern p55_glide_t P55_GlideInfo;
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
