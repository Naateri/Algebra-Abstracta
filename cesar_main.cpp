#include <iostream>
#include <string>
#include "cesar.h"
#include "maths.h"

using namespace std;

int main(){
	int key;
	string message, cifrado, descifrado;
	cout << "Ingrese su mensaje: ";
	getline(cin, message);
	cout << "Ingrese la clave: ";
	cin >> key;
	Cesar Algoritmo(key);
	std::cout << "Mensaje cifrado:\n";
	cifrado = Algoritmo.cifrar(message);
	std::cout << cifrado << endl;
	descifrado = Algoritmo.descifrar(cifrado);
	std::cout << "Mensaje descifrado\n" << descifrado << endl;
	
}
