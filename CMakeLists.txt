cmake_minimum_required(VERSION 3.15)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  cmake_path(SET VCPKG_ROOT NORMALIZE $ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 8.0.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)
