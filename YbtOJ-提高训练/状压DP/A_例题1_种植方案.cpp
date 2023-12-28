#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 13, mod = 1e8;
int dp[1 << maxn][maxn];
int dirt[maxn][maxn];
int statement[maxn];
int start[1 << maxn], cnt;
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        statement[i] = 0;
        for(int j = 1;j <= m;j++){
            dirt[i][j] = read();
            statement[i] = (statement[i] << 1) + (!dirt[i][j]);
        }
    }
    for(int i = 0;i < (1 << m);i++){
        if(i & (i << 1) || i & (i >> 1))continue;
        start[++cnt] = i;
    }
    for(int i = 1;i <= cnt;i++){
        if(!(start[i] & statement[1])) dp[i][1] = 1;
    }
    for(int i = 2;i <= n;i++){
        for(int j = 1;j <= cnt;j++){
            if(start[j] & statement[i])continue;
            int sum = 0;
            for(int k = 1;k <= cnt;k++){
                if(start[k] & statement[i - 1] || start[j] & start[k])continue;
                sum += dp[k][i - 1];
                sum = sum % mod;
            }
            dp[j][i] = sum % mod;
        }
    }
    int ans = 0;
    for(int i = 1;i <= cnt;i++){
        ans = (ans + dp[i][n]) % mod;
    }
    printf("%lld\n",ans);
    return 0;
}