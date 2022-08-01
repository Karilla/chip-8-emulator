//
// Created by benoit on 01/08/2022.
//

#ifndef REVISON_PRG2_SCREEN_H
#define REVISON_PRG2_SCREEN_H
#include "SDL2/SDL.h"
#include "state.h"

void init_app(State* state, SDL_Window* window, SDL_Renderer* renderer);

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer* renderer);

#endif //REVISON_PRG2_SCREEN_H