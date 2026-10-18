#!/bin/sh
# Start a windowed diagnostic session with the locally built game.
set -eu
repo_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
binary="$repo_dir/build-native/Driver.app/Contents/MacOS/Driver"
if [ ! -x "$binary" ]; then
    echo "Build Driver.app in build-native first." >&2
    exit 1
fi
export RE_DIAG=1
export RE_GFXDBG="${RE_GFXDBG:-1}"
export RE_PRESET="${RE_PRESET:-original}"
export RE_NO_FBO="${RE_NO_FBO:-1}"
export RE_WINDOWED=1
export RE_RES="${RE_RES:-1024x768}"
export RE_DRAW_DIST="${RE_DRAW_DIST:-2}"
if [ "${RE_TEXPACK+x}" != x ] && [ -d "$repo_dir/../driver-texpack" ]; then
    export RE_TEXPACK="$repo_dir/../driver-texpack"
fi
exec "$binary" "$@"
