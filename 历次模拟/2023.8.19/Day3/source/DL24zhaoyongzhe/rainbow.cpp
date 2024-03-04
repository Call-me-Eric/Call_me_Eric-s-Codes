#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 2e3 + 10;
int n, m;
int a[maxn][maxn];
bool col[maxn * maxn];
int f[maxn][maxn], ans;
signed main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			a[i][j] = read();
	for(int i = 1;i <= n;i++)f[i][1] = 1;
	for(int j = 1;j <= m;j++)f[1][j] = 1;
	ans = n + m - 1;
	for(int i = 2;i <= n;i++){
		for(int j = 2;j <= m;j++){
			memset(col,0,sizeof(col));
			col[a[i][j]] = 1;f[i][j] = 1;
			for(int k = 1, lim = min(f[i - 1][j - 1],min(i,j) - 1);k <= lim;k++){
				if(col[a[i][j - k]])break;col[a[i][j - k]] = 1;
				if(col[a[i - k][j]])break;col[a[i - k][j]] = 1;
				if(a[i - k + 1][j] != a[i - k][j - 1])break;
				if(a[i][j - k + 1] != a[i - 1][j - k])break;
				f[i][j]++;
			}
			ans += f[i][j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}

