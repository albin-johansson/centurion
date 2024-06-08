project(centurion-test CXX)

function(cen_install_sdl_runtime_dependencies to)
  if (WIN32)
    install(IMPORTED_RUNTIME_ARTIFACTS SDL3-shared DESTINATION "${to}")

    if (CEN_USE_SDL_IMAGE)
      install(IMPORTED_RUNTIME_ARTIFACTS SDL3_image-shared DESTINATION "${to}")
    endif ()

    if (CEN_USE_SDL_MIXER)
      install(IMPORTED_RUNTIME_ARTIFACTS SDL3_mixer-shared DESTINATION "${to}")
    endif ()

    if (CEN_USE_SDL_TTF)
      install(IMPORTED_RUNTIME_ARTIFACTS SDL3_ttf-shared DESTINATION "${to}")
    endif ()
  endif ()
endfunction()

if (CEN_BUILD_DEMO_TESTS)
  add_subdirectory(demo)
endif ()

if (CEN_BUILD_UNIT_TESTS)
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory(unit)
endif ()
