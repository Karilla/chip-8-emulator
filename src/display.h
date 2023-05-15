#ifndef REVISON_PRG2_DISPLAY_H
#define REVISON_PRG2_DISPLAY_H
#include "state.h"
#include <stdbool.h>

void create_rectangle(int x, int y , int w, int h, bool on_off);

void create_grid();

void update_grid(State* state);

#endif //REVISON_PRG2_DISPLAY_H
