project(centurion-mocked-tests LANGUAGES CXX)

add_library(FFF INTERFACE)
target_sources(FFF INTERFACE ${CEN_EXTERNAL_DIR}/fff/fff.h)
target_include_directories(FFF SYSTEM INTERFACE ${CEN_EXTERNAL_DIR})

file(GLOB_RECURSE CENTURION_MOCKED_TEST_FILES
     CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/src/*.hpp
     ${PROJECT_SOURCE_DIR}/src/*.cpp
     )

add_executable(centurion-mocked-tests ${CENTURION_MOCKED_TEST_FILES})

cen_prepare_target(centurion-mocked-tests)

target_include_directories(centurion-mocked-tests
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/src
                           ${CEN_INCLUDE_DIR}
                           ${CEN_EXTERNAL_DIR}/SDL/include
                           ${CEN_EXTERNAL_DIR}/SDL_image/include
                           ${CEN_EXTERNAL_DIR}/SDL_mixer/include
                           ${CEN_EXTERNAL_DIR}/SDL_ttf/include
                           )

target_link_libraries(centurion-mocked-tests
                      PRIVATE
                      FFF
                      GTest::gtest
                      )
