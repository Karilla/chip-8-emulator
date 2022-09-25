//
// Created by benoit on 26/07/2022.
//

#ifndef REVISON_PRG2_EMULATOR_H
#define REVISON_PRG2_EMULATOR_H
#include "state.h"
#include "SDL2/SDL.h"

void load_program(State* state, const char* filename);

uint16_t fetch_instr(State* state);

void decode_instr(State* state, uint16_t instruction, SDL_Renderer** renderer, enum Control controlKey);

void clock_tick(SDL_Renderer** renderer, State* state, enum Control controlKey);

Uint32 timer_callback(Uint32 interval, void* params);

uint8_t decode_control_key(enum Control controlKey);

#endif //REVISON_PRG2_EMULATOR_H
