# Performance notes (native build, v2.38)

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
| 1 | `game/ported86.c: pal8_hd` (via `game_pal8_tex`) + `platform/sdl/plat_texpack.c: re_texpack_load8` | synchronous PNG read + decode + compare + GL upload + mipmaps on the first draw of every (page, palette) pair | 35–40 ms per pair, 75–80 ms frames when cars appear; **the roadblock hitch** | **Opt-in fix:** `RE_TEXPACK_PRELOAD=1` creates all pairs listed by the level's `LEVELS\*.D3D` table while the level loads (`game_preload8`). Off by default (more load time and texture memory). Recommended next: decode on a worker thread / cache decoded RGBA, see §4. |
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

1. **Make HD texture loading asynchronous** (biggest win for the roadblock hitch): decode PNGs on a worker thread
   and draw with the original 8-bit texture until the HD one is ready; or ship pre-decoded / compressed textures
   (KTX/ASTC on Apple Silicon) so a first use is a single upload. Quick win available now: run with `RE_TEXPACK_PRELOAD=1`
   (measured above); make it the default once its load-time/memory cost is acceptable on the target machines.
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
* `RE_PROFILE` unset: one integer test per zone, nothing is timed. The profiler never reads or writes game state.

Related switches: `RE_TEXPACK_PRELOAD=1` (preload HD pairs at level load), `RE_GL_RING=1` (experimental stream
buffer), `RE_GL_CACHE=0` (disable the GL uniform cache), `RE_PTR_LINEAR=1` (old linear pointer lookups).
