/* v2.22: эмуляция CD-audio (MCI cdaudio, формат времени TMSF) для native-сборки.
   Игра (game/ported25.c: InitCDAudio 00524611, GetCDTOC 00524f97, PlayCDTrack 0052479e, CDStop 00524873, CDClose 00524763,
   CDResume 005248cd, CDSetVolume 00524917) зовёт только
   plat_cd_* / plat_aux_* (plat.h). Здесь вместо привода — файлы дорожек:
     каталог: RE_MUSIC_DIR → music_dir в driver.cfg → ./Music (music, MUSIC) в текущем каталоге (каталог данных игры);
     дорожка N: TrackNN.wav | trackNN.cdda.wav (cdparanoia) | «NN *.wav» (EAC), затем .flac, .ogg, .mp3 (dr_flac / stb_vorbis /
     dr_mp3 — vendored, public domain); иначе — первый по имени *.cue каталога (FILE BINARY/MOTOROLA/WAVE, TRACK NN AUDIO,
     INDEX 01: сырой PCM 44100 Гц стерео 16 бит, 2352 байта на сектор); иначе — «заглушка»: дорожка есть, длина
     RE_MUSIC_STUB_LEN с (60), тишина (RE_MUSIC_STUB=tone — тихий тон, свой у каждой дорожки: 220 Гц · 2^((N−2)/12)).
   RE_MUSIC=off — прежнее поведение (Open CD device failed, музыки нет).
   Устройство открывается всегда; дорожек max(10, наибольший найденный номер) (RE_CD_TRACKS — явно); позиция дорожки — TMSF
   T:0:0:0, длина — MSF (так их возвращает MCI cdaudio при формате TMSF). Конец игра считает P21_AddMsf(позиция, длина)
   (005250cb): байт дорожки складывается с минутами длины. Эмуляция узнаёт это значение и играет до конца дорожки N
   (иное «to» читается как TMSF внутри той же дорожки). Конец при MCI_NOTIFY (PlayCDTrack: MCI_PLAY|NOTIFY|FROM|TO) —
   MM_MCINOTIFY(MCI_NOTIFY_SUCCESSFUL) в оконную процедуру из цикла сообщений (plat_sys.c); P31_WndProc сбрасывает
   P25_CdPlaying, и кадр меню/игры снова зовёт PlayCDTrack — так в оригинале дорожка повторяется. MCI_STOP (CDStop) снимает
   ожидание уведомления и сохраняет позицию; MCI_PLAY без FROM (CDResume) — с этой позиции, без уведомления.
   Громкость — auxSetVolume устройства CD (aux 0): L/R 0..0xffff, линейно (RE_MUSIC_VOL — множитель 0..4).
   Смешивание — cda_mix() из dsm_mix (plat_dsmix.c) до мягкого ограничителя, 44100 Гц стерео. */
#include "../plat.h"
#include "plat_cdaudio.h"
#include "plat_gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wextra"
#endif
#define STB_VORBIS_NO_PUSHDATA_API
#include "../../third_party/stb_vorbis.c"
#undef L
#undef C
#undef R
#define DR_FLAC_IMPLEMENTATION
#define DR_FLAC_NO_OGG
#include "../../third_party/dr_flac.h"
#define DR_MP3_IMPLEMENTATION
#include "../../third_party/dr_mp3.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

void plat_snd_lockdev(int on);   /* plat_snd.c */
#define OUT_RATE 44100
#define FR_PER_SECTOR 588        /* 2352 / 4 */
#define MAXT 100

/* ===================== разбор .cue ===================== */
static int ieqn(const char *a, const char *b, size_t n) { for (size_t i = 0; i < n; i++) { if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return 0; if (!a[i]) return 1; } return 1; }
static const char *skipws(const char *p) { while (*p == ' ' || *p == '\t') p++; return p; }
static int msf_sectors(const char *p, int64_t *out) {
  int m, s, f;
  if (sscanf(p, "%d:%d:%d", &m, &s, &f) != 3 || m < 0 || s < 0 || s > 59 || f < 0 || f > 74) return -1;
  *out = ((int64_t)m * 60 + s) * 75 + f; return 0;
}
int cda_cue_parse(const char *text, cda_cue *c) {
  memset(c, 0, sizeof *c);
  int line = 0, cur = -1, curfile = -1;
  const char *p = text;
  if ((unsigned char)p[0] == 0xef && (unsigned char)p[1] == 0xbb && (unsigned char)p[2] == 0xbf) p += 3;   /* BOM */
  while (*p) {
    const char *e = p; while (*e && *e != '\n' && *e != '\r') e++;
    char b[512]; size_t n = (size_t)(e - p); if (n >= sizeof b) n = sizeof b - 1;
    memcpy(b, p, n); b[n] = 0; line++;
    p = e; if (*p == '\r') p++; if (*p == '\n') p++;
    const char *q = skipws(b);
    if (!*q) continue;
    if (ieqn(q, "FILE ", 5) || ieqn(q, "FILE\t", 5)) {
      q = skipws(q + 4);
      char name[256]; const char *r;
      if (*q == '"') { const char *z = strchr(q + 1, '"'); if (!z) return line; size_t k = (size_t)(z - q - 1); if (k >= sizeof name) return line; memcpy(name, q + 1, k); name[k] = 0; r = z + 1; }
      else { size_t k = 0; while (q[k] && q[k] != ' ' && q[k] != '\t') k++; if (k >= sizeof name) return line; memcpy(name, q, k); name[k] = 0; r = q + k; }
      if (c->nfiles >= CDA_CUE_MAX) return line;
      r = skipws(r);
      curfile = c->nfiles++;
      memcpy(c->files[curfile], name, strlen(name) + 1);
      c->ftype[curfile] = ieqn(r, "BINARY", 6) ? 0 : ieqn(r, "MOTOROLA", 8) ? 1 : ieqn(r, "WAVE", 4) ? 2 : -1;
    } else if (ieqn(q, "TRACK ", 6) || ieqn(q, "TRACK\t", 6)) {
      int num; char type[32] = "";
      if (curfile < 0 || sscanf(q + 6, "%d %31s", &num, type) < 2 || num < 1 || num > 99 || c->ntracks >= CDA_CUE_MAX) return line;
      cur = c->ntracks++;
      c->t[cur].num = num; c->t[cur].audio = ieqn(type, "AUDIO", 6); c->t[cur].file = curfile; c->t[cur].start = -1; c->t[cur].len = -1;
    } else if (ieqn(q, "INDEX ", 6) || ieqn(q, "INDEX\t", 6)) {
      int idx; char tm[32];
      if (cur < 0 || sscanf(q + 6, "%d %31s", &idx, tm) != 2) return line;
      int64_t s; if (msf_sectors(tm, &s)) return line;
      if (idx == 1) c->t[cur].start = s;
      else if (idx == 0 && c->t[cur].start < 0) c->t[cur].start = -2 - s;   /* INDEX 00 — пока нет INDEX 01 */
    }
    /* REM, PREGAP, POSTGAP, FLAGS, ISRC, TITLE, PERFORMER, CATALOG, CDTEXTFILE, SONGWRITER — на данные в файле не влияют */
  }
  for (int i = 0; i < c->ntracks; i++) {
    if (c->t[i].start <= -2) c->t[i].start = -2 - c->t[i].start;
    if (c->t[i].start < 0) return -1 - i;
  }
  return 0;
}
void cda_cue_resolve(cda_cue *c, const int64_t *file_bytes) {
  for (int i = 0; i < c->ntracks; i++) {
    cda_cue_track *t = &c->t[i];
    int64_t end = -1;
    for (int j = i + 1; j < c->ntracks; j++) if (c->t[j].file == t->file) { end = c->t[j].start; break; }
    if (end < 0) end = file_bytes ? file_bytes[t->file] / 2352 : t->start;
    t->len = end > t->start ? end - t->start : 0;
  }
}

/* ===================== поиск файлов ===================== */
typedef struct {
  int kind; char path[1024];
  int64_t off;          /* CUE: байт начала дорожки в файле */
  int be;               /* CUE MOTOROLA */
  int64_t frames;       /* в частоте источника */
  int rate, ch;
  int64_t frames44;     /* длина в кадрах 44100 Гц */
} trk_t;
static trk_t g_trk[MAXT];
static int g_scanned, g_ntracks, g_maxfound;
static char g_dir[1024], g_dir_why[64], g_cue[1024];
static int g_test = 0;                 /* 1 — учётный режим selftest test_p25 (plat_cd_stub_set) */
static char g_dir_override[1024];      /* cda_reset(dir) — тесты */

static const char *envs(const char *n) { const char *v = getenv(n); return v && *v ? v : NULL; }
static int isdir(const char *p) { struct stat st; return stat(p, &st) == 0 && S_ISDIR(st.st_mode); }
static int64_t fsize(const char *p) { struct stat st; return stat(p, &st) == 0 ? (int64_t)st.st_size : -1; }
const char *cda_music_dir(void) {
  if (g_dir_override[0]) { snprintf(g_dir, sizeof g_dir, "%s", g_dir_override); snprintf(g_dir_why, sizeof g_dir_why, "тест"); return g_dir; }
  const char *e = envs("RE_MUSIC_DIR");
  if (e) { snprintf(g_dir, sizeof g_dir, "%s", e); snprintf(g_dir_why, sizeof g_dir_why, "RE_MUSIC_DIR"); return g_dir; }
  const char *c = re_gfx()->music_dir;
  if (c && *c) { snprintf(g_dir, sizeof g_dir, "%s", c); snprintf(g_dir_why, sizeof g_dir_why, "driver.cfg music_dir"); return g_dir; }
  static const char *def[] = { "Music", "music", "MUSIC" };
  for (int i = 0; i < 3; i++) if (isdir(def[i])) { snprintf(g_dir, sizeof g_dir, "%s", def[i]); snprintf(g_dir_why, sizeof g_dir_why, "./%s", def[i]); return g_dir; }
  snprintf(g_dir, sizeof g_dir, "Music"); snprintf(g_dir_why, sizeof g_dir_why, "каталога нет");
  return g_dir;
}
static void lower(char *d, const char *s, size_t n) { size_t i = 0; for (; s[i] && i + 1 < n; i++) d[i] = (char)tolower((unsigned char)s[i]); d[i] = 0; }
static int ends(const char *s, const char *suf) { size_t a = strlen(s), b = strlen(suf); return a >= b && !strcmp(s + a - b, suf); }
/* номер дорожки по имени файла (нижний регистр): trackNN.*, trackNN.cdda.wav, NN.*, «NN - название.*», NN_*; −1 — нет */
static int name_track(const char *lo) {
  const char *p = lo;
  if (!strncmp(p, "track", 5)) { p += 5; if (*p == ' ' || *p == '_' || *p == '-') p++; }
  if (!isdigit((unsigned char)p[0]) || !isdigit((unsigned char)p[1]) || isdigit((unsigned char)p[2])) return -1;
  int n = (p[0] - '0') * 10 + (p[1] - '0');
  char c = p[2];
  if (c != '.' && c != ' ' && c != '-' && c != '_') return -1;
  return n >= 1 && n <= 99 ? n : -1;
}
static int ext_kind(const char *lo) {
  if (ends(lo, ".wav")) return CDA_SRC_WAV;
  if (ends(lo, ".flac")) return CDA_SRC_FLAC;
  if (ends(lo, ".ogg")) return CDA_SRC_OGG;
  if (ends(lo, ".mp3")) return CDA_SRC_MP3;
  return 0;
}
static int kind_rank(int k) { return k == CDA_SRC_WAV ? 0 : k == CDA_SRC_FLAC ? 1 : k == CDA_SRC_OGG ? 2 : k == CDA_SRC_MP3 ? 3 : 9; }

static int64_t fsize_f(FILE *f) { long c = ftell(f); if (fseek(f, 0, SEEK_END)) return -1; long e = ftell(f); fseek(f, c, SEEK_SET); return (int64_t)e; }
static uint32_t rd32(const uint8_t *b) { return (uint32_t)b[0] | (uint32_t)b[1] << 8 | (uint32_t)b[2] << 16 | (uint32_t)b[3] << 24; }
/* WAV: PCM 8/16/24 бит (и EXTENSIBLE с PCM), 1–2 канала → смещение и размер данных */
static int wav_probe(FILE *f, int *rate, int *ch, int *bits, int64_t *off, int64_t *bytes) {
  uint8_t h[12]; if (fread(h, 1, 12, f) != 12 || memcmp(h, "RIFF", 4) || memcmp(h + 8, "WAVE", 4)) return -1;
  int got_fmt = 0;
  for (;;) {
    uint8_t ck[8]; if (fread(ck, 1, 8, f) != 8) return -1;
    uint32_t sz = rd32(ck + 4);
    if (!memcmp(ck, "fmt ", 4)) {
      uint8_t fm[40] = { 0 }; size_t k = sz < sizeof fm ? sz : sizeof fm;
      if (k < 16 || fread(fm, 1, k, f) != k) return -1;
      if (fseek(f, (long)(sz - k + (sz & 1)), SEEK_CUR)) return -1;
      int tag = fm[0] | fm[1] << 8; *ch = fm[2] | fm[3] << 8; *rate = (int)rd32(fm + 4); *bits = fm[14] | fm[15] << 8;
      if (tag == 0xfffe && k >= 26) tag = fm[24] | fm[25] << 8;
      if (tag != 1 || *ch < 1 || *ch > 2 || (*bits != 8 && *bits != 16 && *bits != 24) || *rate < 8000 || *rate > 192000) return -2;
      got_fmt = 1;
    } else if (!memcmp(ck, "data", 4)) {
      if (!got_fmt) return -1;
      *off = ftell(f); *bytes = sz;
      int64_t real = fsize_f(f) - *off; if (real >= 0 && real < *bytes) *bytes = real;
      return 0;
    } else if (fseek(f, (long)(sz + (sz & 1)), SEEK_CUR)) return -1;
  }
}

/* ===================== источник PCM (поток) ===================== */
enum { SRC_BUF = 1024 };
typedef struct {
  int kind, track; FILE *f; int64_t off, frames, pos; int rate, ch, bits, be;
  stb_vorbis *v; drflac *fl; drmp3 *mp3;
  int tone; double phase, dphase;
  float buf[2 * SRC_BUF]; int bn, bi;
} src_t;
static double g_stub_len = 60.0;
static void src_close(src_t *s) {
  if (s->f) fclose(s->f);
  if (s->v) stb_vorbis_close(s->v);
  if (s->fl) drflac_close(s->fl);
  if (s->mp3) { drmp3_uninit(s->mp3); free(s->mp3); }
  memset(s, 0, sizeof *s);
}
/* открыть источник дорожки; 0 — ок. kind NONE — заглушка (тишина/тон) */
static int src_open(src_t *s, const trk_t *t, int track) {
  memset(s, 0, sizeof *s); s->kind = t->kind; s->track = track; s->ch = 2; s->rate = OUT_RATE;
  switch (t->kind) {
  case CDA_SRC_WAV: {
    s->f = fopen(t->path, "rb"); if (!s->f) return -1;
    int64_t bytes = 0; if (wav_probe(s->f, &s->rate, &s->ch, &s->bits, &s->off, &bytes)) { src_close(s); return -1; }
    s->frames = bytes / (s->ch * (s->bits / 8));
    break; }
  case CDA_SRC_CUE:
    s->f = fopen(t->path, "rb"); if (!s->f) return -1;
    s->off = t->off; s->bits = 16; s->be = t->be; s->frames = t->frames;
    break;
  case CDA_SRC_OGG: {
    int err = 0; s->v = stb_vorbis_open_filename(t->path, &err, NULL); if (!s->v) return -1;
    stb_vorbis_info in = stb_vorbis_get_info(s->v); s->rate = (int)in.sample_rate; s->ch = in.channels > 2 ? 2 : in.channels;
    s->frames = (int64_t)stb_vorbis_stream_length_in_samples(s->v);
    break; }
  case CDA_SRC_FLAC:
    s->fl = drflac_open_file(t->path, NULL); if (!s->fl) return -1;
    s->rate = (int)s->fl->sampleRate; s->ch = s->fl->channels; s->frames = (int64_t)s->fl->totalPCMFrameCount;
    break;
  case CDA_SRC_MP3:
    s->mp3 = (drmp3 *)calloc(1, sizeof *s->mp3); if (!s->mp3) return -1;
    if (!drmp3_init_file(s->mp3, t->path, NULL)) { free(s->mp3); s->mp3 = NULL; return -1; }
    s->rate = (int)s->mp3->sampleRate; s->ch = (int)s->mp3->channels;
    s->frames = t->frames > 0 ? t->frames : (int64_t)drmp3_get_pcm_frame_count(s->mp3);
    break;
  default: {   /* заглушка */
    const char *m = envs("RE_MUSIC_STUB");
    s->tone = m && !strcmp(m, "tone");
    s->frames = t->frames44 > 0 ? t->frames44 : (int64_t)(g_stub_len * OUT_RATE);
    s->dphase = 2.0 * 3.14159265358979 * 220.0 * pow(2.0, (track - 2) / 12.0) / OUT_RATE;
    break; }
  }
  if (s->rate <= 0 || s->ch < 1) { src_close(s); return -1; }
  return 0;
}
static int src_seek(src_t *s, int64_t fr) {
  if (fr < 0) fr = 0;
  if (fr > s->frames) fr = s->frames;
  s->bn = s->bi = 0; s->pos = fr;
  switch (s->kind) {
  case CDA_SRC_WAV: case CDA_SRC_CUE: return fseek(s->f, (long)(s->off + fr * s->ch * (s->bits / 8)), SEEK_SET);
  case CDA_SRC_OGG: return stb_vorbis_seek(s->v, (unsigned)fr) ? 0 : -1;
  case CDA_SRC_FLAC: return drflac_seek_to_pcm_frame(s->fl, (drflac_uint64)fr) ? 0 : -1;
  case CDA_SRC_MP3: return drmp3_seek_to_pcm_frame(s->mp3, (drmp3_uint64)fr) ? 0 : -1;
  default: s->phase = fmod(s->dphase * (double)fr, 2.0 * 3.14159265358979); return 0;
  }
}
/* следующий кусок в buf (стерео float); число кадров, 0 — конец */
static int src_fill(src_t *s) {
  int want = SRC_BUF; int64_t left = s->frames - s->pos;
  if (left <= 0) return s->bn = s->bi = 0;
  if (want > left) want = (int)left;
  int got = 0, ch = s->ch;
  float tmp[8 * SRC_BUF];
  switch (s->kind) {
  case CDA_SRC_WAV: case CDA_SRC_CUE: {
    int bps = s->bits / 8, fb = s->ch * bps; uint8_t raw[2 * 3 * SRC_BUF];
    got = (int)(fread(raw, 1, (size_t)want * fb, s->f) / (size_t)fb);
    for (int i = 0; i < got * s->ch; i++) {
      const uint8_t *b = raw + i * bps; float v;
      if (bps == 1) v = (b[0] - 128) / 128.0f;
      else if (bps == 2) v = (int16_t)(s->be ? (b[0] << 8 | b[1]) : (b[1] << 8 | b[0])) / 32768.0f;
      else v = (float)((int32_t)((uint32_t)b[0] << 8 | (uint32_t)b[1] << 16 | (uint32_t)b[2] << 24) >> 8) / 8388608.0f;
      tmp[i] = v;
    }
    break; }
  case CDA_SRC_OGG: got = stb_vorbis_get_samples_float_interleaved(s->v, ch, tmp, want * ch); break;
  case CDA_SRC_FLAC: got = (int)drflac_read_pcm_frames_f32(s->fl, (drflac_uint64)want, tmp); break;   /* до 8 каналов */
  case CDA_SRC_MP3: got = (int)drmp3_read_pcm_frames_f32(s->mp3, (drmp3_uint64)want, tmp); break;
  default:
    for (int i = 0; i < want; i++) {
      float v = s->tone ? 0.05f * (float)sin(s->phase) : 0.0f;
      s->phase += s->dphase; if (s->phase > 6.283185307179586) s->phase -= 6.283185307179586;
      tmp[2 * i] = tmp[2 * i + 1] = v;
    }
    got = want; ch = 2; break;
  }
  if (got <= 0) { s->pos = s->frames; return s->bn = s->bi = 0; }
  for (int i = 0; i < got; i++) {
    s->buf[2 * i] = tmp[i * ch];
    s->buf[2 * i + 1] = ch > 1 ? tmp[i * ch + 1] : tmp[i * ch];
  }
  s->pos += got; s->bn = got; s->bi = 0;
  return got;
}
static void src_next(src_t *s, float *o) {
  if (s->bi >= s->bn && src_fill(s) == 0) { o[0] = o[1] = 0; return; }
  o[0] = s->buf[2 * s->bi]; o[1] = s->buf[2 * s->bi + 1]; s->bi++;
}

/* ===================== каталог → таблица дорожек ===================== */
static void join(char *out, size_t n, const char *a, const char *b) {   /* a/b без предупреждений -Wformat-truncation */
  size_t la = strlen(a), lb = strlen(b);
  if (la + 1 + lb + 1 > n) { out[0] = 0; return; }
  memcpy(out, a, la); out[la] = '/'; memcpy(out + la + 1, b, lb + 1);
}
static int find_ci(const char *dir, const char *name, char *out, size_t n) {
  char want[256]; lower(want, name, sizeof want);
  for (char *q = want; *q; q++) if (*q == '\\') *q = '/';
  const char *base = strrchr(want, '/'); base = base ? base + 1 : want;   /* путь в FILE — берётся имя файла */
  DIR *d = opendir(dir); if (!d) return -1;
  struct dirent *e; int ok = -1;
  while ((e = readdir(d))) { char lo[256]; lower(lo, e->d_name, sizeof lo); if (!strcmp(lo, base)) { join(out, n, dir, e->d_name); ok = out[0] ? 0 : -1; break; } }
  closedir(d); return ok;
}
static uint32_t msf_of(int64_t frames44) {
  int64_t cf = (frames44 + FR_PER_SECTOR - 1) / FR_PER_SECTOR;
  int64_t m = cf / (75 * 60), s = (cf / 75) % 60, f = cf % 75;
  if (m > 255) { m = 255; s = 59; f = 74; }
  return (uint32_t)m | (uint32_t)s << 8 | (uint32_t)f << 16;
}
static uint32_t add_msf(uint32_t a, uint32_t b) {   /* = P21_AddMsf (005250cb) — как игра считает конец дорожки */
  int32_t m = (int32_t)(a & 0xff) + (int32_t)(b & 0xff);
  int32_t s = (int32_t)(a & 0xffff) / 256 + (int32_t)(b & 0xffff) / 256;
  int32_t f = (int32_t)((a >> 16) & 0xff) + (int32_t)((b >> 16) & 0xff);
  if (f > 0x4a) { s++; f -= 0x4b; }
  if (s > 0x3b) { m++; s -= 0x3c; }
  return (uint32_t)(m & 0xff) | ((uint32_t)(s & 0xffff) << 8) | ((uint32_t)(f & 0xff) << 16);
}
static const char *kname(int k) { static const char *n[] = { "заглушка", "wav", "ogg", "flac", "mp3", "cue" }; return k >= 0 && k <= 5 ? n[k] : "?"; }
static void scan(void) {
  memset(g_trk, 0, sizeof g_trk); g_maxfound = 0; g_cue[0] = 0;
  const char *sl = envs("RE_MUSIC_STUB_LEN"); g_stub_len = sl ? atof(sl) : 60.0; if (!(g_stub_len >= 1.0)) g_stub_len = 1.0; if (g_stub_len > 3600) g_stub_len = 3600;
  const char *dir = cda_music_dir();
  DIR *d = opendir(dir);
  if (d) {
    struct dirent *e;
    while ((e = readdir(d))) {
      char lo[256]; lower(lo, e->d_name, sizeof lo);
      if (ends(lo, ".cue")) { char p[1024]; join(p, sizeof p, dir, e->d_name); if (!g_cue[0] || strcmp(p, g_cue) < 0) snprintf(g_cue, sizeof g_cue, "%s", p); continue; }
      int n = name_track(lo), k = ext_kind(lo);
      if (n < 1 || !k) continue;
      trk_t *t = &g_trk[n];
      if (t->kind && kind_rank(t->kind) <= kind_rank(k)) continue;
      join(t->path, sizeof t->path, dir, e->d_name); if (t->path[0]) t->kind = k;
    }
    closedir(d);
  }
  for (int n = 1; n < MAXT; n++) {   /* длины файлов дорожек */
    trk_t *t = &g_trk[n]; if (!t->kind) continue;
    src_t s; if (src_open(&s, t, n) || s.frames <= 0) { fprintf(stderr, "[cd] %s: не читается (%s) — пропущен\n", t->path, kname(t->kind)); if (!src_open(&s, t, n)) src_close(&s); t->kind = 0; continue; }
    t->frames = s.frames; t->rate = s.rate; t->ch = s.ch; src_close(&s);
    t->frames44 = (int64_t)((double)t->frames * OUT_RATE / t->rate);
  }
  if (g_cue[0]) {   /* .cue + bin */
    FILE *f = fopen(g_cue, "rb"); char *txt = NULL; long sz = 0;
    if (f) { fseek(f, 0, SEEK_END); sz = ftell(f); fseek(f, 0, SEEK_SET); txt = (char *)malloc((size_t)sz + 1); if (txt) { sz = (long)fread(txt, 1, (size_t)sz, f); txt[sz] = 0; } fclose(f); }
    static cda_cue c;
    int r = txt ? cda_cue_parse(txt, &c) : -1; free(txt);
    if (r) fprintf(stderr, "[cd] %s: ошибка разбора (%d) — не используется\n", g_cue, r);
    else {
      char cdir[1024]; snprintf(cdir, sizeof cdir, "%s", g_cue); char *sl2 = strrchr(cdir, '/'); if (sl2) *sl2 = 0; else snprintf(cdir, sizeof cdir, ".");
      static char fpath[CDA_CUE_MAX][1024]; int64_t fbytes[CDA_CUE_MAX], foff[CDA_CUE_MAX];
      for (int i = 0; i < c.nfiles; i++) {
        fbytes[i] = -1; foff[i] = 0;
        if (find_ci(cdir, c.files[i], fpath[i], sizeof fpath[i])) { fprintf(stderr, "[cd] %s: нет файла '%s'\n", g_cue, c.files[i]); continue; }
        if (c.ftype[i] == 2) {
          FILE *w = fopen(fpath[i], "rb"); int rate = 0, ch = 0, bits = 0; int64_t off = 0, bytes = 0;
          if (w && !wav_probe(w, &rate, &ch, &bits, &off, &bytes) && rate == OUT_RATE && ch == 2 && bits == 16) { fbytes[i] = bytes; foff[i] = off; }
          else fprintf(stderr, "[cd] %s: '%s' — WAVE не 44100 Гц/стерео/16 бит\n", g_cue, c.files[i]);
          if (w) fclose(w);
        } else if (c.ftype[i] >= 0) fbytes[i] = fsize(fpath[i]);
        else fprintf(stderr, "[cd] %s: тип файла '%s' не поддержан (нужен BINARY/MOTOROLA/WAVE)\n", g_cue, c.files[i]);
      }
      cda_cue_resolve(&c, fbytes);
      for (int i = 0; i < c.ntracks; i++) {
        cda_cue_track *ct = &c.t[i]; trk_t *t = &g_trk[ct->num];
        if (!ct->audio || fbytes[ct->file] < 0 || ct->len <= 0) continue;
        if (t->kind) continue;   /* отдельный файл дорожки важнее */
        t->kind = CDA_SRC_CUE; snprintf(t->path, sizeof t->path, "%s", fpath[ct->file]);
        t->off = foff[ct->file] + ct->start * 2352; t->be = c.ftype[ct->file] == 1;
        t->frames = ct->len * FR_PER_SECTOR; t->rate = OUT_RATE; t->ch = 2; t->frames44 = t->frames;
      }
    }
  }
  for (int n = 1; n < MAXT; n++) if (g_trk[n].kind && n > g_maxfound) g_maxfound = n;
  const char *nt = envs("RE_CD_TRACKS");
  g_ntracks = nt ? atoi(nt) : (g_maxfound > 10 ? g_maxfound : 10);
  if (g_ntracks < 1) g_ntracks = 1;
  if (g_ntracks > 99) g_ntracks = 99;
  for (int n = 1; n < MAXT; n++) if (!g_trk[n].kind) { g_trk[n].frames44 = g_trk[n].frames = (int64_t)(g_stub_len * OUT_RATE); g_trk[n].rate = OUT_RATE; g_trk[n].ch = 2; }
  g_scanned = 1;
  char sum[1024]; int o = 0;
  for (int n = 2; n <= g_ntracks && o < (int)sizeof sum - 32; n++)
    o += snprintf(sum + o, sizeof sum - (size_t)o, " %d=%s", n, kname(g_trk[n].kind));
  const char *m = envs("RE_MUSIC_STUB");
  fprintf(stderr, "[cd] эмуляция CD-audio: каталог '%s' (%s)%s%s, дорожек %d:%s; заглушка — %s, %.0f с\n", dir, g_dir_why,
          g_cue[0] ? ", cue " : "", g_cue[0] ? g_cue : "", g_ntracks, sum, m && !strcmp(m, "tone") ? "тон" : "тишина", g_stub_len);
}
int cda_track_source(int track, const char **path, int64_t *frames44) {
  if (!g_scanned) scan();
  if (track < 1 || track >= MAXT) return -1;
  if (path) *path = g_trk[track].kind ? g_trk[track].path : NULL;
  if (frames44) *frames44 = g_trk[track].frames44;
  return g_trk[track].kind;
}

/* ===================== устройство (состояние воспроизведения — под блокировкой звука) ===================== */
static struct {
  int on, track; src_t s; int64_t pos44, end44; float f0[2], f1[2]; double frac, step; int notify; void *hwnd;
} g_p;
static int g_open, g_npend; static void *g_nhwnd;
static uint32_t g_cdvol = 0xffffffffu;
/* учётный режим selftest (test_p25): прежняя заглушка v0.72 */
static int g_cdn, g_cdaux = -1, g_tplay; static uint32_t g_cdfrom, g_cdto;

void cda_reset(const char *dir) {
  plat_snd_lockdev(1); src_t old = g_p.s; memset(&g_p, 0, sizeof g_p); g_npend = 0; plat_snd_lockdev(0);
  src_close(&old);
  g_test = 0; g_open = 0; g_cdvol = 0xffffffffu;
  snprintf(g_dir_override, sizeof g_dir_override, "%s", dir ? dir : "");
  scan();
}
int cda_state(int *track, int64_t *pos44, int64_t *end44) {
  plat_snd_lockdev(1);
  int on = g_p.on; if (track) *track = g_p.track; if (pos44) *pos44 = g_p.pos44; if (end44) *end44 = g_p.end44;
  plat_snd_lockdev(0);
  return on;
}
void cda_mix(float *acc, int frames) {
  if (!g_p.on) return;
  double vm = 1.0; const char *e = getenv("RE_MUSIC_VOL"); if (e && *e) { vm = atof(e); if (!(vm >= 0)) vm = 0; if (vm > 4) vm = 4; }
  float gl = (float)((g_cdvol & 0xffff) / 65535.0 * vm), gr = (float)((g_cdvol >> 16) / 65535.0 * vm);
  for (int i = 0; i < frames; i++) {
    if (g_p.pos44 >= g_p.end44) {
      g_p.on = 0;
      if (g_p.notify) { g_npend = 1; g_nhwnd = g_p.hwnd; g_p.notify = 0; }
      break;
    }
    float fr = (float)g_p.frac;
    acc[2 * i] += (g_p.f0[0] * (1 - fr) + g_p.f1[0] * fr) * gl;
    acc[2 * i + 1] += (g_p.f0[1] * (1 - fr) + g_p.f1[1] * fr) * gr;
    g_p.frac += g_p.step;
    while (g_p.frac >= 1.0) { g_p.f0[0] = g_p.f1[0]; g_p.f0[1] = g_p.f1[1]; src_next(&g_p.s, g_p.f1); g_p.frac -= 1.0; }
    g_p.pos44++;
  }
}
int plat_cd_take_notify(void **hwnd, uint32_t *wp, int32_t *lp) {
  if (!g_npend) return 0;
  plat_snd_lockdev(1);
  int n = g_npend; g_npend = 0; void *h = g_nhwnd;
  plat_snd_lockdev(0);
  if (!n) return 0;
  if (hwnd) *hwnd = h;
  if (wp) *wp = 1;        /* MCI_NOTIFY_SUCCESSFUL */
  if (lp) *lp = 1;        /* id устройства MCI */
  fprintf(stderr, "[cd] дорожка %d закончилась → MM_MCINOTIFY(SUCCESSFUL)\n", g_p.track);
  return 1;
}

void plat_cd_stub_set(int n, int aux) { g_test = 1; g_cdn = n; g_cdaux = aux; }
int plat_cd_stub_state(uint32_t *f, uint32_t *t, uint32_t *v) {
  *f = g_cdfrom; *t = g_cdto; *v = g_cdvol;
  return g_test ? g_tplay : g_p.on;
}
int plat_cd_open(void *hwnd) {
  (void)hwnd;
  if (g_test) { if (g_cdn <= 0) return 0; g_open = 1; return 1; }
  const char *m = envs("RE_MUSIC");
  if (m && (!strcmp(m, "off") || !strcmp(m, "0"))) return 0;
  if (!g_scanned) scan();
  g_open = 1;
  return 1;
}
static void stop_play(void) {
  plat_snd_lockdev(1); src_t old = g_p.s; memset(&g_p.s, 0, sizeof g_p.s); g_p.on = 0; g_p.notify = 0; plat_snd_lockdev(0);
  src_close(&old);
}
void plat_cd_close(void) {
  if (g_test) { g_open = 0; g_tplay = 0; return; }
  if (g_open || g_p.on) stop_play();
  g_open = 0; g_p.track = 0;
}
int plat_cd_track_count(void) {
  if (g_test) return g_open ? g_cdn : -1;
  return g_open ? g_ntracks : -1;
}
int plat_cd_track_info(int t, uint32_t *pos, uint32_t *len) {
  if (g_test) {
    if (!g_open || t < 1 || t > g_cdn) return 1;
    *pos = (uint32_t)t | (uint32_t)(t * 2) << 8;     /* T, M */
    *len = 3u | 30u << 8;                            /* M=3, S=30 */
    return 0;
  }
  if (!g_open || t < 1 || t > g_ntracks) return 1;
  *pos = (uint32_t)t;                 /* TMSF T:00:00:00 — начало дорожки */
  *len = msf_of(g_trk[t].frames44);   /* MSF */
  return 0;
}
/* конец воспроизведения (кадры 44100 Гц от начала дорожки) по значению MCI_TO */
static int64_t end_of(int track, uint32_t to) {
  int64_t len = g_trk[track].frames44;
  if (to == add_msf((uint32_t)track, msf_of(len))) return len;   /* так считает PlayCDTrack — до конца дорожки */
  if ((int)(to & 0xff) == track) {
    int64_t e = ((int64_t)((to >> 8) & 0xff) * 60 * 75 + (int64_t)((to >> 16) & 0xff) * 75 + (int64_t)(to >> 24)) * FR_PER_SECTOR;
    return e < len ? e : len;
  }
  static int warned;
  if (!warned) { warned = 1; fprintf(stderr, "[cd] MCI_TO %08x вне дорожки %d: переход через границу дорожек не эмулируется — до конца дорожки\n", (unsigned)to, track); }
  return len;
}
static int start_at(void *hwnd, int track, int64_t at44, int64_t end44, int notify, const char *why) {
  src_t ns;
  if (src_open(&ns, &g_trk[track], track)) {
    fprintf(stderr, "[cd] дорожка %d: '%s' не открылась — заглушка\n", track, g_trk[track].path);
    trk_t stub = g_trk[track]; stub.kind = 0; src_open(&ns, &stub, track);
  }
  src_seek(&ns, (int64_t)((double)at44 * ns.rate / OUT_RATE));
  float f0[2], f1[2]; src_next(&ns, f0); src_next(&ns, f1);
  plat_snd_lockdev(1);
  src_t old = g_p.s;
  g_p.s = ns; g_p.track = track; g_p.pos44 = at44; g_p.end44 = end44; g_p.frac = 0; g_p.step = (double)ns.rate / OUT_RATE;
  memcpy(g_p.f0, f0, sizeof f0); memcpy(g_p.f1, f1, sizeof f1); g_p.notify = notify; g_p.hwnd = hwnd; g_p.on = at44 < end44;
  if (!g_p.on && notify) { g_npend = 1; g_nhwnd = hwnd; g_p.notify = 0; }
  plat_snd_lockdev(0);
  src_close(&old);
  int s0 = (int)(at44 / OUT_RATE), s1 = (int)(end44 / OUT_RATE);
  fprintf(stderr, "[cd] %s: дорожка %d (%s%s%s) %d:%02d → %d:%02d%s\n", why, track, kname(g_trk[track].kind),
          g_trk[track].kind ? " " : "", g_trk[track].kind ? g_trk[track].path : "", s0 / 60, s0 % 60, s1 / 60, s1 % 60, notify ? ", с уведомлением" : "");
  return 1;
}
int plat_cd_play_range(void *hwnd, uint32_t from, uint32_t to) {
  if (g_test) { if (!g_open) return 0; g_cdfrom = from; g_cdto = to; g_tplay = 1; return 1; }
  if (!g_open) return 0;
  int track = (int)(from & 0xff);
  if (track < 1 || track > g_ntracks) return 0;   /* MCIERR_OUTOFRANGE */
  g_cdfrom = from; g_cdto = to;
  int64_t at = ((int64_t)((from >> 8) & 0xff) * 60 * 75 + (int64_t)((from >> 16) & 0xff) * 75 + (int64_t)(from >> 24)) * FR_PER_SECTOR;
  int64_t end = end_of(track, to);
  if (at > end) at = end;
  return start_at(hwnd, track, at, end, 1, "MCI_PLAY");
}
int plat_cd_play_to(uint32_t to) {
  if (g_test) { if (!g_open) return 0; g_cdto = to; g_tplay = 1; return 1; }
  if (!g_open) return 0;
  g_cdto = to;
  if (!g_p.track || !g_p.s.frames) {   /* ещё ничего не играло — с начала первой звуковой (2) */
    int tr = g_p.track ? g_p.track : 2; if (tr > g_ntracks) return 0;
    return start_at(NULL, tr, 0, end_of(tr, to), 0, "MCI_PLAY (без FROM)");
  }
  plat_snd_lockdev(1);
  g_p.end44 = end_of(g_p.track, to); g_p.notify = 0; g_p.on = g_p.pos44 < g_p.end44;
  int tr = g_p.track; int64_t at = g_p.pos44;
  plat_snd_lockdev(0);
  fprintf(stderr, "[cd] MCI_PLAY (продолжить): дорожка %d с %d:%02d\n", tr, (int)(at / OUT_RATE) / 60, (int)(at / OUT_RATE) % 60);
  return 1;
}
void plat_cd_pause(void) {   /* MCI_STOP: позиция сохраняется, ожидание уведомления снимается (ABORTED игре не нужен) */
  if (g_test) { g_tplay = 0; return; }
  plat_snd_lockdev(1); int was = g_p.on; g_p.on = 0; g_p.notify = 0; plat_snd_lockdev(0);
  if (was) fprintf(stderr, "[cd] MCI_STOP: дорожка %d\n", g_p.track);
}
int plat_aux_find_cd(void) { return g_test ? g_cdaux : 0; }
void plat_aux_set_volume(int dev, uint32_t lr) {
  if (g_test) { if (dev == g_cdaux) g_cdvol = lr; return; }
  if (dev == 0) { plat_snd_lockdev(1); g_cdvol = lr; plat_snd_lockdev(0); }
}
