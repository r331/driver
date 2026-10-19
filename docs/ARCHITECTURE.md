# Архитектура репозитория

Короткая карта для человека, который впервые открывает проект. Подробности — в ссылках:
правила переноса и история версий — [re/README.md](../re/README.md), разрывы native и переключатели отладки —
[NATIVE_GAPS.md](NATIVE_GAPS.md), журнал шагов — [PLATFORM_PLAN.md](PLATFORM_PLAN.md),
указатель модулей `re/game/` — [MODULES.md](MODULES.md).

## Идея

`Game.exe` (Driver PC, 1999, MSVC 6) переписан на C функция за функцией в стиле re3. Один и тот же код игры
(`re/game/`) собирается в две цели:

| Цель | Что это | Как собрать |
|---|---|---|
| **native** | самостоятельная программа на SDL2 + OpenGL 3.3 (Linux, macOS arm64, Windows x64); нужны только данные игры (`Data_Files`) | `cmake -S re -B build-native && cmake --build build-native` или `re/build.sh native` |
| **hook** | прокси `DINPUT.dll` (i686) для оригинального `Game.exe`: перенесённые функции ставятся поверх оригинальных (JMP rel32), так каждую можно сверить в живой игре | `re/build.sh hook` (mingw `i686-w64-mingw32-gcc`) |

CI ([.github/workflows](../.github/workflows)): Linux — native + ctest, native с SDL3 (`RE_SDL3_COMPAT`, Steam Controller), hook; macOS 14 (arm64) — native, ctest, `Driver.app`.

## Каталоги

| Путь | Что внутри |
|---|---|
| `re/game/` | перенесённый код игры, без WinAPI. `portedNN.c/.h` — модули по шагам переноса (см. MODULES.md), `director*.c`, `menu*.c`, `uihandlers*.c` и т. п. — тематические; `pNN_data.h`, `data_image.c`, `data_init.c`, `gvar_img_tab.c`, `sintab_data.h` — **сгенерированы** из Game.exe скриптами `tools/gen_*.py` |
| `re/platform/plat.h` | единственный интерфейс игры к платформе (окно, рендер, ввод, звук, CD, файлы, время) |
| `re/platform/sdl/` | реализация `plat.h` для native: SDL2/OpenGL (эмуляция DirectDraw/D3D/Glide), DirectInput → SDL, микшер DirectSound, эмуляция CD-audio, HD-текстуры, 3D-детали фасадов |
| `re/platform/native/` | точка входа native (`main.c`), сервисы движка (`engine_native.c`), диагностика, слабые заглушки и связки (`stubs.c`, `links.c`, `game_fwd.c`), таблицы адресов (`fn_table.c`, `thunk_table.c`), замены MSVC CRT |
| `re/platform/win32/` | hook-сборка: прокси DINPUT, установка перехватов (`hook.c`, `install.c` — список всех подменённых функций), `stdcall_tbl.h`, реализация `plat.h` поверх WinAPI/DirectX оригинала |
| `re/tests/` | `driver --selftest` (тесты перенесённых модулей, без данных игры), `--inputtest`, тесты рендера/звука/CD |
| `re/third_party/` | однофайловые библиотеки (stb_image, stb_vorbis, dr_flac, dr_mp3, cgltf) — не править |
| `docs/` | `functions.csv` (все 3632 функции Game.exe: адрес, имя, модуль, статус), `platform_funcs.csv`, `binary-info.md`, планы и журналы; `docs/ci/` — копия `.github/workflows/*.yml` (держать в синхроне) |
| `tools/` | Python: генераторы таблиц из Game.exe, генераторы связок, проверки, HD-пак, сейвы (см. ниже) |
| `scripts/` | Ghidra headless (экспорт функций/псевдо-C, имена, ссылки строк) и диагностический запуск на macOS |
| `src/` | псевдо-C Ghidra, разложенный по модулям оригинала, — **справочник, в сборку не входит** |

## Как код игры связан с двумя целями

**Глобальные переменные — `GAME_VAR` (`re/game/gvar.h`).** В hook-сборке имя раскрывается в ячейку оригинального
Game.exe по её адресу. В native — обычная C-переменная; если адрес лежит в `.rdata/.data` (00546000..0057c000),
то в режиме игры переменная живёт в образе этих секций (`data_image.c`, `re_gvar`): у одного адреса может быть
несколько имён-псевдонимов, и запись через любое видна всем. Блоки `#pragma push_macro … /*gvi*/` в файлах
расставляет `tools/gen_gvar_img.py` — руками не править.

**32-битные указатели игры — `re_ptr` / `re_addr` (`re/game/reptr.h`).** Поля-указатели в таблицах игры в native
хранятся как адреса Game.exe; перевод в родной указатель и обратно — только через реестр областей `reptr.c`.
Указатели на функции — `re_fn(адрес)`: таблица `fn_table.c` (адрес → перенесённая функция, генерируется из
`install.c`) и `thunk_table.c` (переходники `jmp rel32` Game.exe → цель).

**Ещё не перенесённые / маршрутизируемые вызовы — `re/game/unported.h`.** X-макрос-список «имя, адрес, сигнатура».
hook: вызов оригинала по адресу. native: слабая заглушка из `platform/native/stubs.c` (пишет «not ported: …»),
которую перекрывает строгое определение — перенесённая функция с тем же именем или мост в `links.c`/`game_fwd.c`.
Часть записей — уже перенесённые функции, оставленные под старым именем ради тестов-шпионов (см. правила v1.65/v1.68).

**Подмена в hook-сборке.** `platform/win32/install.c` перечисляет `re_hook(адрес, функция, "имя")`; функции,
которые в оригинале `stdcall` (`ret N`), получают переходник по `stdcall_tbl.h`. Отключить одну функцию в живой
игре — `re_driver.ini`, секция `[disable]`.

## Имена

- Адрес Game.exe — главный ключ. Он есть в имени (`Call0040C20B`, `P14_Fn004E3924`, `MenuRedraw409231`) или в
  комментарии рядом с функцией; по нему функция находится в `docs/functions.csv`, Ghidra и `src/`. Эти адреса не
  удалять и не переименовывать.
- `PNN_` — функция/переменная из `portedNN.c/.h`. `CallXXXXXXXX` и `PNN_FnXXXXXX` в `unported.h` — вызовы по адресу.
- Переменные с адресом в имени (`P11_00b87e38`, `G6_01145A60`, `A_00D04B00`) — ячейки Game.exe; новые имена внутри
  уже описанных таблиц — макросы `*_VAR` над таблицей (cartab.h, nodetab.h, menugfx.h …), а не новые переменные.
- Мелкие помощники чтения полей (`rd32`, `wr32`, `rdf`, `iabs`, `fround`) — `re/game/memrw.h`.

## Проверка изменений

```sh
cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release && cmake --build build-native -j
(cd build-native && ctest --output-on-failure)        # selftest + inputtest, без данных игры
re/build.sh hook                                       # DINPUT.dll собирается
```

Воспроизводимый прогон игры (нужны свои `Data_Files`, рабочий каталог — копия, игра пишет в него):
`RE_FIXED_DT=1 RE_CARDBG=10 RE_MAX_FRAMES=1700 RE_SHOT_PNG=out.png
RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,700:0x28:1000,1000:0x2d:25"
xvfb-run build-native/driver --data .` — Take A Ride, Майами. Строки `[car]`, `debug.log` и снимок должны
совпадать побайтно до и после рефакторинга. Остальные переключатели `RE_*` — в NATIVE_GAPS.md и DIAGNOSTICS.md.

## tools/

| Группа | Скрипты |
|---|---|
| таблицы `.data` из Game.exe → `re/game/*.h` | `gen_pNN_data.py`, `gen_p84_handlers.py`, `gen_sintab.py`, `gen_data_init.py` (data_init.c, data_image.c), `gen_gvar_img.py` |
| связки и таблицы адресов | `gen_fn_table.py` (fn_table.c из install.c), `gen_thunk_table.py`, `gen_native_links.py` (links.c; после v2.x файл правился и вручную — сверять дифф), `gen_stdcall.py` |
| проверки | `find_gvar_bypass.py`, `find_split_alias.py`, `mark_thunks.py`, `pedump.py` |
| одноразовые шаги начала проекта (v0.x), оставлены для воспроизводимости | `name_pass1.py`, `split_modules.py` (создал `src/`), `gen_glide.py` (пишет в /tmp), `redriver2_funcs.txt` |
| данные игрока | `texpack.py` (HD-пак), `driver_save.py` (сейвы), `make_music_stubs.py` |
| документация | `gen_module_index.py` → docs/MODULES.md |

Генераторы читают **вашу** копию Game.exe; ни Game.exe, ни данные игры, ни HD-пак в репозиторий не коммитятся.
