#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10, mod = 1e9 + 7;
int n, p[maxn];
struct BIT{
    int c[maxn << 2];
    inline int lowbit(int x){return x & (-x);}
    void add(int x,int upd){for(;x <= n;x += lowbit(x))c[x] += upd;}
    int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tree;
int d[maxn], sum[maxn];

int pw[maxn], invpw[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int C(int n,int m){return pw[n] * invpw[m] % mod * invpw[n - m] % mod;}

signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        p[i] = read();
        d[i] = p[i] - tree.qry(p[i]) - 1;
        tree.add(p[i],1);sum[i] = (sum[i - 1] + d[i]) % mod;
    }
    int ans = sum[n];

    pw[0] = 1;
    for(int i = 1;i <= 1e6;i++)pw[i] = pw[i - 1] * i % mod;
    invpw[(int)1e6] = qpow(pw[(int)1e6],mod - 2);
    for(int i = 1e6 - 1;i + 1;i--){invpw[i] = invpw[i + 1] * (i + 1) % mod;}

    for(int i = 1;i <= n;i++){
        ans = (ans + d[i] * C(n - i,2) % mod * C(n - i,2) % mod * pw[n - i - 2] % mod) % mod;
        ans = (ans + d[i] * (d[i] - 1) / 2 % mod * pw[n - i] % mod) % mod;
        ans = (ans + d[i] * pw[n - i] % mod * sum[i - 1] % mod) % mod;
    }
    printf("%lld\n",ans);
    return 0;
}