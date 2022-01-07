#include <iostream>
#include "Header.h"
#include <iomanip>

using namespace std;
real Num::norma(real* a){
	real res = 0;
	for (int i = 0; i < N; i++)
	{
		res += a[i] * a[i];
	}
	return sqrt(res);

}
void Num::matvecproduct(real* a, real* b) {
	for (int i = 0; i < N; i++)
	{
		b[i] = 0;
		for (int j = 0; j < N; j++)
		{
			b[i] += A[i][j] * a[j];
		}
	}
}

void Num::LUsolve(real* f, real* a) {
	for (int i = 0; i < N; i++)
	{
		real sum = 0.0;
		for (int j = 0; j < i; j++)
		{
			sum += L[i][j] * a[j];
		}
		a[i] = f[i] - sum;
	}
	for (int i = N - 1; i >= 0; i--)
	{
		real sum = 0;
		for (int j = i + 1; j < N; j++)
		{
			sum += U[i][j] * a[j];
		}
		a[i] =(a[i]- sum)/U[i][i];
	}
}

void Num::input(ifstream& finput) {
	finput >> N;
	finput >> maxiter;
	finput >> eps;
	A = new real* [N];
	x = new real [N];
	x1 = new real [N];
	L = new real* [N];
	U = new real* [N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new real[N];
		for (int j = 0; j < N; j++)
		{
			finput >> A[i][j];
		}
		x[i] = 1;//надо выбрать )
	}

}

void Num::LU() {
	real sum = 0;
	for (int i = 0; i < N; i++)
	{
		L[i] = new real[N];
		U[i] = new real[N];
	}
	for (int i = 0; i < N; i++) {
	
		L[i][i] = 1;
		for (int j = i; j < N; j++) {
			sum = 0;
			for (int k = 0; k < i; k++) {
				sum += L[i][k] * U[k][j];
			}
			U[i][j] = A[i][j] - sum;
		}

		for (int j = i; j < N; j++) {
			sum = 0;
			for (int k = 0; k < i; k++) {
				sum += L[j][k] * U[k][i];
			}
			L[j][i] = (A[j][i] - sum) / U[i][i];
		}
	}
}

void Num::FindMax() {
	real lambd = 0, lambd_1, norm_x, norm_x1, nev;
	int iter = 0;
	norm_x = norma(x);
	for (; iter < maxiter; iter++)
	{
		matvecproduct(x, x1);
		norm_x1 = norma(x1);
		lambd_1 = norm_x1 / norm_x;
		nev = abs(lambd_1 - lambd) / abs(lambd_1);
		if (nev < eps)
		{
			lambd = lambd_1;
			break;
		}
		lambd = lambd_1;
		norm_x = norm_x1;
		for (int i = 0; i < N; i++)
		{
			x[i] = x1[i];
			//x[i] /= norm_x;// как я понимаю если убрать это и след хуйню то ничего не поменяется)(!?
		}
		//norm_x = 1; // не понимаю почему
	}
	cout << "Iteration: " << iter << endl << "accuracy: " << nev << endl << setprecision(14) << "lambda: " << lambd << endl;
}
void Num::FindMin() {
	real lambd = 0, lambd_1, norm_x, norm_x1, nev;
	int iter = 0;
	norm_x = norma(x);
	LU();
	for (; iter < maxiter; iter++)
	{
		LUsolve(x,x1);
		norm_x1 = norma(x1);
		lambd_1 = norm_x1 / norm_x;
		nev = abs(lambd_1 - lambd) / abs(lambd_1);
		if (nev < eps)
		{
			lambd = lambd_1;
			break;
		}
		lambd = lambd_1;
		norm_x = norm_x1;
		for (int i = 0; i < N; i++)
		{
			x[i] = x1[i];
			//x[i] /= norm_x;// как я понимаю если убрать это и след хуйню то ничего не поменяется)(!?
		}
		//norm_x = 1; // не понимаю почему

	}
	cout << "Iteration: " << iter << endl << "accuracy: " << nev << endl << setprecision(14) << "lambda: " << 1/lambd << endl;
}