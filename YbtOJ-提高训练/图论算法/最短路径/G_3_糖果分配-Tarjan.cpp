
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 100010;

int dis[maxn];bool book[maxn];
queue<int> que;

int head[maxn], tot, totequal, rtot, rhead[maxn], d[maxn];
struct edge{int topoint, nextedge, weight;}e[maxn * 2],re[maxn * 2];
void add(int u,int v,int w){e[++tot] = {v,head[u],w};head[u] = tot;}
void radd(int u,int v,int w){re[++rtot] = {v,rhead[u],w};rhead[u] = rtot;}

stack<int> stk;
int dfn[maxn], low[maxn], ind;
int col[maxn], color, size[maxn];
bool instk[maxn];
void Tarjan(int u){
    dfn[u] = low[u] = ++ind; instk[u] = true;
    stk.push(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instk[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(dfn[u] == low[u]){
        color++;
        col[u] = color;
        instk[u] = false;
        size[color]++;
        while(stk.top() != u){
            instk[stk.top()] = false;
            col[stk.top()] = color;
            stk.pop();
            size[color]++;
        }
        stk.pop();
    }
}

signed main(){
    n = read(); m = read();
    int opt, u, v;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();
        switch(opt){
            case 1:{add(u,v,0);add(v,u,0);break;}
            case 2:{add(u,v,1);break;}
            case 3:{add(v,u,0);break;}
            case 4:{add(v,u,1);break;}
            case 5:{add(u,v,0);break;}
            default:{break;}
        }
    }
    //Tarjan
    for(int i = 1;i <= n;i++){
        if(!dfn[i])Tarjan(i);
    }
    //rebuild map
    for(int u = 1;u <= n;u++){
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(w && col[u] == col[v]){
                puts("-1");
                return 0;
            }
            if(col[u] != col[v]){
                radd(col[u],col[v],w);
                d[col[v]]++;
            }
        }
    }
    //topsort
    memset(dis,-0x3f,sizeof(dis));
    for(int i = 1;i <= color;i++){
        if(!d[i]){
            que.push(i);
            dis[i] = 1;
        }
    }
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = rhead[u];i;i = re[i].nextedge){
            int v = re[i].topoint,w = re[i].weight;
            d[v]--;
            if(!d[v]) que.push(v);
            dis[v] = max(dis[v],dis[u] + w);
        }
    }
    int ans = 0;
    for(int i = 1;i <= color;i++)ans += dis[i] * size[i];
    printf("%lld\n",ans);
    return 0;
}