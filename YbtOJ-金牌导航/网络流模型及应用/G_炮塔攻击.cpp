#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e2 + 10,maxm = 5e5 + 10, INF = 0x3f3f3f3f;
int n, m;
int id[2][maxn][maxn], total;

int head[maxm], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}

int dep[maxm], cur[maxm];
int dfs(int u,int flow,int T){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0)dep[v] = INF;
            e[i].flow += tmp; e[i ^ 1].flow -= tmp;
            flow -= tmp;rest += tmp;
            if(!flow)return rest;
        }
    }
    return rest;
}
bool bfs(int S,int T){
    queue<int> que;
    for(int i = 1;i <= total;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}

int a[maxn][maxn], mx[maxn][maxn];
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = { 0, 0,-1, 1};

signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            a[i][j] = read();
            id[0][i][j] = ++total; id[1][i][j] = ++total;
            addd(id[0][i][j],id[1][i][j],INF);
        }
    int S = ++total;int T = ++total, ans = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++){
            if(a[i][j] < 0){
                int x = 0, posi = i, posj = j;
                int nx = i, ny = j;
                int opt = -a[i][j] - 1;
                while(1){
                    nx += dx[opt];ny += dy[opt];
                    if(!(nx > 0 && nx <= n && ny > 0 && ny <= m))break;
                    if(a[nx][ny] > x){
                        x = a[nx][ny];
                        posi = nx;posj = ny;
                    }
                }
                if(posi == i && posj == j)continue;
                mx[i][j] = x;ans += x;
                if(a[i][j] >= -2){
                    nx = posi;ny = posj;a[i][j] = 0;
                    while(1){
                        addd(id[1][nx][ny],id[1][nx - dx[opt]][ny - dy[opt]],mx[i][j] - a[nx - dx[opt]][ny - dy[opt]]);
                        nx -= dx[opt];ny -= dy[opt];
                        if(nx == i && ny == j)break;
                    }
                    addd(id[1][i][j],T,INF);
                }
                else{
                    nx = i;ny = j;a[i][j] = 0;
                    while(1){
                        addd(id[0][nx][ny],id[0][nx + dx[opt]][ny + dy[opt]],mx[i][j] - a[nx][ny]);
                        nx += dx[opt];ny += dy[opt];
                        if(nx == posi && ny == posj)break;
                    }
                    addd(S,id[0][i][j],INF);
                }
            }
        }
    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= m;j++){
    //         printf("(%d,%d)id = %d, %d\n",i,j,id[0][i][j],id[1][i][j]);
    //     }
    // }
    // for(int i = 2;i <= tot;i += 2){
    //     printf("%d %d %d %d\n",e[i ^ 1].to,e[i].to,e[i].cap,e[i].flow);
    // }
    printf("%d\n",ans - Dinic(S,T));
    return 0;
}
/*
6 5
-4 0 9 3 2
-3 -4 4 7 6
1 0 -1 -4 8
0 -2 -2 -2 -1
-4 3 6 0 0
9 0 8 0 -1

*/