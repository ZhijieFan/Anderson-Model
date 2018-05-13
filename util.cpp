//=====================================================================
//	util.cpp
//	DiffusionQMC
//
//	Created by Zhijie Fan, 5/1/2018
//=====================================================================
#include <iostream>
#include <math.h>
#include "util.h"

//Initialize the random number generator with system time
void init_srand(void) {
	//Declare variable to hold seconds on clock.
	time_t seconds;
	//Get value from system clock and place in seconds variable.
	time(&seconds);
	//Convert seconds to a unsigned
	srand((unsigned int)seconds);
	//srand48(seconds);
}

int mod(int x, int m) {
	if (x >= 0 && x<m)
		return x;
	else if (x<0)
		return m - 1 - mod(-1 - x, m);
	else
		return x%m;
}