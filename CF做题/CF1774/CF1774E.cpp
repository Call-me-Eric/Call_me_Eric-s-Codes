#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, d;

vector<int> edg[maxn];

int dep[maxn],mdep[maxn][2];
bool book[maxn][2];
bool need[maxn][2];

void dfs(int u,int f,int opt){
    dep[u] = dep[f] + 1;
    if(need[u][opt])book[u][opt] = 1;
    if(need[u][!opt])mdep[u][!opt] = dep[u];
    for(int v : edg[u]){
        if(v != f){
            dfs(v, u,opt);
            mdep[u][!opt] = max(mdep[u][!opt],mdep[v][!opt]);
            book[u][opt] |= book[v][opt];
        }
    }
    if(mdep[u][!opt] - dep[u] >= d)book[u][opt] |= 1;
}

signed main(){
    n = read(); d = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v); edg[v].push_back(u);
    }
    for(int i = read();i;i--)need[read()][0] = 1;
    for(int i = read();i;i--)need[read()][1] = 1;
    dfs(1,0,0); dfs(1,0,1);
    int ans = 4 * (n - 1);
    for(int i = 2;i <= n;i++){ans -= (2 * (!book[i][0]) + 2 * (!book[i][1]));}
    printf("%d\n",ans);
    return 0;
}