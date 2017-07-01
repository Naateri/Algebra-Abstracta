#include "protocolo.h"
#include "maths.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <bitset>
#include <ctime>
#include <NTL/ZZ.h>
#include <opencv2/opencv.hpp>
using namespace std;

string Protocolo::firmarImagen(cv::Mat a){
	string RGB, lengMyQ = zToString(this->q), lengN = zToString(this->N), lengMyN = zToString(this->myN), temp, ret, ret2;
	if (lengN.size() == lengMyN.size()) cout << "Iguales pe\n";
	long MyQLength = lengMyQ.size() - 1, NLength = lengN.size() - 1, i, modd;
	NTL::ZZ rub, tmp, firma, ten, ten2;
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(NLength));
	RGB = getRGB(a);
	cout << "Original: " << RGB << endl;
	modd = modulo(RGB.size(), NLength);
	while (modd != 0){
		RGB = "0" + RGB;
		modd = modulo(RGB.size(), NLength);
	}
	//cout << "New original: " << RGB << endl;
	for(i = 0; i < RGB.size(); i+=NLength){
		cout << "Iter " << i << endl;
		/*if (i+NLength > RGB.size()){
		temp = RGB.substr(i, (RGB.size()- (i)));
		} else {*/
		temp = RGB.substr(i, NLength);
		//}
		tmp = stringToZZ(temp);
		rub = modExponentiation1(tmp, this->d, this->myN);
		/*if (rub > this->N){
		temp = zToString(rub);
		modd = modulo(temp.size(), NLength);
		while (modd != 0){
		temp = "0" + temp;
		modd = modulo(temp.size(), NLength);
		}
		for(int j = 0; j < temp.size(); j+=NLength){
		tmp = stringToZZ(temp.substr(j, NLength));
		firma = modExponentiation1(tmp, this->e, this->N);
		ten2 = ten;
		while(firma < ten2){ ///metiendo 0's para que el nro de digitos sea igual al tam de N-rec
		ret += "0";
		ten2 /= 10;
		}
		ret += zToString(firma);
		}
		} else {*/
		firma = modExponentiation1(rub, this->e, this->N); ///claves publicas del receptor
		ten2 = ten;
		while(firma < ten2){ ///metiendo 0's para que el nro de digitos sea igual al tam de N-rec
			ret += "0";
			ten2 /= 10;
		}
		ret += zToString(firma);
		//}
	}
	return ret;
}

string Protocolo::descifrarImagen(string img){
	string RGB, lengMyN = zToString(this->myN), lengQ = zToString(this->N), temp, ret, ret2;
	long MyNLength = lengMyN.size(), QLength = lengQ.size(), i;
	NTL::ZZ F, tmp, R, ten, ten2;
	ten = potenciacion(NTL::to_ZZ(10), MyNLength-NTL::to_ZZ(2));
	//i = img.size() - 9216;
	for(i = 0; i < img.size(); i+=MyNLength){
		cout << "iter: " << i << endl;
		temp = img.substr(i, MyNLength);
		tmp = stringToZZ(temp);
		F = modExponentiation1(tmp, this->d, this->myN);
		R = modExponentiation1(F, this->e, this->N);
		ten2 = ten;
		while(R < ten2){
			ret += "0";
			ten2 /= 10;
		}
		ret += zToString(R);
	}
	return ret;
	//return ret.substr(img.size() - 9216,9216);
}

Protocolo::Protocolo(int bits){
	NTL::ZZ phi;
	this->myQ = DES(bits);
	this->myQ = (this->myQ<<1) + 1;
	this->myG = findRoot(this->myQ);
	this->p_1 = DES(bits);
	this->p_2 = DES(bits);
	this->myN = this->p_1 * this->p_2;
	phi = (this->p_1 - 1) * (this->p_2 - 1);
	do{
		this->myE = ga(bits>>1, bits>>2, 1, 1);
	}while(mcdNTL(this->myE, phi) != 1); ///e siempre va a ser mayor que 1
	this->d = inversaNTL(this->myE, phi);
	do{
		this->a = ga(bits>>2, bits>>4, 1, 1); ///aleatorio para cifrar
	}while(this->a >= (this->myQ - 2));
	cout << "Claves generadas.\n";
}

string Protocolo::cifrar(string msj){
	long alfL = this->alfabeto.size();
	string leng = zToString(this->q), c, original, tmp, alfLeng = zToString(NTL::to_ZZ(alfL));
	long k = leng.size() - 1, modd, lengP, lengAlf = alfLeng.size()-1; ///k = digitos de N - 1s
	long i, found;
	NTL::ZZ result, temp, ten, ten2, ka, Ca;
	ka = modExponentiation1(this->g, this->a, this->q);
	Ca = modExponentiation1(this->a, this->e, this->N);
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(lengAlf));
	for (i = 0; i < msj.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(msj[i]);
		ten2 = ten;
		if (found < ten2){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
			ten2 /= 10;
		}
		original += zToString(NTL::to_ZZ(found));
	}
	modd = modulo(original.size(), k);
	while(modd != 0){ ///agrega "26" (espacio) mientras la long del texto
		original += "26"; ///en numeros no sea divisible entre la long de N-1
		modd = modulo(original.size(), k);
	}
	cout << "original: " << original << endl;
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(k)); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		ten2 = ten;
		tmp = original.substr(i, k);
		temp = stringToZZ(tmp);
		cout << "temp: " << temp << endl;
		result = ntlModulo((temp * ka), this->q);
		while (result  < ten2){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten2 /= 10;
		}
		c += zToString(result);
	}
	string ca = zToString(Ca), c0;
	k = ca.size();
	leng = zToString(this->N);
	while(k < leng.size()){
		c0 += "0";
		k++;
	}
	c0 += ca; ///c0 guarda el ca
	c0 += c;
	return c0;
}

string Protocolo::descifra_mensaje(string c){
	long alfL = this->alfabeto.size();
	string leng = zToString(this->myN), desi, ret, tmp, ca, alfLeng = zToString(NTL::to_ZZ(alfL));
	long k = leng.size(), lengAlf = alfLeng.size(); ///P Digitos
	long i, found;
	NTL::ZZ result, temp, ten, ten2, invKM, A, caN, ka;
	ca = c.substr(0, k);
	caN = stringToZZ(ca);
	A = modExponentiation1(caN, this->d, this->myN);
	ka = modExponentiation1(this->myG, A, this->myQ);
	invKM = inversaNTL(ka, this->myQ);
	i = k;
	leng = zToString(this->myQ);
	k = leng.size();
	ten = potenciacion(NTL::to_ZZ(10), k-NTL::to_ZZ(2)); ///10^{N-2} para ver si el numero es menor a eso
	for(i; i < c.size(); i+=k){
		tmp.clear(); ///borrando datos del string
		ten2 = ten;
		tmp = c.substr(i, k);
		temp = stringToZZ(tmp);
		result = ntlModulo((temp * invKM), this->myQ);
		while (result < ten2){ ///guardando en bloques N-1
			desi += "0";
			ten2 /= 10;
		}
		desi += zToString(result);
	}
	for(i = 0; i < desi.size(); i+=lengAlf){
		tmp.clear();
		tmp = desi.substr(i, lengAlf);
		found = NTL::to_long(stringToZZ(tmp));
		ret += this->alfabeto[found];
	}
	return ret;
}

NTL::ZZ Protocolo::getE(){return this->e;} ///e del receptor
void Protocolo::setE(NTL::ZZ e){this->e = e;}
NTL::ZZ Protocolo::getN(){return this->N;} ///n del receptor
void Protocolo::setN(NTL::ZZ n){this->N = n;} ///set N del receptor
void Protocolo::setQ(NTL::ZZ q){this->q = q;} ///set Q del receptor
NTL::ZZ Protocolo::getQ(){return this->q;} ///q del receptor
void Protocolo::setG(NTL::ZZ g){this->g = g;} ///g del receptor
NTL::ZZ Protocolo::getMyE() {return this->myE;}
NTL::ZZ Protocolo::getMyN() {return this->myN;}
NTL::ZZ Protocolo::getMyG() {return this->myG;}
NTL::ZZ Protocolo::getMyQ() {return this->myQ;}
