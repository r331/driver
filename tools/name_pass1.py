#!/usr/bin/env python3
"""Pass 1: модули по assert-путям + CRT, имена из debug-строк, сверка с REDRIVER2.
Вход: out/functions.csv, out/string_xrefs.tsv, tools/redriver2_funcs.txt
Выход: docs/functions.csv"""
import csv,re,os,collections
R=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
funcs=[r for r in csv.DictReader(open(f"{R}/out/functions.csv"))]
for f in funcs: f['a']=int(f['address'],16)
funcs.sort(key=lambda f:f['a'])
rd2={l.strip() for l in open(f"{R}/tools/redriver2_funcs.txt") if l.strip()}
rd2low={n.lower():n for n in rd2}
xr=collections.defaultdict(list)
for r in csv.DictReader(open(f"{R}/out/string_xrefs.tsv"),delimiter='\t'):
    xr[r['func_addr']].append(r['string'])
CRT=set("""dbgheap dbgrpt sprintf fopen _sftbuf _open vsprintf stdenvp sscanf ioinit input fscanf fprintf fgets a_env _getbuf _flsbuf _file ungetc strupr stream stdargv osfinfo mbtowc ftell fseek fgetc fclose chsize _freebuf _filbuf output crt0 crt0dat crt0msg winxfltr""".split())
BAD=set("ERROR FATAL FAILED Error Dir File DAMAGE Expression Warning WARNING Program Line Module Note GAMEMAIN Object Data".split())
mod={};name={};src={}
for f in funcs:
    k=f['address']
    for s in xr.get(k,[]):
        m=re.match(r'D:\\Driver\\Game\\(.+)\.c$',s,re.I)
        if m: mod[k]=m.group(1).replace('\\','/'); src[k]='assert'
        elif re.fullmatch(r'[\w]+\.c',s) and s[:-2] in CRT: mod.setdefault(k,'CRT'); src.setdefault(k,'crt')
        m=re.match(r'(?:(\w+)\.c::)?([A-Z][A-Za-z0-9_]{3,}): ',s) or re.match(r'FAILED: ([A-Z][A-Za-z0-9_]{3,})',s)
        if m:
            n=m.group(m.lastindex)
            if n not in BAD and not n.isupper(): name.setdefault(k,n)
            if m.lastindex==2 and m.group(1): mod.setdefault(k,m.group(1))
# propagate modules between two tagged functions of the same module (MSVC keeps .obj contiguous)
tagged=[i for i,f in enumerate(funcs) if f['address'] in mod]
for a,b in zip(tagged,tagged[1:]):
    ma,mb=mod[funcs[a]['address']],mod[funcs[b]['address']]
    if ma==mb and b-a<=200:
        for i in range(a+1,b):
            k=funcs[i]['address']
            if k not in mod: mod[k]=ma; src[k]='range'
out=open(f"{R}/docs/functions.csv","w",newline='');w=csv.writer(out)
w.writerow(['address','ghidra_name','name','name_source','module','module_source','redriver2','size','status'])
st=collections.Counter()
for f in funcs:
    k=f['address'];n=name.get(k,'')
    rd=rd2low.get(n.lower(),'') if n else ''
    if not n and not f['name'].startswith(('FUN_','thunk_FUN_')) : n=f['name']; ns='ghidra'
    else: ns='debug_string' if n else ''
    if n and not rd: rd=rd2low.get(n.lower(),'')
    w.writerow([k,f['name'],n,ns,mod.get(k,''),src.get(k,''),rd,f['size'],'named' if n else 'todo'])
    st['named' if n else 'todo']+=1; st['mod:'+mod.get(k,'?')]+=1; st['rd2']+= bool(rd); st['dbgname']+= ns=='debug_string'
print(dict(st))
