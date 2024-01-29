#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m, Q;
const int maxn = 210, maxQ = 50010;
int e[maxn][maxn][maxn], t[maxn];
signed main(){
    int u, v, ti;
    n = read(); m = read();
    memset(e,0x3f,sizeof(e));
    for(int i = 0;i < n;i++){t[i] = read();e[0][i][i] = 0;}
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        e[0][u][v] = e[0][v][u] = read();
    }
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            e[0][i][j] = min(e[0][i][0] + e[0][0][j], e[0][i][j]);
    for(int k = 1;k < n;k++)
        for(int i = 0;i < n;i++)
            for(int j = 0;j < n;j++)
                e[k][i][j] = min(e[k - 1][i][j],e[k - 1][i][k] + e[k - 1][k][j]);
    Q = read();
    for(int i = 1;i <= Q;i++){
        u = read(); v = read(); ti = read();
        int pos = upper_bound(t,t + n,ti) - t - 1;
        if(!(t[u] > ti || t[v] > ti || e[pos][u][v] == 0x3f3f3f3f))printf("%d\n",e[pos][u][v]);
        else puts("-1");
    }
    return 0;
}