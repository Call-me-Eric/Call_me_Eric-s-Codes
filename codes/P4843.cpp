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

bool book[maxn];int dis[maxn],pre[maxn];

bool SPFA(int S,int T){
    queue<int> que;
    for(int i = 0;i <= T;i++)dis[i] = INF,book[i] = pre[i] = 0;
    que.push(S);book[S] = true;dis[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = false;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
                pre[v] = i;dis[v] = dis[u] + e[i].cost;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
    }
    return pre[T] != 0;
}

pair<int,int> MCMF(int S,int T){
    int mincost = 0, maxflow = 0;
    while(SPFA(S,T)){
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
            
        mincost += fl * dis[T];maxflow += fl;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;e[i ^ 1].flow -= fl;
        }
    }
    return make_pair(maxflow,mincost);
}

void main(){
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