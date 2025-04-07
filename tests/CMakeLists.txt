set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.10)
project(GameBoyTest)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_fetch_decode 
    tests_fetch_decode.cpp
    ../src/executors/Emulator.cpp ../src/executors/Emulator.h
    ../src/executors/GameBoy.cpp ../src/executors/GameBoy.h
    ../src/executors/Cpu.cpp ../src/executors/Cpu.h 
    ../src/executors/Memory.cpp ../src/executors/Memory.h 
    ../src/instructions/Opcodes.cpp ../src/instructions/Opcodes.h 
    ../src/instructions/FetchDecode.cpp ../src/instructions/FetchDecode.h
)
target_link_libraries(tests_fetch_decode GTest::GTest GTest::Main pthread)
enable_testing()
add_test(NAME FetchDecodeTests COMMAND tests_fetch_decode)
