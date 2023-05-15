cmake_minimum_required(VERSION 3.21)
project(Chip-8-Emulator C)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)
set_property(GLOBAL PROPERTY C_STANDARD 11)
set(CMAKE_C_FLAGS -std=c11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_executable(Chip-8-Emulator src/main.c src/state.c src/state.h src/emulator.c src/emulator.h src/debug.c src/debug.h src/instruction.c src/instruction.h src/system.c src/system.h src/display.c src/display.h "src/constant .h" src/widget.c src/widget.h src/log.c src/log.h src/gui.c src/gui.h src/raygui.h src/raygui.c src/gui.c src/state_machine.c src/state_machine.h)
SET(CMAKE_C_FLAGS_DEBUG "-O0")

target_link_libraries(Chip-8-Emulator raylib)
