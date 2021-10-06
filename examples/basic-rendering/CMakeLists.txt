cmake_minimum_required(VERSION 3.15)

project(centurion-examples-basic-rendering CXX)

add_executable(example_basic_rendering basic_rendering.cpp)

target_link_libraries(example_basic_rendering PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_basic_rendering ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()