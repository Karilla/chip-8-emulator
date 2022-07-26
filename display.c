//
// Created by benoit on 06/08/2022.
//

#include "display.h"
#include "SDL2/SDL.h"

const int PIXEL_SIZE = 10;

void create_rectangle(SDL_Renderer** renderer, int x, int y , int w, int h, bool on_off){
    SDL_Rect rect = {x,y,w,h};
    int color = (int)on_off * 255;
    SDL_SetRenderDrawColor(*renderer,0,color,0,255);
    SDL_RenderFillRect(*renderer,&rect);
}

void create_grid(SDL_Renderer** renderer){
    for(int x = 0; x < 64;++x){
        for(int y = 0; y < 32; ++y){
            create_rectangle(renderer,PIXEL_SIZE * x, 10 + PIXEL_SIZE * y, PIXEL_SIZE, PIXEL_SIZE, 0);
        }
    }
    SDL_RenderPresent(*renderer);
}

void update_grid(SDL_Renderer** renderer, State* state){
    for(int y = 0; y < 32;++y){
        for(int x = 0; x < 64; ++x){
            create_rectangle(renderer,PIXEL_SIZE * x, 10 + PIXEL_SIZE * y, PIXEL_SIZE, PIXEL_SIZE, state->screen[x][y]);
        }
    }
    SDL_RenderPresent(*renderer);
}