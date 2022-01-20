cmake_minimum_required(VERSION 3.15)

project(centurion
        VERSION 7.0.0
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

include(Dependencies)
include(Utilities)

set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test/resources")
set(CEN_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CEN_BINARIES_DIR "${PROJECT_SOURCE_DIR}/bin")

set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET testcenturion)
set(CENTURION_MOCK_TARGET mockcenturion)

option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" ON)
option(CEN_EXAMPLES "Build the examples" ON)

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

add_library(${CENTURION_LIB_TARGET} INTERFACE)

target_include_directories(${CENTURION_LIB_TARGET}
                           SYSTEM PUBLIC INTERFACE
                           ${SDL2_INCLUDE_DIR}
                           ${SDL2_IMAGE_INCLUDE_DIRS}
                           ${SDL2_TTF_INCLUDE_DIRS}
                           ${SDL2_MIXER_INCLUDE_DIRS}
                           )

target_link_libraries(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
                      ${SDL2_LIBRARY}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES}
                      ${SDL2_MIXER_LIBRARIES}
                      )

if (CEN_TESTS)
  add_subdirectory(test)
endif ()

if (CEN_EXAMPLES)
  add_subdirectory(examples)
endif ()