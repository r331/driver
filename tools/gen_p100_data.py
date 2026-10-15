#!/usr/bin/env python3
"""Читает таблицы меню из .data Game.exe и пишет re/game/p100_data.h (для native, где .data пуст; v1.45):
обработчики меню 0054c810 (0x90) и 0054e0b0 (0x50), записи пунктов/таблицы обработчиков 0054d4a8..0054d890 (0x3e8),
таблица скоростей повтора 0054e33c (9 × uint32). Адреса функций/строк в таблицах остаются адресами Game.exe (re_fn/re_ptr).
Запуск: python3 tools/gen_p100_data.py <Game.exe> re/game/p100_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
TABS = (("C810", 0x54c810, 0x90), ("D4A8", 0x54d4a8, 0x3e8), ("E0B0", 0x54e0b0, 0x50), ("E33C", 0x54e33c, 0x24))
with open(dst, 'w') as f:
    f.write("/* Таблицы меню .data Game.exe для native. tools/gen_p100_data.py */\n#pragma once\n")
    for nm, a, n in TABS:
        b = rd(exe, a, n)
        f.write("#define P100_%s_ADDR 0x%08xu\n#define P100_%s_SIZE 0x%x\n" % (nm, a, nm, n))
        f.write("#define P100_%s_INIT { %s }\n" % (nm, ", ".join("0x%02x" % x for x in b)))
        if nm == "E33C":
            f.write("#define P100_E33C_U32 { %s }\n" % ", ".join("0x%08xu" % int.from_bytes(b[i:i+4], 'little') for i in range(0, n, 4)))
