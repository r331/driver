/* Нативная точка входа (macOS arm64 / Linux / Windows x64): SDL2 + OpenGL.
   Пока: окно, игровой цикл, проверка данных игры. Игровые модули подключаются по мере переноса. */
#include <SDL.h>
#include <stdio.h>
#include <string.h>
int  re_selftest(void);
static int file_exists(const char *dir, const char *name) {
    char p[1024]; snprintf(p, sizeof p, "%s/%s", dir, name);
    FILE *f = fopen(p, "rb"); if (f) fclose(f); return f != NULL;
}
int main(int argc, char **argv) {
    const char *data = "Data_Files"; int selftest = 0, frames = -1;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--selftest")) selftest = 1;
        else if (!strcmp(argv[i], "--data") && i + 1 < argc) data = argv[++i];
        else if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atoi(argv[++i]);
    }
    if (selftest) return re_selftest();
    if (!file_exists(data, "FSIN.DAT")) {
        fprintf(stderr, "Не найдены данные игры: укажите папку Data_Files с вашего диска: --data <путь>\n");
        return 1;
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
