cmake_minimum_required(VERSION 3.15)

project(centurion-examples-event-dispatcher CXX)

cen_create_executable(example_event_dispatcher event_dispatcher.cpp)
cen_set_compiler_options(example_event_dispatcher)

cen_include_centurion_headers(example_event_dispatcher)
cen_link_against_sdl(example_event_dispatcher)

if (WIN32)
  cen_copy_runtime_binaries(example_event_dispatcher)
endif ()