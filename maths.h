//maths.h
//operaciones de algebra abstracta
#include <utility>
#include <vector>
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
NTL::ZZ potenciacion(NTL::ZZ a, NTL::ZZ b);
long potenModular(long, long, long);
NTL::ZZ ntlPotenModular(NTL::ZZ a, NTL::ZZ b, NTL::ZZ m);
NTL::ZZ modExponentiation1(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n); //EXAMEN PARCIAL ALGORITMO 1
NTL::ZZ modExponentiation2(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n, int k); //EXAMEN PARCIAL ALGORITMO 2
vector<NTL::ZZ> ecuModulo(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n);
NTL::ZZ TCR(NTL::ZZ *a, NTL::ZZ *b, NTL::ZZ *n, int tam); //teorema chino del resto
//GENERADOR DE ALEATORIOS
NTL::ZZ getBase10(std::vector<bool> binary);
void rightShift(std::vector<bool> &binary, int shift);
void leftShift(std::vector<bool> &binary, int shift);
NTL::ZZ ga(int tamTotal, int seedSize, int parts, int v);

#endif
