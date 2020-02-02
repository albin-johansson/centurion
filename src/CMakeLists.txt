cmake_minimum_required(VERSION 3.12)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        ${CTN_INCLUDE_DIR}/window.h
        ${CTN_INCLUDE_DIR}/window_listener.h
        ${CTN_INCLUDE_DIR}/font.h
        ${CTN_INCLUDE_DIR}/renderer.h
        ${CTN_INCLUDE_DIR}/image.h
        ${CTN_INCLUDE_DIR}/sound_effect.h
        ${CTN_INCLUDE_DIR}/centurion_exception.h
        ${CTN_INCLUDE_DIR}/bool_converter.h
        ${CTN_INCLUDE_DIR}/centurion_api.h
        ${CTN_INCLUDE_DIR}/centurion.h
        ${CTN_INCLUDE_DIR}/colors.h
        ${CTN_INCLUDE_DIR}/image_generator.h
        ${CTN_INCLUDE_DIR}/paths.h
        ${CTN_INCLUDE_DIR}/system.h
        ${CTN_INCLUDE_DIR}/timer.h
        ${CTN_INCLUDE_DIR}/log.h
        ${CTN_INCLUDE_DIR}/blend_mode.h
        ${CTN_INCLUDE_DIR}/message_box.h
        ${CTN_INCLUDE_DIR}/color.h
        ${CTN_INCLUDE_DIR}/rectangle.h
        ${CTN_INCLUDE_DIR}/point.h
        ${CTN_INCLUDE_DIR}/key_state.h
        ${CTN_INCLUDE_DIR}/mouse_state.h
        ${CTN_INCLUDE_DIR}/music.h
        ${CTN_INCLUDE_DIR}/centurion_utils.h
        ${CTN_INCLUDE_DIR}/error.h
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

if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif()

if (DEFINED ENV{TRAVIS})
    # The Travis CI virtual machines can't handle the audio stuff
    target_compile_definitions(${CENTURION_LIB} PUBLIC CENTURION_NOAUDIO)
endif ()

if (DEFINED ENV{ENABLE_COVERAGE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")

#    set_target_properties(${CENTURION_LIB} PROPERTIES
#            COMPILE_FLAGS "-ftest-coverage -fprofile-arcs"
#            LINK_FLAGS    "-lgcov --coverage")

    #    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
    find_package(codecov)
    add_coverage(${CENTURION_LIB})
    list(APPEND LCOV_REMOVE_PATTERNS "/usr/") # FIXME only works on Linux
    coverage_evaluate()
else ()
    message("Not generating code coverage!")
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

target_include_directories(${CENTURION_LIB} PUBLIC ${CTN_INCLUDE_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${CTN_SOURCE_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${CTN_LIBRARY_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${CTN_LIBRARY_DIR}/gsl)

target_link_libraries(${CENTURION_LIB}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})