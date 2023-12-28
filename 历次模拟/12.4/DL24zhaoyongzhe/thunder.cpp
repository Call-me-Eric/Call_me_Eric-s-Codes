#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch  = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2.5e5 + 10,INF = 0x3f3f3f3f;
int x[maxn], y[maxn];
int rest[maxn];
int siz[maxn];
int n;
struct edge{
    int to, nexte, cost, cap, flow;
    edge(int to = 0,int ne = 0,int cap = 0,int we = 0,int flow = 0):to(to),nexte(ne),cap(cap),cost(we),flow(flow){}
}e[maxn << 2];
int head[maxn], tot = 1;
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost);add(v, u, 0, -cost);}

int to[maxn], dis[maxn];
queue<int> que; bool book[maxn];
bool SPFA(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 1;i <= T;i++)dis[i] = INF, to[i] = 0, book[i] = 0;
    que.push(S);book[S] = 1;dis[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(dis[v] > dis[u] + w && e[i].cap > e[i].flow){
                dis[v] = dis[u] + w;to[v] = i;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return to[T] != 0;
}
pair<int,int> MCMF(int S,int T){
    int mxflow = 0,mincost = 0;
    while(SPFA(S,T)){
        int fl = 0x3f3f3f3f;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
        mincost += dis[T] * fl;mxflow += fl;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            e[i].flow += fl,e[i ^ 1].flow -= fl;
    }
    return make_pair(mxflow,mincost);
}
signed main(){
    freopen("thunder.in","r",stdin);
    freopen("thunder.out","w",stdout);
    n = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        addd(u, v, INF, w);addd(v, u, INF, w);
    }
    int S = n + 1, T = n + 2;
    for(int i = 1;i <= n;i++){
        x[i] = read(); y[i] = read();
        rest[i] = x[i] - y[i];
        if(rest[i] > 0)addd(i,T,rest[i],0);
        if(rest[i] < 0)addd(S,i,-rest[i],0);
    }
    printf("%lld\n",MCMF(S,T).second);
    return 0;
}