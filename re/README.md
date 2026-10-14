# re_driver — восстановленный Driver PC (1999)

Одна кодовая база, две цели сборки:
- **native** — самостоятельная программа (macOS Apple Silicon, Linux, Windows x64): SDL2 + OpenGL.
  Сейчас: окно, игровой цикл, проверка данных и перенесённые модули с тестами. Игра в ней
  появится по мере переноса модулей (в Game.exe ~3270 функций без учёта CRT).
- **hook** — DINPUT.dll для оригинального Game.exe: те же перенесённые функции подменяют
  оригинальные. Так каждую функцию можно проверить в живой игре, пока native не готов.

## macOS M1 (нативно)
    brew install cmake sdl2
    ./build.sh native                       # сборка + selftest -> build-native/driver
    ./build-native/driver --data /путь/к/Data_Files     # Data_Files с вашего диска
    ./build-native/driver --selftest

## Проверка функций в оригинальной игре
    brew install mingw-w64 && ./build.sh hook   # -> build/DINPUT.dll
Положить DINPUT.dll рядом с Game.exe (MD5 8e19d76a4bd5f3838a5c5cbf1cc5cfb5). На маке запускать под
Wine/CrossOver: `WINEDLLOVERRIDES="dinput=n,b" wine Game.exe`. Лог — re_driver.log;
отключить функцию: re_driver.ini, секция [disable], `ИмяФункции=1`.

## Структура
- game/        — перенесённые модули игры (имена — по путям D:\Driver\Game\*.c). Без WinAPI.
- game/gvar.h  — GAME_VAR: в hook-сборке глобал = адрес в Game.exe, в native — обычная переменная
- platform/native/ — main (SDL2), нативные DebugMalloc/DebugFree/DebugLog
- platform/win32/  — прокси DINPUT.dll и перехват (JMP rel32), install.c — список подменённых функций
- game/unported.h — список ещё не перенесённых функций Game.exe (hook: вызов по адресу; native: заглушка platform/native/stubs.c, лог «not ported: ИМЯ (адрес)»)
- tests/selftest.c — тесты перенесённых модулей (ctest)

## Правила переноса
- в файловых/игровых структурах — только типы фиксированного размера, размер проверять _Static_assert;
- указатели не хранить в структурах, которые читаются с диска (на arm64 они 8 байт);
- новая функция: game/<module>.c + строка в platform/win32/install.c + тест + статус ported в docs/functions.csv.

## Статус
Перенесено 1255 функций (из ~3275 без CRT), отслеживается в docs/functions.csv (status=ported).
Director.c (17): FindCameraById, RenumberCameras, InsertCamera, DeleteCamera, AddDirectorCamera,
SetCamera, GetCamera, FindCameraForFrame, FreeCameraList, FindNearestCamera, CameraFrameDistance,
AddDefaultCamera, FreeDirectorBuffer, FreeDirectorData, BackupCameraState, DropCameraBackup, RestoreCameraBackup.
v0.4: +5 DirectorStorage.c (22 всего): WriteDirectorData, WriteReplayHeaderChunk, WriteWaypointChunk, WriteCameraChunk, LogWaypoint. Файловый ввод-вывод — game/crt.h.
v0.5: +7 (29 всего): DirectorStorage.c — ReadDirectorData, ReadCameraChunkV2, ReadCameraChunkV1, LoadWaypoints, DeleteWaypointFile (модуль DirectorStorage перенесён целиком); Director.c — GetWaypointAfterFrame, ResetDirectorState. Тест: запись→чтение блока, камеры старого формата, Waypoint.tmp.
- v0.6 (Director): SyncCameraFromList, IsCameraCarFarEnough; всего 31
- v0.7 (Director): GetCameraTypeName, SelectNewCamera, CountNearbyCars, ClearDirectorTables; всего 35
- v0.8 (DirNodes): DirNopStub, GetWaypointForFrame, FindNodeById, FindNodeByLink, FindNodeAtPixel, SetNodeEnabled
- v0.9 (DirNodes): ClearDirectorTable, DrawNodeChain, DrawNodeMarkersChain, GetNodeParent; всего 45
- v0.10 (DirNodes): DumpWaypoints, DrawCornerIndicator; всего 47
- v0.11 (DirNodes): DrawNode, DrawNodeMarker; всего 49
- v0.12 (DirNodes): ReadDirectorKeys, ClampCameraHeight; всего 51
- v0.13 (Director): CameraDump; всего 52
- v0.14 (MenuState): MenuFlagSet, MenuFlagUpdate, MenuStateSetFour; всего 55
- v0.15 (MenuState): 7 MenuToggleOpt* + MenuReturnOne; всего 63
- v0.16 (MenuState): MenuCallAction40CD17; всего 64
- v0.17 (MenuState): 4 мелких функции; всего 68
- v0.18 (MenuState): SumBytes, MenuCopyPos; всего 70
- v0.19 (MenuState): 18 функций меню (10 переключателей, 5 перерисовок, Inc/Dec); всего 88
- v0.20 (MenuState): MenuDecVarB87E4C; всего 89
- v0.21 (MenuState): 4 сеттера флагов 54A844/54A854; всего 93
- v0.22 (MenuState): 8 функций Enter/LeaveMode 1,2,3,5; всего 101
- v0.23 (MenuState): Enter/LeaveMode 4,7,6; всего 107
- v0.24 (MenuState): MenuSetColor, MenuSetPos, MenuSetVals5D77C0, MenuSetByte5D77C1; всего 111
- v-next (Noop): 5 пустых функций (0041b054,0041b3a6,0041e456,0041ed21,0041ed39); всего 116
- v0.26 (MenuState): MenuSet54BE5CTo3, MenuSet54BE5CTo2, MenuSet54BE7CTo3, MenuSet54BE7CTo2; всего 120
- v0.27 (MenuState): 4 сеттера 54ACD4/54ACF4/54AD14/54AD34 + MenuTableGet54B010; всего 125
- v0.28 (MenuState/menuselect.c): 84 обработчика Select/Leave подсветки меню; всего 209
- v0.29 (MenuState/uihandlers.c): 60 простых сеттеров/переходов UI-меню (Ui<адрес>); всего 269
- v0.30 (MenuUI/uihandlers2.c): 48 простых UI-обработчиков; всего 317
- v0.31 (UIMisc/uihandlers3.c): 61 простая функция (сеттеры, переключатели, обёртки); всего 378

v0.32: +53 простые UI-функции (game/uihandlers4.c: сеттеры, переключатели, инкремент/декремент меню). Всего перенесено 381.

v0.33: +50 пустых функций (game/noop.c, NoopFn<адрес>). Всего перенесено 431.

v0.34: +24 пустых функций (push/pop ebp; ret) в noop.c. Всего перенесено 455.

v0.35: +31 сеттера/копировальщика глобалов (game/globalsets.c, GlobalSet<адрес>). Всего перенесено 486.

v0.36: +60 мелких функций (game/smallfuncs.c: пустые, сеттеры полей, пулы индексов, опкоды скрипта, векторные примитивы, подсветка меню). Всего перенесено 546.

v0.37: +59 функций (game/widgets.c: выбор строк меню, шаги громкости/float, переключатели, иконки, мелкие геттеры). В csv отмечено ported: 605.

v0.38: +15 SmallFuncs (game/smallfuncs2.c): ScriptStack pop/push, ClearSlots, AddClamp4095 и др.

v0.39: +76 функций (game/ported4.c): 58 обработчиков пунктов меню (MenuSlotHandler*), буферы карты Alloc/Free, ResetEffectsState и др.

v0.40: +51 функция (game/ported5.c): выбор пунктов меню (MenuPick*), подсветка строк, иконки-переключатели, шаги float, мелкие цепочки вызовов. В csv отмечено ported: 747

v0.41: +87 функций (game/ported6.c: переключатели меню, подсветка строк, звук-обёртки, пулы индексов, векторы, мелкие вызовы). В csv ported (без CRT): 834.

v0.42: +31 функция (game/ported7.c: сканы/поиск по таблицам, генератор случайных чисел, векторные примитивы, инициализации слотов). В csv ported: 865.

v0.43: +16 функций (game/ported8.c: матрицы 3x3, режимы, векторы, шаги скорости) и +225 thunk-переходов (jmp на уже перенесённые функции). Всего перенесено 1106.

v0.44: +3 (SelectByDifficulty 00416d17, ResetSlots 004a2b70, IsButtonActive 004e3924) — game/ported9.c

- v0.10: +5 (ported10: интерпретатор скрипта 004D1135/12CA/133C/1635, SetTableValue_004F89B7)

v0.45: +33 функции (game/ported11.c: вызовы-обёртки, чтение блоков, шаги float, переключатели панелей, мини-интерпретатор скрипта).

v0.46: +55 функций (game/ported12.c: 21 меню-обёртка, циклы по таблицам объектов/звуков, float-шаги, загрузка/выгрузка слотов).

v0.47: +3 функции (game/ported13.c: ApplyDetailLevel 004064b4, CopyDwords 00422ac0, GetScriptErrorText 004f8735).

v0.48: +17 функций (game/ported14.c: таймеры/состояния, разность времени, точка в треугольнике, копия блока, поиск слота, обёртки).
v0.49: +17 функций (ported15: меню-подсказки, blit, списки), всего 1239
v0.50: +3 (ported16: StepParticles 004b9d79, IdleTimer 004e12e4, FillHudRect 0050268f), всего 1242
v0.51: +4 (ported17: SlotMapSide 0051bcc0, SlotFindIndex 0051bd09, ISqrt 00528e12, PushScreenState 005104ed), всего 1246
- v0.52: +1 (ported18: P18_ClearFlag 0052840c), всего 1247 (остальные простые листовые — COM/WinAPI/указатели, не переносимы)
