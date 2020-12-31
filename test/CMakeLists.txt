cmake_minimum_required(VERSION 3.15)

project(CenturionTest
    LANGUAGES CXX)

include(DownloadProject)

download_project(PROJ googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    "UPDATE_DISCONNECTED 1")

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

set(TEST_FILES
    unittests/test_main.cpp

    unittests/detail/bool_converter_test.cpp
    unittests/detail/to_string_test.cpp

    unittests/system/clipboard_test.cpp

    unittests/geometry/area_test.cpp
    unittests/geometry/rect_test.cpp
    unittests/geometry/point_test.cpp

    unittests/graphics/blend_mode_test.cpp
    unittests/graphics/color_test.cpp
    unittests/graphics/cursor_test.cpp
    unittests/graphics/font_test.cpp
    unittests/graphics/font_cache_test.cpp
    unittests/graphics/surface_test.cpp
    unittests/graphics/surface_handle_test.cpp
    unittests/graphics/texture_test.cpp
    unittests/graphics/texture_handle_test.cpp
    unittests/graphics/texture_access_test.cpp
    unittests/graphics/scale_mode_test.cpp

    unittests/thread/condition_test.cpp
    unittests/thread/mutex_test.cpp
    unittests/thread/scoped_lock_test.cpp
    unittests/thread/semaphore_test.cpp
    unittests/thread/thread_test.cpp

    unittests/event/audio_device_event_test.cpp
    unittests/event/common_event_test.cpp
    )

#if (CEN_AUDIO)
#    set(TEST_FILES
#            ${TEST_FILES}
#            unittests/sound_effect_test.cpp
#            unittests/music_test.cpp)
#endif ()

if (WIN32)
  add_executable(${CENTURION_TEST_TARGET} WIN32 ${TEST_FILES})
else ()
  add_executable(${CENTURION_TEST_TARGET} ${TEST_FILES})
endif ()

if (CEN_AUDIO)
  target_compile_definitions(${CENTURION_TEST_TARGET}
      PUBLIC CEN_AUDIO)
endif ()

add_header_only_lib(libFFF lib/fff lib/fff/fff.h)
include(CTest)

target_include_directories(${CENTURION_TEST_TARGET}
    PUBLIC unittests
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${CEN_INCLUDE_DIR}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
      -Wno-unused-result)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
      /EHsc)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_TEST_TARGET} PRIVATE
      /EHsc
      /MP
      /W3)
endif ()

message("Linking against...")
message("  * SDL2       @ ${SDL2_LIBRARY}")
message("  * SDL2_image @ ${SDL2_IMAGE_LIBRARIES}")
message("  * SDL2_mixer @ ${SDL2_MIXER_LIBRARIES}")
message("  * SDL2_ttf   @ ${SDL2_TTF_LIBRARIES}")

target_link_libraries(${CENTURION_TEST_TARGET}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${CENTURION_IMPORT_LIB}
    PUBLIC gtest
    PUBLIC gmock
    PUBLIC libFFF)

add_test(NAME ${CENTURION_TEST_TARGET} COMMAND ${CENTURION_TEST_TARGET})

copy_directory_post_build(
    ${CENTURION_TEST_TARGET}
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  copy_file_post_build(
      ${CENTURION_TEST_TARGET}
      ${CENTURION_DYNAMIC_LIB}
      ${CMAKE_CURRENT_BINARY_DIR})

  copy_directory_post_build(
      ${CENTURION_TEST_TARGET}
      ${CEN_BINARIES_DIR}
      ${CMAKE_CURRENT_BINARY_DIR})
endif ()
