//
// Created by benoit on 06/08/2022.
//

#ifndef REVISON_PRG2_DISPLAY_H
#define REVISON_PRG2_DISPLAY_H
#include "SDL2/SDL.h"
#include "state.h"
#include <stdbool.h>

void create_rectangle(SDL_Renderer** renderer, int x, int y , int w, int h, bool on_off);

void create_grid(SDL_Renderer** renderer);

#endif //REVISON_PRG2_DISPLAY_H
