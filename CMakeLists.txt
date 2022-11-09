cmake_minimum_required(VERSION 3.23)
project(Set C)

set(CMAKE_C_STANDARD 99)

add_executable(Set main.c library.c library.h)

add_library(library library.c library.h)