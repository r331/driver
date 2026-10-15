/* DirectInput: инициализация и перечисление джойстиков — восстановлено из Game.exe (Input.c). */
#include "ported37.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P37_MouseShared, 0x00575f28)

/* Начальная раскладка клавиш: 20 байт в P36_KeyCfg (данные по 0054b7a8) и 12 байт в P19_Keys1 (0054b7d8). */
static const uint8_t k_defcfg[20] = { 0x3b,0x3c,0x3d,0x3e,0x2c,0x2d,0x28,0x35,0x39,0x1c,0x2b,0x24,0x25,0x26,0x2e,0x23,0x02,0x03,0x00,0x00 };
static const uint8_t k_defkeys[12] = { 0x20,0x21,0x00,0x02,0x01,0x03,0x04,0x05,0x06,0x07,0x08,0x09 };

int32_t P37_JoyEnumCb(const void *inst, void *di) {
  (void)di;
  void *d1 = plat_di_create_device(P34_Di, (const uint8_t *)inst + 4);
  if (!d1) return 1;
  void *dev = plat_di_query_device2(d1);
  plat_di_release(d1);
  if (!dev) return 1;
  if (plat_di_set_format(dev, 2) != 0 ||
      plat_di_set_coop(dev, (void *)(uintptr_t)G6_00BDF9C0, 5) != 0 ||
      plat_di_set_prop(dev, 4, 0, 1, -31, 31) != 0 ||     /* диапазон оси X */
      plat_di_set_prop(dev, 4, 4, 1, -31, 31) != 0 ||     /* оси Y */
      plat_di_set_prop(dev, 5, 0, 1, 3, 0) != 0 ||        /* мёртвая зона X */
      plat_di_set_prop(dev, 5, 4, 1, 3, 0) != 0) {        /* мёртвая зона Y */
    plat_di_release(dev); return 1;
  }
  P34_Joy = dev;
  if (P36_AcquireDevice(2) == 0) { plat_di_release(dev); return 1; }
  uint32_t sub; memcpy(&sub, (const uint8_t *)inst + 0x24, 4);
  sub = (sub & 0xff00) >> 8;
  int32_t axes = (sub != 4);
  uint32_t caps = 0;
  if (plat_di_get_caps_flags(dev, &caps) != 0) { plat_di_release(dev); return 1; }
  int32_t ff = 0;
  if (caps & 0x100) {
    if (P35_CreateEffectA(dev, P36_JoyCount) != 0) ff = 1;
    if (P35_CreateEffectB(dev, P36_JoyCount) != 0) ff = 1;
  }
  P34_EffC[P36_JoyCount] = dev;
  P36_JoyAxisCap[P36_JoyCount] = axes;
  P36_JoyAux[P36_JoyCount] = ff;
  P36_JoyCount++;
  return P36_JoyCount < 8;
}

int32_t P37_InitInput(void) {
  if (P34_Di) P34_ReleaseInput();
  P34_Di = plat_di_create((void *)(uintptr_t)G6_00BDF9C4, 0x500);
  if (!P34_Di) return 0;
  P34_Kbd = plat_di_create_sys_device(P34_Di, 0);
  if (!P34_Kbd) goto fail;
  P34_Mouse = plat_di_create_sys_device(P34_Di, 1);
  if (!P34_Mouse) goto fail;
  if (plat_di_set_format(P34_Kbd, 0) != 0) goto fail;
  if (plat_di_set_format(P34_Mouse, 1) != 0) goto fail;
  if (plat_di_set_coop(P34_Kbd, (void *)(uintptr_t)G6_00BDF9C0, 6) != 0) goto fail;
  if (plat_di_set_coop(P34_Mouse, (void *)(uintptr_t)G6_00BDF9C0, P37_MouseShared == 0 ? 6 : 5) != 0) goto fail;
  if (P36_AcquireDevice(0) == 0) goto fail;
  P35_InputMode = 0;
  memcpy(P36_KeyCfg, k_defcfg, 20);
  memcpy((void *)P19_Keys1, k_defkeys, 12);
  P34_Event = plat_event_create();
  if (!P34_Event) goto fail;
  if (plat_di_set_event(P34_Mouse, P34_Event) != 0) goto fail;
  if (plat_di_set_prop(P34_Mouse, 1, 0, 0, 0x20, 0) != 0) goto fail;       /* буфер событий мыши — 32 */
  if (plat_di_acquire(P34_Mouse) != 0) goto fail;
  P34_Reg24 = 0;
  P36_JoyCount = 0;
  if (P36_JoyPresent != 0) {
    plat_di_enum_joysticks(P34_Di, P37_JoyEnumCb);
    if (P36_JoyCount > 0) P36_SelectJoystick(0);
  }
  return 1;
fail:
  P34_ReleaseInput();
  return 0;
}
