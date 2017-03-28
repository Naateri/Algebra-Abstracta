#include <string>
class Cesar{
private:
	std::string alfabeto;
	int key;
public:
	Cesar(int k);
	std::string cifrar(std::string msj);
	std::string descifrar(std::string cifrado);
	int getKey();
	void setKey(int k);
};

