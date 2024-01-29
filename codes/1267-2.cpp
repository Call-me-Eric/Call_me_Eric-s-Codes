#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int f[101][101];
int c[101], w[101]; 
int main() {
	int n, W;
	scanf("%d%d",&W, &n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&w[i], &c[i]);
	}
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= W;j++){
			if(j >= w[i]){//只要能塞进去的统统塞进去，包括正好满。 
				f[i][j] = max(f[i - 1][j],f[i - 1][j - w[i]] + c[i]);
			}
			else
				f[i][j] = f[i - 1][j];
		}
	}
	printf("%d\n",f[n][W]);
	return 0;
}

