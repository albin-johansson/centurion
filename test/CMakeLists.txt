cmake_minimum_required(VERSION 3.15)

project(centurion-test CXX)

enable_testing()

add_subdirectory(unit-tests)
add_subdirectory(mocked-tests)
