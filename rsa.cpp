#include <iostream>
#include <string>
#include <ctime>
#include "rsa.h"
#include "maths.h"

using namespace std;

void RSA::generarClaves(){
	long p, q, e, phi;
}

RSA::RSA(){
	this->alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
	generarClaves();
}

string RSA::cifrar(string msj){
	string cifrado;
	char letra;
	int i, found, result;
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra); //la letra
		result = potencia(found,this->pubKey); //cifrado en si
		if (result > alfabeto.size())
			result = modulo(result, alfabeto.size());
		cifrado += alfabeto[result];
	}
	return cifrado;
	
}

string RSA::descifrar(string msj){
	;
}

long RSA::getPrivKey() {return this->privKey;}

long RSA::getPubKey() {return this->pubKey;}

int RSA::getAlfSize() {return this->alfabeto.size();}

void RSA::setPrivKey(long a) {this -> a = privKey;}

void RSA::setPubKey(long a) {this -> a = pubKey;}
