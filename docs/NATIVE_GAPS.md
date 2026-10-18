# Native-сборка как игра: разрывы (v2.00–v2.21, 2026-10-16)

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
- v2.08: `RE_FIXED_DT=1` — виртуальные часы (воспроизводимые прогоны, см. «Исправлено в v2.08»); RE_WATCHDOG печатает стек и без ASan.
- v2.03: `RE_KEYS="кадр:клавиша,…"` — сценарий нажатий (клавиша нажата с кадра N `RE_KEYS_HOLD` кадров, по умолчанию 2; имена UP DOWN
  LEFT RIGHT RETURN ESC SPACE F1..F12 A..Z 0..9 … или номер DIK); `RE_TRACE_KEYS=1` — журнал GetDeviceState и шагов P114_MenuStep;
  `RE_TRACE_TEXT=1` — список надписей P117_TextList; `RE_CRASH_BT=1` — стек (glibc backtrace) при аварии; `RE_NO_GVAR_IMG=1` — выключить
  размещение переменных в образе данных (для сравнения).
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
| 7 | `P48_StartupSystems` (DirectInput, DirectSound, CD) | проходит; v2.22: CD — эмуляция (plat_cdaudio.c), раньше «InitCDAudio: Open CD device failed» |
| 8 | `P140_Frontend`: `P140_KeysLoad`, `P126_ShowBmpFade` COPYRIGHT.BMP, GT.BMP, REFLECT.BMP | **v2.01: картинка есть** (плитки 256×256 через D3D-эмуляцию → GL, с затемнением) — out/native_v2.01.png (кадр 30, COPYRIGHT), out/native_v2.01_gt.png (кадр 70, GT); REFLECT — кадр 120 |
| 9 | `P150_PlayFmv` (пропуск), `P136_FrontInit`, главное меню 0054cc90 — цикл `for(;;)` в P140_Frontend | **v2.02: главное меню видно** — фон BKGRND1A..F, логотип DRIVER, значки пунктов (машины, флаг, хлопушка, конусы, полицейский) — out/native_v2.02.png (кадр 300); подписи пунктов (шрифт P117_TextList/P116_Text) на снимке не видны — не проверено, рисуются ли |
| 9a | v2.03: подписи пунктов (P117_TextList → P116_Text) | **видны** — out/native_v2.03.png (кадр 300, «Undercover») |
| 9b | v2.03: ввод SDL → DirectInput, листание меню | **работает** — RE_KEYS="300:RIGHT": пункт 0 → 7, out/native_v2.03_keys.png («Car Chases», кадр 330); RE_KEYS="300:RETURN,400:RETURN,500:RETURN" — подменю Undercover (New Game / Load Saved Game), out/native_v2.03_sub.png (кадр 600) |
| 10 | Undercover → New Game: Ui0041355B → P68_ScreenReset → P139_LadderLoad (MLADDER.DML) → P140_LadderRun → `P136_GameLoop` → `P145_LevelLoad` → P138_LoadMission → P77_LoadLevel | **v2.03: доходит до загрузки уровня**; «LoadMission», cosmetics/denting загружены; авария SIGSEGV в `P40_DownloadPalette` ← `P41_LoadTexPages` ← P77_LoadLevel (кадр ≈410, RE_KEYS="300:RETURN,400:RETURN"); в журнале «not ported: Call004D303A, Call005283B5» |
| 11 | `P131_GameFrame` (заезд) | не достигнуто |

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

## Исправлено в v2.03 (по порядку, в каком мешало)

1. **Ввод SDL → DirectInput** (platform/sdl/plat_di.c, только игра — `plat_input_enable(1)` в platform/native/main.c): GetDeviceState(0x100)
   клавиатуры = SDL_GetKeyboardState через таблицу SDL_Scancode → DIK + первый SDL_GameController (крестовина/левый стик → стрелки,
   A/Start → RETURN, B/Back → ESC, X → SPACE) + сценарий RE_KEYS. Буферизованный ввод (GetDeviceData) игре не нужен: перенос 004e417f
   читает только GetDeviceState. Мышь, джойстик DIJOYSTATE (кроме lX/lY заглушки) — не сделаны.
2. **00d04b00 — один блок клавиш.** P34_Keys/P34_KeysPrev (пишет 004e417f), A_00D04B00 (читает IsFlagSetNotMasked_004E383A — «нажата,
   а в прошлом кадре нет», которым листает меню P114_MenuStep), KeyState (dirnodes/ported107/110) и P21_AxisOut были четырьмя разными
   native-объектами: клавиши не доходили до меню. В native — макросы над одним блоком (ported34.h, dirnodes.h, ported21.h); hook не затронут.
3. **Подписи пунктов: таблицы меню и переменные .data — один объект на адрес** (блокеры 3/4). Строки пунктов берутся из таблицы
   0054cc50 (`P45_PtrA`): слово +8 — адрес строки, его пишут обработчики пунктов (SetIconIdx00412A0D: `Q0054CC58 = Q00C5585C`) из таблицы
   языка 00c55820 (P98_LoadLang). В v2.02 у этих адресов было по два объекта (native-переменная и копия .data для re_ptr) — список надписей
   был пуст. Теперь: game/gvar.h `re_gvar()` + tools/gen_gvar_img.py — в игре **2423 переменных GAME_VAR** со скалярными типами
   (и массивами из них, плюс p42_var_t) с адресами 00546000..01287000 (.rdata+.data+.bss Game.exe, 13 МБ) живут в образе данных
   (game/data_image.c + нули); их адреса re_ptr отдаёт в образ раньше реестра (game/gvar_img_tab.c — таблица диапазонов). Вне игры
   (selftest/ctest) образа нет — прежние native-объекты. Генератор правит заголовки (блоки «gvar-img v2.03») и объявления
   (`#pragma push_macro … /*gvi*/`); перезапуск — `python3 tools/gen_gvar_img.py`. Структуры с указателями/иной раскладкой в 64 битах
   не переносятся (остаются native).
4. **re_fn по всем перенесённым функциям**: platform/native/fn_table.c (tools/gen_fn_table.py из 2205 re_hook install.c) — колбэки таблиц
   меню (обработчики пунктов 004129.. 00413…), таймеров и т. п. по адресу Game.exe; только в игре.
5. **fgets текстового режима MSVC** (game/crt.h, native): «\r\n» → «\n». MLADDER.DML (CRLF) давал токен «[MIAMI]\r» → «MLADDER: Unknown CITY»,
   New Game сразу возвращался в меню.
6. P139_KeyMenuA/B: `static const` с адресами переменных → `const` (адрес через re_gvar не константа); поведение то же.
7. RE_CRASH_BT — стек при аварии (так найден P42_FindVar: таблица переменных скрипта 0056dc10 была пустой native-копией без записи 0x7f).

Замечено: запись «SAVES\SCORES.HI» — каталога SAVES нет в work/run_game (и в work/run), plat_fopen_game создаёт файл с обратной косой
чертой в имени в текущем каталоге (не в input/). Нужно: создавать SAVES в каталоге запуска или в plat_fopen_game для режима записи.

## Исправлено в v2.12 (мотель → первая миссия, погоня, гудок)

Сценарии (`RE_FIXED_DT=1`, work/fxrun.sh): Undercover — `RE_SKIP_INTERVIEW=1 RE_KEYS="300:RETURN,400:RETURN,1700:RETURN,2100:RETURN,2300:RIGHT,2400:RETURN,2600:RIGHT,2700:RETURN,2900:RIGHT,3000:RETURN"`;
Take A Ride с газом — `300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,800:0x28:900`. Новые переключатели: `RE_MOTELDBG=N` (меню мотеля
и Enter автоответчика), `RE_3DDBG=N` (3D-ослабление голосов с громкостью > −10000 в plat_dsmix), `RE_SND_LOG` печатает и смену громкости буфера.

1. **Мотель: Enter не действовал — thunk-адреса.** Меню мотеля P132_MenuLoop (00417b80) кладёт в 005fea44 адрес обработчика пункта —
   это thunk-и инкрементальной компоновки Game.exe (P58_MenuSwitch 00417e0d: 004013c5 → 00416540 автоответчик, 00401dde → 0041ab60,
   00401dc5 → 00417970, 00402621 → 00419f00; 00417f45 — сама функция). re_fn знал только адреса функций, давал NULL — Enter ставил
   обработчик, но он не вызывался. Теперь re_fn разрешает thunk: re/platform/native/thunk_table.c (1378 переходников 00401005..00402aea,
   tools/gen_thunk_table.py читает jmp rel32 из Game.exe). Ожидания конца звука/CD/FMV в мотеле нет (сверено: P58_Menu416540 00416540 —
   цикл опроса 00416794 + перерисовка; P124_MotelKeys 00416794 — ←/→ выбирают кнопку автоответчика 0..3 (назад / проиграть / вперёд /
   принять), Enter — действие; «принять» у пункта с флагом 2 (миссия) возвращает 1 и номер пункта в 0054e51c). CD-попытка
   InitCDAudio каждый кадр (P66_FrameBegin 004188b0, `P25_CdPlaying == 0`) — как в оригинале без диска, не блокирует.
2. **Мотель: «проиграть» падал (SIGSEGV в snprintf).** P68_ChangeSample (0052455f) передаёт драйверу 0048bf9a (= P140_SndLoadWav(n,
   const char *)) 32-битный адрес имени AUDIO\MOTEL\ANS001.WAV — в native это было число вместо указателя. Теперь для этого драйвера
   имя берётся через re_ptr (иной драйвер, например шпион selftest, вызывается как в оригинале; hook без изменений).
3. **Надписи меню мотеля.** P66_ScreenFrame (0041846c) не рисовал таблицы пунктов из .data Game.exe (Resolve → NULL); теперь адрес
   берётся из образа данных (re_ptr) — на снимке «Get A New Job» (out/native_v2.12_motel_text.png).
   Результат: Undercover → New Game → мотель → Enter (автоответчик, out/native_v2.12_answering.png) → →/Enter «проиграть» → →/Enter →
   →/Enter «принять» (пункт 0, флаги 0x12, номер 1) → **первая миссия Майами «Get to the bank.»** с таймером, машина на улице
   (284812, −50302) — out/native_v2.12_mission1.png (кадр 3600).
4. **Погоня — таблица машин закрыта «байтовой» заглушкой образа.** re_ptr сначала проверял диапазоны образа данных; заглушка
   A_00D04B00 (g8_bytes_t, 0x40000 байт от 00d04b00, блок клавиш) накрывает таблицу машин 00d077c0..00d0cb10, которая живёт только в
   native-массиве P99_Cars (cartab.h). Поэтому re_ptr(адрес машины) отдавал нулевой образ: машина копа из слота +0xcd0 для
   P102_CopsTick/ИИ копов, позиция игрока 00d07888 для 3D-звуков. Теперь re_ptr для области P99_Cars возвращает P99_Cars до проверки
   образа (game/reptr.c). Следствия: (а) «через ~40 кадров слот копа получает другую машину» — это было обычное пересоздание дальней
   патрульной машины трафиком: RE_COPNEAR переставлял пустую запись образа, настоящая машина ехала дальше; (б) теперь с
   `RE_COPNEAR=3000:900` коп видит → Felony 682 → 2049 → 4095 (предел), активны 4 копа (sugg 4), трое преследуют игрока и таранят
   (дистанция 600–1100) — out/native_v2.12_chase.png (две полицейские машины с мигалками вплотную, полоса Felony полная). Кадр
   погони ИИ (P142_CopDrive → P128_CopReplan → P128_CopPath → P44_Atan2) отработал без падений (до исправления путь копа читал
   узлы из устаревших k_regions и падал в P44_Atan2). Без отладки: Felony 0 — патруль к игроку по-прежнему не подходит.
   Поиск `(uint32_t)(uintptr_t)` по re/game: в native-ветках остались только синтетические адреса/хэши (ported129 RepeatCheck,
   ported59:345 маска, регистраторы ported98/139) — не указатели в слоты. tools/find_gvar_bypass.py: новых обходов нет (остаток — объявления
   через запятую в ported68.c и уже обёрнутые re_gvar).
5. **Гудок.** Голос 2 привязан к позиции игрока (SoundLoop_0052422D(2, re_addr(&P99_Cars[0].pos)), ported116.c → такт звука ported115.c
   читает позицию через re_ptr) — из-за п. 4 источник стоял в (0, 0, 0), в 420 тыс. от слушателя: ослабление DS3D
   1/(1 + rolloff·(d − 1)) при rolloff ≈ 0,0003 давало ×0,008 (−42 дБ). Теперь источник у машины (≈1300 от камеры, ×0,73): разница
   WAV с H и без — RMS ≈ 8900 (на фоне ≈ 9000–10000; в v2.11 — ≈ 100). Отрывок 24,5–30,5 с — out/native_v2.12_horn.wav. Тот же путь
   у сирен и двигателей машин трафика (ported101.c:709, ported103.c:763) — теперь тоже с правильной позицией.

## Исправлено в v2.11 (копы видят игрока, псевдонимы образа данных, пропуск интервью)

Сценарий Take A Ride — как в v2.10 (`300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN`), `RE_FIXED_DT=1`, work/fxrun.sh.
Новые переключатели: `RE_COPNEAR=K[:кадр]` — **отладка**: один раз (по умолчанию игровой кадр P62_Frame 1000) первая патрульная машина
ставится перед машиной игрока (машина + K/1000·(машина − камера), как RE_PEDNEAR), дальше — обычный ИИ; `RE_COPDBG` теперь печатает и
позицию игрока, и флаги выхода P112_ChaseTick (`[chase]`); `RE_SKIP_INTERVIEW=1` — интервью пропускается, как чит 00b87e9c;
`RE_HORNDBG=N` — голос 2 (гудок) в P48_SetVoiceVolume. Инструмент tools/find_gvar_bypass.py — обращения к переменным образа данных
в обход re_gvar (после препроцессора каждого game/*.c).

1. **Копы не видели игрока — усечение указателя.** P102_CopsTick (004a6403, сверено с out/Game_decomp.c) берёт машину копа из
   слота +0xcd0 через re_ptr; в native слот заполняли `(uint32_t)(uintptr_t)указатель` (ported62.c:580 — патруль из трафика,
   ported119.c:286), re_ptr давал NULL → `continue` для каждого копа, «видит» не могло стать 1. Исправлено: re_addr (в hook — как было).
   Теперь в слоте адрес таблицы машин (00d08ed0 и т. п.). Проверка: с RE_COPNEAR=3000:900 и газом коп в 3720 от игрока — seen 1,
   **Felony 0 → 682** (0x2aa — порог «розыск»), «Last observed felony» 2 (превышение скорости); полоса Felony на HUD заполнена —
   out/native_v2.11_felony.png (кадр 1722, на тротуаре видны пешеходы). Без отладки патруль ходит по z ≈ 430 тыс., игрок стартует в
   (−256, 418712) и упирается в стену при движении назад (z 420172) / вперёд (z 400500) — ближе 9,8 тыс. коп не подходит, а видит он
   ближе 4000 всегда или ближе 12500 в конусе ±0x100 (P99_CopsNear 004d2b5d / FillRange 004d2b16 сверены) — поэтому без отладки Felony 0.
   Не сделано: после перестановки ИИ копа держит свою точку пути (+0x319/+0x31b) и через ~40 кадров слот получает другую машину
   (вдали) — погоня не началась; полицейской машины на снимке нет.
2. **Псевдонимы в обход образа данных** (tools/find_gvar_bypass.py): макросы v1.4x вида `#define ALIAS NAME` над native-объектом
   работали мимо образа (v2.03) там, где заголовок NAME не включён. Переведены на re_gvar: TrafficRecs в ported7.h (A_011443E0,
   CountByOwner_0048F2E7) и ported21.h (P21_Entries, 0049509a — подсчёт записей трафика), P17_SlotBase/P17_MapBase (nodetab.h, таблицы
   слотов 00c1ed80 и узлов 00bf1c40), P12_00c808d0 (полоса HUD, P101_Hud+0x10), P8_005507d0/d4/d8/01251a68 (направление света),
   D_00b1c0d4/D_00b1c0d8 (ported4.h, Glide-флаги). Остаток списка — ложные срабатывания (объявления через запятую в ported68.c).
3. **Undercover — интервью.** В ladder (data/mladder.dml) первая запись INTERVIEW {0xb}: P140_LadderRun, case 0xb — если
   MenuOptB87E9C (00b87e9c) = 0, идёт P136_GameLoop с P62_HudOff2 = 1 (интервью в гараже, «Interview 1, Training 0, mode 2»),
   иначе интервью пропускается. Флаг 00b87e9c — пункт 5 меню Cheats (ToggleB87E9C 00404f2d, появляется при 00bdf9fc ≠ 0; строка
   «Skip Interview» есть в lang.eng). С RE_SKIP_INTERVIEW=1 Undercover → New Game доходит до **мотеля** — комната с автоответчиком
   (out/native_v2.11_motel.png, кадр 1800). Дальше не идёт: кадр неподвижен, Enter (кадры 1900/2300/2700) ничего не меняет, надписей нет
   (кадр 3400 тот же). «Could not find required models. Pedestrians have been disabled.» — это ported137.c (пешеходы в гараже), к
   миссиям не относится. Что требует само интервью (порядок упражнений) — по коду не разобрано.
4. **Гудок H.** Игровая сторона работает: H → P107_HornVol 0 → P48_SetVoiceVolume(2) — слот 2 флаги 0x21 (играет + 3D у машины),
   id 0xa, бит 8 снимается в такте звука (ported115.c → DrvH). Но в WAV RMS по секундам с H и без отличается на 1–2 (10141 / 10140) —
   голос почти не слышен; вероятно, ослабление 3D-буфера в plat_dsmix или громкость сэмпла — не выяснено.

## Исправлено в v2.10 (управление, пауза, копы, пешеходы, ограничитель звука)

Сценарий: меню как в v2.08 (`300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN`), `RE_FIXED_DT=1`, work/fxrun.sh.
Новые переключатели: `RE_COPDBG=N` — раз в N кадров рейтинг Felony / активные копы / рекомендовано / предел / последнее нарушение
и позиции копов (0112da00, +0x319/+0x31b, видит ли игрока); `RE_PEDDBG=1` дополнен — первые 3 пешехода (позиция, флаги) и счётчики
отсева в P113_PartDraw (вызовы / ближе 15001 / в пирамиде / в сетке света / мин. дистанция), `RE_PEDN=N` — период печати;
`RE_PEDNEAR=K` — **отладка**: первый активный пешеход каждый такт ставится перед машиной (машина + K/1000·(машина − камера));
`RE_CRASH_BT=1` теперь печатает pc/lr места аварии из контекста сигнала (sigaction SA_SIGINFO; раньше стек показывал только обработчик).

1. **Клавиши машины** — раскладка по умолчанию `k_defcfg` (P37_InitInput, .data 0054b7a8) → P36_KeyCfg; P36_GetPadButtons собирает
   биты, P107_CarInput (004d5f..) их разбирает. Проверка по `[car]`/`[carin]` (RE_CARDBG):
   | бит | клавиша (DIK) | действие по коду | проверка |
   |---|---|---|---|
   | 2 | `'` 0x28 | газ (ff8 = +mx) | скорость 10c растёт до ≈ 690000 |
   | 1 | `/` 0x35 | тормоз, затем задний ход (ff8 = −mx) | с газа 475349 → 398575 → −139345 → −565299 (едет назад, pos z растёт) |
   | 8 / 4 | `Z` 0x2c / `X` 0x2d | руль (ffc ∓ 0x10 за кадр, предел 0x160) | ffc до 352 |
   | 0x10 | пробел 0x39 | резкий руль: шаг 0x20, предел 0x1ff | ffc до 511 (без пробела — 352) |
   | 0x20 | Enter 0x1c | ручник (f104 = 1, звук канала 10) | с нажатым газом 167752 → 6139 за 100 кадров |
   | 0x40 | `\` 0x2b | f108 — пробуксовка на старте (при 10c > 0xa2000 → газ) | не проверено |
   | 0x80 | `C` 0x2e | круиз-контроль (P102_D0DDEC, строка «Cruise control active») | не проверено |
   | 0x100 | `H` 0x23 | гудок: P107_HornVol → P48_SetVoiceVolume(2); в режиме 10 — переключение сирены | WAV с H и без — RMS по секундам одинаков (9058/9011 vs 9057/9011): **не слышно**, не выяснено |
   Прочие (P126_DebugKeys 004d74e0, P98_FreeCamKeys 004d7766): `1` (DIK 2, KeyCfg[16]) — камера 0 → 2 → 8 (P59_Mode1137324):
   **проверено**, режим 2 — вид с капота (out/native_v2.10_cam_bonnet.png); `2` (KeyCfg[17]) — камера 0x11; `J`/`K`/`L` — поворот
   свободной камеры влево/вправо/назад; F1/F2 — дальность 01270c24 (15000..45000), F3/F4 — зеркало; `-`/`=` — зум; F12 — снимок BMP;
   **Esc** — пауза (SetLatchValue0050E940(1)).
2. **Esc падал** («Application Error»): P116_PauseMenu → SoundMenuSave0051080E вызывал ячейку 01270e80 (grDepthBufferMode; метка
   0041e3b0 не в k_fns → в native NULL) без проверки — переход по нулевому адресу (pc 0, lr в P116_PauseMenu). Проверка добавлена в
   SoundMenuIn/Out/Save (ported6.c) и uihandlers3.c:375, как в остальных местах; в hook ячейка не NULL — поведение то же.
   Меню паузы видно: out/native_v2.10_pause.png (PAUSED: Continue, Restart, Sound Setup, Gfx Details, Film Director, Quick Replay,
   Show Map, Exit).
3. **Копы/Felony**: в Take A Ride появляется одна патрульная машина (active cops 1, sugg 1, max 4). Она ездит в 13–40 тыс. единиц от
   игрока (дальше всех прогонов — 13390), P102_CopsTick ни разу не выставил «видит» (P95_SndReady = 0) → P95_SndTrigger нарушения не
   засчитывает: Felony 0, «Last observed felony» нет, хотя были столкновения и скорость (spd до 286). По коду это поведение оригинала
   (нарушение засчитывается, только если коп видит). Снимка с полицейской машиной нет. Не проверено: погоня, рост Felony.
4. **Пешеходы — почему не видны**: модель рисуется — с RE_PEDNEAR=1500 пешеход перед машиной виден (out/native_v2.10_ped_debug.png,
   отладочная расстановка). Причина невидимости на обычном прогоне — расстояния, а не рендер: точки появления — пустые клетки на кольце
   23 клетки × 1500 = 34500 от игрока (P94_BuildDirTab 00490591 — сверено с out/Game_decomp.c), удаление дальше 40500, а P113_PartDraw
   рисует только ближе 15001 (0x3a99). В сценарии v2.09 (поворот направо) машина уезжала от пешеходов: минимум 17,6 тыс., ни одного
   вызова ближе 15001. С поворотом налево (`1000:0x2c:25`) пешеход подходит до 8 тыс., проходит все проверки (351 отрисовка), но машина
   упирается в парапет набережной и пешеход оказывается вне кадра — на снимке без отладки пешехода нет. Исправлять в коде нечего (как
   в оригинале); не проверено, так ли далеко появляются пешеходы в оригинальной игре.
5. **Мягкий ограничитель микса** (plat_dsmix.c): голоса суммируются во float, до 0.7 без изменений, выше — tanh-колено
   y = 0.7 + 0.3·tanh((x − 0.7)/0.3), вывод ×32760. WAV сценария v2.09 (out/native_v2.10.wav, 39,7 с): пик 32024, отсчётов в насыщении
   0 (в v2.09 — 32768 и 62), RMS езды 9314. Тест snd_test: +1.0 → 30000..32766, ниже 0.7 — без изменений, монотонность, |y| ≤ 1.

Не сделано: гудок (не слышно), камеры `2`/J/K/L, круиз, F-клавиши — не проверены; Felony/погоня; пешеход на снимке без отладки;
CD-музыка; Доплер.

## Исправлено в v2.09 (звук DirectSound → SDL, пешеходы)

Сценарий тот же, что в v2.08, плюс запись микса: `RE_FIXED_DT=1 RE_WAV_OUT=out.wav RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,700:0x28:1000,1000:0x2d:25"`.
Новые переключатели: `RE_WAV_OUT=файл.wav` — микс 44100 Гц стерео S16 пишется в WAV по часам plat_time_ms на каждом plat_flip
(устройство SDL_audio тогда не открывается; без переменной — SDL_audio, при отсутствии устройства звук молча выключен);
`RE_SND_LOG=1` — журнал Play/Stop буферов и счётчик активных раз в 50 кадров; `RE_PEDDBG=1` — состояние пешеходов раз в 100 тактов.

1. **DirectSound в игре — собственный микшер** (platform/sdl/plat_dsmix.c, вызывается из plat_dd.c только при g_game_present; тесты —
   прежние учётные заглушки). Буферы: первичный (Play/SetFormat — без действия), вторичные (PCM 8/16 бит, 1/2 канала, частота из
   WAVEFORMATEX, Lock — вся память буфера), DuplicateSoundBuffer делит PCM (счётчик ссылок), SetVolume (сотые дБ), SetFrequency
   (0 — исходная), SetCurrentPosition, Play с циклом (флаг 1), Stop, GetStatus (PLAYING | LOOPING). 3D: слушатель (позиция,
   ориентация front/top, факторы), IDirectSound3DBuffer (позиция, режимы NORMAL / HEADRELATIVE / DISABLE): ослабление DS3D
   min/(min + rolloff·(d − min)), MinDistance 1, панорама по оси right = top × front. Доплер и EAX не моделируются (QuerySupport в игре
   отдаёт 0 — EAX выключен). Release объектов DS — через plat_dd_release по метке объекта.
2. **«Error while loading sample» — причина**: SDL-заглушка Lock отдавала буфер 64 КБ и отказывала при большем размере → P148_Fill
   падал → P148_BufFromWav = NULL → P140_SndLoadWav = −1 (например, сэмплы двигателя по 101052 байта). Теперь Lock — память буфера;
   в debug.log прогона сообщения нет.
3. **Флаги сэмплов /LOOP и /2D не доходили до голоса**: P140_BankLine пишет флаги в P48_Samples 00bdc886 (объект образа данных, v2.03),
   а P109_SndPlay читает байт +6 записи P68_Samps 00bdc880 — это был отдельный native-объект → все звуки без цикла и всегда 3D
   (двигатель замолкал через 4,6 с). P68_Samps теперь тоже в образе (переопределение после блока генератора в ported68.h).
4. **0048beee — параметры слушателя** (метка у Ghidra, вне functions.csv; адрес в таблице драйвера 00bdcb1c, P140_SndInit зовёт с 0.15f):
   по ассемблеру SetDistanceFactor(f), SetDopplerFactor(1.0), SetRolloffFactor(0x3995cbec ≈ 2.857e-4) — новая P148_ListenerParams
   (game/ported148.c, re_fn через k_fns game/reptr.c; в hook адрес не хукается) и plat_ds_listener_set_factor (sdl; win32 — vtable
   0x2c/0x30/0x3c).
5. **Пешеходы** (частицы A_00C56780, 64 × 0xb4, «Number of pedestrians active»): включены (P106_PartOn = 1, лимит P60_PartLimit = 32,
   точки появления P102_DustN 8–16), но жил один. Причина — псевдонимы: ported6.c (PoolAlloc0051210C), ported60.c (P60_SpawnParticle),
   ported70/71/73.c не включали ported43.h/ported7.h и работали с native-объектами P43_FreeCnt/P43_FreeList/A_00C56780, а остальные —
   с объектами образа данных (счётчик занятых слотов не рос, слоты не освобождались). Теперь заголовки включены: 12–16 пешеходов
   активны (типы 1 и 3), ближайший — в 17–30 тыс. единиц от машины; на снимках прогона их не видно — видимость не проверена.

WAV прогона (out/native_v2.09.wav, 39,7 с, RMS по секундам — out/native_v2.09_wav_rms.txt): 0–17,5 с (заставки) — тишина (музыка
фронтенда в оригинале — CD-audio, не эмулируется); меню 17,5–25,8 с — щелчки пунктов (сэмпл 1624/1400 байт, 2D) RMS 2167, пик 31231;
езда 26–39,7 с — непрерывный двигатель и шумы (8 циклических голосов, 101052/27020/43400 байт…) RMS 9318, пик 32768 (62 отсчёта в
насыщении — сумма голосов без ограничителя). Снимок out/native_v2.09.png (кадр 1500); с исправлением пешеходов кадр отличается от прогона без него (появление пешеходов зовёт Rand_004D9078 и сдвигает общую последовательность); позиции машины не сверялись.

Не сделано: CD-музыка (в SDL нет привода; честно без неё), Esc/пауза-меню, тормоз/ручник (клавиши не искались), Доплер, видимость пешеходов.

## Исправлено в v2.08 (по порядку, в каком мешало)

Город — режим **Take A Ride** (свободная езда, без интервью). Сценарий (с RE_FIXED_DT=1 — воспроизводимо):
`RE_FIXED_DT=1 RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,700:0x28:1000,1000:0x2d:25" work/run_game.sh 1700 out.png`
(главное меню: LEFT ×3 — Undercover → High Scores → Options → Take A Ride; RETURN — «Choose your city:» Miami; RETURN — Day/Night,
RETURN — загрузка; газ ' с кадра 700, руль X 25 кадров с 1000). Скрипт прогона с журналами — work/fxrun.sh.

1. **Таблица команд MScript 00563980 (P42_Cmds) в игре была пустым native-объектом** (`GAME_VAR_DEF(..., 0x00000000)`, заполнял только
   selftest) → «FAILED: CompileMissionScript - Unrecognised command, Line: 10» (StopPlayer) в Scripts\Missions\Mission46.dms (Take a Ride,
   Miami): скрипт миссии не загружался — LoadMap "Miami_01.lev"/EventScript "Miami_19.des" не выполнялись, машина стояла в (0, 162, 0)
   у края карты, в небе — чёрная полоса. Теперь p42_cmd_t/p42_cmdtab_t в списке проверенных структур tools/gen_gvar_img.py (char[0x100] +
   4 × int32) — таблица живёт в образе данных Game.exe (152 команды: CHECKPOINT, MISSIONEND, SET, …). Результат: «LoadMission Complete»,
   старт игрока (−255, 163, 418712) в парковке у берега, «Motion capture has been initialised» (пешеходы в Take a Ride не отключаются),
   HUD Damage/Felony, карта-радар.
2. **0051755e (текст с тенью) — V-заглушка при готовом переносе** P70_ShadowText (490 «not ported» за прогон): связано в
   platform/native/links.c (`P56_DrawText` → P70_ShadowText, строка через re_addr) — спидометр P62_SpeedText виден (правый нижний угол).
3. **Детерминизм: RE_FIXED_DT=1** (platform/sdl/plat_sys.c, plat_snd.c, plat_di.c). Источник расхождений: P21_FrameTicks (такт логики
   20 мс от plat_time_ms = SDL_GetTicks — при медленном кадре 1..10 тактов логики на кадр, число зависит от скорости Mesa), таймеры
   P25_TimerStart на SDL_AddTimer (поток; счётчик 005d577c 00408710 — ожидание заставок и меню), srand(timeGetTime()) в SetDirectorMode,
   P26_RandomFx (биты времени). Режим: виртуальные часы — +1 мс на каждый plat_time_ms, опрос ввода (GetDeviceState) и цикл сообщений,
   не меньше кадр·20 мс на каждом plat_flip, plat_sleep_ms только сдвигает часы; таймеры срабатывают в основном потоке по этим часам.
   Ожидание заставки P126_ShowBmpFade крутит `while (wait > 005d577c && P48_AnyKey() == 0)` при P31_Active = 0 (без вызова platform) —
   в P48_AnyKey добавлен plat_vt_poll() (win32 — пустая функция, hook не меняется). Проверено: два прогона сценария выше (1600 кадров) —
   строки [car] совпадают, PNG побайтно (md5 373d88cf…); без RE_FIXED_DT два прогона расходятся уже на кадре ≈1000 (pos 5 / 0, 3975 / 2546).
   Побочно: прогон в 2–3 раза быстрее (нет ожидания реального времени). Позиции кадров RE_KEYS для меню те же.
4. Отладка: RE_WATCHDOG без ASan печатает стек glibc backtrace (platform/native/main.c).

Город (out/native_v2.08.png, кадр 1100): машина на улице у дамбы (−1879, 205, 402298 по [car]; клетка 209,406; блоки карты в слотах
P87_SlotLumpA = −1 45 −1 52), спидометр «5», Damage/Felony, радар (Washington/Collins Av). out/native_v2.08_drive.png (кадр 1700, 600 кадров
газа после первого снимка): бульвар с пальмами, фонарями и встречным трафиком (до 32 машин в P142_CarsStep), машина (−45879, 160, 400032),
клетка 197,403, слоты блоков **44 45 51 52** (блоки 44 и 51 подгружены по ходу — стриминг работает). Без скрипта миссии (до п. 1) — та же
езда по Майами от (0, 162, 0): к кадру 2900 блоки 31 → 32 (клетки 209 → 224).

Не исправлено: пешеходы на улицах не замечены (модели находятся, не проверено, спавнятся ли — P103_MissionModels/P106_PartOn);
в Undercover (уровень интервью) моделей пешеходов нет («Could not find required models») — не сверено с оригиналом; единица скорости
у спидометра пустая (P62_Unit); «Error while loading sample»; звук (DirectSound → SDL) не подключён.

## Исправлено в v2.07 (по порядку, в каком мешало)

1. **Столкновения со стенами — модели в P129 читались через re_ptr.** P129_ObjBoxes (00500937) и model() в ported129.c брали модель
   объекта `re_ptr(P79_ModelTab[mi])` и список коробок `re_ptr(m + 0x34)`; в native это ссылки арены карты (P79_PTR, база D_00c98ed0),
   re_ptr давал NULL → ни одной коробки (RE_COLDBG: «objs 6 boxes 0»), машина проходила сквозь стену гаража и уезжала вверх
   (y 163 → −589) в пустоту. Теперь P79_PTR (в hook база 0 — то же, что раньше). После: «boxes 4–5», машина упирается в стену
   (позиция −5542 162 −22694 при газе и руле вправо, кадры 750–1300). Стриминг клеток при этом в порядке: P87_SlotLumpA = 10 9 6 5,
   клетка 117,112 → 118,110 внутри блока 5 (сетка 240×240, блок 60).
2. **Пол и стены у камеры — отсечение по ближней плоскости** (game/ported85.c, только игра). С v2.05 треугольник с вершиной ближе z = 1
   пропускался целиком (D3D-наборы с отсечением 00436ab0../00446e8a.. не перенесены) — у камеры чёрные дыры в полу (правый нижний угол
   кадра при повороте). Теперь P85_Project помечает такие вершины oow = P85_OOW_NEAR (1e−30, u·oow восстановим), P85_PutVtx запоминает
   координаты камеры, P85_CallRaster режет треугольник по z = 1 (Сазерленд–Ходжмен, 1–2 треугольника; u/v с перспективой, цвет/ooz/a линейно;
   RV восстанавливается для второго треугольника четырёхугольника). Отступление native, в оригинале — свой набор обработчиков.
3. **Колёса** рисовались и раньше (P136_DrawWheels → P86_TexQuad, CLEANWHEEL 0x41ac, 96 вершин за кадр), но протектор — цвет записи 0
   (чёрный по данным модели) на тёмном полу, а колпаки видны только сбоку; с п. 2 колёса и колпак видны на повороте (out/native_v2.07.png).
   Альфа-тест колёс сверен с 0041dd37/0041ddc5: ALPHATESTENABLE = 1, ALPHAFUNC = D3DCMP_LESS (2), ALPHAREF 0x82 — у страниц ARGB1555
   непрозрачные тексели с альфой 0, так что тест проходит.
4. **EVENTSCRIPT «(null)»**: строку пишут P99_VarSetStr (P138_LoadMission, поле +0x24 записи через re_wr_ptr) и P59_VarSetString (в native —
   P59_VarStr); P136_CompileEvents читал только второе. Теперь читает оба: «Scripts\Events\LEVEL4.DES» (IVIEW, такого файла нет;
   P28_EventCount = 0 — выход без загрузки, как в оригинале).

Отладка (только native): `RE_COLDBG=N` (клетка/объекты/коробки машины 0 в P129_CarObjects), `RE_COLDBG2=1` (коробки объектов),
`RE_WHEELDBG=1`, `RE_MDLDBG=<ссылка модели hex>` (записи модели, обработчики, освещение), `RE_ATDBG=1` (состояние draw_prim с альфа-тестом
LESS, форматы текстур), `RE_ZDBG=1` (z/rhw draw_prim).

Не исправлено: звук удара по объекту ищет модель в таблице .data 00572b40 по адресу Game.exe (в native — ссылка арены, совпадений нет →
звук по умолчанию); пешеходы («Could not find required models»); «Error while loading sample»; запуск недетерминирован (время кадра).

## Исправлено в v2.06 (по порядку, в каком мешало)

Диагностика: `RE_CARDBG=N` — раз в N вызовов строка [car] (P142_CarsStep: число машин, +0x13c, +0x110, позиция +0x18..0x20,
скорость +0x40.., газ +0xf8, руль +0xfc, +0x10c) и [carin] (P107_CarInput: биты клавиш, газ модели, множитель 00b87e1c);
`RE_CARTEX=1` — страница/слот записей кузова в P84_DrawCar; `RE_TEXDUMP=каталог` — каждая загрузка GL-текстуры в PNG;
`RE_CARSKIP=маска` (1 тень, 2 пятна фар, 4 колёса, 8 дым, 16 задние огни) в P137_DrawCar; `RE_NO8BIT=1` — эмуляция 8-битных текстур.

1. **Машина не ехала: газ = 0.** P107_CarInput (004ddaca) умножает газ игрока на 00b87e1c (DODGY_SPEED_FACTOR, переменная скрипта
   №65 таблицы 0056dc10, умолчание +0x2c = 0x1000), а SetTableValue_004F89B7 (P59_VarsInit → начальные значения переменных скрипта)
   в native ничего не писала — множитель 0, +0xf8 = 0. Теперь native пишет по re_ptr(P42_Vars[i].addr), если type ≠ 1
   (как 004f89b7: таблица 0056dc30/0056dc34). Это же заполняет и прочие переменные скрипта (GHOSTCARTYPE 00c81130, копы и т. д.).
   Результат (`RE_KEYS="300:RETURN,400:RETURN,600:0x28:300,650:0x2c:120"`): позиция машины (−10000, 163, −21504) → (−5596, 161,
   −19100) за ~150 кадров, руль +0xfc = −352 (Z, KeyCfg[4] = 0x2c), удар о стену гаража (скорость меняет знак), к кадру 900 —
   (−6165, 162, −22190); с X (0x2d) — (1096, −588, −30556), машина выезжает за пределы видимой геометрии гаража.
2. **Мусорная текстура кузова.** Страница игрока (слот 3, флаг 4 в P41_LoadTexPages) копируется P99_CarOpsReset (004c1b6c) в
   буфер вмятин 00d17ec8 из `P65_Texs[t].p` и загружается как ARGB1555 в слот 4. В Game.exe 01145a64 + t·0x10 — это поле
   P40_Slots[t].data (01145a60 + 4), в native — два объекта: P65_Texs оставался указателем на страницы FRONTEND.TSD (освобождены).
   Новая P65_TexPage(t) (native: re_ptr(P40_Slots[t].data), иначе P65_Texs[t].p; hook — P65_Texs[t].p) в P99_CarOpsReset,
   P104_CarDents (TEXP) и P122_IconCopy.
3. **Чёрный прямоугольник у левого заднего колеса** — дым выхлопа (P120_CarSmoke → P135_SmokeObj, флаг 0x4000: смешивание
   (4,4) — аддитивное). P23_SetBlendMode (0041d9d2) включает его только при бите 4 в 00a421dc (из DestBlendCaps D3DDEVICEDESC
   +0x78), а SDL-описание устройства игры отдавало нулевые dpcLineCaps/dpcTriCaps → смешивание выключено, квадрат рисовался
   непрозрачным тёмным. platform/sdl/plat_dd.c: Z/AlphaCmpCaps = 0xff, Src/DestBlendCaps = 0x1fff. Заодно видна тень машины.

Снимки: out/native_v2.06.png (кадр 700, гараж: машина с правильной текстурой, тень, дым выхлопа), out/native_v2.06_drive.png
(кадр 900 после 300 кадров газа с поворотом влево — машина у стены гаража), out/native_v2.06_drive2.png (поворот вправо 40 кадров —
машина выехала из гаража, вокруг нет геометрии: чёрный «пол» и небо).

## Исправлено в v2.05 (по порядку, в каком мешало)

Диагностика: `RE_GSTAT=N` — раз в N кадров счётчики (GameFrame, GameDraw, GlideSwap, draw_prim/вершин, записи P85_SkipRecord,
DrawMap/клетки/модели/обработчики записей, CarsStep, P100_RecKeys …; game/redbg.h, platform/sdl/plat_sys.c) и строка [gdraw]
(камера, машина 0, клетка, слоты блоков карты). RE_KEYS принимает «кадр:клавиша:кадров» (удержание одной клавиши), клавиша — имя или
код DIK («0x28»). Итог v2.04: кадр доходил до P131_GameFrame/P132_GameDraw/P47_GlideSwap каждый кадр, но draw_prim = 0.

1. **Таблицы обработчиков записей моделей P84_Handlers в игре были нулевыми** (в hook их дают указатели .data Game.exe 0055082c../
   00550cfc..; в native их заполнял только P85_RegisterNative в тестах) — P84 не рисовал ни одной записи. Теперь tools/gen_p84_handlers.py
   → game/p84_handlers.h (6 × 56 адресов, thunk-и раскрыты), P84_SelectTables в игре переводит их re_fn. Устройство D3D
   (00b1c0d8 = 1 → 00bdfa18 = 0) выбирает D3D-набор 0055082c, а он перенесён лишь частично (P115_*C — типы 0..3; обработчики
   00453759..004737c4 Ghidra не опознала как функции, в functions.csv их нет). Отступления native: неперенесённый D3D-обработчик →
   Glide-обработчик того же типа (P85/P86/P121 — рисуют через ячейки таблицы Glide, которые P151_InstallD3D направляет в D3D-эмуляцию;
   22 типа); наборы с отсечением (режим 1 — ближняя плоскость 00436ab0.., «другой» — дальняя 00446e8a.., тоже не опознаны) → обработчик
   режима 0 без отсечения (76); остальные 44 — P85_SkipRecord.
2. **Вершины за камерой** (обработчики без отсечения): P85_Project читал P12_00ba53a0[round(z)] при z < 1 (за границей таблицы) —
   полигоны рисовались мусором (чёрный потолок). Только в игре (re_ptr_has_image): z вне [1, 0xdbba) → oow = 0, P85_CallRaster такой
   треугольник пропускает. Тест города (RE_REAL_MAP) побайтно как до шага.
3. **P88_CellA/P88_CellB (p88_cell_t) — отдельные native-объекты**, а 00cff9ac/00cff9c6/00cff9c0 (P12_00cff9ac, P55_VarC6, P55_VarC0)
   уже жили в образе данных: P75_ResetObjs грузил блок карты под камерой в неверный слот, слот 3 (блок 5 под камерой) оставался пустым
   (головы клеток 0 → 8 узлов за кадр). p88_cell_t (9 × int32 + 4 байта) добавлена в список проверенных структур tools/gen_gvar_img.py
   и перенесена в образ.
4. **Дальность прорисовки 0**: work/run_game/config.dat (записан ещё в v2.00 из нулевого состояния) давал 01270c24 = 0 → P83_BoxVis
   отбрасывал всё. Файл отодвинут в work/config_v204_zero_far.dat; игра пишет новый config.dat из умолчаний (P13_Fn004064B4(1,1) →
   30000). Причина нулей в старом файле не выяснена (в v2.00 умолчания, видимо, не доходили до образа данных).

Результат: `RE_KEYS="300:RETURN,400:RETURN" work/run_game.sh 700 out/native_v2.05.png` — 3D-кадр Майами (первое «интервью» в подземном
гараже): небо, бетонный пол, колонны, потолок с лампами, таблички «TRUCKS or VANS», машина игрока; ≈10 draw_prim (пакеты по текстурам) и ≈1900 вершин за кадр.
Дефекты кадра: кузов машины — мусорная текстура (страница/палитра машины), чёрный прямоугольник у левого заднего колеса.
Машина не едет: `620:0x28:400` (апостроф — газ по умолчанию, P54_KeySrc[6] = DIK 0x28) даёт P100_RecKeys = 2 и P142_CarsStep
каждый кадр, но позиция P99_Cars[0] не меняется (out/native_v2.05_gas.png — тот же кадр). UP в раскладке Driver PC не газ.

## Исправлено в v2.04 (по порядку, в каком мешало)

1. **SIGSEGV в P40_DownloadPalette** (← P41_LoadTexPages ← P77_LoadLevel): таблица палитр слотов 00b31ee8 читалась как `uint32 P40_ListPtr`
   → указатель; с v2.03 этот псевдоним живёт в образе данных и был 0 при ненулевом счётчике (P58_Cnt4EFC03, тот же адрес +4).
   Теперь читается через P58_Tab4EFC03/P58_Cnt4EFC03 (p58_rec_t — та же 12-байтная запись в hook). Системно по пути загрузки
   страниц текстур: адреса буферов P41_Buf0/Buf1 и палитр 01252be0 — `re_addr` вместо `(int32_t)(uintptr_t)`; арены RAM-страниц
   P41_Arena (map.c) и FRONTEND.TSD (P137_LoadTsd) — `re_ptr_register_dyn` на весь размер (было усечение указателя / область 1 байт);
   `ADDR()` в ported11.h для native — `re_addr(&x)` (10 вызовов: FSIN.DAT, матрицы 011f4080/011effa0 …); строки HUD ported96/120 — re_addr.
2. **Заглушки с переносом, связаны вручную** (platform/native/links.c, аргументы-адреса → re_ptr; копии — только если участок целиком
   в одной области re_ptr, `re_span`): 004d303a ReadWholeFile (P53), 005283b5 Copy4 (P44), 004da76a QuatToMat (P94), 004ec8a8
   FindNameValue (P20), 0048db65 (memset, P14), 004248c6 TexSource (P54), 0052b650 (CRT memcpy), 0041f57d SetPalette (P32, было в stubs.c),
   005261ad EulerMatrix (P43), 00528461 Transpose3 (P44), 004b998b DebrisBounce (P101). Тест test_v204 (selftest).
3. **P101_SkyInit → P15_ScaleVertices SIGSEGV**: поля модели +0x20/+0x24 — ссылки арены карты (P79_PTR, смещение от D_00c98ed0), а не адреса
   re_ptr (в hook — одно и то же).
4. **«Could not find hubcap/clean player car model»**: 004ec8a8 возвращал значения из отдельного нулевого native-массива P20_Values;
   00cfe7a0 — это P79_ModelTab (образ данных). В native `P20_Values` — макрос над P79_ModelTab (ported20.h).
5. **Пути «SAVES\…»** (platform/sdl/plat_sys.c): в игре (`plat_fs_mkdirs(1)` из main.c) запись в отсутствующий подкаталог создаёт
   каталоги пути (work/run_game/SAVES/SCORES.HI); `g_remove` → `plat_remove_game` с тем же переводом пути. Вне игры (selftest) оставлено
   прежнее поведение (файл с «\» в имени в каталоге теста): и создание каталога, и плоское имя «SAVES_SCORES.HI» ломают selftest
   (SIGSEGV позже в тестах, после test_p52; место не найдено — backtrace пуст). Удалены старые файлы с «\» в work/run_game, work/run,
   re/build-native; selftest/ctest создают «SAVES\SCORES.HI»/«Scripts\Waypoint.tmp» заново в work/run и re/build-native.
6. **Запись игры в input/**: work/run_game/Scripts был симлинком на input/…/Scripts — игра создала input/game/Data_Files/Scripts/Waypoint.tmp
   (файл удалён; оригинальные файлы не менялись). Теперь work/run_game/Scripts — каталог с симлинками Events/FlyBy/Missions.

Где останавливается теперь: `RE_CRASH_BT=1 RE_KEYS="300:RETURN,400:RETURN" work/run_game.sh 1500` — New Game → MLADDER → P136_GameLoop →
P145_LevelLoad (уровень Miami, «Interview 1, Training 0, mode 2») загружается полностью, игра крутит кадры до 1500 без падений и без
«not ported» в журнале, но **экран чёрный** (work/shot_v204.png; out/native_v2.04.png не создан — игрового кадра нет).
Журнал: «Could not find required models. Pedestrians have been disabled.», «Attempting to compile event script "Scripts\Events\(null)"»
(EVENTSCRIPT = NULL — вероятно, ещё один псевдоним адреса), «Error while loading sample».

## Блокеры в порядке, в каком они мешают запуску

-9. **v2.12**: без отладки патруль к игроку не подходит (Felony 0) — нужен сценарий с нарушением при копе рядом; миссия 1
   («Get to the bank.») загружается, прохождение не проверено; звук автоответчика (ANS001.WAV) без аудиоустройства не прослушан;
   интервью без пропуска не пройдено; ночь/другие города не проверены.
-8. **v2.11**: Undercover — мотель (автоответчик) не реагирует на Enter, выбор миссии не достигнут; интервью без пропуска не пройдено;
   погоня после «видит» не начинается (слот копа переназначается), без отладки патруль не подходит к игроку; гудок почти не слышен (3D?).

-7. **v2.10: копы не видят игрока** (выше): Felony 0 — нужен сценарий, где патруль оказывается рядом (или сверка P99_CopsNear с оригиналом);
   пешеходы появляются в 34,5 тыс. и видны ближе 15 тыс. — проверить в оригинале; гудок не слышен (голос 2 — запущен ли цикл).
-6. **v2.08: город — Take A Ride** (выше): езда по улицам Майами, стриминг блоков, трафик, HUD. Дальше: пешеходы на улицах, звук,
   копы/погоня (Felony), Undercover — выезд из гаража по сценарию интервью, ночь/другие города (SF, LA, NY) не проверены.
-5. **v2.07: дальше гаража не проверено.** Стены держат, пол у камеры рисуется (выше); не проверены: выезд из гаража по сценарию
   интервью, город за блоками 5/6/9/10, пешеходы (модели не найдены), звук.
-4. ~~v2.06: после ~300 кадров езды машина уходит за геометрию гаража~~ — **исправлено в v2.07** (коробки объектов через P79_PTR). Было: (out/native_v2.06_drive2.png: y ≈ −600, вокруг пусто) —
   проверить столкновения с миром (P103_GroundAt/коробки моделей) и подгрузку клеток карты вокруг машины; колёса на снимках не
   видны (P136_DrawWheels вызывается — не проверено, рисует ли); EVENTSCRIPT «(null)», пешеходы, звук.
-3. ~~v2.05: машина игрока не едет~~ — **исправлено в v2.06** (газ — 00b87e1c, текстура — P65_TexPage, дым — caps смешивания). Было: Газ (DIK 0x28) доходит до P100_RecKeys = 2, P142_CarsStep вызывается каждый кадр, но позиция
   P99_Cars[0] неизменна — искать в P142_CarsStep/P142_WheelPhys/P46 (запись клавиш → управление машины, интеграция, псевдонимы
   полей машины 00d077c0/00d07888 в образе и native). Плюс текстура кузова (мусор), чёрный прямоугольник у колеса, неперенесённые
   D3D-обработчики записей 00453759..004737c4 и наборы с отсечением 00436ab0../00446e8a.. (сейчас подмена, см. v2.05),
   EVENTSCRIPT «(null)», пешеходы.
-2. ~~v2.04: после загрузки уровня экран чёрный~~ — **исправлено в v2.05** (выше). Было: Кадры идут (Flip), падений нет. Не выяснено: доходит ли кадр до P131_GameFrame/
   P132_GameDraw и сколько примитивов D3D рисуется после загрузки (RE_TRACE_DD ограничен первыми ~60 вызовами — нужен счётчик за кадр),
   идёт ли сначала флайбай/интервью (mode 2), не пуст ли EVENTSCRIPT («Scripts\Events\(null)»), пешеходы отключены (модели не найдены).
-1. ~~v2.03: загрузка уровня — SIGSEGV в P40_DownloadPalette~~ — **исправлено в v2.04** (выше).
00. **selftest и пути с подкаталогом**: если «SAVES\…» открывается как настоящий каталог или плоское имя, selftest падает SIGSEGV
   (тест после test_p52, файл повтора/рекордов читается иначе, чем при файле с «\» в имени). Найти и исправить, затем включить
   перевод путей и для selftest.
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
8. ~~**DirectInput → клавиатура SDL.**~~ **v2.03: клавиатура/геймпад/RE_KEYS сделаны** (выше); мышь и полный DIJOYSTATE — нет. Было: `plat_di_get_state` в SDL возвращает «ничего не нажато» (platform/sdl/plat_di.c); `P48_AnyKey`/меню не получают клавиш. Нужно: буфер 256 DIK из `SDL_GetKeyboardState` (таблица SDL_Scancode → DIK), события SDL в `plat_pump_messages`, мышь/джойстик — потом.
9. **DirectSound → SDL-микшер.** `plat_ds_*` (v1.93) — учётные заглушки (Lock в буфер 64 КБ), к `plat_snd_*` (SDL audio) не подключены: тишина. Нужно: вторичные буферы DS → голоса SDL-микшера (Play/Stop/SetVolume/SetFrequency/SetPan, 3D-слушатель — упрощённо).
10. **CD-аудио.** v2.22: сделано — эмуляция привода (plat_cdaudio.c): дорожки из файлов Music/ (wav/flac/ogg/mp3, cue+bin), без файлов — тишина; см. README «CD-музыка». До v2.22 — «InitCDAudio: Open CD device failed», музыки не было.
11. **FMV.** CoCreateInstance в SDL отказывает (E_NOTIMPL) — ролики пропускаются, как задумано (v1.95); не блокирует.
12. **Окно/GL.** Работает: SDL-окно 640×480, GL 4.5 core (Mesa), Flip → SwapWindow. Не проверены: оконный режим (Blt front←back, `plat_dd_blt_rect`), смена разрешения (`plat_window_move`), полноэкранный режим.

## Замечания по безопасности данных

- test_p77 (selftest) пишет и удаляет `Levels/t77.lev` через симлинк `work/run/Levels` → во время selftest временный файл появляется в `input/game/Data_Files/Levels` (оригинальные файлы не меняются; так было и до v2.00). Стоит перенести в отдельный каталог.
- С полным набором Data_Files в рабочем каталоге selftest падает в test_p52 (SIGSEGV) — поэтому игра запускается из `work/run_game`, selftest — из `work/run`.

## Исправлено в v2.14 (ввод macOS, нативное разрешение)

v2.14: ввод и нативное разрешение на macOS. Роман (Mac M1, v2.13): «Controls doesn't work on Mac». Проверено: игра (WinMain) и разбор событий SDL идут в главном потоке (отдельного игрового потока нет; таймер SDL_AddTimer только ставит флаг). Найдено и исправлено (что из этого было причиной на Mac — гипотеза, на Mac не воспроизводилось): (1) клавиши езды оригинала — ' / Z X Enter, стрелки в езде ничего не делали → в P36_GetPadButtons (только native) добавлены ↑ газ, ↓ тормоз, ←/→ руль, пробел — ручник (RE_KEYS: те же числа RE_CARDBG, что у ' / Z; меню не затронуты — они читают стрелки напрямую); (2) первые ~16 с (заставки/FMV) и во время загрузки игра не качает сообщения — теперь plat_flip разбирает события, если цикла сообщений не было (macOS: окно отвечает и получает фокус); (3) короткое нажатие (KEYDOWN+KEYUP между опросами) терялось — защёлка до первого GetDeviceState (так xdotool-нажатия под X11 и дошли); (4) активация: WM_ACTIVATEAPP 1 повторно, если окно с фокусом клавиатуры, а игра неактивна (P36_PollInput не читает клавиатуру при P31_Active=0); SDL_HINT_MAC_BACKGROUND_APP=0, SDL_RaiseWindow, свой Info.plist (NSPrincipalClass, NSHighResolutionCapable). RE_INPUTDBG=1 → driver_input.log (~/Library/Logs на macOS). Нативное разрешение: окно ALLOW_HIGHDPI|RESIZABLE, macOS — FULLSCREEN_DESKTOP по умолчанию, RE_WINDOWED/RE_FULLSCREEN/RE_RES, Cmd/Alt+Enter; кадр 640×480 вписывается в буфер (glViewport/scissor по SDL_GL_GetDrawableSize, pillarbox), 3D растеризуется в разрешении буфера; Hor+ (широкий FOV) не сделан. Снимки out/native_v2.14_1080p.png, out/native_v2.14_2560x1600.png, out/native_v2.14_menu_1080p.png. CI: ctest inputtest (главный поток, SDL_PushEvent → DIK), проверка Info.plist, inputtest внутри Driver.app.

## Исправлено в v2.15 (Hor+, произвольное соотношение сторон)

v2.15: произвольное соотношение сторон (Hor+). Как устроено в оригинале (сверено с out/Game_decomp.c): проекция x = X·(384/z) + 320, y = Y·(384/z) + 240 — фокус P43_ScaleA = 384 (вертикальный FOV 2·atan(240/384) ≈ 64°, горизонтальный 2·atan(320/384) ≈ 79.6°), центр P43_OffX/OffY = W/2, H/2 из P110_ViewSetup 00425b12 (W×H = P19_ScrW×ScrH, в native 640×480; 2D/HUD считаются в 640×480 и масштабируются ScrW/640); окно отсечения P110_Clip* 0..640×0..480 (grClipWindow → D3D-эмуляция 0041e08a P22_SetViewport → viewport/scissor GL); экранное отбрасывание треугольников — P85_EdgeReject (все x < 0, все y < 0, все x > P85_MaxX = 639, все y > 479; .data 00550820) и clip_reject (00447753/0043a5be); растеризатор D3D-эмуляции (0041e926/0041f825 → P23_ConvVertex → plat_draw_prim) сам не отсекает — это делает GPU. Пирамида P82_FrustumSetup3D 00427eea: боковые плоскости — нормаль (±cos θ, 0, −sin θ) из FSIN.DAT[475] (θ = 41.75°: геометрия 39.8° + запас ≈ 1.9°) через точки (±320, 0, 384), верх/низ — тот же угол, ближняя z = 50, дальняя — дальность прорисовки P11_01270c24 (P77_Plane); по ним P82_SphereVis3D/P83_BoxVis отсекают машины трафика, пешеходов, объекты. Клетки карты — P89_DrawMap 004ee8f4: FRUSTRUM.DAT = 256 секторов курса (P59_AngB/16) × строки 31×31 клеток {первая строка, число, {столбец, длина}}, клин ≈ ±45° с вершиной за камерой, плюс маска видимости P89_VisMask; зеркало заднего вида — свои маски P100_MirrorMask/P101_MirrorMaskR (FRUSTRUM ∩ круг дальности). Спрайты/огни/частицы проверяют экран 0..ScrW (P107_CarLight 004b5049, P108_Sprite 004b4b27, ported116 — следы/частицы). LOD и дальность зависят только от расстояния — не трогались. Сделано (только native, `#ifndef RE_HOOK_BUILD`; hook и 4:3 — побитно прежний код): game/aspect.c/.h — математика (S = round((480·аспект − 640)/2), угол боковых плоскостей atan((320+S)/384) + запас оригинала, число дополнительных секторов FRUSTRUM.DAT); игра по-прежнему считает в 640×480 с центром 320, 3D выходит в x ∈ [−S, 640+S]: P110_ViewSetup — окно отсечения шире на S, центр прежний; P82_FrustumSetup2D/3D — боковые плоскости по широкому углу через ±(320+S) (верх/низ — оригинал); P89_DrawMap — объединение секторов курса ±k (16:9 — 6, 21:9 — 12, 32:9 — 19) таблицы FRUSTRUM.DAT (файл не изменён, md5 3c76cb744abe31d5478004ab33005585), обход в порядке оригинала; P85_EdgeReject/clip_reject и экранные проверки спрайтов — по [−S, 639+S]; затемнение P114_CamFadeFrame — на всю ширину. Бэкенд plat_render.c: логический кадр (640+2S)×480, сдвиг x на +S в шейдере (uShift), RE_ASPECT=auto (по окну, по умолчанию) | 4:3 (оригинал, кадр с полосами как v2.14) | W:H (кадр этого аспекта, лишнее — полосы). Уже 4:3 (портрет 1080×1920 и т. п.) — S = 0, letterbox: кадр 4:3 по ширине с полосами сверху/снизу (Vert- не делали: высота 480 зашита в кинокамеру P114/P99_CamMax и 2D). 2D: меню/фронтенд и меню паузы — 640×480 по центру (pillarbox); HUD — якоря plat_hud_anchor: Damage/Felony (по центру полосы в левой трети) и часы при зеркале — к левому краю, радар/стрелки погони/спидометр (P119_Hud) и счётчики режимов P120_HudTimes — к правому, часы миссии/сообщения/зеркало — по центру; без растяжения. Мышь — в 640×480 меню. Проверено на Linux (Xvfb, llvmpipe), Take A Ride, RE_FIXED_DT=1, кадр 1100: out/native_v2.15_1920x1080.png (S 107), _2560x1600 (64), _3440x1440 (253), _5120x1440 (533), _1080x1920 (портрет, letterbox), сравнение с RE_ASPECT=4:3 тем же кадром _1920x1080_aspect4x3.png (центр совпадает, по краям — дополнительные здания/набережная, у краёв ничего не пропадает), меню и пауза 1080p — по центру. selftest test_aspect и inputtest — проекция/угол/секторы/вписывание для 4:3, 16:10, 16:9, 21:9, 32:9, портрета (без данных игры, синтетическая таблица секторов). Погоня на 21:9 (RE_COPNEAR=3000:150, кадр 1450): Felony 4095, 3–4 копа, патрульная машина у левого края расширенной области рисуется целиком — out/native_v2.15_chase_3440x1440.png.

Оставшиеся артефакты / не проверено (v2.15): появление трафика и пешеходов считается по расстоянию, не по углу — на 32:9 возможно «появление» у края (в проверенных кадрах не видно); сценарии кинокамеры (P114, полосы через ScrH), полноэкранная карта, Film Director, зеркало заднего вида (своя ширина 640·4/11, по центру), дождь/снег, блик солнца с LFB-проверкой перекрытия (P143, ветка Glide) в широком кадре не проверялись; в портретной ориентации кадр мелкий (letterbox 4:3 по ширине); P89_DrawMap в native по-прежнему читает P55_Frustum, а оригинал — указатель P66_Scene (для зеркала — маску с кругом дальности), как и до v2.15. Реальный Mac (Retina/полный экран) не проверялся.

## Исправлено в v2.16 (графика: MSAA/FXAA/мипмапы/анизотропия, driver.cfg)

v2.16: графика native. Роман: «Добавь поддержку сглаживания и прочих функций для улучшения графики». До шага кадр рисовался прямо в default framebuffer (билинейная без мипмапов, без сглаживания). После: кадр игры — во FBO (platform/sdl/plat_render.c): цель = буфер окна × render_scale (0.5–2.0), при MSAA — мультисэмпловый FBO (цвет/глубина renderbuffer, 2/4/8x, понижение до GL_MAX_SAMPLES) с resolve glBlitFramebuffer; на flip — пост-проход в окно (копия/билинейное уменьшение, FXAA консольного типа, sharpen, гамма/яркость); прямоугольники viewport/scissor — в пикселях цели. Alpha-to-coverage: альфа-тест без смешивания при MSAA → доля сэмплов по fwidth(альфы). Текстуры: страницы ARGB1555 игра рисует с ALPHAFUNC LESS (видно при альфе 0) и с обычной семантикой, поэтому обработанная копия (dilation цвета в прозрачные пиксели, мипмапы со взвешиванием альфой и сохранением покрытия chroma-key) строится лениво под семантику рисования (var[1] — видно при высокой альфе, var[2] — при низкой; без альфа-теста — исходная картинка, мипмапы простым средним); первая версия с одной копией дала чёрные дорогу/пальмы. Сэмплеры GL 3.3: 3D — nearest/linear/trilinear + анизотропия (GL_EXT/ARB_texture_filter_anisotropic, до 16x), 2D (без z-теста, z=0, rhw=1: HUD/меню/LFB) — sharp-bilinear/linear/nearest. vsync on/off/adaptive, fps_limit (не при RE_FIXED_DT), RE_FRAMESTAT. Настройки: platform/sdl/plat_gfx.c (без SDL/GL) — driver.cfg (RE_CFG, рядом с бинарником, ~/Library/Application Support/Driver, ~/.config/driver), RE_* поверх, пресеты enhanced (по умолчанию: MSAA 4x+A2C, aniso 16, trilinear, mip) / original (как v2.15); re/driver.cfg.example. selftest: test_gfx (разбор, clamp, env, dilation, мипмапы, покрытие). Offscreen-тесты (OSMesa) — пресет original.

Не проверено / ограничения (v2.16): только Linux Xvfb + Mesa llvmpipe (MSAA до 4x, 8x понижается; анизотропия 16x); реальный Mac и GPU не проверены; render_scale действует и на HUD (кадр один); 2D определяется эвристикой (без z-теста, z=0, rhw=1) — 3D без z-теста с такими вершинами получит фильтр HUD; мипмапы/dilation только у текстур степени двойки до 1024; alpha-to-coverage только без смешивания; vsync под Xvfb недоступен (лог), adaptive и fps_limit не проверены на реальном дисплее; на llvmpipe enhanced заметно дороже original (см. времена в README/отчёте).

## Исправлено в v2.17 (HD-текстуры: пак PNG вместо страниц 256×256)

v2.17: HD-текстуры (пак). Роман согласился на подмену текстур апскейлом. RE_TEXPACK=каталог или texpack = каталог в driver.cfg (env важнее): в P86_NativeCapture (re/game/ported86.c) для 16-битной (ARGB1555, не-pair) страницы, если есть <каталог>/<уровень без .lev>/pNNN.png (имя уровня — P77_CurLevelPath из P77_OpenLevel), PNG грузится stb_image (re/third_party/stb_image.h v2.30, public domain; STBI_ONLY_PNG, platform/sdl/plat_texpack.c — чистый C) и создаётся текстура 1024×1024 вместо 256×256 через тот же plat_tex_create/tex_upload (варианты альфа-теста, dilation, мипмапы, анизотропия v2.16). UV нормализованы по странице (u/256 в ported85.c), поэтому масштабировать не нужно. NNN = индекс i страницы в цикле P41_LoadTexPages (страницы в порядке файла, пара 8-битных = два индекса). Перед подменой картинка уменьшается до 256 и сверяется с исходной страницей (средняя |ΔRGB| по всем пикселям ≤ 24, расхождение альфы с битом 0x8000 ≤ 2%); не прошедшая сверку страница остаётся оригинальной, в лог пишется «отклонён». Итог уровня — «[texpack] загружено N страниц (каталог/уровень, отклонено K)». Без каталога — прежнее поведение. Только native (#ifndef RE_HOOK_BUILD). Найдено при проверке: в NY_01 у страниц с прозрачностью (0, 1, 127) бит 0x8000 стоит у тёмного фона, а у содержимого (деревья, знаки, фонари) бит 0 — какое состояние прозрачно, решает альфа-тест при рисовании; первый пак (dilation цвета «в прозрачные по биту» пиксели) затёр содержимое этих страниц (на снимке — чёрные трава/зонт/фонарь), а первая метрика сверки (только по пикселям с битом) этого не видела. Исправлено: метрика по всем пикселям, tools/texpack.py не заменяет цвет пикселей, страницы 0/1/127 пака перегенерированы. tools/texpack.py (argparse: .lev, выходной каталог, --model, --budget, --threads, --verify — сверка готового пака). Пак — производная данных игры, в репозиторий не входит. selftest: test_texpack (синтетический PNG: имя уровня, PNG через stb, неподходящие размеры, сверка, отклонение чужой и «затёртой» страницы, подмена 256→1024 в P86_NativeCapture под OSMesa, без каталога — как раньше).

Не проверено / ограничения (v2.17): пак есть только для NY_01 и только для 16-битных страниц — в NY здания в основном на 8-битных страницах (пары с палитрой, не апскейлятся) и на странице 127, поэтому город меняется мало (заметно на траве, зонтах, знаках, фонарях, машинах, если их страницы в паке); сверка не отличает почти одинаковые страницы (ошибка с соседней страницей бывает 3.6 при 3.1 со своей) — защищает от грубой путаницы, но не от перестановки похожих; PNG только квадратные 256..1024, степень двойки; память: страница 1024² ≈ 4 МБ (+мипмапы и варианты альфа-теста); загрузка PNG добавляет время загрузки уровня; проверено только под OSMesa (снимок 640×480) и Xvfb, на реальном GPU/Mac не проверено.

## Исправлено в v2.18 (HD-текстуры: 8-битные страницы × палитры, подмена в игре)

v2.18: HD-текстуры для 8-битных (палитровых) страниц и подмена в самой игре. Роман сказал «Да» на апскейл 8-битных страниц. Разбор (Game_decomp.c, P41/P40/P86/P149/P109/plat_dd): пара 8-битных страниц (флаг 0x10) — две текстуры Glide GR_TEXFMT_P_8 (fill_block формат 5); цвет даёт палитра, которую 00426580 (P12_Fn00426580) во время рисования загружает grTexDownloadTable (слот 0..49 таблицы 01252be0, 256 записей B,G,R,X из блока 0 файла уровня; текущий слот — g_01252b74; город — палитра 1, кадр 004188b0 ставит 4..7/1, небо и часть объектов — свои слоты). Палитра — не на модель/клетку, а глобальное состояние на момент рисования. Список возможных пар (страница → палитры) — LEVELS\<город>.D3D (P126_ReadMapPals → P58_Tab4EFC03; страница без записи — палитра 1): по нему D3D-эмуляция 0041d63b/004225eb заранее делает текстуру на пару. Прозрачного индекса нет: у P_8 альфа 255, chroma-key игра не включает, в 004229fa прозрачный индекс -1 (сравнение байта с 0xffffffff — выключено). Для NY_01: 56 8-битных страниц (28 пар файла), 30 палитр, 97 пар (страница, палитра) по newyork.d3d; в снимках проверки рендера (2 точки) рисуются 9 пар, все с палитрой 1 (лог RE_TEXLOG). НАЙДЕНО: native-игра рисует не через native_texsrc/P86 (это только проверка рендера test_real_level), а через D3D-эмуляцию Game.exe (P151: P86_TexSrc = 0041f76f): 8-битная страница — PAL8-поверхность аппаратного слота (P109_SlotUpload8, палитра — P32_SetPalette на все слоты), 16-битная — поверхность слота (P109_SlotUpload16); поэтому пак v2.17 в самой игре не применялся (по коду; проверено только в снимке OSMesa). Сделано: (1) пак 8-бит: <каталог>/<уровень>/pNNN_cKKKK.png, KKKK — номер слота палитры уровня (тот же, что в файле уровня, .D3D и коде игры), RGBA 1024×1024, альфа 255 (по индексу, nearest — при --transparent-index); каталог уровня ищется как есть/строчными/ПРОПИСНЫМИ (игра спрашивает MIAMI_01, файл miami_01.lev). (2) проверка рендера (ported86): текстура на пару (страница, палитра), палитра — текущая g_01252b74 (растеризатор перепривязывает текстуру на каждом треугольнике — палитра может смениться между ними); при загрузке — пары из списка .D3D и палитра по умолчанию, прочие при первом рисовании; смена содержимого слота палитры пересоздаёт её текстуры; до v2.18 все 8-битные страницы брались с палитрой 1 (без пака снимки побайтно как v2.17). HD пары сверяется с той же страницей в той же палитре (средняя |ΔRGB| ≤ 24 по всем пикселям, альфа ≤ 2%) — файл с чужой палитрой отклоняется. (3) игра: PAL8-поверхность слота помечается страницей (хэш 64 КБ данных); при установке текстуры поставщик ported86 по палитре поверхности находит слот палитры (сначала текущий g_01252b74) и отдаёт готовую GL-текстуру пары из пака (смена палитры не перезагружает картинку); 16-битная страница узнаётся по хэшу 128 КБ, картинка прикрепляется к поверхности (plat_dd_attach_hd) и при загрузке в GL сверяется с её памятью (re_texpack_merge, альфа — оригинала); эмулированные 8-битные текстуры (устройства без PAL8) — так же по паре из записи (страница, палитра). Unlock снимает картинку и пометку. GL-текстуры P86 в игре больше не создаются (они там не использовались). Без пака кадр игры (Take A Ride, кадр 900) побайтно как v2.17. Проверено в игре (Майами, тестовый пак nearest×4 с сеткой): подмена стен/потолка/неба/машины видна, цвета верные, 16 бит — 7 прикреплено, 4 загрузки, 0 отклонено; PAL8 — 2237 привязок текстур пар. Лог RE_TEXLOG=файл — пары (страница, палитра), треугольники и площадь на экране (проверка рендера). tools/texpack.py --pal8 (--d3d, --texlog — порядок по площади на экране, затем палитра 1, --pairs, --list, --verify — по всем пикселям после уменьшения до 256: своя пара ≤ 24, своя страница лучшая среди страниц в этой палитре, своя палитра лучшая среди палитр страницы). Пак NY_01 (Remacri, CPU): 8-битных пар 62 из 97 пар на момент коммита (все 9 пар, видимые в снимках, готовы; генерация продолжается). Снимок OSMesa NY_01 (enhanced) до/после — out/native_v2.18_before.png, _after.png, _crop.png: фасады и витрины чётче, цвета палитр совпадают, прозрачность не изменилась. selftest: test_texpack8 (синтетика: палитра B,G,R,X → RGBA, сверка с чужой палитрой, PNG пары, каталог без учёта регистра, подмена 256→1024 по текущей палитре, отклонение файла чужой палитры, смена содержимого палитры, склейка пути игры с альфой оригинала).

Не проверено / ограничения (v2.18): пак 8-бит есть только для NY_01 и не полный (62 из 97 пар на момент коммита (все 9 пар, видимые в снимках, готовы; генерация продолжается)); в игре проверен только Майами (Take A Ride) на тестовом паке без нейросети — NY в игре не запускался (режимы игры для NY не проверены); 16-битные страницы в игре подменяются только через P109_SlotUpload16 (другие пути загрузки 16 бит не подключены), PNG 16-битной страницы декодируется при каждой загрузке её в слот (возможны подтормаживания при частой смене страниц в 32 слотах); поверхность PAL8 с цветовым ключом идёт обычным путём; палитра узнаётся по точному совпадению записей с таблицей уровня (одинаковые слоты неразличимы — берётся текущий/первый); память: пара 1024² ≈ 4 МБ + мипмапы; сверка не отличает почти одинаковые страницы; проверено только под OSMesa/Xvfb, на реальном GPU/Mac не проверено.

## Исправлено в v2.19 (дальность прорисовки, draw_distance)

v2.19: дальность прорисовки (draw_distance). Роман: «надо увеличить дальность прорисовки». Разбор (Game_decomp.c): клетка карты P80_Cell = 3000; P21_GridRadius = 45000 / P80_Cell = 15 → окно обхода P89_DrawMap (004ee8f4) 31×31 клеток по FRUSTRUM.DAT (256 секторов курса, клин) и PVS P89_VisMask (004ef793) того же размера; дальняя плоскость P11_01270c24 = опция «дальность» 15000..45000 (шаг 3000, меню/клавиши 00575f4c, по умолчанию в config — 30000 в нашем прогоне), её копия Q01270C24 — отсечение полигонов 00501…/P102 по дальней плоскости, P77_Plane — дальняя плоскость P82_SphereVis3D/P83_BoxVis, трафик рисуется ближе P11 (00490bcb), детали машин (тень/фары/колёса) ближе 15000, дальше — низкополигональная модель (P137); таблица 1/z 00ba53a0 — 0xdbba = 56250 элементов (oow = k/z, z камеры индексом); стриминг — 4 слота блоков (2×2 по чётности, P87_LoadTile 004ed5f8, сосед подгружается за 20 клеток до края, P88_StreamTiles 004edaa2), блок Майами — 60 клеток (180000), в слотах обычно 2 блока; глубина D3D-эмуляции z = 1 − w·ZScale (w = oow, 1/z), 24 бит — от дальней плоскости не зависит; туман — функции Glide в D3D-обёртке Game.exe пустые (0041eb2e/35/3c), в D3D-версии тумана нет; LOD моделей зданий по расстоянию нет (режим модели — только по пересечению с плоскостями); небо — модели P106_SkyModels/фон кадра. Сделано (только native, #ifndef RE_HOOK_BUILD): driver.cfg draw_distance / RE_DRAW_DIST (1.0..4.0; enhanced 2.0, original 1.0); на время 3D-вида P132_GameDraw (после P133_CamUpdate, до блика солнца/зеркала/HUD) P11_01270c24 и Q01270C24 × m (значение опции, config и ползунок не меняются), re_dd_on; таблица 1/z — доступ через RE_OOW/RE_OOW_N (все места чтения): за 0xdbba — k/z (k = 0125f3e0), допустимый размер — far·1.25 только при m > 1; P89_DrawMap после ветки оригинала/Hor+ обходит квадрат радиуса R = ceil(far/3000)+1 (не больше round(15·m)+1) по расстоянию (ближние раньше, списки классов по 0x400 не вытесняют ближнее), пропуская клетки маски оригинала; внутри 31×31 — PVS оригинала, снаружи и в углах квадрата (за кругом 14.5) — конус: курс камеры по P59_AngB в осях FRUSTRUM.DAT (центроиды симметричных секторов 0 и 64), полуугол re_aspect_half_angle(S) + asin(1.5/d); FRUSTRUM.DAT не меняется (md5 3c76cb744abe31d5478004ab33005585 до/после); блок клетки — слот игры, если он там (P87_SlotLump), иначе кэш только для отрисовки: копия разбора 004ed5f8 из P80_LumpTab (уже в памяти) в свои буферы без дорожных данных ИИ и без записи в слоты, 16 блоков, до 2 за кадр, предзагрузка на 6 клеток дальше радиуса, сброс при смене уровня; порог деталей машины 15000 × m (P137, только во время 3D-вида). Дистанции ИИ/спавна/пешеходов (15000)/копов не менялись. selftest: test_drawdist (re_dd_selftest: радиусы, продолжение таблицы 1/z, порядок обхода, курс по осям синтетической таблицы, нет дыр на стыке 31×31 и конуса в угле обзора при 4:3/16:9/21:9 и клине «до квадрата»/«круг», позади камеры — нет; driver.cfg draw_distance). test_real_level: RE_REAL_DD=m (и своя таблица эйлеров — указатель из образа данных мог быть не нулём, падение). Проверка: Take A Ride Майами (work/fxrun_aspect.sh, 1920×1080, enhanced, RE_FIXED_DT, кадр 1000) при 1.0/2.0/3.0 → out/native_v2.19_dd1/_dd2/_dd3.png: машина выезжает к заливу, разница — на горизонте за водой (дальний берег, деревья, постройки при 3.0; кадры отличаются только полосой y 362–404), дыр и z-fighting нет; позиции машины RE_CARDBG при 1.0, 2.0 и 3.0 совпадают побайтно; [dd] при 3.0: far 90000 (опция игры 30000 × 3), R 31, ~640 клеток за окном, блоков из кэша — 4, «нет блока» — 0. Время кадра RE_FRAMESTAT (кадры 800–1000, Mesa llvmpipe, 2 ядра, параллельно шла генерация пака на CPU): 1.0 — 782 мс (медиана 796), 3.0 — 819 мс (846), прогоны 1.0 и 3.0 шли одновременно; 2.0 — 591 мс (603), шёл один — между собой сравнимы только 1.0 и 3.0 (~+5%). OSMesa (test_real_level, RE_REAL_MAP=1 RE_REAL_DD=m): NY_01 улица (far 45000) — 3252 → 22792 треугольников при 3.0, улица видна до схода, out/native_v2.19_ny01_dd1/_dd3/_cmp.png; Майами у старта (far 30000, курс 3072) — out/native_v2.19_miami_osmesa_dd123.png: при 1.0 горизонт пуст, при 2.0 — часть кварталов, при 3.0 — сплошная панорама (синий низ — в проверке рендера не рисуется вода/земля, так же при 1.0). md5 FRUSTRUM.DAT 3c76cb744abe31d5478004ab33005585 до/после.

Не проверено / ограничения (v2.19): тумана в D3D-версии нет — дальняя граница видна резким обрезом (как в оригинале, только дальше); кэш блоков — копии из файла уровня: разрушенные объекты дальнего блока, которого нет в слотах игры, видны целыми, пока блок не попадёт в слот; блоки разбираются по 2 за кадр — первые кадры после загрузки/телепорта дальние блоки могут появиться с задержкой; при 4.0 и большой опции дальности обход до 61 клетки — время кадра растёт; пешеходы рисуются ближе 15000, копы/трафик существуют только в радиусе спавна — дальше их нет (дистанции ИИ не менялись); проверено только под Xvfb/OSMesa (llvmpipe), на Mac — нет.

## Исправлено в v2.20 (кэш вершин, треугольники 0x38, небо)

v2.20: рендер — мигающие треугольники, полоса в небе, пропадающий асфальт. (1) Кэш вершин P85_VCache (p85_vtx, 32 байта): в оригинале модель рисуется одним набором обработчиков (режим 0 — проекция 00528ac8: x,y экранные, z/vx/vy — камера, oow; режимы с отсечением — 00528c91/0052859a: x,y,z — камера), поэтому одной метки кадра stamp достаточно; в native в наборы с отсечением подставлены обработчики режима 0 (P84_HandNoClip), и в одной модели запись с отсечением (P121_ClipTexQuad → prep_bias) и подставленная (P85_Prep, P115 prep) делили вершины — вторая принимала запись первой как готовую (координаты камеры как экранные, oow прошлого кадра): треугольники через весь экран, чёрные дыры дороги и неба. Исправлено (только native): метка формата в pad8 — P85_FMT_PROJ / P85_FMT_BIAS, P85_VC_VALID / P85_VC_FMT (ported85.h); запись чужого формата пересчитывается из вершин модели; записи P122 (quad_tail) / P138 (тень машины) — формат 0 (принимаются как есть). В hook-сборке макросы сводятся к прежней проверке stamp. (2) Новые обработчики записей модели 0x38 (текстурный треугольник): 00430b13 P121_TexTriFlat (цвет записи, без освещения; Ghidra функцией не опознала — по дизассемблеру) и 00439b42 P121_ClipTexTri (с отсечением ближней плоскостью, общий clip_poly с P121_ClipTexQuad: uv +0x14..+0x28, цвет +0x2c); до v2.20 вместо 00439b42 стоял обработчик без отсечения — пропуски у полигонов неба/земли, пересекающих ближнюю плоскость. fn_table и install.c (hook) дополнены. (3) Полоса в небе: P101_SkyInit (004ef3cd) масштабирует 4 модели неба ×1.7; в native ссылка модели — смещение в арене карты, и первая модель уровня (небо, P79_ModelTab[0]) лежит по смещению 0 — прежняя проверка «ссылка == 0 → пропуск» оставляла четверть купола в масштабе 1/1.7 (ближе и ниже остальных), на стыках — чёрная изогнутая полоса; теперь масштабируются все 4 (как в оригинале, безусловно), без арены (тесты) — выход. Отладка: RE_SHOT_EVERY=N [RE_SHOT_FROM=K] — серия снимков RE_SHOT_PNG_NNNNN.png (plat_sys.c). selftest: test_v220 (пересчёт записи чужого формата, кэш своего формата, формат 0; 00430b13 — вершины/uv/цвет/курсор; 00439b42 — треугольник целиком перед ближней плоскостью и с вершиной за ней — веер из двух; SkyInit масштабирует модель по смещению 0). Проверка: Take A Ride Майами до Marina (work/run_marina.sh, 1024×768, RE_FIXED_DT, серия с кадра 1400 через 25), v2.19 против v2.20: доля незакрашенных (r,g,b < 6) пикселей верхней половины кадра (work/blackfrac.py, out/native_v2.20_blackfrac.txt) в кадрах 1400–2100 ~5.5–7.3% → 0.00–0.94%; всплеск на кадре 1775 (11.82% → 5.47%) — тёмные витрины фасада справа (x 640–1024), не дыра. Снимки out/native_v2.20_before.png / _after.png и out/native_v2.20_marina_before.png / _marina_after.png: полоса неба исчезла; асфальт у Marina есть на обоих снимках — дефект асфальта (и мигающие треугольники) на этом маршруте не воспроизвёлся, исправление (1) подтверждено test_v220. Логика не изменилась: строки [car] RE_CARDBG=10 при RE_FIXED_DT, 2600 кадров, v2.19 и v2.20 совпадают побайтно (179 строк). md5 FRUSTRUM.DAT 3c76cb744abe31d5478004ab33005585 до/после.

Не проверено / ограничения (v2.20): на снимках «после» в небе остаётся тонкий светлый вертикальный шов (x ≈ 385–400 при 1024×768) — ЗАКРЫТО в v2.27 (расхождение v колец купола у четвертей, P101_SkyUvFix); мигающие треугольники и дыры асфальта на маршруте Marina не воспроизвелись ни в v2.19, ни в v2.20 (низ кадра ~0% чёрного в обоих) — исправление кэша вершин подтверждено только test_v220; новые обработчики 00430b13/00439b42 в hook-сборке (Game.exe под Windows) не запускались — только собраны. CI macOS на d8e2465: первая попытка — selftest FAIL без сообщения какой-либо проверки, повтор — успех (linux — успех); test_v220 оставлял курсор записей G2_011F4064 в освобождённой арене и не восстанавливал изменённые глобальные — исправлено следующим коммитом (сохранение/восстановление состояния); была ли это причина — не доказано.

## Исправлено в v2.27 (шов неба, варианты неба в HD-паке)

v2.27: небо — (1) тонкий косой шов купола (остался после v2.20, есть и в оригинале 1999 г.): купол неба — 4 модели-четверти (P79_ModelTab[0..3]), кольца вершин на одной высоте, но координата v текстуры на кольцах у четвертей в данных уровня расходится (Майами: кольцо 29° — v 50/47/48/48, кольцо 8° — 115/116/115/115), облака и градиент на стыках сдвинуты на 1–3 строки. Исправлено только в native и только в UV: P101_SkyUvFix (game/ported101.c, вызывается из P101_SkyInit после масштаба ×1.7) приводит v каждого кольца к медиане, если разброс 1..4 текселя; шапка купола (v ≤ 1.5), u, геометрия, логика и порядок рисования не меняются; незнакомый тип записи модели — без изменений; RE_SKYFIX=0 — выключить. (2) Варианты неба в HD-паке: оверлей пака — подкаталог (<пак>/<оверлей>/<уровень>/pNNN_cKKKK.png), его файлы ищутся раньше основного пака и проходят ту же сверку со страницей; выбор — RE_TEXPACK_SKY=<подкаталог или путь> («0» — выкл.) или первое слово файла <пак>/sky.txt (напр. sky_cc0). Пак r331/driver-texpack: sky_hd (перерисованное небо по оригиналу) — в каталогах уровней, sky_cc0 — небо из CC0-панорам Poly Haven. selftest: test_v220 (кольца к медиане, шапка/u не меняются, RE_SKYFIX=0, незнакомая запись), test_texpack8 (оверлей через sky.txt, приоритет, откат на основной пак, RE_TEXPACK_SKY=0). Логика не изменилась: 179 строк RE_CARDBG = v2.26; md5 FRUSTRUM.DAT не изменился.

Не проверено / ограничения (v2.27): исправление шва проверено снимками под Xvfb (llvmpipe) в Майами; в NY_01 v колец у всех четвертей уже совпадают (255/233/111) — исправление там ничего не меняет; Фриско и LA по данным моделей не разбирались. Hook-сборка (Game.exe под Windows) исправление не получает (#ifndef RE_HOOK_BUILD). Небо sky_cc0 — панорамы реального неба, по цвету отличается от оригинала (сверка пака допускает до 24 по |ΔRGB|).

## Исправлено в v2.31 (миссии-тараны: RE_AUTORAM)

v2.31: (1) Проверка RE_AUTORAM (v2.30, только native, отладка) на всех миссиях, проваленных в v2.30 с «цель потеряна»: с `RE_AUTORAM=200:20` (с кадра 200, перенос позади цели каждые 20 кадров) миссии 7 (Bust out Jean-Paul — MISSION COMPLETE), 12, 25, 28, 36, 41 засчитаны (e8 = 0, c4 = 0x8000); без RE_AUTORAM — цель потеряна (e8 = 3). Прогон миссии 7 на коде v2.30 до rebase (без коммитов bd978ad/ef75042) даёт тот же итог (кадр 1273) — успех даёт сама логика RE_AUTORAM v2.30 (запись v2.30 «в миссии 7 пока провал» относилась к более ранней рабочей копии); прогон повторяется побайтно по итогу. (2) Найден расщеплённый псевдоним образа данных 00d12408 (список объектов скрипта): 32-битный адрес головы пишет ported122 (команда 0x7a) в ячейку образа G00D12408, её через re_ptr читает ported133, а P98_ScriptRange (004f5012 — «You lost your target» по удалению), ported97 (два обхода) и ported112 (записи скрипта) обходят отдельный native-указатель P15_ListHead, который в native всегда NULL (журнал RE_AUTORAM: в миссии 7 через P15_ListHead — 0 узлов; в миссиях 39/40 через G00D12408 — 6 узлов). Следствие (вывод, не проверено прогоном исправления): в native проверка дальности 004f5012 не срабатывает, «цель потеряна» ставит только P133_TrafficTick (004967d2) в режиме погони — по удалению от машины в слоте 0x41; логика игры в v2.31 не менялась — исправление псевдонима (перевод P15_ListHead на ячейку образа, как в v2.21/v2.25) отложено, оно меняет поведение миссий и требует перепрогона кампании. (3) RE_AUTORAM: цель берётся как в 004f5012 — объект скрипта с порогом 00b87e60[k] и флагами 1|8 → узел списка 00d12408 (через ячейку образа) → позиция цели (+0x1c, float x/z); иначе — любой включённый объект с узлом в списке; иначе слот машин 0x41, как в v2.30 (`RE_AUTORAM_SLOT=1` — только слот); журнал раз в 500 кадров, если цели в списке нет (число узлов, пороги и флаги объектов). В проверенных миссиях цель-погоня в списке по этим признакам не находится (пороги стоят у объектов без флага 8), автопилот работает по слоту 0x41; миссии 39 (таран припаркованных машин) и 40 (Stop Granger's Gang) режима погони не включают — по-прежнему провал / нет итога.

Статус миссий (v2.31; как в v2.30, плюс RE_AUTORAM=200:20 для миссий с погоней/тараном). Провалы — цели-события (трюки, тайминг, таран без режима погони), не ошибки переноса:

| № (скрипт) | Город | Название | Статус (v2.31) |
|---|---|---|---|
| 1 | Майами | 1. Bank Job (Get to the bank) | успех — MISSION COMPLETE (v2.29, кампания) |
| 2 | Майами | 2a. Super Hot Car | успех (v2.29, подмена Take A Ride) |
| 3 | Майами | 2b. Ticco's Ride | успех — MISSION COMPLETE (v2.29, кампания) |
| 4, 401, 402 | Майами | 3a. Boat Chase | успех (v2.29, подмена) |
| 5, 53 | Майами | 3b. The Clean Up | успех (v2.29) |
| 6 | Майами | 4. Drive to Bar | успех (v2.29, подмена) |
| 7 | Майами | 5. Bust out Jean-Paul (ч. 1) | **успех с RE_AUTORAM=200:20** — MISSION COMPLETE (без него — цель потеряна, e8=3) |
| 54 | Майами | 5. Bust out Jean-Paul (ч. 2) | успех |
| 8 | Майами | 6a. Ram Raid Race | успех |
| 9 | Майами | 6b. Superfly Car Delivery | успех |
| 10 | Майами | 7a. Shipment's Coming In | успех (цепочка после 8) |
| 11 | Майами | 7b. Bait for a Trap | успех |
| 12 | Майами | Take out Di'Angio's Car | **успех с RE_AUTORAM** (без него — цель потеряна, e8=3) |
| 13 | Майами | 8. Chase on the Monorail | успех |
| 14 | Фриско | 9. Casino Job | провал (e8=2): причина не разобрана (цель-событие или время) |
| 15, 151 | Фриско | 10a. Golden Gate Briefcase | успех |
| 16, 161 | Фриско | 10b. Guns in the Trunk | успех |
| 17 | Фриско | 10c. Shopping Mall Getaway | успех |
| 18 | Фриско | 11a. Taxi Ride | провал (e8=1): шкала «Freaked!» — пассажира пугают трюками, автопилот не умеет |
| 20 | Фриско | 12a. Cosy to the Chopper | успех (сейв перед подмиссией, tools/driver_save.py) |
| 19 | Фриско | 11b. In the Pickup | успех |
| 21 | Фриско | 12b. Pick Us Up | успех (цепочка после 19) |
| 22, 221, 222, 223 | Фриско | 13. Rescue Me Man | успех (все 4 части, сейвы tools/driver_save.py) |
| 23 | Фриско | 14a. Setup | успех |
| 24 | Фриско | 15b. Hyde Street Pick Up | провал (e8=2), и с задержкой автопереноса (RE_AUTOTARGET=200:900); причина не разобрана |
| 25 | Фриско | 16. Stop Slater | **успех с RE_AUTORAM** (без него — цель потеряна, e8=3) |
| 26 | Лос-Анджелес | 17a. Steal a Cop Car | успех |
| 28 | Лос-Анджелес | 18a. Stop Duval | **успех с RE_AUTORAM** (без него — цель потеряна, e8=3) |
| 27 | Лос-Анджелес | 17b. Lucky to the Doc | успех |
| 29 | Лос-Анджелес | 18b. Maya | успех |
| 30, 301 | Лос-Анджелес | 19. Assassination | успех |
| 31 | Лос-Анджелес | 20a. Recapture Lucky | успех |
| 32 | Лос-Анджелес | 20b. Beverly Hills Getaway | успех |
| 33 | Лос-Анджелес | 20c. Santa Monica Timing Run | успех |
| 34, 341, 342 | Нью-Йорк | 21a. Grand Central Station Switch | успех (цепочка из 3) |
| 35 | Нью-Йорк | 21b. Real Beat-up Car Delivery | успех |
| 36 | Нью-Йорк | 22a. Cause an Accident | **успех с RE_AUTORAM** (без него — цель потеряна, e8=3) |
| 37 | Нью-Йорк | 22b. Rescue Us | успех |
| 38 | Нью-Йорк | 23a. Steal a Taxi | успех |
| 40 | Нью-Йорк | 24a. Stop Granger's Gang | итога нет за ~8200 кадров миссии (и с RE_AUTORAM: режима погони нет, цели-события) |
| 39 | Нью-Йорк | 23b. Trash Granger's Wheels | провал (e8=2): таран припаркованных машин — режима погони нет, RE_AUTORAM не включается |
| 41 | Нью-Йорк | 24b. Chase One of Granger's Boys | **успех с RE_AUTORAM** (без него — цель потеряна, e8=3) |
| 42 | Нью-Йорк | 25a. Crosstown Record | успех |
| 43 | Нью-Йорк | 25b. Save Ali | успех |
| 44 | Нью-Йорк | 26. President Run | успех |

Итог v2.31: из 45 миссий успех — 40 (из них 6 — с RE_AUTORAM: 7, 12, 25, 28, 36, 41), провал — 4 (14, 18, 24, 39), итога нет — 1 (40). Прогоны — work/v230/r/ram*.log (qr.sh, sv.sh). Логика игры не менялась: RE_CARDBG 179 строк = v2.27, md5 FRUSTRUM.DAT 3c76cb744abe31d5478004ab33005585.

## Исправлено в v2.30 (сейвы из сети, все миссии кампании)

v2.30: прогон всех миссий кампании Undercover (Майами, Фриско, Лос-Анджелес, Нью-Йорк) из сохранений, без прохождения с начала. (1) Сохранения: формат SAVES/GAMEn.BIN разобран (64 байта, little-endian; запись 00405d60, проверка 00405cb4/00405e79, загрузка 0040c480): +0x00 u32 подпись 0x57231356, +0x04 u32 сумма байтов 0x38 байт данных, +0x08 имя[16], +0x18 уровень (00575ef0, 1 Майами … 4 Нью-Йорк), +0x1c номер последней выполненной записи лестницы DATA/MLADDER.DML (продолжение с +1), +0x20 город (01271050: 0 Miami, 1 Frisco, 2 LA, 3 NY), +0x24 биты TRIGGER (для IF n), +0x28 машина CARSELECT, +0x2c..0x3f нули. Сейвы Complete Version с playground.ru (8 шт., Фриско/LA/NY) native читает без изменений: Load Saved Game → мотель → Get A New Job → миссия. tools/driver_save.py — dump (разбор и сумма), ladder (номера записей лестницы), make (сейв перед любой записью/миссией, напр. для Майами 7–13 и подмиссий). Сами сейвы в репозиторий не входят. (2) Отладка (только native, по умолчанию выключено): `RE_AUTOCONT="кадр:клавиша,…"` — после успешного итога миссии нажать клавиши (кадры от итога; Continue → следующая подмиссия или мотель), `RE_CHAIN=N` — так пройти N итогов подряд (RE_END_EXIT срабатывает на провале или на N-м итоге); plat_keys_push (platform/sdl/plat_di.c) — нажатие относительно текущего кадра. `RE_AUTORAM=N[:P[:B]]` — экспериментальный автопилот погони/тарана (P142_CarsStep): в режиме погони (00b87eb0/00b87eac, цель в слоте машин 0x41) руление к цели штатными клавишами и каждые P кадров перенос в B единиц позади цели с её курсом и скоростью; тонкая настройка RE_AUTORAM_SIGN/_FAR/_VK/_CLOSE/_Y (проверка по миссиям — v2.31: 7, 12, 25, 28, 36, 41 — успех). (3) Журнал итога RE_MISSDBG исправлен: 00c810e8 = 0 — успех, 1/2 — провал, 3 — цель потеряна (004f5012/004d4f5c); в журнале v2.29 любое значение ≠ 2 считалось успехом (на итогах v2.29 не сказалось — там все e8 = 0).

Статус миссий (v2.30, Linux под Xvfb, preset original, RE_FIXED_DT=1, без звукового устройства; везде RE_AUTOTARGET — езда к цели заменена переносом машины к включённой цели скрипта, засчитывает цель сама игра). «Провал» здесь — не ошибка переноса: это цели-события (погоня, таран, трюки, тайминг), которые перенос не выполняет и которые нужно проезжать самому; скрипт миссии во всех прогонах идёт до итога без аварий (0 SIGSEGV).

| № (скрипт) | Город | Название | Статус (v2.30) |
|---|---|---|---|
| 1 | Майами | 1. Bank Job (Get to the bank) | успех — MISSION COMPLETE (v2.29, кампания) |
| 2 | Майами | 2a. Super Hot Car | успех (v2.29, подмена Take A Ride) |
| 3 | Майами | 2b. Ticco's Ride | успех — MISSION COMPLETE (v2.29, кампания) |
| 4, 401, 402 | Майами | 3a. Boat Chase | успех (v2.29, подмена) |
| 5, 53 | Майами | 3b. The Clean Up | успех (v2.29) |
| 6 | Майами | 4. Drive to Bar | успех (v2.29, подмена) |
| 7 | Майами | 5. Bust out Jean-Paul (ч. 1) | провал — цель потеряна (e8=3): погоня/таран, автопилот не таранит; с RE_AUTORAM — провал (e8=2) |
| 54 | Майами | 5. Bust out Jean-Paul (ч. 2) | успех |
| 8 | Майами | 6a. Ram Raid Race | успех |
| 9 | Майами | 6b. Superfly Car Delivery | успех |
| 10 | Майами | 7a. Shipment's Coming In | успех (цепочка после 8) |
| 11 | Майами | 7b. Bait for a Trap | успех |
| 12 | Майами | Take out Di'Angio's Car | провал — цель потеряна (e8=3): таран |
| 13 | Майами | 8. Chase on the Monorail | успех |
| 14 | Фриско | 9. Casino Job | провал (e8=2): причина не разобрана (цель-событие или время) |
| 15, 151 | Фриско | 10a. Golden Gate Briefcase | успех |
| 16, 161 | Фриско | 10b. Guns in the Trunk | успех |
| 17 | Фриско | 10c. Shopping Mall Getaway | успех |
| 18 | Фриско | 11a. Taxi Ride | провал (e8=1): шкала «Freaked!» — пассажира пугают трюками, автопилот не умеет |
| 20 | Фриско | 12a. Cosy to the Chopper | успех (сейв перед подмиссией, tools/driver_save.py) |
| 19 | Фриско | 11b. In the Pickup | успех |
| 21 | Фриско | 12b. Pick Us Up | успех (цепочка после 19) |
| 22, 221, 222, 223 | Фриско | 13. Rescue Me Man | успех (все 4 части, сейвы tools/driver_save.py) |
| 23 | Фриско | 14a. Setup | успех |
| 24 | Фриско | 15b. Hyde Street Pick Up | провал (e8=2), и с задержкой автопереноса (RE_AUTOTARGET=200:900); причина не разобрана |
| 25 | Фриско | 16. Stop Slater | провал — цель потеряна (e8=3): таран |
| 26 | Лос-Анджелес | 17a. Steal a Cop Car | успех |
| 28 | Лос-Анджелес | 18a. Stop Duval | провал — цель потеряна (e8=3): таран |
| 27 | Лос-Анджелес | 17b. Lucky to the Doc | успех |
| 29 | Лос-Анджелес | 18b. Maya | успех |
| 30, 301 | Лос-Анджелес | 19. Assassination | успех |
| 31 | Лос-Анджелес | 20a. Recapture Lucky | успех |
| 32 | Лос-Анджелес | 20b. Beverly Hills Getaway | успех |
| 33 | Лос-Анджелес | 20c. Santa Monica Timing Run | успех |
| 34, 341, 342 | Нью-Йорк | 21a. Grand Central Station Switch | успех (цепочка из 3) |
| 35 | Нью-Йорк | 21b. Real Beat-up Car Delivery | успех |
| 36 | Нью-Йорк | 22a. Cause an Accident | провал — цель потеряна (e8=3): таран |
| 37 | Нью-Йорк | 22b. Rescue Us | успех |
| 38 | Нью-Йорк | 23a. Steal a Taxi | успех |
| 40 | Нью-Йорк | 24a. Stop Granger's Gang | итога нет за ~8900 кадров (цели-события, таран) |
| 39 | Нью-Йорк | 23b. Trash Granger's Wheels | провал (e8=2): таран |
| 41 | Нью-Йорк | 24b. Chase One of Granger's Boys | провал — цель потеряна (e8=3): погоня |
| 42 | Нью-Йорк | 25a. Crosstown Record | успех |
| 43 | Нью-Йорк | 25b. Save Ali | успех |
| 44 | Нью-Йорк | 26. President Run | успех |

Итог: из 45 миссий (записей лестницы с MISSION/SUBMISSION, подмиссии в одной строке) успех — 34, провал — 10 (все — цели-события: таран, погоня, трюки, тайминг; 7, 12, 14, 18, 24, 25, 28, 36, 39, 41), итога нет — 1 (40). Прогоны: work/v230 (sv.sh, q.sh, res.sh; кадры r/). Контактный лист: out/native_v2.30_missions.png.

Не проверено / ограничения (v2.30): прохождение настоящей ездой (без RE_AUTOTARGET) и миссии с таранами/погонями — только у игрока; переход между городами (конец лестницы города → SETCITY) прогоном с начала не проверялся — города запускались из сейвов; экран MISSION COMPLETE/мотель после каждой миссии не снимался (признак — итог скрипта 00c810e8 и бит 0x8000 в 00c810c4). Логика Take A Ride (RE_CARDBG) не меняется: 179 строк = v2.27; md5 FRUSTRUM.DAT 3c76cb744abe31d5478004ab33005585.

## Исправлено в v2.29 (прохождение кампании: MISSION COMPLETE после интервью, отладка миссий)

v2.29: (1) После интервью в гараже не наступал MISSION COMPLETE (v2.25 — не проверено). Причина (только native, без аудиоустройства — песочница/CI/машина без звука): 004d6209 (P42_ActionBound) ждёт конца речи (слот 0xf), а без SDL-устройства буферы DirectSound эмулятора plat_dsmix никогда не доигрывали (GetStatus — PLAYING навсегда) → отсчёт конца миссии 00c81100 бесконечно перезапускался на 0x32. Исправлено в platform/sdl/plat_snd.c: «пустое устройство» — микс по часам plat_time_ms на каждом plat_flip без вывода (как RE_WAV_OUT, но без файла). Интервью → MISSION COMPLETE → Continue → мотель проверено прогоном. selftest: test_v229 (plat_snd_null_for_test — буфер доигрывает по часам). (2) Отладка прохождения (только native, по умолчанию выключено): `RE_MISSDBG=1` — журнал команд скрипта миссии `[mis]` (номер, код, первый аргумент, 00c810c4) и отсчёта конца `[end]` (00c81100 раз в 25 кадров, ожидание речи) с итогом «успех»/«ПРОВАЛ» (00c810e8 = 2 — провал); `RE_AUTOTARGET=N[:D]` — с кадра N каждой миссии машина игрока переносится к включённой цели скрипта (00c80ce0 + i·0x34: флаги +0x10 = 1, не событие 8), если цель включена ≥ D кадров (150) и игрок дальше трети радиуса; засчитывает цель сама игра; `RE_END_EXIT=N` — выход через N кадров окна после итога (снимок экрана итога). После любого отладочного переноса (RE_TELEPORT, RE_AUTOTARGET) блоки карты вокруг нового места перезагружаются как командой скрипта 0x8e/004ee129 (P88_TeleportReload) — раньше машина висела над чёрной пустотой. Логика Take A Ride (RE_CARDBG) не меняется: 179 строк = v2.27.

Статус миссий (v2.29, Linux под Xvfb, RE_FIXED_DT=1, без звукового устройства; везде с RE_AUTOTARGET — езда к цели заменена переносом, погони/тараны/тайминги вождением не проверялись):

| Миссия (файл / надпись) | Как проверено | Статус |
|---|---|---|
| Интервью в гараже | кампания New Game, RE_IVPICK | MISSION COMPLETE → мотель |
| 1 — «Get to the bank» | кампания | MISSION COMPLETE (out/native_v2.29_complete.png), мотель (out/native_v2.29_motel.png) |
| 2 — Ticco's Ride («Pick up Ticco») | кампания, выбор в мотеле | MISSION COMPLETE |
| 3 — The Clean Up («Pick up the car») | кампания | успех по скрипту (c4 = 0x8000, отсчёт конца дошёл); экран итога закрыт диалогом «Are you sure?» от клавиш сценария |
| mission2.dms («Take it to the breakers») | подмена Take A Ride | успех (c4 = 0x8000) |
| mission4.dms («Go meet them») | подмена Take A Ride | успех |
| mission401.dms («Make the exchange») | подмена Take A Ride | успех |
| mission402.dms («Chase the boat», ожидание «Too early») | подмена Take A Ride | успех (кадр 5942) |
| mission5.dms («Pick up the car») | подмена Take A Ride | успех |
| mission53.dms («Get the hell out of there!») | подмена Take A Ride | успех |
| mission6.dms («Go and meet Rufus») | подмена Take A Ride | успех |
| mission54.dms («Get Jean-Paul out of there») | подмена Take A Ride | успех |
| mission7.dms (ChaseHQ, 12 таранов) и 8–13 | — | не проверены (цели-события RE_AUTOTARGET не переносит) |

«Подмена Take A Ride» — каталог данных с missionN.dms вместо mission46.dms (work/v229/mkgd.sh, queue.sh); экран итога в этом режиме — GAME OVER (меню паузы выбирается по типу игры: режим 0 — MISSION COMPLETE, 1..7 — GAME OVER/таблица рекордов, 0050ee00), признак успеха — бит 0x8000 в 00c810c4 (провал — 0xff0).

Не проверено / ограничения (v2.29): прохождение без RE_AUTOTARGET (настоящей ездой) и со звуковым устройством — только у Романа; миссии других городов и цели-события (погони, тараны) не проверялись; «пустое устройство» включается только когда SDL не открыл звук.

## Исправлено в v2.21 (трафик по встречке, кампания без заданий)

v2.21: (1) Трафик по встречке на односторонних улицах. Таблицы узлов дороги в .bss Game.exe — 00bf1c40 (запись 0x42), 00c12c60 (0x14), 00c39dc0 (0x24) — рассчитаны на 0x800 узлов (00c39dc0 + 0x800·0x24 = 00c4bdc0 < следующего глобала 00c4bdc4); фактическое число — P11_00b5a8e8 (Майами — 356). Native-типы были на 64 узла, и проверки границ отрезали узлы ≥ 64: P73_RoadSides (0051bf82) не ставил флаг одностороннего движения (+0x3d) узлам ≥ 64, P75_TrafficPos при cls ≥ 64 выходил (позиция оставалась от прошлого вызова), P59 читал узел только при node < 64. Исправлено: P59_NODES_MAX 0x800 (ported59.h), p59_tab_c39dc0_t / p59_tab_bf1c48_t / p17_map_t на 0x800 узлов, пределы в ported73/75/59 сняты; индекс типа ≥ 9 в таблице масок 00575e34 в P73 берётся из образа данных (re_ptr), как в оригинале (без образа — маска 0). Замер предыдущего прохода (журнал машин трафика; «до» — эмуляция прежнего предела 64): доля выборок «против одностороннего» 96/406 → 0/482 (out/native_v2.21_traffic_before.png / _after.png — графики, не кадры игры).
(2) Кампания (Undercover) без заданий: P15_State (00b87e30), P15_Flags9 (00d04a50) и 8 переменных P16_* (P16_IdleMode 00c810c4, P16_FlagA 00b5a778, P16_FlagB 00b87ee4, P16_IdleCounter 00d0778c, P16_FlagC 00bdfa58, P16_FlagD 00bdfa44, P16_IdleArg1 00c810e8, P16_IdleArg2 00c81100) были отдельными native-переменными вместо ячеек образа данных: tools/gen_gvar_img.py не разбирает обёртки P15_VAR/P16_VAR. Ladder писал D_00b87e30 = 4 (интервью), а P56_HudTick/P145_LevelLoad читали отдельный P15_State — интервью в гараже не шло (нет секундомера и листа заданий). Переведены на re_gvar (ported15.h/.c, ported16.h/.c).
(3) Отладка: RE_TELEPORT="кадр:x:z;кадр:x:z…" (до 16 точек; P142_CarsStep; кадр — P62_Frame, счётчик кадров уровня/миссии, а не кадров окна) — машина игрока переносится в (x, z), скорости обнуляются, высота и курс прежние; для проверки прохождения миссий.
selftest: test_v221 — размеры таблиц узлов ≥ 0x800; с временным образом данных &P15_State == &D_00b87e30, &P16_IdleMode == &P14_00c810c4, &P15_Flags9 — ячейка 00d04a50 образа, запись D_00b87e30 видна через P15_State.

Проверка кампании (RE_FIXED_DT=1, 640×480, RE_SKIP_INTERVIEW=1; RE_KEYS="300:RETURN,400:RETURN,1700:RETURN,2100:RETURN,2300:RIGHT,2400:RETURN,2600:RIGHT,2700:RETURN"): Undercover → (интервью пропущено) → мотель → миссия 1 Майами («Get to the bank.», Mission1.dms) загружается, машина на месте парковки (284813, −50302). С RE_TELEPORT="300:-16066:-42824;5000:129666:415995" (банк, затем гараж «lock up» из Mission1.dms): у банка — «Too Early. Come back later.» и обратный отсчёт с 80 с; при входе в окно 15 с цель засчитана (сцену MCS не разглядывал), затем «Get to the lock up.», Felony, секундомер вперёд; после переноса к гаражу — экран «MISSION COMPLETE» (Film Director / Quick Replay / Save Replay / Continue / Exit) около кадра окна 9500 — миссия 1 проходится до конца. Город после телепорта не подгружается сразу (чёрная земля вокруг машины на снимках — стриминг блоков рассчитан на езду, не на перенос). Переход к миссии 2 подтверждён вторым прогоном (после коммита 75af5d1; +RE_KEYS "9600:DOWN,9700:DOWN,9800:DOWN,9900:RETURN,10400:RETURN,10800:RETURN,11000:RIGHT,11100:RETURN,11300:RIGHT,11400:RETURN", 12600 кадров): «MISSION COMPLETE» (кадр 9500, out/native_v2.21_campaign.png) → Continue → мотель, автоответчик «Get A New Job» (кадр 10250, out/native_v2.21_campaign_motel.png) → миссия 2 Майами, ночь, «Pick up Ticco.» с отсчётом 01:25 (кадр 12250, out/native_v2.21_campaign_m2.png). На снимке миссии 2 машина не на старте Mission2.dms: RE_TELEPORT сработал повторно (P62_Frame с началом миссии снова 300) и перенёс её к банку — прохождение миссии 2 не проверялось. Интервью без RE_SKIP_INTERVIEW не пройдено (вождение по заданиям интервью сценарием не воспроизводилось).

Детерминизм и RE_CARDBG (Take A Ride, сценарий work/v221/run.sh по умолчанию, RE_CARDBG=10, 2600 кадров): два прогона v2.21 совпадают побайтно (179 строк [car] и строки [carin]). Против v2.20 (сборка из a29acba): траектория машины игрока не расходится — все 179 строк совпадают, кроме поля n (число обработанных машин: 16 → 19 уже во второй строке, 128 строк из 179 отличаются только им) — другой трафик (узлы ≥ 64 теперь участвуют в появлении), на этом маршруте он машину игрока не задел.

Расщеплённые псевдонимы образа данных. Предыдущий проход v2.21 нашёл 31 адрес образа данных (00546000..00d41000), у которого одно из имён — отдельный native-объект, а не ячейка образа; исправлено 10 (P15_State, P15_Flags9 и 8 P16_*, выше). Его полный список не сохранился; повторная проверка после исправления — tools/find_split_alias.py (запуск из re/game; табличные обёртки MENUGFX/MENUTAB/CARTAB/SLOTTAB/NODETAB — один объект, не считаются) — даёт 19 адресов:
- скалярные (кандидаты на перевод в образ): 005fe9bc P15_MenuMode ↔ G6_005FE9BC; 00c56764 G6_00C56764 ↔ P43_FreeCnt; 00c594a0 P12_00c594a0 / G6_00C594A0 ↔ P43_FreeList; 00c5678c P12_00c5678c / G6_00C5678C (оба вне образа; в v1.48 P12_00c5678c описан как макрос над A_00C56780 — проверить); 00b203a0 G2_00B203A0 ↔ P27_MemTab;
- родные указатели (в образе — 32-битный адрес; нужен перевод на адреса + re_ptr, как в v1.42): 00562d7c P87_ListPtr ↔ P75_Ptr562D7C; 005fe9b0 P15_MenuText ↔ P58_S5FE9B0; 005fe9b8 P15_MenuItems / UiPtr005FE9B8 ↔ P58_S5FE9B8; 00b1c280 P56_EulerTab ↔ UiVar00B1C280; 00b31ee8 P58_Tab4EFC03 ↔ P40_ListPtr; 00bdc28c P44_MatPtr ↔ P11_00bdc28c; 00d0448c P15_Limits ↔ P55_Paper1; 00d12408 P15_ListHead ↔ G00D12408; 00d12414 P10_ScriptPtr ↔ S_00D12414; 00d1240c P10_ScriptCtx / S_00D1240C; 00d12410 P15_ListCur / S_00D12410;
- два native-объекта, ни одного в образе: 00a42160 P31_DDObj2 / P33_Device; 00b1c83c P38_Mms2 / P50_FmvFlag; 00bdfbc4 P46_MapBufC / P58_BlkBuf.
Названные в отчёте предыдущего прохода P34_Keys и D_00b1c0d4 в текущем дереве уже идут через re_gvar (ported34.h, ported4.h) — этой проверкой как расщеплённые не находятся.

v2.22: CD-музыка. «InitCDAudio ~140 раз за 300 кадров» (выше) больше не повторяется: эмулируемый привод открывается с первого раза. Как устроено и таблица дорожек — README «CD-музыка» и PLATFORM_PLAN (v2.22). Переключатели: RE_MUSIC=off (как до v2.22), RE_MUSIC_DIR, RE_MUSIC_STUB=tone, RE_MUSIC_STUB_LEN, RE_MUSIC_VOL, RE_CD_TRACKS; лог [cd] в stderr. Открытое: (1) конец дорожки игра считает P21_AddMsf(TMSF-позиция, MSF-длина) — байт дорожки + минуты длины; как это понимал настоящий mcicda (до конца дорожки или дальше по диску) — не проверено, эмуляция играет только запрошенную дорожку; (2) уведомления MCI_NOTIFY_SUPERSEDED/ABORTED не посылаются (P31_WndProc реагирует только на 1 и 8); (3) поток MP3 при старте дорожки считает длину проходом по файлу (dr_mp3) — один раз при сканировании каталога.

v2.23: набор обработчиков с ближней плоскостью (режим 1) — типы 0..3 (00459b21, 0045a3f6, 0045b1c1, 0045bbd6: плоские/гуро треугольник и четырёхугольник без текстуры) по-прежнему не перенесены; подставленные обработчики режима 0 P115_*C теперь отсекают по z = 1 (P85_CallRasterWith), как P85_CallRaster для остальных подстановок — вершина за камерой больше не уходит в растеризатор (серый полигон по небу). Остаётся: тип 21 и другие текстурные типы режима 1 (004417b5 …) — подстановка P86_* с отсечением в растеризации (v2.07), не оригинальный обработчик; телепорт RE_TELEPORT оставляет блоки без части объектов пола (чёрная земля вокруг машины после переноса; при езде — норма).

v2.24: тёмный экран без меню при звуке (Роман: macOS M1 и Linux, на реальных GPU) — в песочнице не воспроизведён (llvmpipe, softpipe, sdl2-compat/SDL3, Xvfb+openbox, снимки экрана X в реальном времени — меню видно). Причина не подтверждена; вероятные места — путь показа v2.16 (MSAA-FBO → resolve → пост-проход в буфер окна 0) на конкретном драйвере, либо окно/активация на реальном рабочем столе. Добавлены: всегда включённый журнал driver_gfx.log (GL_VENDOR/RENDERER/VERSION, пределы, окно/буфер, ошибки GL/FBO/шейдеров, WM_ACTIVATEAPP, откаты; RE_GFXDBG=1 — подробно), проверка показа с откатом на прямой рендер (и в окно из полного экрана), `fbo = off`/RE_FBO=0, `preset = safe`, RE_FULLSCREEN=desktop|exclusive, Cmd/Alt+Shift+Enter. Открыто: журнал с машины Романа; если тёмный экран остаётся и в safe/RE_FBO=0 с RE_WINDOWED=1 — причина не в FBO (смотреть строки «активация игры» и «буфер окна»). Отладка: RE_GFXTEST=nopost|fboerr — имитация поломки пост-прохода / FBO для проверки отката.

v2.25: интервью в гараже. Исправлено: 00d0448c P15_Limits ↔ P55_Paper1 — в native P15_RaiseLimits читает 32-битный адрес значка LINE из ячейки образа и переводит его re_ptr (NULL — пропуск); native-объект P15_Limits остаётся только для hook-сборки (tools/find_split_alias.py по-прежнему видит его по объявлению, но в native он не читается). P15_Vals9 (00d044a0) — ячейка образа. Расщеплённых псевдонимов осталось 18 (список выше без 00d0448c). Связаны P56_Fn4E5284 → P94_FadeStep (секундомер интервью) и Call0052A910 (sprintf). Отладка: RE_IVDBG=N, RE_IVPICK="кадр:задание;…", RE_TELEPORT — до 64 точек. selftest: test_v225; временный образ данных в test_v221/test_v225 теперь полного размера (00d41000 байт, как reptr.c) — меньший буфер при re_gvar_img_size = 00d41000 пускал адреса выше его конца (авария selftest). Клавиши интервью: Burnout — `\`, ручник — Enter, тормоз — `/` или ↓. Логика Take A Ride (RE_CARDBG) не изменилась.
Проверка v2.25 (RE_FIXED_DT=1, 640×480, work/v225/iv.sh): Undercover New Game (RE_KEYS 300:RETURN,400:RETURN) → интервью; RE_IVPICK засчитал все 9 заданий на кадрах уровня 200–280 без аварии (до v2.25 — SIGSEGV на первом). Дальше до кадра окна 4800 экрана «MISSION COMPLETE» нет: машина в гараже едет сама (похоже на повтор/демо интервью, HUD секундомера и «бумаги» остаётся), нажатия DOWN×3/RETURN после кадра 2700 его не меняют; переход Continue → мотель → миссия 1 после интервью НЕ проверен. Открыто: что игра ждёт после состояния 2 (девятое задание) — смотреть P59_S4654/P14_00d118a8 и вызывающий 004e5284 после засчёта.
RE_CARDBG (Take A Ride, сценарий work/v221/run.sh, RE_FIXED_DT=1, 2600 кадров): при RE_CARDBG=1 все 1790 строк [car] и строки [carin] совпадают с v2.24 (сборка a856d1a) побайтно; каждая 10-я — те же 179 строк, что эталон v2.23/v2.24 (RE_CARDBG=10).

v2.26: кадр заезда маленьким прямоугольником 4:3 по центру окна (Роман, macOS Retina, окно ~2000×1500 пикселей, кадр ~1300×975; меню — нормально). Воспроизведено под Xvfb частично: при режиме игры 1024×768 (config.dat, выбор 4) в окне 16:10 кадр заезда — 4:3 с полосами (Hor+ не применялся: логический кадр 1024×768 после P55_SetScreen/MoveWindow, а Hor+ — только для 640×480; work/v226, out/native_v2.26_before.png / _after.png, поля по снимку экрана X: L66 R67 → 0). Исправлено (native): режим игры → кадр 640×480 (game_res = native, по умолчанию), заполнение проверено снимками окна X (import -window): окно 16:10 и 4:3, RE_FAKE_HIDPI=2 (буфер = 2× окна), ресайз посреди заезда 4:3 → 16:9, полный экран под openbox и переключение окно ↔ полный экран, RE_FBO=0, preset original и safe, режимы 1024×768 и 1600×1200 — кадр 100 % окна; меню — 4:3 по центру, как задумано (v2.15).
Не подтверждено: точная причина у Романа — режим игры даёт полосы только по бокам/сверху-снизу, а не со всех сторон; кадр ~1300×975 в окне ~2000×1500 похож на прежний размер буфера (640×480 точек ×2 = 1280×960) после увеличения окна, т. е. поверхность GL не обновилась под новый размер окна (macOS показывает её по центру). На это — SDL_GL_MakeCurrent при смене буфера и журнал (плотность, прямоугольник кадра, «ВНИМАНИЕ: поля со всех сторон»); на реальном Mac не проверено. Под Xvfb без оконного менеджера SDL считает окно полноэкранным (буфер 960×540), а окно X остаётся 640×480 — кадр обрезан; с openbox — норма (особенность Xvfb, не исправлялась).
RE_CARDBG (Take A Ride, work/v226/run.sh, RE_FIXED_DT=1, 2600 кадров, RE_CARDBG=10, config.dat с режимом 640×480): 179 строк [car] совпадают с v2.25 (work/v225/r/new_s10.car) побайтно; md5 FRUSTRUM.DAT 3c76cb744abe31d5478004ab33005585.
