#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 510, maxm = 5e5 + 10,  INF = 0x3f3f3f3f;
int n ,m;
struct edge1{
    int from, to, L, R;
    edge1(int fr = 0,int to = 0,int l = 0,int r = 0):from(fr),to(to),L(l),R(r){}
}e1[maxm];int totedg;
int day[maxm], girl[maxm], cntpoint;
int in[maxm], out[maxm];

struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm << 1];
int tot = 1, head[maxm];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}

int dis[maxm], cur[maxm];bool book[maxm];
queue<int> que;
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;int res = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(e[i].cap > e[i].flow && dis[v] == dis[u] + 1){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp){dis[v] = INF;continue;}
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            flow -= tmp;res += tmp;
            if(!flow)return res;
        }
    }
    return res;
}
bool bfs(int S,int T){
    while(!que.empty())que.pop();
    for(int i = 1;i <= cntpoint;i++){dis[i] = INF;cur[i] = book[i] = 0;}
    que.push(S);dis[S] = 0;book[S] = 0;cur[S] = head[S];
    while(!que.empty()){
        int u = que.front();que.pop(); book[u] = 0;
// printf("u = %d\n",u);
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
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

signed main(){
bool endline = false;
while(scanf("%d%d",&n,&m) != EOF){
if(endline)puts("");
else endline = true;

    cntpoint = 0;totedg = 0;tot = 1;
    int u, v, l, r;
    int S = ++cntpoint, T = ++cntpoint;
    for(int i = 1;i <= n;i++)day[i] = ++cntpoint;
    for(int i = 1;i <= m;i++)girl[i] = ++cntpoint;
    for(int i = 1;i <= cntpoint + 2;i++)head[i] = in[i] = out[i] = 0;
    memset(e,0,sizeof(e));
// puts("1111111111");
    for(int i = 1;i <= m;i++)
        e1[++totedg] = edge1(girl[i],T,read(),INF);
    for(int i = 1;i <= n;i++){
        u = read(); v = read();
        e1[++totedg] = edge1(S,day[i],0,v);
        for(int j = 1;j <= u;j++){
            v = read() + 1;l = read(); r = read();
            e1[++totedg] = edge1(day[i],girl[v],l,r);
        }
    }
    e1[++totedg] = edge1(T,S,0,INF);
    int ss = ++cntpoint, tt = ++cntpoint, sum = 0, delid = 0;
// puts("2222222222");
    for(int i = 1;i <= totedg;i++){
        in[e1[i].to] += e1[i].L; out[e1[i].from] += e1[i].L;
        addd(e1[i].from,e1[i].to,e1[i].R - e1[i].L);delid = tot - 1;
    }
    for(int i = 1;i <= cntpoint - 2;i++){
        if(in[i] > out[i])addd(ss,i,in[i] - out[i]),sum += in[i] - out[i];
        if(in[i] < out[i])addd(i,tt,out[i] - in[i]);
    }
// printf("cntpoint= %d\n",cntpoint);
    int res = Dinic(ss,tt);
// puts("3333333333");
    if(res != sum){puts("-1");continue;}
    e[delid].cap = e[delid ^ 1].cap = 0;
    printf("%d\n",Dinic(S,T));
}
    return 0;
}