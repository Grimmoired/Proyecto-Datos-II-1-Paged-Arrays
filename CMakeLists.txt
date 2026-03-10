cmake_minimum_required(VERSION 4.1)
project(Proyecto_Datos_II_1_Paged_Arrays)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(generador
        Generador.cpp
)

add_executable(sorter
        PagedArray.cpp
        PagedArray.h
        Sorter.cpp
)