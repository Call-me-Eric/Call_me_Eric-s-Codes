#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 210, maxm = 5100, INF = 0x3f3f3f3f3f3f3f;

int head[maxn], cur[maxn], tot = 1;
struct edge{
    int to, nexte, flow;
    edge(int t = 0,int n = 0,int f = 0):to(t),nexte(n),flow(f){}
}e[maxm * 2];
void add(int u,int v,int flow){e[++tot] = edge(v,head[u],flow); head[u] = tot;}
void addd(int u,int v,int flow){add(u,v,flow);add(v,u,0);}

int n, m, S, T;

int dep[maxn];
int dfs(int u,int flow){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].flow));
            if(tmp == 0)dep[v] = INF;
            e[i].flow -= tmp;
            e[i ^ 1].flow += tmp;
            flow -= tmp;
            rest += tmp;
        }
    }
    return rest;
}
bool bfs(){
    queue<int> que;
    for(int i = 1;i <= n;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(){
    int maxflow = 0;
    while(bfs()){maxflow += dfs(S,INF);}
    return maxflow;
}

signed main(){
    m = read(); n = read(); S = 1; T = n; int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        addd(u,v,w);
    }
    printf("%lld\n",Dinic());
    return 0;
}