cmake_minimum_required(VERSION 3.15)

project(centurion-examples-music CXX)

add_executable(example_music music.cpp)

target_link_libraries(example_music PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_music ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()