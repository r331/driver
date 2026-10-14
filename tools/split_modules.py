#!/usr/bin/env python3
"""Разбивает out/Game_decomp.c на src/<module>.c по docs/functions.csv. Без модуля -> src/_unsorted.c"""
import csv,re,os,collections
R=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
mod={r['address']:r['module'] for r in csv.DictReader(open(f"{R}/docs/functions.csv"))}
parts=re.split(r'^// (?=[0-9a-f]{8}\n)',open(f"{R}/out/Game_decomp.c").read(),flags=re.M)
buf=collections.defaultdict(list)
for p in parts[1:]:
    a=p[:8]; buf[mod.get(a) or '_unsorted'].append(f"// {p}")
os.makedirs(f"{R}/src",exist_ok=True)
for m,b in buf.items():
    fn=f"{R}/src/{'lib/crt' if m=='CRT' else m}.c"; os.makedirs(os.path.dirname(fn),exist_ok=True)
    open(fn,'w').write(f"/* Driver PC (1999) — модуль {m}, псевдо-C из Ghidra. {len(b)} функций */\n\n"+"".join(b))
    print(m,len(b))
