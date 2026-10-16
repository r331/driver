#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "ported5.h"
#include "ported35.h"
#include "ported10.h"
#include <stdint.h>
/* Шаг D: 9 функций — разбор строки скрипта миссий, поиск по таблице имён, имя в меню и блиттеры спрайтов 8 бит. Все cdecl.
   Строка скрипта (DAT_00c81684 — указатель) режется на токены; блиттеры 00529140/00529190 читают текстурную страницу 256x256
   (адрес выровнен на 64 КБ; младшие 16 бит адреса заменяются на u|v<<8, u бежит по кругу в пределах байта) в экран 640x480 (0x57b740). */
typedef char p65_tok_t[0x118];
typedef int32_t p65_ints_t[64];
typedef const char *p65_strtab_t[128];                       /* 0x00c55820: указатели на строки (0x40 — 0x00c55920, 0x41 — 0x00c55924, 0xc — 0x00c55850) */
typedef uint8_t p65_screen_t[640 * 480];
typedef struct { void *p; uint8_t pad[16 - sizeof(void *)]; } p65_tex_t;   /* 16 байт в Game.exe: поле +0 — указатель на страницу */
typedef p65_tex_t p65_texs_t[64];   /* v2.02: 64 (было 16): FRONTEND.TSD — 28 страниц; в Game.exe до 01146f20 свободно 0x14bc байт */
typedef uint8_t p65_blend_t[0x10000];                        /* 0x012752a0: [dst<<8 | src] → цвет */
typedef char p65_name_t[20];
#define P65_Line   GAME_VAR(char *, P65_Line, 0x00c81684)
#define P65_Tok    GAME_VAR(p65_tok_t, P65_Tok, 0x00c81580)
#define P65_Ints   GAME_VAR(p65_ints_t, P65_Ints, 0x00c80c00)
#include "strtab.h"
#include "reptr.h"
#define P65_STR(i) ((const char *)re_ptr(P97_StrAddr[(i)]))   /* бывший P65_Str[i]: единая таблица адресов 00c55820 */
#define P65_Name   GAME_VAR(p65_name_t, P65_Name, 0x0057b718)
#define P65_NamePtr GAME_VAR(const char *, P65_NamePtr, 0x00549fa0)
#define P65_NameBg  GAME_VAR(const char *, P65_NameBg, 0x00549ff0)
#define P65_Screen GAME_VAR(p65_screen_t, P65_Screen, 0x0057b740)
#define P65_Texs   GAME_VAR(p65_texs_t, P65_Texs, 0x01145a64)
#define P65_Blend  GAME_VAR(p65_blend_t, P65_Blend, 0x012752a0)
#define P65_ColorKey GAME_VAR(uint8_t, P65_ColorKey, 0x005c6768)
#define P65_NameVal Q0057B72C
#ifndef RE_HOOK_BUILD
extern char *P65_Line;
#pragma push_macro("P65_Tok") /*gvi*/
#undef P65_Tok /*gvi*/
extern p65_tok_t P65_Tok;
#pragma pop_macro("P65_Tok") /*gvi*/
#pragma push_macro("P65_Ints") /*gvi*/
#undef P65_Ints /*gvi*/
extern p65_ints_t P65_Ints;
#pragma pop_macro("P65_Ints") /*gvi*/

#pragma push_macro("P65_Name") /*gvi*/
#undef P65_Name /*gvi*/
extern p65_name_t P65_Name;
#pragma pop_macro("P65_Name") /*gvi*/
extern const char *P65_NamePtr;
extern const char *P65_NameBg;
#pragma push_macro("P65_Screen") /*gvi*/
#undef P65_Screen /*gvi*/
extern p65_screen_t P65_Screen;
#pragma pop_macro("P65_Screen") /*gvi*/
extern p65_texs_t P65_Texs;
#pragma push_macro("P65_Blend") /*gvi*/
#undef P65_Blend /*gvi*/
extern p65_blend_t P65_Blend;
#pragma pop_macro("P65_Blend") /*gvi*/
#pragma push_macro("P65_ColorKey") /*gvi*/
#undef P65_ColorKey /*gvi*/
extern uint8_t P65_ColorKey;
#pragma pop_macro("P65_ColorKey") /*gvi*/
#endif
typedef struct p65_ent { const char *name; int32_t value; } p65_ent_t;      /* запись таблицы: имя и значение */
typedef struct { int32_t count; p65_ent_t **ents; } p65_tab_t;               /* число записей и массив указателей на них */
int32_t P65_NextToken(char *line, char *tok);       /* 004f6774: токен до пробела/табуляции/\n/,/; в tok, остаток строки сдвигается; 10 — токена нет */
int32_t P65_ReadInts(void *cmd);                    /* 004f87e0: cmd+0x100 чисел из строки в массив 0xc80c00; 0xc — ошибка разбора */
int32_t P65_FindByName(char *name, p65_tab_t *tab); /* 004f8cfd: имя приводится к верхнему регистру; значение записи или -1 */
void    P65_SetNameFields(void);                    /* 004072be: подпись пункта меню (имя и номер) */
void    P65_BlitKeyed(const void *page, uint8_t *dst, int32_t w, int32_t h, int32_t u, int32_t v);   /* 00529140: прозрачный цвет — 005c6768 */
void    P65_BlitBlend(const void *page, uint8_t *dst, int32_t w, int32_t h, int32_t u, int32_t v);   /* 00529190: через таблицу смешивания */
void    P65_SpriteKeyed(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h);  /* 00407cb8 */
void    P65_SpriteBlend(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h);  /* 00407d07 */
int32_t P65_ScriptCall(void);                       /* 004d1529: пропуск 2 байт, слово → 004cfe69, результат 1 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P65_Tok
#define P65_Tok (*(p65_tok_t *)re_gvar(0x00c81580u, sizeof(p65_tok_t), (void *)&P65_Tok))
#undef P65_Ints
#define P65_Ints (*(p65_ints_t *)re_gvar(0x00c80c00u, sizeof(p65_ints_t), (void *)&P65_Ints))
#undef P65_Name
#define P65_Name (*(p65_name_t *)re_gvar(0x0057b718u, sizeof(p65_name_t), (void *)&P65_Name))
#undef P65_Screen
#define P65_Screen (*(p65_screen_t *)re_gvar(0x0057b740u, sizeof(p65_screen_t), (void *)&P65_Screen))
#undef P65_Blend
#define P65_Blend (*(p65_blend_t *)re_gvar(0x012752a0u, sizeof(p65_blend_t), (void *)&P65_Blend))
#undef P65_ColorKey
#define P65_ColorKey (*(uint8_t *)re_gvar(0x005c6768u, sizeof(uint8_t), (void *)&P65_ColorKey))
#endif
/* gvar-img v2.03 end */
