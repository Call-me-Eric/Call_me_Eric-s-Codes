#include<cstdio>
#include<iostream>
using namespace std;
int n, m;
const int N = 111, M = 31;
int a[N];
int dp_min[N][N][M],dp_max[N][N][M];
int sum(int l,int r){
	return ((a[r] - a[l - 1]) % 10 + 10) % 10;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		a[i + n] = a[i];
	}
	for(int i = 1;i <= n * 2;i++){
		a[i] += a[i - 1];
	}
	int r = 0;
	for(int i = 1;i <= m;i++){
		for(int len = 1;len <= n;len++){
			for(int l = 1;l <= n;l++){
				r = l + len - 1;
				if(i == 1){
					dp_min[l][r][i] = dp_max[l][r][i] = sum(l, r);
				}
				else{
					dp_min[l][r][i] = 1e9;
					dp_max[l][r][i] =-1e9;
					for(int k = l + i - 1;k <= r;k++){/*前i-1份可以一份只有一个数*/
						dp_min[l][r][i] = min(dp_min[l][k - 1][i - 1] * sum(k,r),dp_min[l][r][i]);
						dp_max[l][r][i] = max(dp_max[l][k - 1][i - 1] * sum(k,r),dp_max[l][r][i]);
					}
				}
			}
		}
	}
	int minn = 1e9, maxx =-1e9;
	for(int i = 1;i <= n;i++){
		minn = min(minn,dp_min[i][i + n - 1][m]);
		maxx = max(maxx,dp_max[i][i + n - 1][m]);
	}
	printf("%d\n%d",minn,maxx);
	return 0;
}
