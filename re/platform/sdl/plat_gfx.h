/* v2.16: настройки графики native (driver.cfg + переменные RE_*) и обработка текстур без GL (dilation, мипмапы).
   Чистый C без SDL/GL — проверяется в selftest без данных игры. */
#ifndef RE_PLAT_GFX_H
#define RE_PLAT_GFX_H
#include <stdint.h>

enum { RE_FILTER_NEAREST = 0, RE_FILTER_LINEAR = 1, RE_FILTER_TRILINEAR = 2 };   /* filter: 3D-текстуры */
enum { RE_HUD_NEAREST = 0, RE_HUD_LINEAR = 1, RE_HUD_SHARP = 2 };               /* hud_filter: 2D/HUD/шрифты (sharp-bilinear) */
enum { RE_VSYNC_OFF = 0, RE_VSYNC_ON = 1, RE_VSYNC_ADAPTIVE = -1 };

typedef struct {
    char   preset[16];      /* original | enhanced | safe (v2.24: original + без FBO) */
    int    msaa;            /* 0/1 — выкл., 2/4/8 — сэмплов (мультисэмпловый FBO + resolve) */
    int    a2c;             /* alpha-to-coverage для альфа-теста (пальмы, заборы) при MSAA */
    int    fxaa;            /* пост-проход FXAA */
    int    aniso;           /* 1..16, анизотропная фильтрация 3D */
    int    mipmaps;         /* мипмапы (свои, с dilation и сохранением покрытия альфы) */
    int    dilate;          /* цвет непрозрачных соседей в прозрачные пиксели (без ореолов chroma-key) */
    int    filter;          /* RE_FILTER_* */
    int    hud_filter;      /* RE_HUD_* */
    double render_scale;    /* 0.5..2.0 — масштаб кадра (SSAA при > 1) */
    int    vsync;           /* RE_VSYNC_* */
    int    fps_limit;       /* 0 — без ограничения */
    double gamma;           /* 0.5..2.5, 1 — как есть */
    double brightness;      /* 0.5..2.0, 1 — как есть */
    double sharpen;         /* 0..1, 0 — выкл. */
    char   aspect[24];      /* "" — не задано (RE_ASPECT / auto) */
    int    fullscreen;      /* -1 не задано, 0 окно, 1 полный экран рабочего стола, 2 — эксклюзивный (v2.24) */
    int    win_w, win_h;    /* windowed_res, 0 — не задано */
    int    fbo;             /* v2.24: 1 — кадр через FBO (MSAA/FXAA/render_scale/гамма), 0 — прямо в окно (безопасный режим, как v2.15) */
    double draw_distance;   /* v2.19: множитель дальности прорисовки 1.0 (оригинал) .. 4.0; enhanced — 2.0 */
    char   texpack[512];    /* v2.17: каталог HD-пака текстур ("" — выкл.; RE_TEXPACK важнее) */
    char   source[512];     /* откуда прочитан driver.cfg ("" — файла нет) */
    char   music_dir[512];  /* v2.22: каталог дорожек CD-музыки ("" — ./Music; RE_MUSIC_DIR важнее) */
} re_gfx_cfg;

void re_gfx_defaults(re_gfx_cfg *c);                         /* пресет enhanced */
int  re_gfx_preset(re_gfx_cfg *c, const char *name);         /* 0 — ok, -1 — неизвестный пресет */
/* текст driver.cfg: строки key = value, комментарии # и ;, сначала применяется preset, затем остальные ключи по порядку;
   возврат — число ошибок (неизвестный ключ/плохое значение — строка пропускается, в лог через err, если не NULL) */
int  re_gfx_parse(re_gfx_cfg *c, const char *text, void (*err)(const char *msg));
/* переопределения из окружения: getter(имя) → значение или NULL (в игре — getenv); RE_PRESET, RE_MSAA, RE_A2C, RE_FXAA,
   RE_ANISO, RE_MIPMAPS, RE_DILATE, RE_FILTER, RE_HUD_FILTER, RE_RENDER_SCALE, RE_VSYNC, RE_FPS_LIMIT, RE_GAMMA, RE_BRIGHTNESS, RE_SHARPEN, RE_TEXPACK, RE_DRAW_DIST, RE_FBO (v2.24) */
int  re_gfx_env(re_gfx_cfg *c, const char *(*getter)(const char *));
void re_gfx_clamp(re_gfx_cfg *c);                            /* привести к допустимым значениям */
int  re_gfx_set(re_gfx_cfg *c, const char *key, const char *val);   /* 0 ok, -1 ключ, -2 значение */
const char *re_gfx_describe(const re_gfx_cfg *c, char *buf, int n);

/* глобальные настройки процесса (игра): load ищет driver.cfg: RE_CFG, затем exe_dir/driver.cfg, затем user_dir/driver.cfg */
re_gfx_cfg *re_gfx(void);
int  re_gfx_load(const char *exe_dir, const char *user_dir, void (*err)(const char *msg));

/* dilation: RGB пикселей с альфой 0 — среднее непрозрачных (a > 0) соседей, волнами до max_pass; остаток — средний цвет
   непрозрачных. Альфа не меняется. Возврат — число заполненных пикселей. */
int  re_gfx_dilate(uint32_t *rgba, int w, int h, int max_pass);
/* следующий уровень мипмапа (w/2 × h/2, не меньше 1): RGB — среднее, взвешенное альфой; альфа — среднее с коррекцией
   покрытия: доля alpha >= ref как у уровня 0 (coverage, 0..1; < 0 — без коррекции). dst — max(1,w/2)·max(1,h/2) пикселей. */
void re_gfx_mip_next(const uint32_t *src, int w, int h, uint32_t *dst, double coverage, int ref);
void re_gfx_mip_box(const uint32_t *src, int w, int h, uint32_t *dst);   /* простое среднее 2×2 (RGBA), без учёта альфы */
double re_gfx_coverage(const uint32_t *rgba, int w, int h, int ref);
int  re_gfx_has_partial_alpha(const uint32_t *rgba, int w, int h);   /* есть пиксели с альфой < 255 */
#endif
