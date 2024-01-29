#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m;
vector<int> edg[maxn], son[maxn];

int col[maxn],color;
queue<int> que;

int fa[maxn],siz[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void mergef(int x,int y){
    int fx = fa[x], fy = fa[y];
    if(son[fx].size() < son[fy].size())swap(fx,fy);
    for(int v : son[fy]){fa[v] = fx;son[fx].push_back(v);}
    for(int v : edg[fy]){edg[fx].push_back(v);}
    if(edg[fx].size() > 1)que.push(fx);
}

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        edg[u].push_back(v);
    }
    for(int i = 1;i <= n;i++){
        siz[i] = 1;fa[i] = i;
        son[i].push_back(i);
        if(edg[i].size() > 1)que.push(i);
    }
    while(!que.empty()){
        u = que.front();que.pop();
        while(edg[u].size() > 1){
            v = edg[u][edg[u].size() - 1];edg[u].pop_back();
            if(fa[v] != fa[edg[u][edg[u].size() - 1]]){mergef(v,edg[u][edg[u].size() - 1]);}
        }
    }
    for(int i = 1;i <= n;i++){
        u = fa[i];
        if(!col[u])col[u] = ++color;
        printf("%d\n",col[u]);
    }
    return 0;
}