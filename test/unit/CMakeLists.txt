project(centurion-test-unit CXX)

file(GLOB_RECURSE CENTURION_UNIT_TEST_FILES
     CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/src/**/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     )

add_executable(centurion-unit-tests "${CENTURION_UNIT_TEST_FILES}")

cen_apply_compiler_options(centurion-unit-tests)

target_link_libraries(centurion-unit-tests
                      PRIVATE
                      centurion::centurion
                      GTest::gtest
                      )