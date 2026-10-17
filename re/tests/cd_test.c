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
