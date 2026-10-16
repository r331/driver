Driver (1999) — нативная сборка для macOS (Apple Silicon, arm64)

Файлы игры в сборку НЕ входят: нужна ваша копия игры (папка Data_Files с диска/установки).

Куда положить Data_Files (игра ищет файл Data_Files/FSIN.DAT по порядку):
  1) путь из параметра:            ./driver --data /путь/к/Data_Files
  2) текущий каталог:              ./Data_Files
  3) рядом с бинарником driver:    <каталог driver>/Data_Files
  4) для Driver.app:               Driver.app/Contents/Resources/Data_Files
                                   или рядом с приложением: <папка с Driver.app>/Data_Files

Сборка из исходников:
  brew install cmake sdl2
  cd re && ./build.sh native                  # -> re/build-native/driver (+ ctest)
  cmake -S re -B re/build-app -DRE_MACOS_BUNDLE=ON && cmake --build re/build-app   # -> Driver.app

Готовый Driver.app из GitHub Actions (артефакт driver-macos-arm64) не подписан Developer ID:
при первом запуске — правый клик → «Открыть», либо: xattr -dr com.apple.quarantine Driver.app
В бинарнике re/build-native/driver SDL2 берётся из Homebrew (brew install sdl2); в Driver.app SDL2 вложен.

Статус: сборка и selftest проверены в CI на macos-14 (arm64). Запуск игры с окном на реальном Mac не проверялся.
