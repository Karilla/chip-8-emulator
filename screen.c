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
#include "widget.h"


HWND getSDLWindowHandle(SDL_Window* win){
    SDL_SysWMinfo infoWindow;
    SDL_VERSION(&infoWindow.version);
    if(!SDL_GetWindowWMInfo(win, &infoWindow)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Erroorr\n");
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

    AppendMenu(hDebug,MF_STRING, ID_LAUNCHDEBUG, "Launch Debug Session");
    AppendMenu(hDebug,MF_STRING, ID_DUMP, "Dump Memory");
    AppendMenu(hDebug,MF_STRING, ID_STEP, "Step by Step");
    AppendMenu(hDebug,MF_STRING, ID_MEM, "Memory Viewer");
    AppendMenu(hDebug,MF_STRING, ID_STATE, "State Viewer");

    AppendMenu(hHelp, MF_STRING, ID_ABOUT, "About");



    EnableMenuItem(hMenuBar, ID_DUMP, MF_GRAYED);
    EnableMenuItem(hMenuBar, ID_STEP, MF_GRAYED);
    EnableMenuItem(hMenuBar, ID_MEM, MF_GRAYED);
    EnableMenuItem(hMenuBar, ID_STATE, MF_GRAYED);

    SetMenu(windowRef, hMenuBar);
}

void init_app(State* state, SDL_Window** window, SDL_Renderer** renderer, HWND* winHandle){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        exit(EXIT_FAILURE);
    }
    init_state(state);
    *window = SDL_CreateWindow("Test",500,200,640,330,SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    create_grid(renderer);
    SDL_SetWindowTitle(*window, "CHIP8-Emulator");
    *winHandle = getSDLWindowHandle(*window);
    SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void launch_poll_event(State* state, SDL_Window* window, SDL_Renderer** renderer, HWND winHandle){
    bool isRunning = true;
    ActivateMenu(winHandle);
    registerWindowsClass(window);
    HWND modal_debug_handle = NULL;
    bool isDebug = false;
    while (isRunning){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_USEREVENT:
                  clock_tick(renderer, state);
                    break;
                case SDL_SYSWMEVENT:
                    if(event.syswm.msg->msg.win.msg == WM_COMMAND){
                        if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_EXIT){
                            isRunning = false;
                        }
                        else if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_LOAD){
                            char* rom_path = get_rom_file(winHandle);
                            load_program(state,rom_path);
                            dump_memory(state,"test");
                            free(rom_path);
                            SDL_AddTimer(DELAY_OP,timer_callback,NULL);
                        }
                        else if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_LAUNCHDEBUG){
                            isDebug = true;
                            char* rom_path = get_rom_file(winHandle);
                            load_program(state,rom_path);
                            dump_memory(state,"test");
                            free(rom_path);
                            //activate_debug_menu(menu_handle);
                        }
                        else if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_ABOUT) {
                            if(!IsWindow(modal_debug_handle)){
                                modal_debug_handle = display_modal(winHandle);
                            }

                        }
                       else if(LOWORD(event.syswm.msg->msg.win.wParam) == ID_CONTROL){
                           ShowWindow(CreateWindowExA(WS_EX_WINDOWEDGE,NULL,NULL,WS_CHILD,50,50,300,200,winHandle,NULL,NULL,NULL),4);

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
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a File, yo!";
    ofn.lpstrInitialDir = "..";
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);
    char* file_path = calloc(MAX_PATH,sizeof(char));
    strncpy(file_path,ofn.lpstrFile, strlen(ofn.lpstrFile));
    printf("%s\n",ofn.lpstrFile);
    return file_path;
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wp,LPARAM lp){
    switch(msg){
        case WM_CLOSE:
            SDL_Log("Bye\n");
            DestroyWindow(hWnd);
            break;
        case WM_CREATE:
            SDL_Log("Test\n");
            create_table(hWnd);
            break;
        default:
            return DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void registerWindowsClass(SDL_Window* win){
    SDL_SysWMinfo infoWindow;
    SDL_VERSION(&infoWindow.version);
    if(!SDL_GetWindowWMInfo(win, &infoWindow)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Erroorr\n");
        exit(1);
    }
    WNDCLASSW dialog = {0};
    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    dialog.hCursor = LoadCursor(NULL,IDC_ARROW);
    dialog.hInstance = infoWindow.info.win.hinstance;
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProc;

    RegisterClassW(&dialog);
}

HWND display_modal(HWND winHandle){
    return CreateWindowExW(0,L"myDialogClass",L"Debug", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400 ,400,200,200,winHandle,NULL,NULL,NULL);
    //InitCommonControls();
}

void create_table(HWND winHandle){
    //HWND label1 = create_label(winHandle,1,1,50,50,"Test");
   //set_Label_text(label1,"Hello world");
   create_edit(winHandle,10,10,NULL,1);
}