#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10,INF = 0x3f3f3f3f3f3f3f;

int n, m, k;
int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxn << 2];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v,u,0);}

int dep[maxn], cur[maxn];
int dfs(int u,int restflow,int T){
    if(u == T || !restflow)return restflow;
    int rest = 0,res = 0;
    // printf("dfs : u=%lld\n",u);
    for(int i = cur[u];i;i = e[i].nexte){
        int v = e[i].to;cur[u] = i;
        if(e[i].cap - e[i].flow > 0 && dep[v] == dep[u] + 1){
            rest = dfs(v,min(e[i].cap - e[i].flow,restflow),T);
            restflow -= rest; res += rest;
            e[i].flow += rest;e[i ^ 1].flow -= rest;
        }
    }
    return res;
}
bool bfs(int S,int T){
    memset(dep,0x3f,sizeof(dep));
    memset(cur,0,sizeof(cur));
    queue<int> que; que.push(S);cur[S] = head[S];dep[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        // printf("bfs : u=%lld\n",u);
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && !cur[v]){
                cur[v] = head[v];dep[v] = dep[u] + 1;
                que.push(v);
                if(v == T)return true;
            }
        }
    }
    return false;
}
int maxflow(int S,int T){
    int mx = 0;
    while(bfs(S,T)){mx += dfs(S,INF,T);}
    return mx;
}

signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    n = read(); int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w=  read();
        addd(u, v, w);addd(v, u, w);
    }
    int S = n + 1, T = n + 2;
    m = read();
    for(int i = 1;i <= m;i++){
        u = read();addd(S,u,INF);
    }
    k = read();
    for(int i = 1;i <= k;i++){
        u = read();addd(u,T,INF);
    }
    printf("%lld\n",maxflow(S,T));
    return 0;
}