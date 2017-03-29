//23-03-2017
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
#include <iostream>
#include <string>
#include "maths.h"
#include "rutas.h"
using namespace std;
Rutas::Rutas(int k){
	this->alfabeto = "abcdefghijklmnopqrstuvwxyz ";
	this->key = k;
}
string Rutas::cifrar(string msj){
	string messages[this->key]; //para guardar los mensajes
	string cifrado;
	bool sube; //para ver si sube
	int i = 0, j = 0, k;
	while(i < msj.length()){
		k = this->key -1;		
		cout << "Key - 1: " << k << endl;
		if (i == 0){	//primer paso
			messages[j] += msj[i];
			i++;
			j++;
			continue;		
		}
		if (j >= k) 
			sube = true;
		else sube = false;
		for(k; k > 0; k--){ //not always the same number of loops
			//messages[j] += msj[i];
			cout << "k: " << k << endl;			
			if (sube){ //booleano que debe mantenerse igual por k iteraciones				
				j--;
				messages[j] += msj[i];
				cout << "j: " << j << endl;
			}
			else{
				messages[j] += msj[i];
				j++;
				cout << "j: " << j << endl;
			}
			i++;
		}
		if (!sube)
			j--;
	}
	for (i = 0; i<this->key; i++)
		cifrado += messages[i];
	return cifrado;
}
string Rutas::descifrar(string cifrado){
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
	return descifrado;
}
int Rutas::getKey() {return this->key;}
void Rutas::setKey(int k) {this->key = k;}
