#!/usr/bin/env python3
# v2.21: адреса образа данных (00546000..01287000 — re_gvar_img_size 00d41000 от базы 00546000), у которых есть native-имя без re_gvar рядом с другим именем того же адреса
# (расщеплённый псевдоним). Запуск из re/game. v2.35: имена-представления (native-макрос над другим объектом) не считаются. Табличные обёртки (MENUGFX/MENUTAB/CARTAB/SLOTTAB/NODETAB) — один объект, не считаются.
import re,glob,collections
decl={}; gv=set()
for f in glob.glob('*.h')+glob.glob('*.c'):
    s=open(f,errors='replace').read()
    for m in re.finditer(r'#define\s+(\w+)\s+(\w*VAR)\(\s*([^,]+?)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)\s*\)',s):
        n,mac,t,n2,a=m.groups(); decl.setdefault(n,(int(a,16),mac,t.strip(),f))
    for m in re.finditer(r'#define\s+(\w+)\s+\(\*\([^)]*\)\s*re_gvar\(\s*(0x[0-9a-fA-F]+)',s): gv.add(m.group(1))
# v2.35: native redefinitions after the declaration (#undef NAME / #define NAME <expr> in a non-hook block), which make NAME a
# view of another object: a macro over another declared name, re_gvar with another name's fallback, re_ptr/re_addr of a cell
# or pointer, a union member.  Such a NAME is not a separate native object.
view=set(); txt={}
for f in glob.glob('*.h')+glob.glob('*.c'):
    s=open(f,errors='replace').read(); txt[f]=s
for f,s in txt.items():
    for m in re.finditer(r'#define\s+(\w+)\s+(.+)',s):
        n,body=m.group(1),m.group(2)
        if n not in decl or re.match(r'\w*VAR\(',body): continue
        if re.match(r'\(\*\([^)]*\)\s*re_gvar\(\s*0x[0-9a-fA-F]+u?\s*,\s*sizeof\([^)]*\)\s*,\s*\(void \*\)&'+n+r'\b',body): continue
        if re.search(r'\bre_gvar\b|\bre_ptr\b|\bre_addr\w*\b|\b[A-Za-z]\w*U\.[bw]\b',body) or re.fullmatch(r'\s*\(?\s*\w+\s*\)?\s*',body) or re.search(r'\b(P|G|S|D|A)\w*_\w+',body):
            view.add(n)
# v2.35: и имена, у которых есть только GAME_VAR_DEF (без #define в заголовке)
for f,s in txt.items():
    for m in re.finditer(r'GAME_VAR_DEF\(\s*([^,]+?)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)\s*\)',s):
        t,n,a=m.groups()
        if n not in decl and int(a,16): decl[n]=(int(a,16),'DEF',t,f)
by=collections.defaultdict(list)
for n,(a,mac,t,f) in decl.items():
    if a and mac not in ('MENUGFX_VAR','MENUTAB_VAR','CARTAB_VAR','SLOTTAB_VAR','NODETAB_VAR'): by[a].append(n)
for n,(a,mac,t,f) in decl.items():
    if n in gv and 0x546000<=a<0x1287000 and n not in by[a]: by[a].append(n)
for a,ns in sorted(by.items()):
    ns=[n for n in ns if n not in view]
    ng=[n for n in ns if n not in gv]; g=[n for n in ns if n in gv]
    if ng and (g or len(ng)>1): print('%08x  отдельно: %s | в образе: %s'%(a,', '.join('%s<%s>'%(n,decl[n][2]) for n in ng),', '.join(g) or '-'))
