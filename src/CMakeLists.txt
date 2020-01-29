cmake_minimum_required(VERSION 3.12)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        ${INCLUDE_DIR}/window.h
        ${INCLUDE_DIR}/window_listener.h
        ${INCLUDE_DIR}/font.h
        ${INCLUDE_DIR}/renderer.h
        ${INCLUDE_DIR}/image.h
        ${INCLUDE_DIR}/sound_effect.h
        ${INCLUDE_DIR}/centurion_exception.h
        ${INCLUDE_DIR}/bool_converter.h
        ${INCLUDE_DIR}/centurion_api.h
        ${INCLUDE_DIR}/centurion.h
        ${INCLUDE_DIR}/colors.h
        ${INCLUDE_DIR}/image_generator.h
        ${INCLUDE_DIR}/paths.h
        ${INCLUDE_DIR}/system.h
        ${INCLUDE_DIR}/timer.h
        ${INCLUDE_DIR}/log.h
        ${INCLUDE_DIR}/blend_mode.h
        ${INCLUDE_DIR}/message_box.h
        ${INCLUDE_DIR}/color.h
        ${INCLUDE_DIR}/rectangle.h
        ${INCLUDE_DIR}/point.h
        ${INCLUDE_DIR}/key_state.h
        ${INCLUDE_DIR}/mouse_state.h
        ${INCLUDE_DIR}/music.h
        ${INCLUDE_DIR}/centurion_utils.h
        ${INCLUDE_DIR}/error.h
        window.cpp
        font.cpp
        renderer.cpp
        image.cpp
        sound_effect.cpp
        centurion_exception.cpp
        centurion.cpp
        colors.cpp
        image_generator.cpp
        paths.cpp
        system.cpp
        log.cpp
        timer.cpp
        message_box.cpp
        color.cpp
        blend_mode.cpp
        rectangle.cpp
        point.cpp
        key_state.cpp
        mouse_state.cpp
        music.cpp
        error.cpp)

add_library(${CENTURION_LIB} SHARED ${SOURCE_FILES})
add_definitions(-DWIN_EXPORT)

if (DEFINED ENV{TRAVIS})
    # The Travis CI virtual machines can't handle the audio stuff
    target_compile_definitions(${CENTURION_LIB} PUBLIC CENTURION_NOAUDIO)
endif ()

# Specifies C++ version and compiler warning flags.
target_compile_options(${CENTURION_LIB} PRIVATE
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
        -Wconversion)
set_target_properties(${CENTURION_LIB} PROPERTIES
        VERSION 3.0.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        OUTPUT_NAME "Centurion")

target_include_directories(${CENTURION_LIB} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_LIB} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_include_directories(${CENTURION_LIB} PUBLIC ${INCLUDE_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${SOURCE_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${LIBRARY_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${LIBRARY_DIR}/gsl)

target_link_libraries(${CENTURION_LIB}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    get_target_property(CTN_OUTPUT_NAME ${CENTURION_LIB} OUTPUT_NAME)

    if (WIN32)
        message("Moving .dll and .dll.a files...")
        copy_file_post_build(
                ${CENTURION_LIB}
                ${CMAKE_CURRENT_BINARY_DIR}/libCenturion.dll
                ${BINARIES_DIR}/libCenturion.dll)
        copy_file_post_build(
                ${CENTURION_LIB}
                ${CMAKE_CURRENT_BINARY_DIR}/libCenturion.dll.a
                ${BINARIES_DIR}/libCenturion.dll.a)
    else() # FIXME for now we assume some sort of Linux distro
        message("Moving .so file...")
        copy_file_post_build(
                ${CENTURION_LIB}
                ${CMAKE_CURRENT_BINARY_DIR}/libCenturion.so
                ${BINARIES_DIR}/libCenturion.so)
#    else ()
#        message("Failed to move generated Centurion library file!")
    endif ()
endif ()

#copy_directory_post_build(
#        ${CENTURION_LIB}
#        ${BINARIES_DIR}
#        ${CMAKE_CURRENT_BINARY_DIR})