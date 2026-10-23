/* v2.17: подмена страниц текстур HD-паком (RE_TEXPACK / texpack в driver.cfg). Чистый C без SDL/GL — проверяется в selftest.
   Пак: <каталог>/<имя уровня без .lev>/pNNN.png, NNN — индекс страницы i в цикле P41_LoadTexPages (страницы в порядке файла,
   пара 8-битных считается за два индекса); только 16-битные (ARGB1555, не-pair) страницы; PNG квадратный, степень двойки 256..1024. */
#ifndef RE_PLAT_TEXPACK_H
#define RE_PLAT_TEXPACK_H
#include <stdint.h>

/* каталог пака: $RE_TEXPACK (важнее), иначе ключ texpack из driver.cfg; NULL — не задан */
const char *re_texpack_dir(void);
/* "Levels/NY_01.lev" → "NY_01" */
void re_texpack_level_name(const char *path, char *out, int n);
/* PNG из памяти → пиксели A<<24|B<<16|G<<8|R (как plat_tex_create), malloc; NULL — не PNG/ошибка. Только PNG (STBI_ONLY_PNG). */
uint32_t *re_texpack_decode_png(const void *buf, int len, int *w, int *h);
/* <dir>/<level>/pNNN.png → пиксели (проверка: квадрат, степень двойки, 256..1024); NULL — нет файла/не подходит */
uint32_t *re_texpack_load(const char *dir, const char *level, int idx, int *w, int *h);
/* сверка HD-картинки с исходной страницей ARGB1555 256×256: картинка уменьшается до 256 (среднее блока), err — средняя
   |ΔRGB| (0..255) по всем пикселям (какое состояние бита 0x8000 прозрачно, решает альфа-тест при рисовании), amis — доля пикселей, где альфа (>=128) не совпала с битом 0x8000 */
void re_texpack_compare(const uint32_t *hd, int w, int h, const uint16_t *page, double *err, double *amis);
/* v2.18: 8-битные страницы (пара, флаг 0x10). Текстура Glide GR_TEXFMT_P_8 / поверхность PAL8 + палитра — 256 записей B,G,R,X из
   таблицы палитр уровня 01252be0, слот выбирает P12_Fn00426580 (00426580) во время рисования. Альфа 255: прозрачного индекса нет.
   Пак: <dir>/<level>/pNNN_cKKKK.png, NNN — индекс страницы (как у 16-битных), KKKK — номер слота палитры (0..49, из файла уровня).
   Каталог уровня ищется как есть, строчными и ПРОПИСНЫМИ (игра пишет MIAMI_01, файл — miami_01.lev). */
uint32_t *re_texpack_load8(const char *dir, const char *level, int idx, int pal, int *w, int *h);
/* индексы 256×256 + палитра (NULL — серый по индексу) → RGBA как plat_tex_create */
void re_texpack_pal8_rgba(const uint8_t *idx, const uint8_t *pal, uint32_t *out);
/* сверка HD-картинки с эталоном RGBA 256×256: средняя |ΔRGB| и доля расхождений альфы (>=128) */
void re_texpack_compare_rgba(const uint32_t *hd, int w, int h, const uint32_t *ref, double *err, double *amis);
/* путь игры (поверхности plat_dd): orig — страница 256×256 в RGBA так, как её загрузила игра; hd — w×w. 1 — принята
   (средняя |ΔRGB| <= RE_TEXPACK_MAX_ERR), альфа hd заменена альфой orig (nearest): прозрачность как у оригинала. */
int re_texpack_merge(const uint32_t *orig, uint32_t *hd, int w, double *err);
/* v2.27: оверлей неба: $RE_TEXPACK_SKY или первое слово <dir>/sky.txt → полный путь в out; NULL — нет оверлея */
const char *re_texpack_overlay(const char *dir, char *out, int n);
/* v2.36: оверлей HUD (перерисованные цифры часов миссии): $RE_TEXPACK_HUD или первое слово <dir>/hud.txt; ищется раньше неба */
const char *re_texpack_overlay_hud(const char *dir, char *out, int n);
/* порог сверки для файла, который последним вернули re_texpack_load/load8: RE_TEXPACK_HUD_MAX_ERR — из оверлея HUD, иначе RE_TEXPACK_MAX_ERR */
double re_texpack_last_tol(void);
/* re_texpack_merge с порогом tol */
int re_texpack_merge_tol(const uint32_t *orig, uint32_t *hd, int w, double tol, double *err);
/* порог: страница принимается, если err <= RE_TEXPACK_MAX_ERR и amis <= RE_TEXPACK_MAX_AMIS (иначе — перепутан индекс) */
#define RE_TEXPACK_MAX_ERR  24.0
#define RE_TEXPACK_MAX_AMIS 0.02
/* v2.36: оверлей HUD меняет форму глифов (цифры перерисованы, ~38% страницы шрифта) — порог шире; альфа-порог тот же */
#define RE_TEXPACK_HUD_MAX_ERR 48.0
#endif
