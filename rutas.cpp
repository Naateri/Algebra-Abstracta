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
		while(k > 0 && i < msj.size()){ //i < msj.size() por si no llena la 'matriz'		
			if (sube){ //booleano que debe mantenerse igual por k iteraciones				
				j--;
				messages[j] += msj[i];
			}
			else{
				messages[j] += msj[i];
				j++;
			}
			i++;
			k--;
		}
		if (i < msj.size()){ //porque puede que i ya sea igual al tamaño de msj
			if (sube) //para que no se repita el dato en messages[j]
				j++;
			else j--;
		}
	}
	while (j > 0 && j < this->key - 1){ //llenando de X's
		if (sube)
			j--;
		else
			j++;
		messages[j] += "X";
	}
	for (i = 0; i<this->key; i++)
		cifrado += messages[i];
	return cifrado;
}
string Rutas::descifrar(string cifrado){ //funciona hasta que da más de una 'vuelta'
	string messages[this->key]; //para guardar los mensajes
	string descifrado, part; //guarda el descifrado
	char partComparison;
	int sizeofpart, j = 0;
	short i = 0, k = 0, zero = 0; //zero = 0 si solo ha dado una vuelta al descifrar
	sizeofpart = cifrado.size()/this->key; //2 casos: si es 1 o si no es 1
	while(i<cifrado.size()){ //ordenando en los arrays
		part.clear();		
		if (sizeofpart == 1){
			j = sizeofpart+1;
			while(j>0 && i<cifrado.size()){
				part += cifrado[i];
				j--;
				i++;
			}
			messages[k] = part;
			k++;
		} else { //guarda el mensaje por partes en el array 
			if (i < sizeofpart) //messages[0] guarda sizeofpart-1 caracteres
				j = sizeofpart;
			else j = sizeofpart+1;	
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
	while(i<cifrado.size()){
		bool regresa;
		if (j >= this->key){
			regresa = true;
			j--;
			cout << "j: " << j << endl;
		} else {
			regresa = false;
			if (zero != 0){ //no es la primera vez que j = 0
				j++;
				}
			else zero++;
				//k++;
		}
		while(j < this->key && j >= 0 && i < cifrado.size()){ //j>0 no sale del loop
			cout << "entering loop, j: " << j << endl;
			cout << "valor de k: " << k << endl; //j = celda, k = posicion en la palabra
			if (regresa){
				cout << "Regresa (-)\n";
				j--;
				if (j<0)
					//j *= -1;
					break;
				part = messages[j];
				cout << "guardado en la parte " << j << ": " << part << endl;
				descifrado += part[k];
			} else {
				cout << "!regresa (+)\n";
				part = messages[j];
				cout << "guardado en la parte " << j << ": " << part << endl;		
				descifrado += part[k];
				j++;
			}
			i++;
			partComparison = part[k]; //guardando en char para poder comparar
			if (partComparison == 'X') //omitir las X
				descifrado.erase(descifrado.end()-1); //borra la última que haya metido
			cout << "descifrado por ahora: " << descifrado << endl;
		}
		k++;
	}
	return descifrado;
}
int Rutas::getKey() {return this->key;}
void Rutas::setKey(int k) {this->key = k;}
