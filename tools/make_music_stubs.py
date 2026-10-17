#!/usr/bin/env python3
"""v2.22: файлы-заглушки CD-музыки для проверки эмуляции CD-audio native-сборки Driver.

НЕ игровые данные: тишина или синтетический тон. Настоящие дорожки снимаются с диска самим владельцем
(см. re/README.md, «CD-музыка»).

  python3 tools/make_music_stubs.py [каталог=Music] [--tone] [--seconds 8] [--first 2] [--last 10]
                                    [--cue]   # вместо TrackNN.wav — один образ music.bin + music.cue (дорожка 1 — данные)
                                    [--rate 44100] [--mono]

Тон дорожки N: 220 Гц * 2^((N-2)/12) (та же формула, что у RE_MUSIC_STUB=tone), амплитуда ~ -26 dBFS,
короткая пауза в начале — по слуху и по WAV (RE_WAV_OUT) видно, какая дорожка играет и где она зациклилась.
"""
import argparse
import math
import os
import struct


def pcm(track, seconds, rate, ch, tone):
    n = int(seconds * rate)
    out = bytearray()
    f = 220.0 * 2 ** ((track - 2) / 12.0)
    gap = int(0.25 * rate)
    for i in range(n):
        v = 0
        if tone and i >= gap:
            v = int(1600 * math.sin(2 * math.pi * f * i / rate))
        s = struct.pack('<h', v)
        out += s * ch
    return bytes(out)


def wav(path, data, rate, ch):
    with open(path, 'wb') as fo:
        fo.write(b'RIFF' + struct.pack('<I', 36 + len(data)) + b'WAVE')
        fo.write(b'fmt ' + struct.pack('<IHHIIHH', 16, 1, ch, rate, rate * ch * 2, ch * 2, 16))
        fo.write(b'data' + struct.pack('<I', len(data)) + data)


def msf(sectors):
    return '%02d:%02d:%02d' % (sectors // (75 * 60), (sectors // 75) % 60, sectors % 75)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('dir', nargs='?', default='Music')
    ap.add_argument('--tone', action='store_true', help='тихий тон вместо тишины')
    ap.add_argument('--seconds', type=float, default=8.0)
    ap.add_argument('--first', type=int, default=2)
    ap.add_argument('--last', type=int, default=10)
    ap.add_argument('--cue', action='store_true', help='образ music.bin/music.cue вместо TrackNN.wav')
    ap.add_argument('--rate', type=int, default=44100, help='частота WAV (для --cue всегда 44100)')
    ap.add_argument('--mono', action='store_true')
    a = ap.parse_args()
    os.makedirs(a.dir, exist_ok=True)
    if not a.cue:
        ch = 1 if a.mono else 2
        for t in range(a.first, a.last + 1):
            p = os.path.join(a.dir, 'Track%02d.wav' % t)
            wav(p, pcm(t, a.seconds, a.rate, ch, a.tone), a.rate, ch)
            print(p)
        return
    # образ: дорожка 1 — «данные» (нули, 2 с), дальше звуковые дорожки a.first..a.last
    lines = ['REM заглушка tools/make_music_stubs.py — не данные игры', 'FILE "music.bin" BINARY',
             '  TRACK 01 MODE1/2352', '    INDEX 01 00:00:00']
    pos = 0
    with open(os.path.join(a.dir, 'music.bin'), 'wb') as fo:
        fo.write(b'\0' * 2352 * 150)
        pos = 150
        for t in range(max(2, a.first), a.last + 1):
            d = pcm(t, a.seconds, 44100, 2, a.tone)
            d += b'\0' * ((-len(d)) % 2352)
            lines += ['  TRACK %02d AUDIO' % t, '    INDEX 00 %s' % msf(pos), '    INDEX 01 %s' % msf(pos)]
            fo.write(d)
            pos += len(d) // 2352
    with open(os.path.join(a.dir, 'music.cue'), 'w') as fo:
        fo.write('\n'.join(lines) + '\n')
    print(os.path.join(a.dir, 'music.cue'))


if __name__ == '__main__':
    main()
