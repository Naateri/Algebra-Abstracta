#include "cesar.h"
#include <string>
#include "maths.h"
using namespace std;
//Cifrado de Cesar
//Clave ingresada por el usuario
Cesar::Cesar(int k){
	this -> alfabeto = "abcdefghijklmnopqrstuvwxyz ";
	this -> key = k;
}
string Cesar::cifrar(string msj){
	int i = 0, found;
	string cifrado, letra;// = "";
	for (i; i<msj.length(); i++){
		letra = msj[i]; //letra del mensaje original
		found = alfabeto.find(letra); //letra encontrada en el alfabeto
		found += this->key;
		if (found >= alfabeto.length())
			found = modulo(found, alfabeto.length());
		cifrado += this->alfabeto[found];
	}
	return cifrado;
}
string Cesar::descifrar(string cifrado){ 
	int i = 0, found;
	string descifrado, letra;
	for (i; i<cifrado.length(); i++){
		letra = cifrado[i]; //letra en el mensaje cifrado
		found = alfabeto.find(letra); //letra encontrada en el alfabeto
		found -= this->key;
		if (found< 0)
			found = modulo(found, alfabeto.length());
		descifrado += this->alfabeto[found];
	}
	return descifrado;
}
int Cesar::getKey() {return this->key;}
void Cesar::setKey(int k) {this->key = k;}
