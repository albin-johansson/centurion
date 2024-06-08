project(centurion-test-unit CXX)

add_executable(centurion-unit-tests)

file(GLOB_RECURSE CEN_UNIT_TEST_SOURCE_FILES CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/**/*.cpp"
     )
target_sources(centurion-unit-tests PRIVATE "${CEN_UNIT_TEST_SOURCE_FILES}")

cen_prepare_target_options(centurion-unit-tests)

target_link_libraries(centurion-unit-tests
                      PRIVATE
                      centurion::centurion
                      GTest::gtest
                      )

cen_install_assets("${PROJECT_BINARY_DIR}")
cen_install_sdl_runtime_dependencies("${PROJECT_BINARY_DIR}")
