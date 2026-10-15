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
- 2026-10-14 20:25: шаг B (микшер готов): plat_snd.c — программный микшер 44100 Гц стерео S16 (8/16 бит, pitch линейной интерполяцией, volume/pan в сотых дБ как DirectSound, loop), вывод через SDL_audio (plat_snd_open/close), tests/snd_test.c проверяет сэмплы без устройства; native+hook собраны, ctest ок (v0.68). Следующий: перенос render-обёрток (81 функция) в re/game/ над plat_*.
- 2026-10-14 20:50: шаг C: render-обёртки состояния (ported22: 11 функций) над plat_scene_begin/end, plat_set_render_state, plat_set_tex_stage, plat_set_viewport (SDL: GL depth func/scissor; hook: IDirect3DDevice3 vtable). Найдено: 81 хукнутая функция в 0x41d9xx–0x4e43xx — stdcall (ret N), а хуки были cdecl → исправлено переходником в re_hook (platform/win32/stdcall_tbl.h, tools/gen_stdcall.py); G6Call0041F57D теперь вызывается как __stdcall. ctest ок (render_test: ZFUNC), hook собран (v0.69). Следующий: остальные render-обёртки (0041e462/0041e4b9, 0041ec82, DirectDraw-поверхности 004206xx–00422xxx, DirectSound 0048bxxx) с plat_* для поверхностей/звука.
- 2026-10-14 21:10: шаг C: 7 render-функций (ported23): конвертация вершин игры в plat_vertex (00421cfe/00421db8, fistp→lrintf), линии (0041e462/0041e4b9 → plat_draw_lines, GL_LINES), SetBlendMode 0041d9d2 (stdcall ret 0x10 — переходник), InitRenderStates 00421521, ClearZ 00420e93 (plat_clear_depth, D3D Viewport3::Clear2 в hook). Тест test_p23, ctest ок, hook собран (v0.70). Следующий: DirectDraw-обёртки (004206xx–00422xxx: поверхности/палитры/клиппер), 0041ec82 (Flip, __thiscall?), потом DirectSound 0048bxxx.
- 2026-10-14 21:55: шаг C: 12 DirectDraw/Direct3D-обёрток (ported24, v0.71) над новым слоем plat_dd_*/plat_d3d_* (поверхности, клиппер, устройство, viewport, заливка, потеря поверхностей); SDL — учётные заглушки (platform/sdl/plat_dd.c), hook — vtable Game.exe; тест test_p24, native ctest ок, hook собран. Всего 1297. Следующий: DirectDraw-создание 0041fac0/00420038 (DirectDrawCreate), 004213dc (Z-surface), 0041ec82 (Flip), 0041f2a0/0041f57d, затем DirectSound 0048bxxx.
- 2026-10-14 22:05: шаг C: 13 функций CD-аудио и таймеров (ported25, v0.72) над новым слоем plat_cd_*/plat_aux_*/plat_timer_* (hook — winmm напрямую, SDL — заглушка CD + SDL_AddTimer); колбэк таймера 005282e1 — stdcall через переходник; test_p25, native ctest ок, hook собран (-lwinmm). Всего 1310. Следующий: DirectDraw-создание 0041fac0/00420038 (DirectDrawCreate), 004213dc (Z-surface), 0041ec82 (Flip), 0041f2a0/0041f57d, DirectSound 0048bxxx, окно 005223dc/005224a8.
