//
// Created by benoit on 01/08/2022.
//

#include "screen.h"
#include "SDL2/SDL.h"
#include "stdbool.h"

#define HEIGHT 320
#define WIDTH 640

void init_app(State* state, SDL_Window* window, SDL_Renderer* renderer){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        exit(EXIT_FAILURE);
    }

    init_state(state);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);

    SDL_SetWindowTitle(window, "CHIP8-Emulator");
}

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer* renderer){
    bool isRunning = true;
    while (isRunning){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        }
    }
}