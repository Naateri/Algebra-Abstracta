#include <iostream>
#include <ctime>
//#include "maths.h" 
//descomentar si se va a incluir maths.h
using namespace std;

int modulo(int a, int n){ //a mod n
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

int lcg(int seed, int a = 214013, int c = 2531011, unsigned int m = 0x80000000){ //linear congruential algorithm
	seed = seed * a + c; 
	if (seed > m) //0x80000000 = 2^32
		seed = modulo(seed, m);
	return seed;
}

unsigned int lcgPer(int seed, int a = 214013, int c = 2531011, unsigned int m = 0x80000000){
	int sem = seed;
	unsigned int periodo;
	do{
		sem = sem*a;
		if (sem > m)
			sem = modulo(sem, m);
		periodo++;
	} while (sem != seed);
	return periodo;
}

int mcg(int seed, int a = 214013, unsigned int m = 0x80000000){ //multiple congruential algorithm
	seed *= a;  //0x80000000 = 2^32
	if (seed > m)
		seed = modulo(seed, m);
	return seed;
}

unsigned int mcgPer(int seed, int a = 214013, unsigned int m = 0x80000000){
	int sem = seed;
	unsigned int periodo;
	do{
		sem = sem*a;
		if (sem > m)
			sem = modulo(sem, m);
		periodo++;
	} while (sem != seed);
	return periodo;
}

int lfgSum(int seed, int j, int k, unsigned int m = 0x80000000){ //lagged fibonacci generator, $ = +
	seed = (seed - j) + (seed - k);
	if (seed > m)
		seed = modulo(seed, m);
	return seed;
}

unsigned int lfgSumPer(int seed, int j, int k, unsigned int m = 0x80000000){
	int sem = seed;
	unsigned int periodo;
	do{
		sem = (sem - j) + (sem - k);
		if (sem > m)
			sem = modulo(sem, m);
		periodo++;
	} while(sem != seed);
	return periodo;
}

int lfg(int seed, int j, int k){ //lagged fibonacci generator, $ = XOR
	seed = (seed - j) ^ (seed - k);
	return seed;
}

unsigned int lfgPer(int seed, int j, int k){
	int sem = seed;
	unsigned int periodo;
	do{
		sem = (sem - j) ^ (sem - k);
		periodo++;
	} while(sem != seed);
	return periodo;
}

int lfsr(int seed, int v){ //polinomio = x ^ 16 + x ^ 14 + x ^ 13 + x ^ 11 + 1 
	int Lfsr; //v = vueltas 
	short bit;
	Lfsr = seed;
	for (int i = 0; i < v; i++){
		bit  = ((Lfsr >> 0) ^ (Lfsr >> 2) ^ (Lfsr >> 3) ^ (Lfsr >> 5) ) & 1;
		Lfsr =  (Lfsr >> 1) | (bit << 15);
	}
	return Lfsr;
}

int lfsrPeriod(int seed){
	int Lfsr;
	unsigned int period;
	short bit;
	Lfsr = seed;
	do{
		bit  = ((Lfsr >> 0) ^ (Lfsr >> 2) ^ (Lfsr >> 3) ^ (Lfsr >> 5) ) & 1;
		Lfsr =  (Lfsr >> 1) | (bit << 15);
		period++;
	} while(Lfsr!=seed);
	return period;
}


int main(int argc, char *argv[]) {
	int seed = time(NULL);
	int LSFR = lfsr(seed, 10); //mientras mas vueltas dé, mÁs pequeño es el número
	cout << "LSFR: " << LSFR << endl;
	int LFG = lfg(seed, 40, 80);  //siempre da valores más pequeños que el resto de generadores
	//por lo menos con estos valores
	cout << "LFG: " << LFG << endl;
	int LFGSUM = lfgSum(seed, 40, 80); //mismo problema que con el MCG y el LCG, descrito abajo
	//posible solucion: cambiar el seed
	cout << "LFG Sum: " << LFGSUM << endl;
	int MCG = mcg(seed); //mientras no se cambien los valores de a y la semilla, va a sacar aleatorios similares
	//como la semilla en este caso es el tiempo del sistema, el valor aleatorio casi no va a variar
	cout << "MCG: " << MCG << endl;
	int LCG = lcg(seed); //casi lo mismo que el LCG
	cout << "LCG: " << LCG << endl;
	/*int LSFRP = lfsrPeriod(seed);
	cout << "LSFR Period: " << LSFRP << endl;
	no sale del loop luego de mas de un minuto, buen periodo?
	int MCGP = mcgPer(seed);
	cout << "MCG Period: " << MCGP << endl;
	*/
	
	return 0;
}

