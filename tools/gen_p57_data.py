#!/usr/bin/env python3
"""Читает .data меню 0057b578..0057b658 из Game.exe и пишет re/game/p57_data.h (для native, где .data пуст):
0057b578 — номера пунктов (P54_SelTab, 12 × int32), 0057b5a8 — таблица меню опций (11 записей по 0x10:
три адреса обработчиков + 4 байта навигации; заполняет 004048dd).
Запуск: python3 tools/gen_p57_data.py <Game.exe> re/game/p57_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
b = rd(exe, 0x57b578, 0xe0)
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p57_data.py */\n#pragma once\n")
    f.write("#define P57_MENU_INIT { %s }\n" % ", ".join(str(x) for x in b))
