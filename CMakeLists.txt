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
               src/centurion/audio/channels.hpp
               src/centurion/audio/fade_status.hpp
               src/centurion/audio/music.hpp
               src/centurion/audio/music_type.hpp
               src/centurion/audio/sound_effect.hpp
               src/centurion/audio/sound_fonts.hpp

               src/centurion/core/common.hpp
               src/centurion/core/compiler.hpp
               src/centurion/core/exception.hpp
               src/centurion/core/features.hpp
               src/centurion/core/is_stateless_callable.hpp
               src/centurion/core/library.hpp
               src/centurion/core/logging.hpp
               src/centurion/core/sdl_string.hpp
               src/centurion/core/time.hpp
               src/centurion/core/version.hpp

               src/centurion/detail/any_eq.hpp
               src/centurion/detail/array_utils.hpp
               src/centurion/detail/convert_bool.hpp
               src/centurion/detail/czstring_compare.hpp
               src/centurion/detail/hints_impl.hpp
               src/centurion/detail/owner_handle_api.hpp
               src/centurion/detail/sdl_deleter.hpp
               src/centurion/detail/sdl_version_at_least.hpp
               src/centurion/detail/stack_resource.hpp
               src/centurion/detail/static_bimap.hpp
               src/centurion/detail/tuple_type_index.hpp

               src/centurion/events/audio_device_event.hpp
               src/centurion/events/common_event.hpp
               src/centurion/events/controller_axis_event.hpp
               src/centurion/events/controller_button_event.hpp
               src/centurion/events/controller_device_event.hpp
               src/centurion/events/controller_sensor_event.hpp
               src/centurion/events/controller_touchpad_event.hpp
               src/centurion/events/display_event.hpp
               src/centurion/events/display_event_id.hpp
               src/centurion/events/dollar_gesture_event.hpp
               src/centurion/events/drop_event.hpp
               src/centurion/events/event.hpp
               src/centurion/events/event_dispatcher.hpp
               src/centurion/events/event_type.hpp
               src/centurion/events/joy_axis_event.hpp
               src/centurion/events/joy_ball_event.hpp
               src/centurion/events/joy_button_event.hpp
               src/centurion/events/joy_device_event.hpp
               src/centurion/events/joy_hat_event.hpp
               src/centurion/events/joy_hat_position.hpp
               src/centurion/events/keyboard_event.hpp
               src/centurion/events/mouse_button_event.hpp
               src/centurion/events/mouse_motion_event.hpp
               src/centurion/events/mouse_wheel_direction.hpp
               src/centurion/events/mouse_wheel_event.hpp
               src/centurion/events/multi_gesture_event.hpp
               src/centurion/events/quit_event.hpp
               src/centurion/events/sensor_event.hpp
               src/centurion/events/text_editing_event.hpp
               src/centurion/events/text_input_event.hpp
               src/centurion/events/touch_finger_event.hpp
               src/centurion/events/user_event.hpp
               src/centurion/events/window_event.hpp
               src/centurion/events/window_event_id.hpp

               src/centurion/filesystem/base_path.hpp
               src/centurion/filesystem/file.hpp
               src/centurion/filesystem/file_mode.hpp
               src/centurion/filesystem/file_type.hpp
               src/centurion/filesystem/preferred_path.hpp
               src/centurion/filesystem/seek_mode.hpp

               src/centurion/hints/android_hints.hpp
               src/centurion/hints/apple_tv_hints.hpp
               src/centurion/hints/common_hints.hpp
               src/centurion/hints/controller_hints.hpp
               src/centurion/hints/d3d_hints.hpp
               src/centurion/hints/emscripten_hints.hpp
               src/centurion/hints/enum_hint.hpp
               src/centurion/hints/hint_priority.hpp
               src/centurion/hints/hints.hpp
               src/centurion/hints/joystick_hints.hpp
               src/centurion/hints/mac_hints.hpp
               src/centurion/hints/mouse_hints.hpp
               src/centurion/hints/qtwayland_hints.hpp
               src/centurion/hints/raspberry_pi_hints.hpp
               src/centurion/hints/windows_hints.hpp
               src/centurion/hints/winrt_hints.hpp
               src/centurion/hints/x11_hints.hpp
               src/centurion/hints/xinput_hints.hpp

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
               src/centurion/input/key_code.hpp
               src/centurion/input/key_modifier.hpp
               src/centurion/input/keyboard.hpp
               src/centurion/input/keycodes.hpp
               src/centurion/input/mouse.hpp
               src/centurion/input/mouse_button.hpp
               src/centurion/input/scan_code.hpp
               src/centurion/input/scancodes.hpp
               src/centurion/input/sensor.hpp
               src/centurion/input/touch.hpp
               src/centurion/input/touch_device_type.hpp

               src/centurion/math/area.hpp
               src/centurion/math/point.hpp
               src/centurion/math/rect.hpp
               src/centurion/math/vector3.hpp

               src/centurion/system/byte_order.hpp
               src/centurion/system/cpu.hpp
               src/centurion/system/locale.hpp
               src/centurion/system/platform.hpp
               src/centurion/system/shared_object.hpp

               src/centurion/thread/condition.hpp
               src/centurion/thread/lock_status.hpp
               src/centurion/thread/mutex.hpp
               src/centurion/thread/scoped_lock.hpp
               src/centurion/thread/semaphore.hpp
               src/centurion/thread/thread.hpp
               src/centurion/thread/thread_priority.hpp
               src/centurion/thread/try_lock.hpp

               src/centurion/video/blend_factor.hpp
               src/centurion/video/blend_mode.hpp
               src/centurion/video/blend_op.hpp
               src/centurion/video/button_order.hpp
               src/centurion/video/color.hpp
               src/centurion/video/colors.hpp
               src/centurion/video/cursor.hpp
               src/centurion/video/flash_op.hpp
               src/centurion/video/font.hpp
               src/centurion/video/font_cache.hpp
               src/centurion/video/graphics_drivers.hpp
               src/centurion/video/message_box.hpp
               src/centurion/video/message_box_type.hpp
               src/centurion/video/palette.hpp
               src/centurion/video/pixel_format.hpp
               src/centurion/video/pixel_format_info.hpp
               src/centurion/video/renderer.hpp
               src/centurion/video/renderer_info.hpp
               src/centurion/video/scale_mode.hpp
               src/centurion/video/screen.hpp
               src/centurion/video/surface.hpp
               src/centurion/video/system_cursor.hpp
               src/centurion/video/texture.hpp
               src/centurion/video/texture_access.hpp
               src/centurion/video/unicode_string.hpp
               src/centurion/video/window.hpp
               src/centurion/video/window_utils.hpp

               src/centurion/video/opengl/gl_attribute.hpp
               src/centurion/video/opengl/gl_context.hpp
               src/centurion/video/opengl/gl_core.hpp
               src/centurion/video/opengl/gl_library.hpp

               src/centurion/video/vulkan/vk_core.hpp
               src/centurion/video/vulkan/vk_library.hpp
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