#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported31.h"
#include "ported45.h"
#include "ported48.h"
#include "ported56.h"
#include "ported57.h"
#include "smallfuncs.h"
#include "globalsets.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Шаг D: 25 функций — переключатель экрана меню, коды читов, освобождение списков/таблиц (указатели хранятся как есть:
   в hook — 32-битные, в native — родные), циклы экранов меню 00419f00/00419ab0/00413d70/00416540, подготовка меню 00415f67,
   таблица записей карты 0051be3c, демо-ролик, строки LANG/MISSION, значок DLOGO, конфиг CONFIG.DAT и проверка GAMEn.BIN, ширина строки шрифта.
   Все cdecl (Ghidra-метка __fastcall у 00413d70 ложная: ECX не используется). */
typedef struct { const char *name; int32_t *var; } p58_cheat_t;           /* запись таблицы кодов читов (8 байт в Game.exe) */
typedef p58_cheat_t p58_cheats_t[12];                                     /* 11 кодов + нулевая запись */
typedef struct { int32_t a; void *p; } p58_slot_t;                        /* 8 байт в Game.exe: поле +4 — буфер */
typedef struct { int32_t a; void *p; int32_t c; } p58_rec_t;              /* 12 байт в Game.exe: поле +4 — буфер */
typedef struct { int32_t a, b; void *items; } p58_cell_t;                 /* +8 — буфер */
typedef struct { int32_t count; void **items; } p58_list_t;               /* список блоков: каждый элемент начинается с указателя на строку */
typedef const char *p58_names_t[8];
typedef uint8_t p58_font_t[8 * 0x806 + 0x20];
typedef uint8_t p58_objs_t[10][0x34];
typedef void *p58_blkidx_t[0x4000];
typedef uint8_t p58_cfg_t[0x10c];
#define P58_MenuSel     GAME_VAR(int32_t, P58_MenuSel, 0x005fed9c)
#define P58_MenuFn      GAME_VAR(int32_t, P58_MenuFn, 0x005fea44)
#define P58_MenuIdx     GAME_VAR(int32_t, P58_MenuIdx, 0x005fea38)
#define P58_Cheats      GAME_VAR(p58_cheats_t, P58_Cheats, 0x0054cfd8)
#define P58_ItemList    GAME_VAR(int16_t *, P58_ItemList, 0x005f7e64)
#define P58_Tab4EFC03   GAME_VAR(p58_rec_t *, P58_Tab4EFC03, 0x00b31ee8)
#define P58_Cnt4EFC03   GAME_VAR(int32_t, P58_Cnt4EFC03, 0x00b31eec)
#define P58_CntC814E8   GAME_VAR(int32_t, P58_CntC814E8, 0x00c814e8)
#define P58_PtrsC816A0  GAME_VAR(void **, P58_PtrsC816A0, 0x00c816a0)
#define P58_LimC810AC   GAME_VAR(int32_t *, P58_LimC810AC, 0x00c810ac)
#define P58_S5FEA88     GAME_VAR(int32_t, P58_S5FEA88, 0x005fea88)
#define P58_S5FEA8C     GAME_VAR(int32_t, P58_S5FEA8C, 0x005fea8c)
#define P58_S5FEA7C     GAME_VAR(int32_t, P58_S5FEA7C, 0x005fea7c)
#define P58_S5FEA80     GAME_VAR(int32_t, P58_S5FEA80, 0x005fea80)
#define P58_S54E654     GAME_VAR(int32_t, P58_S54E654, 0x0054e654)
#define P58_S5FE9C0     GAME_VAR(int32_t, P58_S5FE9C0, 0x005fe9c0)
#define P58_S5FE9B4     GAME_VAR(uint32_t, P58_S5FE9B4, 0x005fe9b4)
#define P58_S5FE9B0     GAME_VAR(uint32_t, P58_S5FE9B0, 0x005fe9b0)
#define P58_S5FE9B8     GAME_VAR(uint32_t, P58_S5FE9B8, 0x005fe9b8)
#define P58_S5FE9F8     GAME_VAR(int32_t, P58_S5FE9F8, 0x005fe9f8)
#define P58_Page        GAME_VAR(int32_t, P58_Page, 0x00575ef0)
#define P58_TabPtr      GAME_VAR(uint32_t, P58_TabPtr, 0x0054e100)
#define P58_S54DFC8     GAME_VAR(uint32_t, P58_S54DFC8, 0x0054dfc8)
#define P58_S54DFD8     GAME_VAR(uint32_t, P58_S54DFD8, 0x0054dfd8)
#define P58_S54DFE8     GAME_VAR(uint32_t, P58_S54DFE8, 0x0054dfe8)
#define P58_S54DFF8     GAME_VAR(uint32_t, P58_S54DFF8, 0x0054dff8)
#define P58_S54E008     GAME_VAR(uint32_t, P58_S54E008, 0x0054e008)
#define P58_SC559D8     GAME_VAR(uint32_t, P58_SC559D8, 0x00c559d8)
#define P58_SC559E0     GAME_VAR(uint32_t, P58_SC559E0, 0x00c559e0)
#define P58_SC559E4     GAME_VAR(uint32_t, P58_SC559E4, 0x00c559e4)
#define P58_SC559E8     GAME_VAR(uint32_t, P58_SC559E8, 0x00c559e8)
#define P58_SC559EC     GAME_VAR(uint32_t, P58_SC559EC, 0x00c559ec)
#define P58_BlkIdx      GAME_VAR(p58_blkidx_t, P58_BlkIdx, 0x00c29da0)
#define P58_BlkBuf      GAME_VAR(int32_t *, P58_BlkBuf, 0x00bdfbc4)
#define P58_DemoFlag    GAME_VAR(int32_t, P58_DemoFlag, 0x00b87f0c)
#define P58_S5F7E5C     GAME_VAR(int32_t, P58_S5F7E5C, 0x005f7e5c)
#define P58_DemoNo      GAME_VAR(int32_t, P58_DemoNo, 0x005d5780)
#define P58_Demos       GAME_VAR(p58_names_t, P58_Demos, 0x0054a130)
#define P58_LangNo      GAME_VAR(int32_t, P58_LangNo, 0x00c557fc)
#define P58_Langs       GAME_VAR(p58_names_t, P58_Langs, 0x005759e4)
#define P58_Objs        GAME_VAR(p58_objs_t, P58_Objs, 0x00c80ce0)
#define P58_ObjSpare    CARTAB_VAR(uint8_t, P58_ObjSpare, 0x00d0cbd0)
#define P58_S32980      GAME_VAR(int32_t, P58_S32980, 0x00b32980)
#define P58_SB87EB0     GAME_VAR(int32_t, P58_SB87EB0, 0x00b87eb0)
#define P58_ListB31EC4  GAME_VAR(p58_slot_t *, P58_ListB31EC4, 0x00b31ec4)
#define P58_CntB31EBC   GAME_VAR(int32_t, P58_CntB31EBC, 0x00b31ebc)
#define P58_Grid        GAME_VAR(void **, P58_Grid, 0x011342e8)
#define P58_GridW       GAME_VAR(int32_t, P58_GridW, 0x0113452c)
#define P58_GridH       GAME_VAR(int32_t, P58_GridH, 0x01134530)
#define P58_Font        GAME_VAR(p58_font_t, P58_Font, 0x005d57a0)
#define P58_Cfg         GAME_VAR(p58_cfg_t, P58_Cfg, 0x01285320)
#define P58_CfgHdr      GAME_VAR(p56_hdr_t, P58_CfgHdr, 0x0057b6a0)
#define P58_CfgOn       GAME_VAR(int32_t, P58_CfgOn, 0x00b87eb8)
#define P58_CfgLock     GAME_VAR(int32_t, P58_CfgLock, 0x0057b700)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P58_MenuSel") /*gvi*/
#undef P58_MenuSel /*gvi*/
#pragma push_macro("P58_MenuFn") /*gvi*/
#undef P58_MenuFn /*gvi*/
#pragma push_macro("P58_MenuIdx") /*gvi*/
#undef P58_MenuIdx /*gvi*/
extern int32_t P58_MenuSel, P58_MenuFn, P58_MenuIdx; extern p58_cheats_t P58_Cheats; extern int16_t *P58_ItemList;
#pragma pop_macro("P58_MenuIdx") /*gvi*/
#pragma pop_macro("P58_MenuFn") /*gvi*/
#pragma pop_macro("P58_MenuSel") /*gvi*/
#pragma push_macro("P58_Cnt4EFC03") /*gvi*/
#undef P58_Cnt4EFC03 /*gvi*/
#pragma push_macro("P58_CntC814E8") /*gvi*/
#undef P58_CntC814E8 /*gvi*/
extern p58_rec_t *P58_Tab4EFC03; extern int32_t P58_Cnt4EFC03, P58_CntC814E8; extern void **P58_PtrsC816A0; extern int32_t *P58_LimC810AC;
#pragma pop_macro("P58_CntC814E8") /*gvi*/
#pragma pop_macro("P58_Cnt4EFC03") /*gvi*/
#pragma push_macro("P58_S5FEA88") /*gvi*/
#undef P58_S5FEA88 /*gvi*/
#pragma push_macro("P58_S5FEA8C") /*gvi*/
#undef P58_S5FEA8C /*gvi*/
#pragma push_macro("P58_S5FEA7C") /*gvi*/
#undef P58_S5FEA7C /*gvi*/
#pragma push_macro("P58_S5FEA80") /*gvi*/
#undef P58_S5FEA80 /*gvi*/
#pragma push_macro("P58_S54E654") /*gvi*/
#undef P58_S54E654 /*gvi*/
#pragma push_macro("P58_S5FE9C0") /*gvi*/
#undef P58_S5FE9C0 /*gvi*/
#pragma push_macro("P58_S5FE9F8") /*gvi*/
#undef P58_S5FE9F8 /*gvi*/
#pragma push_macro("P58_Page") /*gvi*/
#undef P58_Page /*gvi*/
extern int32_t P58_S5FEA88, P58_S5FEA8C, P58_S5FEA7C, P58_S5FEA80, P58_S54E654, P58_S5FE9C0, P58_S5FE9F8, P58_Page;
#pragma pop_macro("P58_Page") /*gvi*/
#pragma pop_macro("P58_S5FE9F8") /*gvi*/
#pragma pop_macro("P58_S5FE9C0") /*gvi*/
#pragma pop_macro("P58_S54E654") /*gvi*/
#pragma pop_macro("P58_S5FEA80") /*gvi*/
#pragma pop_macro("P58_S5FEA7C") /*gvi*/
#pragma pop_macro("P58_S5FEA8C") /*gvi*/
#pragma pop_macro("P58_S5FEA88") /*gvi*/
#pragma push_macro("P58_S5FE9B4") /*gvi*/
#undef P58_S5FE9B4 /*gvi*/
#pragma push_macro("P58_S5FE9B0") /*gvi*/
#undef P58_S5FE9B0 /*gvi*/
#pragma push_macro("P58_S5FE9B8") /*gvi*/
#undef P58_S5FE9B8 /*gvi*/
#pragma push_macro("P58_TabPtr") /*gvi*/
#undef P58_TabPtr /*gvi*/
#pragma push_macro("P58_S54DFC8") /*gvi*/
#undef P58_S54DFC8 /*gvi*/
#pragma push_macro("P58_S54DFD8") /*gvi*/
#undef P58_S54DFD8 /*gvi*/
#pragma push_macro("P58_S54DFE8") /*gvi*/
#undef P58_S54DFE8 /*gvi*/
#pragma push_macro("P58_S54DFF8") /*gvi*/
#undef P58_S54DFF8 /*gvi*/
#pragma push_macro("P58_S54E008") /*gvi*/
#undef P58_S54E008 /*gvi*/
extern uint32_t P58_S5FE9B4, P58_S5FE9B0, P58_S5FE9B8, P58_TabPtr, P58_S54DFC8, P58_S54DFD8, P58_S54DFE8, P58_S54DFF8, P58_S54E008,
#pragma pop_macro("P58_S54E008") /*gvi*/
#pragma pop_macro("P58_S54DFF8") /*gvi*/
#pragma pop_macro("P58_S54DFE8") /*gvi*/
#pragma pop_macro("P58_S54DFD8") /*gvi*/
#pragma pop_macro("P58_S54DFC8") /*gvi*/
#pragma pop_macro("P58_TabPtr") /*gvi*/
#pragma pop_macro("P58_S5FE9B8") /*gvi*/
#pragma pop_macro("P58_S5FE9B0") /*gvi*/
#pragma pop_macro("P58_S5FE9B4") /*gvi*/
    P58_SC559D8, P58_SC559E0, P58_SC559E4, P58_SC559E8, P58_SC559EC;
extern p58_blkidx_t P58_BlkIdx; extern int32_t *P58_BlkBuf;
#pragma push_macro("P58_DemoFlag") /*gvi*/
#undef P58_DemoFlag /*gvi*/
#pragma push_macro("P58_S5F7E5C") /*gvi*/
#undef P58_S5F7E5C /*gvi*/
#pragma push_macro("P58_DemoNo") /*gvi*/
#undef P58_DemoNo /*gvi*/
#pragma push_macro("P58_LangNo") /*gvi*/
#undef P58_LangNo /*gvi*/
#pragma push_macro("P58_S32980") /*gvi*/
#undef P58_S32980 /*gvi*/
#pragma push_macro("P58_SB87EB0") /*gvi*/
#undef P58_SB87EB0 /*gvi*/
#pragma push_macro("P58_CntB31EBC") /*gvi*/
#undef P58_CntB31EBC /*gvi*/
#pragma push_macro("P58_GridW") /*gvi*/
#undef P58_GridW /*gvi*/
#pragma push_macro("P58_GridH") /*gvi*/
#undef P58_GridH /*gvi*/
#pragma push_macro("P58_CfgOn") /*gvi*/
#undef P58_CfgOn /*gvi*/
#pragma push_macro("P58_CfgLock") /*gvi*/
#undef P58_CfgLock /*gvi*/
extern int32_t P58_DemoFlag, P58_S5F7E5C, P58_DemoNo, P58_LangNo, P58_S32980, P58_SB87EB0, P58_CntB31EBC, P58_GridW, P58_GridH, P58_CfgOn, P58_CfgLock;
#pragma pop_macro("P58_CfgLock") /*gvi*/
#pragma pop_macro("P58_CfgOn") /*gvi*/
#pragma pop_macro("P58_GridH") /*gvi*/
#pragma pop_macro("P58_GridW") /*gvi*/
#pragma pop_macro("P58_CntB31EBC") /*gvi*/
#pragma pop_macro("P58_SB87EB0") /*gvi*/
#pragma pop_macro("P58_S32980") /*gvi*/
#pragma pop_macro("P58_LangNo") /*gvi*/
#pragma pop_macro("P58_DemoNo") /*gvi*/
#pragma pop_macro("P58_S5F7E5C") /*gvi*/
#pragma pop_macro("P58_DemoFlag") /*gvi*/
#pragma push_macro("P58_Objs") /*gvi*/
#undef P58_Objs /*gvi*/
extern p58_names_t P58_Demos, P58_Langs; extern p58_objs_t P58_Objs;
#pragma pop_macro("P58_Objs") /*gvi*/
#pragma push_macro("P58_Font") /*gvi*/
#undef P58_Font /*gvi*/
#pragma push_macro("P58_Cfg") /*gvi*/
#undef P58_Cfg /*gvi*/
#pragma push_macro("P58_CfgHdr") /*gvi*/
#undef P58_CfgHdr /*gvi*/
extern p58_slot_t *P58_ListB31EC4; extern void **P58_Grid; extern p58_font_t P58_Font; extern p58_cfg_t P58_Cfg; extern p56_hdr_t P58_CfgHdr;
#pragma pop_macro("P58_CfgHdr") /*gvi*/
#pragma pop_macro("P58_Cfg") /*gvi*/
#pragma pop_macro("P58_Font") /*gvi*/
#endif
void P58_InitConsts(void);                          /* native: строки таблиц DEMOn/LANG из .data */
void    P58_MenuSwitch(void);                       /* 00417e0d: выбор экрана по P58_MenuSel (5 вариантов) */
void    P58_CheatsAll(void);                        /* 00413381: включить все коды читов */
void    P58_CheatByName(const char *name);          /* 004133b4: включить чит по коду */
void    P58_ItemsDraw(int32_t a);                   /* 00407dba: обход списка пунктов, у которых бит 8 */
void    P58_FreeRecs(void);                         /* 004efc03: освободить таблицу записей */
void    P58_FreeLists(void);                        /* 004f5dcd */
void    P58_FreeNames(p58_list_t *l);               /* 004f8d6d */
int32_t P58_Menu419F00(void);                       /* 00419f00 */
int32_t P58_Menu419AB0(void);                       /* 00419ab0 */
int32_t P58_Menu413D70(void);                       /* 00413d70 */
int32_t P58_Menu416540(void);                       /* 00416540 */
void    P58_PrepPage(void);                         /* 00415f67 */
void    P58_BuildBlockIndex(void);                  /* 0051be3c */
void    P58_PlayDemo(int32_t n);                    /* 00408600 */
void    P58_LangStrings(void);                      /* 00516da0 */
void    P58_DrawLogo(void);                         /* 004a9b1a */
void    P58_DrawObjs(void);                         /* 00506bff */
int32_t P58_ParseInt(const uint8_t *s);             /* 00524e22 */
void    P58_FreeList(void);                         /* 004eb19b */
void    P58_FreeGrid(void);                         /* 004a3354 */
void   *P58_FindChunk(int32_t v);                   /* 004f6011 */
void    P58_Backgrounds(void);                      /* 0040cf35 */
int32_t P58_SaveSlot(int32_t slot, char *dst);      /* 00405e79 */
void    P58_SaveConfig(void);                       /* 00405bfa */
float   P58_TextWidth(const uint8_t *s, int32_t font); /* 0040b1cc */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P58_MenuSel
#define P58_MenuSel (*(int32_t *)re_gvar(0x005fed9cu, sizeof(int32_t), (void *)&P58_MenuSel))
#undef P58_MenuFn
#define P58_MenuFn (*(int32_t *)re_gvar(0x005fea44u, sizeof(int32_t), (void *)&P58_MenuFn))
#undef P58_MenuIdx
#define P58_MenuIdx (*(int32_t *)re_gvar(0x005fea38u, sizeof(int32_t), (void *)&P58_MenuIdx))
#undef P58_Cnt4EFC03
#define P58_Cnt4EFC03 (*(int32_t *)re_gvar(0x00b31eecu, sizeof(int32_t), (void *)&P58_Cnt4EFC03))
#undef P58_CntC814E8
#define P58_CntC814E8 (*(int32_t *)re_gvar(0x00c814e8u, sizeof(int32_t), (void *)&P58_CntC814E8))
#undef P58_S5FEA88
#define P58_S5FEA88 (*(int32_t *)re_gvar(0x005fea88u, sizeof(int32_t), (void *)&P58_S5FEA88))
#undef P58_S5FEA8C
#define P58_S5FEA8C (*(int32_t *)re_gvar(0x005fea8cu, sizeof(int32_t), (void *)&P58_S5FEA8C))
#undef P58_S5FEA7C
#define P58_S5FEA7C (*(int32_t *)re_gvar(0x005fea7cu, sizeof(int32_t), (void *)&P58_S5FEA7C))
#undef P58_S5FEA80
#define P58_S5FEA80 (*(int32_t *)re_gvar(0x005fea80u, sizeof(int32_t), (void *)&P58_S5FEA80))
#undef P58_S54E654
#define P58_S54E654 (*(int32_t *)re_gvar(0x0054e654u, sizeof(int32_t), (void *)&P58_S54E654))
#undef P58_S5FE9C0
#define P58_S5FE9C0 (*(int32_t *)re_gvar(0x005fe9c0u, sizeof(int32_t), (void *)&P58_S5FE9C0))
#undef P58_S5FE9B4
#define P58_S5FE9B4 (*(uint32_t *)re_gvar(0x005fe9b4u, sizeof(uint32_t), (void *)&P58_S5FE9B4))
#undef P58_S5FE9B0
#define P58_S5FE9B0 (*(uint32_t *)re_gvar(0x005fe9b0u, sizeof(uint32_t), (void *)&P58_S5FE9B0))
#undef P58_S5FE9B8
#define P58_S5FE9B8 (*(uint32_t *)re_gvar(0x005fe9b8u, sizeof(uint32_t), (void *)&P58_S5FE9B8))
#undef P58_S5FE9F8
#define P58_S5FE9F8 (*(int32_t *)re_gvar(0x005fe9f8u, sizeof(int32_t), (void *)&P58_S5FE9F8))
#undef P58_Page
#define P58_Page (*(int32_t *)re_gvar(0x00575ef0u, sizeof(int32_t), (void *)&P58_Page))
#undef P58_TabPtr
#define P58_TabPtr (*(uint32_t *)re_gvar(0x0054e100u, sizeof(uint32_t), (void *)&P58_TabPtr))
#undef P58_S54DFC8
#define P58_S54DFC8 (*(uint32_t *)re_gvar(0x0054dfc8u, sizeof(uint32_t), (void *)&P58_S54DFC8))
#undef P58_S54DFD8
#define P58_S54DFD8 (*(uint32_t *)re_gvar(0x0054dfd8u, sizeof(uint32_t), (void *)&P58_S54DFD8))
#undef P58_S54DFE8
#define P58_S54DFE8 (*(uint32_t *)re_gvar(0x0054dfe8u, sizeof(uint32_t), (void *)&P58_S54DFE8))
#undef P58_S54DFF8
#define P58_S54DFF8 (*(uint32_t *)re_gvar(0x0054dff8u, sizeof(uint32_t), (void *)&P58_S54DFF8))
#undef P58_S54E008
#define P58_S54E008 (*(uint32_t *)re_gvar(0x0054e008u, sizeof(uint32_t), (void *)&P58_S54E008))
#undef P58_SC559D8
#define P58_SC559D8 (*(uint32_t *)re_gvar(0x00c559d8u, sizeof(uint32_t), (void *)&P58_SC559D8))
#undef P58_SC559E0
#define P58_SC559E0 (*(uint32_t *)re_gvar(0x00c559e0u, sizeof(uint32_t), (void *)&P58_SC559E0))
#undef P58_SC559E4
#define P58_SC559E4 (*(uint32_t *)re_gvar(0x00c559e4u, sizeof(uint32_t), (void *)&P58_SC559E4))
#undef P58_SC559E8
#define P58_SC559E8 (*(uint32_t *)re_gvar(0x00c559e8u, sizeof(uint32_t), (void *)&P58_SC559E8))
#undef P58_SC559EC
#define P58_SC559EC (*(uint32_t *)re_gvar(0x00c559ecu, sizeof(uint32_t), (void *)&P58_SC559EC))
#undef P58_DemoFlag
#define P58_DemoFlag (*(int32_t *)re_gvar(0x00b87f0cu, sizeof(int32_t), (void *)&P58_DemoFlag))
#undef P58_S5F7E5C
#define P58_S5F7E5C (*(int32_t *)re_gvar(0x005f7e5cu, sizeof(int32_t), (void *)&P58_S5F7E5C))
#undef P58_DemoNo
#define P58_DemoNo (*(int32_t *)re_gvar(0x005d5780u, sizeof(int32_t), (void *)&P58_DemoNo))
#undef P58_LangNo
#define P58_LangNo (*(int32_t *)re_gvar(0x00c557fcu, sizeof(int32_t), (void *)&P58_LangNo))
#undef P58_Objs
#define P58_Objs (*(p58_objs_t *)re_gvar(0x00c80ce0u, sizeof(p58_objs_t), (void *)&P58_Objs))
#undef P58_S32980
#define P58_S32980 (*(int32_t *)re_gvar(0x00b32980u, sizeof(int32_t), (void *)&P58_S32980))
#undef P58_SB87EB0
#define P58_SB87EB0 (*(int32_t *)re_gvar(0x00b87eb0u, sizeof(int32_t), (void *)&P58_SB87EB0))
#undef P58_CntB31EBC
#define P58_CntB31EBC (*(int32_t *)re_gvar(0x00b31ebcu, sizeof(int32_t), (void *)&P58_CntB31EBC))
#undef P58_GridW
#define P58_GridW (*(int32_t *)re_gvar(0x0113452cu, sizeof(int32_t), (void *)&P58_GridW))
#undef P58_GridH
#define P58_GridH (*(int32_t *)re_gvar(0x01134530u, sizeof(int32_t), (void *)&P58_GridH))
#undef P58_Font
#define P58_Font (*(p58_font_t *)re_gvar(0x005d57a0u, sizeof(p58_font_t), (void *)&P58_Font))
#undef P58_Cfg
#define P58_Cfg (*(p58_cfg_t *)re_gvar(0x01285320u, sizeof(p58_cfg_t), (void *)&P58_Cfg))
#undef P58_CfgHdr
#define P58_CfgHdr (*(p56_hdr_t *)re_gvar(0x0057b6a0u, sizeof(p56_hdr_t), (void *)&P58_CfgHdr))
#undef P58_CfgOn
#define P58_CfgOn (*(int32_t *)re_gvar(0x00b87eb8u, sizeof(int32_t), (void *)&P58_CfgOn))
#undef P58_CfgLock
#define P58_CfgLock (*(int32_t *)re_gvar(0x0057b700u, sizeof(int32_t), (void *)&P58_CfgLock))
#endif
/* gvar-img v2.03 end */
