#include <iostream>
#include <string>
#include <stdlib.h>
#include "maths.h"
#include "cesar.h"
using namespace std;
//Cifrado de Cesar
//Clave ingresada por el usuario
	
int main() {
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
	return 0;
}

