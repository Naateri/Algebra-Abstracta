#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include "afin.h"
#include "maths.h"
using namespace std;

int main () {
	string msj, cifrado, descifrado;
	cout << "Ingrese su mensaje: ";
	getline(cin, msj);
	Afin Algoritmo;
	cout << "Clave A: " << Algoritmo.getA() << endl;
	cout << "Clave B: " << Algoritmo.getB() << endl;
	cifrado = Algoritmo.cifrar(msj);
	cout << "Mensaje cifrado: " << cifrado << endl;
	descifrado = Algoritmo.descifrar(cifrado);
	cout << "Mensaje descifrado: " << descifrado << endl;
	return 0;
}

