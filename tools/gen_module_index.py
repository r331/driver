#!/usr/bin/env python3
"""Генерирует docs/MODULES.md — указатель модулей re/game: файл → сколько функций Game.exe он подменяет
(re_hook в re/platform/win32/install.c) → краткое описание (первый комментарий заголовка .h или .c).
Номер portedNN — порядковый номер шага переноса, а не тема, поэтому без указателя модуль не найти.
Запуск из корня репозитория: python3 tools/gen_module_index.py"""
import glob, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME = os.path.join(ROOT, 're', 'game')
inst = open(os.path.join(ROOT, 're', 'platform', 'win32', 'install.c'), encoding='utf-8').read()
hooked = {}
for m in re.finditer(r're_hook\(\s*0x([0-9a-fA-F]+)\s*,\s*\(void\s*\*\)\s*(\w+)', inst):
    hooked[m.group(2)] = int(m.group(1), 16)

def natkey(p):
    return [int(t) if t.isdigit() else t for t in re.split(r'(\d+)', os.path.basename(p))]

def first_comment(path):
    if not os.path.exists(path):
        return ''
    t = open(path, encoding='utf-8', errors='replace').read()
    for m in re.finditer(r'/\*(.*?)\*/', t, re.S):
        c = ' '.join(m.group(1).split())
        if not c or c.startswith('gvar-img') or c == '*gvi*':
            continue
        return c
    return ''

def short(c, n=170):
    c = c.replace('|', '/')
    return c if len(c) <= n else c[:n].rsplit(' ', 1)[0] + ' …'

rows = []
for c in sorted(glob.glob(os.path.join(GAME, '*.c')), key=natkey):
    base = os.path.splitext(os.path.basename(c))[0]
    src = open(c, encoding='utf-8', errors='replace').read()
    defs = set(re.findall(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{', src, re.M))
    n = sum(1 for f in defs if f in hooked)
    desc = first_comment(os.path.join(GAME, base + '.h')) or first_comment(c)
    lines = src.count('\n')
    rows.append((base, n, lines, short(desc)))

out = ['# Указатель модулей `re/game/`', '',
       'Сгенерировано `tools/gen_module_index.py` — не править вручную, перезапустить после добавления модуля.', '',
       'Номер `portedNN.c` — номер шага переноса (см. `docs/PLATFORM_PLAN.md`, `re/README.md`), а не тема модуля;',
       'префикс имён функций и переменных `PNN_` указывает на этот файл. «Хуков» — сколько функций файла подменяет',
       'оригинальные в Game.exe (`re_hook` в `re/platform/win32/install.c`, те же адреса в `re/platform/native/fn_table.c`).', '',
       '| Файл | Хуков | Строк | Что внутри (первый комментарий заголовка) |', '|---|---:|---:|---|']
for base, n, lines, desc in rows:
    out.append('| `%s.c` | %d | %d | %s |' % (base, n, lines, desc))
open(os.path.join(ROOT, 'docs', 'MODULES.md'), 'w', encoding='utf-8').write('\n'.join(out) + '\n')
print('docs/MODULES.md:', len(rows), 'модулей,', sum(r[1] for r in rows), 'хуков из', len(hooked))
