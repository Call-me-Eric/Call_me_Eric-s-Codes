#include<bits/stdc++.h>
#define ll long long
#define TT int
using namespace std;
inline TT read(){
    TT x  = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 100;
int n, m;
int dis[maxn][maxn];
bool f[maxn][maxn][65];
int main(){
    n = read();m = read();
    memset(dis,0x3f,sizeof(dis));
    int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        dis[u][v] = 1;f[u][v][0] = 1;
    }
    for(int k = 1;k <= 64;k++){
        for(int o = 1;o <= n;o++)
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(f[i][o][k - 1] && f[o][j][k - 1]){
                    f[i][j][k] = 1; dis[i][j] = 1;
                }
            }
        }
    }
    for(int k = 1;k <= n;k++){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(dis[i][j] > dis[i][k] + dis[k][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    printf("%d\n",dis[1][n]);
    return 0;
}