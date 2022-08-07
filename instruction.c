//
// Created by benoit on 26/07/2022.
//

#include "instruction.h"


void jump(State* state, uint16_t address){
    state->PC = address;
}

void simple_add(State* state,uint8_t reg, uint8_t value){
    state->V[reg] += value;
}

void set_register(State* state,uint8_t reg, uint8_t value){
    state->V[reg] = value;
}

void set_index_register(State* state, uint16_t value){
    state->index = value;
}

void display(State* state, uint8_t n){

}