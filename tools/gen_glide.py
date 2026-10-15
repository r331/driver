import re,struct,sys
exe=open('input/game/Program_Executable_Files/Game.exe','rb').read()
pe=struct.unpack_from('<I',exe,0x3c)[0]
nsec=struct.unpack_from('<H',exe,pe+6)[0]; opt=struct.unpack_from('<H',exe,pe+20)[0]
base=struct.unpack_from('<I',exe,pe+24+28)[0]
secs=[]
o=pe+24+opt
for i in range(nsec):
    vs,va,rs,ro=struct.unpack_from('<IIII',exe,o+8+i*40)
    secs.append((va,vs,ro,rs))
def rd(va):
    rva=va-base
    for a,vs,ro,rs in secs:
        if a<=rva<a+max(vs,rs):
            off=ro+rva-a; e=exe.index(b'\0',off); return exe[off:e].decode()
t=open('out/Game_decomp.c',errors='replace').read()
t=t[t.index('// 00424c40'):]; t=t[:t.index('\n// ',5)]
ent=[]
for m in re.finditer(r'(?:_?(DAT_[0-9a-f]{8})) = GetProcAddress\(DAT_00b1c0e8,s_\w*?_([0-9a-f]{8})\);',t):
    ent.append((int(m.group(1)[4:],16),rd(int(m.group(2),16))))
print(len(ent),file=sys.stderr)
zeros=[int(x,16) for x in re.findall(r'_?DAT_([0-9a-f]{8}) = 0;',t)]
out=['/* сгенерировано tools/gen_glide.py из Game.exe: имя экспорта glide2x.dll → адрес указателя */','static const struct { const char *name; uint32_t addr; } P33_GlideTab[] = {']
for a,n in ent: out.append('  { "%s", 0x%08x },'%(n,a))
out.append('};')
out.append('static const uint32_t P33_GlideZero[] __attribute__((unused)) = { %s };'%', '.join('0x%08x'%z for z in zeros))
open('/tmp/glide_tab.inc','w').write('\n'.join(out)+'\n')
