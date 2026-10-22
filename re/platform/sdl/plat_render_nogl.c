/* Заглушка offscreen-рендера, когда OSMesa не найден (macOS, Windows): тест рендера сообщает «пропущено». */
/* Offscreen-render stub used when OSMesa is unavailable (macOS, Windows): the render test reports "skipped". */
#include "../plat.h"
/* plat_render_offscreen — native only (no Game.exe address).  Always fails (-1): no offscreen GL context. */
int plat_render_offscreen(int w, int h) { (void)w; (void)h; return -1; }
