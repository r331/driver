#!/usr/bin/env python3
"""Читает таблицы .data из Game.exe и пишет re/game/p74_data.h (для native, где .data пуст).
Запуск: python3 tools/gen_p74_data.py <Game.exe> re/game/p74_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
tabs = [("P74_DistInit", 0x55272c, 65), ("P74_KeyAInit", 0x54ae10, 256), ("P74_KeyBInit", 0x54af10, 256)]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p74_data.py */\n")
    for n, a, l in tabs:
        b = rd(exe, a, l)
        f.write("static const uint8_t %s[%d] = { /* 0x%08x */\n" % (n, l, a))
        for i in range(0, l, 24): f.write("  " + ", ".join(str(x) for x in b[i:i+24]) + ",\n")
        f.write("};\n")
