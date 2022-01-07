#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef double real;

class Num {
	int N;
	int maxiter;
	real eps;
	real nev;
	real** A;
	real** U;
	real** L;
	real* x1;
	real* xk;
	real* x;
public:
	real vecproduct(real* a, real* b);
	void matvecproduct(real* a, real* b);
	void LUsolve(real* f, real* x1);
	real norma(real* a);
	void FindMax();
	void FindMin();
	void LU();
	void input(ifstream& input);
};