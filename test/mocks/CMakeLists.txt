cmake_minimum_required(VERSION 3.15)

project(centurion-test-mocks CXX)

set(SOURCE_FILES
    core_mocks.hpp
    core_mocks.cpp
    mixer_mocks.cpp
    mixer_mocks.hpp
    test_main.cpp
    thread_mocks.hpp
    thread_mocks.cpp

    audio/channels_test.cpp
    audio/sound_fonts_test.cpp

    core/library_test.cpp

    event/event_test.cpp

    filesystem/base_path_test.cpp
    filesystem/file_test.cpp
    filesystem/preferred_path_test.cpp

    input/controller_test.cpp
    input/haptic_test.cpp
    input/joystick_test.cpp
    input/keyboard_test.cpp
    input/sensor_test.cpp
    input/touch_test.cpp

    system/battery_test.cpp
    system/open_url_test.cpp
    system/platform_test.cpp
    system/shared_object_test.cpp

    thread/condition_test.cpp
    thread/mutex_test.cpp
    thread/scoped_lock_test.cpp
    thread/semaphore_test.cpp

    video/gl/gl_context_test.cpp
    video/gl/gl_core_test.cpp
    video/gl/gl_library_test.cpp

    video/vulkan/vk_core_test.cpp
    video/vulkan/vk_library_test.cpp

    video/blend_mode_test.cpp
    video/message_box_test.cpp
    video/renderer_info_test.cpp
    video/renderer_test.cpp
    video/surface_test.cpp
    video/window_test.cpp
    video/window_utils_test.cpp
    )

if (CENTURION_MOCK_FRIENDLY_MODE)
  list(APPEND SOURCE_FILES
       audio/music_test.cpp
       audio/sound_effect_test.cpp
       )
endif ()

add_executable(${CENTURION_MOCK_TARGET} ${SOURCE_FILES})
add_dependencies(${CENTURION_MOCK_TARGET} ${CENTURION_LIB_TARGET})

if (CENTURION_MOCK_FRIENDLY_MODE)
  target_compile_definitions(${CENTURION_MOCK_TARGET} PRIVATE CENTURION_MOCK_FRIENDLY_MODE)
endif ()

add_header_only_lib(libFFF ${CEN_LIBRARY_DIR}/fff ${CEN_LIBRARY_DIR}/fff/fff.h)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_MOCK_TARGET} PRIVATE
                         /EHsc
                         /MP
                         /W4
                         /Zc:preprocessor # Enable conforming preprocessor
                         /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                         /wd4834  # "discarding return value of function with 'nodiscard' attribute"
                         /wd4702  # "unreachable code"
                         )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_MOCK_TARGET} PRIVATE
                         -Wall
                         -Wextra
                         -Wpedantic
                         -Wconversion
                         )

else ()
  message("[centurion::mocks]: could not determine compiler options")
endif ()

target_include_directories(${CENTURION_MOCK_TARGET}
                           PRIVATE
                           ${CEN_SOURCE_DIR}  # TODO remove and fix includes
                           ${PROJECT_SOURCE_DIR}

                           SYSTEM PRIVATE
                           ${SDL2_INCLUDE_DIR}
                           ${SDL2_IMAGE_INCLUDE_DIRS}
                           ${SDL2_TTF_INCLUDE_DIRS}
                           ${SDL2_MIXER_INCLUDE_DIRS}
                           ${gtest_SOURCE_DIR}/include
                           ${gtest_SOURCE_DIR}
                           ${gmock_SOURCE_DIR}/include
                           ${gmock_SOURCE_DIR}
                           )

target_link_libraries(${CENTURION_MOCK_TARGET} PRIVATE
                      gtest
                      libFFF
                      )

add_test(NAME ${CENTURION_MOCK_TARGET} COMMAND ${CENTURION_MOCK_TARGET})