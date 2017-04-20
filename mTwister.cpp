#include <iostream>
#include <cstdlib>
using namespace std;

#define W 32
#define N 624
#define R 31
#define A 0x9908B0DF
#define F 18124332253
#define U 11
#define D 0xFFFFFFFF
#define S 7
#define B 0x9D2C5680
#define T 15
#define C 0xEFC60000
#define L 18
#define M 397
#define MASK_LOWER (1ull << R) - 1 //2^32 - 1
#define MASK_UPPER (1ull << R) //2^32

static int mt[N];
static short index;

int modulo(int a, int n){ //a mod n
	int q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

static void Initialize(unsigned int seed){
	unsigned int i;
	mt[0] = seed;
	for(i = 1; i < N; i++)
		mt[i] = (F * (mt[i-1] ^ (mt[i-1] >> 30)) + i);
	index = N;
}

static void Twist(){
	unsigned int i, x, xA;
	unsigned short suma;
	for (i = 0; i < N; i++){
		//if (i == N-1) i = 0; //para que no se salga del array
		x = (mt[i] & MASK_UPPER) + (mt[i+1] & MASK_LOWER);
		xA = x >> 1;
		if (x & 0x1) xA ^= A; //si x_0 es 1
		suma = i+N;
		if (suma >= N) suma = modulo(suma, N);
		mt[i] = mt[suma] ^ xA; //ecuacion 7
	}
	index = 0;
}

unsigned int getRand(){
	unsigned int y;
	int i;
	if (index >= N) Twist();
	i = index;
	y = mt[i];
	index = i + 1;
	cout << y << endl;
	y ^= (mt[i] >> U);
	y ^= (y << S) & B;
	y ^= (y << T) & C;
	y ^= (y >> L);
	return y;
}

int main(){
	Initialize(time(NULL));
	for (int i = 0; i < 20; i++){
		unsigned int a = getRand();
		cout << a << endl;
	}
	return 0;
}
