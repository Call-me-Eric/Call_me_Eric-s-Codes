#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 310,INF = 0x3f3f3f3f;
int xl[maxn], xr[maxn], yl[maxn], yr[maxn];
int x[maxn], y[maxn];
int n, m;

struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int cap = 0,int flow = 0):to(to),nexte(ne),cap(cap),flow(flow){}
}e[maxn * maxn * 3];
int head[maxn * 10], tot = 1;
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}

int cur[maxn * 10], dis[maxn * 10];bool book[maxn * 10];
queue<int> que;
bool bfs(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 1;i <= T;i++)dis[i] = INF, cur[i] = book[i] = 0;
    que.push(S);dis[S] = 0;cur[S] = head[S];book[S] = 1;
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return dis[T] != INF;
}
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow; int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(e[i].cap > e[i].flow && dis[v] == dis[u] + 1){
            int tmp = dfs(v, min(e[i].cap - e[i].flow,flow),T);
            if(!tmp){dis[v] = INF;continue;}
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
            if(!flow)return res;
        }
    }
    return res;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

signed main(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        xl[i] = read();yl[i] = read(); xr[i] = read() + 1;yr[i] = read() + 1;
        x[i * 2 - 1] = xl[i];x[i * 2] = xr[i];
        y[i * 2 - 1] = yl[i];y[i * 2] = yr[i];
    }
    x[m * 2 + 1] = 1;x[m * 2 + 2] = n + 1;
    y[m * 2 + 1] = 1;y[m * 2 + 2] = n + 1;
    sort(x + 1,x + m * 2 + 2 + 1);int totx = unique(x + 1,x + m * 2 + 2 + 1) - x - 1;
    sort(y + 1,y + m * 2 + 2 + 1);int toty = unique(y + 1,y + m * 2 + 2 + 1) - y - 1;
    // for(int i = 1;i <= totx;i++)printf("x[%d]=%d\n",i,x[i]);
    for(int i = 1;i <= m;i++){
        xl[i] = lower_bound(x + 1,x + 1 + totx, xl[i]) - x;
        xr[i] = lower_bound(x + 1,x + 1 + totx, xr[i]) - x;
        yl[i] = lower_bound(y + 1,y + 1 + toty, yl[i]) - y;
        yr[i] = lower_bound(y + 1,y + 1 + toty, yr[i]) - y;
        for(int l = xl[i];l < xr[i];l++)
            for(int r = yl[i];r < yr[i];r++)
                addd(l,r + totx,INF);
    }
    int S = totx + toty + 1, T = totx + toty + 2;
    for(int i = 1;i < totx;i++) addd(S,i,x[i + 1] - x[i]);
    for(int i = 1;i < toty;i++) addd(i + totx,T,y[i + 1] - y[i]);
    printf("%d\n",Dinic(S,T));
    return 0;
}