# Capturing rendering problems

On this Mac, run the local app in diagnostic mode:

```sh
sh scripts/run_diagnostics_macos.sh
```

The launcher uses a window, the original graphics preset, no FBO, 2× draw
distance, and the sibling `driver-texpack` checkout when present. Override
individual settings with environment variables, for example
`RE_DRAW_DIST=1 RE_TEXPACK='' sh scripts/run_diagnostics_macos.sh`.

Drive to the black road. **Press Cmd+Shift+D** while the defect is visible.
On Linux/Windows the shortcut is Ctrl+Shift+D. The game captures the next
complete rendered frame, so stay in place until the capture is saved. The
shortcut is consumed by the platform and does not reach the game's controls.

The terminal prints the session and capture locations. By default these are
inside `Diagnostics/` in the game data/run directory. For this local setup:

```
work/run/Diagnostics/session-YYYYMMDD-HHMMSS-PID/
```

Set `RE_DIAG_DIR` to an existing writable parent directory to store sessions
elsewhere. Diagnostic mode is opt-in (`RE_DIAG=1`) and is not used by selftest.

Share the **entire session directory**, including the capture subdirectory.
It contains:

- `session.log`: build revision and dirty flag, compiler timestamp, selected
  rendering/reproduction environment variables, engine debug and platform messages.
- `graphics.log`: the existing GL vendor/version, graphics settings, framebuffer
  and shader errors, and window events (unless `RE_GFXLOG` overrides its location).
- `timeline.csv`: sampled frame, level frame, car position/heading/speed, camera
  position/mode, draw distance, scale, map slots, drawable/logical/content sizes,
  FBO state, and clipping counters.
- `config-at-start.dat`: the binary game settings at startup.
- Each `capture-*` directory: `screenshot.png`, `state.txt`, the last 600 frames
  in `frames.csv`, settings copies, `records.csv`, `clipping.csv`, and `draws.csv`.

`records.csv` identifies the level model and polygon record offsets and records
whether a record was processed (0), had no handler/a stub (1), or was culled by
the model's visibility/backface check (2). Offsets refer to the loaded model
arena, not native pointer addresses. `draws.csv` records the vertices actually
submitted to GL, their model/record context, texture handles, depth and alpha
test settings, blend state, UVs, reciprocal depth, and colors. Draws outside a
model handler use `ffffffff` for an unset model/record context; offset zero is
valid. A deferred renderer can also
submit vertices after its originating handler has returned. The added glTF facade
meshes use a separate indexed draw path: they appear in screenshots, but their
vertices and instance matrices are not currently included in `draws.csv`.
Use `DRIVER_DETAIL_LOG=1` to include facade matching and instance summaries in
the session log.

Clipping counters distinguish vertices behind the camera or beyond the
reciprocal-depth range, stale/missing camera data during fallback clipping,
far/fully-behind triangles, emitted clipped triangles, and empty clip polygons.
They are per rendered frame, not cumulative totals. `clipping.csv` identifies
the rejected fallback triangles with their projected coordinates and reciprocal
depth: reason 2 = stale/missing camera data, 3 = far/invalid depth, 4 = all
vertices behind the near plane. The far distance column is
the saved game distance; multiply it by `draw_multiplier` for the extended
main-view distance. Mirror distance remains separate.

Limits keep diagnostics usable during a long drive: 10 captures per session,
150,000 vertex rows and 150,000 record rows per capture, 16 MiB of session
messages, and one timeline row per 30 frames for up to 600,000 frames. Capture
state reports the recorded row counts. Existing sessions are never deleted.
The 600-frame history is held in memory until a capture; the timeline and
messages are flushed as they are written. A sudden process/OS crash can still
interrupt a screenshot or the current buffered vertex dump.

For scripted reproduction, `RE_DIAG_CAPTURE_FRAME=N` requests a capture after
frame N; the screenshot and vertex dump correspond to frame N+1. Use a larger
`RE_MAX_FRAMES` value so the capture can finish. This does not inject keys or
change the car position.

Only the explicitly listed rendering/reproduction environment variables and
game settings are collected; no full environment dump or desktop screenshot
is taken. Console messages written directly with `fprintf` are not all mirrored
into `session.log`; keep terminal output too if reproducing a crash.

## Marina black-road regression (2026-10-17)

The user capture at car position `(33568, 161, 397581)` exposed a full
per-texture Direct3D vertex batch. Each slot holds 4096 vertices; the old
triangle writer stopped at the limit and silently dropped the remaining
geometry, including nearby road tiles. The native triangle submission rounded
the incomplete tail down to 4095 vertices, making a full batch visible in
`draws.csv`. This was reproduced with the captured camera position and matrix.

`P33_EnsureRoom` now flushes queued batches before adding a complete triangle
or quad that would exceed capacity. It preserves the texture binding, palette
cache, and texture-stage state. `batch_rollovers` in frame telemetry and
`Vertex batch rollover` in the session log identify these flushes. Regression
tests cover the last complete triangle, rollover, both quad conversions,
invalid counts, and restoration of state.

Local before/after evidence is in `work/road-repro/marina-before.png` and
`work/road-repro/marina-after.png`. The temporary fixed-camera reproduction
code was removed from the game after verification.

## Facade motion regression (2026-10-17)

The capture near `(9508, 162, 393711)` showed the new facade overlays on the
right-hand building. Their placement was reconstructed each frame from rounded
screen positions and table-quantized reciprocal depth. Those small errors
changed the fitted mesh origin, scale, and grouping as the camera moved.

Native facade matching now uses the exact camera-space vertex coordinates
before projection, including vertices created by either near-clipping path.
The source must match the current vertex slot and transform tag; unmatched
vertices cannot reuse an earlier model's position. The existing wall projection
and UVs stay unchanged. An isolated replay of the captured camera movement
verified stable facade scales; selftests cover fractional depth, stale/mutated
vertices, and clipped-triangle coordinate propagation.

## macOS fullscreen presentation (2026-10-17)

A fullscreen test with FBO enabled showed a black display even though the
framebuffer readback and the existing selfcheck contained a valid image.
The renderer restored the scene FBO after composition and left it bound while
calling `SDL_GL_SwapWindow`. SDL requires the default draw framebuffer (0)
at the swap boundary on macOS; otherwise the rendered frame is not presented.

`plat_flip` now binds framebuffer 0 immediately before the swap and restores
the current scene target and viewport afterward, including after a resize or
fullscreen transition. FBO/MSAA settings remain available. A screenshot or
pre-swap pixel readback alone cannot verify presentation; check the actual
window during repeated fullscreen/windowed transitions.

Validation: reproduced a black fullscreen display before the change while GL
readback/selfcheck showed a valid image. After the change, verified the actual
fullscreen display, four scheduled window/fullscreen switches, and a second
launch with the enhanced preset and 4x MSAA. The user also confirmed fullscreen
works. Both automated tests pass.


## Draw distance hidden by the sky (2026-10-18)

Increasing `RE_DRAW_DIST` loaded and rendered more map cells, but the sky pass
then covered the distant scenery. The original sky used a finite depth bias
of 32767; that bias does not place it behind scenery at an extended draw range.
Disabling only the sky revealed the missing buildings and streetlights at the
same camera position, identifying the occlusion independently of map culling.

Native `P106_SkyModels` now scopes a far-depth override around its four sky
models. `P23_ConvVertexA/B` assign depth 1.0 for these vertices before batching,
retaining their screen position, reciprocal depth, UVs, and color. The previous
override is restored before subsequent passes. The hook build is unchanged.

Validation: identical-camera Miami runs at `(17760, -450, 400019)`, heading 3072,
show progressively farther buildings, palms, and streetlights at 1x, 2x, and 4x.
Before/after images are local in `work/road-repro/distance-4.png` and
`work/road-repro/distance-fixed-4.png`. Only 90 sky vertices changed in the 4x capture, all in their depth field
(from approximately 0.99805 to 1.0); the world geometry was identical.
The enhanced preset also passed with FBO, 4x MSAA, and the texture pack enabled.
Regression tests cover both conversion paths, zero/nonzero bias, preserved
UV/rhw/color, and restored ordinary depth. The temporary fixed-camera controls
were removed before the final build.
