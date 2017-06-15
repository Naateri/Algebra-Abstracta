#include <string>
#include <vector>
#include <NTL/ZZ.h>
class RSABlocksFM{
private:
	NTL::ZZ d;
	NTL::ZZ e;
	NTL::ZZ phi;
	NTL::ZZ p;
	NTL::ZZ q;
	NTL::ZZ N;
	NTL::ZZ myE;
	NTL::ZZ myN;
	std::string alfabeto = "abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789.,;:-_()@{}+/";
	//std::string alfabeto = "0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJLMNOPQRSTUVWXYZ";
	public:
	RSABlocksFM(int bits);
	RSABlocksFM(NTL::ZZ, NTL::ZZ);
	std::string firmaDigital(std::string msj);
	std::string cifrar(std::string msj, std::string fm);
	std::string descifra_mensaje(std::string c);
	NTL::ZZ getPubKey();
	NTL::ZZ getPrivKey();
	void setPubKey(NTL::ZZ);
	void setPrivKey(NTL::ZZ);
	NTL::ZZ getN();
	void setN(NTL::ZZ);
	void setP(NTL::ZZ p);
	void setQ(NTL::ZZ q);
	NTL::ZZ getQ();
	NTL::ZZ getP();
	void setMyN(NTL::ZZ);
	void setMyE(NTL::ZZ);
	NTL::ZZ getMyN();
	NTL::ZZ getMyE();
};
