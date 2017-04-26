#include <string>
#include <vector>
#include <NTL/ZZ.h>
class RSA{
private:
	NTL::ZZ pubKey;
	NTL::ZZ privKey;
	NTL::ZZ phi;
	std::string alfabeto;
	void generarClaves();
public:
	RSA();
	RSA(NTL::ZZ publicKey, NTL::ZZ privateKey);
	std::vector<NTL::ZZ> cifrar(std::string msj);
	std::string descifrar(std::vector<NTL::ZZ> msj);
	NTL::ZZ getPubKey();
	NTL::ZZ getPrivKey();
	int getAlfSize();
	void setPubKey(NTL::ZZ);
	void setPrivKey(NTL::ZZ);
};
