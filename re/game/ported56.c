#include "ported56.h"
#include "ported116.h"
#include "ported14.h"
#include "ported27.h"
#include "ported51.h"
#include "ported8.h"
#include "crt.h"
#include <string.h>
#include <stdio.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Blk84")
#undef P56_Blk84
#pragma push_macro("P56_Blk84") /*gvi*/
#undef P56_Blk84 /*gvi*/
p56_blk84_t P56_Blk84;
#pragma pop_macro("P56_Blk84") /*gvi*/
#pragma pop_macro("P56_Blk84")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Save84")
#undef P56_Save84
#pragma push_macro("P56_Save84") /*gvi*/
#undef P56_Save84 /*gvi*/
p56_blk84_t P56_Save84;
#pragma pop_macro("P56_Save84") /*gvi*/
#pragma pop_macro("P56_Save84")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Blk11")
#undef P56_Blk11
#pragma push_macro("P56_Blk11") /*gvi*/
#undef P56_Blk11 /*gvi*/
p56_blk11_t P56_Blk11;
#pragma pop_macro("P56_Blk11") /*gvi*/
#pragma pop_macro("P56_Blk11")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Save11")
#undef P56_Save11
#pragma push_macro("P56_Save11") /*gvi*/
#undef P56_Save11 /*gvi*/
p56_blk11_t P56_Save11;
#pragma pop_macro("P56_Save11") /*gvi*/
#pragma pop_macro("P56_Save11")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Blk16")
#undef P56_Blk16
#pragma push_macro("P56_Blk16") /*gvi*/
#undef P56_Blk16 /*gvi*/
p56_blk10_t P56_Blk16;
#pragma pop_macro("P56_Blk16") /*gvi*/
#pragma pop_macro("P56_Blk16")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_LoopTab")
#undef P56_LoopTab
#pragma push_macro("P56_LoopTab") /*gvi*/
#undef P56_LoopTab /*gvi*/
p56_snd4_t P56_LoopTab;
#pragma pop_macro("P56_LoopTab") /*gvi*/
#pragma pop_macro("P56_LoopTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Cur")
#undef P56_Cur
#pragma push_macro("P56_Cur") /*gvi*/
#undef P56_Cur /*gvi*/
int32_t P56_Cur;
#pragma pop_macro("P56_Cur") /*gvi*/
#pragma pop_macro("P56_Cur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_B2EA48")
#undef P56_B2EA48
#pragma push_macro("P56_B2EA48") /*gvi*/
#undef P56_B2EA48 /*gvi*/
int32_t P56_B2EA48;
#pragma pop_macro("P56_B2EA48") /*gvi*/
#pragma pop_macro("P56_B2EA48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_B268")
#undef P56_B268
#pragma push_macro("P56_B268") /*gvi*/
#undef P56_B268 /*gvi*/
int32_t P56_B268;
#pragma pop_macro("P56_B268") /*gvi*/
#pragma pop_macro("P56_B268")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_C81880")
#undef P56_C81880
#pragma push_macro("P56_C81880") /*gvi*/
#undef P56_C81880 /*gvi*/
int32_t P56_C81880;
#pragma pop_macro("P56_C81880") /*gvi*/
#pragma pop_macro("P56_C81880")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_F7E58")
#undef P56_F7E58
#pragma push_macro("P56_F7E58") /*gvi*/
#undef P56_F7E58 /*gvi*/
int32_t P56_F7E58;
#pragma pop_macro("P56_F7E58") /*gvi*/
#pragma pop_macro("P56_F7E58")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_AA30")
#undef P56_AA30
#pragma push_macro("P56_AA30") /*gvi*/
#undef P56_AA30 /*gvi*/
uint32_t P56_AA30;
#pragma pop_macro("P56_AA30") /*gvi*/
#pragma pop_macro("P56_AA30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_GhostBuf")
#undef P56_GhostBuf
#pragma push_macro("P56_GhostBuf") /*gvi*/
#undef P56_GhostBuf /*gvi*/
p56_ghost_t P56_GhostBuf;
#pragma pop_macro("P56_GhostBuf") /*gvi*/
#pragma pop_macro("P56_GhostBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_G4538")
#undef P56_G4538
#pragma push_macro("P56_G4538") /*gvi*/
#undef P56_G4538 /*gvi*/
int32_t P56_G4538;
#pragma pop_macro("P56_G4538") /*gvi*/
#pragma pop_macro("P56_G4538")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_G3908")
#undef P56_G3908
#pragma push_macro("P56_G3908") /*gvi*/
#undef P56_G3908 /*gvi*/
int32_t P56_G3908;
#pragma pop_macro("P56_G3908") /*gvi*/
#pragma pop_macro("P56_G3908")
#endif
GAME_VAR_DEF(uint8_t *, P56_GhostPtr, 0x00d04488)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_B87EA8")
#undef P56_B87EA8
#pragma push_macro("P56_B87EA8") /*gvi*/
#undef P56_B87EA8 /*gvi*/
int32_t P56_B87EA8;
#pragma pop_macro("P56_B87EA8") /*gvi*/
#pragma pop_macro("P56_B87EA8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_D4470")
#undef P56_D4470
#pragma push_macro("P56_D4470") /*gvi*/
#undef P56_D4470 /*gvi*/
int32_t P56_D4470;
#pragma pop_macro("P56_D4470") /*gvi*/
#pragma pop_macro("P56_D4470")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_Page")
#undef P56_Page
#pragma push_macro("P56_Page") /*gvi*/
#undef P56_Page /*gvi*/
p56_page_t P56_Page;
#pragma pop_macro("P56_Page") /*gvi*/
#pragma pop_macro("P56_Page")
#endif
GAME_VAR_DEF(uint8_t *, P56_EulerTab, 0x00b1c280)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_C546120")
#undef P56_C546120
#pragma push_macro("P56_C546120") /*gvi*/
#undef P56_C546120 /*gvi*/
float P56_C546120;
#pragma pop_macro("P56_C546120") /*gvi*/
#pragma pop_macro("P56_C546120")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_C54611C")
#undef P56_C54611C
#pragma push_macro("P56_C54611C") /*gvi*/
#undef P56_C54611C /*gvi*/
float P56_C54611C;
#pragma pop_macro("P56_C54611C") /*gvi*/
#pragma pop_macro("P56_C54611C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_C546A38")
#undef P56_C546A38
#pragma push_macro("P56_C546A38") /*gvi*/
#undef P56_C546A38 /*gvi*/
float P56_C546A38;
#pragma pop_macro("P56_C546A38") /*gvi*/
#pragma pop_macro("P56_C546A38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_F573FA0")
#undef P56_F573FA0
#pragma push_macro("P56_F573FA0") /*gvi*/
#undef P56_F573FA0 /*gvi*/
float P56_F573FA0;
#pragma pop_macro("P56_F573FA0") /*gvi*/
#pragma pop_macro("P56_F573FA0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_F573FA4")
#undef P56_F573FA4
#pragma push_macro("P56_F573FA4") /*gvi*/
#undef P56_F573FA4 /*gvi*/
float P56_F573FA4;
#pragma pop_macro("P56_F573FA4") /*gvi*/
#pragma pop_macro("P56_F573FA4")
#endif
GAME_VAR_DEF(uint8_t *, P56_Sprite, 0x00c80888)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_CopsA")
#undef P56_CopsA
#pragma push_macro("P56_CopsA") /*gvi*/
#undef P56_CopsA /*gvi*/
int32_t P56_CopsA;
#pragma pop_macro("P56_CopsA") /*gvi*/
#pragma pop_macro("P56_CopsA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_CopsB")
#undef P56_CopsB
#pragma push_macro("P56_CopsB") /*gvi*/
#undef P56_CopsB /*gvi*/
int32_t P56_CopsB;
#pragma pop_macro("P56_CopsB") /*gvi*/
#pragma pop_macro("P56_CopsB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathLeader")
#undef P56_PathLeader
#pragma push_macro("P56_PathLeader") /*gvi*/
#undef P56_PathLeader /*gvi*/
p56_s60_t P56_PathLeader;
#pragma pop_macro("P56_PathLeader") /*gvi*/
#pragma pop_macro("P56_PathLeader")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathPlayer")
#undef P56_PathPlayer
#pragma push_macro("P56_PathPlayer") /*gvi*/
#undef P56_PathPlayer /*gvi*/
p56_s100_t P56_PathPlayer;
#pragma pop_macro("P56_PathPlayer") /*gvi*/
#pragma pop_macro("P56_PathPlayer")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathPads")
#undef P56_PathPads
#pragma push_macro("P56_PathPads") /*gvi*/
#undef P56_PathPads /*gvi*/
p56_s60_t P56_PathPads;
#pragma pop_macro("P56_PathPads") /*gvi*/
#pragma pop_macro("P56_PathPads")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathPings")
#undef P56_PathPings
#pragma push_macro("P56_PathPings") /*gvi*/
#undef P56_PathPings /*gvi*/
p56_s120_t P56_PathPings;
#pragma pop_macro("P56_PathPings") /*gvi*/
#pragma pop_macro("P56_PathPings")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathCams")
#undef P56_PathCams
#pragma push_macro("P56_PathCams") /*gvi*/
#undef P56_PathCams /*gvi*/
p56_s100_t P56_PathCams;
#pragma pop_macro("P56_PathCams") /*gvi*/
#pragma pop_macro("P56_PathCams")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathKey")
#undef P56_PathKey
#pragma push_macro("P56_PathKey") /*gvi*/
#undef P56_PathKey /*gvi*/
p56_s1a0_t P56_PathKey;
#pragma pop_macro("P56_PathKey") /*gvi*/
#pragma pop_macro("P56_PathKey")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathStart")
#undef P56_PathStart
#pragma push_macro("P56_PathStart") /*gvi*/
#undef P56_PathStart /*gvi*/
p56_s360_t P56_PathStart;
#pragma pop_macro("P56_PathStart") /*gvi*/
#pragma pop_macro("P56_PathStart")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_PathName")
#undef P56_PathName
#pragma push_macro("P56_PathName") /*gvi*/
#undef P56_PathName /*gvi*/
p56_s100_t P56_PathName;
#pragma pop_macro("P56_PathName") /*gvi*/
#pragma pop_macro("P56_PathName")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_SaveHdr")
#undef P56_SaveHdr
#pragma push_macro("P56_SaveHdr") /*gvi*/
#undef P56_SaveHdr /*gvi*/
p56_hdr_t P56_SaveHdr;
#pragma pop_macro("P56_SaveHdr") /*gvi*/
#pragma pop_macro("P56_SaveHdr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P56_SaveBuf")
#undef P56_SaveBuf
#pragma push_macro("P56_SaveBuf") /*gvi*/
#undef P56_SaveBuf /*gvi*/
p56_save_t P56_SaveBuf;
#pragma pop_macro("P56_SaveBuf") /*gvi*/
#pragma pop_macro("P56_SaveBuf")
#endif

static uint32_t r32(const void *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void w32(void *p, uint32_t v) { memcpy(p, &v, 4); }

/* Начальные значения float-констант из .data Game.exe (нужны только native). */
void P56_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P19_DivC = 2.0f; P56_C546120 = 1.5f; P56_C54611C = 2.5f; P56_C546A38 = 0.0007812500116415322f; P56_F573FA0 = 540.0f; P56_F573FA4 = 380.0f;
  P116_K546A3C = 0.0015625000232830644f; P116_BlinkT = 10;
#endif
}

/* 005105da: перед повтором в режимах 4/5 запоминает блок настроек погони (0x84 слова) и 0x11 слов меню. */
void P56_ReplaySetup(void) {
  if (G005F7E54 == 4 || G005F7E54 == 5) {
    if (GameMode == 0) DirectorLastFrame = G8_00D118C0 - 4;
    if ((P56_Blk84[1] & 0x8000) == 0) P56_Blk84[1] = 0xff0;
    memcpy(P56_Save84, P56_Blk84, sizeof(p56_blk84_t));
    memcpy(P56_Save11, P56_Blk11, sizeof(p56_blk11_t));
  }
  G6_00B87E20 = 0;
  SetLatchValue0050E940(0);
}

/* 004da8d9: координаты объекта (>>4) и затухание кватерниона a[3..6]. a — 7 слов с позиции o+0x24. */
void P56_ObjSync(int32_t *a, uint8_t *o) {
  w32(o + 0x18, (uint32_t)(a[0] >> 4)); w32(o + 0xc8, r32(o + 0x18));
  w32(o + 0x1c, (uint32_t)(a[1] >> 4)); w32(o + 0xcc, r32(o + 0x1c));
  w32(o + 0x20, (uint32_t)(a[2] >> 4)); w32(o + 0xd0, r32(o + 0x20));
  int32_t s = (int32_t)((uint32_t)a[3] * (uint32_t)a[3] + (uint32_t)a[4] * (uint32_t)a[4] +
                        (uint32_t)a[5] * (uint32_t)a[5] + (uint32_t)a[6] * (uint32_t)a[6]);
  if (s < 0x400) { a[5] = 0; a[4] = 0; a[3] = 0; a[6] = 0x1000; }
  else {
    int32_t k = 0x1800 - (s >> 13);
    for (int i = 3; i < 7; i++) a[i] = (int32_t)((uint32_t)k * (uint32_t)a[i] + 0x800u) >> 12;
  }
  P56_Fn4DA76A(a + 3, o + 4);
}

/* 004daa36: начальное состояние объекта из позиции q[0..2] (<<4). */
void P56_ObjInit(uint8_t *o, const int32_t *q) {
  P14_Fn0048DB65(o, 0x148);
  P56_B2EA48 = 0;
  w32(o + 0x3c, 0x1000);
  w32(o + 0x24, (uint32_t)q[0] << 4);
  w32(o + 0x28, (uint32_t)q[1] << 4);
  w32(o + 0x2c, (uint32_t)q[2] << 4);
  P56_ObjSync((int32_t *)(o + 0x24), o);
  w32(o + 0x58, 0); w32(o + 0x5c, 0xffffd556u); w32(o + 0x60, 0);
  G6_005624A0 = 0xf;
}

/* 00523ec6: позиция голоса (старая сохраняется), флаг «позиция изменена». */
void P56_SetVoicePos(int32_t slot, float x, float y, float z) {
  if (G8_00B91CF4 != 0 && G8_00575F40 != 0 && (P48_Snd[slot].flags & 0x11) != 0) {
    P48_Slot *s = &P48_Snd[slot];
    if (s->flags & 0x20) s->flags &= 0xdf;
    memcpy(s->data + 0x0c, s->data, 12);
    memcpy(s->data, &x, 4); memcpy(s->data + 4, &y, 4); memcpy(s->data + 8, &z, 4);
    s->flags |= 2;
  }
}

/* 004d62ae: запуск зацикленного звука (голос 10) на объекте n, если его запись в TrafficRecs не равна 1. */
void P56_LoopStart(int32_t n) {
  if (TrafficRecs[(n - 1) * 0x54 + 2] != 1) {
    P56_CallSetVoice(0xb, 10, (float)ObjPosTable[n * 0x52], (float)ObjPosTable[n * 0x52 + 1], (float)ObjPosTable[n * 0x52 + 2]);
    P48_SetVoiceVolume(10, 0x7fff);
    SoundSetPos00523F8A(10, P56_LoopTab[G8_00D118C0 & 3]);
    P56_Cur = n;
  }
}

/* 004d6a47: обновление позиции звука; если запись исчезла — голос освобождается. */
void P56_LoopUpdate(void) {
  int32_t c = P56_Cur;
  if (c == -1) return;
  P56_SetVoicePos(10, (float)ObjPosTable[c * 0x52], (float)(int32_t)(0u - (uint32_t)ObjPosTable[c * 0x52 + 1]),
                  (float)ObjPosTable[c * 0x52 + 2]);
  if (TrafficRecs[(c - 1) * 0x54 + 2] != 1) { P48_FreeVoice(10); P56_Cur = -1; }
}

#ifdef RE_HOOK_BUILD
#  define P56_ARENA() ((void *)(uintptr_t)P41_Arena)
#else
#  define P56_ARENA() ((void *)P41_RamPtr())
#endif
/* 0040c165: сброс состояния при выходе из игры в меню: таймер, CD, звук, буферы страниц и карты. */
void P56_ResetFrontend(void) {
  StopTimer4086EA();
  G6_00B87EFC = 0;
  P56_F7E58 = 0;
  if (Q00B87E90 != 0) { P25_CDStop(); P25_CDClose(); }
  P48_ResetAll();
  if (P41_Arena != 0) { DebugFree(P56_ARENA()); P41_Arena = 0; P41_Offset = 0; }
  if (P54_MapAPtr != 0) { DebugFree(P54_MapAPtr); P54_MapAPtr = 0; P54_MapA = 0; }
  P56_AA30 = 0x3f000000u;
  P54_ClearSwap(4);
  P56_Fn406479();
}

/* 004f5a57: тик погони. */
void P56_ChaseTick(void) {
  int32_t *b = (int32_t *)P56_Blk84;
  P56_B268 = 0;
  b[2]++;
  if ((b[1] & 0x8000) == 0) {
    if (b[1] == 0xf1) {
      if (b[2] < 0x33) P4Call004CA98D(5, b[2]);
      else b[2] = 0x33;
    } else b[1] = 0x7fff;
  } else if (P56_C81880 == 0) {
    P56_C81880 = 1; b[10] = 0; b[16] = 0x96; G2_00D118A8 = 1;
  }
}

/* 0051d8ca: 16 слов в глобальный блок. */
void P56_CopyBlock16(const uint32_t *src) { for (int i = 0; i < 16; i++) P56_Blk16[i] = src[i]; }

/* 004e625e: сброс призрака, подгонка размеров значка «GHOST». */
void P56_GhostInit(void) {
  P14_Fn0048DB65(P56_GhostBuf, 0xb40);
  P56_G4538 = 0; P56_G3908 = 0;
  P56_GhostPtr = P56_FindIcon("GHOST");
  uint8_t *g = P56_GhostPtr;
  if (g != NULL) {
    g[9] = (uint8_t)(g[9] + 1);
    g[10] = (uint8_t)(g[10] + 1);
    g[0xb] = (uint8_t)(g[0xb] + g[9] - 2);
    g[0xc] = (uint8_t)(g[0xc] + g[10] - 2);
  }
}

/* 0049245a: позиция машины (по номеру в TrafficRecs) и сравнение поля +0x138 с min. */
int32_t P56_CarPosCheck(int32_t id, int32_t min, uint32_t *out) {
  int32_t i = 0;
  const uint8_t *e = TrafficRecs;
  for (; i < 0x40 && (uint32_t)e[6] != (uint32_t)id + 1u; e += 0x54) i++;
  const uint8_t *c = G0113A6C4 + (size_t)i * 0x148;
  if (out != NULL) { out[0] = r32(c + 200); out[1] = r32(c + 0xcc); out[2] = r32(c + 0xd0); }
  return min <= (int32_t)r32(c + 0x138);
}

/* 0051990a: восстанавливает запись машины из журнала повтора (0x1a4 байта на кадр). */
int32_t P56_ReplayRead(void) {
  int32_t r = -1;
  if (P55_RecBase != NULL && P55_RecCnt < 0x800) {
    const uint8_t *p = P55_RecBase + (size_t)P55_RecCnt * 0x1a4;
    if ((int32_t)r32(p) == G8_00D118C0) {
      r = (int32_t)r32(p + 4);
      memcpy(TrafficRecs + (size_t)r * 0x54, p + 8, 0x54);
      memcpy(G0113A6C4 + (size_t)r * 0x148, p + 0x5c, 0x148);
      Call004C0218(r);
      P55_RecCnt++;
    }
  }
  return r;
}

/* 004e4f62: тик интерфейса (режим 4 или экран повтора): счётчики и три вызова. */
void P56_HudTick(int32_t a) {
  if (P15_State == 4 || G6_00B87EA0 != 0) {
    void *o = (P56_B87EA8 == 0) ? (void *)P56_Objs[S_00D11878] : (void *)P56_Objs[65];
    if (G6_00B5A778 == 0) G00D044C8++;
    if (P12_00d044d0 != 0) P12_00d044d0--;
    if (0 < P56_D4470) P56_D4470--;
    P56_Fn4E5284(o);
    P56_Fn4E5011(a, o);
    P56_Fn4E53B5(a, o);
  }
}

/* 004f3032: ряд из 31 пары (x, длина) — прямоугольники высотой 10, цвет 0x8800. */
void P56_DrawRowRects(const int16_t *p, int32_t x, int32_t y) {
  if (p == NULL) return;
  for (int32_t i = 0; i < 0x1f; i++, p += 2) {
    if (0 < p[3]) DrawRect((float)(x + p[2] * 10), (float)(y + i * 10), (float)(p[3] * 10), 10.0f, 0x8800);
  }
}

/* 005046f7: копирует прямоугольник w*h из 8-битного bmp в буфер страницы 256 байт в строке и передаёт его в 0048a46b. */
void P56_BmpPage(int32_t page, const uint8_t *bmp, int32_t x, int32_t y, int32_t w, int32_t h, int32_t stride) {
  if (bmp == NULL) { DebugLog("DownloadPageFromBmp: Bitmap not found, operation aborted."); return; }
  const uint8_t *s = bmp + y * stride + x;
  uint8_t *d = P56_Page;
  for (; h != 0; h--) {
    for (int32_t k = w; k != 0; k--) *d++ = *s++;
    s += stride - w;
    d += 0x100 - w;
  }
  P12_Fn0048A46B(page, (int32_t)(uintptr_t)P56_Page);
}

/* 00426c06: таблица матриц поворота вокруг оси Y с шагом step (углы 0..4095), по 0x40 байт на матрицу. */
uint8_t *P56_AllocEulerTab(int32_t step) {
  int16_t ang[4] = {0, 0, 0, 0};
  int32_t n = (int32_t)(0x1000 / (int64_t)step);
  P56_EulerTab = (uint8_t *)DebugMalloc(n << 6, "D:\\Driver\\Game\\Engine\\3dfx\\Object.c", 0xf5);
  if (P56_EulerTab != NULL) {
    uint8_t *q = P56_EulerTab;
    for (int32_t i = 0; i < n; i++) {
      P43_EulerMatrix((float *)q, ang);
      ang[1] = (int16_t)(((uint16_t)ang[1] + (uint16_t)(int16_t)step) & 0xfff);
      q += 0x40;
    }
  }
  return P56_EulerTab;
}

/* 0049ee5d: сплайн Катмулла-Рома через четыре значения, t в 0..1. */
void P56_Spline(float t, float *out, float p0, float p1, float p2, float p3) {
  float f1 = t * t, f2 = f1 * t;
  *out = (P51_Half * f2 - P51_Half * f1) * p3 +
         (P51_Half * t + (P19_DivC * f1 - P56_C546120 * f2)) * p2 +
         ((P56_C546120 * f2 - P56_C54611C * f1) + P8_00546020) * p1 +
         ((f1 - P51_Half * f2) - P51_Half * t) * p0;
}

/* 0049f180: a = b * (a * conj(b)) — поворот четвёрки a кватернионом b (5 слов, как в оригинале). */
void P56_QuatRot(float *a, const float *b) {
  float L[5], Q[5];
  L[0] = a[0]; L[1] = a[1]; L[2] = a[2]; L[3] = a[3]; L[4] = 0.0f;
  memcpy(Q, b, sizeof Q);
  NegateVec3_005270F6(Q);
  P44_QuatMul(L, Q, L);
  P44_QuatMul(b, L, L);
  a[0] = L[0]; a[1] = L[1]; a[2] = L[2]; a[3] = L[3];
}

/* 00506b4b: значок-спрайт в углу экрана, масштаб по ширине экрана. */
void P56_DrawSprite(void) {
  if (P56_Sprite != NULL) {
    float f = P56_C546A38 * (float)P19_ScrW * P19_Scale;
    P56_DrawSpr(P56_F573FA0 - (float)P56_Sprite[0xb] * f * P51_Half, P56_F573FA4 - (float)P56_Sprite[0xc] * f * P51_Half,
                f, f, P56_Sprite, 0xff, 0xff, 0xff, 2);
  }
}

/* 00518137: имена файлов ReplayData для погони (по имени в c54ac0) и для повтора n. */
void P56_ReplayPaths(int32_t n) {
  snprintf(P56_PathLeader, sizeof(p56_s60_t), "ReplayData\\Chase\\%.40s.LEADER", P56_PathName);
  snprintf(P56_PathPlayer, sizeof(p56_s100_t), "ReplayData\\Chase\\%.200s.PLAYER", P56_PathName);
  snprintf(P56_PathPads, sizeof(p56_s60_t), "ReplayData\\Chase\\%.40s.PADS", P56_PathName);
  snprintf(P56_PathPings, sizeof(p56_s120_t), "ReplayData\\Chase\\%.200s.PINGS", P56_PathName);
  snprintf(P56_PathCams, sizeof(p56_s100_t), "ReplayData\\RepCams.%d", n);
  snprintf(P56_PathKey, sizeof(p56_s1a0_t), "ReplayData\\KeyFrame.%d", n);
  snprintf(P56_PathStart, sizeof(p56_s360_t), "ReplayData\\StartPos.%d", n);
}

/* 004d263d: отладочные строки «Cops can see player» (одноразовые флаги). */
void P56_CopsDebug(void) {
  if (P56_CopsA != 0) P56_DrawText(0x10, 0x140, "Cops can see player - Internal 360 radius!", 0, 0, 0xff, 0xff, 0xff);
  if (P56_CopsB != 0) P56_DrawText(0x10, 0x150, "Cops can see player - View frustrum!", 0, 0, 0xff, 0xff, 0xff);
  P56_CopsA = 0; P56_CopsB = 0;
}

/* 00405cb4: проверка файла SAVES\GAMEn.BIN: подпись 0x57231356 и контрольная сумма 0x38 байт. */
int32_t P56_SaveCheck(int32_t slot) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\GAME%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(P56_SaveHdr, 1, 8, f);
  g_fread(P56_SaveBuf, 1, 0x38, f);
  g_fclose(f);
  if (P56_SaveHdr[0] != 0x57231356u) return 0;
  return P56_Fn40682D(P56_SaveBuf, 0x38) == (int32_t)P56_SaveHdr[1];
}
