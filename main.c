
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include <windows.h>
#include "state.h"
#include "emulator.h"
#include "debug.h"
#include "display.h"
#include "screen.h"

int main(int argc, char *argv[]){

    printf("Test\n");
    State state;
    HWND windowHandle;
    SDL_Window* window;
    SDL_Renderer* renderer;

    init_app(&state, &window, &renderer,&windowHandle);

    launch_poll_event(&state,window,renderer, windowHandle);
}

/*
 * while (isRunning)
{
    SDL_PollEvent(&mainEvent);
    switch (mainEvent.type)
    {
    case SDL_WINDOWEVENT_CLOSE:
        mainEvent.type = SDL_QUIT;
        SDL_PushEvent(&mainEvent);
        break;
    case SDL_SYSWMEVENT:
        if (mainEvent.syswm.msg->msg.win.msg == WM_COMMAND)
        {
            if (LOWORD(mainEvent.syswm.msg->msg.win.wParam) == ID_EXIT)
            {
                isRunning = false;
            }
        }
        break;
    case SDL_QUIT:
        isRunning = false;
        break;
    };
}
 */