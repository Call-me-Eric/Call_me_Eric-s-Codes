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
const int maxn = 1e5 + 10, maxN = 100, INF = 0x3f3f3f3f;
int n, m;
int val[maxN][maxN];
int id[maxN][maxN], totpoint;

struct edge{
    int to, nexte, cap, cost, flow;
    edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0
    ):to(t),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn << 3];
int head[maxn], tot = 1;
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

queue<int> que;
int dis[maxn];bool book[maxn];
bool SPFA(int S,int T){
    for(int i = 1;i <= totpoint;i++){book[i] = 0;dis[i] = INF;}
    while(!que.empty())que.pop();
    que.push(T);dis[T] = 0;book[T] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(e[i ^ 1].cap > e[i ^ 1].flow && dis[v] > dis[u] - w){
                dis[v] = dis[u] - w;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return dis[S] != INF;
}
int mincost, maxflow;
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;book[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].cost;
        if(!book[v] && dis[v] == dis[u] - w && e[i].cap > e[i].flow){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp){
                res += tmp;flow -= tmp;mincost += w * tmp;
                e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            }
            if(!flow)return res;
        }
    }
    return res;
}
pair<int,int> MCMF(int S,int T){
    mincost = maxflow = 0;
    while(SPFA(S,T)){
        book[T] = 1;
        while(book[T]){
            for(int i = 1;i <= totpoint;i++)book[i] = 0;
            maxflow += dfs(S,INF,T);
        }
    }
    return make_pair(mincost,maxflow);
}

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0,-1, 1, 0};

void main(){
    n = read(), m = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            val[i][j] = read();
            id[i][j] = ++totpoint;
        }
    int S = ++totpoint;int T = ++totpoint;
    for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++){
        if((i + j) & 1){
            addd(S,id[i][j],1,0);
            for(int k = 0;k < 4;k++){
                int x = dx[k] + i, y = dy[k] + j;
                if(x < 1 || y < 1 || x > n || y > m)continue;
                addd(id[i][j],id[x][y],1,val[i][j] != val[x][y]);
            }
        }
        else addd(id[i][j],T,1,0);
    }
    printf("%d\n",MCMF(S,T).first);
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