cmake_minimum_required(VERSION 3.15)

project(centurion-examples-basic-rendering CXX)

cen_create_executable(example_basic_rendering basic_rendering.cpp)
cen_set_compiler_options(example_basic_rendering)

cen_include_centurion_headers(example_basic_rendering)
cen_link_against_sdl(example_basic_rendering)

if (WIN32)
  cen_copy_runtime_binaries(example_basic_rendering)
endif ()