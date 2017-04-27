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

long valAbs(long a){
	if (a < 0)
		return a*-1;
	else return a;
}

long Algoritmoxx(long a, long b){
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else if ( (modulo(a, 2) == 0) && (modulo(b,2)) == 0)
		return 2 * Algoritmoxx(a/2, b/2);
	else if (modulo(a,2) == 0 && modulo(b,2) == 1)
		return 2 * Algoritmoxx(a/2, b);
	else if (modulo(a,2) == 1 && modulo(b,2) == 0)
		return 2 * Algoritmoxx(a, b/2);
	else
		return Algoritmoxx(valAbs(a-b)/2, b);
}

int main(){
	cout << Algoritmoxx(1764, 868);
	return 0;
}
