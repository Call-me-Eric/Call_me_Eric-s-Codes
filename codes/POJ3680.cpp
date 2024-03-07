#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, maxm = 1e3 + 10,INF = 0x3f3f3f3f3f;int n, m, S, T;
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
    queue<int> que;
    for(int i = 1;i <= n;i++)dis[i] = INF;
    memset(book,0,sizeof(book));
    memset(pre,0,sizeof(pre));
    que.push(S);book[S] = true;dis[S] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = false;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
                pre[v] = i;dis[v] = dis[u] + e[i].cost;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
    }
    return pre[T] != 0;
}
int tmp[maxn], total;
int l[maxn],r[maxn], w[maxn];

signed main(){
    int test = read();
    while(test--){
    n = read(); int k = read();total = 0;tot  = 1;
    memset(head,0,sizeof(head));
    for(int i = 1;i <= n;i++){
        l[i] = read(); r[i] = read(); w[i] = read();
        tmp[++total] = l[i];tmp[++total] = r[i];
    }
    sort(tmp + 1,tmp + 1 + total);
    total = unique(tmp + 1,tmp + 1 + total) - tmp;
    for(int i = 1;i <= n;i++){
        l[i] = lower_bound(tmp + 1,tmp + 1 + total,l[i]) - tmp;
        r[i] = lower_bound(tmp + 1,tmp + 1 + total,r[i]) - tmp;
        addd(l[i],r[i],1,-w[i]);
    }
    for(int i = 0;i <= total;i++){addd(i,i + 1,k,0);}
    S = 0, T = total + 1;
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
    printf("%lld\n",-mincost);
    }
    return 0;
}