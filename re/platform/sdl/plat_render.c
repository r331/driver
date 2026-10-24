/* plat_render.c — native only: the OpenGL 3.3 core render backend (English overview; original notes follow).
   The game sends already-transformed vertices (like D3D TLVERTEX: x, y in window pixels, z 0..1, rhw = 1/w);
   the shader restores perspective-correct interpolation.  GL entry points are loaded through get_proc
   (SDL_GL_GetProcAddress or OSMesaGetProcAddress), without linking libGL.
   Sections: frame/content rectangles and Hor+ (v2.15/v2.26), GL state, render target FBO / MSAA / post pass
   (v2.16), facade detail meshes (v2.31), textures with alpha-test variants and mipmaps, drawing, clears,
   self-check against a black frame (v2.24), flip and readback.
   No Game.exe addresses here: this file implements the plat_* interface used by the ported code. */
/* Рендер-бэкенд OpenGL 3.3 core. Игра шлёт уже преобразованные вершины (как D3D TLVERTEX):
   x,y — пиксели окна, z 0..1, rhw = 1/w; шейдер восстанавливает перспективно-корректные интерполяции.
   GL-функции берутся через get_proc (SDL_GL_GetProcAddress или OSMesaGetProcAddress), без линковки с libGL. */
#include "../plat.h"
#include "../../game/aspect.h"
#include "../native/diagnostics.h"
#include "plat_gfx.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned int GLenum, GLuint, GLbitfield;
typedef int GLint, GLsizei;
typedef unsigned char GLboolean;
typedef char GLchar;
typedef float GLfloat;
typedef ptrdiff_t GLsizeiptr;
enum {
    GL_DEPTH_TEST = 0x0B71, GL_BLEND = 0x0BE2, GL_CULL_FACE = 0x0B44, GL_TEXTURE_2D = 0x0DE1, GL_LEQUAL = 0x0203, GL_ALWAYS = 0x0207,
    GL_COLOR_BUFFER_BIT = 0x4000, GL_DEPTH_BUFFER_BIT = 0x0100, GL_RGBA = 0x1908, GL_UNSIGNED_BYTE = 0x1401, GL_FLOAT = 0x1406,
    GL_TEXTURE_MIN_FILTER = 0x2801, GL_TEXTURE_MAG_FILTER = 0x2800, GL_TEXTURE_WRAP_S = 0x2802, GL_TEXTURE_WRAP_T = 0x2803,
    GL_NEAREST = 0x2600, GL_LINEAR = 0x2601, GL_REPEAT = 0x2901, GL_CLAMP_TO_EDGE = 0x812F, GL_TEXTURE0 = 0x84C0,
    GL_ARRAY_BUFFER = 0x8892, GL_STREAM_DRAW = 0x88E0, GL_TRIANGLES = 0x0004, GL_LINES = 0x0001, GL_VERTEX_SHADER = 0x8B31, GL_FRAGMENT_SHADER = 0x8B30,
    GL_COMPILE_STATUS = 0x8B81, GL_LINK_STATUS = 0x8B82, GL_INFO_LOG_LENGTH = 0x8B84, GL_UNPACK_ALIGNMENT = 0x0CF5, GL_PACK_ALIGNMENT = 0x0D05,
    GL_ZERO = 0, GL_ONE = 1, GL_SRC_COLOR = 0x0300, GL_ONE_MINUS_SRC_COLOR = 0x0301, GL_SRC_ALPHA = 0x0302, GL_ONE_MINUS_SRC_ALPHA = 0x0303,
    GL_DST_ALPHA = 0x0304, GL_ONE_MINUS_DST_ALPHA = 0x0305, GL_DST_COLOR = 0x0306, GL_ONE_MINUS_DST_COLOR = 0x0307, GL_VERSION = 0x1F02,
    GL_NEVER = 0x0200, GL_LESS = 0x0201, GL_EQUAL = 0x0202, GL_GREATER = 0x0204, GL_NOTEQUAL = 0x0205, GL_GEQUAL = 0x0206, GL_SCISSOR_TEST = 0x0C11,
    /* v2.16: FBO, MSAA, мипмапы, анизотропия */
    GL_FRAMEBUFFER = 0x8D40, GL_READ_FRAMEBUFFER = 0x8CA8, GL_DRAW_FRAMEBUFFER = 0x8CA9, GL_RENDERBUFFER = 0x8D41, GL_COLOR_ATTACHMENT0 = 0x8CE0,
    GL_DEPTH_ATTACHMENT = 0x8D00, GL_DEPTH_COMPONENT24 = 0x81A6, GL_RGBA8 = 0x8058, GL_FRAMEBUFFER_COMPLETE = 0x8CD5, GL_MAX_SAMPLES = 0x8D57,
    GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E, GL_LINEAR_MIPMAP_LINEAR = 0x2703, GL_LINEAR_MIPMAP_NEAREST = 0x2701, GL_NEAREST_MIPMAP_NEAREST = 0x2700,
    GL_TEXTURE_MAX_LEVEL = 0x813D, GL_NUM_EXTENSIONS = 0x821D, GL_EXTENSIONS = 0x1F03, GL_MAX_TEXTURE_SIZE = 0x0D33, GL_MAX_RENDERBUFFER_SIZE = 0x84E8,
    GL_TEXTURE_MAX_ANISOTROPY = 0x84FE, GL_MAX_TEXTURE_MAX_ANISOTROPY = 0x84FF, GL_RENDERER = 0x1F01,
    GL_VENDOR = 0x1F00, GL_MAX_VIEWPORT_DIMS = 0x0D3A, GL_SHADING_LANGUAGE_VERSION = 0x8B8C,   /* v2.24 */
    GL_ELEMENT_ARRAY_BUFFER = 0x8893, GL_STATIC_DRAW = 0x88E4, GL_UNSIGNED_INT = 0x1405, GL_POLYGON_OFFSET_FILL = 0x8037   /* v2.31: детальные меши */
};
#define GLFUNCS(X) \
 X(void, Enable, (GLenum)) X(void, Disable, (GLenum)) X(void, BlendFunc, (GLenum, GLenum)) X(void, DepthFunc, (GLenum)) \
 X(void, DepthMask, (GLboolean)) X(void, ClearColor, (GLfloat, GLfloat, GLfloat, GLfloat)) X(void, Clear, (GLbitfield)) \
 X(void, Viewport, (GLint, GLint, GLsizei, GLsizei)) X(void, Scissor, (GLint, GLint, GLsizei, GLsizei)) X(void, ReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *)) \
 X(void, PixelStorei, (GLenum, GLint)) X(void, Finish, (void)) X(const unsigned char *, GetString, (GLenum)) \
 X(void, GenTextures, (GLsizei, GLuint *)) X(void, DeleteTextures, (GLsizei, const GLuint *)) X(void, BindTexture, (GLenum, GLuint)) \
 X(void, TexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *)) X(void, TexParameteri, (GLenum, GLenum, GLint)) \
 X(void, ActiveTexture, (GLenum)) \
 X(GLuint, CreateShader, (GLenum)) X(void, ShaderSource, (GLuint, GLsizei, const GLchar *const *, const GLint *)) X(void, CompileShader, (GLuint)) \
 X(void, GetShaderiv, (GLuint, GLenum, GLint *)) X(void, GetShaderInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *)) \
 X(GLuint, CreateProgram, (void)) X(void, AttachShader, (GLuint, GLuint)) X(void, LinkProgram, (GLuint)) X(void, UseProgram, (GLuint)) \
 X(void, GetProgramiv, (GLuint, GLenum, GLint *)) X(void, GetProgramInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *)) \
 X(GLint, GetUniformLocation, (GLuint, const GLchar *)) X(void, Uniform2f, (GLint, GLfloat, GLfloat)) X(void, Uniform1i, (GLint, GLint)) \
 X(void, Uniform3i, (GLint, GLint, GLint, GLint)) X(void, Uniform1f, (GLint, GLfloat)) \
 X(void, GenVertexArrays, (GLsizei, GLuint *)) X(void, BindVertexArray, (GLuint)) \
 X(void, GenBuffers, (GLsizei, GLuint *)) X(void, BindBuffer, (GLenum, GLuint)) X(void, BufferData, (GLenum, GLsizeiptr, const void *, GLenum)) \
 X(void, VertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *)) X(void, EnableVertexAttribArray, (GLuint)) \
 X(void, DrawArrays, (GLenum, GLint, GLsizei)) X(void, ClearDepth, (double)) \
 X(void, GenFramebuffers, (GLsizei, GLuint *)) X(void, DeleteFramebuffers, (GLsizei, const GLuint *)) X(void, BindFramebuffer, (GLenum, GLuint)) \
 X(void, FramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint)) X(void, FramebufferRenderbuffer, (GLenum, GLenum, GLenum, GLuint)) \
 X(GLenum, CheckFramebufferStatus, (GLenum)) X(void, GenRenderbuffers, (GLsizei, GLuint *)) X(void, DeleteRenderbuffers, (GLsizei, const GLuint *)) \
 X(void, BindRenderbuffer, (GLenum, GLuint)) X(void, RenderbufferStorage, (GLenum, GLenum, GLsizei, GLsizei)) \
 X(void, RenderbufferStorageMultisample, (GLenum, GLsizei, GLenum, GLsizei, GLsizei)) \
 X(void, BlitFramebuffer, (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum)) \
 X(void, GetIntegerv, (GLenum, GLint *)) X(void, GetFloatv, (GLenum, GLfloat *)) X(const unsigned char *, GetStringi, (GLenum, GLuint)) \
 X(void, GenSamplers, (GLsizei, GLuint *)) X(void, DeleteSamplers, (GLsizei, const GLuint *)) X(void, BindSampler, (GLuint, GLuint)) \
 X(void, SamplerParameteri, (GLuint, GLenum, GLint)) X(void, SamplerParameterf, (GLuint, GLenum, GLfloat)) \
 X(GLenum, GetError, (void)) \
 X(void, DrawElements, (GLenum, GLsizei, GLenum, const void *)) X(void, UniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat *)) \
 X(void, Uniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat)) X(void, Uniform3f, (GLint, GLfloat, GLfloat, GLfloat)) \
 X(void, PolygonOffset, (GLfloat, GLfloat)) X(void, GenerateMipmap, (GLenum)) X(void, DeleteBuffers, (GLsizei, const GLuint *)) \
 X(void, DeleteVertexArrays, (GLsizei, const GLuint *))
#define DECL(r, n, a) static r (*gl##n) a;
GLFUNCS(DECL)
/* v2.24: журнал графики (plat_sys.c): всегда — заголовок (GL_VENDOR/RENDERER/VERSION, окно/буфер, FBO), ошибки GL/FBO/шейдеров
   и откаты; RE_GFXDBG=1 — подробнее. Файл: macOS ~/Library/Logs/driver_gfx.log, Linux ~/.config/driver/driver_gfx.log (RE_GFXLOG=путь|off). */
void plat_gfx_logf(const char *fmt, ...);
int  plat_gfx_dbg(void);
static int g_glerr_n;
/* glerr — drains pending GL errors and logs them with `where`; returns whether there were any. */
static int glerr(const char *where) {   /* все накопившиеся ошибки GL; возврат — была ли ошибка */
    int any = 0;
    for (int i = 0; i < 8; i++) {
        GLenum e = glGetError(); if (!e) break;
        any = 1; if (g_glerr_n++ < 64) plat_gfx_logf("[gfx] ошибка GL 0x%04x (%s)\n", e, where);
    }
    return any;
}

static const char *VS =
 "#version 330 core\n"
 "layout(location=0) in vec4 aPos; layout(location=1) in vec4 aCol; layout(location=2) in vec4 aSpec; layout(location=3) in vec2 aUV;\n"
 "uniform vec2 uView; uniform float uShift; out vec4 vCol; out vec3 vSpec; out vec2 vUV;\n"
 "void main(){ float rhw = aPos.w == 0.0 ? 1.0 : aPos.w; float w = 1.0 / rhw;\n"
 "  vec3 n = vec3((aPos.x + uShift) / uView.x * 2.0 - 1.0, 1.0 - aPos.y / uView.y * 2.0, aPos.z * 2.0 - 1.0);\n"
 "  gl_Position = vec4(n * w, w); vCol = aCol.bgra; vSpec = aSpec.bgr; vUV = aUV; }\n";
/* v2.01: стадия 0 текстур D3D (COLOROP/ALPHAOP, ARG1/ARG2: 0 diffuse, 1 current, 2 texture) и альфа-тест D3DCMP по ALPHAREF;
   op 0 (не задан) — прежнее поведение: modulate, альфа-тест a < 0.5 */
static const char *FS =
 "#version 330 core\n"
 "in vec4 vCol; in vec3 vSpec; in vec2 vUV; uniform sampler2D uTex; uniform int uAlphaTest; out vec4 oCol;\n"
 "uniform int uSharp; uniform vec2 uTexSize; uniform float uPxScale; uniform int uA2C;\n"
 /* v2.16: sharp-bilinear (2D/HUD): внутри текселя — ближайший, на границе — линейный переход шириной ~1 пиксель экрана */
 "vec4 samp(){ if (uSharp == 0) return texture(uTex, vUV);\n"
 "  vec2 t = vUV * uTexSize - 0.5, i = floor(t), f = clamp((t - i - 0.5) * uPxScale + 0.5, 0.0, 1.0);\n"
 "  return texture(uTex, (i + f + 0.5) / uTexSize); }\n"
 "uniform ivec3 uCOp; uniform ivec3 uAOp; uniform int uAFunc; uniform float uARef;\n"
 "vec4 arg(int a, vec4 t){ return a == 2 ? t : vCol; }\n"
 "float sel(int op, float a1, float a2){ if (op == 1) return vCol.a; if (op == 2) return a1; if (op == 3) return a2;\n"
 "  float m = a1 * a2; return op == 5 ? m * 2.0 : (op == 6 ? m * 4.0 : m); }\n"
 "void main(){ vec4 t = samp(); vec4 c;\n"
 "  if (uCOp.x == 0) c.rgb = vCol.rgb * t.rgb; else if (uCOp.x == 1) c.rgb = vCol.rgb;\n"
 "  else { vec3 a1 = arg(uCOp.y, t).rgb, a2 = arg(uCOp.z, t).rgb; c.rgb = uCOp.x == 2 ? a1 : (uCOp.x == 3 ? a2 : a1 * a2 * (uCOp.x == 5 ? 2.0 : (uCOp.x == 6 ? 4.0 : 1.0))); }\n"
 "  if (uAOp.x == 0) c.a = vCol.a * t.a; else c.a = clamp(sel(uAOp.x, arg(uAOp.y, t).a, arg(uAOp.z, t).a), 0.0, 1.0);\n"
 /* v2.16: alpha-to-coverage (MSAA, без смешивания): край альфа-теста → доля сэмплов, ширина перехода — fwidth(альфы); uA2C 1 — видно при высокой альфе, 2 — при низкой */
 "  if (uAlphaTest != 0 && uA2C != 0) { float e = uA2C == 1 ? max(uAFunc == 0 ? 0.5 : uARef, 0.5) : min(uARef, 0.5);\n"
 "    float cv = clamp((uA2C == 1 ? c.a - e : e - c.a) / max(fwidth(c.a), 1e-4) + 0.5, 0.0, 1.0);\n"
 "    if (cv <= 0.0) discard; c.a = cv; }\n"
 "  else if (uAlphaTest != 0) { float a = c.a; bool ok = true;\n"
 "    if (uAFunc == 0) ok = a >= 0.5; else if (uAFunc == 1) ok = false; else if (uAFunc == 2) ok = a < uARef; else if (uAFunc == 3) ok = a == uARef;\n"
 "    else if (uAFunc == 4) ok = a <= uARef; else if (uAFunc == 5) ok = a > uARef; else if (uAFunc == 6) ok = a != uARef; else if (uAFunc == 7) ok = a >= uARef;\n"
 "    if (!ok) discard; }\n"
 "  oCol = vec4(clamp(c.rgb, 0.0, 1.0) + vSpec, c.a); }\n";

/* v2.16: пост-проход: кадр игры (FBO, после resolve MSAA) → буфер окна; FXAA (по Т. Лоттсу, консольный вариант), sharpen, гамма/яркость */
static const char *PVS =
 "#version 330 core\n"
 "void main(){ vec2 p = vec2(gl_VertexID == 1 ? 3.0 : -1.0, gl_VertexID == 2 ? 3.0 : -1.0); gl_Position = vec4(p, 0.0, 1.0); }\n";
static const char *PFS =
 "#version 330 core\n"
 "uniform sampler2D uTex; uniform vec2 uRcp; uniform vec2 uOut; uniform int uFxaa; uniform float uGamma, uBright, uSharpen; out vec4 o;\n"
 "const vec3 L = vec3(0.299, 0.587, 0.114);\n"
 "vec3 tx(vec2 p){ return texture(uTex, p).rgb; }\n"
 "vec3 fxaa(vec2 uv){ vec3 nw = tx(uv + vec2(-1.0, -1.0) * uRcp), ne = tx(uv + vec2(1.0, -1.0) * uRcp), sw = tx(uv + vec2(-1.0, 1.0) * uRcp), se = tx(uv + vec2(1.0, 1.0) * uRcp), m = tx(uv);\n"
 "  float lnw = dot(nw, L), lne = dot(ne, L), lsw = dot(sw, L), lse = dot(se, L), lm = dot(m, L);\n"
 "  float mn = min(lm, min(min(lnw, lne), min(lsw, lse))), mx = max(lm, max(max(lnw, lne), max(lsw, lse)));\n"
 "  vec2 d = vec2(-((lnw + lne) - (lsw + lse)), (lnw + lsw) - (lne + lse));\n"
 "  float red = max((lnw + lne + lsw + lse) * (0.25 / 8.0), 1.0 / 128.0), rmin = 1.0 / (min(abs(d.x), abs(d.y)) + red);\n"
 "  d = clamp(d * rmin, vec2(-8.0), vec2(8.0)) * uRcp;\n"
 "  vec3 a = 0.5 * (tx(uv + d * (1.0 / 3.0 - 0.5)) + tx(uv + d * (2.0 / 3.0 - 0.5)));\n"
 "  vec3 b = a * 0.5 + 0.25 * (tx(uv - d * 0.5) + tx(uv + d * 0.5)); float lb = dot(b, L);\n"
 "  return (lb < mn || lb > mx) ? a : b; }\n"
 "void main(){ vec2 uv = gl_FragCoord.xy / uOut; vec3 c = uFxaa != 0 ? fxaa(uv) : tx(uv);\n"
 "  if (uSharpen > 0.0) { vec3 n = tx(uv + vec2(uRcp.x, 0.0)) + tx(uv - vec2(uRcp.x, 0.0)) + tx(uv + vec2(0.0, uRcp.y)) + tx(uv - vec2(0.0, uRcp.y));\n"
 "    c += uSharpen * (c - 0.25 * n); }\n"
 "  c = clamp(c, 0.0, 1.0); if (uGamma != 1.0) c = pow(c, vec3(1.0 / uGamma)); o = vec4(clamp(c * uBright, 0.0, 1.0), 1.0); }\n";

/* v2.16: var[1], var[2] — обработанные копии (dilation, мипмапы с весом альфы) для альфа-теста «видно при высокой альфе»
   (GREATER/GEQUAL, умолчание a >= 0.5) и «видно при низкой» (LESS/LESSEQUAL — так игра рисует страницы ARGB1555); создаются
   при первом таком рисовании из src. id — исходная картинка (мипмапы — простое среднее), для рисования без альфа-теста. */
typedef struct { int w, h; unsigned id; unsigned var[3]; uint32_t *src; unsigned char partial, binary; } tex_t;
#define MAX_TEX 4096
static tex_t g_tex[MAX_TEX];
static int g_ok, g_w, g_h, g_cur;
static unsigned g_prog, g_vao, g_vbo, g_white;
static int g_uShift, g_uAlphaTest, g_at = 1, g_uView, g_uTex, g_zt = 1, g_zw = 1, g_blend, g_bs = 5, g_bd = 6;
static int g_zf = 4, g_vp[4], g_vpset, g_rs[64], g_tss[8][32], g_uCOp, g_uAOp, g_uAFunc, g_uARef, g_af, g_aref;
static void (*g_swap)(void);
/* v2.16: кадр игры рисуется в FBO g_tw×g_th (= буфер окна × render_scale): при MSAA — мультисэмпловый g_fbo_ms, resolve в g_fbo
   (цвет — текстура g_ctex); на flip — пост-проход в буфер окна (0). Нет FBO — прямо в окно, как v2.15 (без пост-эффектов). */
static unsigned g_fbo, g_fbo_ms, g_ctex, g_drb, g_crb_ms, g_drb_ms, g_pprog, g_pvao, g_s3d, g_s2d, g_spl, g_spn;
static int g_tw, g_th, g_msaa, g_maxs, g_aniso_hw, g_a2c, g_uSharp, g_uTexSize, g_uPxScale, g_uA2C, g_pu[8], g_fbo_off, g_tex_proc;
static double g_rscale = 1.0; static float g_aniso;
static int g_chk_flips, g_chk_fail, g_chk_ok;   /* v2.24: показы с последней настройки цели; откат по проверке кадра */
const char *plat_render_gfx_info(char *b, int n);
/* target_fbo — framebuffer to draw into: the multisampled FBO if any, else the single-sample FBO (0 = window). */
static unsigned target_fbo(void) { return g_fbo_ms ? g_fbo_ms : g_fbo; }
/* v2.14: нативное разрешение. g_w×g_h — логический кадр игры (640×480: в нём игра даёт x,y вершин, прямоугольники 2D и
   viewport); g_dw×g_dh — реальный буфер окна (SDL_GL_GetDrawableSize, на Retina — в пикселях). Кадр игры вписывается
   в буфер с сохранением пропорций (4:3, полосы по бокам — pillarbox, сверху/снизу — letterbox); 3D растеризуется
   в разрешении буфера (вершины — float), 2D/HUD масштабируются линейно тем же коэффициентом. */
static int g_dw, g_dh, g_cx, g_cy, g_cw, g_ch; static double g_scx = 1.0, g_scy = 1.0;
/* v2.15: Hor+. g_s — добавка S логических пикселей с каждой стороны кадра 640 (aspect.h): логическая ширина g_ew = 640 + 2S.
   Игра считает в координатах 640×480 (центр 320); 3D выходит в x ∈ [−S, 640 + S], всё сдвигается на g_shift при отрисовке:
   S — по центру (меню/фронтенд — pillarbox, 3D — во всю ширину), 0 / 2S — HUD с якорем к левому / правому краю (plat_hud_anchor).
   RE_ASPECT=auto (по окну, по умолчанию) | 4:3 (оригинал, S = 0 — как v2.14) | W:H. Уже 4:3 (портрет) — S = 0, letterbox. */
static int g_s, g_ew = 640, g_shift, g_amode_set; static double g_amode;
/* aspect_mode_init — reads RE_ASPECT once. */
static void aspect_mode_init(void) { if (!g_amode_set) { g_amode = re_aspect_parse(getenv("RE_ASPECT")); g_amode_set = 1; } }
/* content_rect — recomputes the Hor+ extra width S (g_s, only for a 640x480 game frame), the logical frame width
   g_ew = 640 + 2S, and the content rectangle g_cx..g_ch in render-target pixels (largest uniform scale,
   centred; frames narrower than 4:3 get bars). */
static void content_rect(void) {
    if (g_dw <= 0 || g_dh <= 0) { g_dw = g_w; g_dh = g_h; }
    if (g_tw <= 0 || g_th <= 0) { g_tw = g_dw; g_th = g_dh; }
    aspect_mode_init();
    int s = (g_w == RE_ASPECT_W && g_h == RE_ASPECT_H) ? re_aspect_extra(re_aspect_target(g_dw, g_dh, g_amode)) : 0;
    g_shift = g_shift - g_s + s; g_s = s; g_ew = g_w + 2 * g_s;
    /* v2.16: прямоугольники — в пикселях цели рисования (FBO g_tw×g_th) */
    double sx = (double)g_tw / g_ew, sy = (double)g_th / g_h, sc = sx < sy ? sx : sy;
    if (sx / sy > 0.99 && sx / sy < 1.01) { g_scx = sx; g_scy = sy; }   /* S округлено до пикселя: заполнить буфер без полос в 1–2 px */
    else { g_scx = sc; g_scy = sc; }
    g_cw = (int)(g_ew * g_scx + 0.5); g_ch = (int)(g_h * g_scy + 0.5);
    if (g_cw > g_tw) g_cw = g_tw;
    if (g_ch > g_th) g_ch = g_th;
    g_cx = (g_tw - g_cw) / 2; g_cy = (g_th - g_ch) / 2;
}
/* логический прямоугольник кадра шириной g_ew (верх-лево, y вниз; x уже со сдвигом) → прямоугольник GL в буфере (низ-лево) */
/* map_rect / scissor_logical — map a logical rectangle (top-left origin, y down, already shifted) to a GL
   window rectangle (bottom-left origin), and set the scissor from one. */
static void map_rect(int x, int y, int w, int h, int *o) {
    double x0 = g_cx + x * g_scx, x1 = g_cx + (x + w) * g_scx, y0 = g_cy + (g_h - y - h) * g_scy, y1 = g_cy + (g_h - y) * g_scy;
    o[0] = (int)(x0 + 0.5); o[1] = (int)(y0 + 0.5); o[2] = (int)(x1 + 0.5) - o[0]; o[3] = (int)(y1 + 0.5) - o[1];
}
static void scissor_logical(int x, int y, int w, int h) { int r[4]; map_rect(x, y, w, h, r); glScissor(r[0], r[1], r[2], r[3]); }
/* прямоугольник игры (координаты 640×480): весь кадр 640×480 → вся логическая ширина, иначе — со сдвигом текущего якоря */
/* game_rect — horizontal extent of the game's 640-wide coordinates in the logical frame: the whole width for the
   full 640x480 frame, otherwise shifted by the current HUD anchor. */
static void game_rect(int *x, int *w) {
    if (*x <= 0 && *x + *w >= g_w) { *x = 0; *w = g_ew; }
    else *x += g_shift;
}
static void fbo_setup(void);
/* plat_render_set_drawable / plat_render_set_logical / plat_render_content / plat_render_size /
   plat_render_set_aspect — window drawable size, the game's logical size, queries of the content rectangle,
   and the aspect mode; each recomputes the content rectangle and the viewport. */
void plat_render_set_drawable(int dw, int dh) {
    if (dw <= 0 || dh <= 0) return;
    int ch = dw != g_dw || dh != g_dh; g_dw = dw; g_dh = dh;
    if (g_ok && (ch || !g_tw)) fbo_setup();
    else { if (!g_ok) { g_tw = dw; g_th = dh; } content_rect(); }   /* без GL (тесты) — цель = буфер окна */
    if (g_ok) glViewport(g_cx, g_cy, g_cw, g_ch);
}
void plat_render_set_logical(int w, int h) { if (w > 0 && h > 0) { g_w = w; g_h = h; content_rect(); if (g_ok) glViewport(g_cx, g_cy, g_cw, g_ch); } }
void plat_render_content(int *x, int *y, int *w, int *h, int *tw, int *th) {   /* v2.26 */
    if (x) *x = g_cx;
    if (y) *y = g_cy;
    if (w) *w = g_cw;
    if (h) *h = g_ch;
    if (tw) *tw = g_tw;
    if (th) *th = g_th;
}
void plat_render_size(int *dw, int *dh, int *lw, int *lh) { if (dw) *dw = g_dw; if (dh) *dh = g_dh; if (lw) *lw = g_w; if (lh) *lh = g_h; }
/* v2.15 */
void plat_render_set_aspect(const char *mode) { g_amode = re_aspect_parse(mode); g_amode_set = 1; content_rect(); if (g_ok) glViewport(g_cx, g_cy, g_cw, g_ch); }
/* plat_view_extra — S of the current frame (extra logical pixels on each side of 640). */
int  plat_view_extra(void) { return g_s; }
/* plat_hud_anchor — where 2D HUD elements go in the wider frame: a < 0 left edge, 0 centre (4:3 part), > 0 right edge. */
void plat_hud_anchor(int a) { g_shift = g_s + (a < 0 ? -g_s : a > 0 ? g_s : 0); }
/* окно → логические координаты кадра игры 640×480 (мышь; меню — по центру); 0 — точка вне 640×480 */
/* plat_render_to_logical — window pixel -> logical 640x480 game coordinates (mouse); 0 if outside. */
int plat_render_to_logical(double px, double py, int *lx, int *ly) {
    px *= (double)g_tw / g_dw; py *= (double)g_th / g_dh;   /* v2.16: пиксели окна → пиксели цели (render_scale) */
    double x = (px - g_cx) / g_scx - g_s, y = (py - (g_th - g_cy - g_ch)) / g_scy;
    if (lx) *lx = (int)floor(x);
    if (ly) *ly = (int)floor(y);
    return x >= 0 && y >= 0 && x < g_w && y < g_h;
}
/* после показа кадра: весь буфер (и полосы) — чёрный; содержимое заднего буфера после swap в GL не определено */
/* clear_bars — after showing a frame, clears the whole window buffer (bars included) to black, since the back
   buffer contents after a swap are undefined in GL. */
static void clear_bars(void) {
    if (!g_ok || (g_cw == g_tw && g_ch == g_th)) return;
    glDisable(GL_SCISSOR_TEST); glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT);
}

/* blendf — maps a D3D blend factor (D3DBLEND_*) to the GL one. */
static unsigned blendf(int d3d) {
    static const unsigned m[11] = { GL_ONE, GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                                    GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR };
    return (d3d >= 1 && d3d <= 10) ? m[d3d] : GL_ONE;
}
/* compile / link_prog — compile one shader / link a program; log errors. */
static unsigned compile(unsigned type, const char *src) {
    unsigned s = glCreateShader(type); glShaderSource(s, 1, &src, NULL); glCompileShader(s);
    GLint ok = 0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) { char log[1024]; log[0] = 0; glGetShaderInfoLog(s, sizeof log, NULL, log); plat_gfx_logf("[gfx] ошибка компиляции шейдера (%s): %s\n", type == GL_VERTEX_SHADER ? "вершинный" : "фрагментный", log); return 0; }
    return s;
}
/* apply_state — applies the cached D3D-style render state (blend, depth test/write, alpha test, cull) to GL before a draw. */
static void apply_state(void) {
    static const unsigned zf[9] = { GL_LEQUAL, GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS };
    if (g_zt) { glEnable(GL_DEPTH_TEST); glDepthFunc(zf[g_zf >= 1 && g_zf <= 8 ? g_zf : 4]); } else glDisable(GL_DEPTH_TEST);
    if (g_vpset) { glEnable(GL_SCISSOR_TEST); scissor_logical(g_vp[0], g_vp[1], g_vp[2], g_vp[3]); }   /* g_vp — уже со сдвигом (v2.15) */
    else if (g_cw != g_tw || g_ch != g_th) { glEnable(GL_SCISSOR_TEST); glScissor(g_cx, g_cy, g_cw, g_ch); }   /* v2.14: не рисовать в полосы */
    else glDisable(GL_SCISSOR_TEST);
    glDepthMask(g_zw ? 1 : 0);
    if (g_blend) { glEnable(GL_BLEND); glBlendFunc(blendf(g_bs), blendf(g_bd)); } else glDisable(GL_BLEND);
}
/* ===== v2.16: цель рисования (FBO/MSAA), сэмплеры (фильтрация/анизотропия), пост-проход ===== */
/* fbo_free / fbo_ms_try / fbo_setup — v2.16 render target: free, try an MSAA FBO with n samples, and (re)build the
   FBO at render_scale x window size with fallback to direct rendering (driver_gfx.log says which). */
static void fbo_free(void) {
    if (g_fbo_ms) glDeleteFramebuffers(1, &g_fbo_ms);
    if (g_fbo) glDeleteFramebuffers(1, &g_fbo);
    if (g_ctex) glDeleteTextures(1, &g_ctex);
    unsigned rb[3] = { g_drb, g_crb_ms, g_drb_ms }; for (int i = 0; i < 3; i++) if (rb[i]) glDeleteRenderbuffers(1, &rb[i]);
    g_fbo_ms = g_fbo = g_ctex = g_drb = g_crb_ms = g_drb_ms = 0;
}
static int fbo_ms_try(int n) {
    glGenRenderbuffers(1, &g_crb_ms); glBindRenderbuffer(GL_RENDERBUFFER, g_crb_ms); glRenderbufferStorageMultisample(GL_RENDERBUFFER, n, GL_RGBA8, g_tw, g_th);
    glGenRenderbuffers(1, &g_drb_ms); glBindRenderbuffer(GL_RENDERBUFFER, g_drb_ms); glRenderbufferStorageMultisample(GL_RENDERBUFFER, n, GL_DEPTH_COMPONENT24, g_tw, g_th);
    glGenFramebuffers(1, &g_fbo_ms); glBindFramebuffer(GL_FRAMEBUFFER, g_fbo_ms);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_crb_ms);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_drb_ms);
    GLenum st = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (st == GL_FRAMEBUFFER_COMPLETE && !glerr("MSAA FBO")) return 1;
    plat_gfx_logf("[gfx] MSAA-FBO %dx %dx%d: статус 0x%04x — не готов\n", n, g_tw, g_th, st);
    glDeleteFramebuffers(1, &g_fbo_ms); glDeleteRenderbuffers(1, &g_crb_ms); glDeleteRenderbuffers(1, &g_drb_ms);
    g_fbo_ms = g_crb_ms = g_drb_ms = 0; return 0;
}
static void fbo_setup(void) {
    const re_gfx_cfg *c = re_gfx(); GLint mt = 0, mr = 0;
    fbo_free();
    g_rscale = c->render_scale;
    GLint vp[2] = { 0, 0 };
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mt); glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &mr); if (mr > 0 && mr < mt) mt = mr; if (mt <= 0) mt = 4096;
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, vp); if (vp[0] > 0 && vp[0] < mt) mt = vp[0]; if (vp[1] > 0 && vp[1] < mt) mt = vp[1];   /* v2.24 */
    glerr("до FBO");
    if (!c->fbo && !g_fbo_off) { g_fbo_off = 1; plat_gfx_logf("[gfx] fbo = off (driver.cfg / RE_FBO / preset safe) — рисую прямо в окно\n"); }
    g_tw = (int)(g_dw * g_rscale + 0.5); g_th = (int)(g_dh * g_rscale + 0.5);
    if (g_tw < 1) g_tw = 1;
    if (g_th < 1) g_th = 1;
    if (g_tw > mt || g_th > mt) { double k = (double)mt / (g_tw > g_th ? g_tw : g_th); g_tw = (int)(g_tw * k); g_th = (int)(g_th * k); plat_log("[gfx] render_scale: цель урезана до %dx%d (предел %d)\n", g_tw, g_th, mt); }
    if (!g_fbo_off) {
        glGenTextures(1, &g_ctex); glBindTexture(GL_TEXTURE_2D, g_ctex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_tw, g_th, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glGenFramebuffers(1, &g_fbo); glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_ctex, 0);
        g_msaa = 0;
        if (c->msaa >= 2) {
            int n = c->msaa > g_maxs ? g_maxs : c->msaa; while (n >= 2 && !fbo_ms_try(n)) n /= 2;
            g_msaa = n >= 2 ? n : 0;
            if (g_msaa != c->msaa) plat_log("[gfx] MSAA %dx недоступно (GL_MAX_SAMPLES %d) — %s\n", c->msaa, g_maxs, g_msaa ? "понижено" : "выключено");
            if (g_msaa) { char b[8]; snprintf(b, sizeof b, "%dx", g_msaa); (void)b; }
        }
        if (!g_msaa) {   /* глубина — у самого g_fbo */
            glGenRenderbuffers(1, &g_drb); glBindRenderbuffer(GL_RENDERBUFFER, g_drb); glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, g_tw, g_th);
            glBindFramebuffer(GL_FRAMEBUFFER, g_fbo); glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_drb);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
        GLenum st = glCheckFramebufferStatus(GL_FRAMEBUFFER); int er = glerr("FBO");
        { const char *t = getenv("RE_GFXTEST"); if (t && strstr(t, "fboerr")) st = 0; }   /* v2.24: проверка отката */
        if (st != GL_FRAMEBUFFER_COMPLETE || er) {
            plat_gfx_logf("[gfx] FBO %dx%d (окно %dx%d, MSAA %d): статус 0x%04x%s — откат: рисую прямо в окно (без MSAA/пост-эффектов)\n", g_tw, g_th, g_dw, g_dh, g_msaa, st, er ? ", ошибка GL" : "");
            fbo_free(); g_fbo_off = 1;
        }
    }
    if (g_fbo_off) { g_tw = g_dw; g_th = g_dh; g_msaa = 0; g_rscale = 1.0; }
    g_a2c = g_msaa >= 2 && c->a2c;
    glBindFramebuffer(GL_FRAMEBUFFER, target_fbo());
    content_rect(); glViewport(g_cx, g_cy, g_cw, g_ch);
    glDisable(GL_SCISSOR_TEST); glClearColor(0, 0, 0, 1); glDepthMask(1); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glerr("настройка цели") && g_fbo) { plat_gfx_logf("[gfx] ошибка GL при настройке FBO — откат на прямой рендер\n"); fbo_free(); g_fbo_off = 1; g_tw = g_dw; g_th = g_dh; g_msaa = 0; g_a2c = 0; g_rscale = 1.0; glBindFramebuffer(GL_FRAMEBUFFER, 0); content_rect(); glViewport(g_cx, g_cy, g_cw, g_ch); }
    g_chk_flips = 0; g_chk_ok = 0;   /* v2.24: проверка показа — заново после каждой перенастройки */
    { static int n; if (n++ < 12 || plat_gfx_dbg()) { char b[256]; plat_gfx_logf("[gfx] цель рисования: %s\n", plat_render_gfx_info(b, sizeof b)); } }
}
/* samplers_setup — sampler objects for the texture filtering / mipmap / anisotropy settings. */
static void samplers_setup(void) {
    const re_gfx_cfg *c = re_gfx();
    unsigned *ss[4] = { &g_s3d, &g_s2d, &g_spl, &g_spn };
    for (int i = 0; i < 4; i++) { glGenSamplers(1, ss[i]); }
    int mip = c->mipmaps;
    int mn = c->filter == RE_FILTER_NEAREST ? (mip ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST)
           : c->filter == RE_FILTER_TRILINEAR ? (mip ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR) : (mip ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
    glSamplerParameteri(g_s3d, GL_TEXTURE_MIN_FILTER, mn); glSamplerParameteri(g_s3d, GL_TEXTURE_MAG_FILTER, c->filter == RE_FILTER_NEAREST ? GL_NEAREST : GL_LINEAR);
    g_aniso = 1.f;
    if (c->aniso > 1 && g_aniso_hw > 1 && c->filter != RE_FILTER_NEAREST) { g_aniso = (float)(c->aniso < g_aniso_hw ? c->aniso : g_aniso_hw); glSamplerParameterf(g_s3d, GL_TEXTURE_MAX_ANISOTROPY, g_aniso); }
    else if (c->aniso > 1 && g_aniso_hw <= 1) plat_log("[gfx] анизотропная фильтрация недоступна (нет GL_EXT/ARB_texture_filter_anisotropic) — выключена\n");
    int hn = c->hud_filter == RE_HUD_NEAREST ? GL_NEAREST : GL_LINEAR;
    glSamplerParameteri(g_s2d, GL_TEXTURE_MIN_FILTER, hn); glSamplerParameteri(g_s2d, GL_TEXTURE_MAG_FILTER, hn);
    for (int i = 0; i < 2; i++) { glSamplerParameteri(*ss[i], GL_TEXTURE_WRAP_S, GL_REPEAT); glSamplerParameteri(*ss[i], GL_TEXTURE_WRAP_T, GL_REPEAT); }
    glSamplerParameteri(g_spl, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glSamplerParameteri(g_spl, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(g_spn, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glSamplerParameteri(g_spn, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    for (int i = 2; i < 4; i++) { glSamplerParameteri(*ss[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glSamplerParameteri(*ss[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); }
    g_tex_proc = (c->mipmaps || c->dilate) ? 1 : 0;
}
/* has_ext — 1 if the GL context lists extension `name`. */
static int has_ext(const char *name) {
    GLint n = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    for (GLint i = 0; i < n; i++) { const char *e = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i); if (e && !strcmp(e, name)) return 1; }
    return 0;
}
static unsigned link_prog(const char *vsrc, const char *fsrc) {
    unsigned vs = compile(GL_VERTEX_SHADER, vsrc), fs = compile(GL_FRAGMENT_SHADER, fsrc);
    if (!vs || !fs) return 0;
    unsigned p = glCreateProgram(); glAttachShader(p, vs); glAttachShader(p, fs); glLinkProgram(p);
    GLint ok = 0; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) { char log[1024]; log[0] = 0; glGetProgramInfoLog(p, sizeof log, NULL, log); plat_gfx_logf("[gfx] ошибка линковки шейдеров: %s\n", log); return 0; }
    return p;
}
/* resolve MSAA и пост-проход в буфер окна (идемпотентно: снимок и показ могут вызвать дважды); затем снова цель рисования */
/* compose — resolves MSAA and runs the post pass (FXAA / gamma) into the window buffer; idempotent per frame
   (screenshot and present may both call it). */
static void compose(void) {
    if (!g_ok || !g_fbo) return;
    const re_gfx_cfg *c = re_gfx();
    glDisable(GL_SCISSOR_TEST); glDisable(GL_DEPTH_TEST); glDisable(GL_BLEND); glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    if (g_fbo_ms) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, g_fbo_ms); glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_fbo);
        glBlitFramebuffer(0, 0, g_tw, g_th, 0, 0, g_tw, g_th, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); glViewport(0, 0, g_dw, g_dh);
    glUseProgram(g_pprog);
    glUniform1i(g_pu[0], 0); glUniform2f(g_pu[1], 1.f / g_tw, 1.f / g_th); glUniform2f(g_pu[2], (float)g_dw, (float)g_dh);
    glUniform1i(g_pu[3], c->fxaa); glUniform1f(g_pu[4], (float)c->gamma); glUniform1f(g_pu[5], (float)c->brightness); glUniform1f(g_pu[6], (float)c->sharpen);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_ctex);
    glBindSampler(0, (g_tw == g_dw && g_th == g_dh && !c->fxaa) ? g_spn : g_spl);
    { const char *t = getenv("RE_GFXTEST"); int nopost = t && strstr(t, "nopost");   /* v2.24: имитация «пост-проход не рисует» (тест отката) */
      if (!nopost) { glBindVertexArray(g_pvao); glDrawArrays(GL_TRIANGLES, 0, 3); }
      else { glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT); } }
    glBindSampler(0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, target_fbo()); glViewport(g_cx, g_cy, g_cw, g_ch);
}
/* plat_render_gfx_info — one-line description of what is actually enabled (for the log and tests). */
const char *plat_render_gfx_info(char *b, int n) {   /* v2.16: что реально включено (лог, тесты) */
    snprintf(b, (size_t)n, "цель %dx%d (окно %dx%d, scale %.2f), MSAA %d (max %d), A2C %d, aniso %.0f (max %d), FBO %s", g_tw, g_th, g_dw, g_dh, g_rscale, g_msaa, g_maxs,
             g_a2c, g_aniso, g_aniso_hw, g_fbo ? "да" : g_fbo_off ? "нет (прямо в окно)" : "нет");
    return b;
}
/* ===== v2.31: детальные 3D-меши фасадов (platform/sdl/plat_detail.c). Меш в своём пространстве (метры), матрица uM —
   меш → пространство камеры игры (vx, vy, z); проекция как P85_Project: oow = K/z, экран = v·oow·ScaleA + Off − Half, глубина —
   как P23_ConvVertexA (формат A), так что меш делит z-буфер с миром. Отсечение по ближней плоскости — средствами GL (w = z/K). ===== */
static const char *DVS =
 "#version 330 core\n"
 "layout(location=0) in vec3 aPos; layout(location=1) in vec3 aNrm; layout(location=2) in vec2 aUV;\n"
 "uniform mat4 uM; uniform vec4 uP; uniform vec4 uZ; uniform vec2 uView; uniform float uShift; uniform float uZOff; uniform vec3 uL;\n"
 "out vec2 vUV; out float vShade; out vec2 vM;\n"
 "void main(){ vM = aPos.xy; vec4 c = uM * vec4(aPos.xy, aPos.z + uZOff, 1.0); float z = c.z; float w = z / uP.x;\n"
 /* экран без деления: sx·w = c.x·ScaleA + (OffX − Half)·w */
 "  float sxw = c.x * uP.y + uP.z * w, syw = c.y * uP.y + uP.w * w;\n"
 "  float dw; if (uZ.x == 0.0) dw = w - uZ.y; else { float oow = uP.x / max(z, 1e-3); dw = (1.0 - uZ.z / (uZ.w / oow + uZ.y)) * w; }\n"
 "  gl_Position = vec4((sxw + uShift * w) / uView.x * 2.0 - w, w - syw / uView.y * 2.0, dw * 2.0 - w, w);\n"
 "  vUV = aUV; float k = dot(normalize(aNrm), uL) / max(uL.z, 0.05); vShade = clamp(0.6 + 0.4 * k, 0.45, 1.15); }\n";
static const char *DFS =
 "#version 330 core\n"
 "in vec2 vUV; in float vShade; in vec2 vM; uniform sampler2D uTex; uniform vec3 uTint; uniform float uCut; uniform vec4 uClip; out vec4 oCol;\n"
 "void main(){ if (vM.x < uClip.x || vM.y < uClip.y || vM.x > uClip.z || vM.y > uClip.w) discard; vec4 t = texture(uTex, vUV); if (t.a < uCut) discard; oCol = vec4(clamp(t.rgb * uTint * vShade, 0.0, 1.0), 1.0); }\n";
#define MAX_DMESH 256
typedef struct { unsigned vao, vbo, ibo, tex; int ni; } dmesh_t;
static dmesh_t g_dm[MAX_DMESH];
static unsigned g_dprog; static int g_du[11];
/* detail_forget / detail_init — v2.31 facade detail meshes: forget all GL objects / compile the mesh shader. */
static void detail_forget(void) { memset(g_dm, 0, sizeof g_dm); g_dprog = 0; }
static void detail_init(void) {
    static const char *un[11] = { "uM", "uP", "uZ", "uView", "uShift", "uZOff", "uL", "uTex", "uTint", "uCut", "uClip" };
    memset(g_dm, 0, sizeof g_dm);
    g_dprog = link_prog(DVS, DFS);
    if (!g_dprog) { plat_gfx_logf("[detail] шейдер детальных мешей не собран\n"); return; }
    for (int i = 0; i < 11; i++) g_du[i] = glGetUniformLocation(g_dprog, un[i]);
}
/* pos/nrm — по 3 float, uv — 2 float на вершину; rgba — A<<24|B<<16|G<<8|R; возвращает номер меша (1..) или 0 */
/* plat_mesh_create — uploads a detail mesh (pos/nrm 3 floats, uv 2 floats per vertex, indices, RGBA colour).
   Returns the mesh number (1..) or 0. */
int plat_mesh_create(const float *pos, const float *nrm, const float *uv, int nv, const uint32_t *idx, int ni, const uint32_t *rgba, int tw, int th) {
    if (!g_ok || !g_dprog || nv <= 0 || ni < 3 || !pos || !uv || !idx) return 0;
    int m = 0; for (int i = 1; i < MAX_DMESH && !m; i++) if (!g_dm[i].vao) m = i;
    if (!m) return 0;
    float *buf = (float *)malloc((size_t)nv * 8 * sizeof(float));
    if (!buf) return 0;
    for (int i = 0; i < nv; i++) {
        float *o = buf + i * 8;
        o[0] = pos[i * 3]; o[1] = pos[i * 3 + 1]; o[2] = pos[i * 3 + 2];
        if (nrm) { o[3] = nrm[i * 3]; o[4] = nrm[i * 3 + 1]; o[5] = nrm[i * 3 + 2]; } else { o[3] = 0; o[4] = 0; o[5] = 1; }
        o[6] = uv[i * 2]; o[7] = uv[i * 2 + 1];
    }
    dmesh_t *d = &g_dm[m];
    glGenVertexArrays(1, &d->vao); glBindVertexArray(d->vao);
    glGenBuffers(1, &d->vbo); glBindBuffer(GL_ARRAY_BUFFER, d->vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)nv * 8 * sizeof(float), buf, GL_STATIC_DRAW);
    glGenBuffers(1, &d->ibo); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)ni * sizeof(uint32_t), idx, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 32, (void *)0); glVertexAttribPointer(1, 3, GL_FLOAT, 0, 32, (void *)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 32, (void *)24);
    for (int i = 0; i < 3; i++) glEnableVertexAttribArray(i);
    free(buf);
    d->ni = ni;
    glGenTextures(1, &d->tex); glBindTexture(GL_TEXTURE_2D, d->tex);
    if (rgba && tw > 0 && th > 0) {
        /* края альфа-маски: цвет прозрачных текселей = соседний непрозрачный (как dilation страниц), иначе мипмапы темнеют по краям перил */
        uint32_t *px = (uint32_t *)malloc((size_t)tw * th * 4);
        if (px) {
            memcpy(px, rgba, (size_t)tw * th * 4);
            for (int pass = 0; pass < 4; pass++) for (int y = 0; y < th; y++) for (int x = 0; x < tw; x++) {
                uint32_t *p = &px[y * tw + x]; if ((*p >> 24) >= 128) continue;
                static const int dx[4] = { 1, -1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };
                for (int k = 0; k < 4; k++) { int xx = x + dx[k], yy = y + dy[k]; if (xx < 0 || yy < 0 || xx >= tw || yy >= th) continue;
                    uint32_t q = px[yy * tw + xx]; if ((q >> 24) >= 128) { *p = (*p & 0xFF000000u) | (q & 0x00FFFFFFu); break; } }
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, px); free(px);
        } else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
    } else { uint32_t one = 0xFFFFFFFFu; glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &one); }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindVertexArray(g_vao); glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glerr("detail mesh");
    return m;
}
/* plat_mesh_free — frees mesh m. */
void plat_mesh_free(int m) {
    if (!g_ok || m <= 0 || m >= MAX_DMESH || !g_dm[m].vao) return;
    glDeleteBuffers(1, &g_dm[m].vbo); glDeleteBuffers(1, &g_dm[m].ibo); glDeleteVertexArrays(1, &g_dm[m].vao); glDeleteTextures(1, &g_dm[m].tex);
    memset(&g_dm[m], 0, sizeof g_dm[m]);
}
/* одна копия меша: m16 — матрица меш → камера (по столбцам, как GL), proj — K, ScaleA, OffX − Half, OffY − Half;
   zp — режим глубины (0: 1 − oow·ZScaleA; 1: 1 − ZNum/(ZDenA/oow + ZBias)), ZBias|ZScaleA, ZNum, ZDenA; tint 0..1; zoff — сдвиг из стены (м);
   clip — xmin, ymin, xmax, ymax в пространстве меша (часть прямоугольника, покрытая полигонами) или NULL */
/* plat_mesh_draw — draws mesh m with model matrix m16 and the game's projection; clip = the part of the mesh
   rectangle covered by the wall polygons (or NULL). */
void plat_mesh_draw(int m, const float *m16, const float *proj, const float *zp, const float *tint, const float *clip, float zoff, float poly_ofs) {
    if (!g_ok || !g_dprog || m <= 0 || m >= MAX_DMESH || !g_dm[m].vao) return;
    int zt = g_zt, zw = g_zw, zf = g_zf, bl = g_blend;
    g_zt = 1; g_zw = 1; g_zf = 4; g_blend = 0;
    apply_state();
    g_zt = zt; g_zw = zw; g_zf = zf; g_blend = bl;
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    if (poly_ofs != 0.0f) { glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset(-1.0f, -poly_ofs); }
    glUseProgram(g_dprog);
    glUniformMatrix4fv(g_du[0], 1, 0, m16);
    glUniform4f(g_du[1], proj[0], proj[1], proj[2], proj[3]);
    glUniform4f(g_du[2], zp[0], zp[1], zp[2], zp[3]);
    glUniform2f(g_du[3], (float)g_ew, (float)g_h); glUniform1f(g_du[4], (float)g_shift); glUniform1f(g_du[5], zoff);
    { float l[3] = { 0.35f, 0.75f, 0.55f }, n = sqrtf(l[0] * l[0] + l[1] * l[1] + l[2] * l[2]); glUniform3f(g_du[6], l[0] / n, l[1] / n, l[2] / n); }
    glUniform1i(g_du[7], 0); glUniform3f(g_du[8], tint[0], tint[1], tint[2]); glUniform1f(g_du[9], 0.5f);
    if (clip) glUniform4f(g_du[10], clip[0], clip[1], clip[2], clip[3]); else glUniform4f(g_du[10], -1e9f, -1e9f, 1e9f, 1e9f);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_dm[m].tex); glBindSampler(0, 0);
    glBindVertexArray(g_dm[m].vao);
    glDrawElements(GL_TRIANGLES, g_dm[m].ni, GL_UNSIGNED_INT, (void *)0);
    if (poly_ofs != 0.0f) glDisable(GL_POLYGON_OFFSET_FILL);
    glBindVertexArray(g_vao); glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
}
/* plat_render_attach — binds the backend to a GL context: loads entry points, creates shaders, buffers and the
   render target.  Returns 0 on success, negative on failure (-1 missing entry point, -2 shader compile,
   -3 link). */
int plat_render_attach(void *(*get_proc)(const char *), void (*swap)(void), int w, int h) {
#define LOAD(r, n, a) if (!(gl##n = (r (*) a)get_proc("gl" #n))) { plat_gfx_logf("[gfx] GL: нет функции gl" #n "\n"); return -1; }
    GLFUNCS(LOAD)
    unsigned vs = compile(GL_VERTEX_SHADER, VS), fs = compile(GL_FRAGMENT_SHADER, FS);
    if (!vs || !fs) return -2;
    g_prog = glCreateProgram(); glAttachShader(g_prog, vs); glAttachShader(g_prog, fs); glLinkProgram(g_prog);
    GLint ok = 0; glGetProgramiv(g_prog, GL_LINK_STATUS, &ok);
    if (!ok) { char log[1024]; log[0] = 0; glGetProgramInfoLog(g_prog, sizeof log, NULL, log); plat_gfx_logf("[gfx] ошибка линковки шейдеров: %s\n", log); return -3; }
    g_uView = glGetUniformLocation(g_prog, "uView"); g_uShift = glGetUniformLocation(g_prog, "uShift"); g_uTex = glGetUniformLocation(g_prog, "uTex"); g_uAlphaTest = glGetUniformLocation(g_prog, "uAlphaTest");
    g_uCOp = glGetUniformLocation(g_prog, "uCOp"); g_uAOp = glGetUniformLocation(g_prog, "uAOp");
    g_uAFunc = glGetUniformLocation(g_prog, "uAFunc"); g_uARef = glGetUniformLocation(g_prog, "uARef");
    glGenVertexArrays(1, &g_vao); glBindVertexArray(g_vao);
    glGenBuffers(1, &g_vbo); glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    /* plat_vertex: 4 float, 2 цвета (u8 x4), 2 float */
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, sizeof(plat_vertex), (void *)offsetof(plat_vertex, x));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, 1, sizeof(plat_vertex), (void *)offsetof(plat_vertex, color));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, 1, sizeof(plat_vertex), (void *)offsetof(plat_vertex, specular));
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, sizeof(plat_vertex), (void *)offsetof(plat_vertex, u));
    for (int i = 0; i < 4; i++) glEnableVertexAttribArray(i);
    uint32_t one = 0xFFFFFFFFu; glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &g_white); glBindTexture(GL_TEXTURE_2D, g_white);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &one);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glDisable(GL_CULL_FACE);
    g_uSharp = glGetUniformLocation(g_prog, "uSharp"); g_uTexSize = glGetUniformLocation(g_prog, "uTexSize");
    g_uPxScale = glGetUniformLocation(g_prog, "uPxScale"); g_uA2C = glGetUniformLocation(g_prog, "uA2C");
    /* v2.16: пост-проход, возможности GL, сэмплеры, FBO */
    g_fbo = g_fbo_ms = g_ctex = g_drb = g_crb_ms = g_drb_ms = 0; g_fbo_off = getenv("RE_NO_FBO") != NULL; g_tw = g_th = 0;
    if (!(g_pprog = link_prog(PVS, PFS))) { plat_log("[gfx] пост-шейдер не собран — без FBO\n"); g_fbo_off = 1; }
    else { static const char *pn[7] = { "uTex", "uRcp", "uOut", "uFxaa", "uGamma", "uBright", "uSharpen" }; for (int i = 0; i < 7; i++) g_pu[i] = glGetUniformLocation(g_pprog, pn[i]); }
    glGenVertexArrays(1, &g_pvao); glBindVertexArray(g_vao);
    g_maxs = 0; glGetIntegerv(GL_MAX_SAMPLES, &g_maxs);
    g_aniso_hw = 1;
    if (has_ext("GL_EXT_texture_filter_anisotropic") || has_ext("GL_ARB_texture_filter_anisotropic")) { GLfloat m = 1; glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &m); g_aniso_hw = (int)m; }
    samplers_setup();
    g_w = w; g_h = h; g_dw = w; g_dh = h; g_shift = g_s; g_swap = swap; g_ok = 1; g_cur = 0;
    fbo_setup();
    memset(g_tss, 0, sizeof g_tss); g_af = 0; g_aref = 0;   /* v2.01: новый контекст — состояние стадий с нуля (op 0 — прежнее поведение) */
    g_tss[0][2] = 2; g_tss[0][3] = 1; g_tss[0][5] = 2; g_tss[0][6] = 1;   /* v2.01: умолчания D3D: ARG1 = TEXTURE, ARG2 = CURRENT */
    glViewport(g_cx, g_cy, g_cw, g_ch);
    { const char *ve = (const char *)glGetString(GL_VENDOR), *re = (const char *)glGetString(GL_RENDERER), *vv = (const char *)glGetString(GL_VERSION), *sl = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
      GLint mt = 0, mr = 0, vp[2] = { 0, 0 }; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mt); glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &mr); glGetIntegerv(GL_MAX_VIEWPORT_DIMS, vp);
      plat_log("GL %s (%s)\n", vv ? vv : "?", re ? re : "?");
      plat_gfx_logf("[gfx] GL_VENDOR %s | GL_RENDERER %s | GL_VERSION %s | GLSL %s | MAX_TEXTURE %d MAX_RENDERBUFFER %d MAX_VIEWPORT %dx%d MAX_SAMPLES %d\n",
                    ve ? ve : "?", re ? re : "?", vv ? vv : "?", sl ? sl : "?", mt, mr, vp[0], vp[1], g_maxs);
      if (RE_LOG_ON(render, RE_LV_DEBUG)) {   /* v2.37: расширения GL — одной строкой на десяток */
          GLint ne = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &ne);
          RE_LOGD(render, "GL: расширений %d", (int)ne);
          char b[960]; int o = 0, k = 0;
          for (GLint i = 0; i < ne; i++) { const char *e = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i); if (!e) continue;
              o += snprintf(b + o, sizeof b - (size_t)o, "%s%s", k ? " " : "", e); k++;
              if (o > (int)sizeof b - 64 || i == ne - 1) { RE_LOGD(render, "GL ext: %s", b); o = 0; k = 0; b[0] = 0; } }
          glGetError();
      } }
    detail_init();
    glerr("инициализация");
    { char b[512], b2[256]; plat_gfx_logf("[gfx] %s\n[gfx] %s\n", re_gfx_describe(re_gfx(), b, sizeof b), plat_render_gfx_info(b2, sizeof b2)); }
    return 0;
}
/* plat_render_shutdown — drops all GL objects and texture sources (context going away). */
void plat_render_shutdown(void) { g_ok = 0; detail_forget(); for (int i = 0; i < MAX_TEX; i++) free(g_tex[i].src); memset(g_tex, 0, sizeof g_tex); g_swap = NULL; g_fbo = g_fbo_ms = g_ctex = g_drb = g_crb_ms = g_drb_ms = 0; g_tw = g_th = 0; }

int png_write_rgba(const char *path, const uint32_t *px, int w, int h);
/* tex_dump — v2.06 RE_TEXDUMP: writes each uploaded texture as PNG into the given directory. */
static void tex_dump(int i, int w, int h, const uint32_t *rgba) {   /* v2.06: RE_TEXDUMP=каталог — каждая загрузка текстуры в PNG */
    static int n; const char *d = getenv("RE_TEXDUMP"); if (!d || !rgba || n >= 400) return;
    char p[512]; snprintf(p, sizeof p, "%s/t%03d_id%d_%dx%d.png", d, n++, i, w, h); png_write_rgba(p, rgba, w, h);
}
/* v2.16: загрузка картинки текстуры: dilation цвета в прозрачные пиксели (без тёмных/пурпурных ореолов chroma-key при линейной
   фильтрации) и своя цепочка мипмапов (RGB — среднее, взвешенное альфой; у двоичной альфы chroma-key — сохранение покрытия
   альфа-теста). Только текстуры степени двойки до 1024 (страницы игры 256×256); кадр LFB 640×480 и прочее — как есть. */
static int g_up_n, g_up_px, g_var_n;
/* уровень в GL; inv — альфа хранится инвертированной (вариант «видно при низкой альфе») */
/* put_level / upload_variant / tex_vars_free / tex_upload / tex_variant — texture upload: power-of-two pages get
   mipmaps and up to three alpha variants (0 as is, 1 alpha 0 transparent, 2 alpha 255 transparent, stored
   inverted) chosen at draw time by the alpha-test semantics; tex_variant creates a variant on first use. */
static void put_level(int lv, int w, int h, const uint32_t *px, int inv) {
    if (!inv) { glTexImage2D(GL_TEXTURE_2D, lv, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, px); return; }
    uint32_t *t = (uint32_t *)malloc((size_t)w * h * 4); if (!t) return;
    for (int i = 0; i < w * h; i++) t[i] = px[i] ^ 0xFF000000u;
    glTexImage2D(GL_TEXTURE_2D, lv, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, t); free(t);
}
/* mode 0 — как есть (мипмапы — простое среднее), 1 — прозрачна альфа 0, 2 — прозрачна альфа 255 (инверсия на время обработки) */
static void upload_variant(int w, int h, const uint32_t *rgba, int mode, int binary) {
    const re_gfx_cfg *c = re_gfx(); int levels = 0, inv = mode == 2;
    uint32_t *buf = (uint32_t *)malloc((size_t)w * h * 4), *nx = NULL;
    if (!buf) { put_level(0, w, h, rgba, 0); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0); return; }
    for (int i = 0; i < w * h; i++) buf[i] = inv ? rgba[i] ^ 0xFF000000u : rgba[i];
    if (mode && c->dilate) re_gfx_dilate(buf, w, h, 16);
    put_level(0, w, h, buf, inv);
    if (c->mipmaps && (nx = (uint32_t *)malloc((size_t)(w / 2 + 1) * (h / 2 + 1) * 4))) {
        double cov = (mode && binary) ? re_gfx_coverage(buf, w, h, 128) : -1.0;
        int cw = w, ch = h;
        while (cw > 1 || ch > 1) {
            int nw = cw > 1 ? cw / 2 : 1, nh = ch > 1 ? ch / 2 : 1;
            if (mode) { re_gfx_mip_next(buf, cw, ch, nx, cov, 128); if (c->dilate) re_gfx_dilate(nx, nw, nh, 16); }
            else re_gfx_mip_box(buf, cw, ch, nx);
            put_level(++levels, nw, nh, nx, inv);
            memcpy(buf, nx, (size_t)nw * nh * 4); cw = nw; ch = nh;
        }
        free(nx);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, levels);
    free(buf);
}
static void tex_vars_free(tex_t *t) {
    for (int v = 1; v < 3; v++) if (t->var[v]) { glDeleteTextures(1, &t->var[v]); t->var[v] = 0; }
    free(t->src); t->src = NULL; t->partial = t->binary = 0;
}
/* загрузка картинки: обработка только у текстур степени двойки до 1024 (страницы игры 256×256); кадр LFB 640×480 — как есть */
static void tex_upload(tex_t *t, int w, int h, const uint32_t *rgba) {
    int pow2 = !(w & (w - 1)) && !(h & (h - 1)) && w <= 1024 && h <= 1024;
    g_up_n++; g_up_px += w * h;
    tex_vars_free(t);
    if (!rgba || !pow2 || !g_tex_proc) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0); return;
    }
    t->partial = (unsigned char)re_gfx_has_partial_alpha(rgba, w, h); t->binary = 1;
    if (t->partial) {
        for (int i = 0; i < w * h && t->binary; i++) { unsigned a = rgba[i] >> 24; t->binary = a == 0 || a == 255; }
        if ((t->src = (uint32_t *)malloc((size_t)w * h * 4))) memcpy(t->src, rgba, (size_t)w * h * 4);
    }
    upload_variant(w, h, rgba, 0, t->binary);
}
/* текстура для рисования: вариант по семантике альфа-теста (0 — исходная) */
static unsigned tex_variant(int i, int v) {
    tex_t *t = &g_tex[i];
    if (!v || !t->partial || !t->src) return t->id;
    if (!t->var[v]) {
        glGenTextures(1, &t->var[v]); glBindTexture(GL_TEXTURE_2D, t->var[v]);
        upload_variant(t->w, t->h, t->src, v, t->binary); g_var_n++;
    }
    return t->var[v];
}
/* plat_tex_create / plat_tex_update / plat_tex_bind / plat_tex_free — create a texture from RGBA pixels (returns its
   handle), replace its picture (v2.01), select it for drawing, free it. */
int plat_tex_create(int w, int h, const uint32_t *rgba) {
    if (!g_ok || w <= 0 || h <= 0) return 0;
    for (int i = 1; i < MAX_TEX; i++) if (!g_tex[i].id) {
        glGenTextures(1, &g_tex[i].id); glBindTexture(GL_TEXTURE_2D, g_tex[i].id);
        g_tex[i].w = w; g_tex[i].h = h; tex_upload(&g_tex[i], w, h, rgba);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        g_tex[i].w = w; g_tex[i].h = h; tex_dump(i, w, h, rgba);
        RE_LOGT(render, "текстура %d создана: %dx%d", i, w, h);
        return i;
    }
    if (g_ok && w > 0 && h > 0) RE_LOGW(render, "plat_tex_create %dx%d: таблица текстур полна (%d) — текстура не создана", w, h, MAX_TEX - 1);
    return 0;
}
void plat_tex_update(int tex, int w, int h, const uint32_t *rgba) {   /* v2.01: новая картинка той же текстуры */
    if (!g_ok || tex <= 0 || tex >= MAX_TEX || !g_tex[tex].id || w <= 0 || h <= 0) return;
    glBindTexture(GL_TEXTURE_2D, g_tex[tex].id);
    g_tex[tex].w = w; g_tex[tex].h = h; tex_upload(&g_tex[tex], w, h, rgba);
    g_tex[tex].w = w; g_tex[tex].h = h; tex_dump(tex, w, h, rgba);
}
/* plat_clear_rect — v2.01: colour fill of a rectangle of the back surface (DirectDraw Blt COLORFILL). */
void plat_clear_rect(uint32_t c, int x, int y, int w, int h) {   /* v2.01: Blt COLORFILL задней поверхности */
    if (!g_ok || w <= 0 || h <= 0) return;
    game_rect(&x, &w);
    glEnable(GL_SCISSOR_TEST); scissor_logical(x, y, w, h);
    glClearColor(((c >> 16) & 255) / 255.f, ((c >> 8) & 255) / 255.f, (c & 255) / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT); glDisable(GL_SCISSOR_TEST);
}
void plat_tex_bind(int tex) { g_cur = (tex > 0 && tex < MAX_TEX && g_tex[tex].id) ? tex : 0; }
void plat_tex_free(int tex) {
    if (!g_ok || tex <= 0 || tex >= MAX_TEX || !g_tex[tex].id) return;
    tex_vars_free(&g_tex[tex]); glDeleteTextures(1, &g_tex[tex].id); memset(&g_tex[tex], 0, sizeof g_tex[tex]); if (g_cur == tex) g_cur = 0;
}
/* plat_set_blend / plat_set_zbuffer / plat_scene_begin / plat_scene_end — cached blend and depth state; scene
   begin/end are no-ops in GL. */
void plat_set_blend(int e, int s, int d) { g_blend = e; if (e) { g_bs = s; g_bd = d; } }
void plat_set_zbuffer(int t, int w) { g_zt = t; g_zw = w; }
void plat_scene_begin(void) {}
void plat_scene_end(void) {}
/* plat_set_render_state / plat_get_render_state — D3D render-state ids (e.g. 14 z-write, 15 alpha test, 22 cull,
   23 z-func) cached in g_rs[] and mapped to the GL state used by apply_state. */
void plat_set_render_state(int state, uint32_t value) {
    if (state < 0 || state >= 64) return;
    g_rs[state] = (int)value;
    { static int n; if (getenv("RE_TRACE_DD") && n < 80) { n++; fprintf(stderr, "[gl] rs %d = %u\n", state, value); } }
    switch (state) {
    case 7: g_zt = value != 0; break;
    case 14: g_zw = value != 0; break;
    case 15: g_at = value != 0; break;   /* ALPHATESTENABLE: отбрасывать тексели с альфой < 0.5 (по умолчанию включён) */
    case 19: g_bs = (int)value; break;
    case 20: g_bd = (int)value; break;
    case 23: g_zf = (int)value; break;
    case 24: g_aref = (int)(value & 0xff); break;   /* v2.01: ALPHAREF */
    case 25: g_af = (int)value; break;              /* v2.01: ALPHAFUNC (D3DCMP 1..8) */
    case 27: g_blend = value != 0; break;
    default: break;   /* остальные (альфа-тест, cull) пока только запоминаются */
    }
}
/* plat_set_tex_stage / plat_get_tex_stage — D3D texture-stage states (colour op, filters) cached for draws. */
void plat_set_tex_stage(int stage, int type, uint32_t value) {
    if (stage >= 0 && stage < 8 && type >= 0 && type < 32) g_tss[stage][type] = (int)value;
}
/* plat_set_viewport — the game's viewport rectangle (logical coordinates). */
void plat_set_viewport(int x, int y, int w, int h) {
    /* v2.15: полный вид — и 640×480 без расширения, и расширенный [−S, 640 + S] (окно отсечения 3D P110_Clip*); иначе — со сдвигом якоря */
    int full = (x <= -g_s && y <= 0 && x + w >= g_w + g_s && y + h >= g_h) || (g_s == 0 && x == 0 && y == 0 && w >= g_w && h >= g_h);
    g_vp[0] = x + g_shift; g_vp[1] = y; g_vp[2] = w; g_vp[3] = h; g_vpset = (w > 0 && h > 0 && !full);
}
uint32_t plat_get_tex_stage(int stage, int type) {
    if (stage >= 0 && stage < 8 && type >= 0 && type < 32) return (uint32_t)g_tss[stage][type];
    return 0;
}
static int g_dp_calls, g_dp_type, g_dp_count;
static void draw(const plat_vertex *v, int count, unsigned mode);
/* plat_draw_prim / plat_draw_prim_last — D3D-style DrawPrimitive: type 4 (D3DPT_TRIANGLELIST) and 2 (D3DPT_LINELIST)
   are drawn, others ignored; the last call is remembered for tests.  RE_TRACE_DD / RE_ATDBG / RE_ZDBG print traces. */
void plat_draw_prim(int ptype, const plat_vertex *v, int count) {
    g_dp_calls++; g_dp_type = ptype; g_dp_count = count; { extern int g_re_dbg[16]; g_re_dbg[3]++; g_re_dbg[4] += count; }
    if (getenv("RE_TRACE_DD") && g_dp_calls < 60 && v && count >= 3) fprintf(stderr, "[gl] v1 %.1f %.1f uv %.5f %.5f v2 %.1f %.1f uv %.5f %.5f\n", v[1].x, v[1].y, v[1].u, v[1].v, v[2].x, v[2].y, v[2].u, v[2].v);
    if (getenv("RE_TRACE_DD") && g_dp_calls < 60) fprintf(stderr, "[gl] draw_prim %d n=%d tex %d v0 %.1f %.1f %.3f %.3f col %08x uv %.3f %.3f zt %d zf %d bl %d %d %d at %d vp %d %d %d %d %d tss %d %d %d %d\n", ptype, count, g_cur,
        v ? v[0].x : 0, v ? v[0].y : 0, v ? v[0].z : 0, v ? v[0].rhw : 0, v ? v[0].color : 0, v ? v[0].u : 0, v ? v[0].v : 0, g_zt, g_zf, g_blend, g_bs, g_bd, g_at, g_vpset, g_vp[0], g_vp[1], g_vp[2], g_vp[3], g_tss[0][1], g_tss[0][2], g_tss[0][3], g_tss[0][4]);
    { static int k; if (getenv("RE_ATDBG") && g_at && g_af == 2 && k++ < 6 && v && count) fprintf(stderr, "[at] z %f rhw %f xy %.0f %.0f bl %d %d %d zt %d zw %d zf %d n %d tex %d col %08x aref %d tss c %d %d %d a %d %d %d\n", v[0].z, v[0].rhw, v[0].x, v[0].y, g_blend, g_bs, g_bd, g_zt, g_zw, g_zf, count, g_cur, v[0].color, g_aref,
        g_tss[0][1], g_tss[0][2], g_tss[0][3], g_tss[0][4], g_tss[0][5], g_tss[0][6]); }
    { static int k; static int armed; if (g_at && g_af == 2) armed = 1; if (getenv("RE_ZDBG") && armed && k++ < 40 && v && count) fprintf(stderr, "[z] n %d tex %d z %f rhw %f xy %.0f %.0f zt %d zf %d at %d af %d\n", count, g_cur, v[0].z, v[0].rhw, v[0].x, v[0].y, g_zt, g_zf, g_at, g_af); }
    if (ptype == 4) plat_draw_tris(v, count);
    else if (ptype == 2) plat_draw_lines(v, count);
}
int plat_draw_prim_last(int *ptype, int *count) { if (ptype) *ptype = g_dp_type; if (count) *count = g_dp_count; return g_dp_calls; }
/* draw — uploads count vertices, applies the state and the current texture variant, and issues the GL draw. */
static void draw(const plat_vertex *v, int count, unsigned mode) {
    re_diag_draw(v, count, mode, g_cur, g_zt, g_zw, g_zf, g_blend, g_bs, g_bd, g_at, g_af, g_aref);
    apply_state();
    glUseProgram(g_prog); glUniform2f(g_uView, (float)g_ew, (float)g_h); glUniform1f(g_uShift, (float)g_shift); glUniform1i(g_uTex, 0); glUniform1i(g_uAlphaTest, g_at);
    glUniform3i(g_uCOp, g_tss[0][1], g_tss[0][2], g_tss[0][3]); glUniform3i(g_uAOp, g_tss[0][4], g_tss[0][5], g_tss[0][6]);
    glUniform1i(g_uAFunc, g_af >= 1 && g_af <= 8 ? g_af : 0); glUniform1f(g_uARef, (float)g_aref / 255.f);
    /* v2.16: вариант текстуры по альфа-тесту: 1 — видно при высокой альфе (умолчание, GREATER, GEQUAL), 2 — при низкой (LESS, LESSEQUAL) */
    int avar = !g_at ? 0 : (g_af == 0 || g_af == 5 || g_af == 7) ? 1 : (g_af == 2 || g_af == 4) ? 2 : 0;
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_cur ? tex_variant(g_cur, avar) : g_white);
    /* v2.16: 2D (экранные прямоугольники без z-теста: HUD, шрифты, меню, LFB) — сэмплер HUD (sharp-bilinear/linear/nearest),
       3D — фильтрация/мипмапы/анизотропия; A2C — альфа-тест без смешивания при MSAA */
    int is2d = !g_zt && count > 0 && v[0].z <= 0.0001f && v[0].rhw >= 0.999f && v[0].rhw <= 1.001f;
    const re_gfx_cfg *gc = re_gfx();
    glBindSampler(0, g_cur ? (is2d ? g_s2d : g_s3d) : 0);
    int sharp = is2d && g_cur && gc->hud_filter == RE_HUD_SHARP;
    glUniform1i(g_uSharp, sharp);
    if (sharp) { glUniform2f(g_uTexSize, (float)g_tex[g_cur].w, (float)g_tex[g_cur].h); glUniform1f(g_uPxScale, (float)(g_scy > 1.0 ? g_scy : 1.0)); }
    int a2c = (g_a2c && avar && !g_blend && !is2d) ? avar : 0;
    glUniform1i(g_uA2C, a2c);
    if (a2c) glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE); else glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glBindVertexArray(g_vao); glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)count * sizeof(plat_vertex), v, GL_STREAM_DRAW);
    glDrawArrays(mode, 0, count);
}
/* plat_draw_tris / plat_draw_lines — draw whole triangles / lines from a vertex array. */
void plat_draw_tris(const plat_vertex *v, int count) { if (g_ok && v && count >= 3) draw(v, count - count % 3, GL_TRIANGLES); }
void plat_draw_lines(const plat_vertex *v, int count) { if (g_ok && v && count >= 2) draw(v, count - count % 2, GL_LINES); }
/* plat_clear / plat_set_current_viewport / plat_clear_depth — clear colour (and depth) of the logical frame; depth-only
   clear of a rectangle to value z. */
void plat_clear(uint32_t c, int clear_z) {
    if (!g_ok) return;
    glDepthMask(1); glClearColor(((c >> 16) & 255) / 255.f, ((c >> 8) & 255) / 255.f, (c & 255) / 255.f, (c >> 24) / 255.f);
    if (g_cw != g_tw || g_ch != g_th) { glEnable(GL_SCISSOR_TEST); glScissor(g_cx, g_cy, g_cw, g_ch); }   /* v2.14: только кадр игры */
    glClear(GL_COLOR_BUFFER_BIT | (clear_z ? GL_DEPTH_BUFFER_BIT : 0));
    if (g_cw != g_tw || g_ch != g_th) glDisable(GL_SCISSOR_TEST);
}
void plat_set_current_viewport(void) {}
int plat_get_render_state(int state) { return (state >= 0 && state < 64) ? g_rs[state] : 0; }
void plat_clear_depth(void *viewport, int x, int y, int w, int h, float z) {
    (void)viewport;
    if (!g_ok) return;
    game_rect(&x, &w);
    glEnable(GL_SCISSOR_TEST); scissor_logical(x, y, w, h);
    glDepthMask(1); glClearDepth((double)z); glClear(GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
}
void plat_snd_pump(void);
/* v2.24: проверка показа. После resolve/пост-прохода сравнить кадр в FBO (что нарисовала игра) с буфером окна (что будет показано):
   сетка 8×8 точек кадра. В FBO есть изображение, а в окне — пусто, или ошибка GL при показе → откат на прямой рендер без FBO
   (как v2.15 / preset safe). Проверяется на 3-м, 30-м и 150-м показе после каждой настройки цели (и каждые 600 показов при RE_GFXDBG). */
/* grid_nonblack / plat_render_selfcheck — v2.24: sample a grid of pixels in a framebuffer and compare the FBO with
   the window after presenting; if the FBO has content but the window stays black, fall back to direct
   rendering.  Returns 0 when fine (or nothing to compare), 1 after falling back. */
static int grid_nonblack(unsigned fb, int x0, int y0, int w, int h, unsigned *sum) {
    int n = 0; unsigned char px[4]; *sum = 0;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fb); glPixelStorei(GL_PACK_ALIGNMENT, 1);
    for (int j = 0; j < 8; j++) for (int i = 0; i < 8; i++) {
        int x = x0 + (int)((i + 0.5) * w / 8), y = y0 + (int)((j + 0.5) * h / 8);
        px[0] = px[1] = px[2] = px[3] = 0; glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
        unsigned s = (unsigned)px[0] + px[1] + px[2]; *sum += s; n += s > 12;
    }
    return n;
}
static void fbo_setup(void);
int plat_render_selfcheck(int *fbo_nb, int *win_nb) {   /* 0 — норма (или нечего сравнивать), 1 — был откат на прямой рендер */
    if (!g_ok || !g_fbo) return 0;
    unsigned sf = 0, sw = 0;
    int er = glerr("показ кадра");
    int nf = grid_nonblack(g_fbo, g_cx, g_cy, g_cw, g_ch, &sf);
    int ox = (int)((double)g_cx * g_dw / g_tw), oy = (int)((double)g_cy * g_dh / g_th), ow = (int)((double)g_cw * g_dw / g_tw), oh = (int)((double)g_ch * g_dh / g_th);
    int nw = grid_nonblack(0, ox, oy, ow, oh, &sw);
    er |= glerr("чтение кадра");
    glBindFramebuffer(GL_FRAMEBUFFER, target_fbo());
    if (fbo_nb) *fbo_nb = nf;
    if (nf >= 4 && nw >= 2 && !er) { if (!g_chk_ok) plat_gfx_logf("[gfx] проверка показа: кадр через FBO виден в окне (%d/64 точек) — норма\n", nw); g_chk_ok = 1; }
    if (win_nb) *win_nb = nw;
    if (plat_gfx_dbg() || er || (nf >= 4 && nw == 0)) plat_gfx_logf("[gfx] проверка показа %d: в FBO непусто %d/64 (сумма %u), в окне %d/64 (сумма %u)%s\n", g_chk_flips, nf, sf, nw, sw, er ? ", ошибка GL" : "");
    if (er || (nf >= 4 && nw == 0)) {
        g_chk_fail++;
        plat_gfx_logf("[gfx] ОТКАТ: %s — дальше рисую прямо в окно без FBO (MSAA/FXAA/render_scale/гамма выключены). Чтобы не ждать проверки: fbo = off в driver.cfg или RE_FBO=0\n",
                      er ? "ошибка GL при показе кадра через FBO" : "кадр в FBO есть, а в окне пусто");
        fbo_free(); g_fbo_off = 1; fbo_setup();
        { void plat_fullscreen_fallback(const char *why); const char *f = getenv("RE_FULLSCREEN");
          if (!(f && *f)) plat_fullscreen_fallback("полный экран после отката FBO"); }   /* v2.24: заодно — в окно, если полный экран не задан явно */
        return 1;
    }
    return 0;
}
/* v2.24: переключение на лету (Cmd/Alt+Shift+Enter — plat_sys.c): 1 — через FBO (если доступен), 0 — прямо в окно */
/* plat_render_set_fbo / plat_render_fbo_on — v2.24: switch the render target on the fly (1 = through the FBO if
   available, 0 = straight to the window) / query it. */
int plat_render_set_fbo(int on) {
    if (!g_ok) return -1;
    if (on && g_pprog) g_fbo_off = 0; else g_fbo_off = 1;
    fbo_setup(); plat_gfx_logf("[gfx] переключено: %s\n", g_fbo ? "через FBO" : "прямо в окно");
    return g_fbo ? 1 : 0;
}
int plat_render_fbo_on(void) { return g_fbo != 0; }
/* plat_flip — presents the frame: compose, swap, clear the bars, run the periodic self-check. */
void plat_flip(void) {
    plat_snd_pump(); if (!g_ok) return;
    if (g_swap) compose();   /* v2.16: resolve + пост-проход в буфер окна до снимка/показа */
    /* v2.24: проверка — на 3-м показе, затем каждые 30, пока не будет кадра с изображением (заставки бывают чёрными), до 6000 показов */
    if (g_swap) { g_chk_flips++; if (g_fbo && ((!g_chk_ok && g_chk_flips <= 6000 && (g_chk_flips == 3 || g_chk_flips % 30 == 0)) || (plat_gfx_dbg() && g_chk_flips % 600 == 0))) plat_render_selfcheck(NULL, NULL); }
    else if (g_chk_flips < 4) glerr("кадр");
    if (g_swap) {
        plat_frame_tick("flip");
        /* Cocoa presents only when the window's draw framebuffer is bound.
           compose(), diagnostics and the selfcheck restore the scene FBO, so
           unbind it at the swap boundary, then resume rendering into the scene.
           https://wiki.libsdl.org/SDL2/SDL_GL_SwapWindow */
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        g_swap();
        glBindFramebuffer(GL_FRAMEBUFFER, target_fbo());
        glViewport(g_cx, g_cy, g_cw, g_ch);
        clear_bars();
    } else {
        /* Offscreen callers have no swap to submit the frame. Window swaps
           already submit GL work; finishing first serializes CPU and GPU
           and can miss the next vblank without changing the image. */
        glFinish();
    }
}
/* plat_render_uploads — texture upload counter (count, pixels) for statistics. */
int plat_render_uploads(int *pixels) { if (pixels) *pixels = g_up_px; return g_up_n; }   /* v2.16: счётчик загрузок текстур (статистика) */
/* plat_blit2d — copies a rectangle of texture tex to the logical frame at (dx, dy) (2D screens). */
void plat_blit2d(int tex, int sx, int sy, int sw, int sh, int dx, int dy) {
    if (!g_ok || tex <= 0 || tex >= MAX_TEX || !g_tex[tex].id) return;
    float tw = (float)g_tex[tex].w, th = (float)g_tex[tex].h;
    float u0 = sx / tw, v0 = sy / th, u1 = (sx + sw) / tw, v1 = (sy + sh) / th;
    float x0 = (float)dx, y0 = (float)dy, x1 = (float)(dx + sw), y1 = (float)(dy + sh);
    plat_vertex q[6];
    #define V(i, x, y, u, v) q[i] = (plat_vertex){ x, y, 0.f, 1.f, 0xFFFFFFFFu, 0, u, v }
    V(0, x0, y0, u0, v0); V(1, x1, y0, u1, v0); V(2, x1, y1, u1, v1);
    V(3, x0, y0, u0, v0); V(4, x1, y1, u1, v1); V(5, x0, y1, u0, v1);
    int sv = g_cur, szt = g_zt, sb = g_blend, sbs = g_bs, sbd = g_bd;
    g_cur = tex; g_zt = 0; g_blend = 1; g_bs = 5; g_bd = 6;
    draw(q, 6, GL_TRIANGLES);
    g_cur = sv; g_zt = szt; g_blend = sb; g_bs = sbs; g_bd = sbd;
}
/* plat_render_readback — reads the frame back as RGBA (screenshots / tests).  Returns 0 on success, -1 on failure. */
int plat_render_readback(uint32_t *out) {
    if (!g_ok || !out) return -1;
    compose();   /* v2.16: кадр — после resolve/пост-прохода (offscreen-тесты зовут без plat_flip) */
    glFinish(); glPixelStorei(GL_PACK_ALIGNMENT, 1);
    int W = g_dw, H = g_dh;   /* v2.14: весь буфер окна (с полосами), plat_render_size */
    uint32_t *tmp = malloc((size_t)W * H * 4); if (!tmp) return -1;
    if (g_fbo) glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, tmp);
    if (g_fbo) glBindFramebuffer(GL_FRAMEBUFFER, target_fbo());
    for (int y = 0; y < H; y++) memcpy(out + (size_t)y * W, tmp + (size_t)(H - 1 - y) * W, (size_t)W * 4);
    for (size_t i = 0; i < (size_t)W * H; i++) out[i] |= 0xFF000000u;   /* у экрана (Glide/DirectDraw) нет альфы: пиксель кадра всегда непрозрачен */
    free(tmp); return 0;
}
