#!/usr/bin/env python3
"""Читает байты по виртуальному адресу из Game.exe: pedump.py <exe> <addr hex> <len> [hex|str|c]"""
import struct, sys
def rd(exe, va, n):
    d = open(exe, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    ns = struct.unpack_from('<H', d, pe + 6)[0]; osz = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<I', d, pe + 52)[0]
    for i in range(ns):
        nm, vs, sva, rs, ro = struct.unpack_from('<8sIIII', d, pe + 24 + osz + i * 40)
        if sva + base <= va < sva + base + max(vs, rs):
            o = ro + va - (sva + base)
            return d[o:o + n] if o + n <= ro + rs else d[o:ro + rs] + bytes(n - (ro + rs - o))
    raise SystemExit('нет секции')
if __name__ == '__main__':
    exe, va, n = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3]); mode = sys.argv[4] if len(sys.argv) > 4 else 'hex'
    b = rd(exe, va, n)
    if mode == 'str': print(repr(b.split(b'\0')[0]))
    elif mode == 'c': print(', '.join(str(x) for x in b))
    else: print(b.hex())
