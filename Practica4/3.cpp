#include <iostream>
#include <vector>
#include <utility>
using namespace std;

pair<long, long> modulo(long a, long n){ //a mod n
	long q, r;
	pair<long, long> result;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	result.first = q;
	result.second = r;
	return result; //.first = cociente, .second = remainder
}

vector<long> algoritmo(long a, long b){
	vector<long> result;
	if (b == 0){
		for (int i = 0; i < 3; i++)
			result.push_back(0);
		return result;
	}
	long u = 1, g = a, x = 0, y = b, s, t, q, v;
	pair<long, long> division;
	while (y != 0){
		division = modulo(g, y);
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
pair<long, long> mcdExtendido(long a, long b){
	long r, r1 = a, r2 = b, x, x1 = 1, x2 = 0, y, y1 = 0, y2 = 1, q;
	pair<long, long> moduloo;
	while (r2 != 0){
		moduloo = modulo(r1, r2);
		q = moduloo.first; //EUCLIDES
		r = moduloo.second; //EUCLIDES
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

int main(){
	vector<long> i;
	pair<long, long> I;
	vector<long> ii;
	vector<long> iii;
	vector<long> iv;
	i = algoritmo(527, 1258);
	I = mcdExtendido(527, 1258);
	
	ii = algoritmo(228, 1056);
	iii = algoritmo(163961, 167181);
	iv = algoritmo(3892394, 239847);
	cout << "i: (527, 1258)\n";
	cout << "g: " << i.at(0) << endl;
	cout << "u: " << i.at(1) << endl;
	cout << "v: " << i.at(2) << endl;
	cout << "I: \n";
	cout << "x: " << I.first << endl;
	cout << "y: " << I.second << endl;
	cout << "ii: (228, 1056)\n";
	cout << "g: " << ii.at(0) << endl;
	cout << "u: " << ii.at(1) << endl;
	cout << "v: " << ii.at(2) << endl;
	cout << "iii: (163961, 167181)\n";
	cout << "g: " << iii.at(0) << endl;
	cout << "u: " << iii.at(1) << endl;
	cout << "v: " << iii.at(2) << endl;
	cout << "iv: (3892394, 239847)\n";
	cout << "g: " << iv.at(0) << endl;
	cout << "u: " << iv.at(1) << endl;
	cout << "v: " << iv.at(2) << endl;
	return 0;
}
