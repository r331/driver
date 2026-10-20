/* ported69 — countdown / checkpoint message names, score brackets (Game.exe, cdecl), overlay release, the scene
   frame sequence and Glide device teardown. */
#include "ported69.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P69_STD __attribute__((stdcall))
#else
#  define P69_STD
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Num3")
#undef P69_Num3
#pragma push_macro("P69_Num3") /*gvi*/
#undef P69_Num3 /*gvi*/
uint32_t P69_Num3;
#pragma pop_macro("P69_Num3") /*gvi*/
#pragma pop_macro("P69_Num3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Num2")
#undef P69_Num2
#pragma push_macro("P69_Num2") /*gvi*/
#undef P69_Num2 /*gvi*/
uint32_t P69_Num2;
#pragma pop_macro("P69_Num2") /*gvi*/
#pragma pop_macro("P69_Num2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Num1")
#undef P69_Num1
#pragma push_macro("P69_Num1") /*gvi*/
#undef P69_Num1 /*gvi*/
uint32_t P69_Num1;
#pragma pop_macro("P69_Num1") /*gvi*/
#pragma pop_macro("P69_Num1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Go")
#undef P69_Go
#pragma push_macro("P69_Go") /*gvi*/
#undef P69_Go /*gvi*/
uint32_t P69_Go;
#pragma pop_macro("P69_Go") /*gvi*/
#pragma pop_macro("P69_Go")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Check")
#undef P69_Check
#pragma push_macro("P69_Check") /*gvi*/
#undef P69_Check /*gvi*/
uint32_t P69_Check;
#pragma pop_macro("P69_Check") /*gvi*/
#pragma pop_macro("P69_Check")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Finish")
#undef P69_Finish
#pragma push_macro("P69_Finish") /*gvi*/
#undef P69_Finish /*gvi*/
uint32_t P69_Finish;
#pragma pop_macro("P69_Finish") /*gvi*/
#pragma pop_macro("P69_Finish")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_MsgBlk")
#undef P69_MsgBlk
#pragma push_macro("P69_MsgBlk") /*gvi*/
#undef P69_MsgBlk /*gvi*/
P69_Blk P69_MsgBlk;
#pragma pop_macro("P69_MsgBlk") /*gvi*/
#pragma pop_macro("P69_MsgBlk")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_MsgW")
#undef P69_MsgW
#pragma push_macro("P69_MsgW") /*gvi*/
#undef P69_MsgW /*gvi*/
int32_t P69_MsgW;
#pragma pop_macro("P69_MsgW") /*gvi*/
#pragma pop_macro("P69_MsgW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Score")
#undef P69_Score
#pragma push_macro("P69_Score") /*gvi*/
#undef P69_Score /*gvi*/
int32_t P69_Score;
#pragma pop_macro("P69_Score") /*gvi*/
#pragma pop_macro("P69_Score")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Bonus")
#undef P69_Bonus
#pragma push_macro("P69_Bonus") /*gvi*/
#undef P69_Bonus /*gvi*/
int32_t P69_Bonus;
#pragma pop_macro("P69_Bonus") /*gvi*/
#pragma pop_macro("P69_Bonus")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_ScoreCpy")
#undef P69_ScoreCpy
#pragma push_macro("P69_ScoreCpy") /*gvi*/
#undef P69_ScoreCpy /*gvi*/
int32_t P69_ScoreCpy;
#pragma pop_macro("P69_ScoreCpy") /*gvi*/
#pragma pop_macro("P69_ScoreCpy")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_BlendOn")
#undef P69_BlendOn
#pragma push_macro("P69_BlendOn") /*gvi*/
#undef P69_BlendOn /*gvi*/
uint8_t P69_BlendOn;
#pragma pop_macro("P69_BlendOn") /*gvi*/
#pragma pop_macro("P69_BlendOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_OvlOn")
#undef P69_OvlOn
#pragma push_macro("P69_OvlOn") /*gvi*/
#undef P69_OvlOn /*gvi*/
int32_t P69_OvlOn;
#pragma pop_macro("P69_OvlOn") /*gvi*/
#pragma pop_macro("P69_OvlOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_DevOn")
#undef P69_DevOn
#pragma push_macro("P69_DevOn") /*gvi*/
#undef P69_DevOn /*gvi*/
int32_t P69_DevOn;
#pragma pop_macro("P69_DevOn") /*gvi*/
#pragma pop_macro("P69_DevOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Thr")
#undef P69_Thr
#pragma push_macro("P69_Thr") /*gvi*/
#undef P69_Thr /*gvi*/
P69_ThrTab P69_Thr;
#pragma pop_macro("P69_Thr") /*gvi*/
#pragma pop_macro("P69_Thr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_Ptrs")
#undef P69_Ptrs
#pragma push_macro("P69_Ptrs") /*gvi*/
#undef P69_Ptrs /*gvi*/
P69_PtrTab P69_Ptrs;
#pragma pop_macro("P69_Ptrs") /*gvi*/
#pragma pop_macro("P69_Ptrs")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P69_PtsTab")
#undef P69_PtsTab
#pragma push_macro("P69_PtsTab") /*gvi*/
#undef P69_PtsTab /*gvi*/
P69_Pts P69_PtsTab;
#pragma pop_macro("P69_PtsTab") /*gvi*/
#pragma pop_macro("P69_PtsTab")
#endif

/* Glide export by decorated name, or NULL. */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

/* Languages of P55_Lang (from the message names below). */
enum { LANG_EN = 0, LANG_FR = 1, LANG_DE = 2, LANG_ES = 3, LANG_IT = 4, LANG_EN2 = 5 };
#define SCORE_BONUS_CODE 0xff00   /* P69_AddScore argument: cash in the accumulated bonus */
#define SCORE_MAX        999999
#define SCORE_NBRACKETS  0x12     /* 18 brackets; P69_Bracket returns 0x12 for "above all" */

/* 004a3630 */
/* P69_SetupMsgs — Game.exe 004a3630.  Looks up the models of the race messages "3", "2", "1" and GO / CHECKPOINT /
   FINISHED in the current language (EN for 0 and 5, FR uses EN for the first two); unknown language: GO etc.
   keep their old values.  Clears the 0x48-byte message block and sets the message width 0x8c. */
void P69_SetupMsgs(void) {
  P69_Num3 = (uint32_t)P20_FindNameValue("3");
  P69_Num2 = (uint32_t)P20_FindNameValue("2");
  P69_Num1 = (uint32_t)P20_FindNameValue("1");
  const char *go = NULL, *chk = NULL, *fin = NULL;
  switch (P55_Lang) {
  case LANG_EN: case LANG_EN2: go = "GO"; chk = "CHECKPOINT"; fin = "FINISHED"; break;
  case LANG_FR: go = "GO"; chk = "CHECKPOINT"; fin = "FR_TERMINE"; break;
  case LANG_DE: go = "GR_LOS"; chk = "GR_KONTROLLPUNKT"; fin = "GR_GESCHAFFT"; break;
  case LANG_ES: go = "SP_ADELANTE"; chk = "SP_PUNTO-DE-CONTROL"; fin = "SP_SE-ACABO"; break;
  case LANG_IT: go = "IT_VIA"; chk = "IT_POSTO-DI-CONTROLLO"; fin = "IT_FINE"; break;
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

/* Threshold table P69_Thr: the bracket start pointers P69_Ptrs are stored as Game.exe addresses (real in hook,
   the same numbers 0x01136940 + 4k in native); thr_idx maps such an address to its index k (79 entries), -1 if
   it is not one. */
/* Таблица порогов: указатели хранятся адресами (в hook — настоящими, в native — теми же числами 0x01136940+4k). */
static int thr_idx(uint32_t addr) {
  if (addr < P69_TBASE || ((addr - P69_TBASE) & 3) != 0) return -1;
  uint32_t k = (addr - P69_TBASE) >> 2;
  return k < 79 ? (int)k : -1;
}

/* 004a0cca */
/* P69_Bracket — Game.exe 004a0cca.  Score bracket of value v: walks the sorted threshold table, where bracket c
   starts at P69_Ptrs[c].  Returns the bracket whose run contains a threshold equal to v (or the first bracket
   whose next threshold exceeds v), 0x12 when v is above every threshold.  Faithful transcription of the
   original's pointer walk plus native bounds guards; TODO(RE): unsure what kind of value v is (a stunt
   measurement?). */
uint8_t P69_Bracket(uint32_t v) {
  uint8_t c = 0;            /* current bracket */
  uint32_t p = P69_TBASE;   /* address of the current threshold */
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
/* P69_AddScore — Game.exe 004a0d5f.  v == 0xff00: adds (P69_Bonus / 120) * 100 and clears the bonus; otherwise
   adds the points of v's bracket (P69_PtsTab).  Caps the score at 999999 and mirrors it into P69_ScoreCpy.
   Always returns 0. */
int32_t P69_AddScore(int32_t v) {
  if (v == SCORE_BONUS_CODE) {
    P69_Score += (P69_Bonus / 0x78) * 100;
    P69_Bonus = 0;
  } else {
    uint8_t b = P69_Bracket((uint32_t)v);
    if (b != SCORE_NBRACKETS) P69_Score += P69_PtsTab[b];
  }
  if (P69_Score > SCORE_MAX) P69_Score = SCORE_MAX;
  P69_ScoreCpy = P69_Score;
  return 0;
}

/* 004b3ddb */
/* P69_ReleaseOverlays — Game.exe 004b3ddb.  Restores Glide alpha blending to (ONE, ZERO, ONE, ZERO) if it was
   changed, and when overlays are on runs 004B33D8 for each of the 200 overlay entries (0x3c bytes at
   P12_0110b260) with flag 0x2 in +0x22.  TODO(RE): unsure what the overlay entries are. */
void P69_ReleaseOverlays(void) {
  if (P69_BlendOn != 0) {
    void (P69_STD *f)(int32_t, int32_t, int32_t, int32_t) = (void (P69_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaBlendFunction@16");
    if (f) f(4, 0, 4, 0);   /* GR_BLEND_ONE, GR_BLEND_ZERO, GR_BLEND_ONE, GR_BLEND_ZERO */
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

/* grFogMode(m): 0 = GR_FOG_DISABLE, 2 = TODO(RE): unsure (Glide 2 fog mode value 2). */
static void fog_mode(int32_t m) {
  void (P69_STD *f)(int32_t) = (void (P69_STD *)(int32_t))glide_proc("_grFogMode@4");
  if (f) f(m);
}

/* 004aaea6 */
/* P69_SceneFrame — Game.exe 004aaea6.  Draw sequence of one scene frame: 00426580(0); colour combine 4 set once
   (grColorCombine(3, 1, 0, 1, 0), remembered in G6_01270C34); 004C0C6F(1) when MenuVar553850; view matrix =
   transposed view; then 004B3E55, 004B2C4B, overlay release, 004BA443, and 004AAF3A / 004BA720 drawn with fog
   disabled when P26_FxD (fog switched back on afterwards).  TODO(RE): unsure what each pass draws. */
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
/* P69_FreeDevices — Game.exe 004246f0.  Shuts down the 3D device (00424858), frees the per-device buffers (pointer
   at +0x44 of each device name record, at most 16), marks Glide as not initialised and unloads glide2x.dll. */
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
/* P69_InitConsts — native only.  Fills the per-bracket points table (Game.exe .data 00551528). */
void P69_InitConsts(void) {
  static const int32_t pts[18] = {100,150,200,50,250,300,200,250,150,500,400,0,300,700,1000,200,95,175};
  memcpy(P69_PtsTab, pts, sizeof pts);
}
#endif
