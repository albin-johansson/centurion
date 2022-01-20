cmake_minimum_required(VERSION 3.15)

project(centurion-examples CXX)

# Define macro for the examples with the path to the resources to avoid copying the resources
add_compile_definitions(RESOURCE_DIR="${CEN_RESOURCES_DIR}/")

function(cen_add_example target)
  target_include_directories(${target}
                             PRIVATE
                             ${CEN_SOURCE_DIR}

                             SYSTEM PUBLIC
                             ${SDL2_INCLUDE_DIR}
                             ${SDL2_IMAGE_INCLUDE_DIRS}
                             ${SDL2_TTF_INCLUDE_DIRS}
                             ${SDL2_MIXER_INCLUDE_DIRS}
                             )

  target_link_libraries(${target} PRIVATE
                        ${SDL2_LIBRARY}
                        ${SDL2_IMAGE_LIBRARIES}
                        ${SDL2_TTF_LIBRARIES}
                        ${SDL2_MIXER_LIBRARIES}
                        )

  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target} PRIVATE
                           /EHsc
                           /MP
                           /W4
                           /Zc:preprocessor # Enable conforming preprocessor
                           /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                           )

  elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|AppleClang")
    target_compile_options(${target} PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           )
  endif ()

  if (WIN32)
    copy_directory_post_build(${target} ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
  endif ()
endfunction()

add_subdirectory(basic-rendering)
add_subdirectory(dynamic-configuration)
add_subdirectory(event-dispatcher)
add_subdirectory(message-box)
add_subdirectory(minimal-program)
add_subdirectory(music)
add_subdirectory(responsive-window)
