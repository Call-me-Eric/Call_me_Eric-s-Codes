#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, root;
int val[maxn];

vector<int> edg[maxn];

int dfn[maxn], idx;
int dep[maxn], siz[maxn], fa[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx;fa[u] = f;dep[u] = dep[f] + 1;siz[u] = 1;
    for(int v : edg[u]){if(v != f){dfs(v, u);siz[u] += siz[v];}}
}

signed main(){
    n = read();root = read();int u, v;
    for(int i = 1;i <= n;i++){val[i] = read();}
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(root,root);
    
    return 0;
}