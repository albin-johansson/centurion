cmake_minimum_required(VERSION 3.21)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  cmake_path(SET VCPKG_ROOT NORMALIZE $ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 8.0.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

option(CEN_USE_SYSTEM_SDL "Use the system SDL libraries" ON)
option(CEN_BUILD_UNIT_TESTS "Build the unit test suite" OFF)
option(CEN_BUILD_MOCK_TESTS "Build the mock test suite" OFF)

message(DEBUG "CEN_USE_SYSTEM_SDL: ${CEN_USE_SYSTEM_SDL}")
message(DEBUG "CEN_BUILD_UNIT_TESTS: ${CEN_BUILD_UNIT_TESTS}")
message(DEBUG "CEN_BUILD_MOCK_TESTS: ${CEN_BUILD_MOCK_TESTS}")

set(CENTURION_ROOT_DIR "${PROJECT_SOURCE_DIR}")

message(DEBUG "CENTURION_ROOT_DIR: ${CENTURION_ROOT_DIR}")

if (CEN_USE_SYSTEM_SDL MATCHES "ON")
  find_package(SDL3 REQUIRED)
else ()
  find_package(SDL3 REQUIRED PATHS "${CENTURION_ROOT_DIR}/external/SDL/build")
endif ()

function(cen_apply_compiler_options target)
  set_target_properties(${target}
                        PROPERTIES
                        CXX_STANDARD_REQUIRED ON
                        CXX_STANDARD_EXTENSIONS OFF
                        )

  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${target}
                           PRIVATE
                           /EHsc
                           /MP
                           /W4
                           /permissive-
                           /Zc:preprocessor
                           /Zc:__cplusplus
                           )
  else ()
    target_compile_options(${target}
                           PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           -Wsign-conversion
                           )
  endif ()
endfunction()

add_subdirectory("lib")

if (CEN_BUILD_UNIT_TESTS MATCHES "ON")
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory("test/unit")
endif ()

if (CEN_BUILD_MOCK_TESTS MATCHES "ON")
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory("test/mock")
endif ()
