#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 70;
int n, m, r, g, b, mod;
int p[maxn];
int f[maxn][maxn][maxn];
int siz[maxn], tot;
bool book[maxn];
int calc(){
    for(int i = 1;i <= n;i++)book[i] = 0;
    for(int i = 0;i <= n;i++)
        for(int j = 0;j <= n;j++)
            for(int k = 0;k <= n;k++)
                f[i][j][k] = 0;
    tot = 0;
    for(int i = 1;i <= n;i++){
        if(!book[i]){
            tot++; int len = 0, u = i;
            while(!book[u]){book[u] = 1;u = p[u];len++;}
            siz[tot] = len;
        }
    }
    f[0][0][0] = 1;
    for(int l = 1;l <= tot;l++){
        for(int i = r;i + 1;i--){
            for(int j = g;j + 1;j--){
                for(int k = b;k + 1;k--){
                    if(i >= siz[l])f[i][j][k] += f[i - siz[l]][j][k];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                    if(j >= siz[l])f[i][j][k] += f[i][j - siz[l]][k];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                    if(k >= siz[l])f[i][j][k] += f[i][j][k - siz[l]];
                    if(f[i][j][k] >= mod)f[i][j][k] -= mod;
                }
            }
        }
    }
    return f[r][g][b];
}
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
signed main(){
    r = read(); g = read(); b = read(); m = read(); mod = read(); n = r + g + b;
    int ans = 0;
    for(int i = 1;i <= m;i++){
        for(int j = 1;j <= n;j++)p[j] = read();
        ans += calc();if(ans >= mod)ans -= mod;
    }
    for(int j = 1;j <= n;j++)p[j] = j;
    ans += calc();if(ans >= mod) ans -= mod;
    printf("%d\n",ans * qpow(m + 1,mod - 2) % mod);
    return 0;
}