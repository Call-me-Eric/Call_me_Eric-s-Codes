#include <cstdio>
#include <iostream>
using namespace std;
int main() {
	int n , x, t, sum = 0;
	cin >> n >> x;
	for (int i = 1; i <= n; i++){
		int k = i;
		while (k){
		t = k % 10;
		if(t == x) sum ++;
		k /= 10;
		}
	}

	cout << sum;
	return 0;
} 
