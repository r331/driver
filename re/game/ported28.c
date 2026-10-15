/* Загрузка моделей событий и машин уровня — восстановлено из Game.exe. */
#include "ported28.h"
#include "ported79.h"
#include "ported6.h"
#include "ported20.h"
#include "ported27.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "engine.h"
#include "unported.h"
#include <stdio.h>
#include <string.h>
GAME_VAR_DEF(p28_evtab_t, P28_EventModels, 0x00d11a60)
GAME_VAR_DEF(int32_t, P28_EventCount, 0x00d12418)
GAME_VAR_DEF(p28_models_t, P28_CarClean, 0x010ddfe0)
GAME_VAR_DEF(p28_models_t, P28_CarDam, 0x010de020)
GAME_VAR_DEF(p28_models_t, P28_CarLow, 0x010de080)
GAME_VAR_DEF(p28_deltas_t, P28_CarDelta, 0x010de320)
GAME_VAR_DEF(p28_sizes_t, P28_CarOpsSize, 0x00e00680)
GAME_VAR_DEF(int32_t, P28_CarShine, 0x011b6140)
GAME_VAR_DEF(p28_clear100_t, P28_Clear100, 0x010de120)
GAME_VAR_DEF(p28_blk1_t, P28_Dst1, 0x00559074)
GAME_VAR_DEF(p28_src1_t, P28_Src1, 0x005554d4)
GAME_VAR_DEF(p28_src2_t, P28_Src2, 0x00557694)
GAME_VAR_DEF(p28_blk2_t, P28_Dst2, 0x0055a6f4)
GAME_VAR_DEF(int32_t, P28_DbgFlag, 0x00dbb450)
GAME_VAR_DEF(int32_t, P28_ShineFlag, 0x0055c974)
GAME_VAR_DEF(int32_t, P28_BadGuyFlag, 0x00b87f04)
#define P28_Ptr(v) ((const uint8_t *)(uintptr_t)(uint32_t)(v))
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)
#define MAP_C "D:\\Driver\\Game\\map.c"

void P28_LoadEventModels(void *file) {
  void *tmp = DebugMalloc(0x80000, MAP_C, 0x3d4);
  void *buf = DebugMalloc(0x80000, MAP_C, 0x3d5);
  for (int i = 0; i < P28_EventCount; i++) {
    if (P28_EventModels[i] != NULL) { P79_EventFree(P28_EventModels[i]); P28_EventModels[i] = NULL; }
  }
  P27_ReadChunked(&P28_EventCount, 4, 1, file);
  for (int i = 0; i < P28_EventCount; i++) {
    int32_t sz;
    P27_ReadChunked(&sz, 4, 1, file);
    P27_ReadChunked(tmp, sz, 1, file);
    sz = Call00475A3D(tmp, buf);
    void *m = P79_EventAlloc(sz);
    P28_EventModels[i] = m;
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

static int32_t find_model(const char *name, const char *msg) {
  int32_t m = P20_FindNameValue(name);
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
    P28_CarClean[3 + i] = P20_FindNameValue(name);
    if (P28_CarClean[3 + i] == 0) plat_message_box(MAIN_HWND, "Could not find clean civ car model.\n Change name in LEV file.", name, 0);
    snprintf(name, sizeof name, "CIVCAR%dDAM", i + 1);
    P28_CarDam[3 + i] = P20_FindNameValue(name);
    if (P28_CarDam[3 + i] == 0) plat_message_box(MAIN_HWND, "Could not find damaged civ car model.\n  Change name in LEV file.", name, 0);
    snprintf(name, sizeof name, "CIVCAR%dLOW", i + 1);
    P28_CarLow[3 + i] = P20_FindNameValue(name);
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
