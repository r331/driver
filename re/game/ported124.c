/* ported124 — motel screen (answering machine samples, keys, entry), car selection, 640x480 BMP loading, debug.log,
   the watch-variable display and the replay director's menu navigation and per-frame handler (Game.exe, cdecl).
   Original note (addresses and thunks): */
/* v1.69: ported124 — восстановлено из Game.exe. Все функции cdecl (work/rets.py: ret без операнда).
   00416794 — клавиши мотеля: Ghidra видит __fastcall(param_1), но ECX нигде не читается (push ecx — резерв локала,
     IsKeyDown 004e383a берёт один аргумент); native-версия принимает мусорный аргумент и игнорирует его, вызывать с 0.
   00416d6d — имя сэмпла AUDIO\MOTEL\ANS%03d/CAR%03d (min 2, +1)/JOKE%03d (min 3) по флагам пункта P100_ItemTab, ChangeSample(…, 7).
   0040c610/0040d6e8 — BMP 640×480×24 (буфер 0x12c000 из DebugMalloc frontend.c:0x1d5), пиксель B,G,R → +2,+1,+0 из 4 байт.
   004182b0 — вход в мотель; 004171f0 — экран выбора машины (CARSEL%d.FBD, по выходу FLAT%d.FBD).
   004bf2a0 — DebugLog: debug.log "r+t" — если нет или уже писали (00b20254 ≠ 0) → "a+t", иначе "wt"; "%s\n", 00b20254 = ftell.
   004bf4a1 — наблюдаемые переменные: формат "0%bb" (тип 1, двоичный) в MSVC CRT печатается как "0bb" — воспроизведено.
   004c38e2 — ReplayMenuHandler; 004c813d — HandleDirector (thunk-и: 00401a6e→004c9bf4 LogWaypoint, 004028d3→004c52d9
     SyncCameraFromList, 004028a1→004c5367 DirNopStub, 004016b3→004c5222 SelectNewCamera, 00402347→004c38e2,
     0040264e→004c2d73 P102_DirFreeCam, 0040220c→004c2ab0 P97_DirKeys, 00402239→004c2b9a P98_DirCamKeys;
     0040209f→004c419e FindNodeByLink, 00402955→004c4151 FindNodeById, 00401e8d→004c43b6 — действие узла меню повтора,
     нет в Ghidra-списке, вызывается через unported.h P124_Fn4C43B6). */
#include "ported132.h"
#include "ported124.h"
#include "ported125.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "reptr.h"
#include "director.h"
#include "dirnodes.h"
#include "directorstorage.h"
#include "smallfuncs.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported9.h"
#include "ported12.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported29.h"
#include "ported30.h"
#include "ported31.h"
#include "ported36.h"
#include "ported43.h"
#include "ported47.h"
#include "ported48.h"
#include "ported57.h"
#include "ported59.h"
#include "ported61.h"
#include "ported62.h"
#include "ported66.h"
#include "ported67.h"
#include "ported68.h"
#include "ported77.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported102.h"
#include "ported105.h"
#include "ported110.h"
#include "ported117.h"
#include "ported118.h"
#include "ported119.h"
#include "ported33.h"
#include "globalsets.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P124_ReplayPrev")
#undef P124_ReplayPrev
#pragma push_macro("P124_ReplayPrev") /*gvi*/
#undef P124_ReplayPrev /*gvi*/
int32_t P124_ReplayPrev;
#pragma pop_macro("P124_ReplayPrev") /*gvi*/
#pragma pop_macro("P124_ReplayPrev")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P124_DirBlink")
#undef P124_DirBlink
#pragma push_macro("P124_DirBlink") /*gvi*/
#undef P124_DirBlink /*gvi*/
int32_t P124_DirBlink;
#pragma pop_macro("P124_DirBlink") /*gvi*/
#pragma pop_macro("P124_DirBlink")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P124_LogSize")
#undef P124_LogSize
#pragma push_macro("P124_LogSize") /*gvi*/
#undef P124_LogSize /*gvi*/
int32_t P124_LogSize;
#pragma pop_macro("P124_LogSize") /*gvi*/
#pragma pop_macro("P124_LogSize")
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P124_LogOn") /*gvi*/
#undef P124_LogOn /*gvi*/
int32_t P124_LogOn = 1;                      /* .data 00553bbc */
#pragma pop_macro("P124_LogOn") /*gvi*/
#endif

#include "memrw.h"

#include "dik.h"   /* DirectInput scan codes */

/* Motel answering-machine item flags (+0 u16). */
#define MITEM_MISSION 0x02   /* selecting it starts a mission (P67_Res51C = item) */
#define MITEM_JOKE    0x04   /* JOKE%03d sample */
#define MITEM_CAR     0x08   /* CAR%03d sample; selecting it opens the car selection for row +2 */
#define MITEM_PLAYED  0x10   /* set once its sample was played */

/* Answering-machine buttons (P9_005fe9f0, cycled with Left / Right, activated with Enter). */
enum { MBTN_PREV = 0, MBTN_PLAY = 1, MBTN_NEXT = 2, MBTN_SELECT = 3 };

/* запись пункта меню мотеля (шаг 8): +0 флаги uint16, +2 номер uint16 */
static uint8_t *motel_item(void) {
  uint8_t *t = (uint8_t *)re_ptr(P100_ItemTab);
  return t ? t + P100_ItemSel * 8 : NULL;
}
static uint16_t rd16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }

/* ---- 00416d6d ---- */
static char s_snd_name[32];                  /* в оригинале — локальный буфер; static, чтобы адрес прошёл через ChangeSample */
/* P124_MotelSample — Game.exe 00416d6d.  Plays the message of the selected answering-machine item into sample slot 7:
   AUDIO\MOTEL\ANS<n>.WAV, CAR<min(n,2)+1>.WAV (car item) or JOKE<min(n,3)>.WAV (joke item); marks it as played. */
void P124_MotelSample(void) {
  P48_FreeVoice(10);
  uint8_t *it = motel_item();
  if (it == NULL) return;                    /* native: таблица пунктов вне известных областей */
  uint16_t fl = (uint16_t)(rd16(it) | MITEM_PLAYED); memcpy(it, &fl, 2);
  uint32_t n = rd16(it + 2);
  if ((fl & MITEM_JOKE) == 0) {
    if ((fl & MITEM_CAR) == 0) snprintf(s_snd_name, sizeof s_snd_name, "AUDIO\\MOTEL\\ANS%03d.WAV", (int)n);
    else snprintf(s_snd_name, sizeof s_snd_name, "AUDIO\\MOTEL\\CAR%03d.WAV", (int)((n < 3 ? n : 2) + 1));
  } else snprintf(s_snd_name, sizeof s_snd_name, "AUDIO\\MOTEL\\JOKE%03d.WAV", (int)(n < 4 ? n : 3));
  if (P68_ChangeSample((int32_t)re_addr(s_snd_name), 7) != 0) SoundPlay00523E50(7, 10, 0x5622);
}

/* ---- 00416794 ---- */
/* P124_MotelKeys — Game.exe 00416794.  Answering-machine keys: Esc -> -1 (leave); Left / Right cycle the four buttons;
   Enter activates: previous / replay / next message, or select — a mission item returns 1 (mission chosen), a car
   item runs the car selection and returns to the motel.  Otherwise 0.  junk is the unused ECX of the original. */
int32_t P124_MotelKeys(int32_t junk) {
  (void)junk;
  if (IsKeyDown(DIK_ESCAPE)) { Ui00418886(); return -1; }
  if (IsKeyDown(DIK_LEFT)) {
    Ui00418886(); if (--P9_005fe9f0 < 0) P9_005fe9f0 = 3; SelectByDifficulty_00416D17(); return 0;
  }
  if (IsKeyDown(DIK_RIGHT)) {
    Ui00418886(); if (3 < ++P9_005fe9f0) P9_005fe9f0 = 0; SelectByDifficulty_00416D17(); return 0;
  }
  if (!IsKeyDown(DIK_RETURN)) return 0;
  Ui00418886();
#ifndef RE_HOOK_BUILD
  if (getenv("RE_MOTELDBG")) {               /* v2.12: отладка автоответчика */
    uint8_t *it = motel_item();
    fprintf(stderr, "[motel] Enter: кнопка %d пункт %d/%d флаги %04x номер %d (таблица %08x)\n", (int)P9_005fe9f0, (int)P100_ItemSel,
            (int)P100_ItemN, it ? rd16(it) : 0xffff, it ? rd16(it + 2) : -1, (unsigned)P100_ItemTab);
  }
#endif
  switch (P9_005fe9f0) {
  case MBTN_PREV: if (--P100_ItemSel < 0) P100_ItemSel = P100_ItemN - 1; P124_MotelSample(); break;
  case MBTN_PLAY: P124_MotelSample(); break;
  case MBTN_NEXT: if (P100_ItemN <= ++P100_ItemSel) P100_ItemSel = 0; P124_MotelSample(); break;
  case MBTN_SELECT: {
    uint8_t *it = motel_item();
    if (it == NULL) break;
    uint16_t fl = rd16(it);
    if (fl & MITEM_MISSION) { P12_Fn00418433(0x0054e250u, 0x004169afu); P67_Res51C = P100_ItemSel; return 1; }
    if (fl & MITEM_CAR) {
      P12_Fn00418433(0x0054e250u, 0x004169afu);
      P48_FreeVoice(10);
      P124_CarSelect((int32_t)rd16(it + 2));
      Ui0041A1EC(4);
      P118_CamRoute(9);
      Ui004183E8();
      P12_Fn004183F7(0x0054e250u, 0x004169afu);
    }
    break;
  }
  default: P9_005fe9f0 = 0; break;
  }
  return 0;
}

/* ---- 0040d6e8 ---- */
/* BMP header checks of P124_ReadBmp: "BM", 640 x 480, 24 bpp, BI_RGB. */
#define BMP_MAGIC   0x4d42
#define BMP_HDR     0x36
#define SCREEN_W    0x280
#define SCREEN_H    0x1e0

/* P124_ReadBmp — Game.exe 0040d6e8.  Loads an uncompressed 640x480 24-bit BMP into dst as 4-byte pixels (B, G, R
   stored at +2, +1, +0; byte +3 untouched), flipping the bottom-up rows.  Returns 1, or 0 for a missing / other file. */
int32_t P124_ReadBmp(const char *name, uint8_t *dst) {
  int32_t ok = 0;
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  uint8_t h[BMP_HDR];
  memset(h, 0, sizeof h);
  g_fread(h, 1, BMP_HDR, f);
  int32_t w = rd32(h + 0x12), hh = rd32(h + 0x16);
  int16_t bpp; memcpy(&bpp, h + 0x1c, 2);
  if (rd16(h) == BMP_MAGIC && w == SCREEN_W && hh == SCREEN_H && bpp == 0x18 && rd32(h + 0x1e) == 0) {
    for (int32_t y = SCREEN_H - 1; y >= 0; y--)
      for (int32_t x = 0; x < w; x++) {
        uint8_t *p = dst + (y * w + x) * 4;
        p[2] = (uint8_t)g_fgetc(f);
        p[1] = (uint8_t)g_fgetc(f);
        p[0] = (uint8_t)g_fgetc(f);
      }
    ok = 1;
  }
  g_fclose(f);
  return ok;
}

/* ---- 0040c610 ---- */
/* P124_ShowBmp — Game.exe 0040c610.  Shows a 640x480 BMP full screen (blitted 4 times — once per buffer of the swap
   chain, presumably) and with wait != 0 waits for all keys up, then any key down. */
void P124_ShowBmp(const char *name, int32_t wait) {
  if (P117_ClipFn) P117_ClipFn(0, 0, P19_ScrW, P19_ScrH);
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(0x12c000,   /* 640 * 480 * 4 */ "D:\\Driver\\Game\\frontend\\frontend.c", 0x1d5);
  if (buf == NULL) return;
  if (P124_ReadBmp(name, buf) != 0) {
    P105_BlitScaled(buf); P105_BlitScaled(buf); P105_BlitScaled(buf); P105_BlitScaled(buf);
    if (wait != 0) {
      while (P48_AnyKey() != 0) {}
      while (P48_AnyKey() == 0) {}
    }
  }
  P98_DebugFree(buf);
}

/* (*01270d6c)(0,1,1) = grTexFilterMode — по имени из таблицы Glide (как ported119) */
#ifdef RE_HOOK_BUILD
#  define P124_STD __attribute__((stdcall))
#else
#  define P124_STD
#endif
static void tex_filter(int32_t a, int32_t b, int32_t c) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grTexFilterMode@12") == 0) {
      void (P124_STD *f)(int32_t, int32_t, int32_t) = (void (P124_STD *)(int32_t, int32_t, int32_t))P33_GlideProc(i);
      if (f != NULL) f(a, b, c);
      return;
    }
}

/* ---- 004182b0 ---- */
/* P124_MotelInit — Game.exe 004182b0.  Enters the motel: flags, icon scale, the motel flyby of the current city, level
   load, MOTEL.DSS bank, screen state (perspective scale 384, bilinear filtering), CD track 3 when CD audio is on. */
void P124_MotelInit(void) {
  G6_00B87EEC = 1;
  G6_00B87EFC = 1;
  P110_IconKX = (float)P19_ScrW / P19_DivW;
  P110_IconKY = (float)P19_ScrH / P19_DivH;
  P47_LoadFlyby(D_00b87e30);
  Ui0041A192();
  P125_LevelLoad();
  P48_ResetAll();
  P77_LoadBank("MOTEL.DSS", 0);
  SoundSetVolB0052360D(5);
  P12_Fn00516E76();
  SetRGB00516EB4(0, 0, 0);
  P43_ScaleA = 384.0f;                       /* 0x43c00000 */
  tex_filter(0, 1, 1);
  if (FnPtr01270E80) FnPtr01270E80(2);
  DrvSetMode0042655A(1);
  if (G6_01270DE4) G6_01270DE4(3);
  if (Q00B87E90 != 0) { P25_InitCDAudio(); P25_PlayCDTrack(3); }
  P21_FrameTicks();
  P66_Nest = 1;
}

/* ---- 004171f0 ---- */
/* P124_CarSelect — Game.exe 004171f0.  Car selection screen for row 0..2 (CARSEL<row>.FBD flyby, row table
   0054e320/28/30): runs its own frame loop until P119_CarSelKey returns non-zero, then reloads the city's FLAT<n>.FBD
   and returns that result.  Missing files are fatal. */
int32_t P124_CarSelect(int32_t row) {
  char name[32];
  LoadArrowIcons00417353();
  P66_LoadFlag = 1;
  snprintf(name, sizeof name, "SCRIPTS\\FLYBY\\CARSEL%d.FBD", (int)row);
  if (P132_LoadFlyby(name) == 0) P30_FatalError("Files missing, please reinstall");
  if (row == 1) P119_SelPtr = 0x0054e328u;
  else if (row == 2) P119_SelPtr = 0x0054e330u;
  else { row = 0; P119_SelPtr = 0x0054e320u; }
  P119_SelIdx = 0;
  Ui0041A1EC((int32_t)P119_SelByte(0));
  P118_CamRoute((uint32_t)P119_SelByte(0));
  Ui004183E8();
  P12_Fn004183F7(0x0054e300u, 0x00417479u);
  for (;;) {
    Call00522323();
    P36_PollInput();
    if ((P59_NoKeyFlag | D_005feda0 | UiVar005FEDA0) == 0) {   /* три native-псевдонима 005feda0 */
      int32_t r = P119_CarSelKey(row);
      if (r != 0) {
        snprintf(name, sizeof name, "SCRIPTS\\FLYBY\\FLAT%d.FBD", (int)D_00b87e30);
        if (P132_LoadFlyby(name) == 0) P30_FatalError("Files missing, please reinstall");
        P12_Fn00418433(0x0054e300u, 0x00417479u);
        P66_LoadFlag = 0;
        return r;
      }
    }
    P66_ScreenFrame(0x0054e300u, 0x00417479u);
  }
}

/* ---- 004bf2a0 ---- */
/* P124_DebugLog — Game.exe 004bf2a0.  Appends msg + "\n" to debug.log; the first write of a run truncates an existing
   file ("wt"), later writes append (P124_LogSize = file size after the last write).  Off when P124_LogOn == 0. */
void P124_DebugLog(const char *msg) {
  if (P124_LogOn == 0) return;
  void *f = g_fopen("debug.log", "r+t");
  if (f == NULL || P124_LogSize != 0) {
    if (f != NULL) g_fclose(f);
    f = g_fopen("debug.log", "a+t");
  } else {
    g_fclose(f);
    f = g_fopen("debug.log", "wt");
  }
  if (f == NULL) return;
  if (msg != NULL) g_fwrite(msg, 1, strlen(msg), f);
  g_fwrite("\n", 1, 1, f);
  P124_LogSize = (int32_t)g_ftell(f);
  g_fclose(f);
}

/* ---- 004bf4a1 ---- */
/* P124_WatchShow — Game.exe 004bf4a1.  Debug overlay: for each of 32 watch entries (0xc bytes: name address, variable
   address, type, size code 0/1/2 = 8/16/32 bit) prints "name: value" — type 0 hex, 1 "binary" (prints the literal
   "0bb", as MSVC did), 2 unsigned, 3 signed, 4 float, 5 string. */
void P124_WatchShow(void) {
  char *buf = (char *)&A_010EA620[0x200];   /* 010ea820 — буфер строки (0x80 до 010ea8a0) */
  CursorSet004D94B7(0, 0);
  for (int32_t i = 0; i < 0x20; i++) {
    uint8_t *e = &A_010EA620[i * 0xc];
    if (rd32(e) == 0) continue;
    P96_LogLine((const char *)re_ptr((uint32_t)rd32(e)));
    P96_LogLine(": ");
    uint8_t ty = e[8], sz = e[9];
    uint32_t va = (uint32_t)rd32(e + 4);
    const uint8_t *v = (const uint8_t *)re_ptr(va);
    int show = 1;
    if (ty <= 4 && v == NULL) show = 0;      /* native: адрес переменной вне известных областей */
    switch (ty) {
    case 0:
      if (!show) break;
      if (sz == 0) snprintf(buf, 0x80, "%#04x", (unsigned)v[0]);
      else if (sz == 1) { int16_t s; memcpy(&s, v, 2); snprintf(buf, 0x80, "%#06x", (unsigned)(int32_t)s); }
      else snprintf(buf, 0x80, "%#010x", (unsigned)rd32(v));
      P96_LogLine(buf);
      break;
    case 1:
      if (!show) break;
      strcpy(buf, "0bb");                    /* "0%bb": MSVC печатает неизвестный %b как 'b' */
      P96_LogLine(buf);
      break;
    case 2:
      if (!show) break;
      if (sz == 0) snprintf(buf, 0x80, "%u", (unsigned)v[0]);
      else if (sz == 1) snprintf(buf, 0x80, "%u", (unsigned)rd16(v));
      else snprintf(buf, 0x80, "%u", (unsigned)rd32(v));
      P96_LogLine(buf);
      break;
    case 3:
      if (!show) break;
      if (sz == 0) snprintf(buf, 0x80, "%d", (int)(int8_t)v[0]);
      else if (sz == 1) { int16_t s; memcpy(&s, v, 2); snprintf(buf, 0x80, "%d", (int)s); }
      else snprintf(buf, 0x80, "%d", (int)rd32(v));
      P96_LogLine(buf);
      break;
    case 4: {
      if (!show) break;
      float fv; memcpy(&fv, v, 4);
      snprintf(buf, 0x80, "%f", (double)fv);
      P96_LogLine(buf);
      break;
    }
    case 5:
      snprintf(buf, 0x80, "%s", v ? (const char *)v : "");
      P96_LogLine(buf);
      break;
    default: break;
    }
    CursorWrap004D9478();
  }
}

/* ---- 004c38e2 ---- */
/* P124_ReplayMenu — Game.exe 004c38e2 (ReplayMenuHandler).  Moves the replay menu selection DirectorUnk7C through the
   node graph by input bits dir: 1 / 2 follow link1 backwards / forwards, 4 / 8 link2, skipping nodes with flag 4
   (special wrap between nodes 1 and 8); 0x10 activates the node (P125_ReplayNodeAction).  Moving between nodes
   6 <-> 9 and 7 <-> 0xd saves / restores the camera state.  TODO(RE): unsure which bits are up/down/left/right. */
void P124_ReplayMenu(int32_t dir) {
  int more = 1;
  P124_ReplayPrev = DirectorUnk7C;
  DIR_NODE *n = FindNodeById(DirectorUnk7C);
  if (n == NULL) return;
  switch (dir) {
  case 0: break;
  case 1:
    if (DirectorUnk7C == 1) { DirectorUnk7C = 8; break; }
    while (more) {
      more = 0;
      int32_t id = n->id;
      n = FindNodeByLink(id);
      if (n == NULL || n->link1 != id) return;
      if (n->flags & 4) {
        if (n->id == 1) { n = FindNodeById(8); if (n == NULL) return; }
        else more = 1;
      }
    }
    DirectorUnk7C = n->id;
    break;
  case 2:
    if (DirectorUnk7C == 8) { DirectorUnk7C = 1; break; }
    if ((n->flags & 8) == 0 || n->id == 1) {
      n = FindNodeById(n->link1);
      do {
        if (n == NULL) return;
        if ((n->flags & 4) == 0) more = 0; else n = FindNodeById(n->link1);
      } while (more);
    }
    DirectorUnk7C = n->id;
    break;
  case 4:
    while (more) {
      int32_t id = n->id;
      n = FindNodeByLink(id);
      if (n == NULL || n->link2 != id) return;
      more = (n->flags & 4) != 0;
    }
    DirectorUnk7C = n->id;
    break;
  case 8:
    if ((n->flags & 0x10) == 0) {
      n = FindNodeById(n->link2);
      do {
        if (n == NULL) return;
        if ((n->flags & 4) == 0) more = 0; else n = FindNodeById(n->link2);
      } while (more);
    }
    DirectorUnk7C = n->id;
    break;
  case 0x10: P125_ReplayNodeAction(DirectorUnk7C); break;
  default: DebugLog("ReplayMenuHandler: Error! - Unknown movement/selection."); break;
  }
  if (DirectorUnk7C == 9 && P124_ReplayPrev == 6) BackupCameraState();
  if (DirectorUnk7C == 0xd && P124_ReplayPrev == 7) BackupCameraState();
  if (DirectorUnk7C == 7 && P124_ReplayPrev == 0xd) RestoreCameraBackup();
  if (DirectorUnk7C == 6 && P124_ReplayPrev == 9) RestoreCameraBackup();
}

/* ---- 004c813d ---- */
/* Playback continues: frames left and Esc not pressed. */
static int dir_playing(void) { return DirectorUnk6C < DirectorLastFrame && IsKeyDown(DIK_ESCAPE) == 0; }
static void dir_quit(int32_t sub) { FreeCameraList(); FreeDirectorBuffer(); SetDirectorMode(0, sub, 0); }
/* P124_HandleDirector — Game.exe 004c813d (HandleDirector).  Per-frame replay director: syncs the frame counter,
   '.' toggles P29_Flag48, then runs the behaviour of the current mode (see SetDirectorMode in ported29.c: record
   waypoints, menu, playback variants, camera editors; at the end of playback saves $TEMP$.CAMS and returns to mode 0
   or the menu), animates the selection colour (blink, or a pulsing yellow when P29_FlagA4), checks the camera
   distance, restores the camera state and refreshes the menu nodes. */
void P124_HandleDirector(void) {
  DirectorUnk6C = P62_Frame;
  if (IsKeyDown(DIK_PERIOD)) P29_Flag48 = (P29_Flag48 == 0);
  if (CamBackupValid != 0) P61_StoreCamState((uint8_t *)&DirectorCam);
  uint32_t keys = ReadDirectorKeys();
  int32_t prev = DirectorUnk7C;
  switch (P29_Mode) {
  case 0: LogWaypoint(P62_Frame); break;
  case 1: if (DirectorUnk6C < 2) SyncCameraFromList(); else SetDirectorMode(0xc, DirectorUnk7C, 0); break;
  case 2: DirNopStub(); break;
  case 3: if (dir_playing()) { SelectNewCamera(); P124_ReplayMenu((int32_t)keys); } else SetDirectorMode(1, 2, 0); break;
  case 4: if (dir_playing()) { SyncCameraFromList(); P124_ReplayMenu((int32_t)keys); } else SetDirectorMode(1, 1, 0); break;
  case 5: SyncCameraFromList(); SetDirectorMode(1, 4, 0); break;
  case 6:
    if (DirectorUnk6C < DirectorLastFrame) {
      SyncCameraFromList();
      if (DirectorCam.id == DirectorUnk6C) SetDirectorMode(1, 3, 0); else P124_ReplayMenu((int32_t)keys);
    } else SetDirectorMode(1, 3, 0);
    break;
  case 7: case 0xe:
    if (dir_playing()) SyncCameraFromList();
    else {
      dir_quit(0);
      G005F7E54 = 1; P17_Const6 = 1;         /* native-псевдонимы 005f7e54 */
      G6_00B87E20 = 0;
      SetLatchValue0050E940(0);
    }
    break;
  case 8: P102_DirFreeCam(keys); break;
  case 9: P97_DirKeys(keys); break;
  case 10: P98_DirCamKeys(keys); break;
  case 0xb:
    if (dir_playing()) { SelectNewCamera(); P124_ReplayMenu((int32_t)keys); }
    else { SaveDirector("REPLAYDATA\\USER\\$TEMP$.CAMS"); SetDirectorMode(0, 0, 0); SetLatchValue0050E940(1); }
    break;
  case 0xc: P124_ReplayMenu((int32_t)keys); break;
  case 0xd:
    if (dir_playing()) { SyncCameraFromList(); P124_ReplayMenu((int32_t)keys); }
    else { SaveDirector("REPLAYDATA\\USER\\$TEMP$.CAMS"); SetDirectorMode(0, 0, 0); SetLatchValue0050E940(1); }
    break;
  case 0xf:
    if (dir_playing()) SyncCameraFromList();
    else { dir_quit(1); SetLatchValue0050E940(1); }
    break;
  default: DebugLog("HandleDirector: Error! - Unknown control type for replays!"); break;
  }
  if (0x3f < ++DirIndicatorCnt) DirIndicatorCnt = 0;
  if (0x1f < ++P124_DirBlink) P124_DirBlink = 0;
  if (P29_FlagA4 == 0) DirSelectedColor = P124_DirBlink < 0x10 ? 0xffff00u : 0xff8b00u;
  else {
    uint32_t u = (uint32_t)P29_Flag74 + 5;
    P29_Flag74 = (int32_t)(u & 0xff);
    if ((u & 0x80) == 0) { uint32_t c = 0xffu - (uint32_t)P29_Flag74; DirSelectedColor = c << 16 | c << 8; }
    else { uint32_t c = (u & 0x7f) + 0x80; DirSelectedColor = c << 16 | c << 8; }
  }
  if (prev != DirectorUnk7C) P124_DirBlink = 0;
  P99_CamCheckDist((int32_t *)&DirectorCam);
  if (CamBackupValid == 0) {
    DIRECTOR_CAMERA *c = FindCameraById(DirectorUnk6C);
    if (c != NULL) { P61_RestoreCamState((uint8_t *)c); P61_StoreCamState((uint8_t *)&DirectorCam); }
  } else P61_RestoreCamState((uint8_t *)&DirectorCam);
  P102_DirMenuNodes();
}
