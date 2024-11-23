cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin )

set(PROJECT_NAME cha_test)
project(${PROJECT_NAME})

set(SRC "../test.c")

add_executable(${PROJECT_NAME} ${SRC})
