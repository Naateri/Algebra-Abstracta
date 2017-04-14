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

int lgc(int seed, int a, int c, int m = 0x7fff){ //linear congruential method
  int output;
  seed = seed * a + c;
  if (m == 0x7fff)
    output = (seed >> 16) & 0x7fff; //0x7fff = 2^32
  else
    output = modulo(seed, m);
  return output;
}
