#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "engine.h"
#include "ported4.h"
#include "ported11.h"
#include "ported14.h"
#include "ported19.h"
#include "ported20.h"
#include "ported21.h"
#include "ported26.h"
#include "ported42.h"
#include "ported43.h"
#include "ported54.h"
#include "ported6.h"
#include "ported62.h"
#include "ported63.h"
#include "ported72.h"
#include "ported76.h"
#include "uihandlers4.h"
#include "ported27.h"
#include "ported79.h"
#include <stdint.h>
/* Шаг D, ported80 (веха 1: город из LEV), все cdecl:
   - 00426ce3 — ограничивающий параллелепипед модели по номеру (по вершинам всех записей) → 8 слов:
     {minX, minY, minZ, maxX, maxY, maxZ, maxY−minY, round(maxY−minY)}; последнее число дублируется в 00ba52d0;
   - 004eb490 — блок 1 файла уровня: число моделей, затем [размер][данные] каждой; модель с диска переводится в формат памяти
     (00475a3d) в арене карты; ссылки раскрываются (сначала корневые модели, parent == −1, потом дочерние); для каждой модели
     считаются параллелепипед (таблица 00cf56e0, 0x20 байт на модель) и класс (байтовая таблица 00c98a40). */
typedef float   p80_box_t[8];
typedef p80_box_t p80_boxtab_t[1126];
typedef uint8_t p80_class_t[1126];
#define P80_Boxes GAME_VAR(p80_boxtab_t, P80_Boxes, 0x00cf56e0)
#define P80_Class GAME_VAR(p80_class_t, P80_Class, 0x00c98a40)
typedef void   *p80_lumps_t[1024];
#define P80_LumpTab  GAME_VAR(p80_lumps_t, P80_LumpTab, 0x00d012e0)       /* указатели на списки блока 2 по номеру (в hook 32-бит, в native 64) */
#define P80_GridH    GAME_VAR(int32_t, P80_GridH, 0x00562d3c)
#define P80_Cell     GAME_VAR(int32_t, P80_Cell, 0x00562d40)
#define P80_Hdr5     GAME_VAR(int32_t, P80_Hdr5, 0x00d01274)
#define P80_Hdr6     GAME_VAR(int32_t, P80_Hdr6, 0x00c97a28)
#define P80_HalfW    GAME_VAR(int32_t, P80_HalfW, 0x00cb8f08)
#define P80_HalfH    GAME_VAR(int32_t, P80_HalfH, 0x00cf2f9c)
#define P80_InvMap   GAME_VAR(float, P80_InvMap, 0x00c1cc60)
#define P80_Cols     GAME_VAR(int32_t, P80_Cols, 0x00d00250)
#define P80_Save0    GAME_VAR(float, P80_Save0, 0x00d001f0)
#define P80_Save1    GAME_VAR(float, P80_Save1, 0x00d001f4)
#define P80_Save2    GAME_VAR(float, P80_Save2, 0x00d001f8)
#define P80_Save3    GAME_VAR(float, P80_Save3, 0x00d001fc)
#define P80_Dir3     GAME_VAR(float, P80_Dir3, 0x005507dc)
#define P80_SaveW    GAME_VAR(float, P80_SaveW, 0x00cb8f00)
#define P80_Alt0     GAME_VAR(float, P80_Alt0, 0x00d00240)
#define P80_Alt1     GAME_VAR(float, P80_Alt1, 0x00d00244)
#define P80_Alt2     GAME_VAR(float, P80_Alt2, 0x00d00248)
#define P80_Alt3     GAME_VAR(float, P80_Alt3, 0x00d0024c)
#define P80_AltW     GAME_VAR(float, P80_AltW, 0x00d01264)
#define P80_Flag17AEC GAME_VAR(int32_t, P80_Flag17AEC, 0x00d17aec)
#define P80_One      GAME_VAR(float, P80_One, 0x00546020)
#define P80_C45      GAME_VAR(float, P80_C45, 0x005461f4)
#define P80_C02      GAME_VAR(float, P80_C02, 0x00546080)
#define P80_C045     GAME_VAR(float, P80_C045, 0x005469ec)
#define P80_Half     GAME_VAR(float, P80_Half, 0x00546068)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P80_Boxes") /*gvi*/
#undef P80_Boxes /*gvi*/
extern p80_boxtab_t P80_Boxes;
#pragma pop_macro("P80_Boxes") /*gvi*/
#pragma push_macro("P80_Class") /*gvi*/
#undef P80_Class /*gvi*/
extern p80_class_t P80_Class;
#pragma pop_macro("P80_Class") /*gvi*/
extern p80_lumps_t P80_LumpTab;
#pragma push_macro("P80_GridH") /*gvi*/
#undef P80_GridH /*gvi*/
#pragma push_macro("P80_Cell") /*gvi*/
#undef P80_Cell /*gvi*/
#pragma push_macro("P80_Hdr5") /*gvi*/
#undef P80_Hdr5 /*gvi*/
#pragma push_macro("P80_Hdr6") /*gvi*/
#undef P80_Hdr6 /*gvi*/
#pragma push_macro("P80_HalfW") /*gvi*/
#undef P80_HalfW /*gvi*/
#pragma push_macro("P80_HalfH") /*gvi*/
#undef P80_HalfH /*gvi*/
#pragma push_macro("P80_Cols") /*gvi*/
#undef P80_Cols /*gvi*/
#pragma push_macro("P80_Flag17AEC") /*gvi*/
#undef P80_Flag17AEC /*gvi*/
extern int32_t P80_GridH, P80_Cell, P80_Hdr5, P80_Hdr6, P80_HalfW, P80_HalfH, P80_Cols, P80_Flag17AEC;
#pragma pop_macro("P80_Flag17AEC") /*gvi*/
#pragma pop_macro("P80_Cols") /*gvi*/
#pragma pop_macro("P80_HalfH") /*gvi*/
#pragma pop_macro("P80_HalfW") /*gvi*/
#pragma pop_macro("P80_Hdr6") /*gvi*/
#pragma pop_macro("P80_Hdr5") /*gvi*/
#pragma pop_macro("P80_Cell") /*gvi*/
#pragma pop_macro("P80_GridH") /*gvi*/
#pragma push_macro("P80_InvMap") /*gvi*/
#undef P80_InvMap /*gvi*/
#pragma push_macro("P80_Save0") /*gvi*/
#undef P80_Save0 /*gvi*/
#pragma push_macro("P80_Save1") /*gvi*/
#undef P80_Save1 /*gvi*/
#pragma push_macro("P80_Save2") /*gvi*/
#undef P80_Save2 /*gvi*/
#pragma push_macro("P80_Save3") /*gvi*/
#undef P80_Save3 /*gvi*/
#pragma push_macro("P80_Dir3") /*gvi*/
#undef P80_Dir3 /*gvi*/
#pragma push_macro("P80_SaveW") /*gvi*/
#undef P80_SaveW /*gvi*/
#pragma push_macro("P80_Alt0") /*gvi*/
#undef P80_Alt0 /*gvi*/
#pragma push_macro("P80_Alt1") /*gvi*/
#undef P80_Alt1 /*gvi*/
#pragma push_macro("P80_Alt2") /*gvi*/
#undef P80_Alt2 /*gvi*/
#pragma push_macro("P80_Alt3") /*gvi*/
#undef P80_Alt3 /*gvi*/
#pragma push_macro("P80_AltW") /*gvi*/
#undef P80_AltW /*gvi*/
extern float P80_InvMap, P80_Save0, P80_Save1, P80_Save2, P80_Save3, P80_Dir3, P80_SaveW, P80_Alt0, P80_Alt1, P80_Alt2, P80_Alt3, P80_AltW;
#pragma pop_macro("P80_AltW") /*gvi*/
#pragma pop_macro("P80_Alt3") /*gvi*/
#pragma pop_macro("P80_Alt2") /*gvi*/
#pragma pop_macro("P80_Alt1") /*gvi*/
#pragma pop_macro("P80_Alt0") /*gvi*/
#pragma pop_macro("P80_SaveW") /*gvi*/
#pragma pop_macro("P80_Dir3") /*gvi*/
#pragma pop_macro("P80_Save3") /*gvi*/
#pragma pop_macro("P80_Save2") /*gvi*/
#pragma pop_macro("P80_Save1") /*gvi*/
#pragma pop_macro("P80_Save0") /*gvi*/
#pragma pop_macro("P80_InvMap") /*gvi*/
#pragma push_macro("P80_One") /*gvi*/
#undef P80_One /*gvi*/
#pragma push_macro("P80_C45") /*gvi*/
#undef P80_C45 /*gvi*/
#pragma push_macro("P80_C02") /*gvi*/
#undef P80_C02 /*gvi*/
#pragma push_macro("P80_C045") /*gvi*/
#undef P80_C045 /*gvi*/
#pragma push_macro("P80_Half") /*gvi*/
#undef P80_Half /*gvi*/
extern float P80_One, P80_C45, P80_C02, P80_C045, P80_Half;
#pragma pop_macro("P80_Half") /*gvi*/
#pragma pop_macro("P80_C045") /*gvi*/
#pragma pop_macro("P80_C02") /*gvi*/
#pragma pop_macro("P80_C45") /*gvi*/
#pragma pop_macro("P80_One") /*gvi*/
#endif
void    P80_InitConsts(void);
float  *P80_Bounds(float *out, int32_t model);     /* 00426ce3 */
void    P80_LoadModels(void *f);                    /* 004eb490 */
void    P80_LoadHeader(void *f);                    /* 004ed055: блок 2 — параметры карты/сетки, направление света, таблица 0x14-байтных записей, списки */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P80_Boxes
#define P80_Boxes (*(p80_boxtab_t *)re_gvar(0x00cf56e0u, sizeof(p80_boxtab_t), (void *)&P80_Boxes))
#undef P80_Class
#define P80_Class (*(p80_class_t *)re_gvar(0x00c98a40u, sizeof(p80_class_t), (void *)&P80_Class))
#undef P80_GridH
#define P80_GridH (*(int32_t *)re_gvar(0x00562d3cu, sizeof(int32_t), (void *)&P80_GridH))
#undef P80_Cell
#define P80_Cell (*(int32_t *)re_gvar(0x00562d40u, sizeof(int32_t), (void *)&P80_Cell))
#undef P80_Hdr5
#define P80_Hdr5 (*(int32_t *)re_gvar(0x00d01274u, sizeof(int32_t), (void *)&P80_Hdr5))
#undef P80_Hdr6
#define P80_Hdr6 (*(int32_t *)re_gvar(0x00c97a28u, sizeof(int32_t), (void *)&P80_Hdr6))
#undef P80_HalfW
#define P80_HalfW (*(int32_t *)re_gvar(0x00cb8f08u, sizeof(int32_t), (void *)&P80_HalfW))
#undef P80_HalfH
#define P80_HalfH (*(int32_t *)re_gvar(0x00cf2f9cu, sizeof(int32_t), (void *)&P80_HalfH))
#undef P80_InvMap
#define P80_InvMap (*(float *)re_gvar(0x00c1cc60u, sizeof(float), (void *)&P80_InvMap))
#undef P80_Cols
#define P80_Cols (*(int32_t *)re_gvar(0x00d00250u, sizeof(int32_t), (void *)&P80_Cols))
#undef P80_Save0
#define P80_Save0 (*(float *)re_gvar(0x00d001f0u, sizeof(float), (void *)&P80_Save0))
#undef P80_Save1
#define P80_Save1 (*(float *)re_gvar(0x00d001f4u, sizeof(float), (void *)&P80_Save1))
#undef P80_Save2
#define P80_Save2 (*(float *)re_gvar(0x00d001f8u, sizeof(float), (void *)&P80_Save2))
#undef P80_Save3
#define P80_Save3 (*(float *)re_gvar(0x00d001fcu, sizeof(float), (void *)&P80_Save3))
#undef P80_Dir3
#define P80_Dir3 (*(float *)re_gvar(0x005507dcu, sizeof(float), (void *)&P80_Dir3))
#undef P80_SaveW
#define P80_SaveW (*(float *)re_gvar(0x00cb8f00u, sizeof(float), (void *)&P80_SaveW))
#undef P80_Alt0
#define P80_Alt0 (*(float *)re_gvar(0x00d00240u, sizeof(float), (void *)&P80_Alt0))
#undef P80_Alt1
#define P80_Alt1 (*(float *)re_gvar(0x00d00244u, sizeof(float), (void *)&P80_Alt1))
#undef P80_Alt2
#define P80_Alt2 (*(float *)re_gvar(0x00d00248u, sizeof(float), (void *)&P80_Alt2))
#undef P80_Alt3
#define P80_Alt3 (*(float *)re_gvar(0x00d0024cu, sizeof(float), (void *)&P80_Alt3))
#undef P80_AltW
#define P80_AltW (*(float *)re_gvar(0x00d01264u, sizeof(float), (void *)&P80_AltW))
#undef P80_Flag17AEC
#define P80_Flag17AEC (*(int32_t *)re_gvar(0x00d17aecu, sizeof(int32_t), (void *)&P80_Flag17AEC))
#undef P80_One
#define P80_One (*(float *)re_gvar(0x00546020u, sizeof(float), (void *)&P80_One))
#undef P80_C45
#define P80_C45 (*(float *)re_gvar(0x005461f4u, sizeof(float), (void *)&P80_C45))
#undef P80_C02
#define P80_C02 (*(float *)re_gvar(0x00546080u, sizeof(float), (void *)&P80_C02))
#undef P80_C045
#define P80_C045 (*(float *)re_gvar(0x005469ecu, sizeof(float), (void *)&P80_C045))
#undef P80_Half
#define P80_Half (*(float *)re_gvar(0x00546068u, sizeof(float), (void *)&P80_Half))
#endif
/* gvar-img v2.03 end */
