//
// Created by benoit on 26/07/2022.
//

#include "instruction.h"

void jump(State* state, uint16_t address){
    state->PC = address;
}