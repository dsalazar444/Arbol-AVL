cmake_minimum_required(VERSION 3.29)
project(Practica2_ArbolAVL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practica2_ArbolAVL
    Arbol.cpp
    Arbol.h
    Nodo.cpp
    Nodo.h
        main.cpp)
