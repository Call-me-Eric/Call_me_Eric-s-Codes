#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10, maxm = 5e4 + 10;
int head[maxn], tot;
bool book[maxn];//book[i] -> i有没有被搜索过
int dfn[maxn], low[maxn];//dfn[i] -> i的dfs序 low[i] -> i能回溯到的最小dfs序
int num, col;//num -> 当前的dfs序 col -> 强连通分量总数
int co[maxn];//co[i] -> i所在的强连通分量标号
stack<int> stk;//stk -> 记录强连通分量
int indegree[maxn];// indegree[i] -> i的入度
int sizeconnect[maxn];//sizeconnect[i] -> 第i个强连通分量的大小
int weight[maxn];//weight -> i的点权
struct edge{
    int nextedge, topoint;
}e[maxn];
int n, m;
void add(int u,int v){
    e[++tot].nextedge = head[u];
    head[u] = tot;
    e[tot].topoint = v;
}
void Tarjan(int u){
    dfn[u] = low[u] = ++num;
    book[u] = 1;
    stk.push(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(book[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]){//u是强连通分量的起点
        ++col; int k;
        do{
            k = stk.top(); stk.pop();
            co[k] = col;
            book[k] = 0;
            sizeconnect[col]++;
        }while(k != u);
    }
}
int main(){
    n = read(); m = read();
    int x, y;
    for(int i = 1;i <= n;i++){
        weight[i] = read();
    }
    for(int i = 1;i <= m;i++){
        x = read(); y = read();
    }
    for(int i = 1;i <= n;i++){
        if(!dfn[i])Tarjan(i);
    }
    return 0;
}