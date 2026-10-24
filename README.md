**English** | [Русский](README.ru.md)

# Driver (PC, 1999) — decompilation and C port

A reconstruction of **Driver** (Reflections Interactive / GT Interactive, PC, 1999) as C source code,
based on the original executable:

- `Game.exe` (installed from the disc as `DRIVER.EXE`), PE32, image base 0x400000, built **1999-09-10** 16:35:21 UTC, MSVC 6.0 linker;
- MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`, SHA1 `06ae86374f5df850c678583b556a9a4bc9811575` (details in [docs/binary-info.md](docs/binary-info.md)).

**Game files and `Game.exe` are not included in the repository.** To run it you need your own copy of the game (the Driver PC CD).

One code base (`re/`), two build targets:
- **native** — a standalone program on SDL2 + OpenGL 3.3 that uses only the game data (`Data_Files`);
- **hook** — a `DINPUT.dll` proxy for the original `Game.exe`: ported functions replace the original ones right inside the running game
  (so every function can be checked against the original).

## Status

**Function porting:** according to [docs/functions.csv](docs/functions.csv), **3292 of 3292** non-CRT Game.exe functions have `status=ported`
(the table lists 3632 functions in total; the 340 MSVC CRT functions are not ported — in native they are replaced by libc and `re/platform/native/crt_msvc.c`).

To count:

```sh
python3 -c "import csv; r=[x for x in csv.DictReader(open('docs/functions.csv')) if x['module']!='CRT']; print(sum(x['status']=='ported' for x in r), 'из', len(r))"
```

**Native as a game — v2.36** (verified with `RE_KEYS` scripts and a real X11 keyboard (xdotool) under Xvfb, Linux arm64; build, selftest and inputtest on macOS arm64 in CI):
- working: intro screens and the main menu, **Take A Ride** mode in Miami — driving around the city (map block streaming), traffic, collisions, HUD (Damage/Felony, radar, speedometer);
- car controls: throttle, brake/reverse, handbrake, hard steering, camera switching (bonnet view), Esc pause with a menu (Continue / Restart / Sound Setup / Gfx Details / Film Director / Quick Replay / Show Map / Exit) — see "Controls";
- sound: DirectSound is emulated by our own mixer (SDL_audio or WAV capture), engine and ambient noises are audible, soft limiter — no clipping; music — CD-audio emulation (v2.22, tracks from files ripped from your disc — see "CD music");
- pedestrians: 12–16 active, the model is drawn (verified with a pedestrian standing in front of the car); in a normal run they spawn ~34,500 units from the player but are drawn only within 15,000 — drive closer to see them;
- cops: patrol car (limit 4); v2.12 — pursuit works: when a cop is near, Felony rises to its cap, up to 4 cops join in, chase and ram; v2.34 — the patrol finds the player on its own and follows (without the RE_COPNEAR debug switch): fixed the x87 rounding mode (Game.exe rounds toward zero), which made cops fail to find a route and stop; in Survival the cops give chase;
- Undercover: the garage interview starts; with the interview skipped (RE_SKIP_INTERVIEW=1, like a cheat) — the motel, the answering machine (←/→ — button, Enter — action, "accept" — mission) and the **first Miami mission** "Get to the bank." (completion not verified);
- the H horn is audible (v2.12: a 3D source at the car);
- v2.14: native resolution — the game's 4:3 frame fits a window/screen of any size (Retina, 1080p, 2560×1600) with side bars; 3D is rasterized at screen resolution; fullscreen by default on macOS; driving with the arrow keys and space (handbrake) in addition to the original keys;
- v2.15: any aspect ratio (Hor+) — on a wide screen (16:10, 16:9, 21:9, 32:9) the vertical angle matches the original and more of the city is visible at the sides; HUD is anchored to the screen edges, menus are centered at 4:3; see "Resolution and aspect ratio";
- v2.16: graphics enhancements — MSAA (2/4/8x, multisampled FBO) with alpha-to-coverage for palms and fences, FXAA, render_scale 0.5–2.0 (SSAA), halo-free mipmaps, anisotropic filtering up to 16x, filtering choice, crisp HUD (sharp-bilinear), vsync/FPS limit, gamma/brightness; `driver.cfg` file and original/enhanced presets — see "Graphics";
- v2.17: HD textures — texture pages replaced with upscaled images (PNG 1024×1024) from your own pack, `RE_TEXPACK`/`texpack` — see "HD textures";
- v2.18: HD textures for 8-bit (paletted) pages too — one file per "page × palette" pair; replacement now works in the game itself (previously only in the render test);
- v2.19: draw distance — `draw_distance` (multiplier 1.0–4.0, 2.0 in `enhanced`): distant blocks become visible, game logic is unchanged — see "Graphics";
- v2.22: CD music — CD-audio drive emulation: tracks `Music/TrackNN.wav|flac|ogg|mp3` or a `.cue/.bin` image, silence without files; looping and volume as in the original — see "CD music";
- v2.34: music is picked up automatically from the HD pack (`<texpack>/Music`) if there is no `Music/` in the data directory;
- v2.33: PlayStation-style dynamic music (optional): your own 16 files in `Music/dynamic/` — each city has day/night × Drive/Chase, crossfading to Chase during a cop pursuit and back — see "CD music";
- v2.23: fixed a grey polygon over the sky (usually top left) — flat/Gouraud polygons of the near set are clipped at z = 1, vertices behind the camera no longer fly off into a screen corner;
- v2.35: all split aliases of the data image have been merged (0 left): every Game.exe address has a single object in native. Event-script checks that were previously missing now work: "You lost your target" by distance from the target (004f5012), freeing the event list between missions, script advancement for six commands, dust, menu item highlighting; Take A Ride and Survival are unchanged (byte for byte) — see docs/NATIVE_GAPS.md, section «Исправлено в v2.35» ("Fixed in v2.35");
- v2.36: the garage interview stopwatch (dial and case) and the mission clock digits (Miami) in the HD pack have been redrawn by a neural network — crisp, with a smooth edge; the `hud_hd` pack variant, off with `RE_TEXPACK_HUD=0` — see "HD textures";
- not verified / not working: night and the other cities (SF, LA, NY); FMV cutscenes are skipped.

Details: [docs/NATIVE_GAPS.md](docs/NATIVE_GAPS.md) (native gaps, debug switches), [docs/PLATFORM_PLAN.md](docs/PLATFORM_PLAN.md) (step-by-step porting log),
[re/README.md](re/README.md) (porting rules and version history).

## Directory layout

How the code is organized and how the two build targets relate — [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md); index of the `re/game/` modules — [docs/MODULES.md](docs/MODULES.md).

| Directory | Contents |
|---|---|
| `re/game/` | ported game modules in C (`ported*.c`, menus, Director, generated Game.exe `.data` tables); no WinAPI |
| `re/platform/sdl/` | SDL2/OpenGL platform implementation: window, renderer (DirectDraw/D3D/Glide emulation on GL 3.3), input (DirectInput → SDL), sound stubs |
| `re/platform/win32/` | hook build: `DINPUT.dll` proxy, Game.exe function interception (JMP rel32), `install.c` — list of replaced functions |
| `re/platform/native/` | native entry point (`main.c`), stubs for unported code, glue, MSVC CRT replacements |
| `re/tests/` | self-test of the ported modules (`driver --selftest`, run via ctest), render and sound tests |
| `docs/` | `ARCHITECTURE.md` (code map), `MODULES.md` (module index), `DEAD_CODE_AUDIT.md` (suspicious code left in place), `functions.csv` (all functions, names, modules, status), `binary-info.md`, plans and porting log |
| `tools/` | Python generators: data tables from Game.exe (`gen_*.py`), thunk markup, module splitting, `pedump.py` |
| `scripts/` | Ghidra scripts (export of functions and pseudo-C, applying names, string cross-references) and their runners |
| `src/` | Ghidra pseudo-C split by the original's modules (`Director.c`, `MScript.c`, `frontend/` …) — reference material, not part of the build |

## Building

The commands below are run from the repository root. `re/build.sh native` does the same steps (build directory `re/build-native/`).

> Built and verified on **Linux arm64** (Debian 13, gcc 14, SDL 2.32, CMake 3.31) in a clean clone.
> **Not verified** on Linux x86_64 or on a real Mac.

### Linux (verified path)

```sh
sudo apt-get update
sudo apt-get install -y build-essential cmake libsdl2-dev libgl-dev libegl-dev libosmesa6-dev
# optional: xvfb (headless runs), gcc-mingw-w64-i686 (hook build), unshield (extracting data from the CD)

cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release
cmake --build build-native -j
(cd build-native && ctest --output-on-failure)     # selftest
```

The result is `build-native/driver`. `libosmesa6-dev` is only needed for the offscreen render test in selftest: if OSMesa is not found,
CMake uses `plat_render_nogl.c` and the render test is skipped. The program is not linked against libGL — GL functions are obtained via `SDL_GL_GetProcAddress`.
The system SDL2 Classic does not see the Steam Controller (2026) — for it, build with `-DRE_SDL3_COMPAT=ON`; packages and udev rules are in the "Gamepads on Linux" section below.

### macOS (Apple Silicon)

Verified in GitHub Actions CI: the `macos-14` runner (arm64, Apple clang 15) — Release build, `ctest` (selftest),
a run without data, and a `Driver.app` build with bundled SDL ([.github/workflows/macos.yml](.github/workflows/macos.yml)).
Roman ran v2.13 on an M1 Mac: the window and picture were there, but "the controls don't work". The exact cause was not established (it did not
reproduce on a Mac); v2.14 fixed everything that could have caused it (see below) and added an input log, `RE_INPUTDBG=1`.

**macOS: keys, resolution, input log (v2.14)**

- Driving: **arrow keys** (↑ throttle, ↓ brake/reverse, ←/→ steering), **space** — handbrake; the original keys work too
  (`'` throttle, `/` brake, `Z`/`X` steering, `Enter` handbrake). In menus the arrows still move between items, `Enter` selects, `Esc` — back/pause.
  Keys are read by physical position (scancode), so the keyboard layout (Russian, etc.) does not matter. `RE_ARROWKEYS=0` — no arrow keys while driving.
- Fullscreen by default (the whole display, at native Retina resolution); **Cmd+Enter** (or Alt/Option+Enter) toggles window/fullscreen.
  `RE_WINDOWED=1` — start in a window, `RE_RES=1440x1080` — window size in points, `RE_FULLSCREEN=1` — force fullscreen.
  3D is drawn at full screen resolution and across the full width (v2.15, Hor+ — see "Resolution and aspect ratio"), menus are 4:3 centered,
  the HUD sits at the screen edges, nothing is stretched. Cmd+Q or closing the window quits.
- If the keys don't work: launch from Terminal with
  `RE_INPUTDBG=1 ./Driver.app/Contents/MacOS/Driver` (or `RE_INPUTDBG=1 ./driver --data …`), press some keys in the menu and while driving,
  quit the game and send the file **`~/Library/Logs/driver_input.log`** — it contains the SDL version, the event-loop thread, window/focus events,
  every key press (scancode → DIK) and what the game saw of it.

```sh
brew install cmake sdl2          # Homebrew installs sdl2-compat (the SDL2 API on top of SDL3)
cd re && ./build.sh native       # -> re/build-native/driver, then ctest
./build-native/driver --data /path/to/run-dir   # see "Running"
# app: Driver.app (SDL2 from Homebrew; to move it to another Mac, see the CI artifact with bundled SDL)
cmake -S . -B build-app -DCMAKE_BUILD_TYPE=Release -DRE_MACOS_BUNDLE=ON && cmake --build build-app -j
```

The `APPLE` branch in `re/CMakeLists.txt`: SDL2 is looked up in Homebrew (`/opt/homebrew`, `/usr/local`), the OpenGL framework is not linked
(GL functions come via `SDL_GL_GetProcAddress`), the context is 3.3 core forward-compatible, and the offscreen render test (OSMesa) is Linux-only.
Game data (`Data_Files` containing `FSIN.DAT`) is searched for in: `--data <path>`, `./Data_Files`, next to the binary, in `Driver.app/Contents/Resources/Data_Files`
or next to `Driver.app` — details in [re/README_macOS.txt](re/README_macOS.txt). The ready-made `Driver.app` from CI (artifact `driver-macos-arm64`)
is only ad-hoc signed: on first launch, right-click → "Open", or run `xattr -dr com.apple.quarantine Driver.app`.

**Installer for another Apple Silicon Mac:** `scripts/package_macos.py` builds a self-contained DMG with your original game data and optional HD textures. Install by dragging Driver.app to Applications; saves stay in Application Support. The local HD installer is `dist/Driver-AppleSilicon.dmg`. See [packaging and verification](docs/MACOS_DMG.md).

**What runs in CI** (there are no game files there): `ctest -L nodata` — `driver --inputtest` (v2.14: event loop on the main thread —
`pthread_main_np`, a key event via `SDL_PushEvent` → the game's event parsing → DIK, Cmd+Enter, arrow-key driving bits, frame fitting)
and `driver --selftest`, unit checks of the ported functions
on synthetic data (the real-level test `RE_REAL_LEVEL` and the OSMesa render snapshot are skipped on macOS); Linux x86_64 —
the same plus the `DINPUT.dll` hook build and (v2.32) the `native-sdl3` job: a build with `RE_SDL3_COMPAT=ON`, ctest and a portability check of `driver` + `sdl-runtime/` ([.github/workflows/linux.yml](.github/workflows/linux.yml)).

## Resolution and aspect ratio

Since v2.15 the native build draws 3D across the full width of a screen of any aspect ratio (**Hor+**): the vertical field of view matches the original
(focal length 384 at a height of 480, ≈ 64°), and the horizontal one grows with the aspect — ≈ 96° at 16:9 instead of 79.6° at 4:3, ≈ 112° at 21:9, ≈ 131° at 32:9.
The image is not stretched: the game's logical frame is (480·aspect)×480, and 3D is rasterized at native resolution (in pixels on Retina).

- `RE_ASPECT=auto` (default) — from the window/screen size; `RE_ASPECT=4:3` — as in the original (a 4:3 frame with side bars, like v2.14);
  `RE_ASPECT=21:9` (any `W:H` or a number like `2.35`) — a frame of that aspect, the rest of the window is bars.
- A screen narrower than 4:3 (portrait, 5:4) — a 4:3 frame fitted to the width with bars at the top and bottom (letterbox); the angle does not change.
- Menus, the frontend and the pause menu are 640×480 centered with bars (pillarbox). The in-game HUD is anchored to the edges: Damage/Felony — top left,
  radar and speedometer — bottom right, mode counters — top right, the mission clock and messages — centered.
- Culling is widened in code: the 3D clip window, the frustum side planes, the map-cell walk (merging neighbouring
  `FRUSTRUM.DAT` sectors — the file itself is unchanged), on-screen checks for sprites/lights. The hook build (DINPUT.dll) behaves like the original (4:3).
- Verified on Linux under Xvfb (1920×1080, 2560×1600, 3440×1440, 5120×1440, 1080×1920); not yet on a real Mac.

## Graphics

Since v2.16 the native build renders the game frame into an offscreen buffer (FBO) and presents it to the window with a post-pass. Game logic is unchanged
(`RE_FIXED_DT` determinism is the same); the hook build (DINPUT.dll) renders like the original.

- **Anti-aliasing:** MSAA 2/4/8x — a multisampled FBO with resolve (not the default framebuffer); alpha-to-coverage for alpha-tested textures
  (palms, fences, trees, barriers) — the transparency edge is smoothed along with MSAA; FXAA — a post-pass (shader in code);
  `render_scale` 0.5–2.0 — frame resolution relative to the window (2.0 = SSAA 4x, 0.5 — for weak machines; the HUD is drawn in the same frame).
- **Textures:** custom mipmaps for the game's texture pages: the colour of visible neighbours is carried into transparent pixels (dilation), downscaling
  is alpha-weighted, and chroma-key textures keep their share of visible pixels — no black/magenta halos and no "balding" palms in the distance.
  The game draws ARGB1555 pages both with "visible at alpha 0" (ALPHAFUNC LESS) and with the usual semantics, so the processed copy
  is built for whichever semantics the texture is drawn with (drawing without an alpha test uses the source image).
  Anisotropic filtering up to 16x (if the driver provides `GL_EXT/ARB_texture_filter_anisotropic`; macOS does); 3D filtering:
  `nearest` (original pixelated look), `linear`, `trilinear`.
- **HUD/menus/fonts:** `sharp-bilinear` — solid colour inside a texel, a one-screen-pixel transition at its border (menu fonts don't blur
  when scaling 640×480 → 1080p/Retina); `linear` or `nearest` are also available.
- **Other:** vsync on/off/adaptive, FPS limit, gamma and brightness (post-pass), light sharpening (`sharpen`).
- If something is unsupported (no MSAA at the requested level, no anisotropy, FBO cannot be created) — it is downgraded/disabled with a `[gfx]` message on stderr, without crashing.

**Presets:** `enhanced` (default) — MSAA 4x + alpha-to-coverage, 16x anisotropy, trilinear, mipmaps, dilation, sharp HUD, FXAA off;
`original` — like v2.15: bilinear without mipmaps, no anti-aliasing, linear HUD.

**The `driver.cfg` file** (first one found): `$RE_CFG`; next to the binary; macOS — `~/Library/Application Support/Driver/driver.cfg`;
Linux — `${XDG_CONFIG_HOME:-~/.config}/driver/driver.cfg`. `RE_*` variables take precedence over the file. A full annotated example is in `re/driver.cfg.example`:

```ini
preset       = enhanced    # enhanced | original
msaa         = 4           # 0 | 2 | 4 | 8
a2c          = on          # alpha-to-coverage (with msaa)
fxaa         = off
aniso        = 16          # 1..16
mipmaps      = on
filter       = trilinear   # nearest | linear | trilinear
hud_filter   = sharp       # sharp | linear | nearest
render_scale = 1.0         # 0.5..2.0
draw_distance = 2.0        # 1.0 (original) .. 4.0
vsync        = on          # on | off | adaptive
fps_limit    = 0           # 0 — unlimited
gamma        = 1.0
brightness   = 1.0
aspect       = auto        # auto | 4:3 | 21:9 …
fullscreen   = 1
windowed_res = 1600x900
```

**Gamepads / Steam Controller (2026):** native controls work in menus and while driving. On this Mac, the 2026 controller is detected over USB/Puck with SDL3 3.4.18 through SDL2-compat 2.32.74. Build with the pinned modern runtime (the first configure downloads the upstream archives):

```sh
cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release -DRE_MACOS_BUNDLE=ON -DRE_SDL3_COMPAT=ON
cmake --build build-native -j8
```

The modern SDL libraries are built into `Driver.app/Contents/Frameworks`; the system SDL installation stays unchanged. `RE_SDL3_COMPAT=OFF` uses the existing system SDL2. The older SDL2 Classic driver does not support the 2026 controller's native USB/Puck protocol. Controller discovery starts after SDL creates the window, and supports connecting or reconnecting while the game is running.

| Controller | Driving | Menus |
|---|---|---|
| Left stick / D-pad left/right | Steer | Navigate |
| RT / LT | Throttle / brake and reverse | — |
| D-pad up/down | Throttle / brake and reverse | Navigate |
| A / B | Handbrake | Confirm / back |
| X | Burnout | — |
| Y | Change camera | — |
| Left stick click | Horn | — |
| LB / RB | Look back / hard turn | — |
| Menu / View | Pause | Confirm / back |

Driving buttons follow the game's keyboard bindings, including changes made in its options. Steering and pedals currently use the game's digital action path, with stick/trigger deadzones. Keyboard input remains available. Held buttons are suppressed when crossing between menus and gameplay until released. `RE_GAMEPAD=0` disables native controller handling, useful with a Steam Input keyboard layout to avoid duplicate input. Damage vibration sends short pulses for crashes into cars and scenery, scaled to the damage received. Vibration stops on pause, focus loss, or disconnect; `RE_RUMBLE=0` disables it. Gyro and trackpad gestures are not mapped by this implementation.

Use `RE_INPUTDBG=1` to log detection, mapping, axes, buttons, and delivered game keys (`~/Library/Logs/driver_input.log` on macOS). `RE_DIAG=1` also records device connection/disconnection in the diagnostic session. For Steam Input, choose a conventional gamepad layout; use the disable option above if choosing a keyboard layout instead.

**Gamepads on Linux (v2.32).** The input code is the same as on macOS, but distribution SDL2 packages are SDL2 Classic (Ubuntu 24.04 — 2.30, Debian 13 — 2.32.4) and do not know the 2026 controller either, so build the same pinned runtime with `RE_SDL3_COMPAT=ON`. Ubuntu/Debian packages (checked on Debian 13 arm64 and in CI on Ubuntu 24.04 x86_64):

```sh
sudo apt-get install -y build-essential cmake \
  libx11-dev libxext-dev libxcursor-dev libxi-dev libxrandr-dev libxtst-dev \
  libudev-dev libasound2-dev libpulse-dev libdbus-1-dev
# recommended: Wayland and extra X11 features
sudo apt-get install -y libwayland-dev libxkbcommon-dev libdecor-0-dev libxss-dev libxfixes-dev libusb-1.0-0-dev
# optional: libosmesa6-dev (offscreen render test in selftest)

cmake -S re -B build-sdl3 -DCMAKE_BUILD_TYPE=Release -DRE_SDL3_COMPAT=ON
cmake --build build-sdl3 -j
(cd build-sdl3 && ctest --output-on-failure -L nodata)
```

- The first line (`libx11-dev` … `libxtst-dev`) is the minimum for SDL3 to configure: without X11/Xext it stops with "could not find X11 or Wayland", and without `libxcursor-dev`, `libxi-dev`, `libxrandr-dev` or `libxtst-dev` with "Couldn't find dependency package for XCURSOR/XINPUT/XRANDR/XTEST". It builds without the rest, but then has **no sound** (`libasound2-dev`/`libpulse-dev`, or `libpipewire-0.3-dev`) and **no udev** (`libudev-dev`: device discovery and hotplug for HIDAPI/evdev). `libsdl2-dev` is not needed for this build. SDL3 picks optional backends silently, so check the configure summary: `Joystick drivers: hidapi linux virtual`, `SDL_LIBUDEV ON`, `Audio drivers: … alsa pulseaudio`.
- The result is `build-sdl3/driver` plus `build-sdl3/sdl-runtime/` (`libSDL2-2.0.so.0` = sdl2-compat 2.32.74, `libSDL3.so.0` = SDL3 3.4.18). The binary's RUNPATH is `$ORIGIN/sdl-runtime` and sdl2-compat's is `$ORIGIN` (it loads SDL3 with `dlopen`), so copy **`driver` and `sdl-runtime/` together**; the folder can live anywhere. Check with `ldd driver | grep SDL` — it must point to `…/sdl-runtime/`. At startup the game logs `[gamepad] SDL 2.32.74 (sdl2-compat/SDL3, …)`; `SDL Classic` there means the system SDL2 was picked up (the bundled folder is missing, or `LD_LIBRARY_PATH` overrides it). The CI artifact `driver-linux-x86_64-sdl3` (tar.gz with `driver` + `sdl-runtime/`) is built this way.
- **Device access.** SDL talks to the controller through `/dev/hidraw*` (HIDAPI). By default only root can open it, so install Valve's udev rules: `sudo apt-get install steam-devices` (Ubuntu: multiverse; Debian: contrib), or copy [60-steam-input.rules](https://github.com/ValveSoftware/steam-devices/blob/master/60-steam-input.rules) to `/etc/udev/rules.d/` and run `sudo udevadm control --reload-rules && sudo udevadm trigger`, then reconnect the controller/Puck. Without access the controller is not opened (or only appears through the kernel's generic evdev driver with a different mapping); `RE_INPUTDBG=1` (log `driver_input.log` next to the binary) shows what SDL opened.
- **Steam Input.** If Steam is running, it may hold the controller and present a virtual pad. Choose a conventional gamepad layout, or with a Steam Input keyboard layout run the game with `RE_GAMEPAD=0` to avoid duplicate input — same as on macOS.

**Draw distance (v2.19, `draw_distance`, env `RE_DRAW_DIST`):** a multiplier on the distance from the game options (Gfx Details, 15,000–45,000
units; a map cell is 3000): 1.0 — original, up to 4.0; `enhanced` — 2.0, `original` — 1.0. In the original, distance is limited by: the 31×31
cell-walk window from the FRUSTRUM.DAT table (radius 15 cells = 45,000) and a PVS of the same size, the far plane (an option) and its copy used for polygon
culling, a 1/z table of 56,250 entries, and 4 map-block slots (2×2 blocks of 60 cells in Miami). With a multiplier > 1, native, while the 3D view is drawn,
multiplies the far plane, walks cells beyond the 31×31 window with its own cone test (camera heading from the FRUSTRUM.DAT axes, half-angle from the side
planes with Hor+ taken into account; the table itself is unchanged), extends the 1/z table (k/z), and unpacks missing neighbouring blocks from the already loaded
level into a separate draw-only cache (up to 2 blocks per frame with prefetch; the game's slots and road data are untouched). The low-poly car
threshold (15,000) is multiplied the same way. Depth is 1 − n/z (24-bit) and does not depend on the far plane: close-range precision is the same.
In native the sky is drawn at depth 1.0: its original finite offset of 32767 covered distant buildings and roads,
even though the extended map walk was already sending them to be drawn. The sky's UVs and perspective are preserved.
There is no fog in the D3D version (the Glide fog functions in Game.exe's D3D wrapper are empty), so there is nothing to push back. Logic, AI, spawning, and
pedestrian/cop distances are unchanged (`RE_CARDBG` car positions at 1.0 and 3.0 match). The hook build behaves like the original.

Variables: `RE_PRESET`, `RE_MSAA`, `RE_A2C`, `RE_FXAA`, `RE_ANISO`, `RE_MIPMAPS`, `RE_DILATE`, `RE_FILTER`, `RE_HUD_FILTER`, `RE_RENDER_SCALE`,
`RE_VSYNC`, `RE_FPS_LIMIT`, `RE_GAMMA`, `RE_BRIGHTNESS`, `RE_SHARPEN`, `RE_DRAW_DIST`, `RE_CFG` (path to the file), `RE_NO_FBO=1` (draw straight to the window, like v2.15),
`RE_FRAMESTAT=N` (frame timing from frame N, summary on exit via `RE_MAX_FRAMES`). What actually got enabled is shown by the `[gfx]` lines on stderr.

Verified on Linux under Xvfb (Mesa llvmpipe: MSAA up to 4x, 16x anisotropy); not yet on a real Mac.

## Rendering diagnostics

To capture a rendering problem with a screenshot, car/camera position history,
graphics settings, model records and submitted vertices, see
[Rendering diagnostics](docs/DIAGNOSTICS.md). On macOS run
`sh scripts/run_diagnostics_macos.sh` and press **Cmd+Shift+D** at the problem.

## HD textures

Since v2.17 the native build can replace a level's 16-bit texture pages (256×256, ARGB1555) with high-resolution images
(PNG, square 256..1024, usually 1024×1024 — a ×4 neural-network upscale). A pack is derived from the game data, so it is not in the repository:
you make it yourself from your own copy of the game.

**Ready-made pack (private):** [r331/driver-texpack](https://github.com/r331/driver-texpack) — ×4 upscale (4x_foolhardy_Remacri),
all of NY_01, miami_01. Access is owner-only, do not publish. To use it: `git clone https://github.com/r331/driver-texpack.git`,
then `texpack = /path/driver-texpack` in `driver.cfg` or `RE_TEXPACK=/path/driver-texpack` (16-bit since v2.17, 8-bit and in-game replacement since v2.18).

```sh
pip install numpy pillow torch spandrel          # a CPU build of torch is enough
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --model 4x_foolhardy_Remacri.pth   # ~1 min/page on CPU
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --verify    # check: downscaled PNG ≈ its own page
RE_TEXPACK=texpack ./driver                       # or in driver.cfg: texpack = /path/to/texpack
```

Layout: `<dir>/<level without .lev>/pNNN.png`, where NNN is the page number in the level file (a pair of 8-bit pages takes two numbers).
Model: any ESRGAN-compatible ×4 (`.pth`/`.safetensors`, loaded by spandrel).

**8-bit pages (v2.18).** In NY almost all buildings are 8-bit pages: 256×256 indices, with colour coming from a palette the game picks
at draw time (one page may be drawn with different palettes — city, sky, time of day). So there is one file per pair:
`<dir>/<level>/pNNN_cKKKK.png`, where KKKK is the level's palette slot number (0..49, as in the level file). Which pairs occur is taken from
`Levels/<city>.d3d` (97 pairs for NY_01). 8-bit pages have no transparent index, so the PNG is opaque.

```sh
RE_TEXLOG=texlog.txt ./driver --selftest …        # optional: which pairs are on screen and how much area (generation order)
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --texlog texlog.txt --budget 3600   # ~30 s/pair on 2 cores
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --list      # what is done
python3 tools/texpack.py Data_Files/Levels/NY_01.lev texpack --pal8 --verify    # check all pairs
```

In-game replacement: an 8-bit page is drawn through a slot surface with a palette; the surface's palette identifies the palette slot,
and the ready HD texture for that pair is used; for a 16-bit page the image is attached to the slot surface and checked against its contents on load.
The level directory is looked up as is, in lowercase, and in UPPERCASE.
PNG alpha = the page's 0x8000 bit (no smoothing); the colour of every pixel is kept — transparency is still decided by the game's alpha test.
On load each image is downscaled to 256 and compared with the source page; if it does not match (wrong number, corrupt file),
the original stays, with `[texpack] … отклонён` (rejected) on stderr. Summary: `[texpack] загружено N страниц` (N pages loaded). Without `RE_TEXPACK`/`texpack` everything works as before.

**Interview stopwatch and mission clock digits (v2.36).** The garage interview stopwatch (level `iview`, 16-bit page 8, a 96×128 area:
the dial with 5–55 tick marks, the case, the ring and the buttons) has been redrawn by a neural network from the original at 4× (`hud_hd/iview/p008.png`); files in
`hud_hd/` keep their own alpha — a smooth silhouette, so the alpha test cuts a clean edge instead of 4×4 steps (if a file's alpha differs
from the original in more than 2 % of texels, the original's alpha is used). The needle is drawn by the game and is unchanged.
Upscaling the small HUD font comes out blurry, so the mission clock digits ("MM:SS.cc") have also been redrawn
by a neural network from the original and fitted into the same font atlas cells (page 51 of `miami_01`, palettes 24 and 3): all digits 0–9 are the same height,
on one baseline, centred in cells of equal width — the timer doesn't "jump". This is a separate pack variant, like the sky: the `hud_hd/`
subdirectory, enabled by default by a `hud.txt` file (containing the word `hud_hd`) in the pack root; `RE_TEXPACK_HUD=hud_hd|0|path` takes precedence over the file;
`RE_TEXPACK_HUD=0` or deleting `hud.txt` gives the previous upscale. To regenerate from your own copy of the game:

```sh
pip install numpy pillow scipy
python3 tools/texpack_hud.py Data_Files/Levels/miami_01.lev texpack/hud_hd/src/digits.png texpack --out texpack/hud_hd --sheet hud_cells.png
```

Only Miami is done so far (other cities use a different font page — the cells can be printed with `RE_FONTDUMP=1`).

Limitations: the NY_01 pack is partial (8-bit — 62 of 97 pairs at the time of the commit (all 9 pairs visible in the snapshots are done; generation continues)); in-game replacement has only been verified in Miami with a test pack;
a 1024² page takes ~4 MB of video memory versus 256 KB; verified under OSMesa/Xvfb, not yet on a real Mac.

## CD music

In the original, music is the disc's audio tracks (Red Book): the game opens the drive via MCI (`cdaudio`, TMSF format), reads the table of contents,
plays a track from start to end with an `MM_MCINOTIFY` notification, and on it starts the track again (looping). Since v2.22 the native build
emulates this drive (`re/platform/sdl/plat_cdaudio.c`; the game code is unchanged): tracks come from files, the music is mixed
with the game sound, and the volume is the music slider in the game's sound settings. **There are no music files in the repository** — the tracks are ripped from
your disc.

**Where to put them.** A `Music/` directory in the game data directory (next to `Levels/`), or `music_dir = /path` in `driver.cfg`, or
`RE_MUSIC_DIR=/path` (takes precedence). Since v2.34, if there is no `Music/` in the data directory, music is taken from the HD pack — `<texpack>/Music`
(that is where it lives in `r331/driver-texpack`): `texpack = …` in `driver.cfg` is enough. Names: `Track02.wav` … `Track10.wav` (also `track02.cdda.wav` from cdparanoia and `02 - anything.wav`
from EAC); instead of WAV you can use `.flac`, `.ogg`, `.mp3` (dr_flac, stb_vorbis, dr_mp3 decoders — `re/third_party`, public domain).
You can also supply a disc image: `*.cue` + `*.bin` (`FILE … BINARY`/`MOTOROLA`/`WAVE`, `TRACK NN AUDIO`, `INDEX 01`; raw PCM 44100 Hz
stereo 16-bit, 2352 bytes per sector) — an individual track file takes precedence over the image. WAV: PCM 8/16/24-bit, mono/stereo, any sample rate
(resampled to 44100 Hz).

**How to rip the tracks** (only from your own disc):

```sh
# Linux: cdparanoia (apt install cdparanoia); macOS — cdparanoia from Homebrew or XLD (WAV output)
cdparanoia -Q                       # table of contents: how many tracks, lengths
mkdir Music && cd Music && cdparanoia -B 2-10   # → track02.cdda.wav … track10.cdda.wav
# whole image: cdrdao read-cd --read-raw --datafile driver.bin driver.toc && toc2cue driver.toc driver.cue
#   (cdrdao writes audio big-endian — in the resulting .cue replace BINARY with MOTOROLA)
# Windows: Exact Audio Copy — "Copy Selected Tracks → Uncompressed" (WAV) for tracks 2–10, or "Copy Image & Create CUE Sheet";
#   rename the files to Track02.wav … or keep "02 - ….wav"
```

**Without files** the drive still "exists": calls succeed, and the tracks are 60-second silent stubs (`RE_MUSIC_STUB=tone` — a quiet tone,
different for each track: 220 Hz · 2^((N−2)/12); `RE_MUSIC_STUB_LEN=s` — length). `RE_MUSIC=off` — as before: "Open CD device failed",
no music. A set of stub files for testing (silence/tone, not game data): `python3 tools/make_music_stubs.py Music --tone`
(`--cue` — a `music.bin/music.cue` image). On stderr: `[cd] эмуляция CD-audio: каталог …, дорожек 10: 2=wav …` and for each request
`[cd] MCI_PLAY: дорожка N …`, `[cd] дорожка N закончилась → MM_MCINOTIFY`.

| CD track | Where the game requests it (per the code) | What it is |
|---|---|---|
| 1 | — | data (PlayCDTrack rejects numbers < 2) |
| 2 | `P136_FrontInit` (after loading `TITLE.DSS`), menu frame `P119_MenuFrame` 0040cb9f | frontend/main menu |
| 3 | `P124_MotelInit` 004182b0 (after `MOTEL.DSS`); screen frame `P66_FrameBegin` 004188b0, if the CD is not playing | motel and P66 menu screens |
| 4 + N | `P145_LevelLoad` 004d38b7 and game frame `P131_GameFrame` 004d4a63: `PlayCDTrack(N + 4)`, N — level number 00b87e30 | level |
|  4 | N = 0, `MIAMI_01.LEV` | Miami |
|  5 | N = 1, `FRISCO_01.LEV` | San Francisco |
|  6 | N = 2, `LA_01.LEV` | Los Angeles |
|  7 | N = 3, `NY_01.LEV` | New York |
|  8 | N = 4, `IVIEW.LEV` | interview (test drive in the garage; N = 4 is written by the campaign ladder) |
|  9 | N = 5, `TRAIN.LEV` | `TRAIN` level — purpose (track/training) **not confirmed** by the code |
| 10 | N = 6, `NC_01.LEV` (`NEWCASTLE.DES`) | Newcastle |

Level names come from the Game.exe tables 00562d44 (`*.LEV`) and 00551cb4 (`*.DES`). The titles of the music pieces cannot be
determined from the code and are not given here. Check how many tracks your disc has yourself (`cdparanoia -Q`): the emulation expects tracks 2–10.

Behaviour matches the original (per `game/ported25.c` and Game_decomp.c: InitCDAudio 00524611, PlayCDTrack 0052479e — `MCI_PLAY` with NOTIFY|FROM|TO flags, CDStop 00524873 — `MCI_STOP`, CDResume 005248cd — `MCI_PLAY` with TO only, CDSetVolume 00524917, GetCDTOC 00524f97, the window procedure — `MM_MCINOTIFY` with wp 1/8): the menu, motel and level restart the track when
the end notification arrives; pause (`P127_Pause`) stops the CD, and after a pause the track starts over; an invalid track number
turns the music off (the "music" option = off), as in the original. Noted: the game computes the track end as `P21_AddMsf(TMSF position, MSF length)`
(005250cb) — the length's minutes are added to the track number; what the real Windows driver did with such an end (it may have played
the following tracks too) has not been checked — the emulation plays exactly the requested track. `RE_MUSIC_VOL` — music volume multiplier (0..4).

### PlayStation-style dynamic music (v2.33, optional)

An addition to the PC original (which has one CD track per level): as on PlayStation, each city has 4 pieces — day/night ×
Drive/Chase, and during a cop chase the music smoothly switches to Chase and back. Game logic is unchanged — the emulation only
chooses what to mix. **There are no files in the repository** — these are your own files.

**How to lay out the 16 files.** In the music directory (the same `Music/`, `music_dir` or `RE_MUSIC_DIR`) create a `dynamic/` subdirectory:

```
Data_Files/                      (game data directory, next to Levels/)
└── Music/
    ├── Track02.wav … Track10.wav   (optional: regular CD tracks — menu, motel, interview, Newcastle, fallback)
    └── dynamic/
        ├── 01. Miami At Day Drive.mp3
        ├── 02. Miami At Day Chase.mp3
        ├── 03. Miami At Night Drive.mp3
        ├── 04. Miami At Night Chase.mp3
        ├── 05. San Francisco At Day Drive.mp3
        ├── 06. San Francisco At Day Chase.mp3
        ├── 07. San Francisco At Night Drive.mp3
        ├── 08. San Francisco At Night Chase.mp3
        ├── 09. Los Angeles At Day Drive.mp3
        ├── 10. Los Angeles At Day Chase.mp3
        ├── 11. Los Angeles At Night Drive.mp3
        ├── 12. Los Angeles At Night Chase.mp3
        ├── 13. New York At Day Drive.mp3
        ├── 14. New York At Day Chase.mp3
        ├── 15. New York At Night Drive.mp3
        └── 16. New York At Night Chase.mp3
```

Any format of `.mp3`, `.flac`, `.ogg`, `.wav` (they can be mixed). The name is recognized by words, case-insensitively: city
(`miami`; `san francisco`/`frisco`/`sf`; `los angeles`/`la`; `new york`/`ny`), `day`/`night`, `drive`/`chase` — in any order and with
any separators. If there are no such words, inside `dynamic/` the leading number `01`…`16` applies, in the order of the list above. The subdirectory exists
to avoid confusion with the regular "`NN - anything.wav` = CD track NN" scheme: in `Music/` itself a numbered file is treated as a CD track,
while files with the full set of words (city + day/night + drive/chase) are recognized there too (and are not treated as tracks), but `dynamic/` takes precedence.
A partial set is fine.

**How it is chosen.** When the game requests level track 4–7 (Miami, San Francisco, Los Angeles, New York), the city's set plays
instead. Day/night follows the level's night flag (the same one the game uses to pick the night sky and street lights: Take A Ride Day/Night,
Undercover night missions; per the `P145_LevelLoad` code, in Los Angeles the night flag is always set — so Night plays there). If the time of day changes during a level (dawn/dusk
in a mission) and stays for 3 s, it switches to the other time-of-day pair with a crossfade. A chase is the condition the game uses to turn the radar
red and decide "have you lost the cops": wanted level (Felony) above the first mark and a cop sees the player or has not yet lost sight of them.
Chase kicks in immediately, back to Drive after 4 s without a chase (`RE_MUSIC_CHASE_HOLD=s`); crossfade 1.5 s (`RE_MUSIC_FADE=s`).
If the Drive and Chase tracks of the same time of day are close in length (difference no more than max(1 s, 2 %)), both play in parallel from the same
position and only the volume switches (`RE_MUSIC_SYNC=0` to disable); otherwise Chase/Drive starts from the beginning (equal-power
crossfade). The set loops; pause, volume and stop behave as for a regular track (after a pause the game restarts the track).

**Fallbacks.** If a file is missing — Drive of the same time of day, then Drive of the other, then any file of the city; if a city has no
files at all — the regular `TrackNN` track (4–7), and without it — the stub. Missions where you chase a target (not cops) and the interview/Newcastle
do not use the set.

**To disable:** `RE_MUSIC_DYNAMIC=0` or `music_dynamic = off` in `driver.cfg` (`auto` is the default: enabled if a set is found).
On stderr: `[music] динамический набор: N из 16 …` (what was found per city), `[music] Майами, день: Drive = …, Chase = …`,
`[music] → Chase (погоня)`, `[music] → Drive (погони нет 4 с)`.
To test without your own files: `python3 tools/make_music_stubs.py Music --dynamic` — 16 tones with the correct names (220 + 110·k Hz,
k = 0…15 in list order); `RE_WAV_OUT` shows which file is playing.

## Running

### Game data

You need the `Data_Files` directory from your copy of the game (it is recognized by the presence of `FSIN.DAT`). On the CD the data is inside the InstallShield archive `DATA1.CAB`:

```sh
unshield -d driver-cd x /path/to/CD/DATA1.CAB    # -> driver-cd/Data_Files, driver-cd/Program_Executable_Files/Game.exe
```

The game writes to its working directory (`config.dat`, `debug.log`, `SAVES/`, `Scripts/Waypoint.tmp`, `ReplayData/`). To leave your game copy untouched,
set up a separate run directory: symlinks to the `Data_Files` files, with `Scripts` and `ReplayData` as copies:

```sh
GAME=/path/to/driver-cd/Data_Files
RUN=$HOME/driver-run
mkdir -p "$RUN" && cd "$RUN"
for f in "$GAME"/*; do
  case "$(basename "$f")" in Scripts|ReplayData) cp -R "$f" . ;; *) ln -sf "$f" . ;; esac
done
```

### Launching

```sh
./build-native/driver --data "$RUN"
```

Without `--data` the program looks for `Data_Files` in the current directory. Other options: `--selftest` (self-test, no data needed),
`--frames N` (same as `RE_MAX_FRAMES=N`), `--idle` (an empty window, no game).

Headless (this is how it was verified):

```sh
RE_NO_MSGBOX=1 RE_MAX_FRAMES=300 RE_SHOT_PNG=menu.png \
  xvfb-run -a -s "-screen 0 1024x768x24" ./build-native/driver --data "$RUN"
```

Take A Ride in Miami from a key-press script (menu: LEFT×3 → Take A Ride, RETURN×3 — Miami and start; then throttle and a turn):

```sh
RE_NO_MSGBOX=1 RE_FIXED_DT=1 RE_MAX_FRAMES=1100 RE_SHOT_PNG=ride.png \
RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN,700:APOSTROPHE:300,850:X:25" \
  xvfb-run -a -s "-screen 0 1024x768x24" ./build-native/driver --data "$RUN"
```

### Controls

Default Driver PC key layout (`P37_InitInput`, table 0054b7a8; car key bits — `P36_GetPadButtons` → `P107_CarInput`).
"Verified" means with an `RE_KEYS` script (speed/steering from `RE_CARDBG`, PNG snapshots), v2.10.

| Action | Key | Verified |
|---|---|---|
| throttle | `'` (apostrophe) or **↑** (v2.14) | yes — speed rises; ↑ gives the same numbers as `'` |
| brake / reverse | `/` or **↓** | yes — speed drops to 0, then the car reverses |
| steer left / right | `Z` / `X` or **←** / **→** | yes |
| handbrake | `Enter` or **space** (v2.14) | yes — speed drops to 0 even with the throttle held |
| hard steering (faster and up to 511 instead of 352) | `space` (together with the handbrake, v2.14) | yes — by the steering value |
| change camera (behind → bonnet → …) | `1` | yes — bonnet snapshot |
| TV camera / static | `2` | no |
| look left / right / back | `J` / `K` / `L` | no |
| horn (siren in cop mode) | `H` | no — no audible difference in the sound capture |
| cruise control | `C` | no |
| bit 0x40 (`\`, wheelspin at start) | `\` | no |
| draw distance − / + | `F1` / `F2` | no |
| mirror distance − / + | `F3` / `F4` | no |
| pause (pause menu) | `Esc` | yes — pause menu snapshot |
| screenshot (BMP) | `F12` | no |

The arrow keys and space for driving (v2.14, native only) were added to `P36_GetPadButtons` — it is called only from the driving tick, and menus read
the arrow keys directly, so menu navigation is unchanged. Window/fullscreen — Cmd+Enter or Alt+Enter (not passed to the game).

Menus: arrow keys, Enter to select. Gamepad (the first SDL GameController): D-pad and left stick → arrow keys, A/Start → Enter, B/Back → Esc, X → space.

### Environment variables

| Variable | Effect |
|---|---|
| `RE_MAX_FRAMES=N` | exit with code 0 after the N-th presented frame |
| `RE_SHOT_PNG=path` | save frame N (`RE_MAX_FRAMES`) as PNG; with `RE_SHOT_FIRST=1` — the first frame. The program does a `chdir` into the data directory, so a relative path is resolved from `$RUN` (`menu.png`, `ride.png` from the examples end up there) |
| `RE_KEYS="frame:key[:frames],…"` | key-press script: the key is held from frame N for `RE_KEYS_HOLD` frames (2 by default) or for the given number; the key is a name (`UP DOWN LEFT RIGHT RETURN ENTER ESC SPACE TAB F1..F12 A..Z 0..9 APOSTROPHE LSHIFT …`) or a DIK code (`0x28`) |
| `RE_FIXED_DT=1` | virtual clock (20 ms per frame) — reproducible runs independent of the computer's speed |
| `RE_NO_MSGBOX=1` | MessageBox messages go only to stderr (under Xvfb a message box blocks) |
| `RE_WATCHDOG=N` | after N seconds print a stack trace and exit with code 3 |
| `RE_INPUTDBG=1` | v2.14: input log `driver_input.log` (macOS — `~/Library/Logs/`, otherwise next to the binary or in the current directory) |
| `RE_WINDOWED=1` / `RE_FULLSCREEN=1` | v2.14: window / fullscreen (default: fullscreen on macOS, windowed elsewhere) |
| `RE_RES=WxH` | v2.14: window size (default — the largest integer multiple of 640×480 within 85% of the screen); the `RE_SHOT_PNG` snapshot is at the window buffer size |
| `RE_ASPECT=auto\|4:3\|W:H` | v2.15: 3D aspect ratio (Hor+): from the window (default), original 4:3, or a given one — see "Resolution and aspect ratio" |
| `RE_PRESET`, `RE_MSAA`, `RE_FXAA`, `RE_ANISO`, `RE_FILTER`, `RE_RENDER_SCALE`, … | v2.16: graphics — see "Graphics" (override `driver.cfg`) |
| `RE_TEXPACK=dir` | v2.17: HD texture pack — see "HD textures" (takes precedence over the `texpack` key in `driver.cfg`) |
| `RE_TEXPACK_HUD=hud_hd\|0\|path` | v2.36: pack variant with the redrawn interview stopwatch and mission clock digits (takes precedence over `<pack>/hud.txt`; `0` — the previous upscale) |
| `RE_FONTDUMP=1` | v2.36, debugging (native only): logs once the glyph cells of fonts 0 and 1 for "0123456789:." (page, u, v, w, h) |
| `RE_TEXLOG=file` | v2.18: statistics per (page, palette) pair: triangles and on-screen area — to order pack generation |
| `RE_ARROWKEYS=0` | v2.14: don't add arrow keys/space to the driving keys |
| `RE_PROBE=1\|all\|car,traffic,ped,mission,menu,walk` | RE debugging: a field log for the open questions in [docs/RE_QUESTIONS.md](docs/RE_QUESTIONS.md) (`RE_PROBE_LOG`, `RE_PROBE_EVERY`, `RE_PROBE_SHOTS`, `RE_PROBE_WALK`); native only, read-only — see docs/ARCHITECTURE.md «RE_PROBE» |
| `RE_COPTRACE=N` | v2.34, cop debugging (native only): every N frames a `[coptr]` line per tracked cop (slot, car, AI record fields, throttle, steering), `[copplan]` — the route-planning result of P128_CopReplan |
| `RE_FPU_CHOP=0` | v2.34, debugging: don't emulate Game.exe's x87 round-toward-zero (`lrintf` etc. round to nearest, as before v2.34) — for comparing runs; see docs/ARCHITECTURE.md |
| `RE_RANGEDBG=1` | v2.35, debugging (native only): log of the 004f5012 range check (`P98_ScriptRange`) — script object, threshold, distance, target and player positions; "→ цель потеряна" (target lost) when it fires |

The other debug switches (`RE_TRACE*`, `RE_GSTAT`, `RE_CARDBG` …) are described in [docs/NATIVE_GAPS.md](docs/NATIVE_GAPS.md).

## Hook build for Windows (proxy DINPUT.dll)

Game.exe imports only `DirectInputCreateA` from `DINPUT.dll`. The proxy DLL exports the same function (forwarding the call to the system `dinput.dll`),
and on load installs hooks on the ported functions (`re/platform/win32/install.c` has 2265 `re_hook` calls).

Build with MinGW i686 (verified on Linux; running on Windows has not been tested):

```sh
sudo apt-get install -y gcc-mingw-w64-i686      # macOS: brew install mingw-w64 (not tested)
sh re/build.sh hook                              # -> re/build/DINPUT.dll
```

`re/CMakeLists.txt` has an `RE_HOOK_BUILD` branch, but it has not been tested and does not include all the `platform/win32` files and libraries
that `build.sh hook` uses; the working path is `build.sh hook`. An MSVC build is neither supported nor tested.

Installation: put `DINPUT.dll` **next to `Game.exe`** (MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`; other exe versions are not supported) and start the game.
Under Wine (from `re/README.md`, not tested here): `WINEDLLOVERRIDES="dinput=n,b" wine Game.exe`.

How to check that the hook works: `re_driver.log` appears in the game's working directory. The first line is
`re_driver: Driver (PC, 1999) reconstruction layer`, followed by one line per function: `hook   <address> <name>`.
Errors: `ERROR: system dinput.dll not found`, `ERROR: Game.exe not at 0x400000`, `FAIL   <address> <name>` (failed to unprotect the page).
To disable an individual function: a `re_driver.ini` file next to the game, section `[disable]`, line `FunctionName=1`
(the log will show `skip   <address> <name> (disabled in ini)`).

## Legal notice

Driver is the property of its rights holders (Reflections Interactive / GT Interactive and their successors).
The repository contains no game files: no `Game.exe`, no data (`Data_Files`), no disc image. This is a research project
to reconstruct the code; running it requires a legally obtained copy of the game.

---

## English summary

A decompilation and C port of **Driver** (PC, 1999, Reflections / GT Interactive), based on `Game.exe` built 1999-09-10
(MD5 `8e19d76a4bd5f3838a5c5cbf1cc5cfb5`). **No game files are included** — you need your own copy of the game (CD).

- **Status:** 3292 of 3292 non-CRT functions are marked `ported` in `docs/functions.csv`. The native build (v2.12) runs the menus and
  *Take A Ride* in Miami (driving, traffic, HUD, brake/reverse, handbrake, bonnet camera, Esc pause menu) with sound (own DirectSound
  mixer, soft limiter; no CD music). Pedestrians are rendered but appear far from the player; cops pursue and ram the player once felony
  is raised (verified with a debug placement); FMV is skipped; Undercover reaches the motel and the first Miami mission. v2.15: any aspect ratio (Hor+: original vertical FOV, wider horizontal FOV, HUD anchored to screen edges, menus 4:3 centered; `RE_ASPECT=auto|4:3|W:H`). See `docs/NATIVE_GAPS.md`.
- **Build (Linux, verified on arm64):** `apt-get install build-essential cmake libsdl2-dev libgl-dev libegl-dev libosmesa6-dev`, then
  `cmake -S re -B build-native -DCMAKE_BUILD_TYPE=Release && cmake --build build-native -j && (cd build-native && ctest --output-on-failure)`.
  macOS (Apple Silicon): `brew install cmake sdl2`, same commands; build + selftest verified in GitHub Actions on `macos-14` (arm64),
  `-DRE_MACOS_BUNDLE=ON` builds `Driver.app`. Running the game with a window on a real Mac is not tested yet.
- **Run:** `./build-native/driver --data <run dir>`, where the run dir symlinks your `Data_Files` and holds copies of `Scripts` and `ReplayData`
  (the game writes there). Controls: arrows/Enter in menus, `'` throttle, `/` brake/reverse, `Z`/`X` steering, Enter handbrake, `1` camera, Esc pause, gamepad supported.
- **Hook build:** `sh re/build.sh hook` (MinGW i686) produces a proxy `DINPUT.dll`; put it next to `Game.exe`, check `re_driver.log`.
  Windows run not tested.
- Driver is the property of its rights holders; this repository contains none of their files.
