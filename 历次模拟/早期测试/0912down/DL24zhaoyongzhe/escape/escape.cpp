#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e4 + 10;
int a[maxn];
int dep[maxn];
int f[maxn][30];
vector<int> e[maxn];
void dfs(int u,int fa){
    f[u][0] = fa;
    for(int i = 1;i <= 20;i++){
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for(int i = e[u].size() - 1;i >= 0;i--){
        int v = e[u][i];
        if(v == fa)continue;
        dep[v] = dep[u] + 1;
        dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    int k = dep[u] - dep[v];
    for(int i = 20;i >= 0;i--){
        if((k >> i) & 1){
            u = f[u][i];
        }
    }
    if(u == v)return u;
    for(int i = 20;i >= 0;i--){
        if(f[u][i] != f[v][i]){
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
int solve(int l,int r){
    vector<int> tmp;
    for(int i = l;i <= r;i++){
        for(int j = l;j <= r;j++){
            tmp.push_back(LCA(a[i],a[j]));
        }
    }
    sort(tmp.begin(),tmp.end());
    return unique(tmp.begin(),tmp.end()) - tmp.begin();
}
signed main(){
    freopen("escape.in","r",stdin);
    freopen("escape.out","w",stdout);
    int tmp = 0;
    n = read(); m = read();
    for(int i = 2;i <= n;i++){
        tmp = read();
        e[tmp].push_back(i);
    }
    for(int i = 1;i <= n;i++){
        a[i] = read();
    }
    dep[1] = 0;
    dfs(1,1);
    for(int i = 1;i <= m;i++){
        int l = read(), r = read();
        printf("%d\n",solve(l,r));
    }
    return 0;
}