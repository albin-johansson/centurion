cmake_minimum_required(VERSION 3.15)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 7.3.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

if (${CMAKE_CXX_STANDARD} STREQUAL "")
  set(CMAKE_CXX_STANDARD 17)
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})
message("[centurion]: version ${CENTURION_VERSION}")

message("[centurion]: CMAKE_CXX_STANDARD is '${CMAKE_CXX_STANDARD}'")
message("[centurion]: CMAKE_CXX_COMPILER is '${CMAKE_CXX_COMPILER}'")
message("[centurion]: CMAKE_CXX_COMPILER_ID is '${CMAKE_CXX_COMPILER_ID}'")

include(cmake/centurion.cmake)

# Directories
set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test/resources")
set(CEN_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CEN_BINARIES_DIR "${PROJECT_SOURCE_DIR}/bin")
set(CEN_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")

# Target names
set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET testcenturion)
set(CENTURION_MOCK_TARGET mockcenturion)

# Build options
option(BUILD_TESTS "Build the test suite" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(INCLUDE_AUDIO_TESTS "Test audio components" ON)

# System dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (BUILD_TESTS)
  # Vcpkg test dependencies
  find_package(GTest CONFIG REQUIRED)
  find_package(cereal CONFIG REQUIRED)
  find_package(GLEW REQUIRED)

  add_subdirectory(test)
endif ()

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif ()