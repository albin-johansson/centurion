project(centurion-test-mock CXX)

add_library(lib-fff INTERFACE)
add_library(centurion::fff ALIAS lib-fff)
target_sources(lib-fff INTERFACE "${CENTURION_ROOT_DIR}/external/fff/fff.h")
target_include_directories(lib-fff SYSTEM INTERFACE "${CENTURION_ROOT_DIR}/external/fff")

file(GLOB_RECURSE CENTURION_MOCK_TEST_FILES
     CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/inc/**/*.hpp"
     "${PROJECT_SOURCE_DIR}/inc/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     )

add_executable(centurion-mock-tests "${CENTURION_MOCK_TEST_FILES}")

cen_apply_compiler_options(centurion-mock-tests)

target_include_directories(centurion-mock-tests
                           PRIVATE
                           "${PROJECT_SOURCE_DIR}/inc"
                           "${CENTURION_ROOT_DIR}/lib/inc"
                           )

target_link_libraries(centurion-mock-tests
                      PRIVATE
                      centurion::centurion-lite
                      centurion::fff
                      GTest::gtest
                      )
