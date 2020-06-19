cmake_minimum_required(VERSION 3.15)
project(CenturionSrcProj)

set(SOURCE_FILES
        ${CTN_INCLUDE_DIR}/window.h
        ${CTN_INCLUDE_DIR}/font.h
        ${CTN_INCLUDE_DIR}/renderer.h
        ${CTN_INCLUDE_DIR}/texture.h
        ${CTN_INCLUDE_DIR}/centurion_exception.h
        ${CTN_INCLUDE_DIR}/centurion_api.h
        ${CTN_INCLUDE_DIR}/centurion.h
        ${CTN_INCLUDE_DIR}/colors.h
        ${CTN_INCLUDE_DIR}/texture_loader.h
        ${CTN_INCLUDE_DIR}/paths.h
        ${CTN_INCLUDE_DIR}/platform.h
        ${CTN_INCLUDE_DIR}/timer.h
        ${CTN_INCLUDE_DIR}/log.h
        ${CTN_INCLUDE_DIR}/blend_mode.h
        ${CTN_INCLUDE_DIR}/message_box.h
        ${CTN_INCLUDE_DIR}/color.h
        ${CTN_INCLUDE_DIR}/rect.h
        ${CTN_INCLUDE_DIR}/point.h
        ${CTN_INCLUDE_DIR}/key_state.h
        ${CTN_INCLUDE_DIR}/mouse_state.h
        ${CTN_INCLUDE_DIR}/centurion_utils.h
        ${CTN_INCLUDE_DIR}/error.h
        ${CTN_INCLUDE_DIR}/surface.h
        ${CTN_INCLUDE_DIR}/pixel_format.h
        ${CTN_INCLUDE_DIR}/cursor.h
        ${CTN_INCLUDE_DIR}/cpu.h
        ${CTN_INCLUDE_DIR}/ram.h
        ${CTN_INCLUDE_DIR}/battery.h
        ${CTN_INCLUDE_DIR}/screen.h
        ${CTN_INCLUDE_DIR}/key.h
        ${CTN_INCLUDE_DIR}/touch.h
        ${CTN_INCLUDE_DIR}/event.h
        ${CTN_INCLUDE_DIR}/event_type.h
        ${CTN_INCLUDE_DIR}/mouse_button.h
        ${CTN_INCLUDE_DIR}/event.h
        ${CTN_INCLUDE_DIR}/keyboard_event.h
        ${CTN_INCLUDE_DIR}/common_event.h
        ${CTN_INCLUDE_DIR}/quit_event.h
        ${CTN_INCLUDE_DIR}/button_state.h
        ${CTN_INCLUDE_DIR}/window_event.h
        ${CTN_INCLUDE_DIR}/audio_device_event.h
        ${CTN_INCLUDE_DIR}/controller_axis_event.h
        ${CTN_INCLUDE_DIR}/controller_button_event.h
        ${CTN_INCLUDE_DIR}/game_controller.h
        ${CTN_INCLUDE_DIR}/controller_device_event.h
        ${CTN_INCLUDE_DIR}/dollar_gesture_event.h
        ${CTN_INCLUDE_DIR}/drop_event.h
        ${CTN_INCLUDE_DIR}/touch_finger_event.h
        ${CTN_INCLUDE_DIR}/joy_axis_event.h
        ${CTN_INCLUDE_DIR}/joy_ball_event.h
        ${CTN_INCLUDE_DIR}/joy_hat_event.h
        ${CTN_INCLUDE_DIR}/joy_button_event.h
        ${CTN_INCLUDE_DIR}/joy_device_event.h
        ${CTN_INCLUDE_DIR}/mouse_motion_event.h
        ${CTN_INCLUDE_DIR}/mouse_button_event.h
        ${CTN_INCLUDE_DIR}/mouse_wheel_event.h
        ${CTN_INCLUDE_DIR}/multi_gesture_event.h
        ${CTN_INCLUDE_DIR}/text_editing_event.h
        ${CTN_INCLUDE_DIR}/text_input_event.h
        ${CTN_INCLUDE_DIR}/area.h
        ${CTN_INCLUDE_DIR}/key_modifier.h
        ${CTN_INCLUDE_DIR}/syswm_event.h
        ${CTN_INCLUDE_DIR}/hints.h
        window.cpp
        font.cpp
        renderer.cpp
        texture.cpp
        centurion_exception.cpp
        centurion.cpp
        texture_loader.cpp
        paths.cpp
        platform.cpp
        log.cpp
        timer.cpp
        message_box.cpp
        color.cpp
        blend_mode.cpp
        key_state.cpp
        mouse_state.cpp
        error.cpp
        surface.cpp
        cursor.cpp
        pixel_format.cpp
        cpu.cpp
        ram.cpp
        battery.cpp
        screen.cpp
        key.cpp
        event.cpp
        event_type.cpp
        quit_event.cpp
        window_event.cpp
        keyboard_event.cpp
        audio_device_event.cpp
        controller_axis_event.cpp
        controller_button_event.cpp
        game_controller.cpp
        controller_device_event.cpp
        dollar_gesture_event.cpp
        drop_event.cpp
        touch_finger_event.cpp
        joy_axis_event.cpp
        joy_ball_event.cpp
        joy_hat_event.cpp
        joy_button_event.cpp
        joy_device_event.cpp
        mouse_motion_event.cpp
        mouse_button_event.cpp
        mouse_wheel_event.cpp
        multi_gesture_event.cpp
        text_editing_event.cpp
        text_input_event.cpp
        syswm_event.cpp)

if (NOT DEFINED ENV{TRAVIS})
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${CTN_INCLUDE_DIR}/sound_effect.h
            ${CTN_INCLUDE_DIR}/music.h
            sound_effect.cpp
            music.cpp)
endif ()

add_library(${CENTURION_LIB_TARGET} SHARED ${SOURCE_FILES})

if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

if (DEFINED ENV{TRAVIS})
    target_compile_definitions(${CENTURION_LIB_TARGET} PUBLIC CENTURION_NOAUDIO)
endif ()

set_target_properties(${CENTURION_LIB_TARGET} PROPERTIES
        VERSION 4.0.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "libcenturion")

target_include_directories(${CENTURION_LIB_TARGET}
        PRIVATE ${CTN_INCLUDE_DIR}
        SYSTEM INTERFACE ${CTN_INCLUDE_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC libGSL
        PUBLIC libOptional)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wuninitialized
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wsuggest-override
            -Wduplicated-cond
            -Wconversion
            -Wc++11-compat
            -Wc++14-compat
            -Wc++17-compat)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
            /EHsc
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wuninitialized
            -Wconversion
            -Wc++11-compat
            -Wc++14-compat
            -Wc++17-compat
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-unused-template
            -Wno-unused-macros
            -Wno-newline-eof
            -Wno-documentation-unknown-command)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${CENTURION_LIB_TARGET} PRIVATE
            /EHsc
            /W3
            /experimental:external
            /external:anglebrackets)
endif ()
