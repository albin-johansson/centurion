cmake_minimum_required(VERSION 3.15)

project(centurion-examples-responsive-window CXX)

cen_create_executable(example_responsive_window responsive_window.cpp)
cen_set_compiler_options(example_responsive_window)

cen_include_centurion_headers(example_responsive_window)
cen_link_against_sdl(example_responsive_window)

if (WIN32)
  cen_copy_runtime_binaries(example_responsive_window)
endif ()