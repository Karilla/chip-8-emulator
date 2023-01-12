//
// Created by benoit on 06/08/2022.
//

#include "display.h"
#include "raylib.h"

const int PIXEL_SIZE = 10;

void create_grid(){
   BeginDrawing();
    for(int x = 0; x < 64;++x){
        for(int y = 0; y < 32; ++y){
            //create_rectangle(renderer,PIXEL_SIZE * x, 10 + PIXEL_SIZE * y, PIXEL_SIZE, PIXEL_SIZE, 0);
            DrawRectangle(PIXEL_SIZE * x, PIXEL_SIZE * y,PIXEL_SIZE,PIXEL_SIZE,WHITE);
        }
    }
    //SDL_RenderPresent(*renderer);
    EndDrawing();
}

void update_grid(State* state){
   BeginDrawing();
    for(int y = 0; y < 32;++y){
        for(int x = 0; x < 64; ++x){
            //create_rectangle(renderer,PIXEL_SIZE * x, 10 + PIXEL_SIZE * y, PIXEL_SIZE, PIXEL_SIZE, state->screen[x][y]);
           DrawRectangle(PIXEL_SIZE * x, PIXEL_SIZE * y,PIXEL_SIZE,PIXEL_SIZE,state->screen[x][y] ? BLACK : WHITE);
        }
    }
    //SDL_RenderPresent(*renderer);
    EndDrawing();
}