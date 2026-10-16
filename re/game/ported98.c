/* v1.43: 30 функций — восстановлено из Game.exe по стандарту указателей v1.42 (см. ported98.h). */
#include "ported98.h"
#include "reptr.h"
#include "crt.h"
#include "engine.h"
#include "director.h"
#include "globalsets.h"
#include "smallfuncs2.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported22.h"
#include "ported23.h"
#include "ported24.h"
#include "ported26.h"
#include "ported27.h"
#include "ported28.h"
#include "ported29.h"
#include "ported32.h"
#include "ported33.h"
#include "ported34.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported52.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported67.h"
#include "ported71.h"
#include "ported73.h"
#include "ported74.h"
#include "ported76.h"
#include "ported79.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "unported.h"
#include "ported127.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
/* .data Game.exe (tools/gen_p98_data.py → p98_data.h) */
p98_credits_t P98_Credits = P98_CREDITS_INIT;
const p98_credh_t P98_CredH = P98_CREDH_INIT;
const p98_facenames_t P98_FaceNames = P98_FACES_INIT;
p98_faceblk_t P98_FaceBlk = P98_FACEBLK_INIT;
#endif
GAME_VAR_DEF(p98_faces_t, P98_Faces, 0x00b1ffa0)
GAME_VAR_DEF(int32_t, P98_FaceCur, 0x00b1ffb8)
GAME_VAR_DEF(p98_strtab2_t, P98_MisStr, 0x00c55280)
GAME_VAR_DEF(p98_gr1_fn, P98_GrD40, 0x01270d40)
GAME_VAR_DEF(int32_t, P98_IconN, 0x0110e4e8)
GAME_VAR_DEF(p98_iconidx_t, P98_IconIdx, 0x010ffa40)
GAME_VAR_DEF(p98_f3_t, P98_IconCol, 0x010fc9d8)
GAME_VAR_DEF(uint32_t, P98_SixRec, 0x01123260)
GAME_VAR_DEF(p98_six_t, P98_Six, 0x010ff900)
GAME_VAR_DEF(uint8_t, P98_DD70, 0x00d0dd70)
GAME_VAR_DEF(int16_t, P98_DDE4, 0x00d0dde4)
GAME_VAR_DEF(p98_b54_t, P98_TrafX, 0x011458e0)
GAME_VAR_DEF(uint32_t, P98_CamW, 0x00b1c27c)
GAME_VAR_DEF(float, P98_ScaleB, 0x01137300)
GAME_VAR_DEF(p98_f5_t, P98_CamQuat, 0x01137340)
GAME_VAR_DEF(p98_camrecs_t, P98_CamRecs, 0x00c4daa0)
GAME_VAR_DEF(uint32_t, P98_TgtW, 0x01136c7c)
GAME_VAR_DEF(int32_t, P98_FreeTurn, 0x01137364)
GAME_VAR_DEF(uint8_t, P98_KeyL, 0x00d04d0b)
GAME_VAR_DEF(uint8_t, P98_KeyR, 0x00d04d0c)
GAME_VAR_DEF(uint8_t, P98_KeyB, 0x00d04d0d)
GAME_VAR_DEF(uint8_t, P98_KeyMode, 0x00d04d10)
GAME_VAR_DEF(uint8_t, P98_KeyTgt, 0x00d04d11)
GAME_VAR_DEF(int32_t, P98_MrkOff, 0x00d02630)
GAME_VAR_DEF(int32_t, P98_MrkModel, 0x00d02638)
GAME_VAR_DEF(p98_f3_t, P98_MrkPos, 0x00d02670)
GAME_VAR_DEF(uint32_t, P98_MrkW, 0x00d0267c)
GAME_VAR_DEF(p98_f3_t, P98_MrkSrc, 0x00d02720)
GAME_VAR_DEF(p98_carmat_t, P98_CarMat, 0x01135060)
GAME_VAR_DEF(int32_t, P98_C824A0, 0x00c824a0)
GAME_VAR_DEF(int32_t, P98_ScrFirst, 0x00c80cc0)
GAME_VAR_DEF(int32_t, P98_ScrModel, 0x00c81114)
GAME_VAR_DEF(p98_i10_t, P98_Range, 0x00b87e60)
GAME_VAR_DEF(int32_t, P98_PartDist, 0x00c56704)
GAME_VAR_DEF(p98_f16_t, P98_PartPl, 0x00c56720)
GAME_VAR_DEF(p98_pix_t, P98_PixTab, 0x00601bc0)
GAME_VAR_DEF(p98_b410_t, P98_CarBufA, 0x00dbb040)
GAME_VAR_DEF(p98_b110_t, P98_CarTimer, 0x00dbb460)
GAME_VAR_DEF(p98_b45100_t, P98_CarOpsA, 0x00dbb580)
GAME_VAR_DEF(p98_b61c00_t, P98_CarOpsB, 0x0107c3e0)
GAME_VAR_DEF(p98_b27b600_t, P98_CarOpsC, 0x00e006c0)
GAME_VAR_DEF(p98_b708_t, P98_CarBufB, 0x0107bcc0)
GAME_VAR_DEF(p98_b44_t, P98_CarKind, 0x010de0c0)
GAME_VAR_DEF(p98_bf8_t, P98_CarBufC, 0x010de220)
GAME_VAR_DEF(uint8_t, P98_M4658, 0x00d04658)
GAME_VAR_DEF(uint8_t, P98_M38F7, 0x00d038f7)
GAME_VAR_DEF(int32_t, P98_M4A60, 0x00d04a60)
GAME_VAR_DEF(int32_t, P98_M478C, 0x00d0478c)
GAME_VAR_DEF(int32_t, P98_M4A4C, 0x00d04a4c)
GAME_VAR_DEF(int32_t, P98_M447C, 0x00d0447c)
GAME_VAR_DEF(int32_t, P98_M465C, 0x00d0465c)
GAME_VAR_DEF(int32_t, P98_M44C4, 0x00d044c4)
GAME_VAR_DEF(int32_t, P98_M446C, 0x00d0446c)
GAME_VAR_DEF(int32_t, P98_M4660, 0x00d04660)
GAME_VAR_DEF(int32_t, P98_M48E8, 0x00d048e8)
GAME_VAR_DEF(int32_t, P98_M4780, 0x00d04780)
GAME_VAR_DEF(int32_t, P98_M3580, 0x00d03580)
GAME_VAR_DEF(int32_t, P98_M4664, 0x00d04664)
GAME_VAR_DEF(int32_t, P98_M4474, 0x00d04474)
GAME_VAR_DEF(int32_t, P98_M4A5C, 0x00d04a5c)
GAME_VAR_DEF(int32_t, P98_M4A48, 0x00d04a48)
GAME_VAR_DEF(int32_t, P98_M390C, 0x00d0390c)
GAME_VAR_DEF(int32_t, P98_M4464, 0x00d04464)
GAME_VAR_DEF(int32_t, P98_M453C, 0x00d0453c)
GAME_VAR_DEF(int32_t, P98_M44D8, 0x00d044d8)
GAME_VAR_DEF(int32_t, P98_M48EC, 0x00d048ec)
GAME_VAR_DEF(int32_t, P98_M4460, 0x00d04460)
GAME_VAR_DEF(int32_t, P98_M4480, 0x00d04480)
GAME_VAR_DEF(int32_t, P98_M38F8, 0x00d038f8)
GAME_VAR_DEF(int32_t, P98_M4468, 0x00d04468)
GAME_VAR_DEF(int32_t, P98_M48F4, 0x00d048f4)
GAME_VAR_DEF(int32_t, P98_M4648, 0x00d04648)
GAME_VAR_DEF(int32_t, P98_M4644, 0x00d04644)
GAME_VAR_DEF(int32_t, P98_M4640, 0x00d04640)
GAME_VAR_DEF(p98_b148_t, P98_M47A0, 0x00d047a0)
GAME_VAR_DEF(p98_b148_t, P98_M4900, 0x00d04900)

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static uint32_t fbits(float f) { uint32_t v; memcpy(&v, &f, 4); return v; }
static int32_t fround(float v) { return (int32_t)lrintf(v); }                   /* fistp */
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static uint8_t *link(const uint8_t *field) { return (uint8_t *)re_rd_ptr(field); }
static int32_t dist8(int32_t dx, int32_t dz) { dx = iabs(dx); dz = iabs(dz); return dx < dz ? dz + dx / 2 : dx + dz / 2; }
static void cam_set(float x, float y, float z) { P44_CamX = x; P44_CamY = y; P44_CamZ = z;
#ifndef RE_HOOK_BUILD
  P59_VX = x; P59_VY = y; P59_VZ = z;   /* в native это разные переменные-псевдонимы 00b1c270.. */
#endif
}
/* освобождение блока игры: в native ещё и снять его адрес из реестра */
static void dfree(void *p) { if (p == NULL) return; re_ptr_unregister(p); DebugFree(p); }

/* ---- 004d8db4 / 004d8f30: DebugMalloc / DebugFree с таблицей выделений 00b203a0 {адрес, размер, адрес строки журнала} ---- */
static uint32_t reg_block(void *p, uint32_t n) {
#ifdef RE_HOOK_BUILD
  (void)n; return (uint32_t)(uintptr_t)p;
#else
  return re_ptr_register_dyn(p, n ? n : 1);
#endif
}
void *P98_DebugMalloc(int32_t size, const char *file, int32_t line) {
  char msg[128];
  snprintf(msg, sizeof msg, "File: %s (Line: %d)", file, line);
  uint8_t *p = (uint8_t *)g_malloc((size_t)(uint32_t)(size + 4));
  if (p == NULL) return NULL;   /* в оригинале memset/метка пишутся и при NULL */
  if (size != 0) P14_Fn0048DB65(p, (uint32_t)size);
  p[size] = 'N'; p[size + 1] = 'A'; p[size + 2] = 'I'; p[size + 3] = 'F';
  for (int32_t i = 0; i < 0x1000; i++) {
    uint32_t *e = &P27_MemTab[i * 3];
    if (e[0] != 0) continue;
    e[0] = reg_block(p, (uint32_t)size + 4);
    e[1] = (uint32_t)size;
    size_t n = strlen(msg) + 1;
    char *s = (char *)g_malloc(n);
    e[2] = s ? reg_block(s, (uint32_t)n) : 0;
    if (s != NULL) memcpy(s, msg, n);
    break;
  }
  P27_MemAllocated += size;
  G2_00B2C3A4 += size;
  if (G2_00B20394 < G2_00B2C3A4) G2_00B20394 = G2_00B2C3A4;
  return p;
}
void P98_DebugFree(void *p) {
  if (p == NULL) return;
  uint32_t key = re_addr(p);
  int32_t i;
  for (i = 0; i < 0x1000; i++) if (P27_MemTab[i * 3] == key) break;
  if (i < 0x1000) {   /* в оригинале при промахе читается/пишется запись 0x1000 (за таблицей) */
    uint32_t *e = &P27_MemTab[i * 3];
    if (e[2] != 0) { void *s = re_ptr(e[2]); re_ptr_unregister(s); g_free(s); }
    e[2] = 0;
    P27_MemFreed += (int32_t)e[1];
    G2_00B2C3A4 -= (int32_t)e[1];
    e[0] = 0;
  }
  re_ptr_unregister(p);
  g_free(p);
}

/* ---- 004d0102: освободить список скрипта 00d12408 (узлы 0x24, объекты 0x60, база +0x50) и модели событий ---- */
void P98_ScriptFreeAll(void) {
  uint8_t *n = P15_ListHead;
  P15_ListHead = NULL;
  while (n != NULL) {
    uint8_t *next = link(n + 0x20);
    uint8_t *o = link(n + 0x1c);
    while (o != NULL) {
      uint8_t *on = link(o + 0x58);
      if ((rd16(n) & 0x20) == 0) { dfree(link(o + 0x50)); wr32(o + 0x50, 0); }
      dfree(o);
      o = on;
    }
    dfree(n);
    n = next;
  }
  if (P28_EventCount != 0) {
    for (int32_t i = 0; i < P28_EventCount; i++) { P79_EventFree(re_ptr(P28_EventModels[i])); P28_EventModels[i] = 0; }
    P28_EventCount = 0;
  }
}

/* ---- 004a9850 / 004a9cd0: титры — y строк по высоте вида, лица PERSON1..3 ---- */
void P98_CreditsInit(void) {
  int32_t y = 0x1e0;
  for (int32_t i = 0; P98_Credits[i].kind != 8; i++) {
    P98_Credits[i].y = y;
    y += P98_CredH[P98_Credits[i].kind];
  }
  for (int32_t k = 0; k < 3; k++) {
    char name[12];
    P98_Faces[k].id = 0xffff; P98_Faces[k].page = 0xffff; P98_Faces[k].icon = 0;
    snprintf(name, sizeof name, "PERSON%d", k + 1);
    uint8_t *ic = P93_FindIcon(name);
    if (ic != NULL) P98_Faces[k].page = ic[8];
  }
  P98_FaceCur = 0;
  G00B1FFBC = 0;
}
int32_t P98_CreditsFace(uint8_t *rec) {
  for (int32_t k = 0; k < 3; k++) if ((uint16_t)rec[1] == P98_Faces[k].id) return 1;
  P98_FaceCur = (P98_FaceCur + 1) % 3;
  /* сравнение page с 0xffffffff в оригинале всегда ложно (xor eax,eax; mov ax,…) — проверки нет */
  p98_face_t *f = &P98_Faces[P98_FaceCur];
  f->id = rec[1];
  const char *name = NULL;
#ifndef RE_HOOK_BUILD
  if (rec[1] < P98_FACES_N)
#endif
    name = (const char *)re_ptr(P98_FaceNames[rec[1]]);
  uint8_t *ic = name ? P93_FindIcon(name) : NULL;
  f->icon = re_addr(ic);
  if (f->icon == 0) return 0;
  P12_Fn0048A46B((int32_t)f->page, rd32(&g_01145a60[(uint32_t)ic[8] * 0x10 + 4]));
  wr16(rec + 2, (uint16_t)P98_FaceCur);
  return 1;
}

/* ---- 004b4095: вывести накопленные значки (00c56804 + i*0xb4 → 004accf0) ---- */
void P98_IconFlush(void) {
  if (P94_IconRec == 0) { P98_IconN = 0; return; }
  float c = (float)((0xff - P14_00d17b18) * 0xff >> 8);
  P98_IconCol[0] = c; P98_IconCol[1] = c; P98_IconCol[2] = c;
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(0);
  P12_Fn00426580(0);
  int32_t mode = Call0042655A(0);
  while (P98_IconN != 0) {
    P98_IconN--;
    P98_Fn4ACCF0(0x00c56804u + (uint32_t)P98_IconIdx[P98_IconN] * 0xb4u, 100);
  }
  P98_IconN = 0;
  if (FnPtr01270E80 != NULL) ((p98_gr1_fn)FnPtr01270E80)(2);
  Call0042655A(mode);
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(2);
}

/* ---- 004ba720: шесть записей 0x30 (010ff900) текстурой значка *01123260 ---- */
void P98_DrawSix(void) {
  if (D_00b87e30 != 2) return;
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  const uint8_t *six = (const uint8_t *)re_ptr(P98_SixRec);
  if (six == NULL) return;   /* native: запись значка не задана */
  uint32_t t = six[8];
  if (t != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)t;
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[t * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[t * 0x10 + 0xc]));
  }
  if (P85_BlendCur != 4) { if (P85_BlendFn) P85_BlendFn(4, 6, 4, 0); P85_BlendCur = 4; }
  int32_t mode = Call0042655A(0);
  for (int32_t i = 0; i < 6; i++) P98_Fn4BA81F(P98_Six + i * 0x30);
  Call0042655A(mode);
}

/* ---- 0041e52c / 0041e729: четырёхугольник (4 вершины по 0x3c) как два треугольника 0-1-2, 0-2-3 в буфер слота ---- */
static plat_vertex *vslot(void) {
  int32_t s = P22_TexVarA;
  int32_t n = P33_Count[s]++;
  return (plat_vertex *)&P33_VBuf[s][n * 0x20];
}
void P98_QuadA(int32_t unused, const uint8_t *v) {
  (void)unused;
  if (P22_DevReady == 0) return;
  static const int32_t off[6] = { 0, 0x3c, 0x78, 0, 0x78, 0xb4 };
  for (int32_t i = 0; i < 6; i++) P23_ConvVertexA((const int32_t *)(const void *)(v + off[i]), vslot());
}
void P98_QuadB(int32_t unused, const uint8_t *v) {
  (void)unused;
  if (P22_DevReady == 0) return;
  static const int32_t off[6] = { 0, 0x3c, 0x78, 0, 0x78, 0xb4 };
  for (int32_t i = 0; i < 6; i++) P23_ConvVertexB((const int32_t *)(const void *)(v + off[i]), vslot());
}

/* ---- 004e49c0: сброс состояния миссии ---- */
void P98_ResetMission(void) {
  P98_M4658 = 0; P98_M38F7 = 0;
  P56_G4538 = 0; P98_M4A60 = 0; P98_M478C = 0; P98_M4A4C = 0; P98_M447C = 0; P56_D4470 = 0; P12_00d044d0 = 0;
  P98_M465C = 0; P98_M44C4 = 0; P59_S4654 = 0; G2_00D044C8 = 0; P98_M446C = 0; P98_M4660 = 0; P98_M48E8 = 0;
  P98_M4780 = 0; P98_M3580 = 0; P98_M4664 = 0; P98_M4474 = 0; P98_M4A5C = 0; P98_M4A48 = 0; P98_M390C = 0;
  P98_M4464 = 0; P98_M453C = 0; P94_FadeVal = 0; P94_FadeDir = 0; P94_FadePos = 0.0f; P94_FadeSpeed = 0.0f;
  P98_M44D8 = 0; P56_G3908 = 0; P44_Rst_B31EA0 = 0; P98_M48EC = 0; P98_M4460 = 0; P98_M4480 = 0; P98_M38F8 = 0;
  P59_S44CC = 0; P59_S4790 = 0; P59_S3904 = 0; P98_M4468 = 0; P98_M48F4 = 0;
  P98_M4648 = 0; P98_M4644 = P98_M4648; P98_M4640 = P98_M4644;
#ifndef RE_HOOK_BUILD
  G2_00D04654 = 0; G00D044C8 = 0; P59_Flags9[0] = 0; memset(P59_Flags9, 0, 9); memset(G6_00D04A50, 0, 9);   /* псевдонимы в native */
#endif
  P14_Fn0048DB65(P15_Flags9, 9);
  P14_Fn0048DB65(P98_M47A0, 0x148);
  P14_Fn0048DB65(P56_GhostBuf, 0xb40);
  P14_Fn0048DB65(A_00D044E0, 0x50);
  P14_Fn0048DB65(P15_Vals9, 0x24);
  P14_Fn0048DB65(P98_M4900, 0x148);
}

/* ---- 004911d9: поворот колёс/мигалок трафика (поле +0x16 записей 0x54); при 00b87eac/00b87eb0 — 0x41 запись ---- */
static uint8_t *trec(int32_t i) { return i < 0x40 ? &TrafficRecs[i * 0x54] : P98_TrafX; }
void P98_TrafficSpin(void) {
  uint8_t idx[0x44];
  uint32_t n = 0;
  if (P98_DD70 != 0) P98_DDE4 = (int16_t)((P98_DDE4 + 0x200) & 0xfff);
  int32_t cnt = (G6_00B87EAC == 0 && P58_SB87EB0 == 0) ? 0x40 : 0x41;
  for (int32_t i = 0; i < cnt; i++) {
    const uint8_t *r = trec(i);
    if (r[1] != 0 && ((r[0xc] == 1 && r[5] != 0 && r[1] == 4) || r[1] == 9)) idx[n++ & 0xff] = (uint8_t)i;
  }
  for (uint32_t k = 0; k < (n & 0xff); k++) {
    uint8_t *r = trec(idx[k]);
    float f = 1.0f;
    if (r[1] != 9) {
      uint32_t c = r[5];
      f = (c >= 1 && c <= 16) ? rdf(&P74_Cars[(c - 1) * 0xcd8 + 0x20]) : 0.0f;
    }
    int32_t s = (int16_t)rd16(r + 0x16);
    wr16(r + 0x16, (uint16_t)((s + (int32_t)((double)512.0f * f)) & 0xfff));
  }
}

/* ---- 004cb857: порядок 100 записей таблицы, значки SPLASH/RFLECT ---- */
void P98_InitSplash(uint8_t *tab) {
  for (int32_t i = 0; i < 100; i++) { wr32(tab + 4 + i * 4, i); wr16(tab + i * 0x34 + 0x1c6, (uint16_t)i); }
  wr32(tab, 0);
  G00D164EC = P93_FindIcon("SPLASH");
  uint8_t *s = G00D164EC;
  if (s != NULL) {
    s[9]++; s[10]++;
    s[0xb] = (uint8_t)(s[0xb] + s[9] - 1);
    s[0xc] = (uint8_t)(s[0xc] + s[10] - 1);
  }
  G00D14EF0 = P93_FindIcon("RFLECT");
  uint8_t *r = G00D14EF0;
  if (r != NULL) {
    r[0xb] = (uint8_t)(r[0xb] + r[9]);
    r[0xc] = (uint8_t)(r[0xc] + r[10]);
    G8_00D17B0C = 0;
  }
}

/* ---- 004c2042: обнулить данные машин игрока/трафика ---- */
void P98_ClearCarData(void) {
  P14_Fn0048DB65(P28_CarDelta, 0xc300);
  P14_Fn0048DB65(P98_CarOpsA, 0x45100);
  P14_Fn0048DB65(P98_CarOpsB, 0x61c00);
  P14_Fn0048DB65(P98_CarOpsC, 0x27b600);
  P14_Fn0048DB65(P28_CarClean, 0x30);
  P14_Fn0048DB65(P28_CarDam, 0x30);
  P14_Fn0048DB65(P28_CarLow, 0x30);
  P14_Fn0048DB65(P28_CarOpsSize, 0x30);
  P14_Fn0048DB65(P98_CarBufA, 0x410);
  P14_Fn0048DB65(P98_CarTimer, 0x110);
  P14_Fn0048DB65(P98_CarBufC, 0xf8);
  P14_Fn0048DB65(P95_DebRnd, 0x10);
  P14_Fn0048DB65(P28_Clear100, 0x100);
  P14_Fn0048DB65(P98_CarBufB, 0x708);
  P14_Fn0048DB65(P98_CarKind, 0x44);
#ifndef RE_HOOK_BUILD
  G010DE220 = 0;   /* псевдоним 010de220 */
#endif
  P95_Deb0 = 0;
  P95_Deb1 = 0;
  P28_DbgFlag = 0;
}

/* ---- 0049ec01: камера по ключам (записи 0x34): время — Hermite, позиция — Catmull-Rom, поворот — кватернион, масштаб ---- */
void P98_CamSpline(int32_t t, const uint8_t *k) {
  float tt = 0.0f, pos[4] = { 0, 0, 0, 0 }, q[5] = { 0, 0, 0, 0, 0 }, sc = 0.0f;
  P63_Hermite(t, &tt, rd32(k - 8), rd32(k + 0x2c), rd32(k + 0x60), rd32(k + 0x94));
  P63_CatmullRom(&tt, pos, (const float *)(const void *)(k - 0x34), (const float *)(const void *)k,
                 (const float *)(const void *)(k + 0x34), (const float *)(const void *)(k + 0x68));
  P73_CatmullRom(&tt, q, (const float *)(const void *)(k - 0x24), (const float *)(const void *)(k + 0x10),
                 (const float *)(const void *)(k + 0x44), (const float *)(const void *)(k + 0x78));
  P56_Spline(tt, &sc, rdf(k - 0x10), rdf(k + 0x24), rdf(k + 0x58), rdf(k + 0x8c));
  P44_QuatNormalize(q);
  P95_CamFromQuat(q);
  P43_ScaleA = sc;
  P98_ScaleB = sc;
  cam_set(pos[0], pos[1], pos[2]);
  P98_CamW = fbits(pos[3]);   /* в оригинале — неинициализированное слово стека */
  memcpy(P98_CamQuat, q, sizeof q);
}

/* ---- 0051763a: файл языка/миссии → таблица 0x15e адресов строк (00c55820 / 00c55280) ---- */
static const char k_lang_missing[] = "Lang.? missing!";
static const char k_mis_missing[] = "Mission.? missing!";
void P98_LoadLang(const char *name, int32_t mission) {
  int32_t size = 0;
  uint8_t *p = (uint8_t *)P55_LoadFileSize(name, &size);
  if (mission == 0) G6_00B5A840 = p; else G6_00B5A83C = p;
#ifndef RE_HOOK_BUILD
  if (p != NULL && size > 0) re_ptr_register_dyn(p, (uint32_t)size);   /* строки — внутри буфера файла */
#endif
  uint32_t *tab = mission == 0 ? P97_StrAddr : P98_MisStr;
  for (int32_t c = 0; c < 0x15e; c++) {
    if (size < 1) { tab[c] = re_addr(mission == 0 ? k_lang_missing : k_mis_missing); continue; }
    tab[c] = re_addr(p);
    uint8_t *last = p;
    do {
      if (*p == 10) break;
      if (*p > 0x1f) last = p + 1;
      size--; p++;
    } while (size > 1);
    *last = 0;
    p++; size--;
  }
}

/* ---- 004cb4ff: цвет фонарей (типы 4 и 5) в первых 4 моделях ---- */
void P98_LampColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int32_t k = 0; k < 4; k++) {
    if (P79_ModelTab[k] == 0) continue;
    uint8_t *m = (uint8_t *)P79_PTR(P79_ModelTab[k]);
    uint8_t *c = (uint8_t *)P79_PTR((uint32_t)rd32(m + 0x2c));
    for (uint32_t n = rd16(m + 0x16); n != 0; n--) {
      if (*c == 5) { wrf(c + 0x38, (float)r); wrf(c + 0x3c, (float)g); wrf(c + 0x40, (float)b); }
      if (*c == 4) { wrf(c + 0x2c, (float)r); wrf(c + 0x30, (float)g); wrf(c + 0x34, (float)b); }
      c += G2_TABLE_00550ACC[*c];
    }
  }
}

/* ---- 00519a45: добавить запись камеры повтора (0x28 байт, 00c4daa0) ---- */
static uint8_t *camrec(int32_t i) { return &P98_CamRecs[i * 0x28]; }
void P98_CamRecAdd(int8_t at_end) {
  if (G6_00B5A8A0 == 0x200) return;
#ifndef RE_HOOK_BUILD
  if (G6_00B5A8A0 < 0 || G6_00B5A8A0 >= 0x20f || P47_CamB >= 0x20f) return;
#endif
  if (at_end == 0 && G6_00B5A8A0 < P47_CamB)
    for (int32_t c = P47_CamB + 1; G6_00B5A8A0 < c; c--) memcpy(camrec(c), camrec(c - 1), 0x28);
  uint8_t *r = camrec(G6_00B5A8A0);
  if (at_end == 0) wr32(r, P62_Frame);
  r[4] = P59_Mode1137324;
  switch (P59_Mode1137324) {
  case 0:
  case 1:
    wrf(r + 8, P44_CamX); wrf(r + 0xc, P44_CamY); wrf(r + 0x10, P44_CamZ); wr32(r + 0x14, (int32_t)P98_CamW);
    wr32(r + 0x18, (int32_t)P59_AngA); wr32(r + 0x1c, (int32_t)P59_AngC);
    if (P59_Mode1137324 == 0) { wr32(r + 0x20, (int32_t)P61_Dist8); wr32(r + 0x24, P61_V18); }
    break;
  case 2:
    wr32(r + 0x20, P61_V10b);
    break;
  case 0x10:
  case 0x11:
    wrf(r + 8, P61_TgtX); wrf(r + 0xc, P61_TgtY); wrf(r + 0x10, P61_TgtZ); wr32(r + 0x14, (int32_t)P98_TgtW);
    if (P59_Mode1137324 == 0x10) { wr32(r + 0x18, (int32_t)P61_AngB8); wr32(r + 0x1c, (int32_t)P61_AngBC); }
    else { wr32(r + 0x18, (int32_t)P59_AngA); wr32(r + 0x1c, (int32_t)P59_AngC); }
    wr32(r + 0x20, P60_Var1373C0 & 1);
    break;
  default: break;
  }
  if (at_end == 0) P47_CamB++; else G6_00B5A8A0++;
  P52_ResetA = 1;
}

/* ---- 004ea346: маркер цели — модель P79_ModelTab[00d02638] в точке 00d02720 относительно игрока ---- */
void P98_DrawMarker(void) {
  if (P98_MrkOff != 0) return;
  float v[4] = { P98_MrkSrc[0], P98_MrkSrc[1] - 100.0f, P98_MrkSrc[2], 0.0f };
  P44_MatPtr = P98_MrkMat;
  P44_XformT(v);
  P98_MrkPos[0] = v[0] + (float)P59_PosX;
  P98_MrkPos[2] = v[2] + (float)P59_PosZ;
  P98_MrkW = fbits(v[3]);
  P98_MrkPos[1] = v[1] + (float)-P59_PosY + P95_Near;
  float d[3] = { P98_MrkPos[0] - P44_CamX, (v[1] + (float)-P59_PosY) - P44_CamY, P98_MrkPos[2] - P44_CamZ };
  P44_MatPtr = P44_ViewMatT;
  P44_Xform(d);
  P84_DrawModel(P79_ModelTab[P98_MrkModel], P98_MrkMat, d, 1);
}

/* ---- 004c32c1: камера режиссёра дальше 15000 от игрока — подтянуть ---- */
int32_t P98_CamClamp(int32_t *cam) {
  int32_t dx = iabs(P59_PosX - cam[0x13]), dz = iabs(P59_PosZ - cam[0x15]);
  if ((int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz) > 225000000) {
    if (cam[0] == 0) { cam[2] = 15000; cam[3] = 15000; }
    else if (cam[0] == 0x11 || cam[0] == 0x10) {
      int32_t a = P44_Atan2(cam[0x19] - P59_PosZ, cam[0x17] - P59_PosX) & 0xfff;
      cam[0x17] = (int32_t)((double)P43_Sin[a + 0x400] * 15000.0);
      cam[0x19] = (int32_t)((double)P43_Sin[a] * 15000.0);
      cam[0x17] += P59_PosX;
      cam[0x19] += P59_PosZ;
      cam[0x13] = cam[0x17]; cam[0x14] = cam[0x18]; cam[0x15] = cam[0x19]; cam[0x16] = cam[0x1a];
    }
  }
  return 1;
}

/* ---- 004c6740: следующая камера режиссёра (по id, иначе новая автокамера) ---- */
int32_t P98_DirCamNext(void **out) {
  DIRECTOR_CAMERA tmp;
  if (P98_C824A0 != 0) return 0;
  DIRECTOR_CAMERA *c = FindCameraById(DirectorUnk6C);
  if (c != NULL) { DirectorCam = *c; *out = c; return 1; }
  memset(&tmp, 0, sizeof tmp);
  if (CameraList == NULL) {
    P127_AutoCamera(&tmp);
    *out = AddDirectorCamera(&tmp, DirectorUnk6C < 4 ? 2 : DirectorUnk6C);
    return 1;
  }
  c = FindNearestCamera(DirectorUnk6C);
  WAYPOINT_REC *w = GetWaypointForFrame(DirectorUnk6C);
  if (w != NULL) {
    if (c != NULL && iabs(c->id - w->frame) < 0x96) return 0;
    if (DirectorUnk6C + 0x96 < DirectorLastFrame) {
      P127_AutoCamera(&tmp);
      *out = AddDirectorCamera(&tmp, DirectorUnk6C);
      return 1;
    }
  }
  return 0;
}

/* ---- 00514a47: направление частицы на игрока (+0x50 угол, +0x4c сила) ---- */
void P98_PartAim(int16_t *p) {
  uint8_t *b = (uint8_t *)p;
  int32_t lc = 0;
  wr16(b + 0x50, 0); wr16(b + 0x52, 0);
  if (P98_D078C8 != 0) lc = 10;
  float fx = rdf(b + 0x84) - (float)P59_PosX;
  float fz = rdf(b + 0x8c) - (float)P59_PosZ;
  P11_00ba52d0 = fround(fz * fz + fx * fx);
  int32_t q = P11_00ba52d0 / 0x5dc;
  if (q < 6) { if (q > 0) lc = lc / q; }
  else lc = 0;
  wr32(b + 0x4c, lc);
  P11_00ba52d0 = fround(fz);
  int32_t iz = P11_00ba52d0;
  P11_00ba52d0 = fround(fx);
  uint32_t u = (uint32_t)P44_Atan2(P11_00ba52d0, iz);
  u = (((uint32_t)((int32_t)(int16_t)rd16(b + 0x5e) - (int32_t)(u & 0xfff)) + 0x800) & 0xfff) - 0x800;
  wr32(b + 0x50, (int32_t)(u & 0xfff));
  if (rd32(b + 0x1c) == 1 || p[0] == 3) {
    if ((int32_t)u >= 0x349 || (int32_t)u < -0x348) { wr16(b + 0x50, 0); wr16(b + 0x52, 0); }
  } else { wr16(b + 0x50, 0); wr16(b + 0x52, 0); }
}

/* ---- 004fc3f4: модели меток скрипта (до 5 записей 0x14 с 00c80cc0) ---- */
void P98_DrawScriptModels(const uint8_t *recs) {
  if (!((P14_00c810c4 == 7 || P95_B87EDC != 0) && recs != NULL)) return;
  uint32_t m = P95_B87EDC == 0 ? P79_ModelTab[P98_ScrModel] : P79_ModelTab[0x1aa];   /* 00cfee48 */
  if (m == 0) return;
  const uint8_t *r = recs + P98_ScrFirst * 0x14;
  for (int32_t c = 0; c < 5 && c + P98_ScrFirst <= G6_00C81108; c++, r += 0x14) {
    float pos[3] = { (float)rd32(r + 4), (float)rd32(r + 8), (float)rd32(r + 0xc) };
    int32_t vis = P83_BoxVis(pos, rdf((const uint8_t *)P79_PTR(m) + 0xc));
    if (vis != 0 && P76_InBox(pos, (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) != 0) {
      float d[3] = { pos[0] - P44_CamX, pos[1] - P44_CamY, pos[2] - P44_CamZ };
      P44_Xform(d);
      P84_DrawModelIdx(m, 0, d, vis == 1 ? 0 : vis == 2 ? 1 : 2);
      P44_MatPtr = P44_ViewMatT;
    }
  }
}

/* ---- 004d7766: клавиши свободной камеры повтора ---- */
void P98_FreeCamKeys(void) {
  if (P29_Mode != 0) return;
  int32_t chg = 0;
  if (IsKeyDown(P98_KeyMode) != 0) {
    if (P59_Mode1137324 == 0) P59_Mode1137324 = 2;
    else if (P59_Mode1137324 == 2) P59_Mode1137324 = 8;
    else P59_Mode1137324 = 0;
    chg = 1;
  }
  if (P34_Keys[P98_KeyL] != 0) P98_FreeTurn = 0x4000000;
  else if (P34_Keys[P98_KeyR] != 0) P98_FreeTurn = -0x4000000;
  else if (P34_Keys[P98_KeyB] != 0) P98_FreeTurn = P98_FreeTurn < 1 ? -0x8000000 : 0x8000000;
  else P98_FreeTurn = 0;
  if (chg) {
    if (P59_Mode1137324 == 0) { P61_OffY = -256.0f; P61_Dist8 = 1280.0f; P61_V18 = 0x800; }
    else P61_V10b = 0;
  }
  if (IsKeyDown(P98_KeyTgt) != 0) {
    P61_TgtX = P44_CamX; P61_TgtY = P44_CamY; P61_TgtZ = P44_CamZ; P98_TgtW = P98_CamW;
    if (P59_Mode1137324 == 0x11) P60_Var1373C0 ^= 1;
    else { P59_Mode1137324 = 0x11; P60_Var1373C0 = 0; }
  }
}

/* ---- 005240d0: позиция/громкость голоса (слоты 0x34, 00bdc2a0) ---- */
void P98_VoicePos(int32_t voice, const int32_t *pos, int32_t a, int32_t vol) {
  if (G6_00B91CF4 == 0 || G00575F40 == 0) return;
  P48_Slot *s = &P48_Snd[voice];
  if ((s->flags & 0x11) == 0) return;
  if ((s->flags & 0x20) != 0) s->flags &= 0xdf;
  memcpy(s->data + 0xc, s->data, 12);                       /* +0x10.. ← +0x4.. (прежняя позиция) */
  wrf(s->data + 0, (float)pos[0]);
  wrf(s->data + 4, (float)-pos[1]);
  wrf(s->data + 8, (float)pos[2]);
  if (a == -1) a = rd32(s->data + 0x20);
  wr32(s->data + 0x24, a);
  if (vol == 0x7fff) vol = s->defVol;
  if (vol < -10000) vol = -10000;
  if (vol > 0) vol = 0;
  s->vol = (int16_t)vol;
  s->scaled = (int16_t)P48_VolTab[vol + 10000];
  s->flags |= 0xe;
}

/* ---- 0040cd6f: пункты текущего меню (записи 20 байт, конец — бит 4): текст 00407d56 или значок 0040cfdf ---- */
void P98_ItemsDraw(void) {
  int16_t *it = P58_ItemList;
  if (it == NULL) return;
  for (; (it[4] & 4) == 0; it += 10) {
    if ((it[4] & 8) != 0) continue;
    if ((it[4] & 1) == 0) {
      SndHelper_00407D56(it[0], it[1], re_addr(it + 7), (uint32_t)(int32_t)it[5], (uint32_t)(int32_t)it[6]);   /* 7 аргументов в оригинале, 00407d56 берёт 5 */
    } else {
      const char *name = (const char *)re_ptr((uint32_t)rd32(it + 2));
      if (name != NULL) P67_DrawIcon(it[0], it[1], (int32_t)re_addr(it + 7), name);
    }
  }
}

/* ---- 0048c5b7: найти в образе RIFF/WAVE блоки "fmt " и "data" ---- */
int32_t P98_RiffFind(const void *riff, const void **fmt, const void **data, uint32_t *size) {
  const uint8_t *b = (const uint8_t *)riff;
  if (fmt) *fmt = NULL;
  if (data) *data = NULL;
  if (size) *size = 0;
  int32_t len = rd32(b + 4);
  const uint8_t *c = b + 12;
  if ((uint32_t)rd32(b) != 0x46464952u || (uint32_t)rd32(b + 8) != 0x45564157u) return 0;
  while (c < b + len + 8) {
    uint32_t sz = (uint32_t)rd32(c + 4);
    const uint8_t *d = c + 8;
    uint32_t id = (uint32_t)rd32(c);
    if (id == 0x20746d66u) {
      if (fmt != NULL && *fmt == NULL) {
        if (sz < 0xe) return 0;
        *fmt = d;
        if ((data == NULL || *data != NULL) && (size == NULL || *size != 0)) return 1;
      }
    } else if (id == 0x61746164u && ((data != NULL && *data == NULL) || (size != NULL && *size == 0))) {
      if (data) *data = d;
      if (size) *size = sz;
      if (fmt == NULL || *fmt != NULL) return 1;
    }
    c = d + ((sz + 1) & ~1u);
  }
  return 0;
}

/* ---- 00421a80: таблица 0x10000 пикселей 1555 → формат поверхности (маски DevInfo +0x538..+0x544) ---- */
void P98_PixTabInit(void) {
  const uint8_t *d = P32_DevInfo;
  if (d == NULL) return;
  P24_RShiftR = MaskShift_00421C1D((uint32_t)rd32(d + 0x538)); P24_RShiftL = CountTrailingZeros00421C72((uint32_t)rd32(d + 0x538));
  P24_GShiftR = MaskShift_00421C1D((uint32_t)rd32(d + 0x53c)); P24_GShiftL = CountTrailingZeros00421C72((uint32_t)rd32(d + 0x53c));
  P24_BShiftR = MaskShift_00421C1D((uint32_t)rd32(d + 0x540)); P24_BShiftL = CountTrailingZeros00421C72((uint32_t)rd32(d + 0x540));
  if (rd32(d + 0x544) == 0) { P55_A4219C = 0x20; P55_A421A0 = 0; }
  else { P55_A4219C = MaskShift_00421C1D((uint32_t)rd32(d + 0x544)); P55_A421A0 = CountTrailingZeros00421C72((uint32_t)rd32(d + 0x544)); }
  for (uint32_t i = 0; i < 0x10000; i++) {
    int32_t a = (i & 0x8000) ? (0xff >> (P55_A4219C & 0x1f)) : 0;
    P98_PixTab[i] = (uint16_t)(((((int32_t)(i & 0x7c00) >> 7) >> (P24_RShiftR & 0x1f)) << (P24_RShiftL & 0x1f)) |
                               ((((int32_t)(i & 0x3e0) >> 2) >> (P24_GShiftR & 0x1f)) << (P24_GShiftL & 0x1f)) |
                               ((((int32_t)((i & 0x1f) << 3)) >> (P24_BShiftR & 0x1f)) << (P24_BShiftL & 0x1f)) |
                               (a << (P55_A421A0 & 0x1f)));
  }
}

/* ---- 004f5012: объекты скрипта дальше порога 00b87e60[k] — тревога (00c810c4=0xff0) ---- */
void P98_ScriptRange(void) {
  if (P97_ScrObjOn == 0) return;
  for (int32_t k = 0; k < 10; k++) {
    const uint8_t *o = P58_Objs[k];
    uint32_t f = (uint32_t)rd32(o + 0x10);
    if (P98_Range[k] == 0 || (f & 1) == 0 || (f & 8) == 0) continue;
    for (uint8_t *n = P15_ListHead; n != NULL; n = link(n + 0x20)) {
      if ((rd16(n) & 8) != 0 && (uint32_t)rd16(n + 6) == (uint32_t)rd32(o + 0xc)) {
        const uint8_t *c = link(n + 0x1c);
        if (c != NULL) {
          P11_00ba52d0 = fround(rdf(c));
          int32_t dx = P59_PosX - P11_00ba52d0;
          P11_00ba52d0 = fround(rdf(c + 8));
          int32_t dz = P59_PosZ - P11_00ba52d0;
          if (P98_Range[k] < dist8(dx, dz)) { P14_00c810c4 = 0xff0; P14_00c810e8 = 3; P14_00c81100 = 0x5a; }
        }
        break;
      }
    }
  }
}

/* ---- 0051564f: частица задела игрока — запуск эффекта и звука ---- */
static void part_hit(uint8_t *b) { P62_ParticleInit(b, P56_Objs); P95_SndTrigger(P97_D11980, 1, 0x1000); }
void P98_PartCheck(int16_t *p) {
  uint8_t *b = (uint8_t *)p;
  uint32_t f = (uint32_t)rd32(b + 0xc);
  if ((f & 0x80) != 0 || rd32(b + 0x1c) == 3 || (f & 0x800) != 0) return;
  int32_t free_ = 1;
  if (p[0] == 3) {
    P11_00ba52d0 = fround(rdf(b + 0x8c));
    int32_t z = P11_00ba52d0;
    P11_00ba52d0 = fround(rdf(b + 0x84));
    if (FindSlot_004A2DB5(P11_00ba52d0, z) != 0) free_ = 0;
  }
  if (!free_) { part_hit(b); return; }
  P11_00ba52d0 = fround(rdf(b + 0x84));
  int32_t dx = P11_00ba52d0 - P59_PosX;
  P11_00ba52d0 = fround(rdf(b + 0x8c));
  int32_t dz = P11_00ba52d0 - P59_PosZ;
  if (dist8(dx, dz) <= P98_PartDist && P71_InPlanes(b, P98_PartPl) != 0) part_hit(b);
}

/* ---- 004c2b9a: клавиши камеры режиссёра (поворот DirectorCam+0x7c, высота +0x60) ---- */
void P98_DirCamKeys(uint32_t k) {
  uint8_t *c = (uint8_t *)&DirectorCam;
  if ((k & 0x10) == 0) P29_Flag94 = 0;
  else if (P29_Flag94 == 0) { SetDirectorMode(0xc, DirectorUnk7C, 0); return; }
  uint16_t lo = rd16(c + 0x7c), hi = rd16(c + 0x7e);
  if (k & 1) hi = (uint16_t)(hi + 0x14);
  if (k & 2) hi = (uint16_t)(hi - 0x14);
  if (k & 4) lo = (uint16_t)(lo + 0x14);
  if (k & 8) lo = (uint16_t)(lo - 0x14);
  if (k & 0x100) lo = 0;
  if (k & 0x20) wr32(c + 0x60, rd32(c + 0x60) - 0x28);
  if (k & 0x40) wr32(c + 0x60, rd32(c + 0x60) + 0x28);
  lo &= 0xfff; hi &= 0xfff;
  if (lo > 0x3ff && lo < 0x800) lo = 0x400;
  if (lo > 0x7ff && lo < 0xc00) lo = 0xc00;
  wr16(c + 0x7c, lo); wr16(c + 0x7e, hi);
  wr32(c + 0x18, (int16_t)hi);
  wr32(c + 0x20, (int16_t)lo);
  wr32(c + 0x1c, (int16_t)hi);
  ClampCameraHeight((int32_t *)(void *)&DirectorCam);
}
