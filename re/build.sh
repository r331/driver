#!/bin/sh
# ./build.sh native  — нативная сборка (macOS M1: brew install cmake sdl2) -> build-native/driver
# ./build.sh hook    — DINPUT.dll для оригинального Game.exe (нужен i686-w64-mingw32-gcc) -> build/DINPUT.dll
set -e; cd "$(dirname "$0")"
case "${1:-native}" in
native) cmake -S . -B build-native -DCMAKE_BUILD_TYPE=Release && cmake --build build-native -j && (cd build-native && ctest --output-on-failure) ;;
hook)   mkdir -p build && i686-w64-mingw32-gcc -std=c11 -O1 -Wall -DRE_HOOK_BUILD -shared -static-libgcc \
          -o build/DINPUT.dll game/*.c platform/win32/*.c -Wl,--kill-at -Wl,--enable-stdcall-fixup -lwinmm && echo "OK: build/DINPUT.dll" ;;
esac
