/* ported138.c — car shadows, mission loading, replay config / pads loading and the trail recorder end
   (English overview; original notes follow). */
/* v1.83: ported138 — см. ported138.h.
   00520278 — тень машины car: нет значка CARSHAD/00d11880 = 0 или машина над дорогой с флагом 0x80 — выход (метка 01270c20 + 1);
     в повторе (00b87ea0) машина 1 не рисуется, цвет 255 (при 00b20300 — 128). При 00575f20 = 0 (или ровной машине-трафике: |Δy| углов
     < 10) — один четырёхугольник по 4 углам +0x88/+0x98/+0xb8/+0xa8 записи (позиция − камера, y = −10 − камера − y), вершины 0..3
     P85_VCache, uv из P96_ShadUV; дальше 45000 по z — выход; ближе 50 — 0043a5be(2), иначе проекция + 00431016(2).
     Иначе сетка (5×6 для трафика, 8×10 для игрока/повтора) по рельефу 004dcb62, uv по ячейкам, grDepthBiasLevel(−0x300) на время.
     Зеркало (00bdc288): матрица 011effa0 со сменой знака [0], [3], [6] во временной копии.
   004f4180 — загрузка миссии n: сброс переменных/списков/скрипта; n = 0 — имя .LEV в 00c81780, EVENTSCRIPT ← .DES города; иначе
     Scripts\Missions\Mission%d.dms → 004f4596 (0/4/10 — успех: ролик 0048a940(00bdf9c0, 00c814e0, 00c814e4), 00c81270 = 1).
   00517d58 — ReplayData\User\name.CFG (иначе Demo, 00c4da54 = 1): 0x88 байт в 00c54ee0, поля → переменные игры, PADS/CAMS-имена,
     004c9ca0/004c9310; тип повтора +0 (0 — свободный, 1 — миссия, 2 — погоня с 00b87eb0 = 1).
   005181da — PADS погони (P56_PathPads) в буфер 1, LEADER (P56_PathLeader) в запись 0x41, PINGS (0xd2000); при 00c54b00 ≠ 0 — PADS
     игрока (00c4d680) в буфер 0 и запись игрока (P56_PathPlayer), иначе 0051879f.
   0051879f — буфер записи 0x40000 (00b5a854); в погоне — PINGS-буфер 0xd2000 и LEADER в запись 0x41; 005186ce, 00d1187c = 0x20, 00519a45(0).
   00518bbc — без 00b87eb0: PADS игрока из 00c4d680 в буфер 0, сброс счётчиков повтора.
   004fbfad — в TRAIL-файл 00c812f0 пишется 0x7fffffff, файл закрывается, TRAIL.DAT читается заново (int, затем тройки до y = −1);
     тройка с z = 0x7fffffff — в лог z предыдущей и y текущей и позиция игрока, иначе «Trail Not Recorded».
   Отступления native: 00520278 — запись 0x44 b5c7e0 собирается в модуле (страница/цвет из P96_*, индексы пишутся и в P96_ShadIdx);
     машина вне 0..65 — выход; 005181da/0051879f/00518bbc/00517d58 — отсутствующий файл не читается, число PINGS ≤ 0x800, буферы — адреса
     re_ptr_register_dyn в P100_RecPtr; 004fbfad — файл 00c812f0 в native не открыт (как P120), прочитанный TRAIL.DAT хранится в модуле;
     004f4180 — P77_LevelName — родной указатель на P138_LevBuf, обнуление 00c810c0..00c812d0 обновляет и native-псевдонимы внутри. */
#include "ported150.h"
#include "ported139.h"
#include "ported138.h"
#include <string.h>
#include <stdio.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "engine.h"
#include "director.h"
#include "directorstorage.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "globalsets.h"
#include "uihandlers.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "menustate.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported9.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported26.h"
#include "ported33.h"
#include "ported36.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported51.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported65.h"
#include "ported72.h"
#include "ported74.h"
#include "ported77.h"
#include "ported79.h"
#include "ported82.h"
#include "ported84.h"
#include "ported85.h"
#include "ported88.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported109.h"
#include "ported113.h"
#include "ported120.h"
#include "ported121.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported127.h"
#include "ported129.h"
#include "ported136.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_B5A8CC")
#undef P138_B5A8CC
#pragma push_macro("P138_B5A8CC") /*gvi*/
#undef P138_B5A8CC /*gvi*/
int32_t P138_B5A8CC;
#pragma pop_macro("P138_B5A8CC") /*gvi*/
#pragma pop_macro("P138_B5A8CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_C80954")
#undef P138_C80954
#pragma push_macro("P138_C80954") /*gvi*/
#undef P138_C80954 /*gvi*/
int32_t P138_C80954;
#pragma pop_macro("P138_C80954") /*gvi*/
#pragma pop_macro("P138_C80954")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_C80F40")
#undef P138_C80F40
#pragma push_macro("P138_C80F40") /*gvi*/
#undef P138_C80F40 /*gvi*/
int32_t P138_C80F40;
#pragma pop_macro("P138_C80F40") /*gvi*/
#pragma pop_macro("P138_C80F40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_C80F7C")
#undef P138_C80F7C
#pragma push_macro("P138_C80F7C") /*gvi*/
#undef P138_C80F7C /*gvi*/
int32_t P138_C80F7C;
#pragma pop_macro("P138_C80F7C") /*gvi*/
#pragma pop_macro("P138_C80F7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_C8168C")
#undef P138_C8168C
#pragma push_macro("P138_C8168C") /*gvi*/
#undef P138_C8168C /*gvi*/
int32_t P138_C8168C;
#pragma pop_macro("P138_C8168C") /*gvi*/
#pragma pop_macro("P138_C8168C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_LevBuf")
#undef P138_LevBuf
#pragma push_macro("P138_LevBuf") /*gvi*/
#undef P138_LevBuf /*gvi*/
p138_s100_t P138_LevBuf;
#pragma pop_macro("P138_LevBuf") /*gvi*/
#pragma pop_macro("P138_LevBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_PadsPath")
#undef P138_PadsPath
#pragma push_macro("P138_PadsPath") /*gvi*/
#undef P138_PadsPath /*gvi*/
p138_s40_t P138_PadsPath;
#pragma pop_macro("P138_PadsPath") /*gvi*/
#pragma pop_macro("P138_PadsPath")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_CfgName")
#undef P138_CfgName
#pragma push_macro("P138_CfgName") /*gvi*/
#undef P138_CfgName /*gvi*/
p138_s40_t P138_CfgName;
#pragma pop_macro("P138_CfgName") /*gvi*/
#pragma pop_macro("P138_CfgName")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P138_CamsPath")
#undef P138_CamsPath
#pragma push_macro("P138_CamsPath") /*gvi*/
#undef P138_CamsPath /*gvi*/
p138_s40_t P138_CamsPath;
#pragma pop_macro("P138_CamsPath") /*gvi*/
#pragma pop_macro("P138_CamsPath")
#endif

#if defined(_WIN32) && !defined(_WIN64)
#  define P138_STD __attribute__((stdcall))
#else
#  define P138_STD
#endif

#include "memrw.h"
static const char k_rep_c[] = "D:\\Driver\\Game\\replays.c";

#include "carfields.h"
/* Replay config kind (word 0 of the .CFG, see P138_ReplayCfg). */
enum { REPLAY_FREE = 0, REPLAY_MISSION = 1, REPLAY_CHASE = 2 };
#define CAR_LEADER 0x41          /* car record used for the recorded chase leader (spare record) */

/* ---- 00520278 ---- */
/* shad_rec / shad_idx / shad_uv / shad_state / shad_vtx — local helpers of the car shadow: the 0x44-byte quad
   record at 00b5c7e0 (native: built here from P96_ShadPage / P96_ShadRGB), its vertex indices and UVs, the
   blend state, and a cache vertex at a ground point (10 units above the ground, camera-relative). */
static uint8_t *shad_rec(void) {
#ifdef RE_HOOK_BUILD
  return (uint8_t *)&P96_ShadIdx[0] - 8;                    /* запись 0x44 по адресу 00b5c7e0 */
#else
  static float rec_f[0x11];
  uint8_t *r = (uint8_t *)rec_f;
  r[2] = P96_ShadPage;
  memcpy(r + 0x38, P96_ShadRGB, 12);
  return r;
#endif
}
static void shad_idx(uint8_t *rec, int32_t a, int32_t b, int32_t c, int32_t d) {
  int32_t v[4] = { a, b, c, d };
  for (int k = 0; k < 4; k++) { wr32(rec + 8 + 4 * k, v[k]); P96_ShadIdx[k] = v[k]; }
}
static void shad_uv(uint8_t *rec, int k, float u, float v) { memcpy(rec + 0x18 + 8 * k, &u, 4); memcpy(rec + 0x1c + 8 * k, &v, 4); }
/* depth_bias — native helper: grDepthBiasLevel(v) through the loaded Glide DLL (01270e20). */
static void depth_bias(int32_t v) {   /* 01270e20 grDepthBiasLevel */
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grDepthBiasLevel@4") == 0) {
      void (P138_STD *f)(int32_t) = (void (P138_STD *)(int32_t))P33_GlideProc(i);
      if (f != NULL) f(v);
      return;
    }
}
static void shad_state(void) {
  if (P62_I252B78 != 0) {
    if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1);
    if (P97_GrDepth) P97_GrDepth(7);
    P62_I252B78 = 0;
  }
}
static void shad_vtx(p85_vtx *v, const int32_t *c) {
  v->x = (float)c[0] - P44_CamX;
  v->y = (-10.0f - P44_CamY) - (float)c[1];                 /* .rdata 00546a84 = −10 */
  v->z = (float)c[2] - P44_CamZ;
  v->stamp = P44_XformTag;
  P85_VC_FMT(v, 0);
}
/* P138_CarShadow — Game.exe 00520278.  Draws the shadow of car `car` (CARSHAD texture, shadows on 00d11880).
   Skipped on road pieces with model flag 0x80, and car 1 in replays.  A single quad over the 4 ground points
   (CAR_GROUND_PT) when detailed shadows are off (00575f20 == 0) or a traffic car stands level (corner
   heights within 10); otherwise a grid (5x6 for traffic, 8x10 for the player/replays) following the road
   height, drawn with depth bias -0x300.  Gives up beyond the far limit 00546030; quads crossing the near
   plane go through the clipping path.  Mirror view uses a mirrored copy of the view matrix.
   Ends with P44_XformTag++ (the vertex cache was overwritten). */
void P138_CarShadow(int32_t car) {
  float m[16];
  if (P13_00d11880 == 0 || P96_ShadIcon == NULL) { P44_XformTag++; return; }
  if (car < 0 || car >= P99_CARS_N) { P44_XformTag++; return; }
  const uint8_t *carrec = (const uint8_t *)&P99_Cars[car];
  if (P72_RoadLookup(rd32(carrec + CAR_POS_X), rd32(carrec + CAR_POS_Z)) != 0) {
    uint32_t w = P79_ModelTab[(int16_t)P72_Id];
    if (w != 0 && (*(const uint16_t *)((const uint8_t *)P79_PTR(w) + 2) & 0x80) != 0) { P44_XformTag++; return; }
  }
  if (G6_00B87EA0 != 0) {
    if (car == 1) return;
    P96_ShadRGB[2] = 255.0f; P96_ShadRGB[1] = 255.0f; P96_ShadRGB[0] = 255.0f;
  }
  if (P26_FxD != 0) { P96_ShadRGB[0] = 128.0f; P96_ShadRGB[1] = 128.0f; P96_ShadRGB[2] = 128.0f; }
  int32_t corner[4][3];
  static const int32_t k_off[4] = { CAR_GROUND_PT + 0 * CAR_GROUND_PT_SIZE, CAR_GROUND_PT + 1 * CAR_GROUND_PT_SIZE,
                                     CAR_GROUND_PT + 3 * CAR_GROUND_PT_SIZE, CAR_GROUND_PT + 2 * CAR_GROUND_PT_SIZE };   /* corners in quad order */
  for (int k = 0; k < 4; k++) for (int j = 0; j < 3; j++) corner[k][j] = rd32(carrec + k_off[k] + 4 * j);
  int flat = (P13_00575f20 == 0);
  if (!flat && car != 0 && G6_00B87EA0 == 0 && carrec[CAR_MODEL] != 1) {
    int32_t y0 = rd32(carrec + CAR_GROUND_PT + 4), y1 = rd32(carrec + CAR_GROUND_PT + 0x14), y2 = rd32(carrec + CAR_GROUND_PT + 0x24), y3 = rd32(carrec + CAR_GROUND_PT + 0x34);   /* ground y of the 4 corners */
    int32_t d1 = y0 - y1, d2 = y1 - y2, d3 = y2 - y3;
    if ((d1 < 0 ? -d1 : d1) < 10 && (d2 < 0 ? -d2 : d2) < 10 && (d3 < 0 ? -d3 : d3) < 10) flat = 1;
  }
  if (P84_Mirror != 0) {
    memset(m, 0, sizeof m); memcpy(m, P44_ViewMatT, sizeof(p44_m9_t));   /* оригинал копирует 16 float */
    m[0] = -m[0]; m[3] = -m[3]; m[6] = -m[6];
  }
  uint8_t *rec = shad_rec();
  if (flat) {
    p85_vtx *v = P85_VCache;
    const float *uv = P96_ShadUV;
    shad_uv(rec, 0, uv[0], uv[1]); shad_uv(rec, 1, uv[4], uv[5]); shad_uv(rec, 2, uv[10], uv[11]); shad_uv(rec, 3, uv[2], uv[3]);
    shad_idx(rec, 0, 1, 2, 3);
    for (int k = 0; k < 4; k++) shad_vtx(&v[k], corner[k]);
    P44_MatPtr = P84_Mirror == 0 ? (float *)P44_ViewMatT : m;
    for (int k = 0; k < 4; k++) {
      P44_Xform(&v[k].x);
      if (Q00546030 < v[k].z) { P44_XformTag++; return; }
    }
    shad_state();
    G2_011F4064 = rec;
    if (P26_FxD != 0 && P98_GrD40) P98_GrD40(0);
    int32_t mode = DrvSetMode0042655A(0);
    if (v[0].z < P95_Near || v[1].z < P95_Near || v[2].z < P95_Near || v[3].z < P95_Near) P121_ClipTexQuad(2);
    else {
      P82_Edge = 1;
      for (int k = 0; k < 4; k++) P43_ProjectGrid((uint8_t *)&v[k]);
      P121_TexQuadFlat(2);
    }
    DrvSetMode0042655A(mode);
    if (P26_FxD != 0 && P98_GrD40) P98_GrD40(2);
  } else {
    int32_t grid_cols, grid_rows, row_stride;
    if (G6_00B87EA0 == 0 && car != 0) { grid_cols = 5; grid_rows = 6; row_stride = 6; } else { grid_cols = 8; grid_rows = 10; row_stride = 9; }
    float x0 = (float)corner[0][0], z0 = (float)corner[0][2];
    float edge_u_x = (float)corner[1][0] - x0, edge_u_z = (float)corner[1][2] - z0;   /* к углу +0x98 */
    float edge_v_x = (float)corner[3][0] - x0, edge_v_z = (float)corner[3][2] - z0;   /* к углу +0xa8 */
    float du = 1.0f / (float)grid_cols, dv = 1.0f / (float)grid_rows;
    float fv = 0.0f;
    P103_HCellX = 0x7fffff; P103_HCellZ = 0x7fffff;
    P44_MatPtr = P84_Mirror == 0 ? (float *)P44_ViewMatT : m;
    p85_vtx *v = P85_VCache;
    for (int r = 0; r <= grid_rows; r++) {
      float fu = 0.0f;
      for (int col = 0; col <= grid_cols; col++) {
        float pos[3];
        pos[0] = edge_v_x * fv + edge_u_x * fu + x0;
        pos[1] = 0.0f;
        pos[2] = edge_v_z * fv + edge_u_z * fu + z0;
        pos[1] = P103_RoadHeight(pos);
        v->x = pos[0] - P44_CamX;
        v->y = (-10.0f - P44_CamY) - pos[1];
        v->z = pos[2] - P44_CamZ;
        v->stamp = P44_XformTag; P85_VC_FMT(v, 0);
        P44_Xform(&v->x);
        if (Q00546030 < v->z) { P44_XformTag++; return; }
        if (P95_Near <= v->z) P43_ProjectGrid((uint8_t *)v);
        fu += du;
        v++;
      }
      fv += dv;
    }
    float cell_u = P96_ShadW * du, cell_v = P96_ShadH * dv;
    const float *uv = P96_ShadUV;
    float u0, v0 = uv[1], v1 = uv[1] + cell_v;
    shad_state();
    if (P26_FxD != 0 && P98_GrD40) P98_GrD40(0);
    depth_bias(-0x300);
    int32_t mode = DrvSetMode0042655A(0);
    P82_Edge = 1;
    int32_t vi = 0;
    v = P85_VCache;
    for (int r = 0; r < grid_rows; r++) {
      u0 = uv[0];
      for (int col = 0; col < grid_cols; col++) {
        shad_idx(rec, vi, vi + 1, vi + 1 + row_stride, vi + row_stride);
        shad_uv(rec, 0, u0, v0); shad_uv(rec, 1, u0 + cell_u, v0); shad_uv(rec, 2, u0 + cell_u, v1); shad_uv(rec, 3, u0, v1);
        const p85_vtx *a = v, *b = v + 1, *cc = v + row_stride + 1, *d = v + row_stride;
        if (P95_Near < a->z && P95_Near < b->z && P95_Near < cc->z && P95_Near < d->z) {
          G2_011F4064 = rec;
          P121_TexQuadFlat(2);
        }
        u0 += cell_u;
        v++; vi++;
      }
      vi++; v++;
      v0 += cell_v; v1 += cell_v;
    }
    depth_bias(0);
    DrvSetMode0042655A(mode);
    if (P26_FxD != 0 && P98_GrD40) P98_GrD40(2);
  }
  P44_XformTag++;
}

/* ---- 004f4180 ---- */
static const char *const k_lev[7] = { "MIAMI_01.LEV", "FRISCO_01.LEV", "LA_01.LEV", "NY_01.LEV", "IVIEW.LEV", "TRAIN.LEV", "NC_01.LEV" };
static const char *const k_des[7] = { "MIAMI_01.DES", "FRISCO_01.DES", "LA_01.DES", "NY_01.DES", "LEVEL4.DES", "LEVEL5.DES", "NEWCASTLE.DES" };
/* P138_Blk84Clear — native helper (shared with 004f4596): memset(00c810c0, 0, 0x210) plus the native aliases of
   variables inside that block. */
void P138_Blk84Clear(void) {   /* memset(00c810c0, 0, 0x210) + native-псевдонимы внутри */
  memset(P56_Blk84, 0, sizeof(p56_blk84_t) < 0x210 ? sizeof(p56_blk84_t) : 0x210);
  P14_00c810c4 = 0; P47_Limit = 0; P99_CamDelay = 0; P14_00c810e8 = 0; P14_00c81100 = 0; G6_00C81108 = 0;
  P98_ScrModel = 0; P77_LevelName = NULL; P109_C81268 = 0; P97_ScrObjOn = 0; P120_DbgOn = 0; P113_MrkRec = 0;
}
/* P138_LoadMission — Game.exe 004f4180.  Resets mission state and loads mission n: n == 0 is plain driving
   (level file and the city's event script .DES set by city index 00b87e30); otherwise compiles
   Scripts\Missions\Mission<n>.dms (results 0, 4 and 10 count as success, 3 = out of memory) and plays the
   mission's intro FMV.  Returns 1 on success, 0 on failure (reason in debug.log). */
int32_t P138_LoadMission(int32_t n) {
  P88_Mode575 = G6_00B87EAC == 0 ? 2 : 1;
  P98_ScrFirst = 0; P120_ConeN = 0;
  P14_Fn0048DB65(P65_Ints, 0x50);
  P127_ScrPos = 0; P65_Ints[0x15] = 0; P77_ListN = 0; P138_C8168C = 0; P138_C80F7C = 0; P65_Ints[0x16] = 0;
  P101_HudVal = 0; P138_C80F40 = 0; G6_00B31F40 = 0; P102_DmgMax = 0; P58_PtrsC816A0 = NULL; P58_LimC810AC = NULL;
  P58_CntC814E8 = 0; P56_C81880 = 0; P138_C80954 = 0; P97_C810A8 = 0; P127_GoalJump = 0; P14_00d14ee4 = 0; D_00d14ee4 = 0;
  P124_DebugLog("* LoadMission *");
  P138_Blk84Clear();
  memset(P58_Objs, 0, sizeof(p58_objs_t));
  memset(&P99_ScrNames, 0, sizeof(P99_ScrNames));
  P138_C80F7C = 0;
  P58_FreeNames((p58_list_t *)&P99_ScrNames);
  D_00c80ca0 = 0; P11_00c81494 = 0; D_00c81494 = 0; P65_Ints[0x16] = 0;
  if (P62_HudOff2 != 0) S_00D1192C = 0;
  P95_BDFA60 = 0; G6_00C80C50 = NULL;
  P59_VarsInit();
  P125_C814E0 = -1; P125_C814E4 = -1; P125_C81690 = -1; P125_C81694 = -1;
  P56_C81880 = 0; P95_BDFA14 = 0; P113_MrkFall = 0; P95_BDFA0C = 0; P97_C81490 = 0; P95_C818B8 = 0; P123_TgtMode = 0;
  P65_Ints[0x2c] = 0; P65_Ints[0x2d] = 0; P65_Ints[0x2e] = 0;
  P127_GoalJump = 1;
  memset(P136_MapName, 0, 4);                                         /* 00c80fa0 = 0 (int) */
  memset(P47_Slots, 0xff, sizeof(P47_SlotArr)); P99_MsgWin = -1; P99_MsgLose = -1;   /* 00c80f60, 0x1c байт 0xff */
  P77_ListN = 0; P77_List = NULL; G6_00B31F40 = 0;
  P129_C81680 = n;
  if (n == 0) {
    int32_t city = D_00b87e30;
    snprintf(P138_LevBuf, sizeof(p138_s100_t), "%s", (city >= 0 && city < 7) ? k_lev[city] : "");
    P77_LevelName = P138_LevBuf;
    P14_00c810c4 = 0; P14_00c810e8 = 0;
    int32_t i = P42_FindVar("EVENTSCRIPT");
    if (i == -1) { P124_DebugLog("FAILED: Could not find variable for event script filename."); return 0; }
    P99_VarSetStr((uint8_t *)&P42_Vars[i], (city >= 0 && city < 7) ? k_des[city] : "");
    P124_DebugLog(">> LoadMission Complete - No Mission Required, Standard Level Initialised - Routine Terminated <<");
    return 1;
  }
  snprintf(P65_Tok, sizeof(p65_tok_t), "Attempting to load: Scripts\\Missions\\Mission%d.dms", n);
  P124_DebugLog(P65_Tok);
  snprintf(P65_Tok, sizeof(p65_tok_t), "Scripts\\Missions\\Mission%d.dms", n);
  int32_t res = P139_CompileScript(P65_Tok);
  if (res == 0 || res == 10 || res == 4) {
    P150_PlayFmv(G6_00BDF9C0, P125_C814E0, P125_C814E4);
    P97_ScrObjOn = 1;
    P124_DebugLog(">> LoadMission Complete - Routine Terminated <<");
    return 1;
  }
  if (res == 3) { P124_DebugLog("FAILED: CompileMissionScript - OutOfMemory"); return 0; }
  const char *err = P13_Fn004F8735(res);
  snprintf(P65_Tok, sizeof(p65_tok_t), "FAILED: CompileMissionScript - %s, Line: %d", err ? err : "(null)", P65_Ints[0x15]);
  P124_DebugLog(P65_Tok);
  return 0;
}

/* ---- 00517d58 ---- */
/* cfg32 — local helper: int32 at offset o of the loaded replay config (00c54ee0, 0x88 bytes). */
static int32_t cfg32(int o) { return rd32(P103_C54EE0 + o); }
/* P138_ReplayCfg — Game.exe 00517d58.  Loads ReplayData\User\<name>.CFG (or Demo\, which marks a demo) and applies
   it: game options 00bdfa40.., night / weather flags, traffic density, goals, felony settings, then the PADS /
   CAMS paths and the director data.  Kind (word 0): REPLAY_FREE (city or interview), REPLAY_MISSION (mission
   arg), REPLAY_CHASE (with the chase leader, 00b87eb0 = 1).  Returns 1, or 0 if the file or its director data
   is missing. */
int32_t P138_ReplayCfg(const char *name) {
  char path[64];
  P101_RecSaved = 0; P109_C54B00 = 0; P100_RecEnd = 0;
  snprintf(P138_CfgName, sizeof(p138_s40_t), "%s", name);
  snprintf(path, sizeof path, "ReplayData\\User\\%s.CFG", name);
  void *f = g_fopen(path, "rb");
  if (f == NULL) {
    snprintf(path, sizeof path, "ReplayData\\Demo\\%s.CFG", name);
    f = g_fopen(path, "rb");
    if (f == NULL) return 0;
    g_fread(P103_C54EE0, 1, 0x88, f);
    P109_C54B00 = P103_C54EE0[0x2a];
    g_fclose(f);
    P100_RecEnd = 1;
  } else {
    g_fread(P103_C54EE0, 1, 0x88, f);
    P109_C54B00 = P103_C54EE0[0x2a];
    g_fclose(f);
  }
  int32_t s[7];
  for (int k = 0; k < 7; k++) s[k] = cfg32(0x6c + 4 * k);
  P12_00bdfa40 = s[0];
  MenuOptBDFA44 = s[1]; P14_00bdfa44 = s[1]; P62_BusyA = s[1]; G00BDFA44 = s[1];
  MenuOptBDFA48 = s[2]; P62_BusyB = s[2]; G00BDFA48 = s[2];
  MenuOptBDFA4C = s[3]; P62_BusyC = s[3]; G00BDFA4C = s[3];
  MenuOptBDFA50 = s[4]; P62_BusyD = s[4]; G00BDFA50 = s[4];
  MenuOptBDFA54 = s[5]; G00BDFA54 = s[5];
  MenuOptBDFA58 = s[6]; P14_00bdfa58 = s[6]; P62_BusyE = s[6]; G00BDFA58 = s[6];
  P14_00b87e84 = P103_C54EE0[0x10];
  P26_FxA = P103_C54EE0[0x11]; P26_FxC = P103_C54EE0[0x12]; P26_FxB = P103_C54EE0[0x13]; P26_FxD = P103_C54EE0[0x14];
  int32_t te = cfg32(0x60);
  P13_00575ee4 = te; P21_EntryCount = te; P51_TrafficN = te; G8_00575EE4 = te; G2_00575EE4 = te; WI00575EE4 = te;
  { int32_t v = cfg32(0x24); memcpy(P56_PathPings + 0x40, &v, 4); }   /* 00c4d660 */
  P102_D06A04 = P103_C54EE0[0x2b];
  for (int k = 0; k < 7; k++) P127_GoalSave[7 + k] = (uint32_t)cfg32(0x44 + 4 * k);   /* 00c816dc..00c816f4 */
  for (int k = 0; k < 3; k++) { float fv = (float)cfg32(0x2c + 4 * k); memcpy(&P127_GoalSave[k], &fv, 4); }
  P102_C816F8 = cfg32(0x38); P102_C816FC = cfg32(0x3c);
  { int32_t v = cfg32(0x40); MenuVar5759A4 = v; P13_005759a4 = v; P60_PartLimit = v; G005759A4 = v; }
  WI00B87E2C = cfg32(0x64);
  G00575F24 = cfg32(0x68);
  { int32_t v = P14_00b87e84 != 0; G00D17B08 = v; MenuVarB201DC = v; P13_00b201dc = v; G00B201DC = v; }
  snprintf(P138_PadsPath, sizeof(p138_s40_t), "ReplayData\\User\\%s.PADS", name);
  snprintf(P138_CamsPath, sizeof(p138_s40_t), "ReplayData\\User\\%s.CAMS", name);
  if (LoadWaypoints() == 0 && LoadDirector(P138_CamsPath) == 0) return 0;
  P62_HudOff2 = P103_C54EE0[0x28];
  int32_t kind = cfg32(0), arg = cfg32(4);
#define SET_E38(x) do { int32_t v_ = (x); P11_00b87e38 = v_; P17_Cond2 = v_; P19_Cond = v_; P45_Mode = v_; UiVar00B87E38 = v_; } while (0)
  if (kind == REPLAY_FREE) {
    if (P11_00d11934 == 0) {
      SET_E38(0);
      D_00b87e30 = P62_HudOff2 == 0 ? arg : 4;
    } else if (P62_HudOff2 == 0) {
      D_00b87e30 = arg;
    } else {
      SET_E38(0);
      D_00b87e30 = 4;
      G00C8198C = -1; { int32_t m1 = -1; memcpy(&P43_AnimTab, &m1, 4); memcpy(A_00C8198C, &m1, 4); }
      P17_Src = 0;
      G00C81988 = 0xc9;
    }
    P36_PadMode = 2;
    return 1;
  }
  if (kind == REPLAY_MISSION) { SET_E38(arg); P36_PadMode = 2; return 1; }
  if (kind == REPLAY_CHASE) {
    SET_E38(arg);
    if (P109_C54B00 != 0) { P138_B5A8CC = cfg32(8); G00B5A8CD = (uint8_t)(cfg32(8) >> 8); }
    P36_PadMode = 3;
    P58_SB87EB0 = 1; G6_00B87EB0 = 1; G8_00B87EB0 = 1;
    return 1;
  }
#undef SET_E38
  return 1;
}

/* ---- 005181da / 0051879f / 00518bbc ---- */
/* read_pads — local helper: reads a .PADS file (first word, total count, recorded pad data) into recording
   buffer p (0x40000 bytes when big).  The top bit of the count sets 00c4d9a4.  Returns 0 if missing. */
static int32_t read_pads(const char *path, int32_t buf_idx, int32_t big, int32_t line, int32_t *first) {
  void *f = g_fopen(path, "rb");
  if (f == NULL) return 0;
  int32_t file_size = P51_FileSize(f);
  int32_t buf_size = big ? 0x40000 : file_size - 4;
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(buf_size, k_rep_c, line);
  P100_RecPtr[buf_idx] = buf != NULL ? re_ptr_register_dyn(buf, (uint32_t)(buf_size > 0 ? buf_size : 1)) : 0;
  g_fread(first, 1, 4, f);
  g_fread(&P100_RecTot[buf_idx], 1, 4, f);
#ifndef RE_HOOK_BUILD
  if (buf != NULL && file_size - 4 > 0 && file_size - 4 <= buf_size) g_fread(buf, 1, (size_t)(file_size - 4), f);
  else if (buf != NULL && buf_size > 0) g_fread(buf, 1, (size_t)buf_size, f);
#else
  g_fread(buf, 1, (size_t)(file_size - 4), f);
#endif
  g_fclose(f);
  if (((uint32_t)P100_RecTot[buf_idx] & 0x80000000u) != 0) { P100_RecTot[buf_idx] &= 0x7fffffff; P103_C4D9A4 = 1; }
  return 1;
}
/* read_car — local helper: reads a whole car record (0x148 bytes) from a file into car `car`. */
static int read_car(const char *path, int32_t car) {
  void *f = g_fopen(path, "rb");
  if (f == NULL) return 0;
  g_fread(&P99_Cars[car], 1, sizeof(p99_car_t), f);
  g_fclose(f);
  return 1;
}
/* leader_flags — local helper: marks the leader record 0x41 (id, model from 00bdf9d4) and its traffic record
   type `kind`. */
static void leader_flags(uint8_t kind) {
  p99_car_t *c = &P99_Cars[CAR_LEADER];
  c->f00[2] = (uint8_t)P95_BDF9D4; c->f00[0] = 0x41;
  P98_TrafX[1] = kind; P98_TrafX[2] = 0; P98_TrafX[0xc] = (uint8_t)P95_BDF9D4; P98_TrafX[0xd] = (uint8_t)P95_BDF9D0;
}
/* P138_ReplayLoad — Game.exe 005181da.  Loads a chase: leader PADS into buffer 1, the LEADER car record, the
   PINGS snapshots (0x1a4-byte records, see P55_SaveRec); then the player's PADS and car when the config has
   them (00c54b00), else starts recording (P138_ReplayInit).  Native: counts clamped, missing files skipped. */
void P138_ReplayLoad(void) {
  P95_B87EC4 = 1;
  if (read_pads(P56_PathPads, 1, G6_00B87EA0 != 0, G6_00B87EA0 != 0 ? 0x251 : 0x253, &P74_C4D668)) {
    if (G6_00B87EA0 == 0 || P88_Mode575 != 2) read_car(P56_PathLeader, CAR_LEADER);
    p99_car_t *c = &P99_Cars[CAR_LEADER];
    c->vel[0] = 0; c->vel[1] = 0; c->vel[2] = 0; c->f128 = 0; c->f12c = 0; c->f130 = 0; c->f134 = 0;
    leader_flags(7);
    P100_RecRep[1] = 0; P100_RecOff[1] = 0; P100_RecCnt[1] = 0; P55_RecCnt = 0; P36_JoyX = 0; P74_B5A86C[1] = 0;
    P14_00b31e20 = 0; P21_AxisValue = 0; P9_00b31e20 = 0; P74_B5A880[1] = 0;
    P99_CarModelClean(0x40);
    P55_RecBase = (uint8_t *)P98_DebugMalloc(0xd2000, k_rep_c, 0x281);
    if (P55_RecBase != NULL) {
      char path[0x80];
      snprintf(path, sizeof path, "ReplayData\\Chase\\%s.PINGS", P56_PathName);
      void *f = g_fopen(path, "rb");
      if (f != NULL) {
        g_fread(&P103_B5A8C4, 1, 4, f);
#ifndef RE_HOOK_BUILD
        if ((uint32_t)P103_B5A8C4 > 0x800u) P103_B5A8C4 = 0x800;
#endif
        g_fread(P55_RecBase, (size_t)(uint32_t)P103_B5A8C4, 0x1a4, f);
        g_fclose(f);
      }
    }
  }
  if (P109_C54B00 == 0) {
    P12_00b5a898 = 0; P61_V10 = 0; P95_B87EC0 = 1;
    P138_ReplayInit();
    return;
  }
  int32_t skip;
  if (read_pads(P138_PadsPath, 0, 0, 0x297, &skip)) {
    if (G6_00B87EA0 == 0 || P88_Mode575 != 2) read_car(P56_PathPlayer, 0);
    p99_car_t *c = &P99_Cars[0];
    c->vel[0] = 0; c->vel[1] = 0; c->vel[2] = 0; c->f128 = 0; c->f12c = 0; c->f130 = 0; c->f134 = 0;
    c->f00[0] = 0;
    P100_RecRep[0] = 0; P100_RecOff[0] = 0; P100_RecCnt[0] = 0; P74_B5A86C[0] = 0; P74_B5A880[0] = 0;
    P99_CarModelClean(-1);
    P96_ReplayB++;
  }
}
/* P138_ReplayInit — Game.exe 0051879f.  Allocates the 0x40000-byte recording buffer; in a chase (00b87eac) also
   the PINGS buffer and the LEADER car.  Resets the HUD and records the first camera. */
void P138_ReplayInit(void) {
  if (P96_ReplayB != 0) return;
  P100_RecBuf = (uint8_t *)P98_DebugMalloc(0x40000, k_rep_c, 0x31b);
  if (P100_RecBuf == NULL) return;
  if (G6_00B87EAC != 0) {
    P55_RecBase = (uint8_t *)P98_DebugMalloc(0xd2000, k_rep_c, 0x330);
    if (P55_RecBase == NULL) return;
    memset(P55_RecBase, 0, 0xd2000);
    if (G6_00B87EAC != 0) {
      char path[0x80];
      snprintf(path, sizeof path, "ReplayData\\Chase\\%s.LEADER", P56_PathName);
      read_car(path, CAR_LEADER);
      leader_flags(8);
      P99_CarModelClean(0x40);
    }
  }
  P74_ResetHud();
  P100_RecKeys = 0x20;
  P98_CamRecAdd(0);
}
/* P138_LoadPads — Game.exe 00518bbc.  Outside a chase replay, loads the player's PADS into buffer 0 and resets
   the player's velocity/damage and the replay counters. */
void P138_LoadPads(void) {
  if (G6_00B87EB0 != 0) return;
  if (!read_pads(P138_PadsPath, 0, 0, 0x3ed, &P74_C4D668)) return;
  p99_car_t *c = &P99_Cars[0];
  c->f138 = 0; c->f130 = 0; c->f12c = 0; c->f128 = 0; c->vel[2] = 0; c->vel[1] = 0; c->vel[0] = 0;
  P100_RecRep[0] = 0; P100_RecOff[0] = 0; P100_RecCnt[0] = 0; P55_RecCnt = 0; P36_JoyX = 0; P74_B5A86C[0] = 0;
  P14_00b31e20 = 0; P21_AxisValue = 0; P9_00b31e20 = 0; P74_B5A880[0] = 0;
}

/* ---- 004fbfad ---- */
#ifndef RE_HOOK_BUILD
static void *p138_trail;   /* native: TRAIL.DAT, открытый последним вызовом (00c812f0 — int32) */
#endif
/* P138_TrailEnd — Game.exe 004fbfad.  Ends trail recording: writes the end marker 0x7fffffff, closes and re-reads
   TRAIL.DAT and logs the last cone position (or "Trail Not Recorded").  Native: the file is never open. */
void P138_TrailEnd(void) {
  int32_t mark = 0x7fffffff, hdr, t[3];
#ifdef RE_HOOK_BUILD
  void *f = (void *)(uintptr_t)(uint32_t)Q00C812F0;
  g_fwrite(&mark, 1, 4, f);
  g_fclose(f);
  f = g_fopen("TRAIL.DAT", "rb");
  Q00C812F0 = (int32_t)(uintptr_t)f;
#else
  (void)mark;
  if (p138_trail != NULL) g_fclose(p138_trail);
  void *f = p138_trail = g_fopen("TRAIL.DAT", "rb");
  if (f == NULL) { P124_DebugLog("Trail Not Recorded"); return; }
#endif
  g_fread(&hdr, 4, 1, f);
  int32_t prev = hdr;                                    /* local_10: z предыдущей тройки (сначала — заголовок) */
  for (;;) {
    int32_t px = prev;
    if (g_fread(t, 4, 3, f) != 3 || t[1] == -1) break;
    prev = t[2];
    if (t[2] == 0x7fffffff) {
      g_fclose(f);
#ifndef RE_HOOK_BUILD
      p138_trail = NULL;
#endif
      snprintf(P65_Tok, sizeof(p65_tok_t), "Last Cone: x = %d, z = %d\n", px, t[1]);
      P124_DebugLog(P65_Tok);
      snprintf(P65_Tok, sizeof(p65_tok_t), "End Car Position: x = %d, z = %d\n", P99_Cars[0].pos[0], P99_Cars[0].pos[2]);
      P124_DebugLog(P65_Tok);
      return;
    }
  }
  P124_DebugLog("Trail Not Recorded");
}
