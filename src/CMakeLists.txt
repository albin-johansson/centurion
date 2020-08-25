cmake_minimum_required(VERSION 3.15)
project(CenturionSrcProj)

set(SOURCE_FILES
        ../include/centurion_cfg.hpp
        ../include/centurion_fwd.hpp
        ../include/centurion_types.hpp
        ../include/video.hpp
        ../include/basic_window.hpp
        ../include/basic_window.ipp
        ../include/window.hpp
        ../include/window_handle.hpp
        ../include/window_utils.hpp
        ../include/window_utils.ipp
        ../include/font.hpp
        ../include/basic_renderer.hpp
        ../include/basic_renderer.ipp
        ../include/renderer.hpp
        ../include/renderer.ipp
        ../include/renderer_handle.hpp
        ../include/basic_joystick.hpp
        ../include/basic_joystick.ipp
        ../include/joystick.hpp
        ../include/texture.hpp
        ../include/texture.ipp
        ../include/centurion_exception.hpp
        ../include/centurion_api.hpp
        ../include/centurion.hpp
        ../include/colors.hpp
        ../include/texture_loader.hpp
        ../include/texture_loader.ipp
        ../include/paths.hpp
        ../include/platform.hpp
        ../include/counter.hpp
        ../include/log.hpp
        ../include/blend_mode.hpp
        ../include/message_box.hpp
        ../include/message_box.ipp
        ../include/color.hpp
        ../include/rect.hpp
        ../include/point.hpp
        ../include/key_state.hpp
        ../include/mouse_state.hpp
        ../include/surface.hpp
        ../include/pixel_format.hpp
        ../include/cursor.hpp
        ../include/cpu.hpp
        ../include/ram.hpp
        ../include/battery.hpp
        ../include/screen.hpp
        ../include/scan_code.hpp
        ../include/touch.hpp
        ../include/mouse_button.hpp
        ../include/event_type.hpp
        ../include/event.hpp
        ../include/button_state.hpp
        ../include/game_controller.hpp
        ../include/area.hpp
        ../include/key_modifier.hpp
        ../include/hints.hpp
        ../include/touch.hpp
        ../include/font_cache.hpp
        ../include/font_cache.ipp
        ../include/unicode_string.hpp
        ../include/game_loop.hpp
        ../include/joystick_handle.hpp
        ../include/basic_texture.hpp
        ../include/basic_texture.ipp
        ../include/scale_mode.hpp
        ../include/sharing_texture.hpp
        ../include/sharing_texture.ipp
        ../include/thread.hpp
        ../include/mutex.hpp
        ../include/scoped_lock.hpp
        ../include/try_lock.hpp
        ../include/condition.hpp
        ../include/semaphore.hpp
        ../include/clipboard.hpp

        ../include/detail/centurion_utils.hpp
        ../include/detail/sdl_string.hpp
        ../include/detail/algorithm.hpp
        ../include/detail/static_bimap.hpp

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
        graphics/sharing_texture.cpp

        system/base_path.cpp
        system/pref_path.cpp
        system/platform.cpp
        system/battery.cpp
        system/screen.cpp
        system/clipboard.cpp

        input/key_state.cpp
        input/mouse_state.cpp
        input/joystick.cpp
        input/touch.cpp
        input/key_code.cpp
        input/scan_code.cpp
        input/joystick_handle.cpp

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
        event/text_input_event.cpp

        thread/thread.cpp
        thread/scoped_lock.cpp
        thread/mutex.cpp
        thread/condition.cpp
        thread/try_lock.cpp
        thread/semaphore.cpp)

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
            -Wc++17-compat
            -Wno-attributes)
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

