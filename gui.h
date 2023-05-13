#ifndef REVISON_PRG2_GUI_H
#define REVISON_PRG2_GUI_H

#include "state.h"

void init_window(const int width, const int height, char* title);

void draw_state(int x, int y, int font_size, State* state);

#endif //REVISON_PRG2_GUI_H

