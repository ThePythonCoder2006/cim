#include <SDL.h>

#include <timer.h>

Timer *Timer_init()
{
	Timer *timer = malloc(sizeof(Timer));

	timer->start_ticks = timer->paused_ticks = 0;

	// timer is not started nor is it paused
	timer->paused = timer->started = 0;

	return timer;
}

void Timer_start(Timer *timer)
{
	timer->started = 1;
	timer->paused = 0;

	timer->start_ticks = SDL_GetTicks64();
	timer->paused_ticks = 0;
}

void Timer_stop(Timer *timer)
{
	timer->started = 0;
	timer->paused = 0;

	timer->start_ticks = 0;
	timer->paused_ticks = 0;
}

void Timer_pause(Timer *timer)
{
	if (timer->started && !timer->paused)
	{
		timer->paused = 1;

		timer->paused_ticks = SDL_GetTicks64() - timer->start_ticks;
		timer->start_ticks = 0;
	}
}

void Timer_unpause(Timer *timer)
{
	if (timer->started && timer->paused)
	{
		timer->paused = 0;

		timer->start_ticks = SDL_GetTicks64() - timer->paused_ticks;
		timer->paused_ticks = 0;
	}
}

uint64_t Timer_get_ticks(Timer *timer)
{
	if (timer->started)
	{
		if (timer->paused)
			return timer->paused_ticks;

		return SDL_GetTicks64() - timer->start_ticks;
	}

	return 0;
}
