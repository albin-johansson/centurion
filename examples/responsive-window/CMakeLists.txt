cmake_minimum_required(VERSION 3.15)

project(centurion-examples-responsive-window CXX)

add_executable(example_responsive_window responsive_window.cpp)

target_link_libraries(example_responsive_window PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_responsive_window ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()