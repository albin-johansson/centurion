project(centurion-test-demo-iostream CXX)

add_executable(centurion_iostream_demo)

target_sources(centurion_iostream_demo PRIVATE "main.cpp")

cen_prepare_target_options(centurion_iostream_demo)

target_link_libraries(centurion_iostream_demo PUBLIC centurion::centurion)

cen_install_sdl_runtime_dependencies("${PROJECT_BINARY_DIR}")
