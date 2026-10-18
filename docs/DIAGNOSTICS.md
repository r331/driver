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
submit vertices after its originating handler has returned.

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
