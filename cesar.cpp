#include <iostream>
#include <string>
#include <stdlib.h>
#include "maths.h"
using namespace std;
//Cifrado de Cesar
//Clave ingresada por el usuario
class Cesar{
private:
	string alfabeto;
	int key;
	/*int generarClaves(){
		return rand() % 10 + 1;
	}*/
public:
	Cesar(int k){
		this -> alfabeto = "abcdefghijklmnopqrstuvwxyz ";
		this -> key = k;
	}
	string cifrar(string msj){
		int i = 0, found;
		string cifrado, letra;// = "";
		for (i; i<msj.length(); i++){
			letra = msj[i]; //letra del mensaje original
			found = alfabeto.find(letra); //letra encontrada en el alfabeto
			found += this->key;
			if (found > alfabeto.length())
				found = modulo(found, alfabeto.length());
			cifrado += this->alfabeto[found];
		}
		return cifrado;
	}
	string descifrar(string cifrado){ 
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
	int getKey() {return this->key;}
	void setKey(int k) {this->key = k;}
	
};
void acciones(){
	string mensaje, cifrado, descifrado;
	int key;
	//while(mensaje != "0"){
		cout << "Ingrese su mensaje: ";
		getline(cin, mensaje);
		cout << "Ingrese clave: ";
		cin >> key;
		cout << "Mensaje original: " << mensaje << endl;
		Cesar Algoritmo(key);
		//Algoritmo.setKey(key);
		cifrado = Algoritmo.cifrar(mensaje);
		cout << "Clave: " << Algoritmo.getKey() << endl;
		cout << "Mensaje cifrado: " << cifrado << endl;
		descifrado = Algoritmo.descifrar(cifrado);
		cout << "Mensaje descifrado: " << descifrado << endl;
	//}
}
	
int main() {
	acciones();
	return 0;
}

