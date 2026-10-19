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

## 2. 60 адресов Game.exe перехвачены дважды (`re/platform/win32/install.c`)

Для 60 адресов `re_hook` вызывается два раза: одна функция из `re/game/menustate.c`, другая из `re/game/uihandlers4.c`
(одни и те же обработчики меню перенесены дважды под разными именами). Две цели сборки выбирают **разных** победителей:

- hook-сборка (`DINPUT.dll`): каждый `re_hook` пишет JMP поверх функции, поэтому работает **последний** вызов;
- native (`re/platform/native/fn_table.c`, генерируется `tools/gen_fn_table.py`): в таблицу попадает **первый**.

Тела пар по смыслу совпадают (например `MenuFlagSet` и `Set5F7E4C_1` оба ставят 005f7e4c = 1), но пишут через разные
имена переменных (`MenuFlag5F7E4C` против `G005F7E4C`) — если какое-то из имён окажется расщеплённым псевдонимом
(отдельный native-объект вместо образа данных), поведение целей разойдётся. В native проигравшие функции не вызываются
(компоновщик с `--gc-sections` их выбрасывает), в hook-сборке — наоборот.

**Нужно решение:** оставить одну реализацию на адрес (скорее `menustate.c` — осмысленные имена; в native сейчас
побеждает `menustate.c` в 16 случаях и `uihandlers4.c` в 44), убрать второй `re_hook` и перегенерировать
`fn_table.c`. После этого — прогон меню и кампании в обеих целях. В этой ветке не трогалось.

| Адрес | native: `fn_table.c` (первый `re_hook`) | hook: последний `re_hook` (его JMP и остаётся) |
|---|---|---|
| 00404687 | `MenuFlagSet` (menustate.c) | `Set5F7E4C_1` (uihandlers4.c) |
| 00404eb0 | `MenuToggleOptBDFA44` (menustate.c) | `ToggleBDFA44_Call40500D` (uihandlers4.c) |
| 00404ec9 | `MenuToggleOptBDFA48` (menustate.c) | `ToggleBDFA48_Call40500D` (uihandlers4.c) |
| 00404ee2 | `MenuToggleOptBDFA4C` (menustate.c) | `ToggleBDFA4C_Call40500D` (uihandlers4.c) |
| 00404efb | `MenuToggleOptBDFA50` (menustate.c) | `ToggleBDFA50_Call40500D` (uihandlers4.c) |
| 00404f14 | `MenuToggleOptBDFA54` (menustate.c) | `ToggleBDFA54_Call40500D` (uihandlers4.c) |
| 00404f2d | `MenuToggleOptB87E9C` (menustate.c) | `ToggleB87E9C_Call40500D` (uihandlers4.c) |
| 00404f46 | `MenuToggleOptBDFA58` (menustate.c) | `ToggleBDFA58_Call40500D` (uihandlers4.c) |
| 00404f5f | `MenuStateSetFour` (menustate.c) | `Set575EF0_4Ret0` (uihandlers4.c) |
| 0040831c | `Copy54A0C0` (uihandlers4.c) | `MenuCopyPos` (menustate.c) |
| 00408337 | `MenuFlag54A0BCSet` (menustate.c) | `Set54A0BC_1` (uihandlers4.c) |
| 00408343 | `MenuFlag54A0BCClear` (menustate.c) | `Set54A0BC_0` (uihandlers4.c) |
| 0040844c | `MenuVar54A0CCClear` (menustate.c) | `Set54A0CC_0` (uihandlers4.c) |
| 00408710 | `MenuCounter5D577CInc` (menustate.c) | `Inc5D577C` (uihandlers4.c) |
| 00408a69 | `ToggleEF8_55384C` (uihandlers4.c) | `MenuToggle55384CRedraw` (menustate.c) |
| 00408b03 | `ToggleEF8_553850` (uihandlers4.c) | `MenuToggle553850Redraw` (menustate.c) |
| 00408b9d | `ToggleEF8_B31F04` (uihandlers4.c) | `MenuToggleB31F04Redraw` (menustate.c) |
| 00408d0c | `MenuToggle575F44Redraw` (menustate.c) | `ToggleEF8_575F44` (uihandlers4.c) |
| 00408da6 | `ToggleEF8_55C974` (uihandlers4.c) | `MenuToggle55C974Redraw` (menustate.c) |
| 00408e40 | `MenuToggle575F30Redraw` (menustate.c) | `ToggleEF8_575F30` (uihandlers4.c) |
| 00408eda | `ToggleEF8_B201DC` (uihandlers4.c) | `MenuToggleB201DCRedraw` (menustate.c) |
| 00408f74 | `ToggleEF8_575EE8` (uihandlers4.c) | `MenuToggle575EE8Redraw` (menustate.c) |
| 0040900e | `MenuToggle575F3CRedraw` (menustate.c) | `ToggleEF8_575F3C` (uihandlers4.c) |
| 004090a8 | `ToggleEF8_D118C8` (uihandlers4.c) | `MenuToggleD118C8Redraw` (menustate.c) |
| 00409231 | `RefreshMenu00409231` (uihandlers4.c) | `MenuRedraw409231` (menustate.c) |
| 004092d8 | `RefreshMenu004092D8` (uihandlers4.c) | `MenuRedraw4092D8` (menustate.c) |
| 0040937f | `RefreshMenu0040937F` (uihandlers4.c) | `MenuRedraw40937F` (menustate.c) |
| 00409426 | `RefreshMenu00409426` (uihandlers4.c) | `MenuRedraw409426` (menustate.c) |
| 004094cd | `RefreshMenu004094CD` (uihandlers4.c) | `MenuRedraw4094CD` (menustate.c) |
| 00409b75 | `Inc5759A4Max40` (uihandlers4.c) | `MenuIncVar5759A4` (menustate.c) |
| 00409b9f | `Dec5759A4Min0` (uihandlers4.c) | `MenuDecVar5759A4` (menustate.c) |
| 00409c31 | `IncB87E4CMax3` (uihandlers4.c) | `MenuIncVarB87E4C` (menustate.c) |
| 00409c5b | `DecB87E4CMin0` (uihandlers4.c) | `MenuDecVarB87E4C` (menustate.c) |
| 0040a443 | `Set54A844_1` (uihandlers4.c) | `MenuSet54A844On` (menustate.c) |
| 0040a44f | `Set54A844_0` (uihandlers4.c) | `MenuSet54A844Off` (menustate.c) |
| 0040a495 | `Set54A854_1` (uihandlers4.c) | `MenuSet54A854On` (menustate.c) |
| 0040a4a1 | `Set54A854_0` (uihandlers4.c) | `MenuSet54A854Off` (menustate.c) |
| 0040a625 | `Select54A90C_Mode2` (uihandlers4.c) | `MenuEnterMode2` (menustate.c) |
| 0040a63b | `Clear54A90C_IfZero` (uihandlers4.c) | `MenuLeaveMode2` (menustate.c) |
| 0040a64d | `Select54A91C_Mode1` (uihandlers4.c) | `MenuEnterMode1` (menustate.c) |
| 0040a663 | `Clear54A91C_IfZero` (uihandlers4.c) | `MenuLeaveMode1` (menustate.c) |
| 0040a675 | `Select54A8FC_Mode5` (uihandlers4.c) | `MenuEnterMode5` (menustate.c) |
| 0040a68b | `Clear54A8FC_IfZero` (uihandlers4.c) | `MenuLeaveMode5` (menustate.c) |
| 0040a69d | `Select54A92C_Mode3` (uihandlers4.c) | `MenuEnterMode3` (menustate.c) |
| 0040a6b3 | `Clear54A92C_IfZero` (uihandlers4.c) | `MenuLeaveMode3` (menustate.c) |
| 0040a6c5 | `Select54A8EC_Mode4` (uihandlers4.c) | `MenuEnterMode4` (menustate.c) |
| 0040a6db | `Clear54A8EC_IfZero` (uihandlers4.c) | `MenuLeaveMode4` (menustate.c) |
| 0040a6ed | `Select54A94C_Mode7` (uihandlers4.c) | `MenuEnterMode7` (menustate.c) |
| 0040a703 | `Clear54A94C_IfZero` (uihandlers4.c) | `MenuLeaveMode7` (menustate.c) |
| 0040a715 | `Select54A93C_Mode6` (uihandlers4.c) | `MenuEnterMode6` (menustate.c) |
| 00413df3 | `MenuAnyFlag00413DF3` (ported6.c) | `P62_MenuBusy` (ported62.c) |
| 0048ac0d | `Chain0048AC0D` (ported5.c) | `P50_FmvStopRelease` (ported50.c) |
| 0048cc5f | `NoopFn0048cc5f` (noop.c) | `P50_Nop` (ported50.c) |
| 004a6749 | `P14_Fn004A6749` (ported14.c) | `P62_FindFreeTrafficSlot` (ported62.c) |
| 004e12e4 | `P14_Fn004E12E4` (ported14.c) | `P16_IdleTimer` (ported16.c) |
| 004eafcf | `Fwd004EAFCF` (ported5.c) | `P78_LoadLampsBlock` (ported78.c) |
| 004ef997 | `FillOnes4EF997` (ported4.c) | `P89_Fill1` (ported89.c) |
| 00514c72 | `SetObjState_00514C72` (ported7.c) | `P62_ParticleSet` (ported62.c) |
| 005223be | `ClearHandles005223BE` (ported6.c) | `P30_InitWindowGlobals` (ported30.c) |
| 005291ed | `P101_FillRows` (ported101.c) | `P152_FillRows` (ported152.c) |

## 3. ~326 слабых заглушек `unported.h`, перекрытых портами (устаревшие имена)

`re/game/unported.h` перечисляет 350 «ещё не перенесённых» вызовов; `re/platform/native/stubs.c` делает из них слабые
(`__attribute__((weak))`) заглушки. 326 из 350 перекрыты строгими определениями (в `re/platform/native/links.c` или
прямо в портах) — то есть функции давно перенесены, а в коде остались вызовы по старым именам вида `P98_Fn4ACCF0`.
Настоящих заглушек осталось 24. Чистка = заменить вызовы старых имён на имена портов и удалить строки из списка;
это меняет hook-сборку (там вызовы идут по адресу в Game.exe), поэтому — отдельной веткой с прогоном обеих целей.

## 4. Псевдонимы образа данных, которые выбрасывает компоновщик — оставлены

С `-ffunction-sections -fdata-sections -Wl,--gc-sections` компоновщик выкидывает 13 объектов данных в `re/game/`
(например `CamParamTblArr`, `P10_Tab`, `P96_PartTab`, `MenuFlag54A9xx`) и, кроме проигравших дублей из п. 2, 5 функций (используются только hook-сборкой или
встроены в вызывающих: `P50_FmvStopRelease`, `re_crt_mkdir`, `P14_Fn004E3924`, `re_dd_heading`, `re_dd_cell_in`). Объекты данных — native-копии адресов Game.exe,
к которым обращения идут через `re_gvar(...)`/макросы; они документируют карту адресов и нужны hook-сборке или
генераторам (`tools/gen_gvar_img.py`). Выигрыш от удаления — байты; **оставлены**. Сторонние single-header библиотеки
(`dr_flac`/`dr_mp3` в `plat_cdaudio.c`, `cgltf` в `plat_detail.c`) дают остальные выброшенные секции — это норма.

## 5. Старые одноразовые инструменты и дрейф `links.c`

- `tools/name_pass1.py`, `tools/split_modules.py` — первичная разметка имён и раскладка `src/` по модулям (ранний этап);
- `tools/gen_glide.py` — генератор слоя Glide (упоминается в `re/game/ported33.c`, `re/README.md`);
- `scripts/run_ghidra.sh`, `scripts/rerun_export.sh` — запуск экспорта Ghidra.

Ни сборка, ни CI их не вызывают; упоминаются только в документации. Оставлены как история воспроизводимости
(как были получены `src/` и `docs/functions.csv`); при повторном запуске, вероятно, потребуют правок.

`re/platform/native/links.c` разошёлся со своим генератором `tools/gen_native_links.py`: перегенерация даёт ~100 строк
разницы (другие `#include`, новые обёртки для вызовов, которые уже перекрыты определениями в портах → были бы
повторные определения). Файл правился руками; **не перегенерировать** вслепую. Решение: либо научить генератор
пропускать уже определённые имена, либо объявить `links.c` ручным файлом и удалить генератор (связано с п. 3).

## 6. Возможная ошибка в selftest

`re/tests/selftest.c:611` (`test_p21`): `memset(P21_Entries, 0, sizeof P21_Entries)`. `P21_Entries` — макрос-указатель
(`re/game/ported21.h`), поэтому `sizeof` = размер указателя (8 байт на 64-бит, 4 на i686), а не таблицы
`0x40 * 0x54`. Тест проходит, потому что проверяемые байты и так нулевые, но очистка не та, что задумана.
Вероятно, нужно `memset(P21_Entries, 0, 0x40 * 0x54)` (или хотя бы `2 * 0x54`). Не исправлено — поведение теста
не менялось в этой ветке.
