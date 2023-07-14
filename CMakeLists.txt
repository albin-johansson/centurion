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
set(CEN_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CEN_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")

function(cen_prepare_target target)
  set_target_properties(${target}
                        PROPERTIES
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF
                        )

  if (CEN_USE_SDL_IMAGE MATCHES OFF)
    target_compile_definitions(${target} PRIVATE CENTURION_NO_SDL_IMAGE)
  endif ()

  if (CEN_USE_SDL_MIXER MATCHES OFF)
    target_compile_definitions(${target} PRIVATE CENTURION_NO_SDL_MIXER)
  endif ()

  if (CEN_USE_SDL_TTF MATCHES OFF)
    target_compile_definitions(${target} PRIVATE CENTURION_NO_SDL_TTF)
  endif ()

  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target}
                           PRIVATE
                           /EHsc
                           /MP
                           /W4
                           /Zc:preprocessor # Enable conforming preprocessor
                           /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                           /wd4996          # Disable deprecation warnings
                           )

    if (CEN_TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE /WX)
    endif ()
  else ()
    target_compile_options(${target} PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           -Wno-deprecated
                           -Wno-deprecated-declarations
                           -Wno-format-security
                           )

    if (CEN_TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE -Werror)
    endif ()
  endif ()
endfunction()

if (CEN_USE_SYSTEM_DEPS MATCHES ON)
  # TODO
else ()
  add_subdirectory(external/SDL)
endif ()

if (CEN_BUILD_TESTS MATCHES ON)
  find_package(GTest CONFIG REQUIRED)
  find_package(cereal CONFIG REQUIRED)
  find_package(GLEW REQUIRED)
  # add_subdirectory(test)
endif ()

if (CEN_BUILD_EXAMPLES MATCHES ON)
endif ()