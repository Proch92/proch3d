#include "proch3d.h"

P3d_Timer::P3d_Timer() {
	last = 0;
	last_tick = 0;
}

void P3d_Timer::start() {
	last = get_time();
	last_tick = last;
}

void P3d_Timer::stop() {
	
}

long P3d_Timer::get_tick() {
	last_tick = get_time();
	return (get_time() - last);
}

long P3d_Timer::get_elapsed_last_call() {
	last_tick = get_time();
	return (get_time() - last_tick);
}
