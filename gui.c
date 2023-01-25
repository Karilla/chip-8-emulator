#include "raylib.h"
#include "gui.h"
#include "display.h"

void init_window(const int width, const int height, char* title){
    InitWindow(width, height, title);
    SetExitKey(0);
    create_grid();
}