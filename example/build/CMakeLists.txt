cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

set(PROJECT_NAME cha_example)
project(${PROJECT_NAME})

set(SRC "../example.c")

add_executable(${PROJECT_NAME} ${SRC})
