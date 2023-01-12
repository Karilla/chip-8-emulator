//
// Created by benoit on 01/08/2022.
//

#ifndef REVISON_PRG2_SYSTEM_H
#define REVISON_PRG2_SYSTEM_H
#include "state.h"

void registerWindowsClass(SDL_Window* window);

HWND display_modal(HWND winHandle);

void init_app(State* state, SDL_Window** window, SDL_Renderer** renderer,HWND* winHandle);

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer** renderer, HWND winHandle);

HMENU ActivateMenu(HWND windowRef);

HWND getSDLWindowHandle(SDL_Window* win);

char* get_rom_file(HWND win_handle);

void create_table(HWND winHandle);
#endif //REVISON_PRG2_SYSTEM_H
