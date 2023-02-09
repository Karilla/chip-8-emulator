#include "state.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void init_state(State* state){
    state->PC = 0x200;
    state->index = 0;
    state->delay_timer = 0;
    state->sound_timer = 0;
    state->stack_pointer = 4094;
    state->controlKey = NO_KEYS;
    memset(state->memory,0,4096);
    memset(state->V,0,16);
    memset(state->stack,0,16);
    //memset(state->screen,0,32*64);
    for(int x = 0; x < 64;++x){
        for(int y = 0; y < 32; ++y){
            state->screen[x][y] = 0;
        }
    }
    load_font(state,std_font);
    srand(time(NULL));
}

void print_state(State* state){
    printf("PC \t=\t%d\n",state->PC);
    printf("Index \t=\t%d\n",state->index);
    printf("Stack pointer \t=\t%d\n",state->stack_pointer);
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

void push_stack(State* state, uint16_t address){
    state->memory[state->stack_pointer] = (uint8_t) (address >> 8);
    state->memory[state->stack_pointer + 1] = (uint8_t) address ;
    printf("DEEEEEEEEEEE %d\n", address);
    state->stack_pointer -= 2;
}

uint16_t pop_stack(State* state){
    state->stack_pointer += 2;
    uint16_t instr = (state->memory[state->stack_pointer] << 8);
    instr |= state->memory[state->stack_pointer + 1];
    printf("LEEEEEEEEEEE %d\n", instr);
    return instr;
}

void set_key(State* state, enum Control key){
    state->controlKey = key;
}