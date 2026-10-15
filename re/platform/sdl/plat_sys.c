#include "../plat.h"
#include <SDL.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <limits.h>
static SDL_Window *g_win;
uint32_t plat_time_ms(void){ return SDL_GetTicks(); }
void plat_sleep_ms(uint32_t ms){ SDL_Delay(ms); }
void plat_log(const char *f, ...){ va_list a; va_start(a,f); vfprintf(stderr,f,a); va_end(a); }
void *plat_file_open(const char *path, const char *mode){
    FILE *f = fopen(path, mode); if (f) return f;
    char dir[PATH_MAX], *s; strncpy(dir, path, sizeof dir - 1); dir[sizeof dir - 1] = 0;
    s = strrchr(dir, '/'); const char *base = s ? s + 1 : dir;
    if (s) *s = 0; else strcpy(dir, ".");
    DIR *d = opendir(dir); if (!d) return NULL;
    struct dirent *e; char full[PATH_MAX*2];
    while ((e = readdir(d))) if (!strcasecmp(e->d_name, base)) {
        snprintf(full, sizeof full, "%s/%s", dir, e->d_name); closedir(d); return fopen(full, mode); }
    closedir(d); return NULL;
}
int plat_window_open(const char *t,int w,int h,int fs){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) return -1;
    g_win = SDL_CreateWindow(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, fs?SDL_WINDOW_FULLSCREEN_DESKTOP:0);
    return g_win ? 0 : -1;
}
int plat_poll_events(void){ SDL_Event e; while (SDL_PollEvent(&e)) if (e.type==SDL_QUIT) return 0; return 1; }
int plat_key_down(int sc){ const Uint8 *k = SDL_GetKeyboardState(NULL); return k ? k[sc] : 0; }
void plat_window_close(void){ if (g_win) SDL_DestroyWindow(g_win); g_win=0; SDL_Quit(); }
