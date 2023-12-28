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
const int maxk = 102,maxn = 1e5 + 10,MAXM = 200002;
int a[maxk];int dp[MAXM][maxk];
int dfs(int n, int now){
    if(n == 0)return 0;if(now == 1)return n / a[1];
    if(n < MAXM && dp[n][now])return dp[n][now];
    int ans = n / a[now] - dfs(n / a[now],now - 1) + dfs(n,now - 1);
    if(n < MAXM)dp[n][now] = ans;return ans;
}
signed main(){
    freopen("calc.in","r",stdin);
    freopen("calc.out","w",stdout);
    n  =read(); k = read();
    for(int i = 1;i <= k;i++){
        a[i] = read();
    }
    sort(a + 1,a + 1 + k);
    printf("%lld\n",n - dfs(n,k));
    return 0;
}