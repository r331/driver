/* Заглушка offscreen-рендера, когда OSMesa не найден (macOS, Windows): тест рендера сообщает «пропущено». */
#include "../plat.h"
int plat_render_offscreen(int w, int h) { (void)w; (void)h; return -1; }
