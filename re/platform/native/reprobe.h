/* reprobe.h — RE_PROBE: opt-in runtime instrumentation for open reverse-engineering questions
 * (docs/RE_QUESTIONS.md).  Native build only; every call site sits under #ifndef RE_HOOK_BUILD, and every
 * entry point returns at once (one cached flag test) unless RE_PROBE is set, so a run without RE_PROBE
 * behaves and logs exactly as before.  The probe only reads game state (and, for "walk", queues key
 * presses through the RE_KEYS script queue); it never writes game memory and never draws random numbers.
 *
 *   RE_PROBE=1 | all              every topic
 *   RE_PROBE=car,traffic,...      chosen topics: car traffic ped mission menu walk
 *   RE_PROBE_LOG=path             log file (default probe.log in the working directory)
 *   RE_PROBE_EVERY=N              period of the periodic dumps in physics steps (default 50)
 *   RE_PROBE_SHOTS=dir            menu topic: one PNG per newly seen menu table (dir/menu_<table>.png)
 *   RE_PROBE_WALK=file            walk topic: state file of the front-end menu walker (default probe_walk.txt)
 *
 * Topics:
 *   car      player car: every change of +0x138 with the damage zones and the map cell, periodic dump of
 *            +0x58/+0x68 (pending impulses), +0x108, +0x13c..+0x141 with the control bits;
 *            all cars: +0x108 / +0x13e transitions.
 *   traffic  periodic dump of every live traffic record (TrafficRecs 011443e0) next to the values
 *            P59_CellLeft computes for it and the model of the car it drives.
 *   ped      periodic census of the 64-slot pool A_00C56780 (in-use count, record type histogram).
 *   mission  every change of the mission state 00c810c4, result 00c810e8 and countdown 00c81100.
 *   menu     every newly seen front-end menu table: table address, entries, the static text list
 *            (P45_PtrA) of the screen, optional screenshot.
 *   walk     drives the front end on its own (depth-first over menu entries, one RETURN per untried
 *            entry, ESC when a table is done); state persists in RE_PROBE_WALK so repeated runs continue
 *            where an entry left the front end.  Implies "menu". */
#pragma once
#include <stdint.h>

void        re_probe_step(void);                       /* once per P142_CarsStep */
void        re_probe_menu(uint32_t tbl, int32_t cur);  /* once per P114_MenuStep */
const char *re_probe_frame(int frame);                 /* once per shown frame; returns a PNG path to write, or NULL */
