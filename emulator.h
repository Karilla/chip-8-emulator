//
// Created by benoit on 26/07/2022.
//

#ifndef REVISON_PRG2_EMULATOR_H
#define REVISON_PRG2_EMULATOR_H
#include "state.h"

void load_program(State* state, const char* filename);

uint16_t fetch_instr(State* state);

void decode_instr(State* state, uint16_t instruction, enum Control controlKey);

uint8_t decode_control_key(enum Control controlKey);

void update_timer(State* state);

#endif //REVISON_PRG2_EMULATOR_H
