#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10;
int n, t;
double p, f[maxn][maxn];
signed main(){
    n = read();scanf("%lf",&p);t = read();
    f[0][0] = 1;
    for(int i = 1;i <= t;i++){
        f[i][0] = f[i - 1][0] * (1.0 - p);
        for(int j = 1;j <= n;j++){
            f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1.0 - p);
        }
        f[i][n] += f[i - 1][n] * p;
    }
    double ans = 0;
    for(int i = 0;i <= n;i++)ans += 1.0 * i * f[t][i];
    printf("%.7lf\n",ans);
    return 0;
}