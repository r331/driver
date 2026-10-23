#!/usr/bin/env python3
"""HUD-вариант HD-пака (v2.36): перерисованные цифры часов миссии.

Часы миссии (P96_ClockText, Game.exe 004fba23) печатают «MM:SS» шрифтом 1 и «.cc» шрифтом 0. В Майами
(miami_01) оба шрифта лежат на 8-битной странице 51, палитра 24 (заголовок шрифта +8; ячейки глифов —
RE_FONTDUMP=1 в native). Скрипт берёт полосу из десяти цифр 0..9 (белые на чёрном, перерисованы нейросетью,
лежит в паке: hud_hd/src/digits.png), режет её на связные компоненты, масштабирует все цифры ОДНИМ
коэффициентом (общая высота и базовая линия — таймер не «прыгает») и вписывает по центру ячеек шрифта
на HD-странице (4×, 1024×1024); по ширине — до STRETCH× (оригинал приземистее), один коэффициент на шрифт. Двоеточие и точка — круги той же толщины, что и в оригинале. Остальные
глифы страницы остаются из основного пака (или nearest-апскейл оригинала, если в паке страницы нет).

Цвет: 8-битная страница рисуется палитрой; покрытие глифа c (0..1) → индекс c·255 → цвет палитры
(линейная интерполяция). Пишутся все пары (страница, палитра) из LEVELS/miami.d3d (24 и 3).

В ячейке остаётся чёрная рамка ≥ 3 HD-пикселей: билинейная выборка и мипмапы не захватывают соседние
глифы атласа (UV ячеек не меняются — те же u, v, w, h игры).

Пример (каталог пака = клон r331/driver-texpack):
  python3 tools/texpack_hud.py Data_Files/Levels/miami_01.lev texpack/hud_hd/src/digits.png texpack \\
      --out texpack/hud_hd
Включение в игре: <пак>/hud.txt со словом hud_hd (или RE_TEXPACK_HUD=hud_hd); выкл. — RE_TEXPACK_HUD=0.
Зависимости: numpy, Pillow, scipy (ndimage.label).
"""
import argparse
import os
import sys

import numpy as np
from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import texpack  # noqa: E402

# Ячейки глифов (u, v, w, h) на странице 256×256 — RE_FONTDUMP=1, miami_01 (шрифты строятся из значков F1_/F2_).
LEVELS = {
    'miami_01': {
        'page': 51,
        'big': {'0': (91, 16), '1': (169, 62), '2': (0, 46), '3': (164, 115), '4': (130, 16),
                '5': (16, 175), '6': (26, 122), '7': (215, 191), '8': (39, 46), '9': (78, 92)},
        'big_wh': (38, 52), 'colon': (203, 122, 16, 52),
        'small': {'0': (241, 99, 13), '1': (110, 69, 12), '2': (40, 228, 13), '3': (150, 138, 13),
                  '4': (117, 92, 13), '5': (63, 99, 13), '6': (48, 99, 14), '7': (0, 191, 13),
                  '8': (117, 161, 14), '9': (136, 138, 13)},
        'small_h': 22, 'dot': (211, 16, 6, 22),
        # раскладка в ячейке (пиксели страницы 256): верх и базовая линия цифр, круги «:» и «.»
        'big_top': 5.0, 'big_base': 44.0, 'colon_d': 14.5, 'colon_cy': (15.5, 33.5),
        'small_top': 6.0, 'small_base': 19.0, 'dot_d': 5.0, 'dot_cy': 16.5,
    },
}
S = 4          # масштаб HD-страницы (1024 / 256)
MARGIN = 3     # чёрная рамка внутри ячейки, HD-пиксели
STRETCH = 1.2  # во сколько раз шире пропорций полосы можно сделать цифры (если влезают)


def digits_from_strip(path, bold=0):
    """10 компонент (слева направо) → [(маска float 0..1 полной высоты строки, x0, x1)], строка y0..y1."""
    from scipy import ndimage
    a = np.asarray(Image.open(path).convert('L')).astype(np.float32) / 255.0
    lab, n = ndimage.label(a > 0.4)
    objs = ndimage.find_objects(lab)
    big = sorted([(s[1].start, s[1].stop, s[0].start, s[0].stop, i + 1) for i, s in enumerate(objs)
                  if (lab[s] == i + 1).sum() > 0.002 * a.size])
    if len(big) != 10:
        raise SystemExit(f'{path}: найдено {len(big)} крупных компонент, нужно 10 (цифры 0..9 без касаний)')
    y0 = min(b[2] for b in big); y1 = max(b[3] for b in big)
    out = []
    for x0, x1, _a, _b, k in big:
        pad = 4
        xa, xb = max(0, x0 - pad), min(a.shape[1], x1 + pad)
        region = lab[y0:y1, xa:xb]
        # своя компонента + сглаженный край 3 пикселя (края соседних цифр сюда не попадают)
        own = ndimage.binary_dilation(region == k, iterations=3) & ((region == 0) | (region == k))
        m = np.where(own, a[y0:y1, xa:xb], 0.0)
        if bold > 0:   # утолщение штриха: серая дилатация круглым ядром радиуса bold (оригинал жирнее полосы)
            m = np.pad(m, bold)
            yy, xx = np.mgrid[-bold:bold + 1, -bold:bold + 1]
            m = ndimage.grey_dilation(m, footprint=(xx * xx + yy * yy) <= bold * bold)
        cols = np.where((m > 0.02).any(0))[0]
        out.append(m[:, cols[0]:cols[-1] + 1])
    return out, y1 - y0 + 2 * bold


def scales(glyphs, widths, top, base, row_h):
    """коэффициенты ky (высота строки → base−top) и kx: шире на STRETCH (оригинал — приземистый, почти квадратный),
    но не больше, чем позволяет самая узкая по запасу ячейка (рамка MARGIN) — один kx на весь шрифт (моноширинность)."""
    ky = (base - top) * S / row_h
    fit = min((w * S - 2 * MARGIN - 1) / g.shape[1] for g, w in zip(glyphs, widths))
    return min(ky * STRETCH, fit), ky


def place(glyph, cell_w, cell_h, top, kx, ky):
    """HD-ячейка cell_w×cell_h (пикс. 256) с глифом, масштаб kx×ky, по центру по x, верх строки — top."""
    W, H = cell_w * S, cell_h * S
    gw = max(1, int(round(glyph.shape[1] * kx))); gh = max(1, int(round(glyph.shape[0] * ky)))
    im = Image.fromarray((glyph * 255).astype(np.uint8)).resize((gw, gh), Image.LANCZOS)
    g = np.asarray(im).astype(np.float32) / 255.0
    cell = np.zeros((H, W), np.float32)
    x = int(round((W - gw) / 2.0)); y = int(round(top * S))
    if x < MARGIN or x + gw > W - MARGIN or y < MARGIN or y + gh > H - MARGIN:
        raise SystemExit(f'глиф {gw}×{gh} не влезает в ячейку {W}×{H} с рамкой {MARGIN} (x {x}, y {y})')
    cell[y:y + gh, x:x + gw] = np.clip(g, 0, 1)
    return cell


def dots(cell_w, cell_h, d, cys):
    """круги диаметра d (пикс. 256) по центру ячейки по x, центры cys; суперсэмплинг 8×."""
    W, H, ss = cell_w * S, cell_h * S, 8
    im = Image.new('L', (W * ss, H * ss), 0); dr = ImageDraw.Draw(im)
    cx = cell_w / 2.0
    for cy in cys:
        r = d / 2.0
        dr.ellipse([(cx - r) * S * ss, (cy - r) * S * ss, (cx + r) * S * ss, (cy + r) * S * ss], fill=255)
    return np.asarray(im.resize((W, H), Image.LANCZOS)).astype(np.float32) / 255.0


def cov_to_rgb(cov, pal):
    """покрытие 0..1 → цвет палитры по индексу cov·255 (линейная интерполяция соседних индексов)."""
    f = np.clip(cov, 0, 1) * 255.0
    i0 = np.floor(f).astype(int); i1 = np.minimum(i0 + 1, 255); t = (f - i0)[..., None]
    p = pal.astype(np.float32)
    return (p[i0] * (1 - t) + p[i1] * t).round().clip(0, 255).astype(np.uint8)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('lev', help='Data_Files/Levels/miami_01.lev')
    ap.add_argument('strip', help='полоса цифр 0..9 (белые на чёрном), напр. <пак>/hud_hd/src/digits.png')
    ap.add_argument('pack', help='основной пак (база страницы: <пак>/<уровень>/pNNN_cKKKK.png)')
    ap.add_argument('--out', required=True, help='каталог варианта, напр. <пак>/hud_hd')
    ap.add_argument('--bold', type=int, default=10, help='утолщение штриха, пиксели полосы (0 — как нарисовано)')
    ap.add_argument('--sheet', help='PNG-лист проверки: все ячейки крупно')
    a = ap.parse_args()
    lv = texpack.os.path.basename(a.lev)[:-4].lower() if a.lev.lower().endswith('.lev') else os.path.basename(a.lev)
    if lv not in LEVELS:
        raise SystemExit(f'для уровня {lv} ячейки шрифта не описаны (есть: {", ".join(LEVELS)})')
    c = LEVELS[lv]
    data = open(a.lev, 'rb').read()
    pals, pages = texpack.lev_pal8(data)
    pg = c['page']
    d3d = texpack.find_d3d(a.lev)
    pairs = [k for i, k in texpack.pal8_pairs(pals, pages, texpack.read_d3d(d3d) if d3d else None) if i == pg]
    glyphs, row_h = digits_from_strip(a.strip, a.bold)
    bw, bh = c['big_wh']
    cells = []   # (u, v, w, h, покрытие HD)
    bkx, bky = scales(glyphs, [bw] * 10, c['big_top'], c['big_base'], row_h)
    skx, sky = scales(glyphs, [c['small'][ch][2] for ch in '0123456789'], c['small_top'], c['small_base'], row_h)
    print(f'масштаб: крупные {bkx / bky:.2f}× по ширине, мелкие {skx / sky:.2f}×')
    for n, ch in enumerate('0123456789'):
        u, v = c['big'][ch]
        cells.append((u, v, bw, bh, place(glyphs[n], bw, bh, c['big_top'], bkx, bky)))
        u, v, w = c['small'][ch]
        cells.append((u, v, w, c['small_h'], place(glyphs[n], w, c['small_h'], c['small_top'], skx, sky)))
    u, v, w, h = c['colon']; cells.append((u, v, w, h, dots(w, h, c['colon_d'], c['colon_cy'])))
    u, v, w, h = c['dot']; cells.append((u, v, w, h, dots(w, h, c['dot_d'], (c['dot_cy'],))))
    os.makedirs(os.path.join(a.out, lv), exist_ok=True)
    for k in pairs:
        fn = f'p{pg:03d}_c{k:04d}.png'
        src = os.path.join(a.pack, lv, fn)
        if os.path.exists(src):
            base = np.asarray(Image.open(src).convert('RGBA')).copy()
        else:
            base = np.dstack([np.repeat(np.repeat(pals[k][pages[pg]], S, 0), S, 1), np.full((256 * S, 256 * S), 255, np.uint8)])
        if base.shape[0] != 256 * S:
            raise SystemExit(f'{src}: ожидалась страница {256 * S}×{256 * S}')
        for u, v, w, h, cov in cells:
            base[v * S:(v + h) * S, u * S:(u + w) * S, :3] = cov_to_rgb(cov, pals[k])
            base[v * S:(v + h) * S, u * S:(u + w) * S, 3] = 255
        Image.fromarray(base, 'RGBA').save(os.path.join(a.out, lv, fn), optimize=True)
        print(f'{lv}/{fn}: {len(cells)} ячеек (база: {"пак" if os.path.exists(src) else "оригинал nearest"})')
    if a.sheet:
        row = lambda chs, key, h: np.hstack([[cl for cl in cells if cl[:2] == ((c[key][x][0], c[key][x][1]))][0][4]
                                              for x in chs])
        big = row('0123456789', 'big', bh)
        colon = [cl for cl in cells if cl[:2] == c['colon'][:2]][0][4]
        small = row('0123456789', 'small', c['small_h'])
        dot = [cl for cl in cells if cl[:2] == c['dot'][:2]][0][4]
        top = np.hstack([big, colon]); bot = np.hstack([small, dot])
        bot = np.pad(bot, ((0, 0), (0, top.shape[1] - bot.shape[1])))
        sh = np.vstack([top, np.full((8, top.shape[1]), 0.25), bot])
        Image.fromarray((sh * 255).astype(np.uint8)).save(a.sheet)
    return 0


if __name__ == '__main__':
    sys.exit(main())
