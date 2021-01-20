cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 5.1.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
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
    include/area.hpp

    include/base_path.hpp
    include/battery.hpp
    include/blend_mode.hpp
    include/button_state.hpp

    include/cast.hpp
    include/centurion.hpp
    include/centurion_api.hpp
    include/centurion_cfg.hpp
    include/clipboard.hpp
    include/color.hpp
    include/colors.hpp
    include/condition.hpp
    include/controller.hpp
    include/counter.hpp
    include/cpu.hpp
    include/cursor.hpp
    include/czstring.hpp

    include/event_type.hpp
    include/event.hpp
    include/exception.hpp

    include/font.hpp
    include/font_cache.hpp

    include/graphics_drivers.hpp

    include/hints.hpp

    include/integers.hpp

    include/joystick.hpp

    include/key_code.hpp
    include/key_modifier.hpp
    include/key_state.hpp

    include/log.hpp

    include/message_box.hpp
    include/mouse_button.hpp
    include/mouse_state.hpp
    include/mutex.hpp

    include/not_null.hpp

    include/owner.hpp

    include/pixel_format.hpp
    include/platform.hpp
    include/point.hpp
    include/pref_path.hpp

    include/ram.hpp
    include/rect.hpp
    include/renderer.hpp

    include/scale_mode.hpp
    include/scan_code.hpp
    include/scoped_lock.hpp
    include/screen.hpp
    include/sdl_string.hpp
    include/semaphore.hpp
    include/surface.hpp

    include/texture.hpp
    include/texture_access.hpp
    include/thread.hpp
    include/time.hpp
    include/touch.hpp
    include/try_lock.hpp
    include/types.hpp

    include/unicode_string.hpp

    include/window.hpp
    include/window_utils.hpp

    include/detail/address_of.hpp
    include/detail/any_eq.hpp
    include/detail/clamp.hpp
    include/detail/convert_bool.hpp
    include/detail/czstring_eq.hpp
    include/detail/max.hpp
    include/detail/owner_handle_api.hpp
    include/detail/stack_resource.hpp
    include/detail/static_bimap.hpp
    include/detail/to_string.hpp)

if (CEN_AUDIO MATCHES ON)
  set(CENTURION_HEADERS
      ${CENTURION_HEADERS}
      include/sound_effect.hpp
      include/music.hpp)
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)
target_include_directories(${CENTURION_LIB_TARGET} INTERFACE ${CEN_INCLUDE_DIR})

export(TARGETS ${CENTURION_LIB_TARGET} FILE ${PROJECT_BINARY_DIR}/centurion-target.cmake)

if (CEN_TESTS)
  enable_testing()
  add_subdirectory(test)
endif ()
