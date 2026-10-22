/* reprobe.c — RE_PROBE runtime instrumentation (see reprobe.h for the topics and variables).
 * Read-only with respect to game state; the menu walker only queues key presses (plat_keys_push).
 * Native build only (not part of the hook DLL). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reprobe.h"
#include "../plat.h"
#include "../../game/reptr.h"
#include "../../game/cartab.h"
#include "../../game/carfields.h"
#include "../../game/trafficrec.h"
#include "../../game/director.h"
#include "../../game/ported14.h"
#include "../../game/ported43.h"
#include "../../game/ported45.h"
#include "../../game/ported59.h"
#include "../../game/ported62.h"
#include "../../game/ported100.h"

int plat_keys_push(int rel, const char *name);   /* plat_di.c (debug key queue) */

enum { T_CAR = 1, T_TRAFFIC = 2, T_PED = 4, T_MISSION = 8, T_MENU = 16, T_WALK = 32 };
static int g_mask = -1;            /* -1 = not initialised, 0 = off */
static FILE *g_log;
static int g_every = 50;
static const char *g_shots;

static int probe_init(void) {
  const char *e = getenv("RE_PROBE");
  g_mask = 0;
  if (e == NULL || *e == 0 || !strcmp(e, "0")) return 0;
  if (!strcmp(e, "1") || !strcmp(e, "all")) g_mask = T_CAR | T_TRAFFIC | T_PED | T_MISSION | T_MENU | T_WALK;
  else {
    static const struct { const char *n; int m; } k[] = { { "car", T_CAR }, { "traffic", T_TRAFFIC }, { "ped", T_PED },
                                                          { "mission", T_MISSION }, { "menu", T_MENU }, { "walk", T_WALK | T_MENU } };
    for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++) if (strstr(e, k[i].n)) g_mask |= k[i].m;
  }
  /* "1"/"all" means passive topics only; the walker drives the menus and has to be asked for by name */
  if (!strcmp(e, "1") || !strcmp(e, "all")) g_mask &= ~T_WALK;
  const char *p = getenv("RE_PROBE_LOG");
  g_log = fopen(p && *p ? p : "probe.log", "w");
  if (g_log == NULL) { g_mask = 0; return 0; }
  setvbuf(g_log, NULL, _IOLBF, 0);
  const char *ev = getenv("RE_PROBE_EVERY"); if (ev && atoi(ev) > 0) g_every = atoi(ev);
  g_shots = getenv("RE_PROBE_SHOTS");
  fprintf(g_log, "# RE_PROBE=%s mask=%#x every=%d\n", e, g_mask, g_every);
  return g_mask;
}
static inline int on(int t) { if (g_mask < 0) probe_init(); return g_mask & t; }

static int32_t r32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static int16_t r16(const uint8_t *p, uint32_t o) { int16_t v; memcpy(&v, p + o, 2); return v; }

/* ------------------------------------------------------------------ car / traffic / ped (per physics step) */
static int32_t g_prev138[0x42], g_prev108[0x42];
static uint8_t g_prev13e[0x42];
static int g_steps;

static void car_step(void) {
  const uint8_t *c0 = (const uint8_t *)&P99_Cars[0];
  int32_t frame = P62_Frame;
  for (int i = 0; i < 0x42; i++) {
    const uint8_t *c = (const uint8_t *)&P99_Cars[i];
    int32_t v = r32(c, CAR_DAMAGE_SUM);
    if (v != g_prev138[i] && (i == 0 || v != 0)) {
      int32_t zs = 0; for (int z = 0; z < 6; z++) zs += r32(c, CAR_DAMAGE + z * 4);
      fprintf(g_log, "car138 f=%d car=%d model=%d old=%d new=%d d=%d zones=%d,%d,%d,%d,%d,%d zsum=%d pos=%d,%d cell=%d,%d spd=%d\n",
              frame, i, c[CAR_MODEL], g_prev138[i], v, v - g_prev138[i], r32(c, 0x11c), r32(c, 0x120), r32(c, 0x124), r32(c, 0x128),
              r32(c, 0x12c), r32(c, 0x130), zs, r32(c, CAR_POS_X), r32(c, CAR_POS_Z), r32(c, CAR_POS_X) >> 10, r32(c, CAR_POS_Z) >> 10, r32(c, CAR_SPEED));
      g_prev138[i] = v;
    }
    int32_t b = r32(c, CAR_BURNOUT);
    if (b != g_prev108[i]) {
      fprintf(g_log, "car108 f=%d car=%d %d->%d fwd=%d thr=%d keys=%#x hb=%d\n", frame, i, g_prev108[i], b, r32(c, CAR_FWD_SPEED),
              r32(c, CAR_THROTTLE), i == 0 ? (unsigned)P100_RecKeys : 0u, r32(c, CAR_HANDBRAKE));
      g_prev108[i] = b;
    }
    if (c[CAR_AI_DRIVEN] != g_prev13e[i]) {
      fprintf(g_log, "car13e f=%d car=%d %d->%d model=%d\n", frame, i, g_prev13e[i], c[CAR_AI_DRIVEN], c[CAR_MODEL]);
      g_prev13e[i] = c[CAR_AI_DRIVEN];
    }
  }
  if (g_steps % g_every == 0)
    fprintf(g_log, "car0 f=%d keys=%#x 58=%d,%d,%d 68=%d,%d,%d angvel=%d,%d,%d vel=%d,%d,%d 108=%d 13c=%d 13d=%d 13e=%d 13f=%d 140=%d 141=%d steer=%d fwd=%d 138=%d\n",
            frame, (unsigned)P100_RecKeys, r32(c0, 0x58), r32(c0, 0x5c), r32(c0, 0x60), r32(c0, 0x68), r32(c0, 0x6c), r32(c0, 0x70),
            r32(c0, CAR_ANGVEL), r32(c0, CAR_ANGVEL + 4), r32(c0, CAR_ANGVEL + 8), r32(c0, CAR_VEL), r32(c0, CAR_VEL + 4), r32(c0, CAR_VEL + 8),
            r32(c0, 0x108), c0[0x13c], c0[0x13d], c0[0x13e], c0[0x13f], (int8_t)c0[0x140], (int8_t)c0[0x141], r32(c0, CAR_STEER),
            r32(c0, CAR_FWD_SPEED), r32(c0, CAR_DAMAGE_SUM));
}

static void traffic_step(void) {
  if (g_steps % g_every != 0) return;
  const uint8_t *base = (const uint8_t *)&TrafficRecs;
  for (int i = 0; i < 64; i++) {
    const uint8_t *r = base + i * TREC_SIZE;
    if (r[TREC_STATE] == 0) continue;
    const uint8_t *c = P59_CarsTab + r[TREC_CAR] * 0x148;   /* the car this record drives (as P59_CellLeft) */
    uint32_t left = P59_CellLeft(r);
    fprintf(g_log, "trec f=%d i=%d car=%d model=%d st=%d sub=%d b3=%d b5=%d b8=%d b9=%d bc=%d lane=%d at=%d f13=%#x dist=%d left=%d node=%d dir=%d n28=%d n2c=%d dir2=%d f34=%d spd=%d tgt=%d cell=%d,%d celleft=%d carspd=%d ai=%d\n",
            (int)P62_Frame, i, r[TREC_CAR], c[CAR_MODEL], r[1], r[2], r[3], r[5], r[8], r[9], r[0xc], (int)(uint16_t)r16(r, TREC_LANE), r[TREC_AT_TARGET],
            r[TREC_FLAGS13], r32(r, TREC_ROAD_DIST), r32(r, TREC_ROAD_DONE), r32(r, TREC_ROAD_NODE), r32(r, TREC_ROAD_DIR), r32(r, TREC_NEXT_NODE),
            r32(r, TREC_NEXT_NODE2), r32(r, TREC_DIR2), r32(r, TREC_F34), r32(r, TREC_SPEED), r32(r, TREC_TGT_SPEED), r32(r, TREC_CELL_X), r32(r, TREC_CELL_Z),
            (int)(left & 0xff), r32(c, CAR_SPEED), c[CAR_AI_DRIVEN]);
  }
}

static void ped_step(void) {
  if (g_steps % g_every != 0) return;
  const uint8_t *p = (const uint8_t *)&A_00C56780;
  int used = 0, hist[8] = { 0 };
  for (int i = 0; i < 0x40; i++) {
    const uint8_t *q = p + i * 0xb4;
    if ((r32(q, 0xc) & 0x10) == 0) continue;
    used++;
    int t = r16(q, 0); hist[t >= 0 && t < 7 ? t : 7]++;
  }
  fprintf(g_log, "ped f=%d active=%d inuse=%d type0..6,other=%d,%d,%d,%d,%d,%d,%d,%d\n", (int)P62_Frame, (int)P43_FreeCnt, used,
          hist[0], hist[1], hist[2], hist[3], hist[4], hist[5], hist[6], hist[7]);
}

void re_probe_step(void) {
  if (!on(T_CAR | T_TRAFFIC | T_PED)) return;
  if (on(T_CAR)) car_step();
  if (on(T_TRAFFIC)) traffic_step();
  if (on(T_PED)) ped_step();
  g_steps++;
}

/* ------------------------------------------------------------------ menus */
#define MAXT 128
#define MAXRES 1024
static struct { uint32_t tbl; int n; uint8_t items[64]; int shot; int seen_calls; } g_tb[MAXT];
static int g_ntb;
static struct { uint32_t tbl; int item; char res[24]; } g_res[MAXRES];
static int g_nres;
static char g_shot_path[512];
static uint32_t g_cur_tbl;
static int g_calls, g_last_menu_frame, g_frame;
/* walker */
static uint32_t g_stack[32]; static int g_sp;
static uint32_t g_pend_tbl; static int g_pend_item = -1, g_pend_calls;
static int g_target = -1, g_esc_calls;
static const char *g_walk_file;

static int tb_find(uint32_t tbl) { for (int i = 0; i < g_ntb; i++) if (g_tb[i].tbl == tbl) return i; return -1; }

/* entries reachable from entry 0 / cur over the left/right/up/down neighbour bytes, down-chain order first */
static void tb_items(int k, const uint8_t *t, int32_t cur) {
  uint8_t seen[256] = { 0 }; int n = 0; uint8_t q[64];
  int qh = 0, qt = 0;
  q[qt++] = 0; seen[0] = 1;
  if (cur >= 0 && cur < 64 && !seen[cur]) { q[qt++] = (uint8_t)cur; seen[cur] = 1; }
  while (qh < qt && n < 64) {
    uint8_t it = q[qh++]; g_tb[k].items[n++] = it;
    static const int nb[4] = { 0xf, 0xe, 0xd, 0xc };
    for (int j = 0; j < 4; j++) { uint8_t x = t[it * 0x10 + nb[j]]; if (x < 64 && !seen[x] && qt < 64) { seen[x] = 1; q[qt++] = x; } }
  }
  g_tb[k].n = n;
}

static const char *res_get(uint32_t tbl, int item) {
  for (int i = g_nres - 1; i >= 0; i--) if (g_res[i].tbl == tbl && g_res[i].item == item) return g_res[i].res;
  return NULL;
}
static void res_set(uint32_t tbl, int item, const char *r, int persist) {
  int i;
  for (i = 0; i < g_nres; i++) if (g_res[i].tbl == tbl && g_res[i].item == item) break;
  if (i == g_nres) { if (g_nres >= MAXRES) return; g_nres++; }
  g_res[i].tbl = tbl; g_res[i].item = item; snprintf(g_res[i].res, sizeof g_res[i].res, "%s", r);
  if (persist && g_walk_file) { FILE *f = fopen(g_walk_file, "a"); if (f) { fprintf(f, "R %08x %d %s\n", tbl, item, r); fclose(f); } }
  fprintf(g_log, "walk f=%d result %08x item %d -> %s\n", g_frame, tbl, item, r);
}
static void walk_load(void) {
  const char *w = getenv("RE_PROBE_WALK"); g_walk_file = (w && *w) ? w : "probe_walk.txt";
  FILE *f = fopen(g_walk_file, "r"); if (!f) return;
  char line[128]; unsigned tbl; int item; char r[32];
  while (fgets(line, sizeof line, f))
    if (sscanf(line, "R %x %d %31s", &tbl, &item, r) == 3) res_set(tbl, item, strcmp(r, "try") ? r : "leave", 0);
  fclose(f);
}

static int in_stack(uint32_t t) { for (int i = 0; i < g_sp; i++) if (g_stack[i] == t) return 1; return 0; }
static int tb_complete(uint32_t tbl, int depth) {
  int k = tb_find(tbl); if (k < 0 || depth > 16) return 0;
  for (int j = 0; j < g_tb[k].n; j++) {
    const char *r = res_get(tbl, g_tb[k].items[j]);
    if (r == NULL) return 0;
    if (!strncmp(r, "open:", 5)) { uint32_t x = (uint32_t)strtoul(r + 5, NULL, 16); if (x != tbl && !in_stack(x) && !tb_complete(x, depth + 1)) return 0; }
  }
  return 1;
}

static void log_texts(uint32_t tbl) {
  if (P45_PtrA == 0) { fprintf(g_log, "menutext %08x (no text list)\n", tbl); return; }
  const uint8_t *e = (const uint8_t *)re_ptr(P45_PtrA);
  fprintf(g_log, "menutext %08x list=%08x:", tbl, (unsigned)P45_PtrA);
  for (int n = 0; e && n < 48; n++, e += 0x10) {
    uint32_t sa = (uint32_t)r32(e, 8); if (sa == 0) break;
    const char *s = (const char *)re_ptr(sa);
    fprintf(g_log, " \"%s\"", s ? s : "?");
  }
  fprintf(g_log, "\n");
}

/* BFS from cur to target over the neighbour bytes; returns the key name of the first move or NULL */
static const char *nav_key(const uint8_t *t, int cur, int target, int sliders) {
  int prev[64], how[64]; uint8_t q[64]; int qh = 0, qt = 0;
  for (int i = 0; i < 64; i++) prev[i] = -2;
  if (cur < 0 || cur >= 64) return NULL;
  q[qt++] = (uint8_t)cur; prev[cur] = -1;
  static const int nb[4] = { 0xf, 0xe, 0xd, 0xc }; static const char *kn[4] = { "DOWN", "UP", "RIGHT", "LEFT" };
  while (qh < qt) {
    int it = q[qh++];
    if (it == target) break;
    for (int j = 0; j < (sliders ? 2 : 4); j++) { int x = t[it * 0x10 + nb[j]]; if (x < 64 && prev[x] == -2) { prev[x] = it; how[x] = j; q[qt++] = (uint8_t)x; } }
  }
  if (prev[target] == -2) return NULL;
  int x = target; while (prev[x] != cur && prev[x] >= 0) x = prev[x];
  return kn[how[x]];
}

static void walk_step(uint32_t tbl, int32_t cur, const uint8_t *t, int k) {
  if (g_calls < 45 || (g_calls % 8) != 0) return;            /* let the screen settle; one action per 8 frames */
  if (g_pend_item >= 0) {                                    /* an entry was chosen and we are still on this table */
    if (++g_pend_calls < 12) return;
    if (g_pend_tbl == tbl) { res_set(g_pend_tbl, g_pend_item, "stay", 1); g_pend_item = -1; }
  }
  if (g_calls > 3000) { plat_keys_push(1, "ESC"); return; }
  if (g_target < 0 || res_get(tbl, g_target) != NULL) {
    g_target = -1;
    for (int j = 0; j < g_tb[k].n && g_target < 0; j++) {
      int it = g_tb[k].items[j]; const char *r = res_get(tbl, it);
      if (r == NULL) g_target = it;
      else if (!strncmp(r, "open:", 5)) { uint32_t x = (uint32_t)strtoul(r + 5, NULL, 16); if (x != tbl && !in_stack(x) && !tb_complete(x, 0)) g_target = it; }
    }
  }
  if (g_target < 0) {                                        /* table done: back out (root: finished) */
    if (g_sp <= 1) { fprintf(g_log, "walk f=%d done at root %08x\n", g_frame, tbl); fflush(g_log); _Exit(0); }
    if (g_esc_calls++ % 4 == 0) { fprintf(g_log, "walk f=%d ESC on %08x\n", g_frame, tbl); plat_keys_push(1, "ESC"); }
    return;
  }
  if (cur != g_target) {
    const char *key = nav_key(t, cur, g_target, 0);
    if (key == NULL) { res_set(tbl, g_target, "unreachable", 1); g_target = -1; return; }
    plat_keys_push(1, key);
    return;
  }
  if (res_get(tbl, cur) == NULL) res_set(tbl, cur, "try", 1);
  fprintf(g_log, "walk f=%d RETURN on %08x item %d\n", g_frame, tbl, cur);
  g_pend_tbl = tbl; g_pend_item = cur; g_pend_calls = 0;
  plat_keys_push(1, "RETURN");
}

void re_probe_menu(uint32_t tbl, int32_t cur) {
  if (!on(T_MENU)) return;
  static int walk_init;
  if (on(T_WALK) && !walk_init) { walk_init = 1; walk_load(); }
  const uint8_t *t = (const uint8_t *)re_ptr(tbl);
  if (t == NULL) return;
  g_last_menu_frame = g_frame;
  if (tbl != g_cur_tbl) {
    int k = tb_find(tbl);
    if (k < 0 && g_ntb < MAXT) { k = g_ntb++; g_tb[k].tbl = tbl; tb_items(k, t, cur); g_tb[k].shot = 0; }
    fprintf(g_log, "menu f=%d enter %08x from %08x cur=%d entries=%d:", g_frame, tbl, g_cur_tbl, cur, k >= 0 ? g_tb[k].n : -1);
    if (k >= 0) for (int j = 0; j < g_tb[k].n; j++) { int it = g_tb[k].items[j];
      fprintf(g_log, " %d[sel=%08x]", it, (unsigned)r32(t, it * 0x10 + 8)); }
    fprintf(g_log, "\n");
    if (g_pend_item >= 0) {                                  /* the chosen entry opened this table (or went back) */
      char r[24]; snprintf(r, sizeof r, "open:%08x", tbl);
      if (g_pend_tbl != tbl) res_set(g_pend_tbl, g_pend_item, r, on(T_WALK) != 0);
      g_pend_item = -1;
    }
    int at = -1; for (int i = 0; i < g_sp; i++) if (g_stack[i] == tbl) at = i;
    if (at >= 0) g_sp = at + 1; else if (g_sp < 32) g_stack[g_sp++] = tbl;
    g_cur_tbl = tbl; g_calls = 0; g_target = -1; g_esc_calls = 0;
  }
  g_calls++;
  static int32_t last_cur = -1; static int cur_calls;
  if (cur != last_cur) { last_cur = cur; cur_calls = 0; }
  if (++cur_calls == 6 && g_calls > 30) { fprintf(g_log, "menusel f=%d %08x item %d:", g_frame, tbl, cur); log_texts(tbl); }
  int k = tb_find(tbl);
  if (k >= 0 && g_calls == 30) {
    log_texts(tbl);
    if (g_shots && !g_tb[k].shot) { g_tb[k].shot = 1; snprintf(g_shot_path, sizeof g_shot_path, "%s/menu_%08x.png", g_shots, tbl); }
  }
  if (on(T_WALK) && k >= 0) walk_step(tbl, cur, t, k);
}

/* ------------------------------------------------------------------ per frame: mission state, walker watchdog */
const char *re_probe_frame(int frame) {
  if (!on(T_MISSION | T_MENU)) return NULL;
  g_frame = frame;
  if (on(T_MISSION)) {
    static int32_t c4 = -1, e8 = -1;
    if (P14_00c810c4 != c4 || P14_00c810e8 != e8) {
      fprintf(g_log, "mission f=%d frame=%d c4=%#x e8=%d c81100=%d\n", frame, (int)P62_Frame, (unsigned)P14_00c810c4, (int)P14_00c810e8, (int)P14_00c81100);
      c4 = P14_00c810c4; e8 = P14_00c810e8;
    }
  }
  if (on(T_WALK) && g_last_menu_frame > 0 && frame - g_last_menu_frame > 600) {
    if (g_pend_item >= 0) res_set(g_pend_tbl, g_pend_item, "leave", 1);
    fprintf(g_log, "walk f=%d left the front end (last menu frame %d) — exit\n", frame, g_last_menu_frame);
    fflush(g_log); _Exit(0);
  }
  if (g_shot_path[0]) { static char p[512]; memcpy(p, g_shot_path, sizeof p); g_shot_path[0] = 0; return p; }
  return NULL;
}
