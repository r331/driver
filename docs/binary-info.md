# Бинарник: Driver PC (диск DRIVER_PC, загружен Романом 2026-10-13)
- Образ: input/driver.bin (Mode1/2352, 723 649 248 байт), ISO-дерево (Joliet) → input/disc/, InstallShield DATA1.CAB → input/game/ (unshield)
- Исполняемый: input/game/Program_Executable_Files/Game.exe (1 736 751 байт; ставится как DRIVER.EXE), Config.exe — настройщик
- MD5 8e19d76a4bd5f3838a5c5cbf1cc5cfb5, SHA1 06ae86374f5df850c678583b556a9a4bc9811575
- PE32, база 0x400000, сборка 1999-09-10 16:35:21 UTC, линкер MSVC 6.0
- Debug-директория: D:\Driver\Game\Compat\Game.pdb (самого PDB на диске нет)
- Слинкован debug CRT (dbgheap.c, dbgrpt.c) → в .exe есть пути исходников (assert): Director.c, DirectorStorage.c, Engine\3dfx\Object.c, MScript.c, chairs.c, compiler.c, denting.c, eax\directsound.c, file.c, frontend\config.c, frontend\frontend.c, frontend\gvars.c, general.c, lamps.c, map.c, mirror.c, motion_c.c, overlay.c, replays.c, roadbits.c
- Импорты: KERNEL32, USER32, GDI32, ole32, WINMM, DDRAW, DSOUND, DINPUT
- *.map в Data_Files — карты городов (данные), не линкер-карты
- Скрипт распаковки образа: work/isox.py
