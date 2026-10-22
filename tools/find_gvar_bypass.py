#!/usr/bin/env python3
"""v2.11: ищет обращения к переменным образа данных (gvar_img_tab.c) в обход re_gvar — после препроцессора каждого game/*.c."""
import re, glob, os, subprocess, sys
R = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 're')   # v2.35: каталог re/ (по умолчанию — рядом с tools/)
tab = open(R + '/game/gvar_img_tab.c').read()
names = {}
for m in re.finditer(r'\{ 0x([0-9a-f]+)u, \(uint32_t\)sizeof\(([^)]*)\) \},\s*/\* (\w+) \*/', tab):
    names[m.group(3)] = m.group(1)
print('имён в образе:', len(names), file=sys.stderr)
tok = re.compile(r'\b[A-Za-z_]\w*\b')
for c in sorted(glob.glob(R + '/game/*.c')):
    if c.endswith('gvar_img_tab.c'): continue
    p = subprocess.run(['cc', '-E', '-P', '-std=gnu11', '-isystem', '/usr/include/SDL2', '-I', R + '/game', '-I', R + '/platform', '-I', R, c],
                       capture_output=True, text=True)
    s = p.stdout
    if p.returncode: print('ERR', c, p.stderr[:200]); continue
    s = re.sub(r're_gvar\(0x[0-9a-f]+u, (sizeof\([^()]*\)|0x[0-9a-f]+u?|\d+u?), \(void \*\)&\w+(\[0\])?\)', 're_gvar()', s)
    hits = {}
    for ch in s.split(';'):
        st = re.split(r'[{}]', ch)[-1].strip()
        if st.startswith('extern') or st.startswith('typedef'): continue
        for seg in re.split(r'[{}]', ch):
            seg2 = seg.strip()
            if seg2.startswith('extern') or seg2.startswith('typedef'): continue
            if re.match(r'^(static\s+)?(volatile\s+)?[A-Za-z_][\w ]*?\s\**(\w+)\s*(\[[^\]]*\])*(\s*=.*)?$', seg2, re.S) and not re.search(r'[()+\-/&|<>!?:.]', seg2.split('=')[0]): continue
            for t in tok.findall(seg):
                if t in names: hits.setdefault(t, ' '.join(seg2.split())[:140])
    for t, l in hits.items(): print(os.path.basename(c), t, names[t], '|', l)
