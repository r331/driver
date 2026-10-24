cmake_minimum_required(VERSION 3.16)
project(re_driver C)
set(CMAKE_C_STANDARD 11)
file(GLOB GAME_SRC game/*.c)

if(RE_HOOK_BUILD)
  # Win32-DLL для оригинального Game.exe (i686): те же исходники, библиотеки и флаги компоновки, что `build.sh hook`
  # (эталон — build.sh, его собирает CI; до этой правки ветка CMake не компоновалась — не хватало platform/win32/plat_*.c):
  #   cmake -S re -B build-hook -DRE_HOOK_BUILD=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc
  file(GLOB HOOK_SRC platform/win32/*.c)
  add_library(DINPUT SHARED ${GAME_SRC} ${HOOK_SRC})
  target_compile_definitions(DINPUT PRIVATE RE_HOOK_BUILD)
  target_link_options(DINPUT PRIVATE -static-libgcc -Wl,--kill-at -Wl,--enable-stdcall-fixup)
  target_link_libraries(DINPUT PRIVATE winmm gdi32 user32 ddraw ole32)
  set_target_properties(DINPUT PROPERTIES PREFIX "")
else()
  # Нативная сборка: macOS (Apple Silicon), Linux, Windows x64.
  # GL-функции берутся через SDL_GL_GetProcAddress (platform/sdl/plat_render.c) — с libGL/OpenGL.framework не линкуемся.
  option(RE_MACOS_BUNDLE "macOS: собрать Driver.app (MACOSX_BUNDLE)" OFF)
  if(APPLE)
    if(NOT CMAKE_OSX_DEPLOYMENT_TARGET)
      set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0" CACHE STRING "Minimum supported macOS version" FORCE)
    endif()
    set(RE_MACOS_MIN_VERSION "${CMAKE_OSX_DEPLOYMENT_TARGET}")
    # v2.13: Homebrew SDL2 (/opt/homebrew на arm64, /usr/local на x86_64)
    foreach(p /opt/homebrew /usr/local)
      if(EXISTS ${p}/lib/cmake/SDL2 OR EXISTS ${p}/opt/sdl2)
        list(APPEND CMAKE_PREFIX_PATH ${p} ${p}/opt/sdl2)
      endif()
    endforeach()
    if(NOT CMAKE_OSX_ARCHITECTURES AND CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
      set(CMAKE_OSX_ARCHITECTURES arm64)
    endif()
  endif()
  option(RE_SDL3_COMPAT "Use pinned SDL3 drivers through the SDL2 compatibility layer (Steam Controller 2026)" OFF)
  if(RE_SDL3_COMPAT)
    include(cmake/ModernSDL.cmake)
  else()
    find_package(SDL2 REQUIRED)
  endif()

  # Offscreen-тест рендера через OSMesa — только Linux (на macOS OSMesa нет; render_test там выдаёт «пропущено»)
  set(RENDER_OFFSCREEN platform/sdl/plat_render_nogl.c)
  if(NOT APPLE AND NOT WIN32)
    find_library(OSMESA_LIB OSMesa)
    find_path(OSMESA_INC GL/osmesa.h)
    if(OSMESA_LIB AND OSMESA_INC)
      set(RENDER_OFFSCREEN platform/sdl/plat_render_osmesa.c)
      message(STATUS "OSMesa найден: тест рендера offscreen включён")
    endif()
  endif()

  set(NATIVE_SRC ${GAME_SRC} platform/native/main.c platform/native/engine_native.c platform/native/stubs.c platform/native/links.c platform/native/crt_msvc.c platform/native/game_fwd.c platform/native/fn_table.c platform/native/thunk_table.c platform/native/reprobe.c platform/native/reprof.c platform/plat_log.c platform/sdl/plat_sys.c platform/sdl/plat_gfx.c platform/sdl/plat_texpack.c platform/sdl/plat_detail.c platform/sdl/plat_render.c platform/sdl/plat_dd.c platform/sdl/plat_di.c ${RENDER_OFFSCREEN} platform/sdl/plat_snd.c platform/sdl/plat_dsmix.c platform/sdl/plat_cdaudio.c tests/selftest.c tests/render_test.c tests/snd_test.c tests/cd_test.c tests/input_test.c)

  list(APPEND NATIVE_SRC platform/native/diagnostics.c)
  # v2.34: x87 rounding of Game.exe (truncate after 005283e2 / 0052840c) for lrintf & co. in the ported code — game/fpucw.h
  set_source_files_properties(${GAME_SRC} PROPERTIES COMPILE_OPTIONS "-include;${CMAKE_CURRENT_SOURCE_DIR}/game/fpucw.h")
  set(RE_BUILD_LABEL "" CACHE STRING "Override the diagnostics build revision for private packaging")
  if(RE_BUILD_LABEL)
    set(RE_BUILD_REV "${RE_BUILD_LABEL}")
  else()
    execute_process(COMMAND git rev-parse --short HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      OUTPUT_VARIABLE RE_BUILD_REV OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    if(NOT RE_BUILD_REV)
      set(RE_BUILD_REV unknown)
    endif()
    execute_process(COMMAND git diff --quiet HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE RE_BUILD_DIRTY OUTPUT_QUIET ERROR_QUIET)
    if(RE_BUILD_DIRTY EQUAL 1)
      string(APPEND RE_BUILD_REV "-dirty")
    endif()
  endif()
  set_source_files_properties(platform/native/diagnostics.c PROPERTIES COMPILE_DEFINITIONS "RE_BUILD_REV=\"${RE_BUILD_REV}\"")

  if(APPLE AND RE_MACOS_BUNDLE)
    enable_language(OBJC)
    list(APPEND NATIVE_SRC platform/native/bundle_data.m)
    add_executable(driver MACOSX_BUNDLE ${NATIVE_SRC})
    set_target_properties(driver PROPERTIES OUTPUT_NAME Driver
      MACOSX_BUNDLE_BUNDLE_NAME Driver MACOSX_BUNDLE_GUI_IDENTIFIER org.r331.driver
      MACOSX_BUNDLE_SHORT_VERSION_STRING 2.32.0
      MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in)   # v2.14: NSPrincipalClass, NSHighResolutionCapable
    target_compile_definitions(driver PRIVATE RE_MACOS_BUNDLE)
    target_link_libraries(driver PRIVATE "-framework Foundation")
  else()
    add_executable(driver ${NATIVE_SRC})
  endif()

  if(TARGET SDL2::SDL2)
    target_link_libraries(driver PRIVATE SDL2::SDL2)
  else()   # старые SDL2-конфиги без imported target
    target_include_directories(driver PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(driver PRIVATE ${SDL2_LIBRARIES})
  endif()
  if(RE_SDL3_COMPAT)
    add_dependencies(driver SDL3-shared)
    if(APPLE AND RE_MACOS_BUNDLE)
      set_target_properties(driver PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@executable_path/../Frameworks")
    elseif(UNIX AND NOT APPLE)
      # v2.32: RUNPATH относительно бинарника — driver + sdl-runtime/ можно переносить вместе;
      # абсолютный <build>/sdl-runtime вне каталога сборки молча давал системный SDL2 Classic.
      set_target_properties(driver PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "$ORIGIN/sdl-runtime")
    endif()
  endif()
  if(NOT WIN32)
    target_link_libraries(driver PRIVATE m)
  endif()
  # v2.37: RE_LOG (platform/plat_log.c) — мьютекс журнала: звук пишет из своего потока
  find_package(Threads REQUIRED)
  target_link_libraries(driver PRIVATE Threads::Threads)
  if(OSMESA_LIB AND OSMESA_INC AND RENDER_OFFSCREEN MATCHES osmesa)
    target_include_directories(driver PRIVATE ${OSMESA_INC})
    target_link_libraries(driver PRIVATE ${OSMESA_LIB})
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(driver PRIVATE -Wall -Wextra -Wno-unused-parameter -ffp-contract=off)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    # Перенесённый код MSVC-эпохи: шумные у clang предупреждения (не ошибки) приглушены
    target_compile_options(driver PRIVATE -Wno-unknown-warning-option -Wno-pointer-sign -Wno-incompatible-pointer-types-discards-qualifiers
      -Wno-sometimes-uninitialized -Wno-unused-but-set-variable -Wno-tautological-constant-out-of-range-compare)
  endif()

  enable_testing()
  # selftest не читает файлы игры: всё нужное он создаёт сам во временном каталоге сборки (работает и в CI без данных)
  add_test(NAME selftest COMMAND driver --selftest)
  set_tests_properties(selftest PROPERTIES LABELS "nodata" ENVIRONMENT "SDL_AUDIODRIVER=dummy;SDL_VIDEODRIVER=dummy")
  # v2.14: ввод — цикл событий в главном потоке, SDL_PushEvent → разбор событий игры → DIK (защёлка, стрелки, Cmd/Alt+Enter)
  add_test(NAME inputtest COMMAND driver --inputtest)
  set_tests_properties(inputtest PROPERTIES LABELS "nodata" ENVIRONMENT "SDL_AUDIODRIVER=dummy;SDL_VIDEODRIVER=dummy")
  if(APPLE AND RE_MACOS_BUNDLE)
    find_package(Python3 QUIET COMPONENTS Interpreter)
    if(Python3_Interpreter_FOUND)
      add_test(NAME bundletest COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/test_macos_bundle.py $<TARGET_BUNDLE_DIR:driver>)
      set_tests_properties(bundletest PROPERTIES LABELS "nodata" TIMEOUT 90)
    endif()
  endif()
endif()
