# Аудит мёртвого кода: что оставлено на месте

Ветка `cleanup/dead-code` убрала то, что точно не используется (21 функция без ссылок, артефакты прогонов
`re/debug.log` / `re/render_test.png`, дубли `rd32/wr32/rdf/iabs/fround` → `re/game/memrw.h`, поля `snd_t.x/y/z`).
Здесь — то, что **похоже** на мёртвое, но удалять без решения нельзя или незачем. Каждый пункт — с причиной.

Проверка ветки: нативная сборка + `ctest` (selftest, inputtest), `build.sh hook`, детерминированный прогон
(`RE_FIXED_DT=1`, Take A Ride, Майами, 1700 кадров, `RE_CARDBG=10`) — журнал `[car]`, `debug.log`, снимок и stdout
совпадают с `main` байт в байт.

## 1. `src/` — псевдо-C из Ghidra (~163 тыс. строк, 21 файл)

Справочный материал: исходник для переноса и сверки, в сборку не входит (ни CMake, ни `build.sh` его не видят).
Не мёртвый код в обычном смысле — **оставить**. Если репозиторий нужно облегчить, можно вынести в отдельный репозиторий
или архив, но `docs/functions.csv` и комментарии в портах ссылаются на эти функции по именам.

## 2. 60 адресов Game.exe, перехваченных дважды — РЕШЕНО (cleanup/round2)

Было: для 60 адресов `re_hook` вызывался дважды (hook DLL брала последний, native `fn_table.c` — первый). Теперь у каждого
адреса одна реализация; `fn_table.c` перегенерирован (2207 записей). Сверка: тела пар скомпилированы hook-сборкой и
сравнены дизассемблером с Game.exe (`rp-game.dis`).

- **50 обработчиков меню 00404687..0040a715: оставлен `menustate.c`**, копии в `uihandlers4.c` удалены. 37 пар давали
  одинаковый код; в 13 парах входа/выхода режимов меню (0040a625..0040a715) `menustate.c` пишет байт (`movb`, как
  Game.exe), а `uihandlers4.c` писал dword — копия была менее точной. В native раньше побеждал `uihandlers4.c` в 44
  случаях — прогон Take A Ride от смены не изменился. `reptr.c` (k_fns), selftest `test_ui4` переведены на имена
  `menustate.c`. Переменные `G00xxxxxx` в `uihandlers4.c` оставлены (их используют другие модули и `data_init.c`).
- **10 прочих пар** — оставлен именованный/документированный порт, дубль удалён, прямые вызовы переведены:

| Адрес | Оставлено | Удалено | Примечание |
|---|---|---|---|
| 00413df3 | `P62_MenuBusy` | `MenuAnyFlag00413DF3` (ported6) | код одинаковый |
| 0048ac0d | `P50_FmvStopRelease` | `Chain0048AC0D` (ported5) | вызовы в ported150/52 переведены |
| 0048cc5f | `P50_Nop` | `NoopFn0048cc5f` (noop.c) | |
| 004a6749 | `P62_FindFreeTrafficSlot` | `P14_Fn004A6749` | memset вместо P14_Fn0048DB65 (тот же memset); вызовы в ported119 |
| 004e12e4 | `P16_IdleTimer` | `P14_Fn004E12E4` | код одинаковый; вызов в ported132 |
| 004eafcf | `P78_LoadLampsBlock` | `Fwd004EAFCF` (ported5) | прямой вызов вместо вызова по адресу |
| 004ef997 | `P89_Fill1` | `FillOnes4EF997` (ported4) | |
| 00514c72 | `P62_ParticleSet` | `SetObjState_00514C72` (ported7) | код одинаковый |
| 005223be | `P30_InitWindowGlobals` | `ClearHandles005223BE` (ported6) | вызов в ported151 |
| 005291ed | `P152_FillRows` | `P101_FillRows` | P152 документирован и вызывается P152_ScreenFill; лишняя проверка dst == NULL — только защита native |

После удаления у `unported.h` стали ненужны `Call0048B65D`, `Call0048B568`, `Call004EAFE0`, `G6Call004A2B70` — убраны.

## 3. ~326 слабых заглушек `unported.h`, перекрытых портами (устаревшие имена)

`re/game/unported.h` перечисляет 350 «ещё не перенесённых» вызовов; `re/platform/native/stubs.c` делает из них слабые
(`__attribute__((weak))`) заглушки. 326 из 350 перекрыты строгими определениями (в `re/platform/native/links.c` или
прямо в портах) — то есть функции давно перенесены, а в коде остались вызовы по старым именам вида `P98_Fn4ACCF0`.
Настоящих заглушек осталось 24. Чистка = заменить вызовы старых имён на имена портов и удалить строки из списка;
это меняет hook-сборку (там вызовы идут по адресу в Game.exe), поэтому — отдельной веткой с прогоном обеих целей.

## 4. Псевдонимы образа данных, которые выбрасывает компоновщик — оставлены

С `-ffunction-sections -fdata-sections -Wl,--gc-sections` компоновщик выкидывает 13 объектов данных в `re/game/`
(например `CamParamTblArr`, `P10_Tab`, `P96_PartTab`, `MenuFlag54A9xx`) и 4 функции (используются только hook-сборкой или
встроены в вызывающих: `re_crt_mkdir`, `P14_Fn004E3924`, `re_dd_heading`, `re_dd_cell_in`). Объекты данных — native-копии адресов Game.exe,
к которым обращения идут через `re_gvar(...)`/макросы; они документируют карту адресов и нужны hook-сборке или
генераторам (`tools/gen_gvar_img.py`). Выигрыш от удаления — байты; **оставлены**. Сторонние single-header библиотеки
(`dr_flac`/`dr_mp3` в `plat_cdaudio.c`, `cgltf` в `plat_detail.c`) дают остальные выброшенные секции — это норма.

## 5. Старые одноразовые инструменты и дрейф `links.c`

- `tools/name_pass1.py`, `tools/split_modules.py` — первичная разметка имён и раскладка `src/` по модулям (ранний этап);
- `tools/gen_glide.py` — генератор слоя Glide (упоминается в `re/game/ported33.c`, `re/README.md`);
- `scripts/run_ghidra.sh`, `scripts/rerun_export.sh` — запуск экспорта Ghidra.

Ни сборка, ни CI их не вызывают; упоминаются только в документации. Оставлены как история воспроизводимости
(как были получены `src/` и `docs/functions.csv`); при повторном запуске, вероятно, потребуют правок.

**`links.c` и генератор — РЕШЕНО (cleanup/round2).** `tools/gen_native_links.py` снова воспроизводит
`re/platform/native/links.c` байт в байт:
- имена, уже строго определённые в `re/game` / `re/platform/native` (например `Call0040C20B`, `LoadIconByName` в
  `game_fwd.c`), пропускаются — раньше перегенерация дала бы повторные определения;
- `tools/native_links_skip.txt` — список имён, которые генератор не должен связывать. В cleanup/round2 в нём было
  38 имён «перенос есть, связи нет»; **fix/link-ported (п. 7.1) показал, что все 38 уже связаны** (шпионы
  `tests/selftest.c` и `game_fwd.c`), генератор теперь видит определения и в `re/tests/*.c`, список пуст;
- всё после строки `/* ==== manual part … ==== */` в `links.c` — ручная часть (sprintf 0052a910, R12_40DAE1,
  колбэки таймеров, `P56_Fn4E5284` с другой сигнатурой); генератор переносит её как есть.

## 6. Ошибка в selftest — ИСПРАВЛЕНО (cleanup/round2)

`test_p21`: `memset(P21_Entries, 0, sizeof P21_Entries)` очищал 8 байт (sizeof макроса-указателя); теперь
`memset(P21_Entries, 0, 0x40 * 0x54)`. Тест проходит, как и раньше.

## 7. Раунд 2 (`cleanup/round2`, PR #5): что ещё сделано и что осталось

- **`P87_DrawCells` удалена.** Адреса в Game.exe нет, вызывал только selftest (упрощённый 004ee8f4 времён v1.32).
  Проверка рендера `RE_REAL_CITY` теперь идёт по точному пути `P89_DrawMap` (синоним `RE_REAL_MAP`; `RE_REAL_R` убран).
- **Предупреждения native (Linux, gcc 14): 30 → 0.** selftest — настоящие исправления; в игре — приведения типов без
  изменения кода, `PackRGB00503ECC(const uint8_t *)`; `-Wformat-truncation` в ported126/138/139/147/150 заглушён
  `#pragma` (только GCC): пути реплеев/FMV собираются ограниченным snprintf в буферы фиксированного размера, усечение
  длинного имени — ожидаемое поведение, а увеличение буферов изменило бы объектный код; в `diagnostics.c` (платформа)
  буферы путей увеличены по-настоящему.
- **Дубли помощников → `memrw.h`:** `rdu16`, `rds16`, `wr16(p, v)`, `wrf(p, v)`, `u2f`, `fbits`, `f2i` — локальные
  копии (75) убраны из 42 файлов (`ported87` — ещё и дубли `rd32/rdf`). Новые помощники — `static` (не `inline`) с
  `__attribute__((unused))`, как бывшие локальные копии, чтобы hook-сборка (-O1) принимала прежние решения о
  встраивании; `wr16` принимает `int32_t` и усекает (у копий были `uint16_t`/`int16_t`/`int32_t`).
  **В 6 файлах (`ported102/127/133/142/143/144`) локальные копии оставлены** (`#define RE_MEMRW_LOCAL16` перед
  `#include "memrw.h"`): перенос определений в заголовок менял у GCC -O1 порядок операндов (`cmp a,b; jl` ↔
  `cmp b,a; jg`) или порядок функций в hook-объектах — семантика та же, байты другие. Итог: все hook- и
  native-объекты, которых не касались удаления (п. 2, `P87_DrawCells`, `links.c`/`unported.h`, selftest), совпадают
  с `fix/cops` байт в байт.
- **Неиспользуемые функции/глобалы:** поиск по `nm` (определено в `re/game`, нет ссылок ни в native, ни в hook-объектах,
  ни в fn_table/install/links) дал только известные 5 функций из п. 4 (`re_dd_cell_in`, `re_dd_heading`,
  `P14_Fn004E3924`, `re_crt_mkdir`, `P37_JoyEnumCb` — нужны hook-сборке/встроены). Глобалы без ссылок — псевдонимы
  образа данных (оставлены, п. 4) и отладочные счётчики (`P85_LastBlend` — только запись; `P84_Hand*` — для журнала).
- **Осталось:** ~60 групп мелких локальных помощников с другой сигнатурой или смыслом (`rd32(p, o)`, `wr16(p, o, v)`,
  `rd32` → uint32, `mul`, `ftol`, `neg`, `carmodel`, `oow_at`, `tex_select` …) — объединять только с переименованием
  и сверкой объектов; п. 3 (326 устаревших имён `unported.h`). 38 «несвязанных» переносов — см. п. 7.1 (уже связаны).


### 7.1. 38 «перенесённых, но не связанных» функций (`fix/link-ported`, PR #6) — уже связаны

Итог: **связывать нечего — все 38 в native уже вызывают перенос; ни одно соответствие не отвергнуто.** Находка
раунда 2 была ошибкой генератора, а не пробелом в native.

- **Почему так вышло.** `tests/selftest.c` входит в native-сборку (`NATIVE_SRC` в `re/CMakeLists.txt`, один бинарник
  с игрой). С v2.02 в нём «шпионы» для этих имён: строгое определение вида
  `if (!re_selftest_on) { return <перенос>(...); } <счётчик selftest>` — в игре (`re_selftest_on = 0`) вызов идёт в
  перенос, в `--selftest` — в счётчик. Они перекрывают слабые заглушки `stubs.c` так же, как `links.c`. Ещё 2 имени
  (`Call004EC91E`, `Call0040BF50`) так же связаны в `platform/native/game_fwd.c`. Генератор искал готовые определения
  только в `re/game` и `re/platform/native`, не видел шпионов и сгенерировал бы для них повторные определения — их и
  заглушили списком `native_links_skip.txt`, приняв за «несвязанные».
- **Проверка на бинарнике:** в `driver` (base `ec72cac`) символ, например, `P77_Fn501C63` — это шпион selftest
  (проверка `re_selftest_on`, затем `P102_HudInit`), а не заглушка `stubs.c`. Пробная перегенерация `links.c` без
  списка ломает компоновку: `multiple definition of 'P56_FindIcon'` … (`selftest.c.o` против `links.c.o`).
- **Проверка соответствий (все 38 верны):** адрес строки `unported.h` → `re_hook` в `platform/win32/install.c`
  (на каждый адрес ровно один) → тот же перенос в `fn_table.c` → комментарий «Game.exe <адрес>» у определения
  переноса. Сигнатуры совместимы (generator `gcc -fsyntax-only -Werror=int-conversion,incompatible-pointer-types`
  проходит для всех 36 V/R-строк; порядок аргументов сверен у неочевидных: `P61_Fn5139D7(0, x, z, out)` ↔
  `P101_PickCell(want, x, z, out)`, `P63_Fn49521E(rec, 1, 0)` ↔ `P102_TrafficAhead(rec, dist, parked)` (так же
  зовёт `P118`), `Call005233BE` ↔ `P140_SndInit(drv, arg, eax)`). Шпионы передают те же аргументы, что дал бы
  генератор. Единственное место, где генератор ошибся бы: `Call004EC91E` (R-строка `int32_t`) — сгенерированное
  `(int32_t)P93_FindIcon(…)` обрезало бы 64-битный указатель; правильная связь — в `game_fwd.c` через
  `re_addr()` (32-битный адрес записи значка, как в Game.exe).
- **Что изменено:** `tools/gen_native_links.py` считает определёнными и имена из `re/tests/*.c`;
  `tools/native_links_skip.txt` пуст (только заголовок). `links.c` перегенерируется байт в байт (259 связей; «типы не
  сходятся» 17 → 16 — одно из них оказалось шпионом selftest). Каталог `re/` не изменился: все 196 native-объектов
  совпадают с базой (кроме `diagnostics.c.o` — там `__TIME__` сборки), hook-сборка (`./build.sh hook`) — 0 предупреждений.
- **Прогоны** (Linux arm64, Xvfb; бинарник тот же, что у базы): Take A Ride Miami 1700 кадров `RE_FIXED_DT=1`
  (и с `RE_FPU_CHOP=0`), Survival 2400 кадров, обход меню RE_PROBE walk (8 запусков, 10 экранов меню; 8-й — таймаут 300 с) — «not ported» в debug.log/stdout: 0 → 0,
  падений и assert нет.
- **Осталось:** 16 имён `unported.h`, у которых перенос по адресу есть, но генератор не связывает их из-за
  несовпадения типов (`P62_Fn424A02`, `P47_Fn405FDB`, `Fn00416040`, `Call00524496`, `Call004D78F3`, `Call004DAA36`,
  `Call004D28A3`, `Call00514A47`, `Call004D90F4`, `UiCall004D8F30`, `GameDrawIcon`, `G6Call00519D22`,
  `Call004BF910`, `Call00528982`, `Call004D8F30`, `P58_Fn407E2F`) — в прогонах выше не вызываются; связывать вручную
  (ручная часть `links.c`) только с проверкой сигнатуры каждого.

| Группа | Имя заглушки | Адрес | Перенос | Где связь |
|---|---|---|---|---|
| HUD/текст/2D | `P56_FindIcon` | 004ec91e | `P93_FindIcon` | tests/selftest.c:2737 |
| HUD/текст/2D | `Call004EC91E` | 004ec91e | `P93_FindIcon` | platform/native/game_fwd.c:17 |
| HUD/текст/2D | `P58_Fn4AA4EA` | 004aa4ea | `P110_IconRect` | tests/selftest.c:2738 |
| HUD/текст/2D | `P66_Draw5173D7` | 005173d7 | `P73_Text` | tests/selftest.c:2603 |
| HUD/текст/2D | `P67_Fn40ABAC` | 0040abac | `P116_Text` | tests/selftest.c:2732 |
| HUD/текст/2D | `P70_Fn5063A4` | 005063a4 | `P135_RadarLine` | tests/selftest.c:2932 |
| HUD/текст/2D | `P70_Fn507925` | 00507925 | `P131_RadarArrow` | tests/selftest.c:2933 |
| HUD/текст/2D | `P77_Fn501770` | 00501770 | `P136_OverlayMap` | tests/selftest.c:3465 |
| HUD/текст/2D | `P77_Fn501C63` | 00501c63 | `P102_HudInit` | tests/selftest.c:3464 |
| HUD/текст/2D | `P66_Fn4C68A7` | 004c68a7 | `P112_DirTimeline` | tests/selftest.c:2610 |
| HUD/текст/2D | `P76_Fn40DCE0` | 0040dce0 | `P109_TileDraw` | tests/selftest.c:3354 |
| меню/фронтенд/устройства | `P57_MenuStep` | 0040c8f1 | `P114_MenuStep` | tests/selftest.c:2044 |
| меню/фронтенд/устройства | `P58_Fn418675` | 00418675 | `P110_MenuSel` | tests/selftest.c:2085 |
| меню/фронтенд/устройства | `Call00414D1F` | 00414d1f | `P103_OptionsInit` | tests/selftest.c:2741 |
| меню/фронтенд/устройства | `Call0040BF50` | 0040bf50 | `P136_FrontInit` | platform/native/game_fwd.c:6 |
| меню/фронтенд/устройства | `P68_Fn41B1C0` | 0041b1c0 | `P139_LadderLoad` | tests/selftest.c:2797 |
| меню/фронтенд/устройства | `P68_Fn41B3AB` | 0041b3ab | `P140_LadderRun` | tests/selftest.c:2798 |
| меню/фронтенд/устройства | `P74_Fn41CE90` | 0041ce90 | `P149_DDEnumAll` | tests/selftest.c:3158 |
| меню/фронтенд/устройства | `P74_Fn424B70` | 00424b70 | `P76_GlideRegister` | tests/selftest.c:3159 |
| звук | `Call005233BE` | 005233be | `P140_SndInit` | tests/selftest.c:2740 |
| звук | `P66_Fn523829` | 00523829 | `P115_SndUpdate` | tests/selftest.c:2605 |
| звук | `P67_Stream` | 00524496 | `P77_LoadBank` | tests/selftest.c:2736 |
| звук | `P77_Fn524BD8` | 00524bd8 | `P140_BankLine` | tests/selftest.c:3466 |
| 3-D сцена/эффекты | `P66_Fn427EEA` | 00427eea | `P82_FrustumSetup3D` | tests/selftest.c:2606 |
| 3-D сцена/эффекты | `P69_Fn4AAF3A` | 004aaf3a | `P139_Effects` | tests/selftest.c:2887 |
| 3-D сцена/эффекты | `P69_Fn4B2C4B` | 004b2c4b | `P121_DustDraw` | tests/selftest.c:2886 |
| 3-D сцена/эффекты | `P69_Fn4B33D8` | 004b33d8 | `P135_DebrisTri` | tests/selftest.c:2884 |
| 3-D сцена/эффекты | `P69_Fn4B3E55` | 004b3e55 | `P114_DebrisAll` | tests/selftest.c:2885 |
| 3-D сцена/эффекты | `P69_Fn4BA720` | 004ba720 | `P98_DrawSix` | tests/selftest.c:2888 |
| 3-D сцена/эффекты | `P76_Fn4268EF` | 004268ef | `P82_AddLight` | tests/selftest.c:3355 |
| мир (трафик, частицы) | `P61_Fn5139D7` | 005139d7 | `P101_PickCell` | tests/selftest.c:2931 |
| мир (трафик, частицы) | `P63_Fn49521E` | 0049521e | `P102_TrafficAhead` | tests/selftest.c:2043 |
| мир (трафик, частицы) | `P75_Fn491A56` | 00491a56 | `P119_TrafficSpawn` | tests/selftest.c:3266 |
| мир (трафик, частицы) | `P75_Fn4958B7` | 004958b7 | `P107_TrafficRow` | tests/selftest.c:3265 |
| мир (трафик, частицы) | `P75_Fn4EDD08` | 004edd08 | `P88_CellUpdate` | tests/selftest.c:3267 |
| мир (трафик, частицы) | `P67_Fn514165` | 00514165 | `P71_Course` | tests/selftest.c:2735 |
| мир (трафик, частицы) | `P67_Fn51500C` | 0051500c | `P101_PartTurn` | tests/selftest.c:2734 |
| мир (трафик, частицы) | `P68_Fn514A47` | 00514a47 | `P98_PartAim` | tests/selftest.c:2796 |
