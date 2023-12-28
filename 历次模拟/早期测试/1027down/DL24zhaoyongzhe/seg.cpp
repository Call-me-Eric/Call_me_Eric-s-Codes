#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, k;
const int maxn = 510, P = 1e9 + 7;
int dp[maxn][maxn];
int pw[maxn];
signed main(){
    n = read(); k = read();
    for(int i = 0;i <= n;i++){
        dp[i][0] = 1;
    }
    pw[0] = 1;
    for(int i = 1;i <= n;i++){pw[i] = (pw[i - 1] * 2) % P;}
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= i;j++)
            for(int k = j - 1;k <= i;k++)
	            (dp[i][j] += dp[k][j - 1] * (pw[i - k] - 1) % P * pw[(i - k) * k] % P) %= P;
    printf("%lld\n",dp[n][k]);
    return 0;
}