#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e4 + 10, maxm = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m;

struct edge{
    int to, nexte, times, cap, flow;
    edge(int to = 0,int ne = 0,int ti = 0,int ca = 0,int fl = 0):to(to),nexte(ne),times(ti),cap(ca),flow(fl){}
}e[maxm << 1];
int head[maxn], tot = 1;
void add(int u,int v,int times,int cap){e[++tot] = edge(v,head[u],times,cap);head[u] = tot;}
void addd(int u,int v,int ti,int cap){add(u, v, ti,cap);add(v, u, ti, 0);}

vector<int> tmp;
int lim, S, T;
int cur[maxn], dis[maxn];
int dfs(int u,int rest){
    // printf("u = %d\n",u);
    if(u == T || !rest)return rest;
    int res = 0;
    for(int i = cur[u];i;i = e[i].nexte){
        cur[u] = i;int v = e[i].to;
        if(dis[v] != dis[u] + 1 || e[i].cap - e[i].flow <= 0 || e[i].times > lim)continue;
        int tmp = dfs(v,min(e[i].cap - e[i].flow,rest));
        if(tmp == 0)dis[v] = INF;
        rest -= tmp;e[i].flow += tmp;res += tmp;e[i ^ 1].flow -= tmp;
    }
    return res;
}
bool bfs(){
    memset(cur,0,sizeof(cur));memset(dis,0x3f,sizeof(dis));
    queue<int> que;que.push(S);cur[S] = head[S];dis[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        // printf("u=%d\n",u);
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] != INF || e[i].times > lim || e[i].cap <= e[i].flow)continue;
            dis[v] = dis[u] + 1;cur[v] = head[v];que.push(v);
            if(v == T)return 1;
        }
    }
    return 0;
}
int mxflow(){
    int mxflow = 0;
    for(int i = 1;i <= tot;i++){e[i].flow = 0;}
    // printf("lim = %d\n",lim);
    while(bfs()){
        // for(int i = 1;i <= n * 2 + 3;i++){printf("dis[%d]=%d\n",i,dis[i]);}
        mxflow += dfs(S,INF);
        // printf("mxflow=%d\n",mxflow);
    }
    // for(int u = 1;u <= n * 2 + 2;u++){
    //     printf("u = %d->\n",u);
    //     for(int i = head[u];i;i = e[i].nexte){
    //         printf("v=%d flow=%d times=%d\n",e[i].to,e[i].flow,e[i].times);
    //     }
    // }
    // getchar();
    return mxflow;
}

signed main(){
    n = read(); m = read();int u, v, w;S = (n << 1) + 2,T = (n << 1) + 1;
    for(int i = 1;i <= m;i++){
        u = read(); v = read() + n;w = read();
        addd(u, v, w, 1);tmp.push_back(w);
    }
    for(int i = 1;i <= n;i++){addd(S,i,0,1);addd(i + n,T,0,1);}
    sort(tmp.begin(),tmp.end());
    int l = 0, r = tmp.size() - 1, mid = 0, ans = -1;
    while(l <= r){
        mid = l + r >> 1;lim = tmp[mid];
        if(mxflow() >= n){r = mid - 1;ans = mid;}
        else l = mid + 1;
    }
    printf("%d\n",ans == -1 ? -1 : tmp[ans]);
    return 0;
}