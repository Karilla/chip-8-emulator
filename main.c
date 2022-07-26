
#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "emulator.h"
#include "debug.h"

int main(int argc, char *argv[])
{
    State state;
    init_state(&state);
    load_program(&state,"../IBM Logo.ch8");
    //print_state(&state);
    for(int x = 0; x < 20;++x){
        decode_instr(&state, fetch_instr(&state));
    }
    dump_memory(&state,"../dump.txt");
    return 0;
}