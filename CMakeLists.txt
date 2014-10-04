cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_COMPILER "/usr/bin/c++")

project (FiveHundred)

set(CMAKE_BUILD_TYPE RELEASE)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_MULTITHREADING "-pthread -fopenmp -fpic -DNDEBUG -DUSE_OPENMP")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g ${CMAKE_CXX_FLAGS_MULTITHREADING} -DBUILD_TYPE_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${CMAKE_CXX_FLAGS_MULTITHREADING} -DBUILD_TYPE_RELEASE")
set(CMAKE_CXX_FLAGS_PROFILING "-pg")

add_subdirectory (${PROJECT_SOURCE_DIR}/ext/gtest/gtest-1.7.0)
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/ext/gtest/gtest-1.7.0/include)
include_directories (${PROJECT_SOURCE_DIR}/ext/petters/monte-carlo-tree-search)

add_executable(test_console
  test/test_console.cpp
  src/console.cpp)
target_link_libraries(test_console gtest gtest_main)
add_custom_command(TARGET test_console
  POST_BUILD
  COMMAND ./test_console)

add_executable(test_card_500
  test/test_card_500.cpp
  src/card_500.cpp)
target_link_libraries(test_card_500 gtest gtest_main)
add_custom_command(TARGET test_card_500
  POST_BUILD
  COMMAND ./test_card_500)

add_executable(test_card_collection_500
  test/test_card_collection_500.cpp
  src/card_500.cpp
  src/card_collection_500.cpp)
target_link_libraries(test_card_collection_500 gtest gtest_main)
add_custom_command(TARGET test_card_collection_500
  POST_BUILD
  COMMAND ./test_card_collection_500)

add_executable(test_hand_500
  test/test_hand_500.cpp
  src/card_500.cpp
  src/card_collection_500.cpp
  src/hand_500.cpp)
target_link_libraries(test_hand_500 gtest gtest_main)
add_custom_command(TARGET test_hand_500
  POST_BUILD
  COMMAND ./test_hand_500)

add_executable(test_trick_500
  test/test_trick_500.cpp
  src/console.cpp
  src/card_500.cpp
  src/card_collection_500.cpp
  src/trick_500.cpp)
target_link_libraries(test_trick_500 gtest gtest_main)
add_custom_command(TARGET test_trick_500
  POST_BUILD
  COMMAND ./test_trick_500)

add_executable(test_deck_500
  test/test_deck_500.cpp
  src/console.cpp
  src/card_500.cpp
  src/card_collection_500.cpp
  src/hand_500.cpp
  src/kitty_500.cpp
  src/deck_500.cpp)
target_link_libraries(test_deck_500 gtest gtest_main)
add_custom_command(TARGET test_deck_500
  POST_BUILD
  COMMAND ./test_deck_500)

add_executable(test_game_state_500
  test/test_game_state_500.cpp
  src/console.cpp
  src/card_500.cpp
  src/card_collection_500.cpp
  src/hand_500.cpp
  src/kitty_500.cpp
  src/trick_500.cpp
  src/deck_500.cpp
  src/game_state_500.cpp)
target_link_libraries(test_game_state_500 gtest gtest_main)
add_custom_command(TARGET test_game_state_500
  POST_BUILD
  COMMAND ./test_game_state_500)

add_executable(test_mcts
  test/test_mcts.cpp
  src/mcts.cpp)
target_link_libraries(test_mcts gtest gtest_main)
add_custom_command(TARGET test_mcts
  POST_BUILD
  COMMAND ./test_mcts)

add_executable(test_mcts_500
  test/test_mcts_500.cpp
  src/console.cpp
  src/card_500.cpp
  src/card_collection_500.cpp
  src/hand_500.cpp
  src/kitty_500.cpp
  src/trick_500.cpp
  src/deck_500.cpp
  src/game_state_500.cpp
  src/mcts.cpp)
target_link_libraries(test_mcts_500 gtest gtest_main)
add_custom_command(TARGET test_mcts_500
  POST_BUILD
  COMMAND ./test_mcts_500)
