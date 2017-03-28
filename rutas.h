/*
mensaje: holacomoesta
clave: 4
h     m     X
 o   o o   a
  l c   e t
   a     s
Mensaje cifrado: 
hmXoooalcetas
Mensaje cifrado:
holacomoesta
*/

#include <string>
class Rutas{
private:
	std::string alfabeto;
	int key;
public:
	Rutas(int);
	std::string cifrar(std::string);
	std::string descifrar(std::string);
	int getKey();
	void setKey(int);
};


