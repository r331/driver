# Driver (1999, PC) — реконструкция исходного кода

Нативная реконструкция Driver: You Are the Wheelman (Reflections, 1999) по PC `Game.exe`
(MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`, сборка 1999-09-10). Цель — сборка и запуск
нативно на macOS Apple Silicon без Wine/эмуляции. По образцу [REDRIVER2](https://github.com/OpenDriver2/REDRIVER2).

Файлы игры в репозиторий не входят — нужна своя копия.

## Структура
- `re/` — переносимый код: `game/` (перенесённые модули), `platform/native` (SDL2), `platform/win32` (прокси `DINPUT.dll` для проверки в оригинальном Game.exe), `tests/`. Подробно — `re/README.md`.
- `docs/` — план (`PLAN.md`), сведения о бинарнике, трекер функций `functions.csv` (адрес, имя, модуль, статус).
- `src/` — псевдо-C из Ghidra, разложенный по модулям (сырьё для переноса).
- `scripts/` — Ghidra headless скрипты; `tools/` — вспомогательные Python-скрипты.

## Сборка (macOS M1)
```bash
brew install cmake sdl2
cd re && ./build.sh native
./build-native/driver --selftest
./build-native/driver --data /путь/к/Data_Files
```
