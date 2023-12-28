#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m, g;
int a[maxn], val[maxn];

int head[maxn], tot = 1;
struct edge{
    int to, nexte,cap, flow;
    edge(int to  =0,int ne = 0,int ca = 0
        ,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn << 1];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}

queue<int> que;int dis[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(e[i].cap > e[i].flow && dis[v] == dis[u] + 1){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp)cur[v] = 0;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;e[i].flow += tmp;
        }
    }
    return res;
}
bool bfs(int S,int T){
    memset(cur,0,sizeof(cur));memset(dis,0x3f,sizeof(dis));
    while(!que.empty())que.pop();
    que.push(S);dis[S] = 0;cur[S] = head[S];
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1; cur[v] = head[v];
                que.push(v);
            }
        }
    }
    return dis[T] != INF;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

signed main(){
    n = read(); m = read(); g = read();
    int S = n + m + 2, T = n + m + 3, sum = 0;
    for(int i = 1;i <= n;i++){a[i] = read();}
    for(int i = 1;i <= n;i++){
        val[i] = read();
        if(!a[i]){addd(S,i,val[i]);}
        else{addd(i,T,val[i]);}
    }
    for(int i = 1;i <= m;i++){
        int typ = read(), w = read(), k = read();sum += w;
        for(int j = 1;j <= k;j++){
            if(!typ){addd(i + n,read(),INF);}
            else addd(read(),i + n,INF);
        }
        int co = g * read();
        if(!typ){addd(S,i + n,co + w);}
        else addd(i + n,T,co + w);
    }
    int ans = Dinic(S,T);
    printf("%d\n",sum - ans);
    return 0;
}