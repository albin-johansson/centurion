project(centurion-test-unit-tests LANGUAGES CXX)

file(GLOB_RECURSE CENTURION_UNIT_TEST_FILES
     CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/*.hpp
     ${PROJECT_SOURCE_DIR}/*.cpp
     )

add_executable(centurion-tests ${CENTURION_UNIT_TEST_FILES})

cen_prepare_target(centurion-tests)

target_include_directories(centurion-tests
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}
                           ${CEN_INCLUDE_DIR}
                           )

target_link_libraries(centurion-tests
                      PRIVATE
                      SDL3::SDL3
                      cereal::cereal
                      GLEW::GLEW
                      GTest::gtest
                      )

if (CEN_INCLUDE_AUDIO_TESTS MATCHES ON)
  target_compile_definitions(centurion-tests PRIVATE CENTURION_INCLUDE_AUDIO_TESTS)
endif ()

target_precompile_headers(centurion-tests PRIVATE
                          <SDL3/SDL.h>
                          <array>
                          <algorithm>
                          <vector>
                          <memory>
                          <string>
                          <string_view>
                          <sstream>
                          <optional>
                          <ostream>
                          <iostream>
                          <utility>
                          <type_traits>
                          )

add_test(NAME centurion-tests COMMAND centurion-tests)

file(COPY ${CEN_RESOURCES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  file(COPY ${CEN_BINARIES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()