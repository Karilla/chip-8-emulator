#ifndef REVISON_PRG2_SYSTEM_H
#define REVISON_PRG2_SYSTEM_H
#include "state.h"

State* init_game();

void process_input(State* state);

int sys_clock_tick(void);

int sys_timer_tick(void);

#endif //REVISON_PRG2_SYSTEM_H
