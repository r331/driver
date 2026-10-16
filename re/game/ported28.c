/* Загрузка моделей событий и машин уровня — восстановлено из Game.exe. */
#include "ported28.h"
#include "ported79.h"
#include "reptr.h"
#include "ported6.h"
#include "ported20.h"
#include "ported27.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "engine.h"
#include "unported.h"
#include <stdio.h>
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_EventModels")
#undef P28_EventModels
#pragma push_macro("P28_EventModels") /*gvi*/
#undef P28_EventModels /*gvi*/
p28_evtab_t P28_EventModels;
#pragma pop_macro("P28_EventModels") /*gvi*/
#pragma pop_macro("P28_EventModels")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_EventCount")
#undef P28_EventCount
#pragma push_macro("P28_EventCount") /*gvi*/
#undef P28_EventCount /*gvi*/
int32_t P28_EventCount;
#pragma pop_macro("P28_EventCount") /*gvi*/
#pragma pop_macro("P28_EventCount")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarClean")
#undef P28_CarClean
#pragma push_macro("P28_CarClean") /*gvi*/
#undef P28_CarClean /*gvi*/
p28_models_t P28_CarClean;
#pragma pop_macro("P28_CarClean") /*gvi*/
#pragma pop_macro("P28_CarClean")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarDam")
#undef P28_CarDam
#pragma push_macro("P28_CarDam") /*gvi*/
#undef P28_CarDam /*gvi*/
p28_models_t P28_CarDam;
#pragma pop_macro("P28_CarDam") /*gvi*/
#pragma pop_macro("P28_CarDam")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarLow")
#undef P28_CarLow
#pragma push_macro("P28_CarLow") /*gvi*/
#undef P28_CarLow /*gvi*/
p28_models_t P28_CarLow;
#pragma pop_macro("P28_CarLow") /*gvi*/
#pragma pop_macro("P28_CarLow")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarDelta")
#undef P28_CarDelta
#pragma push_macro("P28_CarDelta") /*gvi*/
#undef P28_CarDelta /*gvi*/
p28_deltas_t P28_CarDelta;
#pragma pop_macro("P28_CarDelta") /*gvi*/
#pragma pop_macro("P28_CarDelta")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarOpsSize")
#undef P28_CarOpsSize
#pragma push_macro("P28_CarOpsSize") /*gvi*/
#undef P28_CarOpsSize /*gvi*/
p28_sizes_t P28_CarOpsSize;
#pragma pop_macro("P28_CarOpsSize") /*gvi*/
#pragma pop_macro("P28_CarOpsSize")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_CarShine")
#undef P28_CarShine
#pragma push_macro("P28_CarShine") /*gvi*/
#undef P28_CarShine /*gvi*/
int32_t P28_CarShine;
#pragma pop_macro("P28_CarShine") /*gvi*/
#pragma pop_macro("P28_CarShine")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_Clear100")
#undef P28_Clear100
#pragma push_macro("P28_Clear100") /*gvi*/
#undef P28_Clear100 /*gvi*/
p28_clear100_t P28_Clear100;
#pragma pop_macro("P28_Clear100") /*gvi*/
#pragma pop_macro("P28_Clear100")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_Dst1")
#undef P28_Dst1
#pragma push_macro("P28_Dst1") /*gvi*/
#undef P28_Dst1 /*gvi*/
p28_blk1_t P28_Dst1;
#pragma pop_macro("P28_Dst1") /*gvi*/
#pragma pop_macro("P28_Dst1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_Src1")
#undef P28_Src1
#pragma push_macro("P28_Src1") /*gvi*/
#undef P28_Src1 /*gvi*/
p28_src1_t P28_Src1;
#pragma pop_macro("P28_Src1") /*gvi*/
#pragma pop_macro("P28_Src1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_Src2")
#undef P28_Src2
#pragma push_macro("P28_Src2") /*gvi*/
#undef P28_Src2 /*gvi*/
p28_src2_t P28_Src2;
#pragma pop_macro("P28_Src2") /*gvi*/
#pragma pop_macro("P28_Src2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_Dst2")
#undef P28_Dst2
#pragma push_macro("P28_Dst2") /*gvi*/
#undef P28_Dst2 /*gvi*/
p28_blk2_t P28_Dst2;
#pragma pop_macro("P28_Dst2") /*gvi*/
#pragma pop_macro("P28_Dst2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_DbgFlag")
#undef P28_DbgFlag
#pragma push_macro("P28_DbgFlag") /*gvi*/
#undef P28_DbgFlag /*gvi*/
int32_t P28_DbgFlag;
#pragma pop_macro("P28_DbgFlag") /*gvi*/
#pragma pop_macro("P28_DbgFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_ShineFlag")
#undef P28_ShineFlag
#pragma push_macro("P28_ShineFlag") /*gvi*/
#undef P28_ShineFlag /*gvi*/
int32_t P28_ShineFlag;
#pragma pop_macro("P28_ShineFlag") /*gvi*/
#pragma pop_macro("P28_ShineFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P28_BadGuyFlag")
#undef P28_BadGuyFlag
#pragma push_macro("P28_BadGuyFlag") /*gvi*/
#undef P28_BadGuyFlag /*gvi*/
int32_t P28_BadGuyFlag;
#pragma pop_macro("P28_BadGuyFlag") /*gvi*/
#pragma pop_macro("P28_BadGuyFlag")
#endif
#define P28_Ptr(v) ((const uint8_t *)P79_PTR(v))   /* v1.44: ссылки моделей — uint32 (P79_PTR: hook — адрес, native — арена карты) */
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)
#define MAP_C "D:\\Driver\\Game\\map.c"

void P28_LoadEventModels(void *file) {
  void *tmp = DebugMalloc(0x80000, MAP_C, 0x3d4);
  void *buf = DebugMalloc(0x80000, MAP_C, 0x3d5);
  for (int i = 0; i < P28_EventCount; i++) {
    if (P28_EventModels[i] != 0) { P79_EventFree(re_ptr(P28_EventModels[i])); P28_EventModels[i] = 0; }
  }
  P27_ReadChunked(&P28_EventCount, 4, 1, file);
  for (int i = 0; i < P28_EventCount; i++) {
    int32_t sz;
    P27_ReadChunked(&sz, 4, 1, file);
    P27_ReadChunked(tmp, sz, 1, file);
    sz = Call00475A3D(tmp, buf);
    void *m = P79_EventAlloc(sz);
    P28_EventModels[i] = re_addr(m);
    if (m == NULL) {
      P28_EventCount = 0;
      plat_message_box(MAIN_HWND, "Not enogh memory for event models!", "Memory Error!", 0x30);
      DebugFree(buf);
      DebugFree(tmp);
      return;
    }
    memcpy(m, buf, (size_t)sz);
    Call00427757(m);
    Call0042793F(m, 0);
    Call0042793F(m, 1);
    Call004757D2(m);
    Call00475906(m);
  }
  DebugFree(buf);
  DebugFree(tmp);
}

static uint32_t find_model(const char *name, const char *msg) {
  uint32_t m = (uint32_t)P20_FindNameValue(name);
  if (m == 0 && msg != NULL) plat_message_box(MAIN_HWND, msg, "ERROR IN _LEVEL_ DATA", 0);
  return m;
}

void P28_LoadCarModels(void) {
  char name[80];
  Call004C2042();
  P28_DbgFlag = 0;
  memset(P28_Clear100, 0, 0x100);
  P28_CarShine = Call004EC91E("CARSHINE");
  if (P28_CarShine == 0) P28_ShineFlag = 0;
  for (int i = 5; i >= 0; i--) memcpy(&P28_Dst1[i * 0x50], &P28_Src1[i * 0x50 + S_00D1192C * 0x1e0], 0x50);
  memcpy(P28_Dst2, &P28_Src2[S_00D1192C * 0x170], 0x170);
  snprintf(name, sizeof name, "PLAYERCAR%dCLEAN", (int)S_00D1192C + 1);
  P28_CarClean[0] = find_model(name, "Could not find clean player car model.\n Change name in LEV file.");
  snprintf(name, sizeof name, "PLAYERCAR%dDAM", (int)S_00D1192C + 1);
  P28_CarDam[0] = find_model(name, "Could not find damaged player car model.\n Change name in LEV file.");
  P28_CarLow[0] = P28_CarClean[0];
  P28_CarClean[1] = find_model("COPCARCLEAN", "Could not find clean cop car model.\n Change name in LEV file.");
  P28_CarDam[1] = find_model("COPCARDAM", "Could not find damaged cop car model.\n Change name in LEV file.");
  P28_CarLow[1] = find_model("COPCARLOW", "Could not find low cop car model.\n Change name in LEV file.");
  if (P28_BadGuyFlag == 1) {
    P28_CarClean[2] = find_model("CIVCAR1CLEAN", "Could not find clean bad guy car model.\n Change name in LEV file.");
    P28_CarDam[2] = find_model("CIVCAR1DAM", "Could not find damaged bad guy model.\n Change name in LEV file.");
    P28_CarLow[2] = find_model("CIVCAR1LOW", "Could not find low bad guy model.\n Change name in LEV file.");
  } else {
    P28_CarClean[2] = find_model("CIVCAR1CLEAN", "Could not find clean bad guy car model.\n Change name in LEV file.");
    P28_CarDam[2] = find_model("CIVCAR1DAM", "Could not find damaged bad guy model.\n Change name in LEV file.");
    P28_CarLow[2] = find_model("CIVCAR1LOW", NULL);
  }
  for (int i = 0; i < 9; i++) {
    snprintf(name, sizeof name, "CIVCAR%dCLEAN", i + 1);
    P28_CarClean[3 + i] = (uint32_t)P20_FindNameValue(name);
    if (P28_CarClean[3 + i] == 0) plat_message_box(MAIN_HWND, "Could not find clean civ car model.\n Change name in LEV file.", name, 0);
    snprintf(name, sizeof name, "CIVCAR%dDAM", i + 1);
    P28_CarDam[3 + i] = (uint32_t)P20_FindNameValue(name);
    if (P28_CarDam[3 + i] == 0) plat_message_box(MAIN_HWND, "Could not find damaged civ car model.\n  Change name in LEV file.", name, 0);
    snprintf(name, sizeof name, "CIVCAR%dLOW", i + 1);
    P28_CarLow[3 + i] = (uint32_t)P20_FindNameValue(name);
    if (P28_CarLow[3 + i] == 0) plat_message_box(MAIN_HWND, "Could not find low civ car model.\n  Change name in LEV file.", name, 0);
  }
  /* дельты вершин «целая − повреждённая» / 4096 */
  for (int k = 0; k < 12; k++) {
    if (P28_CarDam[k] == 0 || P28_CarClean[k] == 0) continue;  /* оригинал здесь упал бы на нулевой модели */
    const float *dm = (const float *)P28_Ptr(*(const int32_t *)(P28_Ptr(P28_CarDam[k]) + 0x20));
    const float *cl = (const float *)P28_Ptr(*(const int32_t *)(P28_Ptr(P28_CarClean[k]) + 0x20));
    float *out = P28_CarDelta[k];
    int n = *(const uint16_t *)(P28_Ptr(P28_CarClean[k]) + 0x14);
    for (int v = 0; v < n; v++) {
      out[0] = (dm[0] - cl[0]) / 4096.0f;
      out[1] = (dm[1] - cl[1]) / 4096.0f;
      out[2] = (dm[2] - cl[2]) / 4096.0f;
      cl += 4; dm += 4; out += 4;
    }
  }
  for (int k = 0; k < 12; k++) {
    P28_CarOpsSize[k] = 0;
    if (P28_CarClean[k] != 0) {
      int32_t total = 0;
      const uint8_t *p = (const uint8_t *)P28_Ptr(*(const int32_t *)(P28_Ptr(P28_CarClean[k]) + 0x2c));
      uint32_t cnt = *(const uint16_t *)(P28_Ptr(P28_CarClean[k]) + 0x16);
      while (cnt != 0) {
        int32_t step = G2_TABLE_00550ACC[*p];
        total += step; p += step; cnt--;
      }
      P28_CarOpsSize[k] = total;
    }
  }
  P27_LoadDentTextures();
  Call004C0218(-1);
}
