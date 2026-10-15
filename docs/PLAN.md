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

- v0.83: +4 функции (ported36: DirectInput джойстик/геймпад над plat_di_poll), всего 1349

- v0.84: +2 функции (ported37: InitInput и колбэк джойстиков), всего 1351
- v0.85: +7 функций (ported38: FMV-проигрыватель и DirectSound-обёртки), всего 1358
- v0.86: +7 функций (ported39: Lock/Unlock/GetSurfaceFormat/Present/QueryDD4/QueryD3D/CreateFrontBack), всего 1365
- v0.87: +4 функции (ported40: память текстур Glide — ResetTexMem/UploadTexSlot/UploadTexSlotPair/DownloadSlotPalette), всего 1369
| v0.91 | математика ч.2 (ported44) + меню (ported45), native-линковка перенесённых функций; всего 1571 |
| v0.94 | звуковые слоты и мастер-громкость, запуск/остановка подсистем, 7 операций скрипта (ported48); всего 1638 |
| v0.96 | DirectSound/FMV: освобождение, сброс буферов, EAX-свойства (ported50); всего 1661 |
- v0.97 (2026-10-15): +11 листовых функций (ported51), всего 1682.
- v0.98 (2026-10-15): +9 функций (ported52: Glide-туман/мипмап, меню, HUD, FMV), всего 1697 по functions.csv
- v0.99 (2026-10-15): +9 функций (ported53: шаг границ, ввод имени, текстурный источник, поиск узла текстуры, чтение файла, три меню-действия) +3 thunk-а; всего 1709
- v1.01 (2026-10-15): +20 функций (ported55: таблицы объектов, списки имён, очередь вызовов, FRUSTRUM.DAT, устройство D3D/Glide, загрузка файлов, раскладка, остановка звука), +11 thunk-ов, всего 1766.
- v1.02 (2026-10-15): +22 функции (ported56: повтор/погоня, объекты, звук голоса, HUD, сплайн, кватернион, проверка сохранений), +15 thunk-ов, всего 1803.
- v1.03 (2026-10-15): +25 функций (ported57: 14 экранов меню, SaveDirector/LoadDirector, рекорды SCORES.HI, запись файла, пропуск блока карты, сброс слотов текстур, экран→вид), +21 thunk, всего 1849.
- v1.04 (2026-10-15): +25 функций (ported58: переключатель экрана, читы, освобождение таблиц, циклы меню, индекс блоков карты, демо, конфиг, слот сохранения, ширина текста), +14 thunk, всего 1888.
- v1.05 (2026-10-15): +13 функций (ported59: камера, переменные скрипта, трафик, клетка, список моделей, подбор предмета, направление объекта, REPLAYn.BIN, клавиши меню, блок из файла), +11 thunk, всего 1912.

v1.08: +17 функций (game/ported62.c): InitCamDefaults 0049c850, InitRenderConsts 00425a50, HeadingDelta 0049431d, FarFromPlayer 00492398, QueueTri 0042d2c9, MapRow 0051ac05 (RLE-строка карты), ModelLookup 004a58ad, FindFreeTrafficSlot 004a6749, SpawnTrafficCar 0049199a, DownloadPageFromBmp 005047ab, SaveScores 0051cb98, ScoreTable 0051cdec, MenuBusy 00413df3, SpeedText 005025dc, LoadMapHeader 004ec336, ParticleSet 00514c72, ParticleInit 00515813. +12 thunk. Всего 1959 по functions.csv (без CRT, из 3275). Новые unported: 00424a02, 0051cc55, 00515cca. native ctest ок (test_p62), hook собран, все cdecl.
v1.09: +10 функций (game/ported63.c): трафик по узлам (NearOnNode, CountByNode, NearestAdd, NearestRec, CanEnter, CarSpeed), InPlanes, SphereHits, CatmullRom, Hermite. +8 thunk. Всего 1977 по functions.csv (без CRT, из 3275). native ctest ок (test_p63), hook собран.
v1.10: +10 функций (game/ported64.c): сохранение повтора (SaveChunk, SaveReplay, ReplayStart), места в таблицах рекордов (Rank*, RankPlace). Всего 1990.
v1.11: +9 функций (game/ported65.c): токены/числа скрипта, поиск по имени, подпись пункта меню, блиттеры 00529140/00529190 + обёртки, вызов скрипта 004d1529. Всего 2005.

v1.12: +4 функции (game/ported66.c): кадр экрана 0041846c, подготовка кадра 004188b0, таблица пунктов 0041897c, переключатель режима режиссёра 004c862f. +2 thunk. Всего 2011.
v1.13: +8 функций (game/ported67.c): пул 30 записей 004bb060, позиция/цвет по центру экрана 00516fbe, шаг частицы 00513fbc, значки GT/REFLEC 004a9e88/0040cfdf, три экрана меню 00415ec0/00417970/00415188. +3 thunk. Всего 2022.
v1.15: +6 функций (game/ported69.c): надписи отсчёта 004a3630, очки 004a0cca/004a0d5f, кадр сцены 004aaea6, накладки 004b3ddb, устройства Glide 004246f0 (+6 thunk), всего 2049
v1.16: +10 функций (game/ported70.c): запуск частиц, поиск частицы, строка RLE-карты, загрузка REPLAYn.BIN, переход цвета, текст с тенью, радар (+7 thunk), всего 2066
v1.18: +4 функции (game/ported73.c): текст по центру экрана 005173d7, стороны дорог 0051bf82, сброс частиц 00511e60, сплайн 0049f031 (+4 thunk), всего 2096
v1.19: +10 функций (game/ported74.c): запись трафика, сдвиг строк, сброс HUD, 8→16 бит текстура, выбор устройства, расстояние, разбор чисел скрипта, SKID, опрос клавиш; +9 thunk. Всего 2115.
v1.20: +8 функций (game/ported75.c): трафик (позиция, появление, пополнение), фоновые звуки, звук при смене клетки, сброс объектов, голос двигателя, вырезка текстуры 256x256; +4 thunk. Всего 2127.
v1.21: +12 функций (game/ported76.c): вершины треугольников в буфер слота, пометка слотов, устройство Glide, заливка кадра, мигание, клетка сетки, цвет по углу, таблицы рекордов; +6 thunk. Всего 2145.
