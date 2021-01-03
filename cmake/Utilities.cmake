
# Creates an interface library target for a header-only library.
#   name: the name of the library target.
#   includeDirectory: the path of the directory that contains the headers of the library.
#   sources: the headers associated with the library.
function(add_header_only_lib name includeDirectory sources)
  add_library(${name} INTERFACE)
  target_sources(${name} INTERFACE ${sources})
  target_include_directories(${name} SYSTEM INTERFACE ${includeDirectory})
endfunction()

# Checks if an environment variable is defined.
#   envVar: the name of the actual environment variable.
#   name: the name of the library associated with the environment variable.
function(find_env_var envVar name)
  if (DEFINED ENV{${envVar}})
    message("${name} path: " $ENV{${envVar}})
  else ()
    message(WARNING "Couldn't find environment variable ${envVar}!")
  endif ()
endfunction()

# Copies a file.
#   target: the associated target.
#   from: the file that will be copied.
#   to: the target destination of the copied file.
function(copy_file_post_build target from to)
  add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${from}
      ${to})
endfunction()

# Copies a directory.
#   target: the associated target.
#   from: the directory that will be copied.
#   to: the target destination of the copied directory.
function(copy_directory_post_build target from to)
  add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${from}
      ${to})
endfunction()

# Sets appropriate compiler options depending on the current platform.
#   target: the associated target.
function(cen_set_compiler_options target)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target} PRIVATE
        /EHsc
        /MP
        /W3)

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${target} PRIVATE
        /EHsc)

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${target} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wdouble-promotion
        -Wswitch-default
        -Wswitch-enum
        -Wunused
        -Wuninitialized
        -Wsuggest-final-types
        -Wsuggest-final-methods
        -Wsuggest-override
        -Wduplicated-cond
        -Wconversion
        -Wc++17-compat
        -Wno-attributes)
  endif ()
endfunction()

# Adds an executable associated with the target, will be created using WIN32 on windows.
#   target: the associated target.
function(cen_create_executable name files)
  #message("Creating executable from: ${files}")
  if (WIN32)
    add_executable(${name} WIN32 ${files})
  else ()
    add_executable(${name} ${files})
  endif ()
endfunction()

# Includes Centurion and SDL2 headers.
#   target: the associated target.
function(cen_include_centurion_headers target)
  target_include_directories(${target}
      SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
      SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
      SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
      SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
      SYSTEM PUBLIC ${CEN_INCLUDE_DIR})
endfunction()

# Links against the SDL2 libraries.
#   target: the associated target.
function(cen_link_against_sdl target)
  target_link_libraries(${target}
      PUBLIC ${SDL2_LIBRARY}
      PUBLIC ${SDL2_IMAGE_LIBRARIES}
      PUBLIC ${SDL2_MIXER_LIBRARIES}
      PUBLIC ${SDL2_TTF_LIBRARIES})
endfunction()

# Copies runtime binaries to current binary dir. This is only necessary on Windows.
#   target: the associated target.
function(cen_copy_runtime_binaries target)
  copy_directory_post_build(
      ${target}
      ${CEN_BINARIES_DIR}
      ${CMAKE_CURRENT_BINARY_DIR})
endfunction()