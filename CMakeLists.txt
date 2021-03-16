cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 6.0.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/centurion)
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
    src/centurion/area.hpp

    src/centurion/base_path.hpp
    src/centurion/battery.hpp
    src/centurion/blend_mode.hpp
    src/centurion/button_state.hpp

    src/centurion/cast.hpp
    src/centurion/library.hpp
    src/centurion/centurion_cfg.hpp
    src/centurion/clipboard.hpp
    src/centurion/color.hpp
    src/centurion/colors.hpp
    src/centurion/condition.hpp
    src/centurion/controller.hpp
    src/centurion/counter.hpp
    src/centurion/cpu.hpp
    src/centurion/cursor.hpp
    src/centurion/czstring.hpp

    src/centurion/events/event_type.hpp
    src/centurion/events/event.hpp
    src/centurion/exception.hpp

    src/centurion/font.hpp
    src/centurion/font_cache.hpp

    src/centurion/graphics_drivers.hpp

    src/centurion/hints.hpp

    src/centurion/integers.hpp

    src/centurion/joystick.hpp

    src/centurion/key_code.hpp
    src/centurion/key_modifier.hpp
    src/centurion/key_state.hpp

    src/centurion/log.hpp

    src/centurion/message_box.hpp
    src/centurion/mouse_button.hpp
    src/centurion/mouse_state.hpp
    src/centurion/mutex.hpp

    src/centurion/not_null.hpp

    src/centurion/owner.hpp

    src/centurion/pixel_format.hpp
    src/centurion/platform.hpp
    src/centurion/point.hpp
    src/centurion/pref_path.hpp

    src/centurion/ram.hpp
    src/centurion/rect.hpp
    src/centurion/renderer.hpp

    src/centurion/scale_mode.hpp
    src/centurion/scan_code.hpp
    src/centurion/scoped_lock.hpp
    src/centurion/screen.hpp
    src/centurion/sdl_string.hpp
    src/centurion/semaphore.hpp
    src/centurion/surface.hpp

    src/centurion/texture.hpp
    src/centurion/texture_access.hpp
    src/centurion/thread.hpp
    src/centurion/time.hpp
    src/centurion/touch.hpp
    src/centurion/try_lock.hpp

    src/centurion/unicode_string.hpp

    src/centurion/window.hpp
    src/centurion/window_utils.hpp

    src/centurion/detail/address_of.hpp
    src/centurion/detail/any_eq.hpp
    src/centurion/detail/clamp.hpp
    src/centurion/detail/convert_bool.hpp
    src/centurion/detail/czstring_eq.hpp
    src/centurion/detail/max.hpp
    src/centurion/detail/owner_handle_api.hpp
    src/centurion/detail/stack_resource.hpp
    src/centurion/detail/static_bimap.hpp
    src/centurion/detail/to_string.hpp)

if (CEN_AUDIO MATCHES ON)
  set(CENTURION_HEADERS
      ${CENTURION_HEADERS}
      src/centurion/sound_effect.hpp
      src/centurion/music.hpp)
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)

if (CEN_TESTS)
  enable_testing()
  add_subdirectory(test)
endif ()