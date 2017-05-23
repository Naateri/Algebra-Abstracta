#include <string>
#include <vector>
#include <NTL/ZZ.h>
class RSABlocks{
private:
	NTL::ZZ d;
	NTL::ZZ e;
	NTL::ZZ phi;
	NTL::ZZ p;
	NTL::ZZ q;
	NTL::ZZ N;
	std::string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
public:
	RSABlocks(int bits);
	RSABlocks(NTL::ZZ, NTL::ZZ);
	std::string cifrar(std::string msj);
	std::string descifra_mensaje(std::string c);
	NTL::ZZ getPubKey();
	NTL::ZZ getPrivKey();
	void setPubKey(NTL::ZZ);
	void setPrivKey(NTL::ZZ);
	NTL::ZZ getN();
	NTL::ZZ getPhi();
};
