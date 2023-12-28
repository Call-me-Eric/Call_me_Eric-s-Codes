#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 100100,maxc = 1000100, maxp = maxn + maxc * 2;
int n, R, C;
int head[maxn + maxc * 2], tot, head2[maxp],tot2;
struct edge{
    int topoint, nextedge;
    edge(int topoint = 0, int nextedge = 0){
        this->nextedge = nextedge;
        this->topoint = topoint;
    }
}e[maxp],e2[maxp];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
void add2(int u,int v){e2[++tot2] = edge(v,head2[u]);head2[u] = tot2;}
map<pair<int,int> , int> mapp;
const int dx[8] = { 1, 1, 1, 0, 0,-1,-1,-1};
const int dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

int xx[maxn], yy[maxn];
int dfn[maxp],low[maxp], ind;
int col[maxp], color;stack<int> stk;
int dis[maxp], d[maxp],disa[maxp], f[maxp];
void Tarjan(int u){
    dfn[u] = low[u] = ++ind;
    stk.push(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!col[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        int v = 0;color++;
        do{
            v = stk.top();stk.pop();
            col[v] = color;
            disa[color] += dis[v];
        }while(v != u);
    }
}
signed main(){
    int x, y, t;
    n = read(); R = read(); C = read();
    for(int i = 1;i <= n;i++){
        x = read(); y = read(); t = read();
        dis[R + C + i] = 1;
        add(x,R + C + i);add(y + R,R + C + i);
        if(t == 1) add(R + C + i,x);
        else if(t == 2) add(R + C + i,y + R);
        else {xx[i] = x;yy[i] = y;}
        mapp[make_pair(x,y)] = i;
    }
    for(int i = 1;i <= n;i++)
        if(xx[i])
            for(int j = 0;j < 8;j++)
                if(mapp[make_pair(xx[i] + dx[j],yy[i] + dy[j])])
                    add(R + C + i,mapp[make_pair(xx[i] + dx[j],yy[i] + dy[j])] + R + C);
    for(int i = 1;i <= R + C + n;i++)if(!dfn[i])Tarjan(i);
    for(int u = 1;u <= R + C + n;u++)
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(col[u] != col[v]){
                add2(col[u],col[v]);
                d[col[v]]++;
            }
        }
    queue<int> que;
    for(int i = 1;i <= color;i++){
        if(!d[i]){que.push(i);f[i] = disa[i];}
    }
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head2[u];i;i = e2[i].nextedge){
            int v = e2[i].topoint;
            d[v]--;
            f[v] = max(f[v],f[u] + disa[v]);
            if(!d[v])que.push(v);
        }
    }
    int ans = 0;
    for(int i = 1;i <= color;i++){
        ans = max(ans,f[i]);
    }
    printf("%d\n",ans);
    return 0;
}