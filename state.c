//
// Created by benoit on 26/07/2022.
//
#include "state.h"
#include <string.h>
#include <stdio.h>

void init_state(State* state){
    state->PC = 0x200;
    state->index = 0;
    state->delay_timer = 0;
    state->sound_timer = 0;
    state->stack_pointer = 0;
    memset(state->memory,0,4096);
    memset(state->V,0,16);
    memset(state->stack,0,16);
    load_font(state,std_font);
}

void print_state(State* state){
    printf("PC \t=\t%d\n",state->PC);
    printf("Index \t=\t%d\n",state->index);
    printf("Stack pointer \t=\t&d\n",state->stack_pointer);
    printf("Delay Timer \t=\t%d\n",state->delay_timer);
    printf("Sound Timer \t=\t%d\n",state->sound_timer);
    for(int i = 0; i < 15;++i){
        printf("V%3d\t=\t%d\n",i,state->V[i]);
    }
    printf("VF\t=\t%d\n",state->V[15]);
}

void load_font(State* state,const uint8_t* font){
    for(uint16_t i = 0; i < (0x09f - 0x050);++i){
        state->memory[0x050 + i] = font[i];
    }
}