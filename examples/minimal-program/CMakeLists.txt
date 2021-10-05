cmake_minimum_required(VERSION 3.15)

project(centurion-examples-minimal-program CXX)

add_executable(example_minimal_program minimal_program.cpp)

target_link_libraries(example_minimal_program PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_minimal_program ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()