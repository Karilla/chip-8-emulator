#include "display.h"
#include "raylib.h"

const int PIXEL_SIZE = 10;

void create_grid(){
    BeginDrawing();
    for(int x = 0; x < 64;++x){
        for(int y = 0; y < 32; ++y){
            DrawRectangle(PIXEL_SIZE * x, 30 +PIXEL_SIZE * y,PIXEL_SIZE,PIXEL_SIZE,BLACK);
        }
    }
    EndDrawing();
}

void update_grid(State* state){
    for(int y = 0; y < 32;++y){
        for(int x = 0; x < 64; ++x){
           DrawRectangle(PIXEL_SIZE * x, 30 +PIXEL_SIZE * y,PIXEL_SIZE,PIXEL_SIZE,state->screen[x][y] ? WHITE : BLACK);
        }
    }
}