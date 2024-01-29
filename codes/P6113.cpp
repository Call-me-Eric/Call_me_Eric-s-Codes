#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, maxm = 1e5 + 10;

int n, m;
vector<int> edg[maxn];

struct DSU{
    int fa[maxn];
    void init(){for(int i = 1;i <= n;i++)fa[i] = i;}
    int getf(int x){return fa[x] != x ? fa[x] = getf(fa[x]) : x;}
}dsu;

int pre[maxn], match[maxn];
int vis[maxn], dfn[maxn], idx;
queue<int> que;
void blossom(int x,int y,int w){
    while(dsu.getf(x) != w){
        pre[x] = y;y = match[x];
        if(vis[y] == 2){vis[y] = 1;que.push(y);}
        if(dsu.getf(x) == x){dsu.fa[x] = w;}
        if(dsu.getf(y) == y){dsu.fa[y] = w;}
        x = pre[y];
    }
}
int LCA(int x,int y){
    for(++idx, x = dsu.getf(x), y = dsu.getf(y);dfn[x] != idx;){
        dfn[x] = idx;x = dsu.getf(pre[match[x]]);if(y)swap(x, y);
    }
    return x;
}
int dfs(int S){
    for(int i = 1;i <= n;i++){vis[i] = pre[i] = 0;}
    dsu.init();while(!que.empty())que.pop();
    que.push(S);vis[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int v : edg[u]){
            int w = 0;
            if(!(dsu.getf(u) == dsu.getf(v) || vis[v] == 2)){
                if(!vis[v]){
                    vis[v] = 2;pre[v] = u;
                    if(!match[v]){
                        for(int x = v, lst = 0;x;x = lst){
                            lst = match[pre[x]];match[x] = pre[x];match[pre[x]] = x;
                        }
                        return 1;
                    }
                    vis[match[v]] = 1;que.push(match[v]);
                }
                else{
                    blossom(u, v,w = LCA(u, v));
                    blossom(v, u, w);
                }
            }
        }
    }
    return 0;
}

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    int ans = 0;
    for(int i = n;i;i--){
        if(!match[i]){ans += dfs(i);}
    }
    printf("%d\n",ans);
    for(int i = 1;i <= n;i++)printf("%d ",match[i]);
    return 0;
}