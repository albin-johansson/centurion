cmake_minimum_required(VERSION 3.15)

project(CenturionTest)

include(DownloadProject)

download_project(PROJ googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    "UPDATE_DISCONNECTED 1")

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

set(TEST_FILES
    unittests/test_main.cpp
    unittests/to_string_test.cpp)

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
    PUBLIC gmock)

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
