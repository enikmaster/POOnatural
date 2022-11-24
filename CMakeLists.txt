cmake_minimum_required(VERSION 3.23)
project(POOnatural)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp Comandos.cpp)
target_link_libraries(${PROJECT_NAME} C:/Users/filip_4sxaizl/Documents/Filipe/00-ISEC/pdcurses.a)