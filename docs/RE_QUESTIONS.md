# Open reverse-engineering questions

Collected from the readability pass (`readability/comments`, PR #2) — every `TODO(RE)` the workers left that
matters beyond a single line, plus findings that contradict older names or notes.  The full list is
`git grep -n "TODO(RE)" re/` (≈330 places); this file groups the ones worth an answer.  When a question is
settled, fix the comment / header at the place named here and delete the entry.

Rules that still hold: names carrying a Game.exe address (functions, globals, data-image aliases) are **not**
renamed even when they are wrong — the correction goes into the comment.  Shared record layouts live in the
headers listed in `docs/ARCHITECTURE.md` ("Соглашения о коде и именах").

## Notable findings (contradict an older name or note)

| Finding | Where | Status |
|---|---|---|
| `P60_NextTrafficCar` (004c5c5d) does not return the next traffic car: it returns the first car after `from` whose traffic record is a **cop** (record `[5] != 0`, state `[1] == 4` = cop AI, model kind `[0xc] == 1`) within 30000 units of the player. The director's "next car" key therefore cycles through nearby cops. | ported60.c | name kept, comment fixed |
| Weather flags `P26_FxA..D` = **rain / lightning / snow / fog** — the flags the MScript keywords RAINING, LIGHTNING, SNOWING, FOGGY set. Lightning only together with rain, snow only by day, fog only at night (P14_00b87e84). | ported26.c, ported147.c | comment |
| `P22_AlphaRef` is misnamed: it caches the last alpha-test **compare function** mode of `P22_SetAlphaFunc` (0041ddc5), not the alpha reference value (that one is set by `P22_SetAlphaRef`, render state 24). | ported22.c | name kept (address alias), comment; rename only after checking all address users |
| `Mat3MulT_005284AC` computes `A * B`; `Mat3Mul_0052859A` computes `(A * B)^T` — the names are backwards. | ported8.c / ported8.h | names kept, comments fixed |
| Frustum planes: `P82_PlF` is the **near** plane (z = 50, normal (0,0,-1)), `P77_Plane` the **far** plane (z = P11_01270c24). The old Russian note in ported82.h and the P83_BoxVis header had them swapped. | ported82.c/.h, ported83.c | fixed |
| Glide texture format 0xb is `GR_TEXFMT_ARGB_1555` (16-bit, 128 KB page spills into the second block), not "8 bpp with alpha". | ported40.c/.h | fixed |
| `p99_car_t.vel[3]` (+0x11c) never held a velocity: it is the first three of the six damage zones. Renamed to `damage[3]`. Zones 0/1 below 1000 decide whether the car's lights glow (inferred: the two headlights). | cartab.h, ported100/106/132/137/138 | renamed |
| Car field +0x138: `carfields.h` calls it `CAR_DAMAGE_SUM` (total damage, 6 × 0xfff when wrecked; P100_CarHit, Get138*), but ported75 (004d6dac) uses "+0x138 >> 3" of the player as the **map cell** for a cell-change sound. One of the two readings is wrong — check 004d6dac in Game.exe. | carfields.h, ported75.c, ported100.c, uihandlers3.c | open |
| Car field +0x68..+0x70: `CAR_TORQUE_OUT` (last accumulated torque, P94_SpringStep) — ported129 (car vs static object) adds the **angular impulse** of the collision there. Probably the same accumulator ("torque in this step"), but confirm the units. | carfields.h, ported129.c | open |
| Pool `A_00C56780` (64 × 0xb4): ported43.h / ported71 call it pedestrians ("walkers" that walk the map grid), ported71.h / ported102 / ported106 / ported114 call the same records particles (dust at empty cells). Possibly one pool shared by two object kinds (flag 0x10 = walker). | ported71.c, ported102.c, ported106.c, ported114.c | open |
| `P87_DrawCells` has no Game.exe address and no caller in the tree — possibly dead native code; check before the next dead-code pass. | ported87.c | open |
| `MISSION_FAILED` 0xff0 has three local names for one value of 00c810c4: `MISSION_FAILED` (ported16, ported127), `C4_FAILED` (ported140); ported98 also writes result 3 to 00c810e8 ("likely failed"). Candidate for a shared mission-state header once 00c810c4 / P16_IdleMode are confirmed to be the same cell. | ported16/98/127/140 | open |

## Car fields (`carfields.h`, `cartab.h`)

- +0x108, +0x13c..+0x141 — still unnamed (open since part 1 of the pass).
- +0x5c: reset code writes `-0x2aaa` (ported56 `CAR_FORCE_OUT + 4`, ported137) — gravity? Units?
- Damage zones 0..5: which zone is front / rear / left / right (ported104 "zone damaged per face id"; ported100 P100_CarHit picks the zone from the impact direction).
- car+0xcb4 / slot+0xcb4 (ported91 P91_ReleaseTraffic, ported51 `SLOT_FCB4`) — "active" flag? Slot fields +0x40, +0x5c, +0xcb8, +0xcbc, +0xcd4 (scale 1.0f) unknown.
- ported94: physical meaning of the spring constants; who uses `P94_CurveB` / `P94_CurveC`.
- ported99: gearbox table column meanings are inferred from use only.

## Traffic record (`trafficrec.h`, TrafficRecs 011443e0, 0x54 bytes)

- `TREC_CLASS` (+9): low 2 bits pick the speed limits (P63_LimA/B), but P102_TrafficAhead compares it as the "lane". Class or lane?
- `TREC_NEXT_NODE` (+0x28): "node the car heads to" (P63_NearOnNode) vs P119_TrafficStep storing the road word under the car there, then copying +0x2c over it after the turn.
- `TREC_ROAD_DIST` (+0x18) measured from which end of the segment; `TREC_ROAD_LEFT` (+0x1c).
- `TREC_F03`, `TREC_F08`, `TREC_F34` (−1 = ignore, 0 = blocks the junction), `TREC_DIR2` (direction after the turn — confirm).
- Byte +5 (≠ 0 for cops in P60_NextTrafficCar, "in use" in ported91) and +0xc (car model kind, 1 = police?).
- State 4 = cop AI (P60_NextTrafficCar) — this answers director.c "kind 1 / state 4" and ported121 "state 4 (pursuit?)"; confirm and add `TRF_COP` to the state enum in ported133.c.
- ported118: record kind 3 and the value 0x82 written at +0x3c on a turn.
- ported51: traffic-light reading of byte +3 / direction parity.
- Older modules ported103.c / ported133.c still use raw offsets — convert to `TREC_*` when touched.

## Cameras and the replay director (`dircam.h`, director.c, dirnodes.c, ported59–61, ported133/134)

- Camera types 0x10 / 0x11: the game's own strings say "Static camera" / "Watch car camera", but the ported60 key handlers place a tripod as 0x11 and turn it into 0x10 when aiming at a car — confirm in the replay editor.
- `DCAM_HOLD` (+0x5c, "Holding camera position" in CameraDump): P61_StoreCamState stores the look-at target there, the tripod handlers a copy of the position.
- `DCAM_ANG_REL` / `DCAM_ANG_ABS` (+0x18 / +0x1c): relative vs absolute angle — the static-camera code writes the same absolute aim angle into both.
- `DCAM_FLAG48` / `P60_Var1373C0`: toggled by the director "toggle" key in watch-car mode, and also forces clipping in P82_SphereVis3D / P83_BoxVis.
- dirnodes: `DirectorUnk7C` (selected node?), `GetNodeParent` (is unk18 really a parent link?); directorstorage: v1 words +0x2c..+0x38 copied into two v2 blocks.
- Camera mode 6 in ported59 (map / overview?); director key group 10 in ported60 ("camera on a car").
- Open from part 1: Cine0/Cine1 in `MCS_SETCAMERASTART/END`.

## Menus and UI (ported4/5/12/15/17/19/45/53/54/57/66/77, menuselect.c, menustate.c, widgets.c, uihandlers*.c)

- Which screen each front-end table is (P57_MenuXXXXXX, P77_Menu407160 / 414C30 / 408770, 005754d8, 0057b740, 0054a008 …) — none mapped yet. A one-time run that logs the table address per visible screen would settle most of them.
- Menu item state values 0 / 2 / 3 (normal / disabled / highlighted?) — menuselect.c, ported15 `MENU_ITEM_STATE`, widgets.c.
- Settings: 00b87e2c (cop steering table → likely difficulty), the two volume sliders in widgets.c, 00575f50 (stereo / 3D sound?), 0125f3f8 (fog / draw distance?), 0125f3e0 (FOV?), G00B87E4C (night brightness?).
- Game-mode numbers: ported12 mode 0x105, ported71 / ported120 / ported141 score and table ids 1..0xb (Take a Ride, pursuit, …).
- ported124: which key bits are up/down/left/right in the replay camera save/restore.

## Mission script, ladder and results (ported16/42/96/97/98/123/139–141/147, mscript_ops.h, ladder.h)

- `ladder.h` names follow the MLADDER source keywords (SETCITY, ROOM, MISSION, RENDER, TRIGGER, IF, IFOK, ENDIF, QUITONFAIL, INTERVIEW, END); the interpreter comments come from P140_LadderRun. Codes 8 and 0xa are never emitted — unused?
- Result codes: 0xff0 in 00c810c4 (see findings), result 3 in 00c810e8 (ported98), fail-reason ids around 0x5a (ported16), ported56 end-countdown result codes.
- Script compiler: line result 10 (`MSC_LINE_OK_10`), 0xb vs 0 return of INCREASE/DECREASE (ported147), parser error 9 (`FINDCMD_NOTFOUND`) and 0xc ("missing word", ported96).
- The ×50 factor on script times (ported147, smallfuncs.c) — seconds → frames at 50 Hz?
- Event-script keywords for commands 4 and 0x32 (ported123); goal record fields (ported97); the 6 words + value 8 in ported147 / ported141 (+0x18 = 8 "record filled").
- Open from part 1: MScript code 0x52; the "marker" of ported140 (chase helicopter?).

## Sound (ported6/7/12/25/38/48/49/50/56/116/148, plat_snd.c)

- Sound driver entries 08 / 0C / 38 / 54 (ported48) and the per-voice assignment (ported116).
- P140_B1F434 (EAX / 3D sound switch, ported148); EAX listener property id 1 and value 2 (ported50); DSSPEAKER modes vs menu entries (ported38).
- Q00B87E90 = CD music option? (ported25); Q00B87E94 = Doppler / music toggle (ported6, ported115).
- `P25_TimerCnt` is decremented by P25_TimerStop but never incremented in the ported code.
- ported56: the looping sound picked by frame & 3 (siren?); ported75 +0x7c / +0x7e (engine revs / load?).
- plat_snd.c (native): a 65th live SDL timer would overwrite one of the 64 reused contexts.

## Rendering (ported11/15/22/23/28/32/40/47/52/69/76/80/82/87/89/111/112/135/143)

- Render classes 0..7 of map models (P80_Class) and object class 7 (ported89, drawn first with render state 0x13); class 5 detail option 00575ee8.
- Glide colour-combine argument sets (ported143), fog mode value 2 (ported69), what each fog pass draws.
- Vertex conversion A vs B (P23_ConvVertexA/B, ported76) and why two scale variants exist (ported23); P23_DevCaps blend bits.
- ported112: confirm format 5 = GR_TEXFMT_P_8 in the director texture path; ported40 slot flag 2 / palette argument.
- ported15: does the model array hold planes or plain normals; ported111: y-up-negative road surface quad.
- ported32 / ported39: device flag +0x518 (hardware device / system-memory back buffer).
- ported28: what the four per-pass calls (00427757, 0042793F, 004757D2, 00475906) do; ported27 dent texture indices (panels × damage stages).
- Searchlights level (ported135), skid ring B (ported117), surface flag 0x4000 at model +8 = "hard" surface (ported117 `MDL_F_HARD`).
