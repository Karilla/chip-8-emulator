//
// Created by benoit on 01/08/2022.
//

#include <SDL2/SDL_syswm.h>
#include "screen.h"
#include "SDL2/SDL.h"
#include "stdbool.h"
#include "windows.h"

HWND getSDLWindowHandle(SDL_Window* win){
    SDL_SysWMinfo infoWindow;
    SDL_VERSION(&infoWindow.version);
    if(!SDL_GetWindowWMInfo(win, &infoWindow)){
        printf("Erroorr\n");
        exit(1);
    }
    return(infoWindow.info.win.window);
}

void ActivateMenu(HWND windowRef)
{
    HMENU hMenuBar = CreateMenu();
    HMENU hFile = CreateMenu();
    HMENU hEdit = CreateMenu();
    HMENU hHelp = CreateMenu();

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelp, "Help");

    AppendMenu(hFile, MF_STRING, 0, "Load ROM");
    AppendMenu(hFile, MF_STRING, 1, "Exit");

    AppendMenu(hEdit, MF_STRING, 2, "Configure Controls");

    AppendMenu(hHelp, MF_STRING, 3, "About");

    SetMenu(windowRef, hMenuBar);
}

void init_app(State* state, SDL_Window* window, SDL_Renderer* renderer, HWND* winHandle){

    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        exit(EXIT_FAILURE);
    }
    init_state(state);
    SDL_CreateWindowAndRenderer(640, 300, SDL_WINDOW_RESIZABLE, &window, &renderer);

    SDL_SetWindowTitle(window, "CHIP8-Emulator");

    *winHandle = getSDLWindowHandle(window);
    ActivateMenu(*winHandle);

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