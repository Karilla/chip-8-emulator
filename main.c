
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include <windows.h>
#include "state.h"
#include "emulator.h"
#include "debug.h"
#include "screen.h"

int main(int argc, char *argv[]){

    State state;
    SDL_Window* window;
    SDL_Renderer* renderer;

    init_app(&state, window, renderer);

    launch_poll_event(&state,window,renderer);
}