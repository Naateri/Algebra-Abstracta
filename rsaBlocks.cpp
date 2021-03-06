#include <iostream>
#include <string>
#include <ctime>
#include <NTL/ZZ.h>
#include "rsaBlocks.h"
#include "maths.h"

using namespace std;

RSABlocks::RSABlocks(int bits){
	//testear primalidad de p y q
	NTL::ZZ pub;
	/*this->p = ga(bits, bits/2, 1, 1);
	this->p = NTL::NextPrime(this->p, 1);*/
	this->p = DES(bits);
	//this->p = NTL::NextPrime(this->p, 1);
	/*this->q = ga(bits, bits/2, 1, 1);
	this->q = NTL::NextPrime(this->q, 1);*/
	this->q = DES(bits);
	this->N = p*q;
	this->phi = (p - 1) * (q - 1);
	do{
		pub = ga(bits>>1, bits>>3, 1, 1);
	}while(mcdNTL(pub, this->phi) != 1 || pub >= this->N); //e debe ser menor que N
	this->e = pub;
	this->d = inversaNTL(pub, this->phi);
}
RSABlocks::RSABlocks(NTL::ZZ ee, NTL::ZZ eN){
	this->e = ee;
	this->N = eN;
	this->phi = this->e*this->N; ///valor temporal para no tener que modificar cifrado y euler
}
std::string RSABlocks::cifrar(std::string msj){
	long alfL = this->alfabeto.size();
	string leng = zToString(this->N), c, original, tmp, alfLeng = zToString(NTL::to_ZZ(alfL));
	long k = leng.size() - 1, modd, lengAlf = alfLeng.size()-1; ///k = digitos de N - 1s
	long i, found;
	bool euler;
	NTL::ZZ result, temp, ten, ten2;
	temp = this->e - NTL::to_ZZ(1);
	///Euler: a^{k*phi(N) + 1} === a mod n
	if (ntlModulo(temp, this->phi) == 0){ ///comprobando que se cumpla lo de arriba
		euler = true; ///si se cumple, result = a mod n
	} else ///si no, se realiza la potenciacion modular
		euler = false;
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(lengAlf));
	for (i = 0; i < msj.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(msj[i]);
		ten2 = ten;
		if (found < ten2){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
			ten2 /= 10;
		}
		original += zToString(NTL::to_ZZ(found)); ///guardamos ese numero en un string
	}
	modd = modulo(original.size(), k);
	while(modd != 0){ ///agrega "26" (espacio) mientras la long del texto
		original += "26"; ///en numeros no sea divisible entre la long de N
		modd = modulo(original.size(), k);
	}
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(k)); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		ten2 = ten;
		tmp = original.substr(i,k);
		temp = stringToZZ(tmp); ///string tmp to int (NTL) temp
		if (euler)
			result = ntlModulo(temp, this->N); //teorema de euler
		else
			result = modExponentiation1(temp, this->e, this->N); //cifrado en si
		while (result  < ten2){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten2 /= 10;
		}
		c += zToString(result); ///c + "result"
	}
	//modd = modulo(c.size() , k+1);
	return c;
}
std::string RSABlocks::descifra_mensaje(std::string c){
	long alfL = this->alfabeto.size();
	string leng = zToString(this->N), d, ret, tmp, alfLeng = zToString(NTL::to_ZZ(alfL));
	long k = leng.size(), lengAlf = alfLeng.size(); ///N Digitos
	long i, found;//, hundred = 100, hun;
	NTL::ZZ result, temp, ten, ten2;
	ten = potenciacion(NTL::to_ZZ(10), k-NTL::to_ZZ(2)); ///10^{N-2} para ver si el numero es menor a eso
	///Quisquater-Couvreur
	NTL::ZZ dp, dq;
	dp = ntlModulo(this->d, (this->p)-1);
	dq = ntlModulo(this->d, (this->q)-1);
	vector<NTL::ZZ> a, b, n;
	a.push_back(NTL::to_ZZ(1)); a.push_back(NTL::to_ZZ(1));
	n.push_back(this->p); n.push_back(this->q);
	for(i = 0; i < c.size(); i+=k){
		b.clear(); ///limpiando valores anteriores del vector
		tmp.clear(); ///borrando datos del string        //ten2 = ten;
		ten2 = ten;
		tmp = c.substr(i,k);
		temp = stringToZZ(tmp);///string tmp to int (NTL) temp
		b.push_back(modExponentiation1(temp, dp, p));
		b.push_back(modExponentiation1(temp, dq, q));
		result = TCR(a, b, n);
		while (result < ten2){ ///guardando en bloques N-1
			d += "0";
			ten2 /= 10;
		}
		d += zToString(result);
	}
	for(i = 0; i < d.size(); i+=lengAlf){
		tmp.clear();
		tmp = d.substr(i, lengAlf);
		found = NTL::to_int(stringToZZ(tmp));
		ret += this->alfabeto[found];
	}
	return ret;
}
NTL::ZZ RSABlocks::getPubKey(){
	return this->e;
}
NTL::ZZ RSABlocks::getPrivKey(){
	return this->d;
}
void RSABlocks::setPubKey(NTL::ZZ pub){
	this->e = pub;
}
void RSABlocks::setPrivKey(NTL::ZZ priv){
	this->d = priv;
}
NTL::ZZ RSABlocks::getN(){
	return this->N;
}
void RSABlocks::setN(NTL::ZZ n){
	this->N = n;
}
void RSABlocks::setP(NTL::ZZ pe){
	this->p = pe;
}
void RSABlocks::setQ(NTL::ZZ qu){
	this->q = qu;
}
NTL::ZZ RSABlocks::getQ(){return this->q;}
NTL::ZZ RSABlocks::getP(){return this->p;}
