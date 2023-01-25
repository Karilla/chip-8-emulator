#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "system.h"
#include "emulator.h"
#include "display.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    bool argument = true;
    bool isRunning = false;
    if(argc <= 1){
        printf("No argument provided... Started without launching game\n");
        argument = false;
    }
    printf("%s\n",argv[1]);
    State state;
    init_game(&state);
    if(argument){
        if(load_program(&state, argv[1]) == -1){
            printf("Error while loading program...\n");
        }
        printf("Program Loaded...\n");
        isRunning = true;
    }
    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);
        if(sys_clock_tick() && isRunning){
            decode_instr(&state, fetch_instr(&state), NO_KEYS);
        }
        if(sys_timer_tick() && isRunning){
            update_timer(&state);
        }

        update_grid(&state);
        process_input(&state);
        EndDrawing();
    }
}