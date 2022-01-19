cmake_minimum_required(VERSION 3.15)

project(centurion-test-unit-tests)

set(SOURCE_FILES
    serialization_utils.hpp

    typed_test_macros.hpp
    test_main.cpp

    concurrency/condition_test.cpp
    concurrency/lock_status_test.cpp
    concurrency/mutex_test.cpp
    concurrency/scoped_lock_test.cpp
    concurrency/semaphore_test.cpp
    concurrency/thread_priority_test.cpp
    concurrency/thread_test.cpp
    concurrency/try_lock_test.cpp

    controller/controller_axis_test.cpp
    controller/controller_bind_type_test.cpp
    controller/controller_button_test.cpp
    controller/controller_mapping_result_test.cpp
    controller/controller_test.cpp
    controller/controller_type_test.cpp

    core/exception_test.cpp
    core/features_test.cpp
    core/log_category_test.cpp
    core/log_priority_test.cpp
    core/log_test.cpp
    core/result_test.cpp
    core/sdl_string_test.cpp
    core/to_underlying_test.cpp
    core/version_test.cpp

    detail/address_of_test.cpp
    detail/clamp_test.cpp
    detail/from_string_test.cpp
    detail/max_test.cpp
    detail/min_test.cpp
    detail/owner_handle_api_test.cpp

    endian/endian_test.cpp

    event/audio_device_event_test.cpp
    event/common_event_test.cpp
    event/drop_event_test.cpp
    event/event_dispatcher_test.cpp
    event/event_test.cpp
    event/event_type_test.cpp
    event/keyboard_event_test.cpp
    event/quit_event_test.cpp
    event/sensor_event_test.cpp
    event/touch_finger_event_test.cpp
    event/user_event_test.cpp

    event/controller/controller_axis_event_test.cpp
    event/controller/controller_button_event_test.cpp
    event/controller/controller_device_event_test.cpp
    event/controller/controller_sensor_event_test.cpp
    event/controller/controller_touchpad_event_test.cpp

    event/display/display_event_id_test.cpp
    event/display/display_event_test.cpp

    event/gesture/dollar_gesture_event_test.cpp
    event/gesture/multi_gesture_event_test.cpp

    event/joystick/joy_axis_event_test.cpp
    event/joystick/joy_ball_event_test.cpp
    event/joystick/joy_button_event_test.cpp
    event/joystick/joy_device_event_test.cpp
    event/joystick/joy_hat_event_test.cpp
    event/joystick/joy_hat_position_test.cpp

    event/mouse/mouse_button_event_test.cpp
    event/mouse/mouse_motion_event_test.cpp
    event/mouse/mouse_wheel_direction_test.cpp
    event/mouse/mouse_wheel_event_test.cpp

    event/text/text_editing_event_test.cpp
    event/text/text_input_event_test.cpp

    event/window/window_event_id_test.cpp
    event/window/window_event_test.cpp

    filesystem/base_path_test.cpp
    filesystem/file_mode_test.cpp
    filesystem/file_test.cpp
    filesystem/file_type_test.cpp
    filesystem/preferred_path_test.cpp
    filesystem/seek_mode_test.cpp

    font/font_bundle_test.cpp
    font/font_cache_test.cpp
    font/font_hint_test.cpp
    font/font_test.cpp

    hints/hint_priority_test.cpp
    hints/hints_test.cpp

    input/button_state_test.cpp
    input/haptic_direction_type_test.cpp
    input/haptic_feature_test.cpp
    input/haptic_test.cpp
    input/hat_state_test.cpp
    input/joystick_power_test.cpp
    input/joystick_test.cpp
    input/joystick_type_test.cpp
    input/sensor_test.cpp
    input/sensor_type_test.cpp
    input/touch_device_type_test.cpp
    input/touch_test.cpp

    keyboard/key_code_tests.cpp
    keyboard/key_modifier_test.cpp
    keyboard/keyboard_test.cpp
    keyboard/scan_code_tests.cpp

    locale/locale_test.cpp

    math/area_test.cpp
    math/rect_test.cpp
    math/point_test.cpp
    math/vector3_test.cpp

    memory/simd_block_test.cpp

    message-box/mb_button_flags_test.cpp
    message-box/mb_button_order_test.cpp
    message-box/mb_color_scheme.cpp
    message-box/mb_color_type_test.cpp
    message-box/mb_type_test.cpp
    message-box/message_box_test.cpp

    mouse/cursor_test.cpp
    mouse/mouse_button_test.cpp
    mouse/mouse_test.cpp
    mouse/system_cursor_test.cpp

    pixels/palette_test.cpp
    pixels/pixel_format_info_test.cpp
    pixels/pixel_format_test.cpp

    power/battery_test.cpp
    power/power_state_test.cpp

    render/graphics_drivers_test.cpp
    render/renderer_handle_test.cpp
    render/renderer_test.cpp

    system/clipboard_test.cpp
    system/counter_test.cpp
    system/platform_id_test.cpp
    system/platform_test.cpp
    system/ram_test.cpp
    system/shared_object_test.cpp

    texture/scale_mode_test.cpp
    texture/texture_access_test.cpp
    texture/texture_handle_test.cpp
    texture/texture_test.cpp

    unicode/unicode_string_test.cpp

    video/blend_factor_test.cpp
    video/blend_mode_test.cpp
    video/blend_op_test.cpp
    video/color_test.cpp
    video/display_mode_test.cpp
    video/display_test.cpp
    video/flash_op_test.cpp
    video/orientation_test.cpp
    video/surface_handle_test.cpp
    video/surface_test.cpp
    video/window_flags_test.cpp
    video/window_test.cpp
    video/window_handle_test.cpp

    video/opengl/gl_attribute_test.cpp
    video/opengl/gl_swap_interval_test.cpp
    )

if (CEN_AUDIO)
  list(APPEND
       SOURCE_FILES
       audio/fade_status_test.cpp
       audio/music_test.cpp
       audio/music_type_test.cpp
       audio/sound_effect_test.cpp
       )
endif ()

add_executable(${CENTURION_TEST_TARGET} ${SOURCE_FILES})
add_dependencies(${CENTURION_TEST_TARGET} ${CENTURION_LIB_TARGET})

target_include_directories(${CENTURION_TEST_TARGET}
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}
                           ${CEN_SOURCE_DIR}

                           SYSTEM PRIVATE
                           ${gtest_SOURCE_DIR}/include
                           ${gtest_SOURCE_DIR}
                           ${gmock_SOURCE_DIR}/include
                           ${gmock_SOURCE_DIR}
                           ${CEN_LIBRARY_DIR}/cereal
                           )

target_link_libraries(${CENTURION_TEST_TARGET} PRIVATE
                      ${CENTURION_LIB_TARGET}
                      gtest
                      )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
                         /wd4834  # "discarding return value of function with 'nodiscard' attribute"
                         )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
                         -Wno-unused-result
                         )
endif ()

if (CEN_AUDIO)
  target_compile_definitions(${CENTURION_TEST_TARGET} PRIVATE CEN_AUDIO)
endif ()

target_precompile_headers(${CENTURION_TEST_TARGET} PRIVATE
                          <SDL.h>
                          <array>
                          <algorithm>
                          <vector>
                          <memory>
                          <string>
                          <string_view>
                          <sstream>
                          <optional>
                          <ostream>
                          <iostream>
                          <utility>
                          <type_traits>
                          )

add_test(NAME ${CENTURION_TEST_TARGET} COMMAND ${CENTURION_TEST_TARGET})

copy_directory_post_build(${CENTURION_TEST_TARGET}
                          ${CEN_RESOURCES_DIR}
                          ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  copy_directory_post_build(${CENTURION_TEST_TARGET} ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()