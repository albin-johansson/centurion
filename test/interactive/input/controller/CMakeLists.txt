cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-input-controller LANGUAGES CXX)

cen_create_executable(InteractiveController "interactive_controller.cpp")
cen_set_compiler_options(InteractiveController)

cen_include_centurion_headers(InteractiveController)
cen_link_against_sdl(InteractiveController)

copy_directory_post_build(InteractiveController
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveController)
endif ()
