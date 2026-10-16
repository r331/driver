#!/usr/bin/env python3
"""Читает таблицы .data Game.exe и пишет re/game/p127_data.h (для native, где .data пуст):
00574710..00574f08 (0x7f8) — меню паузы/конца миссии, адреса которых Pause (0050ee00) пишет в 00b5a730
(00574710, 005747d8, 00574868, 005748f8, 005749b0, 00574a40, 00574ad0, 00574b60, 00574bf0, 00574c90, 00574ce0,
00574d48, 00574db0, 00574e28, 00574ea0); 0054cf80..0054cfd8 (0x58) — экран ввода имени (004131a0).
Запуск: python3 tools/gen_p127_data.py <Game.exe> re/game/p127_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
tabs = [("PAUSE", 0x574710, 0x7f8), ("NAME", 0x54cf80, 0x58)]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p127_data.py */\n#pragma once\n")
    for n, a, s in tabs:
        b = rd(exe, a, s)
        f.write("#define P127_%s_ADDR 0x%08xu\n#define P127_%s_SIZE 0x%x\n" % (n, a, n, s))
        f.write("#define P127_%s_INIT { %s }\n" % (n, ", ".join(str(x) for x in b)))
