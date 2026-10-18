#!/usr/bin/env python3
"""Driver (PC, 1999) — сохранения кампании Undercover SAVES\\GAMEn.BIN (v2.30).

Формат (00405d60 запись, 00405cb4/00405e79 проверка, 0040c480 загрузка; little-endian, 64 байта, одинаков в оригинале
и Complete Version — проверено на сейвах Complete Version с playground.ru):
  +0x00 u32  0x57231356 подпись
  +0x04 u32  сумма байтов 0x38 байт данных (0040682d)
  +0x08 char[16] имя (вводится в мотеле)
  +0x18 i32  уровень (00575ef0, P19_Level): 1 Майами … 4 Нью-Йорк — открытые города; при загрузке берётся максимум
  +0x1c i32  номер записи лестницы DATA\\MLADDER.DML (01271048: (cur − base) >> 4) — последняя выполненная (продолжение с +1)
  +0x20 i32  город (01271050, P68_IntroA): 0 Miami, 1 Frisco, 2 LA, 3 NY
  +0x24 u32  биты TRIGGER (0127104c) — для IF n в лестнице (бит 0 — «Ali Story completed» → миссия 43)
  +0x28 i32  машина CARSELECT (00b87e54)
  +0x2c..0x3f нули
Native читает файл без изменений: путь <каталог данных>/SAVES/GAMEn.BIN (g_fopen: '\\' → '/').

  driver_save.py dump ФАЙЛ...                      — разбор и проверка суммы
  driver_save.py ladder [mladder.dml]              — номера записей лестницы (для make --entry)
  driver_save.py make ВЫХОД --entry N|--mission M [--name S] [--level L] [--city C] [--triggers T] [--car Y] [--dml F]
                                                   — сейв «в мотеле»: N — последняя выполненная запись (игра продолжит с N+1;
                                                     для выбора в ROOM — запись перед ROOM), --mission M — перед MISSION/SUBMISSION M
"""
import argparse, struct, sys

MAGIC = 0x57231356
CITIES = ['Miami', 'Frisco', 'LA', 'NY']
COUNTED = {'SETCITY', 'ROOM', 'INTERVIEW', 'MISSION', 'SUBMISSION', 'RENDER', 'TRIGGER', 'IF', 'IFOK', 'ELSE', 'ENDIF',
           'QUITONFAIL', 'END'}   # P141_LadderLine: команды, создающие запись 0x10 (ENDROOM/JOKE/CARSELECT — нет)


def parse(b):
    if len(b) < 0x40:
        raise ValueError('короче 64 байт')
    magic, csum = struct.unpack_from('<II', b, 0)
    data = b[8:0x40]
    name = data[:16].split(b'\0')[0].decode('latin-1')
    level, entry, city, trig, car = struct.unpack_from('<iiiIi', data, 0x10)
    return dict(magic=magic, csum=csum, ok=magic == MAGIC and csum == sum(data) & 0xffffffff, name=name, level=level,
                entry=entry, city=city, triggers=trig, car=car)


def build(name, level, entry, city, trig, car):
    data = bytearray(0x38)
    n = name.encode('latin-1')[:15]
    data[:len(n)] = n
    struct.pack_into('<iiiIi', data, 0x10, level, entry, city, trig, car)
    return struct.pack('<II', MAGIC, sum(data) & 0xffffffff) + bytes(data)


def ladder(path):
    out, n, city = [], 0, 0
    for ln, line in enumerate(open(path, encoding='latin-1'), 1):
        t = line.split('#')[0].split()
        if not t:
            continue
        k = t[0].upper()
        if k == 'SETCITY' and len(t) > 1:
            city = {'[MIAMI]': 0, '[SF]': 1, '[LA]': 2, '[NY]': 3}.get(t[1].upper(), city)
        if k in COUNTED:
            out.append((n, ln, city, k, t[1] if len(t) > 1 else ''))
            n += 1
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest='cmd', required=True)
    d = sp.add_parser('dump'); d.add_argument('files', nargs='+')
    l = sp.add_parser('ladder'); l.add_argument('dml', nargs='?', default='DATA/MLADDER.DML')
    m = sp.add_parser('make'); m.add_argument('out')
    g = m.add_mutually_exclusive_group(required=True)
    g.add_argument('--entry', type=lambda s: int(s, 0)); g.add_argument('--mission', type=int)
    m.add_argument('--name'); m.add_argument('--level', type=int); m.add_argument('--city', type=int)
    m.add_argument('--triggers', type=lambda s: int(s, 0), default=0); m.add_argument('--car', type=int, default=0)
    m.add_argument('--dml', default='DATA/MLADDER.DML')
    a = ap.parse_args()
    if a.cmd == 'dump':
        rc = 0
        for f in a.files:
            s = parse(open(f, 'rb').read())
            c = CITIES[s['city']] if 0 <= s['city'] < 4 else s['city']
            print('%s: %s имя=%r уровень=%d запись=0x%x город=%s триггеры=0x%x машина=%d' % (
                f, 'ok' if s['ok'] else 'ОШИБКА подписи/суммы', s['name'], s['level'], s['entry'], c, s['triggers'], s['car']))
            rc |= not s['ok']
        return rc
    if a.cmd == 'ladder':
        for n, ln, city, k, arg in ladder(a.dml):
            print('0x%02x  строка %3d  %-6s %s %s' % (n, ln, CITIES[city], k, arg))
        return 0
    lad = ladder(a.dml)
    entry, city = a.entry, None
    if a.mission is not None:
        for i, (n, ln, c, k, arg) in enumerate(lad):
            if k in ('MISSION', 'SUBMISSION') and arg == str(a.mission):
                entry, city = n - 1, c   # запись = последняя выполненная: игра продолжает со следующей
                break
        else:
            sys.exit('миссия %d не найдена в лестнице' % a.mission)
    if city is None:
        city = next((c for n, ln, c, k, arg in lad if n == entry), 0)
    if a.city is not None:
        city = a.city
    level = a.level if a.level is not None else city + 1
    name = a.name if a.name is not None else ('M%d' % a.mission if a.mission is not None else 'E%x' % entry)
    open(a.out, 'wb').write(build(name, level, entry, city, a.triggers, a.car))
    print('%s: запись 0x%x город %s уровень %d' % (a.out, entry, CITIES[city], level))
    return 0


if __name__ == '__main__':
    sys.exit(main())
