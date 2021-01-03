cmake_minimum_required(VERSION 3.15)

project(centurion-test-interactive-graphics-fontcache LANGUAGES CXX)

cen_create_executable(InteractiveFontCache "interactive_font_cache.cpp")
cen_set_compiler_options(InteractiveFontCache)

cen_include_centurion_headers(InteractiveFontCache)
cen_link_against_centurion(InteractiveFontCache)

copy_directory_post_build(InteractiveFontCache
    ${CEN_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (WIN32)
  cen_copy_runtime_binaries(InteractiveFontCache)
endif ()
