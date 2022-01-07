#include <iostream>
#include "Header.h"
#include <iomanip>

using namespace std;
real Num:: vecproduct(real* a, real* b){
	real res = 0;
	for (int i = 0; i < N; i++)
	{
		res += a[i] * b[i];
	}
	return res;
}

void Num::matvecproduct() {
	for (int i = 0; i < N; i++)
	{
		xk[i] = vecproduct(A[i], xk_1);
	}
}

void Num::Ly(real* f) {
	for (int i = 0; i < N; i++)
	{
		real sum = 0.0;
		for (int j = 0; j < i; j++)
		{
			sum -= A[i][j] * y[j];
		}
		y[i] = f[i] + sum;
	}
}

void Num::Ux() {
	real* x = y;
	for (int i = N-1; i >= 0; i--)
	{
		real sum = 0;
		for (int j = i+1; j < N; j++)
		{
			x[i] -= A[i][j] * x[j];
		}
		x[i] /= A[i][i];
	}
}

void Num::input(ifstream& finput) {
	finput >> N;
	finput >> maxiter;
	finput >> eps;
	A = new real* [N];
	y = new real [N];
	xk = new real[N];
	xk_1 = new real[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new real[N];
		for (int j = 0; j < N; j++)
		{
			finput >> A[i][j];
		}
		xk[i] = 1;//надо выбрать )
		xk_1[i] = xk[i];
	}

}

void Num::LU() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i <= j)
			{
				real res = 0;
				for (int k = 0; k < N; k++)
					res -= A[i][k] * A[k][j];
				A[i][j] += res;
			}
			else
			{
				real res = 0;
				for (int k = 0; k < N; k++)
				{
					res -= A[i][k] * A[k][j];
				}
				A[i][j] += res;
				A[i][j] /= A[j][j];
			}
		}
	}
}