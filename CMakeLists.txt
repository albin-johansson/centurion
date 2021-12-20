cmake_minimum_required(VERSION 3.15)

project(centurion
        VERSION 7.0.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})
message("[centurion]: version ${CENTURION_VERSION}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
  message("[centurion]: no explicit C++ version specified")
  set(CMAKE_CXX_STANDARD 17)
endif ()

message("[centurion]: using C++ standard... ${CMAKE_CXX_STANDARD}")
message("[centurion]: compiler is... ${CMAKE_CXX_COMPILER}")
message("[centurion]: compiler identifier is... ${CMAKE_CXX_COMPILER_ID}")

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

include(Dependencies)
include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/centurion)
set(CEN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)

set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET testcenturion)
set(CENTURION_MOCK_TARGET mockcenturion)

option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" ON)
option(CEN_EXAMPLES "Build the examples" ON)
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

if (CEN_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)

target_sources(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
               src/centurion/audio.hpp
               src/centurion/color.hpp
               src/centurion/concurrency.hpp
               src/centurion/endian.hpp
               src/centurion/filesystem.hpp
               src/centurion/font.hpp
               src/centurion/keyboard.hpp
               src/centurion/locale.hpp
               src/centurion/math.hpp
               src/centurion/message_box.hpp
               src/centurion/mouse.hpp
               src/centurion/opengl.hpp
               src/centurion/pixels.hpp
               src/centurion/power.hpp
               src/centurion/render.hpp
               src/centurion/surface.hpp
               src/centurion/system.hpp
               src/centurion/texture.hpp
               src/centurion/unicode.hpp
               src/centurion/video.hpp
               src/centurion/vulkan.hpp

               src/centurion/common.hpp
               src/centurion/core/exception.hpp
               src/centurion/core/features.hpp
               src/centurion/core/initialization.hpp
               src/centurion/core/logging.hpp
               src/centurion/core/sdl_string.hpp
               src/centurion/core/version.hpp

               src/centurion/detail/array_utils.hpp
               src/centurion/detail/owner_handle_api.hpp
               src/centurion/detail/sdl_deleter.hpp
               src/centurion/detail/sdl_version_at_least.hpp
               src/centurion/detail/stack_resource.hpp
               src/centurion/detail/tuple_type_index.hpp

               src/centurion/events/audio_device_event.hpp
               src/centurion/events/controller_events.hpp
               src/centurion/events/display_event.hpp
               src/centurion/events/display_event_id.hpp
               src/centurion/events/dollar_gesture_event.hpp
               src/centurion/events/drop_event.hpp
               src/centurion/events/event.hpp
               src/centurion/events/event_base.hpp
               src/centurion/events/event_dispatcher.hpp
               src/centurion/events/event_type.hpp
               src/centurion/events/joystick_events.hpp
               src/centurion/events/keyboard_event.hpp
               src/centurion/events/mouse_events.hpp
               src/centurion/events/multi_gesture_event.hpp
               src/centurion/events/quit_event.hpp
               src/centurion/events/sensor_event.hpp
               src/centurion/events/text_editing_event.hpp
               src/centurion/events/text_input_event.hpp
               src/centurion/events/touch_finger_event.hpp
               src/centurion/events/user_event.hpp
               src/centurion/events/window_event.hpp

               src/centurion/input/button_state.hpp
               src/centurion/input/controller.hpp
               src/centurion/input/haptic.hpp
               src/centurion/input/haptic_condition.hpp
               src/centurion/input/haptic_constant.hpp
               src/centurion/input/haptic_custom.hpp
               src/centurion/input/haptic_direction.hpp
               src/centurion/input/haptic_direction_type.hpp
               src/centurion/input/haptic_effect.hpp
               src/centurion/input/haptic_left_right.hpp
               src/centurion/input/haptic_periodic.hpp
               src/centurion/input/haptic_ramp.hpp
               src/centurion/input/joystick.hpp
               src/centurion/input/sensor.hpp
               src/centurion/input/touch.hpp
               src/centurion/input/touch_device_type.hpp

               src/centurion/window.hpp
               )

target_include_directories(${CENTURION_LIB_TARGET}
                           PUBLIC INTERFACE
                           ${PROJECT_SOURCE_DIR}/src

                           SYSTEM PUBLIC INTERFACE
                           ${SDL2_INCLUDE_DIR}
                           ${SDL2_IMAGE_INCLUDE_DIRS}
                           ${SDL2_TTF_INCLUDE_DIRS}
                           ${SDL2_MIXER_INCLUDE_DIRS}
                           )

target_link_libraries(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
                      ${SDL2_LIBRARY}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES}
                      ${SDL2_MIXER_LIBRARIES}
                      )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
                         /EHsc
                         /MP
                         /W4
                         /Zc:preprocessor # Enable conforming preprocessor
                         /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                         )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
                         -Wall
                         -Wextra
                         -Wpedantic
                         -Wconversion
                         )
else ()
  message("[centurion]: could not determine compiler options")
endif ()

if (CEN_TESTS)
  add_subdirectory(test)
endif ()

if (CEN_EXAMPLES)
  add_subdirectory(examples)
endif ()