cmake_minimum_required(VERSION 2.8.4)
project(PPAR-M1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#HelloWorld
set(SOURCE_FILES_HELLO TP1/HelloWorld/HelloWorld.cpp)
add_executable(TP1_HelloWorld ${SOURCE_FILES_HELLO})

#Matrix Multiplication
set(SOURCE_FILES_MATRIX TP1/Matrix/Matrix.cpp)
add_executable(TP1_Matrix ${SOURCE_FILES_MATRIX})