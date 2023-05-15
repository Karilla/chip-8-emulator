#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "system.h"
#include "gui.h"
#include "emulator.h"
#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "constant .h"

int main(int argc, char *argv[]){
    State state;
    uint8_t programState;
   char* log = (char*)calloc(512, sizeof (char ));
    if(argc <= 1){
        programState = IDLE;
        init_game(&state, GAME_WIDTH, GAME_HEIGHT, false);
       printf("No argument provided... Started without launching game\n");
    }
    else if(argc == 2){
       programState = RUNNING;
       init_game(&state, GAME_WIDTH, GAME_HEIGHT, false);
       printf("Started in running mode with file %s\n", argv[1]);
    }
    else if(argc == 3 && (strcmp(argv[2],"--debug") == 0)){
       programState = DEBUGING;
       init_game(&state,GAME_WIDTH + DEBUGER_WIDTH, GAME_HEIGHT + DEBUGER_HEIGHT, true);
       printf("Starting in debug mode.... \n");
    }
    else{
       programState = ERROR;
    }
    if(programState == RUNNING || programState == DEBUGING){
        if(load_program(&state, argv[1]) == -1){
            printf("Error while loading program...\n");
            programState = ERROR;
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
                decode_instr(&state, fetch_instr(&state), state.controlKey);
             }
             if(sys_timer_tick()){
                update_timer(&state);
             }
             update_grid(&state);
             break;
          case DEBUGING:

               if(IsKeyPressed(KEY_SPACE)){
                  log = decode_instr(&state, fetch_instr(&state), state.controlKey);
                  update_timer(&state);
               }
             DrawText(log,10,430,21,RED);
             break;
          case ERROR:
             DrawText("ERROR OCCURED PLS RESTART THE PROGRAM",10,200,50,RED);
             break;
           case MENU:
               break;
          default:
             break;
       }

       DrawFPS(0,0);
       draw_state(640 ,20,21,&state);
       update_grid(&state);
       EndDrawing();
    }
    free(log);
}