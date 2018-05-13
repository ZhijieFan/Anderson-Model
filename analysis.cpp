#include "analysis.h"

double dos_range = 6;
double ipr_range = 6;

void Estimator::compute_dos(void) {
	double inverse_de = (double)Nh_dos / (double)(2 * dos_range);

	for (int i = 0; i <Nh_dos+1; i++) {
		dos[i] = 0;
	}

	for (int i = 0; i < eigval.size(); i++) {
		cout << eigval(i) << endl;
		int e_idx = int((eigval(i) + dos_range)*inverse_de + 0.5);
		if (e_idx < 0 || e_idx > Nh_dos+1) {
			cout << "out of range" << endl;
		}
		else {
			dos[e_idx]++;
		}
	}
}

void Estimator::compute_ipr(void) {
	double Im[N];
	double Im4, Im2;
	double de = (double)(2 * ipr_range) / (double)Nh_ipr;
	
	for (int i = 0; i < Nh_ipr+1; i++) {
		ipr[i] = 0;
	}

	for (int m = 0; m < N; m++) {
		Im4 = 0;	Im2 = 0;

		for (int r = 0; r < N; r++) {
			Im4 += pow(eigvec(r, m), 4);
			Im2 += pow(eigvec(r, m), 2);
		}

		Im[m] = Im4 / pow(Im2, 2);
	}

	for (int i = 0; i < Nh_ipr+1; i++) {

		double e = i*de - ipr_range;

		for (int m = 0; m < N; m++) {
			if (eigval(m)<e + 0.5*de && eigval(m)>e - 0.5*de) {
				ipr[i] += Im[m];
			}
		}

	}

}

void Estimator::print_dos(const string filename) {
	double de = (double)(2 * dos_range) / (double)Nh_dos;

	double sum = 0;
	for (int i = 0; i < Nh_dos+1; i++) {
		sum += dos[i] * de;
	}

	std::ofstream fs;
	fs.open(filename.c_str(), std::ios::out);
	fs.precision(8);
	for (int i = 0; i < Nh_dos+1; i++) {
		fs << (i)*de - dos_range << '\t';
		fs << dos[i] / sum << endl;
	}
	fs.close();
}

void Estimator::print_ipr(const string filename) {
	double de = (2 * ipr_range) / (double)Nh_ipr;

	std::ofstream fs;
	fs.open(filename.c_str(), std::ios::out);
	fs.precision(8);
	for (int i = 0; i < Nh_ipr+1; i++) {
		fs << (i)*de - ipr_range << '\t';
		fs << ipr[i] << endl;
	}
	fs.close();
}

void average(Estimator & accu, Estimator & esti, int nc) {
	accu.n_run = nc;

	for (int i = 0; i < Nh_dos+1; i++) {
		accu.dos[i] = (nc * accu.dos[i] + esti.dos[i]) / (nc + 1.);
		//accu.dos[i] += esti.dos[i];
	}

	for (int i = 0; i < Nh_ipr+1; i++) {
		accu.ipr[i] = (nc * accu.ipr[i] + esti.ipr[i]) / (nc + 1.);
	}
}