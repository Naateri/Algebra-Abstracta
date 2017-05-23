//maths.h
//operaciones de algebra abstracta
#include <utility>
#include <vector>
#include <string>
#include <NTL/ZZ.h>
#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED
long modulo(long a, long n);
NTL::ZZ ntlModulo(NTL::ZZ, NTL::ZZ);
std::pair<int, int> moduloQandR(int a, int n);
std::pair<NTL::ZZ, NTL::ZZ> moduloQandRntl(NTL::ZZ a, NTL::ZZ n);
long mcd(long a, long b);
NTL::ZZ mcdNTL(NTL::ZZ a, NTL::ZZ b);
std::pair<long, long> mcdExtendido(long a, long b);
std::pair<NTL::ZZ, NTL::ZZ> mcdExtendidoNTL(NTL::ZZ a, NTL::ZZ b);
long inversa(long, long);
NTL::ZZ inversaNTL(NTL::ZZ a, NTL::ZZ n);
NTL::ZZ potenciacion(int, int);
long potenModular(long, long, long);
NTL::ZZ ntlPotenModular(NTL::ZZ a, NTL::ZZ b, NTL::ZZ m);
NTL::ZZ modExponentiation1(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n);r
NTL::ZZ modExponentiation2(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n, int k); //k = numero de bits para representar el numero -1
vector<NTL::ZZ> ecuModulo(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n); //ax === b mod n
NTL::ZZ TCR(vector<NTL::ZZ> a, vector<NTL::ZZ> b, vector<NTL::ZZ> n);
std::string zToString(const NTL::ZZ &z);
//GENERADOR DE ALEATORIOS
NTL::ZZ getBase10(std::vector<bool> binary);
void rightShift(std::vector<bool> &binary, int shift);
void leftShift(std::vector<bool> &binary, int shift);
NTL::ZZ ga(int tamTotal, int seedSize, int parts, int v);
#endif
