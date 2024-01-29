#include <iostream>
#include <cstdio>
using namespace std;
int a[101][101], b[101][101];
int main() {
	int n, m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	int u;
	for(int i = 1, u = n;i <= n;i++, u--){
		for(int j = 1;j <= m;j++){
			b[j][u] = a[i][j];
		}
	}
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= n;j++){
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	return 0;
}

