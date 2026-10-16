#!/usr/bin/env python3
"""v2.01: начальные значения .data Game.exe для скалярных GAME_VAR_DEF native (блокер 4, docs/NATIVE_GAPS.md).
В native GAME_VAR_DEF — `type name;` без инициализатора (0). Генератор читает Game.exe (только чтение input/) по адресу
каждой скалярной переменной (int8/16/32, uint8/16/32, float, double) и для ненулевых байтов инициализированной части
секции (не .text) пишет запись в game/data_init.c. re_init_data_game() применяет запись, только если native-значение
после re_init_consts всё ещё нулевое; вызывается из platform/native/main.c в режиме игры (не в selftest).
Запуск: python3 tools/gen_data_init.py (из корня проекта)."""
import re, struct, glob, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
d = open(os.path.join(ROOT, 'input/game/Program_Executable_Files/Game.exe'), 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]; ns = struct.unpack_from('<H', d, pe + 6)[0]; osz = struct.unpack_from('<H', d, pe + 20)[0]
ib = struct.unpack_from('<I', d, pe + 52)[0]; so = pe + 24 + osz
secs = [struct.unpack_from('<8sIIIIIIHHI', d, so + i * 40) for i in range(ns)]
def rd(va, n):
    for s in secs:
        nm, vs, vaddr, rs, rp = s[0].rstrip(b'\0'), s[1], s[2], s[3], s[4]
        ch = s[-1]
        a = ib + vaddr
        if a <= va < a + max(vs, rs):
            if ch & 0x20 or nm == b'.idata': return None   # код и таблица импорта
            off = va - a
            if off + n > rs: return None         # .bss / неинициализированный хвост
            return d[rp + off: rp + off + n]
    return None
SIZES = {'int8_t': 1, 'uint8_t': 1, 'int16_t': 2, 'uint16_t': 2, 'int32_t': 4, 'uint32_t': 4, 'float': 4, 'double': 8}
rx = re.compile(r'^\s*GAME_VAR_DEF\(\s*(int8_t|uint8_t|int16_t|uint16_t|int32_t|uint32_t|float|double)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)\s*\)', re.M)
ents = []
for f in sorted(glob.glob(os.path.join(ROOT, 're/game/*.c'))):
    if os.path.basename(f) in ('data_init.c',): continue
    for t, name, addr in rx.findall(open(f, encoding='utf-8', errors='replace').read()):
        b = rd(int(addr, 16), SIZES[t])
        if b is None or not any(b): continue
        ents.append((t, name, int(addr, 16), b))
out = ['/* Автогенерация: tools/gen_data_init.py (v2.01). Начальные значения .data Game.exe для скалярных GAME_VAR_DEF native:',
       '   применяются re_init_data_game() только к нулевым после re_init_consts (режим игры, не selftest). */',
       '#include <stdint.h>', '#include <string.h>', '#ifndef RE_HOOK_BUILD']
for t, name, a, b in ents: out.append('extern %s %s;' % (t, name))
out.append('typedef struct { void *p; uint8_t n; uint8_t b[8]; } re_dinit_t;')
out.append('static const re_dinit_t k_dinit[] = {')
for t, name, a, b in ents:
    out.append('  { &%s, %d, { %s } },   /* %08x */' % (name, len(b), ', '.join('0x%02x' % x for x in b), a))
out.append('};')
out.append('int re_init_data_game(void) {   /* → число применённых значений */')
out.append('  int n = 0; static const uint8_t z[8];')
out.append('  for (unsigned i = 0; i < sizeof k_dinit / sizeof k_dinit[0]; i++)')
out.append('    if (memcmp(k_dinit[i].p, z, k_dinit[i].n) == 0) { memcpy(k_dinit[i].p, k_dinit[i].b, k_dinit[i].n); n++; }')
out.append('  return n;')
out.append('}')
out.append('#endif')
open(os.path.join(ROOT, 're/game/data_init.c'), 'w').write('\n'.join(out) + '\n')
print(len(ents), 'записей')
