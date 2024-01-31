#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, INF = 0x3f3f3f3f;

int n, m;
vector<pair<int,int> > edg[maxn];

struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn << 3];
int head[maxn], tot = 1,S , T;
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}

int fa[maxn], siz[maxn], son[maxn],dep[maxn];
int edgid[maxn];//对每条边，存储在dep大的点上
void dfs1(int u,int f){
    fa[u] = f;dep[u] = dep[f] + 1;
    siz[u] = 1;son[u] = 0;
    for(auto i : edg[u]){
        int v = i.first;
        if(v != f){
            dfs1(v, u); siz[u] += siz[v];
            edgid[v] = i.second;
            son[u] = siz[son[u]] > siz[v] ? son[u] : v;
        }
    }
}
int top[maxn], dfn[maxn], idx, rev[maxn];//top重链顶端,dfn编号,rev[dfn[u]] = u
void dfs2(int u,int t){
    top[u] = t;dfn[u] = ++idx;rev[idx] = u;
    if(!son[u])return; dfs2(son[u],t);
    for(auto i : edg[u]){
        int v = i.first;
        if(v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

int id[maxn], cntpoint;
int rrev[maxn];//rrev[l]=p表示[l,r]在线段树上编号
struct Segment_Tree{
    int d[maxn];
    void build(int l,int r,int p){
        id[p] = ++cntpoint;
        if(l == r){addd(id[p],T,1);rrev[l] = p;return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        addd(id[p],id[p << 1],INF);addd(id[p],id[p << 1 | 1],INF);
    }
    void query(int l,int r,int s,int t,int p,int u){//opt=0 == u->[s,t],cap=INF;opt=1 == [s,t]->T,cap=t-s
        if(s <= l && r <= t){addd(u,id[p],INF);return;}
        int mid = l + r >> 1;
        if(s <= mid)query(l,mid,s,t,p << 1,u);
        if(mid < t)query(mid + 1,r,s,t,p << 1 | 1,u);
    }
    void query(int s,int t,int u){query(1,n,s,t,1,u);}
    void build1(int l = 1,int r = n,int p = 1){
        if(l == r){
            for(int i = head[id[p]];i;i = e[i].nexte)
                if(e[i].to == T){d[p] = e[i].flow;break;}
            return;
        }
        int mid = l + r >> 1;
        build1(l,mid,p << 1);build1(mid + 1,r,p << 1 | 1);
        d[p] = d[p << 1] + d[p << 1 | 1];
    }
    void DEBUG(int l = 1,int r = n,int p = 1){
        printf("[%d,%d], p = %d, id = %d\n",l,r,p,id[p]);
        if(l == r)return; int mid = l + r >> 1;
        DEBUG(l,mid,p << 1);DEBUG(mid + 1,r,p << 1 | 1);
    }
}tree;
void query(int u,int v,int to){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]])swap(u, v);
        tree.query(dfn[top[u]],dfn[u],to);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])swap(u, v);
    if(u == v)return;
    tree.query(dfn[son[u]],dfn[v],to);
}

int dis[maxn],cur[maxn];bool book[maxn];
queue<int> que;
bool bfs(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 0;i <= cntpoint;i++){dis[i] = INF;cur[i] = book[i] = 0;}
    dis[S] = 0;que.push(S);cur[S] = head[S];book[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                cur[v] = head[v];dis[v] = dis[u] + 1;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return dis[T] != INF;
}
int dfs(int u,int flow,int T){
    if(!flow || u == T)return flow;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(dis[v] == dis[u] + 1 && e[i].cap > e[i].flow){
            int tmp = dfs(v, min(flow,e[i].cap - e[i].flow),T);
            if(!tmp)dis[v] = INF;
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
        }
    }
    return res;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

vector<int> citizen, guard;
bool vis[maxn];
void dfs3(int u,int f){
    if(vis[u])return;vis[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(e[i].cap > e[i].flow)
            dfs3(v, u);
    }
}

signed main(){
    n = read(); m = read();int u, v;cntpoint = m;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(make_pair(v, i));
        edg[v].push_back(make_pair(u, i));
    }
    S = ++cntpoint;T = ++cntpoint;
    dfs1(1, 0);dfs2(1, 1);tree.build(1,n,1);
    
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        addd(S, i, 1); query(u, v, i);
    }
    
    int ans = Dinic(S,T);dfs3(S,S);
    for(int i = 1;i <= m;i++)
        if(!vis[i])citizen.push_back(i);
    for(int i = 2;i <= n;i++)
        if(vis[id[rrev[dfn[i]]]])guard.push_back(i);

    printf("%d\n",citizen.size() + guard.size());
    printf("%d",citizen.size());for(int i : citizen)printf(" %d",i);puts("");
    printf("%d",guard.size());for(int i : guard)printf(" %d",edgid[i]);puts("");

    // tree.DEBUG(); printf("ans = %d\n",ans);
    // for(int u = 1;u <= cntpoint;u++)
    //     for(int i = head[u];i;i = e[i].nexte)
    //         printf("%d -> %d, cap = %d, flow = %d\n",u,e[i].to,e[i].cap,e[i].flow);
    // for(int i = 1;i <= n;i++)
    //     printf("i=%d,fa=%d,siz=%d,son=%d,dep=%d,top=%d,dfn=%d,edgid=%d\n",i,fa[i],siz[i],son[i],dep[i],top[i],dfn[i],edgid[i]);
    return 0;
}