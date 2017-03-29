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
#include <stdlib.h>
#include "maths.h"
#include "rutas.h"
using namespace std;
int main(){
	string msj;
	int key;
	cout << "Ingrese su mensaje: ";
	getline(cin, msj);
	cout << "Ingrese la clave: ";
	cin >> key;
	Rutas Algoritmo(key);
	cout << "Objeto creado.\n";
	//Algoritmo.setKey(key);
	msj = Algoritmo.cifrar(msj);
	cout << "Mensaje cifrado: " << msj << endl;
	msj = Algoritmo.descifrar(msj);
	cout << "Mensaje descifrado: " << msj << endl;
	return 0;
}
