#include <iostream>
#include <cstdio>
using namespace std;

const int f[10] = {6,2,5,5,4,5,6,3,7,6};

int fun(int x){
	int num = 0;
	while(x / 10 != 0){
		num += f[x % 10];
		x /= 10;
	}
	num += f[x];
	return num;
}

int main(){
	ios::sync_with_stdio(false);
	int a, b, c, m, sum = 0;
	cin >> m;
	for(a = 0;a <= 711;a++){
		for(b = 0;b <= 711;b++){
			c = a + b;
			if(fun(a) + fun(b) + fun(c) == m - 4)
				sum++;
		}
	}
	cout << sum;
	return 0;
}

