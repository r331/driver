# Native-сборка как игра: разрывы (v2.00, 2026-10-16)

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
| 8 | `P140_Frontend`: `P140_KeysLoad`, `P126_ShowBmpFade` COPYRIGHT.BMP, GT.BMP (по 5 с по таймеру) | проходит, кадры показываются (Flip → plat_flip), **картинка чёрная** |
| 9 | дальше в P140_Frontend (REFLECT, главное меню 0054cc90) | через 40 с стоит в ожидании (стек в vdso — функция не установлена; см. блокер 1/4) |
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

## Блокеры в порядке, в каком они мешают запуску

1. **Текстуры/2D через DirectDraw-эмуляцию — чёрный экран.** Цепочка заставки: `P12_Fn0040DA56` → `P75_BmpToPage` (страница 005d7e40) → `P40_UploadSlot` → `Call0042486B` (grTexDownloadMipMap эмуляции) → эмулируемые текстуры `P149_EmulNew`/`P105_EmulSurface` → `plat_dd_create_surface`/`plat_dd_lock`. В SDL поверхности — учётные заглушки без памяти пикселей, Lock не даёт буфер, загрузки в GL (`plat_tex_create`) нет. Нужно: поверхность SDL с реальной памятью (w×h×bpp), Lock/Unlock → `plat_tex_create`/обновление GL-текстуры, `plat_set_texture` → `plat_tex_bind`; палитры (`plat_dd_create_palette`/`plat_tex_palette_changed`) для 8-бит.
2. **64-битные указатели через int32.** 35 мест `(int32_t|uint32_t)(uintptr_t)&…` в re/game (напр. `P40_UploadSlot`: `info = (uint32_t)(uintptr_t)&P40_Blocks[b].info[0]`, аргумент `Call0042486B`), плюс таблица Glide с типами `FnIntI` для аргументов-указателей. Нужно: аудит ячеек Glide с аргументом-указателем (grTexDownloadMipMap, grTexSource, grDrawPolygonVertexList, grLfbLock, grSstQueryHardware …) → `intptr_t`/re_addr+re_ptr; поля структур — re_addr.
3. **Несколько native-объектов на один адрес Game.exe.** 310 адресов с более чем одним `GAME_VAR_DEF` (D_/G/P…): запись в один псевдоним не видна читателю другого (так ломались 00b1c0d4 и 005d577c). Нужно: сводить в один объект (макрос-псевдоним), начиная с путей загрузки/меню; инструмент поиска — work/own191.py.
4. **Начальные значения .data.** `GAME_VAR_DEF` в native без инициализатора: 371 скалярный объект (из 2567) с ненулевым значением в .data Game.exe — кандидаты (часть уже ставит re_init_consts/P56_InitConsts). Нужно: генератор инициализаторов из Game.exe .data (как tools/gen_*_data.py) с проверкой против re_init_consts.
5. **Шпионы selftest в игровом бинарнике.** tests/selftest.c линкуется в driver; 41 имя из `--skip` (work/skip_v196.txt) в игре — шпионы, а не перенос (исправлено 2: P74_Fn41CE90, P74_Fn424B70). Нужно: каждый шпион вне selftest передаёт вызов настоящей функции (по образцу v2.00) либо вынести тесты из игрового бинарника.
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
