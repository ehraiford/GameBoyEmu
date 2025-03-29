cmake_minimum_required(VERSION 3.16)
project(GameBoyEmu)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0156 NEW)

add_executable(GameBoyEmu 
  ../src/main.cpp 
  ../src/Opcodes.cpp ../src/Opcodes.h 
  ../src/Cpu.cpp ../src/Cpu.h 
  ../src/Ram.cpp ../src/Ram.h 
)

target_include_directories(GameBoyEmu PRIVATE src)

# Add the Rust cdylib
add_library(rust_lib SHARED IMPORTED)
set_target_properties(rust_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../gui/fast_emu_gui/target/release/libfast_emu_gui.so" 
)

# Link the Rust library to the main executable
target_link_libraries(GameBoyEmu PRIVATE rust_lib)
