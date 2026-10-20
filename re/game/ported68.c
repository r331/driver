/* ported68 — assorted leaf functions (Game.exe, cdecl): key auto-repeat, text line reader, object aim / step
   helpers, camera-script argument packing, sample reload, LFB lock, screen-mode reset and traffic car spawning. */
#include "ported68.h"
#include "ported140.h"
#include "reptr.h"
#include "crt.h"
#include <math.h>
#include <string.h>

#ifdef RE_HOOK_BUILD
#  define P68_STD __attribute__((stdcall))
#else
#  define P68_STD
#endif

#ifndef RE_HOOK_BUILD
#pragma push_macro("P68_CamF") /*gvi*/
#undef P68_CamF /*gvi*/
#pragma push_macro("P68_Samps")
#undef P68_Samps
P68_RepArr P68_Rep_; P68_SampArr P68_Samps; P68_FLoad P68_DrvLoad; P68_Cam4 P68_CamF;
#pragma pop_macro("P68_Samps")
#pragma pop_macro("P68_CamF") /*gvi*/
#pragma push_macro("P68_CamI0") /*gvi*/
#undef P68_CamI0 /*gvi*/
#pragma push_macro("P68_CamI1") /*gvi*/
#undef P68_CamI1 /*gvi*/
#pragma push_macro("P68_CamI2") /*gvi*/
#undef P68_CamI2 /*gvi*/
#pragma push_macro("P68_CamI3") /*gvi*/
#undef P68_CamI3 /*gvi*/
#pragma push_macro("P68_ModeW") /*gvi*/
#undef P68_ModeW /*gvi*/
#pragma push_macro("P68_ModeH") /*gvi*/
#undef P68_ModeH /*gvi*/
#pragma push_macro("P68_B87E54") /*gvi*/
#undef P68_B87E54 /*gvi*/
#pragma push_macro("P68_D11A48") /*gvi*/
#undef P68_D11A48 /*gvi*/
uint16_t P68_CamI0, P68_CamI1, P68_CamI2, P68_CamI3; int32_t P68_ModeW, P68_ModeH, P68_B87E54, P68_D11A48;
#pragma pop_macro("P68_D11A48") /*gvi*/
#pragma pop_macro("P68_B87E54") /*gvi*/
#pragma pop_macro("P68_ModeH") /*gvi*/
#pragma pop_macro("P68_ModeW") /*gvi*/
#pragma pop_macro("P68_CamI3") /*gvi*/
#pragma pop_macro("P68_CamI2") /*gvi*/
#pragma pop_macro("P68_CamI1") /*gvi*/
#pragma pop_macro("P68_CamI0") /*gvi*/
#pragma push_macro("P68_Saved") /*gvi*/
#undef P68_Saved /*gvi*/
#pragma push_macro("P68_IntroBase") /*gvi*/
#undef P68_IntroBase /*gvi*/
#pragma push_macro("P68_IntroCur") /*gvi*/
#undef P68_IntroCur /*gvi*/
#pragma push_macro("P68_IntroA") /*gvi*/
#undef P68_IntroA /*gvi*/
P68_SaveArr P68_Saved; uint32_t P68_IntroBase, P68_IntroCur; int32_t P68_IntroA;
#pragma pop_macro("P68_IntroA") /*gvi*/
#pragma pop_macro("P68_IntroCur") /*gvi*/
#pragma pop_macro("P68_IntroBase") /*gvi*/
#pragma pop_macro("P68_Saved") /*gvi*/
#endif

static int32_t rd_i32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static float rd_f(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
static void wr_f(uint8_t *p, uint32_t o, float v) { memcpy(p + o, &v, 4); }
static void wr_u16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }

/* 00522e64 */
/* P68_RepeatCheck — Game.exe 00522e64.  Repeat detector over the last keys: if key is in the 4-entry history
   P68_Rep_, bumps its count and returns 1 exactly when the count passes 2 (third occurrence); otherwise stores
   key at the round-robin index P12_00bde728 with count 0 and returns 0.  The index wraps after 4, i.e. it can
   reach 4 (one past the 4 checked entries) — kept literally; TODO(RE): unsure whether P68_Rep_ has 5 entries. */
int32_t P68_RepeatCheck(int32_t key) {
  int32_t c;
  for (c = 0; c < 4; c++)
    if (P68_Rep_[c].key == key) break;
  if (c > 3) {
    P68_Rep_[P12_00bde728].cnt = 0;
    P68_Rep_[P12_00bde728].key = key;
    P12_00bde728 = P12_00bde728 + 1;
    if (P12_00bde728 > 4) P12_00bde728 = 0;
    return 0;
  }
  uint8_t old = P68_Rep_[c].cnt;
  P68_Rep_[c].cnt = (uint8_t)(old + 1);
  return (old < 3 && P68_Rep_[c].cnt > 2) ? 1 : 0;
}

/* 00524ed1 */
/* P68_ReadWords — Game.exe 00524ed1.  Reads one non-empty line from file into buf, collapsing runs of tabs /
   spaces into one space (none at the start), NUL-terminated.  Returns its length; at EOF returns what was read
   so far without terminating it, or -1 if nothing. */
int32_t P68_ReadWords(void *file, uint8_t *buf) {
  int32_t n = 0;
  int spaced = 0;
  for (;;) {
    int c = g_fgetc(file);
    if (c == -1) return n != 0 ? n : -1;
    if (c == '\n' || c == '\r') {
      if (n == 0) continue;
      break;
    }
    if (c == '\t' || c == ' ') {
      if (!spaced && n > 0) { *buf++ = ' '; spaced = 1; n++; }
    } else {
      *buf++ = (uint8_t)c; spaced = 0; n++;
    }
  }
  *buf = 0;
  return n;
}

/* P68_AimSetup — Game.exe 00514f47.  Points a scripted object at its target: +0x5c = 0x800, +0x60 = 0, direction
   vector +0x64.. = target (+0x94..) - origin (+0x84..), and heading +0x5e = (-atan2(dz, dx) - 90 deg) & 0xfff.
   Each difference is a float store and each conversion an x87 fistp (round to nearest even) through the global
   P11_00ba52d0, as in the original.  TODO(RE): unsure what object type this is and what +0x5c/+0x60 are. */
/* 00514f47: каждая разность и fistp — как в x87: float, округление к ближайшему чётному */
void P68_AimSetup(uint8_t *obj) {
  wr_u16(obj, 0x5c, 0x800);
  wr_u16(obj, 0x60, 0);
  volatile float dx = rd_f(obj, 0x94) - rd_f(obj, 0x84);
  wr_f(obj, 0x64, dx);
  volatile float dy = rd_f(obj, 0x98) - rd_f(obj, 0x88);
  wr_f(obj, 0x68, dy);
  volatile float dz = rd_f(obj, 0x9c) - rd_f(obj, 0x8c);
  wr_f(obj, 0x6c, dz);
  P11_00ba52d0 = (int32_t)lrintf(rd_f(obj, 0x64));
  int32_t ix = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(rd_f(obj, 0x6c));
  int32_t iz = P11_00ba52d0;
  int32_t a = P44_Atan2(iz, ix);
  wr_u16(obj, 0x5e, (uint16_t)((-a - 0x400) & 0xfff));
}

/* 00513efd */
/* P68_ObjStepB — Game.exe 00513efd.  Step of a scripted object: 00514a47 first; then 00514C9F(obj, 5, 0).  On result
   1 runs 0051500C and, if flag 0x10 (+0xc) is set and +0x38 changed during the step, restores the heading half
   +0x5e from before and calls 00514165.  Otherwise 00514165 when none of flags 0x80 / 0x400 / 0x08 is set.
   TODO(RE): unsure what the callees and flags do. */
void P68_ObjStepB(uint8_t *obj) {
  int32_t f38_old = rd_i32(obj, 0x38);
  P68_Fn514A47(obj);
  uint32_t c = (uint32_t)rd_i32(obj, 0x5c);
  uint16_t hi = (uint16_t)(c >> 16);   /* = int16 at +0x5e before the step */
  int32_t r = P67_Fn514C9F(obj, 5, 0);
  uint32_t flags = (uint32_t)rd_i32(obj, 0xc);
  if (r == 1) {
    P67_Fn51500C(obj);
    flags = (uint32_t)rd_i32(obj, 0xc);
    if ((flags & 0x10) != 0 && rd_i32(obj, 0x38) != f38_old) {
      wr_u16(obj, 0x5e, hi);
      P67_Fn514165(obj);
    }
  } else if ((flags & 0x80) == 0 && (flags & 0x400) == 0 && (flags & 8) == 0) {
    P67_Fn514165(obj);
  }
}

/* 004a5505 */
/* P68_ReadCamArgs — Game.exe 004a5505.  Packs parsed camera-script arguments into out by the format string fmt:
   'f' -> next float (P68_CamF taken in reverse order, 4 bytes), 'i' -> next uint16 (P68_CamI0..3, 2 bytes);
   stops at any other character and returns the end of the packed data.  Arguments past the fourth of a kind
   only advance out. */
uint8_t *P68_ReadCamArgs(uint8_t *out, const char *fmt) {
  int32_t fi = 0, ii = 0;   /* float / int argument counters */
  for (;; fmt++) {
    if (*fmt == 'f') {
      if (fi >= 0 && fi < 4) memcpy(out, &P68_CamF[3 - fi], 4);
      fi++; out += 4;
    } else if (*fmt == 'i') {
      uint16_t v;
      int ok = 1;
      switch (ii) {
      case 0: v = P68_CamI0; break;
      case 1: v = P68_CamI1; break;
      case 2: v = P68_CamI2; break;
      case 3: v = P68_CamI3; break;
      default: v = 0; ok = 0; break;
      }
      if (ok) memcpy(out, &v, 2);
      ii++; out += 2;
    } else {
      return out;
    }
  }
}

/* 0052455f */
/* P68_ChangeSample — Game.exe 0052455f.  Replaces sound sample n: frees it and loads a new one through the sound
   driver's loader (arg = 32-bit address of the file name).  Status byte P48_Samples[n * 8]: 2 = loaded,
   4 = load error; byte +1 = 8 on success (TODO(RE): unsure).  Returns 1 on success or when sound is off,
   0 on a bad sample number or load error. */
int32_t P68_ChangeSample(int32_t arg, int32_t n) {
  if (G6_00B91CF4 == 0) return 1;
  if (n < 0 || G6_00B91D34 <= n) {
    DebugLog("ChangeSample: Invalid sample number");
    return 0;
  }
  P48_FreeSample((uint32_t)n);
#ifdef RE_HOOK_BUILD
  int32_t h = P68_DrvLoad ? P68_DrvLoad(n, arg) : -1;
#else
  /* v2.12: arg — 32-битный адрес имени (re_addr); драйвер 0048bf9a = P140_SndLoadWav(n, const char *) — native-указатель через re_ptr
     (было: усечённое число как указатель → SIGSEGV в snprintf при «Play» на автоответчике мотеля) */
  int32_t h;
  if (P68_DrvLoad != NULL && (re_fn_t)P68_DrvLoad == (re_fn_t)P140_SndLoadWav) {
    const char *nm = (const char *)re_ptr((uint32_t)arg);
    h = nm ? P140_SndLoadWav(n, nm) : -1;
  } else h = P68_DrvLoad ? P68_DrvLoad(n, arg) : -1;   /* иной драйвер (шпион selftest) — как в оригинале */
#endif
  P68_Samps[n].handle = h;
  if (h == -1) {
    DebugLog("ChangeSample: Error loading sample");
    P48_Samples[n * 8] = 4;
    return 0;
  }
  P48_Samples[n * 8] = 2;
  P68_Samps[n].extra = 0;
  P48_Samples[n * 8 + 1] = 8;
  return 1;
}

/* Glide export by decorated name, or NULL (same helper as in ported54.c). */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
/* P68_LfbLock — Game.exe 0042476c.  Locks a frame buffer for direct pixel access.  Glide: grLfbLock(write-only
   = 1, buffer which, 565 format = 0, origin P47_WinArg5, no pipeline, info) and fills info+0x14.. with the pixel
   layout (16 bpp; then three (shift, bits)-like bytes 3,2 / 3,0xb / 5,0 — TODO(RE): unsure of the exact
   meaning of those bytes).  D3D: P39_GetSurfaceFormat.  Returns the lock result, 0 without a device. */
uint32_t P68_LfbLock(int32_t which, void *info) {
  if (D_00b1c0d4 == 0) return 0;
  if (D_00b1c0d8 == 0) {
    int32_t (P68_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t, void *) =
        (int32_t (P68_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t, void *))glide_proc("_grLfbLock@24");
    uint32_t r = f ? (uint32_t)f(1, which, 0, P47_WinArg5, 0, info) : 0;
    uint8_t *p = (uint8_t *)info;
    p[0x14] = 0x10; p[0x15] = 3; p[0x16] = 2; p[0x17] = 3; p[0x18] = 0xb; p[0x19] = 5; p[0x1a] = 0;
    return r;
  }
  if (D_00b1c0d8 == 1) return (uint32_t)P39_GetSurfaceFormat(which, (P39_SurfInfo *)info);
  return 0;
}

/* 0040c480 */
/* P68_ScreenReset — Game.exe 0040c480.  Leaves the frontend: resets it and, if 0041B1C0 allows, restores the
   saved screen mode; with restore != 0 also restores the saved level (only upwards), intro position and
   three settings from P68_Saved and saves the config.  Finally re-runs the frontend init 0040BF50. */
void P68_ScreenReset(int32_t restore) {
  P56_ResetFrontend();
  if (P68_Fn41B1C0() != 0) {
    if (P68_ModeW != P19_ScrW || P68_ModeH != P19_ScrH) P55_SetScreen(P68_ModeW, P68_ModeH);
    if (restore != 0) {
      if (P19_Level < P68_Saved[0]) P19_Level = P68_Saved[0];
      P68_IntroCur = P68_IntroBase + (uint32_t)P68_Saved[1] * 0x10u;
      P68_IntroA = P68_Saved[2];
      S_0127104C = (uint32_t)P68_Saved[3];
      P68_B87E54 = P68_Saved[4];
      P58_SaveConfig();
    }
    P68_Fn41B3AB();
    NoopFn0041b3a6();
  }
  Call0040BF50();
}

/* P68_SpawnCar — Game.exe 004a67b0.  Takes a free traffic car slot (0xcd8-byte objects at P12_0112da00) for record
   rec: rec[5] = slot + 1 (in-use id), slot initialised by P51_InitCarSlot, live-traffic counter + 1.
   Returns the slot or NULL when none is free.  Off-by-one kept from the original (see the note below). */
/* 004a67b0: оригинал берёт слот с номером i (1..8), хотя 004a6749 инициализировал i−1 — сохранено намеренно */
uint8_t *P68_SpawnCar(uint8_t *rec, uint32_t owner) {
  uint8_t *slot = NULL;
  int32_t i = P62_FindFreeTrafficSlot();
  if (i != -1) {
#ifndef RE_HOOK_BUILD
    if (i >= 8) return NULL;   /* native: массив из 8 слотов, оригинал здесь пишет за его конец */
#endif
    slot = (uint8_t *)P12_0112da00 + (uint32_t)i * 0xcd8u;
    rec[5] = (uint8_t)(i + 1);
    P51_InitCarSlot(owner, slot, (uint32_t)i);
    G0112B284 += 1;
    P68_D11A48 = 0;
  }
  return slot;
}
