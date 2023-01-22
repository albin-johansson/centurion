cmake_minimum_required(VERSION 3.15)

project(centurion-test CXX)
enable_testing()

set(CEN_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(unit-tests)
add_subdirectory(mocked-tests)
