cmake_minimum_required(VERSION 3.12)
project(CenturionTestProj)

set(TEST_FILES
        unittests/test_main.cpp
        unittests/window_test.cpp
        unittests/bool_converter_test.cpp
        unittests/font_test.cpp
        unittests/texture_test.cpp
        unittests/texture_loader_test.cpp
        unittests/renderer_test.cpp
        unittests/log_test.cpp
        unittests/battery_test.cpp
        unittests/blend_mode_test.cpp
        unittests/message_box_test.cpp
        unittests/color_test.cpp
        unittests/point_test.cpp
        unittests/key_state_test.cpp
        unittests/mouse_state_test.cpp
        unittests/rect_test.cpp
        unittests/centurion_exception_test.cpp
        unittests/error_test.cpp
        unittests/timer_test.cpp
        unittests/paths_test.cpp
        unittests/platform_test.cpp
        unittests/cpu_test.cpp
        unittests/ram_test.cpp
        unittests/screen_test.cpp
        unittests/audio_test.cpp
        unittests/surface_test.cpp
        unittests/pixel_format_test.cpp
        unittests/cursor_test.cpp
        unittests/key_test.cpp
        unittests/window_event_test.cpp
        unittests/keyboard_event_test.cpp
        unittests/common_event_test.cpp
        unittests/audio_device_event_test.cpp
        unittests/controller_axis_event_test.cpp
        unittests/controller_button_event_test.cpp
        unittests/game_controller_button_test.cpp
        unittests/game_controller_axis_test.cpp
        unittests/controller_device_event_test.cpp
        unittests/dollar_gesture_event_test.cpp
        unittests/drop_event_test.cpp
        unittests/touch_finger_event_test.cpp
        unittests/joy_axis_event_test.cpp
        unittests/joy_ball_event_test.cpp
        unittests/joy_hat_event_test.cpp
        unittests/joy_button_event_test.cpp
        unittests/event_test.cpp
        unittests/joy_device_event_test.cpp
        unittests/mouse_button_test.cpp
        unittests/mouse_motion_event_test.cpp
        unittests/mouse_button_event_test.cpp
        unittests/mouse_wheel_event_test.cpp
        unittests/multi_gesture_event_test.cpp
        unittests/text_editing_event_test.cpp
        unittests/text_input_event_test.cpp
        unittests/quit_event_test.cpp)

if (NOT DEFINED ENV{TRAVIS})
    set(TEST_FILES
            ${TEST_FILES}
            unittests/sound_effect_test.cpp
            unittests/music_test.cpp)
endif ()

add_executable(${CENTURION_TEST_TARGET} ${TEST_FILES})
add_dependencies(${CENTURION_TEST_TARGET} ${CENTURION_LIB_TARGET})

if (DEFINED ENV{TRAVIS})
    target_compile_definitions(${CENTURION_TEST_TARGET} PUBLIC CENTURION_NOAUDIO)
    target_compile_definitions(${CENTURION_TEST_TARGET} PUBLIC TRAVIS_TEST)
endif ()

set_target_properties(${CENTURION_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

include(CTest)
include(Catch)

enable_testing()
add_test(NAME ${CENTURION_TEST_TARGET}
        COMMAND ${CENTURION_TEST_TARGET})

target_include_directories(${CENTURION_TEST_TARGET} PUBLIC unittests)
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${CTN_LIBRARY_DIR})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${CTN_INCLUDE_DIR})
target_include_directories(${CENTURION_TEST_TARGET} SYSTEM PUBLIC ${CTN_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
            -Wno-unused-result
            )
endif ()

message("------ LINKING TEST EXECUTABLE ------")
message("Linking against SDL2: ${SDL2_LIBRARY}")
message("Linking against SDL2_image: ${SDL2_IMAGE_LIBRARIES}")
message("Linking against SDL2_image: ${SDL2_MIXER_LIBRARIES}")
message("Linking against SDL2_image: ${SDL2_TTF_LIBRARIES}")
message("Centurion link target (unused in header-only mode): ${CENTURION_LIBRARIES}")
target_link_libraries(${CENTURION_TEST_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${CENTURION_LIBRARIES}
        PUBLIC Catch2)

catch_discover_tests(${CENTURION_TEST_TARGET})

copy_directory_post_build(
        ${CENTURION_TEST_TARGET}
        ${CTN_RESOURCES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
    copy_file_post_build(
            ${CENTURION_TEST_TARGET}
            ${CENTURION_DYNAMIC_LIB}
            ${CMAKE_CURRENT_BINARY_DIR})

    copy_directory_post_build(
            ${CENTURION_TEST_TARGET}
            ${CTN_BINARIES_DIR}
            ${CMAKE_CURRENT_BINARY_DIR})
endif ()
