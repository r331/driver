Driver (1999) — нативная сборка для macOS (Apple Silicon, arm64)

Файлы игры в сборку НЕ входят: нужна ваша копия игры (папка Data_Files с диска/установки).

Куда положить Data_Files (игра ищет файл Data_Files/FSIN.DAT по порядку):
  1) путь из параметра:            ./driver --data /путь/к/Data_Files
  2) текущий каталог:              ./Data_Files
  3) рядом с бинарником driver:    <каталог driver>/Data_Files
  4) для Driver.app:               Driver.app/Contents/Resources/Data_Files
                                   или рядом с приложением: <папка с Driver.app>/Data_Files
Игра пишет в каталог данных (config.dat, debug.log, SAVES/, Scripts/, ReplayData/) — лучше отдельный каталог запуска
с симлинками на файлы Data_Files и копиями Scripts и ReplayData (см. README.md, раздел «Данные игры»).

Сборка из исходников:
  brew install cmake sdl2                     # Homebrew ставит sdl2-compat (SDL2 API поверх SDL3)
  cd re && ./build.sh native                  # -> re/build-native/driver (+ ctest)
  cmake -S re -B re/build-app -DRE_MACOS_BUNDLE=ON && cmake --build re/build-app   # -> Driver.app

Готовый Driver.app из GitHub Actions (артефакт driver-macos-arm64, Driver-macos-arm64.zip) подписан только ad-hoc:
при первом запуске — правый клик → «Открыть», либо: xattr -dr com.apple.quarantine Driver.app
В бинарнике re/build-native/driver SDL берётся из Homebrew; в Driver.app из CI вложены libSDL2-2.0.0.dylib (sdl2-compat) и libSDL3.0.dylib.

Управление (v2.14): езда — стрелки (↑ газ, ↓ тормоз/назад, ←/→ руль), пробел — ручник; оригинальные ' / Z X Enter тоже работают.
Меню — стрелки, Enter, Esc. Клавиши по физическому положению: раскладка не важна.
Экран (v2.14): по умолчанию полный экран в нативном разрешении (кадр 4:3 с полосами по бокам). Cmd+Enter — окно/полный экран.
  RE_WINDOWED=1 — в окне, RE_RES=1440x1080 — размер окна, RE_FULLSCREEN=1 — полный экран. Cmd+Q — выход.
Если клавиши не работают: RE_INPUTDBG=1 ./Driver.app/Contents/MacOS/Driver  → пришлите ~/Library/Logs/driver_input.log

Тёмный экран, хотя звук есть (v2.24):
  1) запустите в окне:                RE_WINDOWED=1 ./Driver.app/Contents/MacOS/Driver
  2) если тёмно и в окне — без FBO:     RE_WINDOWED=1 RE_FBO=0 ./Driver.app/Contents/MacOS/Driver
     (или в driver.cfg: preset = safe — то же, что original, но без FBO; fullscreen = 0 — всегда окно)
  3) подробный журнал:                 RE_GFXDBG=1 ./Driver.app/Contents/MacOS/Driver
     и пришлите ~/Library/Logs/driver_gfx.log (пишется всегда, RE_GFXDBG=1 — подробнее; на Linux — ~/.config/driver/driver_gfx.log).
  Игра сама проверяет первые кадры: если через FBO в окне пусто — переходит на прямой рендер и (если полный экран
  не задан явно) в окно; в журнале это строки «ОТКАТ». Cmd+Shift+Enter — FBO вкл./выкл. на лету, Cmd+Enter — окно/полный экран.
  Полный экран: RE_FULLSCREEN=desktop (по умолчанию, как раньше) или RE_FULLSCREEN=exclusive (смена режима дисплея).

Статус: сборка, selftest и inputtest проверены в CI на macos-14 (arm64). v2.13 на Mac M1 (Роман): окно есть, управление не работало;
v2.14 — исправления ввода и нативное разрешение, на реальном Mac ещё не проверено.
