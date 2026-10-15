#pragma once
#include <stdint.h>
/* Единый реестр «адрес Game.exe ↔ native-объект» (стандарт v1.42, см. re/README.md «Правила переноса»).
   Указатели, которые в оригинале лежат 32-битными полями таблиц/списков/записей игры, в native хранятся как uint32_t-адреса
   Game.exe. re_ptr(адрес) даёт родной указатель, re_addr(указатель) — адрес обратно.
   RE_HOOK_BUILD: тождество (адрес и есть указатель в 32-битном процессе Game.exe).
   Нативная сборка: статические области (GAME_VAR-массивы с известным адресом) + области, зарегистрированные в работе
   (re_ptr_register — по адресу Game.exe; re_ptr_register_dyn — синтетический адрес 0x80000000+ для кучи/строк native).
   re_addr() родного указателя вне всех областей регистрирует его синтетическим адресом (размер 1) — так строки и
   прочие родные объекты переживают путь через 32-битное поле. Указатели на функции — re_fn()/re_fn_addr() по таблице
   адрес Game.exe → native-функция (в native неизвестный адрес → NULL). */
typedef void (*re_fn_t)(void);

void    *re_ptr(uint32_t addr);                                  /* 0 → NULL; в native вне областей → NULL */
uint32_t re_addr(const void *p);                                 /* NULL → 0 */
void     re_ptr_register(uint32_t addr, void *native, uint32_t size);
uint32_t re_ptr_register_dyn(void *native, uint32_t size);      /* → синтетический адрес */
void     re_ptr_unregister(const void *native);
re_fn_t  re_fn(uint32_t addr);
uint32_t re_fn_addr(re_fn_t fn);
void     re_fn_register(uint32_t addr, re_fn_t fn);

/* чтение/запись 32-битного поля-указателя записи */
static inline uint32_t re_rd_addr(const void *field) { const uint8_t *b = (const uint8_t *)field;
  return (uint32_t)b[0] | (uint32_t)b[1] << 8 | (uint32_t)b[2] << 16 | (uint32_t)b[3] << 24; }
static inline void *re_rd_ptr(const void *field) { return re_ptr(re_rd_addr(field)); }
static inline void re_wr_addr(void *field, uint32_t a) { uint8_t *b = (uint8_t *)field;
  b[0] = (uint8_t)a; b[1] = (uint8_t)(a >> 8); b[2] = (uint8_t)(a >> 16); b[3] = (uint8_t)(a >> 24); }
static inline void re_wr_ptr(void *field, const void *p) { re_wr_addr(field, re_addr(p)); }
