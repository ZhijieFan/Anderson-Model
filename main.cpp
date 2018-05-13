#include <iostream>
#include <fstream>
#include <armadillo>
#include "anderson.h"
#include "util.h"

using namespace std;

int main(void) {
	double W = 2;
	int N_avg = 100;

	Timer timer;
	timer.start();

	init_srand();

	//dos_ref("ref_dos.dat");

	diagonalization(W, N_avg);

	timer.print("Total time spent:");
}