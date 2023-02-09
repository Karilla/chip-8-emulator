#include <inttypes.h>
#include <time.h>
#include "raylib.h"
#include "state.h"
#include "gui.h"
#include <stdio.h>

// CPU settings
#define CPU_FREQ 10 // 600Hz
#define CPU_TIMER_FREQ 50 // 60Hz
#define CPU_NS_PER_HZ 1000000000 // 1s
#define CPU_NS_PER_CYCLE CPU_NS_PER_HZ / CPU_FREQ // 0.001ms or 1KHz
#define CPU_NS_PER_TIMER_CYCLE CPU_NS_PER_HZ / CPU_TIMER_FREQ // 16670000ns or 60Hz

static struct timespec  clock_last_tick;
static struct timespec  timer_last_tick;
static uint64_t         clock_delta_tick;
static uint64_t         timer_delta_tick;

int sys_clock_tick(void) {
    // Emulate 1000Hz clock for system
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    clock_delta_tick = now.tv_nsec - clock_last_tick.tv_nsec;

    if (clock_delta_tick < CPU_NS_PER_CYCLE) {
        return 0;
    }

    clock_delta_tick -= CPU_NS_PER_CYCLE;

    clock_last_tick = now;
    return 1;
}

void process_input(State* state){
    if(IsKeyDown(49)) set_key(state, KEY_1S);
    else if(IsKeyDown(50)) printf("Pressed\n");//set_key(state, KEY_2S);
    else if(IsKeyDown(51)) set_key(state, KEY_3S);
    else if(IsKeyDown(52)) set_key(state, KEY_4S);

    else if(IsKeyDown(81)) set_key(state, KEY_QS);
    else if(IsKeyDown(87)) set_key(state, KEY_WS);
    else if(IsKeyDown(69)) set_key(state, KEY_ES);
    else if(IsKeyDown(82)) set_key(state, KEY_RS);

    else if(IsKeyDown(65)) set_key(state, KEY_AS);
    else if(IsKeyDown(83)) set_key(state, KEY_SS);
    else if(IsKeyDown(68)) set_key(state, KEY_DS);
    else if(IsKeyDown(70)) set_key(state, KEY_FS);

    else if(IsKeyDown(89)) set_key(state, KEY_YS);
    else if(IsKeyDown(88)) set_key(state, KEY_XS);
    else if(IsKeyDown(67)) set_key(state, KEY_CS);
    else if(IsKeyDown(86)) set_key(state, KEY_VS);
    else set_key(state, NO_KEYS);
}

int sys_timer_tick(void) {
    // Emulate 60Hz clock for system
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    timer_delta_tick = now.tv_nsec - timer_last_tick.tv_nsec;

    if (timer_delta_tick < CPU_NS_PER_TIMER_CYCLE) {
        return 0;
    }

    timer_delta_tick -= CPU_NS_PER_TIMER_CYCLE;

    timer_last_tick = now;
    return 1;
}

void init_game(State* state){
    init_state(state);
    init_window(640,350,"TODO CHANGE ME");
}
