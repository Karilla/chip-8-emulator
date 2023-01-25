#ifndef REVISON_PRG2_EMULATOR_H
#define REVISON_PRG2_EMULATOR_H
#include "state.h"

int load_program(State* state, const char* filename);

uint16_t fetch_instr(State* state);

void decode_instr(State* state, uint16_t instruction, enum Control controlKey);

void update_timer(State* state);

#endif //REVISON_PRG2_EMULATOR_H
