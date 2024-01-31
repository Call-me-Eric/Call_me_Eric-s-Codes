#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int t, N;
int A;
signed main(){
    t = read();N = read();
    A = (100LL * N) / t + ((100ll * N) % t ? 1ll : 0ll);
    printf("%lld\n",A + (t * A) / 100ll - 1ll);
    return 0;
}