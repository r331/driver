#!/usr/bin/env python3
"""Читает .data Game.exe и пишет re/game/p143_data.h (для native, где .data пуст):
005536a8..005537c8 — записи спрайтов-вспышек: SUN2 005536a8 (0x20), BLANK 005536c8 (0x20), CARLIGHT 005536e8 (8 × 0x1c):
+0 адрес имени, +4 значок, +8 цвет RGB, +0xc яркость, +0x10/+0x14 экранные x/y, +0x18 размер (004b418d, 004b5049, 004b4b27).
Запуск: python3 tools/gen_p143_data.py <Game.exe> re/game/p143_data.h"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
a, s = 0x5536a8, 0x120
w = struct.unpack('<%dI' % (s // 4), rd(exe, a, s))
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p143_data.py */\n#pragma once\n")
    f.write("#define P143_FX_ADDR 0x%08xu\n#define P143_FX_WORDS 0x%x\n" % (a, s // 4))
    f.write("#define P143_FX_INIT { %s }\n" % ", ".join("0x%xu" % x for x in w))
