cmake_minimum_required(VERSION 3.23)
project(POOnatural)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp Comandos.cpp Reserva.cpp Includes.h Terminal.h Terminal.cpp curses.h)