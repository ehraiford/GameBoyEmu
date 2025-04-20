set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.10)
project(GameBoyTest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB SRC_FILES "../src/**/*.cpp" "../src/**/*.h")

add_executable(tests 
    tests.cpp
    ${SRC_FILES}
)
target_link_libraries(tests GTest::GTest GTest::Main pthread)
enable_testing()
add_test(NAME FetchDecodeTests COMMAND tests)
