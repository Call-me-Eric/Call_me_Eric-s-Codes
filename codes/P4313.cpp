#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110, INF = 0x3f3f3f3f, maxm = 3e5 + 10;

int n, m;
int art, sci;
int sart, ssci;

int head[maxm], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int cap = 0,int fl = 0):to(to),nexte(ne),cap(cap),flow(fl){}
}e[maxm * 10];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u, v, cap);add(v, u, 0);}
    // printf("%d -> %d, cap = %d\n",u, v, cap);

const int dx[5] = {0,-1, 1, 0, 0};
const int dy[5] = {0, 0, 0,-1, 1};

queue<int> que;
bool book[maxm];
int dis[maxm], cur[maxm];
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(dis[v] == dis[u] + 1 && e[i].cap > e[i].flow){
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp)dis[v] = INF;
            e[i].flow += tmp;e[i ^ 1].flow -= tmp;
            res += tmp;flow -= tmp;
        }
    }
    return res;
}
bool bfs(int S,int T){
    while(!que.empty())que.pop();memset(cur,0,sizeof(cur));
    memset(book,0,sizeof(book));memset(dis,0x3f,sizeof(dis));
    cur[S] = head[S];dis[S] = 0;que.push(S);
    while(!que.empty()){
        int u = que.front();que.pop();if(book[u])continue;book[u] = 1;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] == INF && e[i].cap > e[i].flow){
                dis[v] = dis[u] + 1;cur[v] = head[v];
                que.push(v);
            }
        }
    }
    return dis[T] != INF;
}
int maxflow(int S,int T){
    int mxflow = 0;
    while(bfs(S,T))mxflow += dfs(S,INF,T);
    return mxflow;
}
int pos[maxn][maxn][3], cntpoint;
signed main(){
    n = read(); m = read();int S = ++cntpoint, T = ++cntpoint, sum = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            for(int k = 0;k < 3;k++){
                pos[i][j][k] = ++cntpoint;
                // printf("pos[%d][%d][%d]=%d\n",i,j,k,cntpoint);
            }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            sum += (art = read());
            // puts("type 111111111111");
            addd(S,pos[i][j][0],art);
        }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            sum += (sci = read());
            // puts("type 222222222222");
            addd(pos[i][j][0],T,sci);
        }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            sum += (sart = read());
            // puts("type 333333333333");
            addd(S,pos[i][j][1],sart);
        }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            sum += (ssci = read());
            // puts("type 444444444444");
            addd(pos[i][j][2],T,ssci);
        }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            for(int l = 0;l < 5;l++){
                int nx = dx[l] + i, ny = dy[l] + j;
                if(nx < 1 || ny < 1 || nx > n || ny > m)continue;
                // puts("type 55555555555");
                addd(pos[nx][ny][1],pos[i][j][0], INF);
                addd(pos[i][j][0],pos[nx][ny][2],INF);
            }
    printf("%d\n",sum - maxflow(S,T));
    // for(int u = 1;u <= cntpoint;u++)
    //     for(int i = head[u];i;i = e[i].nexte)
    //         printf("i = %d,%d -> %d, cap = %d, flow = %d\n",i,u,e[i].to,e[i].cap,e[i].flow);
    return 0;
}