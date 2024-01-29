#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 300, maxm = 3000;
const double eps = 1e-8;
int n, W;
int w[maxn], t[maxn];
double f[maxm], val[maxn];

bool check(double mid){
    for(int i = 1;i <= W;i++)f[i] = -114514.0;
    for(int i = 1;i <= n;i++){val[i] = (double)t[i] - mid * (double)w[i];}
    f[0] = 0;
    for(int i = 1;i <= n;i++)
        for(int j = W;j >= 0;j--){
            if(j + w[i] >= W){f[W] = max(f[W],f[j] + val[i]);}
            else f[j + w[i]] = max(f[j + w[i]],f[j] + val[i]);
        }
    return f[W] >= 0;
}

signed main(){
    n = read(); W = read(); double l = 0, r = 0;
    for(int i = 1;i <= n;i++){w[i] = read(); t[i] = read();r += t[i];}

    double mid = 0;
    while(l + eps <= r){
        mid = (l + r) / 2.0;
        if(check(mid)){l = mid;}
        else r = mid;
    }
    printf("%d\n",(int)(l * 1000));
    return 0;
}