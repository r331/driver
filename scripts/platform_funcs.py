import re,csv,collections
src=open('out/Game_decomp.c',errors='replace').read()
parts=re.split(r'^// ([0-9a-f]{8})\n',src,flags=re.M)
fm={r['address']:r for r in csv.DictReader(open('docs/functions.csv'))}
layers={
'system':r'\b(CreateFile[AW]|ReadFile|WriteFile|CloseHandle|SetFilePointer|GetFileSize|FindFirstFile[AW]|FindNextFile[AW]|FindClose|GetTickCount|QueryPerformance\w+|Sleep|GetModuleFileName[AW]|GetCurrentDirectory[AW]|SetCurrentDirectory[AW]|GetLastError|GetSystemTime|GetLocalTime|ExitProcess|OutputDebugString[AW]|GetCommandLine[AW]|MessageBox[AW]|GetDiskFreeSpace\w*|GetDriveType\w*|GetVolumeInformation\w*|CreateMutex\w*|CreateEvent\w*|WaitForSingleObject|timeGetTime|timeSetEvent|timeKillEvent|timeBeginPeriod|timeEndPeriod|GetVersion\w*|GetProcAddress|LoadLibrary\w*|HeapAlloc|HeapFree|VirtualAlloc|VirtualFree|GlobalMemoryStatus|DeleteFile[AW]|CreateDirectory[AW]|GetFileAttributes[AW]|SetFileAttributes[AW]|GetStartupInfo\w*|GetEnvironmentVariable\w*|lstr\w+|wsprintf[AW])\b',
'window_input':r'\b(CreateWindowEx[AW]|RegisterClass\w*|DefWindowProc[AW]|GetMessage[AW]|PeekMessage[AW]|DispatchMessage[AW]|TranslateMessage|PostMessage[AW]|PostQuitMessage|ShowWindow|UpdateWindow|SetWindowPos|GetClientRect|GetWindowRect|SetCursor|ShowCursor|LoadCursor[AW]|LoadIcon[AW]|GetAsyncKeyState|GetKeyState|DirectInputCreate\w*|ClipCursor|SetCapture|ReleaseCapture|DestroyWindow|SetFocus|GetActiveWindow|SetForegroundWindow|GetSystemMetrics|AdjustWindowRect\w*|SetWindowLong[AW]|GetWindowLong[AW]|SetWindowText[AW]|joyGetPos\w*|joyGetDevCaps\w*|joyGetNumDevs|GetCursorPos|SetCursorPos|ScreenToClient)\b',
'cdaudio':r'\b(mci\w+|auxGet\w+|auxSet\w+|waveOut\w+)\b',
'sound':r'\b(DirectSoundCreate\w*)\b',
'render':r'\b(DirectDrawCreate\w*|CoCreateInstance|CreateCompatibleDC|GetDC|ReleaseDC|BitBlt|CreateDIBSection|SelectObject|DeleteObject|DeleteDC|TextOut[AW]|GetDeviceCaps|SetDIBits|StretchBlt|SetPixel|CreateFont\w*|PALETTEENTRY|DirectDrawEnumerate\w*)\b'}
rows=[]
for i in range(1,len(parts),2):
    a,b=parts[i],parts[i+1]
    imps=collections.OrderedDict()
    lay=[]
    for l,rx in layers.items():
        m=set(re.findall(rx,b))
        if m:
            lay.append(l); [imps.setdefault(x) for x in sorted(m)]
    # COM vtable: (**(code **)(*piVar + 0xNN))
    com=re.findall(r'\(\*\*?\(code \*\*\)\(\*\w+ \+ (0x[0-9a-f]+)\)\)',b)
    if com and not lay:
        t='render'
        if re.search(r'DirectSound|DSBUF|dsound',b,re.I): t='sound'
        elif re.search(r'DirectInput|DIDEV|dinput',b,re.I): t='window_input'
        lay=[t]; imps.setdefault('COM_vtable')
    if not lay: continue
    L=lay[0]
    name=fm.get(a,{}).get('name') or fm.get(a,{}).get('ghidra_name','')
    rows.append([a,name,L,';'.join(imps),'',fm.get(a,{}).get('status','todo')])
# callers
callee=collections.Counter()
for r in rows: pass
w=csv.writer(open('docs/platform_funcs.csv','w',newline=''))
w.writerow('address,name,layer,imports,callers,status'.split(','))
rows.sort(key=lambda r:(r[2],r[0]))
for r in rows: w.writerow(r)
print(len(rows),collections.Counter(r[2] for r in rows))
