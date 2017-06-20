#include "protocolo.h"
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

Protocolo::Protocolo(int bits){
	NTL::ZZ phi;
	this->myQ = ga(bits, bits>>1, 1, 1);
	this->myQ = NTL::NextPrime(this->myQ, 1);
	do{
		this->myG = ga(bits, bits>>1, 1, 1);
	}while(this->myG > this->myQ);
	this->p_1 = ga(bits, bits>>1, 1, 1);
	this->p_1 = NTL::NextPrime(this->p_1, 1);
	this->p_2 = ga(bits, bits>>1, 1, 1);
	this->p_2 = NTL::NextPrime(this->p_2, 1);
	this->myN = this->p_1 * this->p_2;
	phi = (this->p_1 - 1) * (this->p_2 - 1);
	do{
		this->myE = ga(bits, bits>>1, 1, 1);
	}while(mcdNTL(e, phi) != 1); ///e siempre va a ser mayor que 1
	this->d = inversaNTL(e, phi);
	do{
		a = ga(bits, bits>>1, 1, 1); ///aleatorio para cifrar
	}while(a > this->q);
}

string Protocolo::cifrar(string msj){
	long alfL = this->alfabeto.size();
	string leng = zToString(this->q), c, original, tmp, alfLeng = zToString(NTL::to_ZZ(alfL));
	long k = leng.size() - 1, modd, lengP, lengAlf = alfLeng.size()-1; ///k = digitos de N - 1s
	long i, found;
	NTL::ZZ result, temp, ten, ten2, ka, Ca;
	ka = modExponentiation1(this->g, this->a, this->q);
	Ca = modExponentiation1(this->a, this->e, this->N);
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(lengAlf));
	for (i = 0; i < msj.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(msj[i]);
		ten2 = ten;
		if (found < ten2){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
			ten2 /= 10;
		}
		original += zToString(NTL::to_ZZ(found));
	}
	modd = modulo(original.size(), k);
	while(modd != 0){ ///agrega "26" (espacio) mientras la long del texto
		original += "26"; ///en numeros no sea divisible entre la long de N
		modd = modulo(original.size(), k);
	}
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(k)); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		ten2 = ten;
		tmp = original.substr(i, k);
		temp = stringToZZ(tmp);
		result = ntlModulo((ka * temp), this->q);
		while (result  < ten2){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten2 /= 10;
		}
		c += zToString(result);
	}
	string ca = zToString(Ca), c0;
	k = ca.size();
	leng = zToString(this->N);
	while(k < leng.size()){
		c0 += "0";
		k++;
	}
	c0 += ca;
	c += c0;
	return c;
}

string Protocolo::descifra_mensaje(string c){
	string d;
	return d;
}

NTL::ZZ Protocolo::getE(){return this->e;} ///e del receptor
void Protocolo::setE(NTL::ZZ e){this->e = e;}
NTL::ZZ Protocolo::getN(){return this->N;} ///n del receptor
void Protocolo::setN(NTL::ZZ n){this->N = n;} ///set N del receptor
void Protocolo::setQ(NTL::ZZ q){this->q = q;} ///set Q del receptor
NTL::ZZ Protocolo::getQ(){return this->q;} ///q del receptor
void Protocolo::setG(NTL::ZZ g){this->g = g;} ///g del receptor
NTL::ZZ Protocolo::getMyE() {return this->myE;}
NTL::ZZ Protocolo::getMyN() {return this->myN;}
NTL::ZZ Protocolo::getMyG() {return this->myG;}
NTL::ZZ Protocolo::getMyQ() {return this->myQ;}
