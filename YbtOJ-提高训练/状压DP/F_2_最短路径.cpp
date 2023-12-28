#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, k, S, T;
const int maxn = 50010,maxm = 1e5 + 10;
int key[11];
int head[maxn], tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int to = 0,int ne = 0,int we = 0):topoint(to),nextedge(ne),weight(we){}
}e[maxm];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
int to[13][13];

struct node{int dis, u;node(int d = 0,int u = 0):dis(d),u(u){}}; bool operator > (node a,node b){return a.dis > b.dis;}
int dis[maxn];bool book[maxn];
int dijkstra(int s){
    priority_queue<node, vector<node>, greater<node> > que;
    memset(dis,0x3f,sizeof(dis)); memset(book,0,sizeof(book));
    dis[s] = 0; que.push(node(0,s));
    while(!que.empty()){
        node u = que.top(); que.pop();
        if(book[u.u])continue;
        book[u.u] = 1;
        for(int i = head[u.u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v] > dis[u.u] + w){
                dis[v] = dis[u.u] + w;
                que.push(node(dis[v],v));
            }
        }
    }
}

int ans = 0x3f3f3f3f;
void dfs(int u,int sum,int dep){
    if(dep == k){
        if(ans > sum + to[u][k + 1])ans = sum + to[u][k + 1];
        return;
    }
    for(int i = 1;i <= k;i++){
        if(u != i && !book[i] && to[u][i] != 0x3f3f3f3f){
            book[i] = 1;
            dfs(i,sum + to[u][i],dep + 1);
            book[i] = 0;
        }
    }
}
signed main(){
    int u, v , w;
    n = read(); m = read(); k = read(); S = read(); T = read();
    for(int i = 1;i <= m;i++){u = read(); v = read(); w = read(); add(u,v,w);}
    for(int i = 1;i <= k;i++){key[i] = read();}
    dijkstra(S);
    if(k == 0){
        if(dis[T] == 0x3f3f3f3f)puts("-1");
        else printf("%d\n",dis[T]);
        return 0;
    }
    for(int i = 1;i <= k;i++)to[0][i] = dis[key[i]];
    for(int i = 1;i <= k;i++){
        dijkstra(key[i]);
        for(int j = 1;j <= k;j++)
            to[i][j] = dis[key[j]];
        to[i][k + 1] = dis[T];
    }
    dijkstra(T);
    for(int j = 1;j <= k;j++)to[k + 1][j] = dis[key[j]];
    to[k + 1][k + 1] = dis[T];
    memset(book,0,sizeof(book));
    dfs(0,0,0);
    printf("%d\n",ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}