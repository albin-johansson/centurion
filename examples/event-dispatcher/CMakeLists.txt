cmake_minimum_required(VERSION 3.15)

project(centurion-examples-event-dispatcher CXX)

add_executable(example_event_dispatcher event_dispatcher.cpp)

target_link_libraries(example_event_dispatcher PRIVATE ${CENTURION_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(example_event_dispatcher ${CEN_BINARIES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()