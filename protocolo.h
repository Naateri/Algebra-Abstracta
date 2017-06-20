#include <iostream>
#include <string>
class Protocolo{
private:
	NTL::ZZ q; ///q del receptor
	NTL::ZZ myQ;
	NTL::ZZ g; ///g del receptor
	NTL::ZZ myG;
	NTL::ZZ p_1;
	NTL::ZZ p_2;
	NTL::ZZ N; ///N del receptor
	NTL::ZZ myN;
	NTL::ZZ e; ///e del receptor
	NTL::ZZ myE;
	NTL::ZZ d;
	NTL::ZZ a;
	std::string alfabeto = "abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789.,;:-_()@{}+/";
	public:
	Protocolo(int bits);
	std::string cifrar(std::string msj); //, std::string fm);
	std::string descifra_mensaje(std::string c);
	NTL::ZZ getE(); ///e del receptor
	void setE(NTL::ZZ);
	NTL::ZZ getN(); ///n del receptor
	void setN(NTL::ZZ); ///set N del receptor
	void setQ(NTL::ZZ); ///set Q del receptor
	NTL::ZZ getQ(); ///q del receptor
	void setG(NTL::ZZ); ///g del receptor
	NTL::ZZ getMyE();
	NTL::ZZ getMyN();
	NTL::ZZ getMyG();
	NTL::ZZ getMyQ();
};
