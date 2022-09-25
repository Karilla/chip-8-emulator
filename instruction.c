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

void display(State* state,uint8_t y, uint8_t x,uint8_t n){
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

void call_push(State* state, uint16_t address){
    push_stack(state,state->PC);
    state->PC = address;
}

void clear_screen(State* state){
    for(int x = 0; x < 64;++x){
        for(int y = 0; y < 32; ++y){
            state->screen[x][y] = 0;
        }
    }
}
void skip_if_vx_egal(State* state,uint8_t x, uint8_t value){
    if(state->V[x] == value){
        state->PC +=2;
    }
}

void skip_if_not_vx_egal(State* state, uint8_t x, uint8_t value){
    if(state->V[x] != value){
        state->PC +=2;
    }
}

void skip_if_vx_vy_egal(State* state, uint8_t x, uint8_t y){
    if(state->V[x] == state->V[y]){
        state->PC +=2;
    }
}

void skip_if_vx_vy_not_egal(State* state, uint8_t x, uint8_t y){
    if(state->V[x] != state->V[y]){
        state->PC +=2;
    }
}

void set(State* state, uint8_t x, uint8_t y){
    state->V[x] = state->V[y];
}

void or(State* state, uint8_t x, uint8_t y){
    state->V[x] |= state->V[y];
}

void and(State* state, uint8_t x, uint8_t y){
    state->V[x] &= state->V[y];
}

void xor(State* state, uint8_t x, uint8_t y){
    state->V[x] ^= state->V[y]   ;
}

void add_register(State* state, uint8_t x, uint8_t y){
    if((x > (UCHAR_MAX - y)) && (y > (UCHAR_MAX - x))){
        state->V[0xf] = 1;
    }
    state->V[0xF] = 0;
    state->V[x] += state->V[y];
}

void substract_register(State* state, uint8_t x, uint8_t y, bool mode){
    if(mode){
        if(state->V[x] > state->V[y]){
            state->V[0xF] = 1;
        }
        state->V[0xF] = 0;
        state->V[x] -= state->V[y];
    }
    else{
        if(state->V[y] > state->V[x]) {
            state->V[0xF] = 1;
        }
        state->V[0xF] = 0;
        state->V[x] = state->V[y] - state->V[x];
    }
}

void shift(State* state, uint8_t x, uint8_t y, bool direction){
    state->V[x] = state->V[y];
    if(direction){
        state->V[0xf] = 0;
        if((state->V[x] & 0x01) > 0){
            state->V[0xf] = 1;
        }
        state->V[x] >>= 1;
    } else{
        state->V[0xf] = 0;
        if((state->V[x] & 0x80) > 0) {
            state->V[0xf] = 1;
        }
        state->V[x] <<= 1;
    }
}

void jump_offset(State* state, uint16_t value){
    state->PC = state->V[0] + value;
}

void random(State* state,uint8_t reg, uint8_t modulo){
    state->V[reg] = rand() & modulo;
}

void skip_if_key(State* state, uint8_t x, uint8_t key){
   if(key == state->V[x]){
      state->PC += 2;
   }
}

void skip_if_not_key(State* state, uint8_t x, uint8_t key) {
   if(key != state->V[x]){
      state->PC += 2;
   }
}

void get_timer_value(State* state, uint8_t x){
   state->V[x] = state->delay_timer;
}

void set_timer_value(State* state, uint8_t x){
   state->delay_timer = state->V[x];
}

void set_sound_timer(State* state, uint8_t x){
   state->sound_timer = state->V[x];
}

void add_index(State* state, uint8_t x){
   state->index += state->V[x];
}

void get_key(State* state, uint8_t x, uint8_t key){
   if(key == 0){
      state->PC -= 2;
   }
   else{
      state->V[x] = key;
   }
}

void get_character(State* state, uint8_t x){
   state->index = 512 + state->V[x];
}

void binary_to_dec(State* state, uint8_t x){
   state->memory[state->index] = state->V[x] / 100;
   state->memory[state->index + 1] = (state->V[x] / 10) % 10;
   state->memory[state->index + 2] = state->V[x] % 10;
}

void store_memory(State* state,uint8_t x){
   for(uint8_t i = 0; i <= x; ++i){
      state->memory[state->index + i] = state->V[i];
   }
}

void load_memory(State* state, uint8_t x){
   for(uint8_t i = 0; i <= x; ++i){
      state->V[i] = state->memory[state->index + i];
   }
}