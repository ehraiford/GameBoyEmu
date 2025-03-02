cmake_minimum_required(VERSION 3.16)
project(MyProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Clang-Tidy if available
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    message(STATUS "Using Clang-Tidy: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*")
endif()

# Enable Cppcheck if available
find_program(CPPCHECK_EXE NAMES cppcheck)
if(CPPCHECK_EXE)
    message(STATUS "Using Cppcheck: ${CPPCHECK_EXE}")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE};--enable=all;--inconclusive;--quiet")
endif()

# Enable AddressSanitizer, UndefinedBehaviorSanitizer, ThreadSanitizer
option(ENABLE_SANITIZERS "Enable Address, Undefined, and Thread Sanitizers" ON)

if(ENABLE_SANITIZERS)
    message(STATUS "Sanitizers Enabled")
    set(SANITIZER_FLAGS "-fsanitize=address,undefined,thread -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
endif()

# Enable MemorySanitizer (only with Clang)
option(ENABLE_MEMORY_SANITIZER "Enable MemorySanitizer" OFF)
if(ENABLE_MEMORY_SANITIZER AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "MemorySanitizer Enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
endif()

# Create executable
add_executable(MyExecutable main.cpp)

# Link with sanitizers
if(ENABLE_SANITIZERS)
    target_link_libraries(MyExecutable PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=thread)
endif()

# Enable warnings and treat warnings as errors (optional)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
