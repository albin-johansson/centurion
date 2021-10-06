cmake_minimum_required(VERSION 3.15)

project(centurion-examples CXX)

# Define macro for the examples with the path to the resources to avoid copying the resources
add_compile_definitions(RESOURCE_DIR="${CEN_RESOURCES_DIR}/")

add_subdirectory(basic-rendering)
add_subdirectory(dynamic-configuration)
add_subdirectory(event-dispatcher)
add_subdirectory(minimal-program)
add_subdirectory(music)
add_subdirectory(responsive-window)
