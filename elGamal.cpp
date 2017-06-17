#include "elGamal.h"
#include "maths.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <bitset>
#include <ctime>
#include <NTL/ZZ.h>
using namespace std;

ElGamal::ElGamal(int bits){
	NTL::ZZ q;
	///q = ga(bits, bits/2, 1, 1);
	///do{
	///q++;
	///q = ga(bits, bits/2, 1, 1);
	q = ga(bits, bits/2, 1, 1);
	q = NTL::NextPrime(q, 1);
	//this->p = (q << 1) + 1;
	//cout << "p: " << this->p << endl;
	///}while (NTL::ProbPrime((q<<1) + 1, 1) != 1);
	//this->p = ga(bits, bits/2, 1, 1);
	//this->p = NTL::NextPrime(p, 1);
	this->p = (q<<1) + 1;
	//cout << "final p: " << this->p << endl;
	this->e = findRoot(p);
	do{
		this->d = ga(bits, bits/2, 1, 1);
	}while (d >= (this->p - 2));
	this->e_2 = modExponentiation1(e, d, p);
}
ElGamal::ElGamal(NTL::ZZ p, NTL::ZZ e, NTL::ZZ e2, int bits){
	this->p = p;
	this->e = e;
	this->e_2 = e2;
	do{
		this->r = ga(bits, bits/2, 1, 1);
	}while (this->r > (this->p-2));
	this->C_1 = modExponentiation1(this->e, this->r, this->p);
	this->K_M = modExponentiation1(this->e_2, this->r, this->p);
}

string ElGamal::cifrar(string msj){
	string leng = zToString(this->p), c, original, tmp, alfLeng = zToString(NTL::to_ZZ(this->alfabeto.size()));
	long k = leng.size() - 1, modd, lengP, lengAlf = alfLeng.size()-1; ///k = digitos de N - 1s
	long i, found;
	NTL::ZZ result, temp, ten, ten2;
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(lengAlf));
	for (i = 0; i < msj.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(msj[i]);
		ten2 = ten;
		if (found < ten2){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
			ten2 /= 10;
		}
		original += zToString(NTL::to_ZZ(found));
		/*ostringstream conv;
		conv << found;
		original += conv.str(); ///guardamos ese numero en un string*/
	}
	modd = modulo(original.size(), k);
	while(modd != 0){ ///agrega "26" (espacio) mientras la long del texto
		original += "26"; ///en numeros no sea divisible entre la long de N
		modd = modulo(original.size(), k);
	}
	cout << "Original: " << original << endl;
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(k)); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		ten2 = ten;
		tmp = original.substr(i, k);
		/*stringstream convi(tmp);
		convi >> temp; ///string tmp to int (NTL) temp*/
		temp = stringToZZ(tmp);
		result = ntlModulo((this->K_M * temp), this->p);
		while (result  < ten2){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten2 /= 10;
		}
		/*ostringstream conv;
		conv << result;
		c += conv.str(); ///c + "result"*/
		c += zToString(result);
	}
	string c1 = zToString(this->C_1), c0;
	k = c1.size();
	while(k < leng.size()){
		c0 += "0";
		k++;
	}
	c0 += c1;
	c = c0 + c;
	return c;
}

string ElGamal::descifra_mensaje(string c){
	string leng = zToString(this->p), d, ret, tmp, c1, alfLeng = zToString(NTL::to_ZZ(this->alfabeto.size()));
	long k = leng.size(), lengAlf = alfLeng.size(); ///P Digitos
	long i, found;
	NTL::ZZ result, temp, ten, ten2, invKM;
	for (i = 0; i < k; i++){
		c1 += c[i];
	}
	/*stringstream convi(c1);
	convi >> this->C_1; ///c1 (string) a C_1 (ZZ)*/
	this->C_1 = stringToZZ(c1);
	this->K_M = modExponentiation1(this->C_1, this->d, this->p);
	invKM = inversaNTL(this->K_M, this->p);
	ten = potenciacion(NTL::to_ZZ(10), k-NTL::to_ZZ(2)); ///10^{N-2} para ver si el numero es menor a eso
	for(i = k; i < c.size(); i+=k){
		tmp.clear(); ///borrando datos del string
		ten2 = ten;
		tmp = c.substr(i, k);
		/*stringstream convi(tmp);
		convi >> temp; ///string tmp to int (NTL) temp*/
		temp = stringToZZ(tmp);
		result = ntlModulo((temp * invKM), this->p);
		ostringstream conv;
		conv << result;
		while (result < ten2){ ///guardando en bloques N-1
			d += "0";
			ten2 /= 10;
		}
		d += conv.str();
	}
	for(i = 0; i < d.size(); i+=lengAlf){
		tmp.clear();
		tmp = d.substr(i, lengAlf);
		/*stringstream convi(tmp);
		convi >> found;*/
		found = NTL::to_long(stringToZZ(tmp));
		ret += this->alfabeto[found];
	}
	return ret;
}

NTL::ZZ ElGamal::getP() {return this->p;}
NTL::ZZ ElGamal::getE() {return this->e;}
NTL::ZZ ElGamal::getE2() {return this->e_2;}
NTL::ZZ ElGamal::getC1() {return this->C_1;}
NTL::ZZ ElGamal::getD() {return this->d;}
void ElGamal::setP(NTL::ZZ p) {this->p = p;}
void ElGamal::setD(NTL::ZZ d) {this->d = d;}
