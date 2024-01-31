#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 210, mod = 998244353;
int f[maxn][maxn][maxn][2][2];
int n, a[maxn], m,fac[maxn];
bool lim[maxn][maxn],line[maxn],row[maxn];
signed main(){
    fac[0] = 1; n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++){
        fac[i] = fac[i - 1] * i % mod;
        if(a[i] != -1){
            m++; lim[i][a[i]] = line[a[i]] = row[i] = 1;
        }
    }
    m = n - m;int *x;
    f[0][0][0][1][1] = 1;
    for(int i = 0;i <= n + 1;i++)for(int j = 0;j <= n + 1;j++)
        for(int k = 0;k <= m;k++)
            for(int a = 0;a < 2;a++)for(int b = 0;b < 2;b++){
                int t = f[i][j][k][a][b];if(!t || lim[i][j])continue;
                if(!lim[i + 1][j]){
                    x = &f[i + 1][j][k][row[i + 1]][b];
                    *x += t;if(*x > mod)*x -= mod;
                }
                if(!lim[i][j + 1]){
                    x = &f[i][j + 1][k][a][line[j + 1]];
                    *x += t;if(*x > mod)*x -= mod;
                }
                if(a || b)continue;

                if(!lim[i + 1][j]){
                    x = &f[i + 1][j][k + 1][row[i + 1]][1];
                    *x -= t;if(*x < 0)*x += mod;
                }
                if(!lim[i][j + 1]){
                    x = &f[i][j + 1][k + 1][1][line[j + 1]];
                    *x -= t;if(*x < 0)*x += mod;
                }
            }
    int ans = 0;
    for(int i = 0;i <= m;i++){ans = (ans + f[n + 1][n + 1][i][0][0] * fac[m - i]) % mod;}
    printf("%lld\n",ans);
    return 0;
}