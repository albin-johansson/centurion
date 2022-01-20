cmake_minimum_required(VERSION 3.15)

project(centurion-examples-minimal-program CXX)

add_executable(ex-minimal-program demo.cpp)
cen_add_example(ex-minimal-program)