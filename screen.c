//
// Created by benoit on 01/08/2022.
//

#include <SDL2/SDL_syswm.h>
#include "screen.h"
#include "SDL2/SDL.h"
#include "stdbool.h"
#include "constant .h"
#include <commdlg.h>
#include "windows.h"
#include <tchar.h>
#include "debug.h"
#include "display.h"
#include "emulator.h"

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
    HMENU hDebug = CreateMenu();
    HMENU hHelp = CreateMenu();

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "Edit");
    AppendMenu(hMenuBar, MF_POPUP,(UINT_PTR)hDebug, "Debug");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelp, "Help");

    AppendMenu(hFile, MF_STRING, ID_LOAD, "Load ROM");
    AppendMenu(hFile, MF_STRING, ID_EXIT, "Exit");

    AppendMenu(hEdit, MF_STRING, ID_CONTROL, "Configure Controls");

    AppendMenu(hDebug,MF_STRING, ID_DUMP, "Dump Memory");
    AppendMenu(hDebug,MF_STRING, ID_STEP, "Step by Step");
    AppendMenu(hDebug,MF_STRING, ID_MEM, "Memory Viewer");
    AppendMenu(hDebug,MF_STRING, ID_STATE, "State Viewer");

    AppendMenu(hHelp, MF_STRING, ID_ABOUT, "About");

    SetMenu(windowRef, hMenuBar);
}

void init_app(State* state, SDL_Window** window, SDL_Renderer** renderer, HWND* winHandle){

    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        exit(EXIT_FAILURE);
    }
    init_state(state);
    *window = SDL_CreateWindow("Test",20,20,640,330,SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    create_grid(renderer);
    //create_rectangle(renderer,30,50,50,50, 1);
    SDL_SetWindowTitle(*window, "CHIP8-Emulator");
    *winHandle = getSDLWindowHandle(*window);
    ActivateMenu(*winHandle);
    //Enable WinAPI Events Processing
    SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer* renderer, HWND winHandle){
    bool isRunning = true;
    while (isRunning){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_SYSWMEVENT:
                    if(event.syswm.msg->msg.win.msg == WM_COMMAND){
                        if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_EXIT){
                            isRunning = false;
                        }
                        else if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_LOAD){
                            load_program(state,get_rom_file(winHandle));
                            dump_memory(state,"test");
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

char* get_rom_file(HWND win_handle){
    char filename [MAX_PATH];

    OPENFILENAME ofn;
    memset(filename,0,MAX_PATH);
    ZeroMemory( &ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = win_handle;
    ofn.lpstrFilter = "Chip-8 Rom\0*.ch8\0Any File\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a File, yo!";
    ofn.lpstrInitialDir = "C:\\Users\\benoit\\Documents\\Dev-Project\\cpp\\Revison-prg2";
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);
    return ofn.lpstrFile;
}