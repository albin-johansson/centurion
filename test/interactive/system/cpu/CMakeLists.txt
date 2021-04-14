cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-system-cpu LANGUAGES CXX)

cen_create_executable(InteractiveCPU "interactive_cpu.cpp")
cen_set_compiler_options(InteractiveCPU)

cen_include_centurion_headers(InteractiveCPU)
cen_link_against_sdl(InteractiveCPU)

copy_directory_post_build(InteractiveCPU
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveCPU)
endif ()
