cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-video-renderer LANGUAGES CXX)

cen_create_executable(InteractiveRenderer "interactive_renderer.cpp")
cen_set_compiler_options(InteractiveRenderer)

cen_include_centurion_headers(InteractiveRenderer)
cen_link_against_sdl(InteractiveRenderer)

copy_directory_post_build(InteractiveRenderer
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveRenderer)
endif ()
