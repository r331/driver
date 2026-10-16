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

Статус: сборка и selftest проверены в CI на macos-14 (arm64). Запуск игры с окном на реальном Mac не проверялся.
