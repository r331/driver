#!/usr/bin/env python3
"""v2.05: таблицы обработчиков записей моделей Game.exe (.data 0055082c/0055090c/005509ec — программный набор,
00550cfc/00550ddc/00550ebc — аппаратный, по 56 адресов) → re/game/p84_handlers.h: адреса с раскрытыми thunk-ами (jmp rel32).
В native игре P84_InitGameHandlers переводит их re_fn; неперенесённые — P85_SkipRecord (запись пропускается)."""
import struct, os
P = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
exe = open(os.path.join(P, 'input/game/Program_Executable_Files/Game.exe'), 'rb').read()
pe = struct.unpack('<I', exe[0x3c:0x40])[0]; ns = struct.unpack('<H', exe[pe+6:pe+8])[0]; osz = struct.unpack('<H', exe[pe+20:pe+22])[0]
secs = []; o = pe + 24 + osz
for i in range(ns):
    n, vs, va, rs, rp = struct.unpack('<8sIIII', exe[o:o+24]); secs.append((va + 0x400000, vs, rp, rs)); o += 40
def rd(a, n):
    for va, vs, rp, rs in secs:
        if va <= a < va + max(vs, rs): return exe[rp + a - va: rp + a - va + n]
def tgt(a):
    b = rd(a, 5)
    return (a + 5 + struct.unpack('<i', b[1:])[0]) & 0xffffffff if b and b[0] == 0xe9 else a
L = ['/* Автогенерация: tools/gen_p84_handlers.py (v2.05). Обработчики записей моделей по типу (0..55), thunk-и раскрыты. */',
     'static const uint32_t P84_HandAddr[6][56] = {']
for t, base in enumerate([0x55082c, 0x55090c, 0x5509ec, 0x550cfc, 0x550ddc, 0x550ebc]):
    v = struct.unpack('<56I', rd(base, 0xe0))
    L.append('  { /* %08x */ ' % base + ', '.join('0x%08xu' % (tgt(a) if a else 0) for a in v) + ' },')
L.append('};')
open(os.path.join(P, 're/game/p84_handlers.h'), 'w').write('\n'.join(L) + '\n')
print('ok')
