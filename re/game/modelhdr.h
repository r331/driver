/* modelhdr.h — header of a level model record (map models, ported79; car models, ported28; map-object
 * drawing, ported87).  Byte offsets only (rd16(mdl + MDL_NVERTS)); no structures, no code.
 * Each name says what it is based on; anything not confirmed by code carries TODO(RE). */
#pragma once

/* ---- Map model header (ported79.c): 0x38 bytes, followed by its arrays ----
   "Links" are offsets from the map arena in native, absolute addresses in the hook build (P79_OFF/P79_PTR);
   while MDL_LINKED is set in MDL_FLAGS they are absolute, otherwise relative to the model itself. */
#define MDL_HDR_SIZE    0x38
#define MDL_FLAGS       0x02   /* u16: MDL_LINKED, axis-classification marks 0x10 / 0x30 (P79_MarkRecords) */
#define MDL_LINKED      0x8000
#define MDL_PARENT      0x04   /* int32: -1 = own geometry, else index in P79_ModelTab of the model whose
                                  vertex/normal arrays and table +0x34 this one shares */
#define MDL_FLAGS2      0x08   /* u32: second flag word (ported87: bits 0x80 / 0x2000 pick the P87 draw lists;
                                  ported117: 0x4000 = surface that gives effect 3) */
#define MDL_RADIUS      0x0c   /* float: largest vertex distance from the origin */
#define MDL_RADIUS_XZ   0x10   /* float: same, ignoring Y */
#define MDL_NVERTS      0x14   /* u16: vertices (float4 each) at MDL_VERTS */
#define MDL_NRECS       0x16   /* u16: polygon (draw) records at MDL_RECS; one float4 per record at MDL_RECVEC.
                                  P87 takes its 0x2000 fast path only for single-record models */
#define MDL_N28         0x18   /* u16: float4 entries at MDL_L28 — TODO(RE): unsure what they are */
#define MDL_NBYTES1C    0x1a   /* u16: bytes at MDL_L1C — TODO(RE): unsure */
#define MDL_L1C         0x1c   /* link: byte array */
#define MDL_VERTS       0x20   /* link: vertices, float x, y, z, w (w = 1.0 in memory) */
#define MDL_RECVEC      0x24   /* link: one float4 per record — likely the polygon normal (axis-aligned ones
                                  are classified by P79_VertClass); TODO(RE): confirm */
#define MDL_L28         0x28   /* link: float4 array (MDL_N28 entries) */
#define MDL_RECS        0x2c   /* link: variable-size polygon records; byte 0 = type (size from 00550acc) */
#define MDL_SUB         0x30   /* link: sub-block with links at +0xc, +0x10, +0x14, +0x18 (relative to itself) */
#define MDL_L34         0x34   /* link: table {int32 n; n * 0x14 bytes} or 0 */
