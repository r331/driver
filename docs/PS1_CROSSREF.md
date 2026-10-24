# Сверка с PS1-декомпиляцией Driver 1

Источник: [olink9/driver1-decomp](https://github.com/olink9/driver1-decomp), коммит `5bb6cda`
(matching-декомпиляция PS1-версии, цель US `SLUS_008.42`, 1217/1232 функций link-verified).
Имена PS1 взяты из `pilot/names-applied.tsv` / `symbol_addrs*.txt` этого репозитория; большая часть — имена
Driver 2 (REDRIVER2 / отладочные символы D2), которые авторы olink9 проверили на Driver 1.

**Лицензия.** У olink9/driver1-decomp нет общей лицензии (нет `LICENSE`); `THIRD_PARTY.md` описывает только
MIT-части из REDRIVER2/PsyCross. Поэтому код оттуда **не копировался**: в наш репозиторий перенесены только
имена функций и факты соответствия «функция X нашей версии ≈ функция Y PS1» со ссылкой на источник.
Логика и символы `re/game` не менялись — только комментарии.

## Итог

| Уверенность | Функций |
|---|---:|
| high | 21 |
| medium | 21 |
| low | 14 |
| **всего** | **56** |

Из ~200 именованных PS1-функций основного исполняемого файла (без PsyQ) примерно половина — платформенный
код, у которого на PC нет аналога: XM-плеер и SPU (`XM_*`, `JPlayNote`, `SetNote`, `DoVibrato`…),
CD-стриминг регионов и текстур (`UpdateSpool`, `data_cb_*`, `ready_cb_*`, `LoadRegionData`…), GTE-подразбиение
теней (`SubdivShadow`, `clipAgainstZ`, `sQuad`), загрузка с CD (`Loadfile`, `loadsectors`). Их не сопоставляли.
Оверлеи FRONTEND/MCARD/CRED/IVIEW в PS1 пока без имён (все `func_*`) — для имён они бесполезны.

* `high` — совпадает алгоритм: одинаковые характерные константы/формулы и поля записей, плюс согласованный
  граф вызовов. Только они помечены в коде комментарием
  `/* PS1: Имя @ 0xАДРЕС (olink9/driver1-decomp@5bb6cda, high) */` над определением и записаны в новую
  колонку `ps1` файла `docs/functions.csv`.
* `medium` — та же уникальная роль и согласованная структура вызовов, но PC-код заметно переписан
  (D3D/float вместо GPU/GTE) или функции слиты/разделены. Как факт не использовать без проверки.
* `low` — совпадает только назначение. Это гипотеза, не факт.

Полная таблица: `docs/ps1_crossref.csv` (наш адрес/имя, файл, PS1 имя, PS1 адрес, уверенность, обоснование).

## Методика

1. **Константы.** Из каждой PS1-функции (`src/pilot/*.c`) и каждой функции Game.exe (дамп Ghidra
   `out/Game_decomp.c`) извлечены числовые литералы ≥ 16; сходство — сумма IDF-весов общих констант
   (редкие в обоих корпусах значения весят больше), нормированная на размер функций. Так нашлись
   опорные пары (`StepOneCar`, `LongQuaternion2Matrix`, `Setup_Smoke`, `ROADS_GetRouteData`, `DoAutoDirect`).
2. **Граф вызовов.** От опорных пар — сопоставление вызываемых и вызывающих (Ghidra-вызовы через thunk
   разрешены по `docs/functions.csv`). Пример: `GlobalTimeStep` → `StepCars` → `StepOneCar` ↔
   `P142_CarsStep` → `P46_UpdateObjects` → `P142_WheelPhys`; `CarBuildingCollision` →
   `bcollided2d`/`bFindCollisionTime`/`bFindCollisionPoint` ↔ `P129_ObjHit` → `P100_BoxOverlap`/
   `P103_BoxContactTime`/`P102_BoxContact`.
3. **Поля записей.** Запись машины PS1 (`car_data`, шаг 0x18C, 25 машин) и PC (`P99_Cars` 00d077c0, шаг 0x148,
   66 машин) совпадают по смещениям: скорость 0x40, угл. скорость 0x4C, импульсы 0x58/0x68, колёса 0x78,
   точки контакта 0x88, позиция 0xC8; дальше раскладка расходится.
4. **Ручная проверка.** Каждая `high`-пара просмотрена бок о бок (PS1 C ↔ наш C). Строковые литералы почти
   не помогли: игровые строки PS1 лежат в rodata (в C их мало), а на PC тексты в файлах языков.

Рабочие скрипты сверки (не в репозитории): извлечение констант/графа и скоринг.

## Сопоставленные функции

### high
| Наш адрес | Наше имя | PS1 имя | PS1 адрес | Обоснование |
|---|---|---|---|---|
| `00499fb0` | `P100_BoxOverlap` | `bcollided2d` | `0x0003F2E0` | 2D OBB overlap leaf; callers exactly {CarBuildingCollision, bFindCollisionTime} <-> {P129_ObjHit, P103_BoxContactTime} |
| `0049a21d` | `P102_BoxContact` | `bFindCollisionPoint` | `0x0003F658` | third helper of CarBuildingCollision, leaf, contact point/normal after collision time |
| `0049a520` | `P103_BoxContactTime` | `bFindCollisionTime` | `0x0003F88C` | calls only bcollided2d (<->P100_BoxOverlap), called only by CarBuildingCollision (<->P129_ObjHit) |
| `0049b14d` | `P129_ObjHit` | `CarBuildingCollision` | `0x0003FF0C` | same car-vs-building box collision: bcollided2d -> bFindCollisionTime -> bFindCollisionPoint chain (PC 00499fb0/0049a520/0049a21d), damage, sparks/debris, lamp/object damage |
| `004a1d4c` | `P136_DrawWheels` | `DrawCarWheels` | `0x0003B208` | same wheel spin: wheel_speed/256 front and back, back wheels -700 while wheelspinning, clean/fast wheel model switch; shared constants 700, 0xf4, 0x88 |
| `004ad3b5` | `P127_FarDebris` | `AddGroundDebris` | `0x000426B4` | same logic: only when /speed/>99999, walks the nearby-object list, distance ring (PS1 7000..9000, PC 12000..15000), debris cap (PS1 40, PC 80), random offset + road lookup for y |
| `004b8d49` | `P125_SmokePuffs` | `Setup_Debris` | `0x00047824` | identical velocity formula ((r&0x7f00)*n*2, ((r&0x7f)-64)*n<<10, (r&0x7fff)-0x4000), type>=8 branch grey 60/60/60; our name "SmokePuffs" is misleading |
| `004b8f4e` | `P118_SkidFx` | `Setup_Smoke` | `0x00047A90` | distinctive shared constants 800000 (0xc3500), 0x10006/0x4006/0x2006 (smoke type flags), pool 0x3c/0x50; our name P118_SkidFx is narrower than the real role |
| `004c032a` | `P128_CarDeform` | `DentCar` | `0x0003E6A0` | same algorithm: per-zone damage (6 zones, up to 50 vertex indices, 0xff terminator) weights each vertex, vertex = clean + (damaged-clean)*w>>12, then damaged polys; PC P128_CarDeform |
| `004c582f` | `P127_AutoCamera` | `DoAutoDirect` | `0x0005B784` | auto camera director; distinctive shared constants 2023 (0x7e7), 1000, 70, 0x3ff; calls MapHeight<->P100_RoadHeight |
| `004c5c5d` | `P60_NextTrafficCar` | `SelectCameraCar` | `0x0005BC04` | same scan: cars i+1.. of state 4 (cops) near the player, returns index or 0; PS1 box /dx/,/dz/<8000, PC squared distance |
| `004d6ae7` | `P99_GearBox` | `GetEngineRevs` | `0x0004C610` | identical gear-selection loop: gear clamped 0..3, ws>>11 (=/2048), down/up thresholds per gear (low_ws / lowidl_ws when coasting, hi_ws), reverse -> gear 0; PC P99_GearBox |
| `004da76a` | `P94_QuatToMat` | `LongQuaternion2Matrix` | `0x0001B380` | quaternion->3x3 matrix; constant set identical (score 1.0), leaf called from body sync like GlobalTimeStep |
| `004dacee` | `P142_CarsStep` | `GlobalTimeStep` | `0x0001BAC0` | physics step: calls StepCars, CheckCarToCarCollisions, quaternion->matrix, debris/sparks/3D-sound/damage in the same roles |
| `004dd039` | `P100_RoadHeight` | `MapHeight` | `0x0001F5B0` | ground height at pos: same 1500-unit cell grid with 750 offset (0x5dc/0x2ee) and road-cell lookup; shared callers (auto camera, hubcap/debris bounce) |
| `004deb99` | `P103_CarsOverlap` | `CheckCarToCarCollisions` | `0x0001FAFC` | same broad-phase algorithm: AABB from orientation + velocity/8, y +-2400 (0x960), /16, pairwise overlap sets mayBeColliding (PC +0x13c) |
| `004defd1` | `P46_UpdateObjects` | `StepCars` | `0x0001D648` | thin loop calling StepOneCar for every car; sole callee P142_WheelPhys, sole caller GlobalTimeStep<->P142_CarsStep |
| `004df024` | `P142_WheelPhys` | `StepOneCar` | `0x0001D6E4` | same role (per-car wheel/suspension forces), same car-record offsets (vel 0x40, wheels 0x78, contacts 0x88), largest shared-constant score (1352), only caller = StepCars<->P46_UpdateObjects |
| `004e10e3` | `P126_WheelSmoke` | `jump_debris` | `0x00020844` | same logic: any wheel touching -> reset; airborne landing timer, random +-256 (0x1ff) position, y 200 above, emits Setup_Debris; timer differs (PS1 80/<75, PC 50/<45) |
| `00502787` | `P110_Gauge` | `DrawPercentageBar` | `0x00056BDC` | same PERCENTAGE_BAR record (active, x, y, w, h, position, max, colour, label, flags): clamp position<=max, fill direction by flags, frame + label; PC P110_Gauge (D3D) |
| `0051b65a` | `P72_RoadLookup` | `ROADS_GetRouteData` | `0x000217C8` | same road-cell decode: id=(v>>16)&0x3ff, low 16 bits, direction from v>>30; PC inlines the cell lookup (1500-unit cells, +750) |

### medium
| Наш адрес | Наше имя | PS1 имя | PS1 адрес | Обоснование |
|---|---|---|---|---|
| `0049cad4` | `P134_CamCollide` | `CameraCollisionCheck` | `0x0003C998` | camera vs collision boxes of map objects in the camera's cell (sphere vs box); PC P134_CamCollide (float rewrite) |
| `004aae34` | `P12_Fn004AAE34` | `HandleDebris` | `0x00048660` | per-frame debris/hubcap/particle update (calls MoveHubcap<->P119_Hubcap); PC splits update (P12_Fn004AAE34) from drawing (P69_SceneFrame) |
| `004ac779` | `P122_CarGlow` | `PlacePoolForCar` | `0x00040BAC` | headlight pool quad on the road in front of a car (D2 DEBRIS.C PlacePoolForCar); PC P122_CarGlow |
| `004b05ea` | `P111_DebrisIcon` | `DisplayDebris` | `0x000481C8` | draws one debris piece (rotation index into shape tables, colour, leaf kind); PC P111_DebrisIcon is the D3D version |
| `004b418d` | `P143_SunFlare` | `DrawLensFlare` | `0x00046E44` | sun lens-flare ghosts with on-screen visibility test of the sun pixels (PS1 StoreImage, PC LFB read); PC P143_SunFlare |
| `004b6deb` | `P111_Flare` | `ShowFlare` | `0x00045718` | single light flare sprite with depth bias; PC P111_Flare (D3D) |
| `004b955c` | `P125_ObjABurst` | `func_00047FA4 (Setup_Sparks in PS1 comment)` | `0x00047FA4` | PS1 comment calls it Setup_Sparks (D2 name, not applied in PS1 symbols); same caller set (StepOneCar, CarBuildingCollision, GlobalTimeStep), spark pool emitter |
| `004b955c` | `P125_ObjABurst` | `func_00047FA4 (Setup_Sparks in PS1 comment)` | `0x00047FA4` | PS1 comment calls it Setup_Sparks (D2 name, not applied in PS1 symbols); same call sites (StepOneCar, CarBuildingCollision, GlobalTimeStep) |
| `004c0c6f` | `P119_Hubcap` | `MoveHubcap` | `0x0003F01C` | flying hubcap of the player car with road bounces (MapHeight); PC P119_Hubcap merges LoseHubcap + MoveHubcap + draw (draw flag) |
| `004c0c6f` | `P119_Hubcap` | `LoseHubcap` | `0x0003ED78` | hubcap detach logic, only called from MoveHubcap in PS1; in PC merged into P119_Hubcap |
| `004cadb5` | `P130_Lightning` | `DoLightning` | `0x0004A654` | unique role: lightning flash in storms; PC P130_Lightning (rendering rewritten) |
| `004cc801` | `P116_Reflections` | `DisplayLightReflections` | `0x0004A398` | unique role: reflections of lights on the wet road at night (D2 DEBRIS.C); PC version is a D3D rewrite (P116_Reflections) |
| `004dacee` | `P142_CarsStep` | `SetShadowPoints` | `0x0001D3EC` | computes the 4 ground points under the car via FindSurface; in PC this is inlined into P142_CarsStep / P142_WheelPhys (writes CAR_GROUND_PT 0x88) |
| `004dd262` | `P103_GroundAt` | `func_0001EEB4 (FindSurface in PS1 comment)` | `0x0001EEB4` | PS1 comment: FindSurface; PC P103_GroundAt — ground probe called from StepOneCar<->WheelPhys |
| `004e3b19` | `ReturnZero004E3B19` | `func_00035B50 (SetPadVibration-like in PS1 comment)` | `0x00035B50` | PS1 comment: SetPadVibration-like; PC slot returns 0 (no vibration), same call sites in StepOneCar/CarBuildingCollision |
| `004ec336` | `P62_LoadMapHeader` | `ProcessMapLump` | `0x0002DFEC` | map header lump: cells across/down -> world size, half sizes; PC P62_LoadMapHeader (PS1 also derives regions for CD streaming) |
| `004ee8f4` | `P89_DrawMap` | `DrawMapPSX` | `0x0002C8FC` | main city draw: walks visible cells, builds per-yaw matrices; best constant match among all PC functions; PC P89_DrawMap |
| `00504cad` | `P117_Radar` | `DrawOverheadMap` | `0x0005474C` | in-game radar/overhead map; both call the compass (DrawCompass<->P107_Compass) and the map-tile upload (LoadMapTile<->P100_RadarMap); PC P117_Radar |
| `00506fa0` | `P107_Compass` | `DrawCompass` | `0x00053E54` | compass needle drawn by the overhead map / radar; PC P107_Compass |
| `00520278` | `P138_CarShadow` | `PlaceShadowForCar` | `0x0002ADEC` | car shadow over the four ground points; PC P138_CarShadow (D3D grid instead of GTE subdivision) |
| `00523cda` | `P97_SndStart` | `Start3DSoundVolPitch` | `0x0004D7E4` | 3D positional sound start called from the same physics/collision sites; PC sound API differs (DirectSound) |

### low
| Наш адрес | Наше имя | PS1 имя | PS1 адрес | Обоснование |
|---|---|---|---|---|
| `0040a8b0` | `P122_FontIcons` | `LoadFont` | `0x0005C99C` | builds the font glyph table; PC P122_FontIcons — role only |
| `0040abac` | `P116_Text` | `PrintString` | `0x0005CC68` | draws a string with the current font; PC P116_Text — role only |
| `0040b1cc` | `P58_TextWidth` | `StringWidth` | `0x0005C7EC` | text width in a font; PC P58_TextWidth — role only |
| `004a32e9` | `P96_PickChair` | `FindSeated` | `0x00060E4C` | seated pedestrians (D2 SEATED) correspond to PC "chairs" (P78_LoadChairs/P99_ChairHit); picking algorithm differs (PS1 cyclic near player, PC random per cell) |
| `004b10ce` | `P135_SmokeObj` | `DisplaySmoke` | `0x00048E88` | draws one smoke puff sprite; PC P135_SmokeObj — role only |
| `004b23f8` | `P135_SparkQuad` | `DisplaySpark` | `0x00045CEC` | draws a spark streak between old and new position; PC P135_SparkQuad — role only |
| `004c61b2` | `FindCameraForFrame` | `FindNextChange` | `0x00058D70` | finds the replay camera for a frame; PS1 fixed 60-slot array, PC sorted malloc list (FindCameraForFrame) |
| `004c813d` | `P124_HandleDirector` | `ControlReplay` | `0x00059D94` | per-frame replay/director control; PC director UI is redesigned (node menu), P124_HandleDirector — role only |
| `004cbc1e` | `P131_RainDraw` | `DrawRainDrops` | `0x00049590` | draws rain drops; PC P131_RainDraw — role only |
| `004cc008` | `P130_RainSpawn` | `AddRainDrops` | `0x00049DB8` | spawns rain drops around the camera; PC P130_RainSpawn — role only |
| `004cc1a2` | `P131_Splash` | `DisplaySplashes` | `0x0004A064` | rain splashes on the road; PC P131_Splash — role only |
| `004d35b2` | `P125_LevelLoad` | `ShowLoadingScreen` | `0x000508B0` | shows the loading picture before a level; PC P125_LevelLoad (LOADING.BMP) — role only |
| `004d38b7` | `P145_LevelLoad` | `LoadGameLevel` | `0x0002258C` | loads and initialises the level; PC P145_LevelLoad — role only |
| `00504479` | `P100_RadarMap` | `LoadMapTile` | `0x00056278` | copies the map tile around the player into the radar texture; PC P100_RadarMap (different storage) |

## Глобальные переменные (только факты, в коде не помечены)

| Наш символ | PS1 | Уверенность | Основание |
|---|---|---|---|
| `P99_Cars` (00d077c0, шаг 0x148) | `car_data` (0x9B0A4, шаг 0x18C) | high | совпадают смещения vel/avel/wheels/contacts/pos во всех high-функциях физики |
| `P14_00b87e84` | `gNight` (0x96850) | medium | оба — флаг ночи уровня, проверяются только на 0/≠0 (наш флаг уже используется как «ночь» динамической музыкой) |
| пул `P12_0110b260` (записи 0x3C, 200) | `debris[60]` (0xBABC0, записи 40 байт) | medium | пул, который заполняет `Setup_Debris` ↔ `P125_SmokePuffs` |

Адресные имена вида `P14_00b87e84` / `P11_00ba52d0` в `re/game` — в основном **глобальные переменные**, а не
функции; у PS1 для данных названо лишь 43 символа (`pilot/names-applied-data.tsv`), поэтому сопоставились единицы.

## Полезные находки

* `P125_SmokePuffs` (004b8d49) — на самом деле `Setup_Debris` (обломки, не дым); `P118_SkidFx` (004b8f4e) —
  `Setup_Smoke`; `P125_ObjABurst` — вероятно `Setup_Sparks`.
* `P128_CarDeform` = `DentCar`, `P99_GearBox` = `GetEngineRevs`, `P110_Gauge` = `DrawPercentageBar`,
  `P60_NextTrafficCar` = `SelectCameraCar`, `P126_WheelSmoke` = `jump_debris`, `P127_FarDebris` = `AddGroundDebris`.
* Широкая фаза столкновений `P103_CarsOverlap` = `CheckCarToCarCollisions`; столкновение с объектами карты
  `P129_ObjHit` = `CarBuildingCollision` с тремя помощниками из BCOLLIDE.C.
* PC-«стулья» (`P78_LoadChairs`, `P99_ChairHit`, `P96_PickChair`) соответствуют сидящим пешеходам PS1/D2 (`SEATED`, `FindSeated`).
* `SetShadowPoints` на PC встроена в физику: её результат — `CAR_GROUND_PT` (0x88) в записи машины.

## Расхождения PC и PS1, которые стоит проверить (логика не менялась)

1. `jump_debris` ↔ `P126_WheelSmoke`: таймер после приземления PS1 80 кадров и выброс при < 75, PC 50 и < 45
   плюс случайный фильтр `rand & 0x3f < b`; PS1 не вызывает `func_00020998`, когда `D_00096834` (по данным olink9 — `gTimeOfDay`) == 6, PC вызывает свой аналог (`AddVelocity004E122C`) всегда.
2. `AddGroundDebris` ↔ `P127_FarDebris`: кольцо дальности 7000..9000 → 12000..15000, лимит 40 → 80, разброс
   ±512 → ±1024 (похоже на сознательное увеличение дальности на PC).
3. `Setup_Debris` ↔ `P125_SmokePuffs`: PS1 ночью делит цвет обломков пополам (`gNight`), цвет — из таблицы по
   `type >> 16`; PC берёт цвет по `S_00D1192C & 7` или «синий» флаг и ночью не затемняет; граница типов
   `< 8` (PS1) против `< 5` (PC); поле `pos` = `i & 0x1f` против `(кадр + i) & 0x1f`.
4. `SelectCameraCar` ↔ `P60_NextTrafficCar`: PS1 — квадрат |dx|,|dz| < 8000, PC — круг (`COP_FOLLOW_DIST2`).
5. `CheckCarToCarCollisions` ↔ `P103_CarsOverlap`: PS1 строит полуразмеры из фиксированных 585/209 (+90),
   PC — из размеров модели (+0x164..0x168); PS1 в режимах 3/6 принудительно ставит флаг машине 23 и в 7/8
   сбрасывает `D_0009D564[0]`, на PC этого нет (вместо этого `ClearFlagByte0048FBBA`).
6. `DrawPercentageBar` ↔ `P110_Gauge`: биты флагов переставлены (PS1 бит 0 = справа налево; PC бит 1 = справа
   налево, бит 0 = вертикальная) — это представление, не ошибка, но при переносе имён полей учесть.
