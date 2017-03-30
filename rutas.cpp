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
Mensaje descifrado:
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
		if (i == 0){//primer paso
			messages[j] += msj[i];
			i++;
			j++;
			continue;		
		}
		if (j >= k) 
			sube = true;
		else sube = false;
		//DEBUGGING cout << "New for loop\n";
		while(k > 0 && i < msj.size()){ //i < msj.size() por si no llena la 'matriz' 			
			if (sube){ //booleano que debe mantenerse igual por k iteraciones				
				j--;
				messages[j] += msj[i];
			}
			else{
				messages[j] += msj[i];
				j++;
			}
			cout << "j: " << j << endl;
			i++;
			k--;
		}
		if (i < msj.size()){ //porque puede que i ya sea igual al tamaño de msj
			if (sube) //para que no se repita el dato en messages[j]
				j++;
			else j--;
		}
		//DEBUGGING cout << "j una vez fuera del for: " << j << endl;
	}
	while (j > 0 && j < this->key - 1){ //llenando de X's
		if (sube){
			j--;
			messages[j] += "X";
		}
		else {
			j++;
			messages[j] += "X";
		}
	}
	for (i = 0; i<this->key; i++)
		cifrado += messages[i];
	return cifrado;
}
string Rutas::descifrar(string cifrado){
	string messages[this->key]; //para guardar los mensajes
	string descifrado, part; //guarda el descifrado
	int i = 0, j = 0, sizeofpart, k = 0;
	sizeofpart = cifrado.size()/this->key;
	j = sizeofpart-1;
	while(i<cifrado.size()){ //ordenando en los arrays
		if (sizeofpart == 1){ //loop cumple su funcion
			j = sizeofpart+1;
			part.clear();
			while(j>0 && i<cifrado.size()){
				part += cifrado[i];
				j--;
				i++;
			}
			messages[k] = part;
			k++;
		}
	}
	i = 0; j = 0; k = 0;
	while(i<cifrado.size()){ //infinite loop?
		bool regresa;
		//cout << "j: " << j << endl;
		if (j >= this->key){
			regresa = true;
			j--;
			cout << "j: " << j << endl;
		}
		else regresa = false;
		while(j < this->key && j >= 0 && i < cifrado.size()){
			cout << "j: " << j << endl;
			part = messages[j][k]; //j = celda, k = posicion en la palabra
			if (regresa){
				j--;
				part = messages[j];
				cout << "guardado en la parte " << j << ": " << part << endl;
				descifrado += part[k];
				i++;
			} else {
				part = messages[j];
				cout << "guardado en la parte " << j << ": " << part << endl;		
				descifrado += part[k];
				j++; i++;
			}
			if (part == "X"){ //omitir las X
				descifrado.erase(i); //borra la última que haya metido
			}
			cout << "descifrado por ahora: " << descifrado << endl;
		}
		k++;
	}
	/*for(i = 0; i<key; i++){
		if (messages[i] == "X")
			continue;
		descifrado += messages[i];
	}*/
	return descifrado;
}
int Rutas::getKey() {return this->key;}
void Rutas::setKey(int k) {this->key = k;}
