cmake_minimum_required(VERSION 3.15)

project(Centurion
        VERSION 5.0.0
        HOMEPAGE_URL "https://github.com/albin-johansson/Centurion"
        LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

set(CTN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CTN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CTN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CTN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CTN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CTN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

set(CENTURION_LIB_TARGET CenturionLibrary)
set(CENTURION_TEST_TARGET CenturionTests)

set(CENTURION_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/${CMAKE_SHARED_LIBRARY_PREFIX}Centurion${CMAKE_SHARED_LIBRARY_SUFFIX})
set(CENTURION_IMPORT_LIB ${CMAKE_BINARY_DIR}/src/${CMAKE_IMPORT_LIBRARY_PREFIX}Centurion${CMAKE_IMPORT_LIBRARY_SUFFIX})

unset(SDL2_BUILDING_LIBRARY) # Force linking to SDL2main

option(CEN_TESTS "Build the Centurion test project" ON)
option(CEN_AUDIO "Build audio components" ON)

find_env_var(SDL2DIR SDL2)
find_env_var(SDL2IMAGEDIR SDL2_image)
find_env_var(SDL2MIXERDIR SDL2_mixer)
find_env_var(SDL2TTFDIR SDL2_ttf)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

add_subdirectory(src)
if (CEN_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()