#include <iostream>
#include <string>
#include <ctime>
#include <NTL/ZZ.h>
#include "rsa.h"
#include "maths.h"

using namespace std;

void RSA::generarClaves(){
	NTL::ZZ e; //testear primalidad de p y q
	this->p = ga(1024, 32, 1, 1);
	this->p = NTL::NextPrime(this->p, 1);
	this->q = ga(1024, 32, 1, 1);
	this->q = NTL::NextPrime(this->q, 1);
	this->N = p*q;
	this->phi = (p - 1) * (q - 1);
	do{
		e = ga(1024, 32, 1, 1);
	}while(mcdNTL(e, this->phi) != 1 || e >= this->N); //e debe ser menor que N
	this->pubKey = e;
	this->privKey = inversaNTL(e, this->phi);
}

RSA::RSA(){ //receptor
	this->alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
	generarClaves();
}

RSA::RSA(NTL::ZZ publicKey, NTL::ZZ ene, NTL::ZZ fi){ //emisor
	this->alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
	this->pubKey = publicKey;
	this->N = ene;
	this->phi = fi;
}

vector<NTL::ZZ> RSA::cifrar(string msj){ //GUT
	vector<NTL::ZZ> cifrado;
	long i, found;
	bool euler;
	NTL::ZZ result, k, temp;
	temp = this->pubKey - NTL::to_ZZ(1);
	//k = temp / this->phi; //Euler: a^{k*phi(N) + 1} === a mod n
    if (ntlModulo(temp, this->phi) == 0){ //comprobando que se cumpla lo de arriba
            euler = true; //si se cumple, result = a mod n
    } else //si no, se realiza la potenciacion modular
        euler = false;
    for(i = 0; i < msj.size(); i++){
		found = this->alfabeto.find(msj.at(i)); //la letra
        if (euler)
            result = ntlModulo(NTL::to_ZZ(found), this->N); //teorema de euler
        else
            result = ntlPotenModular(NTL::to_ZZ(found),this->pubKey, this->N); //cifrado en si
		cifrado.push_back(result);
	}
	return cifrado;

}

string RSA::descifrar(vector<NTL::ZZ> msj){ //CHECK
	string descifrado;
	descifrado.clear();
	NTL::ZZ val, res, k, temp;
	bool euler;
	temp = this->privKey - NTL::to_ZZ(1);
	//k = temp / this->phi; //Euler: a^{k*phi(N) + 1} === a mod n
    if (ntlModulo(temp, this->phi) == 0){ //comprobando que se cumpla lo de arriba
        euler = true; //si se cumple, result = a mod n
    } else //si no, se realiza la potenciacion modular
        euler = false;
	for(int i = 0; i < msj.size(); i++){
		val = msj.at(i);
		if (euler){
            res = ntlModulo(val, this->N);
		} else {
            res = ntlPotenModular(val, this->privKey, this->N);
		}
        descifrado += this->alfabeto.at(NTL::to_int(res)); //castear res a int o val a int para llamar a potenmodular normal
	}
	return descifrado;
}

NTL::ZZ RSA::getPrivKey() {return this->privKey;}

NTL::ZZ RSA::getPubKey() {return this->pubKey;}

int RSA::getAlfSize() {return this->alfabeto.size();}

void RSA::setPrivKey(NTL::ZZ a) {this -> privKey = a;}

void RSA::setPubKey(NTL::ZZ a) {this -> pubKey = a;}

NTL::ZZ RSA::getN() {return this->N;}

NTL::ZZ RSA::getPhi() {return this->phi;}
