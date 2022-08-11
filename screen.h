//
// Created by benoit on 01/08/2022.
//

#ifndef REVISON_PRG2_SCREEN_H
#define REVISON_PRG2_SCREEN_H
#include "SDL2/SDL.h"
#include "state.h"

void init_app(State* state, SDL_Window** window, SDL_Renderer** renderer,HWND* winHandle);

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer* renderer, HWND winHandle);

void ActivateMenu(HWND windowRef);

HWND getSDLWindowHandle(SDL_Window* win);

char* get_rom_file(HWND win_handle);

#endif //REVISON_PRG2_SCREEN_H
