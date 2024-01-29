#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10, INF = 0x3f3f3f3f;
int n, cntpoint, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap,flow, cost;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0
                ):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn << 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost);add(v, u, 0,-cost);}


int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(int S,int T){
    queue<int> que;
    for(int i = 1;i <= cntpoint;i++)dis[i] = INF;
    memset(book,0,sizeof(book));
    memset(pre,0,sizeof(pre));
    que.push(S);book[S] = true;dis[S] = 0;
    while(!que.empty()){
    // puts("111111111");
        int u = que.front();que.pop();book[u] = false;
        // printf("head:%d\n",u);
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            // printf("%d ->%d,%d %d %d %d %d\n",i,e[i].to,e[i].cap,e[i].flow,dis[v],dis[u],e[i].cost);
            if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
                pre[v] = i;dis[v] = dis[u] + e[i].cost;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
    }
    return pre[T] != 0;
}
pair<int,int> MCMF(int S,int T){
    int mincost = 0, maxflow = 0;
    while(SPFA(S,T)){
        // puts("times");
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            fl = min(fl,e[i].cap - e[i].flow);
            // printf("%d %d\n",fl,e[i ^ 1].to);
        }
        mincost += fl * dis[T];maxflow += fl;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;
            e[i ^ 1].flow -= fl;
        }
    }
    return make_pair(maxflow,mincost);
}
signed main(){
    n = read(); m = read();
    int S = n * 2 + 1,ss = n * 2 + 2, T = n * 2 + 3;cntpoint = T;
    addd(S,ss,m,0);
    for(int i = 1;i <= n;i++){
        int cap = read();
        addd(ss,i + n,INF,0);
        addd(S,i,cap,0);
        addd(i + n,T,cap,0);
    }
    for(int i = 1;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            int co = read();if(co == -1)co = INF;
            addd(i,j + n,INF,co);
        }
    }
    printf("%d\n",MCMF(S,T).second);
    return 0;
}