#include "ported69.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P69_STD __attribute__((stdcall))
#else
#  define P69_STD
#endif
GAME_VAR_DEF(uint32_t, P69_Num3, 0x01134298)
GAME_VAR_DEF(uint32_t, P69_Num2, 0x01134264)
GAME_VAR_DEF(uint32_t, P69_Num1, 0x01134294)
GAME_VAR_DEF(uint32_t, P69_Go, 0x0113429c)
GAME_VAR_DEF(uint32_t, P69_Check, 0x0113428c)
GAME_VAR_DEF(uint32_t, P69_Finish, 0x01134288)
GAME_VAR_DEF(P69_Blk, P69_MsgBlk, 0x011342a0)
GAME_VAR_DEF(int32_t, P69_MsgW, 0x011342d4)
GAME_VAR_DEF(int32_t, P69_Score, 0x011368c4)
GAME_VAR_DEF(int32_t, P69_Bonus, 0x01136ac8)
GAME_VAR_DEF(int32_t, P69_ScoreCpy, 0x01271068)
GAME_VAR_DEF(uint8_t, P69_BlendOn, 0x0125f3e4)
GAME_VAR_DEF(int32_t, P69_OvlOn, 0x01123210)
GAME_VAR_DEF(int32_t, P69_DevOn, 0x00b1c0d0)
GAME_VAR_DEF(P69_ThrTab, P69_Thr, 0x01136940)
GAME_VAR_DEF(P69_PtrTab, P69_Ptrs, 0x01136a80)
GAME_VAR_DEF(P69_Pts, P69_PtsTab, 0x00551528)

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

/* 004a3630 */
void P69_SetupMsgs(void) {
  P69_Num3 = (uint32_t)P20_FindNameValue("3");
  P69_Num2 = (uint32_t)P20_FindNameValue("2");
  P69_Num1 = (uint32_t)P20_FindNameValue("1");
  const char *go = NULL, *chk = NULL, *fin = NULL;
  switch (P55_Lang) {
  case 0: case 5: go = "GO"; chk = "CHECKPOINT"; fin = "FINISHED"; break;
  case 1: go = "GO"; chk = "CHECKPOINT"; fin = "FR_TERMINE"; break;
  case 2: go = "GR_LOS"; chk = "GR_KONTROLLPUNKT"; fin = "GR_GESCHAFFT"; break;
  case 3: go = "SP_ADELANTE"; chk = "SP_PUNTO-DE-CONTROL"; fin = "SP_SE-ACABO"; break;
  case 4: go = "IT_VIA"; chk = "IT_POSTO-DI-CONTROLLO"; fin = "IT_FINE"; break;
  default: break;
  }
  if (go) {
    P69_Go = (uint32_t)P20_FindNameValue(go);
    P69_Check = (uint32_t)P20_FindNameValue(chk);
    P69_Finish = (uint32_t)P20_FindNameValue(fin);
  }
  memset(P69_MsgBlk, 0, 0x48);
  P69_MsgW = 0x8c;
}

/* Таблица порогов: указатели хранятся адресами (в hook — настоящими, в native — теми же числами 0x01136940+4k). */
static int thr_idx(uint32_t addr) {
  if (addr < P69_TBASE || ((addr - P69_TBASE) & 3) != 0) return -1;
  uint32_t k = (addr - P69_TBASE) >> 2;
  return k < 79 ? (int)k : -1;
}

/* 004a0cca */
uint8_t P69_Bracket(uint32_t v) {
  uint8_t c = 0;
  uint32_t p = P69_TBASE;
  for (;;) {
    if ((int32_t)c >= 0x12) return c;
    /* пропускаем совпадение с указателем-границей (в оригинале без проверки c < 0x12 — охранная проверка массива) */
    while (c < 18 && p == P69_Ptrs[c + 1]) c++;
    if (c >= 18) return c;
    int k = thr_idx(p);
    if (k < 0) return c;
    uint32_t t = P69_Thr[k];
    if (t > v) {
      c++;
      if (c >= 18) return c;
      p = P69_Ptrs[c];
    } else if (t < v) {
      if (p == P69_TEND) return 0x12;
      p += 4;
    } else return c;
  }
}

/* 004a0d5f */
int32_t P69_AddScore(int32_t v) {
  if (v == 0xff00) {
    P69_Score += (P69_Bonus / 0x78) * 100;
    P69_Bonus = 0;
  } else {
    uint8_t b = P69_Bracket((uint32_t)v);
    if (b != 0x12) P69_Score += P69_PtsTab[b];
  }
  if (P69_Score > 999999) P69_Score = 999999;
  P69_ScoreCpy = P69_Score;
  return 0;
}

/* 004b3ddb */
void P69_ReleaseOverlays(void) {
  if (P69_BlendOn != 0) {
    void (P69_STD *f)(int32_t, int32_t, int32_t, int32_t) = (void (P69_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaBlendFunction@16");
    if (f) f(4, 0, 4, 0);
    P69_BlendOn = 0;
  }
  if (P69_OvlOn != 0) {
    uint8_t *e = (uint8_t *)P12_0110b260;
    for (int i = 0; i < 200; i++, e += 0x3c) {
      uint16_t fl; memcpy(&fl, e + 0x22, 2);
      if (fl & 2) P69_Fn4B33D8(e);
    }
  }
}

static void fog_mode(int32_t m) {
  void (P69_STD *f)(int32_t) = (void (P69_STD *)(int32_t))glide_proc("_grFogMode@4");
  if (f) f(m);
}

/* 004aaea6 */
void P69_SceneFrame(void) {
  P12_Fn00426580(0);
  if (G6_01270C34 != 4) {
    void (P69_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t) = (void (P69_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grColorCombine@20");
    if (f) f(3, 1, 0, 1, 0);
    G6_01270C34 = 4;
  }
  if (MenuVar553850 != 0) Call004C0C6F(1);
  P44_MatPtr = (float *)&P44_ViewMatT;
  P69_Fn4B3E55();
  P69_Fn4B2C4B();
  P69_ReleaseOverlays();
  InitSubsys004BA443();
  if (P26_FxD != 0) fog_mode(0);
  P69_Fn4AAF3A();
  P69_Fn4BA720();
  if (P26_FxD != 0) fog_mode(2);
}

/* 004246f0 */
void P69_FreeDevices(void) {
  Dev00424858();
  if (P69_DevOn != 0) {
    for (int32_t i = 0; i < P42_DevCount && i < 16; i++) {
      uint32_t ptr; memcpy(&ptr, P42_DevNames[i] + 0x44, 4);
      if (ptr != 0) CrtFree_0052CB70(ptr);
    }
    P69_DevOn = 0;
    D_00b1c0d4 = 0;
    P42_DevCount = 0;
  }
  P42_FreeGlide();
}

#ifndef RE_HOOK_BUILD
void P69_InitConsts(void) {
  static const int32_t pts[18] = {100,150,200,50,250,300,200,250,150,500,400,0,300,700,1000,200,95,175};
  memcpy(P69_PtsTab, pts, sizeof pts);
}
#endif
