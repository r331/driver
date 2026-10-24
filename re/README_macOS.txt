Driver — native macOS app for Apple Silicon (M1/M2/M3/M4), macOS 14 or later

Personal DMG: dist/Driver-AppleSilicon.dmg
Open the disk image, drag Driver.app onto Applications, eject the image, then open Driver.
The personal installer includes original game data, HD textures, SDL runtimes, controller support,
and damage vibration. No Homebrew, Python or Rosetta installation is needed on the receiving Mac.

This personal build is ad-hoc signed, not Apple-notarized. If macOS blocks it after opening,
use System Settings > Privacy & Security > Open Anyway (https://support.apple.com/102445).

Saves and settings: ~/Library/Application Support/Driver/
  driver.cfg: graphics settings
  GameData/: config.dat, SAVES, Scripts, ReplayData, and links to the installed assets
Existing saves/settings are kept when replacing or moving Driver.app.

Controls:
  Menus: arrows / Enter / Esc; gamepad stick or D-pad, A confirms, B goes back.
  Driving: arrows, Space handbrake; original keyboard bindings also work.
  Gamepad: stick steering, RT throttle, LT brake/reverse, A/B handbrake,
  X burnout, Y camera, stick click horn, Menu pause. Crashes trigger vibration.
  Cmd+Enter: window/fullscreen. Cmd+Shift+Enter: toggle FBO. Cmd+Q: quit.
  RE_RUMBLE=0 disables vibration. RE_GAMEPAD=0 disables native controller input.

Build a personal installer (from the repository root):
  python3 scripts/package_macos.py --data /path/to/Data_Files --texpack /path/to/driver-texpack
  Optional: --profile /path/to/current/run/directory to seed settings and progress.
  Full instructions and checks: docs/MACOS_DMG.md

A bare app built without packaged data still supports --data /path/to/Data_Files,
or Data_Files inside Contents/Resources. That developer mode writes into the selected data folder.

HD stopwatch and mission timer digits (v2.36):
  The texture pack includes the hud_hd variant for the garage stopwatch and Miami mission timer digits.
  It is enabled by hud.txt containing hud_hd in the texture-pack directory.
  To restore the previous upscale, use RE_TEXPACK_HUD=0 or remove hud.txt.

Debug log (v2.37):
  Off by default. To record one for a bug report, start Driver from Terminal:
    RE_LOG=all:debug /Applications/Driver.app/Contents/MacOS/Driver
  or add the line  log = all:info  to ~/Library/Application Support/Driver/driver.cfg.
  The log is written to ~/Library/Logs/Driver/driver.log (open it with Console.app or Finder > Go > Go to Folder...).
  Graphics details stay in ~/Library/Logs/driver_gfx.log, input details (RE_INPUTDBG=1) in ~/Library/Logs/driver_input.log.
  Channels and levels: docs/DIAGNOSTICS.md, section RE_LOG.
