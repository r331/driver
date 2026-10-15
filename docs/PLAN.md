# Декомпиляция Driver: You Are the Wheelman (1999) — план

Статус: Ф0 выполнена — версия PC (Game.exe, MSVC 6, debug CRT). См. docs/binary-info.md
Правило: работаем ТОЛЬКО с копией, которую загрузит Роман. Игру из сети не скачиваем.

## Фаза 0 — Вход
- [x] Получить исполняемый файл — PC, Game.exe из DATA1.CAB
- [x] Версия и хэши → docs/binary-info.md
- [x] Отладочные файлы: PDB/SYM/MAP на диске нет; в exe есть пути 20 .c-файлов (assert)

## Фаза 1 — Окружение
- [x] Ghidra 12.1.4 headless + JDK 21 (/workspace/tools; на arm64 нативный decompile собран из исходников: make ghidra_opt sleigh_opt ARCH_TYPE=)
- [ ] PS1: загрузчик PSX-EXE для Ghidra (ghidra_psx_ldr), сигнатуры PsyQ SDK для опознания библиотечных функций
- [ ] PC: стандартный PE-загрузчик, FID/сигнатуры MSVC CRT, DirectX-импорты
- [x] scripts/ExportAll.java, run_ghidra.sh, rerun_export.sh → out/functions.csv (3616 функций), out/Game_decomp.c; проект Ghidra: ghidra_project/

## Фаза 2 — Разметка
- [ ] Отделить библиотечный код (PsyQ / CRT) от игрового
- [ ] Сопоставление с REDRIVER2: имена функций и структур Driver 2, унаследованных из Driver 1 (по строкам, константам, графу вызовов)
- [ ] Форматы данных из OpenDriver2Tools (LEV/BLK/SBK) и krishty.com/driver_en → структуры в Ghidra
- [ ] Трекер функций: docs/functions.csv (адрес, имя, источник имени, статус)

## Фаза 3 — Декомпиляция
- [ ] Перенос функций в C по модулям (main loop, физика, ИИ полиции, камера, рендер, звук, миссии)
- [ ] Сборка и сверка поведения (по возможности — побайтовое совпадение для PS1 через PsyQ-компилятор)

## Справка
- REDRIVER2: https://github.com/OpenDriver2/REDRIVER2
- OpenDriverEngine: https://github.com/OpenDriver2/OpenDriverEngine
- OpenDriver2Tools: https://github.com/OpenDriver2/OpenDriver2Tools
- krishty.com/driver_en, someone972 Driver Level Editor

## Ф2 — проход 1 (2026-10-13)
- [x] out/string_xrefs.tsv (scripts/StringXrefs.java): строки ↔ функции
- [x] tools/name_pass1.py → docs/functions.csv: модуль по assert-путям D:\Driver\Game\*.c (+ протяжка между соседями одного модуля), CRT по именам CRT .c, имена из debug-строк "Name: ..."
- [x] scripts/ApplyNames.java применяет имена в Ghidra; tools/split_modules.py → src/<module>.c, src/lib/crt.c, src/_unsorted.c
- Итог: 3616 функций; CRT 341; игровых модулей размечено ~165 (map 49, MScript 49, frontend 17, compiler 14 …); 27 имён из строк; прямых совпадений имён с REDRIVER2 всего 3 (SetCamera, DeleteCamera, DrawFullscreenMap); без модуля 3111
- [ ] Проход 2: сопоставление с REDRIVER2 по константам/таблицам/строкам и графу вызовов от известных якорей; отделить DirectX/D3D-обёртки и DInput/DSound

## Ф3 — пересобираемый слой re/ (2026-10-13)
- [x] re/: прокси DINPUT.dll (MinGW i686, re/build.sh), перехват JMP, GVAR/GFUNC; re_driver.ini для отключения функций
- [x] Перенесено 4 функции Director.c: FindCameraById, RenumberCameras, DeleteCamera, AddDirectorCamera
- [ ] Ждём от Романа тест на Windows (re_driver.log)
- [ ] Дальше: переносить модуль за модулем, статус `ported` в docs/functions.csv; в конце — самостоятельный exe

## Цель: нативная сборка macOS M1 (запрос Романа 2026-10-13)
- [ ] Переносимые правила кода (см. re/README.md): без WinAPI в игровых модулях, фиксированные типы в файловых структурах
- [ ] Платформенный слой src/platform/: win32 (хуки) → SDL2 + OpenGL
- [ ] CMake с двумя целями; нативный exe — после переноса всего игрового кода
- Пока: DLL собирается на M1 через brew mingw-w64, тест под Wine/CrossOver

## v0.2 (2026-10-13): единая кодовая база re/ — native (CMake+SDL2, arm64 собирается и запускается, selftest) + hook (DINPUT.dll). Director.c: 5 функций.

## v0.3 (2026-10-13): +12 функций Director.c (всего 17 ported); механизм unported.h + native stubs.c. Следующие кандидаты Director: 004c6740 (автокамера), 004c8070 (сброс режиссёра), 004c862f, 004c93b1; затем DirectorStorage.
- v0.4: перенесено 5 функций DirectorStorage (всего 22); осталось 004c98de, 004c9a16 (assert)
- v0.5: +7 функций (всего 29): DirectorStorage завершён (чтение блока, камеры V1/V2, LoadWaypoints). Дальше Director: 004c6740 (автокамера), 004c8070-соседи, 004c862f (thunk-адреса), 004c5499/004c536c (Store/RestoreCameraState), 004c93b1 (SaveDirector — осторожно, __thiscall?); затем MScript
- v0.6: +SyncCameraFromList (004c52d9), IsCameraCarFarEnough (004c60b2); всего 31
| v0.7 | Director +4 (всего 35) |
| v0.8 | DirNodes +6 |
| v0.9 | DirNodes +4 (всего 45) |
- v0.10: DumpWaypoints, DrawCornerIndicator (47 всего)
- v0.11: DrawNode, DrawNodeMarker (всего 49)
- v0.12: +ReadDirectorKeys, ClampCameraHeight (51 всего)
- v0.13: +CameraDump (52 всего)
- v0.19: +18 MenuState (88 всего)
- v0.73: +6 функций (ported26: системные обёртки над plat_message_box/utc/wave/cd_roots), всего 1316
