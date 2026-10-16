#!/usr/bin/env python3
"""v2.03: переменные GAME_VAR с адресом в .rdata+.data Game.exe (00546000..0057c000) в native-игре живут в образе секций.
В конец каждого заголовка re/game/*.h — блок #undef NAME / #define NAME (*(type *)re_gvar(addr, sizeof(type), (void *)&NAME));
определения GAME_VAR_DEF таких имён в .c — через push_macro/pop_macro. Повторный запуск перегенерирует блоки."""
import re, glob, os, sys
G = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 're', 'game')
LO, HI = 0x00546000, 0x01287000   # .rdata+.data (с .bss) Game.exe
BEG = '/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */'
END = '/* gvar-img v2.03 end */'
rx = re.compile(r'^\s*#\s*define\s+(\w+)\s+GAME_VAR\(\s*([^,]+?)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)u?\s*\)', re.M)
undef = set()
hdrs = sorted(glob.glob(os.path.join(G, '*.h')))
for h in hdrs:
    s = open(h).read()
    s = re.sub(re.escape(BEG) + r'.*?' + re.escape(END) + r'\n?', '', s, flags=re.S)
    s = '\n'.join(l for l in s.split('\n') if not l.endswith('/*gvi*/'))
    for m in re.finditer(r'#\s*undef\s+(\w+)', s): undef.add(m.group(1))
    for m in re.finditer(r'^\s*#\s*define\s+(\w+)[ \t]+(?=\S)(?!GAME_VAR\()', s, re.M): undef.add(m.group(1))   # переопределён другим макросом
skip = set(sys.argv[1:])
# только типы с одинаковой раскладкой в Game.exe и в 64-битной native: скаляры до 32 бит, float/double и typedef-массивы из них
SCAL = {'int8_t','uint8_t','int16_t','uint16_t','int32_t','uint32_t','float','double','char','unsigned char','signed char','short',
        'unsigned short','int','unsigned','unsigned int'}
safe = set(SCAL)
# структуры, проверенные вручную: одинаковая раскладка в 32-битной Game.exe и в native (только 32-битные поля, _Static_assert размера)
safe |= {'p42_var_t', 'p42_vartab_t', 'p88_cell_t', 'p42_cmd_t', 'p42_cmdtab_t'}   # v2.05: p88_cell_t — 9 × int32 + 4 байта; v2.08: p42_cmd_t — char[0x100] + 4 × int32 (таблица команд MScript 00563980)
alltxt = ''.join(open(h).read() for h in hdrs)
for _ in range(3):
    for m in re.finditer(r'typedef\s+([\w ]+?)\s+(\w+)\s*((?:\[[^\]]+\])+)\s*;', alltxt):
        if m.group(1).strip() in safe: safe.add(m.group(2))
    for m in re.finditer(r'typedef\s+([\w ]+?)\s+(\w+)\s*;', alltxt):
        if m.group(1).strip() in safe: safe.add(m.group(2))
names = {}
total = 0
for h in hdrs:
    s = open(h).read()
    s = re.sub(re.escape(BEG) + r'.*?' + re.escape(END) + r'\n?', '', s, flags=re.S)
    out = []
    for m in rx.finditer(s):
        n, t, n2, a = m.groups(); a = int(a, 16)
        if n != n2 or not (LO <= a < HI) or n in undef or n in skip or n in names or t.strip() not in safe: continue
        names[n] = (t, a); out.append((n, t, a))
    if out:
        blk = [BEG, '#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)']
        for n, t, a in out:
            blk += ['#undef %s' % n, '#define %s (*(%s *)re_gvar(0x%08xu, sizeof(%s), (void *)&%s))' % (n, t, a, t, n)]
        blk += ['#endif', END]
        s = s.rstrip('\n') + '\n' + '\n'.join(blk) + '\n'
        total += len(out)
    open(h, 'w').write(s)
# определения
dx = re.compile(r'^([ \t]*)GAME_VAR_DEF\(\s*([^,]+?)\s*,\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+)u?\s*\)[ \t]*;?[ \t]*(/\*.*?\*/|//.*)?$', re.M)
nd = 0
for c in sorted(glob.glob(os.path.join(G, '*.c'))):
    s = open(c).read()
    s = re.sub(r'#ifndef RE_HOOK_BUILD /\* gvar-img \*/\n#pragma push_macro\("(\w+)"\)\n#undef \w+\n(.*?) \1;\n#pragma pop_macro\("\w+"\)\n#endif\n',
               lambda m: 'GAME_VAR_DEF(%s, %s, 0x%08x)\n' % (m.group(2), m.group(1), names.get(m.group(1), ('', 0))[1]), s)
    def rep(m):
        global nd
        ind, t, n, a, cm = m.groups()
        if n not in names: return m.group(0)
        nd += 1
        return '#ifndef RE_HOOK_BUILD /* gvar-img */\n#pragma push_macro("%s")\n#undef %s\n%s %s;\n#pragma pop_macro("%s")\n#endif' % (n, n, t, n, n)
    s2 = dx.sub(rep, s)
    if s2 != s: open(c, 'w').write(s2)
# объявления/определения с первой колонки (extern T NAME; T NAME = …;) — имя без подстановки макроса
decl = re.compile(r'^(static\s+|extern\s+|const\s+|volatile\s+)*[A-Za-z_]\w*(\s*\*)*\s+\**\s*[A-Za-z_]')
idrx = re.compile(r'\b[A-Za-z_]\w*\b')
PUSH = '#pragma push_macro("%s") /*gvi*/'; POP = '#pragma pop_macro("%s") /*gvi*/'; UND = '#undef %s /*gvi*/'
nw = 0
wrapset = set(names)
for _ in range(3):   # макросы-псевдонимы #define A B, где B — перенаправленное имя
    for m in re.finditer(r'^\s*#\s*define\s+(\w+)\s+(\w+)\s*(?:/\*.*?\*/|//.*)?$', alltxt, re.M):
        if m.group(2) in wrapset: wrapset.add(m.group(1))
    for m in rx.finditer(alltxt):
        if m.group(3) in wrapset: wrapset.add(m.group(1))   # #define A GAME_VAR(type, B, addr)
for f in sorted(glob.glob(os.path.join(G, '*.c')) + hdrs):
    lines = open(f).read().split('\n')
    lines = [l for l in lines if not l.endswith('/*gvi*/')]
    out = []; inblk = False
    for l in lines:
        if l.startswith(BEG): inblk = True
        if l.startswith(END): inblk = False
        if (not inblk and l and not l[0].isspace() and l[0] not in '#/}{*' and decl.match(l) and not l.startswith('return')
                and not re.match(r'^[^=]*?\b\w+\s*\((?!\s*\*)', re.sub(r'/\*.*?\*/|//.*', '', l))):
            code = re.sub(r'/\*.*?\*/|//.*', '', l)
            ids = [i for i in dict.fromkeys(idrx.findall(code)) if i in wrapset]
            if ids:
                nw += 1
                for i in ids: out += [PUSH % i, UND % i]
                out.append(l)
                for i in reversed(ids): out.append(POP % i)
                continue
        out.append(l)
    open(f, 'w').write('\n'.join(out))
# таблица перенаправленных диапазонов для re_ptr (game/gvar_img_tab.c)
hdr_of = {}
for h in hdrs:
    t = open(h).read()
    for m in rx.finditer(t):
        if m.group(1) in names and m.group(1) not in hdr_of: hdr_of[m.group(1)] = os.path.basename(h)
with open(os.path.join(G, 'gvar_img_tab.c'), 'w') as f:
    f.write('/* v2.03: сгенерировано tools/gen_gvar_img.py — диапазоны переменных, живущих в образе данных Game.exe (re_ptr: образ раньше реестра). */\n')
    f.write('#ifndef RE_HOOK_BUILD\n#define RE_GVAR_PLAIN\n')
    for hh in sorted(set(hdr_of.values())): f.write('#include "%s"\n' % hh)
    f.write('typedef struct { uint32_t addr, size; } re_gvar_range_t;\nconst re_gvar_range_t re_gvar_ranges[] = {\n')
    for n, (t, a) in sorted(names.items(), key=lambda x: x[1][1]): f.write('  { 0x%08xu, (uint32_t)sizeof(%s) },   /* %s */\n' % (a, t, n))
    f.write('};\nconst uint32_t re_gvar_ranges_n = (uint32_t)(sizeof re_gvar_ranges / sizeof re_gvar_ranges[0]);\n#endif\n')
print('имён:', total, 'определений:', nd, 'строк-объявлений:', nw)
