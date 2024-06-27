cmake_minimum_required(VERSION 3.22)
project(TodoAppTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(
  todoappTest
  hello_test.cpp
)

target_link_libraries(
  todoappTest
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(todoappTest)

add_custom_command(
  TARGET todoappTest
  COMMENT "Run tests"
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failure
)