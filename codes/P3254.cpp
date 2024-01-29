#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn =  1e5 + 10, maxm = 2e5 + 10,INF = 0x3f3f3f3f;

int n, m;
int head[maxn], tot = 1;
struct edge{
    int to, nexte;int flow;bool flag;
    edge(int to = 0,int ne = 0,int f = 0, bool fl = 0):to(to), nexte(ne),flow(f), flag(fl){}
}e[maxm];
void addd(int u,int v,int cap,bool fl){e[++tot] = edge(v,head[u],cap,fl);head[u] = tot;}
void add(int u,int v,int cap){addd(u,v,cap,1);addd(v,u,0,0);}

int S, T;

int cur[maxn], dep[maxn];int dfs(int u,int flow){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].flow));
            if(tmp == 0)dep[v] = INF;
            e[i].flow -= tmp;
            e[i ^ 1].flow += tmp;
            flow -= tmp;
            rest += tmp;
        }
    }
    return rest;
}
bool bfs(){
    queue<int> que;
    for(int i = 1;i <= n + m + 3;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            // printf("%d -> %d\n",u,v);
            if(e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(){
    int maxflow = 0;
    while(bfs()){maxflow += dfs(S,INF);}
    return maxflow;
}

signed main(){
    n = read(); m = read();S = n + m + 1; T = S + 1;
    int u, v;
    int ans = 0;
    for(int i = 1;i <= n;i++){u = read(); add(S,i,u); ans += u;}
    for(int i = 1;i <= m;i++){u = read(); add(i + n,T,u);}

    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            add(i,j + n,1);

    ans -= Dinic();
    // printf("%d\n",ans);
    if(ans == 0){
        puts("1");
        for(int i = 1;i <= n;i++){
            for(int j = head[i];j;j = e[j].nexte){
                int v  = e[j].to;
                if(v != S && !e[j].flow && e[j].flag){
                    printf("%d ",v - n);
                }
            }
            puts("");
        }
    }
    else puts("0");
    return 0;
}