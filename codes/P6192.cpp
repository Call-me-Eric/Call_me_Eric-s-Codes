#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e2 + 10, maxm = 5e2 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, m, k;
int f[maxn][1 << 11];
int e[maxn][maxn];
int id[maxn];
bool vis[maxn];

void main(){
    n = read(); m = read(); k = read();
    memset(e,0x3f,sizeof(e));memset(f,0x3f,sizeof(f));
    for(int i = 1;i <= n;i++){e[i][i] = 0;}
    for(int i = 1;i <= m;i++){
        int u = read(), v = read(), w = read();
        e[u][v] = e[v][u] = min(e[u][v],w);
    }
    for(int i = 1;i <= k;i++)id[i] = read();
    for(int k = 1;k <= n;k++)for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)e[i][j] = min(e[i][j],e[i][k] + e[k][j]);
    for(int i = 1;i < (1 << k);i++){
        for(int j = i;j;j = (j - 1) & i)for(int l = 1;l <= n;l++)
            f[l][i] = min(f[l][i],f[l][j] + f[l][i - j]);
        if(!(i & (i - 1)))for(int l = 0;l < k;l++)//只有一个点
            if((i >> l) & 1){f[id[l + 1]][i] = 0;break;}
        for(int j = 1;j <= n;j++)vis[j] = 0;
        for(int x = 1;x <= n;x++){
            int p = 0;
            for(int j = 1;j <= n;j++)if(!vis[j] && (!p || f[j][i] < f[p][i]))p = j;
            if(f[p][i] >= INF)break;vis[p] = 1;
            for(int j = 1;j <= n;j++)f[j][i] = min(f[j][i],f[p][i] + e[p][j]);
        }
    }
    int ans = INF;
    for(int i = 1;i <= n;i++)ans = min(ans,f[i][(1 << k) - 1]);
    printf("%lld\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}