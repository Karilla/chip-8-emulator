//
// Created by benoit on 26/07/2022.
//

#include "emulator.h"
#include <stdio.h>
#include <stdlib.h>

void load_program(State* state, const char* filename){
    FILE* program_file = fopen(filename, "rb");
    if(!program_file){
        printf("Cannot open %s ! Try again>>\n", filename);
        return;
    }

    fseek(program_file, 0l, SEEK_END);
    int size = ftell(program_file);
    rewind(program_file);

    for(int i = 0; i < size; ++i){
        state->memory[0x200 + i] = getc(program_file);
    }

    fclose(program_file);
    printf("Program loaded successfully\n");
}

uint16_t fetch_instr(State* state){
    uint16_t temp = (state->memory[state->PC]) << 8;
    temp |= state->memory[state->PC + 1];
    state->PC +=2;
    return temp;
}

void decode_instr(State* state, uint16_t instruction){
    switch(instruction >> 12){
        case 0x0:
            printf("Effacage de l'ecran\n");
            break;
        case 0x1:
            printf("Jump\n");
            break;
        case 0x6:
            printf("set register\n");
            break;
        case 0x7:
            printf("Add value\n");
            break;
        case 0xA:
            printf("Set index register\n");
            break;
        case 0xD:
            printf("Display/Draw\n");
            break;
        default:
            printf("Instruction not implemented yet\n");
            break;
    }
}