cmake_minimum_required(VERSION 3.23)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 7.3.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
  set(CMAKE_CXX_STANDARD 17)
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Build options
option(BUILD_TESTS "Build the test suite" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(INCLUDE_AUDIO_TESTS "Test audio components" ON)
option(TREAT_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

include(cmake/centurion.cmake)

# Directories
set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test/resources")
set(CEN_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CEN_BINARIES_DIR "${PROJECT_SOURCE_DIR}/bin")
set(CEN_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")

# Target names
set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET centurion-tests)
set(CENTURION_MOCK_TARGET centurion-mocks)

# System dependencies
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# CMake Targets
add_library(centurion-headers-only INTERFACE)
add_library(centurion::centurion-headers-only ALIAS centurion-headers-only)
add_subdirectory("${CEN_SOURCE_DIR}")

add_library(centurion INTERFACE)
add_library(centurion::centurion ALIAS centurion)
target_link_libraries(centurion INTERFACE
  centurion-headers-only
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
  $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
  $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

if (TARGET SDL2::SDL2-static)
  add_library(centurion-static INTERFACE)
  add_library(centurion::centurion-static ALIAS centurion-static)
  target_link_libraries(centurion-static INTERFACE
    centurion-headers-only
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2_ttf::SDL2_ttf-static
  )
endif ()

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

# Installer
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_file(
  "${CMAKE_MODULE_PATH}/centurion.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/centurion.pc"
  @ONLY
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/centurion.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/centurion-config-version.cmake"
  COMPATIBILITY AnyNewerVersion
  ARCH_INDEPENDENT
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/centurion-config-version.cmake"
  "${CMAKE_MODULE_PATH}/centurion-config.cmake"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/centurion"
)

install(
  TARGETS centurion-headers-only centurion
  EXPORT centurionTargets
  FILE_SET HEADERS
)

if(TARGET centurion-static)
  install(TARGETS centurion-static EXPORT centurionTargets)
endif()

install(
  EXPORT centurionTargets
  NAMESPACE centurion::
  DESTINATION "${CMAKE_INSTALL_DATADIR}/centurion"
)
