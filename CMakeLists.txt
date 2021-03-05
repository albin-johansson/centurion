cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 5.3.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CEN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CEN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})

message("Centurion version: ${CENTURION_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

set(CENTURION_LIB_TARGET CenturionLibrary)
set(CENTURION_TEST_TARGET CenturionTests)
set(CENTURION_MOCK_TARGET CenturionMocks)

if (UNIX)
  set(CENTURION_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/${CMAKE_SHARED_LIBRARY_PREFIX}Centurion${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(CENTURION_IMPORT_LIB ${CENTURION_DYNAMIC_LIB})
else ()
  set(CENTURION_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/${CMAKE_SHARED_LIBRARY_PREFIX}Centurion${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(CENTURION_IMPORT_LIB ${CMAKE_BINARY_DIR}/src/${CMAKE_IMPORT_LIBRARY_PREFIX}Centurion${CMAKE_IMPORT_LIBRARY_SUFFIX})
endif ()

message("Centurion dynamic library: ${CENTURION_DYNAMIC_LIB}")
message("Centurion import library: ${CENTURION_IMPORT_LIB}")

unset(SDL2_BUILDING_LIBRARY) # Force linking to SDL2main

option(CEN_AUDIO "Include audio components" ON)
option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" ON)
option(CENTURION_MOCK_FRIENDLY_MODE "Enable more mocked tests" ON)

if (WIN32)
  find_env_var(SDL2DIR SDL2)
  find_env_var(SDL2IMAGEDIR SDL2_image)
  find_env_var(SDL2MIXERDIR SDL2_mixer)
  find_env_var(SDL2TTFDIR SDL2_ttf)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (CEN_COVERAGE MATCHES ON)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

set(CENTURION_HEADERS
    src/area.hpp

    src/base_path.hpp
    src/battery.hpp
    src/blend_mode.hpp
    src/button_state.hpp

    src/cast.hpp
    src/centurion.hpp
    src/centurion_cfg.hpp
    src/clipboard.hpp
    src/color.hpp
    src/colors.hpp
    src/condition.hpp
    src/controller.hpp
    src/counter.hpp
    src/cpu.hpp
    src/cursor.hpp
    src/czstring.hpp

    src/event_type.hpp
    src/event.hpp
    src/exception.hpp

    src/font.hpp
    src/font_cache.hpp

    src/graphics_drivers.hpp

    src/hints.hpp

    src/integers.hpp

    src/joystick.hpp

    src/key_code.hpp
    src/key_modifier.hpp
    src/key_state.hpp

    src/log.hpp

    src/message_box.hpp
    src/mouse_button.hpp
    src/mouse_state.hpp
    src/mutex.hpp

    src/not_null.hpp

    src/owner.hpp

    src/pixel_format.hpp
    src/platform.hpp
    src/point.hpp
    src/pref_path.hpp

    src/ram.hpp
    src/rect.hpp
    src/renderer.hpp

    src/scale_mode.hpp
    src/scan_code.hpp
    src/scoped_lock.hpp
    src/screen.hpp
    src/sdl_string.hpp
    src/semaphore.hpp
    src/surface.hpp

    src/texture.hpp
    src/texture_access.hpp
    src/thread.hpp
    src/time.hpp
    src/touch.hpp
    src/try_lock.hpp

    src/unicode_string.hpp

    src/window.hpp
    src/window_utils.hpp

    src/detail/address_of.hpp
    src/detail/any_eq.hpp
    src/detail/clamp.hpp
    src/detail/convert_bool.hpp
    src/detail/czstring_eq.hpp
    src/detail/max.hpp
    src/detail/owner_handle_api.hpp
    src/detail/stack_resource.hpp
    src/detail/static_bimap.hpp
    src/detail/to_string.hpp)

if (CEN_AUDIO MATCHES ON)
  set(CENTURION_HEADERS
      ${CENTURION_HEADERS}
      src/sound_effect.hpp
      src/music.hpp)
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)

if (CEN_TESTS)
  enable_testing()
  add_subdirectory(test)
endif ()