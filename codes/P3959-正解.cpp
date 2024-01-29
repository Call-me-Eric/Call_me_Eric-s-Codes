#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 13;
int dis[maxn][maxn],trans[1 << maxn][1 << maxn], poww[maxn];
long long f[maxn][1 << maxn];
signed main(){
    int u, v, w;
    n = read(); m = read();
    memset(dis,0x3f,sizeof(dis));
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        if(dis[u][v] > w) dis[u][v] = dis[v][u] = w;
    }
    m = (1 << n); poww[0] = 1;
    for(int i = 1;i <= n;i++)poww[i] = poww[i - 1] * 2;
    for(int i = 0;i < m;i++){
        for(int j = i;j;j = (j - 1) & i){
            bool flag = true; int xorij = (i ^ j);
            for(int k = n - 1;k >= 0;k--){
                if(xorij >= poww[k]){
                    int minn = 0x3f3f3f3f;
                    for(int l = 1;l <= n;l++){
                        if((poww[l - 1] & j) == poww[l - 1]){
                            minn = min(minn,dis[l][k + 1]);
                        }
                    }
                    if(minn == 0x3f3f3f3f){
                        flag = false;
                        break;
                    }
                    trans[j][i] += minn;
                    xorij -= poww[k];
                }
            }
            if(!flag)trans[j][i] = 0x3f3f3f3f;
        }
    }
    memset(f,0x3f,sizeof(f));
    for(int i = 1;i <= n;i++)
        f[1][poww[i - 1]] = 0;
    for(int i = 2;i <= n;i++)
        for(int j = 0;j < m;j++)
            for(int k = j;k;k = (k - 1) & j)
                if(trans[k][j] != 0x3f3f3f3f)
                    f[i][j] = min(f[i][j],f[i - 1][k] + (i - 1) * trans[k][j]);
    long long ans = 0x3f3f3f3f3f3f3f3fLL;
    for(int i = 1;i <= n;i++){
        ans = min(ans,f[i][m - 1]);
    }
    printf("%lld\n",ans);
    return 0;
}