#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, maxm = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m;
int head[maxn], tot = 1;
int total, id[maxm][3];//0=products,1=person1,2= person2
struct edge{
    int to, nexte, cap,flow, cost;
    edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(t),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(int S,int T){
    queue<int> que;
    for(int i = 1;i <= total;i++)dis[i] = INF;
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

pair<int,int> MCMF(int S,int T){
    int mincost = 0, maxflow = 0;
    while(SPFA(S,T)){
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to])
            fl = min(fl,e[i].cap - e[i].flow);
            
        mincost += fl * dis[T];maxflow += fl;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;e[i ^ 1].flow -= fl;
        }
    }
    return make_pair(maxflow,mincost);
}
int t[maxn], w[maxn];
signed main(){
    m = read(); n = read();
    for(int i = 1;i <= m;i++){id[i][1] = ++total;id[i][2] = ++total;}
    for(int i = 1;i <= n;i++){id[i][0] = ++total;}
    int S = ++total;int T = ++total;
    for(int i = 1;i <= n;i++){addd(S,id[i][0],read(),0);}
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++)
            if(read()){addd(id[j][0],id[i][1],INF,0);}
    for(int i = 1;i <= m;i++){
        int s = read();
        int lst = 0;
        for(int j = 1;j <= s;j++)t[j] = read();
        for(int j = 1;j <= s + 1;j++)w[j] = read();
        for(int j = 1;j <= s;j++)addd(id[i][1],id[i][2],t[j] - t[j - 1],w[j]);
        addd(id[i][1],id[i][2],INF,w[s + 1]);
        addd(id[i][2],T,INF,0);
    }
    printf("%lld\n",MCMF(S,T).second);
    return 0;
}