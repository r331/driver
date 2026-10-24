#!/usr/bin/env python3
"""Exercise packaged-app startup, writable files and relocation with tiny fixtures."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("app", type=Path)
    args = parser.parse_args()
    original = args.app.resolve()
    with tempfile.TemporaryDirectory(prefix="bundle-test-", dir=original.parent) as temp:
        root = Path(temp)
        app = root / "First Location/Driver.app"
        shutil.copytree(original, app, symlinks=True)
        resources = app / "Contents/Resources"
        seed = resources / "Data_Files"
        if seed.is_symlink():
            seed.unlink()
        seed.mkdir(parents=True)
        (seed / ".driver-package").write_text("1\n")
        (seed / "FSIN.DAT").write_bytes(b"immutable fixture")
        for folder in ("Scripts", "ReplayData", "SAVES"):
            (seed / folder).mkdir()
            (seed / folder / "seed.txt").write_text("original\n")
        (seed / "config.dat").write_bytes(b"original config")
        (resources / "Defaults").mkdir()
        (resources / "Defaults/driver.cfg").write_text("preset = original\n")
        (resources / "TexturePack").mkdir()
        (resources / "TexturePack/texture.txt").write_text("HD fixture")
        profile = root / "User Data"
        env = {k: v for k, v in os.environ.items() if not k.startswith("RE_")}
        env.update(RE_USER_DATA_DIR=str(profile), SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy")

        def launch(current_app, *extra):
            subprocess.run([current_app / "Contents/MacOS/Driver", "--idle", "--frames", "1", *extra],
                           env=env, cwd=root, check=True, timeout=30, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        launch(app)
        data = profile / "GameData"
        assert (data / "FSIN.DAT").is_symlink()
        assert (data / "TexturePack/texture.txt").read_text() == "HD fixture"
        for folder in ("Scripts", "ReplayData", "SAVES"):
            assert not (data / folder).is_symlink()
            (data / folder / "seed.txt").write_text("user edit\n")
        (data / "config.dat").write_bytes(b"user config")
        (profile / "driver.cfg").write_text("preset = safe\n")
        launch(app)
        moved = root / "Installed Applications/Driver.app"
        moved.parent.mkdir()
        app.rename(moved)
        launch(moved)
        assert (data / "FSIN.DAT").resolve() == moved / "Contents/Resources/Data_Files/FSIN.DAT"
        assert (data / "FSIN.DAT").read_bytes() == b"immutable fixture"
        assert (data / "TexturePack").resolve() == moved / "Contents/Resources/TexturePack"
        for folder in ("Scripts", "ReplayData", "SAVES"):
            assert (data / folder / "seed.txt").read_text() == "user edit\n"
        assert (data / "config.dat").read_bytes() == b"user config"
        assert (profile / "driver.cfg").read_text() == "preset = safe\n"
        # Explicit developer data remains independent of packaged-app bootstrap.
        bypass = root / "Unused Profile"
        env["RE_USER_DATA_DIR"] = str(bypass)
        launch(moved, "--data", moved / "Contents/Resources/Data_Files")
        assert not bypass.exists()
        print("Bundle startup: first launch, preservation, relocation and --data override OK")


if __name__ == "__main__":
    main()
