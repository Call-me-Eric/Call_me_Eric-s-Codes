#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch  =getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
bool stmemory;
const int maxn = 1e3 + 10, maxk = 15, mod = 1e9 + 7;
int n, k, b[maxn];
char ch[maxn];
int f[2][maxn],st[1 << maxk][3];
int dp[2][1 << maxk][3];
const int nxt[3][3] = {{1,0,0},{1,2,0},{1,0,3}};
int ans[maxk + 1];

bool edmemory;
signed main(){
	cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost.\n";
	n = read(); k = read();
	scanf("%s",ch + 1);
	for(int i = 1;i <= n;i++){b[i] = (ch[i] == 'N' ? 0 : ch[i] == 'O' ? 1 : 2);}
	for(int sta = 0;sta < (1 << k);sta++){
		for(int i = 0;i < k;i++){f[0][i + 1] = f[0][i] + ((sta >> i) & 1);}
		for(int j = 0;j <= 2;j++){
			for(int i = 1;i <= k;i++){
				f[1][i] = max(f[1][i - 1],f[0][i]);
				if(b[i] == j){f[1][i] = max(f[1][i],1 + f[0][i - 1]);}
			}
			int t = 0;
			for(int i = 1;i <= k;i++){if(f[1][i] - f[1][i - 1]){t |= (1 << (i - 1));}}
			st[sta][j] = t;
		}
	}
	dp[1][0][0] = 1;
	for(int i = 1;i <= n;i++){
		memset(dp[(i & 1) ^ 1],0,sizeof(dp[(i & 1) ^ 1]));
		for(int sta = 0;sta < (1 << k);sta++){
			for(int j = 0;j <= 2;j++){
				for(int m = 0;m <= 2;m++){
					if(j == m && j == 2)continue;
					int l = nxt[j][m];int *x = &dp[(i & 1) ^ 1][st[sta][m]][l];
					*x += dp[i & 1][sta][j];if(*x > mod)*x -= mod;
				}
			}
		}
	}
	auto popcount = [](int x)->int{
		int cnt = 0;
		while(x){if(x & 1)cnt++;x >>= 1;}
		return cnt;
	};
	for(int sta = 0;sta < (1 << k);sta++){
		for(int j = 0;j <= 2;j++){
			int *x = &ans[popcount(sta)];
			*x += dp[(n & 1) ^ 1][sta][j];if(*x > mod)*x -= mod;
		}
	}
	for(int i = 0;i <= k;i++)printf("%d\n",ans[i]);
	return 0;
}
