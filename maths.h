//maths.h
//operaciones de algebra abstracta
#include <utility>
#include <vector>
#include <string>
#include <NTL/ZZ.h>
#include <opencv2/opencv.hpp>
#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED
int pc1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
int pc2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31,
	37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

long modulo(long a, long n);
NTL::ZZ ntlModulo(NTL::ZZ, NTL::ZZ);
std::pair<int, int> moduloQandR(int a, int n);
std::pair<NTL::ZZ, NTL::ZZ> moduloQandRntl(NTL::ZZ a, NTL::ZZ n);
long mcd(long a, long b);
NTL::ZZ mcdNTL(NTL::ZZ a, NTL::ZZ b);
std::vector<long> mcdExtendido(long a, long b);
std::vector<NTL::ZZ> mcdExtendidoNTL(NTL::ZZ a, NTL::ZZ b);
long inversa(long, long);
NTL::ZZ inversaNTL(NTL::ZZ a, NTL::ZZ n);
NTL::ZZ potenciacion(int, int);
long potenModular(long, long, long);
NTL::ZZ ntlPotenModular(NTL::ZZ a, NTL::ZZ b, NTL::ZZ m);
NTL::ZZ modExponentiation1(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n);
NTL::ZZ modExponentiation2(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n, int k); //k = numero de bits para representar el numero -1
vector<NTL::ZZ> ecuModulo(NTL::ZZ a, NTL::ZZ b, NTL::ZZ n); //ax === b mod n
NTL::ZZ TCR(vector<NTL::ZZ> a, vector<NTL::ZZ> b, vector<NTL::ZZ> n);
std::string zToString(const NTL::ZZ &z);
NTL::ZZ stringToZZ(std::string a)
//GENERADOR DE ALEATORIOS
int rdtsc();
NTL::ZZ getBase10(std::vector<bool> binary);
void rightShift(std::vector<bool> &binary, int shift);
void leftShift(std::vector<bool> &binary, int shift);
NTL::ZZ ga(int tamTotal, int seedSize, int parts, int v);
NTL::ZZ DES(NTL::ZZ num);
/* PRIMITIVE ROOT*/
NTL::ZZ findRoot(NTL::ZZ p);
/*BUILDING IMAGE*/
std::string getRGB(cv::Mat img);
void getImg(std::string RGB, cv::Mat &result);
#endif
