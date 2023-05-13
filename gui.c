#include "raylib.h"
#include "gui.h"
#include "display.h"

#define STRING_SIZE 258

const int STEP_Y_DEBUG = 20;

void init_window(const int width, const int height, char* title){
    InitWindow(width, height, title);
    SetExitKey(0);
    create_grid();
}

void draw_state(int x, int y, int font_size, State* state){
   char string[STRING_SIZE];
   snprintf(string, sizeof(string),"Pc = %d", state->PC);
   DrawText(string,x,y,font_size,RED);
   y+= STEP_Y_DEBUG;
   snprintf(string, sizeof(string),"Stack pointer = %d", state->stack_pointer);
   DrawText(string,x,y,font_size,RED);
   y+= STEP_Y_DEBUG;
   for(int i = 0; i < 16; i++){
      snprintf(string,sizeof(string),"V%d = %d", i, state->V[i]);
      DrawText(string,x,y,font_size,RED);
      y+= STEP_Y_DEBUG;
   }
   snprintf(string, sizeof(string),"Delay Timer = %d", state->delay_timer);
   DrawText(string,x,y,font_size,RED);
   y+= STEP_Y_DEBUG;
   snprintf(string, sizeof(string),"Sound Timer = %d", state->sound_timer);
   DrawText(string,x,y,font_size,RED);
}