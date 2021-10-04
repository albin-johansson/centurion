cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 6.3.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
  message("No explicit C++ version specified, assuming C++17...")
  set(CMAKE_CXX_STANDARD 17)
else ()
  message("Using C++${CMAKE_CXX_STANDARD}...")
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

include(Dependencies)
include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/centurion)
set(CEN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})

message("Centurion version: ${CENTURION_VERSION}")

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
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/channels.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/fade_status.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/music.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/music_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/sound_effect.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/audio/sound_fonts.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/compiler/compiler.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/compiler/features.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/core/cast.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/exception.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/integers.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/is_stateless_callable.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/library.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/log.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/log_category.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/log_macros.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/log_priority.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/macros.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/not_null.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/owner.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/result.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/sdl_log_category_workaround.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/sdl_string.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/sfinae.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/str.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/str_or_na.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/time.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/to_underlying.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/core/version.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/detail/address_of.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/any_eq.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/array_utils.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/clamp.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/convert_bool.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/czstring_compare.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/czstring_eq.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/from_string.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/hints_impl.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/lerp.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/max.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/min.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/owner_handle_api.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/sdl_deleter.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/sdl_version_at_least.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/stack_resource.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/static_bimap.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/detail/tuple_type_index.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/events/audio_device_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/common_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/controller_axis_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/controller_button_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/controller_device_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/controller_sensor_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/controller_touchpad_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/display_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/display_event_id.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/dollar_gesture_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/drop_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/event_dispatcher.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/event_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_axis_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_ball_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_button_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_device_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_hat_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/joy_hat_position.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/keyboard_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/mouse_button_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/mouse_motion_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/mouse_wheel_direction.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/mouse_wheel_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/multi_gesture_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/quit_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/sensor_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/text_editing_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/text_input_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/touch_finger_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/user_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/window_event.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/events/window_event_id.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/base_path.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/file.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/file_mode.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/file_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/preferred_path.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/filesystem/seek_mode.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/hints/android_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/apple_tv_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/common_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/controller_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/d3d_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/emscripten_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/enum_hint.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/hint_priority.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/joystick_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/mac_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/mouse_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/qtwayland_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/raspberry_pi_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/windows_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/winrt_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/x11_hints.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/hints/xinput_hints.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/input/button_state.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/controller.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/controller_axis.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/controller_bind_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/controller_button.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/controller_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_condition.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_constant.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_custom.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_direction.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_direction_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_effect.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_left_right.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_periodic.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/haptic_ramp.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/hat_state.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/joystick.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/joystick_power.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/joystick_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/key_code.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/key_modifier.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/keyboard.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/keycodes.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/mouse.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/mouse_button.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/scan_code.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/scancodes.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/sensor.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/sensor_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/touch.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/input/touch_device_type.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/math/area.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/math/point.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/math/rect.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/math/vector3.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/system/battery.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/byte_order.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/clipboard.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/counter.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/cpu.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/locale.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/open_url.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/platform.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/power_state.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/ram.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/system/shared_object.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/thread/condition.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/lock_status.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/mutex.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/scoped_lock.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/semaphore.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/thread.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/thread_priority.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/thread/try_lock.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/video/blend_factor.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/blend_mode.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/blend_op.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/button_order.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/color.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/colors.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/cursor.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/flash_op.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/font.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/font_cache.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/graphics_drivers.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/message_box.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/message_box_type.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/palette.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/pixel_format.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/pixel_format_info.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/renderer.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/renderer_info.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/scale_mode.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/screen.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/surface.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/system_cursor.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/texture.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/texture_access.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/unicode_string.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/window.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/window_utils.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/video/opengl/gl_attribute.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/opengl/gl_context.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/opengl/gl_core.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/opengl/gl_library.hpp

    ${PROJECT_SOURCE_DIR}/src/centurion/video/vulkan/vk_core.hpp
    ${PROJECT_SOURCE_DIR}/src/centurion/video/vulkan/vk_library.hpp

    ${PROJECT_SOURCE_DIR}/src/everything.hpp
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

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
      /EHsc
      )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
      -Wall
      -Wextra
      -Wpedantic
      -Wconversion
      -Wc++17-compat
      )
endif ()

if (CEN_TESTS)
  add_subdirectory(test)
endif ()

if (CEN_EXAMPLES)
  add_subdirectory(examples)
endif ()