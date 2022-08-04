cmake_minimum_required(VERSION 3.21)
project(Revison_prg2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH "E:\\_DL\\SDL2-devel-2.0.22-mingw\\SDL2-2.0.22\\x86_64-w64-mingw32")
set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include)
find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIR})
add_executable(Revison_prg2 main.c state.c state.h emulator.c emulator.h debug.c debug.h instruction.c instruction.h screen.c screen.h)
SET(CMAKE_C_FLAGS_DEBUG "-O0")

target_link_libraries(Revison_prg2 ${SDL2_LIBRARY} )
