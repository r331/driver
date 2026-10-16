#include <stdio.h>
#include "ported151.h"
#include "ported55.h"
#include "ported116.h"
#include "ported87.h"
#include "ported27.h"
#include "ported30.h"
#include "ported48.h"
#include "ported51.h"
#include "crt.h"
#include <string.h>

GAME_VAR_DEF(int32_t, P55_CntA, 0x00cf2f88)
GAME_VAR_DEF(p55_tabA_t, P55_TabA, 0x00ce0f40)
GAME_VAR_DEF(int32_t, P55_CntB, 0x00d022e4)
GAME_VAR_DEF(p55_tabB_t, P55_TabB, 0x00d00260)
GAME_VAR_DEF(int32_t, P55_Flag38C, 0x00b1c38c)
GAME_VAR_DEF(int32_t, P55_VarC0, 0x00cff9c0)
GAME_VAR_DEF(int32_t, P55_Var20, 0x00c97a20)
GAME_VAR_DEF(int32_t, P55_VarD2C, 0x00d0022c)
GAME_VAR_DEF(int32_t, P55_VarD28, 0x00d00228)
GAME_VAR_DEF(int32_t, P55_VarD24, 0x00d00224)
GAME_VAR_DEF(int32_t, P55_VarD20, 0x00d00220)
GAME_VAR_DEF(uint8_t, P55_VarC6, 0x00cff9c6)
GAME_VAR_DEF(const char *, P55_DefName, 0x00c55854)
GAME_VAR_DEF(p55_flags8_t, P55_FlagsC, 0x00b5a428)
GAME_VAR_DEF(int32_t, P55_PopCnt, 0x00b2c3b0)
GAME_VAR_DEF(p55_pop_t, P55_PopTab, 0x00d10e80)
GAME_VAR_DEF(int32_t, P55_PopSkip, 0x00b87ecc)
GAME_VAR_DEF(int32_t, P55_PopB2AC, 0x00b2c3ac)
GAME_VAR_DEF(p55_frustum_t, P55_Frustum, 0x00cb8f20)
GAME_VAR_DEF(int32_t, P55_A4219C, 0x00a4219c)
GAME_VAR_DEF(int32_t, P55_A421A0, 0x00a421a0)
GAME_VAR_DEF(uint8_t *, P55_RecBase, 0x00b5a8bc)
GAME_VAR_DEF(int32_t, P55_RecCnt, 0x00b5a8c0)
GAME_VAR_DEF(int32_t, P55_V57B6FC, 0x0057b6fc)
GAME_VAR_DEF(int32_t, P55_V1285428, 0x01285428)
GAME_VAR_DEF(int32_t, P55_V1285424, 0x01285424)
GAME_VAR_DEF(int32_t, P55_BDFA18, 0x00bdfa18)
GAME_VAR_DEF(p55_glide_t, P55_GlideInfo, 0x00bdfa80)
GAME_VAR_DEF(int32_t, P55_B87EB8, 0x00b87eb8)
GAME_VAR_DEF(int32_t, P55_Paper0, 0x00d03900)
GAME_VAR_DEF(int32_t, P55_Paper1, 0x00d0448c)
GAME_VAR_DEF(int32_t, P55_Paper2, 0x00d038fc)
GAME_VAR_DEF(int32_t, P55_Lang, 0x00c557fc)

#define P55_FILE_C "D:\\Driver\\Game\\file.c"

void P55_RunTableA(void) {
  if (P55_CntA == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  /* Ограничение размером таблицы — защита от мусорного счётчика (в оригинале его нет). */
  int32_t n = P55_CntA;
  if (n < 0 || n > 1106) n = 1106;
  for (int32_t i = 0; i < n; i++) if (P55_TabA[i]) P87_DrawObjA((const uint8_t *)P55_TabA[i]);   /* пустой элемент — охранная проверка */
}

void P55_RunTableB(void) {
  if (P55_CntB == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t n = P55_CntB;
  P55_Flag38C = 2;
  if (n < 0 || n > 2081) n = 2081;
  for (int32_t i = 0; i < n; i++) if (P55_TabB[i]) P87_DrawObjA((const uint8_t *)P55_TabB[i]);
  P55_Flag38C = 0;
}

void P55_ResetSel(void) {
  P55_VarC0 = -1; P55_Var20 = -1;
  P55_VarD2C = -1; P55_VarD28 = -1; P55_VarD24 = -1; P55_VarD20 = -1;
  P55_Fn4ED5F8(P12_00cff9ac, (int32_t)P55_VarC6);
  P55_Fn4EDAA2();
}

/* Общий разбор «имя слота i или имя по умолчанию». Копия ограничена размером записи (stride-1 символ + 0). */
static void p55_names(uint8_t *names, int stride, int32_t *flags, int bufsz, int use405fdb) {
  uint8_t buf[32];
  for (int32_t i = 0; i < 8; i++) {
    memset(buf, 0, sizeof buf);
    int32_t r = use405fdb ? P55_Fn405FDB(i, buf) : P55_Fn405E79(i, buf);
    uint8_t *dst = names + i * stride;
    const char *src = r == 0 ? P55_DefName : (const char *)buf;
    (void)bufsz;
    if (src == NULL) src = "";
    size_t n = strnlen(src, (size_t)(stride - 1));
    memcpy(dst, src, n);
    memset(dst + n, 0, (size_t)stride - n);
    flags[i] = r != 0;
  }
}

void P55_NamesA(void) { p55_names((uint8_t *)P12_005fe7a8 + 0x20, 0x10, P12_005fe7a8, 20, 0); }
void P55_NamesB(void) { p55_names((uint8_t *)P12_005fe884 + 0x20, 0x10, P12_005fe884, 32, 1); }
void P55_NamesC(void) { p55_names((uint8_t *)P12_005fee60, 0x11, P12_005fee40, 20, 0); }
void P55_NamesD(void) { p55_names((uint8_t *)P52_NameTab, 0x11, P55_FlagsC, 16, 1); }

void P55_PopDeferred(void) {
  while (P55_PopCnt != 0) {
    P55_PopCnt = P55_PopCnt - 1;
    uint32_t i = (uint32_t)P55_PopCnt;
    if (i >= 146) { P55_PopCnt = 0; break; }   /* защита от мусорного счётчика */
    WH00B2C3A8 = P55_PopTab[i].w;
    G6_00D117A4 = (int32_t)P55_PopTab[i].x;
    G6_00D117A8 = (int32_t)P55_PopTab[i].y;
    if (P55_PopSkip == 0) P55_Fn4D92D2(P55_PopTab[i].id);
  }
  G6_00D117A8 = 0;
  G6_00D117A4 = 0;
  P55_PopB2AC = 0;
}

int32_t P55_LoadFrustum(void) {
  void *f = g_fopen("FRUSTRUM.DAT", "rb");
  if (f == NULL) return -1;
  int32_t n;
  P27_ReadChunked(&n, 4, 1, f);
  for (n = 0; n < 0x100; n++) P27_ReadChunked(P55_Frustum + n * 0x80, 1, 0x80, f);
  g_fclose(f);
  return 0;
}

void P55_FillDevInfo(uint32_t *out) {
  out[0] = (uint32_t)P24_RShiftR; out[1] = (uint32_t)P24_RShiftL;
  out[2] = (uint32_t)P24_GShiftR; out[3] = (uint32_t)P24_GShiftL;
  out[4] = (uint32_t)P24_BShiftR; out[5] = (uint32_t)P24_BShiftL;
  out[6] = (uint32_t)P55_A4219C;  out[7] = (uint32_t)P55_A421A0;
  out[8] = (uint32_t)G6_00A421F0;
  out[10] = 0x00601bc0u;
  out[9] = P23_DevCaps;
}

void P55_GlideDevInfo(uint32_t *out) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    out[0] = 3; out[1] = 10; out[2] = 3; out[3] = 5; out[4] = 3; out[5] = 0;
    out[8] = 0; out[9] = 0xffffffffu; out[10] = 0;
  } else if (D_00b1c0d8 == 1) {
    P55_FillDevInfo(out);
  }
}

void *P55_LoadFile(const char *name) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return NULL;
  int32_t size = P51_FileSize(f);
  if (size != 0) {
    void *buf = DebugMalloc(size, P55_FILE_C, 0x86);
    if (buf != NULL && (P27_ReadChunked(buf, size, 1, f) & 0xff) != 0) { g_fclose(f); return buf; }
  }
  g_fclose(f);
  return NULL;
}

void *P55_LoadFileSize(const char *name, int32_t *size) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return NULL;
  *size = P51_FileSize(f);
  if (*size != 0) {
    void *buf = DebugMalloc(*size, P55_FILE_C, 0xb1);
    if (buf != NULL && (P27_ReadChunked(buf, *size, 1, f) & 0xff) != 0) { g_fclose(f); return buf; }
  }
  g_fclose(f);
  return NULL;
}

void P55_SaveRec(int32_t idx) {
  if (P55_RecBase == NULL || P55_RecCnt >= 0x800) return;
  uint8_t *p = P55_RecBase + (size_t)P55_RecCnt * 0x1a4;
  uint32_t t = (uint32_t)G8_00D118C0, i = (uint32_t)idx;
  memcpy(p, &t, 4);
  memcpy(p + 4, &i, 4);
  memcpy(p + 8, (uint8_t *)TrafficRecs + (size_t)idx * 0x54, 0x54);
  memcpy(p + 0x5c, G0113A6C4 + (size_t)idx * 0x148, 0x148);
  P55_RecCnt = P55_RecCnt + 1;
}

int32_t P55_NextPad(void) {
  int32_t n = Q0057B72C;
  Q0057B72C = n + 1;
  if (P36_SelectJoystick(n) == 0) {
    Q0057B72C = 0;
    memcpy(P36_KeyCfg, (uint8_t *)P54_KeySrc + 24, 20);
  } else {
    memcpy(P36_KeyCfg, (uint8_t *)P54_KeySrc, 20);
    if (Q00B87EF0 != 0) Q00B87EF0 = Q00B31E2C;
  }
  Call004072BE();
  return 0;
}

void P55_StopAudio(void) {
  G6_00B5A778 = 0;
  G6_00B87EFC = 0;
  if (P29_Mode != 0) return;
  G00B5A730 = 0;
  if (G6_00B87E20 == 0) {
    Call005237B1();
    if (Q00B87E90 != 0) { Call00524873(); Call00524763(); }
  } else {
    Call005243EB();
    if (Q00B87E90 != 0) P55_Fn5248CD();
  }
  if (P55_B87EB8 != 0 && GameMode == 0) P47_Fn405BFA();
}

#ifndef RE_HOOK_BUILD
#include <stdlib.h>
#define TRACE_GI(...) do { if (getenv("RE_TRACE")) { fprintf(stderr, "[trace] GlideInit: " __VA_ARGS__); fputc('\n', stderr); } } while (0)
#else
#define TRACE_GI(...) ((void)0)
#endif
void P55_GlideInit(int32_t a, int32_t b, int32_t mode) {
  (void)a; (void)b;
  P55_Fn424530(P55_V57B6FC, P55_V1285428, P55_V1285424);
  TRACE_GI("devsel idx=%d devcount=%d ok=%d kind_d3d=%d", (int)P55_V57B6FC, (int)P42_DevCount, (int)G00B1C0D8, (int)G00B1C0D8);
  if (P48_GlideCheck() == 0) { TRACE_GI("GlideCheck=0"); return; }
  P55_BDFA18 = P55_Fn4245E2() == 0;
  P31_WindowMode = mode != 1;
  if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) != 0) G6_00B87E20 = 1;
  TRACE_GI("Reopen -> b87e20=%d", (int)G6_00B87E20);
  P55_GlideDevInfo(P55_GlideInfo);
}

int32_t P55_SetScreen(int32_t w, int32_t h) {
  int32_t oldW = P19_ScrW, oldH = P19_ScrH;
  P55_Fn4264A7();
  P19_ScrW = w; P19_ScrH = h;
  if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) == 0) {
    P19_ScrH = oldH; P19_ScrW = oldW;
    if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) == 0)
      P30_FatalError("FATAL: Can't allocate 3D hardware");
  }
  return 1;
}

void P55_MenuLangCall(void) {
  int32_t lang = -1;
  if (MenuI005D578C == 0x1c) lang = 0;
  if (MenuI005D578C == 0x1d) lang = 1;
  if (MenuI005D578C == 0x1e) lang = 2;
  if (MenuI005D578C == 0x1f) lang = 3;
  if (MenuI005D578C == 0x20) lang = 4;
  P116_Sliders5(p116_f(P55_A680), p116_f(P55_A688), p116_f(P55_A68C), p116_f(P55_A684), p116_f(P55_A690), lang);
}

void P55_LoadPaper(void) {
  P55_Paper0 = Call004EC91E("ELPAPEL");
  P55_Paper1 = Call004EC91E("LINE");
  P55_Paper2 = Call004EC91E("CROSS");
  switch (P55_Lang) {
  case 1: P55_Fn4E7450(P55_Paper0, "PAPER_FR"); break;
  case 2: P55_Fn4E7450(P55_Paper0, "PAPER_GE"); break;
  case 3: P55_Fn4E7450(P55_Paper0, "PAPER_SP"); break;
  case 4: P55_Fn4E7450(P55_Paper0, "PAPER_IT"); break;
  }
  memset(G6_00D04A50, 0, 9 * 4);
}
