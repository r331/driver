#!/usr/bin/env python3
"""HD-пак текстур для native-порта Driver (v2.17).

Апскейлит 16-битные (ARGB1555, не-pair) страницы текстур из блока 0 файла уровня .lev
нейросетью (ESRGAN-совместимая модель, грузится через spandrel) и пишет
<out>/<уровень без .lev>/pNNN.png — RGBA, размер 256*scale (модели 4x → 1024×1024).

NNN — индекс страницы i в цикле P41_LoadTexPages: страницы в порядке файла, пара
8-битных страниц (флаг 0x10) считается за два индекса i и i+1. 8-битные страницы не
апскейлятся. Альфа = бит 0x8000 (nearest, без сглаживания). Цвет пикселей НЕ заменяется:
какое состояние бита прозрачно, решает функция альфа-теста при рисовании (в NY_01 у
страниц с деревьями/знаками бит 0x8000 стоит у тёмного фона, а у содержимого бит 0),
поэтому «dilation по биту» портила бы само изображение. Ореолы на краях снимает рендер
(dilation и мипмапы своего варианта текстуры).

v2.18 — 8-битные страницы (пара, флаг 0x10): --pal8. В игре такая страница — текстура
GR_TEXFMT_P_8 (в native-игре — поверхность PAL8 слота), цвет даёт палитра, выбранная во время
рисования (00426580: слот 0..49 таблицы палитр уровня). Одна страница рисуется разными палитрами,
поэтому файл — на пару: <out>/<уровень>/pNNN_cKKKK.png, KKKK — номер слота палитры (как в файле
уровня и в коде игры). Какие пары бывают: список LEVELS/<город>.d3d (по нему D3D-режим игры
заранее делает текстуру на каждую пару; страница без записи — палитра 1). Приоритет генерации —
площадь на экране из логов RE_TEXLOG (--texlog), затем палитра 1 (здания), затем остальные.
Альфа 255: у P_8 прозрачного индекса нет (--transparent-index N — сделать индекс N прозрачным).

Пак — производная данных игры: не коммитить, держать у себя. Подключение:
RE_TEXPACK=<out> или texpack = <out> в driver.cfg.

Примеры:
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --model 4x_foolhardy_Remacri.pth
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --verify   # сверка готового пака
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --texlog texlog.txt --budget 3600
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --list      # пары и что готово
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --verify

Зависимости: numpy, Pillow; для апскейла ещё torch и spandrel.
"""
import argparse
import os
import struct
import sys
import time

import numpy as np
from PIL import Image


def lev_pages(data):
    """[(i, offset, flags)] 16-битных страниц блока 0 и общее число индексов."""
    cnt = struct.unpack_from('<i', data, 0)[0]
    p, tex = 4, None
    for _ in range(cnt):
        kind, size = struct.unpack_from('<ii', data, p)
        if kind == 0:
            tex = p + 8
        p += 8 + size
    if tex is None:
        raise SystemExit('в .lev нет блока 0 (текстуры)')
    p = tex
    npal = struct.unpack_from('<h', data, p)[0]
    p += 2 + npal * 0x402                      # палитры (P27_LoadPalettes)
    count = struct.unpack_from('<i', data, p)[0]
    p += 4
    pages, i = [], 0
    while i < count:
        fl, _tex = struct.unpack_from('<HH', data, p)
        p += 4
        if fl & 0x10:                          # пара 8-битных: 0x10000 + 4 + 0x10000
            p += 0x20004
            i += 2
        else:
            pages.append((i, p, fl))
            p += 0x20000
            i += 1
    return pages, count


def lev_pal8(data):
    """палитры {слот: массив 256×3 uint8 (R,G,B)} и 8-битные страницы {индекс: массив 256×256 uint8} блока 0."""
    cnt = struct.unpack_from('<i', data, 0)[0]
    p, tex = 4, None
    for _ in range(cnt):
        kind, size = struct.unpack_from('<ii', data, p)
        if kind == 0:
            tex = p + 8
        p += 8 + size
    p = tex
    npal = struct.unpack_from('<h', data, p)[0]
    p += 2
    pals = {}
    for _ in range(npal):                      # P27_LoadPalettes: слот (int16) + 256 × (B,G,R,X)
        slot = struct.unpack_from('<h', data, p)[0]
        bgrx = np.frombuffer(data, np.uint8, 0x400, p + 2).reshape(256, 4)
        if 0 <= slot <= 0x31:
            pals[slot] = bgrx[:, [2, 1, 0]].copy()
        p += 0x402
    count = struct.unpack_from('<i', data, p)[0]
    p += 4
    pages, i = {}, 0
    while i < count:
        fl, _tex = struct.unpack_from('<HH', data, p)
        p += 4
        if fl & 0x10:                          # пара: страница i (0x10000), 4 байта, страница i+1 (0x10000)
            pages[i] = np.frombuffer(data, np.uint8, 0x10000, p).reshape(256, 256)
            pages[i + 1] = np.frombuffer(data, np.uint8, 0x10000, p + 0x10004).reshape(256, 256)
            p += 0x20004
            i += 2
        else:
            p += 0x20000
            i += 1
    return pals, pages


D3D_BY_PREFIX = [('ny', 'newyork.d3d'), ('miami', 'miami.d3d'), ('frisco', 'frisco.d3d'), ('la', 'la.d3d'),
                 ('nc', 'nc_01.d3d'), ('iview', 'iview.d3d'), ('train', 'train.d3d'), ('flat', 'flat.d3d')]


def find_d3d(lev):
    base = os.path.basename(lev).lower()
    d = os.path.dirname(os.path.abspath(lev))
    for pre, name in D3D_BY_PREFIX:
        if base.startswith(pre):
            for f in os.listdir(d):
                if f.lower() == name:
                    return os.path.join(d, f)
    return None


def read_d3d(path):
    """LEVELS/<город>.d3d (P126_ReadMapPals): {страница: [слоты палитр]}."""
    d = open(path, 'rb').read()
    n = struct.unpack_from('<i', d, 0)[0]
    p, out = 4, {}
    for _ in range(n):
        a, c = struct.unpack_from('<ii', d, p)
        out[a] = list(struct.unpack_from('<%di' % c, d, p + 8))
        p += 8 + 4 * c
    return out


def pal8_pairs(pals, pages, d3d):
    """все пары (страница, палитра), которые может нарисовать игра: список .d3d, без записи — палитра 1 (P40_DownloadPalette)."""
    out = []
    for i in sorted(pages):
        lst = d3d.get(i, [1]) if d3d is not None else [1]
        for k in lst:
            if k in pals and (i, k) not in out:
                out.append((i, k))
    return out


def read_texlog(files):
    """RE_TEXLOG: строки «страница палитра треугольники площадь» → {(страница, палитра): площадь}."""
    area = {}
    for fn in files or []:
        for ln in open(fn):
            if ln.startswith('#') or not ln.strip():
                continue
            s, k, _n, a = ln.split()[:4]
            if int(k) >= 0:
                area[(int(s), int(k))] = area.get((int(s), int(k)), 0.0) + float(a)
    return area


def pal8_rgba(pals, pages, i, k, tidx=None):
    rgb = pals[k][pages[i]]                    # 256×256×3 uint8
    a = np.ones((256, 256), bool) if tidx is None else pages[i] != tidx
    return rgb, a


def verify8(pals, pages, pairs, outdir, tidx=None):
    """каждый pNNN_cKKKK.png → 256 (среднее блока), сверка по всем пикселям: со своей парой ошибка <= 24 и альфа <= 2%;
    своя страница — лучшая среди всех 8-битных страниц в той же палитре; своя палитра — лучшая среди палитр страницы."""
    bad = n = 0
    pal_of = {}
    for i, k in pairs:
        pal_of.setdefault(i, []).append(k)
    for f in sorted(os.listdir(outdir)):
        if not (len(f) == 14 and f.startswith('p') and f[4:6] == '_c' and f.endswith('.png')):   # pNNN_cKKKK.png (без .tmp)
            continue
        i, k = int(f[1:4]), int(f[6:10])
        if i not in pages or k not in pals:
            print(f'{f}: нет такой страницы/палитры — НЕСОВПАДЕНИЕ'); bad += 1; n += 1
            continue
        im = np.asarray(Image.open(os.path.join(outdir, f)).convert('RGBA')).astype(np.float32)
        s = im.shape[0] // 256
        sm = im.reshape(256, s, 256, s, 4).mean((1, 3))
        def err(j, q):
            return float(np.abs(sm[..., :3] - pals[q][pages[j]].astype(np.float32)).mean())
        own = err(i, k)
        best_p = min(pages, key=lambda j: err(j, k))
        best_k = min(set(pal_of.get(i, []) + [k]), key=lambda q: err(i, q))
        am = float(((sm[..., 3] >= 128) != pal8_rgba(pals, pages, i, k, tidx)[1]).mean())
        ok = own <= 24.0 and am <= 0.02 and err(best_p, k) >= own and err(i, best_k) >= own
        bad += not ok
        n += 1
        print(f'{f}: ошибка со своей парой {own:.2f}, лучшая страница {best_p}, лучшая палитра {best_k}, '
              f'альфа не совпала {am * 100:.2f}% — {"OK" if ok else "НЕСОВПАДЕНИЕ"}')
    print(f'проверено {n}, несовпадений {bad}')
    return 1 if bad else 0


def page_rgba(data, off):
    w = np.frombuffer(data, '<u2', 65536, off).reshape(256, 256).astype(np.uint32)
    r, g, b = (w >> 10) & 31, (w >> 5) & 31, w & 31
    rgb = np.dstack([r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2]).astype(np.float32) / 255
    return rgb, (w & 0x8000) != 0


def verify(data, pages, outdir):
    """Уменьшает каждый pNNN.png до 256 и сравнивает со всеми страницами: свой индекс должен быть лучшим."""
    src = {i: page_rgba(data, o) for i, o, _ in pages}
    bad = n = 0
    for f in sorted(os.listdir(outdir)):
        if not (len(f) == 8 and f.startswith('p') and f[1:4].isdigit() and f.endswith('.png')):   # pNNN.png (v2.18: не pNNN_cKKKK)
            continue
        k = int(f[1:-4])
        im = np.asarray(Image.open(os.path.join(outdir, f)).convert('RGBA')).astype(np.float32) / 255
        s = im.shape[0] // 256
        sm = im.reshape(256, s, 256, s, 4).mean((1, 3))
        errs = {}
        for j, (rgb, a) in src.items():   # по всем пикселям: и с битом 0x8000, и без
            errs[j] = float(np.abs(sm[..., :3] - rgb).mean() * 255)
        best = min(errs, key=errs.get)
        am = float(((sm[..., 3] >= 0.5) != src[k][1]).mean()) if k in src else -1.0
        ok = best == k and am <= 0.02 and errs.get(k, 1e9) <= 24.0
        bad += not ok
        n += 1
        print(f'{f}: ошибка со своей страницей {errs.get(k, -1):.2f}, лучшая {best} ({errs[best]:.2f}), '
              f'альфа не совпала {am * 100:.2f}% — {"OK" if ok else "НЕСОВПАДЕНИЕ"}')
    print(f'проверено {n}, несовпадений {bad}')
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    ap.add_argument('lev', help='путь к файлу уровня .lev (например Levels/NY_01.lev)')
    ap.add_argument('out', help='каталог пака (внутри создаётся подкаталог уровня)')
    ap.add_argument('--model', default='4x_foolhardy_Remacri.pth', help='веса модели апскейла (.pth/.safetensors, spandrel)')
    ap.add_argument('--budget', type=float, default=0, help='лимит времени в секундах (0 — без лимита); готовые файлы пропускаются')
    ap.add_argument('--threads', type=int, default=0, help='потоки torch (0 — по умолчанию)')
    ap.add_argument('--verify', action='store_true', help='только сверить готовые PNG со страницами .lev')
    ap.add_argument('--pal8', action='store_true', help='8-битные страницы: файлы pNNN_cKKKK.png на пару (страница, слот палитры)')
    ap.add_argument('--d3d', help='список пар LEVELS/<город>.d3d (по умолчанию — по имени уровня рядом с .lev)')
    ap.add_argument('--texlog', action='append', help='лог RE_TEXLOG (можно несколько): порядок генерации по площади на экране')
    ap.add_argument('--pairs', help='только эти пары: "16:1,122:1"')
    ap.add_argument('--transparent-index', type=int, default=None, help='индекс палитры, который сделать прозрачным (у игры нет)')
    ap.add_argument('--list', action='store_true', help='--pal8: вывести пары по порядку генерации и что уже готово')
    args = ap.parse_args()

    data = open(args.lev, 'rb').read()
    if args.pal8:
        return main_pal8(args, data)
    pages, count = lev_pages(data)
    level = os.path.splitext(os.path.basename(args.lev))[0]
    outdir = os.path.join(args.out, level)
    print(f'{level}: индексов {count}, 16-битных страниц {len(pages)}')
    if args.verify:
        return verify(data, pages, outdir)

    import torch
    import spandrel
    if args.threads:
        torch.set_num_threads(args.threads)
    os.makedirs(outdir, exist_ok=True)
    model = spandrel.ModelLoader().load_from_file(args.model).eval()
    t0 = time.time()
    for idx, off, _fl in pages:
        fn = os.path.join(outdir, f'p{idx:03d}.png')
        if os.path.exists(fn):
            continue
        if args.budget and time.time() - t0 > args.budget:
            print('лимит времени — остановка')
            break
        rgb, a = page_rgba(data, off)
        x = torch.from_numpy(np.ascontiguousarray(rgb)).permute(2, 0, 1)[None]
        with torch.no_grad():
            y = model(x)[0].permute(1, 2, 0).clamp(0, 1).numpy()
        y = (y * 255 + .5).astype(np.uint8)
        s = y.shape[0] // 256
        al = np.repeat(np.repeat(a, s, 0), s, 1).astype(np.uint8) * 255
        Image.fromarray(np.dstack([y, al]), 'RGBA').save(fn)
        print(idx, flush=True)
    left = [q for q in pages if not os.path.exists(os.path.join(outdir, f'p{q[0]:03d}.png'))]
    print(f'готово {len(pages) - len(left)} из {len(pages)}')
    return 0


def main_pal8(args, data):
    pals, pages = lev_pal8(data)
    level = os.path.splitext(os.path.basename(args.lev))[0]
    outdir = os.path.join(args.out, level)
    d3dp = args.d3d or find_d3d(args.lev)
    d3d = read_d3d(d3dp) if d3dp else None
    pairs = pal8_pairs(pals, pages, d3d)
    if args.pairs:
        want = [tuple(int(v) for v in q.split(':')) for q in args.pairs.split(',')]
        pairs = [q for q in want if q[0] in pages and q[1] in pals]
    area = read_texlog(args.texlog)
    for q in area:                             # пара из лога, которой нет в списке, тоже нужна
        if q[0] in pages and q[1] in pals and q not in pairs and not args.pairs:
            pairs.append(q)
    order = sorted(pairs, key=lambda q: (-area.get(q, 0.0), q[1] != 1, q))   # затем палитра 1 (здания), остальные
    print(f'{level}: 8-битных страниц {len(pages)}, палитр {len(pals)}, пар (страница, палитра) {len(pairs)}'
          f' (список {os.path.basename(d3dp) if d3dp else "нет — палитра 1"}), на экране в логах {sum(1 for q in pairs if area.get(q))}')
    fn = lambda q: os.path.join(outdir, f'p{q[0]:03d}_c{q[1]:04d}.png')
    if args.list:
        for q in order:
            print(f'p{q[0]:03d}_c{q[1]:04d} площадь {area.get(q, 0):.0f} {"готово" if os.path.exists(fn(q)) else "-"}')
        print(f'готово {sum(os.path.exists(fn(q)) for q in pairs)} из {len(pairs)}')
        return 0
    if args.verify:
        return verify8(pals, pages, pairs, outdir, args.transparent_index)
    import torch
    import spandrel
    if args.threads:
        torch.set_num_threads(args.threads)
    os.makedirs(outdir, exist_ok=True)
    model = spandrel.ModelLoader().load_from_file(args.model).eval()
    t0 = time.time()
    for q in order:
        if os.path.exists(fn(q)):
            continue
        if args.budget and time.time() - t0 > args.budget:
            print('лимит времени — остановка')
            break
        rgb, a = pal8_rgba(pals, pages, q[0], q[1], args.transparent_index)
        x = torch.from_numpy(np.ascontiguousarray(rgb.astype(np.float32) / 255)).permute(2, 0, 1)[None]
        with torch.no_grad():
            y = model(x)[0].permute(1, 2, 0).clamp(0, 1).numpy()
        y = (y * 255 + .5).astype(np.uint8)
        s = y.shape[0] // 256
        al = np.repeat(np.repeat(a, s, 0), s, 1).astype(np.uint8) * 255     # альфа — nearest
        tmp = fn(q) + '.tmp.png'
        Image.fromarray(np.dstack([y, al]), 'RGBA').save(tmp)
        os.replace(tmp, fn(q))                 # без недописанных файлов при остановке
        print(f'p{q[0]:03d}_c{q[1]:04d} ({time.time() - t0:.0f} с)', flush=True)
    left = [q for q in pairs if not os.path.exists(fn(q))]
    print(f'готово {len(pairs) - len(left)} из {len(pairs)}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
