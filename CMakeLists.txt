cmake_minimum_required(VERSION 3.12)
project(Centurion)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CTN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CTN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(CTN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CTN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CTN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CTN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)

set(CENTURION_LIB_TARGET Centurion_lib)
set(CENTURION_TEST_TARGET Centurion_test)

set(CENTURION_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/libCenturion${CMAKE_SHARED_LIBRARY_SUFFIX})
set(CENTURION_LIBRARIES ${CMAKE_BINARY_DIR}/src/libCenturion${CMAKE_IMPORT_LIBRARY_SUFFIX})

if (DEFINED ENV{TRAVIS}) # FIXME tmp fix
    set(CENTURION_LIBRARIES "${CMAKE_BINARY_DIR}/src/libCenturion.so")
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

add_library(gsl-lite INTERFACE)
target_include_directories(gsl-lite INTERFACE ${CTN_LIBRARY_DIR})  # adapt as necessary

message("Found all required SDL libraries!")

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
