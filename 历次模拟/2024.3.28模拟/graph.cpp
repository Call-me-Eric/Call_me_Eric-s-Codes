#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10,INF = 0x3f3f3f3f3f3f3f3f;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, cost ,flow;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0
    ):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn << 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost);add(v, u, 0, -cost);}

queue<int> que;
int dis[maxn], pre[maxn];bool book[maxn];
bool SPFA(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 0;i <= T;i++){dis[i] = INF;book[i] = pre[i] = 0;}
    que.push(S);dis[S] = 0;book[S] = 1;pre[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = false;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(e[i].cap > e[i].flow && dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;pre[v] = i;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return pre[T] != 0;
}
pair<int,int> MCMF(int S,int T){
    int maxflow = 0,mincost = 0;
    while(SPFA(S,T)){
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
        mincost += fl * dis[T];maxflow += fl;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            e[i].flow += fl,e[i ^ 1].flow -= fl;
    }
    return make_pair(mincost,maxflow);
}

void main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        addd(u, v, 1, w);
    }
    int S = n + 1, T = n + 1;addd(S,1,2,0);
    for(int i = 2;i <= n;i++){
        T++;addd(i,T,2,0);
        for(int j = 0;j <= tot;j++)e[j].flow = 0;
        auto tmp = MCMF(S,T);
        if(tmp.second == 2){printf("%lld\n",tmp.first);}
        else puts("-1");
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 8
1 2 5
2 3 1
1 4 1
4 5 1
3 2 9
3 5 3
4 2 4
4 1 4
*/