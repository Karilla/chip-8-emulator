//
// Created by benoit on 26/07/2022.
//

#include "emulator.h"
#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"

#define MASK_12BITS 0x0FFF
#define MASK_8BITS 0x00FF
#define MASK_4BITS 0x000F

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

void decode_instr(State* state, uint16_t instruction, SDL_Renderer** renderer,enum Control controlKey){
    switch(instruction >> 12){
        case 0x0:
            if((instruction & MASK_12BITS) == 0x0E0){
                SDL_Log("Effacage de l'ecran\n");
                clear_screen(state);
                update_grid(renderer, state);
            }
            if((instruction & MASK_12BITS) == 0x0EE){
                state->PC = pop_stack(state);
                SDL_Log("Popped from the stack\n");
            }
            break;
        case 0x1:
            jump(state,(instruction & ~0xF000));
            SDL_Log("Jump\n");
            break;
        case 0x2:
            call_push(state, instruction & MASK_12BITS);
            SDL_Log("Jump and push stack\n");
            break;
        case 0x3:
            skip_if_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            break;
        case 0x4:
            skip_if_not_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            break;
        case 0x5:
            skip_if_vx_vy_egal(state,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            break;
        case 0x6:
            set_register(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            SDL_Log("Set %d at register %d\n",instruction & MASK_8BITS, (instruction >> 8) & MASK_4BITS);
            break;
        case 0x7:
            simple_add(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
             SDL_Log("Add %d at v%d\n", instruction & MASK_8BITS,(instruction >> 8) & MASK_4BITS);
            break;
        case 0x8:
            switch(instruction & MASK_4BITS){
                case 0:
                   set(state, (instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                   break;
                case 1:
                  or(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                  break;
                case 2:
                   and(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                  break;
                case 3:
                   xor(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                  break;
                case 4:
                   add_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                  break;
                case 5:
                   substract_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS, true );
                    break;
                case 6:
                   shift(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS,true);
                    break;
                case 7:
                   substract_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS, false );
                    break;
                case 0xE:
                   shift(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS,false);
                  break;
                default:
                    break;
            }
            break;
        case 0x9:
            skip_if_vx_vy_not_egal(state,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            break;
        case 0xA:
            set_index_register(state, instruction & MASK_12BITS);
            SDL_Log("Set index register at %d\n", instruction & MASK_12BITS);
            break;
        case 0xB:
           jump_offset(state,instruction & MASK_12BITS);
            break;
        case 0xC:
           random(state, (instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            break;
        case 0xD:
            SDL_Log("Display with x = %d, y = %d, et n = %d\n",(instruction >> 8) & MASK_4BITS ,(instruction >> 4) & MASK_4BITS,instruction & MASK_4BITS);
            display(state,(instruction >> 4) & MASK_4BITS, (instruction >> 8) & MASK_4BITS, instruction & MASK_4BITS);
            update_grid(renderer, state);
            break;
        case 0xE:
           if((instruction & MASK_8BITS ) == 0x65){
              skip_if_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
           }
           else if((instruction & MASK_8BITS) == 0xA1){
              skip_if_not_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
           }
            break;
        case 0xF:
           switch(instruction & MASK_8BITS){
              case 0x07:
                 get_timer_value(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x15:
                 set_timer_value(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x18:
                 set_sound_timer(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x1E:
                 add_index(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x0A:
                 get_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
                 break;
              case 0x29:
                 get_character(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x33:
                 binary_to_dec(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x55:
                 store_memory(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x65:
                 load_memory(state,(instruction >> 8) & MASK_4BITS);
                 break;
              default:
                 break;
           }
            break;
        default:
           SDL_Log("Instruction not implemented yet : %04x\n",instruction);
            break;
    }
}

void clock_tick(SDL_Renderer** renderer, State* state, enum Control controlKey){
    Uint16 instr = fetch_instr(state);
    decode_instr(state,instr,renderer,controlKey);
}

Uint32 timer_callback(Uint32 interval, void* params){
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

uint8_t decode_control_key(enum Control controlKey){
   return (uint8_t) controlKey;
}