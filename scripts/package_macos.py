#!/usr/bin/env python3
"""Build a private, self-contained Apple Silicon DMG from owned game assets."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import plistlib
import re
import shutil
import subprocess
import tempfile

from audit_macos_privacy import audit_app

ROOT = Path(__file__).resolve().parents[1]
EXCLUDE = shutil.ignore_patterns(".git", ".DS_Store", "Diagnostics", "*.log", "config.dat", "config.dat.backup*", "driver.cfg", "SAVES", "$TEMP$*", "STARTPOS.X")


def prepare_icon(source, build):
    """Convert the owned game's Windows icon (a BMP) or a custom image to ICNS."""
    if not source.is_file():
        raise RuntimeError(f"Missing application icon: {source}. Supply an image with --icon.")
    output = build / "Driver.icns"
    if source.suffix.lower() == ".icns":
        if source.resolve() != output.resolve():
            shutil.copy2(source, output)
        return output
    with tempfile.TemporaryDirectory(prefix="app-icon-", dir=build) as temporary:
        root = Path(temporary)
        png = root / "original.png"
        run("sips", "-s", "format", "png", source, "--out", png, stdout=subprocess.DEVNULL)
        iconset = root / "Driver.iconset"
        iconset.mkdir()
        for size in (16, 32, 128, 256, 512):
            for scale in (1, 2):
                pixels = size * scale
                name = f"icon_{size}x{size}" + ("@2x" if scale == 2 else "") + ".png"
                run("sips", "-z", pixels, pixels, png, "--out", iconset / name, stdout=subprocess.DEVNULL)
        run("iconutil", "--convert", "icns", "--output", output, iconset)
    return output


def run(*args, **kwargs):
    print("+", " ".join(map(str, args)), flush=True)
    return subprocess.run(list(map(str, args)), check=True, **kwargs)


def verify_app(app):
    app = app.resolve()
    info = plistlib.loads((app / "Contents/Info.plist").read_bytes())
    icon_name = info.get("CFBundleIconFile", "")
    icon = app / "Contents/Resources" / icon_name
    if not icon_name or Path(icon_name).name != icon_name or not icon.is_file() or icon.read_bytes()[:4] != b"icns":
        raise RuntimeError("Missing or invalid macOS application icon")
    minimum = tuple(map(int, info["LSMinimumSystemVersion"].split(".")))
    binary = app / "Contents/MacOS/Driver"
    files = {binary, *(p.resolve() for p in (app / "Contents/Frameworks").glob("*.dylib"))}
    for item in files:
        arch = subprocess.check_output(["lipo", "-archs", item], text=True).strip()
        if arch != "arm64":
            raise RuntimeError(f"Expected Apple Silicon binary: {item}: {arch}")
        load = subprocess.check_output(["otool", "-l", item], text=True)
        found = re.search(r"\bminos ([0-9.]+)", load)
        if not found or tuple(map(int, found[1].split("."))) > minimum:
            raise RuntimeError(f"Deployment target does not match Info.plist: {item}")
        deps = subprocess.check_output(["otool", "-L", item], text=True)
        for line in deps.splitlines()[1:]:
            dep = line.strip().split(" ", 1)[0]
            if not dep.startswith(("@rpath/", "@loader_path/", "@executable_path/", "/System/Library/", "/usr/lib/")):
                raise RuntimeError(f"External dependency: {item}: {dep}")
    for directory, dirs, names in os.walk(app):
        for name in dirs + names:
            path = Path(directory) / name
            if path.is_symlink() and not path.resolve().is_relative_to(app):
                raise RuntimeError(f"Nonportable symlink inside app: {path}")
    for name in ("FSIN.DAT", "FRUSTRUM.DAT", "Levels"):
        if not (app / "Contents/Resources/Data_Files" / name).exists():
            raise RuntimeError(f"Missing game asset: {name}")
    run("codesign", "--verify", "--deep", "--strict", app)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--data", type=Path, required=True, help="Original Data_Files directory")
    parser.add_argument("--texpack", type=Path, help="HD texture pack; .git is excluded")
    parser.add_argument("--icon", type=Path, help="Custom app icon; defaults to the original game's driver.ico")
    parser.add_argument("--build-dir", type=Path, default=ROOT / "build-macos-package")
    parser.add_argument("--output", type=Path, default=ROOT / "dist/Driver-AppleSilicon.dmg")
    parser.add_argument("--skip-build", action="store_true", help="Package an already built modern-runtime app")
    args = parser.parse_args()
    if platform.system() != "Darwin":
        parser.error("DMG packaging requires macOS")
    data = args.data.resolve()
    if not (data / "FSIN.DAT").is_file() or not (data / "Levels").is_dir():
        parser.error("--data must point to a complete Data_Files directory")
    if args.texpack and not args.texpack.is_dir():
        parser.error("--texpack is not a directory")
    build, output = args.build_dir.resolve(), args.output.resolve()
    build.mkdir(parents=True, exist_ok=True)
    output.parent.mkdir(parents=True, exist_ok=True)
    icon = prepare_icon((args.icon or data.parent / "Program_Executable_Files/driver.ico").resolve(), build)
    if not args.skip_build:
        # Map compiler-emitted source paths in both the game and bundled SDL.
        flags = f"-ffile-prefix-map={Path.home()}=/build -ffile-prefix-map={ROOT}=. -fdebug-prefix-map={Path.home()}=/build -fdebug-prefix-map={ROOT}=."
        with (build / "package-build.log").open("w") as log:
            run("cmake", "-S", ROOT / "re", "-B", build, "-DCMAKE_BUILD_TYPE=Release",
                "-DRE_MACOS_BUNDLE=ON", "-DRE_SDL3_COMPAT=ON", "-DCMAKE_OSX_ARCHITECTURES=arm64",
                "-DCMAKE_OSX_DEPLOYMENT_TARGET=14.0", "-DSDL_HIDAPI_LIBUSB=OFF", "-DRE_BUILD_LABEL=macos-release",
                f"-DCMAKE_C_FLAGS={flags}", f"-DCMAKE_OBJC_FLAGS={flags}", f"-DCMAKE_CXX_FLAGS={flags}",
                stdout=log, stderr=subprocess.STDOUT)
            run("cmake", "--build", build, "-j", "8", stdout=log, stderr=subprocess.STDOUT)
        run("ctest", "--test-dir", build, "--output-on-failure")
    original_app = build / "Driver.app"
    if not (original_app / "Contents/Frameworks/libSDL3.0.dylib").is_file():
        raise RuntimeError("Build the app with RE_SDL3_COMPAT=ON first")
    with tempfile.TemporaryDirectory(prefix="dmg-stage-", dir=build) as temporary:
        staging = Path(temporary) / "Driver Installer"
        staging.mkdir()
        app = staging / "Driver.app"
        shutil.copytree(original_app, app, symlinks=True)
        resources = app / "Contents/Resources"
        resources.mkdir(exist_ok=True)
        shutil.copy2(icon, resources / "Driver.icns")
        plist = app / "Contents/Info.plist"
        info = plistlib.loads(plist.read_bytes())
        info["CFBundleIconFile"] = "Driver.icns"
        info["CFBundleIdentifier"] = "org.driver.game"
        plist.write_bytes(plistlib.dumps(info, sort_keys=False))
        assets = resources / "Data_Files"
        # A development app may have a link to work/run. Never ship that link.
        if assets.is_symlink():
            assets.unlink()
        elif assets.exists():
            shutil.rmtree(assets)
        print("Copying original game assets…", flush=True)
        shutil.copytree(data, assets, symlinks=False, ignore=EXCLUDE)
        (assets / ".driver-package").write_text("1\n")
        if args.texpack:
            print("Copying HD textures (excluding Git history)…", flush=True)
            shutil.copytree(args.texpack.resolve(), resources / "TexturePack", symlinks=False, ignore=EXCLUDE)
            # Repository instructions contain the owner's GitHub handle. Keep
            # runtime textures, manifests and third-party credits/licenses.
            (resources / "TexturePack/README.md").unlink(missing_ok=True)
        defaults = resources / "Defaults"
        defaults.mkdir(exist_ok=True)
        (defaults / "driver.cfg").write_text(
            "# Driver for Apple Silicon. Cmd+Enter toggles fullscreen.\n"
            "preset = enhanced\ndraw_distance = 2\naspect = auto\n"
            "fullscreen = off\nwindowed_res = 1280x800\n"
            + ("texpack = TexturePack\n" if args.texpack else ""))
        licenses = resources / "Licenses"
        licenses.mkdir(exist_ok=True)
        cache = (build / "CMakeCache.txt").read_text()
        for dep, label in (("driver_sdl3", "SDL3"), ("driver_sdl2compat", "SDL2-compat")):
            source = re.search(rf"^FETCHCONTENT_SOURCE_DIR_{dep.upper()}:PATH=(.+)$", cache, re.MULTILINE)
            directory = Path(source[1]) if source else build / f"_deps/{dep}-src"
            shutil.copy2(directory / "LICENSE.txt", licenses / f"{label}.txt")
        (resources / "BUILD-INFO.json").write_text(json.dumps({
            "build": "macos-release", "architecture": "arm64",
            "minimum_macos": "14.0", "hd_textures": bool(args.texpack),
            "sdl3": "3.4.18", "sdl2_compat": "2.32.74", "signing": "ad-hoc",
        }, indent=2) + "\n")
        (staging / "Applications").symlink_to("/Applications", target_is_directory=True)
        (staging / "Install Driver.txt").write_text(
            "Driver for Apple Silicon — macOS 14 or later\n\n"
            "1. Drag Driver.app onto Applications.\n"
            "2. Eject this disk image, then open Driver from Applications.\n\n"
            "Original game data, SDL runtimes and HD textures are included. No Homebrew or other installs are needed.\n"
            "Saves/settings live in ~/Library/Application Support/Driver/. Existing saves are preserved.\n"
            "Cmd+Enter: fullscreen/window. Gamepads and damage vibration are supported.\n\n"
            "This personal build is ad-hoc signed, not Apple-notarized. If macOS blocks it,\n"
            "use System Settings > Privacy & Security > Open Anyway after trying to open it.\n")
        # Remove copied download/Finder metadata before creating signatures.
        run("xattr", "-cr", app)
        audit_app(app)
        for library in sorted({p.resolve() for p in (app / "Contents/Frameworks").glob("*.dylib")}):
            run("codesign", "--force", "--sign", "-", library)
        run("codesign", "--force", "--sign", "-", app)
        verify_app(app)
        temporary_image = Path(temporary) / "Driver.dmg"
        run("hdiutil", "create", "-volname", "Driver", "-srcfolder", staging,
            "-fs", "HFS+", "-format", "UDZO", temporary_image)
        run("hdiutil", "verify", temporary_image)
        os.replace(temporary_image, output)
    checksum = hashlib.sha256()
    with output.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            checksum.update(block)
    digest = checksum.hexdigest()
    output.with_suffix(".dmg.sha256").write_text(f"{digest}  {output.name}\n")
    print(f"Ready: {output} ({output.stat().st_size / 1024**3:.2f} GiB)", flush=True)


if __name__ == "__main__":
    main()
