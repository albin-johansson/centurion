cmake_minimum_required(VERSION 3.15)

project(centurion-test-mocks LANGUAGES CXX)

set(SOURCE_FILES
    test_main.cpp
    core_mocks.hpp
    core_mocks.cpp
    thread_mocks.hpp
    thread_mocks.cpp

    config/hints_test.cpp

    core/centurion_test.cpp

    event/event_test.cpp

    graphics/message_box_test.cpp
    graphics/renderer_test.cpp
    graphics/surface_test.cpp
    graphics/window_test.cpp
    graphics/window_utils_test.cpp

    input/controller_test.cpp
    input/haptic_test.cpp
    input/joystick_test.cpp
    input/key_state_test.cpp
    input/sensor_test.cpp
    input/touch_test.cpp

    system/base_path_test.cpp
    system/battery_test.cpp
    system/platform_test.cpp
    system/pref_path_test.cpp
    system/shared_object_test.cpp

    thread/condition_test.cpp
    thread/mutex_test.cpp
    thread/scoped_lock_test.cpp
    thread/semaphore_test.cpp)

if (CENTURION_MOCK_FRIENDLY_MODE MATCHES ON)
  set(SOURCE_FILES
      ${SOURCE_FILES}

      audio/music_test.cpp
      audio/sound_effect_test.cpp)
endif ()

add_executable(${CENTURION_MOCK_TARGET} ${SOURCE_FILES})

if (CENTURION_MOCK_FRIENDLY_MODE MATCHES ON)
  target_compile_definitions(${CENTURION_MOCK_TARGET}
      PUBLIC CENTURION_MOCK_FRIENDLY_MODE)
endif ()

add_header_only_lib(libFFF ../lib/fff ../lib/fff/fff.h)
cen_set_compiler_options(${CENTURION_MOCK_TARGET})

target_include_directories(${CENTURION_MOCK_TARGET}
    PUBLIC .
    PUBLIC ${CEN_SOURCE_DIR}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR})

target_link_libraries(${CENTURION_MOCK_TARGET}
    PUBLIC gtest
    PUBLIC libFFF)

add_test(NAME ${CENTURION_MOCK_TARGET} COMMAND ${CENTURION_MOCK_TARGET})