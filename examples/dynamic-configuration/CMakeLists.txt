cmake_minimum_required(VERSION 3.15)

project(centurion-examples-dynamic-configuration CXX)

add_executable(ex-dynamic-configuration demo.cpp)
cen_add_example(ex-dynamic-configuration)