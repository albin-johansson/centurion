cmake_minimum_required(VERSION 3.12)
project(${CENTURION_TEST})

if (DEFINED ENV{TRAVIS})
    set(TEST_FILES
            unittests/test_main.cpp
            unittests/window_test.cpp
            unittests/bool_converter_test.cpp
            unittests/font_test.cpp
            unittests/image_test.cpp
            unittests/image_generator_test.cpp
            unittests/renderer_test.cpp
            unittests/log_test.cpp
            unittests/power_test.cpp
            unittests/blend_mode_test.cpp
            unittests/message_box_test.cpp
            unittests/color_test.cpp
            unittests/point_test.cpp
            unittests/key_state_test.cpp
            unittests/mouse_state_test.cpp
            unittests/rectangle_test.cpp
            unittests/centurion_exception_test.cpp
            unittests/error_test.cpp)
else ()
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
            unittests/color_test.cpp
            unittests/point_test.cpp
            unittests/key_state_test.cpp
            unittests/mouse_state_test.cpp
            unittests/music_test.cpp
            unittests/rectangle_test.cpp
            unittests/centurion_exception_test.cpp
            unittests/error_test.cpp)
endif ()

add_executable(${CENTURION_TEST} ${TEST_FILES})
add_dependencies(${CENTURION_TEST} ${CENTURION_LIB})

set_target_properties(${CENTURION_TEST} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing()
add_test(NAME ${CENTURION_TEST} COMMAND ${CENTURION_TEST})

target_include_directories(${CENTURION_TEST} PUBLIC unittests)
target_include_directories(${CENTURION_TEST} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${CENTURION_TEST} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${CENTURION_TEST} PUBLIC ${CTN_INCLUDE_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${CTN_LIBRARY_DIR})
target_include_directories(${CENTURION_TEST} PUBLIC ${CTN_LIBRARY_DIR}/gsl)

message("------ LINKING TEST EXECUTABLE ------")
message("Linking against SDL2: ${SDL2_LIBRARY}")
message("Linking against SDL2_image: ${SDL2_IMAGE_LIBRARIES}")
message("Linking against SDL2_image: ${SDL2_MIXER_LIBRARIES}")
message("Linking against SDL2_image: ${SDL2_TTF_LIBRARIES}")
message("Linking against Centurion: ${CENTURION_LIBRARIES}")

include(CTest)
include(Catch)
include(ParseAndAddCatchTests)

target_link_libraries(${CENTURION_TEST}
        PUBLIC Catch2
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${CENTURION_LIBRARIES})

catch_discover_tests(${CENTURION_TEST})

copy_directory_post_build(
        ${CENTURION_TEST}
        ${CTN_RESOURCES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resources)

#copy_directory_post_build(
#        ${CENTURION_TEST}
#        ${CMAKE}
#        ${CMAKE_CURRENT_BINARY_DIR})
