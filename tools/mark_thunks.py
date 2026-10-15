#!/usr/bin/env python3
"""Помечает thunk_FUN_X (5-байтный jmp rel32) как ported, если его цель X уже ported.
Проверка по байтам Game.exe (e9 rel32 -> цель == X). Печатает счёт; запись только с --write."""
import csv,struct,sys,io
root=sys.argv[1]
exe=open(root+'/input/game/Program_Executable_Files/Game.exe','rb').read()
e_lfanew=struct.unpack_from('<I',exe,0x3c)[0]
nsec=struct.unpack_from('<H',exe,e_lfanew+6)[0]
optsz=struct.unpack_from('<H',exe,e_lfanew+20)[0]
base=struct.unpack_from('<I',exe,e_lfanew+24+28)[0]
secs=[]
off=e_lfanew+24+optsz
for i in range(nsec):
    vs,va,rs,ro=struct.unpack_from('<IIII',exe,off+8+i*40)
    secs.append((va,max(vs,rs),ro))
def rd(va,n):
    rva=va-base
    for s,sz,ro in secs:
        if s<=rva<s+sz: return exe[ro+rva-s:ro+rva-s+n]
raw=open(root+'/docs/functions.csv','rb').read().decode('utf-8')
crlf='\r\n' in raw
rows=list(csv.reader(io.StringIO(raw,newline='')))
hdr=rows[0]; st=hdr.index('status'); nm=hdr.index('ghidra_name')
status={r[0].lower():r[st] for r in rows[1:]}
n=0
for r in rows[1:]:
    if r[nm].startswith('thunk_FUN_') and r[st]=='todo':
        tgt=r[nm][10:].lower()
        if status.get(tgt)!='ported': continue
        a=int(r[0],16); b=rd(a,5)
        if b and b[0]==0xe9 and (a+5+struct.unpack('<i',b[1:])[0])&0xffffffff==int(tgt,16):
            r[st]='ported'; n+=1
print('thunks marked',n)
if '--write' in sys.argv:
    out=io.StringIO(newline='')
    csv.writer(out,lineterminator='\r\n' if crlf else '\n').writerows(rows)
    open(root+'/docs/functions.csv','wb').write(out.getvalue().encode('utf-8'))
