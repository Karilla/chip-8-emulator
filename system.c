//
// Created by benoit on 01/08/2022.
//
#include <inttypes.h>
#include <time.h>

// CPU settings
#define CPU_FREQ 600 // 600Hz
#define CPU_TIMER_FREQ 60 // 60Hz
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