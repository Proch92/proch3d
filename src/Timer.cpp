#include "proch3d.h"

Timer::Timer() {
	last = 0;
	last_tick = 0;
}

void Timer::start() {
	last = get_time();
	last_tick = last;
}

void Timer::stop() {
	
}

long Timer::get_tick() {
	last_tick = get_time();
	return (get_time() - last);
}

long Timer::get_elapsed_last_call() {
	last_tick = get_time();
	return (get_time() - last_tick);
}
