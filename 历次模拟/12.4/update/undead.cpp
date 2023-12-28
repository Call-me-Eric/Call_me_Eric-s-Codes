#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10,maxm = 1e5 + 10, mod = 998244353;
ll pw[maxm], inv[maxm];

ll qpow(ll x,int a){
    ll res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}

ll C(int x,int y){if(x < y)return 0;return pw[x] * inv[x - y] % mod * inv[y] % mod;}

int len;
struct query{
    int n, m, id;
    query(int n = 0,int m = 0,int id = 0):n(n),m(m),id(id){}
    friend bool operator < (query a,query b){
        if(a.n / len != b.n / len)return a.n < b.n;
        return ((a.n / len) & 1) ? a.m > b.m : a.m < b.m;
    }
}qry[maxm];

ll F, H, G;ll inv2;
void addn(ll n,ll m){
    H = (H + (n % 2 == 1) * C(n + 1,m)) % mod;
    F = (F + G - C(n, m) * ((n + m) % 2 == 0) + mod) % mod;
    G = (2 * G - C(n, m) + mod) % mod;
}
void deln(ll n,ll m){
    n--;
    H = (H - (n % 2 == 1) * C(n + 1, m) + mod) % mod;
    G = (G - C(n, m) + mod) % mod * inv2 % mod;
    F = (F - G + C(n ,m) * ((n + m) % 2 == 0) + mod) % mod;
}
void addm(ll n,ll m){
    G = (G + C(n, m + 1)) % mod;
    H = mod - H;
    H = (H + C(((n + 2) / 2) *  2,m + 2)) % mod;
    H = H * inv2 % mod;
    if((m + 1) & 1){F = (F + C(n + 1,m + 2)) % mod;F = (F - H + mod) % mod;}
    else F = (F + H) % mod;
}
void delm(ll n,ll m){
    m--;
    G = (G - C(n,m + 1) + mod) % mod;
    if((m + 1) & 1){F = (F - C(n + 1,m + 2)) % mod;F = (F + H) % mod;}
    else F = (F - H + mod) % mod;
    H = H * 2 % mod;
    H = (H - C(((n + 2) / 2) * 2,m + 2) + mod) % mod;
    H = mod - H;
}

ll ans[maxm];

signed main(){
    // freopen("undead.in","r",stdin);
    // freopen("undead.out","w",stdout);
    
    pw[0] = 1;inv[0] = 1;inv2 = qpow(2, mod - 2);
    for(int i = 1;i < maxm;i++)pw[i] = pw[i - 1] * i % mod;
    inv[maxm - 1] = qpow(pw[maxm - 1], mod - 2);
    for(int i = maxm - 2;i;i--)inv[i] = inv[i + 1] * (i + 1) % mod;

    int T = read();int mx = 0;
    for(int i = 1;i <= T;i++){
        int u = read(), v = read();
        mx = max(mx,max(u, v));
        qry[i] = query(u, v, i);
    }
    len = sqrt(mx);sort(qry + 1,qry + 1 + T);
    F = H = G = 1;int n = 0, m = 0;
    for(int i = 1;i <= T;i++){
        while(n < qry[i].n)addn(n++,m);
        while(m < qry[i].m)addm(n,m++);
        while(qry[i].n < n)deln(n--,m);
        while(qry[i].m < m)delm(n,m--);
        // printf("%d %d F = %lld, G = %lld, H = %lld\n",n,m,F,G,H);
        ans[qry[i].id] = F;
    }
    for(int i = 1;i <= T;i++)printf("%lld\n",ans[i]);
    return 0;
}
/*
4
0 0
1 0
2 0
2 1

10
0 0
2 1
9 2
10 3
26 8
60 8
202 161
2013 2016
10635 1080
75689 22265

*/