#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 300;
int n, m;
double pw[maxn], f[maxn][2];
signed main(){
    n = read(); m = read();pw[0] = 1;
    for(int i = 1;i <= n;i++)pw[i] = pw[i - 1] / (double)m;
    f[1][1] = 1;
    for(int i = 2;i <= n;i++){
        for(int j = 1;j < i;j++){
            f[i][0] += f[j][0] * (i - j) * pw[i - j - 1] * (1 - 2.0 / (double)m) + f[j][1] * (i - j) * pw[i - j - 1] * (1 - 1.0 / (double)m);
            f[i][1] += f[j][0] * (i - j) * pw[i - j];
        }
    }
    double ans = n * pw[n - 1];
    for(int i = 1;i < n;i++){
        ans += i * i * f[n - i + 1][0] * pw[i - 1];
    }
    printf("%.5lf\n",ans);
    return 0;
}