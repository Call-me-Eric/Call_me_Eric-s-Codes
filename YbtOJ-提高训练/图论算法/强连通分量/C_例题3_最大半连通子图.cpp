#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, mod;
const int maxn = 1e6 + 10;
//map
int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int topoint = 0,int nextedge = 0){
        this->nextedge = nextedge;
        this->topoint = topoint;
    }
}e[maxn];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
//Tarjan && rebuild map
vector<int> e2[maxn];
int dfn[maxn], low[maxn],ind;
int col[maxn], color,size[maxn];
stack<int> stk;
void Tarjan(int u){
    stk.push(u);
    dfn[u] = low[u] = ++ind;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(!col[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        int v = 0;color++;
        do{
            v = stk.top();
            stk.pop();
            col[v] = color;
            size[color]++;
        }while(v != u);
    }
}
//Topsort && TopDP
int f[maxn], ans[maxn], d[maxn];
queue<int> que;
signed main(){
    n = read(); m = read(); mod = read();
    for(int i = 1;i <= m;i++)add(read(),read());
    for(int i = 1;i <= n;i++){if(!dfn[i])Tarjan(i);}
    for(int u = 1;u <= n;u++){
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(col[u] != col[v]){
                e2[col[u]].push_back(col[v]);
            }
        }
    }
    for(int i = 1;i <= color;i++){
        sort(e2[i].begin(),e2[i].end());
        e2[i].erase(unique(e2[i].begin(),e2[i].end()),e2[i].end());
        for(int j = 0, len = e2[i].size();j < len;j++){d[e2[i][j]]++;}
    }
    for(int i = 1;i <= color;i++){
        if(!d[i]){
            que.push(i);
            f[i] = size[i];
            ans[i] = 1;
        }
    }
    while(!que.empty()){
        int x = que.front();que.pop();
        for(int j = 0, len = e2[x].size();j < len;j++){
            int y = e2[x][j];d[y]--;
            if(f[y] < f[x] + size[y]){
                f[y] = f[x] + size[y];
                ans[y] = ans[x];
            }
            else if(f[y] == f[x] + size[y]){
                ans[y] += ans[x];
                ans[y] %= mod;
            }
            if(!d[y])que.push(y);
        }
    }
    int _f = -1, _ans = 0;
    for(int x = 1;x <= color;x++){
        if(f[x] > _f){_ans = ans[x];_f = f[x];}
        else if(f[x] == _f){
            _ans += ans[x];
            _ans %= mod;
        }
    }
    printf("%d\n%d\n",_f,_ans);
    return 0;
}