/* Партия v0.42 */
#pragma once
#include "gvar.h"
typedef uint8_t g8_bytes_t[0x40000];
#define A_005D57AE GAME_VAR(g8_bytes_t, A_005D57AE, 0x005d57ae)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_005D57AE") /*gvi*/
#undef A_005D57AE /*gvi*/
extern g8_bytes_t A_005D57AE;
#pragma pop_macro("A_005D57AE") /*gvi*/
#endif
#define A_0054DFC5 GAME_VAR(g8_bytes_t, A_0054DFC5, 0x0054dfc5)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_0054DFC5") /*gvi*/
#undef A_0054DFC5 /*gvi*/
extern g8_bytes_t A_0054DFC5;
#pragma pop_macro("A_0054DFC5") /*gvi*/
#endif
#define A_006017C0 GAME_VAR(g8_bytes_t, A_006017C0, 0x006017c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_006017C0") /*gvi*/
#undef A_006017C0 /*gvi*/
extern g8_bytes_t A_006017C0;
#pragma pop_macro("A_006017C0") /*gvi*/
#endif
#define G8_00A4217C GAME_VAR(int32_t, G8_00A4217C, 0x00a4217c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00A4217C") /*gvi*/
#undef G8_00A4217C /*gvi*/
extern int32_t G8_00A4217C;
#pragma pop_macro("G8_00A4217C") /*gvi*/
#endif
#define G8_011EFFE4 GAME_VAR(int32_t, G8_011EFFE4, 0x011effe4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_011EFFE4") /*gvi*/
#undef G8_011EFFE4 /*gvi*/
extern int32_t G8_011EFFE4;
#pragma pop_macro("G8_011EFFE4") /*gvi*/
#endif
#define A_012083C0 GAME_VAR(g8_bytes_t, A_012083C0, 0x012083c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_012083C0") /*gvi*/
#undef A_012083C0 /*gvi*/
extern g8_bytes_t A_012083C0;
#pragma pop_macro("A_012083C0") /*gvi*/
#endif
#define A_01146F20 GAME_VAR(g8_bytes_t, A_01146F20, 0x01146f20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_01146F20") /*gvi*/
#undef A_01146F20 /*gvi*/
extern g8_bytes_t A_01146F20;
#pragma pop_macro("A_01146F20") /*gvi*/
#endif
#ifdef RE_HOOK_BUILD
#define A_011443E0 GAME_VAR(g8_bytes_t, A_011443E0, 0x011443e0)
#else
#pragma push_macro("TrafficRecs") /*gvi*/
#undef TrafficRecs /*gvi*/
extern uint8_t TrafficRecs[0x40 * 0x54];   /* v1.47: одна таблица трафика (director.h) */
#pragma pop_macro("TrafficRecs") /*gvi*/
#define A_011443E0 ((uint8_t *)re_gvar(0x011443e0u, 0x40 * 0x54, (void *)TrafficRecs))   /* v2.11: через образ данных (re_gvar), иначе — отдельный native-объект */
#endif
#define G8_00575EE4 GAME_VAR(int32_t, G8_00575EE4, 0x00575ee4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00575EE4") /*gvi*/
#undef G8_00575EE4 /*gvi*/
extern int32_t G8_00575EE4;
#pragma pop_macro("G8_00575EE4") /*gvi*/
#endif
#define A_01134540 GAME_VAR(g8_bytes_t, A_01134540, 0x01134540)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_01134540") /*gvi*/
#undef A_01134540 /*gvi*/
extern g8_bytes_t A_01134540;
#pragma pop_macro("A_01134540") /*gvi*/
#endif
#define A_010F51C8 GAME_VAR(g8_bytes_t, A_010F51C8, 0x010f51c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_010F51C8") /*gvi*/
#undef A_010F51C8 /*gvi*/
extern g8_bytes_t A_010F51C8;
#pragma pop_macro("A_010F51C8") /*gvi*/
#endif
#define A_010EA8A0 GAME_VAR(g8_bytes_t, A_010EA8A0, 0x010ea8a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_010EA8A0") /*gvi*/
#undef A_010EA8A0 /*gvi*/
extern g8_bytes_t A_010EA8A0;
#pragma pop_macro("A_010EA8A0") /*gvi*/
#endif
#define G8_0110E144 GAME_VAR(int32_t, G8_0110E144, 0x0110e144)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_0110E144") /*gvi*/
#undef G8_0110E144 /*gvi*/
extern int32_t G8_0110E144;
#pragma pop_macro("G8_0110E144") /*gvi*/
#endif
#define A_0110B040 GAME_VAR(g8_bytes_t, A_0110B040, 0x0110b040)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_0110B040") /*gvi*/
#undef A_0110B040 /*gvi*/
extern g8_bytes_t A_0110B040;
#pragma pop_macro("A_0110B040") /*gvi*/
#endif
#define A_0110E2E0 GAME_VAR(g8_bytes_t, A_0110E2E0, 0x0110e2e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_0110E2E0") /*gvi*/
#undef A_0110E2E0 /*gvi*/
extern g8_bytes_t A_0110E2E0;
#pragma pop_macro("A_0110E2E0") /*gvi*/
#endif
#define A_011171C0 GAME_VAR(g8_bytes_t, A_011171C0, 0x011171c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_011171C0") /*gvi*/
#undef A_011171C0 /*gvi*/
extern g8_bytes_t A_011171C0;
#pragma pop_macro("A_011171C0") /*gvi*/
#endif
#define A_01123302 GAME_VAR(g8_bytes_t, A_01123302, 0x01123302)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_01123302") /*gvi*/
#undef A_01123302 /*gvi*/
extern g8_bytes_t A_01123302;
#pragma pop_macro("A_01123302") /*gvi*/
#endif
#define A_010FFB60 GAME_VAR(g8_bytes_t, A_010FFB60, 0x010ffb60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_010FFB60") /*gvi*/
#undef A_010FFB60 /*gvi*/
extern g8_bytes_t A_010FFB60;
#pragma pop_macro("A_010FFB60") /*gvi*/
#endif
#define G8_0110B024 GAME_VAR(int32_t, G8_0110B024, 0x0110b024)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_0110B024") /*gvi*/
#undef G8_0110B024 /*gvi*/
extern int32_t G8_0110B024;
#pragma pop_macro("G8_0110B024") /*gvi*/
#endif
#define A_010EA620 GAME_VAR(g8_bytes_t, A_010EA620, 0x010ea620)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_010EA620") /*gvi*/
#undef A_010EA620 /*gvi*/
extern g8_bytes_t A_010EA620;
#pragma pop_macro("A_010EA620") /*gvi*/
#endif
#define A_010DE120 GAME_VAR(g8_bytes_t, A_010DE120, 0x010de120)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_010DE120") /*gvi*/
#undef A_010DE120 /*gvi*/
extern g8_bytes_t A_010DE120;
#pragma pop_macro("A_010DE120") /*gvi*/
#endif
#define G8_00DBB450 GAME_VAR(int32_t, G8_00DBB450, 0x00dbb450)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00DBB450") /*gvi*/
#undef G8_00DBB450 /*gvi*/
extern int32_t G8_00DBB450;
#pragma pop_macro("G8_00DBB450") /*gvi*/
#endif
#define A_00D132C0 GAME_VAR(g8_bytes_t, A_00D132C0, 0x00d132c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00D132C0") /*gvi*/
#undef A_00D132C0 /*gvi*/
extern g8_bytes_t A_00D132C0;
#pragma pop_macro("A_00D132C0") /*gvi*/
#endif
#define G8_00D17B0C GAME_VAR(int32_t, G8_00D17B0C, 0x00d17b0c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00D17B0C") /*gvi*/
#undef G8_00D17B0C /*gvi*/
extern int32_t G8_00D17B0C;
#pragma pop_macro("G8_00D17B0C") /*gvi*/
#endif
#define A_00B20330 GAME_VAR(g8_bytes_t, A_00B20330, 0x00b20330)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00B20330") /*gvi*/
#undef A_00B20330 /*gvi*/
extern g8_bytes_t A_00B20330;
#pragma pop_macro("A_00B20330") /*gvi*/
#endif
#define G8_00B20344 GAME_VAR(int32_t, G8_00B20344, 0x00b20344)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B20344") /*gvi*/
#undef G8_00B20344 /*gvi*/
extern int32_t G8_00B20344;
#pragma pop_macro("G8_00B20344") /*gvi*/
#endif
#define A_00B20310 GAME_VAR(g8_bytes_t, A_00B20310, 0x00b20310)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00B20310") /*gvi*/
#undef A_00B20310 /*gvi*/
extern g8_bytes_t A_00B20310;
#pragma pop_macro("A_00B20310") /*gvi*/
#endif
#define A_00D11830 GAME_VAR(g8_bytes_t, A_00D11830, 0x00d11830)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00D11830") /*gvi*/
#undef A_00D11830 /*gvi*/
extern g8_bytes_t A_00D11830;
#pragma pop_macro("A_00D11830") /*gvi*/
#endif
#define G8_00B20368 GAME_VAR(int32_t, G8_00B20368, 0x00b20368)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B20368") /*gvi*/
#undef G8_00B20368 /*gvi*/
extern int32_t G8_00B20368;
#pragma pop_macro("G8_00B20368") /*gvi*/
#endif
#define G8_00B2034C GAME_VAR(int32_t, G8_00B2034C, 0x00b2034c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B2034C") /*gvi*/
#undef G8_00B2034C /*gvi*/
extern int32_t G8_00B2034C;
#pragma pop_macro("G8_00B2034C") /*gvi*/
#endif
#define G8_00D118C0 GAME_VAR(int32_t, G8_00D118C0, 0x00d118c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00D118C0") /*gvi*/
#undef G8_00D118C0 /*gvi*/
extern int32_t G8_00D118C0;
#pragma pop_macro("G8_00D118C0") /*gvi*/
#endif
#define G8_00B87EAC GAME_VAR(int32_t, G8_00B87EAC, 0x00b87eac)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B87EAC") /*gvi*/
#undef G8_00B87EAC /*gvi*/
extern int32_t G8_00B87EAC;
#pragma pop_macro("G8_00B87EAC") /*gvi*/
#endif
#define G8_00B87EB0 GAME_VAR(int32_t, G8_00B87EB0, 0x00b87eb0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B87EB0") /*gvi*/
#undef G8_00B87EB0 /*gvi*/
extern int32_t G8_00B87EB0;
#pragma pop_macro("G8_00B87EB0") /*gvi*/
#endif
#define G8_00D11800 GAME_VAR(int32_t, G8_00D11800, 0x00d11800)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00D11800") /*gvi*/
#undef G8_00D11800 /*gvi*/
extern int32_t G8_00D11800;
#pragma pop_macro("G8_00D11800") /*gvi*/
#endif
#define G8_00D10E40 GAME_VAR(int32_t, G8_00D10E40, 0x00d10e40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00D10E40") /*gvi*/
#undef G8_00D10E40 /*gvi*/
extern int32_t G8_00D10E40;
#pragma pop_macro("G8_00D10E40") /*gvi*/
#endif
#define A_00D04B00 GAME_VAR(g8_bytes_t, A_00D04B00, 0x00d04b00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00D04B00") /*gvi*/
#undef A_00D04B00 /*gvi*/
extern g8_bytes_t A_00D04B00;
#pragma pop_macro("A_00D04B00") /*gvi*/
#endif
#define A_00D044E0 GAME_VAR(g8_bytes_t, A_00D044E0, 0x00d044e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00D044E0") /*gvi*/
#undef A_00D044E0 /*gvi*/
extern g8_bytes_t A_00D044E0;
#pragma pop_macro("A_00D044E0") /*gvi*/
#endif
#define A_00C8198C GAME_VAR(g8_bytes_t, A_00C8198C, 0x00c8198c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00C8198C") /*gvi*/
#undef A_00C8198C /*gvi*/
extern g8_bytes_t A_00C8198C;
#pragma pop_macro("A_00C8198C") /*gvi*/
#endif
#define G8_00B91CF4 GAME_VAR(int32_t, G8_00B91CF4, 0x00b91cf4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00B91CF4") /*gvi*/
#undef G8_00B91CF4 /*gvi*/
extern int32_t G8_00B91CF4;
#pragma pop_macro("G8_00B91CF4") /*gvi*/
#endif
#define G8_00575F40 GAME_VAR(int32_t, G8_00575F40, 0x00575f40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00575F40") /*gvi*/
#undef G8_00575F40 /*gvi*/
extern int32_t G8_00575F40;
#pragma pop_macro("G8_00575F40") /*gvi*/
#endif
#define A_00BDC2A0 GAME_VAR(g8_bytes_t, A_00BDC2A0, 0x00bdc2a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00BDC2A0") /*gvi*/
#undef A_00BDC2A0 /*gvi*/
extern g8_bytes_t A_00BDC2A0;
#pragma pop_macro("A_00BDC2A0") /*gvi*/
#endif
#define A_00B93E58 GAME_VAR(g8_bytes_t, A_00B93E58, 0x00b93e58)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00B93E58") /*gvi*/
#undef A_00B93E58 /*gvi*/
extern g8_bytes_t A_00B93E58;
#pragma pop_macro("A_00B93E58") /*gvi*/
#endif
#define G8_00C56710 GAME_VAR(int32_t, G8_00C56710, 0x00c56710)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_00C56710") /*gvi*/
#undef G8_00C56710 /*gvi*/
extern int32_t G8_00C56710;
#pragma pop_macro("G8_00C56710") /*gvi*/
#endif
#define A_00C56780 GAME_VAR(g8_bytes_t, A_00C56780, 0x00c56780)
#ifndef RE_HOOK_BUILD
#pragma push_macro("A_00C56780") /*gvi*/
#undef A_00C56780 /*gvi*/
extern g8_bytes_t A_00C56780;
#pragma pop_macro("A_00C56780") /*gvi*/
#endif
#define G8_0057A0E2_u16 GAME_VAR(uint16_t, G8_0057A0E2_u16, 0x0057a0e2)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_0057A0E2_u16") /*gvi*/
#undef G8_0057A0E2_u16 /*gvi*/
extern uint16_t G8_0057A0E2_u16;
#pragma pop_macro("G8_0057A0E2_u16") /*gvi*/
#endif
#define G8_0057A0E0_u16 GAME_VAR(uint16_t, G8_0057A0E0_u16, 0x0057a0e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G8_0057A0E0_u16") /*gvi*/
#undef G8_0057A0E0_u16 /*gvi*/
extern uint16_t G8_0057A0E0_u16;
#pragma pop_macro("G8_0057A0E0_u16") /*gvi*/
#endif
uint8_t ScanSlot_0040AAE2(int32_t p);
void SetHiliteBits_0041621C(int32_t a, int32_t c);
void InitIdentityPalette_0041D8E9(void);
int32_t MaskShift_00421C1D(uint32_t m);
void AddEntry_00426ABC(const uint32_t *p, uint32_t w, int32_t a, int32_t c, int32_t d);
int32_t FindFreeEven_0048A4E6(void);
int32_t CountByOwner_0048F2E7(int32_t owner);
int32_t FindSlot_004A2DB5(int32_t a, int32_t c);
const uint8_t *SkipToIdentStart_004A596B(const uint8_t *p);
void FillThresholds_004A6370(uint8_t *p);
void ResetSlots_004AB712(void);
void ClearTables_004AB780(void);
int32_t FindOrAdd_004BB11F(int32_t id);
void ClearEntry_004BF8A1(int32_t id);
void AddUnique_004C1F9B(int32_t id);
void PushEntry_004CC784(const uint32_t *p, uint8_t a, uint8_t c);
void SetFirstFree_004D6190(int32_t v);
void CopyTable_004D6E9F(void);
uint32_t Rand_004D9078(void);
int32_t AnyKeyHeld_004E3871(void);
void PushHistory_004E5938(int32_t v);
void SetObjState_00514C72(uint8_t *p, uint16_t a, uint32_t c, uint32_t d, uint32_t e);
void InitObjState_00514BC7(uint8_t *p, int32_t mode, uint32_t arg);
void ResetObjState_00514E99(uint8_t *p);
void InitSoundVolumes_00523C56(void);
void SoundLoop_0052422D(int32_t i, int32_t v);
void Lerp4_00527885(const float *a, const float *c, float t, float *o);
void CopyShort9_005278FB(const int16_t *p);
long double Dot4_005270BD(const float *a, const float *c);
void CountActive_005120A7(void);
void InitFpuCw_005283E2(void);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef A_005D57AE
#define A_005D57AE (*(g8_bytes_t *)re_gvar(0x005d57aeu, sizeof(g8_bytes_t), (void *)&A_005D57AE))
#undef A_0054DFC5
#define A_0054DFC5 (*(g8_bytes_t *)re_gvar(0x0054dfc5u, sizeof(g8_bytes_t), (void *)&A_0054DFC5))
#undef A_006017C0
#define A_006017C0 (*(g8_bytes_t *)re_gvar(0x006017c0u, sizeof(g8_bytes_t), (void *)&A_006017C0))
#undef G8_00A4217C
#define G8_00A4217C (*(int32_t *)re_gvar(0x00a4217cu, sizeof(int32_t), (void *)&G8_00A4217C))
#undef G8_011EFFE4
#define G8_011EFFE4 (*(int32_t *)re_gvar(0x011effe4u, sizeof(int32_t), (void *)&G8_011EFFE4))
#undef A_012083C0
#define A_012083C0 (*(g8_bytes_t *)re_gvar(0x012083c0u, sizeof(g8_bytes_t), (void *)&A_012083C0))
#undef A_01146F20
#define A_01146F20 (*(g8_bytes_t *)re_gvar(0x01146f20u, sizeof(g8_bytes_t), (void *)&A_01146F20))
#undef G8_00575EE4
#define G8_00575EE4 (*(int32_t *)re_gvar(0x00575ee4u, sizeof(int32_t), (void *)&G8_00575EE4))
#undef A_01134540
#define A_01134540 (*(g8_bytes_t *)re_gvar(0x01134540u, sizeof(g8_bytes_t), (void *)&A_01134540))
#undef A_010F51C8
#define A_010F51C8 (*(g8_bytes_t *)re_gvar(0x010f51c8u, sizeof(g8_bytes_t), (void *)&A_010F51C8))
#undef A_010EA8A0
#define A_010EA8A0 (*(g8_bytes_t *)re_gvar(0x010ea8a0u, sizeof(g8_bytes_t), (void *)&A_010EA8A0))
#undef G8_0110E144
#define G8_0110E144 (*(int32_t *)re_gvar(0x0110e144u, sizeof(int32_t), (void *)&G8_0110E144))
#undef A_0110B040
#define A_0110B040 (*(g8_bytes_t *)re_gvar(0x0110b040u, sizeof(g8_bytes_t), (void *)&A_0110B040))
#undef A_0110E2E0
#define A_0110E2E0 (*(g8_bytes_t *)re_gvar(0x0110e2e0u, sizeof(g8_bytes_t), (void *)&A_0110E2E0))
#undef A_011171C0
#define A_011171C0 (*(g8_bytes_t *)re_gvar(0x011171c0u, sizeof(g8_bytes_t), (void *)&A_011171C0))
#undef A_01123302
#define A_01123302 (*(g8_bytes_t *)re_gvar(0x01123302u, sizeof(g8_bytes_t), (void *)&A_01123302))
#undef A_010FFB60
#define A_010FFB60 (*(g8_bytes_t *)re_gvar(0x010ffb60u, sizeof(g8_bytes_t), (void *)&A_010FFB60))
#undef G8_0110B024
#define G8_0110B024 (*(int32_t *)re_gvar(0x0110b024u, sizeof(int32_t), (void *)&G8_0110B024))
#undef A_010EA620
#define A_010EA620 (*(g8_bytes_t *)re_gvar(0x010ea620u, sizeof(g8_bytes_t), (void *)&A_010EA620))
#undef A_010DE120
#define A_010DE120 (*(g8_bytes_t *)re_gvar(0x010de120u, sizeof(g8_bytes_t), (void *)&A_010DE120))
#undef G8_00DBB450
#define G8_00DBB450 (*(int32_t *)re_gvar(0x00dbb450u, sizeof(int32_t), (void *)&G8_00DBB450))
#undef A_00D132C0
#define A_00D132C0 (*(g8_bytes_t *)re_gvar(0x00d132c0u, sizeof(g8_bytes_t), (void *)&A_00D132C0))
#undef G8_00D17B0C
#define G8_00D17B0C (*(int32_t *)re_gvar(0x00d17b0cu, sizeof(int32_t), (void *)&G8_00D17B0C))
#undef A_00B20330
#define A_00B20330 (*(g8_bytes_t *)re_gvar(0x00b20330u, sizeof(g8_bytes_t), (void *)&A_00B20330))
#undef G8_00B20344
#define G8_00B20344 (*(int32_t *)re_gvar(0x00b20344u, sizeof(int32_t), (void *)&G8_00B20344))
#undef A_00B20310
#define A_00B20310 (*(g8_bytes_t *)re_gvar(0x00b20310u, sizeof(g8_bytes_t), (void *)&A_00B20310))
#undef A_00D11830
#define A_00D11830 (*(g8_bytes_t *)re_gvar(0x00d11830u, sizeof(g8_bytes_t), (void *)&A_00D11830))
#undef G8_00B20368
#define G8_00B20368 (*(int32_t *)re_gvar(0x00b20368u, sizeof(int32_t), (void *)&G8_00B20368))
#undef G8_00B2034C
#define G8_00B2034C (*(int32_t *)re_gvar(0x00b2034cu, sizeof(int32_t), (void *)&G8_00B2034C))
#undef G8_00D118C0
#define G8_00D118C0 (*(int32_t *)re_gvar(0x00d118c0u, sizeof(int32_t), (void *)&G8_00D118C0))
#undef G8_00B87EAC
#define G8_00B87EAC (*(int32_t *)re_gvar(0x00b87eacu, sizeof(int32_t), (void *)&G8_00B87EAC))
#undef G8_00B87EB0
#define G8_00B87EB0 (*(int32_t *)re_gvar(0x00b87eb0u, sizeof(int32_t), (void *)&G8_00B87EB0))
#undef G8_00D11800
#define G8_00D11800 (*(int32_t *)re_gvar(0x00d11800u, sizeof(int32_t), (void *)&G8_00D11800))
#undef G8_00D10E40
#define G8_00D10E40 (*(int32_t *)re_gvar(0x00d10e40u, sizeof(int32_t), (void *)&G8_00D10E40))
#undef A_00D04B00
#define A_00D04B00 (*(g8_bytes_t *)re_gvar(0x00d04b00u, sizeof(g8_bytes_t), (void *)&A_00D04B00))
#undef A_00D044E0
#define A_00D044E0 (*(g8_bytes_t *)re_gvar(0x00d044e0u, sizeof(g8_bytes_t), (void *)&A_00D044E0))
#undef A_00C8198C
#define A_00C8198C (*(g8_bytes_t *)re_gvar(0x00c8198cu, sizeof(g8_bytes_t), (void *)&A_00C8198C))
#undef G8_00B91CF4
#define G8_00B91CF4 (*(int32_t *)re_gvar(0x00b91cf4u, sizeof(int32_t), (void *)&G8_00B91CF4))
#undef G8_00575F40
#define G8_00575F40 (*(int32_t *)re_gvar(0x00575f40u, sizeof(int32_t), (void *)&G8_00575F40))
#undef A_00BDC2A0
#define A_00BDC2A0 (*(g8_bytes_t *)re_gvar(0x00bdc2a0u, sizeof(g8_bytes_t), (void *)&A_00BDC2A0))
#undef A_00B93E58
#define A_00B93E58 (*(g8_bytes_t *)re_gvar(0x00b93e58u, sizeof(g8_bytes_t), (void *)&A_00B93E58))
#undef G8_00C56710
#define G8_00C56710 (*(int32_t *)re_gvar(0x00c56710u, sizeof(int32_t), (void *)&G8_00C56710))
#undef A_00C56780
#define A_00C56780 (*(g8_bytes_t *)re_gvar(0x00c56780u, sizeof(g8_bytes_t), (void *)&A_00C56780))
#undef G8_0057A0E2_u16
#define G8_0057A0E2_u16 (*(uint16_t *)re_gvar(0x0057a0e2u, sizeof(uint16_t), (void *)&G8_0057A0E2_u16))
#undef G8_0057A0E0_u16
#define G8_0057A0E0_u16 (*(uint16_t *)re_gvar(0x0057a0e0u, sizeof(uint16_t), (void *)&G8_0057A0E0_u16))
#endif
/* gvar-img v2.03 end */
