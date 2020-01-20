cmake_minimum_required(VERSION 3.12)
project(${CENTURION_TEST})

set(TEST_FILES
        unittests/test_main.cpp
        unittests/window_test.cpp
        unittests/bool_converter_test.cpp
        unittests/font_test.cpp
        unittests/image_test.cpp
        unittests/sound_effect_test.cpp
        unittests/image_generator_test.cpp
        unittests/renderer_test.cpp
        unittests/log_test.cpp
        unittests/power_test.cpp
        unittests/blend_mode_test.cpp
        unittests/message_box_test.cpp
        unittests/color_test.cpp)

add_executable(${CENTURION_TEST} ${TEST_FILES})

set_target_properties(${CENTURION_TEST} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing()
add_test(NAME ${CENTURION_TEST} COMMAND ${CENTURION_TEST})

target_include_directories(${CENTURION_TEST} PUBLIC unittests)
target_include_directories(${CENTURION_TEST} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} PUBLIC ${INCLUDE_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${SOURCE_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${LIBRARY_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${LIBRARY_DIR}/gsl)

if (WIN32)
    target_link_libraries(${CENTURION_TEST}
            mingw32
            Catch2
            ${CENTURION_DLL_PATH}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
else ()
    target_link_libraries(${CENTURION_TEST}
            Catch2
            ${CENTURION_DLL_PATH}
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES})
endif ()

include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(${CENTURION_TEST})
#catch_discover_tests(${CENTURION_TEST})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(
        TARGET ${CENTURION_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${BINARIES_DIR}
        ${CMAKE_BINARY_DIR}/test)

# Copies all of the resources and puts the in the build folder
add_custom_command(
        TARGET ${CENTURION_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_DIR}
        ${CMAKE_BINARY_DIR}/test/resources)