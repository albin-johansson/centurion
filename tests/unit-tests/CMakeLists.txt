project(centurion-unit-tests LANGUAGES CXX)

file(GLOB_RECURSE CENTURION_UNIT_TEST_FILES
     CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/src/*.hpp
     ${PROJECT_SOURCE_DIR}/src/*.cpp
     )

add_executable(centurion-tests ${CENTURION_UNIT_TEST_FILES})

cen_prepare_target(centurion-tests)

target_include_directories(centurion-tests PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(centurion-tests
                      PRIVATE
                      cen::centurion
                      GTest::gtest
                      )

if (WIN32)
  file(COPY ${SDL3_BINARY_DIR}/SDL3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_BINARY_DIR}/external/SDL_image/SDL3_image.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_BINARY_DIR}/external/SDL_mixer/SDL3_mixer.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_BINARY_DIR}/external/SDL_ttf/SDL3_ttf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()
