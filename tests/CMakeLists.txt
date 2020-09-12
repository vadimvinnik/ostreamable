cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(type_erasure_tests)

add_executable(${PROJECT_NAME}
  main.cpp
  tests.cpp)

target_link_libraries(${PROJECT_NAME}
  CONAN_PKG::catch2
  ostreamable
  )

target_include_directories(${PROJECT_NAME} PRIVATE ../include) 

add_test(
  NAME test_all
  COMMAND type_erasure_tests)

