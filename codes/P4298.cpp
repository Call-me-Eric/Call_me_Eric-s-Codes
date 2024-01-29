#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 128, INF = 0x3f3f3f3f, maxm = 400;
int n, m;
bitset<maxn> edg[maxn];

struct edge{
    int to, nexte, cap, flow;
    edge(int to  =0,int ne = 0,int we = 0,int flow = 0):to(to),nexte(ne),cap(we),flow(flow){}
}e[maxm * maxm * 3];
int head[maxm], tot = 1;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
void addd(int u,int v,int w){add(u, v, w);add(v, u, 0);}

bool ban[maxm];
int cur[maxm], dis[maxm];
queue<int> que;
int dfs(int u,int flow,int T){
    // printf("dfs u = %d", u);
    if(u == T || !flow)return flow; int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(ban[v])continue;
        if(dis[v] == dis[u] + 1 && e[i].cap > e[i].flow){
            int tmp = dfs(v, min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0){dis[v] = INF;}
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
            if(!flow)return res;
        }
    }
    return res;
}
bool bfs(int S,int T){
    for(int i = 1;i <= T;i++)cur[i] = 0, dis[i] = INF;
    while(!que.empty())que.pop();
    que.push(S);cur[S] = head[S];dis[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        // printf("bfs u = %d\n",u);
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;if(ban[v])continue;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                que.push(v);
            }
        }
    }
    // printf("dis[T = %d] = %d\n",T,dis[T]);
    return dis[T] != INF;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}

int match[maxm];
bool s[maxm], t[maxm];
void dfs(int u){
    if(s[u])return; s[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(!t[v]){t[v] = true;dfs(match[v]);}
    }
}

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){u = read(); v = read(); edg[u].set(v);}
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            if(edg[i][k]) edg[i] = edg[i] | edg[k];
    // puts("1111");
    int S = n * 2 + 1, T = n * 2 + 2;
    for(int i = 1;i <= n;i++){
        addd(S,i,1);addd(i + n, T, 1);
        for(int j = 1;j <= n;j++)
            if(edg[i][j])addd(i,j + n,INF);
    }
    int res = n - Dinic(S,T);
    printf("%d\n",res);

    for(int u = 1;u <= n;u++)
        for(int i = head[u];i;i = e[i].nexte)
            if(e[i].flow == 1 && e[i].to != S){
                match[u] = e[i].to; match[e[i].to] = u; break;
            }
    for(int i = 1;i <= n;i++)if(!match[i])dfs(i);
    for(int i = 1;i <= n;i++)putchar('0' + (s[i] && !t[i + n]));puts("");

    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= n;j++){
    //         putchar('0' + edg[i][j]);
    //     }
    //     puts("");
    // }

    for(int i = 1;i <= n;i++){
        int cnt = 0;tot = 1;
        memset(head,0,sizeof(head));memset(e,0,sizeof(e));
        for(int j = 1;j <= n;j++)if(edg[j][i] || edg[i][j] || j == i)ban[j] = ban[j + n] = 1;
        for(int k = 1;k <= n;k++){
            if(!ban[k]){
                addd(S,k,1);addd(k + n,T,1);cnt++;
                for(int j = 1;j <= n;j++)
                    if(!ban[j] && edg[k][j])addd(k,j + n,INF);
            }
        }
        int tmp = Dinic(S,T);
        // printf("cnt = %d,tmp = %d\n",cnt,cnt - tmp);
        putchar('0' + ((cnt - tmp) == (res - 1)));
        for(int j = 1;j <= n;j++)if(edg[j][i] || edg[i][j] || j == i)ban[j] = ban[j + n] = 0;
    }
    return 0;
}