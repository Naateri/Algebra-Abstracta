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

long mcd(long a, long b){ //mcd iterativo
	long r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

long mcdRec(long a, long b){
	if (b == 0)
		return a;
	return mcdRec(b, modulo(a, b));
}

int main(){
	long a = 412, b = 260;
	cout << "Iterativo: " << mcd(a, b) << endl;
	cout << "Recursivo: " << mcdRec(a, b) << endl;
	return 0;
}
