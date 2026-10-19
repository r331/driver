/* v2.22: selftest эмуляции CD-audio (platform/sdl/plat_cdaudio.c) — разбор .cue, выбор источника дорожки, TOC как у MCI,
   PlayCDTrack → конец дорожки → MM_MCINOTIFY → P31_WndProc → повтор (цикл как в оригинале), MCI_STOP/продолжение,
   громкость aux, заглушка (тишина/тон), RE_MUSIC=off. Файлы — синтетические, в каталоге cd_test текущего каталога. */
#include "../platform/plat.h"
#include "../platform/sdl/plat_cdaudio.h"
#include "../game/ported25.h"
#include "../game/ported31.h"
#include "../game/engine.h"
#include "../game/ported5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>

#define CK(c) do { if (!(c)) { printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #c); rc = 1; goto out; } } while (0)

static void put32(FILE *f, uint32_t v) { fputc((int)(v & 255), f); fputc((int)(v >> 8 & 255), f); fputc((int)(v >> 16 & 255), f); fputc((int)(v >> 24), f); }
static void put16(FILE *f, uint32_t v) { fputc((int)(v & 255), f); fputc((int)(v >> 8 & 255), f); }
/* WAV 16 бит: значение отсчёта i канала c = gen(i, c) */
static int wav16(const char *p, int rate, int ch, int frames, int (*gen)(int, int)) {
  FILE *f = fopen(p, "wb"); if (!f) return -1;
  uint32_t data = (uint32_t)(frames * ch * 2);
  fwrite("RIFF", 1, 4, f); put32(f, 36 + data + 8 + 4); fwrite("WAVE", 1, 4, f);
  fwrite("LIST", 1, 4, f); put32(f, 4); fwrite("INFO", 1, 4, f);                 /* посторонний чанк — пропускается */
  fwrite("fmt ", 1, 4, f); put32(f, 16); put16(f, 1); put16(f, (uint32_t)ch); put32(f, (uint32_t)rate); put32(f, (uint32_t)(rate * ch * 2)); put16(f, (uint32_t)(ch * 2)); put16(f, 16);
  fwrite("data", 1, 4, f); put32(f, data);
  for (int i = 0; i < frames; i++) for (int c = 0; c < ch; c++) put16(f, (uint32_t)(uint16_t)(int16_t)gen(i, c));
  fclose(f); return 0;
}
static int g_a(int i, int c) { return (int)((i % 1000) * 8 - 4000) * (c ? -1 : 1); }   /* пила, правый канал инвертирован */
static int g_m(int i, int c) { (void)c; return i & 1 ? 3000 : -3000; }               /* моно 22050 */
static float exp_a(int i, int c) { return (float)g_a(i, c) / 32768.0f; }

int test_v222(void) {
  int rc = 0;
  int32_t save_q = Q00B87E90;
  /* --- 1. разбор .cue --- */
  {
    static cda_cue c;
    const char *cue =
      "\xef\xbb\xbfREM COMMENT \"x\"\r\n"
      "FILE \"Driver (Disc).bin\" BINARY\r\n"
      "  TRACK 01 MODE1/2352\r\n    INDEX 01 00:00:00\r\n"
      "  TRACK 02 AUDIO\r\n    INDEX 00 00:02:00\r\n    INDEX 01 00:04:00\r\n"
      "  TRACK 03 AUDIO\r\n    PREGAP 00:02:00\r\n    INDEX 01 00:10:00\r\n"
      "FILE track04.bin MOTOROLA\n  TRACK 04 AUDIO\n    INDEX 00 00:00:00\n";
    CK(cda_cue_parse(cue, &c) == 0);
    CK(c.nfiles == 2 && c.ntracks == 4);
    CK(!strcmp(c.files[0], "Driver (Disc).bin") && c.ftype[0] == 0 && !strcmp(c.files[1], "track04.bin") && c.ftype[1] == 1);
    CK(c.t[0].num == 1 && !c.t[0].audio && c.t[1].num == 2 && c.t[1].audio && c.t[1].start == 300 && c.t[2].start == 750);
    CK(c.t[3].file == 1 && c.t[3].start == 0);                 /* только INDEX 00 — берётся он */
    int64_t fb[2] = { 2352LL * 1000, 2352LL * 77 + 100 };
    cda_cue_resolve(&c, fb);
    CK(c.t[0].len == 300 && c.t[1].len == 450 && c.t[2].len == 250 && c.t[3].len == 77);
    CK(cda_cue_parse("FILE a.bin BINARY\nTRACK 02 AUDIO\nINDEX 01 00:61:00\n", &c) == 3);   /* секунды > 59 */
    CK(cda_cue_parse("TRACK 02 AUDIO\n", &c) == 1);                                       /* TRACK без FILE */
    CK(cda_cue_parse("FILE a.bin BINARY\nTRACK 02 AUDIO\n", &c) < 0);                    /* без INDEX */
  }
  /* --- 2. каталог: Track02.wav (44100 стерео 1 с), track03.cdda.wav (22050 моно), cue/bin: 02 (уступает файлу), 04 (BE), 05 --- */
  mkdir("cd_test", 0777);
  CK(wav16("cd_test/Track02.wav", 44100, 2, 44100, g_a) == 0);
  CK(wav16("cd_test/track03.cdda.wav", 22050, 1, 22050, g_m) == 0);
  {
    FILE *b = fopen("cd_test/IMAGE.BIN", "wb"); CK(b != NULL);
    for (int s = 0; s < 10 * 2352 / 2; s++) put16(b, 0);                       /* дорожка 1 «данные»: 10 секторов */
    for (int s = 0; s < 20 * 588; s++) { put16(b, 0x1111); put16(b, 0x2222); } /* дорожка 2 в образе: 20 секторов */
    for (int s = 0; s < 30 * 588; s++) { fputc(0x12, b); fputc(0x34, b); fputc(0xff, b); fputc(0x00, b); } /* 4 — big-endian: L 0x1234, R 0xff00 */
    fclose(b);
    FILE *c = fopen("cd_test/image.cue", "w"); CK(c != NULL);
    fputs("FILE \"image.bin\" MOTOROLA\n TRACK 01 MODE1/2352\n  INDEX 01 00:00:00\n TRACK 02 AUDIO\n  INDEX 01 00:00:10\n"
          " TRACK 04 AUDIO\n  INDEX 00 00:00:29\n  INDEX 01 00:00:30\n", c);
    fclose(c);
  }
  unsetenv("RE_MUSIC"); unsetenv("RE_MUSIC_STUB"); unsetenv("RE_CD_TRACKS"); unsetenv("RE_MUSIC_VOL");
  setenv("RE_MUSIC_STUB_LEN", "2", 1);
  cda_reset("cd_test");
  {
    const char *p = NULL; int64_t fr = 0;
    CK(cda_track_source(2, &p, &fr) == CDA_SRC_WAV && strstr(p, "Track02.wav") && fr == 44100);
    CK(cda_track_source(3, &p, &fr) == CDA_SRC_WAV && strstr(p, "track03.cdda.wav") && fr == 44100);
    CK(cda_track_source(4, &p, &fr) == CDA_SRC_CUE && fr == 30 * 588);
    CK(cda_track_source(5, &p, &fr) == CDA_SRC_NONE && p == NULL && fr == 2 * 44100);   /* заглушка 2 с */
  }
  /* --- 3. TOC как у MCI cdaudio (TMSF): позиция T:0:0:0, длина MSF --- */
  plat_cd_close(); P25_CdOpen = 0; P25_CdPlaying = 0;
  CK(P25_InitCDAudio() == 1 && P25_CdOpen == 1 && P25_CdTracks == 10 && P25_AuxDev == 0);
  {
    uint32_t pos = 0, len = 0;
    CK(plat_cd_track_info(2, &pos, &len) == 0 && pos == 2u && len == (0u | 1u << 8 | 0u << 16));       /* 1 с */
    CK(plat_cd_track_info(4, &pos, &len) == 0 && len == (0u | 0u << 8 | 30u << 16));                  /* 30 кадров CD */
    CK(plat_cd_track_info(11, &pos, &len) == 1);
  }
  /* --- 4. PlayCDTrack(2): данные, громкость, конец → уведомление → WndProc → повтор --- */
  {
    static float acc[2 * 44100 + 64];
    int tr; int64_t pos, end; void *h; uint32_t wp; int32_t lp;
    Q00B87E90 = 1;
    P25_CDSetVolume(0xffff);
    P25_PlayCDTrack(2);
    CK(P25_CdPlaying == 1 && P25_CdTrack == 2 && cda_state(&tr, &pos, &end) && tr == 2 && pos == 0 && end == 44100);
    memset(acc, 0, sizeof acc); cda_mix(acc, 3000);
    for (int i = 0; i < 3000; i++) CK(fabsf(acc[2 * i] - exp_a(i, 0)) < 1e-6f && fabsf(acc[2 * i + 1] - exp_a(i, 1)) < 1e-6f);
    P25_CDSetVolume(0x8000);
    memset(acc, 0, sizeof acc); cda_mix(acc, 10);
    CK(fabsf(acc[0] - exp_a(3000, 0) * (32768.0f / 65535.0f)) < 1e-5f);
    P25_CDSetVolume(0xffff);
    CK(plat_cd_take_notify(&h, &wp, &lp) == 0);
    memset(acc, 0, sizeof acc); cda_mix(acc, 44100);                       /* досюда — 3010, конец на 44100 */
    CK(!cda_state(&tr, &pos, &end) && pos == 44100);
    CK(acc[2 * (44100 - 3010)] == 0.0f);                                    /* после конца — тишина */
    CK(plat_cd_take_notify(&h, &wp, &lp) == 1 && wp == 1 && plat_cd_take_notify(&h, &wp, &lp) == 0);
    P31_WndProc(h, 0x3b9, wp, lp);                                          /* MM_MCINOTIFY(SUCCESSFUL) → P25_CdPlaying = 0 */
    CK(P25_CdPlaying == 0);
    if (Q00B87E90 != 0 && P25_CdPlaying == 0) { P25_InitCDAudio(); P25_PlayCDTrack(2); }   /* как P119_MenuFrame 0040cb9f */
    CK(P25_CdPlaying == 1 && cda_state(&tr, &pos, &end) && tr == 2 && pos == 0);
    memset(acc, 0, sizeof acc); cda_mix(acc, 5);
    CK(fabsf(acc[0] - exp_a(0, 0)) < 1e-6f);                                /* снова с начала — цикл */
    /* MCI_STOP (CDStop) — позиция сохраняется, уведомления нет; CDResume — продолжение без уведомления (MCI_PLAY без NOTIFY) */
    P25_CDStop();
    CK(P25_CdPlaying == 0 && !cda_state(&tr, &pos, &end) && pos == 5);
    memset(acc, 0, sizeof acc); cda_mix(acc, 100); CK(acc[0] == 0.0f);
    P25_CDResume();
    CK(P25_CdPlaying == 1 && cda_state(&tr, &pos, &end) && pos == 5 && end == 44100);
    memset(acc, 0, sizeof acc); cda_mix(acc, 1); CK(fabsf(acc[0] - exp_a(5, 0)) < 1e-6f);
    cda_mix(acc, 44100);
    CK(!cda_state(NULL, NULL, NULL) && plat_cd_take_notify(&h, &wp, &lp) == 0);
    /* дорожка 3: 22050 Гц моно → 44100 стерео (линейная интерполяция), L == R */
    P25_CdPlaying = 0; P25_PlayCDTrack(3);
    CK(cda_state(&tr, &pos, &end) && tr == 3 && end == 44100);
    memset(acc, 0, sizeof acc); cda_mix(acc, 4);
    CK(fabsf(acc[0] - (-3000 / 32768.0f)) < 1e-6f && acc[0] == acc[1]);
    CK(fabsf(acc[2] - 0.0f) < 1e-6f);                                       /* середина между −3000 и 3000 */
    CK(fabsf(acc[4] - 3000 / 32768.0f) < 1e-6f);
    /* дорожка 4 из .cue (MOTOROLA): L 0x1234, R (int16)0xff00 */
    P25_PlayCDTrack(4);
    CK(cda_state(&tr, &pos, &end) && tr == 4 && end == 30 * 588);
    memset(acc, 0, sizeof acc); cda_mix(acc, 2);
    CK(fabsf(acc[0] - 0x1234 / 32768.0f) < 1e-6f && fabsf(acc[1] - (-256 / 32768.0f)) < 1e-6f);
    /* дорожка 5 — заглушка: тишина; RE_MUSIC_STUB=tone — тон */
    P25_PlayCDTrack(5);
    memset(acc, 0, sizeof acc); cda_mix(acc, 2000);
    { float mx = 0; for (int i = 0; i < 4000; i++) mx = fmaxf(mx, fabsf(acc[i])); CK(mx == 0.0f && cda_state(NULL, NULL, &end) && end == 2 * 44100); }
    setenv("RE_MUSIC_STUB", "tone", 1);
    P25_PlayCDTrack(5);
    memset(acc, 0, sizeof acc); cda_mix(acc, 2000);
    { float mx = 0; for (int i = 0; i < 4000; i++) mx = fmaxf(mx, fabsf(acc[i])); CK(mx > 0.03f && mx < 0.06f); }
    unsetenv("RE_MUSIC_STUB");
    /* неверный номер — как в оригинале: «Invalid track number», музыка выключается (Q00B87E90 = 0) */
    P25_PlayCDTrack(11); CK(Q00B87E90 == 0);
    Q00B87E90 = 1;
    P25_CDClose(); CK(P25_CdOpen == 0 && P25_CdPlaying == 0 && !cda_state(NULL, NULL, NULL));
  }
  /* --- 5. пустой каталог: все дорожки — заглушки, устройство открыто; RE_MUSIC=off — «Open CD device failed» --- */
  cda_reset("cd_test/нет_такого");
  { const char *p; int64_t fr; CK(cda_track_source(2, &p, &fr) == CDA_SRC_NONE && fr == 2 * 44100); }
  P25_CdOpen = 0; CK(P25_InitCDAudio() == 1 && P25_CdTracks == 10);
  P25_PlayCDTrack(7); CK(P25_CdPlaying == 1);
  P25_CDClose();
  setenv("RE_MUSIC", "off", 1);
  P25_CdOpen = 0; CK(P25_InitCDAudio() == 0 && P25_CdOpen == 0);
  unsetenv("RE_MUSIC");
out:
  unsetenv("RE_MUSIC_STUB_LEN"); unsetenv("RE_MUSIC_STUB"); unsetenv("RE_MUSIC");
  if (P25_CdOpen) P25_CDClose();
  P25_CdOpen = 0; P25_CdPlaying = 0; P25_CdTrack = 0; P25_CdTracks = 0;
  Q00B87E90 = save_q;
  remove("cd_test/Track02.wav"); remove("cd_test/track03.cdda.wav"); remove("cd_test/IMAGE.BIN"); remove("cd_test/image.cue"); rmdir("cd_test");
  cda_reset(NULL);
  return rc;
}

/* ===================== v2.33: динамическая музыка (PS-стиль) =====================
   Имена файлов → слоты, запасные варианты, гистерезис Drive↔Chase, кроссфейд (синхронный и с начала), смена дня/ночи,
   пауза/продолжение, громкость, выключатель RE_MUSIC_DYNAMIC=0, обычная дорожка для города без набора.
   Файлы — синтетические WAV с постоянным уровнем (у каждого свой), в каталоге cd_dyn текущего каталога. */
static int g_dc;
static int g_const(int i, int c) { (void)i; (void)c; return g_dc; }
static int wavc(const char *p, int value, int frames) { g_dc = value; return wav16(p, 44100, 2, frames, g_const); }
static float lv(int v) { return (float)v / 32768.0f; }
/* смешать n кадров, сообщая игре признаки (как кадр игры) каждые 735 кадров; последний отсчёт L */
static float mixn(int n, int night, int chase) {
  static float acc[2 * 1024];
  float last = 0;
  while (n > 0) { int k = n > 735 ? 735 : n; plat_music_hint(night, chase); memset(acc, 0, sizeof acc); cda_mix(acc, k); last = acc[2 * (k - 1)]; n -= k; }
  plat_music_hint(night, chase);
  return last;
}
int test_v233(void) {
  int rc = 0;
  int32_t save_q = Q00B87E90;
  /* --- 1. имена → слоты --- */
  CK(cda_dyn_classify("01. Miami At Day Drive.mp3", 0) == 0);
  CK(cda_dyn_classify("02. Miami At Day Chase.flac", 0) == 1);
  CK(cda_dyn_classify("04 - MIAMI AT NIGHT CHASE.OGG", 0) == 3);
  CK(cda_dyn_classify("05. San Francisco At Day Drive.wav", 0) == 4);
  CK(cda_dyn_classify("frisco_night_chase.wav", 0) == 7);
  CK(cda_dyn_classify("SF Day Chase.mp3", 0) == 5);
  CK(cda_dyn_classify("09. Los Angeles At Day Drive.wav", 0) == 8);
  CK(cda_dyn_classify("LA-Night-Drive.mp3", 0) == 10);
  CK(cda_dyn_classify("13. New York At Day Drive.wav", 0) == 12);
  CK(cda_dyn_classify("NY night chase.WAV", 0) == 15);
  CK(cda_dyn_classify("Track04.wav", 0) == -1 && cda_dyn_classify("07 - Something.wav", 0) == -1);
  CK(cda_dyn_classify("07 - Something.wav", 1) == 6 && cda_dyn_classify("16.mp3", 1) == 15 && cda_dyn_classify("17.mp3", 1) == -1);
  CK(cda_dyn_classify("Miami Day.mp3", 0) == -1 && cda_dyn_classify("01 Miami Day Drive.jpg", 1) == -1 && cda_dyn_classify("cover.png", 1) == -1);
  CK(cda_dyn_classify("12 New York At Day Drive.mp3", 1) == 12);   /* ключевые слова важнее номера */
  /* --- 2. запасные варианты --- */
  {
    int h[16] = { 0 };
    CK(cda_dyn_pick(h, 0, 0, 0) == -1);
    h[0] = 1; CK(cda_dyn_pick(h, 0, 1, 1) == 0 && cda_dyn_pick(h, 1, 0, 0) == -1);
    memset(h, 0, sizeof h); h[2] = h[3] = 1;
    CK(cda_dyn_pick(h, 0, 0, 0) == 2 && cda_dyn_pick(h, 0, 0, 1) == 2 && cda_dyn_pick(h, 0, 1, 1) == 3);
    memset(h, 0, sizeof h); h[5] = 1; CK(cda_dyn_pick(h, 1, 1, 0) == 5);
    memset(h, 0, sizeof h); h[4] = h[5] = h[6] = h[7] = 1; CK(cda_dyn_pick(h, 1, 1, 1) == 7 && cda_dyn_pick(h, 1, 0, 1) == 5);
  }
  /* --- 3. гистерезис: Chase сразу, обратно — после hold кадров подряд без погони --- */
  {
    cda_dyn_ctl c = { 0, 0, 1000 };
    CK(cda_dyn_ctl_step(&c, 1, 100) == 1 && c.chase_on);
    CK(cda_dyn_ctl_step(&c, 0, 600) == 0 && c.chase_on);
    CK(cda_dyn_ctl_step(&c, 1, 10) == 0 && c.chase_on && c.calm44 == 0);   /* моргнул — счёт заново */
    CK(cda_dyn_ctl_step(&c, 0, 600) == 0 && cda_dyn_ctl_step(&c, 0, 300) == 0 && c.chase_on);
    CK(cda_dyn_ctl_step(&c, 0, 100) == 1 && !c.chase_on);
    CK(cda_dyn_ctl_step(&c, 0, 5000) == 0 && !c.chase_on);
  }
  /* --- 4. каталог: Track04.wav (обычная дорожка), «01. Miami At Day Drive.wav» в корне (не дорожка 1, уступает dynamic/),
         dynamic/: Майами — 4 файла по 0.5 с (синхронно), SF — по номеру: 05 (0.5 с) и 06 (2 с — не синхронно) --- */
  mkdir("cd_dyn", 0777); mkdir("cd_dyn/Dynamic", 0777);
  CK(wavc("cd_dyn/Track04.wav", 7000, 44100) == 0);
  CK(wavc("cd_dyn/01. Miami At Day Drive.wav", 9000, 44100) == 0);
  CK(wavc("cd_dyn/Dynamic/01. Miami At Day Drive.wav", 1000, 22050) == 0);
  CK(wavc("cd_dyn/Dynamic/02. Miami At Day Chase.wav", 2000, 22050) == 0);
  CK(wavc("cd_dyn/Dynamic/03. Miami At Night Drive.wav", 3000, 22050) == 0);
  CK(wavc("cd_dyn/Dynamic/04. Miami At Night Chase.wav", 4000, 22050) == 0);
  CK(wavc("cd_dyn/Dynamic/05 track.wav", 5000, 22050) == 0);
  CK(wavc("cd_dyn/Dynamic/06 track.wav", 6000, 88200) == 0);
  unsetenv("RE_MUSIC"); unsetenv("RE_MUSIC_STUB"); unsetenv("RE_CD_TRACKS"); unsetenv("RE_MUSIC_VOL"); unsetenv("RE_MUSIC_DYNAMIC"); unsetenv("RE_MUSIC_SYNC");
  setenv("RE_MUSIC_STUB_LEN", "2", 1);
  setenv("RE_MUSIC_FADE", "0.01", 1);          /* 441 кадр */
  setenv("RE_MUSIC_CHASE_HOLD", "0.1", 1);     /* 4410 кадров */
  plat_music_hint(0, 0);
  cda_reset("cd_dyn");
  {
    const char *p = NULL; int64_t fr = 0;
    CK(cda_dyn_source(0, &p, &fr) == CDA_SRC_WAV && strstr(p, "Dynamic/01. Miami") && fr == 22050);
    CK(cda_dyn_source(3, &p, &fr) == CDA_SRC_WAV && strstr(p, "04. Miami At Night Chase"));
    CK(cda_dyn_source(4, &p, &fr) == CDA_SRC_WAV && strstr(p, "05 track") && cda_dyn_source(5, &p, &fr) == CDA_SRC_WAV && fr == 88200);
    CK(cda_dyn_source(8, &p, &fr) == CDA_SRC_NONE && p == NULL);
    CK(cda_track_source(1, &p, &fr) == CDA_SRC_NONE);                     /* «01. Miami …» — не дорожка 1 */
    CK(cda_track_source(4, &p, &fr) == CDA_SRC_WAV && strstr(p, "Track04.wav"));
  }
  plat_cd_close(); P25_CdOpen = 0; P25_CdPlaying = 0;
  CK(P25_InitCDAudio() == 1 && P25_CdTracks == 10);
  Q00B87E90 = 1; P25_CDSetVolume(0xffff);
  {
    int city, night, ch, sync, tr; float gd, gc; int64_t pos, end; void *h; uint32_t wp; int32_t lp;
    /* Майами, день, без погони → Day Drive */
    plat_music_hint(0, 0); P25_PlayCDTrack(4);
    CK(P25_CdPlaying == 1 && cda_dyn_state(&city, &night, &ch, &gd, &gc, &sync) && city == 0 && night == 0 && !ch && sync == 1 && gd == 1.0f && gc == 0.0f);
    CK(fabsf(mixn(100, 0, 0) - lv(1000)) < 1e-5f);
    /* погоня → Chase сразу, кроссфейд 441 кадр (линейный, сумма громкостей 1) */
    {
      static float acc[2 * 1000];
      plat_music_hint(0, 1); memset(acc, 0, sizeof acc); cda_mix(acc, 1000);
      CK(cda_dyn_state(NULL, NULL, &ch, &gd, &gc, NULL) && ch == 1 && gc == 1.0f && gd == 0.0f);
      CK(acc[0] > lv(1000) && acc[0] < lv(1010));
      CK(fabsf(acc[2 * 220] - lv(1500)) < lv(10));                         /* середина кроссфейда */
      CK(fabsf(acc[2 * 999] - lv(2000)) < 1e-5f);
    }
    /* моргание признака: 2000 без погони, снова погоня, 3000 без — Chase держится */
    CK(fabsf(mixn(2000, 0, 0) - lv(2000)) < 1e-5f);
    mixn(10, 0, 1);
    CK(fabsf(mixn(3000, 0, 0) - lv(2000)) < 1e-5f && cda_dyn_state(NULL, NULL, &ch, NULL, NULL, NULL) && ch == 1);
    /* без погони дольше 0.1 с → Drive */
    CK(fabsf(mixn(3000, 0, 0) - lv(1000)) < 1e-5f && cda_dyn_state(NULL, NULL, &ch, NULL, NULL, NULL) && ch == 0);
    /* цикл: набор длиннее файла (0.5 с), уведомления нет, дорожка «играет» */
    mixn(30000, 0, 0);
    CK(cda_state(&tr, &pos, &end) && tr == 4 && plat_cd_take_notify(&h, &wp, &lp) == 0 && P25_CdPlaying == 1);
    /* громкость */
    P25_CDSetVolume(0x8000);
    CK(fabsf(mixn(10, 0, 0) - lv(1000) * (32768.0f / 65535.0f)) < 1e-5f);
    P25_CDSetVolume(0xffff);
    /* пауза (MCI_STOP) — тишина, продолжение (CDResume) — тот же набор */
    P25_CDStop();
    CK(P25_CdPlaying == 0 && mixn(100, 0, 0) == 0.0f);
    P25_CDResume();
    CK(P25_CdPlaying == 1 && fabsf(mixn(100, 0, 0) - lv(1000)) < 1e-5f);
    /* ночь (рассвет/закат миссии): смена — если держится 3 с, кроссфейд к Night Drive */
    CK(fabsf(mixn(44100, 1, 0) - lv(1000)) < 1e-5f && cda_dyn_state(NULL, &night, NULL, NULL, NULL, NULL) && night == 0);
    mixn(3 * 44100, 1, 0);
    CK(cda_dyn_state(NULL, &night, NULL, NULL, NULL, NULL) && night == 1);
    CK(fabsf(mixn(1000, 1, 0) - lv(3000)) < 1e-5f);
    CK(fabsf(mixn(1000, 1, 1) - lv(4000)) < 1e-5f);                        /* ночная погоня */
    /* повторный запрос дорожки (как после паузы): ночь и погоня сразу */
    plat_music_hint(1, 1); P25_PlayCDTrack(4);
    CK(cda_dyn_state(&city, &night, &ch, &gd, &gc, NULL) && night == 1 && ch == 1 && gc == 1.0f);
    CK(fabsf(mixn(100, 1, 1) - lv(4000)) < 1e-5f);
    /* SF по номерам: Drive 0.5 с, Chase 2 с — не синхронно: Chase с начала, кроссфейд равной мощности */
    plat_music_hint(0, 0); P25_PlayCDTrack(5);
    CK(cda_dyn_state(&city, &night, &ch, NULL, NULL, &sync) && city == 1 && night == 0 && sync == 0);
    CK(fabsf(mixn(500, 0, 0) - lv(5000)) < 1e-5f);
    CK(fabsf(mixn(1000, 0, 1) - lv(6000)) < 1e-5f);
    CK(fabsf(mixn(1000, 1, 1) - lv(6000)) < 1e-5f);                        /* ночи у SF нет — замена днём (смена не нужна) */
    /* LA — набора нет: обычная дорожка 6 (заглушка) */
    plat_music_hint(0, 0); P25_PlayCDTrack(6);
    CK(!cda_dyn_state(NULL, NULL, NULL, NULL, NULL, NULL) && cda_state(&tr, NULL, &end) && tr == 6 && end == 2 * 44100);
    /* меню (дорожка 2) — обычная, набор выключен */
    P25_PlayCDTrack(2); CK(!cda_dyn_state(NULL, NULL, NULL, NULL, NULL, NULL));
    /* RE_MUSIC_DYNAMIC=0 — дорожка 4 = Track04.wav */
    setenv("RE_MUSIC_DYNAMIC", "0", 1);
    P25_PlayCDTrack(4);
    CK(!cda_dyn_state(NULL, NULL, NULL, NULL, NULL, NULL) && fabsf(mixn(10, 0, 0) - lv(7000)) < 1e-5f);
    unsetenv("RE_MUSIC_DYNAMIC");
    P25_CDClose(); CK(!cda_dyn_state(NULL, NULL, NULL, NULL, NULL, NULL) && !cda_state(NULL, NULL, NULL));
  }
  /* --- 5. без dynamic/: набор по ключевым словам в корне (только NY Night Chase) — для любого состояния NY --- */
  remove("cd_dyn/Track04.wav"); remove("cd_dyn/01. Miami At Day Drive.wav");
  {
    const char *dn[] = { "01. Miami At Day Drive.wav", "02. Miami At Day Chase.wav", "03. Miami At Night Drive.wav", "04. Miami At Night Chase.wav", "05 track.wav", "06 track.wav" };
    char p[256]; for (int i = 0; i < 6; i++) { snprintf(p, sizeof p, "cd_dyn/Dynamic/%s", dn[i]); remove(p); }
    rmdir("cd_dyn/Dynamic");
  }
  CK(wavc("cd_dyn/16 - New York At Night Chase.wav", 8000, 4410) == 0);
  cda_reset("cd_dyn");
  { const char *p; int64_t fr; CK(cda_dyn_source(15, &p, &fr) == CDA_SRC_WAV && cda_track_source(16, &p, &fr) == CDA_SRC_NONE); }
  P25_CdOpen = 0; CK(P25_InitCDAudio() == 1);
  plat_music_hint(0, 0); P25_PlayCDTrack(7);
  CK(cda_dyn_state(NULL, NULL, NULL, NULL, NULL, NULL) && fabsf(mixn(10, 0, 0) - lv(8000)) < 1e-5f);
  P25_CDClose();
out:
  unsetenv("RE_MUSIC_STUB_LEN"); unsetenv("RE_MUSIC_FADE"); unsetenv("RE_MUSIC_CHASE_HOLD"); unsetenv("RE_MUSIC_DYNAMIC");
  if (P25_CdOpen) P25_CDClose();
  P25_CdOpen = 0; P25_CdPlaying = 0; P25_CdTrack = 0; P25_CdTracks = 0;
  Q00B87E90 = save_q;
  plat_music_hint(0, 0);
  {
    const char *dn[] = { "01. Miami At Day Drive.wav", "02. Miami At Day Chase.wav", "03. Miami At Night Drive.wav", "04. Miami At Night Chase.wav", "05 track.wav", "06 track.wav" };
    char p[256]; for (int i = 0; i < 6; i++) { snprintf(p, sizeof p, "cd_dyn/Dynamic/%s", dn[i]); remove(p); }
  }
  rmdir("cd_dyn/Dynamic");
  remove("cd_dyn/Track04.wav"); remove("cd_dyn/01. Miami At Day Drive.wav"); remove("cd_dyn/16 - New York At Night Chase.wav"); rmdir("cd_dyn");
  cda_reset(NULL);
  return rc;
}
