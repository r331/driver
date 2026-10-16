#!/usr/bin/env python3
"""Читает из .data Game.exe таблицы для native и пишет re/game/p103_data.h (v1.48):
объекты миссий 00572f00..00573810 (0x910): записи 0x24 (+4 номер модели, +8 адрес имени модели), строки имён 0057368c..,
таблица адресов групп по миссии 005734ac (5 × uint32) и число записей 005734c0 (5 × int32).
Адреса строк в записях остаются адресами Game.exe (re_ptr; блок зарегистрирован в k_regions game/reptr.c).
Запуск: python3 tools/gen_p103_data.py <Game.exe> re/game/p103_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
TABS = (("MOBJ", 0x572f00, 0x910),)
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p103_data.py */\n#pragma once\n")
    for nm, a, n in TABS:
        b = rd(exe, a, n)
        f.write("#define P103_%s_ADDR 0x%08xu\n#define P103_%s_SIZE 0x%x\n" % (nm, a, nm, n))
        f.write("#define P103_%s_INIT { %s }\n" % (nm, ", ".join("0x%02x" % x for x in b)))
