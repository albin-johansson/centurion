cmake_minimum_required(VERSION 3.15)

project(centurion-test-mocked-tests CXX)

set(SOURCE_FILES
    core_mocks.hpp
    core_mocks.cpp
    mixer_mocks.cpp
    mixer_mocks.hpp
    test_main.cpp
    thread_mocks.hpp
    thread_mocks.cpp

    audio/music_test.cpp
    audio/sound_effect_test.cpp

    common/initialization_test.cpp

    concurrency/condition_test.cpp
    concurrency/mutex_test.cpp
    concurrency/scoped_lock_test.cpp
    concurrency/semaphore_test.cpp

    event/event_handler_test.cpp

    filesystem/base_path_test.cpp
    filesystem/file_test.cpp
    filesystem/preferred_path_test.cpp

    input/controller_test.cpp
    input/joystick_test.cpp
    input/keyboard_test.cpp
    input/sensor_test.cpp
    input/touch_test.cpp

    message-box/message_box_test.cpp

    system/open_url_test.cpp
    system/platform_test.cpp
    system/power_test.cpp
    system/shared_object_test.cpp

    video/blend_mode_test.cpp
    video/surface_test.cpp
    video/window_test.cpp
    video/window_utils_test.cpp

    video/opengl/gl_context_test.cpp
    video/opengl/gl_core_test.cpp
    video/opengl/gl_library_test.cpp

    video/render/renderer_info_test.cpp
    video/render/renderer_test.cpp

    video/vulkan/vk_core_test.cpp
    video/vulkan/vk_library_test.cpp
    )

add_executable(${CENTURION_MOCK_TARGET} ${SOURCE_FILES})

target_compile_definitions(${CENTURION_MOCK_TARGET} PRIVATE CENTURION_MOCK_FRIENDLY_MODE)

set(CEN_FFF_DIR "${CEN_EXTERNAL_DIR}/fff")

cen_add_header_only_lib(libFFF ${CEN_FFF_DIR} ${CEN_FFF_DIR}/fff.h)

target_include_directories(${CENTURION_MOCK_TARGET}
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}
                           )

target_link_libraries(${CENTURION_MOCK_TARGET}
                      PRIVATE
                      centurion::centurion
                      GTest::gtest
                      libFFF)

cen_set_basic_compiler_options(${CENTURION_MOCK_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_MOCK_TARGET}
                         PRIVATE
                         /wd4834 # Disable [[nodiscard]] warnings
                         /wd4702 # Disable "unreachable code" warnings
                         )

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|AppleClang")
  target_compile_options(${CENTURION_MOCK_TARGET}
                         PRIVATE
                         -Wno-unused-result
                         )
endif ()

add_test(NAME ${CENTURION_MOCK_TARGET} COMMAND ${CENTURION_MOCK_TARGET})