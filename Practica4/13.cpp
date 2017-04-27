#include <iostream>
#include <vector>
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
	if (u < 0)
		u += b;
	result.push_back(g);
	result.push_back(u);
	result.push_back(v);
	return result;
}

long inversa(long a, long n){ //retorna 0 si no hay inversa
	vector<long> gcd; 
	gcd = algoritmo(a, n);
	if (gcd.at(0) == 1)
		return gcd.at(1);
	else
		return 0;
}

int main(int argc, char *argv[]) {
	cout << inversa(13, 17);
	return 0;
}

