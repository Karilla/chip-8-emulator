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
    bool isDebug = false;
    if(argc <= 1){
        printf("No argument provided... Started without launching game\n");
        argument = false;
    }
    printf("%s\n",argv[1]);
    if(argc == 3 && (strcmp(argv[2],"-debug") == 0)){
       isDebug = true;
    }
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
        process_input(&state);
        ClearBackground(BLACK);
        if(sys_clock_tick() && isRunning && !isDebug){
            decode_instr(&state, fetch_instr(&state), state.controlKey);
        }
        if(sys_timer_tick() && isRunning && !isDebug){
            update_timer(&state);
        }

        update_grid(&state);
        DrawFPS(0,0);
        char string[512];
        for(int i = 0; i < 16; i++){
           snprintf(string,sizeof(string),"V%d = %d", i, state.V[i]);
           DrawText(string,640 + 10, 20*(i+1) + 2,21,RED);
        }
       snprintf(string,sizeof(string),"Timer = %d", state.delay_timer);
       DrawText(string,640 + 10, 20*(16+1) + 2,21,RED);
        EndDrawing();
    }
}