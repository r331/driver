#!/usr/bin/env python3
"""Генерирует re/game/p84_data.h: байтовые таблицы отрисовки записей модели 0x550cc4 (аргумент обработчика) и 0x550c8c (нужен ли свет), по 56 штук.
Запуск из корня проекта: python3 tools/gen_p84_data.py"""
import struct
exe = open('input/game/Program_Executable_Files/Game.exe', 'rb').read()
pe = struct.unpack_from('<I', exe, 0x3c)[0]
ns = struct.unpack_from('<H', exe, pe + 6)[0]; so = struct.unpack_from('<H', exe, pe + 20)[0]
base = struct.unpack_from('<I', exe, pe + 52)[0]
def rd(va, n):
    rva = va - base
    for i in range(ns):
        o = pe + 24 + so + i * 40
        vs, vr, rs, rp = struct.unpack_from('<IIII', exe, o + 8)
        if vr <= rva < vr + max(vs, rs): return exe[rp + rva - vr: rp + rva - vr + n]
a = rd(0x550cc4, 56); l = rd(0x550c8c, 56)
open('re/game/p84_data.h', 'w').write('/* Сгенерировано tools/gen_p84_data.py из Game.exe — не править вручную. */\n'
  'static const uint8_t P84_ArgInit[56] = {' + ','.join(map(str, a)) + '};\n'
  'static const uint8_t P84_LitInit[56] = {' + ','.join(map(str, l)) + '};\n')
