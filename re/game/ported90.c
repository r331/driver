/* Рисование однозаписной модели блока карты — восстановлено из Game.exe (0042a423). */
#include "ported90.h"
#include "ported8.h"
#include "ported85.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "../platform/native/diagnostics.h"
#endif

/* 0042a423 */
void P90_DrawSingle(uint32_t m, int32_t idx, float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(m);
#ifndef RE_HOOK_BUILD
  re_diag_model(m);
#endif
  static float local[16];   /* зеркальная копия: в оригинале на стеке, указатель на неё остаётся в P44_MatPtr */
  if (G2_011F43B0 == 0) P63_SphN = 0;
  else P63_SphereHits(pos, (const uint8_t *)mdl);
  P84_LightIn[0] = P81_PosY;
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
  float *mat = P84_MatCache[idx];
  if (P84_MatFlag[idx] != (int32_t)P47_SwapCnt) {
    Mat3Mul_0052859A(P44_ViewMat, (const float *)(P56_EulerTab + (size_t)idx * 0x40), mat);
    P84_MatFlag[idx] = (int32_t)P47_SwapCnt;
  }
  P44_MatPtr = mat;
  if (P84_Mirror) {
    memcpy(local, mat, sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  uint32_t type = G2_011F4064[0];
  uint8_t md = (uint8_t)mode;
  const uintptr_t *tab = md == 0 ? P84_Tab0 : md == 1 ? P84_Tab1 : P84_Tab2;
  uintptr_t f = (tab && type < 56) ? tab[type] : 0;   /* type < 56 — охранная проверка (таблицы по 56 указателей), в оригинале её нет */
#ifndef RE_HOOK_BUILD
  re_diag_record(P79_OFF(G2_011F4064), type, !f || f == (uintptr_t)P85_SkipRecord);
#endif
  if (f) ((p84_handler_t)f)(0);
#ifndef RE_HOOK_BUILD
  re_diag_model(UINT32_MAX);
#endif
  P44_XformTag++;
}
