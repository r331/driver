/* v2.31: детальные 3D-меши фасадов — см. plat_detail.h. glTF: cgltf (MIT, third_party/cgltf.h), JSON записи — jsmn из cgltf. */
#include "plat_detail.h"
#include "plat_texpack.h"
#include "plat_gfx.h"
#include "../plat.h"
#include "../../game/ported12.h"
#include "../../game/ported23.h"
#include "../../game/ported33.h"
#include "../../game/ported43.h"
#include "../../game/ported44.h"
#include "../../game/cartab.h"
#include "../../game/ported77.h"
#include "../../game/ported85.h"
#include "../../game/ported86.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#define CGLTF_IMPLEMENTATION
#include "../../third_party/cgltf.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

int re_detail_capture;

#define DMAX_ENT 512
#define DMAX_INST 1024
typedef struct {
    char level[64];
    int page, pal;                 /* pal −1 — любая (16-битная страница) */
    float u0, v0, u1, v1;          /* uv_rect_256 */
    float w, h;                    /* размер меша по x, y (метры) */
    float lod;                     /* метры */
    int mesh;                      /* plat_mesh или 0 */
    int partial_logged;
    char glb[512];
} dent_t;
typedef struct {
    int e;
    double o[3], x[3], y[3];
    double umin, vmin, umax, vmax;
    double col[3]; int ncol, ntri;
} dinst_t;

static dent_t g_ent[DMAX_ENT];
static int g_nent, g_state = -1;   /* −1 — не проверено, 0 — выключено */
static char g_level[128];
static unsigned char g_pagemask[256];
static dinst_t g_inst[DMAX_INST];
static int g_ninst, g_log, g_frame;
static long g_st_tri, g_st_pal, g_st_drawn, g_st_partial, g_st_far;
static double g_lodk = 1.0, g_zoff = 0.08, g_pofs = 2.0;
static int g_partial_mode = 1;

static int env_on(void) { const char *e = getenv("DRIVER_DETAIL"); return !(e && (e[0] == '0' || !strcmp(e, "off"))); }

/* ---------- JSON (jsmn из cgltf) ---------- */
static int tskip(const jsmntok_t *t, int i) {   /* индекс токена после поддерева i */
    int n = t[i].size, j = i + 1;
    if (t[i].type == JSMN_OBJECT) { for (int k = 0; k < n; k++) { j = tskip(t, j); j = tskip(t, j); } }
    else if (t[i].type == JSMN_ARRAY) { for (int k = 0; k < n; k++) j = tskip(t, j); }
    return j;
}
static int teq(const char *js, const jsmntok_t *t, const char *s) {
    int n = (int)(t->end - t->start); return t->type == JSMN_STRING && (int)strlen(s) == n && !strncmp(js + t->start, s, (size_t)n);
}
static int tfind(const char *js, const jsmntok_t *t, int obj, const char *key) {   /* значение ключа в объекте или −1 */
    if (obj < 0 || t[obj].type != JSMN_OBJECT) return -1;
    int j = obj + 1;
    for (int k = 0; k < t[obj].size; k++) { if (teq(js, &t[j], key)) return j + 1; j = tskip(t, j + 1); }
    return -1;
}
static double tnum(const char *js, const jsmntok_t *t, int i, double def) {
    if (i < 0 || (t[i].type != JSMN_PRIMITIVE && t[i].type != JSMN_STRING)) return def;
    char b[64]; int n = (int)(t[i].end - t[i].start); if (n <= 0 || n > 63) return def;
    memcpy(b, js + t[i].start, (size_t)n); b[n] = 0;
    if (!strcmp(b, "null")) return def;
    char *e; double v = strtod(b, &e); return e == b ? def : v;
}
static void tstr(const char *js, const jsmntok_t *t, int i, char *out, int cap) {
    out[0] = 0; if (i < 0 || t[i].type != JSMN_STRING) return;
    int n = (int)(t[i].end - t[i].start); if (n >= cap) n = cap - 1; memcpy(out, js + t[i].start, (size_t)n); out[n] = 0;
}
/* поле записи: сначала в "key", затем в самой записи */
static int efind(const char *js, const jsmntok_t *t, int ent, const char *key) {
    int k = tfind(js, t, ent, "key"), v = tfind(js, t, k, key);
    return v >= 0 ? v : tfind(js, t, ent, key);
}

/* ---------- glb ---------- */
static int load_glb(dent_t *e) {
    cgltf_options opt; memset(&opt, 0, sizeof opt);
    cgltf_data *d = NULL;
    if (cgltf_parse_file(&opt, e->glb, &d) != cgltf_result_success) { plat_log("[detail] %s: не glTF\n", e->glb); return 0; }
    if (cgltf_load_buffers(&opt, d, e->glb) != cgltf_result_success) { plat_log("[detail] %s: буферы не прочитаны\n", e->glb); cgltf_free(d); return 0; }
    /* все примитивы-треугольники всех мешей в одну сетку; текстура — baseColor первого материала с текстурой */
    size_t nv = 0, ni = 0;
    for (size_t m = 0; m < d->meshes_count; m++) for (size_t p = 0; p < d->meshes[m].primitives_count; p++) {
        cgltf_primitive *pr = &d->meshes[m].primitives[p];
        if (pr->type != cgltf_primitive_type_triangles) continue;
        for (size_t a = 0; a < pr->attributes_count; a++) if (pr->attributes[a].type == cgltf_attribute_type_position) nv += pr->attributes[a].data->count;
        ni += pr->indices ? pr->indices->count : 0;
    }
    float *pos = (float *)calloc(nv * 3 + 1, sizeof(float)), *nrm = (float *)calloc(nv * 3 + 1, sizeof(float)), *uv = (float *)calloc(nv * 2 + 1, sizeof(float));
    uint32_t *idx = (uint32_t *)calloc(ni + 1, sizeof(uint32_t));
    uint32_t *rgba = NULL; int tw = 0, th = 0;
    float bmax[2] = { 0, 0 };
    size_t vb = 0, ib = 0;
    for (size_t m = 0; m < d->meshes_count && pos && nrm && uv && idx; m++) for (size_t p = 0; p < d->meshes[m].primitives_count; p++) {
        cgltf_primitive *pr = &d->meshes[m].primitives[p];
        if (pr->type != cgltf_primitive_type_triangles || !pr->indices) continue;
        size_t cnt = 0;
        for (size_t a = 0; a < pr->attributes_count; a++) {
            cgltf_attribute *at = &pr->attributes[a];
            if (at->type == cgltf_attribute_type_position) { cnt = at->data->count; cgltf_accessor_unpack_floats(at->data, pos + vb * 3, cnt * 3); }
            else if (at->type == cgltf_attribute_type_normal) cgltf_accessor_unpack_floats(at->data, nrm + vb * 3, at->data->count * 3);
            else if (at->type == cgltf_attribute_type_texcoord && at->index == 0) cgltf_accessor_unpack_floats(at->data, uv + vb * 2, at->data->count * 2);
        }
        for (size_t i = 0; i < pr->indices->count; i++) idx[ib + i] = (uint32_t)(vb + cgltf_accessor_read_index(pr->indices, i));
        ib += pr->indices->count; vb += cnt;
        if (!rgba && pr->material && pr->material->has_pbr_metallic_roughness) {
            cgltf_texture *tx = pr->material->pbr_metallic_roughness.base_color_texture.texture;
            if (tx && tx->image && tx->image->buffer_view) {
                cgltf_buffer_view *bv = tx->image->buffer_view;
                rgba = re_texpack_decode_png((const uint8_t *)bv->buffer->data + bv->offset, (int)bv->size, &tw, &th);
            }
        }
    }
    for (size_t i = 0; i < vb; i++) { if (pos[i * 3] > bmax[0]) bmax[0] = pos[i * 3]; if (pos[i * 3 + 1] > bmax[1]) bmax[1] = pos[i * 3 + 1]; }
    if (e->w <= 0) e->w = bmax[0];
    if (e->h <= 0) e->h = bmax[1];
    int mesh = (vb && ib) ? plat_mesh_create(pos, nrm, uv, (int)vb, idx, (int)ib, rgba, tw, th) : 0;
    plat_log("[detail] %s: %d вершин, %d треугольников, текстура %dx%d, размер %.2fx%.2f м, меш %d\n", e->glb, (int)vb, (int)(ib / 3), tw, th, e->w, e->h, mesh);
    free(pos); free(nrm); free(uv); free(idx); free(rgba); cgltf_free(d);
    return mesh;
}

/* ---------- detail.json ---------- */
static char *read_file(const char *path, long *len) {
    FILE *f = fopen(path, "rb"); if (!f) return NULL;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    char *b = (char *)malloc((size_t)n + 1); if (!b) { fclose(f); return NULL; }
    if (fread(b, 1, (size_t)n, f) != (size_t)n) { free(b); fclose(f); return NULL; }
    b[n] = 0; fclose(f); *len = n; return b;
}
static void parse_entry(const char *js, const jsmntok_t *t, int ent, const char *dir, const char *level) {
    if (g_nent >= DMAX_ENT || t[ent].type != JSMN_OBJECT) return;
    dent_t e; memset(&e, 0, sizeof e);
    tstr(js, t, efind(js, t, ent, "level"), e.level, sizeof e.level);
    if (e.level[0] && strcasecmp(e.level, level) != 0) return;
    char pf[128]; tstr(js, t, efind(js, t, ent, "page_file"), pf, sizeof pf);
    e.page = (int)tnum(js, t, efind(js, t, ent, "page_index"), -1);
    if (e.page < 0 && pf[0] == 'p') e.page = atoi(pf + 1);
    e.pal = (int)tnum(js, t, efind(js, t, ent, "palette_slot"), -2);
    if (e.pal == -2) { const char *c = strstr(pf, "_c"); e.pal = c ? atoi(c + 2) : -1; }
    int r = efind(js, t, ent, "uv_rect_256");
    if (r < 0 || t[r].type != JSMN_ARRAY || t[r].size != 4 || e.page < 0 || e.page > 255) { plat_log("[detail] запись без страницы/uv_rect_256 — пропуск\n"); return; }
    e.u0 = (float)tnum(js, t, r + 1, 0); e.v0 = (float)tnum(js, t, r + 2, 0); e.u1 = (float)tnum(js, t, r + 3, 0); e.v1 = (float)tnum(js, t, r + 4, 0);
    e.lod = (float)tnum(js, t, tfind(js, t, ent, "lod_distance_hint"), 80);
    /* размер меша: mesh_size_m [W,H], facade_width_m/facade_height_m или mesh_space {w,h}/{width,height}; иначе — по габаритам glb */
    int ms = tfind(js, t, ent, "mesh_size_m");
    if (ms >= 0 && t[ms].type == JSMN_ARRAY && t[ms].size >= 2) { e.w = (float)tnum(js, t, ms + 1, 0); e.h = (float)tnum(js, t, ms + 2, 0); }
    if (e.w <= 0) { e.w = (float)tnum(js, t, tfind(js, t, ent, "facade_width_m"), 0); e.h = (float)tnum(js, t, tfind(js, t, ent, "facade_height_m"), 0); }
    int sp = tfind(js, t, ent, "mesh_space");
    if (sp >= 0 && t[sp].type == JSMN_OBJECT && e.w <= 0) {
        e.w = (float)tnum(js, t, tfind(js, t, sp, "w"), tnum(js, t, tfind(js, t, sp, "width"), 0));
        e.h = (float)tnum(js, t, tfind(js, t, sp, "h"), tnum(js, t, tfind(js, t, sp, "height"), 0));
    }
    char mesh[256]; tstr(js, t, tfind(js, t, ent, "mesh"), mesh, sizeof mesh);
    if (!mesh[0]) tstr(js, t, tfind(js, t, ent, "glb"), mesh, sizeof mesh);
    if (!mesh[0]) { plat_log("[detail] запись p%03d без mesh — пропуск\n", e.page); return; }
    snprintf(e.glb, sizeof e.glb, "%s/%s", dir, mesh);
    if (!(e.mesh = load_glb(&e))) return;
    if (e.w <= 0 || e.h <= 0 || e.u1 <= e.u0 || e.v1 <= e.v0) { plat_log("[detail] %s: неверный размер/прямоугольник\n", e.glb); plat_mesh_free(e.mesh); return; }
    g_ent[g_nent++] = e; g_pagemask[e.page] = 1;
    plat_log("[detail] запись %d: p%03d палитра %d uv %.0f,%.0f..%.0f,%.0f lod %.0f м\n", g_nent - 1, e.page, e.pal, e.u0, e.v0, e.u1, e.v1, e.lod);
}
static void unload(void) {
    for (int i = 0; i < g_nent; i++) plat_mesh_free(g_ent[i].mesh);
    g_nent = 0; memset(g_pagemask, 0, sizeof g_pagemask);
}
static void load_level(const char *level) {
    unload();
    char dir[1024]; dir[0] = 0;
    const char *ov = getenv("DRIVER_DETAIL_DIR"), *pack = re_texpack_dir();
    char path[1200]; long len = 0; char *js = NULL;
    if (ov && ov[0]) { snprintf(dir, sizeof dir, "%s", ov); snprintf(path, sizeof path, "%s/detail.json", dir); js = read_file(path, &len); }
    else if (pack) {
        char lv[3][128]; snprintf(lv[0], 128, "%s", level);
        for (int k = 0; k < 128; k++) { lv[1][k] = (char)tolower((unsigned char)level[k]); lv[2][k] = (char)toupper((unsigned char)level[k]); if (!level[k]) break; }
        lv[1][127] = lv[2][127] = 0;
        for (int k = 0; k < 3 && !js; k++) { snprintf(dir, sizeof dir, "%s/%s/detail", pack, lv[k]); snprintf(path, sizeof path, "%s/detail.json", dir); js = read_file(path, &len); }
    }
    if (!js) { if (g_log) plat_log("[detail] %s: нет detail.json\n", level); return; }
    jsmn_parser p; jsmn_init(&p);
    int nt = jsmn_parse(&p, js, (size_t)len, NULL, 0);
    jsmntok_t *t = nt > 0 ? (jsmntok_t *)calloc((size_t)nt + 1, sizeof(jsmntok_t)) : NULL;
    if (t) { jsmn_init(&p); nt = jsmn_parse(&p, js, (size_t)len, t, (size_t)nt); }
    if (!t || nt <= 0) { plat_log("[detail] %s: ошибка JSON\n", path); free(t); free(js); return; }
    int arr = -1;
    if (t[0].type == JSMN_ARRAY) arr = 0;
    else if (t[0].type == JSMN_OBJECT) {
        static const char *keys[] = { "entries", "details", "items", "meshes" };
        for (int k = 0; k < 4 && arr < 0; k++) { int v = tfind(js, t, 0, keys[k]); if (v >= 0 && t[v].type == JSMN_ARRAY) arr = v; }
        if (arr < 0) parse_entry(js, t, 0, dir, level);   /* одна запись (как out/detail_entry.json) */
    }
    if (arr >= 0) { int j = arr + 1; for (int k = 0; k < t[arr].size; k++) { parse_entry(js, t, j, dir, level); j = tskip(t, j); } }
    plat_log("[detail] %s: %d записей из %s\n", level, g_nent, path);
    free(t); free(js);
}

/* ---------- кадр ---------- */
void re_detail_frame_begin(void) {
    re_detail_capture = 0;
    if (g_state < 0) {
        g_state = env_on();
        g_log = getenv("DRIVER_DETAIL_LOG") ? atoi(getenv("DRIVER_DETAIL_LOG")) : 0;
        const char *s;
        if ((s = getenv("DRIVER_DETAIL_LOD"))) g_lodk = atof(s);
        if ((s = getenv("DRIVER_DETAIL_ZOFF"))) g_zoff = atof(s);
        if ((s = getenv("DRIVER_DETAIL_POFS"))) g_pofs = atof(s);
        if ((s = getenv("DRIVER_DETAIL_PARTIAL"))) g_partial_mode = atoi(s);
        if (!g_state) plat_log("[detail] выключено (DRIVER_DETAIL=0)\n");
    }
    if (!g_state) return;
    if (!re_texpack_dir() && !getenv("DRIVER_DETAIL_DIR")) return;   /* только с HD-паком */
    char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
    if (strcmp(lv, g_level) != 0) { snprintf(g_level, sizeof g_level, "%s", lv); load_level(lv); }
    g_ninst = 0;
    re_detail_capture = g_nent > 0;
}
static double dot3(const double *a, const double *b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
static double len3(const double *a) { return sqrt(dot3(a, a)); }

/* Exercise matching with a synthetic facade, including the stale page/UVs
   retained by flat and Gouraud streetlight polygons. No GL objects are used. */
int re_detail_selftest(void) {
    dent_t entry = g_ent[0]; dinst_t instance = g_inst[0];
    int nent = g_nent, ninst = g_ninst, log = g_log;
    unsigned char mask = g_pagemask[6];
    long tris = g_st_tri, pals = g_st_pal;
    int page = P86_CurTex, state = P85_StateDirty;
    p85_rv saved[3]; double camera[3][3]; int valid[3];
    memcpy(saved, P85_RV, sizeof saved);
    for (int i = 0; i < 3; i++) valid[i] = P85_GetCameraPoint(&P85_RV[i], camera[i]);
    memset(&g_ent[0], 0, sizeof g_ent[0]);
    g_ent[0].page = 6; g_ent[0].pal = -1;
    g_ent[0].u1 = 128; g_ent[0].v1 = 64; g_ent[0].w = 8; g_ent[0].h = 4;
    g_nent = 1; g_ninst = 0; g_log = 0; g_pagemask[6] = 1; P86_CurTex = 6;
    for (int i = 0; i < 3; i++) {
        p85_rv *v = &P85_RV[i];
        memset(v, 0, sizeof *v);
        v->x = i == 1 ? 420 : 320; v->y = i == 2 ? 340 : 240;
        v->oow = .001f;
        v->tmu[0] = (i == 1 ? 128 : 0) * v->oow;
        v->tmu[1] = (i == 2 ? 64 : 0) * v->oow;
        P85_NoteCameraPoint(i, i == 1 ? 800 : 0, i == 2 ? 400 : 0, 1000);
    }
    int failed = 0;
    P85_StateDirty = 0;
    re_detail_tri(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
    if (g_ninst != 0) failed++;
    P85_StateDirty = 4;
    re_detail_tri(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
    if (g_ninst != 1 || g_inst[0].ntri != 1) failed++;
    P85_StateDirty = 0;
    re_detail_tri(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
    if (g_ninst != 1 || g_inst[0].ntri != 1) failed++;
    for (int i = 0; i < 3; i++) {
        /* Invalidate the fixture's coordinate association before restoring it. */
        P85_RV[i].oow = -1;
        P85_NoteCameraPoint(i, 0, 0, 0);
        P85_RV[i] = saved[i];
        if (valid[i]) P85_NoteCameraPoint(i, camera[i][0], camera[i][1], camera[i][2]);
    }
    g_ent[0] = entry; g_inst[0] = instance;
    g_nent = nent; g_ninst = ninst; g_log = log; g_pagemask[6] = mask;
    g_st_tri = tris; g_st_pal = pals; P86_CurTex = page; P85_StateDirty = state;
    if (failed) fprintf(stderr, "facade texture-state failures: %d\n", failed);
    return failed != 0;
}

void re_detail_tri(const void *pa, const void *pb, const void *pc) {
    /* Flat/Gouraud polygons retain the last texture page and per-vertex UVs.
       They cannot identify a facade, even when those stale values match it. */
    if (P85_StateDirty != 4) return;
    int page = P86_CurTex;
    if (page < 0 || page > 255 || !g_pagemask[page]) return;
    const p85_rv *v[3] = { (const p85_rv *)pa, (const p85_rv *)pb, (const p85_rv *)pc };
    double uu[3], vv[3], P[3][3];
    for (int i = 0; i < 3; i++) {
        double w = v[i]->oow;
        if (!(w > 0)) return;
        uu[i] = v[i]->tmu[0] / w; vv[i] = v[i]->tmu[1] / w;
        /* Rounded TL screen positions and table-quantized reciprocal depth cannot
           provide a stable 3D anchor. Keep the pre-projection camera position. */
        if (!P85_GetCameraPoint(v[i], P[i])) return;
    }
    int pal = P12_01252b74;
    if (g_log >= 2) {   /* DRIVER_DETAIL_LOG=2: все треугольники страниц записей — UV/палитра (поиск полигонов) */
        static long n; if (n++ < 400 || n % 500 == 0)
            plat_log("[detail2] f%d p%03d pal %d uv (%.1f,%.1f) (%.1f,%.1f) (%.1f,%.1f) z %.0f\n", g_frame, page, pal, uu[0], vv[0], uu[1], vv[1], uu[2], vv[2], P[0][2]);
    }
    for (int ei = 0; ei < g_nent; ei++) {
        dent_t *e = &g_ent[ei];
        if (e->page != page) continue;
        int in = 1;
        for (int i = 0; i < 3 && in; i++) in = uu[i] >= e->u0 - 1 && uu[i] <= e->u1 + 1 && vv[i] >= e->v0 - 1 && vv[i] <= e->v1 + 1;
        if (!in) continue;
        if (e->pal >= 0 && e->pal != pal) { g_st_pal++; if (g_log && g_st_pal < 8) plat_log("[detail] p%03d: палитра %d ≠ %d\n", page, pal, e->pal); continue; }
        g_st_tri++;
        /* P(u,v) = A + u·Eu + v·Ev */
        double du1 = uu[1] - uu[0], dv1 = vv[1] - vv[0], du2 = uu[2] - uu[0], dv2 = vv[2] - vv[0], det = du1 * dv2 - du2 * dv1;
        if (fabs(det) < 1e-3) return;
        double Eu[3], Ev[3], A[3], O[3], X[3], Y[3];
        for (int k = 0; k < 3; k++) {
            double d1 = P[1][k] - P[0][k], d2 = P[2][k] - P[0][k];
            Eu[k] = (d1 * dv2 - d2 * dv1) / det; Ev[k] = (d2 * du1 - d1 * du2) / det;
            A[k] = P[0][k] - uu[0] * Eu[k] - vv[0] * Ev[k];
        }
        for (int k = 0; k < 3; k++) {
            O[k] = A[k] + e->u0 * Eu[k] + e->v1 * Ev[k];      /* (x, y) = (0, 0) ↔ (u0, v1) */
            X[k] = Eu[k] * (e->u1 - e->u0) / e->w;
            Y[k] = -Ev[k] * (e->v1 - e->v0) / e->h;           /* y вверх: от v1 к v0 */
        }
        double lx = len3(X), ly = len3(Y);
        if (!(lx > 0) || !(ly > 0) || fabs(dot3(X, Y)) > 0.5 * lx * ly) return;   /* вырожденная/сильно скошенная развёртка */
        /* дедупликация: та же запись, то же начало (±3 см), то же направление x */
        dinst_t *in2 = NULL;
        for (int i = 0; i < g_ninst && !in2; i++) {
            dinst_t *q = &g_inst[i];
            if (q->e != ei) continue;
            double d[3] = { q->o[0] - O[0], q->o[1] - O[1], q->o[2] - O[2] };
            if (len3(d) < 0.03 * lx && dot3(q->x, X) > 0.99 * len3(q->x) * lx) in2 = q;
        }
        if (!in2) {
            if (g_ninst >= DMAX_INST) return;
            in2 = &g_inst[g_ninst++]; memset(in2, 0, sizeof *in2);
            in2->e = ei; memcpy(in2->o, O, sizeof O); memcpy(in2->x, X, sizeof X); memcpy(in2->y, Y, sizeof Y);
            in2->umin = in2->vmin = 1e9; in2->umax = in2->vmax = -1e9;
        }
        for (int i = 0; i < 3; i++) {
            if (uu[i] < in2->umin) in2->umin = uu[i];
            if (uu[i] > in2->umax) in2->umax = uu[i];
            if (vv[i] < in2->vmin) in2->vmin = vv[i];
            if (vv[i] > in2->vmax) in2->vmax = vv[i];
            in2->col[0] += v[i]->r; in2->col[1] += v[i]->g; in2->col[2] += v[i]->b; in2->ncol++;
        }
        in2->ntri++;
        if (g_log && g_frame % 100 == 0 && g_st_tri < 4000)
            plat_log("[detail] f%d tri p%03d pal %d uv (%.1f,%.1f) (%.1f,%.1f) (%.1f,%.1f) z %.0f %.0f %.0f |x| %.1f |y| %.1f ед/м\n", g_frame, page, pal,
                     uu[0], vv[0], uu[1], vv[1], uu[2], vv[2], P[0][2], P[1][2], P[2][2], lx, ly);
        return;
    }
}
void re_detail_frame_end(void) {
    int was = re_detail_capture;
    re_detail_capture = 0;
    g_frame++;
    if (!was || g_ninst == 0) return;
    /* мир — в z-буфер до мешей (пакеты по слотам текстур), привязка текстуры игры восстанавливается, как в P33_EnsureRoom */
    void *keep = plat_stub_last_texture(NULL);
    P33_FlushBatches();
    plat_set_texture(0, keep);
    const float proj[4] = { (float)RE_OOW(1), P43_ScaleA, P43_OffX - P43_Half, P43_OffY - P43_Half };
    float zp[4];
    if (P23_ZBias == 0.0f) { zp[0] = 0; zp[1] = P23_ZScale_A; zp[2] = 0; zp[3] = 0; }
    else { zp[0] = 1; zp[1] = P23_ZBias; zp[2] = P23_ZNum; zp[3] = P23_ZDenA; }
    int drawn = 0, near_i = -1; double near_d = 1e30, near_sx = 0, near_sy = 0;
    for (int i = 0; i < g_ninst; i++) {
        dinst_t *q = &g_inst[i]; dent_t *e = &g_ent[q->e];
        /* покрытие прямоугольника: полигоны кадра (одной плоскости и развёртки) могут дать только часть uv_rect (здания Майами
           собирают этажи из половин прямоугольника) — тогда меш обрезается по покрытой части (отбрасывание фрагментов в шейдере) */
        const double tol = 3.5;   /* края полигонов часто отступают на 1–3 текселя от границы прямоугольника записи */
        float clip[4] = { -1e9f, -1e9f, 1e9f, 1e9f }; int part = 0;
        if (q->umin > e->u0 + tol) { clip[0] = (float)((q->umin - e->u0) / (e->u1 - e->u0) * e->w); part = 1; }
        if (q->umax < e->u1 - tol) { clip[2] = (float)((q->umax - e->u0) / (e->u1 - e->u0) * e->w); part = 1; }
        if (q->vmax < e->v1 - tol) { clip[1] = (float)((e->v1 - q->vmax) / (e->v1 - e->v0) * e->h); part = 1; }
        if (q->vmin > e->v0 + tol) { clip[3] = (float)((e->v1 - q->vmin) / (e->v1 - e->v0) * e->h); part = 1; }
        if (part) {
            g_st_partial++;
            if (g_log && e->partial_logged++ < 5) plat_log("[detail] p%03d: полигоны покрывают uv %.0f,%.0f..%.0f,%.0f из %.0f,%.0f..%.0f,%.0f — меш обрезан (x %.2f..%.2f, y %.2f..%.2f м)\n",
                                                        e->page, q->umin, q->vmin, q->umax, q->vmax, e->u0, e->v0, e->u1, e->v1, clip[0], clip[2], clip[1], clip[3]);
            if (g_partial_mode == 0) continue;   /* DRIVER_DETAIL_PARTIAL=0 — неполные копии пропускать */
        }
        double lx = len3(q->x), ly = len3(q->y), s = sqrt(lx * ly);
        double N[3] = { q->x[1] * q->y[2] - q->x[2] * q->y[1], q->x[2] * q->y[0] - q->x[0] * q->y[2], q->x[0] * q->y[1] - q->x[1] * q->y[0] };
        double ln = len3(N); if (!(ln > 0)) continue;
        double C[3]; for (int k = 0; k < 3; k++) C[k] = q->o[k] + q->x[k] * e->w * 0.5 + q->y[k] * e->h * 0.5;
        if (dot3(N, C) > 0) for (int k = 0; k < 3; k++) N[k] = -N[k];   /* наружу — к камере (камера в начале координат) */
        for (int k = 0; k < 3; k++) N[k] *= s / ln;
        double dist_m = len3(C) / s;
        if (dist_m > e->lod * g_lodk) { g_st_far++; continue; }
        float m16[16] = { (float)q->x[0], (float)q->x[1], (float)q->x[2], 0, (float)q->y[0], (float)q->y[1], (float)q->y[2], 0,
                          (float)N[0], (float)N[1], (float)N[2], 0, (float)q->o[0], (float)q->o[1], (float)q->o[2], 1 };
        float tint[3];
        for (int k = 0; k < 3; k++) { double c = q->col[k] / (q->ncol * 255.0); tint[k] = (float)(c > 1 ? 1 : c < 0 ? 0 : c); }
        if (plat_get_tex_stage(0, 1) == 5) for (int k = 0; k < 3; k++) tint[k] *= 2.0f;   /* MODULATE2X */
        plat_mesh_draw(e->mesh, m16, proj, zp, tint, part ? clip : NULL, (float)g_zoff, (float)g_pofs);
        drawn++;
        if (dist_m < near_d && C[2] > 0) { near_d = dist_m; near_i = i; near_sx = C[0] / C[2]; near_sy = C[1] / C[2]; }
        if (g_log && (g_frame % 50 == 1 || g_log >= 3) && i < 4) {   /* мировое положение центра (для RE_TELEPORT): камера + Vᵀ·c (оба порядка матрицы) */
            const float *V = (const float *)&P44_ViewMat; double wa[3], wb[3];
            for (int j = 0; j < 3; j++) { wa[j] = 0; wb[j] = 0; for (int i = 0; i < 3; i++) { wa[j] += C[i] * V[3 * j + i]; wb[j] += C[i] * V[3 * i + j]; } }
            plat_log("[detail] f%d машина %d %d %d камера %.0f %.0f %.0f, центр копии ≈ %.0f %.0f %.0f | %.0f %.0f %.0f\n", g_frame, (int)P99_Cars[0].pos[0], (int)P99_Cars[0].pos[1], (int)P99_Cars[0].pos[2], P44_CamX, P44_CamY, P44_CamZ,
                     P44_CamX + wa[0], P44_CamY + wa[1], P44_CamZ + wa[2], P44_CamX + wb[0], P44_CamY + wb[1], P44_CamZ + wb[2]);
        }
        if (g_log && (g_frame % 50 == 1 || g_log >= 3) && i < 4)
            plat_log("[detail] f%d копия p%03d: начало %.0f %.0f %.0f, |x| %.1f |y| %.1f ед/м, нормаль %.2f %.2f %.2f, %.1f м, треуг. %d, цвет %.0f %.0f %.0f\n", g_frame, e->page,
                     q->o[0], q->o[1], q->o[2], lx, ly, N[0] / s, N[1] / s, N[2] / s, dist_m, q->ntri, tint[0] * 255, tint[1] * 255, tint[2] * 255);
    }
    g_st_drawn += drawn;
    if (g_log && near_i >= 0 && g_frame % 10 == 0) {
        dent_t *e = &g_ent[g_inst[near_i].e];
        plat_log("[detail] f%d ближайшая: p%03d_c%04d uv %.0f,%.0f..%.0f,%.0f %.1f м, x/z %.2f y/z %.2f, машина %d %d, нарисовано %d\n", g_frame, e->page, e->pal,
                 e->u0, e->v0, e->u1, e->v1, near_d, near_sx, near_sy, (int)P99_Cars[0].pos[0], (int)P99_Cars[0].pos[2], drawn);
    }
    if (g_log && (g_frame % 50 == 1 || g_log >= 3))
        plat_log("[detail] f%d: копий %d, нарисовано %d (всего: треугольников %ld, не та палитра %ld, обрезанных %ld, дальше LOD %ld, нарисовано %ld)\n",
                 g_frame, g_ninst, drawn, g_st_tri, g_st_pal, g_st_partial, g_st_far, g_st_drawn);
}
