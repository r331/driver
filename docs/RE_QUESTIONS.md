# Open reverse-engineering questions

Collected from the readability pass (`readability/comments`, PR #2) — every `TODO(RE)` the workers left that
matters beyond a single line, plus findings that contradict older names or notes.  The full list is
`git grep -n "TODO(RE)" re/` (≈330 places); this file groups the ones worth an answer.  When a question is
settled, fix the comment / header at the place named here and delete the entry.

Rules that still hold: names carrying a Game.exe address (functions, globals, data-image aliases) are **not**
renamed even when they are wrong — the correction goes into the comment.  Shared record layouts live in the
headers listed in `docs/ARCHITECTURE.md` ("Соглашения о коде и именах").

## How questions get answered

`RE_PROBE` (native only, see `docs/ARCHITECTURE.md` «RE_PROBE») logs the fields behind the questions below while the
game runs; topic `walk` drives the front end on its own and logs every menu table with its texts.  Entries marked
**ANSWERED** carry their evidence; the comment / header at the named place has been fixed.  Static evidence
("xref") = every writer / reader found in Game.exe.

## Notable findings (contradict an older name or note)

| Finding | Where | Status |
|---|---|---|
| `P60_NextTrafficCar` (004c5c5d) does not return the next traffic car: it returns the first car after `from` whose traffic record is a **cop** (record `[5] != 0`, state `[1] == 4` = cop AI, model kind `[0xc] == 1`) within 30000 units of the player. The director's "next car" key therefore cycles through nearby cops. | ported60.c | name kept, comment fixed; model 1 = police and state 4 = cop AI **ANSWERED** by RE_PROBE (v2.34, see Traffic record) |
| Weather flags `P26_FxA..D` = **rain / lightning / snow / fog** — the flags the MScript keywords RAINING, LIGHTNING, SNOWING, FOGGY set. Lightning only together with rain, snow only by day, fog only at night (P14_00b87e84). | ported26.c, ported147.c | comment |
| `P22_AlphaRef` is misnamed: it caches the last alpha-test **compare function** mode of `P22_SetAlphaFunc` (0041ddc5), not the alpha reference value (that one is set by `P22_SetAlphaRef`, render state 24). | ported22.c | name kept (address alias), comment; rename only after checking all address users |
| `Mat3MulT_005284AC` computes `A * B`; `Mat3Mul_0052859A` computes `(A * B)^T` — the names are backwards. | ported8.c / ported8.h | names kept, comments fixed |
| Frustum planes: `P82_PlF` is the **near** plane (z = 50, normal (0,0,-1)), `P77_Plane` the **far** plane (z = P11_01270c24). The old Russian note in ported82.h and the P83_BoxVis header had them swapped. | ported82.c/.h, ported83.c | fixed |
| Glide texture format 0xb is `GR_TEXFMT_ARGB_1555` (16-bit, 128 KB page spills into the second block), not "8 bpp with alpha". | ported40.c/.h | fixed |
| `p99_car_t.vel[3]` (+0x11c) never held a velocity: it is the first three of the six damage zones. Renamed to `damage[3]`. Zones 0/1 below 1000 decide whether the car's lights glow (inferred: the two headlights). | cartab.h, ported100/106/132/137/138 | renamed |
| Car field +0x138 is the **accumulated hit damage** (`CAR_DAMAGE_SUM`): P100_CarHit adds force / 2 on every hit; RE_PROBE `car138` lines change only on impacts, never on a cell change. ported75's "+0x138 >> 3" is a damage step for the crash sound, not a map cell. | carfields.h, ported75.c | **ANSWERED** (probe + xref), ported75 comment fixed |
| Car fields +0x58 / +0x68 are **pending velocity / angular-velocity changes** (impulse accumulators, `CAR_DVEL_PEND` / `CAR_DANGVEL_PEND`): collisions (ported129) add to them, P94_SpringStep / P142_CarsStep apply and clear them each step (xref + probe `car0` dumps). Formerly `CAR_FORCE_OUT` / `CAR_TORQUE_OUT`. | carfields.h, ported56/94/129/137/142 | **ANSWERED**, renamed |
| Pool `A_00C56780` (64 × 0xb4) holds **pedestrians only**: its fill limit is 005759a4, the "Pedestrian Density" slider of the Detail menu (RE_PROBE walk) The "particle / dust" wording was wrong. | ported71/102/106/114 | **ANSWERED**, comments fixed (address-alias names like `P99_PartOnChair` kept) |
| `P87_DrawCells` has no Game.exe address; its only caller is the selftest. | ported87.c | **ANSWERED** (grep), comment says so |
| Native cops stopped instead of chasing: the ported code ignored the truncating x87 control word of Game.exe (005283e2 / 0052840c / 00528455 were C stubs without `fldcw`), so every fistp rounded to nearest and the cop route lookup hit the wrong map cell. | fpucw.h, ported6/7/18, ported128 | **FIXED** v2.34 |
| Mission state 00c810c4 (= P16_IdleMode = P56_Blk84[1]) and fail reason 00c810e8: all values settled from every Game.exe writer plus the probe `mission` topic — new shared header `missionstate.h` (MSTATE_*: 0 none, 1 objective, 3 race, 0xff0 failed, 0x7fff objective done, 0x8000 passed bit, 0x80f1 race done; MREASON_*: 1 time out, 2 failed / flipped, 3 target lost, 5 sequence ran out). | missionstate.h, ported16/98/127/140 | **ANSWERED** (reason 5's game event still TODO) |

## Car fields (`carfields.h`, `cartab.h`)

- **ANSWERED**: +0x108 = burnout in progress (`CAR_BURNOUT`, set by P107_CarInput on pad bit 0x40, cleared by the handbrake; probe `car108` toggles only with the burnout key); +0x140 / +0x141 = steering-hold counter / steering key direction (`CAR_STEER_HOLD` / `CAR_STEER_DIR`); control bits 0x40 = burnout, 0x80 = cruise control — matches the Key Redefine screen 0054c530 ("Burn Out", "Cruise Control", "Fast Steer"); +0x128 = damage zone 3.
- +0x13c / +0x13d / +0x13f still unnamed (probe: constant 1 / 0 / 0 for the player).
- +0x5c: reset code writes `-0x2aaa` (ported56 `CAR_FORCE_OUT + 4`, ported137) — gravity? Units?
- Damage zones 0..5: which zone is front / rear / left / right (ported104 "zone damaged per face id"; ported100 P100_CarHit picks the zone from the impact direction).
- car+0xcb4 / slot+0xcb4 (ported91 P91_ReleaseTraffic, ported51 `SLOT_FCB4`) — "active" flag? Slot fields +0x40, +0x5c, +0xcb8, +0xcbc, +0xcd4 (scale 1.0f) unknown.
- ported94: physical meaning of the spring constants; who uses `P94_CurveB` / `P94_CurveC`.
- ported99: gearbox table column meanings are inferred from use only.

## Traffic record (`trafficrec.h`, TrafficRecs 011443e0, 0x54 bytes)

- **ANSWERED** `TREC_CLASS` (+9) is the **lane** (equal to P59_CellLeft in 493 / 512 probe samples; the rest are state 3, not refreshed). Name kept for its users, comment fixed.
- **ANSWERED** `TREC_NEXT_NODE` (+0x28) is the **road word** of the current segment (index into 00c39dc0, bit 0x4000 = crossing a junction, seen in state 3), not a node id; +0x2c is the road word after the coming junction.
- **ANSWERED** +0x18 = distance **left** to the segment end (decreases in 317 / 320 consecutive samples), +0x1c = distance covered; their sum is constant per segment. The old name `TREC_ROAD_LEFT` (+0x1c, from P101_RdLeft) was backwards → renamed `TREC_ROAD_DONE`.
- **ANSWERED** `TREC_F34` (+0x34) = turn at the coming junction (0 straight, ±1 direction index) and `TREC_DIR2` = direction after it: TREC_DIR2 == TREC_ROAD_DIR + TREC_F34 in 457 / 457 samples. Still open: `TREC_F03`, `TREC_F08`; `TREC_LANE` (+0xe) is **not** the lane (values 0, 1, 2, 4 — road type?).
- State 3 (`TRF_STEP`, P119_TrafficStep) = turning through a junction (probe: +0x28 has bit 0x4000 only in state 3).
- **ANSWERED** byte +0xc = **model** of the driven car (equal to CAR_MODEL in all 512 samples of the first probe); **model 1 = police car**: every record in state 4 had model 1 (Take A Ride 43 / 43 samples, Survival 23 / 23; `work/cop-out/tar_base.probe`, `surv_base.probe`), so "model 1" in P60_NextTrafficCar / "!= 2" in P95_NearestTwo are model ids.
- **ANSWERED** byte +5 = **cop slot number** (0 = not a cop; 1..8 by the code, 1..4 observed): P142_CopDrive uses `rec[5] - 1` as the index into the cop table 0112da00; probe values 1..4 only on model-1 records (Take A Ride 25 samples, Survival 23), including model-1 patrol cars still in state 2 (driving as traffic before the chase, 18 samples). The earlier "0 in every record" came from runs without any cop: the first probe (Take A Ride, no chase) and a broken Survival harness (relative `Scripts/` symlinks lost when the run directory was copied, so Mission45.dms was never loaded); with working links Survival spawns 4 cops at once even before v2.34.
- **ANSWERED** state 4 = `TRF_COP` (ported133 enum): runtime-confirmed — records in state 4 are model 1 with a slot in +5; `CAR_AI_DRIVEN` = 1 in Survival 23 / 23 and Take A Ride 29 / 43 samples (the rest are cars just switched). Writers ported119:672 / ported121:492 switch a model-1 patrol from state 2 to 4 when a chase is on.
- **ANSWERED (v2.34)** why native cops never closed in: not the AI code but the x87 rounding mode. Game.exe runs the logic with control word 0x0c7f (truncate; set by 005283e2 at display init and by 0052840c at the start of every tick), the port rounded fistp to nearest, so the route window (P128_CopMapPos, fistp((x + 0x2ee + P62_MapC64) / 1500)) landed on the neighbouring cell about half the time, P128_CopReplan left at "window centre impassable", no route → P142_CopDrive target speed 0 beyond close range. Fix: `game/fpucw.h` (see docs/NATIVE_GAPS.md v2.34). Evidence `RE_COPTRACE`: before — every replan "[copplan] … центр окна непроходим"; after — 67 replans with `res 1`, the patrol follows at speed 300–400 and the felony rises.
- ported118: record kind 3 and the value 0x82 written at +0x3c on a turn.
- ported51: traffic-light reading of byte +3 / direction parity.
- Older modules ported103.c / ported133.c still use raw offsets — convert to `TREC_*` when touched.

## Cameras and the replay director (`dircam.h`, director.c, dirnodes.c, ported59–61, ported133/134)

- Camera types 0x10 / 0x11: the game's own strings say "Static camera" / "Watch car camera", but the ported60 key handlers place a tripod as 0x11 and turn it into 0x10 when aiming at a car — confirm in the replay editor. Not probed yet (needs a saved replay to open in the director; time-boxed out).
- `DCAM_HOLD` (+0x5c, "Holding camera position" in CameraDump): P61_StoreCamState stores the look-at target there, the tripod handlers a copy of the position.
- `DCAM_ANG_REL` / `DCAM_ANG_ABS` (+0x18 / +0x1c): relative vs absolute angle — the static-camera code writes the same absolute aim angle into both.
- `DCAM_FLAG48` / `P60_Var1373C0`: toggled by the director "toggle" key in watch-car mode, and also forces clipping in P82_SphereVis3D / P83_BoxVis.
- dirnodes: `DirectorUnk7C` (selected node?), `GetNodeParent` (is unk18 really a parent link?); directorstorage: v1 words +0x2c..+0x38 copied into two v2 blocks.
- Camera mode 6 in ported59 (map / overview?); director key group 10 in ported60 ("camera on a car").
- Open from part 1: Cine0/Cine1 in `MCS_SETCAMERASTART/END`.

## Menus and UI (ported4/5/12/15/17/19/45/53/54/57/66/77, menuselect.c, menustate.c, widgets.c, uihandlers*.c)

- **ANSWERED** (RE_PROBE walk + direct key runs) — front-end tables: 0054cc90 Main (0 Undercover, 1 High Scores, 2 Options, 3 Take A Ride, 4 Driving Games, 5 Cheats, 6 Training, 7 Car Chases); 0054d138 Undercover (New Game / Load Saved Game); 0054c810 Load game; 0054d300 Car Chases (Load Film Replays, Play Chase 1–4); 0054ca80 Load replay; 0054d418 Highscores; 0054bee8 High-score table; 0054e1d0 Training (Car park / Desert); 0054e040 Choose city; 0054a0e8 Day/Night; 0054d200 Options (Detail / Sound / Control / Gameplay); 0054a470 Detail (19 entries: Detail Level, Shadows, Smoke, Debris, Lens Flare, Light Flares, Rear View Mirror, Shiny Cars, Coloured cars, Tyre Tracks, Real Time Lights, Overlay Map, Fog, Transparent Water, Mirror Viewing Distance, Viewing Distance, Pedestrian Density, Traffic Density, Night Brightness); 0054dd10 Sound (Device, Compatibility, EAX, Effects, Music, Doppler, Mixer, Frequency, Speakers, Effects / Music volume); 0054a008 Control (Input device, defaults, Key Redefine 0054c530, …); 0054ad60 Gameplay (Cop Difficulty, Auto Handbrake, Max frame rate, FMV); 0054a968 Driving Games (Pursuit, Getaway, Cross Town Checkpoint, Trail Blazer, Survival, Dirt Track, Carnage); 0054a870 Dirt Track (Practice / Time Trial); 0054d5b0 "Choose your mission" (city); 0057b5a8 Cheats ("None Available").
- Detail labels are taken from the screen's text order (verified for the Sound screen, where each handler's effect matches its label); the walker skipped entering the slider / key-capture entries (Detail, Sound 3..10, Key Redefine) because RETURN there captures input.
- Not reached: in-game pause menu pages (00419b35 group), 005754d8, 0057b740, P77_Menu* tables that are not front-end screens.
- Menu item state values 0 / 2 / 3 (normal / disabled / highlighted?) — menuselect.c, ported15 `MENU_ITEM_STATE`, widgets.c.
- **ANSWERED** settings: 00b87e2c = Cop Difficulty (0..2); 00575f50 = Environmental Audio (EAX); 00575f40 = sound Effects on/off; Q00B87E90 = Music on/off; Q00B87E94 = Doppler Effect; 00b87e5c = Compatibility mode (3 states); 00575f24 = Auto Handbrake; 00575f48 = FMV; tri_state (0040e9b5) = Max frame rate; G00B87E4C = Night Brightness (0..3, Detail entry 18); 005759a4 = Pedestrian Density; 00575ee8 = Transparent Water (render class 5); 00575ef8 = detail preset (4 = "Custom").
- Still open: 0125f3f8 / 0125f3e0 (not tied to a menu entry; maybe Viewing Distance / Mirror Viewing Distance sliders — the walker did not enter the sliders).
- **ANSWERED** game modes (01271060) / high-score tables: 1 Trail Blazer, 2 Cross Town Checkpoint, 3 Survival, 4 Pursuit, 5 Getaway, 6 Dirt Track Practice, 7 Carnage, 10 Training, 0xb Dirt Track Time Trial (table 0xc = its best lap). Still open: mode 8 (ported12 P12_Fn00404F70 with 00b87e38 = 0x105).
- ported124: which key bits are up/down/left/right in the replay camera save/restore.

## Mission script, ladder and results (ported16/42/96/97/98/123/139–141/147, mscript_ops.h, ladder.h)

- `ladder.h` names follow the MLADDER source keywords (SETCITY, ROOM, MISSION, RENDER, TRIGGER, IF, IFOK, ENDIF, QUITONFAIL, INTERVIEW, END); the interpreter comments come from P140_LadderRun. Codes 8 and 0xa are never emitted — unused?
- **ANSWERED** result codes — see `missionstate.h` (findings table). End countdown 00c81100 = 0x5a / 0x96 / 0xb4 ticks.
- Script compiler: line result 10 (`MSC_LINE_OK_10`), 0xb vs 0 return of INCREASE/DECREASE (ported147), parser error 9 (`FINDCMD_NOTFOUND`) and 0xc ("missing word", ported96).
- **ANSWERED** ×50 = seconds → ticks (the game logic runs 50 ticks per second — RE_FIXED_DT steps 20 ms per tick; script times are written in seconds).
- **ANSWERED** interview tasks 0..8 = Burnout, Handbrake, Slalom, 180, 360, Reverse 180, Speed, Brake Test, Lap.
- Event-script keywords for commands 4 and 0x32 (ported123); goal record fields (ported97); the 6 words + value 8 in ported147 / ported141 (+0x18 = 8 "record filled").
- Open from part 1: MScript code 0x52; the "marker" of ported140 (chase helicopter?).

## Sound (ported6/7/12/25/38/48/49/50/56/116/148, plat_snd.c)

- Sound driver entries 08 / 0C / 38 / 54 (ported48) and the per-voice assignment (ported116).
- P140_B1F434 (EAX / 3D sound switch, ported148); EAX listener property id 1 and value 2 (ported50); DSSPEAKER modes vs menu entries (ported38).
- **ANSWERED** Q00B87E90 = "Music" On/Off, Q00B87E94 = "Doppler Effect" (Sound menu 0054dd10). P140_B1F434 still open.
- **ANSWERED** `P25_TimerCnt` is dead in Game.exe too (Game.exe xref: decremented, never incremented).
- ported56: the looping sound picked by frame & 3 (siren?); ported75 +0x7c / +0x7e (engine revs / load?).
- plat_snd.c (native): a 65th live SDL timer would overwrite one of the 64 reused contexts.

## Rendering (ported11/15/22/23/28/32/40/47/52/69/76/80/82/87/89/111/112/135/143)

- Render classes 0..7 of map models (P80_Class) and object class 7 (ported89, drawn first with render state 0x13). Class 5 option 00575ee8 = Transparent Water (answered).
- Glide colour-combine argument sets (ported143), fog mode value 2 (ported69), what each fog pass draws.
- Vertex conversion A vs B (P23_ConvVertexA/B, ported76) and why two scale variants exist (ported23); P23_DevCaps blend bits.
- ported112: confirm format 5 = GR_TEXFMT_P_8 in the director texture path; ported40 slot flag 2 / palette argument.
- ported15: does the model array hold planes or plain normals; ported111: y-up-negative road surface quad.
- ported32 / ported39: device flag +0x518 (hardware device / system-memory back buffer).
- ported28: what the four per-pass calls (00427757, 0042793F, 004757D2, 00475906) do; ported27 dent texture indices (panels × damage stages).
- Searchlights level (ported135), skid ring B (ported117), surface flag 0x4000 at model +8 = "hard" surface (ported117 `MDL_F_HARD`).
