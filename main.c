#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t getNanosecond(void);

int main(int argc, char *argv[]){
    printf("%d\n",argc);
    InitWindow(800,500, "Some test");
    SetExitKey(0);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
}