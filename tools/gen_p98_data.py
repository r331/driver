#!/usr/bin/env python3
"""Читает таблицы .data из Game.exe и пишет re/game/p98_data.h (для native, где .data пуст):
титры 005527a0 (записи 0xc до вида 8), высоты видов 00552de8, имена лиц 00552e1c → строки 005532cc.
Запуск: python3 tools/gen_p98_data.py <Game.exe> re/game/p98_data.h"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
def u32(a): return struct.unpack('<I', rd(exe, a, 4))[0]
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p98_data.py */\n#pragma once\n")
    n = 0
    while rd(exe, 0x5527a0 + n * 12, 1)[0] != 8: n += 1
    n += 1
    f.write("#define P98_CREDITS_N %d\n" % n)
    f.write("#define P98_CREDITS_INIT { \\\n")
    for i in range(n):
        b = rd(exe, 0x5527a0 + i * 12, 12)
        f.write("  { %d, %d, { 0, 0 }, %d, 0x%08xu }, \\\n" % (b[0], b[1], struct.unpack('<i', b[4:8])[0], struct.unpack('<I', b[8:12])[0]))
    f.write("}\n")
    f.write("#define P98_CREDH_INIT { %s }\n" % ", ".join(str(struct.unpack('<i', rd(exe, 0x552de8 + i * 4, 4))[0]) for i in range(8)))
    names = []
    while True:
        p = u32(0x552e1c + len(names) * 4)
        if not (0x5532cc <= p < 0x5533a4): break
        names.append(p)
    f.write("#define P98_FACES_N %d\n#define P98_FACES_INIT { %s }\n" % (len(names), ", ".join("0x%08xu" % p for p in names)))
    blk = rd(exe, 0x5532cc, 0x5533a4 - 0x5532cc)
    f.write("#define P98_FACEBLK_N %d\n#define P98_FACEBLK_INIT { %s }\n" % (len(blk), ", ".join(str(x) for x in blk)))
