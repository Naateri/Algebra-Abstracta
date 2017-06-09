#include <iostream>
#include <string>
class ElGamal{
private:
	NTL::ZZ p;
	NTL::ZZ e;
	NTL::ZZ d;
	NTL::ZZ e_2;
	NTL::ZZ r; //emisor
	NTL::ZZ C_1;
	NTL::ZZ K_M;
	std::string alfabeto = "0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFHIJKLMNOPQRSTUVWXYZ";
public:
	ElGamal(int bits);
	ElGamal(NTL::ZZ p, NTL::ZZ e, NTL::ZZ e2, int);
	std::string cifrar(std::string msj);
	std::string descifra_mensaje(std::string c);
	NTL::ZZ getP();
	NTL::ZZ getE();
	NTL::ZZ getE2();
	NTL::ZZ getC1();
	NTL::ZZ getD();
	void setP(NTL::ZZ p);
	void setC1(NTL::ZZ c1);
	void setD(NTL::ZZ d);
};
