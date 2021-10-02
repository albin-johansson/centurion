cmake_minimum_required(VERSION 3.15)

project(centurion-examples-music CXX)

cen_create_executable(example_music music.cpp)
cen_set_compiler_options(example_music)

cen_include_centurion_headers(example_music)
cen_link_against_sdl(example_music)

if (WIN32)
  cen_copy_runtime_binaries(example_music)
endif ()