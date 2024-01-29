#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char  ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}

const int maxn = 1e3 + 10, mod = 1e9 + 7;
int n, k;

int head[maxn], tot;
struct edge{int to ,nexte;edge(int to = 0,int ne = 0):to(to),nexte(ne){}}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int f[maxn][maxn * 5][6];
int tmp[maxn * 5][6];
int siz[maxn];
void dfs(int u,int fa){
    siz[u] = 1;
    for(int i = 1;i <= k;i++){f[u][0][i] = 1;}
    for(int ed = head[u];ed;ed = e[ed].nexte){
        int v = e[ed].to; if(v == fa)continue;
        dfs(v,u); memset(tmp,0,sizeof(tmp));
        for(int i = 0;i <= k * siz[u];i++){
        for(int j = 0;j <= k;j++){
            if(f[u][i][j])
            for(int x = 0;x <= k * siz[v];x++){
            for(int y = 0;y <= k;y++){
                if(f[v][x][y]){
                    tmp[i + x + y][max(i + x + y,i + j + x) - (i + x + y)] =
                    (tmp[i + x + y][max(i + x + y,i + j + x) - (i + x + y)] + 
                    f[u][i][j] * f[v][x][y] % mod) % mod;
                }
            }
            }
        }
        }
        memcpy(f[u],tmp,sizeof(tmp));
        siz[u] += siz[v];
    }
}

signed main(){
    n = read(); k = read(); int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v); add(v, u);
    }
    dfs(1,0);
    for(int i = 1;i <= k * n;i++){
        int ans = 0;
        for(int j = 0;j <= min(i,k);j++){ans = (f[1][i - j][j] + ans) % mod;}
        printf("%lld\n",ans);
    }
    return 0;
}