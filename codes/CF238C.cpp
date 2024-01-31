#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10;
int n;
int f[maxn][3][2];
vector<pair<int,int> > edg[maxn];
void dfs(int u,int fa){
    f[u][1][1] = 0;
    for(auto i : edg[u]){
        int v = i.first, w = i.second;
        if(v != fa){
            int g[3][2];memset(g,0x3f,sizeof(g));
            dfs(v, u);
            for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3 - i;j++)
                for(int kx = 0;kx < 2;kx++)
                for(int ky = 0;ky < 2;ky++){
                    g[i + j][kx] = min(g[i + j][kx], w + f[u][i][kx] + f[v][j + ky][ky]);
                    g[i + j][0 ] = min(g[i + j][0 ],!w + f[u][i + kx][kx] + f[v][j][ky]);
                }
            memcpy(f[u],g,sizeof(g));
        }
    }
}
signed main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(make_pair(v, 0));
        edg[v].push_back(make_pair(u, 1));
    }
    memset(f,0x3f,sizeof(f));
    dfs(1, 0);int ans = 0x3f3f3f3f;
    for(int i = 0;i <= 2;i++)
        for(int j = 0;j < 2;j++)
            ans = min(ans,f[1][i][j]);
    printf("%d\n",ans);
    return 0;
}