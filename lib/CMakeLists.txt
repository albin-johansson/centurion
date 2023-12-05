project(centurion-lib CXX)

file(GLOB_RECURSE CENTURION_SOURCE_FILES
     CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/inc/**/*.hpp"
     "${PROJECT_SOURCE_DIR}/inc/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     )

add_library(centurion STATIC "${CENTURION_SOURCE_FILES}")
add_library(centurion-lite STATIC "${CENTURION_SOURCE_FILES}")

add_library(centurion::centurion ALIAS centurion)
add_library(centurion::centurion-lite ALIAS centurion-lite)

cen_apply_compiler_options(centurion)
cen_apply_compiler_options(centurion-lite)

target_include_directories(centurion PUBLIC "${PROJECT_SOURCE_DIR}/inc")
target_include_directories(centurion-lite PUBLIC "${PROJECT_SOURCE_DIR}/inc")

target_link_libraries(centurion PUBLIC SDL3::SDL3)
target_link_libraries(centurion-lite PUBLIC SDL3::Headers)
