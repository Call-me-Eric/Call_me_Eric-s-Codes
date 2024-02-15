#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10,INF = 1e6;
int n, m;
int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int t = 0,int ne = 0,int ca = 0,int fl = 0)
    :to(t),nexte(ne),cap(ca),flow(fl){}
}e[maxn];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}
int cur[maxn], dep[maxn];
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(dep[v] == dep[u] + 1 && e[i].cap > e[i].flow){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp)dep[v] = INF;
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
            if(!flow)return res;
        }
    }
    return res;
}
queue<int> que;
bool bfs(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 0;i <= n + 1;i++){cur[i] = 0;dep[i] = INF;}
    que.push(S);cur[S] = head[S];dep[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap > e[i].flow && dep[v] == INF){
                dep[v] = dep[u] + 1;cur[v] = head[v];
                que.push(v);
            }
        }
    }
    return dep[T] != INF;
}
int Dinic(int S,int T){
    int maxflow = 0;
    while(bfs(S,T))maxflow += dfs(S,INF,T);
    return maxflow;
}
int opt[maxn], from[maxn], to[maxn];
bool vis[maxn];
void dfs1(int u){
    vis[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(e[i].cap > e[i].flow && !vis[v])dfs1(v);
    }
}
int id[maxn];
void main(){
    int S, T;
    n = read(); m = read(); S = read(); T = read();
    int u, v;
    for(int i = 1;i <= m;i++){
        from[i] = u = read();to[i] = v = read(); opt[i] = read();
        if(opt[i] == 1){addd(u,v,1);addd(v, u,INF);}
        else addd(u, v, INF);
    }
    printf("%d\n",Dinic(S,T));
    dfs1(S);
    memset(head,0,sizeof(head));tot = 1;
    memset(e,0,sizeof(e));
    addd(T,S,INF);int ss = 0, tt = n + 1;
    for(int i = 1;i <= m;i++){
        if(opt[i]){
            addd(from[i],to[i],INF - 1);
            addd(ss,to[i],1); addd(from[i],tt,1);
            id[i] = tot - 5;
        }
    }
    for(int i = 1;i <= m;i++){
        if(opt[i]){
            if(vis[from[i]] ^ vis[to[i]])printf("%d %d\n",e[id[i]].flow + 1,e[id[i]].flow + 1);
            else printf("%d 1000000\n",e[id[i]].flow + 1);
        }
        else puts("0 1000000");
    }
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}