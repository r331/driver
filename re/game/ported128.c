/* v1.73: ported128 — восстановлено из Game.exe. Все функции cdecl (work/rets.py: ret без операнда).
   004a706a — позиция копа (запись P12_0112da00) в клетках карты: тип клетки P54_RoadB → P110_CellTab, при mode = 0
     точка цели 0112b260/264 и P99_CopTarget; затем P127_MapWindow(x, z, адрес записи); +0xcc0 = 1; выход — смещение
     до точки +0xc64/+0xc6c. Ghidra: thunk_FUN_0050b957(x, z, rec).
   0049dc73 — свободная камера (P36_Pad2..5 двигают P61_OffX/Z на .data 00546100 = 32.0), камера догоняет на 1/10,
     углы P44_Atan2 (векторы ×256, делятся на 4, пока длина > 64000); 0052dfd4 — sqrt.
   004cd3fb — попадание точки (x, z) в прямоугольник части вида 4 модели клетки (флаг модели 0x100, список +0x34);
     0052e080 — fabs; второй аргумент не используется (вызов из ported121 передаёт 4 аргумента, cdecl).
   004c032a — деформация машины idx+1: карта повреждений (вид 0 — P28_Dst1, 1..11 — .data 00559254, P128_DmgMap),
     веса вершин P98_CarBufA (float), смещения P28_CarDelta, нормали граней P98_CarOpsB (шаг грани — G2_TABLE_00550ACC),
     P104_CarDents(idx+1), таймер P98_CarTimer = 50 − max/64 (не меньше 0); .data 005461ec = 4096.0.
   004949f0 — машина трафика на узле: точка ±0x28a по направлению +0x24, клетка ×P63_Scale, проверка занятости
     соседями TrafficRecs (|Δ| < 5 — выход), запись цели, P101_RoadNode, +0x18 = P101_RdDist, P118_TrafficTurn.
   0050d4a2 — поиск пути копа A* по окну 0x37×0x37 (узлы 0x20 — P77_C65DC0, куча {ключ, узел} — P77_B590E0,
     счётчик 00c595a0 — P12_00c595a0, соседи P12_00c7d800 / шаги P12_00574530, стоимость P77_C62E60, дороги P77_C7D8C0
     со сдвигами −1/+1/∓0x37 — .data 00c7d8bc/c4/7e4/99c); метки узлов — P62_Frame·0x20 + rec[0]; цель — P77_S574570,
     тогда 0050c087. Сравнение в просеивании вниз — «i < n» (как в оригинале).
   0050c087 — путь копа из цепочки родителей: записи 0x20 с +0x60 записи копа {след., пред. (uint32-адреса, re_rd_ptr —
     как P114_PathDraw), x, z, узел, sx/sy i16, тип i16, флаги +0x1a/+0x1e/+0x1f, угол +0x1c}; вставка срезов углов,
     склейка, сдвиг типа 9, удаление повторов, углы P44_Atan2; 1 — если нет поворота ≥ 0x400. Счётчик P77_C7D8A8 не
     обнуляется (как в оригинале). Области путей 8 записей копа (+0x40..+0xcb4) — в k_regions (game/reptr.c).
   004a742a — перепланирование пути копа: P59_NearCars, P128_CopMapPos(mode 0), продолжение старого пути (+0xcb8)
     или новый поиск от центра окна (узел 0x5e8; стоимость центра — .data 00c64600 = P77_C62E60[0x5e8]).
   00490bcb — отрисовка машин трафика в пределах P11_01270c24 (dist8 до P44_CamX/Z): режим смешивания P12_Fn00426580
     (4 / 0x19 по +0xd записи, при 00575f44 ≠ 0 — по значениям 0..0x31), 004a1037 (не перенесена, V-строка
     P128_Fn4A1037) и P107_TrafficLights.
   0050a15b — площадь многоугольника {x, y, след.} (список, след. — uint32-адрес +8), отсечённого прямоугольником
     rect {x0, y0, x1, y1} (Сазерленд — Ходжмен: x ≥ x0, x ≤ x1, y ≥ y0, y ≤ y1; при входе в область — повтор шага от
     точки пересечения), формула площади Гаусса /2 по модулю. Списки на стеке оригинала — массивы в native. */
#include "ported128.h"
#include "p128_data.h"
#include "ported127.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "director.h"
#include "directorstorage.h"
#include "smallfuncs2.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported29.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported48.h"
#include "ported54.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported72.h"
#include "ported74.h"
#include "ported75.h"
#include "ported77.h"
#include "ported78.h"
#include "ported79.h"
#include "ported80.h"
#include "ported82.h"
#include "ported88.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported104.h"
#include "ported107.h"
#include "ported110.h"
#include "ported113.h"
#include "ported114.h"
#include "ported115.h"
#include "ported116.h"
#include "ported117.h"
#include "ported119.h"
#include "ported121.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported126.h"
#include "ported28.h"
#include "ported42.h"
#include "ported118.h"
#include "ported108.h"
#include "ported107.h"
#include "ported101.h"
#include "ported88.h"
#include "menustate.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
p128_dmg_t P128_DmgMap = P128_DMG_INIT;          /* .data 00559254 */
GAME_VAR_DEF(int32_t, P128_FreeCamLock, 0x01137304)
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static uint16_t rdu16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wr16(void *p, int16_t v) { memcpy(p, &v, 2); }
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
#define P128_CAR(i)  ((uint8_t *)&P99_Cars[(i)])
static uint8_t *tcar(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) return (i + 1 >= 0 && i + 1 < P99_CARS_N) ? P128_CAR(i + 1) : P128_CAR(P99_CARS_N - 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}

/* ---- 004a706a ---- */
static int32_t cell_type(int32_t x, int32_t z) {
  int32_t N = P62_MapN;
  if (N <= 0) return 0;                                     /* защита деления: в оригинале нет */
  uint32_t cx = (uint32_t)(x / N); int32_t cz = z / N;
  uint32_t sel = ((uint32_t)((P72_Rows - 1) - cz) & 1u) << 1 | (cx & 1u);
  const uint8_t *b = (const uint8_t *)P54_RoadB[sel];
  if (b == NULL) return 0;                                  /* защита: карта не загружена */
  const uint8_t *p = b + (z - cz * N) * N * 4 + 2 + (x - (int32_t)cx * N) * 4;
  uint16_t v0 = rdu16(p), v1 = rdu16(p + 2);
  return P110_CellTab[(int32_t)(v0 & 0x3c00) >> 9 | (v1 & 1)];
}
void P128_CopMapPos(uint32_t *rec, int32_t *dx, int32_t *dz, int32_t mode) {
  uint8_t *r = (uint8_t *)rec;
  P11_00ba52d0 = fround((float)(PlayerPosX + 0x2ee + P62_MapC64) * P63_Scale);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = fround((float)(P62_Map2C40 - (PlayerPosZ - 0x2ee)) * P63_Scale);
  if (mode == 0) {
    int32_t ty = cell_type(px, P11_00ba52d0);
    wr32(r + 0x48, P97_B260); wr32(r + 0x4c, P97_B264);
    if (P95_AmbN != 0 && (P97_B290 == 0 || ty != 0x1000)) {
      wr32(r + 0x48, PlayerPosX); P97_B260 = PlayerPosX;
      wr32(r + 0x4c, PlayerPosZ); P97_B264 = PlayerPosZ;
      P97_B290 = 1;
    }
    P99_CopTarget((int32_t *)rec);
  } else {
    wr32(r + 0x48, PlayerPosX); wr32(r + 0x4c, PlayerPosZ);
  }
  int32_t zz = P62_Map2C40 - (rd32(r + 0x4c) - 0x2ee);
  P11_00ba52d0 = fround((float)(rd32(r + 0x48) + 0x2ee + P62_MapC64) * P63_Scale);
  wr32(r + 0x50, P11_00ba52d0);
  int32_t x = rd32(r + 0x50);
  P11_00ba52d0 = fround((float)zz * P63_Scale);
  wr32(r + 0x54, P11_00ba52d0);
  int32_t z = rd32(r + 0x54);
  P11_00ba52d0 = fround((float)(rd32(r + 0xc64) + 0x2ee + P62_MapC64) * P63_Scale);
  int32_t tx = P11_00ba52d0;
  P11_00ba52d0 = fround((float)(P62_Map2C40 - (rd32(r + 0xc6c) - 0x2ee)) * P63_Scale);
  int32_t tz = P11_00ba52d0;
  P97_B288 = z; P97_B28C = x;
  P127_MapWindow(x, z, re_addr(rec));
  wr32(r + 0xcc0, 1);
  *dx = x - tx; *dz = z - tz;
}

/* ---- 0049dc73 ---- */
void P128_FreeCam(int32_t car) {
  const float step = 32.0f;                                  /* .data 00546100 */
  if (P36_Pad3 != 0) P61_OffZ += step;
  if (P36_Pad2 != 0) P61_OffZ -= step;
  if (P36_Pad4 != 0) P61_OffX -= step;
  if (P36_Pad5 != 0) P61_OffX += step;
  P11_00ba52d0 = fround(P61_OffX - P44_CamX); int32_t ix = P11_00ba52d0;
  P11_00ba52d0 = fround(P61_OffY - P44_CamY); int32_t iy = P11_00ba52d0;
  P11_00ba52d0 = fround(P61_OffZ - P44_CamZ);
  if ((G6_00B5A778 == 0 || P29_Mode != 0) && P128_FreeCamLock == 0) {
    P44_CamX += (float)(ix / 10);
    P44_CamY += (float)(iy / 10);
    P44_CamZ += (float)(P11_00ba52d0 / 10);
#ifndef RE_HOOK_BUILD
    P59_VX = P44_CamX; P59_VY = P44_CamY; P59_VZ = P44_CamZ;    /* псевдонимы 00b1c270.. */
#endif
  }
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= P99_CARS_N) return;                 /* защита индекса: в оригинале нет */
#endif
  const uint8_t *c = P128_CAR(car);
  float fx = (float)rd32(c + 0xc8) - P44_CamX;
  float fy = P44_CamY + (float)rd32(c + 0xcc);
  float fz = (float)rd32(c + 0xd0) - P44_CamZ;
  float d = (float)sqrt((double)(fz * fz + fx * fx));
  P11_00ba52d0 = fround(d);  int32_t len = P11_00ba52d0 << 8;
  P11_00ba52d0 = fround(fx); int32_t vx = P11_00ba52d0 << 8;
  P11_00ba52d0 = fround(fy); int32_t vy = P11_00ba52d0 << 8;
  P11_00ba52d0 = fround(fz); int32_t vz = P11_00ba52d0 << 8;
  for (; 64000 < len; len /= 4) { vx /= 4; vy /= 4; vz /= 4; }
  uint16_t a = (uint16_t)((uint16_t)((int16_t)P44_Atan2(len, vy) - 0x400) & 0xfff);
  P59_AngA = a;
#ifndef RE_HOOK_BUILD
  P11_00b1c268 = (uint8_t)a;                                 /* псевдоним 00b1c268 */
#endif
  P59_AngB = (uint16_t)(-(int16_t)P44_Atan2(vx, vz) & 0xfff);
  P59_AngC = 0;
  InitXform_005263FE();
}

/* ---- 004cd3fb ---- */
int32_t P128_ModelHit(float x, float y, float z, uint32_t w) {
  (void)y; (void)w;
  P11_00ba52d0 = fround((x + (float)P42_CellX) * P42_CellScale);
  int32_t gx = P11_00ba52d0;
  P11_00ba52d0 = fround((z + (float)P42_CellY) * P42_CellScale);
  int32_t gz = P11_00ba52d0;
  int32_t N = P54_GridN;
  if (N <= 0 || G6_00D01268 == NULL || G6_00CE0F20 == NULL || G6_00D00208 == NULL) return 0;   /* защита */
  uint32_t bx = (uint32_t)(gx / N); int32_t bz = gz / N;
  int32_t cell = ((int32_t)(bx & 1) + (bz & 1) * 2) * N * N + (gx - (int32_t)bx * N) + (gz - bz * N) * N;
  if (cell < 0 || cell >= 4 * N * N) return 0;                                                 /* защита */
  int32_t node = ((const int32_t *)G6_00D01268)[cell];
  for (int32_t guard = 0; guard < 0x14000; guard++) {                                          /* защита */
    if (node == -1) return 0;
    if (node < 0 || node >= 0x14000) return 0;                                                 /* защита */
    const int32_t *nd = (const int32_t *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    const uint8_t *o = (const uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
    int32_t mi = rd32(o + 4);
    uint32_t mr = ((uint32_t)mi < 1126u) ? P79_ModelTab[mi] : 0;
    const uint8_t *m = mr ? (const uint8_t *)P79_PTR(mr) : NULL;
    if (m != NULL && (rd32(m + 8) & 0x100) != 0 && rd32(m + 0x34) != 0) {
      P11_00ba52d0 = fround(rdf(m + 0x10));
      int32_t r2 = P11_00ba52d0 * P11_00ba52d0;
      P11_00ba52d0 = fround((float)fabs((double)(rdf(o + 8) - x)));
      int32_t ex = P11_00ba52d0;
      P11_00ba52d0 = fround((float)fabs((double)(rdf(o + 0x10) - z)));
      if (ex * ex + P11_00ba52d0 * P11_00ba52d0 < r2) {
        const uint8_t *lst = (const uint8_t *)P79_PTR((uint32_t)rd32(m + 0x34));
        int32_t cnt = rd32(lst);
        const uint8_t *e = lst + 4;
        for (int32_t k = 0; k < cnt; k++, e += 20) {
          if (rd16(e) != 4 || P56_EulerTab == NULL) continue;
          float dx = x - rdf(o + 8), dz = z - rdf(o + 0x10);
          const float *mt = (const float *)(const void *)(P56_EulerTab + ((uint32_t)rd32(o + 0x18) & 0xfffu) * 0x40);
          float u = (dz * mt[6] + dx * mt[0]) - (float)rd16(e + 2);
          float v = (dz * mt[8] + dx * mt[2]) - (float)rd16(e + 6);
          float uu = u;
          if (rd16(e + 10) != 0) {
            mt = (const float *)(const void *)(P56_EulerTab + ((uint32_t)(int32_t)rd16(e + 10) & 0xfffu) * 0x40);
            uu = v * mt[6] + u * mt[0];
            v = v * mt[8] + u * mt[2];
          }
          float hw = (float)((int32_t)rd16(e + 14) >> 1), hd = (float)((int32_t)rd16(e + 18) >> 1);
          if (-hw < uu && uu < hw && -hd < v && v < hd) return 1;
        }
      }
    }
    node = nd[1];
  }
  return 0;
}

/* ---- 004c032a ---- */
void P128_CarDeform(int32_t idx) {
  int32_t car = idx + 1, mx = 0;
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= P99_CARS_N || car > 0x40 || car >= 0x44) return;   /* защита индекса: в оригинале нет */
#endif
  uint32_t kind = (car == 0) ? 0u : (uint32_t)TrafficRecs[idx * 0x54 + 0xc];
  P98_CarKind[car] = 0xff;
#ifndef RE_HOOK_BUILD
  if (kind >= 12 || P28_CarClean[kind] == 0) return;        /* native: модель не загружена */
#endif
  uint8_t *mdl = (uint8_t *)P79_PTR(P28_CarClean[kind]);
  uint8_t *ops = P98_CarOpsA + car * 0x1040;
  uint32_t nv = rdu16(mdl + 0x14), nf = rdu16(mdl + 0x16);
#ifndef RE_HOOK_BUILD
  if (nv > 0x104) nv = 0x104;                                /* защита: буферы на 0x104 вершин */
  if (nf > 0x170) nf = 0x170;
#endif
  P44_Copy4(ops, P79_PTR((uint32_t)rd32(mdl + 0x20)), nv << 4);
  float *buf = (float *)(void *)P98_CarBufA;
  memset(buf, 0, 0x410);
  const uint8_t *map = (kind == 0) ? P28_Dst1 : P128_DmgMap + (kind - 1) * 0x1e0;
  for (int32_t side = 0; side < 6; side++) {
    int32_t v = rd32(P128_CAR(car) + 0x11c + side * 4);
    if (mx < v) mx = v;
    for (int32_t k = 0; k < 0x50; k++) {
      uint8_t b = map[k + side * 0x50];
      if (b == 0xff) break;
      if (buf[b] == 0.0f) buf[b] = (float)v + buf[b];
      else { P11_00ba52d0 = fround(buf[b]); buf[b] = (float)((P11_00ba52d0 + v) >> 1); }
      if (4096.0f < buf[b]) buf[b] = 4096.0f;
    }
  }
  float *o = (float *)(void *)ops;
  const float *dl = &P28_CarDelta[kind][0];
  for (uint32_t k = 0; k < nv && k < 0x100; k++) {      /* счётчик — байт (bVar10) */
    P11_00ba52d0 = fround(buf[k]);
    int32_t r = P11_00ba52d0;
    o[0] = (float)r * dl[0] + o[0];
    o[1] = (float)r * dl[1] + o[1];
    o[2] = (float)r * dl[2] + o[2];
    o += 4; dl += 4;
  }
  const uint8_t *f = (const uint8_t *)P79_PTR((uint32_t)rd32(mdl + 0x2c));
  float *n = (float *)(void *)(P98_CarOpsB + car * 0x1700);
  const float *vb = (const float *)(void *)ops;
  for (uint32_t i = 0; i < nf; i++) {
    uint32_t i0 = (uint32_t)rd32(f + 8), i1 = (uint32_t)rd32(f + 0xc), i2 = (uint32_t)rd32(f + 0x10);
#ifndef RE_HOOK_BUILD
    if (i0 >= 0x104 || i1 >= 0x104 || i2 >= 0x104) break;   /* защита индексов */
#endif
    const float *a = vb + i0 * 4, *b = vb + i1 * 4, *c = vb + i2 * 4;
    float x = b[0], y = b[1], z = b[2];
    float nx = -((a[1] - y) * (c[2] - z) - (a[2] - z) * (c[1] - y));
    float ny = -((a[2] - z) * (c[0] - x) - (a[0] - x) * (c[2] - z));
    float nz = -((a[0] - x) * (c[1] - y) - (a[1] - y) * (c[0] - x));
    float l = (float)sqrt((double)(nz * nz + ny * ny + nx * nx));
    if (l == 0.0f) l = 1.0f;
    l = 1.0f / l;
    n[0] = nx * l; n[1] = ny * l; n[2] = nz * l;
    n[3] = z * n[2] + y * n[1] + x * n[0];
    int32_t st = G2_TABLE_00550ACC[*f];
    if (st <= 0) break;                                       /* защита: в оригинале нет */
    f += st; n += 4;
  }
  P104_CarDents(car);
  mx = 0x32 - (mx >> 6);
  if (mx < 0) mx = 0;
  wr32(P98_CarTimer + car * 4, mx);
}

/* ---- 004949f0 ---- */
void P128_TrafficNode(uint8_t *t) {
  uint8_t *car = tcar(t[0]);
  int32_t x = rd32(car + 200), z = rd32(car + 0xd0);
  switch (rd32(t + 0x24)) {
  case 0: x -= 0x28a; break;
  case 1: z += 0x28a; break;
  case 2: x += 0x28a; break;
  case 3: z -= 0x28a; break;
  }
  P11_00ba52d0 = fround((float)x * P63_Scale);
  int32_t gx = P11_00ba52d0;
  wr32(t + 0x48, rd32(car + 200) + 0x2ee);
  wr32(t + 0x4c, rd32(car + 0xd0) - 0x2ee);
  P11_00ba52d0 = fround((float)rd32(t + 0x48) * P63_Scale); wr32(t + 0x48, P11_00ba52d0);
  P11_00ba52d0 = fround((float)rd32(t + 0x4c) * P63_Scale); wr32(t + 0x4c, P11_00ba52d0);
  int32_t n = P21_EntryCount;
  if (n > 0x40) n = 0x40;                                   /* защита: TrafficRecs — 0x40 записей */
  int32_t dir = rd32(t + 0x24);
  for (int32_t k = 0; k < n; k++) {
    const uint8_t *o = TrafficRecs + k * 0x54;
    if (t[0] == o[0] || o[1] == 0 || rd32(t + 0x28) != rd32(o + 0x28)) continue;
    if ((dir & 1) == 0) {
      if (rd32(o + 0x48) != gx) continue;
      if (dir == 0 ? rd32(t + 0x4c) <= rd32(o + 0x4c) : rd32(o + 0x4c) <= rd32(t + 0x4c))
        if (iabs(rd32(o + 0x4c) - rd32(t + 0x4c)) < 5) return;
    } else {
      if (rd32(o + 0x4c) != rd32(t + 0x4c)) continue;
      if (dir == 1 ? rd32(t + 0x48) <= rd32(o + 0x48) : rd32(o + 0x48) <= rd32(t + 0x48))
        if (iabs(rd32(o + 0x48) - rd32(t + 0x48)) < 5) return;
    }
  }
  if ((dir & 1) == 0) {
    wr32(t + 0x40, x); t[0x44] = 0xff; t[0x45] = 0xff; t[0x46] = 0xff; t[0x47] = 0x7f;
  } else {
    t[0x40] = 0xff; t[0x41] = 0xff; t[0x42] = 0xff; t[0x43] = 0x7f; wr32(t + 0x44, z);
  }
  t[0x13] = 0x23; t[1] = 2; t[8] = 1;
  t[0x3c] = 0x82; t[0x3d] = 0; t[0x3e] = 0; t[0x3f] = 0; t[7] = 0;
  P101_RoadNode(x, z, (int8_t)t[0x24]);
  wr32(t + 0x18, P101_RdDist);
  P118_TrafficTurn(t);
}

/* ---- 0050c087 / 0050d4a2 ---- */
#define P128_PATH_MAX ((0xcb4 - 0x60) / 0x20)               /* записей пути до P74_Cars (+0xcb4) */
static uint8_t *nxp(const uint8_t *e) { return (uint8_t *)re_rd_ptr(e); }
static uint8_t *prp(const uint8_t *e) { return (uint8_t *)re_rd_ptr(e + 4); }
static void setn(uint8_t *e, const uint8_t *q) { re_wr_ptr(e, q); }
static void setp(uint8_t *e, const uint8_t *q) { re_wr_ptr(e + 4, q); }
static int32_t road(int32_t n) { return (n >= 0 && n < 0xbd1) ? rd32(P77_C7D8C0 + n * 4) : 0; }   /* защита индекса */
static uint8_t *node(int32_t n) { return P77_C65DC0 + (uint32_t)n * 0x20; }
static int32_t ndv(int32_t n, int32_t off) { return (n >= 0 && n < 0xbd1) ? rd32(node(n) + off) : -1; }
static int32_t path_ins(uint8_t *base, uint8_t *p, uint8_t *nx, int32_t ds, int32_t dy, int32_t ax, int32_t az) {
  if (P77_C7D8A8 < 0 || P77_C7D8A8 >= P128_PATH_MAX) return 0;   /* защита: в оригинале нет */
  uint8_t *q = base + P77_C7D8A8 * 0x20;
  P77_C7D8A8++;
  memmove(q, p, 0x20);
  setn(p, q);
  q[0x1f] = 1; q[0x1a] = 0; wr16(q + 0x18, 0);
  setn(q, nx); setp(q, p); setp(nx, q);
  wr16(q + 0x14, (int16_t)(rd16(q + 0x14) + ds));
  wr16(q + 0x16, (int16_t)(rd16(q + 0x16) + dy));
  wr32(q + 8, rd32(q + 8) + ax); wr32(q + 0xc, rd32(q + 0xc) + az);
  return 1;
}
int32_t P128_CopPath(uint8_t *rec) {
  int32_t c = P77_S574570;
  uint8_t *base = rec + 0x60;
  int32_t X = rd32(rec + 0x48); X += (X < 0 ? -1 : 1) * 0x2ee;
  int32_t Z = rd32(rec + 0x4c); Z += (Z < 0 ? -1 : 1) * 0x2ee;
  X -= X % 0x5dc; Z -= Z % 0x5dc;
  for (int32_t g = 0; c != -1 && g < 0xbd1; g++) { P77_C7D8A8++; c = ndv(c, 0xc); }   /* g — защита */
  c = P77_S574570;
  int32_t pre = (rd32(rec + 0xcb8) == 1) ? P77_C65DA4 : 0;
  if (P77_C7D8A8 < 1 || P77_C7D8A8 + pre > P128_PATH_MAX || pre < 0 || pre > 8) return 0;   /* защита: в оригинале нет */
  uint8_t *e = rec + 0x40 + P77_C7D8A8 * 0x20 + pre * 0x20;
  for (int32_t i = 0; i < P77_C7D8A8; i++) {
    wr32(e + 8, ndv(c, 0x10));
    wr32(e + 0xc, -ndv(c, 0x14));
    wr32(e + 0x10, c);
    wr16(e + 0x18, (int16_t)((c >= 0 && c < 0xbd1) ? rd32(P77_C62E60 + c * 4) : 0));
    setn(e, i == 0 ? NULL : e + 0x20);
    setp(e, i == P77_C7D8A8 - 1 ? NULL : e - 0x20);
    c = ndv(c, 0xc);
    e[0x1a] = 0; e[0x1f] = 0;
    e -= 0x20;
  }
  if (pre != 0) {
    e = base;
    for (int32_t i = 0; i < pre; i++) {
      memcpy(e, P77_C62D60 + i * 0x20, 0x20);
      setp(e, i == 0 ? NULL : e - 0x20);
      setn(e, e + 0x20);
      e[0x1a] = 1;
      e += 0x20;
    }
    setp(e, e - 0x20);
    P77_C7D8A8 += pre;
  }
  int32_t l28 = (rd32(rec + 0x68) + 0x1b) * 4;
  int32_t l34 = (0x1b - rd32(rec + 0x6c)) * 4;
  int32_t dir = 0;                                          /* в оригинале не инициализирован */
  uint8_t *p = base + pre * 0x20;
  for (int32_t g = 0; p != NULL && g < 0x400; g++) {        /* g — защита */
    uint8_t *nx = nxp(p);
    if (p[0x1f] == 0) {
      if (P77_C7D850 != 0) P108_FillRect((float)l28, (float)l34, 4.0f, 4.0f, 0x1f1f1f);
      if (nx == NULL) {
        wr32(p + 8, rd32(p + 8) * 0x5dc + X);
        wr32(p + 0xc, rd32(p + 0xc) * 0x5dc + Z);
      } else {
        int32_t dx = rd32(p + 8) - rd32(nx + 8);
        int32_t dz = rd32(nx + 0xc) - rd32(p + 0xc);
        if (dz < 0) dir = dx < 0 ? 7 : (dx < 1 ? 0 : 1);
        else if (dz < 1) { if (dx < 0) dir = 6; else if (0 < dx) dir = 2; }
        else dir = dx < 0 ? 5 : (dx < 1 ? 4 : 3);
        p[0x1e] = (uint8_t)dir;
        if (p[0x1a] == 0) {
          wr32(p + 8, rd32(p + 8) * 0x5dc + X);
          wr32(p + 0xc, rd32(p + 0xc) * 0x5dc + Z);
          wr16(p + 0x14, (int16_t)l28); wr16(p + 0x16, (int16_t)l34);
        }
        if (rd16(p + 0x18) != 9) {
          int32_t n = rd32(p + 0x10);
          switch (dir) {
          case 1:
            if (road(n + 0x37) == 0) { if (road(n - 1) != 0) path_ins(base, p, nx, -1, 3, -0x177, -0x465); }
            else path_ins(base, p, nx, -3, 1, -0x465, -0x177);
            break;
          case 3:
            if (road(n - 0x37) == 0) { if (road(n - 1) != 0) path_ins(base, p, nx, -1, -3, -0x177, 0x465); }
            else path_ins(base, p, nx, -3, -1, -0x465, 0x177);
            break;
          case 5:
            if (road(n - 0x37) == 0) { if (road(n + 1) != 0) path_ins(base, p, nx, 1, -3, 0x177, 0x465); }
            else path_ins(base, p, nx, 3, -1, 0x465, 0x177);
            break;
          case 7:
            if (road(n + 0x37) == 0) { if (road(n + 1) != 0) path_ins(base, p, nx, 1, 3, 0x177, -0x465); }
            else path_ins(base, p, nx, 3, 1, 0x465, -0x177);
            break;
          }
        }
        l28 += dx * -4; l34 += dz * -4;
      }
      if (nx == NULL) { wr16(p + 0x14, (int16_t)l28); wr16(p + 0x16, (int16_t)l34); }
    }
    p = nx;
  }
  p = base + pre * 0x20;
  for (int32_t g = 0; p != NULL && g < 0x400; g++) {
    uint8_t *nx = nxp(p), *pr = prp(p);
    if (pr != NULL && pr[0x1f] == 0 && nx != NULL) {
      if (nx[0x1f] == 0) {
        uint8_t *n2 = nxp(nx);
        if (n2 != NULL) {
          if (p[0x1f] == 0) {
            if (nx[0x1f] == 0 && (((p[0x1e] & 1) == 0 && (nx[0x1e] & 1) != 0) || ((p[0x1e] & 1) != 0 && (nx[0x1e] & 1) == 0))) {
              if (p[0x1e] == n2[0x1e] && n2[0x1f] == 0) {
                nx = nxp(n2); setn(p, nx);
                if (nx != NULL) setp(nx, p);
                P77_C7D8A8 -= 2;
              } else {
                setn(p, n2); setp(n2, p); P77_C7D8A8--; nx = n2;
              }
            }
          } else if (n2[0x1f] == 0 || p[0x1e] == n2[0x1e]) {
            setn(p, n2); setp(n2, p); P77_C7D8A8--; nx = n2;
          }
        }
      } else {
        setn(pr, nx); setp(nx, pr); P77_C7D8A8--;
      }
    }
    p = nx;
  }
  for (p = base; p != NULL; p = nxp(p)) {
    uint8_t *pr = prp(p);
    if (rd16(p + 0x18) != 9 || pr == NULL) continue;
    int32_t n = rd32(p + 0x10);
    uint32_t m = (n >= 0 && n < 0xbd3) ? (uint32_t)rd32(P77_C5FE00 + n * 4) : 0u;
    switch (pr[0x1e]) {
    case 0: case 4:
      if ((m & 10) == 0) { wr16(p + 0x14, (int16_t)(rd16(p + 0x14) - 1)); wr32(p + 8, rd32(p + 8) - 0x177); }
      else { wr16(p + 0x14, (int16_t)(rd16(p + 0x14) + 1)); wr32(p + 8, rd32(p + 8) + 0x177); }
      break;
    case 2: case 6:
      if ((m & 6) == 0) { wr16(p + 0x16, (int16_t)(rd16(p + 0x16) - 1)); wr32(p + 0xc, rd32(p + 0xc) + 0x177); }
      else { wr16(p + 0x16, (int16_t)(rd16(p + 0x16) + 1)); wr32(p + 0xc, rd32(p + 0xc) - 0x177); }
      break;
    }
  }
  for (p = base; p != NULL; ) {
    uint8_t *nx = nxp(p);
    if (nx != NULL && rd32(p + 8) == rd32(nx + 8) && rd32(p + 0xc) == rd32(nx + 0xc)) {
      uint8_t *n2 = nxp(nx);
      setn(p, n2);
      if (n2 != NULL) setp(n2, p);
      P77_C7D8A8--;
      nx = p;
    }
    p = nx;
  }
  if (P77_C7D8A8 <= 0) return 0;
  for (p = base; p != NULL; ) {
    uint8_t *nx = nxp(p);
    if (nx == NULL) wr16(p + 0x1c, -1);
    else wr16(p + 0x1c, (int16_t)((uint16_t)P44_Atan2(rd32(nx + 8) - rd32(p + 8), rd32(nx + 0xc) - rd32(p + 0xc)) & 0xfff));
    p = nx;
  }
  p = base;
  for (;;) {
    uint8_t *cur, *nx;
    do {
      cur = p;
      if (cur == NULL) return 1;
      p = nx = nxp(cur);
    } while (nx == NULL || rd16(nx + 0x1c) == -1);
    int32_t d = ((((int32_t)rd16(cur + 0x1c) - (int32_t)rd16(nx + 0x1c)) + 0x800) & 0xfff) - 0x800;
    if (iabs(d) >= 0x400) return 0;
  }
}

static int32_t hkey(int32_t i) { return rd32(P77_B590E0 + i * 8); }
static int32_t hval(int32_t i) { return rd32(P77_B590E0 + i * 8 + 4); }
static void hset(int32_t i, int32_t k, int32_t v) { wr32(P77_B590E0 + i * 8, k); wr32(P77_B590E0 + i * 8 + 4, v); }
int32_t P128_CopRoute(int32_t *rec, int32_t dx, int32_t dz, int32_t start) {
  if (iabs(dx) >= 0x1c || iabs(dz) >= 0x1c) return 0;
#ifndef RE_HOOK_BUILD
  if (start < 0 || start >= 0xbd1) return 0;                /* защита индекса */
#endif
  if (rec[0x32e] == 1) {
    uint8_t *e = (uint8_t *)(rec + 0x18);
    for (int32_t k = rec[5]; k != 0 && e != NULL; k--) e = nxp(e);
    for (int32_t i = 0; i < P77_C65DA4 && i < 8 && e != NULL; i++) {   /* i < 8, e — защита */
      memcpy(P77_C62D60 + i * 0x20, e, 0x20);
      e = nxp(e);
    }
  }
  int32_t tag = P62_Frame * 0x20 + rec[0];
  uint8_t *s = node(start);
  wr32(s + 0x10, dx); wr32(s + 0x14, dz); wr32(s + 0, 0);
  wr32(s + 4, (iabs(dx) + iabs(dz)) * 2);
  wr32(s + 8, rd32(s + 0) + rd32(s + 4));
  wr32(s + 0xc, -1); wr32(s + 0x1c, tag);
  hset(1, rd32(s + 8), start);
  P12_00c595a0 = 1;
  for (;;) {
    int32_t cur = hval(1);
    if (P12_00c595a0 == 0) return 0;
    int32_t cnt = P12_00c595a0;
#ifndef RE_HOOK_BUILD
    if (cnt < 1 || cnt > 0x200) return 0;                   /* защита кучи */
#endif
    hset(1, hkey(cnt), hval(cnt));
    P12_00c595a0 = --cnt;
    for (int32_t i = 2, j = 1; i < cnt; ) {
      int32_t c = i;
      if (i + 1 < cnt && hkey(i + 1) < hkey(i)) c = i + 1;
      int32_t k = hkey(c), kj = hkey(j);
      if (kj <= k) break;
      int32_t vc = hval(c), vj = hval(j);
      hset(c, kj, vj); hset(j, k, vc);
      j = c; i = c * 2;
    }
    if (cur == P77_S574570) return P128_CopPath((uint8_t *)rec);
#ifndef RE_HOOK_BUILD
    if (cur < 0 || cur >= 0xbd1) return 0;                  /* защита индекса */
#endif
    uint8_t *cn = node(cur);
    for (P77_B5A0E8 = 7; ; ) {
      int32_t d = P77_B5A0E8;
      int32_t nb = cur + P12_00c7d800[d];
      int32_t cost = (nb >= 0 && nb < 0xbd1) ? rd32(P77_C62E60 + nb * 4) : 0x1000;   /* защита индекса */
      if (cost < 0x1000) {
        int skip = 0;
        if ((d & 1) == 0) {
          switch (d) {
          case 0: skip = road(cur - 1) != 0 && road(cur - 0x37) != 0; break;
          case 2: skip = road(cur + 1) != 0 && road(cur - 0x37) != 0; break;
          case 4: skip = road(cur + 1) != 0 && road(cur + 0x37) != 0; break;
          case 6: skip = road(cur - 1) != 0 && road(cur + 0x37) != 0; break;
          }
          cost += 2;
        }
        if (!skip) {
          uint8_t *bn = node(nb);
          int32_t gc = rd32(cn + 0) + cost;
          int32_t nx = 0, nz = 0;
          if ((gc <= rd32(bn + 0) || (rd32(bn + 0x1c) != tag && rd32(bn + 0x18) != tag)) &&
              (nx = rd32(cn + 0x10) + P12_00574530[d * 2], -0x1b < nx) && nx < 0x1b &&
              (nz = rd32(cn + 0x14) + P12_00574530[d * 2 + 1], -0x1b < nz) && nz < 0x1b) {
            wr32(bn + 0xc, cur); wr32(bn + 0, gc); wr32(bn + 0x18, tag - 0x10);
            wr32(bn + 0x10, nx); wr32(bn + 0x14, nz);
            int32_t h = (iabs(nz) + iabs(nx)) * 2;
            wr32(bn + 4, h); wr32(bn + 8, gc + h);
            if (rd32(bn + 0x1c) != tag) {
              uint32_t u = (uint32_t)++P12_00c595a0;
#ifndef RE_HOOK_BUILD
              if (u > 0x200) return 0;                      /* защита кучи */
#endif
              hset((int32_t)u, rd32(bn + 8), nb);
              while (u != 1) {
                uint32_t pu = u >> 1;
                int32_t ku = hkey((int32_t)u), kp = hkey((int32_t)pu);
                if (kp <= ku) break;
                int32_t vu = hval((int32_t)u), vp = hval((int32_t)pu);
                hset((int32_t)u, kp, vp); hset((int32_t)pu, ku, vu);
                u = pu;
              }
              wr32(bn + 0x1c, tag);
            }
          }
        }
      }
      P77_B5A0E8 = d - 1;
      if (d == 0) break;
    }
    wr32(cn + 0x1c, tag - 0x10);
    wr32(cn + 0x18, tag);
  }
}

/* ---- 004a742a ---- */
void P128_CopReplan(uint8_t *rec) {
  int32_t near = P59_NearCars((const int32_t *)(const void *)rec);
  int32_t go = 0, cx = 0, cz = 0, res = 0;
  if (rd32(rec + 0xcb8) == 0) go = 1;
  else if (rd32(rec + 0x14) == rd32(rec + 0x18) || (rd32(rec + 0x14) < 2 && near == 0)) {
    if (rd32(rec + 0xcc8) == 0) {
      int32_t ax = iabs(rd32(rec + 0x48) - PlayerPosX), az = iabs(rd32(rec + 0x4c) - PlayerPosZ);
      int32_t d = ax < az ? az + ax / 2 : ax + az / 2;
      if (3000 < d) go = 1;
    }
  } else go = 1;
  if (go != 1) return;
  P128_CopMapPos((uint32_t *)(void *)rec, &cx, &cz, 0);
  P77_C7D8A8 = 0;
  if (rd32(P77_C62E60 + 0x5e8 * 4) == 0x1000) return;
  if (rd32(rec + 0x1c) - 2 < rd32(rec + 0x14)) wr32(rec + 0xcb8, 0);
  if (rd32(rec + 0xcb8) == 1) {
    int32_t solid = 0;
    P77_C65DA4 = 0;
    wr32(rec + 0x14, rd32(rec + 0x14) - 1);
    uint8_t *e = rec + 0x60;
    for (int32_t k = rd32(rec + 0x14); k != 0 && e != NULL; k--) e = nxp(e);   /* e != NULL — защита */
    for (int32_t g = 0; e != NULL && g < 0x400; g++) {
      P77_C65DA4++;
      uint8_t *nx = nxp(e);
      if (e[0x1f] == 0) solid++;
      e = nx;
      if (1 < solid && (nx == NULL || nx[0x1f] == 0)) break;
    }
    if (rd32(rec + 0x1c) - rd32(rec + 0x14) <= P77_C65DA4) wr32(rec + 0xcb8, 0);
  }
  if (rd32(rec + 0xcb8) == 1) {
    uint8_t *e = rec + 0x60;
    for (int32_t k = rd32(rec + 0x14) + P77_C65DA4; k != 0; k--) { uint8_t *nx = nxp(e); if (nx != NULL) e = nx; }
    int32_t n = rd32(e + 0x10);
    int32_t dx = (n % 0x37 - 0x1b) - (P97_B28C - rd32(rec + 4));
    int32_t dz = (n / 0x37 - 0x1b) - (P97_B288 - rd32(rec + 8));
    res = P128_CopRoute((int32_t *)(void *)rec, dx, dz, dx + 0x1b + (dz + 0x1b) * 0x37);
  } else {
    int32_t s = (0x1b - cx) + (0x1b - cz) * 0x37;
    res = P128_CopRoute((int32_t *)(void *)rec, s % 0x37 - 0x1b, s / 0x37 - 0x1b, s);
  }
  if (res == 1 && 1 < P77_C7D8A8) {
    wr32(rec + 0x2c, 0x78); wr32(rec + 0x14, 1); wr32(rec + 0x18, 1);
    wr32(rec + 0x1c, P77_C7D8A8); wr32(rec + 0xcb8, 1);
  } else wr32(rec + 0xcb8, 0);
  wr32(rec + 4, P97_B28C); wr32(rec + 8, P97_B288);
}

/* ---- 00490bcb ---- */
static void draw_one(uint32_t i) {
  P128_Fn4A1037((int32_t)i + 1, (int32_t)i);
  P107_TrafficLights((int32_t)i + 1, TrafficRecs + i * 0x54);
}
void P128_TrafficDraw(void) {
  uint8_t list[68];
  uint8_t n = 0;
  if (G6_00B87EA0 != 0 && P88_Mode575 == 2 && (P101_RecSaved == 0 || P101_RecState == 0)) return;
  int32_t cnt = (G6_00B87EAC == 0 && G6_00B87EB0 == 0) ? 0x40 : 0x41;
  P11_00ba52d0 = fround(P44_CamX); int32_t cx = P11_00ba52d0;
  P11_00ba52d0 = fround(P44_CamZ);
  for (int32_t i = 0; i < cnt; i++) {
#ifndef RE_HOOK_BUILD
    if (i >= 0x40) break;                                   /* защита: TrafficRecs — 0x40 записей */
#endif
    if (TrafficRecs[i * 0x54 + 1] == 0) continue;
    const uint8_t *car = tcar(i);
    int32_t ax = iabs(cx - rd32(car + 200)), az = iabs(P11_00ba52d0 - rd32(car + 0xd0));
    int32_t d = ax < az ? az + ax / 2 : ax + az / 2;
    if ((float)d < P11_01270c24 && n < sizeof list) list[n++] = (uint8_t)i;
  }
  if (n == 0) return;
  if (MenuVar575F44 == 0) {
    P12_Fn00426580(4);
    for (int32_t k = 0; k < n; k++) if (TrafficRecs[list[k] * 0x54 + 0xd] != 0x19) draw_one(list[k]);
    P12_Fn00426580(0x19);
    for (int32_t k = 0; k < n; k++) if (TrafficRecs[list[k] * 0x54 + 0xd] == 0x19) draw_one(list[k]);
  } else {
    for (uint32_t b = 0; b < 0x32; b++) {
      int on = 0;
      for (int32_t k = 0; k < n; k++) {
        if (TrafficRecs[list[k] * 0x54 + 0xd] != b) continue;
        if (!on) { on = 1; P12_Fn00426580((int32_t)b); }
        draw_one(list[k]);
      }
    }
  }
}

/* ---- 0050a15b ---- */
typedef struct { int32_t v[2]; } p128_pt_t;
/* один проход отсечения: in[0..n) — цикл (последняя точка замыкается на первую), out — результат */
static int32_t clip_pass(const p128_pt_t *in, int32_t n, p128_pt_t *out, int32_t ax, int32_t c, int32_t hi) {
  int32_t m = 0, flag = 0, i = 0;
  p128_pt_t last = { { 0, 0 } };
  for (int32_t g = 0; i < n && g < 4 * n + 4; g++) {         /* g — защита */
    p128_pt_t P = flag ? last : in[i];
    p128_pt_t Q = (i + 1 < n) ? in[i + 1] : in[0];
    int32_t pa = P.v[ax], qa = Q.v[ax];
    int32_t pin = hi ? !(c < pa) : !(pa < c), qin = hi ? !(c < qa) : !(qa < c);
    int32_t o = ax ^ 1;
    if (pin && qin) { if (m < 48) out[m++] = Q; last = Q; flag = 0; }
    else if (pin != qin) {
      const p128_pt_t *A = (pa < qa) ? &P : &Q, *B = (pa < qa) ? &Q : &P;   /* опора — точка с меньшей координатой */
      float k = (float)(B->v[o] - A->v[o]) / (float)(B->v[ax] - A->v[ax]);
      P11_00ba52d0 = fround(k * (float)(c - A->v[ax]));
      p128_pt_t r; r.v[ax] = c; r.v[o] = A->v[o] + P11_00ba52d0;
      if (m < 48) out[m++] = r;
      last = r;
      flag = qin;                                            /* вход в область — шаг повторяется от точки пересечения */
    }
    if (!flag) i++;
  }
  return m;
}
int32_t P128_ClipArea(const int32_t *poly, const int32_t *rect) {
  p128_pt_t a[48], b[48];
  int32_t n = 0;
  for (const int32_t *p = poly; p != NULL && n < 48; p = (const int32_t *)re_rd_ptr(p + 2)) {
    a[n].v[0] = p[0]; a[n].v[1] = p[1]; n++;
  }
  if (n == 0) return 0;
  if ((n = clip_pass(a, n, b, 0, rect[0], 0)) == 0) return 0;
  if ((n = clip_pass(b, n, a, 0, rect[2], 1)) == 0) return 0;
  if ((n = clip_pass(a, n, b, 1, rect[1], 0)) == 0) return 0;
  if ((n = clip_pass(b, n, a, 1, rect[3], 1)) == 0) return 0;
  int32_t s = 0;
  for (int32_t k = 0; k < n - 1; k++) s += a[k].v[0] * a[k + 1].v[1] - a[k + 1].v[0] * a[k].v[1];
  s = (s + (a[n - 1].v[0] * a[0].v[1] - a[0].v[0] * a[n - 1].v[1])) / 2;
  return s < 0 ? -s : s;
}
