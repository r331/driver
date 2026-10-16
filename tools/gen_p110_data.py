#!/usr/bin/env python3
"""Читает таблицу .data из Game.exe и пишет re/game/p110_data.h (для native, где .data пуст):
типы клеток сетки радара 00574574 (64 × int32, индекс — значение клетки P77_C5FE00).
Запуск: python3 tools/gen_p110_data.py <Game.exe> re/game/p110_data.h"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
v = struct.unpack('<64i', rd(exe, 0x574574, 256))
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p110_data.py */\n#pragma once\n")
    f.write("#define P110_CELLTAB_N 64\n#define P110_CELLTAB_INIT { %s }\n" % ", ".join(str(x) for x in v))
