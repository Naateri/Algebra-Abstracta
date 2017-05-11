#include <iostream>
#include <stdlib.h>
using namespace std;

long valAbs(long a){
	if (a < 0)
		return -a;
	else return a;
}

long Algoritmoxx(long a, long b){
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else if ( !(a&1) && !(b&1))
		return 2 * Algoritmoxx(a>>1, b>>1);
	else if (!(a&1) && (b&1))
		return 2 * Algoritmoxx(a>>1, b);
	else if ((a&1) && !(b&1))
		return 2 * Algoritmoxx(a, b>>1);
	else{
		long res = a-b;
		res>>=2;
		return Algoritmoxx(abs(res), b);
	}
}

int main(){
	cout << Algoritmoxx(1764, 868);
	return 0;
}
