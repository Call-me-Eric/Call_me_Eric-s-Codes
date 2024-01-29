#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;

int val[maxn], n, m;

vector<int> edg[maxn];
int dfn[maxn], idx, siz[maxn],dep[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx;dep[u] = dep[f] + 1;siz[u] = 1;
    for(int v : edg[u])
        if(v != f){dfs(v, u); siz[u] += siz[v];}
}
inline int lowbit(int x){return x & (-x);}
struct BIT{
    int c[maxn << 2];
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
    int query(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}t1, t2;

signed main(){
    n = read(); m = read(); int u, v, opt;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v=  read();
        edg[u].push_back(v); edg[v].push_back(u);
    }
    dfs(1, 0);
    for(int i = 1;i <= m;i++){
        opt = read(); u = read();
        if(opt == 1){
            v = read();
            if(dep[u] & 1){t2.upd(dfn[u],v);t2.upd(dfn[u] + siz[u],-v);}
            else {t1.upd(dfn[u],v);t1.upd(dfn[u] + siz[u],-v);}
        }
        else{printf("%d\n",val[u] + (dep[u] & 1 ? -1 : 1) * (t1.query(dfn[u]) - t2.query(dfn[u])));}
    }
    return 0;
}