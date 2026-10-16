#!/usr/bin/env python3
"""Читает таблицу .data из Game.exe и пишет re/game/p111_data.h (для native, где .data пуст):
цвета вспышек 00553870 (14 записей по 0x1c = 7 × int32: r, g, b, …; индекс — uint16 +0x64 записи вспышки, 004b6deb).
За записью 13 (00553a18) начинаются float-данные — таблица кончается там.
Запуск: python3 tools/gen_p111_data.py <Game.exe> re/game/p111_data.h"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
N = 14
v = struct.unpack('<%di' % (N * 7), rd(exe, 0x553870, N * 0x1c))
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p111_data.py */\n#pragma once\n")
    f.write("#define P111_FLARE_N %d\n#define P111_FLARE_INIT { %s }\n" % (N, ", ".join(
        "{ %s }" % ", ".join(str(x) for x in v[i * 7:i * 7 + 7]) for i in range(N))))
