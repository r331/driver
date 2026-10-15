#!/usr/bin/env python3
"""Читает таблицы .data из Game.exe и пишет re/game/p99_data.h (для native, где .data пуст):
коробка передач 00560328 (4 × 5 int32), размеры команд компилятора событий 00551b32 (uint16 × 33) и их форматы 00551bb0
(адреса строк; адреса вне .data — пустые строки), спецформаты 00552454/00552458/0055245c.
Запуск: python3 tools/gen_p99_data.py <Game.exe> re/game/p99_data.h"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from pedump import rd
exe, dst = sys.argv[1], sys.argv[2]
def u32(a): return struct.unpack('<I', rd(exe, a, 4))[0]
def cstr(a): return rd(exe, a, 64).split(b'\0')[0].decode('latin-1')
N = 33
with open(dst, 'w') as f:
    f.write("/* Таблицы .data Game.exe для native. tools/gen_p99_data.py */\n#pragma once\n")
    g = [struct.unpack('<i', rd(exe, 0x560328 + i * 4, 4))[0] for i in range(20)]
    f.write("#define P99_GEAR_INIT { %s }\n" % ", ".join("{ %s }" % ", ".join(str(x) for x in g[i*5:i*5+5]) for i in range(4)))
    f.write("#define P99_CMD_N %d\n" % N)
    f.write("#define P99_CMDSZ_INIT { %s }\n" % ", ".join(str(struct.unpack('<H', rd(exe, 0x551b32 + i * 2, 2))[0]) for i in range(N)))
    fm = []
    for i in range(N):
        p = u32(0x551bb0 + i * 4)
        fm.append('"%s"' % cstr(p) if 0x550000 <= p < 0x560000 else '""')
    f.write("#define P99_CMDFMT_INIT { %s }\n" % ", ".join(fm))
    for nm, a in (("E", 0x552454), ("14", 0x552458), ("15", 0x55245c)):
        f.write('#define P99_FMT%s "%s"\n' % (nm, cstr(a)))
