#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 100 + 10;
int n, m, S, T;
int e[maxn][maxn];
int K, st[maxn], ed[maxn];
bool avail[maxn];
int tot[maxn][maxn];
int deg[maxn][maxn];
int f[maxn][maxn];
signed main(){
    n = read(); m = read(); S = read(); T = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            e[i][j] = (i != j) * (0x3f3f3f3f);
    for(int i = 1;i <= m;i++){int u = read(), v = read();e[u][v] = 1;}

    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                e[i][j] = min(e[i][j],e[i][k] + e[k][j]);

    K = read();
    for(int i = 1;i <= K;i++){st[i] = read();ed[i] = read();avail[i] = e[st[i]][ed[i]] != 0x3f3f3f3f;}
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= K;j++){
            if(!avail[j] || e[st[j]][i] + e[i][ed[j]] != e[st[j]][ed[j]])continue;
            tot[j][e[st[j]][i]]++;
            for(int k = 1;k <= n;k++)
                if(e[i][k] == 1 && e[st[j]][i] + e[i][k] + e[k][ed[j]] == e[st[j]][ed[j]])
                    deg[i][j]++;
        }
    memset(f,0x3f,sizeof(f));
    for(int i = 1;i <= K;i++){
        if(avail[i] && e[st[i]][T] + e[T][ed[i]] == e[st[i]][ed[i]])
            f[T][i] = 0;
    }
    for(int k = 0;k < n;k++){
        queue<pair<int,int> > que;
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= K;j++)
                if(f[i][j] == k){que.push(make_pair(i, j));}
        while(!que.empty()){
            int x = que.front().first, i = que.front().second;que.pop();
            if(tot[i][e[st[i]][x]] == 1){
                if(x == S){printf("%d\n",f[x][i] + 1);return 0;}
                for(int j = 1;j <= K;j++)
                    if(avail[j] && e[st[j]][x] + e[x][ed[j]] == e[st[j]][ed[j]])
                        f[x][j] = min(f[x][j],f[x][i] + 1);
            }
            for(int y = 1;y <= n;y++){
                if(e[y][x] == 1 && e[st[i]][y] + e[y][x] + e[x][ed[i]] == e[st[i]][ed[i]]){
                    if(!--deg[y][i] && f[y][i] > f[x][i]){
                        f[y][i] = f[x][i];
                        que.push(make_pair(y,i));
                    }
                }
            }
        }
    }
    puts("-1");
    return 0;
}