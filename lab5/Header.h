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
	real** A;
	real* xk_1;
	real* xk;
	real* y;
public:
	real vecproduct(real* a, real* b);
	void matvecproduct();
	void Ly(real* f);
	void Ux();
	void LU();
	void input(ifstream& input);
};