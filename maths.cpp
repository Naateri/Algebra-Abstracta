//maths.cpp
//algebra abstracta
#include <iostream>
#include "maths.h"
#include <utility>
#include <stdlib.h> //rand
#include <time.h>
#include <string>
#include <bitset>

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
int generadorAleatorios(int seed, int tamSeedBits, int tamBitsRandNum, int p, int v){ //p = particiones, v = vueltas
	int randNum, sizeOfP, cont = 0;
	string num;
	bool bit;
	randNum = seed;
	randNum <<= (tamBitsRandNum - tamSeedBits); 
	for (int i = 0, j = tamSeedBits; i < (tamBitsRandNum - tamSeedBits); i++, j++){ //llenar bits que faltan
		bit = ((randNum ^ (1u << i-1)) ^ (randNum ^ (1u << i))); //(S(i) + S(i+1))mod 2    
		if (bit) //si bit == 1, esa posicion será 1, si no se queda como 0
			randNum ^= (1u << (j-1));
	}
	string partitions[p]; //creando las particiones
	sizeOfP = tamBitsRandNum / p;
	bitset<tamBitsRandNum> numBits (randNum);
	num = numBits.to_string();
	j = sizeOfP;
	for (i = 0; i < sizeOfP; i++){ //llenando array
		while (j > 0){
			partitions[i] += num[cont];
			cont++;
			j--;
		}
		j = sizeOfP;
	}
	for (i = 0; i < v; i++){ //haciendo las vueltas
		for (j = 0; j < p; j++){ //analizando cada elemento del array
			bitset<sizeOfP> temp (partitions[j]);
			bit = temp[0];
			temp >>= 1;
			temp[sizeOfP-1] ^= bit;
			partitions[j] = temp.to_string();
		}
	}
	num.clear();
	for (i = 0; i < p; i++)
		num += partitions[i];
	bitset<tamBitsRandNum> finalnum (num);
	randNum = finalnum.to_ulong();
	return randNum;
}

int potenciacion(int a, int b){
	int m, temp, res;
	res = 1;
	m = b;
	while(m != 0){
		if (m == b) temp = a;
		else temp *= temp;
		if (modulo(m, 2) == 1)
			res *= temp;
		m/=2;
	}
	return res;
}

int potenModular(int a, int b, int m){
	int n, temp, res;
	res = 1;
	n = b;
	while(n != 0){
		if (n == b){
			temp = a;
			if (temp > m)
				temp = modulo(temp, m); //por si ocurre que a > m
		}else{ 
			if (temp > m)
				temp = modulo(temp, m);
			temp *= temp;
		}
		if (modulo(n, 2) == 1)
			res *= temp;
		if (res > m)
			res = modulo(res, m);
		n/=2;
	}
	return res;
}
