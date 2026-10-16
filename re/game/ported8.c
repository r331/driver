#include "ported8.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P8_00b91c08, 0x00b91c08)
GAME_VAR_DEF(int32_t, P8_00b91c0c, 0x00b91c0c)
GAME_VAR_DEF(int32_t, P8_00b91c10, 0x00b91c10)
GAME_VAR_DEF(int32_t, P8_00b91c14, 0x00b91c14)
GAME_VAR_DEF(int32_t, P8_00b91c18, 0x00b91c18)
GAME_VAR_DEF(int32_t, P8_00b91c1c, 0x00b91c1c)
GAME_VAR_DEF(int32_t, P8_00d117f8, 0x00d117f8)
GAME_VAR_DEF(int32_t, P8_00d117fc, 0x00d117fc)
GAME_VAR_DEF(int32_t, P8_00d117e4, 0x00d117e4)
GAME_VAR_DEF(int32_t, P8_00d117ec, 0x00d117ec)
GAME_VAR_DEF(int32_t, P8_00d117e8, 0x00d117e8)
GAME_VAR_DEF(int32_t, P8_00d117f0, 0x00d117f0)
GAME_VAR_DEF(int32_t, P8_00d0fe1c, 0x00d0fe1c)
GAME_VAR_DEF(int32_t, P8_00b2c3b8, 0x00b2c3b8)
GAME_VAR_DEF(int32_t, P8_00d17b14, 0x00d17b14)
GAME_VAR_DEF(int32_t, P8_00b5a730, 0x00b5a730)
GAME_VAR_DEF(int32_t, P8_00b5a734, 0x00b5a734)
GAME_VAR_DEF(int32_t, P8_00575550, 0x00575550)
GAME_VAR_DEF(int32_t, P8_00575554, 0x00575554)
GAME_VAR_DEF(int32_t, P8_005f7e54, 0x005f7e54)
GAME_VAR_DEF(int32_t, P8_0054da10, 0x0054da10)
GAME_VAR_DEF(int32_t, P8_012710a0, 0x012710a0)
GAME_VAR_DEF(int32_t, P8_00b5a764, 0x00b5a764)
GAME_VAR_DEF(int32_t, P8_00b5a768, 0x00b5a768)
GAME_VAR_DEF(int32_t, P8_011171a4, 0x011171a4)
GAME_VAR_DEF(int32_t, P8_010ffd0c, 0x010ffd0c)
GAME_VAR_DEF(int32_t, P8_010fb0d0, 0x010fb0d0)
GAME_VAR_DEF(int32_t, P8_005536ac, 0x005536ac)
GAME_VAR_DEF(int32_t, P8_00b93e48, 0x00b93e48)
GAME_VAR_DEF(int32_t, P8_00b93e4c, 0x00b93e4c)
GAME_VAR_DEF(int32_t, P8_00b93e50, 0x00b93e50)
GAME_VAR_DEF(int32_t, P8_00b93e6c, 0x00b93e6c)
GAME_VAR_DEF(int32_t, P8_00b93e70, 0x00b93e70)
GAME_VAR_DEF(int32_t, P8_00b93e74, 0x00b93e74)
GAME_VAR_DEF(int32_t, P8_005feee8, 0x005feee8)
GAME_VAR_DEF(int32_t, P8_005feeec, 0x005feeec)
GAME_VAR_DEF(float, P8_00546020, 0x00546020)
GAME_VAR_DEF(float, P8_00546034, 0x00546034)
GAME_VAR_DEF(float, P8_00a4217c, 0x00a4217c)
GAME_VAR_DEF(float, P8_00546024, 0x00546024)
GAME_VAR_DEF(float, P8_00546078, 0x00546078)
GAME_VAR_DEF(float, P8_00546884, 0x00546884)
GAME_VAR_DEF(float, P8_00d164e4, 0x00d164e4)
GAME_VAR_DEF(float, P8_00d17af4, 0x00d17af4)
GAME_VAR_DEF(float, P8_00d17b24, 0x00d17b24)
GAME_VAR_DEF(float, P8_00d17b2c, 0x00d17b2c)
GAME_VAR_DEF(g8_bytes_t, P8_0054E834, 0x0054e834)
GAME_VAR_DEF(g8_bytes_t, P8_005536EC, 0x005536ec)
uint32_t IsFlagSetNotMasked_004E383A(uint32_t i) { i &= 0xff; return (A_00D04B00[i] == 0 || A_00D04B00[0x100 + i] != 0) ? 0 : 1; }
void NoopFn004F89EB(void) { }
void StepSpeedA_004B9E2B(uint8_t *p) { float f; int32_t a, b; memcpy(&f, p + 4, 4); f -= P8_00546020; memcpy(p + 4, &f, 4); memcpy(&a, p + 0x50, 4); memcpy(&b, p + 0x60, 4); a += b; memcpy(p + 0x50, &a, 4); }
void StepSpeedB_004B9E54(uint8_t *p) { float f; int32_t a, b; uint16_t m; memcpy(&f, p + 4, 4); f -= P8_00546034; memcpy(p + 4, &f, 4); memcpy(&m, p + 100, 2); memcpy(&a, p + 0x50, 4); memcpy(&b, p + 0x60, 4); a = (m < 5) ? a - b : a + b; memcpy(p + 0x50, &a, 4); }
void InitSlotsTable_004AB0DF(void) { for (int32_t i = 0; i < 8; i++) memcpy(&P8_005536EC[i*0x1c], &P8_011171a4, 4); P8_005536ac = P8_010ffd0c; P8_010fb0d0 = 0x40; }
void PushVec3_00523C99(int32_t a, int32_t b, int32_t c) { P8_00b91c14 = P8_00b91c08; P8_00b91c18 = P8_00b91c0c; P8_00b91c1c = P8_00b91c10; P8_00b91c08 = a; P8_00b91c0c = b; P8_00b91c10 = c; }
void SetDrawParams_004D9539(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) { P8_00d117f8 = b; P8_00d117fc = c; P8_00d117e4 = d; P8_00d117ec = e; P8_00d0fe1c = a; P8_00d117e8 = 0; P8_00d117f0 = 0x20000; P8_00b2c3b8 = 1; }
void SetMode4_00510382(void) { if (P8_00b5a768 == 0) { P8_00b5a734 = P8_00b5a730; P8_00575554 = P8_00575550; P8_00b5a730 = 0x5754d8; P8_00575550 = 2; P8_005f7e54 = 4; } }
void SetMode1_00510448(void) { if (P8_00b5a764 == 0) P8_012710a0 = 0; P8_00b5a734 = P8_00b5a730; P8_00575554 = P8_00575550; P8_00b5a730 = 0x5754d8; P8_00575550 = 2; P8_005f7e54 = 1; P8_0054da10 = 0; }
void SetMode1b_005106D2(void) { if (P8_00b5a764 == 0) P8_012710a0 = 0; P8_00b5a734 = P8_00b5a730; P8_00575554 = P8_00575550; P8_00b5a730 = 0x5754d8; P8_00575550 = 2; P8_005f7e54 = 1; P8_0054da10 = 1; }
void Mat3MulT_005284AC(const float *a, const float *b, float *o) {
  o[0] = a[2]*b[6] + a[1]*b[3] + a[0]*b[0]; o[3] = a[5]*b[6] + a[4]*b[3] + a[3]*b[0]; o[6] = a[8]*b[6] + a[7]*b[3] + a[6]*b[0];
  o[1] = a[2]*b[7] + a[1]*b[4] + a[0]*b[1]; o[4] = a[5]*b[7] + a[4]*b[4] + a[3]*b[1]; o[7] = a[8]*b[7] + a[7]*b[4] + a[6]*b[1];
  o[2] = a[2]*b[8] + a[1]*b[5] + a[0]*b[2]; o[5] = a[5]*b[8] + a[4]*b[5] + a[3]*b[2]; o[8] = a[8]*b[8] + a[7]*b[5] + a[6]*b[2]; }
void Mat3Mul_0052859A(const float *a, const float *b, float *o) {
  o[0] = a[2]*b[6] + a[1]*b[3] + a[0]*b[0]; o[1] = a[5]*b[6] + a[4]*b[3] + a[3]*b[0]; o[2] = a[8]*b[6] + a[7]*b[3] + a[6]*b[0];
  o[3] = a[2]*b[7] + a[1]*b[4] + a[0]*b[1]; o[4] = a[5]*b[7] + a[4]*b[4] + a[3]*b[1]; o[5] = a[8]*b[7] + a[7]*b[4] + a[6]*b[1];
  o[6] = a[2]*b[8] + a[1]*b[5] + a[0]*b[2]; o[7] = a[5]*b[8] + a[4]*b[5] + a[3]*b[2]; o[8] = a[8]*b[8] + a[7]*b[5] + a[6]*b[2]; }
void RotVec_005279CB(int32_t *o) {
  int16_t m[9]; memcpy(m, &A_00B93E58[0], 18);
  o[0] = P8_00b93e6c + ((m[0]*P8_00b93e48 + m[1]*P8_00b93e4c + 0x800 + m[2]*P8_00b93e50) >> 12);
  o[1] = P8_00b93e70 + ((m[3]*P8_00b93e48 + m[4]*P8_00b93e4c + 0x800 + m[5]*P8_00b93e50) >> 12);
  o[2] = P8_00b93e74 + ((m[6]*P8_00b93e48 + m[7]*P8_00b93e4c + 0x800 + m[8]*P8_00b93e50) >> 12); }
void RedMarkers_0041ADA1(void) { if (P8_005feee8 != -1) { int32_t k = P8_005feeec; for (int32_t j = 1; j <= 2; j++) { uint8_t *q = &P8_0054E834[(k*2+j)*0x10]; q[0] = 0xff; q[1] = 0; q[2] = 0; } } }
void SetScaled_004CB097(const float *p, float v) { P8_00d17b14 = 0; P8_00d164e4 = (p[0] - P8_005507d0) * P8_00546884; P8_00d17af4 = (p[1] - P8_005507d4) * P8_00546884; P8_00d17b24 = (p[2] - P8_005507d8) * P8_00546884; P8_00d17b2c = (v - P8_01251a68) * P8_00546884; }
void SetZoom_00421CAB(int16_t v) { if (v == 0) { P8_00a4217c = 0.0f; } else { P8_00a4217c = (float)v; if (P8_00a4217c < P8_00546024) P8_00a4217c = P8_00a4217c * P8_00546078; } }
