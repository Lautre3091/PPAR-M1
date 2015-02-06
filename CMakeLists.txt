cmake_minimum_required(VERSION 2.8.4)
project(PPAR-M1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

#HelloWorld
set(SOURCE_FILES_HELLO TP1/HelloWorld/HelloWorld.c)
add_executable(TP1_HelloWorld ${SOURCE_FILES_HELLO})

#Matrix Multiplication
set(SOURCE_FILES_MATRIX TP1/Matrix/Matrix.c)
add_executable(TP1_Matrix ${SOURCE_FILES_MATRIX})