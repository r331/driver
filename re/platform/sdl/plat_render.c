/* Рендер-бэкенд OpenGL 3.3 core. Игра шлёт уже преобразованные вершины (как D3D TLVERTEX):
   x,y — пиксели окна, z 0..1, rhw = 1/w; шейдер восстанавливает перспективно-корректные интерполяции.
   GL-функции берутся через get_proc (SDL_GL_GetProcAddress или OSMesaGetProcAddress), без линковки с libGL. */
#include "../plat.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    GL_NEVER = 0x0200, GL_LESS = 0x0201, GL_EQUAL = 0x0202, GL_GREATER = 0x0204, GL_NOTEQUAL = 0x0205, GL_GEQUAL = 0x0206, GL_SCISSOR_TEST = 0x0C11
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
 X(void, DrawArrays, (GLenum, GLint, GLsizei)) X(void, ClearDepth, (double))
#define DECL(r, n, a) static r (*gl##n) a;
GLFUNCS(DECL)

static const char *VS =
 "#version 330 core\n"
 "layout(location=0) in vec4 aPos; layout(location=1) in vec4 aCol; layout(location=2) in vec4 aSpec; layout(location=3) in vec2 aUV;\n"
 "uniform vec2 uView; out vec4 vCol; out vec3 vSpec; out vec2 vUV;\n"
 "void main(){ float rhw = aPos.w == 0.0 ? 1.0 : aPos.w; float w = 1.0 / rhw;\n"
 "  vec3 n = vec3(aPos.x / uView.x * 2.0 - 1.0, 1.0 - aPos.y / uView.y * 2.0, aPos.z * 2.0 - 1.0);\n"
 "  gl_Position = vec4(n * w, w); vCol = aCol.bgra; vSpec = aSpec.bgr; vUV = aUV; }\n";
/* v2.01: стадия 0 текстур D3D (COLOROP/ALPHAOP, ARG1/ARG2: 0 diffuse, 1 current, 2 texture) и альфа-тест D3DCMP по ALPHAREF;
   op 0 (не задан) — прежнее поведение: modulate, альфа-тест a < 0.5 */
static const char *FS =
 "#version 330 core\n"
 "in vec4 vCol; in vec3 vSpec; in vec2 vUV; uniform sampler2D uTex; uniform int uAlphaTest; out vec4 oCol;\n"
 "uniform ivec3 uCOp; uniform ivec3 uAOp; uniform int uAFunc; uniform float uARef;\n"
 "vec4 arg(int a, vec4 t){ return a == 2 ? t : vCol; }\n"
 "float sel(int op, float a1, float a2){ if (op == 1) return vCol.a; if (op == 2) return a1; if (op == 3) return a2;\n"
 "  float m = a1 * a2; return op == 5 ? m * 2.0 : (op == 6 ? m * 4.0 : m); }\n"
 "void main(){ vec4 t = texture(uTex, vUV); vec4 c;\n"
 "  if (uCOp.x == 0) c.rgb = vCol.rgb * t.rgb; else if (uCOp.x == 1) c.rgb = vCol.rgb;\n"
 "  else { vec3 a1 = arg(uCOp.y, t).rgb, a2 = arg(uCOp.z, t).rgb; c.rgb = uCOp.x == 2 ? a1 : (uCOp.x == 3 ? a2 : a1 * a2 * (uCOp.x == 5 ? 2.0 : (uCOp.x == 6 ? 4.0 : 1.0))); }\n"
 "  if (uAOp.x == 0) c.a = vCol.a * t.a; else c.a = clamp(sel(uAOp.x, arg(uAOp.y, t).a, arg(uAOp.z, t).a), 0.0, 1.0);\n"
 "  if (uAlphaTest != 0) { float a = c.a; bool ok = true;\n"
 "    if (uAFunc == 0) ok = a >= 0.5; else if (uAFunc == 1) ok = false; else if (uAFunc == 2) ok = a < uARef; else if (uAFunc == 3) ok = a == uARef;\n"
 "    else if (uAFunc == 4) ok = a <= uARef; else if (uAFunc == 5) ok = a > uARef; else if (uAFunc == 6) ok = a != uARef; else if (uAFunc == 7) ok = a >= uARef;\n"
 "    if (!ok) discard; }\n"
 "  oCol = vec4(clamp(c.rgb, 0.0, 1.0) + vSpec, c.a); }\n";

typedef struct { int w, h; unsigned id; } tex_t;
#define MAX_TEX 4096
static tex_t g_tex[MAX_TEX];
static int g_ok, g_w, g_h, g_cur;
static unsigned g_prog, g_vao, g_vbo, g_white;
static int g_uAlphaTest, g_at = 1, g_uView, g_uTex, g_zt = 1, g_zw = 1, g_blend, g_bs = 5, g_bd = 6;
static int g_zf = 4, g_vp[4], g_vpset, g_rs[64], g_tss[8][32], g_uCOp, g_uAOp, g_uAFunc, g_uARef, g_af, g_aref;
static void (*g_swap)(void);

static unsigned blendf(int d3d) {
    static const unsigned m[11] = { GL_ONE, GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                                    GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR };
    return (d3d >= 1 && d3d <= 10) ? m[d3d] : GL_ONE;
}
static unsigned compile(unsigned type, const char *src) {
    unsigned s = glCreateShader(type); glShaderSource(s, 1, &src, NULL); glCompileShader(s);
    GLint ok = 0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) { char log[1024]; glGetShaderInfoLog(s, sizeof log, NULL, log); plat_log("GL shader: %s\n", log); return 0; }
    return s;
}
static void apply_state(void) {
    static const unsigned zf[9] = { GL_LEQUAL, GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS };
    if (g_zt) { glEnable(GL_DEPTH_TEST); glDepthFunc(zf[g_zf >= 1 && g_zf <= 8 ? g_zf : 4]); } else glDisable(GL_DEPTH_TEST);
    if (g_vpset) { glEnable(GL_SCISSOR_TEST); glScissor(g_vp[0], g_h - g_vp[1] - g_vp[3], g_vp[2], g_vp[3]); } else glDisable(GL_SCISSOR_TEST);
    glDepthMask(g_zw ? 1 : 0);
    if (g_blend) { glEnable(GL_BLEND); glBlendFunc(blendf(g_bs), blendf(g_bd)); } else glDisable(GL_BLEND);
}
int plat_render_attach(void *(*get_proc)(const char *), void (*swap)(void), int w, int h) {
#define LOAD(r, n, a) if (!(gl##n = (r (*) a)get_proc("gl" #n))) { plat_log("GL: нет gl" #n "\n"); return -1; }
    GLFUNCS(LOAD)
    unsigned vs = compile(GL_VERTEX_SHADER, VS), fs = compile(GL_FRAGMENT_SHADER, FS);
    if (!vs || !fs) return -2;
    g_prog = glCreateProgram(); glAttachShader(g_prog, vs); glAttachShader(g_prog, fs); glLinkProgram(g_prog);
    GLint ok = 0; glGetProgramiv(g_prog, GL_LINK_STATUS, &ok);
    if (!ok) { char log[1024]; glGetProgramInfoLog(g_prog, sizeof log, NULL, log); plat_log("GL link: %s\n", log); return -3; }
    g_uView = glGetUniformLocation(g_prog, "uView"); g_uTex = glGetUniformLocation(g_prog, "uTex"); g_uAlphaTest = glGetUniformLocation(g_prog, "uAlphaTest");
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
    g_w = w; g_h = h; g_swap = swap; g_ok = 1; g_cur = 0;
    memset(g_tss, 0, sizeof g_tss); g_af = 0; g_aref = 0;   /* v2.01: новый контекст — состояние стадий с нуля (op 0 — прежнее поведение) */
    g_tss[0][2] = 2; g_tss[0][3] = 1; g_tss[0][5] = 2; g_tss[0][6] = 1;   /* v2.01: умолчания D3D: ARG1 = TEXTURE, ARG2 = CURRENT */
    glViewport(0, 0, w, h);
    plat_log("GL %s\n", (const char *)glGetString(GL_VERSION));
    return 0;
}
void plat_render_shutdown(void) { g_ok = 0; memset(g_tex, 0, sizeof g_tex); g_swap = NULL; }

int plat_tex_create(int w, int h, const uint32_t *rgba) {
    if (!g_ok || w <= 0 || h <= 0) return 0;
    for (int i = 1; i < MAX_TEX; i++) if (!g_tex[i].id) {
        glGenTextures(1, &g_tex[i].id); glBindTexture(GL_TEXTURE_2D, g_tex[i].id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        g_tex[i].w = w; g_tex[i].h = h; return i;
    }
    return 0;
}
void plat_tex_update(int tex, int w, int h, const uint32_t *rgba) {   /* v2.01: новая картинка той же текстуры */
    if (!g_ok || tex <= 0 || tex >= MAX_TEX || !g_tex[tex].id || w <= 0 || h <= 0) return;
    glBindTexture(GL_TEXTURE_2D, g_tex[tex].id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
    g_tex[tex].w = w; g_tex[tex].h = h;
}
void plat_clear_rect(uint32_t c, int x, int y, int w, int h) {   /* v2.01: Blt COLORFILL задней поверхности */
    if (!g_ok || w <= 0 || h <= 0) return;
    glEnable(GL_SCISSOR_TEST); glScissor(x, g_h - y - h, w, h);
    glClearColor(((c >> 16) & 255) / 255.f, ((c >> 8) & 255) / 255.f, (c & 255) / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT); glDisable(GL_SCISSOR_TEST);
}
void plat_tex_bind(int tex) { g_cur = (tex > 0 && tex < MAX_TEX && g_tex[tex].id) ? tex : 0; }
void plat_tex_free(int tex) {
    if (!g_ok || tex <= 0 || tex >= MAX_TEX || !g_tex[tex].id) return;
    glDeleteTextures(1, &g_tex[tex].id); memset(&g_tex[tex], 0, sizeof g_tex[tex]); if (g_cur == tex) g_cur = 0;
}
void plat_set_blend(int e, int s, int d) { g_blend = e; if (e) { g_bs = s; g_bd = d; } }
void plat_set_zbuffer(int t, int w) { g_zt = t; g_zw = w; }
void plat_scene_begin(void) {}
void plat_scene_end(void) {}
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
void plat_set_tex_stage(int stage, int type, uint32_t value) {
    if (stage >= 0 && stage < 8 && type >= 0 && type < 32) g_tss[stage][type] = (int)value;
}
void plat_set_viewport(int x, int y, int w, int h) {
    g_vp[0] = x; g_vp[1] = y; g_vp[2] = w; g_vp[3] = h; g_vpset = (w > 0 && h > 0 && !(x == 0 && y == 0 && w >= g_w && h >= g_h));
}
uint32_t plat_get_tex_stage(int stage, int type) {
    if (stage >= 0 && stage < 8 && type >= 0 && type < 32) return (uint32_t)g_tss[stage][type];
    return 0;
}
static int g_dp_calls, g_dp_type, g_dp_count;
static void draw(const plat_vertex *v, int count, unsigned mode);
void plat_draw_prim(int ptype, const plat_vertex *v, int count) {
    g_dp_calls++; g_dp_type = ptype; g_dp_count = count;
    if (getenv("RE_TRACE_DD") && g_dp_calls < 60 && v && count >= 3) fprintf(stderr, "[gl] v1 %.1f %.1f uv %.5f %.5f v2 %.1f %.1f uv %.5f %.5f\n", v[1].x, v[1].y, v[1].u, v[1].v, v[2].x, v[2].y, v[2].u, v[2].v);
    if (getenv("RE_TRACE_DD") && g_dp_calls < 60) fprintf(stderr, "[gl] draw_prim %d n=%d tex %d v0 %.1f %.1f %.3f %.3f col %08x uv %.3f %.3f zt %d zf %d bl %d %d %d at %d vp %d %d %d %d %d tss %d %d %d %d\n", ptype, count, g_cur,
        v ? v[0].x : 0, v ? v[0].y : 0, v ? v[0].z : 0, v ? v[0].rhw : 0, v ? v[0].color : 0, v ? v[0].u : 0, v ? v[0].v : 0, g_zt, g_zf, g_blend, g_bs, g_bd, g_at, g_vpset, g_vp[0], g_vp[1], g_vp[2], g_vp[3], g_tss[0][1], g_tss[0][2], g_tss[0][3], g_tss[0][4]);
    if (ptype == 4) plat_draw_tris(v, count);
    else if (ptype == 2) plat_draw_lines(v, count);
}
int plat_draw_prim_last(int *ptype, int *count) { if (ptype) *ptype = g_dp_type; if (count) *count = g_dp_count; return g_dp_calls; }
static void draw(const plat_vertex *v, int count, unsigned mode) {
    apply_state();
    glUseProgram(g_prog); glUniform2f(g_uView, (float)g_w, (float)g_h); glUniform1i(g_uTex, 0); glUniform1i(g_uAlphaTest, g_at);
    glUniform3i(g_uCOp, g_tss[0][1], g_tss[0][2], g_tss[0][3]); glUniform3i(g_uAOp, g_tss[0][4], g_tss[0][5], g_tss[0][6]);
    glUniform1i(g_uAFunc, g_af >= 1 && g_af <= 8 ? g_af : 0); glUniform1f(g_uARef, (float)g_aref / 255.f);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_cur ? g_tex[g_cur].id : g_white);
    glBindVertexArray(g_vao); glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)count * sizeof(plat_vertex), v, GL_STREAM_DRAW);
    glDrawArrays(mode, 0, count);
}
void plat_draw_tris(const plat_vertex *v, int count) { if (g_ok && v && count >= 3) draw(v, count - count % 3, GL_TRIANGLES); }
void plat_draw_lines(const plat_vertex *v, int count) { if (g_ok && v && count >= 2) draw(v, count - count % 2, GL_LINES); }
void plat_clear(uint32_t c, int clear_z) {
    if (!g_ok) return;
    glDepthMask(1); glClearColor(((c >> 16) & 255) / 255.f, ((c >> 8) & 255) / 255.f, (c & 255) / 255.f, (c >> 24) / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | (clear_z ? GL_DEPTH_BUFFER_BIT : 0));
}
void plat_set_current_viewport(void) {}
int plat_get_render_state(int state) { return (state >= 0 && state < 64) ? g_rs[state] : 0; }
void plat_clear_depth(void *viewport, int x, int y, int w, int h, float z) {
    (void)viewport;
    if (!g_ok) return;
    glEnable(GL_SCISSOR_TEST); glScissor(x, g_h - y - h, w, h);
    glDepthMask(1); glClearDepth((double)z); glClear(GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
}
void plat_flip(void) { if (!g_ok) return; glFinish(); if (g_swap) { plat_frame_tick("flip"); g_swap(); } }
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
int plat_render_readback(uint32_t *out) {
    if (!g_ok || !out) return -1;
    glFinish(); glPixelStorei(GL_PACK_ALIGNMENT, 1);
    uint32_t *tmp = malloc((size_t)g_w * g_h * 4); if (!tmp) return -1;
    glReadPixels(0, 0, g_w, g_h, GL_RGBA, GL_UNSIGNED_BYTE, tmp);
    for (int y = 0; y < g_h; y++) memcpy(out + (size_t)y * g_w, tmp + (size_t)(g_h - 1 - y) * g_w, (size_t)g_w * 4);
    for (size_t i = 0; i < (size_t)g_w * g_h; i++) out[i] |= 0xFF000000u;   /* у экрана (Glide/DirectDraw) нет альфы: пиксель кадра всегда непрозрачен */
    free(tmp); return 0;
}
