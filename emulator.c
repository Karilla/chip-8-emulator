#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"
#include "instruction.h"
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

char* decode_instr(State* state, uint16_t instruction,enum Control controlKey){
    char* log;
    log = calloc(1024, sizeof(char));
    switch(instruction >> 12){
        case 0x0:
            if((instruction & MASK_12BITS) == 0x0E0){
                sprintf(log,"Effacage de l'ecran\n");
                clear_screen(state);
                update_grid(state);
                return log;
            }
            if((instruction & MASK_12BITS) == 0x0EE){
                state->PC = pop_stack(state);
                sprintf(log,"Popped from the stack at address %d\n", state->PC);
                return log;
            }
            break;
        case 0x1:
            jump(state,(instruction & ~0xF000));
            sprintf(log,"Jump at %d\n",(instruction & ~0xF000));
            return log;
        case 0x2:
            sprintf(log,"Jump at %d and push %d in stack\n", instruction & MASK_12BITS, state->PC);
            call_push(state, instruction & MASK_12BITS);
            return log;
        case 0x3:
            sprintf(log,"Skip if v%d egal v%d\n",(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            skip_if_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            return log;
        case 0x4:
            sprintf(log,"Skip if v%d is not egal v%d\n",(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            skip_if_not_vx_egal(state,(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            return log;
        case 0x5:
            sprintf(log,"Skip if v%d and v%d aren't equal\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            skip_if_vx_vy_egal(state,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            return log;
        case 0x6:
            set_register(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            sprintf(log,"Set %d at register %d\n",instruction & MASK_8BITS, (instruction >> 8) & MASK_4BITS);
            return log;
        case 0x7:
            simple_add(state,(instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            sprintf(log,"Add %d at v%d without caring about carry\n", instruction & MASK_8BITS,(instruction >> 8) & MASK_4BITS);
            return log;
        case 0x8:
            switch(instruction & MASK_4BITS){
                case 0:
                   sprintf(log,"v%d is set by v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS );
                   set(state, (instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                   return log;
                case 1:
                    sprintf(log,"v%d is set by v%d or v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    or(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                    return log;
                case 2:
                    sprintf(log,"v%d is set by v%d and v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    and(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                    return log;
                case 3:
                    sprintf(log,"v%d is set by v%d xor v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    xor(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                    return log;
                case 4:
                    sprintf(log,"v%d is set by v%d + v%d with caring of carry\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    add_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS);
                    return log;
                case 5:
                    sprintf(log,"v%d is set by v%d - v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
                    substract_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS, true );
                    return log;
                case 6:
                    sprintf(log,"Put the value of v%d in v%d and then shift 1 bit to the right then put to vf the bit shifted\n",(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    shift(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS,true);
                    return log;
                case 7:
                    sprintf(log,"v%d is set by v%d - v%d\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    substract_register(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS, false );
                    return log;
                case 0xE:
                    sprintf(log,"Put the value of v%d in v%d and then shift 1 bit to the left then put to vf the bit shifted\n",(instruction >> 4) & MASK_4BITS,(instruction >> 8) & MASK_4BITS);
                    shift(state,(instruction >> 8) & MASK_4BITS, (instruction >> 4) & MASK_4BITS,false);
                    return log;
                default:
                    break;
            }
            break;
        case 0x9:
            sprintf(log,"Skip if v%d and v%d aren't equal\n",(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            skip_if_vx_vy_not_egal(state,(instruction >> 8) & MASK_4BITS,(instruction >> 4) & MASK_4BITS);
            return log;
        case 0xA:
            set_index_register(state, instruction & MASK_12BITS);
            sprintf(log,"Set index register at %d\n", instruction & MASK_12BITS);
            return log;
        case 0xB:
            sscanf(log,"Jump to address %d + v0\n",instruction & MASK_12BITS);
            jump_offset(state,instruction & MASK_12BITS);
            return log;
        case 0xC:
            sscanf(log,"Put in v%d a random number modulo %d",(instruction >> 8) & MASK_4BITS,instruction & MASK_8BITS);
            chip8_random(state, (instruction >> 8) & MASK_4BITS, instruction & MASK_8BITS);
            return log;
        case 0xD:
            sprintf(log,"Display with x = %d, y = %d, et n = %d\n",(instruction >> 8) & MASK_4BITS ,(instruction >> 4) & MASK_4BITS,instruction & MASK_4BITS);
            display(state,(instruction >> 4) & MASK_4BITS, (instruction >> 8) & MASK_4BITS, instruction & MASK_4BITS);
            update_grid(state);
            return log;
        case 0xE:
           if((instruction & MASK_8BITS ) == 0x9E){
               sscanf(log,"Skip if key in v%d is pressed",(instruction >> 8) & MASK_4BITS);
               skip_if_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
               return log;
           }
           else if((instruction & MASK_8BITS) == 0xA1){
               sscanf(log,"Skip if key in v%d is not pressed",(instruction >> 8) & MASK_4BITS);
               skip_if_not_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
               return log;
           }
            break;
        case 0xF:
           switch(instruction & MASK_8BITS){
              case 0x07:
                  sprintf(log,"Recupere la valeur du timer dans v%d\n",(instruction >> 8) & MASK_4BITS);
                  get_timer_value(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x15:
                  sprintf(log,"Mets la valeur du timer depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                  set_timer_value(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x18:
                  sprintf(log,"Mets la valeur du timer de son depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                  set_sound_timer(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x1E:
                  sprintf(log,"Ajoute a l'index depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                  add_index(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x0A:
                  sprintf(log,"Attends l'entree de l'utilisateur depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                  get_key(state,(instruction >> 8) & MASK_4BITS,controlKey);
                  return log;
              case 0x29:
                  sprintf(log,"Recupere le caractere a afficher depuis v%d\n",(instruction >> 8) & MASK_4BITS);
                  get_character(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x33:
                  sprintf(log,"Convertit la valeur a v&d et la stock en memoire\n",(instruction >> 8) & MASK_4BITS);
                  binary_to_dec(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x55:
                  sprintf(log,"Stock la valeur de v%d dans la memoire\n",(instruction >> 8) & MASK_4BITS);
                  store_memory(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              case 0x65:
                  sprintf(log,"Recupere depuis la memoire et la mets dans v%d\n",(instruction >> 8) & MASK_4BITS);
                  load_memory(state,(instruction >> 8) & MASK_4BITS);
                  return log;
              default:
                 break;
           }
            break;
        default:
            sprintf(log,"Instruction not implemented yet : %04x\n",instruction);
            return log;
    }
}

void update_timer(State* state){
    if(state->delay_timer > 0) state->delay_timer--;
    if(state->sound_timer > 0) state->sound_timer--;
    //printf("Timer = %d\n", state->delay_timer);
}