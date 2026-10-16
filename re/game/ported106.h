/* v1.51 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   004ae6fb — следы фар машины на дороге (объекты B, P96_AddObjB), 004adfcc / 004ad837 — задние огни/стоп-сигналы машины
   (объекты C 0110b24c; 004ad837 — с проверкой угла к камере и объектом B), 00420a21 — проверка формата эмулируемой текстуры
   (две CreateSurface с форматами устройства +0x528/+0x548), 0042282f / 004228eb — загрузка 8-битных/16-битных кадров
   в список эмулируемых текстур (Lock/Unlock), 004d92d2 — текст шрифтом 8×8 (P21_Font8) прямо в LFB,
   0048bf52 — пресет EAX (IKsPropertySet::Set, таблица .data 005511f0), 00512174 — такт частиц, 004ef66a — небесные модели P79_ModelTab[0..3] с текстурой по таблице .data 00562d9c и grDepthBiasLevel. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>

#define P106_SkyRot GAME_VAR(int32_t, P106_SkyRot, 0x00cf2f80)   /* индекс записи P56_EulerTab для неба 004ef66a */
#define P106_PartOn GAME_VAR(int32_t, P106_PartOn, 0x00c56700)   /* частицы включены (00512174) */
#ifndef RE_HOOK_BUILD
extern int32_t P106_PartOn;
extern int32_t P106_SkyRot;
#endif

void    P106_CarHeadSpots(int32_t car);                    /* 004ae6fb */
void    P106_CarTailLights(int32_t car);                   /* 004adfcc */
void    P106_CarBrakeLights(int32_t car);                  /* 004ad837 */
int32_t P106_CanDevTex(const uint8_t *dev, void *dd);      /* 00420a21 */
void    P106_EmulUpload8(void *node, int32_t src);         /* 0042282f: src — адрес 256×256 индексов, палитра — узел +0xc */
void    P106_EmulUpload16(void *node, int32_t src);        /* 004228eb: только узлы с +4 == G6_0054EF2C */
void    P106_LfbText(uint32_t text);                       /* 004d92d2 */
void    P106_SkyModels(void);                              /* 004ef66a */
void    P106_PartTick(void);                               /* 00512174 */
void    P106_EaxPreset(int32_t i);                         /* 0048bf52 */
