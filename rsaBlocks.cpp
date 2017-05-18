#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <NTL/ZZ.h>
#include "rsaBlocks.h"
#include "maths.h"

using namespace std;

RSABlocks::RSABlocks(int bits){
	//testear primalidad de p y q
	this->p = ga(bits, bits/2, 1, 1);
	this->p = NTL::NextPrime(this->p, 1);
	this->q = ga(bits, bits/2, 1, 1);
	this->q = NTL::NextPrime(this->q, 1);
	this->N = p*q;
	this->phi = (p - 1) * (q - 1);
	do{
		this->e = ga(bits, bits/2, 1, 1);
	}while(mcdNTL(e, this->phi) != 1 || e >= this->N); //e debe ser menor que N
	this->d = inversaNTL(this->e, this->phi);
}
RSABlocks::RSABlocks(NTL::ZZ a, NTL::ZZ b){
	;
}
std::string RSABlocks::cifrar(std::string msj){
	string leng = zToString(this->N), c, original, tmp;
	long k = leng.size() - 1; ///k = digitos de N - 1s
	long i, found;
	bool euler;
	NTL::ZZ result, temp, ten;
	temp = this->e - NTL::to_ZZ(1);
	///Euler: a^{k*phi(N) + 1} === a mod n
	if (ntlModulo(temp, this->phi) == 0){ ///comprobando que se cumpla lo de arriba
		euler = true; ///si se cumple, result = a mod n
	} else ///si no, se realiza la potenciacion modular
		euler = false;
	for (i = 0; i < msj.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(msj[i]);
		if (found < 10){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
		}
		ostringstream conv;
		conv << found;
		original += conv.str(); ///guardamos ese numero en un string
	}
	ten = potenciacion(NTL::to_ZZ(10), k); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		for(short j = 0; j < k; j++){
			tmp += original[i+j]; ///saca el bloque de digitos de N - 1
		}
		stringstream convi(tmp);
		convi >> temp; ///string tmp to int (NTL) temp
		if (euler)
			result = ntlModulo(temp, this->N); //teorema de euler
		else
			result = ntlPotenModular(temp,this->e, this->N); //cifrado en si
		while (result  < ten){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten /= 10;
		}
		ostringstream conv;
		conv << result;
		c += conv.str();
	}
	return c;
}
std::string RSABlocks::descifra_mensaje(std::string c){
	string leng = zToString(this->N), d, ret, tmp;
	long k = leng.size() - 1;
	long i, found;
	bool euler;
	NTL::ZZ result, temp;
	temp = this->d - NTL::to_ZZ(1);
	///Euler: a^{k*phi(N) + 1} === a mod n
	if (ntlModulo(temp, this->phi) == 0){ ///comprobando que se cumpla lo de arriba
		euler = true; ///si se cumple, result = a mod n
	} else ///si no, se realiza la potenciacion modular
		euler = false;
	for(i = 0; i < c.size(); i+=k){
		tmp.clear();
		for(short j = 0; j < k; j++){
			tmp += c[i+j];
		}
		stringstream convi(tmp);
		convi >> temp; ///string tmp to int (NTL) temp
		if (euler)
			result = ntlModulo(temp, this->N); //teorema de euler
		else
			result = ntlPotenModular(temp,this->e, this->N); //cifrado en si
		ostringstream conv;
		conv << result;
		d += conv.str();
	}
	cout << "d: " << d << endl;
	for(i = 0; i < d.size(); i+=2){
		tmp.clear();
		for(short j = 0; j < 2; j++){
			tmp += d[i+j];
		}
		stringstream convi(tmp);
		convi >> found;
		ret += this->alfabeto[found];
	}
	return ret;
}
NTL::ZZ RSABlocks::getPubKey(){
	;
}
NTL::ZZ RSABlocks::getPrivKey(){
	;
}
void RSABlocks::setPubKey(NTL::ZZ){
	;
}
void RSABlocks::setPrivKey(NTL::ZZ){
	;
}
NTL::ZZ RSABlocks::getN(){
	;
}
NTL::ZZ RSABlocks::getPhi(){
	;
}
