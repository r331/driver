#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.66: ported121 — новые переменные (вне native-таблиц) */
typedef float p121_clipbuf_t[8 * 12];   /* 01159f80: вершины отсечения по 12 float (в оригинале 5 вершин до 0115a070) */
#define P121_ClipBuf GAME_VAR(p121_clipbuf_t, P121_ClipBuf, 0x01159f80)
#define P121_CamW    GAME_VAR(uint32_t, P121_CamW, 0x00b1c27c)    /* четвёртое слово позиции камеры (00b1c270..7c) */
#ifndef RE_HOOK_BUILD
extern p121_clipbuf_t P121_ClipBuf;
extern uint32_t P121_CamW;
#endif
void     P121_ScriptHud(void);                 /* 004f4a33: сообщения миссии (FAILED/SMASHED/OUTOFRANGE/CARGOTAWAY) и часы скрипта */
uint16_t P121_ParseCamLine(char *s);           /* 004a4a5f: строка сценария камеры → номер команды 1..32 (0 — ошибка, 0x32 — комментарий) */
void     P121_TexQuadFlat(uint32_t arg);       /* 00431016: запись модели 0x44 — текстурный четырёхугольник с цветом записи */
void     P121_DustDraw(void);                  /* 004b2c4b: частицы пыли P96_Dust значками SWBIRD2/SWBIRD1 */
void     P121_ClipQuad(uint32_t arg);          /* 00447753: запись 0x24 — однотонный четырёхугольник с отсечением дальней плоскостью */
void     P121_ClipTexQuad(uint32_t arg);       /* 0043a5be: запись 0x44 — текстурный четырёхугольник с отсечением ближней плоскостью */
void     P121_WheelDust(void);                 /* 0051dc18: пыль из-под колёс 0 и 2 игрока (004b955c) */
int32_t  P121_SndNextDev(void);                /* 00415014: следующее звуковое устройство, банк TITLE/MOTEL.DSS, меню настроек */
void     P121_CopSync(uint8_t *p);             /* 004a7d80: копирование позиции машины в запись копа 0112da00 */
void     P121_CamSounds(void);                 /* 004d602e: такт звуков у камеры (зоны 004cd3fb, двигатели, трафик) */
