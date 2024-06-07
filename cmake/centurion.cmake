
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  list(APPEND CEN_COMPILE_OPTIONS
       "/EHsc"
       "/MP"
       "/W4"
       "/permissive-"
       "/wd4996"          # Disable deprecation warnings
       "/Zc:preprocessor" # Enable conforming preprocessor
       "/Zc:__cplusplus"  # Force MSVC to use __cplusplus macro with correct value
       )

  if (CEN_WARNINGS_AS_ERRORS)
    list(APPEND CEN_COMPILE_OPTIONS "/WX")
  endif ()
else ()
  list(APPEND CEN_COMPILE_OPTIONS
       "-Wall"
       "-Wextra"
       "-Wpedantic"
       "-Wconversion"
       "-Wsign-conversion"
       "-Wshadow"
       "-Wswitch-enum"
       "-Wold-style-cast"
       "-Wno-deprecated"
       "-Wno-deprecated-declarations"
       "-Wno-format-security"
       "-Wno-gnu-zero-variadic-macro-arguments"
       )

  if (CEN_WARNINGS_AS_ERRORS)
    list(APPEND CEN_COMPILE_OPTIONS "-Werror")
  endif ()
endif ()

message(DEBUG "CEN_COMPILE_OPTIONS: ${CEN_COMPILE_OPTIONS}")

function(cen_add_header_only_library name include_dir sources)
  add_library("${name}" INTERFACE)
  target_sources("${name}" INTERFACE "${sources}")
  target_include_directories("${name}" SYSTEM INTERFACE "${include_dir}")
endfunction()

function(cen_prepare_target_options target)
  set_target_properties("${target}"
                        PROPERTIES
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF
                        )

  target_compile_options("${target}" PRIVATE "${CEN_COMPILE_OPTIONS}")
endfunction()

function(cen_install_assets to)
  if (CEN_BUILD_UNIT_TESTS OR CEN_BUILD_DEMO_TESTS)
    install(DIRECTORY "${CEN_ASSETS_DIR}" DESTINATION "${to}")
  endif ()
endfunction()
