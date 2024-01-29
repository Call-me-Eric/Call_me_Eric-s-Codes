#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn * 8];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}

int dis[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dis[v] == dis[u] + 1)){
            tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0)dis[v] = INF;
            e[i].flow += tmp; e[i ^ 1].flow -= tmp;
            flow -= tmp;rest += tmp;
            if(!flow)return rest;
        }
    }
    return rest;
}
bool bfs(int S,int T){
    queue<int> que;
    for(int i = 1;i <= T;i++){dis[i] = INF;cur[i] = 0;}
    que.push(S);dis[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dis[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dis[v] = dis[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}

vector<int> edg[maxn];
int dep[maxn];
void dfs1(int u,int f){for(int v : edg[u])if(v != f){dep[v] = dep[u] + 1;dfs1(v, u);}}

signed main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dep[1] = 1;dfs1(1, 1);int S = n + 1, T = n + 2;
    for(int i = 1;i <= n;i++){
        if(dep[i] & 1){
            addd(S,i,1);
            for(int v : edg[i]){addd(i,v,INF);}
        }
        else addd(i,T,1);
    }
    // int tmp = Dinic(S,T);printf("%d\n",tmp);
    if(Dinic(S,T) * 2 != n){puts("First");}
    else puts("Second");
    return 0;
}