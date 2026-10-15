/* v1.43 — восстановлено из Game.exe по стандарту указателей v1.42 (game/reptr.h).
   DebugMalloc/DebugFree 004d8db4/004d8f30 (таблица выделений 00b203a0: ключ — адрес блока uint32),
   освобождение списка скрипта 004d0102, титры 004a9850/004a9cd0 (.data 005527a0, имена лиц 00552e1c → строки 005532cc),
   значки 004b4095, шесть спрайтов 004ba720, четырёхугольники 0041e52c/0041e729, сброс миссии 004e49c0, вращение трафика 004911d9,
   SPLASH/RFLECT 004cb857, очистка данных машин 004c2042, камера по сплайну 0049ec01, язык 0051763a (таблицы строк 00c55820/00c55280 —
   uint32-адреса), цвет фонарей 004cb4ff, запись камеры 00519a45, маркер 004ea346, камеры режиссёра 004c32c1/004c6740,
   частицы 00514a47/0051564f, модели скрипта 004fc3f4, свободная камера 004d7766, позиция голоса 005240d0, пункты меню 0040cd6f,
   RIFF 0048c5b7, таблица пикселей 00421a80, дальность объектов скрипта 004f5012. Все cdecl. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "p98_data.h"
#include <stdint.h>

#ifdef RE_HOOK_BUILD
#  define P98_STD __attribute__((stdcall))
#else
#  define P98_STD
#endif
typedef void (P98_STD *p98_gr1_fn)(int32_t);

typedef struct { uint8_t kind, sub; uint8_t pad[2]; int32_t y; uint32_t txt; } p98_credit_t;   /* 0xc байт */
_Static_assert(sizeof(p98_credit_t) == 0xc, "p98_credit_t");
typedef p98_credit_t p98_credits_t[P98_CREDITS_N];
typedef int32_t  p98_credh_t[8];
typedef struct { uint16_t id, page; uint32_t icon; } p98_face_t;                                  /* 8 байт: icon — адрес записи значка */
_Static_assert(sizeof(p98_face_t) == 8, "p98_face_t");
typedef p98_face_t p98_faces_t[3];
typedef uint32_t p98_facenames_t[P98_FACES_N];
typedef uint8_t  p98_faceblk_t[P98_FACEBLK_N];
typedef uint32_t p98_strtab2_t[0x15e];
typedef int32_t  p98_iconidx_t[0x3aaa];
typedef uint8_t  p98_six_t[6 * 0x30];
typedef float    p98_f3_t[3];
typedef float    p98_f5_t[5];
typedef float    p98_f9_t[9];
typedef float    p98_f16_t[16];
typedef int32_t  p98_i10_t[10];
typedef uint8_t  p98_b148_t[0x148];
typedef uint8_t  p98_b54_t[0x54];
typedef uint8_t  p98_camrecs_t[0x210 * 0x28];
typedef uint8_t  p98_b410_t[0x410];
typedef uint8_t  p98_b110_t[0x110];
typedef uint8_t  p98_b45100_t[0x45100];
typedef uint8_t  p98_b61c00_t[0x61c00];
typedef uint8_t  p98_b27b600_t[0x27b600];
typedef uint8_t  p98_b708_t[0x708];
typedef uint8_t  p98_b44_t[0x44];
typedef uint8_t  p98_bf8_t[0xf8];
typedef uint16_t p98_pix_t[0x10000];

#define P98_Credits   GAME_VAR(p98_credits_t, P98_Credits, 0x005527a0)     /* титры: вид, подвид, y (пишется), текст */
#define P98_CredH     GAME_VAR(p98_credh_t, P98_CredH, 0x00552de8)         /* высота строки по виду */
#define P98_FaceNames GAME_VAR(p98_facenames_t, P98_FaceNames, 0x00552e1c) /* адреса имён лиц ("MARTIN"...) */
#define P98_FaceBlk   GAME_VAR(p98_faceblk_t, P98_FaceBlk, 0x005532cc)     /* сами строки имён (в native — копия .data, область реестра) */
#define P98_Faces     GAME_VAR(p98_faces_t, P98_Faces, 0x00b1ffa0)
#define P98_FaceCur   GAME_VAR(int32_t, P98_FaceCur, 0x00b1ffb8)
#define P98_MisStr    GAME_VAR(p98_strtab2_t, P98_MisStr, 0x00c55280)      /* адреса строк миссии */
#define P98_GrD40     GAME_VAR(p98_gr1_fn, P98_GrD40, 0x01270d40)
#define P98_IconN     GAME_VAR(int32_t, P98_IconN, 0x0110e4e8)
#define P98_IconIdx   GAME_VAR(p98_iconidx_t, P98_IconIdx, 0x010ffa40)
#define P98_IconCol   GAME_VAR(p98_f3_t, P98_IconCol, 0x010fc9d8)
#define P98_SixRec    GAME_VAR(uint8_t *, P98_SixRec, 0x01123260)
#define P98_Six       GAME_VAR(p98_six_t, P98_Six, 0x010ff900)
#define P98_DD70      GAME_VAR(uint8_t, P98_DD70, 0x00d0dd70)
#define P98_DDE4      GAME_VAR(int16_t, P98_DDE4, 0x00d0dde4)
#define P98_TrafX     GAME_VAR(p98_b54_t, P98_TrafX, 0x011458e0)            /* 0x41-я запись трафика (за массивом 0x40) */
#define P98_CamW      GAME_VAR(uint32_t, P98_CamW, 0x00b1c27c)
#define P98_ScaleB    GAME_VAR(float, P98_ScaleB, 0x01137300)
#define P98_CamQuat   GAME_VAR(p98_f5_t, P98_CamQuat, 0x01137340)
#define P98_CamRecs   GAME_VAR(p98_camrecs_t, P98_CamRecs, 0x00c4daa0)
#define P98_TgtW      GAME_VAR(uint32_t, P98_TgtW, 0x01136c7c)
#define P98_FreeTurn  GAME_VAR(int32_t, P98_FreeTurn, 0x01137364)
#define P98_KeyL      GAME_VAR(uint8_t, P98_KeyL, 0x00d04d0b)
#define P98_KeyR      GAME_VAR(uint8_t, P98_KeyR, 0x00d04d0c)
#define P98_KeyB      GAME_VAR(uint8_t, P98_KeyB, 0x00d04d0d)
#define P98_KeyMode   GAME_VAR(uint8_t, P98_KeyMode, 0x00d04d10)
#define P98_KeyTgt    GAME_VAR(uint8_t, P98_KeyTgt, 0x00d04d11)
#define P98_MrkOff    GAME_VAR(int32_t, P98_MrkOff, 0x00d02630)
#define P98_MrkModel  GAME_VAR(int32_t, P98_MrkModel, 0x00d02638)
#define P98_MrkPos    GAME_VAR(p98_f3_t, P98_MrkPos, 0x00d02670)
#define P98_MrkW      GAME_VAR(uint32_t, P98_MrkW, 0x00d0267c)
#define P98_MrkSrc    GAME_VAR(p98_f3_t, P98_MrkSrc, 0x00d02720)
#define P98_MrkMat    GAME_VAR(p98_f9_t, P98_MrkMat, 0x01135060)
#define P98_C824A0    GAME_VAR(int32_t, P98_C824A0, 0x00c824a0)
#define P98_D078C8    CARTAB_VAR(int32_t, P98_D078C8, 0x00d078c8)            /* поле +0x108 записи игрока (как P97_D078CC) */
#define P98_ScrFirst  GAME_VAR(int32_t, P98_ScrFirst, 0x00c80cc0)
#define P98_ScrModel  GAME_VAR(int32_t, P98_ScrModel, 0x00c81114)
#define P98_Range     GAME_VAR(p98_i10_t, P98_Range, 0x00b87e60)
#define P98_PartDist  GAME_VAR(int32_t, P98_PartDist, 0x00c56704)
#define P98_PartPl    GAME_VAR(p98_f16_t, P98_PartPl, 0x00c56720)
#define P98_PixTab    GAME_VAR(p98_pix_t, P98_PixTab, 0x00601bc0)
#define P98_CarBufA   GAME_VAR(p98_b410_t, P98_CarBufA, 0x00dbb040)
#define P98_CarTimer  GAME_VAR(p98_b110_t, P98_CarTimer, 0x00dbb460)       /* int32 по машине (+1), 0x32 после копии */
#define P98_CarOpsA   GAME_VAR(p98_b45100_t, P98_CarOpsA, 0x00dbb580)
#define P98_CarOpsB   GAME_VAR(p98_b61c00_t, P98_CarOpsB, 0x0107c3e0)
#define P98_CarOpsC   GAME_VAR(p98_b27b600_t, P98_CarOpsC, 0x00e006c0)
#define P98_CarBufB   GAME_VAR(p98_b708_t, P98_CarBufB, 0x0107bcc0)
#define P98_CarKind   GAME_VAR(p98_b44_t, P98_CarKind, 0x010de0c0)
#define P98_CarBufC   GAME_VAR(p98_bf8_t, P98_CarBufC, 0x010de220)
/* сброс миссии 004e49c0 */
#define P98_M4658 GAME_VAR(uint8_t, P98_M4658, 0x00d04658)
#define P98_M38F7 GAME_VAR(uint8_t, P98_M38F7, 0x00d038f7)
#define P98_M4A60 GAME_VAR(int32_t, P98_M4A60, 0x00d04a60)
#define P98_M478C GAME_VAR(int32_t, P98_M478C, 0x00d0478c)
#define P98_M4A4C GAME_VAR(int32_t, P98_M4A4C, 0x00d04a4c)
#define P98_M447C GAME_VAR(int32_t, P98_M447C, 0x00d0447c)
#define P98_M465C GAME_VAR(int32_t, P98_M465C, 0x00d0465c)
#define P98_M44C4 GAME_VAR(int32_t, P98_M44C4, 0x00d044c4)
#define P98_M446C GAME_VAR(int32_t, P98_M446C, 0x00d0446c)
#define P98_M4660 GAME_VAR(int32_t, P98_M4660, 0x00d04660)
#define P98_M48E8 GAME_VAR(int32_t, P98_M48E8, 0x00d048e8)
#define P98_M4780 GAME_VAR(int32_t, P98_M4780, 0x00d04780)
#define P98_M3580 GAME_VAR(int32_t, P98_M3580, 0x00d03580)
#define P98_M4664 GAME_VAR(int32_t, P98_M4664, 0x00d04664)
#define P98_M4474 GAME_VAR(int32_t, P98_M4474, 0x00d04474)
#define P98_M4A5C GAME_VAR(int32_t, P98_M4A5C, 0x00d04a5c)
#define P98_M4A48 GAME_VAR(int32_t, P98_M4A48, 0x00d04a48)
#define P98_M390C GAME_VAR(int32_t, P98_M390C, 0x00d0390c)
#define P98_M4464 GAME_VAR(int32_t, P98_M4464, 0x00d04464)
#define P98_M453C GAME_VAR(int32_t, P98_M453C, 0x00d0453c)
#define P98_M44D8 GAME_VAR(int32_t, P98_M44D8, 0x00d044d8)
#define P98_M48EC GAME_VAR(int32_t, P98_M48EC, 0x00d048ec)
#define P98_M4460 GAME_VAR(int32_t, P98_M4460, 0x00d04460)
#define P98_M4480 GAME_VAR(int32_t, P98_M4480, 0x00d04480)
#define P98_M38F8 GAME_VAR(int32_t, P98_M38F8, 0x00d038f8)
#define P98_M4468 GAME_VAR(int32_t, P98_M4468, 0x00d04468)
#define P98_M48F4 GAME_VAR(int32_t, P98_M48F4, 0x00d048f4)
#define P98_M4648 GAME_VAR(int32_t, P98_M4648, 0x00d04648)
#define P98_M4644 GAME_VAR(int32_t, P98_M4644, 0x00d04644)
#define P98_M4640 GAME_VAR(int32_t, P98_M4640, 0x00d04640)
#define P98_M47A0 GAME_VAR(p98_b148_t, P98_M47A0, 0x00d047a0)
#define P98_M4900 GAME_VAR(p98_b148_t, P98_M4900, 0x00d04900)

#ifndef RE_HOOK_BUILD
extern p98_credits_t P98_Credits; extern const p98_credh_t P98_CredH; extern const p98_facenames_t P98_FaceNames;
extern p98_faceblk_t P98_FaceBlk; extern p98_faces_t P98_Faces; extern int32_t P98_FaceCur; extern p98_strtab2_t P98_MisStr;
extern p98_gr1_fn P98_GrD40; extern int32_t P98_IconN; extern p98_iconidx_t P98_IconIdx; extern p98_f3_t P98_IconCol;
extern uint8_t *P98_SixRec; extern p98_six_t P98_Six; extern uint8_t P98_DD70; extern int16_t P98_DDE4; extern p98_b54_t P98_TrafX;
extern uint32_t P98_CamW; extern float P98_ScaleB; extern p98_f5_t P98_CamQuat; extern p98_camrecs_t P98_CamRecs; extern uint32_t P98_TgtW;
extern int32_t P98_FreeTurn; extern uint8_t P98_KeyL, P98_KeyR, P98_KeyB, P98_KeyMode, P98_KeyTgt;
extern int32_t P98_MrkOff, P98_MrkModel; extern p98_f3_t P98_MrkPos, P98_MrkSrc; extern uint32_t P98_MrkW; extern p98_f9_t P98_MrkMat;
extern int32_t P98_C824A0, P98_ScrFirst, P98_ScrModel; extern p98_i10_t P98_Range; extern int32_t P98_PartDist;
extern p98_f16_t P98_PartPl; extern p98_pix_t P98_PixTab;
extern p98_b410_t P98_CarBufA; extern p98_b110_t P98_CarTimer; extern p98_b45100_t P98_CarOpsA; extern p98_b61c00_t P98_CarOpsB;
extern p98_b27b600_t P98_CarOpsC; extern p98_b708_t P98_CarBufB; extern p98_b44_t P98_CarKind; extern p98_bf8_t P98_CarBufC;
extern uint8_t P98_M4658, P98_M38F7;
extern int32_t P98_M4A60, P98_M478C, P98_M4A4C, P98_M447C, P98_M465C, P98_M44C4, P98_M446C, P98_M4660, P98_M48E8, P98_M4780, P98_M3580,
  P98_M4664, P98_M4474, P98_M4A5C, P98_M4A48, P98_M390C, P98_M4464, P98_M453C, P98_M44D8, P98_M48EC, P98_M4460, P98_M4480, P98_M38F8,
  P98_M4468, P98_M48F4, P98_M4648, P98_M4644, P98_M4640;
extern p98_b148_t P98_M47A0, P98_M4900;
#endif

void    P98_DebugFree(void *p);                                      /* 004d8f30 */
void   *P98_DebugMalloc(int32_t size, const char *file, int32_t line); /* 004d8db4 */
void    P98_ScriptFreeAll(void);                                     /* 004d0102 */
void    P98_CreditsInit(void);                                       /* 004a9850 */
int32_t P98_CreditsFace(uint8_t *rec);                               /* 004a9cd0 */
void    P98_IconFlush(void);                                         /* 004b4095 */
void    P98_DrawSix(void);                                           /* 004ba720 */
void    P98_QuadA(int32_t unused, const uint8_t *v);                 /* 0041e52c */
void    P98_QuadB(int32_t unused, const uint8_t *v);                 /* 0041e729 */
void    P98_ResetMission(void);                                      /* 004e49c0 */
void    P98_TrafficSpin(void);                                       /* 004911d9 */
void    P98_InitSplash(uint8_t *tab);                                /* 004cb857 */
void    P98_ClearCarData(void);                                      /* 004c2042 */
void    P98_CamSpline(int32_t t, const uint8_t *keys);               /* 0049ec01 */
void    P98_LoadLang(const char *name, int32_t mission);             /* 0051763a */
void    P98_LampColor(uint8_t r, uint8_t g, uint8_t b);              /* 004cb4ff */
void    P98_CamRecAdd(int8_t insert_at_end);                         /* 00519a45 */
void    P98_DrawMarker(void);                                        /* 004ea346 */
int32_t P98_CamClamp(int32_t *cam);                                  /* 004c32c1 */
int32_t P98_DirCamNext(void **out);                                  /* 004c6740 */
void    P98_PartAim(int16_t *p);                                     /* 00514a47 */
void    P98_DrawScriptModels(const uint8_t *recs);                   /* 004fc3f4 */
void    P98_FreeCamKeys(void);                                       /* 004d7766 */
void    P98_VoicePos(int32_t voice, const int32_t *pos, int32_t a, int32_t vol); /* 005240d0 */
void    P98_ItemsDraw(void);                                         /* 0040cd6f */
int32_t P98_RiffFind(const void *riff, const void **fmt, const void **data, uint32_t *size); /* 0048c5b7 */
void    P98_PixTabInit(void);                                        /* 00421a80 */
void    P98_ScriptRange(void);                                       /* 004f5012 */
void    P98_PartCheck(int16_t *p);                                   /* 0051564f */
void    P98_DirCamKeys(uint32_t keys);                               /* 004c2b9a */
