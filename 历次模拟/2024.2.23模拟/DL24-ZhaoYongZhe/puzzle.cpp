#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e4 + 10,maxN = 150 + 10, maxm = 1e6 + 10,INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int totpoint;
int w[maxN][maxN];
int c[maxN][maxN];
int id[5][maxN][maxN];
int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, cost, flow;
    edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(t),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxm];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(int S,int T){
    queue<int> que;
    for(int i = 1;i <= totpoint;i++)dis[i] = INF,book[i] = pre[i] = 0;
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
const int dx[5] = {0,-1, 0, 1, 0};
const int dy[5] = {0, 0, 1, 0,-1};
void main(){
    n = read(); m = read();int S = ++totpoint;int T = ++totpoint, tmp = 0,tmp1 = 0;
    for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)c[i][j] = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            w[i][j] = read();
            if(c[i][j])continue;
            for(int k = 0;k < 5;k++)id[k][i][j] = ++totpoint;
            if((i + j) & 1){//源点相连
                tmp += 2;
                addd(S,id[0][i][j],2,0);
                addd(id[0][i][j],id[1][i][j],1,0);
                addd(id[0][i][j],id[2][i][j],1,-w[i][j]);
                addd(id[0][i][j],id[3][i][j],1,0);
                addd(id[2][i][j],id[4][i][j],1,0);
                addd(id[1][i][j],id[4][i][j],1,w[i][j]);
            }
            else{//汇点相连
                tmp1 += 2;
                addd(id[0][i][j],T,2,0);
                addd(id[1][i][j],id[0][i][j],1,0);
                addd(id[2][i][j],id[0][i][j],1,-w[i][j]);
                addd(id[3][i][j],id[0][i][j],1,0);
                addd(id[4][i][j],id[2][i][j],1,0);
                addd(id[4][i][j],id[1][i][j],1,w[i][j]);
            }
        }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            if((i + j) & 1){
                for(int k = 1;k < 5;k++){
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx < 1 || ny < 1 || nx > n || ny > m || c[nx][ny])continue;
                    addd(id[k][i][j],id[(k + 1) % 4 + 1][nx][ny],1,0);
                }
            }
        }
    if(tmp != tmp1){puts("-1");return;}
    auto res = MCMF(S,T);
    // int sum1 = 0, sum2 = 0;
    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= m;j++){
    //         printf("(%lld,%lld),c = %lld,center = %lld,",i,j,c[i][j],id[0][i][j]);
    //         for(int k = head[id[0][i][j]];k;k = e[k].nexte){
    //             if(e[k].to == S){
    //                 printf("flow = %lld",-e[k].flow);sum1 += -e[k].flow;
    //             }
    //             if(e[k].to == T){
    //                 printf("flow = %lld",e[k].flow);sum2 += e[k].flow;
    //             }
    //         }
    //         puts("");
    //     }
    // }
    // printf("%lld %lld\n",sum1,sum2);
    // for(int i = 2;i <= tot;i += 2){
    //     printf("%lld -> %lld,cap = %lld,cost = %lld, flow = %lld\n",e[i ^ 1].to,e[i].to,e[i].cap,e[i].cost,e[i].flow);
    // }
    // printf("tmp = %lld, mxflow = %lld\n",tmp,res.first);
    if(res.first != tmp){puts("-1");return;}
    else printf("%lld\n",-res.second);
    return;
}
};
bool edmemory;
signed main(){
    freopen("puzzle.in","r",stdin);
    freopen("puzzle.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
3 3
1 1 1
1 0 0
1 0 0
48 94 1
78 78 81
1 12 60

*/