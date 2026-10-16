#include <execinfo.h>
/* Нативная точка входа (macOS arm64 / Linux / Windows x64): SDL2 + OpenGL.
   v2.00: без --selftest запускается игра — WinMain 00521f10 (P151_WinMain) с рабочим каталогом Data_Files.
   --idle — прежний режим (пустое окно, --frames N). Кадры/снимок: RE_MAX_FRAMES, RE_SHOT_PNG (platform/sdl/plat_sys.c). */
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
void plat_dd_stub_enum(int n_dd, int n_dev, uint32_t fm);
void plat_input_enable(int on);   /* v2.03: platform/sdl/plat_di.c */
void plat_fs_mkdirs(int on);      /* v2.04: platform/sdl/plat_sys.c */
#include <signal.h>
/* v2.00: RE_WATCHDOG=N — через N с стек (в ASan-сборке) и выход 3: где игра стоит */
#if defined(__APPLE__)
/* v2.13: ld64 не допускает неразрешённый weak-символ без ASan — стек только через backtrace */
#define __sanitizer_print_stack_trace ((void (*)(void))0)
#else
void __sanitizer_print_stack_trace(void) __attribute__((weak));
#endif
static void watchdog(int sig) { (void)sig; fprintf(stderr, "[watchdog] стоп по таймеру\n");
    if (__sanitizer_print_stack_trace) __sanitizer_print_stack_trace();
    else { void *bt[48]; int n = backtrace(bt, 48); backtrace_symbols_fd(bt, n, 2); }   /* v2.08: стек и без ASan */
    fflush(NULL); _Exit(3); }
int32_t P151_WinMain(int32_t hinst, int32_t prev, int32_t cmd, int32_t show);
int  re_selftest(void);
void re_init_consts(void);
int  re_init_data_game(void);   /* v2.01: game/data_init.c (tools/gen_data_init.py) */
extern const uint32_t re_data_image_base, re_data_image_size; extern uint8_t re_data_image[];   /* v2.02: game/data_image.c */
void re_ptr_set_image(uint32_t base, void *p, uint32_t size);
static int file_exists(const char *dir, const char *name) {
    char p[1024]; snprintf(p, sizeof p, "%s/%s", dir, name);
    FILE *f = fopen(p, "rb"); if (f) fclose(f); return f != NULL;
}
int main(int argc, char **argv) {
    const char *data = "Data_Files"; int selftest = 0, frames = -1, idle = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--selftest")) selftest = 1;
        else if (!strcmp(argv[i], "--data") && i + 1 < argc) data = argv[++i];
        else if (!strcmp(argv[i], "--idle")) idle = 1;
        else if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atoi(argv[++i]);
    }
    re_init_consts();
    if (selftest) return re_selftest();
    static char found[1024];
    if (!file_exists(data, "FSIN.DAT") && !strcmp(data, "Data_Files")) {
        /* v2.13: Data_Files рядом с бинарником; в Driver.app — Contents/Resources/Data_Files или рядом с Driver.app
           (из Finder рабочий каталог — «/») */
        char *base = SDL_GetBasePath();
        if (base) {
            static const char *const cand[] = { "Data_Files", "../../../Data_Files" };
            for (unsigned i = 0; i < sizeof cand / sizeof cand[0]; i++) {
                snprintf(found, sizeof found, "%s%s", base, cand[i]);
                if (file_exists(found, "FSIN.DAT")) { data = found; break; }
            }
            SDL_free(base);
        }
    }
    if (!file_exists(data, "FSIN.DAT")) {
        fprintf(stderr, "Не найдены данные игры: укажите папку Data_Files с вашего диска: --data <путь>\n");
        return 1;
    }
    if (!idle) {
        if (chdir(data) != 0) { fprintf(stderr, "Не удалось перейти в %s\n", data); return 1; }
        if (frames > 0) { char b[16]; snprintf(b, sizeof b, "%d", frames); setenv("RE_MAX_FRAMES", b, 0); }
        if (getenv("RE_WATCHDOG")) { signal(SIGALRM, watchdog); alarm((unsigned)atoi(getenv("RE_WATCHDOG"))); }
        { re_ptr_set_image(re_data_image_base, re_data_image, re_data_image_size);   /* v2.02: таблицы/строки .data по адресам */
        int n = re_init_data_game(); if (getenv("RE_TRACE")) printf("[init] .data Game.exe: %d значений\n", n); }   /* v2.01: блокер 4 */
        plat_dd_stub_enum(1, 1, 0x100);
        plat_fs_mkdirs(1);                /* v2.04: «SAVES\\…» — недостающий каталог создаётся (selftest: открытие просто не удаётся) */
        plat_input_enable(1);             /* v2.03: клавиатура SDL / геймпад / RE_KEYS → GetDeviceState */   /* v2.00: один драйвер DirectDraw и одно устройство D3D (GL) */
        printf("Driver native: данные %s, запуск WinMain 00521f10\n", data); fflush(stdout);
        int rc = P151_WinMain(1, 0, 0, 1);
        printf("Driver native: WinMain вернул %d\n", rc);
        return rc;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) { fprintf(stderr, "SDL: %s\n", SDL_GetError()); return 1; }
    SDL_Window *w = SDL_CreateWindow("Driver (native)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *r = w ? SDL_CreateRenderer(w, -1, SDL_RENDERER_PRESENTVSYNC) : NULL;
    if (!r) { fprintf(stderr, "SDL: %s\n", SDL_GetError()); return 1; }
    printf("Driver native: данные %s найдены, окно 640x480\n", data);
    for (int running = 1, n = 0; running && n != frames; n++) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) running = 0;
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255); SDL_RenderClear(r); SDL_RenderPresent(r);
    }
    SDL_DestroyRenderer(r); SDL_DestroyWindow(w); SDL_Quit();
    return 0;
}
