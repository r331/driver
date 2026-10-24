#!/usr/bin/env python3
"""Regression checks for personal data that must never enter the installer."""
import contextlib
import io
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest
import zlib

from audit_macos_privacy import audit_app


class PrivacyTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="privacy-test-")
        self.addCleanup(self.temporary.cleanup)
        self.app = Path(self.temporary.name) / "Driver.app"
        self.resources = self.app / "Contents/Resources"
        self.resources.mkdir(parents=True)

    def audit(self):
        with contextlib.redirect_stdout(io.StringIO()):
            return audit_app(self.app)

    def test_generic_defaults_and_third_party_credits_are_allowed(self):
        (self.resources / "Defaults").mkdir()
        (self.resources / "Defaults/driver.cfg").write_text("preset = enhanced\n")
        (self.resources / "LICENSE.txt").write_text("SDL authors <slouken@libsdl.org>\n")
        self.assertEqual(self.audit()["local_identifiers_found"], 0)

    def test_home_path_in_executable_is_rejected(self):
        (self.resources / "binary").write_bytes(b"\0" + str(Path.home()).encode() + b"/source.c\0")
        with self.assertRaisesRegex(RuntimeError, "account_home"):
            self.audit()

    def test_utf16_path_across_read_boundary_is_rejected(self):
        (self.resources / "binary").write_bytes(b"\0" * (1024 * 1024 - 5) + str(Path.home()).encode("utf-16le"))
        with self.assertRaisesRegex(RuntimeError, "account_home"):
            self.audit()

    def test_compressed_png_metadata_is_rejected(self):
        def chunk(kind, data):
            return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))
        data = b"Source\0\0" + zlib.compress(str(Path.home()).encode())
        (self.resources / "texture.png").write_bytes(b"\x89PNG\r\n\x1a\n" + chunk(b"zTXt", data) + chunk(b"IEND", b""))
        with self.assertRaisesRegex(RuntimeError, "PNG metadata"):
            self.audit()

    def test_copied_scores_are_rejected(self):
        (self.resources / "SAVES").mkdir()
        (self.resources / "SAVES/SCORES.HI").write_bytes(b"score")
        with self.assertRaisesRegex(RuntimeError, "profile_or_private_file"):
            self.audit()

    def test_personal_extended_metadata_is_rejected(self):
        path = self.resources / "texture"
        path.write_bytes(b"asset")
        subprocess.run(["xattr", "-w", "com.driver.privacytest", str(Path.home()), path], check=True)
        with self.assertRaisesRegex(RuntimeError, "extended attribute"):
            self.audit()


if __name__ == "__main__":
    unittest.main()
