# Personal macOS installer

The local installer is `dist/Driver-AppleSilicon.dmg` (approximately 2 GB with
HD textures). It contains an arm64 app for macOS 14 or later, the original game
data, the texture pack without Git history, and pinned SDL runtimes. Homebrew,
Python, Rosetta, and the source checkout are not needed on the receiving Mac.

On the other Mac, open the DMG, drag Driver onto Applications, eject the disk,
and open Driver from Applications. It starts in a window; Cmd+Enter toggles
fullscreen. Steam Controller support and damage vibration are included.

The personal build is ad-hoc signed. No Developer ID signing identity is
available here, so it is not Apple-notarized. If macOS blocks its first launch,
use **System Settings → Privacy & Security → Open Anyway** after trying to open
it. See [Apple's instructions](https://support.apple.com/102445).

## Build another DMG

Run on macOS with Python 3.9+, CMake and Xcode Command Line Tools installed:

```sh
python3 scripts/package_macos.py \
  --data work/game/Data_Files \
  --texpack ../driver-texpack
```

`--data` supplies the original game assets. `--texpack` optionally embeds
HD textures. Local settings, scores, temporary replays and profile overlays
are excluded. Use an untouched extraction of the original game for `--data`. Original assets and generated installers stay outside Git.
The app icon is converted from the original game's
`Program_Executable_Files/driver.ico`; `--icon path/to/image.png` (or `.icns`)
can supply a different icon. The icon is embedded before the app is signed,
and packaging verifies its bundle metadata and resource.

The script builds in `build-macos-package` with a macOS 14 deployment target,
the modern SDL runtime, and no optional Homebrew libusb dependency. Its first
configure downloads checksum-pinned SDL sources. It runs the tests, stages real
asset files rather than development symlinks, signs the app and libraries,
checks dependencies/architecture/deployment targets and scans for personal
identifiers, then creates and verifies
a compressed DMG. A SHA-256 sidecar is written alongside the image. Use
`--output`, `--build-dir`, or `--skip-build` when needed.

## Writable data and upgrades

The installed app's Resources are immutable. On first launch, it creates:

```
~/Library/Application Support/Driver/
  driver.cfg
  GameData/
    config.dat
    SAVES/
    Scripts/
    ReplayData/
```

Other GameData entries link to the installed app's assets. They are refreshed
if the app moves; existing saves, settings, scripts and replays are preserved.
The large texture pack remains inside the app and is not copied into each
profile. Replacing Driver.app therefore preserves the user's progress.
`RE_USER_DATA_DIR` overrides the profile root for isolated testing; explicit
`--data` retains the original developer workflow and skips packaged startup.

## Verification

```sh
python3 scripts/verify_macos_dmg.py dist/Driver-AppleSilicon.dmg \
  --report-dir build-macos-package/verification
```

This mounts the image read-only, validates signing and dependencies, runs
selftest/inputtest, and prepares a writable profile. It then copies the app to
a separate installation directory, ejects the DMG, and runs 1,020 game frames
without repository data or Homebrew libraries. It checks preserved saves and
the app signature after gameplay. The report includes logs and a screenshot.

`bundletest` additionally verifies initial profile creation, preserving changed
files, app relocation, and the explicit-data override using small fixtures.
The current local DMG passed all these checks; HD textures/detail meshes and
the main game view were visibly present in its captured frame. The M3 Pro
machine itself has not been tested here.

## Package privacy

The installer uses a generic bundle identifier and build label, excludes the
texture repository README, and preserves third-party licenses/credits. Compiler
source paths are remapped and SDL loader paths stay relative to the app.
Copied extended attributes are cleared before signing. The privacy audit checks
all packaged file bytes in UTF-8 and UTF-16, PNG metadata, names and extended
attributes for the build account's name, email, home path and hostname, as well
as local profile artifacts and repository identifiers. It runs before packaging
and again against the read-only DMG during verification. Reports stay local.
