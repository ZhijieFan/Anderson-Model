//=====================================================================
//	util.h
//	DiffusionQMC
//
//	Created by Zhijie Fan, 5/1/2018
//=====================================================================
#pragma once
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

const double PI = acos(-1.0);

inline double rand1(void) {
	return ((double)rand()) / ((double)RAND_MAX);
}

inline double rand1(double W) {
	return W*(((double)rand()) / ((double)RAND_MAX) - 0.5);
}

inline double rand2(void) {
	return (double)(rand() *(RAND_MAX + 1) + rand()) / (double)((RAND_MAX + 2)* RAND_MAX);
}

inline double rand2(double W) {
	return W*((double)(rand() *(RAND_MAX + 1) + rand()) / (double)((RAND_MAX + 2)* RAND_MAX) - 0.5);
}

inline double RNG_ex(void) {
	int r = rand();
	if (r == 0) return RNG_ex();
	else return ((double)r) / ((double)RAND_MAX);
}

//Generate Guassian numbers
inline double gaussian(double sigma) {
	double phi = rand1() * 2 * PI;
	double r = sigma*sqrt(-2 * log(RNG_ex()));
	return r*sin(phi);
}

inline int index(int x, int y, int L) {
	return y*L + x;
}

int mod(int x, int m);

void init_srand(void);

class Timer {
public:
	clock_t t;

	Timer(void) {};

	void start(void) {
		t = clock();
	};

	void reset(void) {
		t = clock();
	};

	void print(std::string msg) {
		clock_t t_now = clock();
		cout << msg << " : " << (double)(t_now - t) / CLOCKS_PER_SEC << "s" << endl;
	};

	double time_lapse(void) {
		clock_t t_now = clock();
		return ((double)(t_now - t) / CLOCKS_PER_SEC);
	}
};