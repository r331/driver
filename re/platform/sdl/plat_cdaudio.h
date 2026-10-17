/* v2.22: эмуляция CD-audio (MCI cdaudio) native-сборки — дорожки из файлов вместо привода. См. plat_cdaudio.c. */
#ifndef RE_PLAT_CDAUDIO_H
#define RE_PLAT_CDAUDIO_H
#include <stdint.h>

/* источник дорожки */
enum { CDA_SRC_NONE = 0, CDA_SRC_WAV, CDA_SRC_OGG, CDA_SRC_FLAC, CDA_SRC_MP3, CDA_SRC_CUE };

/* разобранный .cue: дорожки (номер на диске, тип, файл, начало INDEX 01 и длина в секторах по 2352 байта) */
#define CDA_CUE_MAX 99
typedef struct {
  int num;            /* номер дорожки на диске (TRACK NN) */
  int audio;          /* 1 — AUDIO, 0 — данные (MODE1/2352 …) */
  int file;           /* индекс файла в files[] */
  int64_t start;      /* INDEX 01 (если его нет — INDEX 00), секторы от начала файла */
  int64_t len;        /* секторы; заполняет cda_cue_resolve */
} cda_cue_track;
typedef struct {
  int ntracks, nfiles;
  cda_cue_track t[CDA_CUE_MAX];
  char files[CDA_CUE_MAX][256];  /* имя из FILE "…" */
  int ftype[CDA_CUE_MAX];        /* 0 BINARY (LE), 1 MOTOROLA (BE), 2 WAVE, −1 — не поддержан */
} cda_cue;

/* разбор текста .cue (без файловой системы): 0 — ок, >0 — номер строки с ошибкой, <0 — дорожка без INDEX */
int cda_cue_parse(const char *text, cda_cue *c);
/* длины дорожек: до следующей дорожки того же файла или до конца файла (байт PCM / 2352) */
void cda_cue_resolve(cda_cue *c, const int64_t *file_bytes);

/* каталог музыки: RE_MUSIC_DIR → music_dir из driver.cfg → ./Music (music, MUSIC) */
const char *cda_music_dir(void);
/* тесты: сбросить эмуляцию и пересканировать каталог (NULL — по правилам выше); выключает учётный режим plat_cd_stub_set */
void cda_reset(const char *dir);
/* что найдено для дорожки: CDA_SRC_*, путь (NULL у заглушки), длина в кадрах 44100 Гц */
int  cda_track_source(int track, const char **path, int64_t *frames44);
/* смешать CD-музыку в буфер float стерео (вызывается из dsm_mix под блокировкой устройства) */
void cda_mix(float *acc, int frames);
/* уведомление MM_MCINOTIFY (MCI_PLAY с MCI_NOTIFY дошёл до конца): 1 — есть (снимается), wp = MCI_NOTIFY_SUCCESSFUL (1), lp = id устройства */
int  plat_cd_take_notify(void **hwnd, uint32_t *wp, int32_t *lp);
/* состояние для тестов/лога: 1 — играет; дорожка, позиция и конец в кадрах 44100 Гц от начала дорожки */
int  cda_state(int *track, int64_t *pos44, int64_t *end44);
#endif
