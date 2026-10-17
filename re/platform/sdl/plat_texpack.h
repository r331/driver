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
/* порог: страница принимается, если err <= RE_TEXPACK_MAX_ERR и amis <= RE_TEXPACK_MAX_AMIS (иначе — перепутан индекс) */
#define RE_TEXPACK_MAX_ERR  24.0
#define RE_TEXPACK_MAX_AMIS 0.02
#endif
