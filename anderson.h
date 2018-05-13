#pragma once
#include <iostream>
#include <fstream>
#include <armadillo>
#include "analysis.h"
#include "util.h"

using namespace std;
using namespace arma;

const int L = 60;
const int N = L*L;

void matrix_generator(double W);

void diagonalization(double W, int Ni);

void dos_ref(const string filename);

extern double t;

extern int nn[4][2];