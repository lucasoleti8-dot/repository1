#include <iostream>
#include <Eigen/Dense> 
#include "gradiente_coniugato.h"

int main(void) {
	for (int n = 2; n < 100; n++) {
		std::cout << "DIMENSIONE SISTEMA: " << n << std::endl;
		Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
		Eigen::MatrixXd A = B.transpose() * B;
		double detA, condA, errRel;
		if(solve_system(A, detA, condA, errRel)) {
			std::cout<< std::scientific<< "DetA: "<< detA<< ", RCondA: "<< 1.0 / condA<< ", Relative Error: "<< errRel<< "\n";
		}
        else {
			std::cout<< std::scientific<< "DetA: "<< detA<< ", RCondA: "<< 1.0 / condA << " (Matrix is singular)"<< "\n";
		}
		//OSS: usiamo il reciproco del numero di condizionamento -> se matrice mal condizionata
		//reciproco tende a zero
	}
	
	
	
	return 0; 
}