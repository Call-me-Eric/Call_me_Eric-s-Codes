#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch  = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f  = - 1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10, maxm = 5e4 + 10,INF = 0x3f3f3f3f;
int n, m, S, T;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow, cost;
    edge(int t = 0,int ne = 0,int ca = 0,int co = 0):to(t),nexte(ne),cap(ca),cost(co){}
}e[maxm * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dist[maxn];
bool book[maxn];
bool SPFA(){
    queue<int> que;
    memset(book,0,sizeof(book));
    memset(pre,0,sizeof(pre));
    memset(dist,0x3f,sizeof(dist));
    dist[S] = 0; que.push(S);book[S] = true;
    while(!que.empty()){
        int u = que.front();que.pop();
        book[u] = false;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap > e[i].flow && dist[v] > dist[u] + e[i].cost){
                dist[v] = dist[u] + e[i].cost;
                pre[v] = i;
                if(!book[v]){
                    que.push(v);
                    book[v] = true;
                }
            }
        }
    }
    return pre[T] != 0;
}

signed main(){
    n = read(); m = read();S = read(); T = read();int u,v, fl, cost;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); fl = read(); cost = read();
        addd(u,v,fl,cost);
    }
    int maxflow = 0, mincost = 0;
    while(SPFA()){
        fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
        maxflow += fl;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;
            e[i ^ 1].flow -= fl;
        }
        mincost += dist[T] * fl;
    }
    printf("%d %d\n",maxflow,mincost);
    return 0;
}
