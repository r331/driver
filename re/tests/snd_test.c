/* Тест программного микшера: без аудио-устройства, проверяет значения выходных сэмплов. */
#include "../platform/plat.h"
#include <stdio.h>
#include <string.h>
#define CHK(c) do { if (!(c)) { printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #c); return 1; } } while (0)
int test_snd(void) {
    int16_t pcm[100]; for (int i = 0; i < 100; i++) pcm[i] = 16000;      /* моно 16 бит, 44100 Гц */
    int h = plat_snd_create(pcm, sizeof pcm, 44100, 1, 16); CHK(h > 0);
    int16_t out[2 * 64];
    plat_snd_mix(out, 64); CHK(out[0] == 0 && out[1] == 0);               /* не играет → тишина */
    plat_snd_set(h, 0, 44100, 0); plat_snd_play(h, 0);
    plat_snd_mix(out, 64); CHK(out[0] > 15000 && out[0] == out[1]);       /* полная громкость, центр */
    plat_snd_mix(out, 64);                                                /* хвост: кадры 64..99 */
    CHK(out[2 * 35] > 15000 && out[2 * 40] == 0);                         /* закончился на 100-м кадре, дальше тишина */
    plat_snd_set(h, -2000, 44100, 0); plat_snd_play(h, 0);                /* -20 дБ ≈ 0.1 */
    plat_snd_mix(out, 8); CHK(out[0] > 1400 && out[0] < 1800);
    plat_snd_stop(h);
    plat_snd_set(h, 0, 44100, 10000); plat_snd_play(h, 1);                /* pan вправо: левый почти заглушён, цикл */
    plat_snd_mix(out, 64); plat_snd_mix(out, 64);                         /* 128 кадров > 100 → зациклилось */
    CHK(out[0] < 100 && out[1] > 15000);
    plat_snd_stop(h);
    uint8_t p8[10]; memset(p8, 255, sizeof p8);                           /* 8 бит стерео, 255 → ≈ +1.0 */
    int h2 = plat_snd_create(p8, sizeof p8, 44100, 2, 8); CHK(h2 > 0 && h2 != h);
    plat_snd_set(h2, 0, 44100, 0); plat_snd_play(h2, 0); plat_snd_mix(out, 2); CHK(out[0] > 32000);
    plat_snd_destroy(h); plat_snd_destroy(h2);
    CHK(plat_snd_create(NULL, 10, 44100, 1, 16) == 0);
    printf("snd mixer ok\n"); return 0;
}
