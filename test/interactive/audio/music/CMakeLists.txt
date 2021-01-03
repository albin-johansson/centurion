cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-audio-music LANGUAGES CXX)

cen_create_executable(InteractiveMusic "interactive_music.cpp")
cen_set_compiler_options(InteractiveMusic)

cen_include_centurion_headers(InteractiveMusic)
cen_link_against_centurion(InteractiveMusic)

copy_directory_post_build(InteractiveMusic
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveMusic)
endif ()
