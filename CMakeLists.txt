cmake_minimum_required(VERSION 3.15)
project(Centurion)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CTN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CTN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CTN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CTN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CTN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Clang
    set(CTN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin-vs)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    set(CTN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin-mingw)
endif ()

set(CENTURION_LIB_TARGET Centurion_lib)
set(CENTURION_TEST_TARGET Centurion_test)

set(CENTURION_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/libcenturion${CMAKE_SHARED_LIBRARY_SUFFIX})
set(CENTURION_LIBRARIES ${CMAKE_BINARY_DIR}/src/libcenturion${CMAKE_IMPORT_LIBRARY_SUFFIX})

if (DEFINED ENV{TRAVIS} OR ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CENTURION_LIBRARIES "${CMAKE_BINARY_DIR}/src/libCenturion.so")
endif ()

# Checks if an environment variable is defined.
#   envVar: the name of the actual environment variable.
#   name: the name of the library associated with the environment variable.
function(find_env_var [envVar [name]])
    if (DEFINED ENV{${ARGV0}})
        message("Found environment variable: ${ARGV1}=" $ENV{${ARGV0}})
    else ()
        message(WARNING "Couldn't find environment variable ${ARGV0}!")
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

# Creates an interface library target for a header-only library.
#   name: the name of the library target.
#   includeDirectory: the path of the directory that contains the headers of the library.
#   sources: the headers associated with the library.
function(centurion_add_header_only_lib [name [includeDirectory [sources]]])
    add_library(${ARGV0} INTERFACE)
    target_sources(${ARGV0} INTERFACE ${ARGV2})
    target_include_directories(${ARGV0} SYSTEM INTERFACE ${ARGV1})
endfunction()

unset(SDL2_BUILDING_LIBRARY) # Force linking to SDL2main

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

include_directories(
        SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
        SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
        SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

enable_testing()
add_subdirectory(src)
if (NOT DEFINED ENV{NO_TEST_SUBDIRECTORY})
    add_subdirectory(test)
endif ()