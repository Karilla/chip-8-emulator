#ifndef CHIP_8_EMULATOR_STATE_MACHINE_H
#define CHIP_8_EMULATOR_STATE_MACHINE_H

#include <inttypes.h>

typedef uint8_t ProgramState;

void switch_to_idle(ProgramState program_state);

void switch_to_menu(ProgramState program_state);

void switch_to_debug(ProgramState program_state);

void switch_to_error(ProgramState program_state);

void switch_to_running(ProgramState program_state);

#endif //CHIP_8_EMULATOR_STATE_MACHINE_H
