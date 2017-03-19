//maths.cpp
//algebra abstracta
#include "maths.h"
int modulo(int a, int n){
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0){
		q--;
		r += n;
	}
	return r;
}

int mcd(int a, int b){ //mcd iterativo 
	int r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return b;
}

/*int main(){
	
}*/
