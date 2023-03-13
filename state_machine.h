#ifndef CHIP_8_EMULATOR_STATE_MACHINE_H
#define CHIP_8_EMULATOR_STATE_MACHINE_H

#include <inttypes.h>

void switch_to_idle(uint8_t program_state);

void switch_to_menu(uint8_t program_state);

void switch_to_debug(uint8_t program_state);

void switch_to_error(uint8_t program_state);

void switch_to_running(uint8_t program_state);

#endif //CHIP_8_EMULATOR_STATE_MACHINE_H
