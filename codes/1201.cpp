#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int f[22]; 
int main() {
	f[1] = f[2] = 1;
	for(int i = 3;i <= 21;i++){
		f[i] = f[i - 1] + f[i - 2];
	}
	int n, t;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&t);
		printf("%d\n",f[t]);
	}
	return 0;
}

