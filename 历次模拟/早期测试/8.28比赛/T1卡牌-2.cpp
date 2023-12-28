#include<bits/stdc++.h>
#define int long long
#define inf 0x7f7f7f7f7f7f
#define For(a,b,c) for(int a = (b);a <= (c);a++)
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, K, ans;
const int maxn = 100 + 10;
int v[maxn], t[maxn];
int dp[2][maxn][2610];
bool book[maxn];
signed main(){
    n = read(); K = read();
    int T = 2600;
    For(i,1,n){
        v[i] = read(); t[i] = read();
    }
    For(i, 0, 1) For(j, 0, K) For(k, 0, T) dp[i][j][k] = -inf;
    dp[0][0][2600] = 0; 
    For(i, 1, n){
	    For(j, 0, K){
    		For(k, 0, T) dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j][k]);
	    	For(k, t[i], T) dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j][k - t[i]] + v[i]);
		    For(k, 0, T - t[i]) dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j][k + t[i]] + v[i]);
    		if(j >= 1){
	    		For(k, 2 * t[i], T) dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j - 1][k - t[i] * 2] + v[i]);
		    	For(k, 0, T - 2 * t[i]) dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j - 1][k + t[i] * 2] + v[i]);
		    }
	    }
    }
    For(i, 0, K) ans = max(ans, dp[n & 1][i][2600]);
    printf("%lld", max(0LL,ans));

    return 0;
}