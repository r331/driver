#!/usr/bin/env python3
"""Находит хукнутые функции Game.exe, которые заканчиваются `ret N` (stdcall), -> re/platform/win32/stdcall_tbl.h.
Использование: i686-w64-mingw32-objdump -d -M intel Game.exe > /tmp/game.dis; python3 tools/gen_stdcall.py"""
import re
lines=open('/tmp/game.dis').read().split('\n')
pos={}
for i,l in enumerate(lines):
    m=re.match(r'\s*([0-9a-f]{6,8}):\s',l)
    if m: pos[int(m.group(1),16)]=i
src=open('re/platform/win32/install.c').read()
hooks=re.findall(r're_hook\(0x([0-9a-fA-F]+),',src)
out={}
for a in hooks:
    a=int(a,16)
    if a not in pos: continue
    i=pos[a]
    for j in range(i,i+3000):
        l=lines[j]
        m=re.match(r'\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s*ret\s*(.*)',l)
        if m:
            if m.group(1).strip(): out[a]=int(m.group(1).strip(),16)
            break
        if j>i and re.match(r'\s*[0-9a-f]+:\s+55\s+push\s+ebp',l): break
with open('re/platform/win32/stdcall_tbl.h','w') as f:
    f.write('/* автогенерация tools/gen_stdcall.py: хукнутые функции Game.exe с `ret N` (stdcall) -> адрес, байт аргументов */\n')
    for a in sorted(out): f.write('{ 0x%08x, %d },\n'%(a,out[a]))
print(len(out))
