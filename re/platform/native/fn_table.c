/* v2.03: сгенерировано tools/gen_fn_table.py из re_hook(...) platform/win32/install.c — адрес Game.exe → перенос (re_fn). */
#include <stdint.h>
#include <stddef.h>
typedef void (*re_fn_t)(void);
typedef struct { uint32_t addr; re_fn_t fn; } re_fnent_t;
void ActorStep00494678(void);
void AddCamera(void);
void AddClamp4095_004D2ADE(void);
void AddDefaultCamera(void);
void AddDirectorCamera(void);
void AddEntry_00426ABC(void);
void AddToCounter00519D09(void);
void AddTripodCamera(void);
void AddUnique_004C1F9B(void);
void AddVelocity004E122C(void);
void AdvanceOpPtr0042F7B8(void);
void AllocMapBuffer300000(void);
void AllocMapBuffer400000(void);
void AllocSlot00492508(void);
void AngleToDir00514103(void);
void AnyKeyHeld_004E3871(void);
void BackOrDirector_005103C4(void);
void BackupCameraState(void);
void Call004A2C08(void);
void Call004BF476(void);
void Call004BF485(void);
void Call004C020E(void);
void Call004D2D85(void);
void Call00522323(void);
void Call3_0040C455(void);
void CallIf424A02(void);
void CallIfD14EE4(void);
void CameraDump(void);
void CameraFrameDistance(void);
void Chain004D5FFC(void);
void ChangeCamera(void);
void ChangeTripodCamera(void);
void ClampCameraHeight(void);
void Clear110E180(void);
void Clear2C3B8(void);
void ClearDirectorTable(void);
void ClearDirectorTables(void);
void ClearEntry_004BF8A1(void);
void ClearField2C_00502680(void);
void ClearFlagByte0048FBBA(void);
void ClearPair004D6D68(void);
void ClearPairs004D6C20(void);
void ClearSlots004D61CF(void);
void ClearSlots004D8C23(void);
void ClearTables_004AB780(void);
void Copy400_00407C27(void);
void Copy54A838(void);
void CopyBDF984(void);
void CopyShort9_005278FB(void);
void CopySlotTemplate004A1010(void);
void CopySlots_0040AA82(void);
void CopyTable_004D6E9F(void);
void CopyVec3_005265BC(void);
void CopyVec3_0052797A(void);
void CopyWord0041AD8D(void);
void CopyWords8000(void);
void CountActive_005120A7(void);
void CountByOwner_0048F2E7(void);
void CountNearbyCars(void);
void CountTrailingZeros00421C72(void);
void CounterDecrement004D97B8(void);
void CreditsNext00519D2C(void);
void CreditsPrev00519D70(void);
void CreditsTick005193D4(void);
void CursorSet004D94B7(void);
void CursorWrap004D9478(void);
void CycleDec0040F364(void);
void CycleInc0040E918(void);
void CycleInc0040F3AD(void);
void Dec145934(void);
void DeleteCamera(void);
void DeleteWaypointFile(void);
void Dev00424633(void);
void Dev00424647(void);
void Dev004246BD(void);
void Dev0042480D(void);
void Dev00424858(void);
void DirNopStub(void);
void Dispatch0041D50E(void);
void Dispatch0048A68E(void);
void Dot3_00526029(void);
void Dot4_005270BD(void);
void DrainStackC200F(void);
void DrawBanner_004F5D98(void);
void DrawCornerIndicator(void);
void DrawFrame_004A9DDC(void);
void DrawNode(void);
void DrawNodeChain(void);
void DrawNodeMarker(void);
void DrawNodeMarkersChain(void);
void DrawTextLine004FBBC5(void);
void DropCameraBackup(void);
void DrvCall004246D1(void);
void DrvSetMode0042655A(void);
void DumpWaypoints(void);
void ExchangeTable00522F2A(void);
void FillRange004D2B16(void);
void FillTable8_0041D954(void);
void FillThresholds_004A6370(void);
void FindCameraById(void);
void FindCameraForFrame(void);
void FindFreeEven_0048A4E6(void);
void FindNearestCamera(void);
void FindNodeAtPixel(void);
void FindNodeById(void);
void FindNodeByLink(void);
void FindOrAdd_004BB11F(void);
void FindSlot_004A2DB5(void);
void FlagSet0127104C(void);
void FloatStep00409A91(void);
void FloatStep00409ACA(void);
void FloatStep00409B03(void);
void FloatStep00409B3C(void);
void FreeBuf004FC57B(void);
void FreeBuffer5FED98(void);
void FreeBufferD17EC8(void);
void FreeBuffer_004F30E6(void);
void FreeBufs00516E2E(void);
void FreeCameraList(void);
void FreeDirectorBuffer(void);
void FreeDirectorData(void);
void FreeMapBuffer300000(void);
void FreeMapBuffer400000(void);
void FreeMapBufs004ECE1A(void);
void Fwd0042482B(void);
void Fwd004D262C(void);
void Fwd004D2D9F(void);
void Fwd004FC0C7(void);
void Fwd00513CF9(void);
void GameCall00424661(void);
void Get138(void);
void Get138Entry148(void);
void Get4Words004E4379(void);
void GetB31E18(void);
void GetCamera(void);
void GetCameraTypeName(void);
void GetConst0041FA5E(void);
void GetNodeParent(void);
void GetRect_0048F34C(void);
void GetVarA421A4(void);
void GetVarA421A8(void);
void GetVarB1C0D8(void);
void GetWaypointAfterFrame(void);
void GetWaypointForFrame(void);
void GlobalSet0040A5C6(void);
void GlobalSet0040B0A4(void);
void GlobalSet004122C4(void);
void GlobalSet004126DF(void);
void GlobalSet0041351C(void);
void GlobalSet00413691(void);
void GlobalSet0041390C(void);
void GlobalSet00413B7C(void);
void GlobalSet0041640C(void);
void GlobalSet00416433(void);
void GlobalSet0041648A(void);
void GlobalSet00417A2E(void);
void GlobalSet00419F80(void);
void GlobalSet004964E2(void);
void GlobalSet004AADDF(void);
void GlobalSet004C09B9(void);
void GlobalSet004CA0C0(void);
void GlobalSet004CF100(void);
void GlobalSet004E38FE(void);
void GlobalSet004E3911(void);
void GlobalSet00510349(void);
void GlobalSet0051040F(void);
void GlobalSet00510550(void);
void GlobalSet00510595(void);
void GlobalSet0051065B(void);
void GlobalSet00511378(void);
void GlobalSet005113B1(void);
void GlobalSet00519DDB(void);
void GlobalSet00519DE7(void);
void GlobalSet0051BD78(void);
void GlobalSet0051D811(void);
void Inc0B1FFBC(void);
void InitChannels_0052436A(void);
void InitFlags004946DA(void);
void InitFpuCw_005283E2(void);
void InitIdentityPalette_0041D8E9(void);
void InitMapState4D3426(void);
void InitObjState_00514BC7(void);
void InitSlotsTable_004AB0DF(void);
void InitSoundVolumes_00523C56(void);
void InitSubsys004BA443(void);
void InitVec_00526582(void);
void InitXform_005263FE(void);
void InsertCamera(void);
void IsButtonActive_004E3924(void);
void IsCameraCarFarEnough(void);
void IsFlag80_00514E4C(void);
void IsFlagSetNotMasked_004E383A(void);
void IsKeyOnly004E38B4(void);
void IsKeyOnly004E38D9(void);
void IsSlotActive00524473(void);
void IsVar112B284Lt8(void);
void Lerp4_00527885(void);
void LoadArrowIcons00417353(void);
void LoadDirector(void);
void LoadFsin_00525E50(void);
void LoadShort3FromPtr(void);
void LoadSliderIcons00417620(void);
void LoadTrail004FBE96(void);
void LoadWaypoints(void);
void LogWaypoint(void);
void Mask004D9028(void);
void MaskShift_00421C1D(void);
void Mat3MulT_005284AC(void);
void Mat3Mul_0052859A(void);
void MatIdentity3_0052614F(void);
void Menu549FBC(void);
void Menu549FCC(void);
void MenuAction_0041645B(void);
void MenuAction_004164B2(void);
void MenuAddItem004DC8B0(void);
void MenuAllRowsTo2_00412280(void);
void MenuAllRowsTo2_0041269B(void);
void MenuBack005103EC(void);
void MenuBits0041556C(void);
void MenuBits0050F8F2(void);
void MenuBtn00414264(void);
void MenuBtn00414376(void);
void MenuBtn00414488(void);
void MenuBtn0041459A(void);
void MenuCallAction40CD17(void);
void MenuClick004F8ACC(void);
void MenuCopyPos(void);
void MenuCounter5D577CInc(void);
void MenuDecVar5759A4(void);
void MenuDecVarB87E4C(void);
void MenuEnterMode1(void);
void MenuEnterMode2(void);
void MenuEnterMode3(void);
void MenuEnterMode4(void);
void MenuEnterMode5(void);
void MenuEnterMode6(void);
void MenuEnterMode7(void);
void MenuFlag54A0BCClear(void);
void MenuFlag54A0BCSet(void);
void MenuFlagSet(void);
void MenuFlagUpdate(void);
void MenuHiliteRed004106E1(void);
void MenuHiliteRed00411A31(void);
void MenuHiliteWhite0041074D(void);
void MenuHiliteWhite00411A9D(void);
void MenuIncVar5759A4(void);
void MenuIncVarB87E4C(void);
void MenuLeave0040E8FF(void);
void MenuLeave0040E957(void);
void MenuLeave0040E99C(void);
void MenuLeave0040EA3E(void);
void MenuLeave004136DA(void);
void MenuLeave00413728(void);
void MenuLeave00413776(void);
void MenuLeave004137C4(void);
void MenuLeave00413961(void);
void MenuLeave004139AF(void);
void MenuLeave004139E6(void);
void MenuLeave00413A1D(void);
void MenuLeave00413A54(void);
void MenuLeave00413BE5(void);
void MenuLeave00413C17(void);
void MenuLeave00413C49(void);
void MenuLeave00413C7B(void);
void MenuLeave00413CAD(void);
void MenuLeave00416072(void);
void MenuLeave004160D7(void);
void MenuLeave0041613C(void);
void MenuLeave004161A1(void);
void MenuLeave00416449(void);
void MenuLeave004164A0(void);
void MenuLeaveMode1(void);
void MenuLeaveMode2(void);
void MenuLeaveMode3(void);
void MenuLeaveMode4(void);
void MenuLeaveMode5(void);
void MenuLeaveMode6(void);
void MenuLeaveMode7(void);
void MenuMark00412228(void);
void MenuMusic0050F8A2(void);
void MenuMusic0050F8CC(void);
void MenuPageNext00417F59(void);
void MenuPagePrev00417FAC(void);
void MenuPick0040FEA0(void);
void MenuPick0040FF5A(void);
void MenuPick00410014(void);
void MenuPick004100CE(void);
void MenuPick00410188(void);
void MenuPick00410242(void);
void MenuPick004102FC(void);
void MenuPick004103B6(void);
void MenuPick00410470(void);
void MenuPick0041052A(void);
void MenuPick004105E4(void);
void MenuPick0041069E(void);
void MenuQuality004088DB(void);
void MenuQuality0050FA70(void);
void MenuRate00415623(void);
void MenuRate0050F930(void);
void MenuRed0040766D(void);
void MenuRed00409C85(void);
void MenuRed00415904(void);
void MenuRed00419D3E(void);
void MenuRedraw409231(void);
void MenuRedraw4092D8(void);
void MenuRedraw40937F(void);
void MenuRedraw409426(void);
void MenuRedraw4094CD(void);
void MenuReturnOne(void);
void MenuRowsIf0To2_00404E7E(void);
void MenuRowsTo2_00412254(void);
void MenuRowsTo2_0041266F(void);
void MenuRowsTo3_00404E52(void);
void MenuRowsTo3_00412643(void);
void MenuSelect00407334(void);
void MenuSelect00407421(void);
void MenuSelect004074FA(void);
void MenuSelect004075BF(void);
void MenuSelect00408864(void);
void MenuSelect0040891D(void);
void MenuSelect004089F2(void);
void MenuSelect00408A8C(void);
void MenuSelect00408B26(void);
void MenuSelect00408BC0(void);
void MenuSelect00408C95(void);
void MenuSelect00408D2F(void);
void MenuSelect00408DC9(void);
void MenuSelect00408E63(void);
void MenuSelect00408EFD(void);
void MenuSelect00408F97(void);
void MenuSelect00409031(void);
void MenuSelect004090CB(void);
void MenuSelect004091A0(void);
void MenuSelect00409247(void);
void MenuSelect004092EE(void);
void MenuSelect00409395(void);
void MenuSelect0040943C(void);
void MenuSelect0040FE29(void);
void MenuSelect0040FEE3(void);
void MenuSelect0040FF9D(void);
void MenuSelect00410057(void);
void MenuSelect00410111(void);
void MenuSelect004101CB(void);
void MenuSelect00410285(void);
void MenuSelect0041033F(void);
void MenuSelect004103F9(void);
void MenuSelect004104B3(void);
void MenuSelect0041056D(void);
void MenuSelect00410627(void);
void MenuSelect0041104B(void);
void MenuSelect00411100(void);
void MenuSelect004111B5(void);
void MenuSelect0041126A(void);
void MenuSelect0041131F(void);
void MenuSelect004113D4(void);
void MenuSelect00411489(void);
void MenuSelect0041153E(void);
void MenuSelect004115F3(void);
void MenuSelect004116A8(void);
void MenuSelect0041175D(void);
void MenuSelect00411812(void);
void MenuSelect004118C7(void);
void MenuSelect0041197C(void);
void MenuSelect00414F9D(void);
void MenuSelect00415111(void);
void MenuSelect00415230(void);
void MenuSelect00415323(void);
void MenuSelect004153B3(void);
void MenuSelect00415456(void);
void MenuSelect004154F5(void);
void MenuSelect004155AC(void);
void MenuSelect00415666(void);
void MenuSelect00415718(void);
void MenuSelect004157B0(void);
void MenuSet54A844Off(void);
void MenuSet54A844On(void);
void MenuSet54A854Off(void);
void MenuSet54A854On(void);
void MenuSet54ACD4To3(void);
void MenuSet54ACF4To3(void);
void MenuSet54AD14To3(void);
void MenuSet54AD34To3(void);
void MenuSet54BE5CTo2(void);
void MenuSet54BE5CTo3(void);
void MenuSet54BE7CTo2(void);
void MenuSet54BE7CTo3(void);
void MenuSetByte5D77C1(void);
void MenuSetColor(void);
void MenuSetPos(void);
void MenuSetVals5D77C0(void);
void MenuSlotHandler0040737A(void);
void MenuSlotHandler00407605(void);
void MenuSlotHandler004088AA(void);
void MenuSlotHandler00408963(void);
void MenuSlotHandler00408A38(void);
void MenuSlotHandler00408AD2(void);
void MenuSlotHandler00408B6C(void);
void MenuSlotHandler00408C06(void);
void MenuSlotHandler00408CDB(void);
void MenuSlotHandler00408D75(void);
void MenuSlotHandler00408E0F(void);
void MenuSlotHandler00408EA9(void);
void MenuSlotHandler00408F43(void);
void MenuSlotHandler00408FDD(void);
void MenuSlotHandler00409077(void);
void MenuSlotHandler00409111(void);
void MenuSlotHandler0040FE6F(void);
void MenuSlotHandler0040FF29(void);
void MenuSlotHandler0040FFE3(void);
void MenuSlotHandler0041009D(void);
void MenuSlotHandler00410157(void);
void MenuSlotHandler00410211(void);
void MenuSlotHandler004102CB(void);
void MenuSlotHandler00410385(void);
void MenuSlotHandler0041043F(void);
void MenuSlotHandler004104F9(void);
void MenuSlotHandler004105B3(void);
void MenuSlotHandler0041066D(void);
void MenuSlotHandler00411091(void);
void MenuSlotHandler00411146(void);
void MenuSlotHandler004111FB(void);
void MenuSlotHandler004112B0(void);
void MenuSlotHandler00411365(void);
void MenuSlotHandler0041141A(void);
void MenuSlotHandler004114CF(void);
void MenuSlotHandler00411584(void);
void MenuSlotHandler00411639(void);
void MenuSlotHandler004116EE(void);
void MenuSlotHandler004117A3(void);
void MenuSlotHandler00411858(void);
void MenuSlotHandler0041190D(void);
void MenuSlotHandler004119C2(void);
void MenuSlotHandler00414FE3(void);
void MenuSlotHandler00415157(void);
void MenuSlotHandler00415276(void);
void MenuSlotHandler00415369(void);
void MenuSlotHandler004153F9(void);
void MenuSlotHandler0041549C(void);
void MenuSlotHandler0041553B(void);
void MenuSlotHandler004155F2(void);
void MenuSlotHandler004156AC(void);
void MenuSlotHandlerReset004091F3(void);
void MenuSlotHandlerReset0040929A(void);
void MenuSlotHandlerReset00409341(void);
void MenuSlotHandlerReset004093E8(void);
void MenuSlotHandlerReset0040948F(void);
void MenuSlotHandlerReset0041576B(void);
void MenuSlotHandlerReset00415803(void);
void MenuSound0050F781(void);
void MenuSoundCh004156DD(void);
void MenuSoundCh0050F971(void);
void MenuStateSetFour(void);
void MenuTableGet54B010(void);
void MenuToggle00408994(void);
void MenuToggle00408C37(void);
void MenuToggle00409142(void);
void MenuToggle0050FE26(void);
void MenuToggle0050FEE5(void);
void MenuToggle00510028(void);
void MenuToggle55384CRedraw(void);
void MenuToggle553850Redraw(void);
void MenuToggle55C974Redraw(void);
void MenuToggle575EE8Redraw(void);
void MenuToggle575F24Call40EA70(void);
void MenuToggle575F24Call419B35(void);
void MenuToggle575F30Redraw(void);
void MenuToggle575F3CRedraw(void);
void MenuToggle575F40Call414D1F(void);
void MenuToggle575F44Redraw(void);
void MenuToggle575F48Call40EA70(void);
void MenuToggle575F48Call419B35(void);
void MenuToggleB201DCRedraw(void);
void MenuToggleB31F04Redraw(void);
void MenuToggleD118C8Redraw(void);
void MenuToggleOptB87E9C(void);
void MenuToggleOptBDFA44(void);
void MenuToggleOptBDFA48(void);
void MenuToggleOptBDFA4C(void);
void MenuToggleOptBDFA50(void);
void MenuToggleOptBDFA54(void);
void MenuToggleOptBDFA58(void);
void MenuTri0040E9B5(void);
void MenuTri00419C8C(void);
void MenuVar54A0CCClear(void);
void MenuWhite004076E2(void);
void MenuWhite00409CFA(void);
void MenuWhite00415979(void);
void MenuWhite00419DB3(void);
void MenuWhite0041AF29(void);
void NegateCamZ004EAF8D(void);
void NegateVec3To_00526FE3(void);
void NegateVec3_00526FB6(void);
void NegateVec3_005270F6(void);
void NextPcar0040475E(void);
void NoopFn0041F81E(void);
void NoopFn0041FA49(void);
void NoopFn0041FA50(void);
void NoopFn0041FA57(void);
void NoopFn0041FA7D(void);
void NoopFn0041FA8B(void);
void NoopFn0041FA92(void);
void NoopFn0041FAB9(void);
void NoopFn0041b054(void);
void NoopFn0041b3a6(void);
void NoopFn0041d9af(void);
void NoopFn0041d9b6(void);
void NoopFn0041d9bd(void);
void NoopFn0041d9c4(void);
void NoopFn0041d9cb(void);
void NoopFn0041ddbe(void);
void NoopFn0041e075(void);
void NoopFn0041e07c(void);
void NoopFn0041e083(void);
void NoopFn0041e207(void);
void NoopFn0041e20e(void);
void NoopFn0041e456(void);
void NoopFn0041e45b(void);
void NoopFn0041e510(void);
void NoopFn0041e517(void);
void NoopFn0041e51e(void);
void NoopFn0041e525(void);
void NoopFn0041eb2e(void);
void NoopFn0041eb35(void);
void NoopFn0041eb3c(void);
void NoopFn0041eb43(void);
void NoopFn0041eb4a(void);
void NoopFn0041eb69(void);
void NoopFn0041eb70(void);
void NoopFn0041eb77(void);
void NoopFn0041eb7e(void);
void NoopFn0041eb85(void);
void NoopFn0041ed00(void);
void NoopFn0041ed07(void);
void NoopFn0041ed1a(void);
void NoopFn0041ed21(void);
void NoopFn0041ed26(void);
void NoopFn0041ed39(void);
void NoopFn0041ed45(void);
void NoopFn0041ed4c(void);
void NoopFn0041ed63(void);
void NoopFn0041ed7c(void);
void NoopFn0041f485(void);
void NoopFn0041f48c(void);
void NoopFn0041f493(void);
void NoopFn0041f49a(void);
void NoopFn0041f56f(void);
void NoopFn0041f576(void);
void NoopFn0041f6a2(void);
void NoopFn0041f72d(void);
void NoopFn0041f753(void);
void NoopFn0041f75a(void);
void NoopFn0041f761(void);
void NoopFn0041f768(void);
void NoopFn0041f7f0(void);
void NoopFn0041f809(void);
void NoopFn0041f810(void);
void NoopFn0041f817(void);
void NoopFn0041fab4(void);
void NoopFn0042243f(void);
void NoopFn0048a4e1(void);
void NoopFn0048bd3b(void);
void NoopFn00493f95(void);
void NoopFn004946d0(void);
void NoopFn004946d5(void);
void NoopFn004F89EB(void);
void NoopFn004aad60(void);
void NoopFn004af2f8(void);
void NoopFn004bf471(void);
void NoopFn004bf480(void);
void NoopFn004d1a84(void);
void NoopFn004d1a89(void);
void NoopFn0050f9aa(void);
void NoopFn0050f9af(void);
void NoopFn00510102(void);
void NoopFn00510107(void);
void NoopFn0051406e(void);
void NoopFn00519d1d(void);
void NoopFn00519e23(void);
void NoopFn00519e28(void);
void NoopFn00519e2d(void);
void NoopFn00519e32(void);
void NoopFn00528455(void);
void ObjInit00514C43(void);
void P100_Billboards(void);
void P100_BoxFace(void);
void P100_BoxOverlap(void);
void P100_CarHit(void);
void P100_CarRevs(void);
void P100_CarSounds(void);
void P100_ClipFar(void);
void P100_ClipNear(void);
void P100_DebrisInit(void);
void P100_DrawParts(void);
void P100_DrawPartsB(void);
void P100_FreeCamKeys(void);
void P100_GhostNear(void);
void P100_GoalsCheck(void);
void P100_IconLfb2x(void);
void P100_LfbFormat(void);
void P100_MarkerSpawn(void);
void P100_MirrorMask(void);
void P100_PadMenuInit(void);
void P100_PartStep(void);
void P100_RadarMap(void);
void P100_RecInput(void);
void P100_RecRead(void);
void P100_ReplayMenuInit(void);
void P100_RiffFromRes(void);
void P100_RoadHeight(void);
void P100_RoadHeightF(void);
void P100_RoadRect(void);
void P100_RoadRectAbs(void);
void P100_TrafficSlot(void);
void P101_AddObjB(void);
void P101_BoxHit(void);
void P101_CarGround(void);
void P101_CarLight(void);
void P101_CarSkids(void);
void P101_ClipFarUV(void);
void P101_ClipNear5A(void);
void P101_ClipNear5B(void);
void P101_ClipNearRGB(void);
void P101_ClipNearUV(void);
void P101_ClipNearUVW(void);
void P101_DebrisBounce(void);
void P101_DebrisFly(void);
void P101_Drips(void);
void P101_GoalTick(void);
void P101_MirrorMaskR(void);
void P101_Pal16(void);
void P101_Pal32(void);
void P101_PartFall(void);
void P101_PartTurn(void);
void P101_PickCell(void);
void P101_Proj(void);
void P101_ProjT(void);
void P101_ReplayBegin(void);
void P101_RoadBounds(void);
void P101_RoadNode(void);
void P101_SkyInit(void);
void P101_TrafficSounds(void);
void P101_WheelsGround(void);
void P101_XformBias2(void);
void P102_BoxAnyCar(void);
void P102_BoxContact(void);
void P102_CarLights(void);
void P102_CarPlanes(void);
void P102_CarTracks(void);
void P102_CarsCollide(void);
void P102_CarsHit(void);
void P102_ClipFar5(void);
void P102_ClipNear7(void);
void P102_ConfigSnap(void);
void P102_CopPathPoint(void);
void P102_CopTalk(void);
void P102_CopsTick(void);
void P102_DirFreeCam(void);
void P102_DirMenuNodes(void);
void P102_GhostTrail(void);
void P102_HudInit(void);
void P102_LampColor(void);
void P102_ObjMark(void);
void P102_PlayerCorners(void);
void P102_RadarClear(void);
void P102_ResetCars(void);
void P102_RoadSide(void);
void P102_ScanCells(void);
void P102_SixInit(void);
void P102_SpawnDust(void);
void P102_TrafficAdd(void);
void P102_TrafficAhead(void);
void P102_TrafficAlign(void);
void P102_TrafficRoom(void);
void P103_BoxContactTime(void);
void P103_CarDamage(void);
void P103_CarsOverlap(void);
void P103_CopMeet(void);
void P103_Dawn(void);
void P103_Dusk(void);
void P103_GhostState(void);
void P103_GroundAt(void);
void P103_Mission4Cars(void);
void P103_MissionModels(void);
void P103_OptionsInit(void);
void P103_PartPath(void);
void P103_ReplayReset(void);
void P103_RoadHeight(void);
void P103_RoadNeighbour(void);
void P103_TrafficCanGo(void);
void P103_TrafficReset(void);
void P103_TrafficSpawn(void);
void P103_TrafficTick(void);
void P104_CarDents(void);
void P104_DebrisTabs(void);
void P104_GfxMenuInit(void);
void P104_MissionInit(void);
void P104_TrafficTurn(void);
void P105_BlitScaled(void);
void P105_ChaseMusic(void);
void P105_EmulSurface(void);
void P105_LfbToMenu(void);
void P105_SpinModel(void);
void P105_StuntHints(void);
void P106_CanDevTex(void);
void P106_CarBrakeLights(void);
void P106_CarHeadSpots(void);
void P106_CarTailLights(void);
void P106_EaxPreset(void);
void P106_EmulUpload16(void);
void P106_EmulUpload8(void);
void P106_LfbText(void);
void P106_PartTick(void);
void P106_SkyModels(void);
void P107_CarInput(void);
void P107_CarLight(void);
void P107_Compass(void);
void P107_CountModel(void);
void P107_Line(void);
void P107_MenuNav(void);
void P107_Rect(void);
void P107_RectGrad(void);
void P107_TexRelease(void);
void P107_TrafficLights(void);
void P107_TrafficRow(void);
void P108_EmulTex16(void);
void P108_EmulTex8(void);
void P108_FillRect(void);
void P108_FillRectB(void);
void P108_FmvStart(void);
void P108_MapTexRect(void);
void P108_RadarArrow(void);
void P108_RadarCar(void);
void P108_RadarShape(void);
void P108_ReplayStep(void);
void P108_SmokeA(void);
void P108_SmokeB(void);
void P108_Sprite(void);
void P109_DropsDraw(void);
void P109_EmulInit(void);
void P109_GradRect(void);
void P109_GradRectS(void);
void P109_IconDraw(void);
void P109_InputTick(void);
void P109_RadarArrows(void);
void P109_RadarTraffic(void);
void P109_ScriptMarkers(void);
void P109_SlotUpload16(void);
void P109_SlotUpload8(void);
void P109_SndPlay(void);
void P109_TileDraw(void);
void P110_Gauge(void);
void P110_GlowA(void);
void P110_GlowB(void);
void P110_GlowC(void);
void P110_IconQuad(void);
void P110_IconRect(void);
void P110_MenuSel(void);
void P110_RadarGrid(void);
void P110_ScriptSprites(void);
void P110_SmokeRing(void);
void P110_ViewSetup(void);
void P111_DebrisIcon(void);
void P111_Flare(void);
void P111_IconsInit(void);
void P111_ScriptTick(void);
void P112_ChaseTick(void);
void P112_DirTimeline(void);
void P112_FaceIcon(void);
void P112_IconBar(void);
void P112_IconScaled(void);
void P112_OpMoveCur(void);
void P112_OpMoveCurve(void);
void P112_OpMoveTo(void);
void P112_ScriptRunId(void);
void P112_ScriptTriggers(void);
void P112_TexDownload(void);
void P113_Heli(void);
void P113_MenuOpts(void);
void P113_PartDraw(void);
void P114_CamFadeFrame(void);
void P114_ColorFlash(void);
void P114_CreditsDraw(void);
void P114_DebrisAll(void);
void P114_DrawSpr(void);
void P114_MenuStep(void);
void P114_PaperMark(void);
void P114_PartModels(void);
void P114_PathDraw(void);
void P114_RadarMarks(void);
void P114_TexDownloadMip(void);
void P114_Timer(void);
void P115_FlatQuadC(void);
void P115_FlatTriC(void);
void P115_GouraudQuadC(void);
void P115_GouraudTriC(void);
void P115_IconAt(void);
void P115_IconDraw(void);
void P115_IconFlip(void);
void P115_IconScaled(void);
void P115_PaperHud(void);
void P115_RoadArrow(void);
void P115_SndUpdate(void);
void P115_TargetTick(void);
void P116_PauseMenu(void);
void P116_RadarIcon(void);
void P116_Reflections(void);
void P116_SkidsA(void);
void P116_SkidsB(void);
void P116_Sliders2(void);
void P116_Sliders5(void);
void P116_SndLevelStart(void);
void P116_Text(void);
void P117_FullMap(void);
void P117_Radar(void);
void P117_SkidRecA(void);
void P117_SkidRecB(void);
void P117_TextList(void);
void P118_CamRoute(void);
void P118_SkidFx(void);
void P118_TrafficBlocked(void);
void P118_TrafficTurn(void);
void P119_CarDust(void);
void P119_CarSelKey(void);
void P119_CarSkids(void);
void P119_Hubcap(void);
void P119_Hud(void);
void P119_MenuFrame(void);
void P119_TrafficParked(void);
void P119_TrafficSpawn(void);
void P119_TrafficSpeed(void);
void P119_TrafficStep(void);
void P120_CarDebris(void);
void P120_CarSmoke(void);
void P120_CarSparks(void);
void P120_ConeRec(void);
void P120_DebugInfo(void);
void P120_HudTimes(void);
void P120_ObjBShade(void);
void P120_ParseCamInt(void);
void P120_ScriptReset(void);
void P121_CamSounds(void);
void P121_ClipQuad(void);
void P121_ClipTexQuad(void);
void P121_ClipTexTri(void);
void P121_CopSync(void);
void P121_DustDraw(void);
void P121_ParseCamLine(void);
void P121_ScriptHud(void);
void P121_SndNextDev(void);
void P121_TexQuadFlat(void);
void P121_TexTriFlat(void);
void P121_WheelDust(void);
void P122_CarGlow(void);
void P122_EventsParse(void);
void P122_FontIcons(void);
void P122_IconCopy(void);
void P122_MapNames(void);
void P122_NameMenu(void);
void P122_ObjATick(void);
void P122_ObjNames(void);
void P122_SetVar(void);
void P122_SpotShadow(void);
void P123_CamAtCar(void);
void P123_CarGlows(void);
void P123_EvLine(void);
void P123_EventsChunk(void);
void P123_ObjAFall(void);
void P123_ObjShadows(void);
void P123_SideDist(void);
void P124_CarSelect(void);
void P124_DebugLog(void);
void P124_HandleDirector(void);
void P124_MotelInit(void);
void P124_MotelKeys(void);
void P124_MotelSample(void);
void P124_ReadBmp(void);
void P124_ReplayMenu(void);
void P124_ShowBmp(void);
void P124_WatchShow(void);
void P125_AddDashMessage(void);
void P125_BlendTable(void);
void P125_ClipNearXY(void);
void P125_CtrlMenuValues(void);
void P125_DebrisBurst(void);
void P125_DropHit(void);
void P125_LevelLoad(void);
void P125_ModelName(void);
void P125_ObjABurst(void);
void P125_PickupTick(void);
void P125_ReplayNodeAction(void);
void P125_SmokePuffs(void);
void P126_DebugKeys(void);
void P126_DropScan(void);
void P126_DropsAt(void);
void P126_KerbDebris(void);
void P126_PlayerStart(void);
void P126_ReadMapPals(void);
void P126_ScreenShot(void);
void P126_ShowBmpFade(void);
void P126_SpawnInit(void);
void P126_WheelSmoke(void);
void P127_AutoCamera(void);
void P127_FarDebris(void);
void P127_LampLights(void);
void P127_MapWindow(void);
void P127_NameEntry(void);
void P127_Pause(void);
void P127_PlayerSkid(void);
void P127_ScriptTick(void);
void P127_SpawnTick(void);
void P127_TrafficLane(void);
void P128_CarDeform(void);
void P128_ClipArea(void);
void P128_CopMapPos(void);
void P128_CopPath(void);
void P128_CopReplan(void);
void P128_CopRoute(void);
void P128_FreeCam(void);
void P128_ModelHit(void);
void P128_TrafficDraw(void);
void P128_TrafficNode(void);
void P129_BoxMerge(void);
void P129_CarObjects(void);
void P129_MapCars(void);
void P129_ObjBoxes(void);
void P129_ObjHit(void);
void P12_Fn00404F70(void);
void P12_Fn00404FAE(void);
void P12_Fn00407563(void);
void P12_Fn0040A45B(void);
void P12_Fn0040A4AD(void);
void P12_Fn0040C813(void);
void P12_Fn0040DA56(void);
void P12_Fn0040F09C(void);
void P12_Fn004120AF(void);
void P12_Fn004124AF(void);
void P12_Fn004129DF(void);
void P12_Fn00412A4B(void);
void P12_Fn00412AB9(void);
void P12_Fn00412B27(void);
void P12_Fn00412B95(void);
void P12_Fn00412C03(void);
void P12_Fn00412C71(void);
void P12_Fn00412CDF(void);
void P12_Fn00412D4D(void);
void P12_Fn00413596(void);
void P12_Fn004136EC(void);
void P12_Fn0041373A(void);
void P12_Fn00413788(void);
void P12_Fn004137D6(void);
void P12_Fn00413973(void);
void P12_Fn00413CBF(void);
void P12_Fn004152A7(void);
void P12_Fn004183F7(void);
void P12_Fn00418433(void);
void P12_Fn0041A8CD(void);
void P12_Fn0041AECF(void);
void P12_Fn0041AF85(void);
void P12_Fn00425EE0(void);
void P12_Fn00426580(void);
void P12_Fn00489ED6(void);
void P12_Fn0048A46B(void);
void P12_Fn0048A627(void);
void P12_Fn0048EBC8(void);
void P12_Fn00491360(void);
void P12_Fn00496505(void);
void P12_Fn004AAE34(void);
void P12_Fn004B9933(void);
void P12_Fn004DC8EA(void);
void P12_Fn004E5982(void);
void P12_Fn004F3E78(void);
void P12_Fn0050229C(void);
void P12_Fn00504699(void);
void P12_Fn0050C010(void);
void P12_Fn0050E963(void);
void P12_Fn00511FB8(void);
void P12_Fn00516E76(void);
void P12_Fn005188EC(void);
void P12_Fn005229F0(void);
void P12_Fn00525CB7(void);
void P12_Fn00526427(void);
void P130_Lightning(void);
void P130_RainSpawn(void);
void P130_RainStep(void);
void P130_SnowSpawn(void);
void P130_SnowStep(void);
void P131_CamShake(void);
void P131_FlybyStart(void);
void P131_GameFrame(void);
void P131_LoadCosDen(void);
void P131_MenuPick(void);
void P131_MissionObj(void);
void P131_RadarArrow(void);
void P131_RainDraw(void);
void P131_ScriptLine(void);
void P131_Splash(void);
void P132_GameDraw(void);
void P132_GameLogic(void);
void P132_Lights(void);
void P132_LoadFlyby(void);
void P132_MenuLoop(void);
void P132_Smoke(void);
void P133_CamUpdate(void);
void P133_EventModels(void);
void P133_LoadConfig(void);
void P133_MirrorDraw(void);
void P133_TrafficTick(void);
void P134_CamChase(void);
void P134_CamCine(void);
void P134_CamCollide(void);
void P134_CamTarget(void);
void P134_TrafficHold(void);
void P135_DebrisTri(void);
void P135_GhostTrail(void);
void P135_RadarLine(void);
void P135_SixBeam(void);
void P135_SmokeObj(void);
void P135_SparkQuad(void);
void P136_CompileEvents(void);
void P136_DrawWheels(void);
void P136_FrontInit(void);
void P136_GameLoop(void);
void P136_OverlayMap(void);
void P137_DrawCar(void);
void P137_LevelEnd(void);
void P137_LoadMcd(void);
void P137_LoadTsd(void);
void P137_MotionInit(void);
void P138_CarShadow(void);
void P138_LoadMission(void);
void P138_LoadPads(void);
void P138_ReplayCfg(void);
void P138_ReplayInit(void);
void P138_ReplayLoad(void);
void P138_TrailEnd(void);
void P139_AddLabel(void);
void P139_CompileScript(void);
void P139_Effects(void);
void P139_KeyMenuA(void);
void P139_KeyMenuB(void);
void P139_LadderLoad(void);
void P139_ReplayEnd(void);
void P139_SaveCfg(void);
void P139_TrailLoad(void);
void P13_Fn004064B4(void);
void P13_Fn00422AC0(void);
void P13_Fn004F8735(void);
void P140_BankLine(void);
void P140_Frontend(void);
void P140_KeysLoad(void);
void P140_LadderRun(void);
void P140_MrkFly(void);
void P140_SaveGame(void);
void P140_SndInit(void);
void P140_SndLoadWav(void);
void P141_HsSetup(void);
void P141_LadderLine(void);
void P142_CarsStep(void);
void P142_CopDrive(void);
void P142_WheelPhys(void);
void P143_LampGlow(void);
void P143_SunFlare(void);
void P144_FlagFx(void);
void P145_LevelLoad(void);
void P146_MsgPos(void);
void P146_ScriptCmd(void);
void P147_ParseCmd(void);
void P147_ScoreRec(void);
void P148_BufFromWav(void);
void P148_DupVoice(void);
void P148_EnumCb(void);
void P148_Fill(void);
void P148_KsProps(void);
void P148_Refill(void);
void P148_SndEnum(void);
void P148_SndOpen(void);
void P149_BuildDevs(void);
void P149_D3DDevCb(void);
void P149_DDEnumAll(void);
void P149_DDEnumCb(void);
void P149_EmulAddSub(void);
void P149_EmulFreeAll(void);
void P149_EmulNew(void);
void P14_Fn0040F0FB(void);
void P14_Fn0048DB65(void);
void P14_Fn004A39F6(void);
void P14_Fn004A3B80(void);
void P14_Fn004A7E6E(void);
void P14_Fn004CAC86(void);
void P14_Fn004CAD47(void);
void P14_Fn004D623B(void);
void P14_Fn00503E83(void);
void P14_Fn00503EF4(void);
void P14_Fn00504439(void);
void P14_Fn0050D97A(void);
void P14_Fn0051BD9C(void);
void P14_Fn0051BED5(void);
void P14_Fn00526A34(void);
void P150_FlushTris(void);
void P150_FmvDDInit(void);
void P150_OpenAudio(void);
void P150_OpenVideo(void);
void P150_PlayFmv(void);
void P151_CheckDev(void);
void P151_InstallD3D(void);
void P151_Reopen(void);
void P151_WinMain(void);
void P151_WinOpen(void);
void P152_FillRows(void);
void P15_BlitRect16(void);
void P15_BlitRect8(void);
void P15_GridCell(void);
void P15_ListClearActiveByTag(void);
void P15_ListClearAllActive(void);
void P15_MenuItem2(void);
void P15_MenuItem3(void);
void P15_MenuItem4(void);
void P15_MenuItem5(void);
void P15_MenuItem6(void);
void P15_MenuItem7(void);
void P15_MenuMiami(void);
void P15_RaiseLimits(void);
void P15_ScaleNormalW(void);
void P15_ScaleVertices(void);
void P15_SetHighlightRange(void);
void P15_SkipInteger(void);
void P16_FillHudRect(void);
void P16_IdleTimer(void);
void P16_StepParticles(void);
void P17_ISqrt(void);
void P17_PushScreenState(void);
void P17_SlotFindIndex(void);
void P17_SlotMapSide(void);
void P18_ClearFlag(void);
void P19_FadeStep(void);
void P19_KeysUnique12(void);
void P19_KeysUnique14(void);
void P19_ScaleX(void);
void P19_ScaleY(void);
void P19_Sel2(void);
void P19_Sel3(void);
void P19_Sel4(void);
void P19_TakeToken(void);
void P20_FindNameNoCase(void);
void P20_FindNameValue(void);
void P21_AddMsf(void);
void P21_CountActiveEntries(void);
void P21_DrawClock(void);
void P21_DrawFps(void);
void P21_FpsToBuf(void);
void P21_FrameTicks(void);
void P21_GetNameByIndex(void);
void P21_GridCellSet(void);
void P21_MatchPrefix(void);
void P21_SetAxisByte(void);
void P22_BeginScene(void);
void P22_EndScene(void);
void P22_SetAlphaFunc(void);
void P22_SetAlphaRef(void);
void P22_SetAlphaTest(void);
void P22_SetCull(void);
void P22_SetTexFilter(void);
void P22_SetTexOp(void);
void P22_SetViewport(void);
void P22_SetZFunc(void);
void P22_SetZWrite(void);
void P23_ClearZ(void);
void P23_ConvVertexA(void);
void P23_ConvVertexB(void);
void P23_DrawLineA(void);
void P23_DrawLineB(void);
void P23_InitRenderStates(void);
void P23_SetBlendMode(void);
void P24_AddViewport(void);
void P24_AttachSurface(void);
void P24_CreateClipper(void);
void P24_CreateDevice(void);
void P24_CreatePrimarySurface(void);
void P24_CreateSurface(void);
void P24_CreateViewport(void);
void P24_FillBackbuffer(void);
void P24_RestoreDisplay(void);
void P24_RestoreSurfaces(void);
void P24_SetClipper(void);
void P24_SetDisplayMode(void);
void P25_CDClose(void);
void P25_CDResume(void);
void P25_CDSetVolume(void);
void P25_CDStop(void);
void P25_GetCDTOC(void);
void P25_InitCDAudio(void);
void P25_PlayCDTrack(void);
void P25_TimerCb(void);
void P25_TimerStart(void);
void P25_TimerStop(void);
void P25_TimersInit(void);
void P25_TimersShutdown(void);
void P26_ErrorInLine(void);
void P26_FindCdDrive(void);
void P26_FindWheelModels(void);
void P26_LogTime(void);
void P26_RandomFx(void);
void P26_WaveSetVolume(void);
void P27_LoadDentTextures(void);
void P27_LoadPalettes(void);
void P27_MemLeakReport(void);
void P27_ReadChunked(void);
void P28_LoadCarModels(void);
void P28_LoadEventModels(void);
void P30_CrashInstall(void);
void P30_CrashRemove(void);
void P30_Exit(void);
void P30_FatalError(void);
void P30_InitWindowGlobals(void);
void P31_InitWindow(void);
void P31_LoadGlide(void);
void P31_ReleaseDirectDraw(void);
void P31_WndProc(void);
void P32_CreateSlotPalette(void);
void P32_CreateZSurface(void);
void P32_SelectSlotPalette(void);
void P32_SetPalette(void);
void P33_FlushBatches(void);
void P33_LoadGlideProcs(void);
void P34_ReAcquire(void);
void P34_ReadKeyboard(void);
void P34_ReleaseInput(void);
void P35_CreateEffectA(void);
void P35_CreateEffectB(void);
void P35_GetDirectDrawInterface(void);
void P35_UpdateForce(void);
void P36_AcquireDevice(void);
void P36_GetPadButtons(void);
void P36_PollInput(void);
void P36_SelectJoystick(void);
void P37_InitInput(void);
void P38_FmvRelease(void);
void P38_FmvStop(void);
void P38_MmsRun(void);
void P38_MmsStop(void);
void P38_SetPrimaryFormat(void);
void P38_SetSpeakerConfig(void);
void P38_UpdateFrame(void);
void P39_CreateFrontBack(void);
void P39_GetSurfaceFormat(void);
void P39_LockSurface(void);
void P39_Present(void);
void P39_QueryD3D(void);
void P39_QueryDD4(void);
void P39_UnlockSurface(void);
void P40_DownloadPalette(void);
void P40_ResetTexMem(void);
void P40_UploadSlot(void);
void P40_UploadSlotPair(void);
void P41_LoadTexPages(void);
void P42_ActionBound(void);
void P42_CellIndex(void);
void P42_FindCommand(void);
void P42_FindCommandById(void);
void P42_FindVar(void);
void P42_FreeGlide(void);
void P42_GetDeviceName(void);
void P42_GetHighScore(void);
void P42_SetViewAngles(void);
void P42_VersionString(void);
void P43_AnimNext(void);
void P43_CdFadeInit(void);
void P43_ClipT(void);
void P43_Cross(void);
void P43_EulerMatrix(void);
void P43_FreeSlot(void);
void P43_Len3(void);
void P43_Len4(void);
void P43_MatToQuat(void);
void P43_Normalize(void);
void P43_NormalizeCopy(void);
void P43_NormalizeToOut(void);
void P43_Orthonormalize(void);
void P43_PointInPoly(void);
void P43_ProjectGrid(void);
void P43_QuatToMat(void);
void P44_Atan2(void);
void P44_AxisAngleMat(void);
void P44_Copy4(void);
void P44_EulerMatXYZ(void);
void P44_EulerMatYXZ(void);
void P44_EulerToQuat(void);
void P44_LookAt(void);
void P44_PointInQuad(void);
void P44_QuatMul(void);
void P44_QuatNormalize(void);
void P44_ResetState(void);
void P44_RotX(void);
void P44_RotY(void);
void P44_RotZ(void);
void P44_Transpose(void);
void P44_Xform(void);
void P44_XformBias(void);
void P44_XformT(void);
void P45_ModeA(void);
void P45_ModeB(void);
void P45_PickColor(void);
void P45_Wait(void);
void P46_FindTexNode(void);
void P46_LoadMapA(void);
void P46_LoadMapB(void);
void P46_SetBounds(void);
void P46_TexCall(void);
void P46_TexCall2(void);
void P46_UpdateObjects(void);
void P47_Call51B111(void);
void P47_CameraModeText(void);
void P47_DirText(void);
void P47_GlideSwap(void);
void P47_GlideWinOpen(void);
void P47_LoadFlyby(void);
void P47_NoFlags(void);
void P47_PrepareTemp(void);
void P47_ReadLine(void);
void P47_ResetPick(void);
void P47_TexTable(void);
void P47_TitleDispatch(void);
void P48_AnyKey(void);
void P48_FadeEnd(void);
void P48_FreeSample(void);
void P48_FreeVoice(void);
void P48_GetVoiceVolume(void);
void P48_GlideCheck(void);
void P48_OpFlags(void);
void P48_OpRampDown(void);
void P48_OpRampUp(void);
void P48_OpRepeat(void);
void P48_OpSet3(void);
void P48_OpSet4(void);
void P48_OpTurn(void);
void P48_PosToInts(void);
void P48_ResetAll(void);
void P48_SetMasterVolume(void);
void P48_SetVoiceVolume(void);
void P48_ShutdownSystems(void);
void P48_SndPause(void);
void P48_SndShutdown(void);
void P48_StartupSystems(void);
void P48_StopAll(void);
void P49_Commit(void);
void P49_GetStatus(void);
void P49_ListenerOrient(void);
void P49_ListenerPos(void);
void P49_ListenerVel(void);
void P49_Play(void);
void P49_ReleaseProp2C(void);
void P49_ReleaseProps(void);
void P49_SetFreq(void);
void P49_SetMode3D(void);
void P49_SetPos3D(void);
void P49_SetVel3D(void);
void P49_SetVolume(void);
void P50_CreateDummyBuf(void);
void P50_CreateKsProps(void);
void P50_EaxEnable(void);
void P50_EaxSetDefault(void);
void P50_FmvReleaseAll(void);
void P50_FmvReleaseObjs(void);
void P50_FmvStopRelease(void);
void P50_Nop(void);
void P50_ReleaseBuf(void);
void P50_ReleaseVoice(void);
void P50_ResetBuf(void);
void P50_SoundShutdown(void);
void P51_DirFromHeading(void);
void P51_FileSize(void);
void P51_InitCarSlot(void);
void P51_NodeKind(void);
void P51_PitchJitterSfx(void);
void P51_PrefixMatch(void);
void P51_ScalePair(void);
void P51_SkipNumber(void);
void P51_SkipToLine(void);
void P51_SteerHeading(void);
void P51_TrafficConflict(void);
void P52_DrawLabel(void);
void P52_FmvStart(void);
void P52_GlideFogMode(void);
void P52_GlideFogSetup(void);
void P52_HudDispatch(void);
void P52_MenuReload(void);
void P52_MenuStepToggle(void);
void P52_ResetSlots(void);
void P52_TexDownloadMipMap(void);
void P53_CallWithState(void);
void P53_MenuA(void);
void P53_MenuB(void);
void P53_MenuC(void);
void P53_NameEntry(void);
void P53_ReadWholeFile(void);
void P53_SetTexSource(void);
void P53_StepBounds(void);
void P53_TexLookup(void);
void P54_AllocMapBufs(void);
void P54_AllocRoadbits(void);
void P54_ClearBuffers(void);
void P54_ClearSwap(void);
void P54_DefaultKeys(void);
void P54_FreeRoadbits(void);
void P54_FreeTab4(void);
void P54_GetTexture2(void);
void P54_InitInputMode(void);
void P54_MenuTexSel(void);
void P54_ObjInit(void);
void P54_ObjTick(void);
void P54_ReadMapA(void);
void P54_ReadMapB(void);
void P54_ReadNames(void);
void P54_TexSource(void);
void P55_FillDevInfo(void);
void P55_GlideDevInfo(void);
void P55_GlideInit(void);
void P55_LoadFile(void);
void P55_LoadFileSize(void);
void P55_LoadFrustum(void);
void P55_LoadPaper(void);
void P55_MenuLangCall(void);
void P55_NamesA(void);
void P55_NamesB(void);
void P55_NamesC(void);
void P55_NamesD(void);
void P55_NextPad(void);
void P55_PopDeferred(void);
void P55_ResetSel(void);
void P55_RunTableA(void);
void P55_RunTableB(void);
void P55_SaveRec(void);
void P55_SetScreen(void);
void P55_StopAudio(void);
void P56_AllocEulerTab(void);
void P56_BmpPage(void);
void P56_CarPosCheck(void);
void P56_ChaseTick(void);
void P56_CopsDebug(void);
void P56_CopyBlock16(void);
void P56_DrawRowRects(void);
void P56_DrawSprite(void);
void P56_GhostInit(void);
void P56_HudTick(void);
void P56_LoopStart(void);
void P56_LoopUpdate(void);
void P56_ObjInit(void);
void P56_ObjSync(void);
void P56_QuatRot(void);
void P56_ReplayPaths(void);
void P56_ReplayRead(void);
void P56_ReplaySetup(void);
void P56_ResetFrontend(void);
void P56_SaveCheck(void);
void P56_SetVoicePos(void);
void P56_Spline(void);
void P57_FileExists(void);
void P57_LoadScores(void);
void P57_Menu4045E0(void);
void P57_Menu404850(void);
void P57_Menu4082A0(void);
void P57_Menu40A3A0(void);
void P57_Menu40A540(void);
void P57_Menu40E870(void);
void P57_Menu40F2D0(void);
void P57_Menu411FD0(void);
void P57_Menu4123D0(void);
void P57_Menu4134A0(void);
void P57_Menu413610(void);
void P57_Menu413890(void);
void P57_Menu413B00(void);
void P57_Menu416390(void);
void P57_MenuDone(void);
void P57_ResetTexNodes(void);
void P57_SaveDirectorIfAny(void);
void P57_SaveScores(void);
void P57_ScreenToView(void);
void P57_SkipBlock(void);
void P57_WriteFile(void);
void P58_Backgrounds(void);
void P58_BuildBlockIndex(void);
void P58_CheatByName(void);
void P58_CheatsAll(void);
void P58_DrawLogo(void);
void P58_DrawObjs(void);
void P58_FindChunk(void);
void P58_FreeGrid(void);
void P58_FreeList(void);
void P58_FreeLists(void);
void P58_FreeNames(void);
void P58_FreeRecs(void);
void P58_ItemsDraw(void);
void P58_LangStrings(void);
void P58_Menu413D70(void);
void P58_Menu416540(void);
void P58_Menu419AB0(void);
void P58_Menu419F00(void);
void P58_MenuSwitch(void);
void P58_ParseInt(void);
void P58_PlayDemo(void);
void P58_PrepPage(void);
void P58_SaveConfig(void);
void P58_SaveSlot(void);
void P58_TextWidth(void);
void P59_CellLeft(void);
void P59_MenuKeys(void);
void P59_ModelNames(void);
void P59_NearCars(void);
void P59_ObjDir(void);
void P59_PickUp(void);
void P59_ReadBlock(void);
void P59_ReplayCheck(void);
void P59_SetupCamera(void);
void P59_TrafficCheck(void);
void P59_TrafficFind(void);
void P59_VarSetString(void);
void P59_VarsInit(void);
void P60_NextTrafficCar(void);
void P60_ObjUpdate(void);
void P60_SpawnParticle(void);
void P61_CamPrepare(void);
void P61_RestoreCamState(void);
void P61_SetupCamN(void);
void P61_SpawnPart(void);
void P61_StoreCamState(void);
void P62_DownloadPage(void);
void P62_FarFromPlayer(void);
void P62_FindFreeTrafficSlot(void);
void P62_HeadingDelta(void);
void P62_InitCamDefaults(void);
void P62_InitRenderConsts(void);
void P62_LoadMapHeader(void);
void P62_MapRow(void);
void P62_MenuBusy(void);
void P62_ModelLookup(void);
void P62_ParticleInit(void);
void P62_ParticleSet(void);
void P62_QueueTri(void);
void P62_SaveScores(void);
void P62_ScoreTable(void);
void P62_SpawnTrafficCar(void);
void P62_SpeedText(void);
void P63_CanEnter(void);
void P63_CarSpeed(void);
void P63_CatmullRom(void);
void P63_CountByNode(void);
void P63_Hermite(void);
void P63_InPlanes(void);
void P63_NearOnNode(void);
void P63_NearestAdd(void);
void P63_NearestRec(void);
void P63_SphereHits(void);
void P64_RankBestFirst(void);
void P64_RankPlace(void);
void P64_RankScoreB(void);
void P64_RankTimeB(void);
void P64_RankTimeLess(void);
void P64_RankTimeMore(void);
void P64_RankTop(void);
void P64_ReplayStart(void);
void P64_SaveChunk(void);
void P64_SaveReplay(void);
void P65_BlitBlend(void);
void P65_BlitKeyed(void);
void P65_FindByName(void);
void P65_NextToken(void);
void P65_ReadInts(void);
void P65_ScriptCall(void);
void P65_SetNameFields(void);
void P65_SpriteBlend(void);
void P65_SpriteKeyed(void);
void P66_DirSwitch(void);
void P66_DrawTable(void);
void P66_FrameBegin(void);
void P66_ScreenFrame(void);
void P67_CenterDraw(void);
void P67_CompactPool(void);
void P67_DrawIcon(void);
void P67_Logo(void);
void P67_Menu415188(void);
void P67_Menu415EC0(void);
void P67_Menu417970(void);
void P67_ObjStep(void);
void P68_AimSetup(void);
void P68_ChangeSample(void);
void P68_LfbLock(void);
void P68_ObjStepB(void);
void P68_ReadCamArgs(void);
void P68_ReadWords(void);
void P68_RepeatCheck(void);
void P68_ScreenReset(void);
void P68_SpawnCar(void);
void P69_AddScore(void);
void P69_Bracket(void);
void P69_FreeDevices(void);
void P69_ReleaseOverlays(void);
void P69_SceneFrame(void);
void P69_SetupMsgs(void);
void P70_FadeColor(void);
void P70_FindParticle(void);
void P70_LoadReplay(void);
void P70_RadarNearest(void);
void P70_RadarNearestB(void);
void P70_ReadChunk(void);
void P70_RowDecode(void);
void P70_ShadowText(void);
void P70_SpawnPart2(void);
void P70_SpawnPart4(void);
void P71_CountNear(void);
void P71_Course(void);
void P71_EdgeA(void);
void P71_EdgeB(void);
void P71_FaceCar(void);
void P71_InPlanes(void);
void P71_InitNear(void);
void P71_ScoreSetup(void);
void P72_RoadDword(void);
void P72_RoadLookup(void);
void P72_RoadWord(void);
void P73_CatmullRom(void);
void P73_ParticlesReset(void);
void P73_RoadSides(void);
void P73_Text(void);
void P74_Conv8to16(void);
void P74_DevSelect(void);
void P74_Dist(void);
void P74_FreeTraffic(void);
void P74_KeyScan(void);
void P74_ParseFloat(void);
void P74_ParseShorts(void);
void P74_ResetHud(void);
void P74_ShiftRows(void);
void P74_SkidInit(void);
void P75_BgSound(void);
void P75_BmpToPage(void);
void P75_CarSound(void);
void P75_CarVoice(void);
void P75_ResetObjs(void);
void P75_TrafficFill(void);
void P75_TrafficPos(void);
void P75_TrafficSpawn(void);
void P76_AngleColor(void);
void P76_CellFromPos(void);
void P76_FlashStep(void);
void P76_GlideRegister(void);
void P76_InBox(void);
void P76_LoadHsTables(void);
void P76_MarkSlots(void);
void P76_TileFill(void);
void P76_TriA1(void);
void P76_TriA2(void);
void P76_TriB1(void);
void P76_TriB2(void);
void P77_CameraPlane(void);
void P77_ListAdd(void);
void P77_LoadBank(void);
void P77_LoadLevel(void);
void P77_Menu407160(void);
void P77_Menu408770(void);
void P77_Menu414C30(void);
void P77_OpenLevel(void);
void P77_ResetTables(void);
void P78_ChairAdd(void);
void P78_LoadChairs(void);
void P78_LoadLamps(void);
void P78_LoadLampsBlock(void);
void P78_LoadVerts(void);
void P79_Convert(void);
void P79_FindSameVerts(void);
void P79_MarkRecords(void);
void P79_ModelList(void);
void P79_Radius(void);
void P79_Relocate(void);
void P79_Unrelocate(void);
void P79_VertClass(void);
void P80_Bounds(void);
void P80_LoadHeader(void);
void P80_LoadModels(void);
void P81_Light(void);
void P81_Limit(void);
void P82_AddLight(void);
void P82_FrustumSetup2D(void);
void P82_FrustumSetup3D(void);
void P82_SphereVis2D(void);
void P82_SphereVis3D(void);
void P83_BoxVis(void);
void P83_LightMatrices(void);
void P84_DrawCar(void);
void P84_DrawModel(void);
void P84_DrawModelC(void);
void P84_DrawModelIdx(void);
void P85_FlatQuad(void);
void P85_FlatTri(void);
void P85_LitQuad(void);
void P85_LitTri(void);
void P85_Project(void);
void P86_GouraudQuad(void);
void P86_GouraudTri(void);
void P86_TexQuad(void);
void P86_TexQuadD(void);
void P86_TexTri(void);
void P86_TexTriD(void);
void P87_DrawObjA(void);
void P87_DrawObjB(void);
void P87_LoadTile(void);
void P88_CellUpdate(void);
void P88_StreamTiles(void);
void P89_DrawMap(void);
void P89_Fill1(void);
void P89_VisMask(void);
void P90_DrawSingle(void);
void P91_ReleaseTraffic(void);
void P92_DrawAxis(void);
void P92_DrawSpin(void);
void P93_FindIcon(void);
void P94_BuildDirTab(void);
void P94_ClampView(void);
void P94_FadeStep(void);
void P94_IconQuad(void);
void P94_InViewCone(void);
void P94_InitCurves(void);
void P94_MapToScreen(void);
void P94_NearestObjDist(void);
void P94_PackState(void);
void P94_QuatToMat(void);
void P94_RadarXY(void);
void P94_ReadIdent(void);
void P94_RowSpans(void);
void P94_SpringStep(void);
void P94_Wobble(void);
void P95_AmbientTick(void);
void P95_CamFromQuat(void);
void P95_CountNear(void);
void P95_DefaultOptions(void);
void P95_DrawCross(void);
void P95_DrawLineRGB(void);
void P95_InitDebris(void);
void P95_MapRotate(void);
void P95_NearestTwo(void);
void P95_PoolIconInit(void);
void P95_ResetRace(void);
void P95_ScriptTurn(void);
void P95_SeqMatch(void);
void P95_SlotAt(void);
void P95_SndInit(void);
void P95_SndTrigger(void);
void P95_SortObjA(void);
void P95_SortObjB(void);
void P95_SortObjC(void);
void P95_TextWidthCur(void);
void P96_AddObjB(void);
void P96_ClampOptions(void);
void P96_ClockText(void);
void P96_DropFarChairs(void);
void P96_FpsText(void);
void P96_IconAt(void);
void P96_IconRect(void);
void P96_InitRotTab(void);
void P96_InitSphere(void);
void P96_LoadBar(void);
void P96_LogLine(void);
void P96_ParseQuoted(void);
void P96_ParseWord(void);
void P96_PartRunA(void);
void P96_PartRunB(void);
void P96_PickChair(void);
void P96_ReplayScript(void);
void P96_ReplayTag(void);
void P96_ResetDirector(void);
void P96_ShadowInit(void);
void P96_SpawnDust(void);
void P96_SpawnSpark(void);
void P96_TextAt(void);
void P96_TextCenter(void);
void P96_TextMid(void);
void P97_AddTime(void);
void P97_BlinkAStep(void);
void P97_BlinkBStep(void);
void P97_CopsSee(void);
void P97_DirKeys(void);
void P97_FadeIconDraw(void);
void P97_GoalCops(void);
void P97_GoalReached(void);
void P97_HsInit(void);
void P97_KeyMenuAInit(void);
void P97_KeyMenuBInit(void);
void P97_KickDebris(void);
void P97_LfbSnap(void);
void P97_MapIcon(void);
void P97_MarkCells(void);
void P97_MenuCall0(void);
void P97_MenuCall2(void);
void P97_ObjsFromScript(void);
void P97_OptMenuAInit(void);
void P97_OptMenuBInit(void);
void P97_ResetCars(void);
void P97_ScriptEach(void);
void P97_ScriptLoad(void);
void P97_ScriptOpNext(void);
void P97_ScriptResetCur(void);
void P97_ScriptSave(void);
void P97_SndDrvInit(void);
void P97_SndMenuInit(void);
void P97_SndStart(void);
void P97_SpawnSmoke(void);
void P98_CamClamp(void);
void P98_CamRecAdd(void);
void P98_CamSpline(void);
void P98_ClearCarData(void);
void P98_CreditsFace(void);
void P98_CreditsInit(void);
void P98_DebugFree(void);
void P98_DebugMalloc(void);
void P98_DirCamKeys(void);
void P98_DirCamNext(void);
void P98_DrawMarker(void);
void P98_DrawScriptModels(void);
void P98_DrawSix(void);
void P98_FreeCamKeys(void);
void P98_IconFlush(void);
void P98_InitSplash(void);
void P98_ItemsDraw(void);
void P98_LampColor(void);
void P98_LoadLang(void);
void P98_PartAim(void);
void P98_PartCheck(void);
void P98_PixTabInit(void);
void P98_QuadA(void);
void P98_QuadB(void);
void P98_ResetMission(void);
void P98_RiffFind(void);
void P98_ScriptFreeAll(void);
void P98_ScriptRange(void);
void P98_TrafficSpin(void);
void P98_VoicePos(void);
void P99_CamBehind(void);
void P99_CamCheckDist(void);
void P99_CamCheckPlayer(void);
void P99_CamScriptStep(void);
void P99_CarModelClean(void);
void P99_CarOpsReset(void);
void P99_ChairHit(void);
void P99_CmdAppend(void);
void P99_CopTarget(void);
void P99_CopsNear(void);
void P99_DDEnumFmt(void);
void P99_EventAdd(void);
void P99_FreeCamMove(void);
void P99_GearBox(void);
void P99_GoalCheck(void);
void P99_JunctionBlock(void);
void P99_MapFree(void);
void P99_MarkerReset(void);
void P99_MenuDim(void);
void P99_MenuItems(void);
void P99_PartAhead(void);
void P99_PartOnChair(void);
void P99_PathAhead(void);
void P99_RadarXform(void);
void P99_RoadAtCar(void);
void P99_ScriptFree(void);
void P99_ScriptMsgs(void);
void P99_SegClip(void);
void P99_SegCross(void);
void P99_TrafficAhead(void);
void P99_VarSetStr(void);
void Pack565Bytes004BF452(void);
void Pack565_004D950F(void);
void PackRGB00503ECC(void);
void PlayTrack004D7B60(void);
void PoolAlloc004A2C12(void);
void PoolAlloc0051210C(void);
void PoolNext004AC671(void);
void PoolPop004AC6D0(void);
void PoolPop004AC726(void);
void PoolPush004AC6AC(void);
void PoolPush004AC702(void);
void PoolPush004AC755(void);
void PopIndex00493E9B(void);
void PrevPcar00404721(void);
void PushEntry_004CC784(void);
void PushHistory_004E5938(void);
void PushVec3_00523C99(void);
void Rand_004D9078(void);
void RangeCheck00514E6A(void);
void ReadBlocks_004EB7CF(void);
void ReadCameraChunkV1(void);
void ReadCameraChunkV2(void);
void ReadDirectorData(void);
void ReadDirectorKeys(void);
void ReadTable_004EC466(void);
void ReadTable_004EC49A(void);
void ReadTable_004EC522(void);
void ReadTable_004EC556(void);
void RedMarkers_0041ADA1(void);
void ReleaseSlot4A2C5B(void);
void RenumberCameras(void);
void Reset0042D2B0(void);
void Reset004D600B(void);
void ResetDirectorState(void);
void ResetDirector_00522306(void);
void ResetEffectsState(void);
void ResetObjState_00514E99(void);
void ResetPalette00519DF3(void);
void ResetSlots_004A2B70(void);
void ResetSlots_004AB712(void);
void ResetVec_005272C6(void);
void ResolveTable_004FE830(void);
void RestoreCameraBackup(void);
void Ret1(void);
void Ret1FFFF8IfZero(void);
void RetZero0041FA36(void);
void ReturnOne00519D22(void);
void ReturnZero004D03FD(void);
void ReturnZero004E3B19(void);
void RingAdvance004D7B36(void);
void RotVec_005279CB(void);
void Round1024(void);
void RoundSet_004BF400(void);
void SaveDirector(void);
void ScanSlot_0040AAE2(void);
void ScriptLoopStep_004D133C(void);
void ScriptOpClearBit2_004D1402(void);
void ScriptOpSetBit200_004D03D0(void);
void ScriptOpSetBit2_004D0404(void);
void ScriptOpSetBit4_004D13D8(void);
void ScriptOpSkip4_004D1601(void);
void ScriptOpSkipClear004D1111(void);
void ScriptOpToggle10_004D1737(void);
void ScriptReadPair_004D12CA(void);
void ScriptReadShort3_004D02C6(void);
void ScriptReadU32_004D1135(void);
void ScriptReadVec3_004D033F(void);
void ScriptSetWait004F5C72(void);
void ScriptSetWaitX50_004F5C58(void);
void ScriptSkip16_004D14D8(void);
void ScriptSkipBack_004D1635(void);
void ScriptStackPop004CB982(void);
void ScriptStackPop004CB9BA(void);
void ScriptStackPush004CB9F2(void);
void SelectByDifficulty_00416D17(void);
void SelectNewCamera(void);
void SelectRow004110C2(void);
void SelectRow00411177(void);
void SelectRow0041122C(void);
void SelectRow004112E1(void);
void SelectRow00411396(void);
void SelectRow0041144B(void);
void SelectRow00411500(void);
void SelectRow004115B5(void);
void SelectRow0041166A(void);
void SelectRow0041171F(void);
void SelectRow004117D4(void);
void SelectRow00411889(void);
void SelectRow0041193E(void);
void SelectRow004119F3(void);
void Set0D044C8(void);
void Set551134(void);
void Set560388(void);
void SetB31E00(void);
void SetCamera(void);
void SetColorRed00417A55(void);
void SetColorRed0041A051(void);
void SetColorWhite00417AA2(void);
void SetColorWhite0041A085(void);
void SetD11804(void);
void SetDirectorMode(void);
void SetDrawParams_004D9539(void);
void SetFade0051707A(void);
void SetField24_00502779(void);
void SetFirstFree_004D6190(void);
void SetFlagFromArg0041E1E4(void);
void SetHiliteBits_0041621C(void);
void SetIconIdx00412A0D(void);
void SetIconIdx00412A7B(void);
void SetIconIdx00412AE9(void);
void SetIconIdx00412B57(void);
void SetIconIdx00412BC5(void);
void SetIconIdx00412C33(void);
void SetIconIdx00412CA1(void);
void SetIconIdx00412D0F(void);
void SetIconName00412A36(void);
void SetIconName00412AA4(void);
void SetIconName00412B12(void);
void SetIconName00412B80(void);
void SetIconName00412BEE(void);
void SetIconName00412C5C(void);
void SetIconName00412CCA(void);
void SetIconName00412D38(void);
void SetLatchValue0050E940(void);
void SetMode1_00510448(void);
void SetMode1b_005106D2(void);
void SetMode2_004E612A(void);
void SetMode4_00510382(void);
void SetNodeEnabled(void);
void SetPcarName0040479B(void);
void SetRGB00516EB4(void);
void SetScale54EF38(void);
void SetScaled_004CB097(void);
void SetTableValue_004F89B7(void);
void SetVarD1193C(void);
void SetZoom_00421CAB(void);
void SetupMenuTable00412087(void);
void SetupMenuTable00412487(void);
void SetupMiami00416040(void);
void ShutdownAudio004183A3(void);
void SkipLine004A59C6(void);
void SkipToIdentStart_004A596B(void);
void SlotSetOff0052434A(void);
void SlotSetOn0052432A(void);
void SndHelper_00407D56(void);
void SndHelper_00407D97(void);
void SoundGetPos005242A7(void);
void SoundLoop_0052422D(void);
void SoundMenuIn00419814(void);
void SoundMenuOut0051082A(void);
void SoundMenuSave0051080E(void);
void SoundPlay00523E50(void);
void SoundSetFormat005235D3(void);
void SoundSetPos00523F8A(void);
void SoundSetVolA005235F2(void);
void SoundSetVolB0052360D(void);
void StartAudio005233A0(void);
void StartFlyby004A05C0(void);
void StartTimer004086B4(void);
void StepDown00415877(void);
void StepDown004158D5(void);
void StepDown0050F9E3(void);
void StepDown0050FA41(void);
void StepDown_00510145(void);
void StepDown_005101B7(void);
void StepIfActive0041A8AB(void);
void StepSpeedA_004B9E2B(void);
void StepSpeedB_004B9E54(void);
void StepToward004E60C1(void);
void StepUp00415848(void);
void StepUp004158A6(void);
void StepUp0050F9B4(void);
void StepUp0050FA12(void);
void StepUp_0051010C(void);
void StepUp_0051017E(void);
void StopTimer4086EA(void);
void SumBytes(void);
void SwitchPanel_005104B9(void);
void SwitchPanel_0051066A(void);
void SwitchPanel_0051069E(void);
void SyncCameraFromList(void);
void TestBit0041B7AD(void);
void TickTimer4F5D67(void);
void Toggle0050FE82(void);
void Toggle0050FEA3(void);
void Toggle0050FEC4(void);
void Toggle0050FF41(void);
void Toggle0050FF62(void);
void Toggle0050FF83(void);
void Toggle0050FFA4(void);
void Toggle0050FFC5(void);
void Toggle0050FFE6(void);
void Toggle00510007(void);
void ToggleBit0051049E(void);
void ToggleOpt0041542A(void);
void ToggleOpt004154CD(void);
void ToggleVar00407636(void);
void TryStartTrack_004D611B(void);
void TypeIsKnown00514F0A(void);
void Ui00408699(void);
void Ui0040C867(void);
void Ui0040C87A(void);
void Ui0040C88D(void);
void Ui004120EE(void);
void Ui004120FE(void);
void Ui00412112(void);
void Ui00412126(void);
void Ui0041213A(void);
void Ui0041214E(void);
void Ui00412162(void);
void Ui00412176(void);
void Ui0041218A(void);
void Ui004122E7(void);
void Ui00412509(void);
void Ui00412519(void);
void Ui0041252D(void);
void Ui00412541(void);
void Ui00412555(void);
void Ui00412569(void);
void Ui0041257D(void);
void Ui00412591(void);
void Ui004125A5(void);
void Ui00412702(void);
void Ui00412F3A(void);
void Ui00412F56(void);
void Ui00412F62(void);
void Ui00412F74(void);
void Ui00412F90(void);
void Ui00412F9C(void);
void Ui00413543(void);
void Ui0041354F(void);
void Ui0041355B(void);
void Ui0041357E(void);
void Ui0041358A(void);
void Ui004136CE(void);
void Ui0041371C(void);
void Ui0041376A(void);
void Ui004137B8(void);
void Ui00413955(void);
void Ui004139A3(void);
void Ui004139C1(void);
void Ui004139DA(void);
void Ui004139F8(void);
void Ui00413A11(void);
void Ui00413A2F(void);
void Ui00413A48(void);
void Ui00413A66(void);
void Ui00413BC5(void);
void Ui00413BF7(void);
void Ui00413C29(void);
void Ui00413C5B(void);
void Ui00413C8D(void);
void Ui004157A9(void);
void Ui00415841(void);
void Ui00417A89(void);
void Ui00417A98(void);
void Ui00417AD6(void);
void Ui00417AEA(void);
void Ui00417AF9(void);
void Ui00417B03(void);
void Ui00418119(void);
void Ui004183E8(void);
void Ui004184DE(void);
void Ui00418886(void);
void Ui0041889C(void);
void Ui004197F8(void);
void Ui00419C2D(void);
void Ui00419C46(void);
void Ui00419C69(void);
void Ui00419C82(void);
void Ui00419D02(void);
void Ui00419D1B(void);
void Ui00419FBD(void);
void Ui00419FCC(void);
void Ui00419FD6(void);
void Ui00419FE2(void);
void Ui00419FF1(void);
void Ui00419FFB(void);
void Ui0041A007(void);
void Ui0041A016(void);
void Ui0041A020(void);
void Ui0041A02C(void);
void Ui0041A03B(void);
void Ui0041A045(void);
void Ui0041A192(void);
void Ui0041A1EC(void);
void Ui0041AE25(void);
void Ui0041B059(void);
void Ui0041D94A(void);
void Ui0041DEC1(void);
void Ui0041EC79(void);
void Ui0041ED0E(void);
void Ui0041ED2D(void);
void Ui0041ED3E(void);
void Ui0041ED53(void);
void Ui0041ED83(void);
void Ui0041ED8A(void);
void Ui0041ED91(void);
void Ui0041F47C(void);
void Ui0041F74A(void);
void Ui0041F7E7(void);
void Ui0041F7F7(void);
void Ui0041F800(void);
void Ui0041FA2D(void);
void Ui0041FA40(void);
void Ui0041FA6B(void);
void Ui0041FA74(void);
void Ui0041FA84(void);
void Ui0041FA99(void);
void Ui0041FAA2(void);
void Ui0041FAAB(void);
void Ui004264A7(void);
void Ui004268E0(void);
void Ui00426CAF(void);
void Ui00426CC6(void);
void UiSetMode005FEEEC_0(void);
void UiSetMode005FEEEC_1(void);
void UiSetMode005FEEEC_2(void);
void UiSetMode005FEEEC_3(void);
void UiSetMode005FEEEC_4(void);
void UiSetMode005FEEEC_5(void);
void UiSetMode005FEEEC_6(void);
void UiSetMode005FEEEC_7(void);
void UiSetSlot004142E8(void);
void UiSetSlot004143FA(void);
void UiSetSlot0041450C(void);
void UiSetSlot00414621(void);
void Update005012A3(void);
void VecAdd3_00526F7E(void);
void VecAdd4_0052715E(void);
void VecNeg4_00527123(void);
void VecSub4_005271A8(void);
void VolumeDown00409BFD(void);
void VolumeUp00409BC9(void);
void WrapCounter004A3A80(void);
void WriteCameraChunk(void);
void WriteDirectorData(void);
void WriteReplayHeaderChunk(void);
void WriteWaypointChunk(void);
void Zoom_00425E9E(void);
const re_fnent_t re_fn_table[] = {
  { 0x004045e0u, (re_fn_t)P57_Menu4045E0 },
  { 0x00404687u, (re_fn_t)MenuFlagSet },
  { 0x00404696u, (re_fn_t)MenuFlagUpdate },
  { 0x004046c8u, (re_fn_t)P53_MenuB },
  { 0x00404721u, (re_fn_t)PrevPcar00404721 },
  { 0x0040475eu, (re_fn_t)NextPcar0040475E },
  { 0x0040479bu, (re_fn_t)SetPcarName0040479B },
  { 0x00404850u, (re_fn_t)P57_Menu404850 },
  { 0x004048ddu, (re_fn_t)P113_MenuOpts },
  { 0x00404e52u, (re_fn_t)MenuRowsTo3_00404E52 },
  { 0x00404e7eu, (re_fn_t)MenuRowsIf0To2_00404E7E },
  { 0x00404eb0u, (re_fn_t)MenuToggleOptBDFA44 },
  { 0x00404ec9u, (re_fn_t)MenuToggleOptBDFA48 },
  { 0x00404ee2u, (re_fn_t)MenuToggleOptBDFA4C },
  { 0x00404efbu, (re_fn_t)MenuToggleOptBDFA50 },
  { 0x00404f14u, (re_fn_t)MenuToggleOptBDFA54 },
  { 0x00404f2du, (re_fn_t)MenuToggleOptB87E9C },
  { 0x00404f46u, (re_fn_t)MenuToggleOptBDFA58 },
  { 0x00404f5fu, (re_fn_t)MenuStateSetFour },
  { 0x00404f70u, (re_fn_t)P12_Fn00404F70 },
  { 0x00404faeu, (re_fn_t)P12_Fn00404FAE },
  { 0x00404ffeu, (re_fn_t)MenuCallAction40CD17 },
  { 0x0040500du, (re_fn_t)P54_MenuTexSel },
  { 0x00405450u, (re_fn_t)P95_ResetRace },
  { 0x004055e8u, (re_fn_t)P133_LoadConfig },
  { 0x00405abeu, (re_fn_t)P95_DefaultOptions },
  { 0x00405bfau, (re_fn_t)P58_SaveConfig },
  { 0x00405cb4u, (re_fn_t)P56_SaveCheck },
  { 0x00405d60u, (re_fn_t)P140_SaveGame },
  { 0x00405e79u, (re_fn_t)P58_SaveSlot },
  { 0x00405f2eu, (re_fn_t)P47_PrepareTemp },
  { 0x00405f6fu, (re_fn_t)P64_ReplayStart },
  { 0x00405fdbu, (re_fn_t)P59_ReplayCheck },
  { 0x00406096u, (re_fn_t)P64_SaveReplay },
  { 0x00406199u, (re_fn_t)P70_LoadReplay },
  { 0x00406272u, (re_fn_t)P64_SaveChunk },
  { 0x00406369u, (re_fn_t)P70_ReadChunk },
  { 0x00406439u, (re_fn_t)P57_LoadScores },
  { 0x00406479u, (re_fn_t)P57_SaveScores },
  { 0x004064b4u, (re_fn_t)P13_Fn004064B4 },
  { 0x0040682du, (re_fn_t)SumBytes },
  { 0x00406875u, (re_fn_t)P102_ConfigSnap },
  { 0x00406b51u, (re_fn_t)P57_FileExists },
  { 0x00407160u, (re_fn_t)P77_Menu407160 },
  { 0x0040724cu, (re_fn_t)P54_InitInputMode },
  { 0x004072beu, (re_fn_t)P65_SetNameFields },
  { 0x00407334u, (re_fn_t)MenuSelect00407334 },
  { 0x0040737au, (re_fn_t)MenuSlotHandler0040737A },
  { 0x004073abu, (re_fn_t)P55_NextPad },
  { 0x00407421u, (re_fn_t)MenuSelect00407421 },
  { 0x00407460u, (re_fn_t)Menu549FBC },
  { 0x0040748au, (re_fn_t)P54_DefaultKeys },
  { 0x004074fau, (re_fn_t)MenuSelect004074FA },
  { 0x00407539u, (re_fn_t)Menu549FCC },
  { 0x00407563u, (re_fn_t)P12_Fn00407563 },
  { 0x004075bfu, (re_fn_t)MenuSelect004075BF },
  { 0x00407605u, (re_fn_t)MenuSlotHandler00407605 },
  { 0x00407636u, (re_fn_t)ToggleVar00407636 },
  { 0x0040766du, (re_fn_t)MenuRed0040766D },
  { 0x004076e2u, (re_fn_t)MenuWhite004076E2 },
  { 0x004078d0u, (re_fn_t)P100_LfbFormat },
  { 0x004079aau, (re_fn_t)P125_BlendTable },
  { 0x00407c27u, (re_fn_t)Copy400_00407C27 },
  { 0x00407c42u, (re_fn_t)MenuReturnOne },
  { 0x00407c4cu, (re_fn_t)P105_LfbToMenu },
  { 0x00407cb8u, (re_fn_t)P65_SpriteKeyed },
  { 0x00407d07u, (re_fn_t)P65_SpriteBlend },
  { 0x00407d56u, (re_fn_t)SndHelper_00407D56 },
  { 0x00407d97u, (re_fn_t)SndHelper_00407D97 },
  { 0x00407dbau, (re_fn_t)P58_ItemsDraw },
  { 0x00407e2fu, (re_fn_t)P100_IconLfb2x },
  { 0x004082a0u, (re_fn_t)P57_Menu4082A0 },
  { 0x0040831cu, (re_fn_t)MenuCopyPos },
  { 0x00408337u, (re_fn_t)MenuFlag54A0BCSet },
  { 0x00408343u, (re_fn_t)MenuFlag54A0BCClear },
  { 0x0040834fu, (re_fn_t)P45_ModeA },
  { 0x0040844cu, (re_fn_t)MenuVar54A0CCClear },
  { 0x00408458u, (re_fn_t)P45_ModeB },
  { 0x00408600u, (re_fn_t)P58_PlayDemo },
  { 0x00408699u, (re_fn_t)Ui00408699 },
  { 0x004086b4u, (re_fn_t)StartTimer004086B4 },
  { 0x004086eau, (re_fn_t)StopTimer4086EA },
  { 0x00408710u, (re_fn_t)MenuCounter5D577CInc },
  { 0x00408770u, (re_fn_t)P77_Menu408770 },
  { 0x00408864u, (re_fn_t)MenuSelect00408864 },
  { 0x004088aau, (re_fn_t)MenuSlotHandler004088AA },
  { 0x004088dbu, (re_fn_t)MenuQuality004088DB },
  { 0x0040891du, (re_fn_t)MenuSelect0040891D },
  { 0x00408963u, (re_fn_t)MenuSlotHandler00408963 },
  { 0x00408994u, (re_fn_t)MenuToggle00408994 },
  { 0x004089f2u, (re_fn_t)MenuSelect004089F2 },
  { 0x00408a38u, (re_fn_t)MenuSlotHandler00408A38 },
  { 0x00408a69u, (re_fn_t)MenuToggle55384CRedraw },
  { 0x00408a8cu, (re_fn_t)MenuSelect00408A8C },
  { 0x00408ad2u, (re_fn_t)MenuSlotHandler00408AD2 },
  { 0x00408b03u, (re_fn_t)MenuToggle553850Redraw },
  { 0x00408b26u, (re_fn_t)MenuSelect00408B26 },
  { 0x00408b6cu, (re_fn_t)MenuSlotHandler00408B6C },
  { 0x00408b9du, (re_fn_t)MenuToggleB31F04Redraw },
  { 0x00408bc0u, (re_fn_t)MenuSelect00408BC0 },
  { 0x00408c06u, (re_fn_t)MenuSlotHandler00408C06 },
  { 0x00408c37u, (re_fn_t)MenuToggle00408C37 },
  { 0x00408c95u, (re_fn_t)MenuSelect00408C95 },
  { 0x00408cdbu, (re_fn_t)MenuSlotHandler00408CDB },
  { 0x00408d0cu, (re_fn_t)MenuToggle575F44Redraw },
  { 0x00408d2fu, (re_fn_t)MenuSelect00408D2F },
  { 0x00408d75u, (re_fn_t)MenuSlotHandler00408D75 },
  { 0x00408da6u, (re_fn_t)MenuToggle55C974Redraw },
  { 0x00408dc9u, (re_fn_t)MenuSelect00408DC9 },
  { 0x00408e0fu, (re_fn_t)MenuSlotHandler00408E0F },
  { 0x00408e40u, (re_fn_t)MenuToggle575F30Redraw },
  { 0x00408e63u, (re_fn_t)MenuSelect00408E63 },
  { 0x00408ea9u, (re_fn_t)MenuSlotHandler00408EA9 },
  { 0x00408edau, (re_fn_t)MenuToggleB201DCRedraw },
  { 0x00408efdu, (re_fn_t)MenuSelect00408EFD },
  { 0x00408f43u, (re_fn_t)MenuSlotHandler00408F43 },
  { 0x00408f74u, (re_fn_t)MenuToggle575EE8Redraw },
  { 0x00408f97u, (re_fn_t)MenuSelect00408F97 },
  { 0x00408fddu, (re_fn_t)MenuSlotHandler00408FDD },
  { 0x0040900eu, (re_fn_t)MenuToggle575F3CRedraw },
  { 0x00409031u, (re_fn_t)MenuSelect00409031 },
  { 0x00409077u, (re_fn_t)MenuSlotHandler00409077 },
  { 0x004090a8u, (re_fn_t)MenuToggleD118C8Redraw },
  { 0x004090cbu, (re_fn_t)MenuSelect004090CB },
  { 0x00409111u, (re_fn_t)MenuSlotHandler00409111 },
  { 0x00409142u, (re_fn_t)MenuToggle00409142 },
  { 0x004091a0u, (re_fn_t)MenuSelect004091A0 },
  { 0x004091f3u, (re_fn_t)MenuSlotHandlerReset004091F3 },
  { 0x00409231u, (re_fn_t)MenuRedraw409231 },
  { 0x00409247u, (re_fn_t)MenuSelect00409247 },
  { 0x0040929au, (re_fn_t)MenuSlotHandlerReset0040929A },
  { 0x004092d8u, (re_fn_t)MenuRedraw4092D8 },
  { 0x004092eeu, (re_fn_t)MenuSelect004092EE },
  { 0x00409341u, (re_fn_t)MenuSlotHandlerReset00409341 },
  { 0x0040937fu, (re_fn_t)MenuRedraw40937F },
  { 0x00409395u, (re_fn_t)MenuSelect00409395 },
  { 0x004093e8u, (re_fn_t)MenuSlotHandlerReset004093E8 },
  { 0x00409426u, (re_fn_t)MenuRedraw409426 },
  { 0x0040943cu, (re_fn_t)MenuSelect0040943C },
  { 0x0040948fu, (re_fn_t)MenuSlotHandlerReset0040948F },
  { 0x004094cdu, (re_fn_t)MenuRedraw4094CD },
  { 0x004094e3u, (re_fn_t)P94_ClampView },
  { 0x00409622u, (re_fn_t)P104_GfxMenuInit },
  { 0x00409a91u, (re_fn_t)FloatStep00409A91 },
  { 0x00409acau, (re_fn_t)FloatStep00409ACA },
  { 0x00409b03u, (re_fn_t)FloatStep00409B03 },
  { 0x00409b3cu, (re_fn_t)FloatStep00409B3C },
  { 0x00409b75u, (re_fn_t)MenuIncVar5759A4 },
  { 0x00409b9fu, (re_fn_t)MenuDecVar5759A4 },
  { 0x00409bc9u, (re_fn_t)VolumeUp00409BC9 },
  { 0x00409bfdu, (re_fn_t)VolumeDown00409BFD },
  { 0x00409c31u, (re_fn_t)MenuIncVarB87E4C },
  { 0x00409c5bu, (re_fn_t)MenuDecVarB87E4C },
  { 0x00409c85u, (re_fn_t)MenuRed00409C85 },
  { 0x00409cfau, (re_fn_t)MenuWhite00409CFA },
  { 0x00409d66u, (re_fn_t)P55_MenuLangCall },
  { 0x0040a3a0u, (re_fn_t)P57_Menu40A3A0 },
  { 0x0040a41cu, (re_fn_t)Copy54A838 },
  { 0x0040a443u, (re_fn_t)MenuSet54A844On },
  { 0x0040a44fu, (re_fn_t)MenuSet54A844Off },
  { 0x0040a45bu, (re_fn_t)P12_Fn0040A45B },
  { 0x0040a495u, (re_fn_t)MenuSet54A854On },
  { 0x0040a4a1u, (re_fn_t)MenuSet54A854Off },
  { 0x0040a4adu, (re_fn_t)P12_Fn0040A4AD },
  { 0x0040a540u, (re_fn_t)P57_Menu40A540 },
  { 0x0040a5c6u, (re_fn_t)GlobalSet0040A5C6 },
  { 0x0040a625u, (re_fn_t)MenuEnterMode2 },
  { 0x0040a63bu, (re_fn_t)MenuLeaveMode2 },
  { 0x0040a64du, (re_fn_t)MenuEnterMode1 },
  { 0x0040a663u, (re_fn_t)MenuLeaveMode1 },
  { 0x0040a675u, (re_fn_t)MenuEnterMode5 },
  { 0x0040a68bu, (re_fn_t)MenuLeaveMode5 },
  { 0x0040a69du, (re_fn_t)MenuEnterMode3 },
  { 0x0040a6b3u, (re_fn_t)MenuLeaveMode3 },
  { 0x0040a6c5u, (re_fn_t)MenuEnterMode4 },
  { 0x0040a6dbu, (re_fn_t)MenuLeaveMode4 },
  { 0x0040a6edu, (re_fn_t)MenuEnterMode7 },
  { 0x0040a703u, (re_fn_t)MenuLeaveMode7 },
  { 0x0040a715u, (re_fn_t)MenuEnterMode6 },
  { 0x0040a72bu, (re_fn_t)MenuLeaveMode6 },
  { 0x0040a73du, (re_fn_t)P47_TitleDispatch },
  { 0x0040a8b0u, (re_fn_t)P122_FontIcons },
  { 0x0040aa82u, (re_fn_t)CopySlots_0040AA82 },
  { 0x0040aae2u, (re_fn_t)ScanSlot_0040AAE2 },
  { 0x0040ab3au, (re_fn_t)MenuSetColor },
  { 0x0040ab59u, (re_fn_t)MenuSetPos },
  { 0x0040ab6fu, (re_fn_t)MenuSetVals5D77C0 },
  { 0x0040ab9fu, (re_fn_t)MenuSetByte5D77C1 },
  { 0x0040abacu, (re_fn_t)P116_Text },
  { 0x0040b0a4u, (re_fn_t)GlobalSet0040B0A4 },
  { 0x0040b0feu, (re_fn_t)P95_TextWidthCur },
  { 0x0040b1ccu, (re_fn_t)P58_TextWidth },
  { 0x0040b286u, (re_fn_t)P115_IconDraw },
  { 0x0040b6fdu, (re_fn_t)P109_IconDraw },
  { 0x0040bf50u, (re_fn_t)P136_FrontInit },
  { 0x0040c165u, (re_fn_t)P56_ResetFrontend },
  { 0x0040c20bu, (re_fn_t)P136_GameLoop },
  { 0x0040c455u, (re_fn_t)Call3_0040C455 },
  { 0x0040c480u, (re_fn_t)P68_ScreenReset },
  { 0x0040c533u, (re_fn_t)P55_SetScreen },
  { 0x0040c5beu, (re_fn_t)P54_ClearSwap },
  { 0x0040c610u, (re_fn_t)P124_ShowBmp },
  { 0x0040c6bbu, (re_fn_t)P126_ShowBmpFade },
  { 0x0040c813u, (re_fn_t)P12_Fn0040C813 },
  { 0x0040c867u, (re_fn_t)Ui0040C867 },
  { 0x0040c87au, (re_fn_t)Ui0040C87A },
  { 0x0040c88du, (re_fn_t)Ui0040C88D },
  { 0x0040c8a0u, (re_fn_t)P97_MenuCall0 },
  { 0x0040c8f1u, (re_fn_t)P114_MenuStep },
  { 0x0040cb9fu, (re_fn_t)P119_MenuFrame },
  { 0x0040ccb4u, (re_fn_t)P45_Wait },
  { 0x0040cd17u, (re_fn_t)P57_MenuDone },
  { 0x0040cd6fu, (re_fn_t)P98_ItemsDraw },
  { 0x0040ce31u, (re_fn_t)P117_TextList },
  { 0x0040cf35u, (re_fn_t)P58_Backgrounds },
  { 0x0040cfdfu, (re_fn_t)P67_DrawIcon },
  { 0x0040d07bu, (re_fn_t)P137_LoadTsd },
  { 0x0040d4b3u, (re_fn_t)P59_ReadBlock },
  { 0x0040d56cu, (re_fn_t)P122_MapNames },
  { 0x0040d6e8u, (re_fn_t)P124_ReadBmp },
  { 0x0040d81bu, (re_fn_t)P105_BlitScaled },
  { 0x0040da56u, (re_fn_t)P12_Fn0040DA56 },
  { 0x0040dae1u, (re_fn_t)P75_BmpToPage },
  { 0x0040dbeeu, (re_fn_t)P76_TileFill },
  { 0x0040dce0u, (re_fn_t)P109_TileDraw },
  { 0x0040e870u, (re_fn_t)P57_Menu40E870 },
  { 0x0040e8ecu, (re_fn_t)MenuSet54ACD4To3 },
  { 0x0040e8ffu, (re_fn_t)MenuLeave0040E8FF },
  { 0x0040e918u, (re_fn_t)CycleInc0040E918 },
  { 0x0040e944u, (re_fn_t)MenuSet54ACF4To3 },
  { 0x0040e957u, (re_fn_t)MenuLeave0040E957 },
  { 0x0040e970u, (re_fn_t)MenuToggle575F24Call40EA70 },
  { 0x0040e989u, (re_fn_t)MenuSet54AD14To3 },
  { 0x0040e99cu, (re_fn_t)MenuLeave0040E99C },
  { 0x0040e9b5u, (re_fn_t)MenuTri0040E9B5 },
  { 0x0040ea2bu, (re_fn_t)MenuSet54AD34To3 },
  { 0x0040ea3eu, (re_fn_t)MenuLeave0040EA3E },
  { 0x0040ea57u, (re_fn_t)MenuToggle575F48Call40EA70 },
  { 0x0040ea70u, (re_fn_t)P97_OptMenuAInit },
  { 0x0040ec30u, (re_fn_t)P140_KeysLoad },
  { 0x0040efd5u, (re_fn_t)P74_KeyScan },
  { 0x0040f09cu, (re_fn_t)P12_Fn0040F09C },
  { 0x0040f0e7u, (re_fn_t)MenuTableGet54B010 },
  { 0x0040f0fbu, (re_fn_t)P14_Fn0040F0FB },
  { 0x0040f14au, (re_fn_t)P21_GetNameByIndex },
  { 0x0040f2d0u, (re_fn_t)P57_Menu40F2D0 },
  { 0x0040f34cu, (re_fn_t)MenuSet54BE5CTo3 },
  { 0x0040f358u, (re_fn_t)MenuSet54BE5CTo2 },
  { 0x0040f364u, (re_fn_t)CycleDec0040F364 },
  { 0x0040f395u, (re_fn_t)MenuSet54BE7CTo3 },
  { 0x0040f3a1u, (re_fn_t)MenuSet54BE7CTo2 },
  { 0x0040f3adu, (re_fn_t)CycleInc0040F3AD },
  { 0x0040f3deu, (re_fn_t)P141_HsSetup },
  { 0x0040fa60u, (re_fn_t)P139_KeyMenuA },
  { 0x0040fc9au, (re_fn_t)P97_KeyMenuAInit },
  { 0x0040fe29u, (re_fn_t)MenuSelect0040FE29 },
  { 0x0040fe6fu, (re_fn_t)MenuSlotHandler0040FE6F },
  { 0x0040fea0u, (re_fn_t)MenuPick0040FEA0 },
  { 0x0040fee3u, (re_fn_t)MenuSelect0040FEE3 },
  { 0x0040ff29u, (re_fn_t)MenuSlotHandler0040FF29 },
  { 0x0040ff5au, (re_fn_t)MenuPick0040FF5A },
  { 0x0040ff9du, (re_fn_t)MenuSelect0040FF9D },
  { 0x0040ffe3u, (re_fn_t)MenuSlotHandler0040FFE3 },
  { 0x00410014u, (re_fn_t)MenuPick00410014 },
  { 0x00410057u, (re_fn_t)MenuSelect00410057 },
  { 0x0041009du, (re_fn_t)MenuSlotHandler0041009D },
  { 0x004100ceu, (re_fn_t)MenuPick004100CE },
  { 0x00410111u, (re_fn_t)MenuSelect00410111 },
  { 0x00410157u, (re_fn_t)MenuSlotHandler00410157 },
  { 0x00410188u, (re_fn_t)MenuPick00410188 },
  { 0x004101cbu, (re_fn_t)MenuSelect004101CB },
  { 0x00410211u, (re_fn_t)MenuSlotHandler00410211 },
  { 0x00410242u, (re_fn_t)MenuPick00410242 },
  { 0x00410285u, (re_fn_t)MenuSelect00410285 },
  { 0x004102cbu, (re_fn_t)MenuSlotHandler004102CB },
  { 0x004102fcu, (re_fn_t)MenuPick004102FC },
  { 0x0041033fu, (re_fn_t)MenuSelect0041033F },
  { 0x00410385u, (re_fn_t)MenuSlotHandler00410385 },
  { 0x004103b6u, (re_fn_t)MenuPick004103B6 },
  { 0x004103f9u, (re_fn_t)MenuSelect004103F9 },
  { 0x0041043fu, (re_fn_t)MenuSlotHandler0041043F },
  { 0x00410470u, (re_fn_t)MenuPick00410470 },
  { 0x004104b3u, (re_fn_t)MenuSelect004104B3 },
  { 0x004104f9u, (re_fn_t)MenuSlotHandler004104F9 },
  { 0x0041052au, (re_fn_t)MenuPick0041052A },
  { 0x0041056du, (re_fn_t)MenuSelect0041056D },
  { 0x004105b3u, (re_fn_t)MenuSlotHandler004105B3 },
  { 0x004105e4u, (re_fn_t)MenuPick004105E4 },
  { 0x00410627u, (re_fn_t)MenuSelect00410627 },
  { 0x0041066du, (re_fn_t)MenuSlotHandler0041066D },
  { 0x0041069eu, (re_fn_t)MenuPick0041069E },
  { 0x004106e1u, (re_fn_t)MenuHiliteRed004106E1 },
  { 0x0041074du, (re_fn_t)MenuHiliteWhite0041074D },
  { 0x004107b9u, (re_fn_t)P19_KeysUnique12 },
  { 0x00410c30u, (re_fn_t)P139_KeyMenuB },
  { 0x00410e89u, (re_fn_t)P97_KeyMenuBInit },
  { 0x0041104bu, (re_fn_t)MenuSelect0041104B },
  { 0x00411091u, (re_fn_t)MenuSlotHandler00411091 },
  { 0x004110c2u, (re_fn_t)SelectRow004110C2 },
  { 0x00411100u, (re_fn_t)MenuSelect00411100 },
  { 0x00411146u, (re_fn_t)MenuSlotHandler00411146 },
  { 0x00411177u, (re_fn_t)SelectRow00411177 },
  { 0x004111b5u, (re_fn_t)MenuSelect004111B5 },
  { 0x004111fbu, (re_fn_t)MenuSlotHandler004111FB },
  { 0x0041122cu, (re_fn_t)SelectRow0041122C },
  { 0x0041126au, (re_fn_t)MenuSelect0041126A },
  { 0x004112b0u, (re_fn_t)MenuSlotHandler004112B0 },
  { 0x004112e1u, (re_fn_t)SelectRow004112E1 },
  { 0x0041131fu, (re_fn_t)MenuSelect0041131F },
  { 0x00411365u, (re_fn_t)MenuSlotHandler00411365 },
  { 0x00411396u, (re_fn_t)SelectRow00411396 },
  { 0x004113d4u, (re_fn_t)MenuSelect004113D4 },
  { 0x0041141au, (re_fn_t)MenuSlotHandler0041141A },
  { 0x0041144bu, (re_fn_t)SelectRow0041144B },
  { 0x00411489u, (re_fn_t)MenuSelect00411489 },
  { 0x004114cfu, (re_fn_t)MenuSlotHandler004114CF },
  { 0x00411500u, (re_fn_t)SelectRow00411500 },
  { 0x0041153eu, (re_fn_t)MenuSelect0041153E },
  { 0x00411584u, (re_fn_t)MenuSlotHandler00411584 },
  { 0x004115b5u, (re_fn_t)SelectRow004115B5 },
  { 0x004115f3u, (re_fn_t)MenuSelect004115F3 },
  { 0x00411639u, (re_fn_t)MenuSlotHandler00411639 },
  { 0x0041166au, (re_fn_t)SelectRow0041166A },
  { 0x004116a8u, (re_fn_t)MenuSelect004116A8 },
  { 0x004116eeu, (re_fn_t)MenuSlotHandler004116EE },
  { 0x0041171fu, (re_fn_t)SelectRow0041171F },
  { 0x0041175du, (re_fn_t)MenuSelect0041175D },
  { 0x004117a3u, (re_fn_t)MenuSlotHandler004117A3 },
  { 0x004117d4u, (re_fn_t)SelectRow004117D4 },
  { 0x00411812u, (re_fn_t)MenuSelect00411812 },
  { 0x00411858u, (re_fn_t)MenuSlotHandler00411858 },
  { 0x00411889u, (re_fn_t)SelectRow00411889 },
  { 0x004118c7u, (re_fn_t)MenuSelect004118C7 },
  { 0x0041190du, (re_fn_t)MenuSlotHandler0041190D },
  { 0x0041193eu, (re_fn_t)SelectRow0041193E },
  { 0x0041197cu, (re_fn_t)MenuSelect0041197C },
  { 0x004119c2u, (re_fn_t)MenuSlotHandler004119C2 },
  { 0x004119f3u, (re_fn_t)SelectRow004119F3 },
  { 0x00411a31u, (re_fn_t)MenuHiliteRed00411A31 },
  { 0x00411a9du, (re_fn_t)MenuHiliteWhite00411A9D },
  { 0x00411b09u, (re_fn_t)P19_KeysUnique14 },
  { 0x00411fd0u, (re_fn_t)P57_Menu411FD0 },
  { 0x00412087u, (re_fn_t)SetupMenuTable00412087 },
  { 0x004120afu, (re_fn_t)P12_Fn004120AF },
  { 0x004120eeu, (re_fn_t)Ui004120EE },
  { 0x004120feu, (re_fn_t)Ui004120FE },
  { 0x00412112u, (re_fn_t)Ui00412112 },
  { 0x00412126u, (re_fn_t)Ui00412126 },
  { 0x0041213au, (re_fn_t)Ui0041213A },
  { 0x0041214eu, (re_fn_t)Ui0041214E },
  { 0x00412162u, (re_fn_t)Ui00412162 },
  { 0x00412176u, (re_fn_t)Ui00412176 },
  { 0x0041218au, (re_fn_t)Ui0041218A },
  { 0x0041219eu, (re_fn_t)P55_NamesA },
  { 0x00412228u, (re_fn_t)MenuMark00412228 },
  { 0x00412254u, (re_fn_t)MenuRowsTo2_00412254 },
  { 0x00412280u, (re_fn_t)MenuAllRowsTo2_00412280 },
  { 0x004122c4u, (re_fn_t)GlobalSet004122C4 },
  { 0x004122e7u, (re_fn_t)Ui004122E7 },
  { 0x004123d0u, (re_fn_t)P57_Menu4123D0 },
  { 0x00412487u, (re_fn_t)SetupMenuTable00412487 },
  { 0x004124afu, (re_fn_t)P12_Fn004124AF },
  { 0x00412509u, (re_fn_t)Ui00412509 },
  { 0x00412519u, (re_fn_t)Ui00412519 },
  { 0x0041252du, (re_fn_t)Ui0041252D },
  { 0x00412541u, (re_fn_t)Ui00412541 },
  { 0x00412555u, (re_fn_t)Ui00412555 },
  { 0x00412569u, (re_fn_t)Ui00412569 },
  { 0x0041257du, (re_fn_t)Ui0041257D },
  { 0x00412591u, (re_fn_t)Ui00412591 },
  { 0x004125a5u, (re_fn_t)Ui004125A5 },
  { 0x004125b9u, (re_fn_t)P55_NamesB },
  { 0x00412643u, (re_fn_t)MenuRowsTo3_00412643 },
  { 0x0041266fu, (re_fn_t)MenuRowsTo2_0041266F },
  { 0x0041269bu, (re_fn_t)MenuAllRowsTo2_0041269B },
  { 0x004126dfu, (re_fn_t)GlobalSet004126DF },
  { 0x00412702u, (re_fn_t)Ui00412702 },
  { 0x004127f0u, (re_fn_t)P140_Frontend },
  { 0x004129dfu, (re_fn_t)P12_Fn004129DF },
  { 0x00412a0du, (re_fn_t)SetIconIdx00412A0D },
  { 0x00412a36u, (re_fn_t)SetIconName00412A36 },
  { 0x00412a4bu, (re_fn_t)P12_Fn00412A4B },
  { 0x00412a7bu, (re_fn_t)SetIconIdx00412A7B },
  { 0x00412aa4u, (re_fn_t)SetIconName00412AA4 },
  { 0x00412ab9u, (re_fn_t)P12_Fn00412AB9 },
  { 0x00412ae9u, (re_fn_t)SetIconIdx00412AE9 },
  { 0x00412b12u, (re_fn_t)SetIconName00412B12 },
  { 0x00412b27u, (re_fn_t)P12_Fn00412B27 },
  { 0x00412b57u, (re_fn_t)SetIconIdx00412B57 },
  { 0x00412b80u, (re_fn_t)SetIconName00412B80 },
  { 0x00412b95u, (re_fn_t)P12_Fn00412B95 },
  { 0x00412bc5u, (re_fn_t)SetIconIdx00412BC5 },
  { 0x00412beeu, (re_fn_t)SetIconName00412BEE },
  { 0x00412c03u, (re_fn_t)P12_Fn00412C03 },
  { 0x00412c33u, (re_fn_t)SetIconIdx00412C33 },
  { 0x00412c5cu, (re_fn_t)SetIconName00412C5C },
  { 0x00412c71u, (re_fn_t)P12_Fn00412C71 },
  { 0x00412ca1u, (re_fn_t)SetIconIdx00412CA1 },
  { 0x00412ccau, (re_fn_t)SetIconName00412CCA },
  { 0x00412cdfu, (re_fn_t)P12_Fn00412CDF },
  { 0x00412d0fu, (re_fn_t)SetIconIdx00412D0F },
  { 0x00412d38u, (re_fn_t)SetIconName00412D38 },
  { 0x00412d4du, (re_fn_t)P12_Fn00412D4D },
  { 0x00412d7du, (re_fn_t)P99_MenuDim },
  { 0x00412f3au, (re_fn_t)Ui00412F3A },
  { 0x00412f56u, (re_fn_t)Ui00412F56 },
  { 0x00412f62u, (re_fn_t)Ui00412F62 },
  { 0x00412f74u, (re_fn_t)Ui00412F74 },
  { 0x00412f90u, (re_fn_t)Ui00412F90 },
  { 0x00412f9cu, (re_fn_t)Ui00412F9C },
  { 0x004131a0u, (re_fn_t)P127_NameEntry },
  { 0x00413381u, (re_fn_t)P58_CheatsAll },
  { 0x004133b4u, (re_fn_t)P58_CheatByName },
  { 0x004134a0u, (re_fn_t)P57_Menu4134A0 },
  { 0x0041351cu, (re_fn_t)GlobalSet0041351C },
  { 0x00413543u, (re_fn_t)Ui00413543 },
  { 0x0041354fu, (re_fn_t)Ui0041354F },
  { 0x0041355bu, (re_fn_t)Ui0041355B },
  { 0x0041357eu, (re_fn_t)Ui0041357E },
  { 0x0041358au, (re_fn_t)Ui0041358A },
  { 0x00413596u, (re_fn_t)P12_Fn00413596 },
  { 0x00413610u, (re_fn_t)P57_Menu413610 },
  { 0x00413691u, (re_fn_t)GlobalSet00413691 },
  { 0x004136ceu, (re_fn_t)Ui004136CE },
  { 0x004136dau, (re_fn_t)MenuLeave004136DA },
  { 0x004136ecu, (re_fn_t)P12_Fn004136EC },
  { 0x0041371cu, (re_fn_t)Ui0041371C },
  { 0x00413728u, (re_fn_t)MenuLeave00413728 },
  { 0x0041373au, (re_fn_t)P12_Fn0041373A },
  { 0x0041376au, (re_fn_t)Ui0041376A },
  { 0x00413776u, (re_fn_t)MenuLeave00413776 },
  { 0x00413788u, (re_fn_t)P12_Fn00413788 },
  { 0x004137b8u, (re_fn_t)Ui004137B8 },
  { 0x004137c4u, (re_fn_t)MenuLeave004137C4 },
  { 0x004137d6u, (re_fn_t)P12_Fn004137D6 },
  { 0x00413890u, (re_fn_t)P57_Menu413890 },
  { 0x0041390cu, (re_fn_t)GlobalSet0041390C },
  { 0x00413955u, (re_fn_t)Ui00413955 },
  { 0x00413961u, (re_fn_t)MenuLeave00413961 },
  { 0x00413973u, (re_fn_t)P12_Fn00413973 },
  { 0x004139a3u, (re_fn_t)Ui004139A3 },
  { 0x004139afu, (re_fn_t)MenuLeave004139AF },
  { 0x004139c1u, (re_fn_t)Ui004139C1 },
  { 0x004139dau, (re_fn_t)Ui004139DA },
  { 0x004139e6u, (re_fn_t)MenuLeave004139E6 },
  { 0x004139f8u, (re_fn_t)Ui004139F8 },
  { 0x00413a11u, (re_fn_t)Ui00413A11 },
  { 0x00413a1du, (re_fn_t)MenuLeave00413A1D },
  { 0x00413a2fu, (re_fn_t)Ui00413A2F },
  { 0x00413a48u, (re_fn_t)Ui00413A48 },
  { 0x00413a54u, (re_fn_t)MenuLeave00413A54 },
  { 0x00413a66u, (re_fn_t)Ui00413A66 },
  { 0x00413b00u, (re_fn_t)P57_Menu413B00 },
  { 0x00413b7cu, (re_fn_t)GlobalSet00413B7C },
  { 0x00413bc5u, (re_fn_t)Ui00413BC5 },
  { 0x00413be5u, (re_fn_t)MenuLeave00413BE5 },
  { 0x00413bf7u, (re_fn_t)Ui00413BF7 },
  { 0x00413c17u, (re_fn_t)MenuLeave00413C17 },
  { 0x00413c29u, (re_fn_t)Ui00413C29 },
  { 0x00413c49u, (re_fn_t)MenuLeave00413C49 },
  { 0x00413c5bu, (re_fn_t)Ui00413C5B },
  { 0x00413c7bu, (re_fn_t)MenuLeave00413C7B },
  { 0x00413c8du, (re_fn_t)Ui00413C8D },
  { 0x00413cadu, (re_fn_t)MenuLeave00413CAD },
  { 0x00413cbfu, (re_fn_t)P12_Fn00413CBF },
  { 0x00413d70u, (re_fn_t)P58_Menu413D70 },
  { 0x00413df3u, (re_fn_t)P62_MenuBusy },
  { 0x00413e37u, (re_fn_t)P100_PadMenuInit },
  { 0x00414264u, (re_fn_t)MenuBtn00414264 },
  { 0x004142a4u, (re_fn_t)P15_MenuMiami },
  { 0x004142e8u, (re_fn_t)UiSetSlot004142E8 },
  { 0x004142fcu, (re_fn_t)P15_MenuItem2 },
  { 0x00414376u, (re_fn_t)MenuBtn00414376 },
  { 0x004143b6u, (re_fn_t)P15_MenuItem3 },
  { 0x004143fau, (re_fn_t)UiSetSlot004143FA },
  { 0x0041440eu, (re_fn_t)P15_MenuItem4 },
  { 0x00414488u, (re_fn_t)MenuBtn00414488 },
  { 0x004144c8u, (re_fn_t)P15_MenuItem5 },
  { 0x0041450cu, (re_fn_t)UiSetSlot0041450C },
  { 0x00414520u, (re_fn_t)P15_MenuItem6 },
  { 0x0041459au, (re_fn_t)MenuBtn0041459A },
  { 0x004145dau, (re_fn_t)P15_MenuItem7 },
  { 0x00414621u, (re_fn_t)UiSetSlot00414621 },
  { 0x00414638u, (re_fn_t)P53_MenuC },
  { 0x004148b9u, (re_fn_t)P15_SetHighlightRange },
  { 0x00414c30u, (re_fn_t)P77_Menu414C30 },
  { 0x00414d1fu, (re_fn_t)P103_OptionsInit },
  { 0x00414f9du, (re_fn_t)MenuSelect00414F9D },
  { 0x00414fe3u, (re_fn_t)MenuSlotHandler00414FE3 },
  { 0x00415014u, (re_fn_t)P121_SndNextDev },
  { 0x00415111u, (re_fn_t)MenuSelect00415111 },
  { 0x00415157u, (re_fn_t)MenuSlotHandler00415157 },
  { 0x00415188u, (re_fn_t)P67_Menu415188 },
  { 0x00415230u, (re_fn_t)MenuSelect00415230 },
  { 0x00415276u, (re_fn_t)MenuSlotHandler00415276 },
  { 0x004152a7u, (re_fn_t)P12_Fn004152A7 },
  { 0x00415323u, (re_fn_t)MenuSelect00415323 },
  { 0x00415369u, (re_fn_t)MenuSlotHandler00415369 },
  { 0x0041539au, (re_fn_t)MenuToggle575F40Call414D1F },
  { 0x004153b3u, (re_fn_t)MenuSelect004153B3 },
  { 0x004153f9u, (re_fn_t)MenuSlotHandler004153F9 },
  { 0x0041542au, (re_fn_t)ToggleOpt0041542A },
  { 0x00415456u, (re_fn_t)MenuSelect00415456 },
  { 0x0041549cu, (re_fn_t)MenuSlotHandler0041549C },
  { 0x004154cdu, (re_fn_t)ToggleOpt004154CD },
  { 0x004154f5u, (re_fn_t)MenuSelect004154F5 },
  { 0x0041553bu, (re_fn_t)MenuSlotHandler0041553B },
  { 0x0041556cu, (re_fn_t)MenuBits0041556C },
  { 0x004155acu, (re_fn_t)MenuSelect004155AC },
  { 0x004155f2u, (re_fn_t)MenuSlotHandler004155F2 },
  { 0x00415623u, (re_fn_t)MenuRate00415623 },
  { 0x00415666u, (re_fn_t)MenuSelect00415666 },
  { 0x004156acu, (re_fn_t)MenuSlotHandler004156AC },
  { 0x004156ddu, (re_fn_t)MenuSoundCh004156DD },
  { 0x00415718u, (re_fn_t)MenuSelect00415718 },
  { 0x0041576bu, (re_fn_t)MenuSlotHandlerReset0041576B },
  { 0x004157a9u, (re_fn_t)Ui004157A9 },
  { 0x004157b0u, (re_fn_t)MenuSelect004157B0 },
  { 0x00415803u, (re_fn_t)MenuSlotHandlerReset00415803 },
  { 0x00415841u, (re_fn_t)Ui00415841 },
  { 0x00415848u, (re_fn_t)StepUp00415848 },
  { 0x00415877u, (re_fn_t)StepDown00415877 },
  { 0x004158a6u, (re_fn_t)StepUp004158A6 },
  { 0x004158d5u, (re_fn_t)StepDown004158D5 },
  { 0x00415904u, (re_fn_t)MenuRed00415904 },
  { 0x00415979u, (re_fn_t)MenuWhite00415979 },
  { 0x004159e5u, (re_fn_t)P116_Sliders2 },
  { 0x00415ec0u, (re_fn_t)P67_Menu415EC0 },
  { 0x00415f67u, (re_fn_t)P58_PrepPage },
  { 0x00416040u, (re_fn_t)SetupMiami00416040 },
  { 0x00416072u, (re_fn_t)MenuLeave00416072 },
  { 0x00416084u, (re_fn_t)P19_Sel2 },
  { 0x004160d7u, (re_fn_t)MenuLeave004160D7 },
  { 0x004160e9u, (re_fn_t)P19_Sel3 },
  { 0x0041613cu, (re_fn_t)MenuLeave0041613C },
  { 0x0041614eu, (re_fn_t)P19_Sel4 },
  { 0x004161a1u, (re_fn_t)MenuLeave004161A1 },
  { 0x004161b3u, (re_fn_t)P53_MenuA },
  { 0x0041621cu, (re_fn_t)SetHiliteBits_0041621C },
  { 0x00416390u, (re_fn_t)P57_Menu416390 },
  { 0x0041640cu, (re_fn_t)GlobalSet0041640C },
  { 0x00416433u, (re_fn_t)GlobalSet00416433 },
  { 0x00416449u, (re_fn_t)MenuLeave00416449 },
  { 0x0041645bu, (re_fn_t)MenuAction_0041645B },
  { 0x0041648au, (re_fn_t)GlobalSet0041648A },
  { 0x004164a0u, (re_fn_t)MenuLeave004164A0 },
  { 0x004164b2u, (re_fn_t)MenuAction_004164B2 },
  { 0x00416540u, (re_fn_t)P58_Menu416540 },
  { 0x00416605u, (re_fn_t)P100_ReplayMenuInit },
  { 0x00416794u, (re_fn_t)P124_MotelKeys },
  { 0x00416d17u, (re_fn_t)SelectByDifficulty_00416D17 },
  { 0x00416d6du, (re_fn_t)P124_MotelSample },
  { 0x004171f0u, (re_fn_t)P124_CarSelect },
  { 0x00417353u, (re_fn_t)LoadArrowIcons00417353 },
  { 0x00417386u, (re_fn_t)P119_CarSelKey },
  { 0x00417479u, (re_fn_t)P97_BlinkAStep },
  { 0x00417620u, (re_fn_t)LoadSliderIcons00417620 },
  { 0x00417651u, (re_fn_t)P116_Sliders5 },
  { 0x00417970u, (re_fn_t)P67_Menu417970 },
  { 0x00417a2eu, (re_fn_t)GlobalSet00417A2E },
  { 0x00417a55u, (re_fn_t)SetColorRed00417A55 },
  { 0x00417a89u, (re_fn_t)Ui00417A89 },
  { 0x00417a98u, (re_fn_t)Ui00417A98 },
  { 0x00417aa2u, (re_fn_t)SetColorWhite00417AA2 },
  { 0x00417ad6u, (re_fn_t)Ui00417AD6 },
  { 0x00417aeau, (re_fn_t)Ui00417AEA },
  { 0x00417af9u, (re_fn_t)Ui00417AF9 },
  { 0x00417b03u, (re_fn_t)Ui00417B03 },
  { 0x00417b80u, (re_fn_t)P132_MenuLoop },
  { 0x00417cbbu, (re_fn_t)P45_PickColor },
  { 0x00417d56u, (re_fn_t)P59_MenuKeys },
  { 0x00417e0du, (re_fn_t)P58_MenuSwitch },
  { 0x00417f59u, (re_fn_t)MenuPageNext00417F59 },
  { 0x00417facu, (re_fn_t)MenuPagePrev00417FAC },
  { 0x00417fffu, (re_fn_t)P97_BlinkBStep },
  { 0x00418119u, (re_fn_t)Ui00418119 },
  { 0x004182b0u, (re_fn_t)P124_MotelInit },
  { 0x004183a3u, (re_fn_t)ShutdownAudio004183A3 },
  { 0x004183e8u, (re_fn_t)Ui004183E8 },
  { 0x004183f7u, (re_fn_t)P12_Fn004183F7 },
  { 0x00418433u, (re_fn_t)P12_Fn00418433 },
  { 0x0041846cu, (re_fn_t)P66_ScreenFrame },
  { 0x004184deu, (re_fn_t)Ui004184DE },
  { 0x004184f5u, (re_fn_t)P19_FadeStep },
  { 0x004185d2u, (re_fn_t)P97_MenuCall2 },
  { 0x00418675u, (re_fn_t)P110_MenuSel },
  { 0x00418886u, (re_fn_t)Ui00418886 },
  { 0x0041889cu, (re_fn_t)Ui0041889C },
  { 0x004188b0u, (re_fn_t)P66_FrameBegin },
  { 0x0041897cu, (re_fn_t)P66_DrawTable },
  { 0x00418e70u, (re_fn_t)P115_IconAt },
  { 0x0041938au, (re_fn_t)P110_IconQuad },
  { 0x004197f8u, (re_fn_t)Ui004197F8 },
  { 0x00419814u, (re_fn_t)SoundMenuIn00419814 },
  { 0x00419ab0u, (re_fn_t)P58_Menu419AB0 },
  { 0x00419b35u, (re_fn_t)P97_OptMenuBInit },
  { 0x00419c2du, (re_fn_t)Ui00419C2D },
  { 0x00419c46u, (re_fn_t)Ui00419C46 },
  { 0x00419c50u, (re_fn_t)MenuToggle575F24Call419B35 },
  { 0x00419c69u, (re_fn_t)Ui00419C69 },
  { 0x00419c82u, (re_fn_t)Ui00419C82 },
  { 0x00419c8cu, (re_fn_t)MenuTri00419C8C },
  { 0x00419d02u, (re_fn_t)Ui00419D02 },
  { 0x00419d1bu, (re_fn_t)Ui00419D1B },
  { 0x00419d25u, (re_fn_t)MenuToggle575F48Call419B35 },
  { 0x00419d3eu, (re_fn_t)MenuRed00419D3E },
  { 0x00419db3u, (re_fn_t)MenuWhite00419DB3 },
  { 0x00419f00u, (re_fn_t)P58_Menu419F00 },
  { 0x00419f80u, (re_fn_t)GlobalSet00419F80 },
  { 0x00419fbdu, (re_fn_t)Ui00419FBD },
  { 0x00419fccu, (re_fn_t)Ui00419FCC },
  { 0x00419fd6u, (re_fn_t)Ui00419FD6 },
  { 0x00419fe2u, (re_fn_t)Ui00419FE2 },
  { 0x00419ff1u, (re_fn_t)Ui00419FF1 },
  { 0x00419ffbu, (re_fn_t)Ui00419FFB },
  { 0x0041a007u, (re_fn_t)Ui0041A007 },
  { 0x0041a016u, (re_fn_t)Ui0041A016 },
  { 0x0041a020u, (re_fn_t)Ui0041A020 },
  { 0x0041a02cu, (re_fn_t)Ui0041A02C },
  { 0x0041a03bu, (re_fn_t)Ui0041A03B },
  { 0x0041a045u, (re_fn_t)Ui0041A045 },
  { 0x0041a051u, (re_fn_t)SetColorRed0041A051 },
  { 0x0041a085u, (re_fn_t)SetColorWhite0041A085 },
  { 0x0041a130u, (re_fn_t)P47_LoadFlyby },
  { 0x0041a16cu, (re_fn_t)FreeBuffer5FED98 },
  { 0x0041a192u, (re_fn_t)Ui0041A192 },
  { 0x0041a1b5u, (re_fn_t)P48_PosToInts },
  { 0x0041a1ecu, (re_fn_t)Ui0041A1EC },
  { 0x0041a1f9u, (re_fn_t)P118_CamRoute },
  { 0x0041a8abu, (re_fn_t)StepIfActive0041A8AB },
  { 0x0041a8cdu, (re_fn_t)P12_Fn0041A8CD },
  { 0x0041ab60u, (re_fn_t)P122_NameMenu },
  { 0x0041ad8du, (re_fn_t)CopyWord0041AD8D },
  { 0x0041ada1u, (re_fn_t)RedMarkers_0041ADA1 },
  { 0x0041ae25u, (re_fn_t)Ui0041AE25 },
  { 0x0041ae2fu, (re_fn_t)UiSetMode005FEEEC_0 },
  { 0x0041ae43u, (re_fn_t)UiSetMode005FEEEC_1 },
  { 0x0041ae57u, (re_fn_t)UiSetMode005FEEEC_2 },
  { 0x0041ae6bu, (re_fn_t)UiSetMode005FEEEC_3 },
  { 0x0041ae7fu, (re_fn_t)UiSetMode005FEEEC_4 },
  { 0x0041ae93u, (re_fn_t)UiSetMode005FEEEC_5 },
  { 0x0041aea7u, (re_fn_t)UiSetMode005FEEEC_6 },
  { 0x0041aebbu, (re_fn_t)UiSetMode005FEEEC_7 },
  { 0x0041aecfu, (re_fn_t)P12_Fn0041AECF },
  { 0x0041af29u, (re_fn_t)MenuWhite0041AF29 },
  { 0x0041af85u, (re_fn_t)P12_Fn0041AF85 },
  { 0x0041afcau, (re_fn_t)P55_NamesC },
  { 0x0041b054u, (re_fn_t)NoopFn0041b054 },
  { 0x0041b059u, (re_fn_t)Ui0041B059 },
  { 0x0041b1c0u, (re_fn_t)P139_LadderLoad },
  { 0x0041b3a6u, (re_fn_t)NoopFn0041b3a6 },
  { 0x0041b3abu, (re_fn_t)P140_LadderRun },
  { 0x0041b790u, (re_fn_t)FlagSet0127104C },
  { 0x0041b7adu, (re_fn_t)TestBit0041B7AD },
  { 0x0041b7d1u, (re_fn_t)P131_MenuPick },
  { 0x0041b8acu, (re_fn_t)P141_LadderLine },
  { 0x0041c7adu, (re_fn_t)P47_ReadLine },
  { 0x0041c7dau, (re_fn_t)P19_TakeToken },
  { 0x0041ce90u, (re_fn_t)P149_DDEnumAll },
  { 0x0041cedeu, (re_fn_t)P151_InstallD3D },
  { 0x0041d3edu, (re_fn_t)P39_GetSurfaceFormat },
  { 0x0041d50eu, (re_fn_t)Dispatch0041D50E },
  { 0x0041d53cu, (re_fn_t)P114_TexDownloadMip },
  { 0x0041d5e7u, (re_fn_t)P46_TexCall2 },
  { 0x0041d63bu, (re_fn_t)P53_TexLookup },
  { 0x0041d6aau, (re_fn_t)P149_EmulFreeAll },
  { 0x0041d819u, (re_fn_t)P55_FillDevInfo },
  { 0x0041d89cu, (re_fn_t)P46_TexCall },
  { 0x0041d8cdu, (re_fn_t)SetScale54EF38 },
  { 0x0041d8e9u, (re_fn_t)InitIdentityPalette_0041D8E9 },
  { 0x0041d94au, (re_fn_t)Ui0041D94A },
  { 0x0041d954u, (re_fn_t)FillTable8_0041D954 },
  { 0x0041d9afu, (re_fn_t)NoopFn0041d9af },
  { 0x0041d9b6u, (re_fn_t)NoopFn0041d9b6 },
  { 0x0041d9bdu, (re_fn_t)NoopFn0041d9bd },
  { 0x0041d9c4u, (re_fn_t)NoopFn0041d9c4 },
  { 0x0041d9cbu, (re_fn_t)NoopFn0041d9cb },
  { 0x0041d9d2u, (re_fn_t)P23_SetBlendMode },
  { 0x0041dd37u, (re_fn_t)P22_SetAlphaTest },
  { 0x0041ddbeu, (re_fn_t)NoopFn0041ddbe },
  { 0x0041ddc5u, (re_fn_t)P22_SetAlphaFunc },
  { 0x0041de1du, (re_fn_t)P22_SetAlphaRef },
  { 0x0041de46u, (re_fn_t)P54_ClearBuffers },
  { 0x0041dec1u, (re_fn_t)Ui0041DEC1 },
  { 0x0041dec8u, (re_fn_t)P39_Present },
  { 0x0041e037u, (re_fn_t)P22_BeginScene },
  { 0x0041e056u, (re_fn_t)P22_EndScene },
  { 0x0041e075u, (re_fn_t)NoopFn0041e075 },
  { 0x0041e07cu, (re_fn_t)NoopFn0041e07c },
  { 0x0041e083u, (re_fn_t)NoopFn0041e083 },
  { 0x0041e08au, (re_fn_t)P22_SetViewport },
  { 0x0041e14fu, (re_fn_t)P22_SetTexOp },
  { 0x0041e1e4u, (re_fn_t)SetFlagFromArg0041E1E4 },
  { 0x0041e207u, (re_fn_t)NoopFn0041e207 },
  { 0x0041e20eu, (re_fn_t)NoopFn0041e20e },
  { 0x0041e215u, (re_fn_t)P22_SetCull },
  { 0x0041e28au, (re_fn_t)P22_SetZFunc },
  { 0x0041e404u, (re_fn_t)P22_SetZWrite },
  { 0x0041e456u, (re_fn_t)NoopFn0041e456 },
  { 0x0041e45bu, (re_fn_t)NoopFn0041e45b },
  { 0x0041e462u, (re_fn_t)P23_DrawLineA },
  { 0x0041e4b9u, (re_fn_t)P23_DrawLineB },
  { 0x0041e510u, (re_fn_t)NoopFn0041e510 },
  { 0x0041e517u, (re_fn_t)NoopFn0041e517 },
  { 0x0041e51eu, (re_fn_t)NoopFn0041e51e },
  { 0x0041e525u, (re_fn_t)NoopFn0041e525 },
  { 0x0041e52cu, (re_fn_t)P98_QuadA },
  { 0x0041e729u, (re_fn_t)P98_QuadB },
  { 0x0041e926u, (re_fn_t)P76_TriA1 },
  { 0x0041ea2au, (re_fn_t)P76_TriB1 },
  { 0x0041eb2eu, (re_fn_t)NoopFn0041eb2e },
  { 0x0041eb35u, (re_fn_t)NoopFn0041eb35 },
  { 0x0041eb3cu, (re_fn_t)NoopFn0041eb3c },
  { 0x0041eb43u, (re_fn_t)NoopFn0041eb43 },
  { 0x0041eb4au, (re_fn_t)NoopFn0041eb4a },
  { 0x0041eb51u, (re_fn_t)P42_VersionString },
  { 0x0041eb69u, (re_fn_t)NoopFn0041eb69 },
  { 0x0041eb70u, (re_fn_t)NoopFn0041eb70 },
  { 0x0041eb77u, (re_fn_t)NoopFn0041eb77 },
  { 0x0041eb7eu, (re_fn_t)NoopFn0041eb7e },
  { 0x0041eb85u, (re_fn_t)NoopFn0041eb85 },
  { 0x0041eb8cu, (re_fn_t)P39_LockSurface },
  { 0x0041ec79u, (re_fn_t)Ui0041EC79 },
  { 0x0041ec82u, (re_fn_t)P39_UnlockSurface },
  { 0x0041ed00u, (re_fn_t)NoopFn0041ed00 },
  { 0x0041ed07u, (re_fn_t)NoopFn0041ed07 },
  { 0x0041ed0eu, (re_fn_t)Ui0041ED0E },
  { 0x0041ed1au, (re_fn_t)NoopFn0041ed1a },
  { 0x0041ed21u, (re_fn_t)NoopFn0041ed21 },
  { 0x0041ed26u, (re_fn_t)NoopFn0041ed26 },
  { 0x0041ed2du, (re_fn_t)Ui0041ED2D },
  { 0x0041ed39u, (re_fn_t)NoopFn0041ed39 },
  { 0x0041ed3eu, (re_fn_t)Ui0041ED3E },
  { 0x0041ed45u, (re_fn_t)NoopFn0041ed45 },
  { 0x0041ed4cu, (re_fn_t)NoopFn0041ed4c },
  { 0x0041ed53u, (re_fn_t)Ui0041ED53 },
  { 0x0041ed63u, (re_fn_t)NoopFn0041ed63 },
  { 0x0041ed68u, (re_fn_t)GetVarA421A8 },
  { 0x0041ed72u, (re_fn_t)GetVarA421A4 },
  { 0x0041ed7cu, (re_fn_t)NoopFn0041ed7c },
  { 0x0041ed83u, (re_fn_t)Ui0041ED83 },
  { 0x0041ed8au, (re_fn_t)Ui0041ED8A },
  { 0x0041ed91u, (re_fn_t)Ui0041ED91 },
  { 0x0041ed98u, (re_fn_t)P151_WinOpen },
  { 0x0041f2a0u, (re_fn_t)P31_ReleaseDirectDraw },
  { 0x0041f47cu, (re_fn_t)Ui0041F47C },
  { 0x0041f485u, (re_fn_t)NoopFn0041f485 },
  { 0x0041f48cu, (re_fn_t)NoopFn0041f48c },
  { 0x0041f493u, (re_fn_t)NoopFn0041f493 },
  { 0x0041f49au, (re_fn_t)NoopFn0041f49a },
  { 0x0041f4a1u, (re_fn_t)P112_TexDownload },
  { 0x0041f56fu, (re_fn_t)NoopFn0041f56f },
  { 0x0041f576u, (re_fn_t)NoopFn0041f576 },
  { 0x0041f57du, (re_fn_t)P32_SetPalette },
  { 0x0041f6a2u, (re_fn_t)NoopFn0041f6a2 },
  { 0x0041f6a9u, (re_fn_t)P22_SetTexFilter },
  { 0x0041f72du, (re_fn_t)NoopFn0041f72d },
  { 0x0041f734u, (re_fn_t)Ret1FFFF8IfZero },
  { 0x0041f74au, (re_fn_t)Ui0041F74A },
  { 0x0041f753u, (re_fn_t)NoopFn0041f753 },
  { 0x0041f75au, (re_fn_t)NoopFn0041f75a },
  { 0x0041f761u, (re_fn_t)NoopFn0041f761 },
  { 0x0041f768u, (re_fn_t)NoopFn0041f768 },
  { 0x0041f76fu, (re_fn_t)P53_SetTexSource },
  { 0x0041f7e7u, (re_fn_t)Ui0041F7E7 },
  { 0x0041f7f0u, (re_fn_t)NoopFn0041f7f0 },
  { 0x0041f7f7u, (re_fn_t)Ui0041F7F7 },
  { 0x0041f800u, (re_fn_t)Ui0041F800 },
  { 0x0041f809u, (re_fn_t)NoopFn0041f809 },
  { 0x0041f810u, (re_fn_t)NoopFn0041f810 },
  { 0x0041f817u, (re_fn_t)NoopFn0041f817 },
  { 0x0041f81eu, (re_fn_t)NoopFn0041F81E },
  { 0x0041f825u, (re_fn_t)P76_TriA2 },
  { 0x0041f929u, (re_fn_t)P76_TriB2 },
  { 0x0041fa2du, (re_fn_t)Ui0041FA2D },
  { 0x0041fa36u, (re_fn_t)RetZero0041FA36 },
  { 0x0041fa40u, (re_fn_t)Ui0041FA40 },
  { 0x0041fa49u, (re_fn_t)NoopFn0041FA49 },
  { 0x0041fa50u, (re_fn_t)NoopFn0041FA50 },
  { 0x0041fa57u, (re_fn_t)NoopFn0041FA57 },
  { 0x0041fa5eu, (re_fn_t)GetConst0041FA5E },
  { 0x0041fa6bu, (re_fn_t)Ui0041FA6B },
  { 0x0041fa74u, (re_fn_t)Ui0041FA74 },
  { 0x0041fa7du, (re_fn_t)NoopFn0041FA7D },
  { 0x0041fa84u, (re_fn_t)Ui0041FA84 },
  { 0x0041fa8bu, (re_fn_t)NoopFn0041FA8B },
  { 0x0041fa92u, (re_fn_t)NoopFn0041FA92 },
  { 0x0041fa99u, (re_fn_t)Ui0041FA99 },
  { 0x0041faa2u, (re_fn_t)Ui0041FAA2 },
  { 0x0041faabu, (re_fn_t)Ui0041FAAB },
  { 0x0041fab4u, (re_fn_t)NoopFn0041fab4 },
  { 0x0041fab9u, (re_fn_t)NoopFn0041FAB9 },
  { 0x0041fac0u, (re_fn_t)P149_DDEnumCb },
  { 0x0041fcc7u, (re_fn_t)P149_D3DDevCb },
  { 0x0041fe07u, (re_fn_t)P149_BuildDevs },
  { 0x00420038u, (re_fn_t)P151_CheckDev },
  { 0x00420854u, (re_fn_t)P99_DDEnumFmt },
  { 0x00420a21u, (re_fn_t)P106_CanDevTex },
  { 0x00420b19u, (re_fn_t)P35_GetDirectDrawInterface },
  { 0x00420c10u, (re_fn_t)P24_CreateSurface },
  { 0x00420c5au, (re_fn_t)P39_QueryDD4 },
  { 0x00420cacu, (re_fn_t)P39_QueryD3D },
  { 0x00420cfeu, (re_fn_t)P24_CreateDevice },
  { 0x00420d5du, (re_fn_t)P24_CreateViewport },
  { 0x00420dadu, (re_fn_t)P24_AddViewport },
  { 0x00420e93u, (re_fn_t)P23_ClearZ },
  { 0x00420ef6u, (re_fn_t)P24_FillBackbuffer },
  { 0x0042101bu, (re_fn_t)P24_SetDisplayMode },
  { 0x0042106du, (re_fn_t)P24_CreatePrimarySurface },
  { 0x00421149u, (re_fn_t)P39_CreateFrontBack },
  { 0x00421250u, (re_fn_t)P24_CreateClipper },
  { 0x00421298u, (re_fn_t)P24_SetClipper },
  { 0x004212dcu, (re_fn_t)P24_RestoreSurfaces },
  { 0x004213a4u, (re_fn_t)P24_RestoreDisplay },
  { 0x004213dcu, (re_fn_t)P32_CreateZSurface },
  { 0x004214ddu, (re_fn_t)P24_AttachSurface },
  { 0x00421521u, (re_fn_t)P23_InitRenderStates },
  { 0x00421719u, (re_fn_t)P109_SlotUpload8 },
  { 0x00421861u, (re_fn_t)P109_SlotUpload16 },
  { 0x004219e8u, (re_fn_t)P109_EmulInit },
  { 0x00421a39u, (re_fn_t)P57_ResetTexNodes },
  { 0x00421a80u, (re_fn_t)P98_PixTabInit },
  { 0x00421c1du, (re_fn_t)MaskShift_00421C1D },
  { 0x00421c72u, (re_fn_t)CountTrailingZeros00421C72 },
  { 0x00421cabu, (re_fn_t)SetZoom_00421CAB },
  { 0x00421cfeu, (re_fn_t)P23_ConvVertexA },
  { 0x00421db8u, (re_fn_t)P23_ConvVertexB },
  { 0x00421e6cu, (re_fn_t)P108_EmulTex8 },
  { 0x0042200cu, (re_fn_t)P54_GetTexture2 },
  { 0x0042205eu, (re_fn_t)P108_EmulTex16 },
  { 0x004221bfu, (re_fn_t)P107_TexRelease },
  { 0x00422309u, (re_fn_t)P32_CreateSlotPalette },
  { 0x0042243fu, (re_fn_t)NoopFn0042243f },
  { 0x00422444u, (re_fn_t)P46_FindTexNode },
  { 0x0042248bu, (re_fn_t)P149_EmulAddSub },
  { 0x004225ebu, (re_fn_t)P149_EmulNew },
  { 0x00422736u, (re_fn_t)P105_EmulSurface },
  { 0x0042282fu, (re_fn_t)P106_EmulUpload8 },
  { 0x004228ebu, (re_fn_t)P106_EmulUpload16 },
  { 0x004229fau, (re_fn_t)P74_Conv8to16 },
  { 0x00422ac0u, (re_fn_t)P13_Fn00422AC0 },
  { 0x00422ae7u, (re_fn_t)P33_FlushBatches },
  { 0x00422c55u, (re_fn_t)P32_SelectSlotPalette },
  { 0x00424530u, (re_fn_t)P74_DevSelect },
  { 0x004245e2u, (re_fn_t)GetVarB1C0D8 },
  { 0x004245ecu, (re_fn_t)P42_GetDeviceName },
  { 0x00424633u, (re_fn_t)Dev00424633 },
  { 0x00424647u, (re_fn_t)Dev00424647 },
  { 0x00424661u, (re_fn_t)GameCall00424661 },
  { 0x0042467fu, (re_fn_t)P47_GlideWinOpen },
  { 0x004246bdu, (re_fn_t)Dev004246BD },
  { 0x004246d1u, (re_fn_t)DrvCall004246D1 },
  { 0x004246f0u, (re_fn_t)P69_FreeDevices },
  { 0x0042476cu, (re_fn_t)P68_LfbLock },
  { 0x0042480du, (re_fn_t)Dev0042480D },
  { 0x0042482bu, (re_fn_t)Fwd0042482B },
  { 0x00424858u, (re_fn_t)Dev00424858 },
  { 0x0042486bu, (re_fn_t)P52_TexDownloadMipMap },
  { 0x004248c6u, (re_fn_t)P54_TexSource },
  { 0x00424921u, (re_fn_t)P47_TexTable },
  { 0x00424974u, (re_fn_t)P55_GlideDevInfo },
  { 0x00424a02u, (re_fn_t)CallIf424A02 },
  { 0x00424b70u, (re_fn_t)P76_GlideRegister },
  { 0x00424c40u, (re_fn_t)P33_LoadGlideProcs },
  { 0x0042570cu, (re_fn_t)P42_FreeGlide },
  { 0x00425730u, (re_fn_t)P31_LoadGlide },
  { 0x00425a50u, (re_fn_t)P62_InitRenderConsts },
  { 0x00425b12u, (re_fn_t)P110_ViewSetup },
  { 0x00425e9eu, (re_fn_t)Zoom_00425E9E },
  { 0x00425ee0u, (re_fn_t)P12_Fn00425EE0 },
  { 0x00425f52u, (re_fn_t)P48_GlideCheck },
  { 0x00425f7bu, (re_fn_t)P151_Reopen },
  { 0x0042626eu, (re_fn_t)P52_GlideFogSetup },
  { 0x004262ceu, (re_fn_t)P107_Line },
  { 0x004264a7u, (re_fn_t)Ui004264A7 },
  { 0x004264bdu, (re_fn_t)P52_GlideFogMode },
  { 0x0042651au, (re_fn_t)P47_GlideSwap },
  { 0x0042655au, (re_fn_t)DrvSetMode0042655A },
  { 0x00426580u, (re_fn_t)P12_Fn00426580 },
  { 0x004268e0u, (re_fn_t)Ui004268E0 },
  { 0x004268efu, (re_fn_t)P82_AddLight },
  { 0x00426abcu, (re_fn_t)AddEntry_00426ABC },
  { 0x00426b34u, (re_fn_t)P63_SphereHits },
  { 0x00426c06u, (re_fn_t)P56_AllocEulerTab },
  { 0x00426cafu, (re_fn_t)Ui00426CAF },
  { 0x00426cc6u, (re_fn_t)Ui00426CC6 },
  { 0x00426ce3u, (re_fn_t)P80_Bounds },
  { 0x0042754au, (re_fn_t)P79_ModelList },
  { 0x004275aeu, (re_fn_t)P79_Unrelocate },
  { 0x00427757u, (re_fn_t)P79_Relocate },
  { 0x0042793fu, (re_fn_t)P79_Radius },
  { 0x00427a08u, (re_fn_t)P15_ScaleVertices },
  { 0x00427a71u, (re_fn_t)P15_ScaleNormalW },
  { 0x00427abeu, (re_fn_t)P82_FrustumSetup2D },
  { 0x00427d5au, (re_fn_t)P82_SphereVis2D },
  { 0x00427eeau, (re_fn_t)P82_FrustumSetup3D },
  { 0x004282f8u, (re_fn_t)P77_CameraPlane },
  { 0x004283d9u, (re_fn_t)P82_SphereVis3D },
  { 0x00428672u, (re_fn_t)P83_BoxVis },
  { 0x00428928u, (re_fn_t)P83_LightMatrices },
  { 0x00428b69u, (re_fn_t)P84_DrawModel },
  { 0x00429143u, (re_fn_t)P84_DrawModelIdx },
  { 0x0042982eu, (re_fn_t)P92_DrawAxis },
  { 0x0042a423u, (re_fn_t)P90_DrawSingle },
  { 0x0042a5deu, (re_fn_t)P92_DrawSpin },
  { 0x0042a9f1u, (re_fn_t)P84_DrawCar },
  { 0x0042b7cbu, (re_fn_t)P84_DrawModelC },
  { 0x0042d2b0u, (re_fn_t)Reset0042D2B0 },
  { 0x0042d2c9u, (re_fn_t)P62_QueueTri },
  { 0x0042d384u, (re_fn_t)P150_FlushTris },
  { 0x0042d554u, (re_fn_t)P125_ClipNearXY },
  { 0x0042d797u, (re_fn_t)P100_ClipNear },
  { 0x0042da16u, (re_fn_t)P101_ClipNearUV },
  { 0x0042dce8u, (re_fn_t)P101_ClipNearUVW },
  { 0x0042e007u, (re_fn_t)P101_ClipNear5A },
  { 0x0042e3c7u, (re_fn_t)P101_ClipNearRGB },
  { 0x0042e6e6u, (re_fn_t)P101_ClipNear5B },
  { 0x0042eaa6u, (re_fn_t)P102_ClipNear7 },
  { 0x0042eee6u, (re_fn_t)P100_ClipFar },
  { 0x0042f124u, (re_fn_t)P101_ClipFarUV },
  { 0x0042f3f7u, (re_fn_t)P102_ClipFar5 },
  { 0x0042f7b8u, (re_fn_t)AdvanceOpPtr0042F7B8 },
  { 0x0042f7d9u, (re_fn_t)P85_FlatTri },
  { 0x0042fc29u, (re_fn_t)P85_FlatQuad },
  { 0x00430b13u, (re_fn_t)P121_TexTriFlat },
  { 0x00431016u, (re_fn_t)P121_TexQuadFlat },
  { 0x00432186u, (re_fn_t)P85_LitTri },
  { 0x00432601u, (re_fn_t)P85_LitQuad },
  { 0x00432b77u, (re_fn_t)P86_GouraudTri },
  { 0x00433017u, (re_fn_t)P86_GouraudQuad },
  { 0x004335e6u, (re_fn_t)P86_TexTri },
  { 0x00433f4cu, (re_fn_t)P86_TexQuad },
  { 0x00434c58u, (re_fn_t)P86_TexTriD },
  { 0x0043593eu, (re_fn_t)P86_TexQuadD },
  { 0x00439b42u, (re_fn_t)P121_ClipTexTri },
  { 0x0043a5beu, (re_fn_t)P121_ClipTexQuad },
  { 0x00447753u, (re_fn_t)P121_ClipQuad },
  { 0x00452327u, (re_fn_t)P115_FlatTriC },
  { 0x004527acu, (re_fn_t)P115_FlatQuadC },
  { 0x00452d3eu, (re_fn_t)P115_GouraudTriC },
  { 0x004531c5u, (re_fn_t)P115_GouraudQuadC },
  { 0x0047560bu, (re_fn_t)P79_VertClass },
  { 0x004757d2u, (re_fn_t)P79_MarkRecords },
  { 0x00475906u, (re_fn_t)P79_FindSameVerts },
  { 0x00475a3du, (re_fn_t)P79_Convert },
  { 0x00489d20u, (re_fn_t)P40_ResetTexMem },
  { 0x00489ed6u, (re_fn_t)P12_Fn00489ED6 },
  { 0x00489f50u, (re_fn_t)P40_UploadSlotPair },
  { 0x0048a239u, (re_fn_t)P40_UploadSlot },
  { 0x0048a46bu, (re_fn_t)P12_Fn0048A46B },
  { 0x0048a4e1u, (re_fn_t)NoopFn0048a4e1 },
  { 0x0048a4e6u, (re_fn_t)FindFreeEven_0048A4E6 },
  { 0x0048a525u, (re_fn_t)P76_MarkSlots },
  { 0x0048a627u, (re_fn_t)P12_Fn0048A627 },
  { 0x0048a68eu, (re_fn_t)Dispatch0048A68E },
  { 0x0048a940u, (re_fn_t)P150_PlayFmv },
  { 0x0048abdcu, (re_fn_t)P52_FmvStart },
  { 0x0048ac0du, (re_fn_t)P50_FmvStopRelease },
  { 0x0048ac1cu, (re_fn_t)P150_FmvDDInit },
  { 0x0048ae12u, (re_fn_t)P38_FmvRelease },
  { 0x0048af23u, (re_fn_t)P150_OpenVideo },
  { 0x0048b242u, (re_fn_t)P50_FmvReleaseAll },
  { 0x0048b2fdu, (re_fn_t)P38_MmsRun },
  { 0x0048b32bu, (re_fn_t)P38_MmsStop },
  { 0x0048b34cu, (re_fn_t)P38_UpdateFrame },
  { 0x0048b3e8u, (re_fn_t)P150_OpenAudio },
  { 0x0048b568u, (re_fn_t)P50_FmvReleaseObjs },
  { 0x0048b5e3u, (re_fn_t)P108_FmvStart },
  { 0x0048b65du, (re_fn_t)P38_FmvStop },
  { 0x0048b6a9u, (re_fn_t)Set551134 },
  { 0x0048ba20u, (re_fn_t)P148_SndEnum },
  { 0x0048ba31u, (re_fn_t)P148_SndOpen },
  { 0x0048bbd5u, (re_fn_t)P97_SndDrvInit },
  { 0x0048bcc0u, (re_fn_t)P50_SoundShutdown },
  { 0x0048bd3bu, (re_fn_t)NoopFn0048bd3b },
  { 0x0048bd40u, (re_fn_t)P49_Commit },
  { 0x0048bd65u, (re_fn_t)P26_WaveSetVolume },
  { 0x0048bdccu, (re_fn_t)P38_SetPrimaryFormat },
  { 0x0048be68u, (re_fn_t)P38_SetSpeakerConfig },
  { 0x0048bf52u, (re_fn_t)P106_EaxPreset },
  { 0x0048bf9au, (re_fn_t)P140_SndLoadWav },
  { 0x0048c192u, (re_fn_t)P148_BufFromWav },
  { 0x0048c2a3u, (re_fn_t)P148_DupVoice },
  { 0x0048c3e7u, (re_fn_t)P148_Refill },
  { 0x0048c43cu, (re_fn_t)P100_RiffFromRes },
  { 0x0048c47eu, (re_fn_t)P148_Fill },
  { 0x0048c520u, (re_fn_t)P50_ReleaseVoice },
  { 0x0048c5b7u, (re_fn_t)P98_RiffFind },
  { 0x0048c74bu, (re_fn_t)P49_ListenerPos },
  { 0x0048c77eu, (re_fn_t)P49_ListenerOrient },
  { 0x0048c7bdu, (re_fn_t)P49_ListenerVel },
  { 0x0048c7f0u, (re_fn_t)P49_Play },
  { 0x0048c83du, (re_fn_t)P50_ReleaseBuf },
  { 0x0048c8d6u, (re_fn_t)P50_ResetBuf },
  { 0x0048c97cu, (re_fn_t)P49_SetVolume },
  { 0x0048c9b2u, (re_fn_t)P49_SetFreq },
  { 0x0048c9e8u, (re_fn_t)P49_SetPos3D },
  { 0x0048ca28u, (re_fn_t)P49_SetVel3D },
  { 0x0048ca68u, (re_fn_t)P49_SetMode3D },
  { 0x0048caa0u, (re_fn_t)P49_GetStatus },
  { 0x0048cad6u, (re_fn_t)P148_KsProps },
  { 0x0048cba4u, (re_fn_t)P50_EaxSetDefault },
  { 0x0048cbd3u, (re_fn_t)P50_EaxEnable },
  { 0x0048cc5fu, (re_fn_t)P50_Nop },
  { 0x0048cc64u, (re_fn_t)P50_CreateKsProps },
  { 0x0048ccafu, (re_fn_t)P49_ReleaseProps },
  { 0x0048ccddu, (re_fn_t)P50_CreateDummyBuf },
  { 0x0048cd82u, (re_fn_t)P49_ReleaseProp2C },
  { 0x0048cdabu, (re_fn_t)P148_EnumCb },
  { 0x0048d4e0u, (re_fn_t)P115_RoadArrow },
  { 0x0048db65u, (re_fn_t)P14_Fn0048DB65 },
  { 0x0048db8eu, (re_fn_t)P96_InitRotTab },
  { 0x0048dddbu, (re_fn_t)P118_TrafficBlocked },
  { 0x0048ea2cu, (re_fn_t)P63_NearOnNode },
  { 0x0048eb25u, (re_fn_t)P51_TrafficConflict },
  { 0x0048ebc8u, (re_fn_t)P12_Fn0048EBC8 },
  { 0x0048ec34u, (re_fn_t)Ret1 },
  { 0x0048eca3u, (re_fn_t)P59_TrafficFind },
  { 0x0048ed6fu, (re_fn_t)P59_TrafficCheck },
  { 0x0048edffu, (re_fn_t)P103_TrafficCanGo },
  { 0x0048f1c6u, (re_fn_t)P63_CanEnter },
  { 0x0048f2e7u, (re_fn_t)CountByOwner_0048F2E7 },
  { 0x0048f34cu, (re_fn_t)GetRect_0048F34C },
  { 0x0048f3b4u, (re_fn_t)P63_CountByNode },
  { 0x0048f4adu, (re_fn_t)P63_NearestAdd },
  { 0x0048f5d8u, (re_fn_t)P63_NearestRec },
  { 0x0048f6c1u, (re_fn_t)P95_CountNear },
  { 0x0048f7feu, (re_fn_t)P51_NodeKind },
  { 0x0048f899u, (re_fn_t)P102_CarsCollide },
  { 0x0048fbbau, (re_fn_t)ClearFlagByte0048FBBA },
  { 0x0048fbcfu, (re_fn_t)P119_TrafficSpeed },
  { 0x004901c0u, (re_fn_t)P63_CarSpeed },
  { 0x004902a8u, (re_fn_t)P102_ScanCells },
  { 0x00490591u, (re_fn_t)P94_BuildDirTab },
  { 0x004906f9u, (re_fn_t)P126_PlayerStart },
  { 0x00490bcbu, (re_fn_t)P128_TrafficDraw },
  { 0x00490f3au, (re_fn_t)P107_TrafficLights },
  { 0x004911d9u, (re_fn_t)P98_TrafficSpin },
  { 0x00491360u, (re_fn_t)P12_Fn00491360 },
  { 0x004913ccu, (re_fn_t)P75_TrafficPos },
  { 0x00491650u, (re_fn_t)P59_CellLeft },
  { 0x00491928u, (re_fn_t)P51_InitCarSlot },
  { 0x0049199au, (re_fn_t)P62_SpawnTrafficCar },
  { 0x00491a56u, (re_fn_t)P119_TrafficSpawn },
  { 0x00492398u, (re_fn_t)P62_FarFromPlayer },
  { 0x0049245au, (re_fn_t)P56_CarPosCheck },
  { 0x00492508u, (re_fn_t)AllocSlot00492508 },
  { 0x00492530u, (re_fn_t)P103_TrafficSpawn },
  { 0x004928c9u, (re_fn_t)P119_TrafficParked },
  { 0x00492b98u, (re_fn_t)P102_TrafficAdd },
  { 0x00492e42u, (re_fn_t)P75_TrafficSpawn },
  { 0x00492f7du, (re_fn_t)P103_TrafficReset },
  { 0x004932d5u, (re_fn_t)P118_TrafficTurn },
  { 0x00493b51u, (re_fn_t)P102_TrafficAlign },
  { 0x00493e3du, (re_fn_t)P54_ObjInit },
  { 0x00493e9bu, (re_fn_t)PopIndex00493E9B },
  { 0x00493eceu, (re_fn_t)P74_FreeTraffic },
  { 0x00493f95u, (re_fn_t)NoopFn00493f95 },
  { 0x00493f9au, (re_fn_t)P54_ObjTick },
  { 0x00493ff7u, (re_fn_t)P103_TrafficTick },
  { 0x0049431du, (re_fn_t)P62_HeadingDelta },
  { 0x004943dcu, (re_fn_t)P119_TrafficStep },
  { 0x00494620u, (re_fn_t)P134_TrafficHold },
  { 0x00494678u, (re_fn_t)ActorStep00494678 },
  { 0x004946d0u, (re_fn_t)NoopFn004946d0 },
  { 0x004946d5u, (re_fn_t)NoopFn004946d5 },
  { 0x004946dau, (re_fn_t)InitFlags004946DA },
  { 0x00494701u, (re_fn_t)P100_TrafficSlot },
  { 0x004949f0u, (re_fn_t)P128_TrafficNode },
  { 0x00494e01u, (re_fn_t)P127_TrafficLane },
  { 0x0049509au, (re_fn_t)P21_CountActiveEntries },
  { 0x0049512bu, (re_fn_t)P75_TrafficFill },
  { 0x0049521eu, (re_fn_t)P102_TrafficAhead },
  { 0x0049565bu, (re_fn_t)P104_TrafficTurn },
  { 0x00495886u, (re_fn_t)P47_NoFlags },
  { 0x004958b7u, (re_fn_t)P107_TrafficRow },
  { 0x00496372u, (re_fn_t)P102_TrafficRoom },
  { 0x004964c7u, (re_fn_t)Dec145934 },
  { 0x004964e2u, (re_fn_t)GlobalSet004964E2 },
  { 0x00496505u, (re_fn_t)P12_Fn00496505 },
  { 0x00496569u, (re_fn_t)P94_InViewCone },
  { 0x004966fdu, (re_fn_t)P63_InPlanes },
  { 0x004967d2u, (re_fn_t)P133_TrafficTick },
  { 0x00496eb4u, (re_fn_t)P99_JunctionBlock },
  { 0x004997a0u, (re_fn_t)P101_BoxHit },
  { 0x00499951u, (re_fn_t)P100_BoxFace },
  { 0x00499bb2u, (re_fn_t)P102_CarsHit },
  { 0x00499fb0u, (re_fn_t)P100_BoxOverlap },
  { 0x0049a21du, (re_fn_t)P102_BoxContact },
  { 0x0049a520u, (re_fn_t)P103_BoxContactTime },
  { 0x0049aa14u, (re_fn_t)P103_CarDamage },
  { 0x0049ae98u, (re_fn_t)P100_CarHit },
  { 0x0049b14du, (re_fn_t)P129_ObjHit },
  { 0x0049c850u, (re_fn_t)P62_InitCamDefaults },
  { 0x0049c910u, (re_fn_t)P59_SetupCamera },
  { 0x0049c99cu, (re_fn_t)P99_FreeCamMove },
  { 0x0049cad4u, (re_fn_t)P134_CamCollide },
  { 0x0049d84au, (re_fn_t)P134_CamChase },
  { 0x0049dc73u, (re_fn_t)P128_FreeCam },
  { 0x0049df91u, (re_fn_t)P123_CamAtCar },
  { 0x0049e16cu, (re_fn_t)P134_CamTarget },
  { 0x0049e47bu, (re_fn_t)P99_CamBehind },
  { 0x0049e5e7u, (re_fn_t)P61_SetupCamN },
  { 0x0049e7a8u, (re_fn_t)P131_CamShake },
  { 0x0049e911u, (re_fn_t)P131_FlybyStart },
  { 0x0049ea37u, (re_fn_t)P99_CamScriptStep },
  { 0x0049ec01u, (re_fn_t)P98_CamSpline },
  { 0x0049ed20u, (re_fn_t)P63_Hermite },
  { 0x0049ee5du, (re_fn_t)P56_Spline },
  { 0x0049ef12u, (re_fn_t)P63_CatmullRom },
  { 0x0049f031u, (re_fn_t)P73_CatmullRom },
  { 0x0049f180u, (re_fn_t)P56_QuatRot },
  { 0x0049f20au, (re_fn_t)P132_LoadFlyby },
  { 0x0049f418u, (re_fn_t)P95_CamFromQuat },
  { 0x0049f474u, (re_fn_t)P114_CamFadeFrame },
  { 0x0049f6c7u, (re_fn_t)P133_CamUpdate },
  { 0x004a05c0u, (re_fn_t)StartFlyby004A05C0 },
  { 0x004a05fau, (re_fn_t)P122_ObjNames },
  { 0x004a0ccau, (re_fn_t)P69_Bracket },
  { 0x004a0d5fu, (re_fn_t)P69_AddScore },
  { 0x004a1010u, (re_fn_t)CopySlotTemplate004A1010 },
  { 0x004a1037u, (re_fn_t)P137_DrawCar },
  { 0x004a1b2du, (re_fn_t)P99_TrafficAhead },
  { 0x004a1d31u, (re_fn_t)Get138Entry148 },
  { 0x004a1d4cu, (re_fn_t)P136_DrawWheels },
  { 0x004a2b70u, (re_fn_t)ResetSlots_004A2B70 },
  { 0x004a2bf4u, (re_fn_t)ResetEffectsState },
  { 0x004a2c08u, (re_fn_t)Call004A2C08 },
  { 0x004a2c12u, (re_fn_t)PoolAlloc004A2C12 },
  { 0x004a2c5bu, (re_fn_t)ReleaseSlot4A2C5B },
  { 0x004a2c98u, (re_fn_t)P96_DropFarChairs },
  { 0x004a2db5u, (re_fn_t)FindSlot_004A2DB5 },
  { 0x004a2e14u, (re_fn_t)P99_ChairHit },
  { 0x004a2f77u, (re_fn_t)P78_LoadChairs },
  { 0x004a31fcu, (re_fn_t)P78_ChairAdd },
  { 0x004a32e9u, (re_fn_t)P96_PickChair },
  { 0x004a3354u, (re_fn_t)P58_FreeGrid },
  { 0x004a3630u, (re_fn_t)P69_SetupMsgs },
  { 0x004a37d9u, (re_fn_t)P146_MsgPos },
  { 0x004a3808u, (re_fn_t)P115_TargetTick },
  { 0x004a399au, (re_fn_t)P60_ObjUpdate },
  { 0x004a39f6u, (re_fn_t)P14_Fn004A39F6 },
  { 0x004a3a80u, (re_fn_t)WrapCounter004A3A80 },
  { 0x004a3aa7u, (re_fn_t)P76_FlashStep },
  { 0x004a3b80u, (re_fn_t)P14_Fn004A3B80 },
  { 0x004a3d40u, (re_fn_t)P136_CompileEvents },
  { 0x004a3f06u, (re_fn_t)P59_ModelNames },
  { 0x004a3fa6u, (re_fn_t)P123_EventsChunk },
  { 0x004a4340u, (re_fn_t)P99_EventAdd },
  { 0x004a44d4u, (re_fn_t)P122_EventsParse },
  { 0x004a45ebu, (re_fn_t)P123_EvLine },
  { 0x004a4a5fu, (re_fn_t)P121_ParseCamLine },
  { 0x004a4d84u, (re_fn_t)P120_ParseCamInt },
  { 0x004a4f7du, (re_fn_t)P74_ParseFloat },
  { 0x004a50a2u, (re_fn_t)P15_SkipInteger },
  { 0x004a50f7u, (re_fn_t)P51_SkipNumber },
  { 0x004a519au, (re_fn_t)P21_MatchPrefix },
  { 0x004a522au, (re_fn_t)P94_ReadIdent },
  { 0x004a5338u, (re_fn_t)P99_CmdAppend },
  { 0x004a5505u, (re_fn_t)P68_ReadCamArgs },
  { 0x004a5634u, (re_fn_t)P125_ModelName },
  { 0x004a58adu, (re_fn_t)P62_ModelLookup },
  { 0x004a596bu, (re_fn_t)SkipToIdentStart_004A596B },
  { 0x004a59c6u, (re_fn_t)SkipLine004A59C6 },
  { 0x004a59f2u, (re_fn_t)P51_PrefixMatch },
  { 0x004a5a83u, (re_fn_t)P51_SkipToLine },
  { 0x004a5ac3u, (re_fn_t)P26_ErrorInLine },
  { 0x004a5afbu, (re_fn_t)P74_ParseShorts },
  { 0x004a6370u, (re_fn_t)FillThresholds_004A6370 },
  { 0x004a63c6u, (re_fn_t)P51_DirFromHeading },
  { 0x004a6403u, (re_fn_t)P102_CopsTick },
  { 0x004a66d8u, (re_fn_t)IsVar112B284Lt8 },
  { 0x004a66efu, (re_fn_t)P91_ReleaseTraffic },
  { 0x004a6749u, (re_fn_t)P62_FindFreeTrafficSlot },
  { 0x004a67b0u, (re_fn_t)P68_SpawnCar },
  { 0x004a681au, (re_fn_t)P97_ResetCars },
  { 0x004a6a57u, (re_fn_t)P103_CopMeet },
  { 0x004a6dcdu, (re_fn_t)P59_NearCars },
  { 0x004a6e84u, (re_fn_t)P99_CopTarget },
  { 0x004a706au, (re_fn_t)P128_CopMapPos },
  { 0x004a742au, (re_fn_t)P128_CopReplan },
  { 0x004a77b0u, (re_fn_t)P112_ChaseTick },
  { 0x004a7920u, (re_fn_t)P99_PathAhead },
  { 0x004a7aa7u, (re_fn_t)P102_CopPathPoint },
  { 0x004a7d80u, (re_fn_t)P121_CopSync },
  { 0x004a7e6eu, (re_fn_t)P14_Fn004A7E6E },
  { 0x004a7ee9u, (re_fn_t)SetVarD1193C },
  { 0x004a7f0eu, (re_fn_t)P74_Dist },
  { 0x004a7fecu, (re_fn_t)P142_CopDrive },
  { 0x004a9850u, (re_fn_t)P98_CreditsInit },
  { 0x004a994au, (re_fn_t)Inc0B1FFBC },
  { 0x004a995cu, (re_fn_t)P114_CreditsDraw },
  { 0x004a9b1au, (re_fn_t)P58_DrawLogo },
  { 0x004a9bb0u, (re_fn_t)P112_FaceIcon },
  { 0x004a9cd0u, (re_fn_t)P98_CreditsFace },
  { 0x004a9ddcu, (re_fn_t)DrawFrame_004A9DDC },
  { 0x004a9e0au, (re_fn_t)P52_DrawLabel },
  { 0x004a9e88u, (re_fn_t)P67_Logo },
  { 0x004a9f45u, (re_fn_t)P107_Rect },
  { 0x004aa217u, (re_fn_t)P107_RectGrad },
  { 0x004aa4eau, (re_fn_t)P110_IconRect },
  { 0x004aad60u, (re_fn_t)NoopFn004aad60 },
  { 0x004aad65u, (re_fn_t)P52_ResetSlots },
  { 0x004aaddfu, (re_fn_t)GlobalSet004AADDF },
  { 0x004aae34u, (re_fn_t)P12_Fn004AAE34 },
  { 0x004aaea6u, (re_fn_t)P69_SceneFrame },
  { 0x004aaf3au, (re_fn_t)P139_Effects },
  { 0x004ab0dfu, (re_fn_t)InitSlotsTable_004AB0DF },
  { 0x004ab127u, (re_fn_t)P104_DebrisTabs },
  { 0x004ab500u, (re_fn_t)P100_DebrisInit },
  { 0x004ab712u, (re_fn_t)ResetSlots_004AB712 },
  { 0x004ab780u, (re_fn_t)ClearTables_004AB780 },
  { 0x004ab7fau, (re_fn_t)Clear110E180 },
  { 0x004ab808u, (re_fn_t)P95_PoolIconInit },
  { 0x004ab95cu, (re_fn_t)P94_IconQuad },
  { 0x004aba7cu, (re_fn_t)P102_SixInit },
  { 0x004abd69u, (re_fn_t)P111_IconsInit },
  { 0x004ac671u, (re_fn_t)PoolNext004AC671 },
  { 0x004ac6acu, (re_fn_t)PoolPush004AC6AC },
  { 0x004ac6d0u, (re_fn_t)PoolPop004AC6D0 },
  { 0x004ac702u, (re_fn_t)PoolPush004AC702 },
  { 0x004ac726u, (re_fn_t)PoolPop004AC726 },
  { 0x004ac755u, (re_fn_t)PoolPush004AC755 },
  { 0x004ac779u, (re_fn_t)P122_CarGlow },
  { 0x004accf0u, (re_fn_t)P122_SpotShadow },
  { 0x004ad128u, (re_fn_t)P97_KickDebris },
  { 0x004ad244u, (re_fn_t)P126_KerbDebris },
  { 0x004ad3b5u, (re_fn_t)P127_FarDebris },
  { 0x004ad5d2u, (re_fn_t)P96_AddObjB },
  { 0x004ad6f5u, (re_fn_t)P120_CarDebris },
  { 0x004ad837u, (re_fn_t)P106_CarBrakeLights },
  { 0x004adfccu, (re_fn_t)P106_CarTailLights },
  { 0x004ae6fbu, (re_fn_t)P106_CarHeadSpots },
  { 0x004aecb1u, (re_fn_t)P101_CarSkids },
  { 0x004aef57u, (re_fn_t)P102_CarLights },
  { 0x004af076u, (re_fn_t)P101_CarLight },
  { 0x004af2f8u, (re_fn_t)NoopFn004af2f8 },
  { 0x004af2fdu, (re_fn_t)P102_ObjMark },
  { 0x004af619u, (re_fn_t)P102_CarTracks },
  { 0x004af93cu, (re_fn_t)P120_ObjBShade },
  { 0x004afa4cu, (re_fn_t)P125_DebrisBurst },
  { 0x004afcf7u, (re_fn_t)P97_SpawnSmoke },
  { 0x004afe3cu, (re_fn_t)P120_CarSmoke },
  { 0x004aff92u, (re_fn_t)P119_CarDust },
  { 0x004b00adu, (re_fn_t)P120_CarSparks },
  { 0x004b0256u, (re_fn_t)P101_AddObjB },
  { 0x004b04c0u, (re_fn_t)P96_SpawnDust },
  { 0x004b05eau, (re_fn_t)P111_DebrisIcon },
  { 0x004b10ceu, (re_fn_t)P135_SmokeObj },
  { 0x004b1993u, (re_fn_t)P108_SmokeA },
  { 0x004b1ea0u, (re_fn_t)P108_SmokeB },
  { 0x004b23f8u, (re_fn_t)P135_SparkQuad },
  { 0x004b2c4bu, (re_fn_t)P121_DustDraw },
  { 0x004b33d8u, (re_fn_t)P135_DebrisTri },
  { 0x004b3ddbu, (re_fn_t)P69_ReleaseOverlays },
  { 0x004b3e55u, (re_fn_t)P114_DebrisAll },
  { 0x004b3fb1u, (re_fn_t)P123_CarGlows },
  { 0x004b4095u, (re_fn_t)P98_IconFlush },
  { 0x004b418du, (re_fn_t)P143_SunFlare },
  { 0x004b4b27u, (re_fn_t)P108_Sprite },
  { 0x004b5049u, (re_fn_t)P107_CarLight },
  { 0x004b53deu, (re_fn_t)P110_GlowA },
  { 0x004b588eu, (re_fn_t)P144_FlagFx },
  { 0x004b6debu, (re_fn_t)P111_Flare },
  { 0x004b73f3u, (re_fn_t)P143_LampGlow },
  { 0x004b82b2u, (re_fn_t)P110_GlowC },
  { 0x004b8871u, (re_fn_t)P110_GlowB },
  { 0x004b8d49u, (re_fn_t)P125_SmokePuffs },
  { 0x004b8f4eu, (re_fn_t)P118_SkidFx },
  { 0x004b9287u, (re_fn_t)P132_Smoke },
  { 0x004b9464u, (re_fn_t)P96_SpawnSpark },
  { 0x004b955cu, (re_fn_t)P125_ObjABurst },
  { 0x004b9835u, (re_fn_t)P94_Wobble },
  { 0x004b9933u, (re_fn_t)P12_Fn004B9933 },
  { 0x004b998bu, (re_fn_t)P101_DebrisBounce },
  { 0x004b9aecu, (re_fn_t)P101_DebrisFly },
  { 0x004b9d79u, (re_fn_t)P16_StepParticles },
  { 0x004b9e2bu, (re_fn_t)StepSpeedA_004B9E2B },
  { 0x004b9e54u, (re_fn_t)StepSpeedB_004B9E54 },
  { 0x004b9e9fu, (re_fn_t)P123_ObjAFall },
  { 0x004ba093u, (re_fn_t)P100_PartStep },
  { 0x004ba31bu, (re_fn_t)P122_ObjATick },
  { 0x004ba443u, (re_fn_t)InitSubsys004BA443 },
  { 0x004ba457u, (re_fn_t)P95_SortObjA },
  { 0x004ba57au, (re_fn_t)P95_SortObjC },
  { 0x004ba64du, (re_fn_t)P95_SortObjB },
  { 0x004ba720u, (re_fn_t)P98_DrawSix },
  { 0x004ba81fu, (re_fn_t)P135_SixBeam },
  { 0x004bb060u, (re_fn_t)P67_CompactPool },
  { 0x004bb11fu, (re_fn_t)FindOrAdd_004BB11F },
  { 0x004bf2a0u, (re_fn_t)P124_DebugLog },
  { 0x004bf35du, (re_fn_t)P26_LogTime },
  { 0x004bf400u, (re_fn_t)RoundSet_004BF400 },
  { 0x004bf452u, (re_fn_t)Pack565Bytes004BF452 },
  { 0x004bf471u, (re_fn_t)NoopFn004bf471 },
  { 0x004bf476u, (re_fn_t)Call004BF476 },
  { 0x004bf480u, (re_fn_t)NoopFn004bf480 },
  { 0x004bf485u, (re_fn_t)Call004BF485 },
  { 0x004bf4a1u, (re_fn_t)P124_WatchShow },
  { 0x004bf8a1u, (re_fn_t)ClearEntry_004BF8A1 },
  { 0x004bf910u, (re_fn_t)P21_FpsToBuf },
  { 0x004bfc30u, (re_fn_t)P28_LoadCarModels },
  { 0x004c020eu, (re_fn_t)Call004C020E },
  { 0x004c0218u, (re_fn_t)P99_CarModelClean },
  { 0x004c032au, (re_fn_t)P128_CarDeform },
  { 0x004c08bbu, (re_fn_t)P95_InitDebris },
  { 0x004c09b9u, (re_fn_t)GlobalSet004C09B9 },
  { 0x004c09e6u, (re_fn_t)P100_MarkerSpawn },
  { 0x004c0c6fu, (re_fn_t)P119_Hubcap },
  { 0x004c16c1u, (re_fn_t)CopyWords8000 },
  { 0x004c16d9u, (re_fn_t)P15_BlitRect16 },
  { 0x004c1749u, (re_fn_t)P15_BlitRect8 },
  { 0x004c17aeu, (re_fn_t)P27_LoadDentTextures },
  { 0x004c1b46u, (re_fn_t)FreeBufferD17EC8 },
  { 0x004c1b6cu, (re_fn_t)P99_CarOpsReset },
  { 0x004c1c23u, (re_fn_t)P104_CarDents },
  { 0x004c1f9bu, (re_fn_t)AddUnique_004C1F9B },
  { 0x004c200fu, (re_fn_t)DrainStackC200F },
  { 0x004c2042u, (re_fn_t)P98_ClearCarData },
  { 0x004c2ab0u, (re_fn_t)P97_DirKeys },
  { 0x004c2b9au, (re_fn_t)P98_DirCamKeys },
  { 0x004c2d73u, (re_fn_t)P102_DirFreeCam },
  { 0x004c3048u, (re_fn_t)P100_FreeCamKeys },
  { 0x004c32c1u, (re_fn_t)P98_CamClamp },
  { 0x004c3427u, (re_fn_t)P99_CamCheckDist },
  { 0x004c356du, (re_fn_t)ClampCameraHeight },
  { 0x004c36dau, (re_fn_t)ClearDirectorTable },
  { 0x004c372au, (re_fn_t)FreeDirectorBuffer },
  { 0x004c375au, (re_fn_t)GetWaypointAfterFrame },
  { 0x004c379du, (re_fn_t)GetWaypointForFrame },
  { 0x004c37f6u, (re_fn_t)DumpWaypoints },
  { 0x004c38e2u, (re_fn_t)P124_ReplayMenu },
  { 0x004c3c94u, (re_fn_t)DrawNodeChain },
  { 0x004c3cf1u, (re_fn_t)DrawNodeMarkersChain },
  { 0x004c3d5cu, (re_fn_t)DrawNode },
  { 0x004c3e6au, (re_fn_t)DrawNodeMarker },
  { 0x004c3f26u, (re_fn_t)SetNodeEnabled },
  { 0x004c3f8fu, (re_fn_t)ReadDirectorKeys },
  { 0x004c4151u, (re_fn_t)FindNodeById },
  { 0x004c419eu, (re_fn_t)FindNodeByLink },
  { 0x004c41ecu, (re_fn_t)GetNodeParent },
  { 0x004c4226u, (re_fn_t)FindNodeAtPixel },
  { 0x004c42a9u, (re_fn_t)DrawCornerIndicator },
  { 0x004c43b6u, (re_fn_t)P125_ReplayNodeAction },
  { 0x004c459fu, (re_fn_t)AddCamera },
  { 0x004c483eu, (re_fn_t)ChangeCamera },
  { 0x004c4b3au, (re_fn_t)AddTripodCamera },
  { 0x004c4ceeu, (re_fn_t)ChangeTripodCamera },
  { 0x004c4ef9u, (re_fn_t)P102_DirMenuNodes },
  { 0x004c5222u, (re_fn_t)SelectNewCamera },
  { 0x004c52d9u, (re_fn_t)SyncCameraFromList },
  { 0x004c5367u, (re_fn_t)DirNopStub },
  { 0x004c536cu, (re_fn_t)P61_RestoreCamState },
  { 0x004c5499u, (re_fn_t)P61_StoreCamState },
  { 0x004c567au, (re_fn_t)CameraDump },
  { 0x004c57b7u, (re_fn_t)GetCameraTypeName },
  { 0x004c582fu, (re_fn_t)P127_AutoCamera },
  { 0x004c5c5du, (re_fn_t)P60_NextTrafficCar },
  { 0x004c5d40u, (re_fn_t)CountNearbyCars },
  { 0x004c5e08u, (re_fn_t)P99_CamCheckPlayer },
  { 0x004c5f69u, (re_fn_t)P95_SlotAt },
  { 0x004c6091u, (re_fn_t)P47_Call51B111 },
  { 0x004c60b2u, (re_fn_t)IsCameraCarFarEnough },
  { 0x004c60fau, (re_fn_t)SetCamera },
  { 0x004c6142u, (re_fn_t)GetCamera },
  { 0x004c6168u, (re_fn_t)FindCameraById },
  { 0x004c61b2u, (re_fn_t)FindCameraForFrame },
  { 0x004c622cu, (re_fn_t)RenumberCameras },
  { 0x004c6264u, (re_fn_t)AddDirectorCamera },
  { 0x004c6312u, (re_fn_t)InsertCamera },
  { 0x004c64bdu, (re_fn_t)FreeCameraList },
  { 0x004c6524u, (re_fn_t)DeleteCamera },
  { 0x004c6691u, (re_fn_t)FindNearestCamera },
  { 0x004c6715u, (re_fn_t)CameraFrameDistance },
  { 0x004c6740u, (re_fn_t)P98_DirCamNext },
  { 0x004c68a7u, (re_fn_t)P112_DirTimeline },
  { 0x004c6d62u, (re_fn_t)P61_CamPrepare },
  { 0x004c8070u, (re_fn_t)ResetDirectorState },
  { 0x004c810fu, (re_fn_t)ClearDirectorTables },
  { 0x004c812eu, (re_fn_t)FreeDirectorData },
  { 0x004c813du, (re_fn_t)P124_HandleDirector },
  { 0x004c862fu, (re_fn_t)P66_DirSwitch },
  { 0x004c875du, (re_fn_t)SetDirectorMode },
  { 0x004c8e9eu, (re_fn_t)BackupCameraState },
  { 0x004c8ed2u, (re_fn_t)DropCameraBackup },
  { 0x004c8eecu, (re_fn_t)RestoreCameraBackup },
  { 0x004c92c0u, (re_fn_t)SaveDirector },
  { 0x004c9310u, (re_fn_t)LoadDirector },
  { 0x004c9360u, (re_fn_t)AddDefaultCamera },
  { 0x004c93b1u, (re_fn_t)P57_SaveDirectorIfAny },
  { 0x004c93e6u, (re_fn_t)ReadDirectorData },
  { 0x004c9621u, (re_fn_t)WriteDirectorData },
  { 0x004c96d6u, (re_fn_t)WriteWaypointChunk },
  { 0x004c97a2u, (re_fn_t)WriteCameraChunk },
  { 0x004c988eu, (re_fn_t)WriteReplayHeaderChunk },
  { 0x004c98deu, (re_fn_t)ReadCameraChunkV2 },
  { 0x004c9a16u, (re_fn_t)ReadCameraChunkV1 },
  { 0x004c9bf4u, (re_fn_t)LogWaypoint },
  { 0x004c9ca0u, (re_fn_t)LoadWaypoints },
  { 0x004c9dccu, (re_fn_t)DeleteWaypointFile },
  { 0x004ca0c0u, (re_fn_t)GlobalSet004CA0C0 },
  { 0x004ca135u, (re_fn_t)P132_Lights },
  { 0x004ca802u, (re_fn_t)P105_SpinModel },
  { 0x004ca98du, (re_fn_t)P107_CountModel },
  { 0x004cac86u, (re_fn_t)P14_Fn004CAC86 },
  { 0x004cad24u, (re_fn_t)CallIfD14EE4 },
  { 0x004cad47u, (re_fn_t)P14_Fn004CAD47 },
  { 0x004cadb5u, (re_fn_t)P130_Lightning },
  { 0x004cb097u, (re_fn_t)SetScaled_004CB097 },
  { 0x004cb102u, (re_fn_t)P103_Dawn },
  { 0x004cb2f5u, (re_fn_t)P103_Dusk },
  { 0x004cb4ffu, (re_fn_t)P98_LampColor },
  { 0x004cb619u, (re_fn_t)P81_Light },
  { 0x004cb857u, (re_fn_t)P98_InitSplash },
  { 0x004cb982u, (re_fn_t)ScriptStackPop004CB982 },
  { 0x004cb9bau, (re_fn_t)ScriptStackPop004CB9BA },
  { 0x004cb9f2u, (re_fn_t)ScriptStackPush004CB9F2 },
  { 0x004cba1du, (re_fn_t)P130_RainStep },
  { 0x004cbc1eu, (re_fn_t)P131_RainDraw },
  { 0x004cc008u, (re_fn_t)P130_RainSpawn },
  { 0x004cc1a2u, (re_fn_t)P131_Splash },
  { 0x004cc784u, (re_fn_t)PushEntry_004CC784 },
  { 0x004cc801u, (re_fn_t)P116_Reflections },
  { 0x004cd3fbu, (re_fn_t)P128_ModelHit },
  { 0x004cd875u, (re_fn_t)P120_ScriptReset },
  { 0x004cd994u, (re_fn_t)P130_SnowSpawn },
  { 0x004cdb25u, (re_fn_t)P130_SnowStep },
  { 0x004cdda6u, (re_fn_t)P110_ScriptSprites },
  { 0x004cf100u, (re_fn_t)GlobalSet004CF100 },
  { 0x004cf123u, (re_fn_t)P112_ScriptTriggers },
  { 0x004cf2cfu, (re_fn_t)P111_ScriptTick },
  { 0x004cf6b2u, (re_fn_t)P97_ScriptSave },
  { 0x004cf772u, (re_fn_t)P97_ScriptLoad },
  { 0x004cf84cu, (re_fn_t)P133_EventModels },
  { 0x004cfe69u, (re_fn_t)P112_ScriptRunId },
  { 0x004cff20u, (re_fn_t)P15_ListClearActiveByTag },
  { 0x004cff7eu, (re_fn_t)P97_ScriptResetCur },
  { 0x004d0021u, (re_fn_t)P15_ListClearAllActive },
  { 0x004d0071u, (re_fn_t)P51_SteerHeading },
  { 0x004d0102u, (re_fn_t)P98_ScriptFreeAll },
  { 0x004d020bu, (re_fn_t)P48_OpSet3 },
  { 0x004d02c6u, (re_fn_t)ScriptReadShort3_004D02C6 },
  { 0x004d033fu, (re_fn_t)ScriptReadVec3_004D033F },
  { 0x004d03d0u, (re_fn_t)ScriptOpSetBit200_004D03D0 },
  { 0x004d03fdu, (re_fn_t)ReturnZero004D03FD },
  { 0x004d0404u, (re_fn_t)ScriptOpSetBit2_004D0404 },
  { 0x004d0439u, (re_fn_t)P102_BoxAnyCar },
  { 0x004d0734u, (re_fn_t)P112_OpMoveCurve },
  { 0x004d09fdu, (re_fn_t)P112_OpMoveTo },
  { 0x004d0d7cu, (re_fn_t)P48_OpTurn },
  { 0x004d0f28u, (re_fn_t)P95_ScriptTurn },
  { 0x004d107eu, (re_fn_t)P48_OpSet4 },
  { 0x004d1111u, (re_fn_t)ScriptOpSkipClear004D1111 },
  { 0x004d1135u, (re_fn_t)ScriptReadU32_004D1135 },
  { 0x004d116cu, (re_fn_t)P48_OpRampDown },
  { 0x004d121bu, (re_fn_t)P48_OpRampUp },
  { 0x004d12cau, (re_fn_t)ScriptReadPair_004D12CA },
  { 0x004d133cu, (re_fn_t)ScriptLoopStep_004D133C },
  { 0x004d13d8u, (re_fn_t)ScriptOpSetBit4_004D13D8 },
  { 0x004d1402u, (re_fn_t)ScriptOpClearBit2_004D1402 },
  { 0x004d142cu, (re_fn_t)P48_OpFlags },
  { 0x004d14d8u, (re_fn_t)ScriptSkip16_004D14D8 },
  { 0x004d1529u, (re_fn_t)P65_ScriptCall },
  { 0x004d156au, (re_fn_t)P97_ScriptOpNext },
  { 0x004d1601u, (re_fn_t)ScriptOpSkip4_004D1601 },
  { 0x004d1635u, (re_fn_t)ScriptSkipBack_004D1635 },
  { 0x004d1672u, (re_fn_t)P48_OpRepeat },
  { 0x004d1737u, (re_fn_t)ScriptOpToggle10_004D1737 },
  { 0x004d1765u, (re_fn_t)P112_OpMoveCur },
  { 0x004d1a84u, (re_fn_t)NoopFn004d1a84 },
  { 0x004d1a89u, (re_fn_t)NoopFn004d1a89 },
  { 0x004d2500u, (re_fn_t)P95_SndInit },
  { 0x004d262cu, (re_fn_t)Fwd004D262C },
  { 0x004d263du, (re_fn_t)P56_CopsDebug },
  { 0x004d26eau, (re_fn_t)P105_ChaseMusic },
  { 0x004d28a3u, (re_fn_t)P100_CarSounds },
  { 0x004d29e1u, (re_fn_t)P95_SndTrigger },
  { 0x004d2adeu, (re_fn_t)AddClamp4095_004D2ADE },
  { 0x004d2b16u, (re_fn_t)FillRange004D2B16 },
  { 0x004d2b5du, (re_fn_t)P99_CopsNear },
  { 0x004d2c95u, (re_fn_t)P97_CopsSee },
  { 0x004d2d85u, (re_fn_t)Call004D2D85 },
  { 0x004d2d9fu, (re_fn_t)Fwd004D2D9F },
  { 0x004d3000u, (re_fn_t)P51_FileSize },
  { 0x004d303au, (re_fn_t)P53_ReadWholeFile },
  { 0x004d30a3u, (re_fn_t)P57_WriteFile },
  { 0x004d30f8u, (re_fn_t)P55_LoadFile },
  { 0x004d318eu, (re_fn_t)P55_LoadFileSize },
  { 0x004d322cu, (re_fn_t)P26_FindCdDrive },
  { 0x004d33c0u, (re_fn_t)P48_StartupSystems },
  { 0x004d3402u, (re_fn_t)P48_ShutdownSystems },
  { 0x004d3426u, (re_fn_t)InitMapState4D3426 },
  { 0x004d3444u, (re_fn_t)P99_MapFree },
  { 0x004d35b2u, (re_fn_t)P125_LevelLoad },
  { 0x004d38b7u, (re_fn_t)P145_LevelLoad },
  { 0x004d4663u, (re_fn_t)P137_LevelEnd },
  { 0x004d4a63u, (re_fn_t)P131_GameFrame },
  { 0x004d4bfbu, (re_fn_t)P132_GameLogic },
  { 0x004d4fc5u, (re_fn_t)P132_GameDraw },
  { 0x004d53e8u, (re_fn_t)P21_DrawFps },
  { 0x004d5ce0u, (re_fn_t)P116_SndLevelStart },
  { 0x004d5ffcu, (re_fn_t)Chain004D5FFC },
  { 0x004d600bu, (re_fn_t)Reset004D600B },
  { 0x004d602eu, (re_fn_t)P121_CamSounds },
  { 0x004d611bu, (re_fn_t)TryStartTrack_004D611B },
  { 0x004d614au, (re_fn_t)P46_SetBounds },
  { 0x004d6190u, (re_fn_t)SetFirstFree_004D6190 },
  { 0x004d61cfu, (re_fn_t)ClearSlots004D61CF },
  { 0x004d6209u, (re_fn_t)P42_ActionBound },
  { 0x004d623bu, (re_fn_t)P14_Fn004D623B },
  { 0x004d629eu, (re_fn_t)Set560388 },
  { 0x004d62aeu, (re_fn_t)P56_LoopStart },
  { 0x004d6354u, (re_fn_t)P53_StepBounds },
  { 0x004d63bcu, (re_fn_t)P101_TrafficSounds },
  { 0x004d65fau, (re_fn_t)P95_NearestTwo },
  { 0x004d6740u, (re_fn_t)P100_CarRevs },
  { 0x004d68dau, (re_fn_t)P75_CarVoice },
  { 0x004d69edu, (re_fn_t)P51_PitchJitterSfx },
  { 0x004d6a47u, (re_fn_t)P56_LoopUpdate },
  { 0x004d6ae7u, (re_fn_t)P99_GearBox },
  { 0x004d6c20u, (re_fn_t)ClearPairs004D6C20 },
  { 0x004d6c5au, (re_fn_t)P75_BgSound },
  { 0x004d6d68u, (re_fn_t)ClearPair004D6D68 },
  { 0x004d6dacu, (re_fn_t)P75_CarSound },
  { 0x004d6e9fu, (re_fn_t)CopyTable_004D6E9F },
  { 0x004d6ef2u, (re_fn_t)P95_AmbientTick },
  { 0x004d74e0u, (re_fn_t)P126_DebugKeys },
  { 0x004d7766u, (re_fn_t)P98_FreeCamKeys },
  { 0x004d78f3u, (re_fn_t)P21_FrameTicks },
  { 0x004d7a21u, (re_fn_t)P96_FpsText },
  { 0x004d7b36u, (re_fn_t)RingAdvance004D7B36 },
  { 0x004d7b60u, (re_fn_t)PlayTrack004D7B60 },
  { 0x004d7b73u, (re_fn_t)P26_FindWheelModels },
  { 0x004d7c46u, (re_fn_t)P108_FillRect },
  { 0x004d7debu, (re_fn_t)P108_FillRectB },
  { 0x004d7f91u, (re_fn_t)P109_GradRect },
  { 0x004d81dau, (re_fn_t)P109_GradRectS },
  { 0x004d8487u, (re_fn_t)P51_ScalePair },
  { 0x004d8511u, (re_fn_t)P114_DrawSpr },
  { 0x004d8c23u, (re_fn_t)ClearSlots004D8C23 },
  { 0x004d8c80u, (re_fn_t)P27_MemLeakReport },
  { 0x004d8db4u, (re_fn_t)P98_DebugMalloc },
  { 0x004d8f30u, (re_fn_t)P98_DebugFree },
  { 0x004d9013u, (re_fn_t)Round1024 },
  { 0x004d9028u, (re_fn_t)Mask004D9028 },
  { 0x004d9078u, (re_fn_t)Rand_004D9078 },
  { 0x004d90f4u, (re_fn_t)P96_LogLine },
  { 0x004d9237u, (re_fn_t)P55_PopDeferred },
  { 0x004d92d2u, (re_fn_t)P106_LfbText },
  { 0x004d9478u, (re_fn_t)CursorWrap004D9478 },
  { 0x004d94b7u, (re_fn_t)CursorSet004D94B7 },
  { 0x004d950fu, (re_fn_t)Pack565_004D950F },
  { 0x004d9539u, (re_fn_t)SetDrawParams_004D9539 },
  { 0x004d9587u, (re_fn_t)Clear2C3B8 },
  { 0x004d9596u, (re_fn_t)P27_ReadChunked },
  { 0x004d9663u, (re_fn_t)P96_LoadBar },
  { 0x004d97b8u, (re_fn_t)CounterDecrement004D97B8 },
  { 0x004d97dcu, (re_fn_t)SetD11804 },
  { 0x004d97e9u, (re_fn_t)P48_AnyKey },
  { 0x004d9827u, (re_fn_t)P47_DirText },
  { 0x004d986eu, (re_fn_t)P21_DrawClock },
  { 0x004d9908u, (re_fn_t)P47_CameraModeText },
  { 0x004d9951u, (re_fn_t)P126_ScreenShot },
  { 0x004d9ad4u, (re_fn_t)P97_LfbSnap },
  { 0x004da5e0u, (re_fn_t)P94_InitCurves },
  { 0x004da75bu, (re_fn_t)CopyBDF984 },
  { 0x004da76au, (re_fn_t)P94_QuatToMat },
  { 0x004da8d9u, (re_fn_t)P56_ObjSync },
  { 0x004daa36u, (re_fn_t)P56_ObjInit },
  { 0x004daac7u, (re_fn_t)P59_ObjDir },
  { 0x004dab80u, (re_fn_t)P94_PackState },
  { 0x004daceeu, (re_fn_t)P142_CarsStep },
  { 0x004dc8b0u, (re_fn_t)MenuAddItem004DC8B0 },
  { 0x004dc8eau, (re_fn_t)P12_Fn004DC8EA },
  { 0x004dc91bu, (re_fn_t)P100_RoadHeightF },
  { 0x004dcb62u, (re_fn_t)P103_RoadHeight },
  { 0x004dd039u, (re_fn_t)P100_RoadHeight },
  { 0x004dd262u, (re_fn_t)P103_GroundAt },
  { 0x004dd7ecu, (re_fn_t)P102_ResetCars },
  { 0x004ddacau, (re_fn_t)P107_CarInput },
  { 0x004de381u, (re_fn_t)P127_PlayerSkid },
  { 0x004de86cu, (re_fn_t)P119_CarSkids },
  { 0x004dea35u, (re_fn_t)P101_CarGround },
  { 0x004deb99u, (re_fn_t)P103_CarsOverlap },
  { 0x004defd1u, (re_fn_t)P46_UpdateObjects },
  { 0x004df024u, (re_fn_t)P142_WheelPhys },
  { 0x004e0fd4u, (re_fn_t)P94_SpringStep },
  { 0x004e10e3u, (re_fn_t)P126_WheelSmoke },
  { 0x004e122cu, (re_fn_t)AddVelocity004E122C },
  { 0x004e12e4u, (re_fn_t)P16_IdleTimer },
  { 0x004e2ee0u, (re_fn_t)P37_InitInput },
  { 0x004e31d5u, (re_fn_t)P34_ReleaseInput },
  { 0x004e3391u, (re_fn_t)P36_PollInput },
  { 0x004e3769u, (re_fn_t)P36_SelectJoystick },
  { 0x004e3830u, (re_fn_t)GetB31E18 },
  { 0x004e383au, (re_fn_t)IsFlagSetNotMasked_004E383A },
  { 0x004e3871u, (re_fn_t)AnyKeyHeld_004E3871 },
  { 0x004e38b4u, (re_fn_t)IsKeyOnly004E38B4 },
  { 0x004e38d9u, (re_fn_t)IsKeyOnly004E38D9 },
  { 0x004e38feu, (re_fn_t)GlobalSet004E38FE },
  { 0x004e3911u, (re_fn_t)GlobalSet004E3911 },
  { 0x004e3924u, (re_fn_t)IsButtonActive_004E3924 },
  { 0x004e39acu, (re_fn_t)P36_GetPadButtons },
  { 0x004e3b19u, (re_fn_t)ReturnZero004E3B19 },
  { 0x004e3b20u, (re_fn_t)SetB31E00 },
  { 0x004e3b3cu, (re_fn_t)P35_UpdateForce },
  { 0x004e3ffeu, (re_fn_t)P36_AcquireDevice },
  { 0x004e4076u, (re_fn_t)P34_ReAcquire },
  { 0x004e417fu, (re_fn_t)P34_ReadKeyboard },
  { 0x004e41d5u, (re_fn_t)P35_CreateEffectA },
  { 0x004e429bu, (re_fn_t)P35_CreateEffectB },
  { 0x004e4379u, (re_fn_t)Get4Words004E4379 },
  { 0x004e43b7u, (re_fn_t)P21_SetAxisByte },
  { 0x004e49c0u, (re_fn_t)P98_ResetMission },
  { 0x004e4bdcu, (re_fn_t)P104_MissionInit },
  { 0x004e4d35u, (re_fn_t)P103_Mission4Cars },
  { 0x004e4f62u, (re_fn_t)P56_HudTick },
  { 0x004e5011u, (re_fn_t)P103_GhostState },
  { 0x004e5284u, (re_fn_t)P94_FadeStep },
  { 0x004e53b5u, (re_fn_t)P105_StuntHints },
  { 0x004e58bau, (re_fn_t)P15_GridCell },
  { 0x004e5938u, (re_fn_t)PushHistory_004E5938 },
  { 0x004e5982u, (re_fn_t)P12_Fn004E5982 },
  { 0x004e59b9u, (re_fn_t)P52_HudDispatch },
  { 0x004e5a1au, (re_fn_t)P97_FadeIconDraw },
  { 0x004e5b78u, (re_fn_t)P115_PaperHud },
  { 0x004e5d64u, (re_fn_t)P95_SeqMatch },
  { 0x004e5ea2u, (re_fn_t)P59_PickUp },
  { 0x004e5f4du, (re_fn_t)Get138 },
  { 0x004e5f5bu, (re_fn_t)P15_RaiseLimits },
  { 0x004e5fd7u, (re_fn_t)P114_PaperMark },
  { 0x004e60c1u, (re_fn_t)StepToward004E60C1 },
  { 0x004e612au, (re_fn_t)SetMode2_004E612A },
  { 0x004e6166u, (re_fn_t)Set0D044C8 },
  { 0x004e6175u, (re_fn_t)P55_LoadPaper },
  { 0x004e625eu, (re_fn_t)P56_GhostInit },
  { 0x004e6310u, (re_fn_t)P135_GhostTrail },
  { 0x004e6c92u, (re_fn_t)P102_GhostTrail },
  { 0x004e6f90u, (re_fn_t)P100_GhostNear },
  { 0x004e71dcu, (re_fn_t)P96_IconAt },
  { 0x004e72f8u, (re_fn_t)P96_IconRect },
  { 0x004e7450u, (re_fn_t)P122_IconCopy },
  { 0x004e7613u, (re_fn_t)P112_IconBar },
  { 0x004e7755u, (re_fn_t)P112_IconScaled },
  { 0x004e8440u, (re_fn_t)P96_InitSphere },
  { 0x004e8595u, (re_fn_t)P110_SmokeRing },
  { 0x004e8bd0u, (re_fn_t)P114_ColorFlash },
  { 0x004e8f1eu, (re_fn_t)P76_AngleColor },
  { 0x004e9006u, (re_fn_t)P126_DropsAt },
  { 0x004e919du, (re_fn_t)P126_DropScan },
  { 0x004e9427u, (re_fn_t)P99_MarkerReset },
  { 0x004e959au, (re_fn_t)P81_Limit },
  { 0x004e964au, (re_fn_t)P42_SetViewAngles },
  { 0x004e969fu, (re_fn_t)P113_Heli },
  { 0x004e9bbfu, (re_fn_t)P140_MrkFly },
  { 0x004ea346u, (re_fn_t)P98_DrawMarker },
  { 0x004eac70u, (re_fn_t)P127_LampLights },
  { 0x004eaf8du, (re_fn_t)NegateCamZ004EAF8D },
  { 0x004eafcfu, (re_fn_t)P78_LoadLampsBlock },
  { 0x004eafe0u, (re_fn_t)P78_LoadLamps },
  { 0x004eb19bu, (re_fn_t)P58_FreeList },
  { 0x004eb3c0u, (re_fn_t)P55_LoadFrustum },
  { 0x004eb449u, (re_fn_t)AllocMapBuffer400000 },
  { 0x004eb46au, (re_fn_t)FreeMapBuffer400000 },
  { 0x004eb490u, (re_fn_t)P80_LoadModels },
  { 0x004eb7cfu, (re_fn_t)ReadBlocks_004EB7CF },
  { 0x004eb811u, (re_fn_t)P78_LoadVerts },
  { 0x004eb975u, (re_fn_t)P41_LoadTexPages },
  { 0x004ec154u, (re_fn_t)P27_LoadPalettes },
  { 0x004ec280u, (re_fn_t)P54_ReadMapA },
  { 0x004ec2ecu, (re_fn_t)P57_SkipBlock },
  { 0x004ec336u, (re_fn_t)P62_LoadMapHeader },
  { 0x004ec3fdu, (re_fn_t)P54_ReadMapB },
  { 0x004ec466u, (re_fn_t)ReadTable_004EC466 },
  { 0x004ec49au, (re_fn_t)ReadTable_004EC49A },
  { 0x004ec4ceu, (re_fn_t)P46_LoadMapB },
  { 0x004ec522u, (re_fn_t)ReadTable_004EC522 },
  { 0x004ec556u, (re_fn_t)ReadTable_004EC556 },
  { 0x004ec58au, (re_fn_t)P28_LoadEventModels },
  { 0x004ec7acu, (re_fn_t)P54_ReadNames },
  { 0x004ec7f4u, (re_fn_t)P46_LoadMapA },
  { 0x004ec837u, (re_fn_t)P20_FindNameNoCase },
  { 0x004ec8a8u, (re_fn_t)P20_FindNameValue },
  { 0x004ec91eu, (re_fn_t)P93_FindIcon },
  { 0x004eca08u, (re_fn_t)P77_OpenLevel },
  { 0x004ecadeu, (re_fn_t)P77_LoadLevel },
  { 0x004ecda8u, (re_fn_t)P54_AllocMapBufs },
  { 0x004ece1au, (re_fn_t)FreeMapBufs004ECE1A },
  { 0x004ece84u, (re_fn_t)P42_CellIndex },
  { 0x004ecee8u, (re_fn_t)P76_InBox },
  { 0x004ecfbdu, (re_fn_t)P21_GridCellSet },
  { 0x004ed055u, (re_fn_t)P80_LoadHeader },
  { 0x004ed5b1u, (re_fn_t)AllocMapBuffer300000 },
  { 0x004ed5d2u, (re_fn_t)FreeMapBuffer300000 },
  { 0x004ed5f8u, (re_fn_t)P87_LoadTile },
  { 0x004edaa2u, (re_fn_t)P88_StreamTiles },
  { 0x004edd08u, (re_fn_t)P88_CellUpdate },
  { 0x004ee065u, (re_fn_t)P75_ResetObjs },
  { 0x004ee129u, (re_fn_t)P55_ResetSel },
  { 0x004ee18bu, (re_fn_t)P87_DrawObjA },
  { 0x004ee4b7u, (re_fn_t)P87_DrawObjB },
  { 0x004ee813u, (re_fn_t)P76_CellFromPos },
  { 0x004ee8f4u, (re_fn_t)P89_DrawMap },
  { 0x004ef309u, (re_fn_t)P55_RunTableA },
  { 0x004ef364u, (re_fn_t)P55_RunTableB },
  { 0x004ef3cdu, (re_fn_t)P101_SkyInit },
  { 0x004ef66au, (re_fn_t)P106_SkyModels },
  { 0x004ef793u, (re_fn_t)P89_VisMask },
  { 0x004ef997u, (re_fn_t)P89_Fill1 },
  { 0x004ef9cdu, (re_fn_t)P131_LoadCosDen },
  { 0x004efafdu, (re_fn_t)P126_ReadMapPals },
  { 0x004efc03u, (re_fn_t)P58_FreeRecs },
  { 0x004efc7cu, (re_fn_t)P40_DownloadPalette },
  { 0x004f0f90u, (re_fn_t)P134_CamCine },
  { 0x004f1325u, (re_fn_t)P100_DrawPartsB },
  { 0x004f154eu, (re_fn_t)P123_SideDist },
  { 0x004f1745u, (re_fn_t)P126_SpawnInit },
  { 0x004f1a19u, (re_fn_t)P127_SpawnTick },
  { 0x004f2360u, (re_fn_t)P133_MirrorDraw },
  { 0x004f29f7u, (re_fn_t)P101_MirrorMaskR },
  { 0x004f2c9au, (re_fn_t)P100_MirrorMask },
  { 0x004f2f2au, (re_fn_t)P94_RowSpans },
  { 0x004f3032u, (re_fn_t)P56_DrawRowRects },
  { 0x004f30e6u, (re_fn_t)FreeBuffer_004F30E6 },
  { 0x004f3490u, (re_fn_t)P137_LoadMcd },
  { 0x004f388eu, (re_fn_t)P137_MotionInit },
  { 0x004f3c16u, (re_fn_t)P54_FreeTab4 },
  { 0x004f3c74u, (re_fn_t)P100_DrawParts },
  { 0x004f3e78u, (re_fn_t)P12_Fn004F3E78 },
  { 0x004f4180u, (re_fn_t)P138_LoadMission },
  { 0x004f4596u, (re_fn_t)P139_CompileScript },
  { 0x004f472bu, (re_fn_t)P127_ScriptTick },
  { 0x004f4a33u, (re_fn_t)P121_ScriptHud },
  { 0x004f4c3du, (re_fn_t)P94_NearestObjDist },
  { 0x004f4d3cu, (re_fn_t)P99_ScriptMsgs },
  { 0x004f4f10u, (re_fn_t)P97_ObjsFromScript },
  { 0x004f5012u, (re_fn_t)P98_ScriptRange },
  { 0x004f51b4u, (re_fn_t)P101_GoalTick },
  { 0x004f556cu, (re_fn_t)P100_GoalsCheck },
  { 0x004f568au, (re_fn_t)P99_GoalCheck },
  { 0x004f57d7u, (re_fn_t)P97_GoalCops },
  { 0x004f58c6u, (re_fn_t)P97_GoalReached },
  { 0x004f5951u, (re_fn_t)P47_ResetPick },
  { 0x004f5a57u, (re_fn_t)P56_ChaseTick },
  { 0x004f5afeu, (re_fn_t)P114_Timer },
  { 0x004f5c58u, (re_fn_t)ScriptSetWaitX50_004F5C58 },
  { 0x004f5c72u, (re_fn_t)ScriptSetWait004F5C72 },
  { 0x004f5c89u, (re_fn_t)P97_AddTime },
  { 0x004f5d67u, (re_fn_t)TickTimer4F5D67 },
  { 0x004f5d98u, (re_fn_t)DrawBanner_004F5D98 },
  { 0x004f5dcdu, (re_fn_t)P58_FreeLists },
  { 0x004f5e55u, (re_fn_t)P125_AddDashMessage },
  { 0x004f6011u, (re_fn_t)P58_FindChunk },
  { 0x004f60b7u, (re_fn_t)P120_DebugInfo },
  { 0x004f621du, (re_fn_t)P131_ScriptLine },
  { 0x004f6333u, (re_fn_t)P42_FindCommand },
  { 0x004f638du, (re_fn_t)P99_ScriptFree },
  { 0x004f64ddu, (re_fn_t)P42_FindVar },
  { 0x004f652eu, (re_fn_t)P96_ParseWord },
  { 0x004f6612u, (re_fn_t)P96_ParseQuoted },
  { 0x004f6774u, (re_fn_t)P65_NextToken },
  { 0x004f68a1u, (re_fn_t)P147_ParseCmd },
  { 0x004f8485u, (re_fn_t)P122_SetVar },
  { 0x004f8643u, (re_fn_t)P77_ListAdd },
  { 0x004f8735u, (re_fn_t)P13_Fn004F8735 },
  { 0x004f87e0u, (re_fn_t)P65_ReadInts },
  { 0x004f8862u, (re_fn_t)P99_VarSetStr },
  { 0x004f892au, (re_fn_t)P59_VarsInit },
  { 0x004f89b7u, (re_fn_t)SetTableValue_004F89B7 },
  { 0x004f89ebu, (re_fn_t)NoopFn004F89EB },
  { 0x004f8a2du, (re_fn_t)P59_VarSetString },
  { 0x004f8accu, (re_fn_t)MenuClick004F8ACC },
  { 0x004f8b0au, (re_fn_t)P139_AddLabel },
  { 0x004f8cfdu, (re_fn_t)P65_FindByName },
  { 0x004f8d6du, (re_fn_t)P58_FreeNames },
  { 0x004f8e0cu, (re_fn_t)P146_ScriptCmd },
  { 0x004fba23u, (re_fn_t)P96_ClockText },
  { 0x004fbbc5u, (re_fn_t)DrawTextLine004FBBC5 },
  { 0x004fbbfcu, (re_fn_t)P139_TrailLoad },
  { 0x004fbe96u, (re_fn_t)LoadTrail004FBE96 },
  { 0x004fbeb2u, (re_fn_t)P120_ConeRec },
  { 0x004fbfadu, (re_fn_t)P138_TrailEnd },
  { 0x004fc0c7u, (re_fn_t)Fwd004FC0C7 },
  { 0x004fc0d9u, (re_fn_t)P125_PickupTick },
  { 0x004fc3f4u, (re_fn_t)P98_DrawScriptModels },
  { 0x004fc57bu, (re_fn_t)FreeBuf004FC57B },
  { 0x004fc5abu, (re_fn_t)P42_FindCommandById },
  { 0x004fc5e1u, (re_fn_t)P26_RandomFx },
  { 0x004fe830u, (re_fn_t)ResolveTable_004FE830 },
  { 0x004fe869u, (re_fn_t)P102_LampColor },
  { 0x004feb59u, (re_fn_t)P100_Billboards },
  { 0x004fede5u, (re_fn_t)P103_MissionModels },
  { 0x004fef26u, (re_fn_t)P131_MissionObj },
  { 0x004ffad8u, (re_fn_t)P74_ShiftRows },
  { 0x00500090u, (re_fn_t)P97_ScriptEach },
  { 0x00500154u, (re_fn_t)P53_CallWithState },
  { 0x005001bbu, (re_fn_t)P129_BoxMerge },
  { 0x00500937u, (re_fn_t)P129_ObjBoxes },
  { 0x00500e1du, (re_fn_t)P129_CarObjects },
  { 0x005012a3u, (re_fn_t)Update005012A3 },
  { 0x00501770u, (re_fn_t)P136_OverlayMap },
  { 0x00501c63u, (re_fn_t)P102_HudInit },
  { 0x0050229cu, (re_fn_t)P12_Fn0050229C },
  { 0x0050230au, (re_fn_t)P119_Hud },
  { 0x005025dcu, (re_fn_t)P62_SpeedText },
  { 0x00502680u, (re_fn_t)ClearField2C_00502680 },
  { 0x0050268fu, (re_fn_t)P16_FillHudRect },
  { 0x00502779u, (re_fn_t)SetField24_00502779 },
  { 0x00502787u, (re_fn_t)P110_Gauge },
  { 0x00502ceeu, (re_fn_t)P109_ScriptMarkers },
  { 0x00502e76u, (re_fn_t)P123_ObjShadows },
  { 0x00502fe2u, (re_fn_t)P117_FullMap },
  { 0x005032ceu, (re_fn_t)P120_HudTimes },
  { 0x00503c03u, (re_fn_t)P71_ScoreSetup },
  { 0x00503ddfu, (re_fn_t)P147_ScoreRec },
  { 0x00503e83u, (re_fn_t)P14_Fn00503E83 },
  { 0x00503eccu, (re_fn_t)PackRGB00503ECC },
  { 0x00503ef4u, (re_fn_t)P14_Fn00503EF4 },
  { 0x00503f76u, (re_fn_t)P108_RadarShape },
  { 0x00504439u, (re_fn_t)P14_Fn00504439 },
  { 0x00504479u, (re_fn_t)P100_RadarMap },
  { 0x00504699u, (re_fn_t)P12_Fn00504699 },
  { 0x005046f7u, (re_fn_t)P56_BmpPage },
  { 0x005047abu, (re_fn_t)P62_DownloadPage },
  { 0x00504866u, (re_fn_t)P109_RadarArrows },
  { 0x00504a0au, (re_fn_t)P108_RadarArrow },
  { 0x00504cadu, (re_fn_t)P117_Radar },
  { 0x00505b54u, (re_fn_t)P109_RadarTraffic },
  { 0x00505e2bu, (re_fn_t)P108_RadarCar },
  { 0x005061c9u, (re_fn_t)P94_RadarXY },
  { 0x005062ccu, (re_fn_t)P70_RadarNearest },
  { 0x005063a4u, (re_fn_t)P135_RadarLine },
  { 0x00506a07u, (re_fn_t)P99_RadarXform },
  { 0x00506b4bu, (re_fn_t)P56_DrawSprite },
  { 0x00506bffu, (re_fn_t)P58_DrawObjs },
  { 0x00506c96u, (re_fn_t)P116_RadarIcon },
  { 0x00506fa0u, (re_fn_t)P107_Compass },
  { 0x00507310u, (re_fn_t)P95_DrawCross },
  { 0x005073f1u, (re_fn_t)P114_RadarMarks },
  { 0x005074e5u, (re_fn_t)P97_MapIcon },
  { 0x005075f6u, (re_fn_t)P57_ScreenToView },
  { 0x00507672u, (re_fn_t)P94_MapToScreen },
  { 0x0050784du, (re_fn_t)P70_RadarNearestB },
  { 0x00507925u, (re_fn_t)P131_RadarArrow },
  { 0x00507de2u, (re_fn_t)P95_MapRotate },
  { 0x00507eeau, (re_fn_t)P108_MapTexRect },
  { 0x00509c40u, (re_fn_t)P77_ResetTables },
  { 0x00509d27u, (re_fn_t)P95_DrawLineRGB },
  { 0x00509e64u, (re_fn_t)P102_RadarClear },
  { 0x0050a15bu, (re_fn_t)P128_ClipArea },
  { 0x0050b088u, (re_fn_t)P129_MapCars },
  { 0x0050b957u, (re_fn_t)P127_MapWindow },
  { 0x0050bc2bu, (re_fn_t)P97_MarkCells },
  { 0x0050bd09u, (re_fn_t)P110_RadarGrid },
  { 0x0050c010u, (re_fn_t)P12_Fn0050C010 },
  { 0x0050c087u, (re_fn_t)P128_CopPath },
  { 0x0050cfebu, (re_fn_t)P114_PathDraw },
  { 0x0050d4a2u, (re_fn_t)P128_CopRoute },
  { 0x0050d97au, (re_fn_t)P14_Fn0050D97A },
  { 0x0050e940u, (re_fn_t)SetLatchValue0050E940 },
  { 0x0050e963u, (re_fn_t)P12_Fn0050E963 },
  { 0x0050e9abu, (re_fn_t)P96_ReplayScript },
  { 0x0050eaaau, (re_fn_t)P116_PauseMenu },
  { 0x0050ee00u, (re_fn_t)P127_Pause },
  { 0x0050f289u, (re_fn_t)P55_StopAudio },
  { 0x0050f304u, (re_fn_t)P107_MenuNav },
  { 0x0050f569u, (re_fn_t)P99_MenuItems },
  { 0x0050f781u, (re_fn_t)MenuSound0050F781 },
  { 0x0050f7b2u, (re_fn_t)P97_SndMenuInit },
  { 0x0050f8a2u, (re_fn_t)MenuMusic0050F8A2 },
  { 0x0050f8ccu, (re_fn_t)MenuMusic0050F8CC },
  { 0x0050f8f2u, (re_fn_t)MenuBits0050F8F2 },
  { 0x0050f930u, (re_fn_t)MenuRate0050F930 },
  { 0x0050f971u, (re_fn_t)MenuSoundCh0050F971 },
  { 0x0050f9aau, (re_fn_t)NoopFn0050f9aa },
  { 0x0050f9afu, (re_fn_t)NoopFn0050f9af },
  { 0x0050f9b4u, (re_fn_t)StepUp0050F9B4 },
  { 0x0050f9e3u, (re_fn_t)StepDown0050F9E3 },
  { 0x0050fa12u, (re_fn_t)StepUp0050FA12 },
  { 0x0050fa41u, (re_fn_t)StepDown0050FA41 },
  { 0x0050fa70u, (re_fn_t)MenuQuality0050FA70 },
  { 0x0050fab0u, (re_fn_t)P96_ClampOptions },
  { 0x0050fbf4u, (re_fn_t)P125_CtrlMenuValues },
  { 0x0050fe26u, (re_fn_t)MenuToggle0050FE26 },
  { 0x0050fe82u, (re_fn_t)Toggle0050FE82 },
  { 0x0050fea3u, (re_fn_t)Toggle0050FEA3 },
  { 0x0050fec4u, (re_fn_t)Toggle0050FEC4 },
  { 0x0050fee5u, (re_fn_t)MenuToggle0050FEE5 },
  { 0x0050ff41u, (re_fn_t)Toggle0050FF41 },
  { 0x0050ff62u, (re_fn_t)Toggle0050FF62 },
  { 0x0050ff83u, (re_fn_t)Toggle0050FF83 },
  { 0x0050ffa4u, (re_fn_t)Toggle0050FFA4 },
  { 0x0050ffc5u, (re_fn_t)Toggle0050FFC5 },
  { 0x0050ffe6u, (re_fn_t)Toggle0050FFE6 },
  { 0x00510007u, (re_fn_t)Toggle00510007 },
  { 0x00510028u, (re_fn_t)MenuToggle00510028 },
  { 0x00510084u, (re_fn_t)P52_MenuStepToggle },
  { 0x00510102u, (re_fn_t)NoopFn00510102 },
  { 0x00510107u, (re_fn_t)NoopFn00510107 },
  { 0x0051010cu, (re_fn_t)StepUp_0051010C },
  { 0x00510145u, (re_fn_t)StepDown_00510145 },
  { 0x0051017eu, (re_fn_t)StepUp_0051017E },
  { 0x005101b7u, (re_fn_t)StepDown_005101B7 },
  { 0x005101f0u, (re_fn_t)P53_NameEntry },
  { 0x00510349u, (re_fn_t)GlobalSet00510349 },
  { 0x00510382u, (re_fn_t)SetMode4_00510382 },
  { 0x005103c4u, (re_fn_t)BackOrDirector_005103C4 },
  { 0x005103ecu, (re_fn_t)MenuBack005103EC },
  { 0x0051040fu, (re_fn_t)GlobalSet0051040F },
  { 0x00510448u, (re_fn_t)SetMode1_00510448 },
  { 0x0051049eu, (re_fn_t)ToggleBit0051049E },
  { 0x005104b9u, (re_fn_t)SwitchPanel_005104B9 },
  { 0x005104edu, (re_fn_t)P17_PushScreenState },
  { 0x00510550u, (re_fn_t)GlobalSet00510550 },
  { 0x00510595u, (re_fn_t)GlobalSet00510595 },
  { 0x005105dau, (re_fn_t)P56_ReplaySetup },
  { 0x0051065bu, (re_fn_t)GlobalSet0051065B },
  { 0x0051066au, (re_fn_t)SwitchPanel_0051066A },
  { 0x0051069eu, (re_fn_t)SwitchPanel_0051069E },
  { 0x005106d2u, (re_fn_t)SetMode1b_005106D2 },
  { 0x00510728u, (re_fn_t)P52_MenuReload },
  { 0x00510784u, (re_fn_t)P55_NamesD },
  { 0x0051080eu, (re_fn_t)SoundMenuSave0051080E },
  { 0x0051082au, (re_fn_t)SoundMenuOut0051082A },
  { 0x0051084du, (re_fn_t)P115_IconFlip },
  { 0x00510e1du, (re_fn_t)P115_IconScaled },
  { 0x00511378u, (re_fn_t)GlobalSet00511378 },
  { 0x005113b1u, (re_fn_t)GlobalSet005113B1 },
  { 0x00511e60u, (re_fn_t)P73_ParticlesReset },
  { 0x00511fb8u, (re_fn_t)P12_Fn00511FB8 },
  { 0x0051200fu, (re_fn_t)P43_FreeSlot },
  { 0x005120a7u, (re_fn_t)CountActive_005120A7 },
  { 0x0051210cu, (re_fn_t)PoolAlloc0051210C },
  { 0x00512174u, (re_fn_t)P106_PartTick },
  { 0x005128b7u, (re_fn_t)P114_PartModels },
  { 0x005129e1u, (re_fn_t)P113_PartDraw },
  { 0x00512de7u, (re_fn_t)P103_PartPath },
  { 0x0051329bu, (re_fn_t)P102_SpawnDust },
  { 0x0051358du, (re_fn_t)P99_PartOnChair },
  { 0x0051378bu, (re_fn_t)P60_SpawnParticle },
  { 0x0051380bu, (re_fn_t)P71_CountNear },
  { 0x00513905u, (re_fn_t)P70_FindParticle },
  { 0x005139d7u, (re_fn_t)P101_PickCell },
  { 0x00513cc7u, (re_fn_t)P96_PartRunA },
  { 0x00513ce0u, (re_fn_t)P96_PartRunB },
  { 0x00513cf9u, (re_fn_t)Fwd00513CF9 },
  { 0x00513d0au, (re_fn_t)P101_PartFall },
  { 0x00513efdu, (re_fn_t)P68_ObjStepB },
  { 0x00513fbcu, (re_fn_t)P67_ObjStep },
  { 0x0051406eu, (re_fn_t)NoopFn0051406e },
  { 0x00514073u, (re_fn_t)P43_AnimNext },
  { 0x00514103u, (re_fn_t)AngleToDir00514103 },
  { 0x00514165u, (re_fn_t)P71_Course },
  { 0x00514261u, (re_fn_t)P61_SpawnPart },
  { 0x00514332u, (re_fn_t)P70_SpawnPart4 },
  { 0x00514403u, (re_fn_t)P70_SpawnPart2 },
  { 0x005144d4u, (re_fn_t)P71_EdgeA },
  { 0x00514779u, (re_fn_t)P71_EdgeB },
  { 0x00514a47u, (re_fn_t)P98_PartAim },
  { 0x00514bc7u, (re_fn_t)InitObjState_00514BC7 },
  { 0x00514c43u, (re_fn_t)ObjInit00514C43 },
  { 0x00514c72u, (re_fn_t)P62_ParticleSet },
  { 0x00514c9fu, (re_fn_t)P99_PartAhead },
  { 0x00514e4cu, (re_fn_t)IsFlag80_00514E4C },
  { 0x00514e6au, (re_fn_t)RangeCheck00514E6A },
  { 0x00514e99u, (re_fn_t)ResetObjState_00514E99 },
  { 0x00514f0au, (re_fn_t)TypeIsKnown00514F0A },
  { 0x00514f47u, (re_fn_t)P68_AimSetup },
  { 0x0051500cu, (re_fn_t)P101_PartTurn },
  { 0x0051551eu, (re_fn_t)P71_InitNear },
  { 0x0051564fu, (re_fn_t)P98_PartCheck },
  { 0x00515813u, (re_fn_t)P62_ParticleInit },
  { 0x005158cfu, (re_fn_t)P102_CarPlanes },
  { 0x00515bf1u, (re_fn_t)P71_InPlanes },
  { 0x00515ccau, (re_fn_t)P71_FaceCar },
  { 0x00516da0u, (re_fn_t)P58_LangStrings },
  { 0x00516e2eu, (re_fn_t)FreeBufs00516E2E },
  { 0x00516e76u, (re_fn_t)P12_Fn00516E76 },
  { 0x00516eb4u, (re_fn_t)SetRGB00516EB4 },
  { 0x00516ed3u, (re_fn_t)P96_TextCenter },
  { 0x00516fbeu, (re_fn_t)P67_CenterDraw },
  { 0x0051707au, (re_fn_t)SetFade0051707A },
  { 0x005170abu, (re_fn_t)P70_FadeColor },
  { 0x0051718au, (re_fn_t)P96_TextAt },
  { 0x005172bbu, (re_fn_t)P96_TextMid },
  { 0x005173d7u, (re_fn_t)P73_Text },
  { 0x005174c6u, (re_fn_t)P19_ScaleX },
  { 0x00517512u, (re_fn_t)P19_ScaleY },
  { 0x0051755eu, (re_fn_t)P70_ShadowText },
  { 0x0051763au, (re_fn_t)P98_LoadLang },
  { 0x005179d0u, (re_fn_t)P103_ReplayReset },
  { 0x00517d58u, (re_fn_t)P138_ReplayCfg },
  { 0x00518137u, (re_fn_t)P56_ReplayPaths },
  { 0x005181dau, (re_fn_t)P138_ReplayLoad },
  { 0x005186ceu, (re_fn_t)P74_ResetHud },
  { 0x0051879fu, (re_fn_t)P138_ReplayInit },
  { 0x005188ecu, (re_fn_t)P12_Fn005188EC },
  { 0x00518953u, (re_fn_t)P101_ReplayBegin },
  { 0x00518ab4u, (re_fn_t)P108_ReplayStep },
  { 0x00518bbcu, (re_fn_t)P138_LoadPads },
  { 0x00518d32u, (re_fn_t)P100_RecInput },
  { 0x00518f44u, (re_fn_t)P100_RecRead },
  { 0x005191c5u, (re_fn_t)P109_InputTick },
  { 0x005193d4u, (re_fn_t)CreditsTick005193D4 },
  { 0x00519408u, (re_fn_t)P139_ReplayEnd },
  { 0x00519647u, (re_fn_t)P139_SaveCfg },
  { 0x00519873u, (re_fn_t)P55_SaveRec },
  { 0x0051990au, (re_fn_t)P56_ReplayRead },
  { 0x005199bcu, (re_fn_t)P96_ReplayTag },
  { 0x00519a45u, (re_fn_t)P98_CamRecAdd },
  { 0x00519d09u, (re_fn_t)AddToCounter00519D09 },
  { 0x00519d1du, (re_fn_t)NoopFn00519d1d },
  { 0x00519d22u, (re_fn_t)ReturnOne00519D22 },
  { 0x00519d2cu, (re_fn_t)CreditsNext00519D2C },
  { 0x00519d70u, (re_fn_t)CreditsPrev00519D70 },
  { 0x00519ddbu, (re_fn_t)GlobalSet00519DDB },
  { 0x00519de7u, (re_fn_t)GlobalSet00519DE7 },
  { 0x00519df3u, (re_fn_t)ResetPalette00519DF3 },
  { 0x00519e23u, (re_fn_t)NoopFn00519e23 },
  { 0x00519e28u, (re_fn_t)NoopFn00519e28 },
  { 0x00519e2du, (re_fn_t)NoopFn00519e2d },
  { 0x00519e32u, (re_fn_t)NoopFn00519e32 },
  { 0x0051a750u, (re_fn_t)P102_RoadSide },
  { 0x0051aa5bu, (re_fn_t)P54_AllocRoadbits },
  { 0x0051aacdu, (re_fn_t)P54_FreeRoadbits },
  { 0x0051ab31u, (re_fn_t)P70_RowDecode },
  { 0x0051ac05u, (re_fn_t)P62_MapRow },
  { 0x0051acc5u, (re_fn_t)P100_RoadRect },
  { 0x0051aee6u, (re_fn_t)P100_RoadRectAbs },
  { 0x0051b111u, (re_fn_t)P72_RoadWord },
  { 0x0051b208u, (re_fn_t)P103_RoadNeighbour },
  { 0x0051b566u, (re_fn_t)P72_RoadDword },
  { 0x0051b65au, (re_fn_t)P72_RoadLookup },
  { 0x0051b7a3u, (re_fn_t)P99_RoadAtCar },
  { 0x0051b974u, (re_fn_t)P101_RoadNode },
  { 0x0051bcc0u, (re_fn_t)P17_SlotMapSide },
  { 0x0051bd09u, (re_fn_t)P17_SlotFindIndex },
  { 0x0051bd78u, (re_fn_t)GlobalSet0051BD78 },
  { 0x0051bd9cu, (re_fn_t)P14_Fn0051BD9C },
  { 0x0051be3cu, (re_fn_t)P58_BuildBlockIndex },
  { 0x0051bed5u, (re_fn_t)P14_Fn0051BED5 },
  { 0x0051bf82u, (re_fn_t)P73_RoadSides },
  { 0x0051c07au, (re_fn_t)P101_RoadBounds },
  { 0x0051c900u, (re_fn_t)P97_HsInit },
  { 0x0051caa7u, (re_fn_t)P76_LoadHsTables },
  { 0x0051cb98u, (re_fn_t)P62_SaveScores },
  { 0x0051cc55u, (re_fn_t)P64_RankPlace },
  { 0x0051cd43u, (re_fn_t)P42_GetHighScore },
  { 0x0051cdecu, (re_fn_t)P62_ScoreTable },
  { 0x0051ce94u, (re_fn_t)P64_RankTimeMore },
  { 0x0051cf17u, (re_fn_t)P64_RankBestFirst },
  { 0x0051cfdau, (re_fn_t)P64_RankTimeLess },
  { 0x0051d05du, (re_fn_t)P64_RankTimeB },
  { 0x0051d0e0u, (re_fn_t)P64_RankScoreB },
  { 0x0051d1a3u, (re_fn_t)P64_RankTop },
  { 0x0051d440u, (re_fn_t)P74_SkidInit },
  { 0x0051d51cu, (re_fn_t)P102_PlayerCorners },
  { 0x0051d811u, (re_fn_t)GlobalSet0051D811 },
  { 0x0051d8cau, (re_fn_t)P56_CopyBlock16 },
  { 0x0051d97eu, (re_fn_t)P101_WheelsGround },
  { 0x0051dc18u, (re_fn_t)P121_WheelDust },
  { 0x0051dd1bu, (re_fn_t)P117_SkidRecA },
  { 0x0051e1b7u, (re_fn_t)P117_SkidRecB },
  { 0x0051e65eu, (re_fn_t)P116_SkidsA },
  { 0x0051f376u, (re_fn_t)P116_SkidsB },
  { 0x0052008eu, (re_fn_t)P96_ShadowInit },
  { 0x00520278u, (re_fn_t)P138_CarShadow },
  { 0x00521f10u, (re_fn_t)P151_WinMain },
  { 0x005222cfu, (re_fn_t)P96_ResetDirector },
  { 0x00522306u, (re_fn_t)ResetDirector_00522306 },
  { 0x00522323u, (re_fn_t)Call00522323 },
  { 0x00522369u, (re_fn_t)P30_FatalError },
  { 0x005223beu, (re_fn_t)P30_InitWindowGlobals },
  { 0x005223dcu, (re_fn_t)P31_InitWindow },
  { 0x005224a8u, (re_fn_t)P31_WndProc },
  { 0x005226b5u, (re_fn_t)P55_GlideInit },
  { 0x0052273cu, (re_fn_t)P30_CrashInstall },
  { 0x0052274cu, (re_fn_t)P30_CrashRemove },
  { 0x005229f0u, (re_fn_t)P12_Fn005229F0 },
  { 0x00522a50u, (re_fn_t)P109_DropsDraw },
  { 0x00522d02u, (re_fn_t)P101_Drips },
  { 0x00522e64u, (re_fn_t)P68_RepeatCheck },
  { 0x00522f2au, (re_fn_t)ExchangeTable00522F2A },
  { 0x00522f4fu, (re_fn_t)P125_DropHit },
  { 0x005233a0u, (re_fn_t)StartAudio005233A0 },
  { 0x005233beu, (re_fn_t)P140_SndInit },
  { 0x00523595u, (re_fn_t)P48_SndShutdown },
  { 0x005235d3u, (re_fn_t)SoundSetFormat005235D3 },
  { 0x005235f2u, (re_fn_t)SoundSetVolA005235F2 },
  { 0x0052360du, (re_fn_t)SoundSetVolB0052360D },
  { 0x00523628u, (re_fn_t)P48_ResetAll },
  { 0x0052369bu, (re_fn_t)P48_SndPause },
  { 0x00523711u, (re_fn_t)P48_SetMasterVolume },
  { 0x005237b1u, (re_fn_t)P48_StopAll },
  { 0x00523829u, (re_fn_t)P115_SndUpdate },
  { 0x00523c56u, (re_fn_t)InitSoundVolumes_00523C56 },
  { 0x00523c99u, (re_fn_t)PushVec3_00523C99 },
  { 0x00523cdau, (re_fn_t)P97_SndStart },
  { 0x00523e07u, (re_fn_t)P48_FreeVoice },
  { 0x00523e50u, (re_fn_t)SoundPlay00523E50 },
  { 0x00523ec6u, (re_fn_t)P56_SetVoicePos },
  { 0x00523f8au, (re_fn_t)SoundSetPos00523F8A },
  { 0x00523ffdu, (re_fn_t)P48_SetVoiceVolume },
  { 0x005240d0u, (re_fn_t)P98_VoicePos },
  { 0x0052422du, (re_fn_t)SoundLoop_0052422D },
  { 0x005242a7u, (re_fn_t)SoundGetPos005242A7 },
  { 0x005242e7u, (re_fn_t)P48_GetVoiceVolume },
  { 0x0052432au, (re_fn_t)SlotSetOn0052432A },
  { 0x0052434au, (re_fn_t)SlotSetOff0052434A },
  { 0x0052436au, (re_fn_t)InitChannels_0052436A },
  { 0x00524398u, (re_fn_t)P43_CdFadeInit },
  { 0x005243ebu, (re_fn_t)P48_FadeEnd },
  { 0x00524473u, (re_fn_t)IsSlotActive00524473 },
  { 0x00524496u, (re_fn_t)P77_LoadBank },
  { 0x0052455fu, (re_fn_t)P68_ChangeSample },
  { 0x00524611u, (re_fn_t)P25_InitCDAudio },
  { 0x00524763u, (re_fn_t)P25_CDClose },
  { 0x0052479eu, (re_fn_t)P25_PlayCDTrack },
  { 0x00524873u, (re_fn_t)P25_CDStop },
  { 0x005248a0u, (re_fn_t)P25_CDStop },
  { 0x005248cdu, (re_fn_t)P25_CDResume },
  { 0x00524917u, (re_fn_t)P25_CDSetVolume },
  { 0x0052498eu, (re_fn_t)P109_SndPlay },
  { 0x00524b7eu, (re_fn_t)P48_FreeSample },
  { 0x00524bd8u, (re_fn_t)P140_BankLine },
  { 0x00524e22u, (re_fn_t)P58_ParseInt },
  { 0x00524ed1u, (re_fn_t)P68_ReadWords },
  { 0x00524f97u, (re_fn_t)P25_GetCDTOC },
  { 0x005250cbu, (re_fn_t)P21_AddMsf },
  { 0x00525900u, (re_fn_t)P44_ResetState },
  { 0x005259c8u, (re_fn_t)P102_CopTalk },
  { 0x00525cb7u, (re_fn_t)P12_Fn00525CB7 },
  { 0x00525e50u, (re_fn_t)LoadFsin_00525E50 },
  { 0x00525e7eu, (re_fn_t)P44_Atan2 },
  { 0x00526029u, (re_fn_t)Dot3_00526029 },
  { 0x0052605du, (re_fn_t)P43_Cross },
  { 0x005260d7u, (re_fn_t)P43_Normalize },
  { 0x0052614fu, (re_fn_t)MatIdentity3_0052614F },
  { 0x005261adu, (re_fn_t)P43_EulerMatrix },
  { 0x005262ccu, (re_fn_t)P44_EulerMatXYZ },
  { 0x00526365u, (re_fn_t)P44_EulerMatYXZ },
  { 0x005263feu, (re_fn_t)InitXform_005263FE },
  { 0x00526427u, (re_fn_t)P12_Fn00526427 },
  { 0x0052647du, (re_fn_t)P43_ProjectGrid },
  { 0x00526521u, (re_fn_t)P43_NormalizeToOut },
  { 0x00526582u, (re_fn_t)InitVec_00526582 },
  { 0x005265bcu, (re_fn_t)CopyVec3_005265BC },
  { 0x005265e3u, (re_fn_t)P43_Orthonormalize },
  { 0x005266edu, (re_fn_t)P44_LookAt },
  { 0x0052680bu, (re_fn_t)P43_PointInPoly },
  { 0x00526940u, (re_fn_t)P44_PointInQuad },
  { 0x00526a34u, (re_fn_t)P14_Fn00526A34 },
  { 0x00526aebu, (re_fn_t)P99_SegCross },
  { 0x00526cd5u, (re_fn_t)P99_SegClip },
  { 0x00526ed7u, (re_fn_t)P43_ClipT },
  { 0x00526f7eu, (re_fn_t)VecAdd3_00526F7E },
  { 0x00526fb6u, (re_fn_t)NegateVec3_00526FB6 },
  { 0x00526fe3u, (re_fn_t)NegateVec3To_00526FE3 },
  { 0x00527010u, (re_fn_t)P43_NormalizeCopy },
  { 0x005270bdu, (re_fn_t)Dot4_005270BD },
  { 0x005270f6u, (re_fn_t)NegateVec3_005270F6 },
  { 0x00527123u, (re_fn_t)VecNeg4_00527123 },
  { 0x0052715eu, (re_fn_t)VecAdd4_0052715E },
  { 0x005271a8u, (re_fn_t)VecSub4_005271A8 },
  { 0x005271f2u, (re_fn_t)P43_Len3 },
  { 0x00527255u, (re_fn_t)P43_Len4 },
  { 0x005272c6u, (re_fn_t)ResetVec_005272C6 },
  { 0x005272f2u, (re_fn_t)P44_QuatNormalize },
  { 0x005273a3u, (re_fn_t)P43_MatToQuat },
  { 0x00527429u, (re_fn_t)P43_QuatToMat },
  { 0x00527544u, (re_fn_t)P44_QuatMul },
  { 0x0052763bu, (re_fn_t)P44_EulerToQuat },
  { 0x00527746u, (re_fn_t)P44_AxisAngleMat },
  { 0x00527885u, (re_fn_t)Lerp4_00527885 },
  { 0x005278fbu, (re_fn_t)CopyShort9_005278FB },
  { 0x0052797au, (re_fn_t)CopyVec3_0052797A },
  { 0x005279a1u, (re_fn_t)LoadShort3FromPtr },
  { 0x005279cbu, (re_fn_t)RotVec_005279CB },
  { 0x005281b0u, (re_fn_t)P25_TimersInit },
  { 0x005281e1u, (re_fn_t)P25_TimersShutdown },
  { 0x00528221u, (re_fn_t)P25_TimerStart },
  { 0x00528293u, (re_fn_t)P25_TimerStop },
  { 0x005282e1u, (re_fn_t)P25_TimerCb },
  { 0x005283b5u, (re_fn_t)P44_Copy4 },
  { 0x005283e2u, (re_fn_t)InitFpuCw_005283E2 },
  { 0x0052840cu, (re_fn_t)P18_ClearFlag },
  { 0x00528455u, (re_fn_t)NoopFn00528455 },
  { 0x00528461u, (re_fn_t)P44_Transpose },
  { 0x005284acu, (re_fn_t)Mat3MulT_005284AC },
  { 0x0052859au, (re_fn_t)Mat3Mul_0052859A },
  { 0x00528688u, (re_fn_t)P44_RotX },
  { 0x00528788u, (re_fn_t)P44_RotY },
  { 0x00528885u, (re_fn_t)P44_RotZ },
  { 0x00528982u, (re_fn_t)P44_Xform },
  { 0x005289e2u, (re_fn_t)P44_XformT },
  { 0x00528a42u, (re_fn_t)P44_XformBias },
  { 0x00528ac8u, (re_fn_t)P85_Project },
  { 0x00528bb7u, (re_fn_t)P101_ProjT },
  { 0x00528c91u, (re_fn_t)P101_XformBias2 },
  { 0x00528d17u, (re_fn_t)P101_Proj },
  { 0x00528e12u, (re_fn_t)P17_ISqrt },
  { 0x00529140u, (re_fn_t)P65_BlitKeyed },
  { 0x00529190u, (re_fn_t)P65_BlitBlend },
  { 0x005291edu, (re_fn_t)P152_FillRows },
  { 0x00529253u, (re_fn_t)P101_Pal16 },
  { 0x005292d1u, (re_fn_t)P101_Pal32 },
  { 0x0052e400u, (re_fn_t)P30_Exit },
};
const size_t re_fn_table_n = sizeof re_fn_table / sizeof re_fn_table[0];
