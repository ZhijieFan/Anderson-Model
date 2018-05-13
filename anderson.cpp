#include "anderson.h"

double t = -1.;

mat H(N, N);

int nn[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

void matrix_generator(double W) {
	H.zeros();

	int Mx, My = 0;

	for (int x = 0; x < L; x++) {
		for (int y = 0; y < L; y++) {
			Mx = index(x, y, L);

			for (int i = 0; i < 4; i++) {
				My = index(mod(x + nn[i][0], L), mod(y + nn[i][1], L), L);
				H(Mx, My) = -t;
			}

			//H(Mx, Mx) = rand1(W);
			H(Mx, Mx) = rand2(W);
		}
	}
}

void diagonalization(double W, int Ni) {
	cout << "t=" << t << endl;
	cout << "W=" << W << endl;

	Estimator accu;
	Estimator esti;

	Timer timer2;
	timer2.start();
	for (int n = 1; n < Ni + 1; n++) {
		//cout << "n = " << n << endl;
		//cout << "Generate Hamiltonian" << endl;
		matrix_generator(W);

		//cout << "Solving for eigenvalues" << endl;
		esti.reset();
		eig_sym(esti.eigval, esti.eigvec, H);
		esti.compute_dos();
		esti.compute_ipr();

		average(accu, esti, n-1);

		if (n % 1 == 0) {
			cout << "n = " << n << '\t';
			timer2.print("Time spent:");

			//accu.print_dos("dos.dat");
			//accu.print_ipr("ipr.dat");
		}
	}
}

const int ref_L = 10000;
const int ref_N = ref_L*ref_L;
const int Nh_ref = 1200;
double ref_range = 6;

void dos_ref(const string filename){
	double ek[ref_N];

	for (int kx = 0; kx < ref_L; kx++) {
		for (int ky = 0; ky < ref_L; ky++) {
			int idx = index(kx,ky, ref_L);
			ek[idx] = -2 * t*(cos(kx * 2 * PI / (double)ref_L) + cos(ky * 2 * PI / (double)ref_L));
		}
	}

	double dos_ref[Nh_ref+1];
	double de = (double)(2 * ref_range) / (double)Nh_ref;
	for (int i = 0; i < Nh_ref + 1; i++) {
		dos_ref[i] = 0;
	}

	for (int i = 0; i < ref_N; i++) {
		int e_idx = int((ek[i] + ref_range + 0.5*de) / de);
		if (e_idx < 0 || e_idx >  Nh_ref + 1) {
			cout << "out of range" << endl;
		}
		else {
			dos_ref[e_idx]++;
		}
	}

	double sum = 0;
	for (int i = 0; i <  Nh_ref+1; i++) {
		sum += dos_ref[i] * de;
	}


	std::ofstream fs;
	fs.open(filename.c_str(), std::ios::out);
	fs.precision(8);
	for (int i = 0; i <  Nh_ref+1; i++) {
		fs << (i)*de - ref_range << '\t';
		fs << dos_ref[i]/sum << endl;
	}
	fs.close();

}