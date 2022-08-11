//
// Created by benoit on 26/07/2022.
//

#ifndef REVISON_PRG2_INSTRUCTION_H
#define REVISON_PRG2_INSTRUCTION_H
#include "SDL2/SDL.h"
#include "state.h"
#include <inttypes.h>

void jump(State* state, uint16_t address);

void simple_add(State* state,uint8_t reg, uint8_t value);

void set_register(State* state,uint8_t reg, uint8_t value);

void set_index_register(State* state, uint16_t value);

void update_scren(State* state, uint8_t n, SDL_Renderer** renderer);

#endif //REVISON_PRG2_INSTRUCTION_H
