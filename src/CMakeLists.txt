cmake_minimum_required(VERSION 3.12)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        window.h
        window.cpp
        window_listener.h
        font.h
        font.cpp
        renderer.h
        renderer.cpp
        image.h
        image.cpp
        sound_effect.h
        sound_effect.cpp
        centurion_exception.h
        centurion_exception.cpp
        bool_converter.h
        centurion_api.h
        centurion.cpp
        centurion.h
        colors.h
        image_generator.cpp
        image_generator.h
        paths.cpp
        paths.h
        system.h
        system.cpp
        log.cpp
        log.h
        timer.cpp
        timer.h
        blend_mode.h)

add_library(${CENTURION_LIB} SHARED ${SOURCE_FILES})
add_definitions(-DWIN_EXPORT)

# Specifies C++ version and compiler warning flags.
target_compile_options(${CENTURION_LIB} PRIVATE -Wall -Wextra -Wpedantic)
set_target_properties(${CENTURION_LIB} PROPERTIES
        VERSION 3.0.0
        CXX_STANDARD 17
        OUTPUT_NAME "Centurion")

target_include_directories(${CENTURION_LIB} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_LIB} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_LIB} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_include_directories(${CENTURION_LIB} PUBLIC ../src)
target_include_directories(${CENTURION_LIB} PUBLIC lib)
target_include_directories(${CENTURION_LIB} PUBLIC lib/gsl)

target_link_directories(${CENTURION_LIB}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

target_link_libraries(${CENTURION_LIB}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${CENTURION_LIB} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/src)
