#!/usr/bin/env python3
"""Читает таблицы .data Game.exe и пишет re/game/p117_data.h (для native, где .data пуст):
пункты меню паузы/опций (записи 0x14 байт, конец — флаг 0x10 в байте +5):
00574f08 (0x140, меню звука; P97_SndMenu = +0x30), 00575088 (0x2a8, меню управления), 00575370 (0x168, ввод имени).
Запуск: python3 tools/gen_p117_data.py <Game.exe> re/game/p117_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
tabs = [("A", 0x574f08, 0x140), ("B", 0x575088, 0x2a8), ("C", 0x575370, 0x168)]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p117_data.py */\n#pragma once\n")
    for n, a, s in tabs:
        b = rd(exe, a, s)
        f.write("#define P117_MENU%s_ADDR 0x%08xu\n#define P117_MENU%s_SIZE 0x%x\n" % (n, a, n, s))
        f.write("#define P117_MENU%s_INIT { %s }\n" % (n, ", ".join(str(x) for x in b)))
