#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, K;
const int maxn = 255;
int f[maxn][maxn][21][21];
int logg[maxn];
signed main(){
    n = read(); m = read();K = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            f[i][j][0][0] = read();
    logg[0] = -1;
    for(int i = 1,len = max(n,m);i <= len;i++)logg[i] = logg[i >> 1] + 1;
    for(int k = 0;(1 << k) <= n;k++)
        for(int l = 0;(1 << l) <= m;l++)
            if(l || k)
            for(int i = 1;i + (1 << k) - 1 <= n;i++)
                for(int j = 1;j + (1 << l) - 1 <= m;j++){
                    if(k)f[i][j][k][l] = max(f[i][j][k - 1][l],f[i + (1 << k - 1)][j][k - 1][l]);
                    else f[i][j][k][l] = max(f[i][j][k][l - 1],f[i][j + (1 << l - 1)][k][l - 1]);
                }
    for(int i = 1;i <= K;i++){
        int x1 = read(), yy = read(), x2 = read(), y2 = read();
        int k1 = logg[x2 - x1 + 1], k2 = logg[y2 - yy + 1];
		printf("%d\n",max( max(f[x1][yy][k1][k2], f[x2 - (1 << k1) + 1][yy][k1][k2]),
		max(f[x1][y2 - (1 << k2) + 1][k1][k2],f[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2])));
    }
    return 0;
}