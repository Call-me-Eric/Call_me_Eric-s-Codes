// LUOGU_RID: 134332329
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, INF = 0x3f3f3f3f;
int n, a[maxn];
map<int,int> mp;

int head[maxn], tot;
struct edge{
    int to, nexte, cap,flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn << 4];
void add(int u,int v,int cap){
    e[++tot] = edge(v,head[u],cap);
    head[u] = tot;
}
void addd(int u,int v,int cap){add(u,v,cap);add(v,u,0);}

queue<int> que;int dis[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
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
    for(int i = 1;i <= T;i++){dis[i] = INF;cur[i] = 0;}
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
int Test = read();
while(Test--){
    n = read();mp.clear();for(int i = 1;i <= n;i++){mp[a[i] = read()] = i;}
    int S = n * 4 + 1, T = n * 4 + 2;
    for(int i = 1;i <= T;i++)head[i] = 0;tot = 1;
    for(int i = 1;i <= n;i++){
        for(int j = sqrt(a[i]);j;j--){
            if(a[i] % j == 0){
                if(mp[a[i] / j] && j != 1){
                    addd(i        ,mp[a[i] / j] + n    ,1);
                    addd(i + 2 * n,mp[a[i] / j] + n * 3,1);
                }
                if(mp[j] && j * j != a[i]){
                    addd(i        ,mp[j] + n    ,1);
                    addd(i + 2 * n,mp[j] + n * 3,1);
                }
            }
        }
        addd(i + n,i + n * 2,1); addd(S,i,1); addd(i + n * 3,T,1);
    }
    printf("%d\n",Dinic(S,T));
    // for(int u = 1;u <= T;u++)
    //     for(int i = head[u];i;i = e[i].nexte)
    //         printf("%d -> %d: cap = %d, flow = %d\n",u,e[i].to,e[i].cap,e[i].flow);
}
    return 0;
}