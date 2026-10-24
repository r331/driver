[English](README.md) | **Русский**

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

**Native как игра — v2.37** (проверено сценариями `RE_KEYS` и настоящей клавиатурой X11 (xdotool) под Xvfb, Linux arm64; сборка, selftest и inputtest — на macOS arm64 в CI):
- работает: заставки и главное меню, режим **Take A Ride** в Майами — езда по городу (стриминг блоков карты), трафик, столкновения, HUD (Damage/Felony, радар, спидометр);
- управление машиной: газ, тормоз/задний ход, ручник, резкий руль, смена камеры (вид с капота), пауза по Esc с меню (Continue / Restart / Sound Setup / Gfx Details / Film Director / Quick Replay / Show Map / Exit) — см. «Управление»;
- звук: DirectSound эмулируется собственным микшером (SDL_audio или запись в WAV), двигатель и шумы слышны, мягкий ограничитель — без клиппинга; музыка — эмуляция CD-audio (v2.22, дорожки из файлов вашего диска — см. «CD-музыка»);
- пешеходы: 12–16 активны, модель рисуется (проверено, когда пешеход стоит перед машиной); на обычном прогоне они появляются в ~34 500 единиц от игрока, а рисуются ближе 15 000 — чтобы увидеть, надо подъехать;
- копы: патрульная машина (предел 4); v2.12 — погоня работает: когда коп рядом, Felony растёт до предела, подключаются до 4 копов, преследуют и таранят; v2.34 — патруль сам выходит на игрока и едет следом (без отладки RE_COPNEAR): исправлен режим округления x87 (у Game.exe — к нулю), из-за которого копы не находили маршрут и останавливались; в Survival копы преследуют;
- Undercover: интервью в гараже запускается; с пропуском интервью (RE_SKIP_INTERVIEW=1, как чит) — мотель, автоответчик (←/→ — кнопка, Enter — действие, «принять» — миссия) и **первая миссия Майами** «Get to the bank.» (прохождение не проверено);
- гудок H слышен (v2.12: 3D-источник у машины);
- v2.14: нативное разрешение — кадр игры 4:3 вписывается в окно/экран любого размера (Retina, 1080p, 2560×1600) с полосами по бокам; 3D растеризуется в разрешении экрана; на macOS по умолчанию полный экран; езда стрелками и пробелом (ручник) в дополнение к оригинальным клавишам;
- v2.15: любое соотношение сторон (Hor+) — на широком экране (16:10, 16:9, 21:9, 32:9) вертикальный угол как в оригинале, а по бокам видно больше города; HUD прижат к краям экрана, меню — по центру 4:3; см. «Разрешение и соотношение сторон»;
- v2.16: улучшение графики — MSAA (2/4/8x, мультисэмпловый FBO) с alpha-to-coverage для пальм и заборов, FXAA, render_scale 0.5–2.0 (SSAA), мипмапы без ореолов, анизотропная фильтрация до 16x, выбор фильтрации, чёткий HUD (sharp-bilinear), vsync/ограничение FPS, гамма/яркость; файл `driver.cfg` и пресеты original/enhanced — см. «Графика»;
- v2.17: HD-текстуры — подмена страниц текстур апскейлом (PNG 1024×1024) из своего пака, `RE_TEXPACK`/`texpack` — см. «HD-текстуры»;
- v2.18: HD-текстуры и для 8-битных (палитровых) страниц — по файлу на пару «страница × палитра»; подмена работает и в самой игре (раньше — только в проверке рендера);
- v2.19: дальность прорисовки — `draw_distance` (множитель 1.0–4.0, в `enhanced` — 2.0): дальние кварталы видны, логика игры не меняется — см. «Графика»;
- v2.22: CD-музыка — эмуляция привода CD-audio: дорожки `Music/TrackNN.wav|flac|ogg|mp3` или образ `.cue/.bin`, без файлов — тишина; цикл и громкость как в оригинале — см. «CD-музыка»;
- v2.34: музыка автоматически подхватывается из HD-пака (`<texpack>/Music`), если `Music/` нет в каталоге данных;
- v2.33: динамическая музыка в стиле PlayStation (по желанию): свои 16 файлов в `Music/dynamic/` — у каждого города день/ночь × Drive/Chase, при погоне копов кроссфейд на Chase и обратно — см. «CD-музыка»;
- v2.23: исправлен серый полигон поверх неба (чаще слева вверху) — плоские/гуро-полигоны ближнего набора отсекаются по z = 1, вершины за камерой больше не уходят в угол экрана;
- v2.35: слиты все расщеплённые псевдонимы образа данных (осталось 0): у каждого адреса Game.exe в native один объект. Заработали проверки скрипта событий, которых раньше не было: «You lost your target» по удалению от цели (004f5012), освобождение списка событий между миссиями, продвижение скрипта у шести команд, пыль, подсветка пункта меню; Take A Ride и Survival не изменились (побайтно) — см. docs/NATIVE_GAPS.md «Исправлено в v2.35»;
- v2.36: секундомер интервью в гараже (циферблат и корпус) и цифры часов миссии (Майами) в HD-паке перерисованы нейросетью — чёткие, с гладким краем; вариант `hud_hd` пака, выкл. `RE_TEXPACK_HUD=0` — см. «HD-текстуры»;
- v2.37: единый отладочный журнал `RE_LOG` (выключен по умолчанию): `RE_LOG=all:info` → `driver.log` (macOS — `~/Library/Logs/Driver/driver.log`) — старт и настройки, файлы и уровни, меню и миссии (итог и причина провала), сейвы, звук, геймпады, ошибки; каналы и уровни — см. docs/DIAGNOSTICS.md «RE_LOG»;
- v2.39: HD-текстуры грузятся в фоне: машина или объект, впервые попавшие в кадр (например, полицейские машины заслона), несколько кадров рисуются с оригинальной текстурой вместо остановки кадра на декодирование PNG; `RE_TEXPACK_ASYNC=0` / `texpack_async = 0` — прежняя синхронная загрузка — см. «HD-текстуры» и docs/PERFORMANCE.md;
- не проверены/не работают: ночь и другие города (SF, LA, NY); FMV-ролики пропускаются.

Подробно: [docs/NATIVE_GAPS.md](docs/NATIVE_GAPS.md) (разрывы native, переключатели отладки), [docs/PLATFORM_PLAN.md](docs/PLATFORM_PLAN.md) (журнал переноса по шагам),
[re/README.md](re/README.md) (правила переноса и история версий).

## Структура каталогов

Как устроен код и как связаны две цели сборки — [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md); указатель модулей `re/game/` — [docs/MODULES.md](docs/MODULES.md).

| Каталог | Что внутри |
|---|---|
| `re/game/` | перенесённые модули игры на C (`ported*.c`, меню, Director, сгенерированные таблицы `.data` Game.exe); без WinAPI |
| `re/platform/sdl/` | SDL2/OpenGL-реализация платформы: окно, рендер (эмуляция DirectDraw/D3D/Glide на GL 3.3), ввод (DirectInput → SDL), заглушки звука |
| `re/platform/win32/` | hook-сборка: прокси `DINPUT.dll`, перехват функций Game.exe (JMP rel32), `install.c` — список подменённых функций |
| `re/platform/native/` | точка входа native (`main.c`), заглушки неперенесённого, связки, замены MSVC CRT |
| `re/tests/` | самопроверка перенесённых модулей (`driver --selftest`, запускается через ctest), тест рендера и звука |
| `docs/` | `ARCHITECTURE.md` (карта кода), `MODULES.md` (указатель модулей), `DEAD_CODE_AUDIT.md` (подозрительное, оставленное на месте), `functions.csv` (все функции, имена, модули, статус), `binary-info.md`, планы и журнал переноса |
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
Steam Controller (2026) системный SDL2 Classic не видит — для него сборка с `-DRE_SDL3_COMPAT=ON`, пакеты и udev-правила: раздел «Gamepads on Linux» ниже.

### macOS (Apple Silicon)

Проверено в CI GitHub Actions: раннер `macos-14` (arm64, Apple clang 15) — сборка Release, `ctest` (selftest),
запуск без данных, сборка `Driver.app` с вложенным SDL ([.github/workflows/macos.yml](.github/workflows/macos.yml)).
Роман запустил v2.13 на Mac M1: окно и картинка есть, «управление не работает». Точная причина не установлена (на Mac
не воспроизводилось); в v2.14 исправлено всё, что могло дать такой эффект (см. ниже), и добавлен журнал ввода `RE_INPUTDBG=1`.

**macOS: клавиши, разрешение, журнал ввода (v2.14)**

- Езда: **стрелки** (↑ газ, ↓ тормоз/назад, ←/→ руль), **пробел** — ручник; оригинальные клавиши тоже работают
  (`'` газ, `/` тормоз, `Z`/`X` руль, `Enter` ручник). В меню стрелки по-прежнему листают пункты, `Enter` — выбор, `Esc` — назад/пауза.
  Клавиши берутся по физическому положению (scancode) — раскладка (русская и т. п.) не важна. `RE_ARROWKEYS=0` — без стрелок в езде.
- Полный экран по умолчанию (во весь дисплей, в нативном разрешении Retina); **Cmd+Enter** (или Alt/Option+Enter) — окно/полный экран.
  `RE_WINDOWED=1` — запуск в окне, `RE_RES=1440x1080` — размер окна в точках, `RE_FULLSCREEN=1` — принудительно полный экран.
  3D рисуется в полном разрешении экрана и на всю его ширину (v2.15, Hor+ — см. «Разрешение и соотношение сторон»), меню — 4:3 по центру,
  HUD — у краёв экрана, без растяжения. Cmd+Q или закрытие окна — выход.
- Если клавиши не работают: запустите из Терминала
  `RE_INPUTDBG=1 ./Driver.app/Contents/MacOS/Driver` (или `RE_INPUTDBG=1 ./driver --data …`), понажимайте клавиши в меню и в езде,
  закройте игру и пришлите файл **`~/Library/Logs/driver_input.log`** — там версия SDL, поток цикла событий, события окна/фокуса,
  каждое нажатие (scancode → DIK) и что из этого увидела игра.

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

**Installer for another Apple Silicon Mac:** `scripts/package_macos.py` builds a self-contained DMG with your original game data and optional HD textures. Install by dragging Driver.app to Applications; saves stay in Application Support. The local HD installer is `dist/Driver-AppleSilicon.dmg`. See [packaging and verification](docs/MACOS_DMG.md).

**Что запускается в CI** (файлов игры там нет): `ctest -L nodata` — `driver --inputtest` (v2.14: цикл событий в главном потоке —
`pthread_main_np`, событие клавиши через `SDL_PushEvent` → разбор событий игры → DIK, Cmd+Enter, биты езды стрелками, вписывание кадра)
и `driver --selftest`, модульные проверки перенесённых функций
на синтетических данных (тест настоящего уровня `RE_REAL_LEVEL` и рендер-снимок OSMesa на macOS пропускаются); Linux x86_64 —
то же плюс hook-сборка `DINPUT.dll` и (v2.32) job `native-sdl3`: сборка с `RE_SDL3_COMPAT=ON`, ctest и проверка переносимости `driver` + `sdl-runtime/` ([.github/workflows/linux.yml](.github/workflows/linux.yml)).

## Разрешение и соотношение сторон

С v2.15 native-сборка рисует 3D на всю ширину экрана любого соотношения сторон (**Hor+**): вертикальный угол обзора как в оригинале
(фокус 384 при высоте 480, ≈ 64°), горизонтальный растёт с аспектом — на 16:9 ≈ 96° вместо 79.6° у 4:3, на 21:9 ≈ 112°, на 32:9 ≈ 131°.
Картинка не растягивается: логический кадр игры — (480·аспект)×480, 3D растеризуется в нативном разрешении (Retina — в пикселях).

- `RE_ASPECT=auto` (по умолчанию) — по размеру окна/экрана; `RE_ASPECT=4:3` — как в оригинале (кадр 4:3 с полосами по бокам, как v2.14);
  `RE_ASPECT=21:9` (любое `W:H` или число `2.35`) — кадр этого аспекта, остаток окна — полосы.
- Экран уже 4:3 (портрет, 5:4) — кадр 4:3 по ширине с полосами сверху и снизу (letterbox); угол не меняется.
- Меню, фронтенд и меню паузы — 640×480 по центру с полосами (pillarbox). HUD в езде привязан к краям: Damage/Felony — слева сверху,
  радар и спидометр — справа снизу, счётчики режимов — справа сверху, часы миссии и сообщения — по центру.
- Отсечение расширено в коде: окно отсечения 3D, боковые плоскости пирамиды, обход клеток карты (объединение соседних секторов
  `FRUSTRUM.DAT` — сам файл не меняется), экранные проверки спрайтов/огней. Hook-сборка (DINPUT.dll) работает как оригинал (4:3).
- Проверено на Linux под Xvfb (1920×1080, 2560×1600, 3440×1440, 5120×1440, 1080×1920); на реальном Mac — пока нет.

## Графика

С v2.16 native-сборка рисует кадр игры во внеэкранный буфер (FBO) и выводит его в окно пост-проходом. Игровая логика не меняется
(детерминизм `RE_FIXED_DT` тот же); hook-сборка (DINPUT.dll) рисует как оригинал.

- **Сглаживание:** MSAA 2/4/8x — мультисэмпловый FBO с resolve (не default framebuffer); alpha-to-coverage для текстур с альфа-тестом
  (пальмы, заборы, деревья, шлагбаумы) — край прозрачности сглаживается вместе с MSAA; FXAA — пост-проход (шейдер в коде);
  `render_scale` 0.5–2.0 — разрешение кадра относительно окна (2.0 = SSAA 4x, 0.5 — для слабых машин; HUD рисуется в том же кадре).
- **Текстуры:** свои мипмапы для страниц текстур игры: цвет видимых соседей переносится в прозрачные пиксели (dilation), уменьшение
  взвешено альфой, у chroma-key-текстур сохраняется доля видимых пикселей — вдали нет чёрных/пурпурных ореолов и «облысения» пальм.
  Игра рисует страницы ARGB1555 и с «видно при альфе 0» (ALPHAFUNC LESS), и с обычной семантикой, поэтому обработанная копия
  строится под ту семантику, с которой текстуру рисуют (рисование без альфа-теста — исходная картинка).
  Анизотропная фильтрация до 16x (если драйвер даёт `GL_EXT/ARB_texture_filter_anisotropic`, на macOS — есть); фильтрация 3D:
  `nearest` (оригинально-пиксельная), `linear`, `trilinear`.
- **HUD/меню/шрифты:** `sharp-bilinear` — внутри текселя чёткий цвет, на границе — переход в один пиксель экрана (шрифты меню не мылятся
  при масштабе 640×480 → 1080p/Retina); можно `linear` или `nearest`.
- **Прочее:** vsync on/off/adaptive, ограничение FPS, гамма и яркость (пост-проход), лёгкая резкость (`sharpen`).
- Нет поддержки (нет MSAA нужной кратности, нет анизотропии, FBO не создаётся) — понижение/выключение с сообщением `[gfx]` в stderr, без падения.

**Пресеты:** `enhanced` (по умолчанию) — MSAA 4x + alpha-to-coverage, анизотропия 16x, трилинейная, мипмапы, dilation, HUD sharp, FXAA выкл.;
`original` — как v2.15: билинейная без мипмапов, без сглаживания, HUD линейно.

**Файл `driver.cfg`** (первый найденный): `$RE_CFG`; рядом с бинарником; macOS — `~/Library/Application Support/Driver/driver.cfg`;
Linux — `${XDG_CONFIG_HOME:-~/.config}/driver/driver.cfg`. Переменные `RE_*` важнее файла. Полный пример с пояснениями — `re/driver.cfg.example`:

```ini
preset       = enhanced    # enhanced | original
msaa         = 4           # 0 | 2 | 4 | 8
a2c          = on          # alpha-to-coverage (при msaa)
fxaa         = off
aniso        = 16          # 1..16
mipmaps      = on
filter       = trilinear   # nearest | linear | trilinear
hud_filter   = sharp       # sharp | linear | nearest
render_scale = 1.0         # 0.5..2.0
draw_distance = 2.0        # 1.0 (оригинал) .. 4.0
vsync        = on          # on | off | adaptive
fps_limit    = 0           # 0 — без ограничения
gamma        = 1.0
brightness   = 1.0
aspect       = auto        # auto | 4:3 | 21:9 …
fullscreen   = 1
windowed_res = 1600x900
```

**Gamepads / Steam Controller (2026):** native controls work in menus and while driving. On this Mac, the 2026 controller is detected over USB/Puck with SDL3 3.4.18 through SDL2-compat 2.32.74. Build with the pinned modern runtime (the first configure downloads the upstream archives):

```sh
cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release -DRE_MACOS_BUNDLE=ON -DRE_SDL3_COMPAT=ON
cmake --build build-native -j8
```

The modern SDL libraries are built into `Driver.app/Contents/Frameworks`; the system SDL installation stays unchanged. `RE_SDL3_COMPAT=OFF` uses the existing system SDL2. The older SDL2 Classic driver does not support the 2026 controller's native USB/Puck protocol. Controller discovery starts after SDL creates the window, and supports connecting or reconnecting while the game is running.

| Controller | Driving | Menus |
|---|---|---|
| Left stick / D-pad left/right | Steer | Navigate |
| RT / LT | Throttle / brake and reverse | — |
| D-pad up/down | Throttle / brake and reverse | Navigate |
| A / B | Handbrake | Confirm / back |
| X | Burnout | — |
| Y | Change camera | — |
| Left stick click | Horn | — |
| LB / RB | Look back / hard turn | — |
| Menu / View | Pause | Confirm / back |

Driving buttons follow the game's keyboard bindings, including changes made in its options. Steering and pedals currently use the game's digital action path, with stick/trigger deadzones. Keyboard input remains available. Held buttons are suppressed when crossing between menus and gameplay until released. `RE_GAMEPAD=0` disables native controller handling, useful with a Steam Input keyboard layout to avoid duplicate input. Damage vibration sends short pulses for crashes into cars and scenery, scaled to the damage received. Vibration stops on pause, focus loss, or disconnect; `RE_RUMBLE=0` disables it. Gyro and trackpad gestures are not mapped by this implementation.

Use `RE_INPUTDBG=1` to log detection, mapping, axes, buttons, and delivered game keys (`~/Library/Logs/driver_input.log` on macOS). `RE_DIAG=1` also records device connection/disconnection in the diagnostic session. For Steam Input, choose a conventional gamepad layout; use the disable option above if choosing a keyboard layout instead.

**Gamepads on Linux (v2.32).** The input code is the same as on macOS, but distribution SDL2 packages are SDL2 Classic (Ubuntu 24.04 — 2.30, Debian 13 — 2.32.4) and do not know the 2026 controller either, so build the same pinned runtime with `RE_SDL3_COMPAT=ON`. Ubuntu/Debian packages (checked on Debian 13 arm64 and in CI on Ubuntu 24.04 x86_64):

```sh
sudo apt-get install -y build-essential cmake \
  libx11-dev libxext-dev libxcursor-dev libxi-dev libxrandr-dev libxtst-dev \
  libudev-dev libasound2-dev libpulse-dev libdbus-1-dev
# recommended: Wayland and extra X11 features
sudo apt-get install -y libwayland-dev libxkbcommon-dev libdecor-0-dev libxss-dev libxfixes-dev libusb-1.0-0-dev
# optional: libosmesa6-dev (offscreen render test in selftest)

cmake -S re -B build-sdl3 -DCMAKE_BUILD_TYPE=Release -DRE_SDL3_COMPAT=ON
cmake --build build-sdl3 -j
(cd build-sdl3 && ctest --output-on-failure -L nodata)
```

- The first line (`libx11-dev` … `libxtst-dev`) is the minimum for SDL3 to configure: without X11/Xext it stops with "could not find X11 or Wayland", and without `libxcursor-dev`, `libxi-dev`, `libxrandr-dev` or `libxtst-dev` with "Couldn't find dependency package for XCURSOR/XINPUT/XRANDR/XTEST". It builds without the rest, but then has **no sound** (`libasound2-dev`/`libpulse-dev`, or `libpipewire-0.3-dev`) and **no udev** (`libudev-dev`: device discovery and hotplug for HIDAPI/evdev). `libsdl2-dev` is not needed for this build. SDL3 picks optional backends silently, so check the configure summary: `Joystick drivers: hidapi linux virtual`, `SDL_LIBUDEV ON`, `Audio drivers: … alsa pulseaudio`.
- The result is `build-sdl3/driver` plus `build-sdl3/sdl-runtime/` (`libSDL2-2.0.so.0` = sdl2-compat 2.32.74, `libSDL3.so.0` = SDL3 3.4.18). The binary's RUNPATH is `$ORIGIN/sdl-runtime` and sdl2-compat's is `$ORIGIN` (it loads SDL3 with `dlopen`), so copy **`driver` and `sdl-runtime/` together**; the folder can live anywhere. Check with `ldd driver | grep SDL` — it must point to `…/sdl-runtime/`. At startup the game logs `[gamepad] SDL 2.32.74 (sdl2-compat/SDL3, …)`; `SDL Classic` there means the system SDL2 was picked up (the bundled folder is missing, or `LD_LIBRARY_PATH` overrides it). The CI artifact `driver-linux-x86_64-sdl3` (tar.gz with `driver` + `sdl-runtime/`) is built this way.
- **Device access.** SDL talks to the controller through `/dev/hidraw*` (HIDAPI). By default only root can open it, so install Valve's udev rules: `sudo apt-get install steam-devices` (Ubuntu: multiverse; Debian: contrib), or copy [60-steam-input.rules](https://github.com/ValveSoftware/steam-devices/blob/master/60-steam-input.rules) to `/etc/udev/rules.d/` and run `sudo udevadm control --reload-rules && sudo udevadm trigger`, then reconnect the controller/Puck. Without access the controller is not opened (or only appears through the kernel's generic evdev driver with a different mapping); `RE_INPUTDBG=1` (log `driver_input.log` next to the binary) shows what SDL opened.
- **Steam Input.** If Steam is running, it may hold the controller and present a virtual pad. Choose a conventional gamepad layout, or with a Steam Input keyboard layout run the game with `RE_GAMEPAD=0` to avoid duplicate input — same as on macOS.

**Дальность прорисовки (v2.19, `draw_distance`, env `RE_DRAW_DIST`):** множитель к дальности из опций игры (Gfx Details, 15 000–45 000
единиц; клетка карты — 3000): 1.0 — оригинал, до 4.0; `enhanced` — 2.0, `original` — 1.0. В оригинале дальность ограничивают: окно обхода
клеток 31×31 по таблице FRUSTRUM.DAT (радиус 15 клеток = 45 000) и PVS того же размера, дальняя плоскость (опция) и её копия для отсечения
полигонов, таблица 1/z на 56 250 элементов, 4 слота блоков карты (2×2 блока по 60 клеток в Майами). Native при множителе > 1 на время 3D-вида
умножает дальнюю плоскость, обходит клетки за окном 31×31 своей проверкой конуса (курс камеры — по осям FRUSTRUM.DAT, полуугол — боковые
плоскости с учётом Hor+; сама таблица не меняется), продолжает таблицу 1/z (k/z) и разбирает недостающие соседние блоки из уже загруженного
уровня в отдельный кэш только для отрисовки (до 2 блоков за кадр с предзагрузкой; слоты и дорожные данные игры не трогаются). Порог
низкополигональных машин (15 000) умножается так же. Глубина — 1 − n/z (24 бит), от дальней плоскости не зависит: точность вблизи та же.
Небо в native рисуется с глубиной 1.0: его исходное конечное смещение 32767 перекрывало дальние здания и дороги,
хотя расширенный обход карты уже отправлял их на отрисовку. UV и перспектива неба сохраняются.
Тумана в D3D-версии нет (функции тумана Glide в D3D-обёртке Game.exe — пустые), поэтому сдвигать нечего. Логика, ИИ, спавн, расстояния
пешеходов/копов — без изменений (позиции машины `RE_CARDBG` при 1.0 и 3.0 совпадают). Hook-сборка — как оригинал.

Переменные: `RE_PRESET`, `RE_MSAA`, `RE_A2C`, `RE_FXAA`, `RE_ANISO`, `RE_MIPMAPS`, `RE_DILATE`, `RE_FILTER`, `RE_HUD_FILTER`, `RE_RENDER_SCALE`,
`RE_VSYNC`, `RE_FPS_LIMIT`, `RE_GAMMA`, `RE_BRIGHTNESS`, `RE_SHARPEN`, `RE_DRAW_DIST`, `RE_CFG` (путь к файлу), `RE_NO_FBO=1` (рисовать прямо в окно, как v2.15),
`RE_FRAMESTAT=N` (время кадра с кадра N, итог при выходе по `RE_MAX_FRAMES`). Что реально включилось — строки `[gfx]` в stderr.

Проверено на Linux под Xvfb (Mesa llvmpipe: MSAA до 4x, анизотропия 16x); на реальном Mac — пока нет.

## Rendering diagnostics

To capture a rendering problem with a screenshot, car/camera position history,
graphics settings, model records and submitted vertices, see
[Rendering diagnostics](docs/DIAGNOSTICS.md). On macOS run
`sh scripts/run_diagnostics_macos.sh` and press **Cmd+Shift+D** at the problem.

## HD-текстуры

С v2.17 native-сборка может подменять 16-битные страницы текстур уровня (256×256, ARGB1555) картинками высокого разрешения
(PNG, квадрат 256..1024, обычно 1024×1024 — апскейл ×4 нейросетью). Пак — производная данных игры, поэтому в репозитории его нет:
его делают у себя из своей копии игры.

**Готовый пак (приватный):** [r331/driver-texpack](https://github.com/r331/driver-texpack) — апскейл ×4 (4x_foolhardy_Remacri),
NY_01 целиком, miami_01. Доступ только у владельца, не публиковать. Подключение: `git clone https://github.com/r331/driver-texpack.git`,
затем `texpack = /путь/driver-texpack` в `driver.cfg` или `RE_TEXPACK=/путь/driver-texpack` (16-бит — с v2.17, 8-бит и подмена в игре — с v2.18).

```sh
pip install numpy pillow torch spandrel          # torch — CPU-сборки достаточно
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --model 4x_foolhardy_Remacri.pth   # ~1 мин/страница на CPU
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --verify    # сверка: уменьшенный PNG ≈ своя страница
RE_TEXPACK=texpack ./driver                       # или в driver.cfg: texpack = /путь/к/texpack
```

Раскладка: `<каталог>/<уровень без .lev>/pNNN.png`, NNN — номер страницы в файле уровня (пара 8-битных страниц занимает два номера).
Модель — любая ESRGAN-совместимая ×4 (`.pth`/`.safetensors`, загружается spandrel).

**8-битные страницы (v2.18).** В NY почти все здания — 8-битные страницы: 256×256 индексов, цвет даёт палитра, которую игра выбирает
во время рисования (одна страница бывает нарисована разными палитрами — город, небо, время суток). Поэтому файл — на пару:
`<каталог>/<уровень>/pNNN_cKKKK.png`, KKKK — номер слота палитры уровня (0..49, как в файле уровня). Какие пары бывают, берётся из
`Levels/<город>.d3d` (для NY_01 — 97 пар). Прозрачного индекса у 8-битных страниц нет — PNG непрозрачный.

```sh
RE_TEXLOG=texlog.txt ./driver --selftest …        # необязательно: какие пары на экране и сколько площади (порядок генерации)
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --texlog texlog.txt --budget 3600   # ~30 с/пара на 2 ядрах
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --list      # что готово
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --verify    # сверка всех пар
```

Подмена в игре: 8-битная страница рисуется через поверхность слота с палитрой; по палитре поверхности находится слот палитры и
берётся готовая HD-текстура пары; 16-битная — картинка прикрепляется к поверхности слота и при загрузке сверяется с её содержимым.
Каталог уровня ищется как есть, строчными и ПРОПИСНЫМИ.
Альфа PNG = бит 0x8000 страницы (без сглаживания), цвет всех пикселей сохраняется — прозрачность по-прежнему решает альфа-тест игры.
При загрузке каждая картинка уменьшается до 256 и сверяется с исходной страницей; если не похожа (перепутан номер, испорчен файл) —
остаётся оригинал, в stderr `[texpack] … отклонён`. Итог: `[texpack] загружено N страниц`. Без `RE_TEXPACK`/`texpack` — всё как раньше.

**Фоновая загрузка (v2.39).** В игре 8-битная пара (страница, палитра) грузится при первом рисовании. С v2.39 PNG читается, декодируется,
сверяется и получает мипмапы в фоновых потоках (`RE_TEXPACK_THREADS`, по умолчанию 2), а пока рисуется оригинальная текстура; готовая текстура
загружается в GL в главном потоке после кадра, не дольше `texpack_upload_ms` / `RE_TEXPACK_UPLOAD_MS` за кадр (по умолчанию 2 мс, минимум одна текстура).
Новая машина несколько кадров видна в оригинальных цветах и затем переключается на HD — вместо остановки кадра (≈ 75 мс на две пары с прогретым
кэшем диска, 300+ мс с холодным). `texpack_async = 0` / `RE_TEXPACK_ASYNC=0` — прежняя синхронная загрузка; `RE_TEXPACK_PRELOAD=1` — все пары из списка
уровня грузятся при загрузке уровня (дольше загрузка, в игре грузить нечего; такие пары фоновый загрузчик не проходят).
Логика игры от текстур не зависит: симуляция одинакова во всех режимах.

**Секундомер интервью и цифры часов миссии (v2.36).** Секундомер интервью в гараже (уровень `iview`, 16-битная страница 8, область 96×128:
циферблат с делениями 5–55, корпус, кольцо и кнопки) перерисован нейросетью по оригиналу в 4× (`hud_hd/iview/p008.png`); у файлов
`hud_hd/` остаётся своя альфа — гладкий силуэт, альфа-тест режет ровный край вместо ступенек 4×4 (если альфа файла расходится
с оригиналом больше чем на 2 % текселей — берётся альфа оригинала). Стрелку рисует игра — она не менялась.
Апскейл мелкого шрифта HUD выходит мыльным, поэтому и цифры часов миссии («MM:SS.cc») перерисованы
нейросетью по оригиналу и вписаны в те же ячейки атласа шрифта (страница 51 `miami_01`, палитры 24 и 3): все цифры 0–9 одной высоты,
на одной базовой линии, по центру ячейки одинаковой ширины — таймер не «прыгает». Это отдельный вариант пака, как небо: подкаталог
`hud_hd/`, по умолчанию включён файлом `hud.txt` (слово `hud_hd`) в корне пака; `RE_TEXPACK_HUD=hud_hd|0|путь` важнее файла;
`RE_TEXPACK_HUD=0` или удалённый `hud.txt` — прежний апскейл. Сделать заново из своей копии игры:

```sh
pip install numpy pillow scipy
python3 tools/texpack_hud.py Data_Files/Levels/miami_01.lev texpack/hud_hd/src/digits.png texpack --out texpack/hud_hd --sheet hud_cells.png
```

Пока сделан только Майами (в других городах страница шрифта другая — ячейки можно напечатать `RE_FONTDUMP=1`).

Ограничения: пак NY_01 сделан частично (8-бит — 62 из 97 пар на момент коммита (все 9 пар, видимые в снимках, готовы; генерация продолжается)), в игре подмена проверена только в Майами на тестовом паке;
страница 1024² занимает ~4 МБ видеопамяти против 256 КБ; проверено под OSMesa/Xvfb, на реальном Mac — пока нет.

## CD-музыка

В оригинале музыка — звуковые дорожки (Red Book) диска: игра открывает привод через MCI (`cdaudio`, формат TMSF), читает оглавление,
играет дорожку от начала до конца с уведомлением `MM_MCINOTIFY` и по нему запускает её снова (цикл). С v2.22 native-сборка
эмулирует этот привод (`re/platform/sdl/plat_cdaudio.c`; игровой код не менялся): дорожки берутся из файлов, музыка смешивается
со звуком игры, громкость — ползунок музыки в настройках звука игры. **Файлов музыки в репозитории нет** — дорожки снимаются с
вашего диска.

**Куда класть.** Каталог `Music/` в каталоге данных игры (рядом с `Levels/`), или `music_dir = /путь` в `driver.cfg`, или
`RE_MUSIC_DIR=/путь` (важнее). С v2.34, если в каталоге данных `Music/` нет, музыка берётся из HD-пака — `<texpack>/Music`
(в `r331/driver-texpack` она лежит там): достаточно `texpack = …` в `driver.cfg`. Имена: `Track02.wav` … `Track10.wav` (также `track02.cdda.wav` от cdparanoia и `02 - что угодно.wav`
от EAC); вместо WAV можно `.flac`, `.ogg`, `.mp3` (декодеры dr_flac, stb_vorbis, dr_mp3 — `re/third_party`, public domain).
Можно положить образ диска: `*.cue` + `*.bin` (`FILE … BINARY`/`MOTOROLA`/`WAVE`, `TRACK NN AUDIO`, `INDEX 01`; сырой PCM 44100 Гц
стерео 16 бит, 2352 байта на сектор) — отдельный файл дорожки важнее образа. WAV — PCM 8/16/24 бит, моно/стерео, любая частота
(пересчёт в 44100 Гц).

**Как снять дорожки с диска** (только со своего диска):

```sh
# Linux: cdparanoia (apt install cdparanoia); macOS — cdparanoia из Homebrew или XLD (вывод WAV)
cdparanoia -Q                       # оглавление: сколько дорожек, длины
mkdir Music && cd Music && cdparanoia -B 2-10   # → track02.cdda.wav … track10.cdda.wav
# образ целиком: cdrdao read-cd --read-raw --datafile driver.bin driver.toc && toc2cue driver.toc driver.cue
#   (cdrdao пишет звук big-endian — в полученном .cue замените BINARY на MOTOROLA)
# Windows: Exact Audio Copy — «Copy Selected Tracks → Uncompressed» (WAV) дорожек 2–10, или «Copy Image & Create CUE Sheet»;
#   файлы переименуйте в Track02.wav … либо оставьте «02 - ….wav»
```

**Без файлов** привод всё равно «есть»: вызовы успешны, дорожки — заглушки по 60 с тишины (`RE_MUSIC_STUB=tone` — тихий тон,
у каждой дорожки свой: 220 Гц · 2^((N−2)/12); `RE_MUSIC_STUB_LEN=с` — длина). `RE_MUSIC=off` — как раньше: «Open CD device failed»,
музыки нет. Набор файлов-заглушек для проверки (тишина/тон, не данные игры): `python3 tools/make_music_stubs.py Music --tone`
(`--cue` — образ `music.bin/music.cue`). В stderr: `[cd] эмуляция CD-audio: каталог …, дорожек 10: 2=wav …` и на каждый запрос
`[cd] MCI_PLAY: дорожка N …`, `[cd] дорожка N закончилась → MM_MCINOTIFY`.

| Дорожка CD | Где игра её запрашивает (по коду) | Что это |
|---|---|---|
| 1 | — | данные (PlayCDTrack отвергает номера < 2) |
| 2 | `P136_FrontInit` (после загрузки `TITLE.DSS`), кадр меню `P119_MenuFrame` 0040cb9f | фронтенд/главное меню |
| 3 | `P124_MotelInit` 004182b0 (после `MOTEL.DSS`); кадр экранов `P66_FrameBegin` 004188b0, если CD не играет | мотель и экраны меню P66 |
| 4 + N | `P145_LevelLoad` 004d38b7 и кадр игры `P131_GameFrame` 004d4a63: `PlayCDTrack(N + 4)`, N — номер уровня 00b87e30 | уровень |
|  4 | N = 0, `MIAMI_01.LEV` | Майами |
|  5 | N = 1, `FRISCO_01.LEV` | Сан-Франциско |
|  6 | N = 2, `LA_01.LEV` | Лос-Анджелес |
|  7 | N = 3, `NY_01.LEV` | Нью-Йорк |
|  8 | N = 4, `IVIEW.LEV` | интервью (тестовая поездка в гараже; N = 4 пишет лестница кампании) |
|  9 | N = 5, `TRAIN.LEV` | уровень `TRAIN` — назначение (трасса/тренировка) по коду **не подтверждено** |
| 10 | N = 6, `NC_01.LEV` (`NEWCASTLE.DES`) | Ньюкасл |

Имена уровней — из таблиц Game.exe 00562d44 (`*.LEV`) и 00551cb4 (`*.DES`). Названия музыкальных композиций по коду не
определяются и здесь не приводятся. Сколько дорожек на вашем диске, проверьте сами (`cdparanoia -Q`): эмуляция ждёт дорожки 2–10.

Поведение как у оригинала (по коду `game/ported25.c` и Game_decomp.c: InitCDAudio 00524611, PlayCDTrack 0052479e — `MCI_PLAY` с флагами NOTIFY|FROM|TO, CDStop 00524873 — `MCI_STOP`, CDResume 005248cd — `MCI_PLAY` только с TO, CDSetVolume 00524917, GetCDTOC 00524f97, оконная процедура — `MM_MCINOTIFY` с wp 1/8): меню, мотель и уровень перезапускают дорожку, когда
приходит уведомление о конце; пауза (`P127_Pause`) останавливает CD, после паузы дорожка начинается заново; неверный номер дорожки
выключает музыку (опция «музыка» = выкл.), как в оригинале. Замечено: конец дорожки игра считает `P21_AddMsf(позиция TMSF, длина MSF)`
(005250cb) — к номеру дорожки прибавляются минуты длины; что делал с таким концом настоящий драйвер Windows (возможно, играл и
следующие дорожки), не проверено — эмуляция играет ровно запрошенную дорожку. `RE_MUSIC_VOL` — множитель громкости музыки (0..4).

### Динамическая музыка в стиле PlayStation (v2.33, по желанию)

Дополнение к оригиналу PC (там на уровень одна CD-дорожка): как на PlayStation, у каждого города 4 композиции — день/ночь ×
Drive/Chase, во время погони копов музыка плавно переходит на Chase и обратно. Игровая логика не меняется — эмуляция только
выбирает, что смешивать. **Файлов в репозитории нет** — это ваши собственные файлы.

**Как разложить 16 файлов.** В каталоге музыки (тот же `Music/`, `music_dir` или `RE_MUSIC_DIR`) создайте подкаталог `dynamic/`:

```
Data_Files/                      (каталог данных игры, рядом с Levels/)
└── Music/
    ├── Track02.wav … Track10.wav   (необязательно: обычные CD-дорожки — меню, мотель, интервью, Ньюкасл, запасной вариант)
    └── dynamic/
        ├── 01. Miami At Day Drive.mp3
        ├── 02. Miami At Day Chase.mp3
        ├── 03. Miami At Night Drive.mp3
        ├── 04. Miami At Night Chase.mp3
        ├── 05. San Francisco At Day Drive.mp3
        ├── 06. San Francisco At Day Chase.mp3
        ├── 07. San Francisco At Night Drive.mp3
        ├── 08. San Francisco At Night Chase.mp3
        ├── 09. Los Angeles At Day Drive.mp3
        ├── 10. Los Angeles At Day Chase.mp3
        ├── 11. Los Angeles At Night Drive.mp3
        ├── 12. Los Angeles At Night Chase.mp3
        ├── 13. New York At Day Drive.mp3
        ├── 14. New York At Day Chase.mp3
        ├── 15. New York At Night Drive.mp3
        └── 16. New York At Night Chase.mp3
```

Формат — любой из `.mp3`, `.flac`, `.ogg`, `.wav` (можно вперемешку). Имя распознаётся по словам без учёта регистра: город
(`miami`; `san francisco`/`frisco`/`sf`; `los angeles`/`la`; `new york`/`ny`), `day`/`night`, `drive`/`chase` — порядок и
разделители любые. Если слов нет, в `dynamic/` действует номер в начале имени `01`…`16` в порядке списка выше. Подкаталог нужен,
чтобы не путать с обычной схемой «`NN - что угодно.wav` = CD-дорожка NN»: в самом `Music/` файл с номером считается CD-дорожкой,
а файлы с полным набором слов (город + день/ночь + drive/chase) распознаются и там (и не считаются дорожками), но `dynamic/` важнее.
Набор можно положить частично.

**Как выбирается.** Когда игра запрашивает дорожку уровня 4–7 (Майами, Сан-Франциско, Лос-Анджелес, Нью-Йорк), вместо неё звучит
набор города. День/ночь — по флагу ночи уровня (тот же, по которому игра выбирает ночное небо и фонари: Take A Ride Day/Night,
ночные миссии Undercover; по коду `P145_LevelLoad` в Лос-Анджелесе флаг ночи ставится всегда — там звучит Night). Если время суток меняется во время уровня (рассвет/закат
в миссии) и держится 3 с — переход на пару другого времени суток с кроссфейдом. Погоня — признак, по которому игра красит радар в
красный и решает «оторвался ли от копов»: розыск (Felony) выше первой отметки и коп видит игрока или ещё не потерял его из виду.
Chase включается сразу, обратно на Drive — после 4 с без погони (`RE_MUSIC_CHASE_HOLD=с`); кроссфейд 1.5 с (`RE_MUSIC_FADE=с`).
Если длины Drive и Chase одного времени суток близки (разница не больше max(1 с, 2 %)), оба трека идут параллельно с одной
позиции и переключается только громкость (`RE_MUSIC_SYNC=0` — выключить); иначе Chase/Drive начинается с начала (кроссфейд
равной мощности). Набор зациклен; пауза, громкость, остановка — как у обычной дорожки (после паузы игра запускает дорожку заново).

**Запасные варианты.** Нет нужного файла — Drive того же времени суток, затем Drive другого, затем любой файл города; у города нет
ни одного файла — обычная дорожка `TrackNN` (4–7), а без неё — заглушка. Миссии с погоней за целью (не копы) и интервью/Ньюкасл
набор не используют.

**Выключить:** `RE_MUSIC_DYNAMIC=0` или `music_dynamic = off` в `driver.cfg` (`auto` — по умолчанию: включено, если набор найден).
В stderr: `[music] динамический набор: N из 16 …` (что нашлось по городам), `[music] Майами, день: Drive = …, Chase = …`,
`[music] → Chase (погоня)`, `[music] → Drive (погони нет 4 с)`.
Проверить без своих файлов: `python3 tools/make_music_stubs.py Music --dynamic` — 16 тонов с правильными именами (220 + 110·k Гц,
k = 0…15 в порядке списка), по `RE_WAV_OUT` видно, какой файл звучит.

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
| газ | `'` (апостроф) или **↑** (v2.14) | да — скорость растёт; ↑ даёт те же числа, что `'` |
| тормоз / задний ход | `/` или **↓** | да — скорость падает до 0, затем машина едет назад |
| руль влево / вправо | `Z` / `X` или **←** / **→** | да |
| ручник | `Enter` или **пробел** (v2.14) | да — скорость падает до 0 даже с нажатым газом |
| резкий руль (быстрее и до 511 вместо 352) | `пробел` (вместе с ручником, v2.14) | да — по значению руля |
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

Стрелки и пробел в езде (v2.14, только native) добавлены в `P36_GetPadButtons` — она вызывается лишь из такта езды, меню читают
стрелки напрямую, поэтому навигация меню не меняется. Окно/полный экран — Cmd+Enter или Alt+Enter (игре не передаётся).

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
| `RE_LOG=all:info[,канал:уровень…]` | v2.37: единый отладочный журнал `driver.log` (рядом с бинарником; macOS — `~/Library/Logs/Driver/`), каналы `sys load game mission render audio input mem save`, уровни `error warn info debug trace`; `RE_LOG_FILE`, `RE_LOG_STDERR=1`, `RE_LOG_RATE`, `RE_LOG_MAX_MB`; то же — `log = …` в `driver.cfg`. См. docs/DIAGNOSTICS.md «RE_LOG» |
| `RE_INPUTDBG=1` | v2.14: журнал ввода `driver_input.log` (macOS — `~/Library/Logs/`, иначе рядом с бинарником или в текущем каталоге) |
| `RE_WINDOWED=1` / `RE_FULLSCREEN=1` | v2.14: окно / полный экран (по умолчанию: macOS — полный экран, остальные — окно) |
| `RE_RES=WxH` | v2.14: размер окна (по умолчанию — наибольшее целое кратное 640×480 в 85% экрана); снимок `RE_SHOT_PNG` — в размере буфера окна |
| `RE_ASPECT=auto\|4:3\|W:H` | v2.15: соотношение сторон 3D (Hor+): по окну (по умолчанию), оригинальное 4:3 или заданное — см. «Разрешение и соотношение сторон» |
| `RE_PRESET`, `RE_MSAA`, `RE_FXAA`, `RE_ANISO`, `RE_FILTER`, `RE_RENDER_SCALE`, … | v2.16: графика — см. «Графика» (переопределяют `driver.cfg`) |
| `RE_TEXPACK=каталог` | v2.17: HD-пак текстур — см. «HD-текстуры» (важнее ключа `texpack` в `driver.cfg`) |
| `RE_TEXPACK_HUD=hud_hd\|0\|путь` | v2.36: вариант пака с перерисованными секундомером интервью и цифрами часов миссии (важнее `<пак>/hud.txt`; `0` — прежний апскейл) |
| `RE_TEXPACK_ASYNC=0\|1` | v2.39: HD-пары грузятся в фоне (`1`, по умолчанию; пока HD не готова, рисуется оригинальная текстура) или синхронно при первом рисовании (`0`, как до v2.39); важнее `texpack_async` в `driver.cfg` |
| `RE_TEXPACK_UPLOAD_MS=N` | v2.39: бюджет времени на кадр для загрузки готовых HD-текстур в GL, мс (по умолчанию 2, минимум одна текстура за кадр; `0` — одна текстура за кадр); важнее `texpack_upload_ms` |
| `RE_TEXPACK_THREADS=N` | v2.39: потоков фоновой загрузки HD, 1..8 (по умолчанию 2) |
| `RE_TEXPACK_PRELOAD=1` | v2.38: все HD-пары из списка уровня — при загрузке уровня (дольше загрузка, в игре загрузок нет); эти пары грузятся синхронно независимо от `RE_TEXPACK_ASYNC` |
| `RE_PROFILE=N` | v2.38: профилировщик кадров, каждые N кадров — см. docs/PERFORMANCE.md |
| `RE_FONTDUMP=1` | v2.36, отладка (только native): в журнал один раз — ячейки глифов шрифтов 0 и 1 для «0123456789:.» (страница, u, v, w, h) |
| `RE_TEXLOG=файл` | v2.18: статистика пар (страница, палитра): треугольники и площадь на экране — для порядка генерации пака |
| `RE_ARROWKEYS=0` | v2.14: не добавлять стрелки/пробел к клавишам езды |
| `RE_PROBE=1\|all\|car,traffic,ped,mission,menu,walk` | отладка RE: журнал полей для открытых вопросов [docs/RE_QUESTIONS.md](docs/RE_QUESTIONS.md) (`RE_PROBE_LOG`, `RE_PROBE_EVERY`, `RE_PROBE_SHOTS`, `RE_PROBE_WALK`); только native, только чтение — см. docs/ARCHITECTURE.md «RE_PROBE» |
| `RE_COPTRACE=N` | v2.34, отладка копов (только native): каждые N кадров строка `[coptr]` на каждого ведомого копа (слот, машина, поля записи ИИ, газ, руль), `[copplan]` — результат построения маршрута P128_CopReplan |
| `RE_FPU_CHOP=0` | v2.34, отладка: не эмулировать округление x87 «к нулю» Game.exe (`lrintf` и т. п. округляют к ближайшему, как до v2.34) — для сравнения прогонов; см. docs/ARCHITECTURE.md |
| `RE_RANGEDBG=1` | v2.35, отладка (только native): журнал проверки дальности 004f5012 (`P98_ScriptRange`) — объект скрипта, порог, расстояние, позиции цели и игрока; «→ цель потеряна», когда срабатывает |

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
  is raised (verified with a debug placement); FMV is skipped; Undercover reaches the motel and the first Miami mission. v2.15: any aspect ratio (Hor+: original vertical FOV, wider horizontal FOV, HUD anchored to screen edges, menus 4:3 centered; `RE_ASPECT=auto|4:3|W:H`). See `docs/NATIVE_GAPS.md`.
- **Build (Linux, verified on arm64):** `apt-get install build-essential cmake libsdl2-dev libgl-dev libegl-dev libosmesa6-dev`, then
  `cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release && cmake --build build-native -j && (cd build-native && ctest --output-on-failure)`.
  macOS (Apple Silicon): `brew install cmake sdl2`, same commands; build + selftest verified in GitHub Actions on `macos-14` (arm64),
  `-DRE_MACOS_BUNDLE=ON` builds `Driver.app`. Running the game with a window on a real Mac is not tested yet.
- **Run:** `./build-native/driver --data <run dir>`, where the run dir symlinks your `Data_Files` and holds copies of `Scripts` and `ReplayData`
  (the game writes there). Controls: arrows/Enter in menus, `'` throttle, `/` brake/reverse, `Z`/`X` steering, Enter handbrake, `1` camera, Esc pause, gamepad supported.
- **Hook build:** `sh re/build.sh hook` (MinGW i686) produces a proxy `DINPUT.dll`; put it next to `Game.exe`, check `re_driver.log`.
  Windows run not tested.
- Driver is the property of its rights holders; this repository contains none of their files.
