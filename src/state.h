#ifndef REVISON_PRG2_STATE_H
#define REVISON_PRG2_STATE_H
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

enum Control{
   KEY_1S,
   KEY_2S,
   KEY_3S,
   KEY_4S,
   KEY_QS,
   KEY_WS,
   KEY_ES,
   KEY_RS,
   KEY_AS,
   KEY_SS,
   KEY_DS,
   KEY_FS,
   KEY_YS,
   KEY_XS,
   KEY_CS,
   KEY_VS,
   NO_KEYS,
   KEY_SPACES
};

typedef struct State{
    uint8_t memory[4096];
    uint16_t PC;
    uint16_t index;
    uint16_t stack[16];
    uint16_t stack_pointer;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t V[16];
    int screen[64][32];
    enum Control controlKey;
}State;



static uint8_t std_font[80] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                        0x20, 0x60, 0x20, 0x20, 0x70, // 1
                        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                        0xF0, 0x80, 0xF0, 0x80, 0x80};// F

void init_state(State* state);

void print_state(State* state);

void push_stack(State* state, uint16_t address);

uint16_t pop_stack(State* state);

void load_font(State* state,const uint8_t* font);

void set_key(State* state, enum Control key);
#endif //REVISON_PRG2_STATE_H
