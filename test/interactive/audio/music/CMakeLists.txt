cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-audio-music LANGUAGES CXX)

if (WIN32)
  add_executable(InteractiveMusic WIN32 interactive_music.cpp)
else ()
  add_executable(InteractiveMusic interactive_music.cpp)
endif ()

cen_set_compiler_options(InteractiveMusic)

target_include_directories(InteractiveMusic
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${CEN_INCLUDE_DIR})

target_link_libraries(InteractiveMusic
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${CENTURION_IMPORT_LIB})

copy_directory_post_build(InteractiveMusic
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  copy_file_post_build(
      InteractiveMusic
      ${CENTURION_DYNAMIC_LIB}
      ${CMAKE_CURRENT_BINARY_DIR})

  copy_directory_post_build(
      InteractiveMusic
      ${CEN_BINARIES_DIR}
      ${CMAKE_CURRENT_BINARY_DIR})
endif ()
