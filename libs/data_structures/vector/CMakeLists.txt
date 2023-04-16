cmake_minimum_required(VERSION 3.24)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled vector.c)

add_library(data_structures
        vector.c
        vector.h)