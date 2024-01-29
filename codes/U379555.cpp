#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch =getchar();}
    return x * f;
}
const int maxn = 510, mod = 998244353;
int a[maxn][maxn], n;
int f[maxn][maxn], g[maxn][maxn];
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0,-1, 1, 0};
int ans = 0;

int dfs(int x,int y){
    if(f[x][y] != -1)return f[x][y];f[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
        if(a[nx][ny] > a[x][y]){f[x][y] = (f[x][y] + dfs(nx,ny)) % mod;}
        else {f[x][y]++;if(f[x][y] >= mod)f[x][y] -= mod;}
    }
    return f[x][y];
}
int dfs1(int x,int y){
    if(g[x][y] != -1)return g[x][y];g[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
        if(a[nx][ny] < a[x][y]){g[x][y] = (g[x][y] + dfs1(nx,ny)) % mod;}
    }
    return g[x][y];
}

signed main(){
    n = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            a[i][j] = read(),f[i][j] = g[i][j] = -1;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            ans = (ans + (f[i][j] = dfs(i,j))) % mod;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            g[i][j] = dfs1(i,j);
    int q = read();
    for(int i = 1;i <= q;i++){
        int x = read(), y = read();
        printf("%lld\n",(ans - (f[x][y] - 1) * g[x][y] % mod + mod) % mod);
    }
    return 0;
}