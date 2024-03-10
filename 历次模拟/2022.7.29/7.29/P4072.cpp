#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#define ll long long
using namespace std;
int n, m;
const int maxn = 3100;
ll f[maxn][maxn];
int a[maxn],s[maxn];
int que[maxn];
inline double slope(int u,int j,int k){
	return 1.0 * (f[u][j] - f[u][k] + s[j] * s[j] - s[k] * s[k]) * 1.0 / (s[j] - s[k]);
}//work out k

signed main(){
	scanf("%d",&n);
	memset(f,0x3f,sizeof(f));
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		s[i] = s[i - 1] + a[i];
		f[1][i] = s[i] * s[i];
	}
	int h , t;
	f[0][0] = 0;
	for(int p = 2;p <= m;p++){
		h = 1;t = 0;
		for(int i = 1;i <= n;i++){
			while(h < t && slope(p - 1,que[h],que[h + 1]) < 2 * s[i])h++;
			int j = que[h];
			f[p][i] = f[p - 1][j] + (s[j] - s[i]) * (s[j] - s[i]);
			while(h < t && slope(p - 1,que[t - 1],que[t]) > slope(p - 1,que[t],i))t--;
			que[++t] = i;
		}
	}
	printf("%lld",m * f[m][n] - s[n] * s[n]);
	return 0;
}

