#include<bits/stdc++.h>
using namespace std;
inline int read(){
    // int x = 0, f = 1;char ch = getchar();
    // while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    // while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    // return x * f;
    int x;scanf("%d",&x);return x;
}
const int maxn = 2e3 + 10;
int n;char ch[maxn];

int fa[maxn][maxn], f[maxn][maxn];
vector<int> edg[maxn];
void dfs(int u,int fat,int root){
    fa[u][root] = fat;
    for(int v : edg[u])
        if(v != fat){dfs(v, u,root);}
}

int calc(int u,int v){
    if(u == v)return 1;
    if(u == fa[v][1] || v == fa[u][1]){return 1 + (ch[u] == ch[v]);}
    if(f[u][v])return f[u][v];
    return f[u][v] = max(calc(u,fa[v][u]),max(calc(fa[u][v],v),calc(fa[u][v],fa[v][u]) + (ch[u] == ch[v] ? 2 : 0)));
}

signed main(){
    // #ifndef ONLINE_JUDGE
    // freopen("test.in","r",stdin);
    // #endif
int T = read();
while(T--){
    n = read();scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++){edg[i].clear();}
    for(int i = 1;i < n;i++){
        int u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    for(int i = 1;i <= n;i++){
        dfs(i,i,i);
        for(int j = 1;j <= n;j++)f[i][j] = 0;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            ans = max(ans,calc(i,j));
    printf("%d\n",ans);
}
    return 0;
}