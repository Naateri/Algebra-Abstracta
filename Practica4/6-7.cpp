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

long expo(long a, long p, long n){
	long r = 1;
	for (long i = 1; i < p; i++){
		r*=a;
		r = modulo(r, n);
	}
	return r;
}

long expo2(long a, long p, long n){
	if (p == 0)
		return 1;
	long t, mod;
	if (!(p&1)){
		t = expo2(a, p>>1, n);
		t*=t;
		return modulo(t, n);
	}
	t = expo2(a, (p-1)>>2, n);
	t*=t;
	mod = modulo(t,n);
	return modulo(a * mod, n);
}

int main(int argc, char *argv[]) {
	cout << expo(30192, 43791, 65301) << endl;
	cout << expo2(30192, 43791, 65301) << endl;
	return 0;
}

