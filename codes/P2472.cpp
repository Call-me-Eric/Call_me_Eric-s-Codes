#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 21 * 21 * 3, INF = 0x3f3f3f3f;
const int dx[60] = {-1,0,0,1,-2,-1,-1,0,0,1,1,2,-3,-2,-2,-1,-1,0,0,1,1,2,2,3,-4,-3,-3,-2,-2,-1,-1,0,0,1,1,2,2,3,3,4};
const int dy[60] = {0,-1,1,0,0,1,-1,2,-2,1,-1,0,0,1,-1,2,-2,3,-3,2,-2,1,-1,0,0,-1,1,-2,2,-3,3,-4,4,-3,3,-2,2,-1,1,0};

int head[maxn], cur[maxn], tot = 1;
struct edge{
    int to, nexte, flow;
    edge(int t = 0,int n = 0,int f = 0):to(t),nexte(n),flow(f){}
}e[maxn * maxn];
void add(int u,int v,int flow){e[++tot] = edge(v,head[u],flow); head[u] = tot;}
void addd(int u,int v,int flow){add(u,v,flow);add(v,u,0);}

int n, m, d, S, T;

int dep[maxn];
int dfs(int u,int flow){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].flow));
            if(tmp == 0)dep[v] = INF;
            e[i].flow -= tmp;
            e[i ^ 1].flow += tmp;
            flow -= tmp;
            rest += tmp;
        }
    }
    return rest;
}
bool bfs(){
    queue<int> que;
    for(int i = 1;i <= maxn;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(){
    int maxflow = 0;
    while(bfs()){maxflow += dfs(S,INF);}
    return maxflow;
}

char str[22];
int times[22][22], sum = 0;
inline int idin(int x,int y){return x * m + y + 1;}
inline int idout(int x,int y){return x * m + y + 1 + n * m;}
bool reach(int x1,int y1,int x2,int y2,int limit){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= limit * limit;
}
bool exist(int x,int y){return !(x <= 0 || x > n || y <= 0 || y > m);    }
void addedge(int x,int y,int dist){
    if(x - dist <= 0 || x + dist > n || y - dist <= 0 || y + dist > m){addd(idout(x,y),T,INF);return;}
    for(int i = -dist;i <= dist;i++){
        for(int j = -dist;j <= dist;j++){
            if(!i && !j)continue;
            if(!exist(x + i,y + j) || !times[x + i][y + j])continue;
            if(reach(x,y,x + i,y + j,dist)){
                addd(idout(x,y),idin(x + i,y + j),INF);
            }
        }
    }
    return;
}
int x[maxn],y[maxn];
void init(){
    tot = 1;sum = 0;n = read();m = read();d = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",str + 1);
        // if(i == 1) m = strlen(str + 1);
        for(int j = 1;j <= m;j++){
            times[i][j] = str[j] - '0';
            if(times[i][j])addd(idin(i,j),idout(i,j),times[i][j]);
        }
    }
    S = maxn - 2;T = maxn - 1;
    for(int i = 1;i <= n;i++){
        scanf("%s",str + 1);
        for(int j = 1;j <= m;j++){
            if(times[i][j]){
                addedge(i,j,d);
                if(str[j] == 'L'){
                    sum++;
                    x[sum] = i;y[sum] = j;
                    addd(S,idin(i,j),1);
                }
            }
        }
    }
    for(int i = 1;i <= sum;i++){
        for(int j = 1;j <= sum;j++){
            if(i != j && reach(x[i],y[i],x[j],y[j],d)){
                addd(idout(x[i],y[i]),idin(x[j],y[j]),INF);
            }
        }
    }
}
void getans(){
    int ans = Dinic();
    printf("%d\n",sum - ans);
}
signed main(){
    //int test = read();
    //while(test--){
        init();
        getans();
    //}
    return 0;
}