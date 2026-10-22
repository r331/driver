/* Map-file lump loaders: vertex lump, street lamp grid ("GLMP") and chair placement lump
   (seats for sitting pedestrians). */
#include "ported78.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P78_VertCount")
#undef P78_VertCount
#pragma push_macro("P78_VertCount") /*gvi*/
#undef P78_VertCount /*gvi*/
int32_t P78_VertCount;
#pragma pop_macro("P78_VertCount") /*gvi*/
#pragma pop_macro("P78_VertCount")
#endif
GAME_VAR_DEF(void *, P78_VertsA, 0x00d0020c)
GAME_VAR_DEF(void *, P78_VertsB, 0x00c97a2c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P78_LampHdr")
#undef P78_LampHdr
#pragma push_macro("P78_LampHdr") /*gvi*/
#undef P78_LampHdr /*gvi*/
p78_hdr_t P78_LampHdr;
#pragma pop_macro("P78_LampHdr") /*gvi*/
#pragma pop_macro("P78_LampHdr")
#endif

/* 004eb811: запись на диске 0x2c байта (3 слова, 3 short, 3 слова, 3 short, 2 ushort) → запись 0x40 с w = 1.0f. */
/* P78_LoadVerts — Game.exe 004eb811, cdecl.  Load the vertex lump of `size` bytes from file f.
   Each 0x2c-byte disk record (3 int32, 3 int16, 3 int32, 3 int16, 2 uint16) is expanded to a
   0x40-byte record with w = 1.0f after each xyz triple and the two uint16 widened to uint32.
   Allocates P78_VertsA and P78_VertsB (count * 0x40 each), fills only P78_VertsB; sets
   P78_VertCount and S_00D0DDE0 = 1.  TODO(RE): unsure what the int16 triples are (normals?). */
void P78_LoadVerts(void *f, int32_t size) {
  static const char *file = "D:\\Driver\\Game\\map.c";
  const float one = 1.0f;
  P78_VertCount = (int32_t)((uint32_t)size / 0x2c);
  int32_t bytes = P78_VertCount << 6;
  P78_VertsA = DebugMalloc(bytes, file, 0x198);
  P78_VertsB = DebugMalloc(bytes, file, 0x199);
  S_00D0DDE0 = 1;
  uint8_t *out = (uint8_t *)P78_VertsB;
  for (int32_t i = 0; i < P78_VertCount; i++, out += 0x40) {
    uint8_t in[0x2c];
    memset(out, 0, 0x40);
    memset(in, 0, sizeof in);
    P27_ReadChunked(in, 0x2c, 1, f);
    memcpy(out + 0x00, in + 0x00, 12);
    memcpy(out + 0x0c, &one, 4);
    memcpy(out + 0x10, in + 0x0c, 6);                 /* 3 short: +0x10, +0x12, +0x14 */
    memcpy(out + 0x18, in + 0x14, 12);
    memcpy(out + 0x24, &one, 4);
    memcpy(out + 0x28, in + 0x20, 6);                 /* 3 short: +0x28, +0x2a, +0x2c */
    uint16_t a, b;
    memcpy(&a, in + 0x28, 2); memcpy(&b, in + 0x2a, 2);
    uint32_t wa = a, wb = b;
    memcpy(out + 0x30, &wa, 4);
    memcpy(out + 0x34, &wb, 4);
  }
}

/* 004eafe0: сетка фонарей: заголовок 0x14 байт «GLMP», w, h, число записей; запись = {индекс ячейки, число} + число*0x28 байт. */
/* P78_LoadLamps — Game.exe 004eafe0, cdecl.  Load the street lamp grid.  Header 0x14 bytes: "GLMP", ?, width, height, record count; each
   record = {cell index, count} followed by count * 0x28 bytes of lamps.  Rebuilds
   P58_ListB31EC4 (width * height slots).  Returns 1 on success; 0 and rewinds the file if the
   magic does not match; 0 on allocation failure.  Native: rejects out-of-range cell indices. */
int32_t P78_LoadLamps(void *f) {
  static const char *file = "D:\\Driver\\Game\\lamps.c";
  long start = g_ftell(f);
  memset(P78_LampHdr, 0, sizeof(p78_hdr_t));
  g_fread(P78_LampHdr, 1, 0x14, f);
  const uint8_t *m = (const uint8_t *)P78_LampHdr;
  if (!(m[0] == 'G' && m[1] == 'L' && m[2] == 'M' && m[3] == 'P')) {
    g_fseek(f, start, 0);
    return 0;
  }
  if (P58_ListB31EC4 != NULL) P58_FreeList();
  P58_CntB31EBC = P78_LampHdr[2] * P78_LampHdr[3];
  P58_ListB31EC4 = (p58_slot_t *)DebugMalloc(P58_CntB31EBC * (int32_t)sizeof(p58_slot_t), file, 0x102);
  if (P58_ListB31EC4 == NULL) return 0;
  memset(P58_ListB31EC4, 0, (size_t)P58_CntB31EBC * sizeof(p58_slot_t));
  for (int32_t left = P78_LampHdr[4]; left != 0; left--) {
    int32_t rec[2] = {0, 0};
    g_fread(rec, 1, 8, f);
    if (rec[0] < 0 || rec[0] >= P58_CntB31EBC) { P58_FreeList(); return 0; }   /* в оригинале проверки нет */
    p58_slot_t *s = &P58_ListB31EC4[rec[0]];
    s->a = rec[1];
    if (rec[1] == 0) { s->p = NULL; continue; }
    s->p = DebugMalloc(rec[1] * 0x28, file, 0x114);
    if (s->p == NULL) { P58_FreeList(); return 0; }
    g_fread(s->p, 0x28, (size_t)s->a, f);
  }
  return 1;
}

/* P78_LoadLampsBlock — Map-lump callback wrapper around P78_LoadLamps (result ignored). */
void P78_LoadLampsBlock(void *f) { P78_LoadLamps(f); }

/* 004a31fc: ячейка = {индекс, число, буфер}; прежний буфер освобождается. */
/* P78_ChairAdd — Game.exe 004a31fc, cdecl.  Put a chair list into the chair grid: cell rec->a gets {index, count rec->b, items}.
   Allocates the cell on first use; an existing cell's old item buffer is freed.  Returns 1, or 0
   if the grid is missing or (native check) the index is out of range / allocation fails. */
int32_t P78_ChairAdd(const p58_cell_t *rec) {
  if (P58_Grid == NULL || P58_GridW == 0 || P58_GridH == 0) return 0;
  int32_t idx = rec->a;
  if (idx < 0 || idx >= P58_GridW * P58_GridH) return 0;                        /* в оригинале проверки нет */
  p58_cell_t *c = (p58_cell_t *)P58_Grid[idx];
  if (c == NULL) {
    c = (p58_cell_t *)DebugMalloc((int32_t)sizeof(p58_cell_t), "D:\\Driver\\Game\\chairs.c", 0x1ce);
    P58_Grid[idx] = c;
    if (c == NULL) return 0;
  } else if (c->items != NULL) {
    DebugFree(c->items);
  }
  c->items = rec->items;
  c->a = idx;
  c->b = rec->b;
  return 1;
}

/* 004a2f77: блок кресел. Заголовок 0x14 байта {?, версия (2), ширина, высота, число лампов}; сетка ширина*высота указателей;
   лист = {индекс ячейки, число, ...} + число*0x14 байт. Версия не 2 — блок пропускается. */
/* P78_LoadChairs — Game.exe 004a2f77, cdecl.  Load the chair placement lump (`size` bytes).  Header 0x14 bytes: {?, version (must be 2),
   width, height, list count}; then each list = {cell index, count, ?} + count * 0x14-byte
   chairs.  Allocates the P58_Grid pointer grid and adds each list via P78_ChairAdd, counting
   chairs in D_01134ea0.  Other versions are skipped (sitting pedestrians disabled).  Logs progress.
   Note: P58_GridH receives the width and P58_GridW the height — kept as in the original. */
void P78_LoadChairs(void *f, int32_t size) {
  char msg[160];
  DebugLog("\nAttempting to process Chair placement lump.");
  P58_FreeGrid();
  long start = g_ftell(f);
  int32_t hdr[5] = {0, 0, 0, 0, 0};
  g_fread(hdr, 1, 0x14, f);
  if (hdr[1] != 2) {
    g_fseek(f, start + size, 0);
    DebugLog("Chair chunk is an incompatible version, ignoring.  Sitting pedestrians will not be available during game.");
    return;
  }
  int32_t w = hdr[2], h = hdr[3];
  int32_t bytes = w * h * (int32_t)sizeof(void *);
  snprintf(msg, sizeof msg, "Map is %d cells wide and %d cells high, pointer is %d bytes long required memory is %d (%dk).",
           w, h, (int32_t)sizeof(void *), bytes, (bytes + ((bytes >> 31) & 0x3ff)) >> 10);
  DebugLog(msg);
  P58_Grid = (void **)DebugMalloc(bytes, "D:\\Driver\\Game\\chairs.c", 0x17c);
  if (P58_Grid == NULL) {
    snprintf(msg, sizeof msg, "Error allocating memory for ChairCells (%d requested), terminating routine.", bytes);
    DebugLog(msg);
    return;
  }
  memset(P58_Grid, 0, (size_t)bytes);
  P58_GridH = w;
  P58_GridW = h;
  for (int32_t left = hdr[4]; left != 0; left--) {
    int32_t rec3[3] = {0, 0, 0};
    g_fread(rec3, 1, 0xc, f);
    int32_t count = rec3[1];
    void *list = DebugMalloc(count * 0x14, "D:\\Driver\\Game\\chairs.c", 0x193);
    if (list == NULL) {
      DebugLog("Unable to allocate memory for chair list.");
      P58_FreeGrid();
      return;
    }
    D_01134ea0 += count;
    for (int32_t i = 0; i < count; i++) g_fread((uint8_t *)list + i * 0x14, 1, 0x14, f);
    p58_cell_t cell;
    cell.a = rec3[0]; cell.b = count; cell.items = list;
    if (!P78_ChairAdd(&cell)) {
      DebugLog("Failed to Add chair list to game, routine terminated.");
      DebugFree(list);
      P58_FreeGrid();
      return;
    }
  }
  snprintf(msg, sizeof msg, "ProcessChairLump completed successfully (%d chairs retrieved), routine terminated.", D_01134ea0);
  DebugLog(msg);
}
