#include <string>
class RSA{
private:
	long pubKey;
	long privKey;
	long N;
	std::string alfabeto;
	void generarClaves();
public:
	RSA();
	std::string cifrar(std::string msj);
	std::string descifrar(std::string msj);
	long getPubKey();
	long getPrivKey();
	int getAlfSize();
	void setPubKey(long);
	void setPrivKey(long);
};
