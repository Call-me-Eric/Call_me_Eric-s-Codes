#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f =  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e6 + 10, INF = 0x3f3f3f3f;

int n, m;
int head[maxn], tot;
struct edge1{
    int from, to, wei;
    edge1(int f = 0,int to = 0,int we = 0):from(f),to(to),wei(we){}
    friend bool operator < (edge1 a,edge1 b){return a.wei < b.wei;}
}e1[maxn];

struct edge{
    int to, nexte, cap,flow;
    edge(int t = 0,int ne = 0,int ca = 0,int fl = 0):to(t),nexte(ne),cap(ca),flow(fl){}
}e[maxn * 4];
void add(int u,int v,int cap,int flow = 0){e[++tot] = edge(v,head[u],cap,flow);head[u] = tot;}
void addd(int u,int v,int cap,int flow = 0){add(u,v,cap);add(v,u,cap);}

queue<int> que;
int dis[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    if(u == T || !flow)return flow;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        cur[u] = i;int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dis[v] == dis[u] + 1)){
            // printf("u = %d,v = %d, restflow = %d\n",u,v,e[i].cap - e[i].flow);
            int tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(!tmp)dis[v] = INF;
            e[i].flow += tmp;res += tmp;
            e[i ^ 1].flow -= tmp;flow -= tmp;
        }
    }
    return res;
}
bool bfs(int S,int T){
    while(!que.empty())que.pop();memset(cur,0,sizeof(cur));
    memset(dis,0x3f,sizeof(dis));
    que.push(S);dis[S] = 0;cur[S] = head[S];
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dis[v] == INF){
                dis[v] = dis[u] + 1;cur[v] = head[v];que.push(v);
            }
        }
    }
    // for(int i = 1;i <= n;i++)printf("dis[%d]=%d\n",i,dis[i]);
    // for(int u = 1;u <= n;u++){
    //     for(int i = head[u];i;i = e[i].nexte){
    //         int v = e[i].to, cap = e[i].cap, flow = e[i].flow;
            // printf("%d -> %d : cap = %d, flow = %d\n",u,v,cap,flow);
    //     }
    // }
    // getchar();
    return dis[T] < INF;
}
int maxflow(int S,int T){
    int mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}

signed main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){u = read(); v = read(); w= read(); e1[i] = edge1(u,v,w);}
    sort(e1 + 1,e1 + 1 + m); u = read(); v = read(); w= read();
    
    memset(head,0,sizeof(head));tot = 1;
    for(int i = 1;i <= m;i++){
        if(e1[i].wei < w)addd(e1[i].from,e1[i].to,1);
        else break;
    }
    int ans1 = maxflow(u,v);

    memset(head,0,sizeof(head));tot = 1;
    memset(e,0,sizeof(e));
    for(int i = m;i >= 1;i--){
        // printf("%d - > %d wei = %d\n",e1[i].from,e1[i].to,e1[i].wei);
        if(e1[i].wei > w)addd(e1[i].from,e1[i].to,1);
        else break;
    }
    int ans2 = maxflow(u,v);

    printf("%d\n",ans1 + ans2);
    return 0;
}