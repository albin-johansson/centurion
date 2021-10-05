cmake_minimum_required(VERSION 3.15)

project(centurion-examples-dynamic-configuration CXX)

add_executable(example_dynamic_configuration dynamic_configuration.cpp)

target_link_libraries(example_dynamic_configuration PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_dynamic_configuration ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()