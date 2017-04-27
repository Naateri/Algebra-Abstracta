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

void primeTest(int m){
	int x = 2, y; //x = 2 porque es el número más pequeño posible
	if ((m-1) < x) //que según el pseudoalgoritmo funciona
		cout << "Error. M es muy pequeño.\n";
	y = potenModular(x, m-1, m);
	if (y == 1)
		cout << "M puede ser primo.\n";
	else
		cout << "M definitivamente no es primo.\n";
}

int main(int argc, char *argv[]) {
	primeTest(47);
	return 0;
}
 
