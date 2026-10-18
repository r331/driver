#!/usr/bin/env python3
"""Validate a real RE_DIAG capture after an interactive/scripted GPU run."""
import argparse
import csv
import math
from pathlib import Path
import re
import struct


def read_csv(path):
    with path.open(newline="") as stream:
        reader = csv.DictReader(stream)
        rows = list(reader)
        assert reader.fieldnames and rows, f"Empty CSV: {path}"
        assert all(None not in row and None not in row.values() for row in rows), path
        return rows


def check(session):
    assert (session / "session.log").stat().st_size > 0
    assert (session / "graphics.log").stat().st_size > 0
    read_csv(session / "timeline.csv")
    captures = sorted(session.glob("capture-*"))
    assert captures, "No completed captures"
    for capture in captures:
        frame = int(re.search(r"frame-(\d+)$", capture.name)[1])
        history = read_csv(capture / "frames.csv")
        assert 1 <= len(history) <= 600
        assert int(history[-1]["frame"]) == frame
        assert all(int(b["frame"]) == int(a["frame"]) + 1
                   for a, b in zip(history, history[1:]))
        data = (capture / "screenshot.png").read_bytes()
        assert data[:8] == b"\x89PNG\r\n\x1a\n"
        assert struct.unpack_from(">II", data, 16) == (
            int(history[-1]["drawable_w"]), int(history[-1]["drawable_h"]))
        state = (capture / "state.txt").read_text()
        assert f"frame={frame}\n" in state
        cfg = (capture / "config.dat").read_bytes()
        assert len(cfg) == 276
        assert struct.unpack_from("<I", cfg, 4)[0] == sum(cfg[8:])
        vertices = read_csv(capture / "draws.csv")
        assert len(vertices) <= 150000
        for row in vertices:
            assert all(math.isfinite(float(row[k])) for k in ("x", "y", "depth", "rhw", "u", "v"))
        records = read_csv(capture / "records.csv")
        assert len(records) <= 150000
        assert all(row["skipped"] in ("0", "1", "2") for row in records)
        with (capture / "clipping.csv").open(newline="") as stream:
            rejected = list(csv.DictReader(stream))
        assert len(rejected) <= 150000
        assert all(row["reason"] in ("2", "3", "4") for row in rejected)
        print(f"OK {capture.name}: frame {frame}, {len(history)} history rows, "
              f"{len(vertices)} vertices, {len(records)} records, {len(rejected)} rejected triangles")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("session", type=Path)
    check(parser.parse_args().session)
