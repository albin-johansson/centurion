cmake_minimum_required(VERSION 3.15)

project(centurion-test-unittests LANGUAGES CXX)

set(UNIT_TEST_FILES
    test_main.cpp
    centurion_test.cpp
    exception_test.cpp
    log_test.cpp
    sdl_string_test.cpp

    detail/bool_converter_test.cpp
    detail/to_string_test.cpp

    system/base_path_test.cpp
    system/battery_test.cpp
    system/clipboard_test.cpp
    system/counter_test.cpp
    system/cpu_test.cpp
    system/platform_test.cpp
    system/pref_path_test.cpp
    system/ram_test.cpp
    system/screen_test.cpp

    geometry/area_test.cpp
    geometry/rect_test.cpp
    geometry/point_test.cpp

    graphics/blend_mode_test.cpp
    graphics/color_test.cpp
    graphics/cursor_test.cpp
    graphics/font_test.cpp
    graphics/font_cache_test.cpp
    graphics/surface_test.cpp
    graphics/surface_handle_test.cpp
    graphics/texture_test.cpp
    graphics/texture_handle_test.cpp
    graphics/texture_access_test.cpp
    graphics/scale_mode_test.cpp

    input/controller_axis_test.cpp
    input/controller_button_test.cpp
    input/controller_test.cpp
    input/key_code_tests.cpp

    thread/condition_test.cpp
    thread/mutex_test.cpp
    thread/scoped_lock_test.cpp
    thread/try_lock_test.cpp
    thread/semaphore_test.cpp
    thread/thread_test.cpp

    event/audio_device_event_test.cpp
    event/common_event_test.cpp
    event/controller_axis_event_test.cpp
    event/controller_button_event_test.cpp
    event/controller_device_event_test.cpp
    event/dollar_gesture_event_test.cpp
    event/drop_event_test.cpp
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
    event/window_event_id_test.cpp)

#if (CEN_AUDIO)
#    set(UNIT_TEST_FILES
#            ${UNIT_TEST_FILES}
#            unittests/sound_effect_test.cpp
#            unittests/music_test.cpp)
#endif ()

if (WIN32)
  add_executable(${CENTURION_TEST_TARGET} WIN32 ${UNIT_TEST_FILES})
else ()
  add_executable(${CENTURION_TEST_TARGET} ${UNIT_TEST_FILES})
endif ()

if (CEN_AUDIO)
  target_compile_definitions(${CENTURION_TEST_TARGET}
      PUBLIC CEN_AUDIO)
endif ()

cen_set_compiler_options(${CENTURION_TEST_TARGET})

target_include_directories(${CENTURION_TEST_TARGET}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${CEN_INCLUDE_DIR}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR})

target_link_libraries(${CENTURION_TEST_TARGET}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${CENTURION_IMPORT_LIB}
    PUBLIC gtest)

add_test(NAME ${CENTURION_TEST_TARGET} COMMAND ${CENTURION_TEST_TARGET})

copy_directory_post_build(${CENTURION_TEST_TARGET}
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  copy_file_post_build(
      ${CENTURION_TEST_TARGET}
      ${CENTURION_DYNAMIC_LIB}
      ${CMAKE_CURRENT_BINARY_DIR})

  copy_directory_post_build(
      ${CENTURION_TEST_TARGET}
      ${CEN_BINARIES_DIR}
      ${CMAKE_CURRENT_BINARY_DIR})
endif ()
