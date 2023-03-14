#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "system.h"
#include "emulator.h"
#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "constant .h"

int main(int argc, char *argv[]){
    State state;
    uint8_t programState;
    if(argc <= 1){
        printf("No argument provided... Started without launching game\n");
        programState = IDLE;
        init_game(&state, GAME_WIDTH, GAME_HEIGHT, false);
    }
    else if(argc == 2){
       programState = RUNNING;
       init_game(&state, GAME_WIDTH, GAME_HEIGHT, false);
    }
    else if(argc == 3 && (strcmp(argv[2],"--debug") == 0)){
       programState = DEBUGING;
       init_game(&state,GAME_WIDTH + DEBUGER_WIDTH, GAME_HEIGHT, true);
    }
    else{
       programState = ERROR;
    }
    if(programState == RUNNING || programState == DEBUGING){
        if(load_program(&state, argv[1]) == -1){
            printf("Error while loading program...\n");
        }
        printf("Program Loaded...\n");
    }
    while(!WindowShouldClose()){
       process_input(&state);
       BeginDrawing();
       ClearBackground(BLACK);
       switch (programState) {
          case IDLE:
              if(GuiButton((Rectangle){0,0,200,20},"Choose a file ")){
                  programState = ERROR;
              }
             break;
          case RUNNING:
             if(sys_clock_tick()){
                 "%s",decode_instr(&state, fetch_instr(&state), state.controlKey);
             }
             if(sys_timer_tick()){
                update_timer(&state);
             }
             update_grid(&state);
             break;
          case DEBUGING:
             break;
          case ERROR:
             DrawText("ERROR OCCURED PLS RESTARD THE PROGRAM",10,200,50,RED);
             break;
           case MENU:
               break;
          default:
             break;
       }

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