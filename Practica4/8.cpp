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

int potenc(int g, int A, int N){
	int a = g, b = 1;
	while(A > 0){
		if (modulo(a, 2)){
			b*=a;
			if (b > N)
				b = modulo(b, N);
		}
		a*= a;
		if (a > N) a = modulo(a, N);
		A /= 2;
		}
	return b;
	}

int main(int argc, char *argv[]) {
	cout << potenc(444, 343, 527);
	return 0;
}

