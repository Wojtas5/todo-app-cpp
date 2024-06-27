cmake_minimum_required(VERSION 3.22)

project(TodoAppCpp VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(todo-app src/main.cpp)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
add_subdirectory(tests)
