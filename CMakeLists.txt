cmake_minimum_required(VERSION 3.16)
project(GameBoyEmu)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0156 NEW)

add_executable(GameBoyEmu 
  ../src/main.cpp 
  ../src/core/Emulator.cpp ../src/core/Emulator.h
  ../src/core/GameBoy.cpp ../src/core/GameBoy.h
  ../src/core/Cpu.cpp ../src/core/Cpu.h 
  ../src/core/DataBus.cpp ../src/core/DataBus.h
  ../src/core/Ppu.cpp ../src/core/Ppu.h
  ../src/core/Ram.cpp ../src/core/Ram.h 
  ../src/instructions/Opcodes.cpp ../src/instructions/Opcodes.h 
  ../src/instructions/FetchDecode.cpp ../src/instructions/FetchDecode.h
)

target_include_directories(GameBoyEmu PRIVATE src)

add_library(rust_lib SHARED IMPORTED)
set_target_properties(rust_lib PROPERTIES
    IMPORTED_LOCATION "../gui/fast_emu_gui/target/release/libfast_emu_gui.dylib"
)

target_link_libraries(GameBoyEmu PRIVATE rust_lib)