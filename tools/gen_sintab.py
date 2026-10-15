#!/usr/bin/env python3
"""Читает таблицу синусов (0x576f10, 4096 x int16) из Game.exe и пишет re/game/sintab_data.h.
Запуск: python3 tools/gen_sintab.py <путь к Game.exe> <куда>"""
import struct, sys
exe, dst = sys.argv[1], sys.argv[2]
d = open(exe, 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
ns = struct.unpack_from('<H', d, pe + 6)[0]; osz = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 52)[0]
va = 0x576f10
for i in range(ns):
    n, vs, sva, rs, ro = struct.unpack_from('<8sIIII', d, pe + 24 + osz + i * 40)
    if sva + base <= va < sva + base + max(vs, rs):
        o = ro + va - (sva + base); t = struct.unpack_from('<4096h', d, o); break
with open(dst, 'w') as f:
    f.write("/* Таблица синусов Game.exe (0x576f10): sin * 4096 для 4096 углов. tools/gen_sintab.py */\nstatic const int16_t P59_SinInit[4096] = {\n")
    for i in range(0, 4096, 16): f.write("  " + ", ".join(map(str, t[i:i+16])) + ",\n")
    f.write("};\n")
