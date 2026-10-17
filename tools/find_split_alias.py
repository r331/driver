#!/usr/bin/env python3
# v2.21: адреса образа данных (00546000..00d41000), у которых есть native-имя без re_gvar рядом с другим именем того же адреса
# (расщеплённый псевдоним). Запуск из re/game. Табличные обёртки (MENUGFX/MENUTAB/CARTAB/SLOTTAB/NODETAB) — один объект, не считаются.
import re,glob,collections
decl={}; gv=set()
for f in glob.glob('*.h')+glob.glob('*.c'):
    s=open(f,errors='replace').read()
    for m in re.finditer(r'#define\s+(\w+)\s+(\w*VAR)\(\s*([^,]+?)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)\s*\)',s):
        n,mac,t,n2,a=m.groups(); decl.setdefault(n,(int(a,16),mac,t.strip(),f))
    for m in re.finditer(r'#define\s+(\w+)\s+\(\*\([^)]*\)\s*re_gvar\(\s*(0x[0-9a-fA-F]+)',s): gv.add(m.group(1))
by=collections.defaultdict(list)
for n,(a,mac,t,f) in decl.items():
    if 0x546000<=a<0xd41000 and mac not in ('MENUGFX_VAR','MENUTAB_VAR','CARTAB_VAR','SLOTTAB_VAR','NODETAB_VAR'): by[a].append(n)
for n,(a,mac,t,f) in decl.items():
    if n in gv and 0x546000<=a<0xd41000 and n not in by[a]: by[a].append(n)
for a,ns in sorted(by.items()):
    ng=[n for n in ns if n not in gv]; g=[n for n in ns if n in gv]
    if ng and (g or len(ng)>1): print('%08x  отдельно: %s | в образе: %s'%(a,', '.join('%s<%s>'%(n,decl[n][2]) for n in ng),', '.join(g) or '-'))
