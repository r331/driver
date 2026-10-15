#!/usr/bin/env python3
"""Генерирует re/game/p79_data.h: таблицы шагов записей модели (0x550acc, 112 int) и описание
преобразования записей диска → записи в памяти для 00475a3d (разбор switch из out/Game_decomp.c).
Запуск из корня проекта: python3 tools/gen_p79_data.py"""
import re, struct, sys, subprocess
exe = open('input/game/Program_Executable_Files/Game.exe', 'rb').read()
pe = struct.unpack_from('<I', exe, 0x3c)[0]
ns = struct.unpack_from('<H', exe, pe + 6)[0]; so = struct.unpack_from('<H', exe, pe + 20)[0]
base = struct.unpack_from('<I', exe, pe + 52)[0]
def rd(va, n):
    rva = va - base
    for i in range(ns):
        o = pe + 24 + so + i * 40
        vs, vr, rs, rp = struct.unpack_from('<IIII', exe, o + 8)
        if vr <= rva < vr + max(vs, rs): return exe[rp + rva - vr: rp + rva - vr + n]
steps = struct.unpack('<112I', rd(0x550acc, 448))
t = open('out/Game_decomp.c', errors='replace').read()
body = re.split(r'^// 00475a3d\n', t, flags=re.M)[1].split('\n// ')[0]
sw = body[body.index('switch(local_c)'):]
groups = re.split(r'(?=\n    case )', sw)
ops = []; start = {}
for g in groups:
    cases = [int(x, 16) for x in re.findall(r'case (0x[0-9a-f]+):|case (\d+):', g) for x in x if x] if False else None
    cs = re.findall(r'case (0x[0-9a-f]+|\d+):', g)
    if not cs: continue
    key = int(cs[0], 0)
    start[key] = len(ops)
    lst = []
    for m in re.finditer(r'\*\(uint \*\)\(pbVar2 \+ (0x[0-9a-f]+|\d+)\) = \(uint\)\*\(ushort \*\)\(local_14 \+ (0x[0-9a-f]+|\d+)\);', g):
        lst.append(('U', int(m.group(1), 0), int(m.group(2), 0)))
    for m in re.finditer(r'\*\(float \*\)\(pbVar2 \+ (0x[0-9a-f]+|\d+)\) = \(float\)local_14\[(0x[0-9a-f]+|\d+)\];', g):
        lst.append(('F', int(m.group(1), 0), int(m.group(2), 0)))
    if 'pbVar2[2] = local_14[1];' in g: lst.append(('B', 2, 1))
    ops += lst
    start[(key, 'n')] = len(lst)
out = ['/* Сгенерировано tools/gen_p79_data.py из Game.exe и out/Game_decomp.c — не править вручную. */',
       'static const int32_t P79_Steps[112] = {' + ','.join(map(str, steps)) + '};',
       'typedef struct { char op; uint8_t dst, src; } p79_op_t;',
       'static const p79_op_t P79_Ops[] = {' + ','.join('{\'%s\',%d,%d}' % o for o in ops) + '};',
       '/* индекс k = (type & 7) | (type & 0x10 ? 8 : 0): начало и число операций */']
ks = sorted(k for k in start if isinstance(k, int))
sidx = [(0, 0)] * 16
for key in ks:
    k = (key & 7) | (8 if key & 0x10 else 0)
    sidx[k] = (start[key], start[(key, 'n')])
out.append('static const uint16_t P79_OpIdx[16][2] = {' + ','.join('{%d,%d}' % s for s in sidx) + '};')
open('re/game/p79_data.h', 'w').write('\n'.join(out) + '\n')
print(len(ops), 'ops', ks)
