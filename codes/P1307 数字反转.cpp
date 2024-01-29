#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	int n, k = 0;
	cin >> n;
	while(n){
		k = k * 10 + n % 10;
		n = n / 10;
	}
	cout << k << endl;
	return 0;
}

