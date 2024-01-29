#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
const int maxn = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;

int mapp[maxn];
int head[maxn], tot, we[maxn];
struct edge{
    int topoint, nextedge, weight, id;
    edge(int to = 0,int ne = 0,int we = 0,int i = 0):topoint(to),nextedge(ne),weight(we),id(i){}
}e[maxn * 2];
void add(int u,int v,int w,int i){e[++tot] = edge(v,head[u],w,i);head[u] = tot;}

int fa[maxn], son[maxn], dep[maxn], siz[maxn];
void dfs1(int u,int f){
    siz[u] = 1;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight, id = e[i].id;
        if(v == f)continue;
        fa[v] = u; dep[v] = dep[u] + 1;
        dfs1(v,u); siz[u] += siz[v];
        we[v] = w; mapp[id] = v;
        son[u] = siz[v] > siz[son[u]] ? v : son[u];
    }
}
int top[maxn], id[maxn], rev[maxn], ind;
void dfs2(int u,int t){
    top[u] = t; id[u] = ++ind; rev[ind] = u;
    if(!son[u])return; dfs2(son[u],t);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v != fa[u] && v != son[u])dfs2(v,v);
    }
}
struct node{
    int l, r, maxx, minn, summ; bool lazytag;
    node(int l = 0,int r = 0,int ma = 0,int mi = 0,int su = 0,
         bool lz = false):l(l),r(r),maxx(ma),minn(mi),summ(su),lazytag(lz){}
}d[maxn << 2];
void pushdown(int p){
    if(d[p].lazytag){
        d[p << 1].maxx = -d[p << 1].maxx;
        d[p << 1].minn = -d[p << 1].minn;
        d[p << 1].summ = -d[p << 1].summ;
        swap(d[p << 1].maxx,d[p << 1].minn);
        d[p << 1 | 1].maxx = -d[p << 1 | 1].maxx;
        d[p << 1 | 1].minn = -d[p << 1 | 1].minn;
        d[p << 1 | 1].summ = -d[p << 1 | 1].summ;
        swap(d[p << 1 | 1].maxx,d[p << 1 | 1].minn);
        d[p << 1].lazytag = !d[p << 1].lazytag;
        d[p << 1 | 1].lazytag = !d[p << 1 | 1].lazytag;
        d[p].lazytag = false;
    }
}
node mergenode(node l,node r){return node(l.l,r.r,max(l.maxx,r.maxx),min(l.minn,r.minn),l.summ + r.summ,false);}
void build(int l,int r,int p){
    if(l == r){d[p] = node(l,l,we[rev[l]],we[rev[l]],we[rev[l]],false);return;}
    int mid = l + r >> 1; build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}
void update(int goal,int p,int k){
    if(goal == d[p].l && d[p].l == d[p].r){d[p] = node(d[p].l,d[p].r,k,k,k,false);return;}
    pushdown(p); int mid = d[p].l + d[p].r >> 1;
    if(goal <= mid)update(goal,p << 1,k);
    else update(goal,p << 1 | 1,k);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}
node query(int l,int r,int p){
    if(l <= d[p].l && d[p].r <= r)return d[p];
    pushdown(p); int mid = d[p].l + d[p].r >> 1;
    if(mid < l)return query(l,r,p << 1 | 1);
    if(r <= mid)return query(l,r,p << 1);
    return mergenode(query(l,r,p << 1),query(l,r,p << 1 | 1));
}
void revtree(int l,int r,int p){
    if(l <= d[p].l && d[p].r <= r){
        // printf("l=%d,r=%d;but %d %d has changed\n",l,r,d[p].l,d[p].r);
        d[p].lazytag = !d[p].lazytag;
        d[p].maxx = -d[p].maxx;
        d[p].minn = -d[p].minn;
        d[p].summ = -d[p].summ;
        swap(d[p].maxx,d[p].minn);
        return;
    }
    pushdown(p); int mid = d[p].l + d[p].r >> 1;
    if(l <= mid)revtree(l,r,p << 1);
    if(mid < r)revtree(l,r,p << 1 | 1);
    d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
}

void reve(int u,int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        // printf("changed : id[%d]=%d to id[%d]=%d\n",top[u],id[top[u]],u,id[u]);
        revtree(id[top[u]],id[u],1);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u, v);
    if(u != v) revtree(id[son[u]],id[v],1);
}
int qsum(int u,int v){
    int sum = 0;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        sum += query(id[top[u]],id[u],1).summ;
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u, v);
    if(u != v) sum += query(id[son[u]],id[v],1).summ;
    return sum;
}
int qmax(int u,int v){
    int maxx = -INF;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        maxx = max(maxx,query(id[top[u]],id[u],1).maxx);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u, v);
    if(u != v) maxx = max(maxx,query(id[son[u]],id[v],1).maxx);
    return maxx;
}
int qmin(int u,int v){
    int minn = INF;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u,v);
        minn = min(minn,query(id[top[u]],id[u],1).minn);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u, v);
    if(u != v) minn = min(minn,query(id[son[u]],id[v],1).minn);
    return minn;
}

signed main(){
    scanf("%lld",&n); int u, v, w; char ch[10];
    for(int i = 1;i < n;i++){
        scanf("%lld%lld%lld",&u,&v,&w);u++;v++;
        add(u,v,w,i); add(v,u,w,i);
    }
    dfs1(1,0); dfs2(1,1); build(1,n,1);
    scanf("%lld",&m);
    for(int i = 1;i <= m;i++){
        scanf("%s",ch);scanf("%lld%lld",&u,&v);u++;v++;
        if(ch[0] == 'C'){update(id[mapp[u - 1]], 1, v - 1);}
        else if(ch[0] == 'N'){reve(u,v);}
        else if(ch[0] == 'S'){printf("%lld\n",qsum(u,v));}
        else if(ch[1] == 'A'){printf("%lld\n",qmax(u,v));}
        else if(ch[1] == 'I'){printf("%lld\n",qmin(u,v));}
    }
    // for(int i = 1;i <= n;i++){printf("id[%d] = %d,top[%d]=%d\n",i,id[i],i,top[i]);}
    return 0;
}
/*
12
0 1 12
1 2 -6
1 3 7
1 4 -7
4 8 6
8 9 1
8 10 6
9 11 -2
0 5 -3
5 6 6
5 7 3
20

4
0 1 3
1 2 5
1 3 5
12
N 3 0
SUM 0 0
MAX 1 1
MIN 0 0
C 3 9
N 2 0
SUM 2 1

*/