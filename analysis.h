#pragma once
#include <iostream>
#include <fstream>
#include <armadillo>
#include "anderson.h"
#include "util.h"

using namespace std;
using namespace arma;

const int Nh_dos = 120;
const int Nh_ipr = 150;

class Estimator {
public:
	int n_run;
	
	vec eigval;
	mat eigvec;
	
	double dos[Nh_dos+1];
	double ipr[Nh_ipr+1];

	Estimator(void) {
		reset();
	}

	void compute_dos(void);
	void compute_ipr(void);

	void print_dos(const string filename);
	void print_ipr(const string filename);

	void reset(void) {
		n_run = 0;

		eigval.zeros();
		eigvec.zeros();

		for (int i = 0; i < Nh_dos+1; i++) {
			dos[i] = 0;
		}

		for (int i = 0; i < Nh_ipr+1; i++) {
			ipr[i] = 0;
		}
	}
};

void average(Estimator & accu, Estimator & esti, int nc);