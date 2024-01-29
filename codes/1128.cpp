#include <math.h>
#include <cstdio>
using namespace std;
int a[101][101], b[101][101];
int main() {
	int n, m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&a[i][j]);
			b[i][j] = a[i][j];
		}
	}
	for(int i = 2;i <= n - 1;i++){
		for(int j = 2;j <= m - 1;j++){
			b[i][j] =  floor((b[i][j] + a[i - 1][j] + a[i + 1][j]
			 + a[i][j - 1] + a[i][j + 1]) / 5.0 + 0.5);
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

