#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, q;
const int maxn = 110, maxm = 10010;
bool e[maxn][maxn];
signed main(){
    m = read(); n = read(); q = read();
    for(int i = 1;i <= m;i++)e[read()][read()] = true;
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            if(e[i][k])
            for(int j = 1;j <= n;j++)
                if(e[i][k] && e[k][j])e[i][j] = true;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(e[i][j] && e[j][i]){puts("10000words to copy");return 0;}
    for(int i = 1;i <= q;i++){
        int u = read(), v = read();
        if(e[u][v] || e[v][u])
            puts(e[u][v] ? "YES" : "NO");
        else puts("DK");
    }
    return 0;
}
