cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-video-opengl LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH ${CEN_LIBRARY_DIR}/glew)
list(APPEND CMAKE_PREFIX_PATH $ENV{GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

cen_create_executable(InteractiveOpenGL "interactive_opengl.cpp")
cen_set_compiler_options(InteractiveOpenGL)

cen_include_centurion_headers(InteractiveOpenGL)
cen_link_against_sdl(InteractiveOpenGL)

copy_directory_post_build(InteractiveOpenGL
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

target_include_directories(InteractiveOpenGL
    PUBLIC ${OPENGL_INCLUDE_DIRS}
    PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(InteractiveOpenGL
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLEW_LIBRARIES})

if (WIN32)
  cen_copy_runtime_binaries(InteractiveOpenGL)
endif ()
