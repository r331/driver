#!/usr/bin/env python3
"""Читает таблицу .data Game.exe и пишет re/game/p118_data.h (для native, где .data пуст):
маршрут камеры меню 0054e774 (0x58 байт): +0 — 17 пар (камера, камера) прямого направления,
+0x24 — по 3 байта на камеру: флаг «прямой переход», первый и последний ключ P99_CamKeys.
Запуск: python3 tools/gen_p118_data.py <Game.exe> re/game/p118_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
a, s = 0x54e774, 0x58
b = rd(exe, a, s)
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p118_data.py */\n#pragma once\n")
    f.write("#define P118_ROUTE_ADDR 0x%08xu\n#define P118_ROUTE_SIZE 0x%x\n" % (a, s))
    f.write("#define P118_ROUTE_INIT { %s }\n" % ", ".join(str(x) for x in b))
