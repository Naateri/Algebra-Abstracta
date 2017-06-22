//maths.cpp
//algebra abstracta
#include <iostream>
#include "maths.h"
#include <utility>
#include <stdlib.h> //rand
#include <time.h>
#include <string>
#include <vector>
#include <NTL/ZZ.h>
#include <opencv2/opencv.hpp>

using namespace std;

long modulo(long a, long n){ //a mod n
	long q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

NTL::ZZ ntlModulo(NTL::ZZ a, NTL::ZZ n){
	if ((a < n) && (a>=0)) return a;
	NTL::ZZ q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r+=n;
	return r;
}

pair<int, int> moduloQandR(int a, int n){
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		;//r+=n;
	pair<int, int> values(q,r);
	return values;
}

pair<NTL::ZZ, NTL::ZZ> moduloQandRntl(NTL::ZZ a, NTL::ZZ n){
	NTL::ZZ q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		;//r+=n;
	pair<NTL::ZZ, NTL::ZZ> values(q,r);
	return values;
}

long mcd(long a, long b){ //mcd iterativo
	long r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

NTL::ZZ mcdNTL(NTL::ZZ a, NTL::ZZ b){
	NTL::ZZ r;
	while (b!=0){
		r = ntlModulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

/* pair<long, long> mcdExtendido(long a, long b){
long r, r1 = a, r2 = b, x, x1 = 1, x2 = 0, y, y1 = 0, y2 = 1, q;
pair<long, long> modulo;
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
pair<long, long> resultados(x1,y1); //resultados.first = x (x1 = x)
return resultados; //resultados.second = y (y1 = y)
}
*/
vector<long> mcdExtendido(long a, long b){
	vector<long> result;
	if (b == 0){
		for (int i = 0; i < 3; i++)
			result.push_back(0);
		return result;
	}
	long u = 1, g = a, x = 0, y = b, s, t, q, v;
	pair<long, long> division;
	while (y != 0){
		division = moduloQandR(g, y);
		q = division.first;
		t = division.second;
		s = u - q*x;
		u = x; g = y;
		x = s; y = t;
	}
	v = (g - a*u)/b;
	/*if (u < 0)
	u += b;*/
	result.push_back(g);
	result.push_back(u);
	result.push_back(v);
	return result;
}

vector<NTL::ZZ> mcdExtendidoNTL(NTL::ZZ a, NTL::ZZ b){
	vector<NTL::ZZ> result;
	if (b == 0){
		for (int i = 0; i < 3; i++)
			result.push_back(NTL::to_ZZ(0));
		return result;
	}
	NTL::ZZ u, g, x, y, s, t, q, v;
	g = a; y = b; u = 1; x = 0;
	pair<NTL::ZZ, NTL::ZZ> division;
	while (y != 0){
		division = moduloQandRntl(g, y);
		q = division.first;
		t = division.second;
		s = u - q*x;
		u = x; g = y;
		x = s; y = t;
	}
	v = (g - a*u)/b;
	/*if (u < 0)
	u += b;*/
	result.push_back(g);
	result.push_back(u);
	result.push_back(v);
	return result;
}

long inversa(long a, long n){
	long x;
	vector<long> euclides = mcdExtendido(a, n);
	x = euclides.at(1);
	if (x < 0)
		x = modulo(x, n);
	return x;
}

NTL::ZZ inversaNTL(NTL::ZZ a, NTL::ZZ n){
	NTL::ZZ num;
	/*if(NTL::ProbPrime(a, 1) && ntlModulo(n, a) != 0){ //teorema de fermat: si n es primo y n no divide a a
	return ntlPotenModular(a, n-2, n);
	}*/
	vector<NTL::ZZ> euclides = mcdExtendidoNTL(a, n);
	num = euclides.at(1);
	if (num < 0){
		//num = ntlModulo(num, n);
		num += n;
	}
	return num;
}

NTL::ZZ potenciacion(NTL::ZZ a, NTL::ZZ b){
	NTL::ZZ m, temp;
	NTL::ZZ res;
	res = NTL::conv<NTL::ZZ>("1");
	m = b;
	while(m != 0){
		if (m == b) temp = a;
		else temp *= temp;
		if (ntlModulo(m, NTL::to_ZZ(2)) == 1)
			res *= temp;
		m/=2;
	}
	return res;
}

long potenModular(long a, long b, long m){
	long n, temp, res;
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

NTL::ZZ ntlPotenModular(NTL::ZZ a, NTL::ZZ b, NTL::ZZ m){
	NTL::ZZ res;
	res = 1;
	if (a == 0)
		return a;
	if (NTL::ProbPrime(b, 1) && b == m) //si b es primo y b es m
		return ntlModulo(a, b); //a^b mod m = (a mod p) mod m (FERMAT 2)
	if (ntlModulo(m, a) != 0 && NTL::ProbPrime(m, 1) && b == m-1) //si m no divide a a y es primo y b es m-1(FERMAT 1)
		return res; //resultado = 1 (a^{p-1} = 1 mod p)
	NTL::ZZ n , temp;
	n = b;
	while(n != 0){
		if (n == b){
			temp = a;
			if (temp > m)
				temp = ntlModulo(temp, m); //por si ocurre que a > m
		}else{
			if (temp > m)
				temp = ntlModulo(temp, m);
			temp *= temp;
		}
		if (ntlModulo(n, NTL::to_ZZ(2)) == 1)
			res *= temp;
		if (res > m)
			res = ntlModulo(res, m);
		n/=2;
	}
	return res;
}

vector<NTL::ZZ> ecuModulo(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n){ //ax === b mod n
	NTL::ZZ x, d, k, r;
	vector<NTL::ZZ> results;
	d = mcdNTL(a,n);
	a = inversaNTL(a, n);
	r = a*b;
	r = ntlModulo(r, n);
	for(k = 0; k < d; k++){
		x = n*k + r;
		results.push_back(x);
	}
	return results;
}

NTL::ZZ modExponentiation1(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n){ //también la de la práctica
	NTL::ZZ exp, x;
	exp = 1;
	//x = ntlModulo(a, b);
	x = a;
	while (b>0){
		if ((b&1) == 1){
			exp *= x;
			exp = ntlModulo(exp, n);
		}
		x *= x;
		x = ntlModulo(x, n);
		b >>= 1;
	}
	return exp;
}

NTL::ZZ modExponentiation2(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n, int k){ //k = numero de bits para representar el numero -1
	NTL::ZZ d;
	d = 1;
	for (; k >= 0; k--){
		d *= d;
		d = ntlModulo(d, n);
		//bit = (a >> k) & 1;
		if (((b >> k) & 1) == 1){ //bit en la posicion k
			d *= a;
			d = ntlModulo(d, n);
		}
	}
	return d;
}


NTL::ZZ TCR(vector<NTL::ZZ> a, vector<NTL::ZZ> b, vector<NTL::ZZ> n){
	int i;
	NTL::ZZ P, temp, x, x_0;
	long tam = a.size();
	x_0 = 0;
	NTL::ZZ p[tam]; //se guardan los pi's
	NTL::ZZ q[tam]; //se guardan los qi's
	for (i = 0; i < tam; i++){
		if (a.at(i) != 1){
			temp = inversaNTL(a.at(i), n.at(i));
			b.at(i) = b.at(i) * temp;
		}
	}
	P = 1;
	for (i = 0; i < tam; i++)
		P *= n.at(i);
	for (i = 0; i < tam; i++){ //llenando los pi's y qi's
		temp = P / n.at(i);
		p[i] = temp;
		temp = p[i];
		temp = ntlModulo(temp, n.at(i));
		temp = inversaNTL(temp, n.at(i));
		q[i] = temp;
		x = ntlModulo(b.at(i),P) * ntlModulo(p[i], P) * ntlModulo(q[i], P); ///trabajando con clases de equivalencia
		x = ntlModulo(x, P);
		x_0 += x;
	}
	x_0 = ntlModulo(x_0, P);
	cout << "x = " << x_0 << " + " << P << "k" << endl;
	return x_0;
}

string zToString(const NTL::ZZ &z) {
	stringstream leString;
	leString << z;
	return leString.str();
}

/*
Generador de aleatorios*/

int rdtsc(){
	__asm__ __volatile__("rdtsc");
}

NTL::ZZ getBase10(vector<bool> binary){
	NTL::ZZ ret;
	int pot = binary.size() - 1;
	for(int i = 0; i < binary.size(); i++, pot--){
		if (binary.at(i))
			ret += potenciacion(NTL::to_ZZ(2), NTL::to_ZZ(pot));
	}
	return ret;
}

void rightShift(vector<bool> &binary, int shift){
	for (int i = shift; i < binary.size(); i++){
		binary.at(i) = binary.at(i-shift);
	}
}

void leftShift(vector<bool> &binary, int shift){
	for (int i = (binary.size() - shift); i > 0; i--){
		binary.at(i-shift) = binary.at(i);
	}
}

NTL::ZZ ga(int tamTotal, int seedSize, int parts, int v){
	vector<bool> binary;
	long seed;
	int i, j, sizeOfPart;
	long s;
	//seed = time(NULL);
	seed = rdtsc();
	bool res;
	NTL::ZZ result;
	for (i = 0; i < seedSize; i++){ //llenando el vector con la semilla en bits-
		if (modulo(seed, 2) == 1){
			binary.push_back(1);
		} else binary.push_back(0);
		seed /= 2;
	}
	for (j = 0, i; i < tamTotal; i++, j++){
		res = binary.at(j) ^ binary.at(j+1); //pos = s_0 + s_1
		binary.push_back(res);
	}
	sizeOfPart = tamTotal / parts;
	result = getBase10(binary);
	return result;
}

NTL::ZZ DES(NTL::ZZ num){
	vector<bool> binary, perm1, perm2, c0, d0, hola, res;
	long seed;
	int i, j;
	NTL::ZZ result;
	for(j = 1; j <= 16; j++){
		seed = time(NULL) + (j*7);
		for (i = 0; i < 64; i++){ //llenando el vector con la semilla en bits-
			if ((seed & 1) == 1){
				binary.push_back(1);
			} else binary.push_back(0);
			seed >>= 1;
		}
		for(i = 0; i < 56; i++){
			perm1.push_back(binary.at(pc1[i]-1));
		}
		for(i = 0; i < 28; i++){
			c0.push_back(perm1.at(i));
		}
		for(i; i < 56; i++){
			d0.push_back(perm1.at(i));
		}
		if( (j>=3 && j<=8) || (j>=10 && j<=15)){
			leftShift(c0, 1);
			rightShift(d0, 1);
			leftShift(c0, 1);
			rightShift(d0, 1);
		} else {
			leftShift(c0, 1);
			rightShift(d0, 1);
		}
		for(i = 0; i < 28; i++){
			hola.push_back(c0.at(i));
		}
		for(i; i < 56; i++){
			hola.push_back(d0.at(i-28));
		}
		for(i = 0; i < 48; i++){
			perm2.push_back(hola.at(pc2[i]-1));
			res.push_back(perm2.at(i)); ///guardando los K's aqui
		}
		perm2.clear();
		c0.clear();
		d0.clear();
		perm1.clear();
		binary.clear();
		hola.clear();
	}
	result = getBase10(res);
	return result;
}


/* PRIMITIVE ROOT*/

NTL::ZZ findRoot(NTL::ZZ p){
	NTL::ZZ q, found, g, i;
	q = (p-NTL::to_ZZ(1));
	q >>= 1;
	for (i = 1; i < p-1; i++){
		g = p - i;
		if ((ntlModulo(g*g, p) != 1) && (modExponentiation1(g, q, p) != 1)){
			break;
		}
	}
	return g;
}

/* Building an Image*/

string getRGB(cv::Mat img){
	cv::Vec3b colors;
	string ret, temp;
	long color, hund;
	for(int y = 0; y < img.rows; y++){
		for (int x = 0; x < img.cols; x++){
			colors = img.at<cv::Vec3b>(cv::Point(x,y));
			for (int i = 0; i < 3; i++){
				color = int(colors[i]);
				hund = 100;
				if (color == 0){
					ret += "000";
					continue;
				}
				while (color < hund){
					ret += "0";
					hund /= 10;
				}
				temp = zToString(NTL::to_ZZ(color));
				ret += temp;
			}
		}
	}
	return ret;
}

void getImg(string RGB, cv::Mat &result){
	int col, i = 0;
	string temp;
	for(int y = 0; y < 32; y++){
		for(int x = 0; x < 32; x++){
			cv::Vec3b color;
			for(int j = 0; j < 3; j++, i+=3){
				temp.clear();
				temp = RGB.substr(i, 3);
				col = NTL::to_long(stringToZZ(temp));
				color[j] = col;
			}
			result.at<cv::Vec3b>(cv::Point(x,y)) = color;
		}
	}
}
