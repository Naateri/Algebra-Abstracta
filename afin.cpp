#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include "afin.h"
#include "maths.h"

//f(c) = M*a + modulo(b, alfabeto.length());
//f(d) = M*(inverso a) - modulo(b, alfabeto.length());

using namespace std;

void Afin::generarClaves(){
	int alt, a = 0, n;
	n = this->alfabeto.length();
	while (a != 1){
		cout << "a: " << a << endl;
		alt = (rand() % n + 1) - 1; //random que va de 0 a la longitud del alfabeto
		cout << "random: " << alt << endl;
		a = mcd(alt, n);
	}
	this->a = alt;
	this->b = rand() % alfabeto.size() + 1;
	cout << "inversa de a: " << inversa(a, alfabeto.size()) << endl;
}

Afin::Afin(){
	this -> alfabeto = "abcdefghijklmnopqrstuvwxyz ";
	generarClaves();
}

string Afin::cifrar(string msj){
	string letra, cifrado;
	int i, found, result;
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra);
		result = (found * this->a) + modulo(this->b, this->alfabeto.size()); //f(c)
		if (result > this->alfabeto.size())
			result = modulo(result, alfabeto.size());
		cifrado+=alfabeto[result];
	}
	return cifrado;
}

string Afin::descifrar(string msj){
	string letra, descifrado;
	int i, found, result, inverso;
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra);
		inverso = inversa(this->a, this->alfabeto.size());
		result = (found * inverso) - modulo(this->b, this->alfabeto.size()); //f(d)
		if (result > this->alfabeto.size() || result < 0)
			result = modulo(result, alfabeto.size());
		descifrado += alfabeto[result];
	}
	return descifrado;
}

int Afin::getA(){return this->a;}
int Afin::getB(){return this->b;}
