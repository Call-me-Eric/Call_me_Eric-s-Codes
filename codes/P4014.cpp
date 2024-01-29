#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}

const int maxn = 5e2 + 10, maxm = 5e4 + 10, INF = 0x3f3f3f3f3f3f;
int n, m, S, T;
int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap,flow, cost;
    edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(t),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn];
bool book[maxn];
int dis[maxn];
bool SPFA(){
    // puts("IN");
    queue<int> que;
    // memset(dis,0x3f,sizeof(dis));
    for(int i = 1;i <= n + n + 3;i++)dis[i] = INF;
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

int MCMF(){
    int mincost = 0, maxflow = 0;
    while(SPFA()){
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
    return mincost;
}

int c[maxn][maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            c[i][j] = read();
        }
    }
    S = n + n + 1; T = S + 1;
    for(int i = 1;i <= n;i++){addd(S,i,1,0);}
    for(int i = 1;i <= n;i++){addd(i + n,T,1,0);}
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            addd(i,j + n,1,c[i][j]);
        }
    }
    printf("%d\n",MCMF());
    
    memset(head,0,sizeof(head)); tot = 1;
    for(int i = 1;i <= n;i++){addd(S,i,1,0);}
    for(int i = 1;i <= n;i++){addd(i + n,T,1,0);}
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            addd(i,j + n,1,-c[i][j]);
        }
    }
    printf("%d\n",-MCMF());

    return 0;
}