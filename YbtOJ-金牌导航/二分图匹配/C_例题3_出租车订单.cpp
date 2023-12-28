#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}

const int maxn = 5e3 + 10, maxm = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}

int dep[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0)dep[v] = INF;
            e[i].flow += tmp; e[i ^ 1].flow -= tmp;
            flow -= tmp;rest += tmp;
            if(!flow)return rest;
        }
    }
    return rest;
}
bool bfs(int S,int T){
    queue<int> que;
    for(int i = 1;i <= T;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}
int st[maxn];
int sx[maxn], sy[maxn];
int ex[maxn], ey[maxn];
bool ed[maxn][maxn];
void solve(){
    tot = 1;memset(head,0,sizeof(head));
    n = read();int S = n * 2 + 1, T = n * 2 + 2;
    for(int i = 1;i <= n;i++){
        int h, m;
        scanf("%d:%d%d%d%d%d",&h,&m,&sx[i],&sy[i],&ex[i],&ey[i]);
        st[i] = h * 60 + m;
    }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(st[j] > st[i] + abs(ex[i] - sx[j]) + abs(ey[i] - sy[j])
                             + abs(ex[i] - sx[i]) + abs(ey[i] - sy[i]))
                ed[i][j] = 1;
            else ed[i][j] = 0;
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                ed[i][j] |= (ed[i][k] & ed[k][j]);
    for(int i = 1;i <= n;i++){
        addd(S,i,1);addd(i + n,T,1);
        for(int j = 1;j <= n;j++)
            if(ed[i][j])addd(i,j + n,INF);
    }
    printf("%d\n",n - Dinic(S,T));
}
signed main(){
    int T = read();
    while(T--){solve();}
    return 0;
}