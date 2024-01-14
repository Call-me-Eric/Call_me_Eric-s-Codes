#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e2 + 10;
int f[maxn][maxn], g[maxn][maxn];
int n, a[maxn];
void solve(){
	n = read();
	for(int i = 1;i <= n;i++){
		a[i] = read();f[i][i] = g[i][i] = 1;
	}
	for(int l = n;l;l--){
		for(int r = l + 1;r <= n;r++){
			f[l][r] = (a[r] < g[l + 1][r]) ? 1 : (f[l][r - 1] + a[r] - g[l + 1][r] + 1);
			g[l][r] = (a[l] < f[l][r - 1]) ? 1 : (g[l + 1][r] + a[l] - f[l][r - 1] + 1);
		}
	}
	puts(a[1] >= f[1][n] ? "First" : "Second");
}
signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
