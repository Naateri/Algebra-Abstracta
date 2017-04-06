#include <string>
class Afin{
private:
	int a, b; //claves
	std::string alfabeto;
	void generarClaves();
public:
	Afin();
	std::string cifrar(std:: string msj);
	std::string descifrar(std::string msj);
	int getA();
	int getB();
	int getAlfSize();
	void setA(int);
	void setB(int);
};
