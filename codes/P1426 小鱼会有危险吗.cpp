#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	double v = 7, s, x, sum = 0;
	cin >> s >> x;
	while(sum < s - x){
		sum += v;
		v *= 0.98;
	}
	if(v * 0.98 < s + x - sum)
		cout << 'y';
	else 
		cout << 'n';
	return 0;
}

