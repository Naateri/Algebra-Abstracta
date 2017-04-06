//maths.cpp
//algebra abstracta
#include <iostream>
#include "maths.h"
#include <utility>
#include <stdlib.h> //rand
#include <time.h>

using namespace std;

int modulo(int a, int n){ //a mod n
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

pair<int, int> moduloQandR(int a, int n){
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		;//r+=n;
	pair<int, int> values(r, q);
	return values;
}

int mcd(int a, int b){ //mcd iterativo 
	int r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

pair<int, int> mcdExtendido(int a, int b){
	int r, r1 = a, r2 = b, x, x1 = 1, x2 = 0, y, y1 = 0, y2 = 1, q;
	pair<int, int> modulo;
	while (r2 != 0){
		modulo = moduloQandR(r1, r2);
		q = modulo.second; //EUCLIDES
		r = modulo.first; //EUCLIDES
		r1 = r2;
		r2 = r; 
		x = x1 - q*x2;
		x1 = x2; 
		x2 = x;
		y = y1 - q*y2;
		y1 = y2; 
		y2 = y;
	}
	pair<int, int> resultados(x1,y1); //resultados.first = x (x1 = x)
	return resultados; //resultados.second = y (y1 = y)
}
int inversa(int a, int n){
	int x;
	x = mcdExtendido(a, n).first;
	if (x < 0)
		x = modulo(x, n);
	return x;
}
int generadorAleatorios(int tamSeedBits, int tamBitsRandNum, int parts, int vueltas){
	;
}
