//23-03-2017
#include <iostream>
#include <string>
#include <stdlib.h>
#include "maths.h"

/*
mensaje: holacomoesta
clave: 4
h     m     X
 o   o o   a
  l c   e t
   a     s
Mensaje cifrado: 
hmXoooalcetas
Mensaje cifrado:
holacomoesta
*/
using namespace std;

class Rutas{
private:
	string alfabeto;
	int key;
	int generarClave(){
		return rand() % 5 + 1;
	}
public:
	AlgoritmoCifrado(){
		this->alfabeto = "abcdefghijklmnopqrstuvwxyz ";
		this->key = generarClave();
	}
	string cifrar(string msj){
		string messages[key]; //para guardar los mensajes
		string cifrado;
		bool baja; //para bajar
		int i = 0, j = 0, k = key-1;
		while(i < msj.length()){
			if (j >= key)
				baja = true;
			//messages[j] += msj[i];
			for(k; k > 0; k--){
				if (baja)
					j--;
				else 
					j++;
				messages[j] += msj[i];
				i++;
			}
		}
	}
	string descifrar(string cifrado){
		string messages[key];
		string descifrado;
		int i = 0, j = 0;
		for(i, j; i < cifrado.length(); i++, j++){
			if (j>=key)
				j--;
			messages[j] += cifrado[i];
		}
		for(i = 0; i<key; i++)
			descifrado += messages[i];
		return cifrado;
	}
	int getKey() {return this->key;}
	void setKey(int key) {this->key = k;}
};

int main(){
	string msj;
	int key;
	cout << "Ingrese su mensaje: ";
	getline(cin, msj);
	cout << "Ingrese la clave: ";
	cin >> key;
	Rutas Algoritmo;
	Algoritmo.setKey(key);
	msj = Algoritmo.cifrar(msj);
	cout << "Mensaje cifrado: " << msj << endl;
	msj = Algoritmo.descifrar(msj);
	cout << "Mensaje descifrado: " << msj << endl;
	return 0;
}
