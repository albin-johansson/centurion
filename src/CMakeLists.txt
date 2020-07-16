cmake_minimum_required(VERSION 3.15)
project(CenturionSrcProj)

set(SOURCE_FILES
        ${CTN_INCLUDE_DIR}/centurion_cfg.hpp
        ${CTN_INCLUDE_DIR}/centurion_fwd.hpp
        ${CTN_INCLUDE_DIR}/centurion_types.hpp
        ${CTN_INCLUDE_DIR}/window.hpp
        ${CTN_INCLUDE_DIR}/font.hpp
        ${CTN_INCLUDE_DIR}/graphics.hpp
        ${CTN_INCLUDE_DIR}/centurion_exception.hpp
        ${CTN_INCLUDE_DIR}/centurion_api.hpp
        ${CTN_INCLUDE_DIR}/centurion.hpp
        ${CTN_INCLUDE_DIR}/colors.hpp
        ${CTN_INCLUDE_DIR}/texture_loader.hpp
        ${CTN_INCLUDE_DIR}/paths.hpp
        ${CTN_INCLUDE_DIR}/platform.hpp
        ${CTN_INCLUDE_DIR}/counter.hpp
        ${CTN_INCLUDE_DIR}/log.hpp
        ${CTN_INCLUDE_DIR}/blend_mode.hpp
        ${CTN_INCLUDE_DIR}/message_box.hpp
        ${CTN_INCLUDE_DIR}/color.hpp
        ${CTN_INCLUDE_DIR}/rect.hpp
        ${CTN_INCLUDE_DIR}/point.hpp
        ${CTN_INCLUDE_DIR}/key_state.hpp
        ${CTN_INCLUDE_DIR}/mouse_state.hpp
        ${CTN_INCLUDE_DIR}/centurion_utils.hpp
        ${CTN_INCLUDE_DIR}/error.hpp
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
        ${CTN_INCLUDE_DIR}/joystick.hpp
        ${CTN_INCLUDE_DIR}/touch.hpp
        ${CTN_INCLUDE_DIR}/experimental/font.hpp
        window.cpp
        window_base.cpp
        font.cpp
        texture.cpp
        centurion.cpp
        texture_loader.cpp
        paths.cpp
        platform.cpp
        log.cpp
        message_box.cpp
        key_state.cpp
        mouse_state.cpp
        error.cpp
        surface.cpp
        cursor.cpp
        battery.cpp
        screen.cpp
        event.cpp
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
        joystick.cpp
        touch.cpp)

if (NOT DEFINED ENV{TRAVIS})
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${CTN_INCLUDE_DIR}/sound_effect.hpp
            ${CTN_INCLUDE_DIR}/music.hpp
            sound_effect.cpp
            music.cpp)
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

set(NAMED_TYPE_SOURCES
        ${CTN_LIBRARY_DIR}/namedtype/named_type.hpp
        ${CTN_LIBRARY_DIR}/namedtype/named_type_impl.hpp
        ${CTN_LIBRARY_DIR}/namedtype/crtp.hpp
        ${CTN_LIBRARY_DIR}/namedtype/underlying_functionalities.hpp)
centurion_add_header_only_lib(libNamedType ${CTN_LIBRARY_DIR}/namedtype ${NAMED_TYPE_SOURCES})

target_include_directories(${CENTURION_LIB_TARGET}
        PRIVATE ${CTN_INCLUDE_DIR}
        PRIVATE ${CTN_SOURCE_DIR}
        SYSTEM INTERFACE ${CTN_INCLUDE_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC libGSL
        PUBLIC libNamedType)

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
            /W3)
endif ()

