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
		k = this->key -1; //cuanto "sube", cuanto "baja"
		if (i == 0){//primer paso
			messages[j] += msj[i];
			i++;
			j++;
			continue;		
		}
		if (j >= k) //si j es major a la clave-1, 'sube' 
			sube = true;
		else sube = false; //si no, "baja"
		while(k > 0 && i < msj.size()){ //i < msj.size() por si no llena la 'matriz'		
			if (sube){ //booleano que debe mantenerse igual por k iteraciones				
				j--;
				messages[j] += msj[i];
			}
			else{
				messages[j] += msj[i];
				j++;
			}
			i++; //siguiente letra 
			k--; //baja/sube una posicion más
		}
		if (i < msj.size()){ //porque puede que i ya sea igual al tamaño de msj
			if (sube) //para que no se repita el dato en messages[j]
				j++;
			else j--;
		}
	} //puede que no se haya llenado la fila de la "matriz"
	while (j > 0 && j < this->key - 1){ //llenando de X's
		if (sube) //para no sobreescribir
			j--;
		else //la posicion j del mensaje cifrado
			j++;
		messages[j] += "X";
	}
	for (i = 0; i<this->key; i++) //recorriendo el array de tamaño 'k' -> clave
		cifrado += messages[i];
	return cifrado;
}
string Rutas::descifrar(string cifrado){ //funciona en algunos casos (menos de una vuelta), en otros a medias
	string messages[this->key]; //para guardar los mensajes
	string descifrado, part; //guarda el descifrado
	char partComparison;
	int sizeofpart, j = 0;
	short i = 0, k = 0, zero = 0; //zero = 0 si solo ha dado una vuelta al descifrar
	sizeofpart = cifrado.size()/this->key; //2 casos: si es 1 o si no es 1
	while(i<cifrado.size()){ //ordenando en los arrays
		part.clear(); //borrando lo guardado en el string part		
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
			if (i < sizeofpart) //messages[0] guarda sizeofpart caracteres
				j = sizeofpart;
			else j = sizeofpart+1;	
			while(j>0 && i<cifrado.size()){ //&& porque messages[key-1] puede guardar menos caracteres
				part += cifrado[i]; //que j
				j--;
				i++;
			}
			messages[k] = part;
			k++;
		}
	}
	i = 0; j = 0; k = 0;
	while(i<cifrado.size()){ //empezando el descifrado en si
		bool regresa;
		if (j >= this->key){
			regresa = true;
			j--;
		} else {
			regresa = false;
			if (zero != 0) //no es la primera vez que j = 0
				j++;
			else zero++;
		}
		while(j < this->key && j >= 0 && i < cifrado.size()){ //j>0 no sale del loop
			//DEBUGGINGcout << "entering loop, j: " << j << endl;
			//DEBUGGINGcout << "valor de k: " << k << endl;
			if (regresa){ //si 'regresa' en el array
				//DEBUGGINGcout << "Regresa (-)\n";
				j--; //j = celda, k = posicion en la palabra
				if (j<0){
					j++;
					break;
				} 
				part = messages[j];
				//DEBUGGINGcout << "guardado en la parte " << j << ": " << part << endl;
			} else { //si 'avanza' en el array
				//DEBUGGINGcout << "!regresa (+)\n";
				part = messages[j];		
				j++;
			}
			descifrado += part[k];
			partComparison = part[k]; //guardando en char para poder comparar
			if (partComparison == 'X') //omitir las X
				descifrado.erase(descifrado.end()-1); //borra la última que haya metido si es que es X
			i++;
			//DEBUGGINGcout << "descifrado por ahora: " << descifrado << endl;
		}
		k++;
	}
	return descifrado;
}
int Rutas::getKey() {return this->key;}
void Rutas::setKey(int k) {this->key = k;}
