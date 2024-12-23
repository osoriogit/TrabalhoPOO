cmake_minimum_required(VERSION 3.28.1)
project(WORKC)

set(CMAKE_CXX_STANDARD 26)

add_executable(WORKC main.cpp
        Simulador.h
        Simulador.cpp
        Caravanas.h
        Caravanas.cpp
        Cidade.h
        Cidade.cpp
        User.h
        User.cpp
        mapa.txt
        buffer.cpp
        Montanhas.cpp
)
