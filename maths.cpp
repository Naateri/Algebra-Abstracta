//maths.cpp
//algebra abstracta
#include "maths.h"
#include <vector>
int modulo(int a, int n){
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0){
		q--;
		r += n;
	}
	return r;
}

int mcd(int a, int b){ //mcd iterativo 
	int r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return b;
}

std::vector<int> mcdExtendido(int a, int b){
	int r, r1 = a, r2 = b, x, x1 = 1, x2 = 0, y, y1 = 0, y2 = 1, q;
	while (r2 > 0){
		q = r1/r2; //EUCLIDES
		r = r1 - q*r2; //EUCLIDES
		r1 = r2; r2 = r; //EUCLIDES (como borrar?)
		x = x1 - q*x2;
		x1 = x2; x2 = x;
		y = y1 - q * y2;
		y1 = y2; y2 = y;
	}
	std::vector<int> resultados;
	resultados.push_back(x); //resultados.at(0) = x
	resultados.push_back(y); //resultados.at(1) = y
	resultados.push_back(r1); //resultados.at(2) = mcd(a,b)
	return resultados;
}

