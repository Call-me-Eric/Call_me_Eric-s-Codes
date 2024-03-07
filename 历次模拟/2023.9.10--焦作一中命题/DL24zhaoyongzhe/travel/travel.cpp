#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, k;
int val[maxn], a[maxn];

int head[maxn], tot;
struct edge{
    int to, nexte;
    edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int dp[maxn], son[maxn];
void dfs(int u,int f){
    if(k == 1)a[u] = val[u];
    else a[u] = 0;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == f)continue;
        dfs(v, u);
        if(k == 1){
            if(dp[v] > dp[son[u]]){
                son[u] = v;
            }
        }
        else if(k == 2){
            if(dp[v] > dp[son[u]]){
                son[u] = v;
            }
            a[u] += val[v];
        }
        // else{}
    }
    dp[u] = dp[son[u]] + a[u];
}
bool book[maxn];
int path[maxn << 2], cnt;
void putans(int u,int f){
    if(u == 0)return;
    if(!book[u]){ path[++cnt] = u;book[u] = 1;}
    if(k == 1){
        if(son[u])putans(son[u],u);
    }
    else if(k == 2){
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;if(v == f || v == son[u])continue;
            if(!book[v]){path[++cnt] = v;book[v] = 1;}
        }
        if(son[u])  putans(son[u],u);
    }
}

signed main(){
    freopen("travel.in","r",stdin);
    freopen("travel.out","w",stdout);
    n = read(); k = read(); int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v =  read();
        add(u , v);add( v, u);
    }
    for(int i = 1;i <= n;i++)val[i] = read();
    dfs(1, 0);
    if(k == 2)dp[1] += val[1];
    printf("%lld\n",dp[1]);
    putans(1,0);
    printf("%lld\n",cnt);
    for(int i = 1;i <= cnt;i++)printf("%lld ",path[i]);
    puts("");
    return 0;
}