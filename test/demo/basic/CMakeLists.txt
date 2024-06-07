project(centurion-test-demo-basic CXX)

add_executable(centurion_basic_demo)

target_sources(centurion_basic_demo PRIVATE "main.cpp")

cen_prepare_target_options(centurion_basic_demo)

target_link_libraries(centurion_basic_demo PUBLIC centurion::centurion)
