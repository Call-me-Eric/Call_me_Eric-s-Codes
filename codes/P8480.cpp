#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, tmp, mx, mn = 1e9;
int main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        tmp = read();
        mx = max(tmp, mx);
        mn = min(tmp, mn);
    }
    if(mx < 2)mx += 2,m--;
    printf("%lld\n",((1ll * mx) << m )- mn);
    return 0;
}