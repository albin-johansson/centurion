project(centurion-lib CXX)

add_library(centurion STATIC)
add_library(centurion::centurion ALIAS centurion)

file(GLOB_RECURSE CEN_SOURCE_FILES CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/inc/**/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
     )
target_sources(centurion PRIVATE "${CEN_SOURCE_FILES}")

cen_prepare_target_options(centurion)

target_include_directories(centurion PUBLIC "${PROJECT_SOURCE_DIR}/inc")

target_link_libraries(centurion PUBLIC SDL3::SDL3)

if (CEN_USE_SDL_IMAGE)
  target_link_libraries(centurion PUBLIC SDL3_image::SDL3_image)
else ()
  target_compile_definitions(centurion PUBLIC "CENTURION_NO_SDL_IMAGE")
endif ()

if (CEN_USE_SDL_MIXER)
  target_link_libraries(centurion PUBLIC SDL3_mixer::SDL3_mixer)
else ()
  target_compile_definitions(centurion PUBLIC "CENTURION_NO_SDL_MIXER")
endif ()

if (CEN_USE_SDL_TTF)
  target_link_libraries(centurion PUBLIC SDL3_ttf::SDL3_ttf)
else ()
  target_compile_definitions(centurion PUBLIC "CENTURION_NO_SDL_TTF")
endif ()
