#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 100 + 10, mod = 998244353;
int ans, val[maxn],dp[maxn][35][35][35];
int pw[maxn][35];
int C[maxn][maxn];
int popcount(int x){int cnt = 0;for(;x;x >>= 1)cnt += (x & 1);return cnt;}
int n, m, K;
signed main(){
    for(int i = 0;i <= 30;i++){C[i][0] = 1;}
    for(int i = 1;i <= 30;i++){
        for(int j = 1;j <= i;j++){
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    n = read(); m = read(); K = read();
    for(int i = 0;i <= m;i++){
        val[i] = read();
        pw[i][0] = 1;
        for(int j = 1;j <= n;j++){
            pw[i][j] = (pw[i][j - 1] * val[i]) % mod;
        }
    }
    dp[0][0][0][0] = 1;
    for(int i = 0;i <= m;i++)
    for(int j = 0;j <= n;j++)
    for(int k = 0;k <= K;k++)
    for(int p = 0;p <= n >> 1;p++)
    for(int t = 0;t <= n - j;t++)
        dp[i + 1][j + t][k + (t + p & 1)][t + p >> 1] = (dp[i + 1][j + t][k + (t + p & 1)][t + p >> 1] + dp[i][j][k][p] * pw[i][t] % mod * C[n - j][t] % mod) % mod;
    for(int k = 0;k <= K;k++){
        for(int p = 0;p <= n >> 1;p++){
            if(k + popcount(p) <= K){ans = (ans + dp[m + 1][n][k][p]) % mod;}
        }
    }
    printf("%lld\n",ans);
    return 0;
}