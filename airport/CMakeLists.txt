cmake_minimum_required(VERSION 3.30)
project(TG_jhu_dgega_fcascan C)

set(CMAKE_C_STANDARD 11)

add_executable(TG_jhu_dgega_fcascan main.c
        grafo.c
        grafo.h
        aeropuertos.c
        aeropuertos.h)
