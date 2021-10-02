cmake_minimum_required(VERSION 3.15)

project(centurion-examples-minimal-program CXX)

cen_create_executable(example_minimal_program minimal_program.cpp)
cen_set_compiler_options(example_minimal_program)

cen_include_centurion_headers(example_minimal_program)
cen_link_against_sdl(example_minimal_program)

if (WIN32)
  cen_copy_runtime_binaries(example_minimal_program)
endif ()