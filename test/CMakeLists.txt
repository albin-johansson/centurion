cmake_minimum_required(VERSION 3.15)

project(centurion-test LANGUAGES CXX)

include(DownloadProject)
include(CTest)

download_project(PROJ googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    "UPDATE_DISCONNECTED 1")

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
add_subdirectory(unittests)
add_subdirectory(mocks)
add_subdirectory(interactive/audio/music)
add_subdirectory(interactive/graphics/fontcache)