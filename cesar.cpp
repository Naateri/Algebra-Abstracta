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
			letra = msj[i];
			found = alfabeto.find(letra);
			if (found > alfabeto.find('z')){
				cifrado += alfabeto[found]; //arreglar estoooo
				continue;
			}
			found += this->key;
			if (found > alfabeto.length() - 1)
				found = modulo(found, alfabeto.length() - 1);
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
			if (found > alfabeto.find('z')){
				descifrado += alfabeto[found]; //arreglar estooooooooo
				continue;
			}
			found -= this->key;
			if (found< 0){
				found = modulo(found, alfabeto.length()-1);
			}
			descifrado += alfabeto[found];
		}
		return descifrado;
	}
	int getKey() {return this->key;}
	void setKey(int k) {this->key = k;}
	
};
void acciones(){
	string mensaje, cifrado, descifrado;
	int key;
	cin >> key;
	while(mensaje != "0"){
		cout << "Ingrese su mensaje (0 para salir): ";
		getline(cin, mensaje);
		/*cout << "Ingrese clave: ";
		cin >> key;*/
		cout << "Mensaje original: " << mensaje << endl;
		Cesar Algoritmo(key);
		//Algoritmo.setKey(key);
		cifrado = Algoritmo.cifrar(mensaje);
		cout << "Clave: " << Algoritmo.getKey() << endl;
		cout << "Mensaje cifrado: " << cifrado << endl;
		descifrado = Algoritmo.descifrar(cifrado);
		cout << "Mensaje descifrado: " << descifrado << endl;
		//key = 0;
	}
	cout << "Hasta luego!\n";
}
	
int main() {
	acciones();
	return 0;
}

