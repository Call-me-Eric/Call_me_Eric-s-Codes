#include <cstdio>
#include <iostream>
using namespace std;
int n, _k;
long long c, f[11][11], a[11][11];//f[i][j]表示在前i位插入j个乘号获得的最大值
int main() {
	scanf("%d%d%lld",&n, &_k, &c);
	for(int i = n;i >= 1;i--){
		a[i][i] = c % 10;
		c /= 10;
	}
	for(int i = 2;i <= n;i++){
		for(int j = i - 1;j >= 1;j--){
			a[j][i] = a[j][i - 1] * 10 + a[i][i];
		}
	}
	for(int i = 1;i <= n;i++){
		f[i][0] = a[1][i];
	}
	for(int k = 1;k <= _k;k++){
		for(int i = k + 1;i <= n;i++){
			for(int j = k;j < i;j++){
				f[i][k] = max(f[i][k],f[j][k - 1] * a[j + 1][i]);
			}
		}
	}
	printf("%lld",f[n][_k]);
	return 0;
}

