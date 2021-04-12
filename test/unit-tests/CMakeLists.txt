cmake_minimum_required(VERSION 3.15)

project(centurion-test-unittests LANGUAGES CXX)

set(SOURCE_FILES
    serialization_utils.hpp

    typed_test_macros.hpp
    test_main.cpp

    compiler/compiler_test.cpp

    config/hints_test.cpp

    core/exception_test.cpp
    core/sdl_string_test.cpp
    core/version_test.cpp

    detail/address_of_test.cpp
    detail/any_eq_test.cpp
    detail/clamp_test.cpp
    detail/convert_bool_test.cpp
    detail/czstring_eq_test.cpp
    detail/max_test.cpp
    detail/min_test.cpp
    detail/owner_handle_api_test.cpp
    detail/to_string_test.cpp

    event/audio_device_event_test.cpp
    event/common_event_test.cpp
    event/controller_axis_event_test.cpp
    event/controller_button_event_test.cpp
    event/controller_device_event_test.cpp
    event/dollar_gesture_event_test.cpp
    event/drop_event_test.cpp
    event/event_dispatcher_test.cpp
    event/event_test.cpp
    event/event_type_test.cpp
    event/joy_axis_event_test.cpp
    event/joy_ball_event_test.cpp
    event/joy_button_event_test.cpp
    event/joy_device_event_test.cpp
    event/joy_hat_event_test.cpp
    event/joy_hat_position_test.cpp
    event/keyboard_event_test.cpp
    event/mouse_button_event_test.cpp
    event/mouse_motion_event_test.cpp
    event/mouse_wheel_event_test.cpp
    event/mouse_wheel_direction_test.cpp
    event/multi_gesture_event_test.cpp
    event/quit_event_test.cpp
    event/text_editing_event_test.cpp
    event/text_input_event_test.cpp
    event/touch_finger_event_test.cpp
    event/window_event_test.cpp
    event/window_event_id_test.cpp

    input/controller_axis_test.cpp
    input/controller_button_test.cpp
    input/controller_test.cpp
    input/haptic_test.cpp
    input/joystick_test.cpp
    input/key_code_tests.cpp
    input/keyboard_test.cpp
    input/mouse_button_test.cpp
    input/mouse_test.cpp
    input/scan_code_tests.cpp
    input/sensor_test.cpp
    input/touch_test.cpp

    math/area_test.cpp
    math/rect_test.cpp
    math/point_test.cpp
    math/vector3_test.cpp

    misc/log_test.cpp

    system/base_path_test.cpp
    system/battery_test.cpp
    system/byte_order_test.cpp
    system/clipboard_test.cpp
    system/counter_test.cpp
    system/cpu_test.cpp
    system/file_test.cpp
    system/locale_test.cpp
    system/platform_test.cpp
    system/preferred_path_test.cpp
    system/ram_test.cpp
    system/shared_object_test.cpp
    system/simd_block_test.cpp

    thread/condition_test.cpp
    thread/mutex_test.cpp
    thread/scoped_lock_test.cpp
    thread/try_lock_test.cpp
    thread/semaphore_test.cpp
    thread/thread_test.cpp

    video/gl/gl_core_test.cpp

    video/blend_mode_test.cpp
    video/color_test.cpp
    video/cursor_test.cpp
    video/font_cache_test.cpp
    video/font_test.cpp
    video/graphics_drivers_test.cpp
    video/message_box_test.cpp
    video/pixel_format_test.cpp
    video/renderer_test.cpp
    video/renderer_handle_test.cpp
    video/scale_mode_test.cpp
    video/screen_test.cpp
    video/surface_test.cpp
    video/surface_handle_test.cpp
    video/texture_test.cpp
    video/unicode_string_test.cpp
    video/texture_handle_test.cpp
    video/texture_access_test.cpp
    video/window_test.cpp
    video/window_handle_test.cpp
    )

if (CEN_AUDIO)
  set(SOURCE_FILES
      ${SOURCE_FILES}
      audio/sound_effect_test.cpp
      audio/music_test.cpp)
endif ()

cen_create_executable(${CENTURION_TEST_TARGET} "${SOURCE_FILES}")
cen_set_compiler_options(${CENTURION_TEST_TARGET})

if (CEN_AUDIO)
  target_compile_definitions(${CENTURION_TEST_TARGET}
      PUBLIC CEN_AUDIO)
endif ()

target_include_directories(${CENTURION_TEST_TARGET}
    PUBLIC .
    PUBLIC ${CEN_SOURCE_DIR}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}
    SYSTEM PUBLIC ../lib/cereal)

target_link_libraries(${CENTURION_TEST_TARGET}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC gtest)

add_test(NAME ${CENTURION_TEST_TARGET} COMMAND ${CENTURION_TEST_TARGET})

copy_directory_post_build(${CENTURION_TEST_TARGET}
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(${CENTURION_TEST_TARGET})
endif ()