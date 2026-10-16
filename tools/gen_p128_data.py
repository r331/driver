#!/usr/bin/env python3
"""Читает таблицы .data Game.exe и пишет re/game/p128_data.h (для native, где .data пуст):
00559254..0055a6f4 (11 × 0x1e0) — карты распространения повреждений машин видов 1..11 (вид 0 — P28_Dst1 00559074);
читает 004c032a (P128_CarDeform).
Запуск: python3 tools/gen_p128_data.py <Game.exe> re/game/p128_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
tabs = [("DMG", 0x559254, 11 * 0x1e0)]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p128_data.py */\n#pragma once\n")
    for n, a, s in tabs:
        b = rd(exe, a, s)
        f.write("#define P128_%s_ADDR 0x%08xu\n#define P128_%s_SIZE 0x%x\n" % (n, a, n, s))
        f.write("#define P128_%s_INIT { %s }\n" % (n, ", ".join(str(x) for x in b)))
