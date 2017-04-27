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

vector<int> criba(int n){
	vector<int> res;
	int primo, i;
	for (i = 2; i <= n; i++){
		res.push_back(i);
	}
	i = 0;
	while(i < res.size()){
		for (int j = 0; j < res.size(); j++){
			if (modulo(res.at(j), res.at(i)) == 0 && res.at(j) != res.at(i))
				res.erase(res.begin() + j);
		}
		i++;
	}
	return res;
}

int main(int argc, char *argv[]) {
	vector<int> primes;
	primes = criba(50);
	for (int i = 0; i < primes.size(); i++){
		cout << primes.at(i) << endl;
	}
	return 0;
}

