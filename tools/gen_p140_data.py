#!/usr/bin/env python3
"""Читает .data Game.exe и пишет re/game/p140_data.h (для native, где .data пуст):
имена клавиш 0054b4b4 (0x21 строка по 0x10 байт, заменяются файлом KEYS.<язык> в 0040ec30).
Запуск: python3 tools/gen_p140_data.py <Game.exe> re/game/p140_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
a, s = 0x54b4b4, 0x210
b = rd(exe, a, s)
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p140_data.py */\n#pragma once\n")
    f.write("#define P140_KEYSTR_ADDR 0x%08xu\n#define P140_KEYSTR_SIZE 0x%x\n" % (a, s))
    f.write("#define P140_KEYSTR_INIT { %s }\n" % ", ".join(str(x) for x in b))
