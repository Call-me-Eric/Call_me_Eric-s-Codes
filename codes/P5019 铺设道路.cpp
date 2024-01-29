#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int main() {
	int n, now, last = 0, sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> now;
		if(now - last > 0) sum += now - last;
		last = now;
	}
	cout << sum << endl;
	return 0;
}

