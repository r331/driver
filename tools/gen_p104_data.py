#!/usr/bin/env python3
"""Читает из .data Game.exe таблицу экрана графики 0054a170..0054a6f8 (0x588: пункты меню 0054a170..0054a25c,
подписи 0054a25c.., индексы строк 0054a640..0054a678, значения ползунков 0054a680..0054a690, 0054a694, строки SLIDER/SLIDEBOX 0054a698..)
куски вмятин по модели 00554fc4 (12 × 0x48), стороны записей операций по типу машины 0055b834 (12 × 0x170)
и пишет re/game/p104_data.h (v1.49). Адреса строк внутри остаются адресами Game.exe (re_ptr).
Запуск: python3 tools/gen_p104_data.py <Game.exe> re/game/p104_data.h"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
TABS = (("MENUGFX", 0x54a170, 0x588), ("DENT", 0x554fc4, 0x48 * 12), ("FACE", 0x55b834, 0x170 * 12))
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p104_data.py */\n#pragma once\n")
    for nm, a, n in TABS:
        b = rd(exe, a, n)
        f.write("#define P104_%s_ADDR 0x%08xu\n#define P104_%s_SIZE 0x%x\n" % (nm, a, nm, n))
        f.write("#define P104_%s_INIT { %s }\n" % (nm, ", ".join("0x%02x" % x for x in b)))
