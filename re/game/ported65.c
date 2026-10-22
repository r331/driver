/* Front-end helpers: script tokenizer, name lookup, the 8-bit software screen sprite blitters
   and the player-name field. */
#include "ported65.h"
#include <stdio.h>
#include <string.h>
#include "ported40.h"
#include "reptr.h"

#define SCREEN_W     0x280     /* 640: bytes per row of the 8-bit software screen P65_Screen */
#define SCREEN_BYTES 0x4b000   /* 640 * 480 */
/* P65_TexPage — Pointer to texture page t.  Native: from the texture slot table (data image), falling back to
   P65_Texs for t < 64; NULL for t outside 0..255.  Hook: P65_Texs[t].p. */
void *P65_TexPage(int32_t t) {
#ifdef RE_HOOK_BUILD
  return P65_Texs[t].p;
#else
  if (t < 0 || t >= 0x100) return NULL;
  void *p = P40_Slots[t].data != 0 ? re_ptr(P40_Slots[t].data) : NULL;
  if (p == NULL && t < 64) p = P65_Texs[t].p;
  return p;
#endif
}

#ifndef RE_HOOK_BUILD
char *P65_Line = NULL;
#pragma push_macro("P65_Tok") /*gvi*/
#undef P65_Tok /*gvi*/
p65_tok_t P65_Tok;
#pragma pop_macro("P65_Tok") /*gvi*/
#pragma push_macro("P65_Ints") /*gvi*/
#undef P65_Ints /*gvi*/
p65_ints_t P65_Ints;
#pragma pop_macro("P65_Ints") /*gvi*/
#pragma push_macro("P65_Name") /*gvi*/
#undef P65_Name /*gvi*/
p65_name_t P65_Name;
#pragma pop_macro("P65_Name") /*gvi*/
const char *P65_NamePtr = NULL;
const char *P65_NameBg = NULL;
#pragma push_macro("P65_Screen") /*gvi*/
#undef P65_Screen /*gvi*/
p65_screen_t P65_Screen;
#pragma pop_macro("P65_Screen") /*gvi*/
p65_texs_t P65_Texs;
#pragma push_macro("P65_Blend") /*gvi*/
#undef P65_Blend /*gvi*/
p65_blend_t P65_Blend;
#pragma pop_macro("P65_Blend") /*gvi*/
#pragma push_macro("P65_ColorKey") /*gvi*/
#undef P65_ColorKey /*gvi*/
uint8_t P65_ColorKey = 0;
#pragma pop_macro("P65_ColorKey") /*gvi*/
#endif

/* P65_NextToken — Game.exe 004f6774, cdecl.  Cut the next token off `line` into `tok`.  Leading blanks are skipped; a token ends at a blank,
   newline, ',' or ';' (the delimiter is consumed).  The rest of the line is moved to its start.
   Returns 0, or 10 if no token was found (end of line). */
int32_t P65_NextToken(char *line, char *tok) {
  int32_t n = 0, i = 0;
  size_t left = strlen(line);
  while (left != 0) {
    char c = line[i];
    i++;
    left--;
    if ((c != ' ' && c != '\t') || n != 0) {
      if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ';') break;
      tok[n++] = c;
    }
  }
  tok[n] = 0;
  int32_t m = 0;
  for (; line[i] != '\0'; i++) line[m++] = line[i];
  line[m] = '\0';
  return n == 0 ? 10 : 0;
}

/* P65_ReadInts — Game.exe 004f87e0, cdecl.  Read cmd->count (int32 at cmd + 0x100) decimal integers from P65_Line into P65_Ints.
   Returns 0, the tokenizer's error (10) or 0xc if a token is not a number. */
int32_t P65_ReadInts(void *cmd) {
  int32_t count;
  memcpy(&count, (uint8_t *)cmd + 0x100, 4);
  for (int32_t i = 0; i < count; i++) {
    int32_t rc = P65_NextToken(P65_Line, P65_Tok);
    if (rc != 0) return rc;
    int32_t r = g_sscanf(P65_Tok, "%d", &P65_Ints[i]);
    if (r == 0 || r == -1) return 0xc;
  }
  return 0;
}

/* P65_FindByName — Game.exe 004f8cfd, cdecl.  Upper-case `name` in place (ASCII only) and look it up in tab.  Returns the entry's value or
   -1 (also for name == NULL). */
int32_t P65_FindByName(char *name, p65_tab_t *tab) {
  if (name == NULL) return -1;
  for (char *s = name; *s != '\0'; s++)
    if (*s > '`' && *s < '{') *s = (char)(*s - 0x20);          /* strupr (локаль «C») */
  for (int32_t i = 0; i < tab->count; i++)
    if (strcmp(name, tab->ents[i]->name) == 0) return tab->ents[i]->value;
  return -1;
}

/* таблица выбора строки 0x54a058 = {2, 1, -1} */
/* SelIdx — Native copy of the .data table 0054a058 = {2, 1, -1}: string index by 00b87ef0. */
static int32_t SelIdx(int32_t i) {
#ifdef RE_HOOK_BUILD
  return ((int32_t *)(uintptr_t)0x0054a058)[i];
#else
  static const int32_t t[3] = { 2, 1, -1 };
  return (i >= 0 && i < 3) ? t[i] : 0;
#endif
}

/* P65_SetNameFields — Game.exe 004072be, cdecl.  Set the name/background string fields of the player name box.  P65_NameVal == 0: input mode 0,
   strings 0x40 and 0xc; otherwise input mode 2, name = "<string 0x41> <n>", background string
   chosen by 00b87ef0 via SelIdx.  Native: bounded sprintf and range-checked index. */
void P65_SetNameFields(void) {
  if (P65_NameVal == 0) {
    P35_InputMode = 0;
    P65_NamePtr = P65_STR(0x40);
    P65_NameBg = P65_STR(0xc);
  } else {
    P35_InputMode = 2;
    snprintf(P65_Name, sizeof P65_Name, "%s %d", P65_STR(0x41), P65_NameVal);   /* в оригинале sprintf без границ в 20 байт */
    P65_NamePtr = P65_Name;
    int32_t k = SelIdx(Q00B87EF0);
#ifdef RE_HOOK_BUILD
    P65_NameBg = P65_STR(k);
#else
    P65_NameBg = (k >= 0 && k < 0x15e) ? P65_STR(k) : NULL;
#endif
  }
}

/* P65_BlitKeyed — Game.exe 00529140, cdecl.  Copy a w x h block from texel (u, v) of a 256x256 8-bit page to dst (640-byte rows), skipping
   P65_ColorKey (transparent colour).  u and v wrap at 256; page is rounded down to 64 KiB. */
void P65_BlitKeyed(const void *page, uint8_t *dst, int32_t w, int32_t h, int32_t u, int32_t v) {
  const uint8_t *base = (const uint8_t *)((uintptr_t)page & ~(uintptr_t)0xffff);
  uint32_t uu = (uint32_t)u & 0xff, vv = (uint32_t)v & 0xff;
  for (; h > 0; h--) {
    uint32_t x = uu;
    for (int32_t i = 0; i < w; i++) {
      uint8_t c = base[(vv << 8) | x];
      x = (x + 1) & 0xff;
      if (c != P65_ColorKey) dst[i] = c;
    }
    vv = (vv + 1) & 0xff;
    dst += SCREEN_W;
  }
}

/* P65_BlitBlend — Game.exe 00529190, cdecl.  As P65_BlitKeyed, but each pixel becomes P65_Blend[screen pixel][texel] (translucency). */
void P65_BlitBlend(const void *page, uint8_t *dst, int32_t w, int32_t h, int32_t u, int32_t v) {
  const uint8_t *base = (const uint8_t *)((uintptr_t)page & ~(uintptr_t)0xffff);
  uint32_t uu = (uint32_t)u & 0xff, vv = (uint32_t)v & 0xff;
  for (; h > 0; h--) {
    uint32_t x = uu;
    for (int32_t i = 0; i < w; i++) {
      uint8_t s = base[(vv << 8) | x];
      x = (x + 1) & 0xff;
      dst[i] = P65_Blend[((uint32_t)dst[i] << 8) | s];   /* 256x256 blend table: [screen][source] */
    }
    vv = (vv + 1) & 0xff;
    dst += SCREEN_W;
  }
}

/* P65_SpriteKeyed — Game.exe 00407cb8, cdecl.  Draw a colour-keyed sprite from texture `tex` at screen (x, y).  Native: bounds-checked. */
void P65_SpriteKeyed(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h) {
#ifndef RE_HOOK_BUILD
  if (tex < 0 || tex >= 64 || P65_Texs[tex].p == NULL || x < 0 || y < 0 || w <= 0 || h <= 0 || (int64_t)(y + h - 1) * SCREEN_W + x + w > SCREEN_BYTES) return;   /* v2.02: native — границы */
#endif
  P65_BlitKeyed(P65_Texs[tex].p, (uint8_t *)P65_Screen + (ptrdiff_t)y * SCREEN_W + x, w, h, u, v);
}

/* P65_SpriteBlend — Game.exe 00407d07, cdecl.  Draw a blended (translucent) sprite from texture `tex` at screen (x, y).  Native: bounds-checked. */
void P65_SpriteBlend(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h) {
#ifndef RE_HOOK_BUILD
  if (tex < 0 || tex >= 64 || P65_Texs[tex].p == NULL || x < 0 || y < 0 || w <= 0 || h <= 0 || (int64_t)(y + h - 1) * SCREEN_W + x + w > SCREEN_BYTES) return;   /* v2.02: native — границы */
#endif
  P65_BlitBlend(P65_Texs[tex].p, (uint8_t *)P65_Screen + (ptrdiff_t)y * SCREEN_W + x, w, h, u, v);
}

/* P65_ScriptCall — Game.exe 004d1529, cdecl.  Script opcode: skip the opcode word, read the following uint16 argument and call 004cfe69 with
   it.  Returns 1 (continue).  TODO(RE): unsure what 004cfe69 does. */
int32_t P65_ScriptCall(void) {
  uint16_t w;
  P10_ScriptPtr += 2;
  memcpy(&w, P10_ScriptPtr, 2);
  P10_ScriptPtr += 2;
  P65_Fn4CFE69(w);
  return 1;
}
