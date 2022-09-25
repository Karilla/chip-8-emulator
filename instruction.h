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

void display(State* state,uint8_t y, uint8_t x,uint8_t n);

void clear_screen(State* state);

void call_push(State* state, uint16_t address);

void skip_if_vx_egal(State* state,uint8_t x, uint8_t value);

void skip_if_not_vx_egal(State* state, uint8_t x, uint8_t value);

void skip_if_vx_vy_egal(State* state, uint8_t x, uint8_t y);

void skip_if_vx_vy_not_egal(State* state, uint8_t x, uint8_t y);

void set(State* state, uint8_t x, uint8_t y);

void or(State* state, uint8_t x, uint8_t y);

void and(State* state, uint8_t x, uint8_t y);

void xor(State* state, uint8_t x, uint8_t y);

void add_register(State* state, uint8_t x, uint8_t y);

void substract_register(State* state, uint8_t x, uint8_t y, bool mode);

void shift(State* state, uint8_t x, uint8_t y, bool direction);

void jump_offset(State* state, uint16_t value);

void random(State* state,uint8_t reg, uint8_t modulo);

void skip_if_key(State* state, uint8_t x, uint8_t key);

void skip_if_not_key(State* state, uint8_t x, uint8_t key);

void get_timer_value(State* state, uint8_t x);

void set_timer_value(State* state, uint8_t x);

void set_sound_timer(State* state, uint8_t x);

void add_index(State* state, uint8_t x);

void get_key(State* state, uint8_t x, uint8_t key);

void get_character(State* state, uint8_t x);

void binary_to_dec(State* state, uint8_t x);

#endif //REVISON_PRG2_INSTRUCTION_H
