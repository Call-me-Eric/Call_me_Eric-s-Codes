#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;

int fr[maxn], to[maxn];
vector<int> edg[maxn];

int dep[maxn], fa[maxn][31];
void dfs(int u,int f){
    for(int v : edg[u]){
        if(v == f)continue;
        fa[v][0] = u;dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int rev[maxn];

signed main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); fr[i] = u; to[i] = v;
        edg[u].push_back(v); edg[v].push_back(u);
    }
    dep[1] = 1;dfs(1, 0);
    
    for(int i = 1;i < n;i++){
        if(dep[fr[i]] > dep[to[i]])rev[i] = fr[i];
        else rev[i] = to[i];
    }


    return 0;
}