#include "ported65.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
char *P65_Line = NULL;
p65_tok_t P65_Tok;
p65_ints_t P65_Ints;
p65_name_t P65_Name;
const char *P65_NamePtr = NULL;
const char *P65_NameBg = NULL;
p65_screen_t P65_Screen;
p65_texs_t P65_Texs;
p65_blend_t P65_Blend;
uint8_t P65_ColorKey = 0;
#endif

/* 004f6774 */
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

/* 004f87e0 */
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

/* 004f8cfd */
int32_t P65_FindByName(char *name, p65_tab_t *tab) {
  if (name == NULL) return -1;
  for (char *s = name; *s != '\0'; s++)
    if (*s > '`' && *s < '{') *s = (char)(*s - 0x20);          /* strupr (локаль «C») */
  for (int32_t i = 0; i < tab->count; i++)
    if (strcmp(name, tab->ents[i]->name) == 0) return tab->ents[i]->value;
  return -1;
}

/* таблица выбора строки 0x54a058 = {2, 1, -1} */
static int32_t SelIdx(int32_t i) {
#ifdef RE_HOOK_BUILD
  return ((int32_t *)(uintptr_t)0x0054a058)[i];
#else
  static const int32_t t[3] = { 2, 1, -1 };
  return (i >= 0 && i < 3) ? t[i] : 0;
#endif
}

/* 004072be */
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

/* 00529140 */
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
    dst += 0x280;
  }
}

/* 00529190 */
void P65_BlitBlend(const void *page, uint8_t *dst, int32_t w, int32_t h, int32_t u, int32_t v) {
  const uint8_t *base = (const uint8_t *)((uintptr_t)page & ~(uintptr_t)0xffff);
  uint32_t uu = (uint32_t)u & 0xff, vv = (uint32_t)v & 0xff;
  for (; h > 0; h--) {
    uint32_t x = uu;
    for (int32_t i = 0; i < w; i++) {
      uint8_t s = base[(vv << 8) | x];
      x = (x + 1) & 0xff;
      dst[i] = P65_Blend[((uint32_t)dst[i] << 8) | s];
    }
    vv = (vv + 1) & 0xff;
    dst += 0x280;
  }
}

/* 00407cb8 */
void P65_SpriteKeyed(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h) {
#ifndef RE_HOOK_BUILD
  if (tex < 0 || tex >= 64 || P65_Texs[tex].p == NULL || x < 0 || y < 0 || w <= 0 || h <= 0 || (int64_t)(y + h - 1) * 0x280 + x + w > 0x4b000) return;   /* v2.02: native — границы */
#endif
  P65_BlitKeyed(P65_Texs[tex].p, (uint8_t *)P65_Screen + (ptrdiff_t)y * 0x280 + x, w, h, u, v);
}

/* 00407d07 */
void P65_SpriteBlend(int32_t x, int32_t y, int32_t tex, int32_t u, int32_t v, int32_t w, int32_t h) {
#ifndef RE_HOOK_BUILD
  if (tex < 0 || tex >= 64 || P65_Texs[tex].p == NULL || x < 0 || y < 0 || w <= 0 || h <= 0 || (int64_t)(y + h - 1) * 0x280 + x + w > 0x4b000) return;   /* v2.02: native — границы */
#endif
  P65_BlitBlend(P65_Texs[tex].p, (uint8_t *)P65_Screen + (ptrdiff_t)y * 0x280 + x, w, h, u, v);
}

/* 004d1529 */
int32_t P65_ScriptCall(void) {
  uint16_t w;
  P10_ScriptPtr += 2;
  memcpy(&w, P10_ScriptPtr, 2);
  P10_ScriptPtr += 2;
  P65_Fn4CFE69(w);
  return 1;
}
