#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e2 + 10;
int n, m, k, a[maxn], p[maxn];
double f[maxn][maxn][maxn * 2];
signed main(){
    n = read(); m = read(); k = min(read(), n) + 2e2;
    for(int i = 1;i <= n;i++)p[i] = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    f[0][0][k] = 1;
    for(int i = 1;i <= n;i++)
        for(int j = 0;j <= n;j++)
            for(int k = 4e2;k + 1;k--){
                f[i][j][k] = f[i - 1][j][k] * (100.0 - p[i]) / 100.0;
                if(j != 0)f[i][j][k] += f[i - 1][j - 1][k - a[i]] * p[i] / 100.0;
            }
    double ans = 0;
    for(int j = m;j <= n;j++)
        for(int i = 2e2;i <= 4e2;i++)
            ans += f[n][j][i];
    printf("%.6lf\n",ans);
    return 0;
}