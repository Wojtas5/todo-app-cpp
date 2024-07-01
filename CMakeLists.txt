cmake_minimum_required(VERSION 3.22)

project(TodoAppCpp VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/poco)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
add_subdirectory(tests)

file(GLOB SRCS "src/*.cpp")

add_executable(TodoApp ${SRCS})
target_link_libraries(TodoApp PRIVATE Poco::Util Poco::Net)
target_include_directories(TodoApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
