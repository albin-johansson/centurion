cmake_minimum_required(VERSION 3.15)
project(CenturionSrcProj)

set(SOURCE_FILES
        ${CTN_INCLUDE_DIR}/centurion_cfg.hpp
        ${CTN_INCLUDE_DIR}/centurion_fwd.hpp
        ${CTN_INCLUDE_DIR}/centurion_types.hpp
        ${CTN_INCLUDE_DIR}/video.hpp
        ${CTN_INCLUDE_DIR}/basic_window.hpp
        ${CTN_INCLUDE_DIR}/basic_window.ipp
        ${CTN_INCLUDE_DIR}/window.hpp
        ${CTN_INCLUDE_DIR}/window_handle.hpp
        ${CTN_INCLUDE_DIR}/window_utils.hpp
        ${CTN_INCLUDE_DIR}/window_utils.ipp
        ${CTN_INCLUDE_DIR}/font.hpp
        ${CTN_INCLUDE_DIR}/basic_renderer.hpp
        ${CTN_INCLUDE_DIR}/basic_renderer.ipp
        ${CTN_INCLUDE_DIR}/renderer.hpp
        ${CTN_INCLUDE_DIR}/renderer.ipp
        ${CTN_INCLUDE_DIR}/renderer_handle.hpp
        ${CTN_INCLUDE_DIR}/basic_joystick.hpp
        ${CTN_INCLUDE_DIR}/basic_joystick.ipp
        ${CTN_INCLUDE_DIR}/joystick.hpp
        ${CTN_INCLUDE_DIR}/texture.hpp
        ${CTN_INCLUDE_DIR}/texture.ipp
        ${CTN_INCLUDE_DIR}/centurion_exception.hpp
        ${CTN_INCLUDE_DIR}/centurion_api.hpp
        ${CTN_INCLUDE_DIR}/centurion.hpp
        ${CTN_INCLUDE_DIR}/colors.hpp
        ${CTN_INCLUDE_DIR}/texture_loader.hpp
        ${CTN_INCLUDE_DIR}/texture_loader.ipp
        ${CTN_INCLUDE_DIR}/paths.hpp
        ${CTN_INCLUDE_DIR}/platform.hpp
        ${CTN_INCLUDE_DIR}/counter.hpp
        ${CTN_INCLUDE_DIR}/log.hpp
        ${CTN_INCLUDE_DIR}/blend_mode.hpp
        ${CTN_INCLUDE_DIR}/message_box.hpp
        ${CTN_INCLUDE_DIR}/message_box.ipp
        ${CTN_INCLUDE_DIR}/color.hpp
        ${CTN_INCLUDE_DIR}/rect.hpp
        ${CTN_INCLUDE_DIR}/point.hpp
        ${CTN_INCLUDE_DIR}/key_state.hpp
        ${CTN_INCLUDE_DIR}/mouse_state.hpp
        ${CTN_INCLUDE_DIR}/centurion_utils.hpp
        ${CTN_INCLUDE_DIR}/surface.hpp
        ${CTN_INCLUDE_DIR}/pixel_format.hpp
        ${CTN_INCLUDE_DIR}/cursor.hpp
        ${CTN_INCLUDE_DIR}/cpu.hpp
        ${CTN_INCLUDE_DIR}/ram.hpp
        ${CTN_INCLUDE_DIR}/battery.hpp
        ${CTN_INCLUDE_DIR}/screen.hpp
        ${CTN_INCLUDE_DIR}/scan_code.hpp
        ${CTN_INCLUDE_DIR}/touch.hpp
        ${CTN_INCLUDE_DIR}/mouse_button.hpp
        ${CTN_INCLUDE_DIR}/event_type.hpp
        ${CTN_INCLUDE_DIR}/event.hpp
        ${CTN_INCLUDE_DIR}/button_state.hpp
        ${CTN_INCLUDE_DIR}/game_controller.hpp
        ${CTN_INCLUDE_DIR}/area.hpp
        ${CTN_INCLUDE_DIR}/key_modifier.hpp
        ${CTN_INCLUDE_DIR}/hints.hpp
        ${CTN_INCLUDE_DIR}/touch.hpp
        ${CTN_INCLUDE_DIR}/font_cache.hpp
        ${CTN_INCLUDE_DIR}/font_cache.ipp
        ${CTN_INCLUDE_DIR}/unicode_string.hpp
        ${CTN_INCLUDE_DIR}/game_loop.hpp

        core/centurion.cpp
        core/centurion_exception.cpp

        misc/log.cpp

        graphics/window.cpp
        graphics/window_handle.cpp
        graphics/font.cpp
        graphics/font_cache.cpp
        graphics/texture.cpp
        graphics/message_box.cpp
        graphics/message_box_button.cpp
        graphics/message_box_color_scheme.cpp
        graphics/surface.cpp
        graphics/cursor.cpp
        graphics/basic_renderer.cpp
        graphics/renderer_handle.cpp
        graphics/renderer.cpp
        graphics/color.cpp

        system/base_path.cpp
        system/pref_path.cpp
        system/platform.cpp
        system/battery.cpp
        system/screen.cpp

        input/key_state.cpp
        input/mouse_state.cpp
        input/game_controller.cpp
        input/joystick.cpp
        input/touch.cpp
        input/key_code.cpp
        input/scan_code.cpp

        event/event.cpp
        event/quit_event.cpp
        event/window_event.cpp
        event/keyboard_event.cpp
        event/audio_device_event.cpp
        event/controller_axis_event.cpp
        event/controller_button_event.cpp
        event/controller_device_event.cpp
        event/dollar_gesture_event.cpp
        event/drop_event.cpp
        event/touch_finger_event.cpp
        event/joy_axis_event.cpp
        event/joy_ball_event.cpp
        event/joy_hat_event.cpp
        event/joy_button_event.cpp
        event/joy_device_event.cpp
        event/mouse_motion_event.cpp
        event/mouse_button_event.cpp
        event/mouse_wheel_event.cpp
        event/multi_gesture_event.cpp
        event/text_editing_event.cpp
        event/text_input_event.cpp ../include/joystick_handle.hpp input/joystick_handle.cpp)

if (NOT DEFINED ENV{TRAVIS})
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${CTN_INCLUDE_DIR}/sound_effect.hpp
            ${CTN_INCLUDE_DIR}/music.hpp
            audio/sound_effect.cpp
            audio/music.cpp)
endif ()

add_library(${CENTURION_LIB_TARGET} SHARED ${SOURCE_FILES})

if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CENTURION_OUTPUT_NAME Centurion)
else ()
    set(CENTURION_OUTPUT_NAME libCenturion)
endif ()

if (DEFINED ENV{TRAVIS})
    target_compile_definitions(${CENTURION_LIB_TARGET} PUBLIC CENTURION_NOAUDIO)
endif ()

set_target_properties(${CENTURION_LIB_TARGET} PROPERTIES
        VERSION 5.0.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME ${CENTURION_OUTPUT_NAME})

set(GSL_SOURCES
        ${CTN_LIBRARY_DIR}/microsoft/gsl/gsl
        ${CTN_LIBRARY_DIR}/microsoft/gsl/gsl_algorithm
        ${CTN_LIBRARY_DIR}/microsoft/gsl/gsl_assert
        ${CTN_LIBRARY_DIR}/microsoft/gsl/gsl_byte
        ${CTN_LIBRARY_DIR}/microsoft/gsl/gsl_util
        ${CTN_LIBRARY_DIR}/microsoft/gsl/multi_span
        ${CTN_LIBRARY_DIR}/microsoft/gsl/pointers
        ${CTN_LIBRARY_DIR}/microsoft/gsl/span
        ${CTN_LIBRARY_DIR}/microsoft/gsl/span_ext
        ${CTN_LIBRARY_DIR}/microsoft/gsl/string_span)
centurion_add_header_only_lib(libGSL "${CTN_LIBRARY_DIR}/microsoft" ${GSL_SOURCES})

centurion_add_header_only_lib(libEnTT ${CTN_LIBRARY_DIR}/entt ${CTN_LIBRARY_DIR}/entt/entt.hpp)

target_include_directories(${CENTURION_LIB_TARGET}
        PRIVATE ${CTN_INCLUDE_DIR}
        PRIVATE ${CTN_SOURCE_DIR}
        SYSTEM INTERFACE ${CTN_INCLUDE_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC libEnTT
        PUBLIC libGSL)

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
            /MP
            /W3)
endif ()

