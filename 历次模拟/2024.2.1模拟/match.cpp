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
const int maxn = 1e5 + 10,INF = 0x3f3f3f3f3f3f3f3f;
int n;
int x[2][maxn], y[2][maxn];
struct edge{
    int to, nexte, cap, cost, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0
    ):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn * 30];
int tot = 1, head[maxn];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dis[maxn];
bool book[maxn];queue<int> que;
bool SPFA(int S,int T){
    for(int i = 1;i <= T;i++){dis[i] = INF;pre[i] = book[i] = 0;}
    while(!que.empty())que.pop();
    que.push(S);book[S] = 1;dis[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(e[i].cap > e[i].flow && dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;pre[v] = i;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return pre[T];
}
pair<int,int> MCMF(int S,int T){
    int maxflow = 0,mincost = 0;
    while(SPFA(S,T)){
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
        maxflow += fl;mincost += fl * dis[T];
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;e[i ^ 1].flow -= fl;
        }
    }
    return make_pair(maxflow,mincost);
}
void main(){
    n = read();
    for(int j = 0;j < 2;j++)
        for(int i = 1;i <= n;i++){
            x[j][i] = read(); y[j][i] = read();
        }
    int S = n * 2 + 1, T = n * 2 + 2;
    for(int i = 1;i <= n;i++){
        addd(S,i,1,0);addd(i + n,T,1,0);
        for(int j = 1;j <= n;j++){
            addd(i,j + n,1,-(abs(x[1][j] - x[0][i]) + abs(y[1][j] - y[0][i])));
        }
    }
    printf("%lld\n",-MCMF(S,T).second);
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
/*
2
0 0
3 2
2 2
5 0
*/