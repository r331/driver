/* v1.46: единые таблицы дороги. Узлы дороги 00bf1c40 (записи 0x42) и клетки-слоты 00c1ed80 (записи 0x2c) в native — только
   P11_00bf1c40 / P11_00c1ed80 (их заполняют ReadTable_* при загрузке уровня). Прежние отдельные native-переменные внутри них
   (P17_MapBase 00bf1c42, P59_BF1C48 00bf1c48; P17_SlotBase/P11_00c1ed8a 00c1ed8a, P51_Tab1ED80 00c1ed80) — макросы
   NODETAB_VAR/SLOTTAB_VAR над ними (как CARTAB_VAR для таблицы машин); в hook-сборке — ячейки Game.exe как раньше. */
#pragma once
#include <stdint.h>
#ifdef RE_HOOK_BUILD
#  define NODETAB_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#  define SLOTTAB_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#else
#pragma push_macro("P11_00bf1c40") /*gvi*/
#undef P11_00bf1c40 /*gvi*/
#pragma push_macro("P11_00c1ed80") /*gvi*/
#undef P11_00c1ed80 /*gvi*/
extern uint8_t P11_00bf1c40[0x40000], P11_00c1ed80[0x40000];
#pragma pop_macro("P11_00c1ed80") /*gvi*/
#pragma pop_macro("P11_00bf1c40") /*gvi*/
#  define NODETAB_VAR(type, name, addr) (*(type *)(P11_00bf1c40 + ((uint32_t)(addr) - 0x00bf1c40u)))
#  define SLOTTAB_VAR(type, name, addr) (*(type *)(P11_00c1ed80 + ((uint32_t)(addr) - 0x00c1ed80u)))
#endif
