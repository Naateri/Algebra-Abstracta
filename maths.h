//maths.h
//operaciones de algebra abstracta
#include <utility>
#include <vector>
#include <NTL/ZZ.h>
#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED
long modulo(long a, long n);
NTL::ZZ ntlModulo(NTL::ZZ a, NTL::ZZ n);
std::pair<int, int> moduloQandR(int a, int n);
long mcd(long a, long b);
std::pair<long, long> mcdExtendido(long a, long b);
long inversa(long, long);
long long potenciacion(int, int);
long potenModular(long, long, long);
NTL::ZZ ntlPotenModular(NTL::ZZ a, long b, long m);
//GENERADOR DE ALEATORIOS
NTL::ZZ getBase10(vector<bool> binary);
void rightShift(vector<bool> &binary, int shift);
void leftShift(vector<bool> &binary, int shift);
NTL::ZZ ga(int tamTotal, int seedSize, int parts, int v);

#endif
