
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

function(cen_include_sdl_headers target)
  target_include_directories(${target}
                             SYSTEM PRIVATE
                             ${SDL2_INCLUDE_DIR}
                             ${SDL2_IMAGE_INCLUDE_DIRS}
                             ${SDL2_TTF_INCLUDE_DIRS}
                             ${SDL2_MIXER_INCLUDE_DIRS})
endfunction()

function(cen_link_sdl_libs target)
  target_link_libraries(${target}
                        PRIVATE
                        ${SDL2_LIBRARY}
                        ${SDL2_IMAGE_LIBRARIES}
                        ${SDL2_TTF_LIBRARIES}
                        ${SDL2_MIXER_LIBRARIES})
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
                           )

    if (TREAT_WARNINGS_AS_ERRORS MATCHES ON)
      target_compile_options(${target} PRIVATE -Werror)
    endif ()
  endif ()
endfunction()