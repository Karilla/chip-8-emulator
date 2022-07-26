//
// Created by benoit on 26/07/2022.
//

#include "debug.h"
#include <stdio.h>

void dump_memory(State* state, const char* filename){
    FILE* dump_file = fopen(filename, "w");
    fprintf(dump_file,"\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\tA\tB\tC\tD\tE\tF\n");
    for(int i = 0; i < 4096; i+=16){
        fprintf(dump_file,"%03x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t"
                          "%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\n",i
                          ,state->memory[i],state->memory[i+1],state->memory[i+2],state->memory[i+3],state->memory[i+4]
                          ,state->memory[i+5],state->memory[i+6],state->memory[i+7],state->memory[i+8],state->memory[i+9]
                          ,state->memory[i+10],state->memory[i+11],state->memory[i+12],state->memory[i+13],state->memory[i+14]
                          ,state->memory[i+5]);
    }
    fclose(dump_file);
}