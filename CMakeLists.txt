cmake_minimum_required(VERSION 3.21)
project(Revison_prg2 C)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH "C:\\SDL2-2.0.22\\x86_64-w64-mingw32")
set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include)
find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIR})
add_executable(Revison_prg2 main.c state.c state.h emulator.c emulator.h debug.c debug.h instruction.c instruction.h screen.c screen.h display.c display.h "constant .h" widget.c widget.h)
SET(CMAKE_C_FLAGS_DEBUG "-O0")

target_link_libraries(Revison_prg2 ${SDL2_LIBRARY} raylib)
