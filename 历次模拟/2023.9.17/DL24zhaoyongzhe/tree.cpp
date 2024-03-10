#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, col;
    edge(int t = 0,int ne = 0,int c = 0):to(t),nexte(ne),col(c){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dep[maxn], fa[maxn], fedg[maxn];
void dfs(int u,int f){
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;if(v == f)continue;
        dep[v] = dep[u] + 1;fa[v] = u; fedg[v] = i;
        dfs(v, u);
    }
}

void upd(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    while(dep[u] != dep[v]){
        e[fedg[u]].col ^= 1;
        e[fedg[u] ^ 1].col ^= 1;
        u = fa[u];
    }
    if(u == v)return;
    while(u != v){
        e[fedg[u]].col ^= 1;
        e[fedg[u] ^ 1].col ^= 1;
        u = fa[u];
        e[fedg[v]].col ^= 1;
        e[fedg[v] ^ 1].col ^= 1;
        v = fa[v];
    }
}
int query(int x,int f){
    int cnt = 1;
    for(int i = head[x];i;i = e[i].nexte){
        int v = e[i].to;
        if(e[i].col || v == f)continue;
        cnt += query(v, x);
    }
    return cnt;
}

signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    n = read(); m = read(); int u, v, opt;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    dep[1] = 1; dfs(1, 0);
    for(int test = 1;test <= m;test ++){
        opt = read(); u = read();
        if(opt == 1){
            v = read(); upd(u, v);
        }
        else{
            printf("%d\n",query(u,u));
        }
    }
    return 0;
}