#include <iostream>
#include <vector>
using namespace std;

long modulo(long a, long n){ //a mod n
	long q, r;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	return r;
}

vector<int> primos(int n){
	vector<int> res;
	int primo, cont;
	res.push_back(2);
	for (int i = 3; i < n; i++){
		cont = 0;
		for(int j = 0; j < res.size(); j++){
			primo = res.at(j);
			if (modulo(i, primo) ==0)
				cont++;
		}
		if (cont == 0)
			res.push_back(i);
	}
	return res;
}

int main(int argc, char *argv[]) {
	vector<int> primes;
	primes = primos(50);
	for (int i = 0; i < primes.size(); i++){
		cout << primes.at(i) << endl;
	}
	return 0;
}

