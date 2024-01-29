#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxm = 1e6 + 10,INF = 0x3f3f3f3f3f3f3f;
int n, m, S, T, t1, t2, m1, m2;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow, cost;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl),cost(co){}
}e[maxm * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(){
    queue<int> que;
    memset(pre,0,sizeof(pre));
    memset(dis,0x3f,sizeof(dis));
    memset(book,0,sizeof(book));
    que.push(S); book[S] = true; dis[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = false;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
                pre[v] = i;dis[v] = dis[u] + e[i].cost;
                if(!book[v]){book[v] = true;que.push(v);}
            }
        }
    }
    return pre[T] != 0;
}
int MCMF(){
    int mincost = 0;
    while(SPFA()){
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            fl = min(fl,e[i].cap - e[i].flow);
        }
        mincost += fl * dis[T];
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;
            e[i ^ 1].flow -= fl;
        }
    }
    return mincost;
}


signed main(){
    n = read(); S = 0, T = 2 * n + 1;
    t1 = read(); m1 = read(); t2 = read(); m2 = read(); m = read();
    for(int i = 1;i <= n;i++){
        int tmp = read();
        addd(S,i,tmp,0);
        addd(i + n,T,tmp,0);
    }
    for(int i = 1;i <= n;i++){
        if(i + 1 <= n)addd(i,i + 1,INF,0);
        if(i + t1 <= n)addd(i,i + n + t1,INF,m1);
        if(i + t2 <= n)addd(i,i + n + t2,INF,m2);
        addd(S,i + n,INF,m);
    }
    printf("%lld\n",MCMF());
    return 0;
}   