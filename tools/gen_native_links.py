#!/usr/bin/env python3
"""Генерирует re/platform/native/links.c: для каждого вызова из game/unported.h, чей адрес уже перенесён (re_hook в win32/install.c),
в native-сборке строгое определение, вызывающее перенесённую функцию (слабая заглушка из stubs.c перекрывается).
Запуск: python3 tools/gen_native_links.py re [--skip имя,имя]"""
import re,sys,os,subprocess,tempfile
root=sys.argv[1]
skip=set()
if '--skip' in sys.argv: skip=set(sys.argv[sys.argv.index('--skip')+1].split(','))
inst=open(root+'/platform/win32/install.c',encoding='utf-8').read()
hooks={}
for m in re.finditer(r're_hook\(\s*0x([0-9a-fA-F]+)\s*,\s*\(void\*\)\s*(\w+)',inst): hooks[int(m.group(1),16)]=m.group(2)
incs=re.findall(r'#include "\.\./\.\./game/([\w.]+)"',inst)
un=open(root+'/game/unported.h',encoding='utf-8').read()
body=un[un.index('#define UNPORTED_LIST'):un.index('\n\n',un.index('#define UNPORTED_LIST'))]
rows=[]
for line in body.split('\\\n'):
    line=line.strip()
    m=re.match(r'V\((\w+),\s*0x([0-9a-fA-F]+),\s*(\(.*?\)),\s*(\(.*?\))\)\s*$',line)
    if m: rows.append(('V','void',m.group(1),int(m.group(2),16),m.group(3),m.group(4))); continue
    m=re.match(r'R\(([\w\s\*]+?),\s*(\w+),\s*0x([0-9a-fA-F]+),\s*(\(.*?\)),\s*(\(.*?\))\)\s*$',line)
    if m: rows.append(('R',m.group(1),m.group(2),int(m.group(3),16),m.group(4),m.group(5)))
out=['/* Автогенерация: tools/gen_native_links.py. Ещё не перенесённые вызовы в native уходят в слабые заглушки stubs.c; здесь — перенесённые. */',
     '#include "../../game/unported.h"']
out+=['#include "../../game/%s"'%i for i in incs]
def entry(k,rt,name,params,args,fn):
    if k=='V': return 'void %s %s { %s%s; }'%(name,params,'',fn+args)
    return '%s %s %s { return (%s)%s%s; }'%(rt,name,params,rt,fn,args)
hdr='\n'.join(out)
def ok(line):
    with tempfile.NamedTemporaryFile('w',suffix='.c',dir=root+'/platform/native',delete=False) as f:
        f.write(hdr+'\n'+line+'\n'); path=f.name
    r=subprocess.run(['gcc','-fsyntax-only','-w','-Werror=int-conversion','-Werror=incompatible-pointer-types','-I',root+'/game',path],capture_output=True)
    os.unlink(path); return r.returncode==0
n=0; bad=[]
for k,rt,name,addr,params,args in rows:
    fn=hooks.get(addr)
    if not fn or fn==name or name in skip: continue
    line=entry(k,rt,name,params,args,fn)
    if '--nocheck' in sys.argv or ok(line): out.append(line); n+=1
    else: bad.append(name)
open(root+'/platform/native/links.c','w',encoding='utf-8').write('\n'.join(out)+'\n')
print('links:',n,'пропущено (типы не сходятся):',len(bad))
