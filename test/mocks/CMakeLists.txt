cmake_minimum_required(VERSION 3.15)

project(centurion-test-mocks LANGUAGES CXX)

set(TEST_FILES
    test_main.cpp
    controller_test.cpp
    )

add_executable(${CENTURION_MOCK_TARGET} ${TEST_FILES})

add_header_only_lib(libFFF ../lib/fff ../lib/fff/fff.h)
cen_set_compiler_options(${CENTURION_MOCK_TARGET})

target_include_directories(${CENTURION_MOCK_TARGET}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${CEN_INCLUDE_DIR}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR})

target_link_libraries(${CENTURION_MOCK_TARGET}
    PUBLIC gtest
    PUBLIC libFFF)

add_test(NAME ${CENTURION_MOCK_TARGET} COMMAND ${CENTURION_MOCK_TARGET})