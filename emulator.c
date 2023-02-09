#include "emulator.h"
#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "debug.h"

#define MASK_12BITS 0x0FFF
#define MASK_8BITS 0x00FF
#define MASK_4BITS 0x000F

int load_program(State* state, const char* filename){
    FILE* program_file = fopen(filename, "rb");
    if(!program_file){
        printf("Cannot open %s ! Try again>>\n", filename);
        return -1;
    }

    fseek(program_file, 0l, SEEK_END);
    int size = ftell(program_file);
    rewind(program_file);

    for(int i = 0; i < size; ++i){
        state->memory[0x200 + i] = getc(program_file);
    }

    fclose(program_file);
    printf("Program loaded successfully\n");
    return 0;
}


uint16_t fetch_instr(State* state){
    uint16_t temp = (state->memory[state->PC]) << 8;
    temp |= state->memory[state->PC + 1];
    state->PC +=2;
    return temp;
}

void decode_instr(State* state, uint16_t instruction,enum Control controlKey){
    printf("Control Key debuged = %d\n",controlKey);
    switch(instruction >> 12){
        case 0x0:
            if((instruction & MASK_12BITS) == 0x0E0){
                printf("Effacage de l'ecran\n");
                clear_screen(state);
                update_grid(state);
            }
            if((instruction & MASK_12BITS) == 0x0EE){
                state->PC = pop_stack(state);
                printf("Popped from the stack\n");
            }
            break;
        case 0x1:
            jump(state,(instruction & ~0xF000));
            printf("Jump\n");
            break;
        case 0x2:
            call_push(state, instruction & MASK_12BITS);
            printf("Jump and push stack\n");
            break;
        case 0x3:
            skip_if_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            break;
        case 0x4:
            skip_if_not_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            break;
        case 0x5:
        printf("Skif if v%d and v%d aren't equal");
            skip_if_vx_vy_egal(state,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            break;
        case 0x6:
            set_register(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            printf("Set %d at register %d\n",instruction & MASK_8BITS, (instruction >> 8) & MASK_4BITS);
            break;
        case 0x7:
            simple_add(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
             printf("Add %d at v%d\n", instruction & MASK_8BITS,(instruction >> 8) & MASK_4BITS);
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
            printf("Set index register at %d\n", instruction & MASK_12BITS);
            break;
        case 0xB:
           jump_offset(state,instruction & MASK_12BITS);
            break;
        case 0xC:
           random(state, (instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            break;
        case 0xD:
            printf("Display with x = %d, y = %d, et n = %d\n",(instruction >> 8) & MASK_4BITS ,(instruction >> 4) & MASK_4BITS,instruction & MASK_4BITS);
            display(state,(instruction >> 4) & MASK_4BITS, (instruction >> 8) & MASK_4BITS, instruction & MASK_4BITS);
            update_grid(state);
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
                printf("Recupere la valeur du timer dans v%d\n",(instruction >> 8) & MASK_4BITS);
                 get_timer_value(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x15:
                  printf("Mets la valeur du timer depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 set_timer_value(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x18:
                  printf("Mets la valeur du timer de son depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 set_sound_timer(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x1E:
                  printf("Ajoute a l'index depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 add_index(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x0A:
                  printf("Attends l'entree de l'utilisateur depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 get_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
                 break;
              case 0x29:
                  printf("Recupere le caractere a afficher depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 get_character(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x33:
                  printf("Recupere la valeur du timer dans v%d\n",(instruction >> 8) & MASK_4BITS);
                 binary_to_dec(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x55:
                  printf("Convertit en bcd depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                 store_memory(state,(instruction >> 8) & MASK_4BITS);
                 break;
              case 0x65:
                  printf("Recupere depuis la memoire jusqua v%d\n",(instruction >> 8) & MASK_4BITS);
                 load_memory(state,(instruction >> 8) & MASK_4BITS);
                 break;
              default:
                 break;
           }
            break;
        default:
           printf("Instruction not implemented yet : %04x\n",instruction);
            break;
    }
}

void update_timer(State* state){
    if(state->delay_timer > 0) state->delay_timer--;
    if(state->sound_timer > 0) state->sound_timer--;
    //printf("Timer = %d\n", state->delay_timer);
}