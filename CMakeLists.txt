cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 6.0.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/centurion)
set(CEN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})

message("Centurion version: ${CENTURION_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

set(CENTURION_LIB_TARGET CenturionLibrary)
set(CENTURION_TEST_TARGET CenturionTests)
set(CENTURION_MOCK_TARGET CenturionMocks)

unset(SDL2_BUILDING_LIBRARY) # Force linking to SDL2main

option(CEN_AUDIO "Include audio components" ON)
option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" ON)
option(CENTURION_MOCK_FRIENDLY_MODE "Enable more mocked tests" ON)

if (WIN32)
  find_env_var(SDL2DIR SDL2)
  find_env_var(SDL2IMAGEDIR SDL2_image)
  find_env_var(SDL2MIXERDIR SDL2_mixer)
  find_env_var(SDL2TTFDIR SDL2_ttf)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (CEN_COVERAGE MATCHES ON)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)

if (CEN_TESTS)
  enable_testing()
  add_subdirectory(test)
endif ()