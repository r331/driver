/* v2.31: детальные 3D-меши фасадов (балконы, козырьки) поверх плоских стен — только native (SDL/GL), только с HD-паком.
   Данные: <пак>/<уровень>/detail/detail.json + .glb на запись (ключ: уровень, страница pNNN[_cKKKK], слот палитры, uv_rect_256).
   Каждый кадр основного вида (P89_DrawMap(1)) треугольники мира с текстурой, совпадающей с ключом, и UV внутри прямоугольника
   записи дают копию меша: аффинное преобразование «меш (метры) → камера» из точных координат камеры трёх вершин и их UV
   (до округления экранных координат и табличной обратной глубины). Плоский полигон остаётся;
   меши рисуются после сброса пакетов мира с z-тестом и альфа-тестом, оттенок — цвет вершин полигона (свет/туман мира).
   DRIVER_DETAIL=0 — выключить; DRIVER_DETAIL_DIR=каталог с detail.json — вместо пака; DRIVER_DETAIL_LOG=1 — журнал совпадений. */
#ifndef RE_PLAT_DETAIL_H
#define RE_PLAT_DETAIL_H
extern int re_detail_capture;                  /* 1 — внутри основного прохода карты: треугольники проверяются */
void re_detail_frame_begin(void);              /* перед P89_DrawMap(1) */
void re_detail_tri(const void *a, const void *b, const void *c);   /* вершины Glide (p85_rv) треугольника мира — из P76 tri() */
void re_detail_frame_end(void);                /* после P89_DrawMap(1): сброс пакетов и рисование копий */
int re_detail_selftest(void);                  /* matching regression, no graphics context needed */
#endif
