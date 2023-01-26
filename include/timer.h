#pragma once
#ifndef __TIMER__
#define __TIMER__

#include <SDL.h>

typedef struct Timer_struct
{
	uint64_t paused_ticks, start_ticks;
	uint8_t paused, started;
} Timer;

Timer *Timer_init();

void Timer_start(Timer *timer);

void Timer_stop(Timer *timer);

void Timer_pause(Timer *timer);

void Timer_unpause(Timer *timer);

uint64_t Timer_get_ticks(Timer *timer);

#endif // __TIMER__