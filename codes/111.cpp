#include <iostream>
#include <cstdio>
using namespace std;
int f[10];
int main(){
	int x = 123, y =246, z = 369;
	for(int i = 1; i <= 3; i++){
		f[x%10] ++; f[y%10] ++; f[z%10]++;
		x /= 10; y /= 10; z/= 10;
	}
	for(int i = 1; i <= 9; i++)
		cout << f[i];
	return 0;
}

