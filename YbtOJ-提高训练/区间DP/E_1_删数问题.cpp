#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n; const int maxn = 120;
int a[maxn], dp[maxn][maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
        dp[i][i] = a[i];
    }
    for(int k = 1;k <= n;k++){
        for(int i = 1;i + k <= n;i++){
            int maxl = abs(a[i] - a[i + k]) * (k + 1);
            for(int l = i;l < i + k;l++){maxl = max(maxl,dp[i][l] + dp[l + 1][i + k]);}
            dp[i][i + k] = maxl;
        }
    }
    printf("%d\n",dp[1][n]);
    return 0;
}