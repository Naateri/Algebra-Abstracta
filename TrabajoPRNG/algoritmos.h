//algoritmos de numeros aleatorios
#include <iostream>
#ifndef ALGORITMOS_H_INCLUDED
#define ALGORITMOS_H_INCLUDED 
int lcg(int seed, int a = 214013, int c = 2531011, unsigned int m = 0x80000000);
int mcg(int seed, int a = 214013, unsigned int m = 0x80000000);
int lfgsum(int seed, int j, int k, unsigned int m = 0x80000000);
int lfg(int, int, int);
#endif
