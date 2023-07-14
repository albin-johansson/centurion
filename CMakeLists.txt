cmake_minimum_required(VERSION 3.15)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(centurion
        VERSION 8.0.0
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES CXX)

# Build configuration
option(CEN_USE_SYSTEM_DEPS "Use SDL libraries installed on system" ON)
option(CEN_USE_SDL_IMAGE "Enable APIs dependent on the SDL_image library" OFF)
option(CEN_USE_SDL_MIXER "Enable APIs dependent on the SDL_mixer library" OFF)
option(CEN_USE_SDL_TTF "Enable APIs dependent on the SDL_ttf library" OFF)
option(CEN_BUILD_EXAMPLES "Build the examples" OFF)
option(CEN_BUILD_TESTS "Build the test suite" OFF)
option(CEN_INCLUDE_AUDIO_TESTS "Test audio components" ON)
option(CEN_TREAT_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Directories
set(CEN_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(CEN_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(CEN_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")

if (CEN_USE_SYSTEM_DEPS MATCHES ON)
  # TODO
else ()
  add_subdirectory(external/SDL)
endif ()

add_library(centurion INTERFACE)

set_target_properties(centurion
                      PROPERTIES
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      )

target_include_directories(centurion INTERFACE ${CEN_INCLUDE_DIR})

target_link_libraries(centurion INTERFACE SDL3::SDL3)

if (CEN_USE_SDL_IMAGE MATCHES OFF)
  target_compile_definitions(centurion INTERFACE CENTURION_NO_SDL_IMAGE)
endif ()

if (CEN_USE_SDL_MIXER MATCHES OFF)
  target_compile_definitions(centurion INTERFACE CENTURION_NO_SDL_MIXER)
endif ()

if (CEN_USE_SDL_TTF MATCHES OFF)
  target_compile_definitions(centurion INTERFACE CENTURION_NO_SDL_TTF)
endif ()

add_library(cen::centurion ALIAS centurion)

if (CEN_BUILD_TESTS MATCHES ON)
  find_package(GTest CONFIG REQUIRED)
  find_package(cereal CONFIG REQUIRED)
  find_package(GLEW REQUIRED)
  add_subdirectory(tests)
endif ()

if (CEN_BUILD_EXAMPLES MATCHES ON)
endif ()