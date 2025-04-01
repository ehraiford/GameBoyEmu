set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.10)
project(GameBoyTest)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_fetch_decode 
    tests_fetch_decode.cpp
    ../src/core/Emulator.cpp ../src/core/Emulator.h
    ../src/core/GameBoy.cpp ../src/core/GameBoy.h
    ../src/core/Cpu.cpp ../src/core/Cpu.h 
    ../src/core/Ram.cpp ../src/core/Ram.h 
    ../src/instructions/Opcodes.cpp ../src/instructions/Opcodes.h 
    ../src/instructions/FetchDecode.cpp ../src/instructions/FetchDecode.h
)
target_link_libraries(tests_fetch_decode GTest::GTest GTest::Main pthread)
enable_testing()
add_test(NAME FetchDecodeTests COMMAND tests_fetch_decode)
