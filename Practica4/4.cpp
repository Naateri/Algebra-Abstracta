#include <iostream>
#include <stdlib.h>
using namespace std;

long valAbs(long a, long b){
	if ((a-b) < 0)
		return b-a;
	else return a-b;
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
		long res = valAbs(a, b);
		valAbs >>= 1;
		return Algoritmoxx(res, b);
	}
}

int main(){
	cout << Algoritmoxx(1764, 868);
	return 0;
}
