cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-system-battery LANGUAGES CXX)

cen_create_executable(InteractiveBattery "interactive_battery.cpp")
cen_set_compiler_options(InteractiveBattery)

cen_include_centurion_headers(InteractiveBattery)
cen_link_against_sdl(InteractiveBattery)

copy_directory_post_build(InteractiveBattery
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveBattery)
endif ()
