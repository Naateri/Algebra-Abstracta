#include <iostream>
#include <string>
#include <ctime>
#include <NTL/ZZ.h>
#include "rsa.h"
#include "maths.h"

using namespace std;

void RSA::generarClaves(){
	NTL::ZZ p, q, e, N; //testear primalidad de p y q
	do{
		p = ga(16, 8, 1, 1);
	}while(NTL::ProbPrime(p, 1));
	do{
		q = ga(16, 8, 1, 1);
	}while(NTL::ProbPrime(q, 1));
	N = p*q;
	this->phi = (p - 1) * (q - 1);
	do{
		e = ga(32, 16, 1, 1);
	}while(mcdNTL(e, this->phi) != 1 || e >= N); //e debe ser menor que N
	this->pubKey = e;
	this->privKey = inversaNTL(e, this->phi);
}

RSA::RSA(){ //receptor
	this->alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
	generarClaves();
}

RSA::RSA(NTL::ZZ publicKey, NTL::ZZ privateKey){ //emisor
	this->alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
	this->pubKey = publicKey;
	NTL::ZZ mod;
	mod = (this->privKey - 1) * (this->pubKey - 1);//phi
	this->privKey = inversaNTL(this->pubKey, this->phi);
}

vector<NTL::ZZ> RSA::cifrar(string msj){
	vector<NTL::ZZ> cifrado;
	char letra;
	long i, found;
	NTL::ZZ result, foundCast;
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra); //la letra
		foundCast = found; //para que me deje usar la funcion con NTL
		result = ntlPotenModular(foundCast,this->pubKey, this->phi); //cifrado en si
		cifrado.push_back(result);
	}
	return cifrado;
	
}

string RSA::descifrar(vector<NTL::ZZ> msj){
	string descifrado;
	descifrado.clear();
	NTL::ZZ val, res;
	for(int i = 0; i < msj.size(); i++){
		val = msj.at(i);
		res = ntlPotenModular(val, this->privKey, this->phi);
		descifrado += this->alfabeto.at(NTL::to_int(res)); //castear res a int o val a int para llamar a potenmodular normal
	}
	return descifrado;
}

NTL::ZZ RSA::getPrivKey() {return this->privKey;}

NTL::ZZ RSA::getPubKey() {return this->pubKey;}

int RSA::getAlfSize() {return this->alfabeto.size();}

void RSA::setPrivKey(NTL::ZZ a) {this -> privKey = a;}

void RSA::setPubKey(NTL::ZZ a) {this -> pubKey = a;}
