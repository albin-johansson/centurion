cmake_minimum_required(VERSION 3.15)

option(CEN_USE_SYSTEM_SDL "Use the system-wide SDL installation" OFF)
option(CEN_USE_SDL_IMAGE "Build with SDL_image support" OFF)
option(CEN_USE_SDL_MIXER "Build with SDL_mixer support" OFF)
option(CEN_USE_SDL_TTF "Build with SDL_ttf support" OFF)
option(CEN_BUILD_UNIT_TESTS "Build the unit test suite" OFF)
option(CEN_BUILD_DEMO_TESTS "Build the demo test suite" OFF)
option(CEN_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

message(DEBUG "CEN_USE_SYSTEM_SDL: ${CEN_USE_SYSTEM_SDL}")
message(DEBUG "CEN_USE_SDL_IMAGE: ${CEN_USE_SDL_IMAGE}")
message(DEBUG "CEN_USE_SDL_MIXER: ${CEN_USE_SDL_MIXER}")
message(DEBUG "CEN_USE_SDL_TTF: ${CEN_USE_SDL_TTF}")
message(DEBUG "CEN_BUILD_UNIT_TESTS: ${CEN_BUILD_UNIT_TESTS}")
message(DEBUG "CEN_BUILD_DEMO_TESTS: ${CEN_BUILD_DEMO_TESTS}")
message(DEBUG "CEN_WARNINGS_AS_ERRORS: ${CEN_WARNINGS_AS_ERRORS}")

if (CEN_BUILD_UNIT_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "test")
endif ()

message(DEBUG "VCPKG_MANIFEST_FEATURES: ${VCPKG_MANIFEST_FEATURES}")

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION "8.0.0"
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES "CXX"
        )

if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CEN_SUBPROJECT OFF)
else ()
  set(CEN_SUBPROJECT ON)
endif ()

message(DEBUG "CEN_SUBPROJECT: ${CEN_SUBPROJECT}")

# Default to C++20 unless we're being included as a part of another project.
if (NOT CEN_SUBPROJECT AND NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif ()

message(DEBUG "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

if (CMAKE_CXX_STANDARD LESS 20)
  message(FATAL_ERROR "This version of Centurion requires at least C++20")
endif ()

if (NOT CEN_SUBPROJECT)
  set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY OFF)
endif ()

message(DEBUG "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY}")

set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")
set(CEN_ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets")

message(DEBUG "CEN_ROOT_DIR: ${CEN_ROOT_DIR}")
message(DEBUG "CEN_EXTERNAL_DIR: ${CEN_EXTERNAL_DIR}")
message(DEBUG "CEN_ASSETS_DIR: ${CEN_ASSETS_DIR}")

include("${PROJECT_SOURCE_DIR}/cmake/centurion.cmake")

if (CEN_USE_SYSTEM_SDL)
  message(FATAL_ERROR "System-wide SDL3 installation is currently not supported")
else ()
  set(SDL_DISABLE_INSTALL ON)
  set(SDL_DISABLE_UNINSTALL ON)

  add_subdirectory("${PROJECT_SOURCE_DIR}/external/SDL")

  if (CEN_USE_SDL_IMAGE)
    add_subdirectory("${PROJECT_SOURCE_DIR}/external/SDL_image")
  endif ()

  if (CEN_USE_SDL_MIXER)
    add_subdirectory("${PROJECT_SOURCE_DIR}/external/SDL_mixer")
  endif ()

  if (CEN_USE_SDL_TTF)
    add_subdirectory("${PROJECT_SOURCE_DIR}/external/SDL_ttf")
  endif ()
endif ()

add_subdirectory(lib)
add_subdirectory(test)
