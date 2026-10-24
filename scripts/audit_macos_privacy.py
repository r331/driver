#!/usr/bin/env python3
"""Reject local account identifiers and profile artifacts in a packaged app."""
import collections
import ctypes
import json
import os
from pathlib import Path
import re
import socket
import struct
import subprocess
import zlib


def git_value(*args):
    result = subprocess.run(["git", *args], cwd=Path(__file__).resolve().parents[1],
                            text=True, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    return result.stdout.strip() if result.returncode == 0 else ""


def personal_patterns():
    values = {
        "account_name": git_value("config", "user.name"),
        "account_email": git_value("config", "user.email"),
        "account_home": str(Path.home()),
        "machine_hostname": socket.gethostname(),
        "absolute_home_path": "/Users/",
        "temporary_build_path": "/private/var/folders/",
    }
    owner = re.search(r"github\.com[:/]([^/]+)/", git_value("remote", "get-url", "origin"))
    if owner:
        values["repository_owner_link"] = owner[1] + "/"
        values["repository_owner_identifier"] = "org." + owner[1] + "."
    return {label: [value.encode(enc).lower() for enc in ("utf-8", "utf-16le", "utf-16be")]
            for label, value in values.items() if len(value) >= 4}


def extended_attributes():
    """macOS Python does not expose os.listxattr on every distribution."""
    lib = ctypes.CDLL(None)
    lib.listxattr.argtypes = [ctypes.c_char_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int]
    lib.listxattr.restype = ctypes.c_ssize_t
    lib.getxattr.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_void_p,
                            ctypes.c_size_t, ctypes.c_uint32, ctypes.c_int]
    lib.getxattr.restype = ctypes.c_ssize_t

    def read(path):
        raw = os.fsencode(path)
        length = lib.listxattr(raw, None, 0, 1)  # XATTR_NOFOLLOW
        if length <= 0:
            return []
        names = ctypes.create_string_buffer(length)
        if lib.listxattr(raw, names, length, 1) < 0:
            raise RuntimeError("Cannot read packaged extended attributes")
        found = []
        for name in names.raw.rstrip(b"\0").split(b"\0"):
            size = lib.getxattr(raw, name, None, 0, 0, 1)
            if size < 0:
                raise RuntimeError("Cannot read a packaged extended attribute")
            data = ctypes.create_string_buffer(size)
            if lib.getxattr(raw, name, data, size, 0, 1) < 0:
                raise RuntimeError("Cannot read a packaged extended attribute")
            found.append((name.decode(errors="replace"), data.raw))
        return found
    return read


def png_metadata(path):
    with path.open("rb") as stream:
        if stream.read(8) != b"\x89PNG\r\n\x1a\n":
            return
        while True:
            header = stream.read(8)
            if not header:
                return
            if len(header) != 8:
                raise RuntimeError("Truncated packaged PNG")
            length, kind = struct.unpack(">I4s", header)
            if kind not in (b"tEXt", b"zTXt", b"iTXt", b"eXIf"):
                stream.seek(length + 4, 1)
                continue
            payload = stream.read(length)
            stream.read(4)
            if kind == b"zTXt":
                key, rest = payload.split(b"\0", 1)
                payload = key + b"\0" + zlib.decompress(rest[1:])
            elif kind == b"iTXt":
                key, rest = payload.split(b"\0", 1)
                language, translated, text = rest[2:].split(b"\0", 2)
                payload = key + b"\0" + language + b"\0" + translated + b"\0" + (
                    zlib.decompress(text) if rest[0] else text)
            yield payload


def audit_app(app):
    app = Path(app).resolve()
    patterns = personal_patterns()
    patterns["private_key"] = [b"-----begin " + kind + b"private key-----"
                               for kind in (b"", b"rsa ", b"ec ", b"dsa ", b"openssh ")]
    problems = set()
    attribute_counts = collections.Counter()
    read_attributes = extended_attributes()
    files = total = metadata = 0

    def inspect(data, relative):
        lower = data.lower()
        for label, variants in patterns.items():
            if any(value in lower for value in variants):
                problems.add((relative, label))

    for directory, dirs, names in os.walk(app):
        for name in dirs + names:
            path = Path(directory) / name
            relative = str(path.relative_to(app))
            inspect(relative.encode(), relative + " [name]")
            if path.is_symlink():
                inspect(os.fsencode(os.readlink(path)), relative + " [symlink]")
                continue
            if name in (".git", ".ssh", ".aws", ".env", ".DS_Store", "Diagnostics", "SAVES", "config.dat", "driver.cfg"):
                # The generated graphics defaults are intended to ship.
                if relative != "Contents/Resources/Defaults/driver.cfg":
                    problems.add((relative, "profile_or_private_file"))
            if name.upper().startswith("$TEMP$") or name.lower().endswith((".log", ".pem", ".p12", ".mobileprovision")):
                problems.add((relative, "profile_or_private_file"))
            for attr, data in read_attributes(path):
                attribute_counts[attr] += 1
                inspect(data, relative + " [extended attribute]")
            if not path.is_file():
                continue
            files += 1
            total += path.stat().st_size
            with path.open("rb") as stream:
                carry = b""
                while True:
                    block = stream.read(1024 * 1024)
                    if not block:
                        break
                    inspect(carry + block, relative)
                    carry = block[-1024:]
            if path.suffix.lower() == ".png":
                for payload in png_metadata(path):
                    metadata += 1
                    inspect(payload, relative + " [PNG metadata]")
    if problems:
        detail = ", ".join(f"{label}: {path}" for path, label in sorted(problems))
        raise RuntimeError("Package privacy check failed: " + detail)
    result = {"files_scanned": files, "bytes_scanned": total,
              "utf8_and_utf16": True, "png_metadata_chunks_checked": metadata,
              "extended_attributes": dict(attribute_counts),
              "local_identifiers_found": 0, "profile_artifacts_found": 0}
    print("Package privacy check passed: " + json.dumps(result), flush=True)
    return result
