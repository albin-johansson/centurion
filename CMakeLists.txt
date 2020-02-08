cmake_minimum_required(VERSION 3.12)
project(Centurion)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CTN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CTN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(CTN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CTN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CTN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CTN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)

set(CENTURION_LIB ${PROJECT_NAME}_lib)
set(CENTURION_TEST ${PROJECT_NAME}_test)

message("Source directory: ${PROJECT_SOURCE_DIR}")

if (DEFINED ENV{TRAVIS})
    set(CENTURION_LIBRARIES ${CMAKE_BINARY_DIR}/src/libCenturion.so)
else ()
    set(CENTURION_LIBRARIES "${CMAKE_BINARY_DIR}/src/libCenturion.dll.a")
    set(CENTURION_DLL "${CMAKE_BINARY_DIR}/src/libCenturion.dll")
endif ()

# Checks if an environment variable is defined.
#   envVar: the name of the actual environment variable.
#   name: the name of the library associated with the environment variable.
function(find_env_var [envVar [name]])
    if (DEFINED ENV{${ARGV0}})
        message("Found ${ARGV1} environment variable! Path: " $ENV{${ARGV0}})
    else ()
        message("Couldn't find environment variable ${ARGV0}!")
    endif ()
endfunction()

# Copies a file.
#   target: the associated target.
#   from: the file that will be copied.
#   to: the target destination of the copied file.
function(copy_file_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${ARGV1}
            ${ARGV2})
endfunction()

# Copies a directory.
#   target: the associated target.
#   from: the directory that will be copied.
#   to: the target destination of the copied directory.
function(copy_directory_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${ARGV1}
            ${ARGV2})
endfunction()

message("------ LOOKING FOR ENVIRONMENT VARIABLES ------")
find_env_var(SDL2DIR SDL2)
find_env_var(SDL2IMAGEDIR SDL2_image)
find_env_var(SDL2MIXERDIR SDL2_mixer)
find_env_var(SDL2TTFDIR SDL2_ttf)

message("------ LOOKING FOR SDL LIBRARIES ------")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

message("Found all required SDL libraries!")

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif ()

add_subdirectory(src)
add_subdirectory(test)

if (CMAKE_COMPILER_IS_GNUCXX AND DEFINED ENV{TRAVIS} AND DEFINED ENV{ENABLE_COVERAGE})
    setup_target_for_coverage_lcov(
            NAME coverage
            EXECUTABLE "cd test && ctest" # -j ${n_cores} # Executable in PROJECT_BINARY_DIR
            DEPENDENCIES ${CENTURION_TEST})
endif ()
