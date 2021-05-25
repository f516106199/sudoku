cmake_minimum_required(VERSION 3.15)

project(sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(sudoku src/game.cc src/grid.cc src/main.cc src/scene.cc)

target_include_directories(sudoku PRIVATE include/)