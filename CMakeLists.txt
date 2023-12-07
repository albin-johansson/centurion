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
option(CEN_USE_ADDRESS_SANITIZER "Build with the address sanitizer enabled" OFF)
option(CEN_USE_UB_SANITIZER "Build with the undefined behavior sanitizer enabled" OFF)

message(DEBUG "CEN_USE_SYSTEM_SDL: ${CEN_USE_SYSTEM_SDL}")
message(DEBUG "CEN_BUILD_UNIT_TESTS: ${CEN_BUILD_UNIT_TESTS}")
message(DEBUG "CEN_BUILD_MOCK_TESTS: ${CEN_BUILD_MOCK_TESTS}")
message(DEBUG "CEN_USE_ADDRESS_SANITIZER: ${CEN_USE_ADDRESS_SANITIZER}")
message(DEBUG "CEN_USE_UB_SANITIZER: ${CEN_USE_UB_SANITIZER}")

set(CENTURION_ROOT_DIR "${PROJECT_SOURCE_DIR}")

message(DEBUG "CENTURION_ROOT_DIR: ${CENTURION_ROOT_DIR}")

if (CEN_USE_SYSTEM_SDL MATCHES "ON")
  find_package(SDL3 REQUIRED)
else ()
  find_package(SDL3 REQUIRED PATHS "${CENTURION_ROOT_DIR}/external/SDL/build")
endif ()

if (MSVC)
  list(APPEND CENTURION_COMPILER_FLAGS
       /EHsc
       /MP
       /W4
       /permissive-
       /Zc:preprocessor
       /Zc:__cplusplus
       )
else ()
  list(APPEND CENTURION_COMPILER_FLAGS
       -Wall
       -Wextra
       -Wpedantic
       -Wconversion
       -Wsign-conversion
       -Wshadow
       )

  if (NOT MSVC)
    if (CEN_USE_ADDRESS_SANITIZER MATCHES "ON")
      list(APPEND CENTURION_COMPILER_FLAGS -fsanitize=address -fno-sanitize-recover -fno-omit-frame-pointer -g)
      list(APPEND CENTURION_LINK_FLAGS -fsanitize=address -fno-sanitize-recover -fno-omit-frame-pointer -g)
    elseif (CEN_USE_UB_SANITIZER MATCHES "ON")
      list(APPEND CENTURION_COMPILER_FLAGS -fsanitize=undefined -fno-sanitize-recover -fno-omit-frame-pointer -g)
      list(APPEND CENTURION_LINK_FLAGS -fsanitize=undefined -fno-sanitize-recover -fno-omit-frame-pointer -g)
    endif ()
  endif ()
endif ()

message(DEBUG "CENTURION_COMPILER_FLAGS: ${CENTURION_COMPILER_FLAGS}")
message(DEBUG "CENTURION_LINK_FLAGS: ${CENTURION_LINK_FLAGS}")

function(cen_apply_compiler_options target)
  set_target_properties(${target}
                        PROPERTIES
                        CXX_STANDARD_REQUIRED ON
                        CXX_STANDARD_EXTENSIONS OFF
                        )

  target_compile_options(${target} PRIVATE "${CENTURION_COMPILER_FLAGS}")
  target_link_options(${target} PRIVATE "${CENTURION_LINK_FLAGS}")

  if (NOT MSVC)
    if (CEN_USE_ADDRESS_SANITIZER MATCHES "ON")
      target_link_libraries(${target} PRIVATE -fsanitize=address)
    elseif (CEN_USE_UB_SANITIZER MATCHES "ON")
      target_link_libraries(${target} PRIVATE -fsanitize=undefined)
    endif ()
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
