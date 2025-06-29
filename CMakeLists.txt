cmake_minimum_required(VERSION "3.30")

option(CEN_ENABLE_TESTS "Enable the test suites" "OFF")
option(CEN_ENABLE_EXAMPLES "Enable the examples" "OFF")

message(DEBUG "CEN_ENABLE_TESTS: ${CEN_ENABLE_TESTS}")
message(DEBUG "CEN_ENABLE_EXAMPLES: ${CEN_ENABLE_EXAMPLES}")

project(centurion
        VERSION "8.0.0"
        HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
        LANGUAGES "CXX"
        )

find_package(SDL3 CONFIG REQUIRED)

add_library(centurion_lib STATIC)
add_library(centurion::library ALIAS centurion_lib)

set_target_properties(centurion_lib
                      PROPERTIES
                      CXX_STANDARD "20"
                      POSITION_INDEPENDENT_CODE "ON"
                      PREFIX ""
                      )


target_link_libraries(centurion_lib
                      PUBLIC
                      SDL3::SDL3
                      )

