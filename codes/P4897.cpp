#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x <<  3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 500 + 10, maxm = 3e3 + 10, INF = 0x3f3f3f3f;
int n, m;

struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm];
int head[maxn], tot = 1;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
void addd(int u,int v,int w){add(u, v, w);add(v, u, 0);}

int dis[maxn], cur[maxn];
queue<int> que;
bool bfs(int S,int T){
    for(int i = 0;i <= n;i++)dis[i] = INF, cur[i] = 0;
    while(!que.empty())que.pop();
    que.push(S);dis[S] = 0;cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                que.push(v);
            }
        }
    }
    return cur[T];
}
int dfs(int u,int rest,int T){
    if(u == T || !rest)return rest;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(dis[v] != dis[u] + 1 || e[i].cap <= e[i].flow)continue;
        int tmp = dfs(v,min(e[i].cap - e[i].flow,rest),T);
        if(!tmp){dis[v] = INF;}
        res += tmp;rest -= tmp;
        e[i].flow += tmp;e[i ^ 1].flow -= tmp;
        if(!rest)return res;
    }
    return res;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF, T);
    return mxflow;
}

pair<pair<int,int>, int> edges[maxm];

vector<pair<int,int> > edg[maxn];

void build(vector<int> vec){
    // for(int i : vec)printf("%d ",i);puts("");
    if(vec.size() == 1)return;
    int x = vec[0], y = vec[1];
    for(int i = 1;i <= n;i++)head[i] = 0;tot = 1;
    for(int i = 1;i <= m;i++){
        add(edges[i].first.first,edges[i].first.second,edges[i].second);
        add(edges[i].first.second,edges[i].first.first,edges[i].second);
    }
    int w = Dinic(x, y);
    edg[x].push_back(make_pair(y, w));
    edg[y].push_back(make_pair(x, w));
    vector<int> L, R;L.clear();R.clear();
    for(int i : vec){
        if(dis[i] != INF){L.push_back(i);}
        else R.push_back(i);
    }
    build(L);build(R);
}

int fa[21][maxn], minn[21][maxn], dep[maxn];
void dfs1(int u,int f){
    for(int i = 1;i <= 20;i++){
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
        minn[i][u] = min(minn[i - 1][u],minn[i - 1][fa[i - 1][u]]);
    }
    for(auto i : edg[u]){
        int v = i.first, w = i.second;
        if(v != f){fa[0][v] = u;minn[0][v] = w;dep[v] = dep[u] + 1;dfs1(v, u);}
    }
}

pair<int,int> LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    int ans = 0x3f3f3f3f;
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v]){
            ans = min(ans,minn[i][u]);
            u = fa[i][u];
        }
    if(u == v)return make_pair(u, ans);
    for(int i = 20;i + 1;i--){
        if(fa[i][u] != fa[i][v]){
            ans = min(ans,min(minn[i][v],minn[i][u]));
            u = fa[i][u]; v = fa[i][v];
        }
    }
    ans = min(ans,min(minn[0][u],minn[0][v]));
    return make_pair(fa[0][u],ans);
}

signed main(){
    n = read() + 1; m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read() + 1; v = read() + 1; w = read();
        edges[i] = make_pair(make_pair(u, v),w);
    }
    vector<int> tmp;tmp.clear();
    for(int i = 1;i <= n;i++)tmp.push_back(i);
    build(tmp);memset(minn,0x3f,sizeof(minn));
    dep[1] = 1;dfs1(1, 1);
    // for(int i = 1;i <= n;i++){
    //     for(auto j : edg[i]){
    //         printf("%d-%d %d\n",i,j.first,j.second);
    //     }
    // }
    for(int q = read();q;q--){
        u = read() + 1; v = read() + 1;
        printf("%d\n",LCA(u,v).second);
    }
    return 0;
}