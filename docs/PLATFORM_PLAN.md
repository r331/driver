# План: нативная сборка без WinAPI/DirectX (2026-10-14)

Импорты Game.exe: KERNEL32 65, USER32 22, GDI32 1, ole32 3 (CoCreateInstance → Direct3D), WINMM 10 (таймер, CD-аудио mci, громкость), DDRAW 2, DSOUND 2, DINPUT 1. Всего ~106 функций ОС + COM-интерфейсы DirectDraw/Direct3D/DirectSound/DirectInput.

## Принцип
Игровой код (re/game/) зовёт только наш интерфейс platform/plat.h. Две реализации:
- platform/sdl/ — SDL2 + OpenGL (macOS M1, Linux, Win x64);
- platform/win32/ — в hook-сборке plat_* вызывают оригинальные функции/обёртки Game.exe, чтобы проверять в живой игре.

## plat.h (слои)
1. Система: время (timeGetTime/timeSetEvent → SDL_GetTicks/таймер), файлы (CreateFile/ReadFile → stdio, пути без регистра, Data_Files с диска Романа), лог, выход, MessageBox → SDL_ShowSimpleMessageBox.
2. Окно и ввод: окно/цикл сообщений (USER32) → SDL окно/события; DirectInput клавиатура/джойстик → SDL keyboard/gamecontroller.
3. Звук: DirectSound буферы (3D-позиция, громкость, pitch) → SDL_audio + свой микшер; CD-аудио (mci) → треки с диска, сграбленные в WAV/OGG.
4. Рендер: найти все обёртки Direct3D/DirectDraw в Game.exe (вызовы через vtable COM), свести к API: текстуры (загрузка/выбор), режимы смешивания/z-буфера, DrawPrimitive списков треугольников с преобразованными вершинами, очистка/флип, 2D-blit для HUD/меню. Реализация — OpenGL 3.3 core.

## Шаги
1. Скрипт: по графу вызовов найти все функции, которые прямо зовут импорты или COM vtable → docs/platform_funcs.csv (ожидаемо 150–300), сгруппировать по слоям.
2. Описать plat.h, переносить эти функции как тонкие обёртки над plat_*.
3. Указатели: в структурах с диска — 32-битные смещения/индексы, разрешение при загрузке; __ftol → (int32_t) приведение.
4. Затем крупные модули сверху вниз: main loop → frontend → map/LEV загрузка → рендер мира → машины/физика → MScript/миссии → replays.
5. Веха 1: native открывает окно, грузит LEV и рисует город. Веха 2: меню. Веха 3: езда.

## Прогресс
- 2026-10-14 17:05: Роман согласился, задача переключена на этот план. Следующий шаг: A — построить docs/platform_funcs.csv.
- 2026-10-14 17:30: шаг A выполнен: scripts/platform_funcs.py → docs/platform_funcs.csv (189 функций: system 84, render 81, cdaudio 16, window_input 8; слой sound пуст — DirectSound идёт через COM-vtable, эвристику уточнить; колонка callers пуста). Следующий шаг: B — re/platform/plat.h (система + окно/ввод), затем уточнить sound/callers.
- 2026-10-14 17:40: шаг B (часть): re/platform/plat.h (система + окно/ввод), platform/sdl/plat_sys.c, native собран, ctest ок, hook ок. Следующий: hook-вариант plat в win32/, затем рендер/звук, потом перенос обёрток (шаг C).
- 2026-10-14 17:50: шаг B (часть): в plat.h объявлен слой рендера (текстуры, blend/z, draw_tris, clear/flip, blit2d), заглушки platform/sdl/plat_render.c; native+hook собраны. Следующий: GL 3.3 бэкенд, win32-вариант plat, звук.
- 2026-10-14 18:00: шаг B (часть): в plat.h объявлен слой звука/CD, заглушки platform/sdl/plat_snd.c; native+hook собраны. Следующий: GL-бэкенд, win32-вариант plat, SDL_audio микшер.
- 2026-10-14 18:10: шаг B (часть): win32-вариант plat (platform/win32/plat_sys.c: время, sleep, лог, файлы); hook+native собраны. Следующий: GL-бэкенд, win32 render/snd, перенос обёрток (C).
- 2026-10-14 18:20: шаг B (часть): win32/plat_rs.c — render/звук заглушки для hook; native+hook собраны. Следующий: GL-бэкенд, SDL_audio микшер, перенос обёрток (C).
- 2026-10-14 18:40: шаг B (часть): SDL-звук — таблица буферов (create/destroy/play/stop/set/pos3d); native+hook собраны. Следующий: GL-бэкенд, SDL_audio микшер, перенос обёрток (C).
- 2026-10-14 18:55: шаг B (часть): CD-аудио — состояние трека (plat_cd_play/stop/current) в sdl; native+hook собраны. Следующий: GL-бэкенд, SDL_audio микшер, перенос обёрток (C).
- 2026-10-14 19:15: шаг B (часть): plat_local_hms (GetLocalTime) в sdl и win32; native+hook собраны, ctest ок. Следующий: перенос обёртки 004d986e (часы) и timeGetTime-тонков, GL-бэкенд, SDL_audio.
- 2026-10-14 19:20: шаг C: перенесена 004d986e (P21_DrawClock, над plat_local_hms), хук в install.c; native+hook собраны, ctest ок. Следующий: thunk 0040155f, timeGetTime-обёртки, GL-бэкенд.
- 2026-10-14 19:35: шаг C: перенесена 004d53e8 (P21_DrawFps, FPS-счётчик над plat_time_ms), хук; native+hook собраны, ctest ок. Следующий: 004d78f3/004bf910 (timeGetTime), GL-бэкенд, SDL_audio.
- 2026-10-14 19:45: шаг C: перенесена 004d78f3 (P21_FrameTicks, 20мс тики кадра над plat_time_ms), хук; native+hook собраны, ctest ок. Следующий: 004bf910 (FPS в буфер), GL-бэкенд, SDL_audio.
- 2026-10-14 19:55: шаг C: перенесена 004bf910 (P21_FpsToBuf, FPS в 8bpp буфер), хук; native+hook собраны, ctest ок. Следующий: GL-бэкенд, SDL_audio, ещё обёртки timeGetTime.
- 2026-10-14 20:25: шаг B (GL-бэкенд готов): re/platform/sdl/plat_render.c — OpenGL 3.3 core (текстуры, blend по значениям D3DBLEND, z-тест/запись, draw_tris с преобразованными вершинами и перспективно-корректным rhw, clear/flip, blit2d, readback); GL-функции через get_proc (SDL_GL_GetProcAddress / OSMesa). plat_window_open создаёт core-контекст 3.3. Тест tests/render_test.c рендерит offscreen через OSMesa (градиент, текстура, альфа-blend, z-тест, blit2d), проверяет пиксели и пишет PNG (build-native/render_test.png). native+hook собраны, ctest ок (v0.67). Следующий: SDL_audio микшер, затем перенос render-обёрток (81 функция) в re/game/ над plat_*.
