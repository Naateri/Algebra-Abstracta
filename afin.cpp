#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include <time.h>
#include "afin.h"
#include "maths.h"
//trabajo 30-03-2017
//f(c) = M*a + b % alfabeto.length();
//f(d) = (inverso a) * (M - b) % alfabeto.length();

using namespace std;

void Afin::generarClaves(){
	int alt, a = 0, n;
	n = this->alfabeto.length();
	srand (time(NULL));
	while (a != 1){
		alt = rand() % 100 ; //random que va de 0 a 100
		a = mcd(n, alt);
	}
	cout << "valor final de a: " << alt << endl;
	this->a = alt;
	this->b = rand() % 100;
	//cout << "inversa de a: " << inversa(this->a, n) << endl;
}

Afin::Afin(){
	this -> alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,";
	generarClaves();
}

string Afin::cifrar(string msj){
	string cifrado;
	char letra;
	int i, found, result;
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra);
		result = (found * this->a) + this->b; //f(c)
		if (result > this->alfabeto.size())
			result = modulo(result, this->alfabeto.size());
		cifrado+=alfabeto[result];
	}
	return cifrado;
}

string Afin::descifrar(string msj){
	string descifrado;
	char letra;
	int i, found, result, inverso;
	inverso = inversa(this->a, this->alfabeto.size());
	for(i = 0; i < msj.size(); i++){
		letra = msj[i];
		found = this->alfabeto.find(letra);
		result = inverso * (found - this->b); //f(d)
		if (result > this->alfabeto.size() || result < 0)
			result = modulo(result, alfabeto.size());
		descifrado += alfabeto[result];
	}
	return descifrado;
}

int Afin::getA(){return this->a;}
int Afin::getB(){return this->b;}
int Afin::getAlfSize(){return this->alfabeto.size();}
void Afin::setA(int a) {this->a = a;}
void Afin::setB(int b) {this->b = b;}
