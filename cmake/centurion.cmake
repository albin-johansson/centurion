
# Creates an interface library target for a header-only library.
#   name: the name of the library target.
#   includeDirectory: the path of the directory that contains the headers of the library.
#   sources: the headers associated with the library.
function(cen_add_header_only_lib name includeDirectory sources)
  add_library(${name} INTERFACE)
  target_sources(${name} INTERFACE ${sources})
  target_include_directories(${name} SYSTEM INTERFACE ${includeDirectory})
endfunction()

# Copies a directory.
#   target: the associated target.
#   from: the directory that will be copied.
#   to: the target destination of the copied directory.
function(cen_copy_directory_post_build target from to)
  add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${from}
      ${to})
endfunction()

function(cen_set_basic_compiler_options target)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target} PRIVATE
                           /EHsc
                           /MP
                           /W4
                           /wd4996          # Disable deprecation warnings
                           /Zc:preprocessor # Enable conforming preprocessor
                           /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
                           )

    if (TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE /WX)
    endif ()
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|AppleClang")
    target_compile_options(${target} PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           -Wno-deprecated
                           -Wno-deprecated-declarations
                           -Wno-format-security
                           -Wno-gnu-zero-variadic-macro-arguments
                           )

    if (TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE -Werror)
    endif ()
  endif ()
endfunction()

# Checks if targets exists and stores the result in a variable.
#   var: the name of the result variable
#   ARGN: list of targets to check the existence of
function(cen_has_targets var)
  set(${var} FALSE PARENT_SCOPE)
  foreach(target IN LISTS ARGN)
    if (NOT TARGET ${target})
      return()
    endif ()
  endforeach ()
  set(${var} TRUE PARENT_SCOPE)
endfunction()

# Checks if the relevant SDL targets exist and stores the result in the
# corresponding variable
#   shared: the name of the shared libraries variable
#   static: the name of the static libraries variable
function(cen_has_SDL shared static)
  cen_has_targets(_shared
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
  )
  set(${shared} ${_shared} PARENT_SCOPE)
  cen_has_targets(_static 
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2_ttf::SDL2_ttf-static
  )
  set(${static} ${_static} PARENT_SCOPE)
endfunction()
