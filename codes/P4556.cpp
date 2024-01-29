#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 20;

struct node{
    int u, siz;node(int u = 0,int siz = 0):u(u),siz(siz){}
    friend bool operator < (node a,node b){return (a.siz == b.siz) ? a.u > b.u : a.siz < b.siz;}
    friend node operator + (node a,node b){return node(a.u,a.siz + b.siz);}
};
vector<node> vec[maxn];
struct Segment_Tree{
    int son[maxn * 40][2], total;
    node d[maxn * 40];
    void update(int l,int r,int p,node val){
        if(l + 1 == r){d[p] = val + d[p];return;}
        int mid = l + r >> 1;
        if(val.u <= mid)update(l,mid,(son[p][0] == 0) ? (son[p][0] = ++total) : son[p][0] ,val);
        else update(mid,r,(son[p][1] == 0) ? (son[p][1] = ++total) : son[p][1],val);
        d[p] = max(d[son[p][0]],d[son[p][1]]);
    }
    void mergetree(int l,int r,int p1,int p2){
        if(l + 1 == r){d[p1] = d[p1] + d[p2];return;}
        int mid = l + r >> 1;
        if(son[p1][0] && son[p2][0])mergetree(l,mid,son[p1][0],son[p2][0]);//都有左儿子
        else if(son[p2][0])son[p1][0] = son[p2][0];//p2有左儿子,p1与之合并
        //p1有左儿子,不需要合并(合并答案是p1)
        if(son[p1][1] && son[p2][1])mergetree(mid,r,son[p1][1],son[p2][1]);
        else if(son[p2][1])son[p1][1] = son[p2][1];//同理
        d[p1] = max(d[son[p1][0]],d[son[p1][1]]);
    }
}tree;

int head[maxn], tot;
struct edge{int to, nexte;edge(int to = 0,int ne = 0):to(to),nexte(ne){}}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int n, m, ans[maxn];

int fa[maxn][31], dep[maxn];
void dfs1(int u,int f){
    for(int i = 1;i <= 30;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == f)continue;
        fa[v][0] = u;dep[v] = dep[u] + 1;dfs1(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 30;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if(u == v)return u;
    for(int i = 30;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void dfs2(int u){
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == fa[u][0])continue;
        dfs2(v); tree.mergetree(0,maxn - 10,u,v);
    }
    for(auto it = vec[u].begin();it != vec[u].end();it ++){tree.update(0,maxn - 10,u,*it);}
    ans[u] = tree.d[u].u;
}

signed main(){
    n = read(); m = read(); int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v);add(v, u);
    }dep[1] = 1;
    dfs1(1,0);tree.total = n + 1;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();int lca = LCA(u,v);
        vec[u].push_back(node(w,1));vec[v].push_back(node(w,1));
        vec[lca].push_back(node(w,-1));vec[fa[lca][0]].push_back(node(w,-1));
    }
    dfs2(1);
    for(int i = 1;i <= n;i++){printf("%d\n",ans[i]);}
    return 0;
}