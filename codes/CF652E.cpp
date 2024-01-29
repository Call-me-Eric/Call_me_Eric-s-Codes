#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int low[maxn], dfn[maxn], idx;
bool cut[maxn << 1];//cut[i] == 1 <=> i is bridge 
void tarjan(int u,int f){
    low[u] = dfn[u] = ++idx;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u],low[v]);
            if(low[v] > dfn[u]){cut[i] = cut[i ^ 1] = 1;}
        }
        else if(dfn[v] < dfn[u] && v != f)
            low[u] = min(low[u],dfn[v]);
    }
}

int belong[maxn], totblock;
int col[maxn];
void dfs(int u,int f){
    belong[u] = totblock;
    for(int i = head[u];i;i = e[i].nexte){
        if(cut[i])continue; int v = e[i].to;
        if(e[i].wei)col[totblock] |= 1;
        if(!belong[v])dfs(v, u);
    }
}

int head1[maxn], tot1 = 1;edge e1[maxn << 1];
void add1(int u,int v,int w){e1[++tot1] = edge(v,head1[u],w);head1[u] = tot1;}

int fa[maxn], fcol[maxn], dep[maxn];
void dfs1(int u,int f){
    // printf("dep[u = %d] = %d,  f = %d\n",u,dep[u],f);
    for(int i = head1[u];i;i = e1[i].nexte){
        int v = e1[i].to, w = e1[i].wei;
        if(v == f)continue;
        fa[v] = u;fcol[v] = w;
        dep[v] = dep[u] + 1;dfs1(v, u);
    }
}

signed main(){
    n = read(); m =  read();int u, v, w, S, T;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u, v, w);add(v, u, w);
    }
    S = read(); T = read();
// puts("1111111");    
    tarjan(1, 1);
// puts("2222222");
    for(int i = 1;i <= n;i++)if(!belong[i]){totblock++;dfs(i,i);}
    for(int i = 2;i <= tot;i += 2){
        int u = e[i].to, v = e[i ^ 1].to;
        if(cut[i]){
            add1(belong[u],belong[v],e[i].wei);
            add1(belong[v],belong[u],e[i].wei);
            // printf("cut on belong[%d] = %d belong[%d] = %d\n",u,belong[u], v,belong[v]);
        }
    }
    fa[1] = 1;dep[1] = 1;dfs1(1,1);int ans = 0;
    if(belong[S] == belong[T]){
        ans |= col[belong[S]];
        puts(ans ? "YES" : "NO");
        return 0;
    }
    S = belong[S],T = belong[T];
    if(dep[S] < dep[T])swap(S,T);
// puts("3333333");
    while(dep[S] > dep[T]){
        // printf("dep[S = %d] = %d, dep[T = %d] = %d\n",S,dep[S],T,dep[T]);getchar();
        ans |= (fcol[S] | col[S]);S = fa[S];
    }
// puts("4444444");
    if(S != T){
        while(S != T){
            ans |= (fcol[S] | fcol[T]);
            ans |= (col[S] | col[T]);
            S = fa[S]; T = fa[T];
        }
    }
    ans |= col[S];
    puts(ans ? "YES" : "NO");
    return 0;
}