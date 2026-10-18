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

**Native как игра — v2.31** (проверено сценариями `RE_KEYS` и настоящей клавиатурой X11 (xdotool) под Xvfb, Linux arm64; сборка, selftest и inputtest — на macOS arm64 в CI):
- работает: заставки и главное меню, режим **Take A Ride** в Майами — езда по городу (стриминг блоков карты), трафик, столкновения, HUD (Damage/Felony, радар, спидометр);
- управление машиной: газ, тормоз/задний ход, ручник, резкий руль, смена камеры (вид с капота), пауза по Esc с меню (Continue / Restart / Sound Setup / Gfx Details / Film Director / Quick Replay / Show Map / Exit) — см. «Управление»;
- звук: DirectSound эмулируется собственным микшером (SDL_audio или запись в WAV), двигатель и шумы слышны, мягкий ограничитель — без клиппинга; музыка — эмуляция CD-audio (v2.22, дорожки из файлов вашего диска — см. «CD-музыка»);
- пешеходы: 12–16 активны, модель рисуется (проверено, когда пешеход стоит перед машиной); на обычном прогоне они появляются в ~34 500 единиц от игрока, а рисуются ближе 15 000 — чтобы увидеть, надо подъехать;
- копы: патрульная машина (предел 4); v2.12 — погоня работает: когда коп рядом (проверено отладочной перестановкой RE_COPNEAR), Felony растёт до предела, подключаются до 4 копов, преследуют и таранят; без отладки патруль к игроку пока не подходит;
- Undercover: интервью в гараже запускается; с пропуском интервью (RE_SKIP_INTERVIEW=1, как чит) — мотель, автоответчик (←/→ — кнопка, Enter — действие, «принять» — миссия) и **первая миссия Майами** «Get to the bank.» (прохождение не проверено);
- гудок H слышен (v2.12: 3D-источник у машины);
- v2.14: нативное разрешение — кадр игры 4:3 вписывается в окно/экран любого размера (Retina, 1080p, 2560×1600) с полосами по бокам; 3D растеризуется в разрешении экрана; на macOS по умолчанию полный экран; езда стрелками и пробелом (ручник) в дополнение к оригинальным клавишам;
- v2.15: любое соотношение сторон (Hor+) — на широком экране (16:10, 16:9, 21:9, 32:9) вертикальный угол как в оригинале, а по бокам видно больше города; HUD прижат к краям экрана, меню — по центру 4:3; см. «Разрешение и соотношение сторон»;
- v2.16: улучшение графики — MSAA (2/4/8x, мультисэмпловый FBO) с alpha-to-coverage для пальм и заборов, FXAA, render_scale 0.5–2.0 (SSAA), мипмапы без ореолов, анизотропная фильтрация до 16x, выбор фильтрации, чёткий HUD (sharp-bilinear), vsync/ограничение FPS, гамма/яркость; файл `driver.cfg` и пресеты original/enhanced — см. «Графика»;
- v2.17: HD-текстуры — подмена страниц текстур апскейлом (PNG 1024×1024) из своего пака, `RE_TEXPACK`/`texpack` — см. «HD-текстуры»;
- v2.18: HD-текстуры и для 8-битных (палитровых) страниц — по файлу на пару «страница × палитра»; подмена работает и в самой игре (раньше — только в проверке рендера);
- v2.19: дальность прорисовки — `draw_distance` (множитель 1.0–4.0, в `enhanced` — 2.0): дальние кварталы видны, логика игры не меняется — см. «Графика»;
- v2.22: CD-музыка — эмуляция привода CD-audio: дорожки `Music/TrackNN.wav|flac|ogg|mp3` или образ `.cue/.bin`, без файлов — тишина; цикл и громкость как в оригинале — см. «CD-музыка»;
- v2.23: исправлен серый полигон поверх неба (чаще слева вверху) — плоские/гуро-полигоны ближнего набора отсекаются по z = 1, вершины за камерой больше не уходят в угол экрана;
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

**Что запускается в CI** (файлов игры там нет): `ctest -L nodata` — `driver --inputtest` (v2.14: цикл событий в главном потоке —
`pthread_main_np`, событие клавиши через `SDL_PushEvent` → разбор событий игры → DIK, Cmd+Enter, биты езды стрелками, вписывание кадра)
и `driver --selftest`, модульные проверки перенесённых функций
на синтетических данных (тест настоящего уровня `RE_REAL_LEVEL` и рендер-снимок OSMesa на macOS пропускаются); Linux x86_64 —
то же плюс hook-сборка `DINPUT.dll` ([.github/workflows/linux.yml](.github/workflows/linux.yml)).

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

**Дальность прорисовки (v2.19, `draw_distance`, env `RE_DRAW_DIST`):** множитель к дальности из опций игры (Gfx Details, 15 000–45 000
единиц; клетка карты — 3000): 1.0 — оригинал, до 4.0; `enhanced` — 2.0, `original` — 1.0. В оригинале дальность ограничивают: окно обхода
клеток 31×31 по таблице FRUSTRUM.DAT (радиус 15 клеток = 45 000) и PVS того же размера, дальняя плоскость (опция) и её копия для отсечения
полигонов, таблица 1/z на 56 250 элементов, 4 слота блоков карты (2×2 блока по 60 клеток в Майами). Native при множителе > 1 на время 3D-вида
умножает дальнюю плоскость, обходит клетки за окном 31×31 своей проверкой конуса (курс камеры — по осям FRUSTRUM.DAT, полуугол — боковые
плоскости с учётом Hor+; сама таблица не меняется), продолжает таблицу 1/z (k/z) и разбирает недостающие соседние блоки из уже загруженного
уровня в отдельный кэш только для отрисовки (до 2 блоков за кадр с предзагрузкой; слоты и дорожные данные игры не трогаются). Порог
низкополигональных машин (15 000) умножается так же. Глубина — 1 − n/z (24 бит), от дальней плоскости не зависит: точность вблизи та же.
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

Ограничения: пак NY_01 сделан частично (8-бит — 62 из 97 пар на момент коммита (все 9 пар, видимые в снимках, готовы; генерация продолжается)), в игре подмена проверена только в Майами на тестовом паке;
страница 1024² занимает ~4 МБ видеопамяти против 256 КБ; проверено под OSMesa/Xvfb, на реальном Mac — пока нет.

## CD-музыка

В оригинале музыка — звуковые дорожки (Red Book) диска: игра открывает привод через MCI (`cdaudio`, формат TMSF), читает оглавление,
играет дорожку от начала до конца с уведомлением `MM_MCINOTIFY` и по нему запускает её снова (цикл). С v2.22 native-сборка
эмулирует этот привод (`re/platform/sdl/plat_cdaudio.c`; игровой код не менялся): дорожки берутся из файлов, музыка смешивается
со звуком игры, громкость — ползунок музыки в настройках звука игры. **Файлов музыки в репозитории нет** — дорожки снимаются с
вашего диска.

**Куда класть.** Каталог `Music/` в каталоге данных игры (рядом с `Levels/`), или `music_dir = /путь` в `driver.cfg`, или
`RE_MUSIC_DIR=/путь` (важнее). Имена: `Track02.wav` … `Track10.wav` (также `track02.cdda.wav` от cdparanoia и `02 - что угодно.wav`
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
| `RE_INPUTDBG=1` | v2.14: журнал ввода `driver_input.log` (macOS — `~/Library/Logs/`, иначе рядом с бинарником или в текущем каталоге) |
| `RE_WINDOWED=1` / `RE_FULLSCREEN=1` | v2.14: окно / полный экран (по умолчанию: macOS — полный экран, остальные — окно) |
| `RE_RES=WxH` | v2.14: размер окна (по умолчанию — наибольшее целое кратное 640×480 в 85% экрана); снимок `RE_SHOT_PNG` — в размере буфера окна |
| `RE_ASPECT=auto\|4:3\|W:H` | v2.15: соотношение сторон 3D (Hor+): по окну (по умолчанию), оригинальное 4:3 или заданное — см. «Разрешение и соотношение сторон» |
| `RE_PRESET`, `RE_MSAA`, `RE_FXAA`, `RE_ANISO`, `RE_FILTER`, `RE_RENDER_SCALE`, … | v2.16: графика — см. «Графика» (переопределяют `driver.cfg`) |
| `RE_TEXPACK=каталог` | v2.17: HD-пак текстур — см. «HD-текстуры» (важнее ключа `texpack` в `driver.cfg`) |
| `RE_TEXLOG=файл` | v2.18: статистика пар (страница, палитра): треугольники и площадь на экране — для порядка генерации пака |
| `RE_ARROWKEYS=0` | v2.14: не добавлять стрелки/пробел к клавишам езды |

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
