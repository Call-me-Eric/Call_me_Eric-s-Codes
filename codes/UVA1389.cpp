#include<bits/stdc++.h>
// #define int long long
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e2 + 10,maxm = 5e5 + 10, INF = 0x3f3f3f3f;
const double eps = 1e-10;
int n, m;
// double eps;

int head[maxm / 10], tot = 1;
struct edge{
    int to, nexte;double cap, flow;
    edge(int to = 0,int ne = 0,double ca = 0,double fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm * 2];
void add(int u,int v,double cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,double cap){add(u,v,cap);add(v, u, 0);}

int dep[maxm / 10], cur[maxm / 10];
double dfs(int u,double flow,int T){
    // printf("%lld\n",u);
    if(u == T || flow <= eps)return flow;
    double rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0)dep[v] = INF;
            e[i].flow += tmp; e[i ^ 1].flow -= tmp;
            flow -= tmp;rest += tmp;
            if(flow <= eps)return rest;
        }
    }
    return rest;
}
bool bfs(int S,int T){
    queue<int> que;
    for(int i = 1;i <= T;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
                que.push(v);cur[v] = head[v];dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
double Dinic(int S,int T){
    double mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}

pair<int,int> edg[maxm / 100];
int deg[maxn];
int S, T;
double getans(int mid){
    tot = 1;memset(head,0,sizeof(head));
    for(int i = 1;i <= m;i++)add(edg[i].first,edg[i].second,1),add(edg[i].second,edg[i].first,1);
    for(int i = 1;i <= n;i++){addd(S,i,m * 1.0);addd(i,T,1.0 * m + mid * 2.0 - deg[i]);}
    double x = Dinic(S,T);
    return x;
}

bool vis[maxn];
int ans = 0;
void dfs1(int u){
    vis[u] = 1;if(u != S)ans++;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(!vis[v] && e[i].cap - e[i].flow > eps) dfs1(v);
    }
}

void solve(){
    S = n + 1,T = n + 2;memset(deg,0,sizeof(deg));
    memset(vis,0,sizeof(vis));
    memset(edg,0,sizeof(edg));
    for(int i = 1;i <= m;i++){
        edg[i] = make_pair(read(),read());
        deg[edg[i].first]++;deg[edg[i].second]++;
    }
    double l = 0, r = m * 1.0, mid = 0;
    while(r - l > eps){
        mid = (r + l) / 2.0;
        if(m * n - getans(mid) > eps)l = mid;
        else r = mid;
    }
    getans(l); dfs1(S);

    if(ans == 0){puts("1\n1\n");return;}
    printf("%d\n",ans);
    for(int i = 1;i <= n;i++)if(vis[i])printf("%d\n",i);
    return;
}

signed main(){
    while(scanf("%d%d",&n,&m) != EOF)solve();
    return 0;
}