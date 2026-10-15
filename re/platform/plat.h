#ifndef PLAT_H
#define PLAT_H
#include <stdint.h>
/* Platform interface: game code in game/ calls only this. */
/* --- system --- */
uint32_t plat_time_ms(void);
void plat_sleep_ms(uint32_t ms);
void plat_log(const char *fmt, ...);
void *plat_file_open(const char *path, const char *mode); /* case-insensitive lookup */
/* --- window & input --- */
int plat_window_open(const char *title, int w, int h, int fullscreen);
int plat_poll_events(void); /* returns 0 on quit request */
int plat_key_down(int scancode);
void plat_window_close(void);
#endif
