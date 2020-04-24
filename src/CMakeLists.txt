cmake_minimum_required(VERSION 3.12)
project(CenturionSrcProj)

set(SOURCE_FILES
        ${CTN_LIBRARY_DIR}/gsl-lite.hpp
        ${CTN_LIBRARY_DIR}/optional.hpp

        ${CTN_INCLUDE_DIR}/window.h
        ${CTN_INCLUDE_DIR}/window_listener.h
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
        ${CTN_INCLUDE_DIR}/rectangle.h
        ${CTN_INCLUDE_DIR}/point.h
        ${CTN_INCLUDE_DIR}/key_state.h
        ${CTN_INCLUDE_DIR}/mouse_state.h
        ${CTN_INCLUDE_DIR}/centurion_utils.h
        ${CTN_INCLUDE_DIR}/error.h
        ${CTN_INCLUDE_DIR}/event.h
        ${CTN_INCLUDE_DIR}/surface.h
        ${CTN_INCLUDE_DIR}/pixel_format.h
        ${CTN_INCLUDE_DIR}/cursor.h
        ${CTN_INCLUDE_DIR}/cpu.h
        ${CTN_INCLUDE_DIR}/ram.h
        ${CTN_INCLUDE_DIR}/battery.h
        ${CTN_INCLUDE_DIR}/screen.h

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
        event.cpp
        surface.cpp
        cursor.cpp
        pixel_format.cpp
        cpu.cpp
        ram.cpp
        battery.cpp
        screen.cpp)

if (NOT DEFINED ENV{TRAVIS})
    set(SOURCE_FILES
            ${SOURCE_FILES}
            ${CTN_INCLUDE_DIR}/audio.h
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
            -Wc++14-compat
            -Wc++17-compat)
endif ()

set_target_properties(${CENTURION_LIB_TARGET} PROPERTIES
        VERSION 4.0.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "Centurion")

target_include_directories(${CENTURION_LIB_TARGET} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_LIB_TARGET} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB_TARGET} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB_TARGET} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_include_directories(${CENTURION_LIB_TARGET} PUBLIC ${CTN_INCLUDE_DIR})
target_include_directories(${CENTURION_LIB_TARGET} PUBLIC ${CTN_SOURCE_DIR})
target_include_directories(${CENTURION_LIB_TARGET} PUBLIC ${CTN_LIBRARY_DIR})

target_link_libraries(${CENTURION_LIB_TARGET}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})