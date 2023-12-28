#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1e5 + 10;
int a[maxn];
double ans = 1;
signed main(){
    freopen("ill.in","r",stdin);
    freopen("ill.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
    }
    //E[1] = 1(选自己) + P(2)(选2) + P(3) + ... + P(n)
    //P(i) = a[i] / (a[i] + a[1]) (显然)
    for(int i = 2;i <= n;i++){
        ans += (double)a[i] / (a[1] + a[i]);
    }
    printf("%.3lf\n",ans);
    return 0;
}