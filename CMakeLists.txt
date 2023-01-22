cmake_minimum_required(VERSION 3.15)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 7.3.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})
message("[centurion]: version ${CENTURION_VERSION}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
  message("[centurion]: no explicit C++ version specified")
  set(CMAKE_CXX_STANDARD 17)
endif ()

message("[centurion]: using C++ standard... ${CMAKE_CXX_STANDARD}")
message("[centurion]: compiler is... ${CMAKE_CXX_COMPILER}")
message("[centurion]: compiler identifier is... ${CMAKE_CXX_COMPILER_ID}")

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

include(Utilities)

set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test/resources")
set(CEN_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CEN_BINARIES_DIR "${PROJECT_SOURCE_DIR}/bin")

set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET testcenturion)
set(CENTURION_MOCK_TARGET mockcenturion)

option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" OFF)
option(CEN_EXAMPLES "Build the examples" OFF)

option(CENTURION_MOCK_FRIENDLY_MODE "Enable more mocked tests" ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (CEN_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

if (CEN_TESTS)
  find_package(GTest CONFIG REQUIRED)
  find_package(cereal CONFIG REQUIRED)
  find_package(GLEW REQUIRED)

  add_subdirectory(test)
endif ()

if (CEN_EXAMPLES)
  add_subdirectory(examples)
endif ()