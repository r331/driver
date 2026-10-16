#!/usr/bin/env python3
"""v2.03: таблица «адрес Game.exe → перенесённая функция» для native из re_hook(...) platform/win32/install.c
(re_fn: колбэки меню, таймеров и т. п. по адресу). Пишет re/platform/native/fn_table.c; имена — только определённые в native-объектах (nm)."""
import re, os, subprocess, glob, sys
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 're')
src = open(os.path.join(R, 'platform/win32/install.c')).read()
ents = {}
for a, n in re.findall(r're_hook\(\s*0x([0-9a-fA-F]+)\s*,\s*\(void\s*\*\)\s*&?\s*(\w+)', src):
    ents.setdefault(int(a, 16), n)
objs = [o for o in glob.glob(os.path.join(R, 'build-native/CMakeFiles/driver.dir/game/*.o'))]
defined = set()
out = subprocess.run(['nm', '--defined-only', '-g'] + objs, capture_output=True, text=True).stdout
for l in out.split('\n'):
    p = l.split()
    if len(p) == 3 and p[1] in 'TtW': defined.add(p[2])
rows = sorted((a, n) for a, n in ents.items() if n in defined)
names = sorted(set(n for _, n in rows))
with open(os.path.join(R, 'platform/native/fn_table.c'), 'w') as f:
    f.write('/* v2.03: сгенерировано tools/gen_fn_table.py из re_hook(...) platform/win32/install.c — адрес Game.exe → перенос (re_fn). */\n')
    f.write('#include <stdint.h>\n#include <stddef.h>\ntypedef void (*re_fn_t)(void);\ntypedef struct { uint32_t addr; re_fn_t fn; } re_fnent_t;\n')
    for n in names: f.write('void %s(void);\n' % n)
    f.write('const re_fnent_t re_fn_table[] = {\n')
    for a, n in rows: f.write('  { 0x%08xu, (re_fn_t)%s },\n' % (a, n))
    f.write('};\nconst size_t re_fn_table_n = sizeof re_fn_table / sizeof re_fn_table[0];\n')
print('re_hook:', len(ents), 'в таблице:', len(rows), 'нет в native:', len(ents) - len(rows))
