#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10,maxq = 5e5 + 10;
struct edge{
    int fr, to, tim;
    edge(int fr = 0,int to = 0,int tim = 0):fr(fr),to(to),tim(tim){}
    friend bool operator < (edge a,edge b){return a.tim > b.tim;}
}e[maxn];
int n, m, q;
int val[maxq], tim[maxq];
pair<int,int> opt[maxq];int tot;

vector<int> edg[maxq];
int cntpoint, id[maxq];
struct DSU{
    int fa[maxq];
    void init(int x){for(int i = 1;i <= x;i++)fa[i] = i;}
    int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
}dsu;

int fa[21][maxq], idx, dfn[maxq], siz[maxq], rev[maxq];
void dfs(int u,int f){
    dfn[u] = ++idx;siz[u] = 1;rev[idx] = u;
    for(int v : edg[u])
        if(v != f){
            if(tim[v] == 0)tim[v] = tim[u];
            dfs(v, u); siz[u] += siz[v];
        }
}
struct Segment_Tree{
    struct node{
        int maxx, pos;
        node(int mx = 0,int pos = 0):maxx(mx),pos(pos){}
    }d[maxq << 2];
    node mergenode(node l,node r){return node(max(l.maxx,r.maxx),((l.maxx > r.maxx) ? l.pos : r.pos));}
    void build(int l = 1,int r = idx,int p = 1){
        if(l == r){d[p] = node(val[rev[l]],l);return;}
        int mid = (l + r) >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = (l + r) >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p] = node(upd,0);return;}
        int mid = (l + r) >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int s,int t){return query(1,idx,s,t,1);}
    void update(int pos,int upd){update(1,idx,pos,1,upd);}
    void DEBUG(int l = 1,int r = idx,int p = 1){
        printf("l = %d r = %d p = %d,maxx = %d,pos = %d\n",l,r,p,d[p].maxx,d[p].pos);
        if(l == r)return;
        int mid = (l + r) >> 1;
        DEBUG(l,mid,p << 1);DEBUG(mid + 1,r,p << 1 | 1);
    }
}tree;

signed main(){
    n = read(); m = read(); q = read();int u, v;
    for(int i = 1;i <= n;i++){val[i] = read();fa[0][i] = i;}
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        e[i] = edge(u, v, m + 2);
    }
    for(int i = 1;i <= q;i++){
        u = read(); v = read();
        if(u == 1)opt[i - tot] = make_pair(v,tot);
        else e[v].tim = ++tot;
    }
    sort(e + 1,e + 1 + m);dsu.init(n + m);cntpoint = n;
    for(int i = 1;i <= m;i++){
        int fu = dsu.getf(e[i].fr), fv = dsu.getf(e[i].to);
        // printf("%d %d %d\n",e[i].fr,e[i].to,e[i].tim);
        if(fu == fv)continue; ++cntpoint;
        // puts("added");
        dsu.fa[fu] = dsu.fa[fv] = cntpoint;
        tim[cntpoint] = e[i].tim;val[cntpoint] = 0;
        edg[cntpoint].push_back(fu);edg[cntpoint].push_back(fv);
        fa[0][fu] = fa[0][fv] = cntpoint;
        fa[0][cntpoint] = cntpoint;
    }
    for(int i = 1;i <= 20;i++)
        for(int j = 1;j <= cntpoint;j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];

    for(int i = 1;i <= cntpoint;i++){
        if(!dfn[i]){
            u = i;
            for(int j = 20;j + 1;j--)
                if(fa[j][u] != u)u = fa[j][u];
            u = fa[0][u]; dfs(u, u);
        }
    }

    // for(int i = 1;i <= cntpoint;i++){
    //     printf("i = %d, siz[i] = %d, tim[i] = %d,val[i] = %d,dfn[i] = %d, rev[i] = %d,",i,siz[i],tim[i],val[i],dfn[i],rev[i]);
    //     for(int j = 0;j <= 3;j++)printf("fa[%d][%d]=%d,",j,i,fa[j][i]);puts("");
    //     for(int v : edg[i]) printf("-> %d ", v);puts("");
    // }

    tree.build();
    for(int i = 1;i <= q - tot;i++){
        u = opt[i].first, v = opt[i].second;
// printf("query :%d %d\n",u, v);
        if(tim[u] <= v){
            printf("%d\n",tree.query(dfn[u],dfn[u]).maxx);
            tree.update(dfn[u],0);
            continue;
        }
        for(int i = 20;i + 1;i--)
            if(tim[fa[i][u]] > v)
                u = fa[i][u];
        // u = fa[0][u];
// puts("Before query"); tree.DEBUG();
// printf("top = %d\n",u);
        Segment_Tree::node tmp = tree.query(dfn[u],dfn[u] + siz[u] - 1);
        printf("%d\n",tmp.maxx);
// puts("Before update");tree.DEBUG();
// printf("pos = %d,[%d,%d]\n",tmp.pos,dfn[u],dfn[u] + siz[u] - 1);
        if(tmp.maxx) tree.update(tmp.pos,0);
// puts("After update");tree.DEBUG();
    }

    return 0;
}