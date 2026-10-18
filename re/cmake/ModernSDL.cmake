# SDL2 Classic lacks the Steam Controller (2026) HIDAPI driver. Use upstream's
# SDL2-compatible API on SDL3, including the macOS 27 duplicate-device fix.
include(FetchContent)
if(APPLE)
  enable_language(OBJC)
endif()
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2COMPAT_TESTS OFF CACHE BOOL "" FORCE)
set(SDL2COMPAT_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(driver_sdl3
  URL https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/SDL3-3.4.18.tar.gz
  URL_HASH SHA256=9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3)
FetchContent_Declare(driver_sdl2compat
  URL https://github.com/libsdl-org/sdl2-compat/archive/refs/tags/release-2.32.74.tar.gz
  URL_HASH SHA256=155b80cd7ef64e5b10af08eed60b6eab146ea785367ff67e0d8cc8acd511a889)
FetchContent_MakeAvailable(driver_sdl3 driver_sdl2compat)

# SDL2-compat loads SDL3 dynamically; keep the two libraries together. On macOS
# its loader checks @loader_path, so the app also works without Homebrew SDL.
if(APPLE AND RE_MACOS_BUNDLE)
  set(driver_sdl_runtime "${CMAKE_BINARY_DIR}/Driver.app/Contents/Frameworks")
elseif(WIN32)
  set(driver_sdl_runtime "${CMAKE_BINARY_DIR}")
else()
  set(driver_sdl_runtime "${CMAKE_BINARY_DIR}/sdl-runtime")
endif()
set_target_properties(SDL2 SDL3-shared PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${driver_sdl_runtime}"
  RUNTIME_OUTPUT_DIRECTORY "${driver_sdl_runtime}")
if(UNIX AND NOT APPLE)
  set_property(TARGET SDL2 APPEND PROPERTY BUILD_RPATH "$ORIGIN")
endif()
