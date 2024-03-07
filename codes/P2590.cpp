#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 3e4 + 10;
int w[maxn];

int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int to = 0,int ne = 0):topoint(to),nextedge(ne){}
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int fa[maxn], son[maxn], dep[maxn], size[maxn];
int top[maxn], id[maxn], rev[maxn], total;
void dfs1(int u,int f){
    size[u] = 1;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        fa[v] = u; dep[v] = dep[u] + 1;
        dfs1(v,u); size[u] += size[v];
        son[u] = size[v] > size[son[u]] ? v : son[u];
    }
}
void dfs2(int u,int t){
    top[u] = t; id[u] = ++total; rev[total] = u;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u] || v == son[u])continue;
        dfs2(v,v);
    }
}

struct tree{
    int l, r, maxx, summ;
    tree(int l = 0,int r = 0,int m = 0,int s = 0):l(l),r(r),maxx(m),summ(s){}
}d[maxn << 2];
tree mergenode(tree l,tree r){return tree(l.l,r.r,max(l.maxx,r.maxx),l.summ + r.summ);}
void build(int l,int r,int p){
    if(l == r){d[p] = tree(l,r,w[rev[l]],w[rev[l]]);return;}
    int mid = l + r >> 1;
    build(l,mid,p << 1); build(mid + 1,r,p << 1 | 1);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}
tree query(int l,int r,int p){
    if(l <= d[p].l && d[p].r <= r){return d[p];}
    int mid = d[p].l + d[p].r >> 1;
    if(mid < l)return query(l,r,p << 1 | 1);
    else if(r <= mid)return query(l,r,p << 1);
    else return mergenode(query(l,r,p << 1),query(l,r,p << 1 | 1));
}
void update(int goal,int p,int k){
    if(d[p].l == goal && d[p].r == goal){d[p] = tree(d[p].l,d[p].r,k,k);return;}
    int mid = d[p].l + d[p].r >> 1;
    if(goal <= mid)update(goal,p << 1,k);
    else update(goal,p << 1 | 1,k);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}

void upd(int u,int k){update(id[u],1,k);}
int qsum(int u,int v){
    int sum = 0;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        sum += query(id[top[u]],id[u],1).summ;
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u,v);
    sum += query(id[u],id[v],1).summ;
    return sum;
}
int qmax(int u,int v){
    int sum = -0x3f3f3f3f;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        sum = max(sum, query(id[top[u]],id[u],1).maxx);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u,v);
    sum = max(sum,query(id[u],id[v],1).maxx);
    return sum;
}

signed main(){
    scanf("%d",&n);
    int u, v;char ch[10];
    for(int i = 1;i < n;i++){
        scanf("%d%d",&u,&v);
        add(u,v); add(v, u);
    }
    for(int i = 1;i <= n;i++)scanf("%d",&w[i]);
    dfs1(1,0); dfs2(1,1); build(1,n,1);
    scanf("%d",&m);
    for(int i = 1;i <= m;i++){
        scanf("%s%d%d",ch,&u,&v);
        if(ch[0] == 'C')upd(u,v);
        else if(ch[1] == 'S')printf("%d\n",qsum(u,v));
        else if(ch[1] == 'M') printf("%d\n",qmax(u,v));
    }
    return 0;
}