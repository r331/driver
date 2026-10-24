/* reprof.h — native-only frame profiler.  RE_PROFILE=N prints per-zone averages every N displayed frames
   (stderr and driver_gfx.log).  A zone's time includes nested zones.  Counters are per-frame event counts.
   Everything compiles to nothing in the hook build, and the profiler never reads or writes game state,
   so it cannot change the simulation.  See docs/PERFORMANCE.md. */
#ifndef REPROF_H
#define REPROF_H
enum {
  RP_FRAME,       /* plat_flip to plat_flip (wall time of a displayed frame) */
  RP_LOGIC,       /* all P132_GameLogic ticks of the frame */
  RP_L_CARS,      /* P142_CarsStep (physics, car-car collisions) */
  RP_L_TRAFFIC,   /* P133_TrafficTick + chase + car sounds */
  RP_L_MAP,       /* P89_DrawMap(0) in logic (map streaming) */
  RP_DRAW,        /* P132_GameDraw without the swap */
  RP_D_MAP,       /* P89_DrawMap(1): the city */
  RP_D_PLAYER,    /* P137_DrawCar for the player */
  RP_D_TRAFFIC,   /* P128_TrafficDraw + P150_FlushTris: every other car */
  RP_D_FX,        /* event models, shadows, sky, sprites, glows, particles */
  RP_D_HUD,       /* mirror + HUD */
  RP_GL_DRAW,     /* inside plat_render draw(): state + vertex upload + glDrawArrays (CPU side) */
  RP_TEX_UPLOAD,  /* texture uploads: surface conversion, mipmaps, glTexImage2D */
  RP_SWAP,        /* plat_flip: compose + swap (waits for the GPU) */
  RP_HD_LOAD,     /* HD texture-pack PNG loads on first use of a (page, palette) pair, incl. compare + upload */
  RP_DETAIL_LOAD, /* facade detail meshes (glb) of a level, loaded with the level */
  RP_ZONES
};
enum {
  RC_DRAWS, RC_VERTS, RC_TEX_UPLOADS, RC_TEX_PIXELS, RC_TEX_VARIANTS, RC_SURF_UPLOADS, RC_PAL8_BINDS,
  RC_DETAIL_DRAWS, RC_LOGIC_TICKS, RC_CARS_DRAWN, RC_HD_LOADS, RC_PAL_INVAL, RC_COUNTERS
};
#ifndef RE_HOOK_BUILD
#include <stdlib.h>
/* RE_GETENV_ONCE(name) — getenv read once per call site (v2.38): debug switches in per-car / per-wheel / per-collision
   code used to walk the environment every call.  The RE_* variables are never changed while the game runs. */
#define RE_GETENV_ONCE(name) (__extension__({ static int re_ge_done_; static const char *re_ge_val_; \
  if (!re_ge_done_) { re_ge_val_ = getenv(name); re_ge_done_ = 1; } re_ge_val_; }))
extern int re_prof_on;   /* 0 — off (default); set from RE_PROFILE at start */
void re_prof_begin(int zone);
void re_prof_end(int zone);
void re_prof_count(int counter, long n);
void re_prof_frame(void);   /* once per displayed frame, from plat_flip */
#define RP_BEGIN(z) do { if (re_prof_on) re_prof_begin(z); } while (0)
#define RP_END(z)   do { if (re_prof_on) re_prof_end(z); } while (0)
#define RP_COUNT(c, n) do { if (re_prof_on) re_prof_count((c), (long)(n)); } while (0)
#else
#define RP_BEGIN(z) ((void)0)
#define RP_END(z)   ((void)0)
#define RP_COUNT(c, n) ((void)0)
#endif
#endif
