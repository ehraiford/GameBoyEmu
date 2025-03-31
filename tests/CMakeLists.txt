cmake_minimum_required(VERSION 3.10)
project(GameBoyTest)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_fetch_decode tests_fetch_decode.cpp)
target_link_libraries(tests_fetch_decode GTest::GTest GTest::Main pthread)
add_test(NAME FetchDecodeTest COMMAND tests_fetch_decode)
