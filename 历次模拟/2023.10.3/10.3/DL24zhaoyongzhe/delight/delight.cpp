#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e3 + 10,INF = 0x3f3f3f3f;
int n, k, S, E;
int s[maxn];
int val[maxn];
int f[maxn][1 << 10];
int popcount(int x){int cnt = 0;for(;x > 0;x -= (x & (-x)))cnt++;return cnt;}


int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow, cost;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn << 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(int S,int T){
    queue<int> que;memset(book,0,sizeof(book));memset(dis,0x3f,sizeof(dis));
    dis[S] = 0;book[S] = 1;que.push(S);
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0){
                if(dis[v] > e[i].cost + dis[u]){
                    dis[v] = dis[u] + e[i].cost;
                    pre[v] = i;
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f;
}
int MCMF(int S,int T){
    int mincost = 0, maxflow = 0;
    while(SPFA(S, T)){
        int mx = 0x3f3f3f3f;
        for(int pos = pre[T];pos;pos = pre[e[pos ^ 1].to]){
            mx = min(mx,e[pos].flow);
        }
        mincost += dis[T] * mx;maxflow += mx;
        for(int pos = pre[T];pos;pos = pre[e[pos ^ 1].to]){
            e[pos].flow += mx;e[pos ^ 1].flow -= mx;
        }
    }
    return mincost;
}

signed main(){
    freopen("delight.in","r",stdin);
    freopen("delight.out","w",stdout);
    int sume = 0;
    n = read(); k = read(); S = read(); E = read();
    for(int i = 1;i <= n;i++)s[i] = read();
    for(int i = 1;i <= n;i++){int tmp = read();sume += tmp;val[i] = s[i] - tmp;}
if(S){
    memset(f,-0x3f,sizeof(f));
    for(int i = 0;i < (1 << k);i++){
        int tmp = i,pos = 1,cnt = popcount(i);
        f[k][i] = 0;
        while(tmp){
            if(tmp & 1){f[k][i] += val[pos];}
            tmp >>= 1;pos++;
        }
        if(!(cnt >= S && cnt <= k - E)){f[k][i] = -0x3f3f3f3f;}
    }
    for(int i = k + 1;i <= n;i++){
        for(int sta = 0;sta < (1 << k);sta++){
            int tmp = popcount(sta);
            if(!(tmp >= S && tmp <= k - E))continue;
            if(sta & 1){
                if(tmp - 1 >= S && tmp - 1 <= k - E){
                    f[i][(sta >> 1)] = max(f[i][sta >> 1],f[i - 1][sta]);
                }
                f[i][(sta >> 1) | (1 << k - 1)] = max(f[i][(sta >> 1) | (1 << k - 1)],f[i - 1][sta] + val[i]);
            }
            else{
                f[i][sta >> 1] = max(f[i][sta >> 1],f[i - 1][sta]);
                if(tmp + 1 >= S && tmp + 1 <= k - E){
                    f[i][(sta >> 1) | ( 1 << k - 1)] = max(f[i][(sta >> 1) | (1 << k - 1)],f[i - 1][sta] + val[i]);
                }
            }
        }
    }
    // for(int i = k;i <= n;i++){
    //     for(int sta = 0;sta < (1 << k);sta++){
    //         printf("f[%d][%d(%d)] = %d\n",i,sta,popcount(sta),f[i][sta]);
    //     }
    // }
    int ans = -0x3f3f3f3f;
    for(int sta = 0;sta < (1 << k);sta++){
        int tmp = popcount(sta);
        if(tmp >= S && tmp <= k - E)
            ans = max(ans,f[n][sta]);
    }
    printf("%d\n",ans + sume);
}
else{
    int S = n * 2, T = n * 2 + 1;
    for(int i = 1;i <= n;i++)addd(S,i,1,-val[i]);
    for(int i = 1;i <= n;i++){
        for(int j = max(n + i - k + 1,1);j <= n + i;j++){
            addd(i,j,1,0);
        }
    }
    for(int i = n + 1;i <= n + k;i++){addd(i,T,k - E,0);}
    int mxflow = MCMF(S,T);
    printf("%d\n",sume - mxflow);
}
    return 0;
}