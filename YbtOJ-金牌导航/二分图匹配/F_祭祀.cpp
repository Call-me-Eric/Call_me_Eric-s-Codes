#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 128, INF = 0x3f3f3f3f, maxm = 300;
int n, m;
bitset<maxn> edg[maxn];

struct edge{
    int to, nexte, cap, flow;
    edge(int to  =0,int ne = 0,int we = 0,int flow = 0):to(to),nexte(ne),cap(we),flow(flow){}
}e[maxm * maxm * 3];
int head[maxm], tot = 1;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
void addd(int u,int v,int w){add(u, v, w);add(v, u, 0);}

int cur[maxm], dis[maxm];
queue<int> que;
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow; int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(dis[v] == dis[u] + 1 && e[i].cap > e[i].flow){
            int tmp = dfs(v, min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0){dis[v] = INF;}
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
            if(!flow)return res;
        }
    }
    return res;
}
bool bfs(int S,int T){
    for(int i = 1;i <= T;i++)cur[i] = 0, dis[i] = INF;
    while(!que.empty())que.pop();
    que.push(S);cur[S] = head[S];dis[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                que.push(v);
            }
        }
    }
    return dis[T] != INF;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){u = read(); v = read(); edg[u].set(v);}
    for(int i = 1;i <= n;i++)
        for(int k = 1;k <= n;k++)
            if(edg[i][k]) edg[i] = edg[i] | edg[k];
    // puts("1111");
    int S = n * 2 + 1, T = n * 2 + 2;
    for(int i = 1;i <= n;i++){
        addd(S,i,1);addd(i + n, T, 1);
        for(int j = 1;j <= n;j++)
            if(edg[i][j])addd(i,j + n,INF);
    }
    int res = Dinic(S,T);
    printf("%d\n",n - res);
    return 0;
}