#!/usr/bin/env python3
"""Читает .data Game.exe и пишет re/game/p141_data.h (для native, где .data пуст):
0054bd10..0054bee0 — таблица экрана рекордов (0x1d records по 0x10: адрес текста, -1, x/y, флаги; заполняет 0040f3de),
0054bf1c..0054bf90 — строки «1:».. «5:», «/», форматы и «-», на которые в таблице лежат адреса.
Запуск: python3 tools/gen_p141_data.py <Game.exe> re/game/p141_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p141_data.py */\n#pragma once\n")
    for nm, a, s in (("HSMENU", 0x54bd10, 0x1d0), ("HSSTR", 0x54bf1c, 0x74)):
        b = rd(exe, a, s)
        f.write("#define P141_%s_ADDR 0x%08xu\n#define P141_%s_SIZE 0x%x\n" % (nm, a, nm, s))
        f.write("#define P141_%s_INIT { %s }\n" % (nm, ", ".join(str(x) for x in b)))
