#include <iostream>
using namespace std;

long modulo(long a, long n){ //a mod n
	long q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

void algoritmo(long seed, long a, long b, long n){
	long x = seed;
	do{
		x = modulo((a*x + b), n);
		cout << "x: " << x << endl;
	}while(x != seed);
}

int main(){
	algoritmo(0, 3, 7, 11);
	return 0;
}

