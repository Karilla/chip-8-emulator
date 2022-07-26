//
// Created by benoit on 26/07/2022.
//

#ifndef REVISON_PRG2_EMULATOR_H
#define REVISON_PRG2_EMULATOR_H
#include "state.h"

void load_program(State* state, const char* filename);

uint16_t fetch_instr(State* state);
#endif //REVISON_PRG2_EMULATOR_H
