project(centurion-test CXX)

if (CEN_BUILD_DEMO_TESTS)
  add_subdirectory(demo)
endif ()

if (CEN_BUILD_UNIT_TESTS)
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory(unit)
endif ()
