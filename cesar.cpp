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
	int generarClaves(){
		return rand() % 10 + 1;
	}
public:
	Cesar(){
		this -> alfabeto = "abcdefghijklmnopqrstuvwxyz ";
		this -> key = generarClaves();
	}
	string cifrar(string msj){
		int i = 0, found;
		string cifrado, letra;// = "";
		for (i; i<msj.length(); i++){
			letra = msj[i];
			found = alfabeto.find(letra);
			//cout << found << endl;
			if (found+key > alfabeto.length())
				found = modulo(found, alfabeto.length());
			cifrado += alfabeto[found];
			
		}
		return cifrado;
	}
	string descifrar(string cifrado){ 
		int i = 0, found;
		string descifrado, letra;
		for (i; i<cifrado.length(); i++){
			letra = cifrado[i];
			found = alfabeto.find(letra);
			if (found-key < 0){
				found = modulo(found, alfabeto.length());
			}
			descifrado += alfabeto[found];
		}
		return descifrado;
	}
	int getKey() {return this->key;}
	void setKey(int k) {this->key = k;}
	
};
void acciones(){
	string mensaje = "1", cifrado, descifrado;
	int key;
	while(mensaje != "0"){
		cout << "Ingrese su mensaje (0 para salir): ";
		getline(cin, mensaje);
		/*if (mensaje == "0")
			break;*/
		cout << "Mensaje original: " << mensaje << endl;
		Cesar Algoritmo;
		cout << "Ingrese clave: ";
		cin >> key;
		cifrado = Algoritmo.cifrar(mensaje);
		cout << "Clave: " << Algoritmo.getKey() << endl;
		cout << "Mensaje cifrado: " << cifrado << endl;
		descifrado = Algoritmo.descifrar(cifrado);
		cout << "Mensaje descifrado: " << descifrado << endl;
		mensaje = "";
	}
	cout << "Hasta luego!\n";
}
	
int main() {
	acciones();
	return 0;
}

