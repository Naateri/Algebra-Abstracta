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

int lcg(int seed, int a, int c, int m = 0x80000000){ //linear congruential algorithm
  int output;
  seed = seed * a + c;
  if (m == 0x80000000)
    output = (seed >> 16) & 0x7fff; //0x80000000 = 2^32
  else
    output = modulo(seed, m);
  return output;
}

int mcg(int seed, int a, int m = 0x80000000){ //multiple congruential algorithm
  int output;
  seed *= a;
  if (m == 0x80000000)
    output = (seed >> 16) & 0x7fff; //0x80000000 = 2^32
  else
    output = modulo(seed, m);
  return output;
}
