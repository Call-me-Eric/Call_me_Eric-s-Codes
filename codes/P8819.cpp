#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int w[maxn], r[maxn], g[maxn];//r[i]=>i的权值;w[i]=>i当前的入度和;g[i]=>i初始时的入度和
int n, m, q;
signed main(){
    n = read(); m = read();
    mt19937 rng(time(0));
    int now = 0, tot = 0, op = 0, u, v;
    for(int i = 1;i <= n;i++){r[i] = rng();tot += r[i];}
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        w[v] += r[u]; now += r[u]; g[v] = w[v];
    }
    q = read();
    for(int i = 1;i <= q;i++){
        op = read(); u = read();
        if(op == 1){v = read();w[v] -= r[u]; now -= r[u];}
        else if(op == 2){now -= w[u];w[u] = 0;}
        else if(op == 3){v = read();w[v] += r[u]; now += r[u];}
        else {now += g[u] - w[u];w[u] = g[u];}
        puts(now == tot ? "YES" : "NO");
    }
    return 0;
}