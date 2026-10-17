cmake_minimum_required(VERSION 3.16)
project(re_driver C)
set(CMAKE_C_STANDARD 11)
file(GLOB GAME_SRC game/*.c)

if(RE_HOOK_BUILD)
  # Win32-DLL для оригинального Game.exe (i686). См. build.sh
  add_library(DINPUT SHARED ${GAME_SRC} platform/win32/hook.c platform/win32/dinput_proxy.c platform/win32/install.c)
  target_compile_definitions(DINPUT PRIVATE RE_HOOK_BUILD)
  set_target_properties(DINPUT PROPERTIES PREFIX "")
else()
  # Нативная сборка: macOS (Apple Silicon), Linux, Windows x64.
  # GL-функции берутся через SDL_GL_GetProcAddress (platform/sdl/plat_render.c) — с libGL/OpenGL.framework не линкуемся.
  option(RE_MACOS_BUNDLE "macOS: собрать Driver.app (MACOSX_BUNDLE)" OFF)
  if(APPLE)
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
  find_package(SDL2 REQUIRED)

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

  set(NATIVE_SRC ${GAME_SRC} platform/native/main.c platform/native/engine_native.c platform/native/stubs.c platform/native/links.c platform/native/crt_msvc.c platform/native/game_fwd.c platform/native/fn_table.c platform/native/thunk_table.c platform/sdl/plat_sys.c platform/sdl/plat_gfx.c platform/sdl/plat_render.c platform/sdl/plat_dd.c platform/sdl/plat_di.c ${RENDER_OFFSCREEN} platform/sdl/plat_snd.c platform/sdl/plat_dsmix.c tests/selftest.c tests/render_test.c tests/snd_test.c tests/input_test.c)

  if(APPLE AND RE_MACOS_BUNDLE)
    add_executable(driver MACOSX_BUNDLE ${NATIVE_SRC})
    set_target_properties(driver PROPERTIES OUTPUT_NAME Driver
      MACOSX_BUNDLE_BUNDLE_NAME Driver MACOSX_BUNDLE_GUI_IDENTIFIER org.r331.driver
      MACOSX_BUNDLE_SHORT_VERSION_STRING 2.16
      MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in)   # v2.14: NSPrincipalClass, NSHighResolutionCapable
    target_compile_definitions(driver PRIVATE RE_MACOS_BUNDLE)
  else()
    add_executable(driver ${NATIVE_SRC})
  endif()

  if(TARGET SDL2::SDL2)
    target_link_libraries(driver PRIVATE SDL2::SDL2)
  else()   # старые SDL2-конфиги без imported target
    target_include_directories(driver PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(driver PRIVATE ${SDL2_LIBRARIES})
  endif()
  if(NOT WIN32)
    target_link_libraries(driver PRIVATE m)
  endif()
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
endif()
