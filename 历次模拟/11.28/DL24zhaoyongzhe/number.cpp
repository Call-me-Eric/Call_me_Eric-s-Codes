#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10, maxk = 22;
int f[maxn][maxk];
int n, k, X;
int ans = 0x3f3f3f3f3f3f3f, a[maxn], b[maxn];
void dfs(int u){
	if(u == n + 1){
		int res = 0;
		for(int i = 1;i <= n;i++)
			for(int j = 1;j < i;j++)
				res = max(res,f[i][b[i]] + f[j][b[j]] + X * abs(b[i] - b[j]));
		if(res < ans){
			ans = res;
			for(int i = 1;i <= n;i++)a[i] = b[i];
		}
		return;
	}
	for(int i = 1;i <= k;i++){
		b[u] = i;
		dfs(u + 1);
		b[u] = 0;
	}
}
signed main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);	
	n = read(); k = read(); X = read();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= k;j++)
			f[i][j] = read();
	dfs(1);
	printf("%lld\n",ans);
	for(int i = 1;i <= n;i++)printf("%lld ",a[i]);
	return 0;
}
