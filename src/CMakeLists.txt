cmake_minimum_required(VERSION 3.15)

project(CenturionSrc)

set(SOURCE_FILES
        ../include/centurion_cfg.hpp
        ../include/centurion_fwd.hpp
        ../include/types.hpp
        ../include/video.hpp
        ../include/basic_window.hpp
        ../include/window.hpp
        ../include/window_handle.hpp
        ../include/window_utils.hpp
        ../include/font.hpp
        ../include/basic_renderer.hpp
        ../include/renderer.hpp
        ../include/renderer_handle.hpp
        ../include/basic_joystick.hpp
        ../include/joystick.hpp
        ../include/texture.hpp
        ../include/exception.hpp
        ../include/centurion_api.hpp
        ../include/centurion.hpp
        ../include/colors.hpp
        ../include/paths.hpp
        ../include/platform.hpp
        ../include/counter.hpp
        ../include/log.hpp
        ../include/blend_mode.hpp
        ../include/message_box.hpp
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
        ../include/controller.hpp
        ../include/area.hpp
        ../include/key_modifier.hpp
        ../include/hints.hpp
        ../include/touch.hpp
        ../include/font_cache.hpp
        ../include/unicode_string.hpp
        ../include/game_loop.hpp
        ../include/joystick_handle.hpp
        ../include/basic_texture.hpp
        ../include/scale_mode.hpp
        ../include/sharing_texture.hpp
        ../include/thread.hpp
        ../include/mutex.hpp
        ../include/scoped_lock.hpp
        ../include/try_lock.hpp
        ../include/condition.hpp
        ../include/semaphore.hpp
        ../include/clipboard.hpp
        ../include/sdl_string.hpp
        ../include/texture_access.hpp

        ../include/detail/utils.hpp
        ../include/detail/algorithm.hpp
        ../include/detail/static_bimap.hpp
        ../include/detail/to_string.hpp

        core/centurion.cpp
        core/exception.cpp

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
        input/controller.cpp

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

if (CEN_AUDIO)
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${CEN_INCLUDE_DIR}/sound_effect.hpp
            ${CEN_INCLUDE_DIR}/music.hpp
            audio/sound_effect.cpp
            audio/music.cpp)
endif ()

add_library(${CENTURION_LIB_TARGET} SHARED ${SOURCE_FILES})

if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

set_target_properties(${CENTURION_LIB_TARGET} PROPERTIES
        OUTPUT_NAME ${CMAKE_IMPORT_LIBRARY_PREFIX}Centurion
        VERSION ${CENTURION_VERSION})

add_header_only_lib(libEnTT ${CEN_LIBRARY_DIR}/entt ${CEN_LIBRARY_DIR}/entt/entt.hpp)

target_include_directories(${CENTURION_LIB_TARGET}
        SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
        SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
        PRIVATE ${CEN_INCLUDE_DIR}
        PRIVATE ${CEN_SOURCE_DIR}
        SYSTEM INTERFACE ${CEN_INCLUDE_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC libEnTT)

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

