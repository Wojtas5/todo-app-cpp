cmake_minimum_required(VERSION 3.22)

project(TodoAppCpp VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TodoApp src/main.cpp)

add_subdirectory(lib/poco)
target_link_libraries(TodoApp PRIVATE Poco::Util Poco::Net)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
add_subdirectory(tests)
