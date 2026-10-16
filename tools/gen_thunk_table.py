#!/usr/bin/env python3
"""v2.12: таблица переходников инкрементальной компоновки Game.exe (jmp rel32 подряд с 00401000) → re/platform/native/thunk_table.c.
re_fn: адрес thunk-а (например 004013c5 → 00416540, обработчик пункта мотеля в 005fea44) разрешается в цель."""
import os, struct
B = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
d = open(os.path.join(B, 'input/game/Program_Executable_Files/Game.exe'), 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]; opt = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
rows = []
for i in range(nsec):
    s = pe + 24 + opt + i * 40
    va, raw = struct.unpack_from('<I', d, s + 12)[0], struct.unpack_from('<I', d, s + 20)[0]
    if d[s:s + 5] != b'.text': continue
    a = base + va
    while d[raw + (a - base - va)] == 0xcc: a += 1
    while d[raw + (a - base - va)] == 0xe9:
        o = raw + (a - base - va)
        t = (a + 5 + struct.unpack_from('<i', d, o + 1)[0]) & 0xffffffff
        rows.append((a, t)); a += 5
with open(os.path.join(B, 're/platform/native/thunk_table.c'), 'w') as f:
    f.write('/* v2.12: сгенерировано tools/gen_thunk_table.py — thunk Game.exe (jmp rel32) → цель, для re_fn. */\n')
    f.write('#include <stdint.h>\n#include <stddef.h>\nconst uint32_t re_thunk_table[][2] = {\n')
    for a, t in rows: f.write('  { 0x%08xu, 0x%08xu },\n' % (a, t))
    f.write('};\nconst size_t re_thunk_table_n = sizeof re_thunk_table / sizeof re_thunk_table[0];\n')
print('thunk-ов:', len(rows), 'первый %08x последний %08x' % (rows[0][0], rows[-1][0]))
