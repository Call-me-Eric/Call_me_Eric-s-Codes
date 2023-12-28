#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1e5 + 10, maxm = 2e5 + 10;
struct edge{
    int frompoint, topoint, weight;
    edge(int fr = 0, int to = 0,int we = 0){frompoint = fr;topoint = to;weight = we;}
}e[maxm * 2];
bool operator < (edge a, edge b){return a.weight > b.weight;}
int fa[maxn], tot[maxn];
int getf(int x){if(fa[x] == x)return x;return fa[x] = getf(fa[x]);}
signed main(){
    n = read();m = read(); k = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        e[i] = edge(u,v,w);
    }
    for(int i = 1;i <= n;i++)fa[i] = i,tot[i] = 1;
    sort(e + 1,e + 1 + m);
    int cnt = k, ans = 0;
    for(int i = 1;i <= m;i++){
        int u = e[i].frompoint, v = e[i].topoint, w = e[i].weight;
        int fu = getf(u), fv = getf(v);
        int totu = tot[fu], totv = tot[fv];
        if(fu != fv){
            cnt -= totu * totv;
            tot[fu] += tot[fv];
            fa[fv] = fu;
            getf(fv);
            if(cnt <= 0){
                printf("%d\n",w);
                return 0;
            }
        }
    }
    return 0;
}