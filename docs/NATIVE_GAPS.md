# Native-сборка как игра: разрывы (v2.00–v2.02, 2026-10-16)

Сборка `re/build-native/driver` (SDL2 + OpenGL 3.3, Linux arm64, Mesa 25 под Xvfb).
Запуск игры: `work/run_game.sh [кадров] [png]` — каталог `work/run_game` (симлинки на все файлы
`input/game/Data_Files`, `ReplayData` — копия, чтобы игра не писала в `input/`), `RE_NO_MSGBOX=1`,
`xvfb-run`, `timeout 60`. `work/run` оставлен как был (только FRUSTRUM.DAT и Levels) — для selftest.

Переключатели (platform/sdl/plat_sys.c, platform/native/main.c):
- `RE_MAX_FRAMES=N` — выход 0 после N-го показанного кадра (plat_flip); `--frames N` задаёт то же.
- `RE_SHOT_PNG=путь` — снимок кадра N (или первого при `RE_SHOT_FIRST=1`), glReadPixels → PNG.
- `RE_MAX_PUMPS=N` — выход после N циклов сообщений (защита, если кадров нет).
- `RE_NO_MSGBOX=1` — MessageBox только в stderr (SDL_ShowSimpleMessageBox под Xvfb блокирует).
- `RE_WATCHDOG=N` — через N с печать стека (в ASan-сборке) и выход 3: где стоит игра.
- `RE_TRACE=1` — трассировка P55_GlideInit и всех `return 0` в P151_WinOpen/P151_Reopen.
- `--idle` — прежний режим main (пустое окно).
- v2.01: `RE_TRACE_DD=1` — журнал поверхностей DirectDraw (create/lock/upload/set_texture) и первых вызовов GL (draw_prim,
  render state); `RE_NO_CRASH=1` — обработчик аварий игры не ставится (сигналы видит ASan/gdb; ASan-сборка — /tmp/asan).

## Путь от main до игрового цикла

| шаг | функция | статус v2.00 |
|---|---|---|
| 1 | `main` (platform/native/main.c) → `chdir(--data)` → `P151_WinMain` 00521f10 | **новое**: до v2.00 main открывал чёрное окно и игру не вызывал |
| 2 | журнал, `P31_InitWindow` (окно SDL + GL 4.5 core) | проходит |
| 3 | `P133_LoadConfig` (config.dat) | нет файла → настройки по умолчанию + `P58_SaveConfig` (native) |
| 4 | `P55_GlideInit`: `P74_DevSelect` → `P149_DDEnumAll` → `P151_InstallD3D` (Glide → D3D-эмуляция) | проходит: 1 драйвер DD, 1 устройство «SDL OpenGL 0» |
| 5 | `P48_GlideCheck` (grSstQueryHardware) | проходит (после правки указателя) |
| 6 | `P151_Reopen` → `P47_GlideWinOpen` → `P151_WinOpen` 0041ed98 (режим 7, 640×480, Flip) | проходит, `00b87e20 = 1` |
| 7 | `P48_StartupSystems` (DirectInput, DirectSound, CD) | проходит; «InitCDAudio: Open CD device failed» |
| 8 | `P140_Frontend`: `P140_KeysLoad`, `P126_ShowBmpFade` COPYRIGHT.BMP, GT.BMP, REFLECT.BMP | **v2.01: картинка есть** (плитки 256×256 через D3D-эмуляцию → GL, с затемнением) — out/native_v2.01.png (кадр 30, COPYRIGHT), out/native_v2.01_gt.png (кадр 70, GT); REFLECT — кадр 120 |
| 9 | `P150_PlayFmv` (пропуск), `P136_FrontInit`, главное меню 0054cc90 — цикл `for(;;)` в P140_Frontend | **v2.02: главное меню видно** — фон BKGRND1A..F, логотип DRIVER, значки пунктов (машины, флаг, хлопушка, конусы, полицейский) — out/native_v2.02.png (кадр 300); подписи пунктов (шрифт P117_TextList/P116_Text) на снимке не видны — не проверено, рисуются ли |
| 10 | `P132_MenuLoop` / `P136_GameLoop` → `P145_LevelLoad` → `P131_GameFrame` | не достигнуто |

Проверено: 60 кадров, выход 0 (release, `work/run_game.sh 60`), md5 FRUSTRUM.DAT до/после
3c76cb744abe31d5478004ab33005585. Снимок кадра 22: `out/native_v2.00.png` — сплошной чёрный 640×480.

## Исправлено в v2.00 (по порядку, в каком мешало)

1. main не вызывал игру → вызов `P151_WinMain(1,0,0,1)` из каталога данных.
2. Пути Windows: `g_fopen` в native = `plat_fopen_game` ('\\' → '/', поиск каждого компонента без учёта регистра, иначе — путь как есть); `re_crt_mkdir` — то же (`plat_path_native`).
3. MessageBox под Xvfb блокировал процесс → `RE_NO_MSGBOX`.
4. Нет config.dat («Please run Driver Configuration.») → умолчания + запись config.dat (только native).
5. CRT rand/srand (0052e190/0052e180) были заглушками (rand = 0) → ЛКГ MSVC (platform/native/crt_msvc.c); в selftest rand = 0, как раньше.
6. Шпионы selftest линкуются в игру: `P74_Fn41CE90`/`P74_Fn424B70` вне selftest зовут `P149_DDEnumAll`/`P76_GlideRegister` (`re_selftest_on`).
7. Перечисление устройств: SDL-заглушка давала 0 устройств/пустой D3DDEVICEDESC → в игре (`plat_dd_stub_enum(1,1,0x100)`) HAL-описание GL: COLORMODEL|DEVCAPS, RGB, FLOATTLVERTEX|DRAWPRIMTLVERTEX|HWRASTERIZATION, текстуры 1..2048.
8. 64 бит: `GameCall00424661` (grSstQueryHardware) резал адрес GrHwConfiguration до int32 → SEGV; теперь `intptr_t`.
9. Псевдонимы 00b1c0d4/00b1c0d8: `P74_DevSelect` писал `G00B1C0D4`, `P47_GlideWinOpen` читал `D_00b1c0d4` → один объект.
10. `.data 00549ccc` (запрошенная глубина цвета) = 16 в Game.exe, в native был 0 → «switch to a 16/32bit display mode».
11. `P140_KeysLoad`: индекс таблицы имён клавиш `(off − 0x80)/4` (смещения от 0054b000); прежняя формула писала за таблицу 0054b080 до 0054b518 — **ошибка была и в hook**.
12. Заглушки unported.h при готовом переносе: `R12_40DAE1` → `P75_BmpToPage`, `Call00528221` → `P25_TimerStart` (колбэк по re_fn; 00408710 — счётчик 005d577c во все три native-объекта).
13. Кадры не показывались: SDL `plat_dd_flip` в игре зовёт `plat_flip` (glFinish + SwapWindow).

## Исправлено в v2.01 (по порядку, в каком мешало)

1. **DirectDraw-поверхности SDL с памятью** (platform/sdl/plat_dd.c, только игра — `plat_dd_stub_enum(…, 0x100)`; тесты — прежние учётные заглушки):
   w×h×bpp по DDSURFACEDESC2 (формат +0x48 при DDSD_PIXELFORMAT, иначе экран RGB565; цветовой ключ CKSRCBLT); первичная — размер режима
   (SetDisplayMode, по умолчанию 640×480), задняя (GetAttachedSurface) — как первичная. Lock: lpSurface (desc[9]) — синтетический
   32-битный адрес `re_ptr_register_dyn` (игра читает его `re_ptr(d[9])`), pitch, размеры, формат; Unlock помечает изменение.
   GetPixelFormat — формат поверхности. Blt COLORFILL: текстура — заливка памяти, задняя/первичная — `plat_clear_rect` (GL scissor).
   Палитры: CreatePalette/SetEntries хранят 256 PALETTEENTRY, SetPalette привязывает к поверхности (PAL8).
2. **Текстура ↔ поверхность**: QueryInterface(IID_IDirect3DTexture2) поверхности → объект-текстура со ссылкой на неё;
   `plat_set_texture` → при изменении памяти перевод в RGBA (маски формата, альфа по маске, PAL8 через палитру, ключ → альфа 0)
   и `plat_tex_update`/`plat_tex_create`, затем `plat_tex_bind`; NULL — без текстуры. Flip/Blt front←back: LFB-запись в заднюю
   (Lock) накладывается на GL-кадр (пиксель 0 прозрачный), память задней затем обнуляется; затем plat_flip.
3. **Mesa/llvmpipe и SIGILL**: обработчик аварий игры (plat_set_crash_handler) перехватывал SIGILL, которым Mesa на arm64 пробует
   инструкции CPU при первой загрузке текстуры → «Application Error». SIGILL больше не перехватывается.
4. **Шпионы selftest в игре** (блокер 5, частично): 13 шпионов tests/selftest.c вне selftest зовут перенос — P76_Fn40DCE0 → P109_TileDraw
   (плитка заставки; это и была причина пустого кадра), P68_Fn41B1C0 → P139_LadderLoad, P68_Fn41B3AB → P140_LadderRun,
   Call005233BE → P140_SndInit, P77_Fn524BD8 → P140_BankLine, P69_Fn4AAF3A → P139_Effects, P58_Fn416794 → P124_MotelKeys(0),
   P69_Fn4B33D8 → P135_DebrisTri, P70_Fn5063A4 → P135_RadarLine, P70_Fn507925 → P131_RadarArrow, P69_Fn4B2C4B → P121_DustDraw,
   P75_Fn491A56 → P119_TrafficSpawn, P77_Fn501770 → P136_OverlayMap. Слабые заглушки — platform/native/game_fwd.c:
   Call0040BF50 → P136_FrontInit, Call0040C20B → P136_GameLoop, P58_Fn40CFDF → P67_DrawIcon (0040cfdf, фон меню BKGRND*).
5. **64 бит, GrTexInfo** (блокер 2, частично): `P40_UploadSlot*` писали адрес `&P40_Blocks[b].info` как `(uint32_t)(uintptr_t)` →
   теперь `re_addr`; `P53_SetTexSource` (0041f76f, ячейка grTexSource) принимает `uint32_t info` и переводит `re_ptr` (был `const uint8_t *`
   при 32-битном аргументе ячейки — SEGV).
6. **Начальные значения .data** (блокер 4, скаляры): tools/gen_data_init.py → game/data_init.c — 347 скалярных GAME_VAR_DEF
   (int8..int32, uint8..uint32, float, double) с ненулевым значением в инициализированной части .data/.rdata Game.exe;
   `re_init_data_game()` (platform/native/main.c, только игра) пишет значение, если native-переменная после re_init_consts нулевая.
   Здесь мешали P23_ScaleUV_A/B (0054ef60/6c = 1/256) и P23_ZScale_A/B (64.0): без них u = v = 0 и z = 1.
7. **grColorCombine** `P22_SetTexOp` 0041e14f: режим — 4-й аргумент (other, `[ebp+0x14]`; 1 = текстура), прежний перенос брал 5-й
   (invert) → COLOROP = DISABLE, текстура не участвовала. **Ошибка была и в hook.**
8. **Рендер GL**: стадия 0 D3D в шейдере — COLOROP/ALPHAOP (DISABLE/SELECTARG1/2/MODULATE×1/2/4), ARG1/ARG2 (diffuse/texture),
   умолчания D3D (ARG1 = TEXTURE, ARG2 = CURRENT); альфа-тест по ALPHAFUNC (D3DCMP) и ALPHAREF; в игре ALPHATESTENABLE по умолчанию 0
   (как в D3D; тест рендера — прежнее «a < 0.5»). Новые plat_tex_update, plat_clear_rect.
9. **WM_ACTIVATEAPP**: SDL-цикл сообщений шлёт оконной процедуре 0x1c(1) при первом проходе и при FOCUS_GAINED/LOST — иначе
   P140_Frontend крутился в `if (P31_Active == 0) continue` без кадров.

## Исправлено в v2.02 (по порядку, в каком мешало)

Как рисуется меню (выяснено): P119_MenuFrame 0040cb9f → P58_Backgrounds (6 × 0040cfdf = P67_DrawIcon: P93_FindIcon + P65_SpriteKeyed
в **программный 8-битный буфер P65_Screen 0057b740**, 640×480), P98_ItemsDraw (значки пунктов — тот же путь; текстовые пункты —
00407d56 → заливка 005291ed), P117_TextList; затем P105_LfbToMenu 00407c4c: grLfbLock(1) (D3D-эмуляция → Lock задней поверхности
SDL) и перевод индексов через палитру P101_PalLfb (P101_Pal16, 565) в LFB, P58_ItemsDraw; P47_GlideSwap → наложение LFB при Flip.
Glide-значки в меню не участвуют. Lock работал; пустым было всё до него:

1. **Палитра FRONTEND.TSD — псевдонимы.** P137_LoadTsd пишет палитры в таблицу 01252be0 (P14_01252be0, 64 × 0x400), а P136_FrontInit
   брал 012533e0/012537e0 из отдельных native-объектов P136_TsdPalA/B (нули) → P101_PalLfb = 0, LFB чёрный. Теперь в native
   P136_TsdPalA/B/P136_MapPal — макросы над слотами 2/3/23 P14_01252be0, P136_MapPalOn (01252afc) — над P12_01252aa0[23].
2. **Сдвиги каналов 005c6748..5c675c — псевдонимы.** P125_ShrR..ShlB были отдельными нулевыми объектами, а пишет их P100_LfbFormat 004078d0
   как слова [1..6] P100_LfbFmt 005c6744 → вся палитра в синем канале. Теперь макросы над P100_LfbFmt[1..6].
3. **P56_FindIcon (004ec91e) в игре — шпион selftest** (возвращал NULL → значки не рисовались). 23 шпиона tests/selftest.c вне selftest
   передают вызов переносу: P56_FindIcon → P93_FindIcon, P57_MenuStep → P114_MenuStep, P58_Fn418675 → P110_MenuSel, P58_Fn4AA4EA →
   P110_IconRect, P67_Fn40ABAC → P116_Text, P66_Draw5173D7 → P73_Text, P67_Stream → P77_LoadBank, P66_Fn427EEA → P82_FrustumSetup3D,
   P76_Fn4268EF → P82_AddLight, P75_Fn4EDD08 → P88_CellUpdate, P68_Fn514A47 → P98_PartAim, P69_Fn4BA720 → P98_DrawSix,
   P67_Fn514165 → P71_Course, P67_Fn51500C → P101_PartTurn, P61_Fn5139D7 → P101_PickCell, P63_Fn49521E → P102_TrafficAhead,
   P77_Fn501C63 → P102_HudInit, Call00414D1F → P103_OptionsInit, P75_Fn4958B7 → P107_TrafficRow, P66_Fn4C68A7 → P112_DirTimeline,
   P69_Fn4B3E55 → P114_DebrisAll, P66_Fn523829 → P115_SndUpdate, P74_Fn4A4D84 → P120_ParseCamInt. Слабые заглушки LoadIconByName/
   Call004EC91E (тот же 004ec91e) — platform/native/game_fwd.c → re_addr(P93_FindIcon(…)). Шпионов из `--skip` без передачи не осталось.
4. **Таблицы меню .data по адресам (блокер 4, массивы).** P45_Wait(0054cb98, 0054cc50), P97_MenuCall0/P114_MenuStep(0054cc90) читают
   таблицы и строки через re_ptr — областей не было (NULL). tools/gen_data_init.py теперь пишет и **game/data_image.c** — изменяемую копию
   инициализированных .rdata+.data Game.exe 00546000..0057c000 (217332 байта, без хвостовых нулей); `re_ptr_set_image` (game/reptr.c) —
   запасная область re_ptr/re_addr после g_dyn и k_regions, включается только в игре (platform/native/main.c). Native-переменные с теми же
   адресами с копией не связаны (блокер 3 — по-прежнему сводить псевдонимы).
5. **P65_Texs: 16 → 64 страницы.** FRONTEND.TSD — 28 страниц; значки меню на страницах ≥ 16 читали за таблицу (ASan: global-buffer-overflow
   в P65_SpriteKeyed). В Game.exe за 01145a64 свободно до 01146f20. P65_SpriteKeyed/P65_SpriteBlend в native проверяют страницу и границы буфера.
6. **005291ed перенесена** — P152_FillRows (game/ported152.c, test_p152): заливка rows строк с шагом 0x280, ширина вверх до 32 байт;
   00407d56 (SndHelper_00407D56) пишет в P65_Screen (P11_0057b740 был отдельным native-объектом) через P152_ScreenFill с границей 640×480.
   V-строка Call005291ED удалена; hook — re_hook(0x005291ed, P152_FillRows).

**InitCDAudio ~140 раз за 300 кадров — не демо и не ошибка порта.** P119_MenuFrame (0040cb9f) на каждом кадре меню делает
`if (Q00B87E90 != 0 && P25_CdPlaying == 0) { InitCDAudio(); PlayCDTrack(2); }`; без CD открытие MCI не удаётся, флаг не ставится — попытка
на каждом кадре меню (в оригинале так же, сверено с переносом 0040cb9f). Сколько кадров меню — столько попыток (~140 из 300, остальное — заставки).
Ветка `0x2c < 005d577c → 004129df(-1)` в P140_Frontend — отдельный путь (не проверено, что она делает в native). Можно гасить повтор в
native (plat CD: «нет устройства» → не пытаться), но это отступление — не делалось.

## Блокеры в порядке, в каком они мешают запуску

0. ~~v2.01: экран главного меню чёрный~~ — **исправлено в v2.02** (см. выше). Осталось: подписи пунктов (P117_TextList → P116_Text, шрифт
   005d57a0) на снимке не видны — не выяснено; ввод (блокер 8) — без клавиш меню не листается, дальше P140_Frontend игра не идёт.
00. (было) **v2.01: экран главного меню чёрный.** Цикл меню P140_Frontend идёт (P114_MenuStep/P119_MenuFrame), фон рисуется P67_DrawIcon
   (BKGRND1A..), но на снимке кадра 300 — чёрный экран. Не выяснено: рисует ли P67_DrawIcon в программный буфер (P65_Screen) с
   выводом через LFB-Lock задней поверхности (P105, наложение при Flip) или через Glide-значки; плюс «not ported: Call005291ED»
   (005291ed, 102 байта — вызывается из ported11 с адресом 0057b740 + y·0x280 + x: копия/заливка строки буфера, не перенесена).
   Следующий шаг: RE_TRACE_DD на кадрах меню (lock задней, draw_prim), перенос 005291ed.
1. ~~Текстуры/2D через DirectDraw-эмуляцию — чёрный экран~~ — **исправлено в v2.01** (см. выше). Осталось: Blt/BltFast между
   поверхностями в памяти (`plat_dd_blt_from`/`plat_dd_blt_rect` для не-экранных поверхностей — только учёт), мип-уровни, 3D-рендер
   поверх LFB в одном кадре — наложение упрощённое (пиксель 0 прозрачный).
2. **64-битные указатели через int32.** 35 мест `(int32_t|uint32_t)(uintptr_t)&…` в re/game (напр. `P40_UploadSlot`: `info = (uint32_t)(uintptr_t)&P40_Blocks[b].info[0]`, аргумент `Call0042486B`), плюс таблица Glide с типами `FnIntI` для аргументов-указателей. Нужно: аудит ячеек Glide с аргументом-указателем (grTexDownloadMipMap, grTexSource, grDrawPolygonVertexList, grLfbLock, grSstQueryHardware …) → `intptr_t`/re_addr+re_ptr; поля структур — re_addr.
3. **Несколько native-объектов на один адрес Game.exe.** 310 адресов с более чем одним `GAME_VAR_DEF` (D_/G/P…): запись в один псевдоним не видна читателю другого (так ломались 00b1c0d4 и 005d577c). Нужно: сводить в один объект (макрос-псевдоним), начиная с путей загрузки/меню; инструмент поиска — work/own191.py.
4. **Начальные значения .data.** v2.01: скаляры — game/data_init.c (347, только игра). Осталось: массивы/структуры (g8_bytes_t, p99_rgb_t …) и поля-адреса (int32-адреса .data копируются как есть — `re_ptr` их находит только в зарегистрированных областях).
5. **Шпионы selftest в игровом бинарнике.** v2.02: все шпионы из `--skip` вне selftest передают вызов переносу (выше). Было: tests/selftest.c линкуется в driver; 41 имя из `--skip` (work/skip_v196.txt) в игре — шпионы, а не перенос (исправлено 2 в v2.00, ещё 16 в v2.01 — список выше; остальные ~23 — P67_*, P66_*, P56_FindIcon, P57_MenuStep, P58_Fn418675 …). Нужно: каждый шпион вне selftest передаёт вызов настоящей функции (по образцу v2.00) либо вынести тесты из игрового бинарника.
6. **Заглушки unported.h, у которых есть перенос.** 365 строк V/R; часть не связана в links.c (две найдены запуском). Нужно: по журналу «not ported» при каждом новом шаге запуска связывать с перенесёнными функциями (адреса → re_ptr/re_fn).
7. **Колбэки по адресу Game.exe.** `re_fn` знает только функции из k_fns (game/reptr.c); таймер 00408710 там не было (обойдено в links.c). Нужно: зарегистрировать все адреса, передаваемые в TimerStart/таблицы меню/обработчики.
8. **DirectInput → клавиатура SDL.** `plat_di_get_state` в SDL возвращает «ничего не нажато» (platform/sdl/plat_di.c); `P48_AnyKey`/меню не получают клавиш. Нужно: буфер 256 DIK из `SDL_GetKeyboardState` (таблица SDL_Scancode → DIK), события SDL в `plat_pump_messages`, мышь/джойстик — потом.
9. **DirectSound → SDL-микшер.** `plat_ds_*` (v1.93) — учётные заглушки (Lock в буфер 64 КБ), к `plat_snd_*` (SDL audio) не подключены: тишина. Нужно: вторичные буферы DS → голоса SDL-микшера (Play/Stop/SetVolume/SetFrequency/SetPan, 3D-слушатель — упрощённо).
10. **CD-аудио.** «InitCDAudio: Open CD device failed» — MCI нет; музыка с дорожек CD. Нужно: заменить на файлы дорожек (OGG/WAV) или пропуск (сейчас — пропуск, не блокирует).
11. **FMV.** CoCreateInstance в SDL отказывает (E_NOTIMPL) — ролики пропускаются, как задумано (v1.95); не блокирует.
12. **Окно/GL.** Работает: SDL-окно 640×480, GL 4.5 core (Mesa), Flip → SwapWindow. Не проверены: оконный режим (Blt front←back, `plat_dd_blt_rect`), смена разрешения (`plat_window_move`), полноэкранный режим.

## Замечания по безопасности данных

- test_p77 (selftest) пишет и удаляет `Levels/t77.lev` через симлинк `work/run/Levels` → во время selftest временный файл появляется в `input/game/Data_Files/Levels` (оригинальные файлы не меняются; так было и до v2.00). Стоит перенести в отдельный каталог.
- С полным набором Data_Files в рабочем каталоге selftest падает в test_p52 (SIGSEGV) — поэтому игра запускается из `work/run_game`, selftest — из `work/run`.
