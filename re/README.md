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
v1.14: +9 функций (game/ported68.c): RepeatCheck 00522e64, ReadWords 00524ed1, AimSetup 00514f47, ObjStepB 00513efd, ReadCamArgs 004a5505, ChangeSample 0052455f, LfbLock 0042476c, ScreenReset 0040c480, SpawnCar 004a67b0 (+6 thunk). Всего 2037 по functions.csv (без CRT, из 3275). native ctest ок (test_p68), hook собран, все cdecl.
v1.15: +6 функций (game/ported69.c): SetupMsgs 004a3630 (надписи отсчёта по языку), ScoreBracket 004a0cca / AddScore 004a0d5f (очки по таблице порогов; указатели таблицы хранятся адресами 0x01136940+4k), ReleaseOverlays 004b3ddb, SceneFrame 004aaea6 (Glide grColorCombine/grFogMode через имена из P33), FreeDevices 004246f0 (+6 thunk). Всего 2049 по functions.csv (без CRT, из 3275). native ctest ок (test_p69), hook собран, все cdecl (метки __thiscall/__fastcall ложные).
v1.16: +10 функций (game/ported70.c): запуск частиц 00514332/00514403, поиск частицы 00513905, строка RLE-карты 0051ab31, чтение блока повтора 00406369 и загрузка SAVES\REPLAYn.BIN 00406199, переход цвета 005170ab, текст с тенью 0051755e (теперь связан в native — test_p66 считает вызовы 005173d7), ближайший объект радара 005062cc/0050784d (+7 thunk). Всего 2066 по functions.csv (без CRT, из 3275). native ctest ок (test_p70), hook собран, все cdecl.
v1.09: +10 функций (game/ported63.c): NearOnNode 0048ea2c, CountByNode 0048f3b4, NearestAdd 0048f4ad, NearestRec 0048f5d8, CanEnter 0048f1c6, CarSpeed 004901c0, InPlanes 004966fd, SphereHits 00426b34, CatmullRom 0049ef12, Hermite 0049ed20. +8 thunk. Всего 1977 по functions.csv (без CRT, из 3275). Новый unported: 0049521e. native ctest ок (test_p63), hook собран, все cdecl.
v1.10: +10 функций (game/ported64.c): сохранение повтора SaveChunk 00406272, SaveReplay 00406096 (SAVES\REPLAYn.BIN), ReplayStart 00405f6f; место в таблице рекордов RankBestFirst 0051cf17, RankTimeMore 0051ce94, RankTimeLess 0051cfda, RankTimeB 0051d05d, RankScoreB 0051d0e0, RankTop 0051d1a3, RankPlace 0051cc55 (в native поле +0xc заменяет P64_CurTable); +3 thunk. Всего 1990 по functions.csv (без CRT, из 3275)
v1.06: +7 функций (game/ported60.c): AddCamera 004c459f, ChangeCamera 004c483e, AddTripodCamera 004c4b3a, ChangeTripodCamera 004c4cee, NextTrafficCar 004c5c5d, ObjUpdate 004a399a, SpawnParticle 0051378b (+4 thunk-а). Перенесено 1923 функции (из ~3275 без CRT), отслеживается в docs/functions.csv.
v1.07: +5 функций камер (game/ported61.c): SetupCamN 0049e5e7 (матрица вида и положение камеры за машиной; смещения из таблицы 0x560968, в native — P61_InitConsts), StoreCameraState 004c5499 / RestoreCameraState 004c536c (запись режиссёра ↔ состояние игровой камеры, fistp→lrintf), CamPrepare 004c6d62 (дистанция/угол записи камеры к машине), SpawnPart 00514261 (частица в ячейке карты, иначе освободить слот). +5 thunk. Всего 1933 по functions.csv (без CRT, из 3275). native ctest ок (test_p61), hook собран, все cdecl.
v1.08: +17 функций (game/ported62.c): InitCamDefaults 0049c850, InitRenderConsts 00425a50, HeadingDelta 0049431d, FarFromPlayer 00492398, QueueTri 0042d2c9, MapRow 0051ac05 (RLE-строка карты), ModelLookup 004a58ad, FindFreeTrafficSlot 004a6749, SpawnTrafficCar 0049199a, DownloadPageFromBmp 005047ab, SaveScores 0051cb98, ScoreTable 0051cdec, MenuBusy 00413df3, SpeedText 005025dc, LoadMapHeader 004ec336, ParticleSet 00514c72, ParticleInit 00515813. +12 thunk. Всего 1959 по functions.csv (без CRT, из 3275). Новые unported: 00424a02, 0051cc55, 00515cca. native ctest ок (test_p62), hook собран, все cdecl.
v1.02: +22 функции (game/ported56.c): ReplaySetup 005105da, ObjSync 004da8d9, ObjInit 004daa36, LoopStart 004d62ae, LoopUpdate 004d6a47, SetVoicePos 00523ec6, ResetFrontend 0040c165, ChaseTick 004f5a57, CopyBlock16 0051d8ca, GhostInit 004e625e, CarPosCheck 0049245a, ReplayRead 0051990a, HudTick 004e4f62, DrawRowRects 004f3032, DownloadPageFromBmp 005046f7, AllocEulerTab 00426c06, Spline 0049ee5d, QuatRot 0049f180, DrawSprite 00506b4b, ReplayPaths 00518137, CopsDebug 004d263d, SaveCheck 00405cb4 (+15 thunk-ов). Перенесено 1803 функции (из ~3275 без CRT), отслеживается в docs/functions.csv.
v1.00: +16 функций (game/ported54.c): MenuTexSel 0040500d, TexSource 004248c6, ClearBuffers 0041de46 (stdcall), ClearSwap 0040c5be, FreeTab4 004f3c16, FreeRoadbits 0051aacd, AllocRoadbits 0051aa5b, AllocMapBufs 004ecda8, DefaultKeys 0040748a, InitInputMode 0040724c, ObjTick 00493f9a, ObjInit 00493e3d, GetTexture2 0042200c, ReadNames 004ec7ac, ReadMapA 004ec280, ReadMapB 004ec3fd (+10 thunk-ов). Перенесено 1735 функций (из ~3275 без CRT), отслеживается в docs/functions.csv.
v0.97: +11 функций (game/ported51.c): PitchJitterSfx 004d69ed, ScalePair 004d8487, PrefixMatch 004a59f2, SkipToLine 004a5a83, FileSize 004d3000, DirFromHeading 004a63c6, InitCarSlot 00491928, TrafficConflict 0048eb25, NodeKind 0048f7fe, SteerHeading 004d0071, SkipNumber 004a50f7 (+10 thunk-ов). Всего 1682 (по docs/functions.csv, без CRT).
Перенесено 1682 функции (из ~3275 без CRT), отслеживается в docs/functions.csv (status=ported).
v0.77: +6 функций (game/ported30.c, WinMain.c): FatalError (00522369), CrashHandler (00522759, тело), CrashHandlerInstall/Remove (0052273c/0052274c), InitWindowGlobals (005223be), Exit (0052e400). Новое в plat.h: plat_exit, plat_screensaver_get/set, plat_set_crash_handler (SDL: signal; hook: SetUnhandledExceptionFilter / CRT-выход 0052e480). Всего 1328 (по docs/functions.csv).
v0.76: +1 функция (game/ported29.c): SetDirectorMode (004c875d) — переключатель 16 режимов режиссёра повторов, вызывает ported11 вместо заглушки. Всего 1323.
v0.75: +2 функции (game/ported28.c): LoadEventModels (004ec58a), LoadCarModels (004bfc30; MessageBox через plat_message_box). Всего 1322.
v0.74: +4 функции (game/ported27.c): ReadChunked (004d9596), LoadPalettes (004ec154), MemLeakReport (004d8c80, MessageBox → plat_message_box), LoadDentTextures (004c17ae). Всего 1320.
v0.73: +6 функций (game/ported26.c, шаг C платформенного слоя): WaveSetVolume (waveOutSetVolume), ErrorInLine/FindWheelModels (MessageBox), LogTime (GetSystemTime), RandomFx (timeGetTime), FindCdDrive (GetLogicalDriveStrings/GetDriveTypeA). Новое в plat.h: plat_message_box, plat_utc_hms, plat_wave_set_volume, plat_cd_roots. Всего 1316.
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
- v0.54 (ported20): P20_FindNameNoCase, P20_FindNameValue; всего 1257 (остальные простые — WinAPI/ftol/указатели)
- v0.55 (ported21): 5 функций (GridCellSet, AddMsf, SetAxisByte, CountActiveEntries, MatchPrefix); всего 1262 (остальные — WinAPI/указатели/float)
- v0.56 (ported21): GetNameByIndex 0040f14a; всего 1263 (остальные простые — WinAPI/ftol/COM)
- v0.62: plat_local_hms (системный слой), 0 функций перенесено
- v0.66: 004bf910 P21_FpsToBuf (FPS в буфер)
- v0.67: OpenGL 3.3 бэкенд рендера (platform/sdl/plat_render.c) + offscreen-тест через OSMesa (tests/render_test.c, PNG); функций перенесено 0, всего 1267 из 3275
- v0.68: SDL_audio микшер (platform/sdl/plat_snd.c: 44100 Гц стерео S16, 8/16 бит, моно/стерео, pitch, громкость/pan в сотых дБ как DirectSound, loop; plat_snd_open/close/mix) + tests/snd_test.c; функций перенесено 0, всего 1267 из 3275
- v0.69: 11 render-функций состояния устройства (game/ported22.c: Begin/EndScene, ZFunc, ZWrite, AlphaRef/Func/Test, Cull, Viewport, фильтры, TexOp) над новыми plat_scene_*/plat_set_render_state/plat_set_tex_stage/plat_set_viewport (GL-вариант + COM-вариант в hook). ИСПРАВЛЕНИЕ hook: 81 хукнутая функция Game.exe заканчивается `ret N` (stdcall) — re_hook теперь ставит переходник (platform/win32/hook.c, таблица stdcall_tbl.h из tools/gen_stdcall.py), иначе стек терялся. Всего перенесено 1278 из 3275
- v0.70: 7 render-функций (game/ported23.c): конвертеры вершин игры → plat_vertex (00421cfe/00421db8), линии (0041e462/0041e4b9), режимы смешивания 0041d9d2, начальные render-state 00421521, очистка Z 00420e93; новые plat_draw_lines, plat_set_current_viewport, plat_clear_depth, plat_get_render_state. Всего перенесено 1285 из 3275
- v0.71: 12 DirectDraw/Direct3D-обёрток инициализации (game/ported24.c): CreateSurface/CreateDevice/CreateViewport/AddViewport/CreateClipper/SetClipper/AttachSurface (00420c10, 00420cfe, 00420d5d, 00420dad, 00421250, 00421298, 004214dd), SetDisplayMode 0042101b, CreatePrimarySurface 0042106d, FillBackbuffer 00420ef6, RestoreSurfaces 004212dc, RestoreDisplay 004213a4; новый слой plat_dd_*/plat_d3d_* (SDL: заглушки platform/sdl/plat_dd.c, hook: vtable Game.exe). Всего перенесено 1297 из 3275
- v0.72: 13 функций CD-аудио и таймеров (game/ported25.c): InitCDAudio 00524611, CDClose 00524763, PlayCDTrack 0052479e, CDStop 00524873/005248a0, CDResume 005248cd, CDSetVolume 00524917, GetCDTOC 00524f97, TimersInit/Shutdown/Start/Stop 005281b0/005281e1/00528221/00528293, колбэк таймера 005282e1 (stdcall); новый слой plat_cd_*/plat_aux_*/plat_timer_* (hook: winmm, SDL: учётная заглушка + SDL_AddTimer); hook-сборка линкуется с -lwinmm. Всего перенесено 1310 из 3275
- v0.78: 4 функции окна/DirectDraw (game/ported31.c): PumpMessages 00522323, InitWindow 005223dc (+ P31_WndProc 005224a8, вызывается оконным классом), LoadGlide 00425730, ReleaseDirectDraw 0041f2a0; новые plat_pump_messages/plat_game_window_create/plat_set_priority/plat_post_quit/plat_post_close/plat_set_cursor/plat_def_window_proc/plat_dll_load/plat_dd_set_cooperative. Всего перенесено 1332 из 3275
- v0.79: 4 функции Z-буфера и палитр (game/ported32.c): CreateZSurface 004213dc, CreateSlotPalette 00422309, SelectSlotPalette 00422c55, SetPalette 0041f57d (stdcall); новые plat_dd_get_surface_size/create_palette/surface_set_palette/palette_set_entries/plat_tex_palette_changed/plat_set_texture. Всего перенесено 1336 из 3275
- v0.80: 2 функции рендера (game/ported33.c): FlushBatches 00422ae7 (сброс буферов вершин по слотам текстур, 33 слота) и LoadGlideProcs 00424c40 (119 функций glide2x.dll, таблица сгенерирована tools/gen_glide.py); новые plat_get_tex_stage/plat_draw_prim/plat_dll_proc, G6Call00422AE7 заменён на P33_FlushBatches (game/flush.h). Всего перенесено 1338 из 3275
- v0.81: 3 функции DirectInput (game/ported34.c): ReleaseInput 004e31d5, DIReAcquire 004e4076, ReadKeyboard 004e417f; новый слой plat_di_* (Release/Unacquire/SetDataFormat/Acquire/GetDeviceState, plat_event_close; SDL — учёт вызовов, hook — vtable Game.exe). Всего перенесено 1341 из 3275
- v0.82: 4 функции: Force Feedback DirectInput (game/ported35.c: CreateEffectA 004e41d5, CreateEffectB 004e429b, UpdateForce 004e3b3c) и GetDirectDrawInterface 00420b19; новые plat_di_enum_effect/create_effect/set_effect и plat_dd_create/get_display_flags (SDL — учёт вызовов, hook — vtable Game.exe и DirectDrawCreate, -lddraw). Всего перенесено 1345 из 3275
- v0.83: 4 функции DirectInput (game/ported36.c): AcquireDevice 004e3ffe, SelectJoystick 004e3769, GetPadButtons 004e39ac, PollInput 004e3391 (опрос джойстика, перенос осей в таблицу клавиш); новый plat_di_poll (SDL — заглушка с управляемым состоянием lX/lY для теста, hook — Poll по vtable). Всего перенесено 1349 из 3275
- v0.84: 2 функции DirectInput (game/ported37.c): InitInput 004e2ee0 (DirectInput, клавиатура, мышь с событием и буфером 32, перечисление джойстиков) и JoyEnumCallback 004e3cdf (оси ±31, мёртвая зона 3, FF-эффекты; не хукается — stdcall-колбэк, зовётся только из InitInput); новые plat_di_create/create_sys_device/create_device/query_device2/set_coop/set_event/set_prop/get_caps_flags/enum_joysticks, plat_event_create (SDL — заглушки с маской отказов, hook — vtable Game.exe и экспорт DirectInputCreateA этого же DLL). Всего перенесено 1351 из 3275
- v0.85: 7 функций FMV/DirectSound (ported38: MmsRun 0048b2fd, MmsStop 0048b32b, FmvUpdateFrame 0048b34c, FmvRelease 0048ae12, FmvStop 0048b65d, SetPrimaryFormat 0048bdcc, SetSpeakerConfig 0048be68) над новыми plat_mms_set_state/plat_sample_update/plat_dd_blt_from/plat_dd_fill_all/plat_ds_set_format/plat_ds_set_speaker_config. Всего перенесено 1358 из 3275
- v0.86: 7 функций поверхностей DirectDraw (game/ported39.c): LockSurface 0041eb8c (stdcall), UnlockSurface 0041ec82 (stdcall), GetSurfaceFormat 0041d3ed (биты/сдвиги каналов), Present 0041dec8 (stdcall; Blt в окно по центру или Flip), QueryDD4 00420c5a, QueryD3D 00420cac, CreateFrontBack 00421149; новые plat_dd_lock/unlock/get_pixel_format/query_dd4/query_d3d/blt_rect/flip, plat_dd_clipper_set_hwnd, plat_window_client_rect, plat_client_to_screen. Всего 1365 из 3275.
- v0.87: 4 функции памяти текстур Glide (game/ported40.c): ResetTexMem 00489d20 (таблицы слотов 0x100×0x10 и блоков 0x40×0x1c, границы из grTexMin/MaxAddress), UploadTexSlot 0048a239, UploadTexSlotPair 00489f50 (пара слотов), DownloadSlotPalette 004efc7c; структуры P40_Slot/P40_Block с _Static_assert; вызовы в ported6/ported12 переведены на них, 0042486b добавлена в unported. Всего 1369 из 3275.
- v0.88: LoadTexPages 004eb975 (game/ported41.c, страницы текстур карты из файла уровня) + 123 thunk-а jmp на перенесённые функции (tools/mark_thunks.py); всего 1493
- v0.89: 10 функций (game/ported42.c): таблицы MScript FindScriptCommand 004f6333/FindScriptCommandById 004fc5ab/FindScriptVar 004f64dd, GetHighScoreTable 0051cd43, FreeGlide 0042570c (plat_dll_unload), GetVersionString 0041eb51, ActionBound 004d6209, GetGlideDeviceName 004245ec, SetViewAngles 004e964a, CellIndex 004ece84; +6 thunk-ов; всего 1509
- v0.90: 16 функций (game/ported43.c): векторы/матрицы/кватернионы (Normalize 005260d7, Cross 0052605d, Len3/Len4, Orthonormalize 005265e3, EulerMatrix 005261ad, MatToQuat/QuatToMat, PointInPoly, ClipT, ProjectGrid), CdFadeInit 00524398, FreeSlot 0051200f, AnimNext 00514073 + 9 thunk-ов; re_init_consts() задаёт float-константы .data в native; всего 1534
- v0.91: 22 функции + 15 thunk-ов: математика ч.2 (game/ported44.c: Atan2 по таблице 00525e7e, матрицы поворота RotX/RotY/RotZ 00528688/788/885, EulerMat 005262cc/00526365, кватернионы 005272f2/00527544/0052763b, ось-угол 00527746, Xform 00528982/005289e2/00528a42, LookAt 005266ed, PointInQuad, Copy4, Transpose, ResetState) и меню (game/ported45.c: 0040834f, 00408458, 0040ccb4, 00417cbb). Новое: tools/gen_native_links.py → platform/native/links.c — в native перенесённые функции теперь вызываются из «неперенесённых» вызовов (раньше уходили в заглушки; заглушки стали слабыми). Всего 1571
- v0.92: 7 функций (game/ported46.c): FindTexNode 00422444 (список узлов текстур 00a42180), TexCall 0041d89c / TexCall2 0041d5e7 (диспетчеры по узлу; 0041f4a1 — stdcall ret 0x10), SetBounds 004d614a, UpdateObjects 004defd1, LoadMapA 004ec7f4 / LoadMapB 004ec4ce (блоки map.c через DebugMalloc + ReadChunked); +5 thunk-ов; всего 1583
- v0.93: 12 функций (game/ported47.c): ReadLine 0041c7ad (fgets, g_fgets в crt.h), Call51B111 004c6091, NoFlags 00495886, ResetPick 004f5951, TitleDispatch 0040a73d, LoadFlyby 0041a130, CameraModeText 004d9908, DirText 004d9827, PrepareTemp 00405f2e, GlideWinOpen 0042467f (stdcall), GlideSwap 0042651a, TexTable 00424921. Всего 1595 по functions.csv (без CRT, из 3275).
- v0.94: 22 функции (game/ported48.c): звуковые слоты FreeVoice 00523e07 / SetVoiceVolume 00523ffd / SetMasterVolume 00523711 / StopAll 005237b1 / FreeSample 00524b7e / ResetAll 00523628 / SndShutdown 00523595 / SndPause 0052369b / FadeEnd 005243eb / GetVoiceVolume 005242e7, AnyKey 004d97e9, PosToInts 0041a1b5, GlideCheck 00425f52, StartupSystems 004d33c0 / ShutdownSystems 004d3402 (plat_com_init/uninit), операции скрипта OpSet3/OpSet4/OpRampDown/OpRampUp/OpFlags/OpRepeat/OpTurn (004d020b/107e/116c/121b/142c/1672/0d7c); +21 thunk; всего 1638 по functions.csv (без CRT, из 3275)
- v0.95: 13 функций DirectSound 3D (game/ported49.c): слушатель 0048c74b/0048c77e/0048c7bd/0048bd40, буферы 0048c97c/0048c9b2/0048caa0/0048c7f0, 3D-буферы 0048ca68/0048c9e8/0048ca28, освобождение 0048cd82/0048ccaf; новый слой plat_ds_listener_*/plat_ds_buf_*/plat_ds3d_* (hook — vtable, SDL — учёт последнего вызова). Всего 1651 по functions.csv (без CRT, из 3275)
- v0.96: 12 функций DirectSound/FMV (game/ported50.c): FmvReleaseObjs 0048b568, FmvStopRelease 0048ac0d, FmvReleaseAll 0048b242, SoundShutdown 0048bcc0, Nop 0048cc5f, ReleaseVoice 0048c520, ReleaseBuf 0048c83d, ResetBuf 0048c8d6, EaxSetDefault 0048cba4, EaxEnable 0048cbd3, CreateDummyBuf 0048ccdd, CreateKsProps 0048cc64; новые plat_ds_buf_stop/set_position, plat_ds3d_set_velocity_ex, plat_ds_create_buffer, plat_com_query_interface, plat_ds_prop_set/support. Всего 1661 по functions.csv (без CRT, из 3275)
- v0.98: 9 функций (game/ported52.c): обёртки Glide GlideFogSetup 0042626e / GlideFogMode 004264bd / TexDownloadMipMap 0042486b (Glide-вызовы по именам из таблицы P33), MenuStepToggle 00510084, HudDispatch 004e59b9, ResetSlots 004aad65, FmvStart 0048abdc, DrawLabel 004a9e0a, MenuReload 00510728; +6 thunk-ов. Всего 1697 по functions.csv (без CRT, из 3275)
- v0.99: 9 функций (game/ported53.c): StepBounds 004d6354 (шаг границ слота 0xf), NameEntry 005101f0 (ввод имени в меню), SetTexSource 0041f76f (stdcall), TexLookup 0041d63b, CallWithState 00500154 (стековая структура → 00500937), ReadWholeFile 004d303a, меню-действия 004161b3/004046c8/00414638 (Ghidra-метка __fastcall ложная — cdecl); +3 thunk-а; всего 1709 по functions.csv (без CRT, из 3275)
v1.01: 20 функций (game/ported55.c): циклы по таблицам объектов 004ef309/004ef364, сброс 004ee129, списки имён 8 слотов 0041219e/004125b9/0041afca/00510784, очередь отложенных вызовов 004d9237, FRUSTRUM.DAT 004eb3c0, описание устройства D3D/Glide 0041d819/00424974, загрузка файлов 004d30f8/004d318e, запись состояния 00519873, раскладка 004073ab, остановка звука 0050f289, Glide-режим 005226b5/0040c533, язык 00409d66, бумага 004e6175. +11 thunk-ов. Всего 1766.
- v1.03: 25 функций (game/ported57.c): 14 экранов меню (0040a3a0 004082a0 0040e870 004134a0 00413890 0040a540 0040f2d0 00413610 00413b00 00416390 004045e0 00404850 00411fd0 004123d0), выход 0040cd17, SaveDirector 004c92c0 / LoadDirector 004c9310 / 004c93b1, рекорды 00406439/00406479/00406b51, WriteFile 004d30a3, SkipBlock 004ec2ec, ResetTexNodes 00421a39, ScreenToView 005075f6; +21 thunk. Всего 1849 по functions.csv (без CRT, из 3275)
- v1.04: 25 функций (game/ported58.c): экран-переключатель 00417e0d, читы 00413381/004133b4, список пунктов 00407dba, освобождение таблиц/списков (004efc03 004f5dcd 004f8d6d 004eb19b 004a3354), циклы меню 00419f00/00419ab0/00413d70/00416540, подготовка 00415f67, индекс блоков карты 0051be3c, демо 00408600, LANG/MISSION 00516da0, логотип 004a9b1a, объекты 00506bff, ParseInt 00524e22, FindChunk 004f6011, фон меню 0040cf35, слот сохранения 00405e79, CONFIG.DAT 00405bfa, ширина строки 0040b1cc; +14 thunk. Всего 1888 по functions.csv (без CRT, из 3275)
- v1.05: 13 функций (game/ported59.c): камера 0049c910, строковые переменные MScript 004f8a2d/004f892a, трафик 0048ed6f/0048eca3, клетка 00491650, список моделей 004a3f06, соседние машины 004a6dcd, подбор предмета 004e5ea2, направление объекта 004daac7 (таблица синусов 0x576f10 для native — game/sintab_data.h, tools/gen_sintab.py), REPLAYn.BIN 00405fdb, клавиши меню 00417d56, чтение блока 0040d4b3; +11 thunk. Всего 1912 по functions.csv (без CRT, из 3275)
- v1.11: 9 функций (game/ported65.c): токены/числа строки скрипта 004f6774/004f87e0, поиск по имени 004f8cfd, подпись пункта меню 004072be, блиттеры спрайтов 00529140/00529190 + обёртки 00407cb8/00407d07, вызов скрипта 004d1529; +6 thunk. Всего 2005 по functions.csv (без CRT, из 3275)
- v1.12: 4 функции (game/ported66.c): ScreenFrame 0041846c, FrameBegin 004188b0, DrawTable 0041897c, DirSwitch 004c862f (+2 thunk); всего 2011 по functions.csv (без CRT, из 3275)
- v1.13: 8 функций (game/ported67.c): CompactPool 004bb060, CenterDraw 00516fbe, ObjStep 00513fbc, Logo 004a9e88, DrawIcon 0040cfdf, три экрана меню 00415ec0 / 00417970 / 00415188 (+3 thunk); всего 2022 по functions.csv (без CRT, из 3275)
