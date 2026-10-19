/* ported134.c — cameras (English overview; the original Russian notes follow):
   0049cad4 P134_CamCollide (push the camera out of buildings), 0049d84a P134_CamChase (chase camera),
   0049e16c P134_CamTarget (fixed camera aimed at a car), 004f0f90 P134_CamCine (cutscene camera),
   00494620 P134_TrafficHold (traffic state handler).  Camera angles use 4096 = 360 degrees; camera
   coordinates are floats with Y negated relative to the car table (camera Y = -car Y).

   v1.79: ported134 — см. ported134.h.
   0049cad4 — при 00b5a778 ≠ 0 и 00d17bbc = 0 — 0. Иначе 004c6091(ftol x, ftol z) (всегда 1), клетка сетки по камере
     (00ce0f2c/00ce0f30 × 0125f3e8, блоки 2×2 по 00c98ecc), при дистанции 01137368 > 0 — обход списка узлов клетки:
     модели с коробками (+0x34) и 004c60b2 (нет флага 0x400, радиус +0x10 ≥ 200) ближе радиуса по XZ; записи типа 0
     (шаг 0x14): камера в осях модели (матрица 00b1c280 + угол·0x40, второй поворот +0xa), полуразмеры (+0xe..+0x12)/2 + 50
     (.data 0054609c); оба по X/Z < 300 (.data 005460ec) — пропуск; внутри — сдвиг по ближайшей грани, дистанция = min(текущая,
     расстояние до игрока по XZ). Записи типа 1 считают квадрат расстояния, но результат не используется (fcomp без
     перехода). Без касания дистанция += 01136c54 до 0113731c. ground ≠ 0 — не ниже дороги + 250 (004dd262).
   0049d84a — клавиши (01137370/01136acc — дистанция ±40 не меньше 1, 01136c50/0113735c — поворот ∓0x16), плавный курс
     01137310 (1/8, в режиме 00d17bbc — сразу) и наклон 01137318 (1/8), вектор (0, 011373a4, 01137368) поворачивается
     (наклон — если 00d02630 = 0, курс − старшее слово 01137320) и прибавляется к позиции машины; 0049cad4(1); углы на машину.
   0049e16c — камера = 01136c70; 0049cad4(0); car = −1 — углы 011373b8/ba/bc, масштаб 384 или 1152 (флаг 011373c0);
     иначе углы на машину (длина 3D, векторы ×256, /4 пока > 64000), масштаб |d·0.2| в 384..2112 при флаге.
   004f0f90 — при 00c824a0: 004f154e (режим 00c824d0 = 0), 0049cad4(1), доля t = 00c82430·4096/00c823dc ≤ 4096; при 00c82504 = 2 —
     интерполяция камеры 00c82420 → 00c824f0 и масштаба 00c82520 → 00c824dc, копия в 011373a0; иначе высота 011373a4 над дорогой
     (−200 − 00c82500·t′ или 00c82434 + …), камера тянется на 1/8 (ftol), режим 2 — масштаб 784 − 0.097656·t; углы на точку
     00c82448 (P126_Spawn + 8), копии в 01137318/01137310.
   00494620 — машина записи (0113a6c4 + rec[0]·0x148): rec[0xb] ≠ 0 — поле +0xfc = −575 и rec[0xb]−−; иначе rec[1] = 2, rec[2] = 1.
     В Ghidra-списке нет (вызывается только через .data 00551308).
   Отступления native: угол матрицы модели +0x18 маскируется 0xfff и при записи 00bdc28c; NULL сетки/моделей/таблицы
     00b1c280 — без обхода; индекс машины вне 0..65 — без действия; деление на 00c823dc = 0 — t = 4096, слагаемое высоты 0;
     псевдонимы 00b1c270.. (P59_V*) и 00b1c268 (P11_00b1c268) обновляются вместе с P44_Cam* и P59_AngA. */
#include "ported134.h"
#include "carfields.h"
#include <string.h>
#include <math.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported28.h"
#include "ported29.h"
#include "ported35.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported66.h"
#include "ported68.h"
#include "ported69.h"
#include "ported74.h"
#include "ported75.h"
#include "ported77.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported88.h"
#include "ported89.h"
#include "ported95.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported106.h"
#include "ported108.h"
#include "ported109.h"
#include "ported110.h"
#include "ported113.h"
#include "ported114.h"
#include "ported116.h"
#include "ported119.h"
#include "ported121.h"
#include "ported123.h"
#include "ported127.h"
#include "ported128.h"
#include "ported131.h"
#include "ported132.h"
#include "ported126.h"
#include "ported133.h"

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P134_Cine0")
#undef P134_Cine0
#pragma push_macro("P134_Cine0") /*gvi*/
#undef P134_Cine0 /*gvi*/
p134_v3_t P134_Cine0;
#pragma pop_macro("P134_Cine0") /*gvi*/
#pragma pop_macro("P134_Cine0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P134_Cine1")
#undef P134_Cine1
#pragma push_macro("P134_Cine1") /*gvi*/
#undef P134_Cine1 /*gvi*/
p134_v3_t P134_Cine1;
#pragma pop_macro("P134_Cine1") /*gvi*/
#pragma pop_macro("P134_Cine1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P134_ScaleB")
#undef P134_ScaleB
#pragma push_macro("P134_ScaleB") /*gvi*/
#undef P134_ScaleB /*gvi*/
float P134_ScaleB;
#pragma pop_macro("P134_ScaleB") /*gvi*/
#pragma pop_macro("P134_ScaleB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P134_ScaleE")
#undef P134_ScaleE
#pragma push_macro("P134_ScaleE") /*gvi*/
#undef P134_ScaleE /*gvi*/
float P134_ScaleE;
#pragma pop_macro("P134_ScaleE") /*gvi*/
#pragma pop_macro("P134_ScaleE")
#endif
#endif

#include "memrw.h"
static int16_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static int32_t rnd(float f) { P11_00ba52d0 = (int32_t)lrintf(f); return P11_00ba52d0; }   /* fistp → 00ba52d0 */
static void sync_cam(void) {
#ifndef RE_HOOK_BUILD
  P59_VX = P44_CamX; P59_VY = P44_CamY; P59_VZ = P44_CamZ;      /* псевдонимы 00b1c270.. */
#endif
}
static void set_anga(uint16_t a) {
  P59_AngA = a;
#ifndef RE_HOOK_BUILD
  P11_00b1c268 = (uint8_t)a;                                     /* псевдоним 00b1c268 */
#endif
}
static const float *euler(uint32_t a) { return (const float *)(const void *)(P56_EulerTab + (a & 0xfffu) * 0x40); }
static int car_ok(int32_t car) {
#ifndef RE_HOOK_BUILD
  return car >= 0 && car < P99_CARS_N;
#else
  (void)car; return 1;
#endif
}
/* 004c60b2: модель объекта без флага 0x400 и с радиусом ≥ 200 (.data 00546200) */
static int32_t far_enough(const uint8_t *m) { return (rd32(m + 8) & 0x400) == 0 && 200.0f <= rdf(m + 0x10); }

/* ---- 0049cad4 ---- */
/* P134_CamCollide — Game.exe 0049cad4, cdecl.
   Keeps the camera (P44_CamX/Y/Z, float world coordinates; Y is negated: up = -Y) out of buildings.
   Looks up the map-grid cell under the camera (blocks of 2x2 cell slots, see ported89.c), walks the
   cell's object list and, for every model with collision boxes (+0x34) whose bounding circle contains
   the camera, transforms the camera into each box's frame (object rotation + optional box rotation).
   If the camera is inside a box (half-sizes + P95_Near margin), it is pushed out through the nearest
   vertical face, and the chase distance P61_Dist8 is shortened to the new camera-player distance.
   With no contact the distance grows back by P62_F136C54 per call, up to P61_DistC.
   In:  ground — non-zero: also keep the camera at least 250 units above the road.
   Out: 1 if the camera was pushed, else 0 (0 while paused outside the replay director).
   Quirk kept: boxes of type 1 are skipped (the original computes a distance for them and ignores it). */
int32_t P134_CamCollide(int32_t ground) {
  if (G6_00B5A778 != 0 && P29_Mode == 0) return 0;
  int32_t far = P47_Call51B111((int32_t)P44_CamX, (int32_t)P44_CamZ);      /* __ftol; always 1 in practice (004c6091) */
  int32_t clear = 1;   /* stays 1 when no box touched the camera */
  int32_t gx = rnd((P44_CamX + (float)P42_CellX) * P42_CellScale);   /* map-grid cell of the camera */
  int32_t gz = rnd((P44_CamZ + (float)P42_CellY) * P42_CellScale);
  int32_t N = P54_GridN;
  int ok = 1;
#ifndef RE_HOOK_BUILD
  if (N <= 0 || G6_00D01268 == NULL || G6_00CE0F20 == NULL || G6_00D00208 == NULL || P56_EulerTab == NULL) ok = 0;   /* защита */
#endif
  int32_t node = -1;
  if (ok) {
    /* the cell table holds 4 slots of N x N cells; the slot is picked by the parity of the N x N block */
    int32_t bx = gx / N, bz = gz / N;
    int32_t cell = ((bx & 1) + (bz & 1) * 2) * N * N + (gx - bx * N) + (gz - bz * N) * N;
#ifndef RE_HOOK_BUILD
    if (cell < 0 || cell >= 4 * N * N) ok = 0;                                                  /* защита */
    else
#endif
    node = ((const int32_t *)G6_00D01268)[cell];
  }
  if (ok && 0.0f < P61_Dist8) {                                                                 /* .data 00546024 = 0 */
    for (int32_t guard = 0; node != -1 && guard < 0x14000; guard++) {
#ifndef RE_HOOK_BUILD
      if (node < 0 || node >= 0x14000) break;                                                   /* защита */
#endif
      const int32_t *nd = (const int32_t *)(const void *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
      const uint8_t *o = (const uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
      int32_t mi = rd32(o + 4);
      uint32_t mr = ((uint32_t)mi < 1126u) ? P79_ModelTab[mi] : 0;
      const uint8_t *m = mr ? (const uint8_t *)P79_PTR(mr) : NULL;
      if (m != NULL && rd32(m + 0x34) != 0 && (far == 0 || far_enough(m))) {
        int32_t r = rnd(rdf(m + 0x10)); int32_t r2 = r * r;
        int32_t ex = rnd((float)fabs((double)(rdf(o + 8) - P44_CamX)));
        int32_t ez = rnd((float)fabs((double)(rdf(o + 0x10) - P44_CamZ)));
        if (ex * ex + ez * ez < r2) {
          const uint8_t *lst = (const uint8_t *)P79_PTR((uint32_t)rd32(m + 0x34));
          int32_t cnt = rd32(lst);
          const uint8_t *e = lst + 4;
          for (int32_t k = 0; k < cnt; k++, e += 0x14) {
            if (rd16(e) != 0) continue;                       /* тип 1 — результат не используется */
            uint32_t rot = (uint32_t)rd32(o + 0x18);
            P44_MatPtr = (float *)(void *)(P56_EulerTab + (rot & 0xfffu) * 0x40);
            float dx = P44_CamX - rdf(o + 8), dz = P44_CamZ - rdf(o + 0x10);
            const float *mt = euler(rot);
            float u = (dz * mt[6] + dx * mt[0]) - (float)rd16(e + 2);
            float y = (P44_CamY - rdf(o + 0xc)) - (float)rd16(e + 4);
            float v = (dz * mt[8] + dx * mt[2]) - (float)rd16(e + 6);
            float uu = u;
            if (rd16(e + 10) != 0) {
              mt = euler((uint32_t)(int32_t)rd16(e + 10));
              uu = v * mt[6] + u * mt[0];
              v = v * mt[8] + u * mt[2];
            }
            /* box record (0x14 bytes): +0 type, +2/+4/+6 centre, +10 extra rotation, +14/+16/+18 size */
            float hx = (float)((int32_t)rd16(e + 14) >> 1) + P95_Near;
            float hy = (float)((int32_t)rd16(e + 16) >> 1) + P95_Near;
            float hz = (float)((int32_t)rd16(e + 18) >> 1) + P95_Near;
            if (hx < 300.0f && hz < 300.0f) continue;                                           /* .data 005460ec */
            if (!(-hx < uu && uu < hx && -hy < y && y < hy && -hz < v && v < hz)) continue;
            /* distances to the four vertical faces; push out through the nearest one */
            float f1 = (float)fabs((double)(uu + hx)), f2 = (float)fabs((double)(uu - hx));
            float f3 = (float)fabs((double)(v + hz)), f4 = (float)fabs((double)(v - hz));
            int face; float mn;
            if (f1 < f2) { face = 0; mn = f1; } else { face = 1; mn = f2; }
            if (f3 < f4) { if (f3 < mn) face = 2; } else if (f4 < mn) face = 3;
            float px = 0.0f, pz = 0.0f;   /* push in box space, rotated back to world below */
            switch (face) {
            case 0: px = -f1; break;
            case 1: px = f2; break;
            case 2: pz = -f3; break;
            default: pz = f4; break;
            }
            mt = euler((uint32_t)(-(rd32(o + 0x18) + (int32_t)rd16(e + 10))));
            P44_CamX = P44_CamX + pz * mt[6] + px * mt[0];
            P44_CamZ = P44_CamZ + pz * mt[8] + px * mt[2];
            sync_cam();
            float cx = P44_CamX - (float)P99_Cars[0].pos[0], cz = P44_CamZ - (float)P99_Cars[0].pos[2];
            float d = (float)sqrt((double)(cx * cx + cz * cz));
            if (d < P61_Dist8) P61_Dist8 = d;
            clear = 0;
          }
        }
      }
      node = nd[1];
    }
  }
  if (clear) {
    P61_Dist8 = P61_Dist8 + P62_F136C54;
    if (P61_DistC < P61_Dist8) P61_Dist8 = P61_DistC;
  }
  if (ground != 0) {
    int32_t p[3], nrm[3], out[3];
    p[0] = rnd(P44_CamX); p[1] = rnd(P44_CamY); p[2] = rnd(P44_CamZ);
    P103_GroundAt(p, nrm, out);
    if (-P44_CamY < (float)(out[1] + 0xfa)) { P44_CamY = -((float)out[1] + 250.0f); sync_cam(); }   /* .data 005460e4 */
  }
  return clear == 0;
}

/* углы камеры на точку: A = ±(atan2(len, y) − 0x400), B = −atan2(x, z)
   Camera angles towards a direction (fx, fy, fz): pitch P59_AngA = +-(atan2(horizontal length, y) - 90 deg),
   yaw P59_AngB = -atan2(x, z), roll P59_AngC = 0 (4096 = 360 deg). */
static void look_xz(float fx, float fy, float fz, int neg) {
  float d = (float)sqrt((double)(fz * fz + fx * fx));
  int32_t len = rnd(d), ix = rnd(fx), iy = rnd(fy), iz = rnd(fz);
  int32_t a = P44_Atan2(len, iy);
  set_anga(neg ? (uint16_t)(-(int16_t)(a - 0x400) & 0xfff) : (uint16_t)((uint16_t)((int16_t)a - 0x400) & 0xfff));
  P59_AngB = (uint16_t)(-(int16_t)P44_Atan2(ix, iz) & 0xfff);
  P59_AngC = 0;
}

/* ---- 0049d84a ---- */
/* P134_CamChase — Game.exe 0049d84a, cdecl.  The default chase camera behind car `car` (0 = player).
   Keys (when not paused): zoom P61_Dist8 -+40 (minimum 1), orbit P61_V18 -+0x16 per tick.
   The camera heading P61_V1C follows car heading + orbit with 1/8 smoothing per tick (immediately in
   the replay director), the pitch P61_V20 follows -car pitch the same way.  The offset
   (0, P61_OffY, P61_Dist8) is rotated by pitch (skipped during the marker effect) and heading (minus
   the shake offset P133_1137320 >> 16), added to the car position, pushed out of buildings
   (P134_CamCollide(1)) and finally aimed at the car. */
void P134_CamChase(int32_t car) {
  if (!car_ok(car)) return;                                    /* защита индекса: в оригинале нет */
  const p99_car_t *c = &P99_Cars[car];
  if (G6_00B5A778 == 0 && P128_FreeCamLock == 0) {
    if (P36_Pad3 != 0 && (P61_Dist8 = P61_Dist8 - 40.0f, P61_Dist8 < 1.0f)) P61_Dist8 = 1.0f;   /* .data 005460fc, 00546020 */
    if (P36_Pad2 != 0) P61_Dist8 = P61_Dist8 + 40.0f;
    if (P36_Pad4 != 0) P61_V18 = (P61_V18 - 0x16) & 0xfff;
    if (P36_Pad5 != 0) P61_V18 = (P61_V18 + 0x16) & 0xfff;
  }
  /* signed angle difference wrapped to [-180, 180) degrees: ((a - b + 0x800) & 0xfff) - 0x800 */
  int32_t dh = ((c->heading + P61_V18 - P61_V1C + 0x800) & 0xfff) - 0x800;
  int live = (G6_00B5A778 == 0 || P29_Mode != 0) && P128_FreeCamLock == 0;
  if (live) {
    if (P29_Mode == 0) P61_V1C = (P61_V1C + dh / 8) & 0xfff;
    else P61_V1C = c->heading + P61_V18;
  }
  int32_t dp = ((((uint32_t)-(int32_t)c->ang[0] & 0xfffu) - P61_V20 + 0x800) & 0xfff) - 0x800;
  if (live) P61_V20 = (P61_V20 + dp / 8) & 0xfff;
  float v[3] = { 0.0f, P61_OffY, P61_Dist8 };
  static float m[9];                                           /* native: матрица переживает вызов (в оригинале — стек) */
  static const float id[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  memcpy(m, id, sizeof m);
  if (P98_MrkOff == 0) P44_RotX(m, P61_V20 & 0xfff);
  P44_RotY(m, -(P61_V1C - (P133_1137320 >> 16)) & 0xfff);
  P44_MatPtr = m;
  P44_Xform(v);
  P44_CamX = (float)c->pos[0] + v[0];
  P44_CamY = (float)-c->pos[1] + v[1];
  P44_CamZ = (float)c->pos[2] + v[2];
  sync_cam();
  P134_CamCollide(1);
  look_xz((float)c->pos[0] - P44_CamX, (float)-c->pos[1] - P44_CamY, (float)c->pos[2] - P44_CamZ, 1);
  InitXform_005263FE();
}

/* ---- 0049e16c ---- */
/* P134_CamTarget — Game.exe 0049e16c, cdecl.  Fixed-position camera at P61_TgtX/Y/Z.
   car == -1: use the stored angles P61_AngB8/BA/BC; otherwise aim at car `car`.  The projection scale
   P43_ScaleA (focal length: larger = narrower view) is 384 normally; with the zoom flag 011373c0 it is
   1152 for the fixed angles, or 0.2 * distance clamped to 384..2112 when tracking a car.
   The direction vector is scaled by 256 and then reduced by 4 until its length is <= 64000 so the
   integer atan2 keeps its precision. */
void P134_CamTarget(int32_t car) {
  rnd(P44_CamZ);
  P44_CamX = P61_TgtX; P44_CamY = P61_TgtY; P44_CamZ = P61_TgtZ;
  sync_cam();
  P134_CamCollide(0);
  int big = (uint8_t)P60_Var1373C0 != 0;
  if (car == -1) {
    set_anga(P61_AngB8); P59_AngB = P61_AngBA; P59_AngC = P61_AngBC;
    P43_ScaleA = big ? 1152.0f : 384.0f;
  } else {
    if (!car_ok(car)) return;                                  /* защита индекса: в оригинале нет */
    const p99_car_t *c = &P99_Cars[car];
    float fx = (float)c->pos[0] - P44_CamX, fy = P44_CamY + (float)c->pos[1], fz = (float)c->pos[2] - P44_CamZ;
    float d = (float)sqrt((double)(fz * fz + fy * fy + fx * fx));
    int32_t len = rnd(d) << 8, vx = rnd(fx) << 8, vy = rnd(fy) << 8, vz = rnd(fz) << 8;
    for (; 64000 < len; len >>= 2) { vx >>= 2; vy >>= 2; vz >>= 2; }
    set_anga((uint16_t)((uint16_t)((int16_t)P44_Atan2(len, vy) - 0x400) & 0xfff));
    P59_AngB = (uint16_t)(-(int16_t)P44_Atan2(vx, vz) & 0xfff);
    P59_AngC = 0;
    if (!big) P43_ScaleA = 384.0f;
    else {
      P43_ScaleA = (float)fabs((double)(d * 0.2f));            /* .data 00546080 */
      if (P43_ScaleA < 384.0f) P43_ScaleA = 384.0f;            /* .data 00546114 */
      else if ((float)2112.0 < P43_ScaleA) P43_ScaleA = 2112.0f;   /* .data 00546108 (double) */
    }
  }
  InitXform_005263FE();
}

/* ---- 004f0f90 ---- */
/* P134_CamCine — Game.exe 004f0f90, cdecl.  Cinematic camera of a cutscene (active while 00c824a0 is set).
   t = elapsed (00c82430) / duration (00c823dc) in 0..4096.  Mode 2 (00c82504): linear move from 00c82420
   to 00c824f0 with the scale going from 00c82520 to 00c824dc.  Otherwise the camera height is kept
   relative to the road and the camera eases towards its goal by 1/8 per tick; finally it is aimed at
   the point 00c82448 (P126_Spawn + 8) and the angles are copied to the chase-camera state. */
void P134_CamCine(void) {
  if (P98_C824A0 == 0) return;
  if (P123_TgtMode == 0) P123_SideDist();
  P134_CamCollide(1);
  int32_t td = P123_TgtDist;
  int32_t t = (td != 0) ? (P127_SpawnD0 << 12) / td : 0x1000;   /* native: деление на 0 — 4096 */
  if (0x1000 < t) t = 0x1000;
  if (P127_SpawnCnt == 2) {
    float f = (float)t / 4096.0f;                               /* .data 005461ec */
    P44_CamX = (1.0f - f) * P134_Cine0[0] + P134_Cine1[0] * f;
    P44_CamY = (1.0f - f) * P134_Cine0[1] + P134_Cine1[1] * f;
    P44_CamZ = (1.0f - f) * P134_Cine0[2] + P134_Cine1[2] * f;
    P43_ScaleA = (1.0f - f) * P134_ScaleB + P134_ScaleE * f;
    P61_OffX = P44_CamX; P61_OffY = P44_CamY; P61_OffZ = P44_CamZ;
  } else {
    float o[3] = { P61_OffX, P61_OffY, P61_OffZ };
    int32_t h = P100_RoadHeightF(o);
    int32_t q = (td != 0) ? (P62_C82500 * P127_SpawnD0) / td : 0;
    int32_t k = (P123_TgtMode == 0) ? -200 - q : P62_C82434 + q;
    P61_OffY = (float)-h + (float)k;
    if (G6_00B5A778 == 0) {
      int32_t a = (int32_t)(P61_OffX - P44_CamX), b = (int32_t)(P61_OffY - P44_CamY), c = (int32_t)(P61_OffZ - P44_CamZ);
      P44_CamX = P44_CamX + (float)(a / 8);
      P44_CamY = P44_CamY + (float)(b / 8);
      P44_CamZ = P44_CamZ + (float)(c / 8);
    }
    if (P123_TgtMode == 2) P43_ScaleA = 784.0f - 0.097656f * (float)t;   /* .data 005469f0/005469f4 */
  }
  sync_cam();
  const uint8_t *sp = P126_Spawn + 8;
  look_xz(rdf(sp) - P44_CamX, P44_CamY + rdf(sp + 4), rdf(sp + 8) - P44_CamZ, 0);
  P61_V20 = (int32_t)(int16_t)P59_AngA;
  P61_V1C = (int32_t)(int16_t)P59_AngB;
  InitXform_005263FE();
}

/* ---- 00494620 ---- */
/* P134_TrafficHold — Game.exe 00494620, cdecl; reached only through the handler table at .data 00551308.
   Traffic-record state handler: while the countdown rec[0xb] runs, hold the car's steering at -575
   (0xfffffdc1); when it reaches 0 switch the record to state rec[1] = 2, rec[2] = 1.
   TODO(RE): unsure which traffic manoeuvre this is (a turn-in at a junction?). */
void P134_TrafficHold(uint8_t *rec) {
  uint8_t *c;
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) { int32_t i = rec[0] + 1; c = (i < P99_CARS_N) ? (uint8_t *)&P99_Cars[i] : NULL; }
  else
#endif
  c = P59_CarsTab + (uint32_t)rec[0] * 0x148;
  if (rec[0xb] != 0) {
    if (c != NULL) { uint32_t v = 0xfffffdc1u; memcpy(c + CAR_STEER, &v, 4); }   /* -575 */
    rec[0xb] = (uint8_t)(rec[0xb] - 1);
  } else { rec[1] = 2; rec[2] = 1; }
}
