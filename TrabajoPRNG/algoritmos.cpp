#include <iostream>
#include "algoritmos.h"

int modulo(int a, int n){ //a mod n
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

int lcg(int seed, int a, int c, unsigned int m = 0x80000000){ //linear congruential algorithm
  seed = seed * a + c; 
	if (seed > m) //0x80000000 = 2^32
   	seed = modulo(seed, m);
  return seed;
}

int mcg(int seed, int a = 214013, unsigned int m = 0x80000000){ //multiple congruential algorithm
  seed *= a;  //0x80000000 = 2^32
  if (seed > m)
  	seed = modulo(seed, m);
  return seed;
}

int lfgSum(int seed, int j, int k, unsigned int m = 0x80000000){ //lagged fibonacci generator, $ = +
	seed = (seed - j) + (seed - k);
	if (seed > m)
		seed = modulo(seed, m);
  return seed;
}

int lfg(int seed, int j, int k){ //lagged fibonacci generator, $ = XOR
	seed = (seed - j) ^ (seed - k);
	return seed;
}
