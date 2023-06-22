cmake_minimum_required(VERSION 3.15)

project(centurion-examples CXX)

# Define macro for the examples with the path to the resources to avoid copying the resources
add_compile_definitions(RESOURCE_DIR="${CEN_RESOURCES_DIR}/")

function(cen_add_example target)
  target_link_libraries(${target} PRIVATE centurion::centurion)

  cen_set_basic_compiler_options(${target})

  if (WIN32)
    cen_copy_directory_post_build(${target} ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
  endif ()
endfunction()

add_subdirectory(basic-rendering)
add_subdirectory(dynamic-configuration)
add_subdirectory(event-dispatcher)
add_subdirectory(event-handler)
add_subdirectory(font)
add_subdirectory(message-box)
add_subdirectory(minimal-program)
add_subdirectory(music)
add_subdirectory(responsive-window)
