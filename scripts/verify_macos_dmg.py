#!/usr/bin/env python3
"""Mount a DMG read-only, install into a test folder and launch without repo assets."""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

from package_macos import verify_app
from audit_macos_privacy import audit_app


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dmg", type=Path)
    parser.add_argument("--report-dir", type=Path, required=True)
    args = parser.parse_args()
    report = args.report_dir.resolve()
    report.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="installed-test-", dir=report.parent) as temp:
        root = Path(temp)
        mount = root / "Mounted Image"
        mount.mkdir()
        subprocess.run(["hdiutil", "attach", "-readonly", "-nobrowse", "-mountpoint", mount,
                        args.dmg.resolve()], check=True)
        mounted = True
        try:
            disk_app = mount / "Driver.app"
            verify_app(disk_app)
            privacy = audit_app(disk_app)
            (report / "privacy-audit.json").write_text(json.dumps(privacy, indent=2) + "\n")
            env = {k: v for k, v in os.environ.items() if not k.startswith(("RE_", "SDL_", "DYLD_"))}
            env.update(SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy",
                       RE_USER_DATA_DIR=str(root / "User Profile"), RE_GFXLOG=str(report / "graphics.log"),
                       DYLD_PRINT_LIBRARIES="1")
            for test in ("--selftest", "--inputtest"):
                with (report / f"{test[2:]}.log").open("w") as log:
                    subprocess.run([disk_app / "Contents/MacOS/Driver", test], cwd=root, env=env,
                                   stdout=log, stderr=subprocess.STDOUT, check=True, timeout=90)
            # Initialize a profile from the read-only volume, then preserve it
            # while moving to the installed app and ejecting the source image.
            subprocess.run([disk_app / "Contents/MacOS/Driver", "--idle", "--frames", "1"],
                           cwd=root, env=env, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=30)
            profile = root / "User Profile"
            sentinel = profile / "GameData/SAVES/package-test.txt"
            sentinel.write_text("preserve my saves\n")
            app = root / "Installed Applications/Driver.app"
            app.parent.mkdir()
            subprocess.run(["ditto", disk_app, app], check=True)
            subprocess.run(["hdiutil", "detach", mount], check=True)
            mounted = False
            env.pop("SDL_VIDEODRIVER")
            env.update(RE_DIAG="1", RE_DIAG_DIR=str(root / "Diagnostics"), RE_DIAG_CAPTURE_FRAME="1000",
                       RE_GAMEPAD="0", RE_RUMBLE="0", RE_RES="800x600", RE_WINDOWED="1",
                       RE_FIXED_DT="1", RE_VSYNC="off", RE_MAX_FRAMES="1020", RE_NO_MSGBOX="1",
                       RE_KEYS="300:LEFT,340:LEFT,380:LEFT,460:RETURN,560:RETURN,660:RETURN",
                       RE_SHOT_PNG=str(report / "screenshot.png"))
            with (report / "game.log").open("w") as log:
                subprocess.run([app / "Contents/MacOS/Driver"], cwd=root, env=env,
                               stdout=log, stderr=subprocess.STDOUT, check=True, timeout=120)
            assert sentinel.read_text() == "preserve my saves\n"
            assert (profile / "GameData/FSIN.DAT").resolve() == app / "Contents/Resources/Data_Files/FSIN.DAT"
            assert (report / "screenshot.png").stat().st_size > 10000
            log = (report / "game.log").read_text()
            libraries = [line for line in log.splitlines() if line.startswith("dyld[")]
            assert libraries and not any("/opt/homebrew/" in line or "/usr/local/" in line for line in libraries)
            assert any("Installed Applications/Driver.app/Contents/Frameworks/libSDL3" in line for line in libraries)
            assert "RE_MAX_FRAMES=1020" in log
            if (app / "Contents/Resources/TexturePack").exists():
                assert (profile / "GameData/TexturePack").resolve() == app / "Contents/Resources/TexturePack"
                assert "[texpack]" in log and "[detail]" in log
            captures = list((root / "Diagnostics").glob("session-*/capture-*"))
            assert captures
            verify_app(app)  # the installed app's signature survives gameplay
            (report / "verification.json").write_text(json.dumps({
                "dmg": args.dmg.name, "architecture": "arm64", "minimum_macos": "14.0",
                "read_only_dmg_tests": True, "relocated_app_launch": True,
                "no_homebrew_libraries_loaded": True, "user_saves_preserved": True,
                "signature_valid_after_gameplay": True, "rendered_frames": 1020,
                "application_icon_valid": True,
                "hd_textures": (app / "Contents/Resources/TexturePack").exists(),
            }, indent=2) + "\n")
            print(f"DMG verified. Report and screenshot: {report}")
        finally:
            if mounted:
                subprocess.run(["hdiutil", "detach", mount], check=True)


if __name__ == "__main__":
    main()
