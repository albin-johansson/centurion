cmake_minimum_required(VERSION 3.12)
project(${CENTURION_TEST})

#find_package(catch2 REQUIRED)

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_FILES
        unittests/test_main.cpp
        unittests/window_test.cpp
        unittests/bool_converter_test.cpp
        unittests/font_test.cpp
        unittests/image_test.cpp
        unittests/sound_effect_test.cpp
        unittests/image_generator_test.cpp
        unittests/renderer_test.cpp)

add_executable(${CENTURION_TEST} ${TEST_FILES})

include(CTest)
include(Catch)

add_test(NAME ${CENTURION_TEST} COMMAND ${CENTURION_TEST})

set_target_properties(${CENTURION_TEST} PROPERTIES
        CXX_STANDARD 17)

target_include_directories(${CENTURION_TEST} PUBLIC unittests)

if (WIN32)
    target_link_libraries(${CENTURION_TEST}
            mingw32
            Catch
            ${CENTURION_LIB}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
else ()
    target_link_libraries(${CENTURION_TEST}
            Catch
            ${CENTURION_LIB}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
endif ()

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${CENTURION_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/test)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${CENTURION_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/test/resources)
