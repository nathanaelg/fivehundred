cmake_minimum_required (VERSION 2.6)
project (FiveHundred)

SET(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_MULTITHREADING "-pthread -fopenmp -fpic -DNDEBUG -DUSE_OPENMP -rdynamic")
set(CMAKE_CXX_FLAGS_PROFILING "-pg")

add_subdirectory (${PROJECT_SOURCE_DIR}/ext/gtest/gtest-1.7.0)
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/ext/gtest/gtest-1.7.0/include)

add_executable(test_card_500 
  test/test_card_500.cpp 
  src/card_500.cpp)
target_link_libraries(test_card_500 gtest gtest_main)
add_custom_command(TARGET test_card_500
  POST_BUILD
  COMMAND ./test_card_500)