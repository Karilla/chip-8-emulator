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

add_executable(Chip-8-Emulator main.c state.c state.h emulator.c emulator.h debug.c debug.h instruction.c instruction.h system.c system.h display.c display.h "constant .h" widget.c widget.h log.c log.h gui.c gui.h raygui.h raygui.c gui.c state_machine.c state_machine.h)
SET(CMAKE_C_FLAGS_DEBUG "-O0")

target_link_libraries(Chip-8-Emulator raylib)
