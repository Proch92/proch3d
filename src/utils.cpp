#include "proch3d.h"

long get_time() {
	struct timeval actual;
	gettimeofday(&actual, NULL);
	
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

void p3d_delay(long ms) {
	usleep(ms * 1000);
}
