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

Пак — производная данных игры: не коммитить, держать у себя. Подключение:
RE_TEXPACK=<out> или texpack = <out> в driver.cfg.

Примеры:
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --model 4x_foolhardy_Remacri.pth
  python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --verify   # сверка готового пака

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
        if not (f.startswith('p') and f.endswith('.png')):
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
    args = ap.parse_args()

    data = open(args.lev, 'rb').read()
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


if __name__ == '__main__':
    sys.exit(main())
