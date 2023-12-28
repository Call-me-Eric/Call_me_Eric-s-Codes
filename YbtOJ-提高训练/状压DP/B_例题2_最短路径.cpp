#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 20;
int dp[1 << maxn][maxn];
int a[maxn][maxn];
signed main(){
    n = read();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            a[i][j] = read();
        }
    }
    memset(dp,0x3f,sizeof(dp));
    dp[1][0] = 0;
    for(int i = 0;i < (1 << n);i++){
        for(int j = 0;j < n;j++){
            if(!(i & (1 << j)))continue;
            for(int k = 0;k < n;k ++){
                if(!((i ^ (1 << j)) >> k) & 1)continue;
                dp[i][j] = min(dp[i][j],dp[i ^ (1 << j)][k] + a[j][k]);
            }
        }
    }
    printf("%d\n",dp[(1 << n) - 1][n - 1]);
    return 0;
}