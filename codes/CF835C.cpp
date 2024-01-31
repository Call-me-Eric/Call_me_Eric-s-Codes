#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char  ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110, maxm = 1e5 + 10;
int cf[maxn][maxn][11];
int x[maxm], y[maxm], col[maxm];
int n, q, C;
signed main(){
    n = read(); q = read(); C = read() + 1;
    for(int i = 1;i <= n;i++){
        x[i] = read(); y[i] = read(); col[i] = read();
        for(int j = 0;j < C;j++){cf[x[i]][y[i]][j] += ((col[i] + j) % C);}
    }
    for(int k = 0;k < C;k++)
        for(int i = 1;i <= 100;i++)
            for(int j = 1;j <= 100;j++)
                cf[i][j][k] = (cf[i][j][k] + cf[i - 1][j][k] + cf[i][j - 1][k] - cf[i - 1][j - 1][k]);
    int t, xl, xr, yl, yr;
    for(int i = 1;i <= q;i++){
        t = read() % C; xl = read() - 1; yl = read() - 1; xr = read(); yr = read();
        printf("%d\n",cf[xr][yr][t] - cf[xr][yl][t] - cf[xl][yr][t] + cf[xl][yl][t]);
    }
    return 0;
}