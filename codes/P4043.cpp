#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 500, maxm = 40100,INF = 0x3f3f3f3f3f3f3f3f;
int n, m;

struct edge{
    int to, nexte, cap,cost,flow;
    edge(int to = 0,int ne = 0,int cap = 0,int cost = 0,int flow = 0):to(to),nexte(ne),cap(cap),cost(cost),flow(flow){}
}e[maxm << 1];
int head[maxn], tot = 1;
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost); add(v, u, 0, -cost);}

vector<int> b[maxn], t[maxn];
int d[maxn];

int to[maxn], dis[maxn];bool book[maxn];
queue<int> que;
bool SPFA(int S,int T){
    for(int i = 0;i <= T;i++)to[i] = book[i] = 0,dis[i] = INF;
    while(!que.empty())que.pop();
    dis[S] = 0;que.push(S);book[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(e[i].cap > e[i].flow && dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;to[v] = i;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return dis[T] < INF;
}
pair<int,int> MCMF(int S,int T){
    int mincost = 0,maxflow = 0;
    while(SPFA(S,T)){
        int tmp = INF;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            tmp = min(tmp,e[i].cap - e[i].flow);
        mincost += dis[T] * tmp;maxflow += tmp;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            e[i].flow += tmp;
    }
    return make_pair(maxflow,mincost);
}

signed main(){
    n = read();int u, w, ans = 0;
    int S = n + 1, T = n + 2;
    for(int i = 1;i <= n;i++){
        for(int j = read();j;j--){
            u = read();w = read();
            d[i]--;d[u]++;ans += w;
            addd(i,u,INF,w);
        }
    }
    for(int i = 2;i <= n;i++)addd(i,1,INF,0);
    for(int i = 1;i <= n;i++){
        if(d[i] > 0)addd(S,i,d[i],0);
        if(d[i] < 0)addd(i,T,-d[i],0);
    }
    printf("%lld\n",ans + MCMF(S,T).second);
    return 0;
}