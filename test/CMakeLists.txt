cmake_minimum_required(VERSION 3.15)

project(centurion-test LANGUAGES CXX)

option(CEN_AUDIO "Test audio components" ON)

set(CEN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(unit-tests)
add_subdirectory(mocks)
