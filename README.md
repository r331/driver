# Driver (PC, 1999) — декомпиляция и перенос на C

Восстановление игры **Driver** (Reflections Interactive / GT Interactive, PC, 1999) в виде исходного кода на C
по оригинальному исполняемому файлу:

- `Game.exe` (на диске ставится как `DRIVER.EXE`), PE32, база 0x400000, сборка **1999-09-10** 16:35:21 UTC, линкер MSVC 6.0;
- MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`, SHA1 `06ae86374f5df850c678583b556a9a4bc9811575` (подробности — [docs/binary-info.md](docs/binary-info.md)).

**Игровые файлы и `Game.exe` в репозиторий не входят.** Для запуска нужна собственная копия игры (CD Driver PC).

Одна кодовая база (`re/`), две цели сборки:
- **native** — самостоятельная программа на SDL2 + OpenGL 3.3, использует только данные игры (`Data_Files`);
- **hook** — прокси `DINPUT.dll` для оригинального `Game.exe`: перенесённые функции подменяют оригинальные прямо в живой игре
  (так каждую функцию можно сверить с оригиналом).

## Статус

**Перенос функций:** по [docs/functions.csv](docs/functions.csv) — **3292 из 3292** функций Game.exe без CRT имеют `status=ported`
(всего в таблице 3632 функции; 340 функций MSVC CRT не переносятся — в native их заменяют libc и `re/platform/native/crt_msvc.c`).

Подсчёт:

```sh
python3 -c "import csv; r=[x for x in csv.DictReader(open('docs/functions.csv')) if x['module']!='CRT']; print(sum(x['status']=='ported' for x in r), 'из', len(r))"
```

**Native как игра — v2.13** (проверено сценариями `RE_KEYS` под Xvfb, Linux arm64; v2.13 — сборка и selftest на macOS arm64 в CI):
- работает: заставки и главное меню, режим **Take A Ride** в Майами — езда по городу (стриминг блоков карты), трафик, столкновения, HUD (Damage/Felony, радар, спидометр);
- управление машиной: газ, тормоз/задний ход, ручник, резкий руль, смена камеры (вид с капота), пауза по Esc с меню (Continue / Restart / Sound Setup / Gfx Details / Film Director / Quick Replay / Show Map / Exit) — см. «Управление»;
- звук: DirectSound эмулируется собственным микшером (SDL_audio или запись в WAV), двигатель и шумы слышны, мягкий ограничитель — без клиппинга; музыки нет (в оригинале — CD-audio);
- пешеходы: 12–16 активны, модель рисуется (проверено, когда пешеход стоит перед машиной); на обычном прогоне они появляются в ~34 500 единиц от игрока, а рисуются ближе 15 000 — чтобы увидеть, надо подъехать;
- копы: патрульная машина (предел 4); v2.12 — погоня работает: когда коп рядом (проверено отладочной перестановкой RE_COPNEAR), Felony растёт до предела, подключаются до 4 копов, преследуют и таранят; без отладки патруль к игроку пока не подходит;
- Undercover: интервью в гараже запускается; с пропуском интервью (RE_SKIP_INTERVIEW=1, как чит) — мотель, автоответчик (←/→ — кнопка, Enter — действие, «принять» — миссия) и **первая миссия Майами** «Get to the bank.» (прохождение не проверено);
- гудок H слышен (v2.12: 3D-источник у машины);
- не проверены/не работают: ночь и другие города (SF, LA, NY); FMV-ролики пропускаются.

Подробно: [docs/NATIVE_GAPS.md](docs/NATIVE_GAPS.md) (разрывы native, переключатели отладки), [docs/PLATFORM_PLAN.md](docs/PLATFORM_PLAN.md) (журнал переноса по шагам),
[re/README.md](re/README.md) (правила переноса и история версий).

## Структура каталогов

| Каталог | Что внутри |
|---|---|
| `re/game/` | перенесённые модули игры на C (`ported*.c`, меню, Director, сгенерированные таблицы `.data` Game.exe); без WinAPI |
| `re/platform/sdl/` | SDL2/OpenGL-реализация платформы: окно, рендер (эмуляция DirectDraw/D3D/Glide на GL 3.3), ввод (DirectInput → SDL), заглушки звука |
| `re/platform/win32/` | hook-сборка: прокси `DINPUT.dll`, перехват функций Game.exe (JMP rel32), `install.c` — список подменённых функций |
| `re/platform/native/` | точка входа native (`main.c`), заглушки неперенесённого, связки, замены MSVC CRT |
| `re/tests/` | самопроверка перенесённых модулей (`driver --selftest`, запускается через ctest), тест рендера и звука |
| `docs/` | `functions.csv` (все функции, имена, модули, статус), `binary-info.md`, планы и журнал переноса |
| `tools/` | Python-генераторы: таблицы данных из Game.exe (`gen_*.py`), разметка thunk-ов, разбиение на модули, `pedump.py` |
| `scripts/` | скрипты Ghidra (экспорт функций и псевдо-C, применение имён, перекрёстные ссылки строк) и их запуск |
| `src/` | псевдо-C из Ghidra, разложенный по модулям оригинала (`Director.c`, `MScript.c`, `frontend/` …) — справочный материал, в сборку не входит |

## Сборка

Команды ниже — из корня репозитория. Те же шаги делает `re/build.sh native` (каталог сборки `re/build-native/`).

> Собрано и проверено на **Linux arm64** (Debian 13, gcc 14, SDL 2.32, CMake 3.31) в чистом клоне.
> На Linux x86_64 и на реальном Mac **не проверялось**.

### Linux (проверенный путь)

```sh
sudo apt-get update
sudo apt-get install -y build-essential cmake libsdl2-dev libgl-dev libegl-dev libosmesa6-dev
# по желанию: xvfb (запуск без экрана), gcc-mingw-w64-i686 (hook-сборка), unshield (распаковка данных с CD)

cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release
cmake --build build-native -j
(cd build-native && ctest --output-on-failure)     # selftest
```

Результат — `build-native/driver`. `libosmesa6-dev` нужен только для offscreen-теста рендера в selftest: если OSMesa не найден,
CMake подключает `plat_render_nogl.c` и тест рендера пропускается. С libGL программа не линкуется — GL-функции берутся через `SDL_GL_GetProcAddress`.

### macOS (Apple Silicon)

Проверено в CI GitHub Actions: раннер `macos-14` (arm64, Apple clang 15) — сборка Release, `ctest` (selftest),
запуск без данных, сборка `Driver.app` с вложенным SDL ([.github/workflows/macos.yml](.github/workflows/macos.yml)).
**Не проверено:** запуск игры с окном (OpenGL 3.3 core, звук, ввод) на реальном Mac — в CI нет данных игры и экрана.

```sh
brew install cmake sdl2          # Homebrew ставит sdl2-compat (API SDL2 поверх SDL3)
cd re && ./build.sh native       # -> re/build-native/driver, затем ctest
./build-native/driver --data /путь/к/запуску   # см. «Запуск»
# приложение: Driver.app (SDL2 из Homebrew; для переноса на другой Mac — см. артефакт CI, где SDL вложен)
cmake -S . -B build-app -DCMAKE_BUILD_TYPE=Release -DRE_MACOS_BUNDLE=ON && cmake --build build-app -j
```

Ветка `APPLE` в `re/CMakeLists.txt`: SDL2 ищется в Homebrew (`/opt/homebrew`, `/usr/local`), OpenGL framework не линкуется
(GL-функции — через `SDL_GL_GetProcAddress`), контекст 3.3 core forward-compatible, offscreen-тест рендера (OSMesa) — только Linux.
Данные игры (`Data_Files` с `FSIN.DAT`) ищутся: `--data <путь>`, `./Data_Files`, рядом с бинарником, в `Driver.app/Contents/Resources/Data_Files`
или рядом с `Driver.app` — подробно в [re/README_macOS.txt](re/README_macOS.txt). Готовый `Driver.app` из CI (артефакт `driver-macos-arm64`)
подписан только ad-hoc: первый запуск — правый клик → «Открыть» или `xattr -dr com.apple.quarantine Driver.app`.

**Что запускается в CI** (файлов игры там нет): `ctest -L nodata` — `driver --selftest`, модульные проверки перенесённых функций
на синтетических данных (тест настоящего уровня `RE_REAL_LEVEL` и рендер-снимок OSMesa на macOS пропускаются); Linux x86_64 —
то же плюс hook-сборка `DINPUT.dll` ([.github/workflows/linux.yml](.github/workflows/linux.yml)).

## Запуск

### Данные игры

Нужен каталог `Data_Files` вашей копии игры (признак — в нём есть `FSIN.DAT`). На CD данные лежат в InstallShield-архиве `DATA1.CAB`:

```sh
unshield -d driver-cd x /путь/к/CD/DATA1.CAB    # -> driver-cd/Data_Files, driver-cd/Program_Executable_Files/Game.exe
```

Игра пишет в рабочий каталог (`config.dat`, `debug.log`, `SAVES/`, `Scripts/Waypoint.tmp`, `ReplayData/`). Чтобы не трогать копию игры,
соберите отдельный каталог запуска: симлинки на файлы `Data_Files`, а `Scripts` и `ReplayData` — копии:

```sh
GAME=/путь/к/driver-cd/Data_Files
RUN=$HOME/driver-run
mkdir -p "$RUN" && cd "$RUN"
for f in "$GAME"/*; do
  case "$(basename "$f")" in Scripts|ReplayData) cp -R "$f" . ;; *) ln -sf "$f" . ;; esac
done
```

### Запуск

```sh
./build-native/driver --data "$RUN"
```

Без `--data` программа ищет `Data_Files` в текущем каталоге. Прочие ключи: `--selftest` (самопроверка, данные не нужны),
`--frames N` (то же, что `RE_MAX_FRAMES=N`), `--idle` (пустое окно, без игры).

Без экрана (так проверялось):

```sh
RE_NO_MSGBOX=1 RE_MAX_FRAMES=300 RE_SHOT_PNG=menu.png \
  xvfb-run -a -s "-screen 0 1024x768x24" ./build-native/driver --data "$RUN"
```

Take A Ride в Майами по сценарию нажатий (меню: LEFT×3 → Take A Ride, RETURN×3 — город Miami и старт; затем газ и поворот):

```sh
RE_NO_MSGBOX=1 RE_FIXED_DT=1 RE_MAX_FRAMES=1100 RE_SHOT_PNG=ride.png \
RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,700:APOSTROPHE:300,850:X:25" \
  xvfb-run -a -s "-screen 0 1024x768x24" ./build-native/driver --data "$RUN"
```

### Управление

Раскладка Driver PC по умолчанию (`P37_InitInput`, таблица 0054b7a8; биты клавиш машины — `P36_GetPadButtons` → `P107_CarInput`).
«Проверено» — сценарием `RE_KEYS` (скорость/руль из `RE_CARDBG`, снимки PNG), v2.10.

| Действие | Клавиша | Проверено |
|---|---|---|
| газ | `'` (апостроф) | да — скорость растёт |
| тормоз / задний ход | `/` | да — скорость падает до 0, затем машина едет назад |
| руль влево / вправо | `Z` / `X` | да |
| ручник | `Enter` | да — скорость падает до 0 даже с нажатым газом |
| резкий руль (быстрее и до 511 вместо 352) | `пробел` | да — по значению руля |
| смена камеры (сзади → капот → …) | `1` | да — снимок с капота |
| ТВ-камера / неподвижная | `2` | нет |
| взгляд влево / вправо / назад | `J` / `K` / `L` | нет |
| гудок (сирена в режиме копа) | `H` | нет — в записи звука разницы не слышно |
| круиз-контроль | `C` | нет |
| бит 0x40 (`\`, пробуксовка на старте) | `\` | нет |
| дальность прорисовки − / + | `F1` / `F2` | нет |
| дальность зеркала − / + | `F3` / `F4` | нет |
| пауза (меню паузы) | `Esc` | да — снимок меню паузы |
| снимок экрана (BMP) | `F12` | нет |

Меню: стрелки, Enter — выбор. Геймпад (первый SDL GameController): крестовина и левый стик → стрелки, A/Start → Enter, B/Back → Esc, X → пробел.

### Переменные окружения

| Переменная | Действие |
|---|---|
| `RE_MAX_FRAMES=N` | выход с кодом 0 после N-го показанного кадра |
| `RE_SHOT_PNG=путь` | снимок кадра N (`RE_MAX_FRAMES`) в PNG; с `RE_SHOT_FIRST=1` — первого кадра. Программа делает `chdir` в каталог данных, поэтому относительный путь считается от `$RUN` (`menu.png`, `ride.png` из примеров окажутся там) |
| `RE_KEYS="кадр:клавиша[:кадров],…"` | сценарий нажатий: клавиша нажата с кадра N на `RE_KEYS_HOLD` кадров (по умолчанию 2) или на указанное число; клавиша — имя (`UP DOWN LEFT RIGHT RETURN ENTER ESC SPACE TAB F1..F12 A..Z 0..9 APOSTROPHE LSHIFT …`) или код DIK (`0x28`) |
| `RE_FIXED_DT=1` | виртуальные часы (20 мс на кадр) — воспроизводимые прогоны, не зависят от скорости компьютера |
| `RE_NO_MSGBOX=1` | сообщения MessageBox только в stderr (под Xvfb окно сообщения блокирует) |
| `RE_WATCHDOG=N` | через N секунд печать стека и выход с кодом 3 |

Остальные отладочные переключатели (`RE_TRACE*`, `RE_GSTAT`, `RE_CARDBG` …) описаны в [docs/NATIVE_GAPS.md](docs/NATIVE_GAPS.md).

## Hook-сборка для Windows (proxy DINPUT.dll)

Game.exe импортирует из `DINPUT.dll` только `DirectInputCreateA`. Прокси-DLL экспортирует её же (передаёт вызов системной `dinput.dll`),
а при загрузке ставит перехваты на перенесённые функции (в `re/platform/win32/install.c` — 2265 вызовов `re_hook`).

Сборка — MinGW i686 (на Linux проверено, Windows-запуск не проверялся):

```sh
sudo apt-get install -y gcc-mingw-w64-i686      # macOS: brew install mingw-w64 (не проверялось)
sh re/build.sh hook                              # -> re/build/DINPUT.dll
```

В `re/CMakeLists.txt` есть ветка `RE_HOOK_BUILD`, но она не проверялась и не включает все файлы `platform/win32` и библиотеки,
которые использует `build.sh hook`; рабочий путь — `build.sh hook`. Сборка MSVC не поддерживается и не проверялась.

Установка: положить `DINPUT.dll` **рядом с `Game.exe`** (MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`; другие версии exe не поддерживаются) и запустить игру.
Под Wine (из `re/README.md`, здесь не проверялось): `WINEDLLOVERRIDES="dinput=n,b" wine Game.exe`.

Как проверить, что подхват работает: в рабочем каталоге игры появляется `re_driver.log`. Первая строка —
`re_driver: Driver (PC, 1999) reconstruction layer`, дальше по строке на функцию: `hook   <адрес> <имя>`.
Ошибки: `ERROR: system dinput.dll not found`, `ERROR: Game.exe not at 0x400000`, `FAIL   <адрес> <имя>` (не удалось снять защиту страницы).
Отключить отдельную функцию: файл `re_driver.ini` рядом с игрой, секция `[disable]`, строка `ИмяФункции=1`
(в логе будет `skip   <адрес> <имя> (disabled in ini)`).

## Правовая оговорка

Driver — собственность её правообладателей (Reflections Interactive / GT Interactive и их правопреемников).
Репозиторий не содержит файлов игры: ни `Game.exe`, ни данных (`Data_Files`), ни образа диска. Это исследовательский проект
по восстановлению кода; для запуска нужна легально приобретённая копия игры.

---

## English summary

A decompilation and C port of **Driver** (PC, 1999, Reflections / GT Interactive), based on `Game.exe` built 1999-09-10
(MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`). **No game files are included** — you need your own copy of the game (CD).

- **Status:** 3292 of 3292 non-CRT functions are marked `ported` in `docs/functions.csv`. The native build (v2.12) runs the menus and
  *Take A Ride* in Miami (driving, traffic, HUD, brake/reverse, handbrake, bonnet camera, Esc pause menu) with sound (own DirectSound
  mixer, soft limiter; no CD music). Pedestrians are rendered but appear far from the player; cops pursue and ram the player once felony
  is raised (verified with a debug placement); FMV is skipped; Undercover reaches the motel and the first Miami mission. See `docs/NATIVE_GAPS.md`.
- **Build (Linux, verified on arm64):** `apt-get install build-essential cmake libsdl2-dev libgl-dev libegl-dev libosmesa6-dev`, then
  `cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release && cmake --build build-native -j && (cd build-native && ctest --output-on-failure)`.
  macOS (Apple Silicon): `brew install cmake sdl2`, same commands; build + selftest verified in GitHub Actions on `macos-14` (arm64),
  `-DRE_MACOS_BUNDLE=ON` builds `Driver.app`. Running the game with a window on a real Mac is not tested yet.
- **Run:** `./build-native/driver --data <run dir>`, where the run dir symlinks your `Data_Files` and holds copies of `Scripts` and `ReplayData`
  (the game writes there). Controls: arrows/Enter in menus, `'` throttle, `/` brake/reverse, `Z`/`X` steering, Enter handbrake, `1` camera, Esc pause, gamepad supported.
- **Hook build:** `sh re/build.sh hook` (MinGW i686) produces a proxy `DINPUT.dll`; put it next to `Game.exe`, check `re_driver.log`.
  Windows run not tested.
- Driver is the property of its rights holders; this repository contains none of their files.
