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

void display(State* state,uint8_t y, uint8_t x,uint8_t n, SDL_Renderer** renderer){
    int x_sprite = (state->V[x] & 63);
    int y_sprite = (state->V[y] & 31);
    state->V[15] = 0;
    uint8_t current_row;
    for(uint8_t row = 0; row < n; ++row){
        current_row = state->memory[state->index + row];
        for(uint8_t bit = 0; bit < 8; ++bit){

            if((current_row & 0x80) > 0){
                if(state->screen[x_sprite + bit][y_sprite] == 1){
                    state->screen[x_sprite + bit][y_sprite] = 0;
                    state->V[15] = 1;
                }
                else{
                    state->screen[x_sprite + bit][y_sprite] = 1;
                }
            }
                current_row <<= 1;
        }
        y_sprite++;
        if(x_sprite > 64 || y_sprite > 32){
            SDL_Log("Break\n");
            break;
        }
    }
}
