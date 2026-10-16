#pragma once
#include <stdint.h>
#include "gvar.h"
#include "ported42.h"
/* v1.67: ported122 — новые переменные (вне native-таблиц) */
typedef uint8_t p122_rec44_t[0x44];
#define P122_SpotRec  GAME_VAR(p122_rec44_t, P122_SpotRec, 0x010fc9a0)   /* запись модели 0x44 — пятно под точкой (004accf0) */
#define P122_GlowRec  GAME_VAR(p122_rec44_t, P122_GlowRec, 0x01123280)   /* запись модели 0x44 — пятно фар машины (004ac779), +0x38..0x40 — цвет */
#define P122_EvCur    GAME_VAR(uint8_t *, P122_EvCur, 0x00b1ff5c)        /* текущая запись события (0x24 байта, куча) */
#define P122_Ev118    GAME_VAR(int32_t, P122_Ev118, 0x01134118)
#define P122_Ev240    GAME_VAR(int32_t, P122_Ev240, 0x01134240)
#define P122_Blink    GAME_VAR(int32_t, P122_Blink, 0x0054e9d8)        /* .data, начальное 10: такт мигания курсора ввода имени */
#define P122_BlinkOn  GAME_VAR(int32_t, P122_BlinkOn, 0x005feefc)
#define P122_Ev24C    GAME_VAR(int32_t, P122_Ev24C, 0x0113424c)
#ifndef RE_HOOK_BUILD
extern p122_rec44_t P122_SpotRec, P122_GlowRec;
extern uint8_t *P122_EvCur;
extern int32_t P122_Blink, P122_BlinkOn, P122_Ev118, P122_Ev240, P122_Ev24C;
#endif
void     P122_SpotShadow(uint32_t pos, int32_t size);   /* 004accf0: пятно-квадрат 2·size под точкой pos (float x,_,z), на дороге */
void     P122_CarGlow(int32_t car);                     /* 004ac779: пятно света фар перед машиной car, гаснет с высотой камеры */
void     P122_ObjATick(void);                           /* 004ba31b: такт 200 объектов P95_ObjA по флагам, время жизни */
void     P122_MapNames(const uint8_t *hdr, const char *names, uint8_t page);  /* 0040d56c: имена значков страницы в таблицу P54_MapAPtr */
char    *P122_EventsParse(char *p);                     /* 004a44d4: блок событий до EVENT_END в список 00d12408 */
int32_t  P122_FontIcons(uint32_t prefix, int32_t font, int32_t a3, int32_t a4, int32_t a5);  /* 0040a8b0: глифы шрифта из значков «%s%d» */
void     P122_IconCopy(int32_t dst, const char *name);  /* 004e7450: копия пикселей значка name в значок dst (та же страница-размер) */
int32_t  P122_SetVar(p42_cmd_t *cmd, p42_var_t *var);   /* 004f8485: команда установки переменной скрипта (по P65_Tok) */
int32_t  P122_ObjNames(void);                           /* 004a05fa: индексы моделей объектов по 18 группам 01136940 (+ сортировка) */
int32_t  P122_NameMenu(void);                          /* 0041ab60: меню ввода имён (таблицы .data 0054e948/0054e828), курсор «.» мигает */
