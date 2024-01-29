#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, mod = 998244353;
int n, m, A;
int b[maxn];
int ans = 1;
int qpow(int x,int a){int res = 1;for(;a;a >>= 1,x = x * x % mod)if(a & 1)res = res * x % mod;return res;}
signed main(){
    n = read(); m = read(); A = read();
    for(int i = 1;i <= m;i++)b[i] = read();
    ans = qpow(A,n - b[m] - b[m]);int inv2 = qpow(2, mod - 2);
    for(int i = 1;i <= m;i++){
        int x = qpow(A,b[i] - b[i - 1]);
        ans = (ans * (x + x * (x - 1) % mod * inv2 % mod) % mod) % mod;
    }
    printf("%lld\n",ans);
    return 0;
}