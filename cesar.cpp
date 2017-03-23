#include <iostream>
#include <string>
#include <stdlib.h>
#include "maths.h"
using namespace std;
//Cifrado de Cesar
class Cesar{
private:
	string alfabeto;
	int key;
	int generarClaves(){
		return rand() % 10 + 1;
	}
public:
	Cesar(){
		this -> alfabeto = "abcdefghijklmnopqrstuvwxyz";
		this -> key = generarClaves();
	}
	string cifrar(string msj){
		int i = 0, found;
		string cifrado, letra;// = "";
		for (i; i<msj.length(); i++){
			letra = msj[i];
			if (letra == " "){
				cifrado += " ";
				continue;
			}
			found = alfabeto.find(letra);
			//cout << found << endl;
			if (found > alfabeto.length()){
				cout << "Error. Letra no encontrada.\n";
				msj = "Error.\n";
				return msj;
			}
			/*if (found+key > alfabeto.length()){
				//found -= alfabeto.length()
				found = modulo(found, alfabeto.length());
			}*/
			found = modulo(found+key, alfabeto.length());
			cifrado += alfabeto[found];
			
		}
		return cifrado;
	}
	string descifrar(string cifrado){ 
		int i = 0, found;
		string descifrado, letra;
		for (i; i<cifrado.length(); i++){
			letra = cifrado[i];
			if (letra == " "){
				descifrado += " ";
				continue;
			}
			found = alfabeto.find(letra);
			if (found > alfabeto.length()){
				cout << "Error. Letra no encontrada.\n";
				cifrado = "Error.\n";
				return cifrado;
			} 
			/*if (found-key < 0){
				//found += alfabeto.length();
				found = modulo(found, alfabeto.length());
			}*/
			found = modulo(found-key, alfabeto.length());
			descifrado += alfabeto[found];
		}
		return descifrado;
	}
	int getKey() {return this->key;}
	
	
};
void acciones(){
	string mensaje, cifrado, descifrado;
	do{
		cout << "Ingrese su mensaje (0 para salir): ";
		getline(cin, mensaje);
		/*if (mensaje == "0")
			break;*/
		cout << "Mensaje original: " << mensaje << endl;
		Cesar Algoritmo;
		cifrado = Algoritmo.cifrar(mensaje);
		cout << "Clave: " << Algoritmo.getKey() << endl;
		cout << "Mensaje cifrado: " << cifrado << endl;
		descifrado = Algoritmo.descifrar(cifrado);
		cout << "Mensaje descifrado: " << descifrado << endl;
		mensaje = "";
	}while(mensaje!="0");
}
	
int main() {
	acciones();
	return 0;
}

