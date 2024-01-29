#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int f[215];
int v, n, k;
int a[11][31], w[31], c[31], p; 
int main() {
	scanf("%d%d",&v,&n);
	scanf("%d",&k);
	for(int i = 1;i <= n;i++){
		scanf("%d%d%d",&w[i], &c[i], &p);
		a[p][ ++a[p][0] ] = i;
	}
	for(int p = 1;p <= k;p++){
		for(int i = v;i >= 0;i--){
			for(int j = 1;j <= a[p][0];j++){
				int tmp = a[p][j];
				if(i < w[tmp])continue;
				f[i] = max(f[i], f[i - w[tmp]] + c[tmp]);
			}
		}
	}
	printf("%d",f[v]);
	return 0;
}

