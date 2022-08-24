cmake_minimum_required(VERSION 3.19)
project(PROJETO_AEDS2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PROJETO_AEDS2
        funcionarios.c
        funcionarios.h
        main.c)
