#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e2 + 10;
int f[maxn][maxn][maxn];
int n;
int col[maxn], len[maxn];
int solve(int l,int r,int lx){
    int ln = len[r] + lx;
    if(f[l][r][lx] != -1)return f[l][r][lx];
    if(l == r)return ln * ln;
    int ans = solve(l,r - 1,0) + ln * ln;
    for(int k = l;k < r;k++){
        if(col[r] == col[k])ans = max(ans,solve(l,k,ln) + solve(k + 1,r - 1,0));
    }
    return f[l][r][lx] = ans;
}
signed main(){
    n = read();
    memset(f,-1,sizeof(f));
    for(int i = 1;i <= n;i++)col[i] = read();
    for(int i = 1;i <= n;i++)len[i] = read();
    printf("%lld\n",solve(1,n,0));
    return 0;
}