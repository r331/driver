/* ported121 — mission HUD messages, camera/event script line parser, flat-coloured textured model records, dust
   particles, near/far-plane clipped polygons, player wheel dust, sound device cycling, traffic-slot position sync
   and per-tick camera sounds (Game.exe, all cdecl).  The Russian list below gives each function's address.
   Original note: */
/* v1.66: ported121 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004f4a33 — сообщения миссии по P56_Blk84[1] == 0xff0 и режиму P56_Blk84[10] (переменные скрипта P42_Vars), часы записи P113_MrkRec;
   004a4a5f — разбор строки сценария камеры (32 команды, .data 00551c30/00551b72/00551bb0 — таблицы в модуле);
   00431016 — запись модели 0x44: текстурный четырёхугольник, цвет записи без освещения;
   004b2c4b — частицы пыли P96_Dust (значки P96_DustOn/P96_SparkOn, альфа-тест);
   00447753 / 0043a5be — четырёхугольник с отсечением дальней (P100_ClipFar) / ближней с UV (P101_ClipNearUV) плоскостью,
                         вершины — P121_ClipBuf (01159f80), веер 3..5 вершин;
   0051dc18 — пыль из-под колёс игрока (004b955c, P102_Corners);
   00415014 — переключение звукового устройства (005233be), банк TITLE/MOTEL.DSS;
   004a7d80 — позиция машины → запись копа P12_0112da00 (шаг 0x336 слов), 004a706a в свой кадр;
   004d602e — такт звуков у камеры. */
#include "aspect.h"
#include "ported140.h"
#include "ported128.h"
#include "ported121.h"
#ifndef RE_HOOK_BUILD
#include "../platform/native/diagnostics.h"
#endif
#include "cartab.h"
#include "unported.h"
#include "ported125.h"   /* P125_ObjABurst (004b955c) */
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported21.h"
#include "ported26.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported51.h"
#include "ported53.h"
#include "ported56.h"
#include "ported59.h"
#include "ported62.h"
#include "ported74.h"
#include "ported75.h"
#include "ported79.h"
#include "ported82.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported88.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported113.h"
#include "ported116.h"
#include "ported120.h"
#include "reptr.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P121_ClipBuf")
#undef P121_ClipBuf
#pragma push_macro("P121_ClipBuf") /*gvi*/
#undef P121_ClipBuf /*gvi*/
p121_clipbuf_t P121_ClipBuf;
#pragma pop_macro("P121_ClipBuf") /*gvi*/
#pragma pop_macro("P121_ClipBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P121_CamW")
#undef P121_CamW
#pragma push_macro("P121_CamW") /*gvi*/
#undef P121_CamW /*gvi*/
uint32_t P121_CamW;
#pragma pop_macro("P121_CamW") /*gvi*/
#pragma pop_macro("P121_CamW")
#endif

#include "memrw.h"
#include "carfields.h"
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }

/* 1/w for view depth z from the RE_OOW table (native: 0 out of range). */
static float oow_at(float z) {
  long zi = lrintf(z);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (long)(RE_OOW_N)) return 0.0f;
#endif
  return RE_OOW(zi);
}
/* Selects texture page tex unless already current. */
static void tex_page(uint32_t tex) {
  if (tex != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)tex;
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&P12_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&P12_01145a60[tex * 0x10 + 0xc]));
  }
}
static void raster_b(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }

/* ---- 004f4a33 ---- */
/* Script variable index of fail message name; also stops the speech sample playing in slot (slot -> -1). */
static int32_t fail_msg(const char *name, int32_t slot) {
  int32_t v = P42_FindVar(name);
  if (P47_Slots[slot] != -1) MenuClick004F8ACC(P47_Slots[slot] + 0xf000);
  P47_Slots[slot] = -1;
  return v;
}
/* Mission end reasons in P56_Blk84[10] (= P16_IdleArg1, 00c810e8) when the mission failed (P56_Blk84[1] == 0xff0). */
enum { FAIL_GENERIC = 1, FAIL_SMASHED = 2, FAIL_OUTOFRANGE = 3, FAIL_CARGOTAWAY = 4 };

/* P121_ScriptHud — Game.exe 004f4a33.  Mission HUD text: debug info, the stopwatch of the marker record (flag 4), and
   either the fail message for the end reason (script variables FAILEDMESSAGE, SMASHEDMESSAGE, OUTOFRANGEMESSAGE,
   CARGOTAWAYMESSAGE) or the regular script messages; when nothing was shown and a camera delay runs, the line at
   00c81168; then the banner.  Only when script objects are on. */
void P121_ScriptHud(void) {
  uint32_t rec = P113_MrkRec;
  int32_t shown = 0;
  if (P97_ScrObjOn == 0) return;
  P120_DebugInfo();
  P12_Fn00426580(0x18);
  SetRGB00516EB4(0xff, 0xff, 0xff);
  if (rec != 0) {
    const uint8_t *r = (const uint8_t *)re_ptr(rec);
    if (r != NULL && (rd32(r + 4) & 4) != 0) P96_ClockText(r);
  }
  if ((int32_t)P56_Blk84[1] == 0xff0) {   /* 00c810c4: mission failed */
    int32_t v;
    switch ((int32_t)P56_Blk84[10]) {     /* 00c810e8 */
    case FAIL_GENERIC: v = fail_msg("FAILEDMESSAGE", 0); break;
    case FAIL_SMASHED: v = fail_msg("SMASHEDMESSAGE", 1); break;
    case FAIL_OUTOFRANGE: v = fail_msg("OUTOFRANGEMESSAGE", 2); break;
    case FAIL_CARGOTAWAY: v = fail_msg("CARGOTAWAYMESSAGE", 3); break;
    default: v = -1;
    }
#ifndef RE_HOOK_BUILD
    if (v >= 77) v = -1;
#endif
    if (v > -1 && P42_Vars[v].addr != 0) {
      DrawTextLine004FBBC5((int32_t)P42_Vars[v].addr);
      shown = 1;
    }
  } else {
    shown = P99_ScriptMsgs();
  }
  if (shown == 0 && P99_CamDelay != 0) DrawTextLine004FBBC5((int32_t)re_addr((uint8_t *)P56_Blk84 + 0xa8));   /* 00c81168 */
  DrawBanner_004F5D98();
}

/* ---- 004a4a5f ---- */
static const char *const k_cmd[33] = {   /* .data 00551c30 */
  "", "TRIGGER_RADIUS", "TRIGGER_CELL", "TRIGGER_VALUE", "SET_MODEL", "SET_ROTATION", "MODEL_TARGET", "TARGET_PLAYER",
  "MODEL_MOVETO", "MODEL_MOVE", "MODEL_STOP", "MODEL_VELOCITY", "MODEL_SLOW", "MODEL_SPEED", "MODEL_WAIT", "MODEL_DESTROY",
  "TERMINATE_EVENT", "SEND_MESSAGE", "ADD_MODEL", "DO", "LOOP", "LOOP", "TRIGGER", "PLAY_SOUND", "STOPBOX", "MOVEFORWARD",
  "TURNTOTARGET", "WAITFORTARGET", "TRIGNEXT", "MODEL_TURN", "MODEL_SPEEDCURVE", "MODEL_ROTATE", "COLLISIONSOFF" };
static const int16_t k_argc[33] = {   /* .data 00551b72 + 2*u */
  0, 3, 2, 1, 4, 3, 3, 0, 3, 4, 0, 1, 2, 2, 1, 0, 0, 2, 4, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 2, 5, 3, 0 };
static const char *const k_fmt[33] = {   /* .data 00551bb0 + 4*u (пустые строки — .bss 00b1ff6c..) */
  "", "fff", "ii", "i", "ifff", "iii", "fff", "", "fff", "ffff", "", "f", "ff", "ff", "i", "", "", "ii", "ifff", "", "", "i",
  "i", "i", "ii", "", "", "", "i", "fi", "iffff", "iii", "" };
/* Result of P121_ParseCamLine for a comment line. */
#define CAMLINE_COMMENT 0x32

/* P121_ParseCamLine — Game.exe 004a4a5f.  Parses one line of an event script (the "camera scenario" of the original
   port note; the keywords are the event-script commands TRIGGER_RADIUS .. COLLISIONSOFF): keyword -> command 1..32,
   then its arguments by format ('f' float, 'i' integer, comma-separated) into the argument buffers.  Returns the
   command, 0x32 for a comment line (# or //), 0 on an unknown keyword or a syntax error (reported for missing
   commas and junk after the arguments).  The first matching keyword wins (both LOOP entries -> 20). */
uint16_t P121_ParseCamLine(char *s) {
  if (*s == '#' || (s[0] == '/' && s[1] == '/')) return CAMLINE_COMMENT;
  uint16_t u = 0;   /* command */
  for (int32_t k = 0; k < 0x20; k++)
    if (P21_MatchPrefix((const uint8_t *)s, (const uint8_t *)k_cmd[k + 1]) != 0) { u = (uint16_t)(k + 1); break; }
  if (u == 0) return 0;
  s += strlen(k_cmd[u]);
  if (k_argc[u] == 0) return u;
  int32_t sp = 0;
  for (; *s == ' '; s++) sp++;
  if (sp == 0 && *s != '\0') return 0;
  int32_t nf = 0, ni = 0;   /* float / integer arguments parsed */
  const char *f = k_fmt[u];
  for (;;) {
    if (*f == '\0') return u;
    char c = *f++;
    if (c == 'f') { P74_ParseFloat(s, nf); P51_SkipNumber(&s); nf++; }
    else if (c == 'i') { P120_ParseCamInt(&s, ni, (int32_t)u); P15_SkipInteger(&s); ni++; }
    if (*f == '\0') break;
    for (; *s == ' '; s++) {}
    c = *s++;
    if (c != ',') { P26_ErrorInLine("Expecting comma (,)."); return 0; }
    for (; *s == ' '; s++) {}
  }
  for (; *s == ' '; s++) {}
  for (;;) {
    if (*s == '\n' || *s == '#') return u;
    if (s[0] == '/' && s[1] == '/') return u;
    if (*s != '\t' && *s != ' ' && *s != '\n' && *s != '\r') break;
    s++;
  }
  P26_ErrorInLine("Junk at end of line!");
  return 0;
}

/* ---- 00431016 ---- */
/* P121_TexQuadFlat — Game.exe 00431016.  Model record 0x44 bytes: textured quad with the record's own colour (no
   lighting): +2 texture page, +8..+0x14 vertex indices, +0x18..+0x34 four (u, v) pairs, +0x38 r, g, b floats.
   Drawn as triangles (0, 2, 1) and (0, 2, 3); arg = blend mode.  Advances the record pointer. */
void P121_TexQuadFlat(uint32_t arg) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = rd32(rec + 8), i1 = rd32(rec + 0xc), i2 = rd32(rec + 0x10), i3 = rd32(rec + 0x14);
  G2_011F4064 = (uint8_t *)rec + 0x44;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)i0 >= 0x2000u || (uint32_t)i1 >= 0x2000u || (uint32_t)i2 >= 0x2000u || (uint32_t)i3 >= 0x2000u) return;
#endif
  p85_vtx *v0 = P85_Prep(i0), *v1 = P85_Prep(i1), *v2 = P85_Prep(i2), *v3 = P85_Prep(i3);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v0, v1, v2, v3 }; if (P85_EdgeReject(vs, 4)) return; }
  for (int i = 0; i < 3; i++) { P85_RV[i].r = rdf(rec + 0x38); P85_RV[i].g = rdf(rec + 0x3c); P85_RV[i].b = rdf(rec + 0x40); }
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  tex_page(rec[2]);
  if (P85_BlendFn) P85_SetBlend((uint8_t)arg);
  P85_RV[0].tmu[0] = rdf(rec + 0x18) * v0->oow; P85_RV[0].tmu[1] = rdf(rec + 0x1c) * v0->oow;
  P85_RV[2].tmu[0] = rdf(rec + 0x20) * v1->oow; P85_RV[2].tmu[1] = rdf(rec + 0x24) * v1->oow;
  P85_RV[1].tmu[0] = rdf(rec + 0x28) * v2->oow; P85_RV[1].tmu[1] = rdf(rec + 0x2c) * v2->oow;
  P85_PutVtx(&P85_RV[0], v0); P85_PutVtx(&P85_RV[1], v2); P85_PutVtx(&P85_RV[2], v1);
  if (P85_RasterA && P85_RasterB) P85_CallRaster();
  P85_RV[2].tmu[0] = rdf(rec + 0x30) * v3->oow; P85_RV[2].tmu[1] = rdf(rec + 0x34) * v3->oow;
  P85_PutVtx(&P85_RV[2], v3);
  if (P85_RasterA && P85_RasterB) P85_CallRaster();
}

/* ---- 00430b13 (v2.20): запись модели 0x38 (тип 4/36) — текстурный треугольник с цветом записи, без освещения.
   Треугольный вариант 00431016 (Ghidra функцией не опознала — по дизассемблеру): индексы +8/+0xc/+0x10, uv +0x14..+0x28
   (вершины 0, 1, 2), цвет +0x2c/+0x30/+0x34; порядок вершин растеризатора — 0, 1, 2 (у четырёхугольника 0, 2, 1). ---- */
/* P121_TexTriFlat — Game.exe 00430b13.  Triangle variant (record 0x38 bytes; see the note above). */
void P121_TexTriFlat(uint32_t arg) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = rd32(rec + 8), i1 = rd32(rec + 0xc), i2 = rd32(rec + 0x10);
  G2_011F4064 = (uint8_t *)rec + 0x38;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)i0 >= 0x2000u || (uint32_t)i1 >= 0x2000u || (uint32_t)i2 >= 0x2000u) return;
#endif
  p85_vtx *v0 = P85_Prep(i0), *v1 = P85_Prep(i1), *v2 = P85_Prep(i2);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[3] = { v0, v1, v2 }; if (P85_EdgeReject(vs, 3)) return; }
  for (int i = 0; i < 3; i++) { P85_RV[i].r = rdf(rec + 0x2c); P85_RV[i].g = rdf(rec + 0x30); P85_RV[i].b = rdf(rec + 0x34); }
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  tex_page(rec[2]);
  if (P85_BlendFn) P85_SetBlend((uint8_t)arg);
  P85_RV[0].tmu[0] = rdf(rec + 0x14) * v0->oow; P85_RV[0].tmu[1] = rdf(rec + 0x18) * v0->oow;
  P85_RV[1].tmu[0] = rdf(rec + 0x1c) * v1->oow; P85_RV[1].tmu[1] = rdf(rec + 0x20) * v1->oow;
  P85_RV[2].tmu[0] = rdf(rec + 0x24) * v2->oow; P85_RV[2].tmu[1] = rdf(rec + 0x28) * v2->oow;
  P85_PutVtx(&P85_RV[0], v0); P85_PutVtx(&P85_RV[1], v1); P85_PutVtx(&P85_RV[2], v2);
  if (P85_RasterA && P85_RasterB) P85_CallRaster();
}

/* ---- 004b2c4b ---- */
/* Restores alpha combine / depth function after sprite drawing (state cached in P62_I252B78). */
static void dust_end(void) {
  if (P62_I252B78 != 0) {
    if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1);
    if (P97_GrDepth) P97_GrDepth(7);
    P62_I252B78 = 0;
  }
}
/* P121_DustDraw — Game.exe 004b2c4b.  Draws the live dust particles (0x24-byte records like the particles of ported16:
   +0 position, +0x20 life, +0x22 frame) as 80x40 sprites (frame < 4: SWBIRD2 icon, else SWBIRD1 — TODO(RE): the
   icon names suggest birds; unsure).  A particle outside 224 .. far / 2 is killed and drawing stops for this frame
   (the original returns there). */
void P121_DustDraw(void) {
  if (P62_I252B78 != 1) {
    if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 1, 1);
    if (P97_GrDepth) P97_GrDepth(4);
    P62_I252B78 = 1;
  }
  uint8_t *e = P96_Dust;
  for (int32_t n = P96_DustN; n != 0; n--, e += 0x24) {
#ifndef RE_HOOK_BUILD
    if (e + 0x24 > P96_Dust + sizeof P96_Dust) break;
#endif
    if (rd16s(e + 0x20) <= 0) continue;
    float v[3] = { (rdf(e) - P44_CamX) - 40.0f, (rdf(e + 4) - P44_CamY) - 40.0f, rdf(e + 8) - P44_CamZ };
    P44_Xform(v);
    if (v[2] <= 224.0f || P11_01270c24 / 2.0f <= v[2]) { wr16(e + 0x20, 0); dust_end(); return; }
    float x1 = v[0] + 40.0f, y0 = v[1] - 40.0f, y1 = v[1], x0 = v[0] - 40.0f, x3 = v[0] - 40.0f;
    if (P84_Mirror != 0) { x0 = -x0; x1 = -x1; x3 = -x3; }
    float oow = oow_at(v[2]), k = P43_ScaleA * oow;
    p85_rv q[4];
    memset(q, 0, sizeof q);
    const float xs[4] = { x0, x1, x1, x3 }, ys[4] = { y0, y0, y1, y1 };
    for (int i = 0; i < 4; i++) {
      q[i].x = (xs[i] * k + P43_OffX) - P43_Half;
      q[i].y = (ys[i] * k + P43_OffY) - P43_Half;
      q[i].r = 255.0f; q[i].g = 255.0f; q[i].b = 255.0f;
      q[i].oow = oow;
    }
    uint32_t ia = (uint32_t)(rd16s(e + 0x22) < 4 ? P96_DustOn : P96_SparkOn);
    const uint8_t *ic = (const uint8_t *)re_ptr(ia);
#ifndef RE_HOOK_BUILD
    if (ic == NULL) continue;
#endif
    tex_page(ic[8]);
    const uint8_t U[4] = { ic[9], ic[0xb], ic[0xb], ic[9] }, V[4] = { ic[10], ic[10], ic[0xc], ic[0xc] };
    for (int i = 0; i < 4; i++) { q[i].tmu[0] = (float)U[i] * oow; q[i].tmu[1] = (float)V[i] * oow; }
    if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; }
    raster_b(&q[0], &q[1], &q[2]);
    raster_b(&q[0], &q[2], &q[3]);
  }
  dust_end();
}

/* ---- 00447753 / 0043a5be: четырёхугольник с отсечением плоскостью ---- */
/* Cached view-space vertex idx of the current model, transformed with the biased matrix (P44_XformBias). */
static p85_vtx *prep_bias(int32_t idx) {
  p85_vtx *c = &P85_VCache[idx];
  if (!P85_VC_VALID(c, P85_FMT_PROJ)) {
    const float *src = (const float *)((const uint8_t *)P79_PTR(P84_VertRef) + (size_t)idx * 16);
    c->x = src[0]; c->y = src[1]; c->z = src[2];
    P44_XformBias((float *)(void *)c);
    P85_VC_FMT(c, P85_FMT_BIAS);
  }
  return c;
}
/* Trivial screen reject using sign bits: 1 when all vertices are left of / above the screen (AND of sign bits) or all
   right of / below it (OR of sign bits of x - max is clear).  Leaves the mask in P85_Clip.  Hor+ widens x by the
   extra side margin. */
static int clip_reject(const float *xs, const float *ys, int n) {
  uint32_t a = 0x80000000u;
#ifndef RE_HOOK_BUILD
  const float ex = (float)re_view_extra();   /* v2.15 Hor+: экран по x — [−S, 639 + S] */
  if (ex > 0.0f) {
    for (int i = 0; i < n; i++) a &= fbits(xs[i] + ex);
    P85_Clip = a; if (a) return 1;
    a = 0x80000000u;
    for (int i = 0; i < n; i++) a &= fbits(ys[i]);
    P85_Clip = a; if (a) return 1;
    uint32_t o = 0;
    for (int i = 0; i < n; i++) o |= fbits(xs[i] - (P85_MaxX + ex));
    P85_Clip = o; if (o == 0) return 1;
    o = 0;
    for (int i = 0; i < n; i++) o |= fbits(ys[i] - P85_MaxY);
    P85_Clip = o; if (o == 0) return 1;
    return 0;
  }
#endif
  for (int i = 0; i < n; i++) a &= fbits(xs[i]);
  P85_Clip = a; if (a) return 1;
  a = 0x80000000u;
  for (int i = 0; i < n; i++) a &= fbits(ys[i]);
  P85_Clip = a; if (a) return 1;
  uint32_t o = 0;
  for (int i = 0; i < n; i++) o |= fbits(xs[i] - P85_MaxX);
  P85_Clip = o; if (o == 0) return 1;
  o = 0;
  for (int i = 0; i < n; i++) o |= fbits(ys[i] - P85_MaxY);
  P85_Clip = o; if (o == 0) return 1;
  return 0;
}
/* nv = 4 — четырёхугольник (0x24 однотонный / 0x44 текстурный: uv +0x18, цвет +0x18 / +0x38);
   nv = 3 — 00439b42 (v2.20): текстурный треугольник 0x38 (тип 4 набора с ближней плоскостью 00550cfc+0x1c0): индексы +8..+0x10,
   uv +0x14..+0x28, цвет +0x2c; та же схема — отсечение рёбер 0x401514 (P101_ClipNearUV), 3 вершины — (0,1,2), 4 — (0,2,1),(0,2,3).
   До v2.20 вместо него стоял обработчик без отсечения: у полигонов неба/земли, пересекающих ближнюю плоскость, — пропуски. */
/* Shared body of the clipped polygon handlers: clip the nv-gon against the plane into P121_ClipBuf (3..5 vertices),
   project, reject, then draw as a triangle fan.  tex = textured (near plane, UVs) vs flat (far plane). */
static void clip_poly(uint32_t arg, int tex, int nv) {
  const uint8_t *rec = G2_011F4064;
  int32_t ix[4] = { rd32(rec + 8), rd32(rec + 0xc), rd32(rec + 0x10), nv == 4 ? rd32(rec + 0x14) : 0 };
  const int uvo = nv == 4 ? 0x18 : 0x14;
  G2_011F4064 = (uint8_t *)rec + (nv == 3 ? 0x38 : tex ? 0x44 : 0x24);
#ifndef RE_HOOK_BUILD
  for (int i = 0; i < nv; i++) if ((uint32_t)ix[i] >= 0x2000u) return;
#endif
  p85_vtx *v[4];
  for (int i = 0; i < nv; i++) v[i] = prep_bias(ix[i]);
  P100_ClipN = 0;
  P100_ClipOut = &P121_ClipBuf[0];
  for (int i = 0; i < nv; i++) {
    const int j = (i + 1) % nv;
    const uint8_t *a = (const uint8_t *)v[i], *b = (const uint8_t *)v[j];
    if (tex) {
      const float *ua = (const float *)(rec + uvo + 8 * i), *ub = (const float *)(rec + uvo + 8 * j);
      P101_ClipNearUV(a, b, rdf(ua), rdf(ua + 1), rdf(ub), rdf(ub + 1));
    } else P100_ClipFar(a, b);
  }
  int32_t n = P100_ClipN;
  if (n < 3 || n > 5) {
#ifndef RE_HOOK_BUILD
    re_diag_count(RE_DIAG_POLY_EMPTY);
#endif
    return;
  }
  float xs[5], ys[5], ow[5];
  for (int32_t i = 0; i < n; i++) {
    const float *o = &P121_ClipBuf[i * 12];
    ow[i] = oow_at(o[2]);
    if (!tex && i >= 3) { float k = ow[i] * P43_ScaleA; xs[i] = (o[0] * k + P43_OffX) - P43_Half; ys[i] = (o[1] * k + P43_OffY) - P43_Half; }
    else { xs[i] = (o[0] * ow[i] * P43_ScaleA + P43_OffX) - P43_Half; ys[i] = (o[1] * ow[i] * P43_ScaleA + P43_OffY) - P43_Half; }
  }
  if ((n < 5 || (uint8_t)P82_Edge != 0) && clip_reject(xs, ys, n)) return;
  if (tex) {
    if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
    tex_page(rec[2]);
  } else if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendFn) P85_SetBlend((uint8_t)arg);
  const uint8_t *col = rec + (nv == 3 ? 0x2c : tex ? 0x38 : 0x18);
  for (int i = 0; i < 3; i++) { P85_RV[i].r = rdf(col); P85_RV[i].g = rdf(col + 4); P85_RV[i].b = rdf(col + 8); }
  /* веер: 3 — (0,1,2); 4 — (0,2,1),(0,2,3); 5 — ещё (0,4,3) */
  static const int8_t fan[3][3] = { { 0, 2, 1 }, { 0, 2, 3 }, { 0, 4, 3 } };
  int32_t ntri = n - 2;
  for (int32_t t = 0; t < ntri; t++) {
    const int8_t *f = (n == 3) ? (const int8_t[3]){ 0, 1, 2 } : fan[t];
    for (int j = 0; j < 3; j++) {
      int32_t i = f[j];
      P85_RV[j].x = xs[i]; P85_RV[j].y = ys[i]; P85_RV[j].oow = ow[i];
#ifndef RE_HOOK_BUILD
      const float *camera = &P121_ClipBuf[i * 12];
      P85_NoteCameraPoint(j, camera[0], camera[1], camera[2]);
#endif
      if (tex) { const float *o = &P121_ClipBuf[i * 12]; P85_RV[j].tmu[0] = o[4] * ow[i]; P85_RV[j].tmu[1] = o[5] * ow[i]; }
    }
    raster_b(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
  }
}
/* 00447753 / 0043a5be / 00439b42 — see clip_poly. */
void P121_ClipQuad(uint32_t arg) { clip_poly(arg, 0, 4); }
void P121_ClipTexQuad(uint32_t arg) { clip_poly(arg, 1, 4); }
void P121_ClipTexTri(uint32_t arg) { clip_poly(arg, 1, 3); }

/* ---- 0051dc18 ---- */
/* P121_WheelDust — Game.exe 0051dc18.  Kicks up dust behind the player's wheels 0 and 2 while CAR_BURNOUT is set (16
   particles each): for a wheel whose neighbour wheel (k - 1) & 3 reports surface 0, only P102_5624A4 = 1;
   otherwise emits from the body corner k (raised by 0x32) with the car's velocity / 4096 and an upward speed
   of 16 * -0x27a.  TODO(RE): unsure — the surface byte indexing (k - 1) & 3 is kept literally. */
void P121_WheelDust(void) {
  const uint8_t *c = (const uint8_t *)&P99_Cars[0];
  int32_t n = (rd32(c + CAR_BURNOUT) != 0) ? 0x10 : 0;   /* 00d078c8 */
  if (n == 0) return;
  for (int32_t k = 0; k < 4; k++) {
    if (k != 0 && k != 2) continue;
    if (c[CAR_WHEEL + WHEEL_SURFACE + ((uint32_t)(k - 1) & 3) * CAR_WHEEL_SIZE] == 0) { P102_5624A4 = 1; continue; }   /* 00d0783a */
    P102_5624A4 = 0;
    int32_t a[4] = { P102_Corners[k * 4], P102_Corners[k * 4 + 1] - 0x32, P102_Corners[k * 4 + 2], P102_Corners[k * 4 + 3] };
    int32_t b[3] = { rd32(c + CAR_VEL) / 0x1000, n * -0x27a, rd32(c + CAR_VEL + 8) / 0x1000 };   /* 00d07800 / 00d07808 */
    P125_ObjABurst(a, b, n, 2);
  }
}

/* ---- 00415014 ---- */
/* P121_SndNextDev — Game.exe 00415014.  Settings menu: switches to the next sound device that initialises (wrapping;
   device 0 when there is only one), then reloads the sound bank (TITLE.DSS, or MOTEL.DSS when G6_00B87EEC) and
   refreshes the menu (00414D1F).  Returns 0. */
int32_t P121_SndNextDev(void) {
  if (G6_00B91D2C == 0) return 0;
  G6Call00523628();
  int32_t start = P12_00b87e58, k = start;
  if (G6_00B91D2C == 1) {
    P12_00b87e58 = 0;
    Call00523595();
    P140_SndInit(P12_00b87e58, P12_00b87e5c, P12_00575f50);
  } else {
#ifndef RE_HOOK_BUILD
    int32_t guard = G6_00B91D2C + 1;
#endif
    for (;;) {
      k++;
      if (k == start) break;
      if (G6_00B91D2C <= k) k = 0;
      Call00523595();
      if (P140_SndInit(k, P12_00b87e5c, P12_00575f50) != 0) break;
#ifndef RE_HOOK_BUILD
      if (--guard <= 0) break;   /* native: заглушка 005233be всегда 0 — без выхода по кругу при start ≥ числа устройств */
#endif
    }
    P12_00b87e58 = k;
  }
  if (G6_00B87EEC == 0) { Call00524496(0x54dea4, 0); Call0052360D(0); }   /* "TITLE.DSS" */
  else { Call00524496(0x54de98, 0); Call0052360D(5); }                     /* "MOTEL.DSS" */
  Call00414D1F();
  return 0;
}

/* ---- 004a7d80 ---- */
/* P121_CopSync — Game.exe 004a7d80.  Copies the position (x, z), speed and heading of traffic record p's car into its
   car object slot (0xcd8 bytes = 0x336 words at P12_0112da00, slot p[5] - 1) and refreshes its map position every 8th
   frame (staggered by slot).  When the wanted level is above 0x2a9 and chase ambience is active the record is put
   into state 4 (TODO(RE): unsure — pursuit?) and nothing is copied. */
void P121_CopSync(uint8_t *p) {
  if (0x2a9 < G2_00D11A5C && 0 < P95_AmbN) p[1] = 4;
  if (p[1] == 4) return;
  int32_t i = (int32_t)p[5] - 1;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 8) return;
#endif
  uint32_t *r = &P12_0112da00[i * 0x336];
  const uint8_t *base = P59_CarsTab;
#ifndef RE_HOOK_BUILD
  if (base == NULL) base = (const uint8_t *)&P99_Cars[1];
  if (p[0] >= P99_CARS_N - 1) return;
#endif
  const uint8_t *car = base + (uint32_t)p[0] * 0x148;
  r[0x319] = (uint32_t)rd32(car + CAR_POS_X);    /* 0112e664 */
  r[0x31b] = (uint32_t)rd32(car + CAR_POS_Z);    /* 0112e66c */
  r[0xa] = (uint32_t)rd32(car + CAR_SPEED);      /* 0112da28 */
  r[3] = (uint32_t)rd32(car + CAR_HEADING);      /* 0112da0c */
  r[0x32f] = 0;                            /* 0112e6bc */
  if (P62_Frame % 8 == (int32_t)p[5] - 1) {
    int32_t a = 0, b = 0;
    P128_CopMapPos(r, &a, &b, 1);
  }
}

/* ---- 004d602e ---- */
/* P121_CamSounds — Game.exe 004d602e.  Per-tick sound update around the camera: switches the ambience bank (1 / 6)
   when the camera enters or leaves a model zone (P128_ModelHit), engine revs / car voice for the player (0x41 =
   all cars?) depending on game state, traffic sounds, bounds, loops and the pitch-jitter sample. */
void P121_CamSounds(void) {
  int32_t r = P128_ModelHit(P44_CamX, P44_CamY, P44_CamZ, P121_CamW);
  if (r == 0) { if (P116_SndB2035C != 0) Call0052360D(1); }
  else if (P116_SndB2035C == 0) Call0052360D(6);
  P116_SndB2035C = r;
  if (G6_00B87EAC != 0 || G6_00B87EB0 != 0) P100_CarRevs(0x41);
  if (G6_00B87EA0 == 0 || P88_Mode575 != 0) { P100_CarRevs(0); P75_CarVoice(0, 0, 1); }
  else P75_CarVoice(0x41, 0, 1);
  if (G6_00B87EAC == 0 || G6_00B87EB0 != 0) P101_TrafficSounds();
  P53_StepBounds();
  P56_LoopUpdate();
  P51_PitchJitterSfx();
}
