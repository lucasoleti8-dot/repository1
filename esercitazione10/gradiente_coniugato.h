#pragma once
#include <iostream>
#include <Eigen/Dense> 
#include <Eigen/SVD> //serve per decomposizione SVD

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
	unsigned int n = A.rows(); 
	Eigen::VectorXd x = Eigen::VectorXd::Zero(n); //x_0 (condizione iniziale arbitraria)
	Eigen::VectorXd res = b - A * x; //r_0 (residuo iniziale)
	Eigen::VectorXd p = res; 
	
	const unsigned int it_max = 10000; 
	unsigned int it = 0;
	const double res_tol = 1.0e-15;
	while ((it < it_max) && (res.norm() > res_tol)) {
		const double alpha_k = p.dot(res) / (p.dot(A * p)); 
		x = x + alpha_k * p; 
		res = b - A * x; 
		const double beta_k = p.dot(A * res) / (p.dot(A * p)); 
		p = res - beta_k * p; 
		it++; 
	}
	std::cout.precision(4);
	std::cout<< std::scientific<< "it"<< "/"<< "it_max"<< std::endl;
	std::cout<< std::scientific<< it<< "/"<< it_max<< std::endl;
	std::cout<< std::scientific<< "res_norm"<< "/"<< "res_tol"<< std::endl;
	std::cout<< std::scientific<< res.norm() << "/"<< res_tol<< std::endl;
	return x; 
}

bool solve_system(const Eigen::MatrixXd& A,
				//OSS: in queste altri variabili passate in input voglio salvarmi 
				//valori che mi interessano (calcolati tramite questa funzione, ma 
				//modifico variabili esterne)
                 double& detA,
                 double& condA,
                 double& errRel) {
	
	//calcolo numero condizionamento con SVD
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
	Eigen::VectorXd singularValuesA = svd.singularValues();
	condA = singularValuesA.maxCoeff() / singularValuesA.minCoeff();	
	detA = A.determinant();

    if( singularValuesA.minCoeff() < 1e-16)
    {
        return false; //matrice singolare (<-> non invertibile) (<-> non esiste soluzione)
    }
	
	//RISOLVO SISTEMA LINEARE TEST: soluzione esatta è vettore di tutti uni
	unsigned int n = A.rows(); //numero righe matrice A
    Eigen::VectorXd exactSolution = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A.rowwise().sum();
	Eigen::VectorXd x = gradiente_coniugato(A,b);
	errRel = (exactSolution.norm() == 0.0) ? (x - exactSolution).norm() :
                                     (x - exactSolution).norm() / exactSolution.norm();
	
	return true; 
}
	
	

