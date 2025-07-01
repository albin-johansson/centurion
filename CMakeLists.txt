cmake_minimum_required(VERSION "3.30")

option(CEN_ENABLE_TESTS "Enable the test suites" "OFF")
option(CEN_ENABLE_EXAMPLES "Enable the examples" "OFF")
option(CEN_ENABLE_CXX20_MODULE "Enable the C++20 module" "OFF")

if (CEN_ENABLE_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif ()

message(DEBUG "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message(DEBUG "VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")
message(DEBUG "VCPKG_MANIFEST_FEATURES: ${VCPKG_MANIFEST_FEATURES}")
message(DEBUG "CEN_ENABLE_TESTS: ${CEN_ENABLE_TESTS}")
message(DEBUG "CEN_ENABLE_EXAMPLES: ${CEN_ENABLE_EXAMPLES}")
message(DEBUG "CEN_ENABLE_CXX20_MODULE: ${CEN_ENABLE_CXX20_MODULE}")

project(centurion
        VERSION "8.0.0"
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES "CXX"
        )

message(DEBUG "VCPKG_MANIFEST_FEATURES: ${VCPKG_MANIFEST_FEATURES}")

find_package(SDL3 CONFIG REQUIRED)

function(cen_prepare_target_properties target)
  set_target_properties("${target}"
                        PROPERTIES
                        PREFIX ""
                        POSITION_INDEPENDENT_CODE "ON"
                        CXX_STANDARD "20"
                        )
endfunction()

add_library(centurion_lib STATIC)
add_library(centurion::library ALIAS centurion_lib)

cen_prepare_target_properties(centurion_lib)

target_sources(centurion_lib
               PUBLIC FILE_SET "HEADERS" BASE_DIRS "include" FILES
               "include/centurion/gpu/buffer.hpp"
               "include/centurion/gpu/device.hpp"
               "include/centurion/gpu/pipeline.hpp"
               "include/centurion/gpu/sampler.hpp"
               "include/centurion/gpu/shader.hpp"
               "include/centurion/gpu/swapchain.hpp"
               "include/centurion/gpu/texture.hpp"
               "include/centurion/internal/defer.hpp"
               "include/centurion/util/common.hpp"
               "include/centurion/util/handle.hpp"
               "include/centurion/init.hpp"
               "include/centurion/video.hpp"

               PRIVATE
               "src/centurion/gpu/buffer.cpp"
               "src/centurion/gpu/device.cpp"
               "src/centurion/gpu/pipeline.cpp"
               "src/centurion/gpu/sampler.cpp"
               "src/centurion/gpu/shader.cpp"
               "src/centurion/gpu/texture.cpp"
               "src/centurion/init.cpp"
               )

target_link_libraries(centurion_lib
                      PUBLIC
                      SDL3::SDL3
                      )

if (CEN_ENABLE_CXX20_MODULE)
  add_library(centurion_mod)
  add_library(centurion::module ALIAS centurion_mod)

  cen_prepare_target_properties(centurion_mod)

  target_sources(centurion_mod
                 PUBLIC FILE_SET "CXX_MODULES" BASE_DIRS "include" FILES
                 "include/centurion.cppm"
                 )

  target_link_libraries(centurion_mod
                        PUBLIC
                        centurion::library
                        )
endif ()

