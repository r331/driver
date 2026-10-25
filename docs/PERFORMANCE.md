# Performance notes (native build, v2.38–v2.39)

Scope: the native macOS / Linux build (`re/platform/native`, `re/platform/sdl`). The hook build (`RE_HOOK_BUILD`)
is unchanged: all instrumentation compiles to nothing there.

Question investigated: *"when the police set a roadblock (a barrier of police cars) the FPS drops significantly"*.

## 1. Likely cause of the roadblock FPS drop

**Confidence: high for builds running with the HD texture pack (`RE_TEXPACK`), medium without it.**

A roadblock puts several police cars on screen **at the same moment**, most of them seen for the first time in
the mission. The HD texture pack is resolved lazily, per *(8-bit texture page, palette slot)* pair, on the
**first draw** that binds that pair (`re/game/ported86.c: game_pal8_tex → pal8_hd → re_texpack_load8`):

1. read `pNNN_cKKKK.png` from disk,
2. decode it with stb_image (up to 1024×1024 RGBA),
3. compare it with the original page in that palette (`re_texpack_merge` check),
4. upload it to GL and build the mip chain (`plat_render.c: tex_upload / upload_variant`).

Measured in the headless Miami run (`RE_PROFILE=100`, 1280×720, llvmpipe): **each new pair costs ≈ 35–40 ms**,
and the frames where new cars enter the view show `hd_loads=2` with `hd_load ≈ 75–78 ms` and
`d.traffic ≈ 77–80 ms` (the whole cost sits inside `P128_TrafficDraw`). With a cold file cache (first run after
a restart) the same two pairs cost 310–380 ms, i.e. disk read + PNG decode dominate. At level start the worst frame was
2.4 s (16 HD pairs + facade detail meshes). A roadblock of 3–6 cop cars with their own palettes therefore
stalls one or a few frames by 100–250 ms — a visible hitch rather than a lower average.

The steady-state per-car cost is small by comparison: with ~30 cars in view `d.traffic` averages 1.7–2.7 ms and
car physics (`P142_CarsStep`) 0.05 ms per frame. Before this change, however, several per-car / per-collision
paths walked the process environment (`getenv`) and the pointer registry linearly every call (see §2), which made
the simulation and effects cost grow with the number of cars and colliding objects — exactly what a roadblock adds.

Without the HD pack the same first-use path exists but is cheaper (`pal8_make`: 256×256 conversion + upload, a few
ms per pair), so the spike is smaller; if the drop is still severe without the pack, profile with `RE_PROFILE`
(§5) and look at `tex_up` / `d.traffic` in the "worst frame" part.

## 2. Ranked hotspots

| # | Where | Why it is slow | Impact | Fix / status |
|---|-------|----------------|--------|--------------|
| 1 | `game/ported86.c: pal8_hd` (via `game_pal8_tex`) + `platform/sdl/plat_texpack.c: re_texpack_load8` | synchronous PNG read + decode + compare + GL upload + mipmaps on the first draw of every (page, palette) pair | 35–40 ms per pair, 75–80 ms frames when cars appear; **the roadblock hitch** | **Fixed in v2.39 (default):** asynchronous loading — read / decode / compare / CPU mipmaps on worker threads, original texture drawn meanwhile, GL upload on the main thread within a per-frame budget (§6). `RE_TEXPACK_ASYNC=0` restores the synchronous path. v2.38 opt-in alternative: `RE_TEXPACK_PRELOAD=1` creates all pairs listed by the level's `LEVELS\*.D3D` table while the level loads (`game_preload8`). |
| 2 | `game/reptr.c: re_addr / re_addr_known / re_ptr` | linear scan of the dynamic pointer registry `g_dyn` (grows to ~1300 entries in Miami) and of ~2400 data-image ranges on every address translation; called thousands of times per frame (particles depth-sort insert, car/object records) | `logic` 0.90 → 0.29 ms, `d.fx` 0.95 → 0.25 ms per frame | **Fixed:** sorted indexes + binary search (§3). |
| 3 | `getenv(...)` in per-car / per-wheel / per-collision / per-draw code: `ported137.c P137_DrawCar` (`RE_CARSKIP`), `ported136.c P136_DrawWheels`, `ported129.c P129_ObjBoxes`, `ported128.c P128_CopPath`, `ported142.c P142_CarsStep`, `ported132.c`, `ported89.c dd_extend`, `plat_render.c plat_draw_prim` (4× per draw call), `plat_set_render_state`, `plat_dd.c gs_upload` | `getenv` walks the whole environment each call; these sites run per car, per wheel, per collision box, per draw call | scales with cars × objects; part of the logic/draw gains above | **Fixed:** read once (`RE_GETENV_ONCE`, static caches). |
| 4 | `platform/sdl/plat_render.c: draw` | ~10 `glUniform*` + `glUseProgram` per draw call (200–250 draws/frame) even when nothing changed | small on llvmpipe (`gl_draw` ≈ 2.4 ms/frame); more relevant on drivers with expensive state validation (Apple's GL-on-Metal) | **Fixed:** uniform/program shadow cache (`RE_GL_CACHE=0` disables). |
| 5 | `platform/sdl/plat_render.c: draw` — `glBufferData` orphan per draw call | one buffer re-allocation per draw | not measurable on llvmpipe; potentially noticeable on macOS GL | **Experimental, off:** `RE_GL_RING=1` (single 4 MiB stream buffer + `glBufferSubData`). Pixel-identical in the test; needs measuring on an M1 before enabling by default. |
| 6 | `platform/sdl/plat_dd.c: gs_to_rgba` | mask shift recomputed per pixel and channel for 16-bit surfaces; full 640×480 surface converted and re-uploaded every frame in menus / FMV (`tex_px=307200`, `tex_up` 17–29 ms/frame on llvmpipe) | menus and 2D screens, not in-game | **Partly fixed:** mask shifts hoisted per surface. Remaining: upload only dirty rectangles / use a GL_UNSIGNED_SHORT_5_6_5 upload. |
| 7 | `game/ported86.c: game_pal8_tex` | `pal_match` + `pal_changed_check` (1 KiB `memcmp` each) on every PAL8 bind (~90 binds/frame) | < 0.1 ms/frame | Not changed (could cache by palette generation counter). |
| 8 | `platform/sdl/plat_detail.c: load_level` | facade glb meshes loaded synchronously at level start | ~0.9 s once per level | Not changed (load-time only). |

`swap` dominates the headless numbers (100–150 ms/frame) because the harness renders with Mesa llvmpipe
(software); it is not representative of an M1 GPU and was not optimised.

## 3. What was changed (v2.38)

All changes are behaviour-preserving refactors (caching, hoisting, indexed lookup) or opt-in flags:

* `re/game/reptr.c` — `in_gvar_range`: the data-image ranges are merged once into sorted disjoint intervals and
  binary-searched (same yes/no answer). `re_ptr` / `re_addr` / `re_addr_known`: sorted indexes of `g_dyn` by game
  address and by native pointer, rebuilt lazily after every register / re-register / unregister. The original
  scans return the *first* match; the index is used only when a rebuild proves that no two entries overlap
  (then at most one entry can match), otherwise the original linear scan runs. `RE_PTR_LINEAR=1` restores the
  linear scans for comparison.
* `re/game/reprof.h` — `RE_GETENV_ONCE(name)`, used in the debug-switch checks of `ported128/129/132/136/137/142/89.c`
  (native-only `#ifndef RE_HOOK_BUILD` blocks; the `RE_*` debug variables are never changed at run time).
* `re/platform/sdl/plat_render.c` — getenv once in `plat_draw_prim` / `plat_set_render_state`; uniform and
  program shadow cache in `draw` (`use_prog`, `g_uc`, reset on context attach); optional `RE_GL_RING`.
* `re/platform/sdl/plat_dd.c` — `mask8p` (precomputed shift, identical result to `mask8`); `RE_ATDBG` read once.
* `re/game/ported86.c` — `RE_TEXPACK_PRELOAD=1` (off by default) preloads HD pairs at level load.
* Profiler: `re/game/reprof.h`, `re/platform/native/reprof.c`, zones in `ported132.c` (`P132_GameLogic`,
  `P132_GameDraw`), `ported137.c`, `ported86.c`, `plat_render.c`, `plat_dd.c`, `plat_detail.c`.

### Verification

* Release and RelWithDebInfo builds: 0 warnings; `ctest`: selftest + inputtest pass.
* Deterministic comparison (headless Miami survival run, `RE_FIXED_DT=1`, scripted keys, 1500 frames,
  `RE_CARDBG=5` car-state dump every 5 frames): the car-state dumps of the old and new binaries are byte-identical,
  and the final screenshots are pixel-identical (also with `RE_GL_RING=1`).

### Measured (headless, llvmpipe, 1280×720, average ms per frame, frames 1201–1400, ~25–33 cars)

| zone | before | after |
|------|--------|-------|
| logic (`P132_GameLogic`) | 0.90–0.94 | 0.25–0.29 |
| d.fx (event models, particles, sprites) | 0.86–0.95 | 0.25 |
| draw (CPU side, without swap) | 12.2–12.3 | 10.5–10.7 |
| d.map | 7.0 | 6.3 |

The HD first-use spikes are unchanged by default. With `RE_TEXPACK_PRELOAD=1` (same run, same frames) they are gone:

| frames 1101–1400, slowest frame's | default | `RE_TEXPACK_PRELOAD=1` |
|-----------------------------------|---------|------------------------|
| `hd_load` during play | 310–380 ms (2 pairs, cold cache; ≈ 75 ms warm) | 0 (no loads in play) |
| `d.traffic` | 316–381 ms | 0.3–7 ms |
| level load, extra | — | 31 pairs ≈ 3.1 s once |

Car-state dump and final screenshot are identical with the flag as well.

## 4. What remains (recommendations)

1. ~~Make HD texture loading asynchronous~~ — done in v2.39 (§6). Still possible: ship pre-decoded / compressed textures
   (KTX/ASTC on Apple Silicon) so a first use is a single cheap upload and the switch to HD happens a frame after first use;
   make the remaining load-time attach paths (`P86_GameAttachEmul8` / `P86_GameAttach16`, devices without PAL8 and 16-bit
   pages, all at level load) asynchronous as well.
2. Precompute mip chains offline (or use `glGenerateMipmap`) instead of building them on the CPU in `upload_variant`.
3. Batch draw calls: `P150_FlushTris` / `plat_draw_tris` issue 200–250 small draws per frame; grouping by texture
   and state would help Apple's GL-on-Metal layer most. Measure `RE_GL_RING=1` on an M1 and make it the default
   if it helps.
4. 2D/menu surfaces: upload only the dirty rectangle, avoid the per-pixel RGBA conversion for 16-bit surfaces.
5. `game_pal8_tex`: replace the per-bind 1 KiB palette `memcmp`s with a palette generation counter.

## 5. Using the profiler

```
RE_PROFILE=120 ./driver --data <game dir>      # every 120 displayed frames
```

`RE_PROFILE=N` prints, every N displayed frames, to stderr and `driver_gfx.log`:

```
[prof] frames 1201..1300 avg ms: frame=… logic=… l.cars=… l.traffic=… l.map=… draw=… d.map=… d.player=…
       d.traffic=… d.fx=… d.hud=… gl_draw=… tex_up=… swap=… hd_load=… detail_load=…
       | per frame: draws=… verts=… tex_up=… tex_px=… tex_var=… surf_up=… pal8=… detail=… ticks=… cars=… hd_loads=… pal_inval=…
       | worst frame … ms: <zones and counters of the slowest frame in the window>
```

* Zones include their nested zones (e.g. `d.traffic` contains the `hd_load` of a car drawn for the first time).
  `logic` sums all game ticks of the displayed frame (`ticks`).
* Zones: `frame` (flip to flip), `logic` (`P132_GameLogic`), `l.cars` (`P142_CarsStep`), `l.traffic`
  (traffic + chase + car sounds), `draw` (`P132_GameDraw` without swap), `d.map` (city), `d.player`, `d.traffic`
  (all other cars incl. cops), `d.fx`, `d.hud`, `gl_draw` (CPU side of GL draws), `tex_up` (texture uploads),
  `swap` (compose + swap, i.e. GPU wait), `hd_load` (HD-pack first-use loads), `detail_load`.
* The "worst frame" part is the one to read for hitches such as a roadblock appearing.
* v2.39: zone `hd_up` — GL uploads of finished asynchronous HD pairs (after the swap, so it is counted in the next frame);
  counters `hd_req` (pairs queued) and `hd_upn` (pairs uploaded). `hd_load` / `hd_loads` now count only synchronous loads
  (`RE_TEXPACK_ASYNC=0`, `RE_TEXPACK_PRELOAD=1`, or no worker threads).
* `RE_PROFILE` unset: one integer test per zone, nothing is timed. The profiler never reads or writes game state.

Related switches: `RE_TEXPACK_ASYNC=0` (v2.39: synchronous HD loading as before), `RE_TEXPACK_UPLOAD_MS=N`, `RE_TEXPACK_THREADS=N`,
`RE_TEXPACK_PRELOAD=1` (preload HD pairs at level load), `RE_GL_RING=1` (experimental stream
buffer), `RE_GL_CACHE=0` (disable the GL uniform cache), `RE_PTR_LINEAR=1` (old linear pointer lookups).

## 6. v2.39: asynchronous HD texture loading (default)

### Design

* **Where:** `re/platform/sdl/plat_texpack_async.c/.h` (queue + workers), `plat_render.c: plat_tex_prepare /
  plat_tex_create_prepared` (CPU part of `tex_upload` split from the GL part), `re/game/ported86.c: game_pal8_tex /
  pal8_async_done` (game side), `plat_render.c: plat_flip` calls `re_tpa_pump()` after the swap.
* **Cache miss** in `game_pal8_tex` (first draw of a (page, palette) pair, the key is page + palette slot): the reference page
  in that palette (256×256 RGBA) is built on the main thread as before, then `re_tpa_request` copies it together with the pack
  directory and level name into a free slot of a fixed pool of 64 requests (bounded queue; when full, the pair is asked for
  again on a later draw). The pair is marked pending (`g_pend8`) with a unique tag — requests are deduplicated. The function
  returns 0, so `plat_set_texture` keeps binding the original surface texture.
* **Workers** (`RE_TEXPACK_THREADS`, default 2, SDL threads — macOS, Linux, Windows; no new link dependency, SDL2 and
  Threads were already linked) take the oldest request and run `re_texpack_load8_tol` (file read + stb_image decode; the
  page-check tolerance is returned instead of the shared `re_texpack_last_tol` state), `re_texpack_compare_rgba` and
  `plat_tex_prepare` (partial/binary alpha flags + the `re_gfx_mip_box` chain of `upload_variant` mode 0). No GL calls, no game
  state: only the request's own copies. stb_image keeps its failure reason thread-local; `RE_LOG` is mutex-protected.
* **Main / GL thread:** `re_tpa_pump()` once per displayed frame, after the swap, hands finished requests (oldest first) to
  `pal8_async_done`, which uploads with `plat_tex_create_prepared` (only `glTexImage2D` per level + parameters) and stores the
  texture as the pair's; missing / rejected files are remembered in `g_miss8` exactly as the synchronous path does (same
  `[texpack] … отклонён` log). Upload budget: `texpack_upload_ms` / `RE_TEXPACK_UPLOAD_MS` (default 2 ms), at least one
  texture per frame (`0` — exactly one per frame); missing / rejected results cost nothing and are always handed over.
* **Same pixels:** `plat_tex_create_prepared` produces the same levels, flags and alpha-test source as
  `plat_tex_create(w, h, rgba)`; if the mipmap / dilate settings changed between prepare and upload, it falls back to
  `plat_tex_create`.
* **Invalidation:** a result is used only while its pair is still pending with the same tag. `pal_changed_check` (palette slot
  contents changed — palette-dependent variants), `pal8_free` (page freed / re-captured) and `P86_NativeReset` (level change)
  clear the pending flags, so late results are dropped; `P86_NativeReset` also calls `re_tpa_cancel()` (queued and finished
  requests freed at once, running ones freed when they finish). Quit: `re_tpa_shutdown` (atexit) stops and joins the workers.
* **Flags:** `RE_TEXPACK_ASYNC=0` / `texpack_async = 0` — the old synchronous load in `game_pal8_tex`. `RE_TEXPACK_PRELOAD=1`
  still loads every listed pair synchronously while the level loads (`game_preload8` → `pal8_hd`), so those pairs never reach
  the queue; pairs outside the level's list still go through the asynchronous path. If the worker threads cannot be
  created, loading falls back to synchronous.
* **Not changed:** the render-check path (`pal8_make`, `texpack_try`) and the load-time attach paths of the game path
  (`P86_GameAttachEmul8`, `P86_GameAttach16`) stay synchronous — they run while a level loads.

### Measured (same harness as §3: headless Miami survival, `RE_FIXED_DT=1`, scripted keys, 1500 frames, 1280×720,
llvmpipe, `RE_CARDBG=5 RE_PROFILE=100`, page cache dropped before each run)

| frames 1101–1400, slowest frame of each 100-frame window | v2.38 (sync) | v2.39 async (default) |
|-----------------------------------------------------------|--------------|-----------------------|
| `d.traffic` (`P128_TrafficDraw`) | 369 / 373 / 331 ms | 1.8 / 1.1 / 2.7 ms |
| `hd_load` in that frame | ≈ 330–370 ms (cold cache) | 0 (none on the draw path) |
| whole worst frame | 625 / 581 / 550 ms | 206 / 243 / 188 ms (≈ all `swap`, llvmpipe) |
| level-start worst frame | 12.0 s (incl. 2.8 s of HD loads) | 2.0 s (no HD loads; 1.1 s facade meshes) |

The HD uploads moved to `hd_up`: ≈ 2–5 ms per 1024×1024 upload on llvmpipe (estimated from the window totals: 20 uploads
≈ 101 ms in frames 1001–1100, 10 uploads ≈ 21 ms in 1101–1200), never in a worst frame. With `RE_TEXPACK_ASYNC=0` the same build behaves as v2.38
(`hd_load` 100–110 ms / `d.traffic` 105–115 ms in the worst frames of that run, warmer cache).

### Verification

* Car-state dump (`RE_CARDBG=5`, `[car]` lines) md5 `6d56abdb` — identical for v2.38, v2.39 async and v2.39
  `RE_TEXPACK_ASYNC=0`: the simulation never depends on textures.
* `RE_TEXPACK_PRELOAD=1` with the v2.39 build: car dump `6d56abdb`, screenshot `e5feef58`, no asynchronous requests
  during play (`hd_req` 0 — every pair was preloaded).
* Final screenshot md5 `e5feef58` — identical for all of them: with async, every pair is uploaded long before frame 1500. A
  screenshot taken while a pair is still pending would legitimately show that car's original texture.
* Release and RelWithDebInfo: 0 warnings; `ctest` passes; selftest covers the queue (accepted / missing / rejected results,
  cancel) and the new `driver.cfg` keys.
